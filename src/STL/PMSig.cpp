#include "Logging/Logging.h"

void sig_abort_handler(int sig)
{
	Logging::Instance()->log("Caught SIGABRT","PMSIG");
	Logging::Instance()->exit();
}
void sig_term_handler(int sig)
{
	Logging::Instance()->log("Caught SIGTERM","PMSIG");
	Logging::Instance()->exit();
}
