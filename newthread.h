#ifndef NEWTHREAD_H
#define NEWTHREAD_H
#include <QtCore>

class newThread : public QThread
{
public:
    newThread();
    void run();
};

#endif // NEWTHREAD_H
