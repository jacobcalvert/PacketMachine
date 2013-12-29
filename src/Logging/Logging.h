/*
 * File: Logging.h, defines singleton logger that waits for events.
 * Author: Jacob Calvert
 * Date: 12/08/2013
 * Rev: 1.0
 */
#ifndef LOGGING_H
#define LOGGING_H
#include "stdio.h"
#include <iostream>
class Logging
{
private:
	char* file_name;
	unsigned int write_flag;
	void timestamp(char ts [100]);
	static Logging* m_Instance;
	FILE *f;

public:
	Logging();
	~Logging();
	void exit();
	void log(char* event,char* sender);
	void log(std::string event, std::string sender);
	static Logging* Instance();

};
#endif
