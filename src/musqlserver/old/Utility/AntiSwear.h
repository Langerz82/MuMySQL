////////////////////////////////////////////////////////////////////////////////
// AntiSwear.h
#include <vector>
#include <string>

class CAntiSwear
{
public:
	CAntiSwear(void);
	virtual ~CAntiSwear(void);

	bool LoadFile(const char* File);
	bool CompareText(const char* Text);

	std::vector<std::string> m_SwearWords;
};

extern CAntiSwear SwearFilter;

////////////////////////////////////////////////////////////////////////////////
//  vnDev.Games - MuServer S12EP2 IGC v12.0.1.0 - Trong.LIVE - DAO VAN TRONG  //
////////////////////////////////////////////////////////////////////////////////

