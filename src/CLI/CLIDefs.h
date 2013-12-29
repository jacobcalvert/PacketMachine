/*
 * File: CLIDefs.c, defines functions and  pointers to them for CLI commands
 */
#ifndef CLIDEFS
#define CLIDEFS
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "Assert/Assert.h"
#include "IO/PrintStream.h"
#include "PerfMon/PerfMon.h"
#include "PMCore/PacketFlowMgr.h"
#include "Logging/Logging.h"
#include "RandGen/RandGen.h"
std::string CLI_COMMAND[] = {
		"show version",
		"show commands",
		"?",
		"show status",
		"show stats",
		"show stats rt",
		"new flow",
		"start flow",
		"stop flow",
		"exit"
};
std::string CLI_COMMAND_HELP[] = {
		"Display version of software",
		"Display this output",
		"Display this output",
		"Display status of system components",
		"Display current stats",
		"Display stats in realtime",
		"Create a new packet flow",
		"Start a configured packet flow",
		"Stop a running packet flow",
		"Terminates the program"
};
void cli_show_version()
{
	PrintStream::Instance()->print("PacketMachine\r\n Version: 0.8\r\n");
}
void cli_show_commands()
{
	int len = sizeof(CLI_COMMAND)/sizeof(*CLI_COMMAND);
	int i;
	for(i = 0; i<len; i++)
	{
		char buf[100];
		sprintf(buf,"%-20s -%-20s\r\n",CLI_COMMAND[i].c_str(),CLI_COMMAND_HELP[i].c_str());
		PrintStream::Instance()->print(buf);
	}
}
void cli_show_status()
{
	char buf[500];
	std::string out;
	sprintf(buf,"PacketMachine Status\r\n");
	out+=buf;
	sprintf(buf,"  Flow Status\r\n");
	out+=buf;
	std::string flow_name;
	PMCore::Flow *flow = PMCore::PacketFlowMgr::Instance()->getFirstFlow(flow_name);
	if(flow)
	{
		Assert(flow);
		sprintf(buf,"  %s\n    %-25s %-16s\n    %-25s %-16d\n\n",flow_name.c_str(),"Status",flow->status().c_str(),"Packets Queued",flow->numPackets());
		out+=buf;
		flow = PMCore::PacketFlowMgr::Instance()->getNextFlow(flow_name);
		while(flow)
		{
			Assert(flow);
			sprintf(buf,"  %s\n    %-25s %-16s\n    %-25s %-16d\n\n",flow_name.c_str(),"Status",flow->status().c_str(),"Packets Queued",flow->numPackets());

			out+=buf;
			flow = PMCore::PacketFlowMgr::Instance()->getNextFlow(flow_name);
		}
	}
	PrintStream::Instance()->print(out.c_str());


}
void cli_show_stats()
{
	char buf[100];
	std::string out;
	sprintf(buf,"PacketMachine Stats\r\n");
	out+=buf;
	sprintf(buf,"  %-20s %-20u\r\n","Packets Sent",PMCore::PerfMon::Instance()->getPacketsSent());
	out+=buf;
	sprintf(buf,"  %-20s %-20u\r\n","Bytes Sent",PMCore::PerfMon::Instance()->getBytesSent());
	out+=buf;
	sprintf(buf,"  %-20s %-20u\r\n","Errored Packets",PMCore::PerfMon::Instance()->getErroredPackets());
	out+=buf;
	sprintf(buf,"  %-20s %-20.2f %s\r\n","Bandwidth",PMCore::PerfMon::Instance()->getKBPS(),"kBps");
	out+=buf;
	PrintStream::Instance()->print(out.c_str());
}
void cli_show_stats_realtime()
{
	PrintStream::Instance()->print("This is not yet supported\r\n");
}
void cli_exit()
{
	PrintStream::Instance()->print("Shutting down PacketMachine... done.\n");
	exit(0);
}

void cli_new_flow()
{
	bool success = true;
	std::string temp;
	std::string flow_name,ip,port,start_now,num_packets_str;
	uint32_t num_packets = 0;
	while(flow_name.empty())
	{
		PrintStream::Instance()->print("Flow name: ");
		std::getline(std::cin, flow_name);
	}
	while(num_packets == 0)
	{
		PrintStream::Instance()->print("Number of Packets: ");
		std::getline(std::cin, num_packets_str);
		if(!num_packets_str.empty())
		{
			num_packets = atoi(num_packets_str.c_str());
			if(!num_packets)
			{
				num_packets=0;
			}
		}
	}
	while(ip.empty())
	{
		PrintStream::Instance()->print("Remote IP: ");
		std::getline(std::cin, ip);
	}
	while(port.empty())
	{
		PrintStream::Instance()->print("Remote Port: ");
		std::getline(std::cin, port);
	}
	success &=PMCore::PacketFlowMgr::Instance()->AddPacketFlow(flow_name);
	PMCore::Flow *f = PMCore::PacketFlowMgr::Instance()->find(flow_name);
	if(f)
	{

		uint32_t i;
		for(i=0;i<num_packets;i++)
		{
			PMCore::Packet *p = new PMCore::Packet(ip,port,RandGen::Instance()->get(512));//TODO: randgen
			f->add(p);
		}
	}

	while(true)
	{
		PrintStream::Instance()->print("Start now?[y/n]: ");
		std::getline(std::cin, start_now);
		if(strcmp(start_now.c_str(),"y") + strcmp(start_now.c_str(),"n") )
		{
			break;
		}
	}
	if(strcmp(start_now.c_str(),"y") == 0)
	{
		f->Start();
	}
	if(success)
	{
		PrintStream::Instance()->print("Successfully configured flow \r\n");
	}
	else
	{
		PrintStream::Instance()->print("Failed to configured flow \r\n");
	}





}
void cli_start_flow()
{
	std::string flow_name;
	while(flow_name.empty())
	{
		PrintStream::Instance()->print("Flow name: ");
		std::getline(std::cin, flow_name);
	}
	PMCore::Flow* flow = PMCore::PacketFlowMgr::Instance()->find(flow_name);
	if(!flow)
	{
		PrintStream::Instance()->print("Could not find flow\r\n");
	}
	else
	{
		if(!flow->Running())
		{
			flow->Start();
			PrintStream::Instance()->print("Flow started\r\n");
		}
		else
		{
			PrintStream::Instance()->print("Flow is already running\r\n");
		}

	}

}
void cli_stop_flow()
{
	std::string flow_name;
	while(flow_name.empty())
	{
		PrintStream::Instance()->print("Flow name: ");
		std::getline(std::cin, flow_name);
	}
	PMCore::Flow* flow = PMCore::PacketFlowMgr::Instance()->find(flow_name);
	if(!flow)
	{
		PrintStream::Instance()->print("Could not find flow\r\n");
	}
	else
	{
		if(!flow->Running())
		{
			PrintStream::Instance()->print("Flow not running\r\n");
		}
		else
		{
			flow->Kill();
			PrintStream::Instance()->print("Flow stopped.\r\n");
		}
	}

}




void (*CLI_FUNCTION[])()= {
		&cli_show_version,
		&cli_show_commands,
		&cli_show_commands,
		&cli_show_status,
		&cli_show_stats,
		&cli_show_stats_realtime,
		&cli_new_flow,
		&cli_start_flow,
		&cli_stop_flow,
		&cli_exit


};
#endif
