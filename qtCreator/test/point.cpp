#include "point.h"

Point::Point(QWidget *parent) :
    QWidget(parent)
{


}

Point::Point(char command, int phi_b, int phi_c){
    this->command = command;
    this->phi_b = phi_b;
    this->phi_c = phi_c;
}

