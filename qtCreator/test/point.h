#ifndef POINT_H
#define POINT_H

#include <QWidget>

class Point : public QWidget
{
    Q_OBJECT
public:
    explicit Point(QWidget *parent = 0);
    Point(char command, int phi_b, int phi_c);
    char command;
    int phi_b, phi_c;
signals:

public slots:

};

#endif // POINT_H
