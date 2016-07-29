#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#include "shrd_mem.h"
#include <QThread>
#include <QListWidget>

class Trajectory : public QThread
{
    Q_OBJECT
public:
    explicit Trajectory(QObject *parent = 0);
    Trajectory( QListWidget *list );
signals:

public slots:

private:
    QListWidget *list;
    void run();
    int shared_mem_id;
    shared_mem_struct * shared_mem;

};

#endif // TRAJECTORY_H
