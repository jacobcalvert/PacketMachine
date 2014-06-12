/*
 * File: PMCore.h, defines majority of PacketMachine's components
 * Author: Jacob Calvert
 * Date: 12/05/2013
 * Rev: 1.0
 */
#include <string>
#include "../Thread/Thread.h"
#include "boost/asio.hpp"
#ifndef PACKETFLOW_H
#define PACKETFLOW_H
namespace PMCore
{
	class Packet
	{
	private:
		std::string far_address;
		std::string far_port;
		std::string data;
	public:
		Packet(std::string far_address ,std::string far_port,std::string data);
		~Packet();
		std::string farAddress();
		std::string farPort();
		std::string Data();
		void setData(std::string data);
	};
	typedef std::map<int,Packet*> PacketMap;
	class Flow: public Thread
	{
	public:
		Flow();
		~Flow();
		void add(Packet* p);
		void doWork();
		std::string status();
		bool inService();
		char  m_Status[100];
		void Kill();
		int numPackets();

	private:
		PacketMap m_StorageMap;
		boost::asio::io_service io;
		bool m_InService;
		bool m_Kill;




	};

}
#endif
