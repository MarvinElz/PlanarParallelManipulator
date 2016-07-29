/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Steuerung/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   34,   34,   34, 0x08,
      35,   34,   34,   34, 0x08,
      58,   34,   34,   34, 0x08,
      78,   34,   34,   34, 0x08,
     100,   34,   34,   34, 0x08,
     120,   34,   34,   34, 0x08,
     142,   34,   34,   34, 0x08,
     168,   34,   34,   34, 0x08,
     192,   34,   34,   34, 0x08,
     213,   34,   34,   34, 0x08,
     236,   34,   34,   34, 0x0a,
     255,   34,   34,   34, 0x0a,
     274,   34,   34,   34, 0x0a,
     297,   34,   34,   34, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0on_b_reset_B_clicked()\0\0"
    "on_b_reset_C_clicked()\0on_b_B_up_pressed()\0"
    "on_b_B_down_pressed()\0on_b_C_up_pressed()\0"
    "on_b_C_down_pressed()\0on_pushButton_2_clicked()\0"
    "on_pushButton_clicked()\0on_Mani_up_clicked()\0"
    "on_Mani_down_clicked()\0onphiBChanged(int)\0"
    "onphiCChanged(int)\0onphiBSollChanged(int)\0"
    "onphiCSollChanged(int)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_b_reset_B_clicked(); break;
        case 1: _t->on_b_reset_C_clicked(); break;
        case 2: _t->on_b_B_up_pressed(); break;
        case 3: _t->on_b_B_down_pressed(); break;
        case 4: _t->on_b_C_up_pressed(); break;
        case 5: _t->on_b_C_down_pressed(); break;
        case 6: _t->on_pushButton_2_clicked(); break;
        case 7: _t->on_pushButton_clicked(); break;
        case 8: _t->on_Mani_up_clicked(); break;
        case 9: _t->on_Mani_down_clicked(); break;
        case 10: _t->onphiBChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->onphiCChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->onphiBSollChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->onphiCSollChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
