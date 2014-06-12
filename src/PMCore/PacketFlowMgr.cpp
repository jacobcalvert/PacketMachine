/*
 * File: PacketFlowMgr.cpp, implements PFM
 */
#include "PacketFlowMgr.h"
#include "PacketFlow.h"
#include "../Logging/Logging.h"
namespace PMCore
{
	PacketFlowMgr* PacketFlowMgr::m_Instance = 0;
	PacketFlowMgr::PacketFlowMgr()
	{

	}
	PacketFlowMgr* PacketFlowMgr::Instance()
	{
		if(!m_Instance)
		{
			m_Instance = new PacketFlowMgr();
			Logging::Instance()->log("PacketFlowMgr initialized","PMCORE");
		}
		return m_Instance;
	}
	bool PacketFlowMgr::AddPacketFlow(std::string name)
	{
		bool success = false;
		Flow* flow = 0;
		if(!find(name,flow))//essentially this is not already created.
		{
			flow = new Flow();
			this->m_StorageMap.insert(std::make_pair(name,flow));
			success = true;
		}
		if(success)
		{
			Logging::Instance()->log("Packet Flow created","PMCORE");
		}
		return success;
	}
	bool PacketFlowMgr::RemovePacketFlow(std::string name)
	{
		bool success = false;
		PacketFlowMap::iterator it = m_StorageMap.find(name);
		if(it != m_StorageMap.end())
		{
			success = true;
			m_StorageMap.erase(it);
		}
		return success;
	}
	bool PacketFlowMgr::find(std::string &name, Flow *flow)
	{
		bool success = false;
		PacketFlowMap::iterator it = m_StorageMap.find(name);
		if(it != m_StorageMap.end())
		{
			success = true;
			flow = it->second;//should work, doesn't.
		}
		return success;
	}
	Flow* PacketFlowMgr::find(std::string &name)
		{
			PacketFlowMap::iterator it = m_StorageMap.find(name);
			if(it != m_StorageMap.end())
			{
				return it->second;
			}
			return 0;
		}
	bool PacketFlowMgr::getFirstFlow(std::string &name,const Flow* flow)
	{
		bool success = false;
		this->const_it = m_StorageMap.begin();
		if(const_it != m_StorageMap.end())
		{

			flow = const_it->second;
			name = const_it->first;
			success = true;

		}
		return success;
	}
	Flow* PacketFlowMgr::getFirstFlow(std::string &name)
	{

		this->const_it = m_StorageMap.begin();
		if(const_it != m_StorageMap.end())
		{


			name = const_it->first;
			return const_it->second;


		}
		return 0;
	}
	bool PacketFlowMgr::getNextFlow(std::string &name,const Flow* flow)
	{
		bool success = false;
		const_it++;
		if(const_it != m_StorageMap.end())
		{
			flow = const_it->second;
			name = const_it->first;
			success = true;
		}

		return success;
	}
	Flow* PacketFlowMgr::getNextFlow(std::string &name)
	{

		const_it++;
		if(const_it != m_StorageMap.end())
		{

			name = const_it->first;
			return const_it->second;

		}

		return 0;
	}
}
