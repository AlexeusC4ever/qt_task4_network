#ifndef THREAD_H
#define THREAD_H

#include <QThread>

class Thread : public QThread
{
    Q_OBJECT

public:
    Thread();
    virtual ~Thread() {}
    QString getData();

signals:
    void dataIsReady();

protected:
    void run() override;

private:
    QString data;

};

#endif // THREAD_H
