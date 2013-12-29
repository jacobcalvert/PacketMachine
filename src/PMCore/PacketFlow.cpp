/*
 * File: PMCore.cpp, implements most of PMCore
 */
#include "PacketFlow.h"
#include "PerfMon/PerfMon.h"
#include "Logging/Logging.h"
#include "boost/asio.hpp"
#include <string>
namespace PMCore
{
	Packet::Packet(std::string far_address ,std::string far_port,std::string data)
	{
		this->data = data;
		this->far_address = far_address;
		this->far_port = far_port;
	}
	Packet::~Packet()
	{

	}
	void Packet::setData(std::string data)
	{
		this->data = data;
	}
	std::string Packet::farAddress()
	{
		return far_address;
	}
	std::string Packet::farPort()
	{
		return far_port;
	}
	std::string Packet::Data()
	{
		return data;
	}
	Flow::Flow():Thread()
	{
		sprintf(m_Status,"Not Running, no packets in queue");
		m_InService = false;
		m_Kill = false;
	}
	Flow::~Flow()
	{

	}
	void Flow::doWork()
	{
		//this is where we're gonna wanna send packets
		boost::asio::ip::udp::resolver r(this->io);
		boost::asio::ip::udp::socket s(this->io);
		s.open(boost::asio::ip::udp::v4());

		boost::asio::ip::udp::endpoint receiver_endpoint;
		PacketMap::iterator it = m_StorageMap.begin();
		m_InService = true;
		sprintf(m_Status,"Running");
		while(1)
		{
			if(m_Kill)
			{	m_Kill = false;
				this->Exit();
			}
			while(it != m_StorageMap.end())
			{
				boost::asio::ip::udp::resolver::query q(boost::asio::ip::udp::v4(),it->second->farAddress(),it->second->farPort());
				receiver_endpoint = *r.resolve(q);
				uint32_t bytes_sent = s.send_to(boost::asio::buffer(it->second->Data()),receiver_endpoint);

				PerfMon::Instance()->incBytesSent(bytes_sent);// PerfMon calls
				PerfMon::Instance()->incPacketsSent();
				if(bytes_sent == 0)
				{
					//this is probably an errored packet AKA it did not send correctly
					PerfMon::Instance()->incErroredPackets();
					sprintf(m_Status,"Running with errors");
					Logging::Instance()->log("Packet errors encountered","PMCORE");
				}
				it++;
			}
			it = m_StorageMap.begin();
		}

	}
	void Flow::add(Packet* p)
	{

		this->m_StorageMap[this->m_StorageMap.size()] = p;
		if(this->m_StorageMap.size())
		{
			sprintf(m_Status,"Not Running, Not Started");
		}
	}
	std::string Flow::status()
	{
		std::string x(m_Status);
		return x;
	}
	bool Flow::inService()
	{

		Lock();
		bool is;
		is = this->m_InService;
		Unlock();
		return is;
	}
	void Flow::Kill()
	{
		this->m_InService = false;
		sprintf(m_Status,"Not Running, Not Started");
		this->m_Kill = true;
	}
	int Flow::numPackets()
	{
		Lock();
		int stat = this->m_StorageMap.size();
		Unlock();
		return stat;
	}
}
