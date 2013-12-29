#include "PMCore/PacketFlow.h"
#include "PMCore/PacketFlowMgr.h"
#include "PerfMon/PerfMon.h"
#include "CLI/CLI.h"
#include "STL/PMSig.h"
#include "Logging/Logging.h"
#include <csignal>
#define THREADS 1
int main()
{
	signal(SIGABRT,sig_abort_handler);
	signal(SIGTERM,sig_term_handler);
	CLI* cli = CLI::Instance();
	Logging::Instance()->log("PMCore is starting up","INIT");
	cli->Start();
	cli->Wait();
	return 0;
}
