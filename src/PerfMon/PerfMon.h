/*
 * File: Counters.h, contains class definition for packet counters
 * Author: Jacob Calvert
 * Date: 12/05/2013
 * Rev: 1.0
 */
#ifndef PERFMON
#define PERFMON
#include <stdint.h>
#include <vector>
#include "../Thread/Thread.h"
namespace PMCore
{
	class PerfMon;
	class Counter
	{
	friend class PerfMon;
	public:
		Counter();
		~Counter();
		Counter& operator+=(Counter const &other);
		Counter& operator=(Counter const &other);
		//Counter operator-(Counter const &other);
		bool operator!=(Counter const &other);
	private:
		void clear();

		uint32_t packets_sent;
		uint32_t bytes_sent;
		uint32_t errored_packets;
		float	 kbps;

	};
	class PerfMon: public Thread
	{
	public:
		static PerfMon* Instance();

		void incPacketsSent();
		void incBytesSent(uint32_t);
		void incErroredPackets();

		uint32_t getPacketsSent();
		uint32_t getBytesSent();
		uint32_t getErroredPackets();
		void setKBPS(float kbps);
		float getKBPS();
		void doWork(); //not impl;d


	private:
		PerfMon();
		uint32_t prevtime,delta,uptime;
		static PerfMon* m_Instance;
		PerfMon(PerfMon const&){/* do not implement */};
		PerfMon& operator=(PerfMon const&){/* do not implement */};
		Counter m_RollingCounter;
		Counter m_RawCounter;

	};


}
#endif
