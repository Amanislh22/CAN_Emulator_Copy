/****************************************************************************
** Meta object code from reading C++ file 'homewindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../homewindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'homewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HomeWindow_t {
    const uint offsetsAndSize[28];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_HomeWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_HomeWindow_t qt_meta_stringdata_HomeWindow = {
    {
QT_MOC_LITERAL(0, 10), // "HomeWindow"
QT_MOC_LITERAL(11, 13), // "toggleSidebar"
QT_MOC_LITERAL(25, 0), // ""
QT_MOC_LITERAL(26, 15), // "refreshComPorts"
QT_MOC_LITERAL(42, 13), // "connectSerial"
QT_MOC_LITERAL(56, 16), // "disconnectSerial"
QT_MOC_LITERAL(73, 11), // "testConnect"
QT_MOC_LITERAL(85, 14), // "testDisconnect"
QT_MOC_LITERAL(100, 12), // "showHomePage"
QT_MOC_LITERAL(113, 15), // "showMonitorPage"
QT_MOC_LITERAL(129, 17), // "showDashboardPage"
QT_MOC_LITERAL(147, 16), // "showSettingsPage"
QT_MOC_LITERAL(164, 12), // "showHelpPage"
QT_MOC_LITERAL(177, 16) // "showTransmitPage"

    },
    "HomeWindow\0toggleSidebar\0\0refreshComPorts\0"
    "connectSerial\0disconnectSerial\0"
    "testConnect\0testDisconnect\0showHomePage\0"
    "showMonitorPage\0showDashboardPage\0"
    "showSettingsPage\0showHelpPage\0"
    "showTransmitPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HomeWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x08,    1 /* Private */,
       3,    0,   87,    2, 0x08,    2 /* Private */,
       4,    0,   88,    2, 0x08,    3 /* Private */,
       5,    0,   89,    2, 0x08,    4 /* Private */,
       6,    0,   90,    2, 0x08,    5 /* Private */,
       7,    0,   91,    2, 0x08,    6 /* Private */,
       8,    0,   92,    2, 0x08,    7 /* Private */,
       9,    0,   93,    2, 0x08,    8 /* Private */,
      10,    0,   94,    2, 0x08,    9 /* Private */,
      11,    0,   95,    2, 0x08,   10 /* Private */,
      12,    0,   96,    2, 0x08,   11 /* Private */,
      13,    0,   97,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HomeWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HomeWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->toggleSidebar(); break;
        case 1: _t->refreshComPorts(); break;
        case 2: _t->connectSerial(); break;
        case 3: _t->disconnectSerial(); break;
        case 4: _t->testConnect(); break;
        case 5: _t->testDisconnect(); break;
        case 6: _t->showHomePage(); break;
        case 7: _t->showMonitorPage(); break;
        case 8: _t->showDashboardPage(); break;
        case 9: _t->showSettingsPage(); break;
        case 10: _t->showHelpPage(); break;
        case 11: _t->showTransmitPage(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject HomeWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_HomeWindow.offsetsAndSize,
    qt_meta_data_HomeWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_HomeWindow_t
, QtPrivate::TypeAndForceComplete<HomeWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *HomeWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HomeWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HomeWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int HomeWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
