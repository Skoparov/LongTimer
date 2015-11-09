#include "LongTimer.h"

//////////////////////////////////////////////////////////////////////////////
///////////////                  LongTimer              //////////////////////
//////////////////////////////////////////////////////////////////////////////

LongTimer::LongTimer(QObject* parent /*= 0*/) : QObject(parent)
{
	mTimer = new QTimer(this);
	mTimer->setSingleShot(true);

        connect(mTimer,
                SIGNAL(timeout()),
                this,
                SLOT(onInternalTimeout()));

	mMaxInternalTimeout = std::numeric_limits<int>::max();
}

void LongTimer::start(quint64 timeout)
{		
	mTimeout = timeout;
	mTimer->start(newInternalTimeout());	
}

void LongTimer::stop()
{	
	mTimer->stop();
}

void LongTimer::setInterval(const quint64& timeout)
{
	mTimeout = timeout;
}

int LongTimer::newInternalTimeout()
{	
        int newTimeout = mTimeout > mMaxInternalTimeout?
                         mMaxInternalTimeout : mTimeout;

	mTimeout -= newTimeout;
	return newTimeout;
}

void LongTimer::onInternalTimeout()
{		
	if (!mTimeout){
		emit timeout();		
	}
	else
	{	
		int newTimeout = newInternalTimeout();
		mTimer->start(newTimeout);
	}
}



