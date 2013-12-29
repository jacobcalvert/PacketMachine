/*
 * File: CLI.cpp, implements CLI class
 */
#include "CLI.h"
#include "CLIDefs.h"
#include "stdlib.h"
#include "IO/PrintStream.h"
#include <string.h>
CLI * CLI::m_Instance = 0;
CLI::CLI():Thread()
{
}
CLI* CLI::Instance()
{
	if(!m_Instance)
	{
		m_Instance = new CLI();
	}
	return m_Instance;
}
void CLI::process(std::string line)
{

	int len = sizeof(CLI_COMMAND)/sizeof(*CLI_COMMAND);
	int i;
	bool command_found = false;
	for(i = 0; i<len; i++)
	{
		if(strcmp(CLI_COMMAND[i].c_str(),line.c_str()) == 0)
		{
			command_found = true;

			CLI_FUNCTION[i]();

		}

	}
	if(!command_found)
	{
		PrintStream::Instance()->print("ERROR: command not recognized\r\n");
	}
}
void CLI::doWork()
{
	while(1)
	{

	for (std::string line; std::cout << "PacketMachine> " && std::getline(std::cin, line); )
		{
			if(!line.empty())
			{
				process(line);
			}
		}
	}
}
