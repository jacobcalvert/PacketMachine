/*
 * File: PrintStream.cpp, defines PrintStream
 */
#include "PrintStream.h"
#include "stdio.h"
#include <string>
#include <iostream>
#include "Logging/Logging.h"
// Makes this class a singleton
PrintStream* PrintStream::m_Instance = NULL;
PrintStream::PrintStream()
{
}
PrintStream* PrintStream::Instance()
{
	if(!m_Instance)
	{
		m_Instance = new PrintStream;
		Logging::Instance()->log("PrintStream initialized","PRINTSTREAM");
	}
	return m_Instance;
}
void PrintStream::print(const char* data)
{
	if(data)
	{
		printf("%s",data);
	}
}
void PrintStream::print(std::string &data)
{
	if(data.length())
	{
		std::cout<<data;
	}
}
void PrintStream::print(int data)
{
	printf("%d",data);
}
