/*
 * File: CLI.h, defines the singleton CLI
 * Author: Jacob Calvert
 * Date: 12/06/2013
 * Rev: 1.0
 */
#ifndef CLI_H
#define CLI_H
#include <iostream>
#include "Thread/Thread.h"

class CLI:public Thread
{

public:
	static CLI* Instance();
private:
	CLI();
	CLI(CLI const&){/* do not implement */};
	static CLI* m_Instance;
	void process(std::string line);
	void doWork();

};
#endif
