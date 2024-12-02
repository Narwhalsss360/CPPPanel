#include <PanelObjects.h>

using namespace PanelController;

PanelObject::PanelObject()
    : PanelObject(ObjectTypeCode::GENERIC)
{}

PanelObject::PanelObject(ObjectTypeCode typeCode)
    : _typeCode(typeCode)
{}

const char* PanelObject::status() {
    return "No status";
}

const char* PanelObject::name() {
    return "Unnamed";
}

const ObjectTypeCode PanelObject::typeCode() const {
    return _typeCode;
}
