////////////////////////////////////////////////////////////////////////////////
// PluginSystem.h
#ifndef PLUGINSYSTEM_H
#define PLUGINSYSTEM_H
#pragma once

struct plugins
{
	bool active;
	int mask;
};

class CPluginSystem
{
public:
	CPluginSystem();

	~CPluginSystem();

	bool CheckPlugin(int code);
	plugins m_Data;
}; extern CPluginSystem g_IGCPlugins;

#endif

////////////////////////////////////////////////////////////////////////////////
//  vnDev.Games - MuServer S12EP2 IGC v12.0.1.0 - Trong.LIVE - DAO VAN TRONG  //
////////////////////////////////////////////////////////////////////////////////

