/*
 * File: Thread.cpp , implements Thread class
 */
#include "Thread.h"
#include "Assert/Assert.h"
/*
 * Thread ctor, must be inherited by whatever class you want to use it
 */
Thread::Thread()
{
	this->_thread = 0;
	pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_DEFAULT);

	int rc = pthread_mutex_init(&mutex,NULL);
	if(rc != 0)
	{
		assert(0);
	}
	this->isStarted = false;
}
Thread::~Thread()
{
	/* empty fcn */
}
/* Start the thread, return true if success, false otherwise */
bool Thread::Start()
{
	this->isStarted = (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
	return this->isStarted;
}
/* Wait until thread returns to exit */
void Thread::Wait()
{
  (void) pthread_join(_thread, NULL);
}
/* helper to handle context */
void * Thread::InternalThreadEntryFunc(void * This)
{
	((Thread *)This)->doWork();
	return NULL;
}
void Thread::Lock()
{
	int rc = pthread_mutex_lock(&mutex);
	if(rc != 0)
	{
		assert(rc);
	}

}
void Thread::Unlock()
{
	int rc = pthread_mutex_unlock(&mutex);
	if(rc != 0)
	{
		assert(rc);
	}
}
bool Thread::Running()
{
	return this->isStarted;
}
void Thread::Exit()
{
	this->isStarted = false;
	pthread_exit(NULL);
}
