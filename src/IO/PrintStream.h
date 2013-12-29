/*
 * File: PrintStream.h, defines print to screen stream for CLI use
 * Author: Jacob Calvert
 * Date: 12/06/2013
 * Rev: 1.0
 */
#ifndef PRINTSTREAM_H
#define PRINTSTREAM_H
#include <string>
class PrintStream
{
public:
	static PrintStream* Instance();
	void print(const char* data);
	void print(std::string &data);
	void print(int data);
private:
	PrintStream();
	PrintStream(PrintStream const&){/* do not implement */};
	PrintStream& operator=(PrintStream const&){/* do not implement */};
	static PrintStream* m_Instance;
};

#endif
