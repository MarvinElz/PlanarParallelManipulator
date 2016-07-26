#ifndef TRAJECTORY_H
#define TRAJECTORY_H

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

};

#endif // TRAJECTORY_H
