#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <QThread>

class Trajectory : public QThread
{
    Q_OBJECT
public:
    explicit Trajectory(QObject *parent = 0);

signals:

public slots:

};

#endif // TRAJECTORY_H
