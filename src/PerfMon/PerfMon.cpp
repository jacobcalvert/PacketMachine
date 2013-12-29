/*
 * File: Counters.cpp, implements class Counters
 */
#include <unistd.h>
#include "PerfMon.h"
#include "IO/PrintStream.h"
#include "Logging/Logging.h"
#include <ctime>
namespace PMCore
{
	PerfMon* PerfMon::m_Instance = 0;
	PerfMon::PerfMon():Thread()
	{
		prevtime = time(NULL);
		uptime = 1;//this is just for tricking the FPE
		Start();
	}
	PerfMon* PerfMon::Instance()
		{
		if(!m_Instance)
		{
			m_Instance = new PerfMon();
			Logging::Instance()->log("PerfMon initialized","PERFMON");
		}
		return m_Instance;
	}
	void PerfMon::incPacketsSent()
	{
		Lock();
		this->m_RawCounter.packets_sent++;
		Unlock();
	}
	void PerfMon::incBytesSent(uint32_t stat)
	{
		Lock();
		this->m_RawCounter.bytes_sent+=stat;
		Unlock();
	}
	void PerfMon::incErroredPackets()
	{
		Lock();
		this->m_RawCounter.errored_packets++;
		Unlock();
	}
	uint32_t PerfMon::getPacketsSent()
	{
		uint32_t stat;
		Lock();
		stat = this->m_RawCounter.packets_sent;//for now
		Unlock();
		return stat;
	}
	uint32_t PerfMon::getBytesSent()
	{
		uint32_t stat;
		Lock();
		stat =this->m_RawCounter.bytes_sent;
		Unlock();
		return stat;
	}
	uint32_t PerfMon::getErroredPackets()
	{
		uint32_t stat;
		Lock();
		stat = this->m_RawCounter.errored_packets;
		Unlock();
		return stat;
	}
	void PerfMon::setKBPS(float kbps)
	{
		Lock();
		this->m_RawCounter.kbps = kbps;
		Unlock();
	}
	float PerfMon::getKBPS()
	{
		float f;
		Lock();
		f= this->m_RawCounter.kbps;
		Unlock();
		return f;
	}
	void PerfMon::doWork()
	{
		while(1)
		{
			delta = time(NULL) - prevtime;
			uptime+=delta;
			prevtime = time(NULL);
			float Bps = this->m_RawCounter.bytes_sent/uptime;
			float KBps = Bps/1024;
			setKBPS(KBps);

			sleep(1);
		}
	}
	Counter::Counter()
	{
		this->clear();
	}
	Counter::~Counter()
	{

	}
	/*
	Counter& Counter::operator-(Counter const &other)
	{
		Counter *newCounter = new Counter();
		newCounter->packets_sent = this->packets_sent - other.packets_sent;
		newCounter->bytes_sent = this->bytes_sent - other.bytes_sent;
		newCounter->errored_packets = this->errored_packets - other.errored_packets;
		return newCounter;
	}
	*/
	bool Counter::operator!=(Counter const &other)
	{
		bool is_not_equal = true;
		if(packets_sent == other.packets_sent)
		{
			is_not_equal = false;
		}
		if(bytes_sent == other.bytes_sent)
		{
			is_not_equal = false;
		}
		if(errored_packets == other.errored_packets)
		{
			is_not_equal = false;
		}
		return is_not_equal;
	}
	Counter& Counter::operator=(Counter const &other)
	{
		if(*this != other)
		{
			packets_sent = other.packets_sent;
			bytes_sent = other.bytes_sent;
			errored_packets = other.errored_packets;
		}
		return *this;
	}
	Counter& Counter::operator+=(Counter const &other)
	{
		packets_sent += other.packets_sent;
		bytes_sent += other.bytes_sent;
		errored_packets += other.errored_packets;
		return *this;
	}
	void Counter::clear()
	{
		this->packets_sent = 0;
		this->bytes_sent = 0;
		this->errored_packets = 0;
	}

}
