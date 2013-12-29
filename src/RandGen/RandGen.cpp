/*
 *
 */
#include "RandGen.h"
#include "Logging/Logging.h"
#include <fstream>
RandGen* RandGen::m_Instance = 0;
RandGen::RandGen()
{

}
RandGen* RandGen::Instance()
{
	if(!m_Instance)
	{
		m_Instance = new RandGen();
		Logging::Instance()->log("RandGen initialized","RANDGEN");
	}
	return m_Instance;
}
std::string RandGen::get(int bytes)
{
	std::ifstream fs;
	fs.open("/dev/urandom",std::ios::in);//urandom doesn't block
	char buffer[bytes];
	fs.read(buffer,sizeof(buffer));
	fs.close();
	std::string ret(buffer);
	return ret;
}
