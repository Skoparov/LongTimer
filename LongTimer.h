#ifndef LONGTIMER_H
#define LONGTIMER_H

#include <QTimer>
#include <memory>
#include <limits>

//////////////////////////////////////////////////////////////////////////////
///////////////                  LongTimer              //////////////////////
//////////////////////////////////////////////////////////////////////////////

/**
*  Just stores a quint64 timeout, and calls QTimer over and over until this big timeout is reached
*/

class LongTimer : public QObject
{
	Q_OBJECT

public:
        explicit LongTimer(QObject* parent = 0);
        virtual ~LongTimer();

        void setInterval(const quint64& timeout);

public slots:
	void start(quint64 timeout);
	void stop();

private slots:
	void onInternalTimeout();

signals:        
	void timeout();

private:
        QTimer* mTimer;
        quint64 mTimeout;
        int mMaxInternalTimeout;

        int newInternalTimeout();
};

#endif
