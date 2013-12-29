/*
 * File: PacketFlowMgr.h, defines the creation/deletion of PFlows
 * Author: Jacob Calvert
 * Date: 12/08/2013
 * Rev: 1.0
 */
#ifndef PACKETFLOWMGR_H
#define PACKETFLOWMGR_H
#include <map>
#include "PacketFlow.h"
namespace PMCore
{
	typedef std::map<std::string,Flow*> PacketFlowMap;// (name,ptr)
	class PacketFlowMgr
	{
	private:
		static PacketFlowMgr* m_Instance;
		PacketFlowMgr(PacketFlowMgr const&){/* do not implement */};
		PacketFlowMgr& operator=(PacketFlowMgr const&){/* do not implement */}
		PacketFlowMgr();
		PacketFlowMap m_StorageMap;
		PacketFlowMap::const_iterator const_it;;
	public:
		static PacketFlowMgr* Instance();
		bool AddPacketFlow(std::string name);
		bool RemovePacketFlow(std::string name);
		bool find(std::string &name,Flow* flow);
		Flow* find(std::string &name);
		bool getFirstFlow(std::string &name,const Flow* flow);
		bool getNextFlow(std::string &name,const Flow* flow);
		Flow* getFirstFlow(std::string &name);
		Flow* getNextFlow(std::string &name);

	};
}
#endif
