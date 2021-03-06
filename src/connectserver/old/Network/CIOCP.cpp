﻿#include "StdAfx.h"
#include "IOCP.h"
#include "ConnectEngine.h"
#include "ConnectProtocol.h"
#include "Main.h"
#include "generalStructs.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <ace/Dev_Poll_Reactor.h>
#include <ace/TP_Reactor.h>
#include <ace/OS_NS_string.h>
#include <ace/INET_Addr.h>
#include <ace/SString.h>

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

CIOCP IOCP;

class _PER_SOCKET_CONTEXT;

void CIOCP::GiocpInit()
{

#if defined (ACE_HAS_EVENT_POLL) || defined (ACE_HAS_DEV_POLL)
	ACE_Reactor::instance(new ACE_Reactor(new ACE_Dev_Poll_Reactor(ACE::max_handles(), 1), 1), true);
#else
	ACE_Reactor::instance(new ACE_Reactor(new ACE_TP_Reactor(), true), true);
#endif
	ACE_Reactor::instance()->initialized();
}

void CIOCP::ProcessEvents() {

	ACE_Time_Value interval(0, 100000);

	ACE_Reactor::instance()->handle_events(interval);
}

bool CIOCP::CreateListenSocket(WORD uiPort, LPSTR ipAddress)
{
	ACE_INET_Addr bind_addr(uiPort, ipAddress);

	if (g_HostSocket.open(bind_addr, ACE_Reactor::instance()) == -1)
	{
		sLog->outError("MuSQL Game Server can not bind to %s:%d", ipAddress, uiPort);
		return 0;
	}

	return 1;
}

void  CIOCP::CreateUserData(ACE_HANDLE handle)
{
	criti.lock();

	//boost::uuids::basic_random_generator<boost::mt19937> gen;
	//boost::uuids::uuid socketUUID = gen();

	//const std::string sTemp = to_string(socketUUID);
	//const char* sockKey = sTemp.c_str();
	const char* sockKey = nullptr; // not used anymore.

	STR_CS_USER* ObjCSUser = UserAdd(sockKey, (char*) this->get_remote_address().c_str());
	ObjCSUser->Socket = &this->peer();

	_PER_SOCKET_CONTEXT * lpPerSocketContext;
	int RecvBytes;
	unsigned long Flags;

#if FILE_FLOOD_SYSTEMSWITCH
	if (AntiFlood.Enabled == 1)
	{
		if (AntiFlood.Check(inet_ntoa(cInAddr)) == false)
		{
			closesocket(Accept);
			criti.unlock();
			return;
		}
	}
#endif

	ObjCSUser->PerSocketContext->dwIOCount = 0;

	_PER_SOCKET_CONTEXT* sockCtx = ObjCSUser->PerSocketContext;
	sockCtx->IOContext[0].Buffer[0] = { 0 };
	sockCtx->IOContext[1].Buffer[0] = { 0 };
	sockCtx->IOContext[0].IOOperation = 0;
	sockCtx->IOContext[1].IOOperation = 1;
	sockCtx->nIndex = ObjCSUser->Index;

	sockCtx->IOContext[0].nWaitIO = 1;
	sockCtx->dwIOCount++;

	g_UserIDMap.insert(std::pair<ACE_HANDLE, STR_CS_USER*>(
		this->peer().get_handle(), ObjCSUser));

	SCConnectResultSend(*ObjCSUser, 1);

	criti.unlock();
}

int CIOCP::OnAccept(ACE_HANDLE handle)
{
	this->CreateUserData(handle);
	return -1;
}

int CIOCP::OnRead(ACE_HANDLE handle, int len)
{
	int nRet;
#ifdef _WIN64
	ULONGLONG ClientIndex;
#else
	ULONG ClientIndex;
#endif
	_PER_SOCKET_CONTEXT * lpPerSocketContext = nullptr;
	_PER_IO_CONTEXT * lpIOContext = nullptr;

	criti.lock();

	STR_CS_USER* lpUser = this->getCSByHandle(this->peer().get_handle());
	if (lpUser == nullptr)
	{
		sLog->outError("Could not retrieve the User Object.");
		criti.unlock();
		return errno == EWOULDBLOCK ? 0 : -1;
	}

	lpPerSocketContext = lpUser->PerSocketContext;
	if (lpPerSocketContext == nullptr)
	{
		criti.unlock();
		return 0;
	}

	lpIOContext = lpUser->PerSocketContext->IOContext;
	if (lpIOContext == nullptr)
	{
		criti.unlock();
		return 0;
	}

	lpPerSocketContext->dwIOCount--;

	lpIOContext->nWaitIO = 0;

	//unsigned long RecvBytes = 0; // = this->input_buffer_.space();


	recv((char*)lpIOContext->Buffer, len);
	//lpIOContext->Buffer[0] = '\\0';
	//ACE_OS::memcpy(lpIOContext->Buffer, (unsigned char*) this->input_buffer_.rd_ptr(), len);
	//len--;
	lpIOContext->nbBytes = len;
	lpIOContext->nTotalBytes += len;

	//lpIOContext->Buffer[len] = '\\0';

	RecvDataParse(lpIOContext, lpUser->Index);

	//for (int i = 0; i <= len+1; ++i)
	//	lpIOContext->Buffer[i] = '\\0';

	lpIOContext->IOOperation = 0;

	lpPerSocketContext->dwIOCount++;
	lpIOContext->nWaitIO = 1;

	//this->input_buffer_.crunch();

	criti.unlock();

	return 1;
}


bool CIOCP::RecvDataParse(_PER_IO_CONTEXT * lpIOContext, int uIndex)
{
	BYTE* recvbuf;
	int lOfs;
	int size;
	BYTE headcode;
	BYTE xcode;
	STR_CS_USER* lpUser = getCSUser(uIndex);


	if (lpIOContext->nbBytes < 3)
	{
		return true;
	}

	lOfs = 0;
	size = lpIOContext->nbBytes;
	xcode = 0;
	recvbuf = (BYTE*)lpIOContext->Buffer;

	if (size == 0)
	{
		return true;
	}

	while (true)
	{
		if (recvbuf[lOfs] == 0xC1 ||
			recvbuf[lOfs] == 0xC3)
		{
			BYTE * pBuf;

			pBuf = &recvbuf[lOfs];
			size = pBuf[1];
			headcode = pBuf[2];
			xcode = recvbuf[lOfs];
		}
		else if (recvbuf[lOfs] == 0xC2 ||
			recvbuf[lOfs] == 0xC4)
		{
			BYTE * pBuf;

			pBuf = &recvbuf[lOfs];
			size = pBuf[1] * 256;
			size |= pBuf[2];
			headcode = pBuf[3];
			xcode = recvbuf[lOfs];
		}

		else
		{
			sLog->outError("error-L1: Header error (%s %d)lOfs:%d, size:%d", __FILE__, __LINE__, lOfs, lpIOContext->nbBytes);
			lpIOContext->nbBytes = 0;
			return false;
		}

		if (size <= 0)
		{
			sLog->outError("error-L1: size %d",
				size);
			return false;
		}

		if (size <= lpIOContext->nbBytes)
		{
			lpUser->PacketCount++;

			if (lpUser->PacketCount >= g_MaxPacketPerSec /*&& strcmp(lpUser->IP, g_WhiteListIP)*/)
			{
				sLog->outError("[ANTI-FLOOD] Packets Per Second: %d / %d, IP: %d", lpUser->PacketCount, g_MaxPacketPerSec, lpUser->IP);
				criti.unlock();
				this->CloseClient(uIndex);
				return false;
			}

			CSProtocolCore(headcode, &recvbuf[lOfs], size, lpUser->Index, 0, 0);

			lOfs += size;
			lpIOContext->nbBytes -= size;

			if (lpIOContext->nbBytes <= 0)
			{
				break;
			}
		}
		else if (lOfs > 0)
		{
			if (lpIOContext->nbBytes < 1)
			{
				sLog->outError("error-L1: recvbuflen 1 %s %d", __FILE__, __LINE__);
				break;
			}

			if (lpIOContext->nbBytes < MAX_IO_BUFFER_SIZE)
			{
				std::memcpy(recvbuf, &recvbuf[lOfs], lpIOContext->nbBytes);
				sLog->outError("Message copy %d", lpIOContext->nbBytes);
			}
			break;

		}
		else
		{
			break;
		}

	}

	//criti.unlock();
	return true;
}


bool CIOCP::DataSend(int uIndex, LPBYTE lpMsg, DWORD dwSize, bool Encrypt)
{
	_PER_SOCKET_CONTEXT * lpPerSocketContext;

	criti.lock();

	STR_CS_USER* lpCSUser = getCSUser(uIndex);

	if (lpCSUser->ConnectionState == 0)
	{
		criti.unlock();
		return false;
	}

	lpPerSocketContext = lpCSUser->PerSocketContext;

	_PER_IO_CONTEXT  * lpIoCtxt = &lpPerSocketContext->IOContext[1];


#ifdef EMU_NOCRYPT
	if (lpMsg[0] == 0xC3)
		lpMsg[0] = 0xC1;
	if (lpMsg[0] == 0xC4)
		lpMsg[0] = 0xC2;
#endif

#ifdef C3C4_DISABLECRYPT
	if (lpMsg[0] == 0xC3)
		lpMsg[0] = 0xC1;
	if (lpMsg[0] == 0xC4)
		lpMsg[0] = 0xC2;
#endif

	/*if (lpMsg[0] == 0xC3 || lpMsg[0] == 0xC4)
	{
	int ret;
	BYTE btsize;

	if (lpMsg[0] == 0xC3)
	{
	btsize = lpMsg[1];
	ret = g_PacketEncrypt.Encrypt(&lpIoCtxt->Buffer[2], &lpMsg[1], dwSize - 1);
	lpIoCtxt->Buffer[0] = 0xC3;
	lpIoCtxt->Buffer[1] = ret + 2;
	dwSize = ret + 2;
	lpMsg[1] = btsize;
	}
	else
	{
	btsize = lpMsg[2];
	ret = g_PacketEncrypt.Encrypt(&lpIoCtxt->Buffer[3], &lpMsg[2], dwSize - 2);
	lpIoCtxt->Buffer[0] = 0xC4;
	lpIoCtxt->Buffer[1] = SET_NUMBERH(ret + 3);
	lpIoCtxt->Buffer[2] = SET_NUMBERL(ret + 3);
	dwSize = ret + 3;
	}
	}*/

	std::memcpy(lpIoCtxt->Buffer, lpMsg, dwSize);

	lpIoCtxt->nTotalBytes += dwSize;
	lpIoCtxt->nbBytes = dwSize;
	lpIoCtxt->IOOperation = 1;

	if (!lpCSUser->Socket)
	{
		lpIoCtxt->nWaitIO = 1;
		criti.unlock();
		return false;
	}
	this->set_handle(lpCSUser->Socket->get_handle());
	this->send((BYTE*)lpIoCtxt->Buffer, lpIoCtxt->nbBytes);

	lpPerSocketContext->dwIOCount++;
	lpIoCtxt->nWaitIO = 1;
	criti.unlock();
	return true;
}

void CIOCP::CloseClients()
{
	for (std::pair<ACE_HANDLE, STR_CS_USER*> user : g_UserIDMap)
	{
		this->OnClose(user.first);
	}
}

void CIOCP::CloseClient(int aIndex)
{
	this->OnClose(getCSUser(aIndex)->handle);
}

int CIOCP::OnClose(ACE_HANDLE h)
{
	STR_CS_USER* lpCSUser = getCSByHandle(h);

	sLog->outError("error: CloseClient connect error");

	if (lpCSUser->ConnectionState == 0)
	{
		sLog->outError("error-L1 : CloseClient connect error");
		criti.unlock();
		return -1;
	}

	lpCSUser->Socket->close();
	lpCSUser->Socket = nullptr;

	delete lpCSUser;

	return 0;
}


CIOCP::CIOCP(void) :
	input_buffer_(4096),
	remote_address_("<unknown>")
{
}

CIOCP::~CIOCP(void)
{
}

int CIOCP::open(void* arg)
{
	if (Base::open(arg) == -1)
	{
		return -1;
	}

	ACE_INET_Addr addr;

	if (peer().get_remote_addr(addr) == -1)
	{
		return -1;
	}

	char address[1024];

	addr.get_host_addr(address, 1024);

	this->remote_address_ = address;

	this->OnAccept(peer().get_handle());

	return 0;
}

size_t CIOCP::recv_len(void) const
{
	return this->input_buffer_.length();
}

bool CIOCP::recv_soft(char* buf, size_t len)
{
	if (this->input_buffer_.length() < len)
	{
		return false;
	}

	ACE_OS::memcpy(buf, this->input_buffer_.rd_ptr(), len);

	return true;
}

bool CIOCP::recv(char* buf, size_t len)
{
	bool ret = this->recv_soft(buf, len);

	if (ret)
	{
		this->recv_skip(len);
	}

	return ret;
}

void CIOCP::recv_skip(size_t len)
{
	this->input_buffer_.rd_ptr(len);
}

ssize_t CIOCP::noblk_send(ACE_Message_Block& message_block)
{
	const size_t len = message_block.length();

	if (len == 0)
	{
		return -1;
	}

	const ACE_Time_Value waitTime(0, 500000);
	// Try to send the message directly.
	ssize_t n = this->peer().send(message_block.rd_ptr(), len, 0, &waitTime);


	if (n < 0)
	{
		if (errno == EWOULDBLOCK)
			// Blocking signal
		{
			return 0;
		}
		else
			// Error
		{
			return -1;
		}
	}
	else if (n == 0)
	{
		// Can this happen ?
		return -1;
	}

	// return bytes transmitted
	return n;
}

bool CIOCP::send(BYTE* buf, size_t len)
{
	if (buf == NULL || len == 0)
	{
		return true;
	}

	ACE_Data_Block db(
		len,
		ACE_Message_Block::MB_DATA,
		(const char*)buf,
		0,
		0,
		ACE_Message_Block::DONT_DELETE,
		0);

	ACE_Message_Block message_block(
		&db,
		ACE_Message_Block::DONT_DELETE,
		0);

	message_block.wr_ptr(len);

	if (this->msg_queue()->is_empty())
	{
		// Try to send it directly.
		ssize_t n = this->noblk_send(message_block);

		if (n < 0)
		{
			return false;
		}
		else if (n == len)
		{
			return true;
		}

		// adjust how much bytes we sent
		message_block.rd_ptr((size_t)n);

		// fall down
	}

	// enqueue the message, note: clone is needed cause we cant enqueue stuff on the stack
	ACE_Message_Block* mb = message_block.clone();

	if (this->msg_queue()->enqueue_tail(mb, (ACE_Time_Value*)&ACE_Time_Value::zero) == -1)
	{
		mb->release();
		return false;
	}

	// tell reactor to call handle_output() when we can send more data
	if (this->reactor()->schedule_wakeup(this, ACE_Event_Handler::WRITE_MASK) == -1)
	{
		return false;
	}

	return true;
}

int CIOCP::handle_output(ACE_HANDLE handle)
{
	ACE_Message_Block* mb = 0;

	if (this->msg_queue()->is_empty())
	{
		// if no more data to send, then cancel notification
		this->reactor()->cancel_wakeup(this, ACE_Event_Handler::WRITE_MASK);
		return 0;
	}

	if (this->msg_queue()->dequeue_head(mb, (ACE_Time_Value*)&ACE_Time_Value::zero) == -1)
	{
		return -1;
	}

	ssize_t n = this->noblk_send(*mb);

	if (n < 0)
	{
		mb->release();
		return -1;
	}
	else if (n == mb->length())
	{
		mb->release();
		return 1;
	}
	else
	{
		mb->rd_ptr(n);

		if (this->msg_queue()->enqueue_head(mb, (ACE_Time_Value*)&ACE_Time_Value::zero) == -1)
		{
			mb->release();
			return -1;
		}

		return 0;
	}

	ACE_NOTREACHED(return -1);
}

int CIOCP::handle_input(ACE_HANDLE handle)
{
	const ssize_t space = this->input_buffer_.space();

	ssize_t n = this->peer().recv(this->input_buffer_.wr_ptr(), space);

	if (n < 0)
	{
		// blocking signal or error
		return errno == EWOULDBLOCK ? 0 : -1;
	}
	else if (n == 0)
	{
		// EOF
		return -1;
	}

	this->input_buffer_.wr_ptr((size_t)n);

	this->OnRead(handle, n);

	// move data in the buffer to the beginning of the buffer
	this->input_buffer_.crunch();
	//this->input_buffer_.reset();

	// return 1 in case there might be more data to read from OS
	return n == space ? 1 : 0;
}

int CIOCP::handle_close(ACE_HANDLE h, ACE_Reactor_Mask /*m*/)
{
	this->OnClose(h);

	Base::handle_close();
	return 0;
}

void CIOCP::close_connection(void)
{
	this->peer().close_reader();
	this->peer().close_writer();

	reactor()->remove_handler(this, ACE_Event_Handler::DONT_CALL | ACE_Event_Handler::ALL_EVENTS_MASK);
}

