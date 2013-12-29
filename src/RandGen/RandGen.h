/*
 * File: RangGen.h, defines reading from the std:random_device for random packet
 * structure
 * Date: 12/14/2013
 * Author: Jacob Calvert
 */
#include <string>
class RandGen
{
public:
	static RandGen* Instance();
	std::string get(int bytes = 1024);
private:
	RandGen();
	static RandGen* m_Instance;
};
