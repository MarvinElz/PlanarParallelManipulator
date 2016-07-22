// g++ GUI.c -std=c++0x -o GUI 

#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    {
    QWidget *window = new QWidget;
    QPushButton *button1 = new QPushButton("One");
    QPushButton *button2 = new QPushButton("Two");    

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(button1);
    layout->addWidget(button2);

    window->setLayout(layout);
    window->show();
    }
   
    return app.exec();
}     