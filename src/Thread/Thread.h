/*
 * File: 		Thread.h
 * Author:		Jacob Calvert
 * Created:		12/05/2013
 * Rev:			1.0
 *
 */
#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
class Thread
{
public:
	Thread();
	virtual ~Thread();
	bool Start();
	void Wait();
	void Lock();
	void Unlock();
	bool Running();
	void Exit();
protected:
	virtual void doWork() = 0; // must be overridden by child class
private:
	static void * InternalThreadEntryFunc(void * This);
	bool isStarted;
	pthread_t _thread;
	pthread_mutexattr_t attr;
	pthread_mutex_t mutex;

};
#endif
