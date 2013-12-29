#include "Logging.h"
#include <ctime>
#include "stdio.h"
#include "Assert/Assert.h"
Logging* Logging::m_Instance = 0;
Logging::Logging()
{
	file_name = "PacketMachine.log";
	write_flag = 0;
	f = fopen(file_name,"a");
	Assert(f);
	log("Started logger","LOGGING");
}
Logging::~Logging()
{
	log("Shutting down","LOGGER");
	fclose(f);
}
Logging* Logging::Instance()
{
	if(!m_Instance)
	{
		m_Instance = new Logging();
	}
	return m_Instance;
}
void Logging::timestamp(char ts[100])
{
	time_t t = time(NULL);
	struct tm * timeinfo;
	timeinfo = localtime(&t);
	strftime(ts,100,"%x %X",timeinfo);

}
void Logging::log(char* event,char* sender)
{
	char ts[100],buf[1000];
	timestamp(ts);
	sprintf(buf,"%s - %s: %s\n",ts,sender,event);
	Assert(f);
	fprintf(f,"%s",buf);
	fflush(f);

}
void Logging::log(std::string event,std::string sender)
{
	char ts[100],buf[1000];
	timestamp(ts);
	sprintf(buf,"%s - %s: %s\n",ts,sender.c_str(),event.c_str());
	Assert(f);
	fprintf(f,"%s",buf);
	fflush(f);

}
void Logging::exit()
{
	this->~Logging();
}
