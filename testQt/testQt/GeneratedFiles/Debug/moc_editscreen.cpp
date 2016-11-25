/****************************************************************************
** Meta object code from reading C++ file 'editscreen.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../editscreen.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editscreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_editscreen_t {
    QByteArrayData data[20];

    char stringdata0[234];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_editscreen_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_editscreen_t qt_meta_stringdata_editscreen = {
    {
QT_MOC_LITERAL(0, 0, 10), // "editscreen"
QT_MOC_LITERAL(1, 11, 7), // "editMap"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "openMap"
QT_MOC_LITERAL(4, 28, 6), // "newMap"
QT_MOC_LITERAL(5, 35, 7), // "nextMap"
QT_MOC_LITERAL(6, 43, 11), // "previousMap"
QT_MOC_LITERAL(7, 55, 8), // "resetMap"
QT_MOC_LITERAL(8, 64, 12), // "mapMenuClose"
QT_MOC_LITERAL(9, 77, 11), // "newCampaign"
QT_MOC_LITERAL(10, 89, 12), // "loadCampaign"
QT_MOC_LITERAL(11, 102, 19), // "createCampaignMenus"
QT_MOC_LITERAL(12, 122, 9), // "menuClose"
QT_MOC_LITERAL(13, 132, 20), // "createCharacterMenus"
QT_MOC_LITERAL(14, 153, 19), // "characterEditorMenu"
QT_MOC_LITERAL(15, 173, 19), // "characterEditorSave"
QT_MOC_LITERAL(16, 193, 13), // "loadCharacter"
QT_MOC_LITERAL(17, 207, 7), // "viewMap"
QT_MOC_LITERAL(18, 215, 7), // "newItem"
QT_MOC_LITERAL(19, 223, 10) // "newGameMap"


    },
    "editscreen\0editMap\0\0openMap\0newMap\0"
    "nextMap\0previousMap\0resetMap\0mapMenuClose\0"
    "newCampaign\0loadCampaign\0createCampaignMenus\0"
    "menuClose\0createCharacterMenus\0"
    "characterEditorMenu\0characterEditorSave\0"
    "loadCharacter\0viewMap\0newItem\0newGameMap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_editscreen[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x0a /* Public */,
       3,    0,  105,    2, 0x0a /* Public */,
       4,    0,  106,    2, 0x0a /* Public */,
       5,    0,  107,    2, 0x0a /* Public */,
       6,    0,  108,    2, 0x0a /* Public */,
       7,    0,  109,    2, 0x0a /* Public */,
       8,    0,  110,    2, 0x0a /* Public */,
       9,    0,  111,    2, 0x0a /* Public */,
      10,    0,  112,    2, 0x0a /* Public */,
      11,    0,  113,    2, 0x0a /* Public */,
      12,    0,  114,    2, 0x0a /* Public */,
      13,    0,  115,    2, 0x0a /* Public */,
      14,    0,  116,    2, 0x0a /* Public */,
      15,    0,  117,    2, 0x0a /* Public */,
      16,    0,  118,    2, 0x0a /* Public */,
      17,    0,  119,    2, 0x0a /* Public */,
      18,    0,  120,    2, 0x0a /* Public */,
      19,    0,  121,    2, 0x0a /* Public */,


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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void editscreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        editscreen *_t = static_cast<editscreen *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editMap(); break;
        case 1: _t->openMap(); break;
        case 2: _t->newMap(); break;
        case 3: _t->nextMap(); break;
        case 4: _t->previousMap(); break;
        case 5: _t->resetMap(); break;
        case 6: _t->mapMenuClose(); break;
        case 7: _t->newCampaign(); break;
        case 8: _t->loadCampaign(); break;
        case 9: _t->createCampaignMenus(); break;
        case 10: _t->menuClose(); break;
        case 11: _t->createCharacterMenus(); break;
        case 12: _t->characterEditorMenu(); break;
        case 13: _t->characterEditorSave(); break;
        case 14: _t->loadCharacter(); break;
        case 15: _t->viewMap(); break;
        case 16: _t->newItem(); break;
        case 17: _t->newGameMap(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject editscreen::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_editscreen.data,
      qt_meta_data_editscreen,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *editscreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *editscreen::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_editscreen.stringdata0))
        return static_cast<void*>(const_cast< editscreen*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int editscreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;

    }
    return _id;
}
QT_END_MOC_NAMESPACE
