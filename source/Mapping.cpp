#include <Profiling.h>

using namespace PanelController;
using std::string;

Mapping::Mapping(const char* name, PanelID panelID, InterfaceTypes interfaceType, InterfaceID interfaceID, bool onActivate)
    : _name(name), _panelID(panelID), _interfaceType(interfaceType), _interfaceID(interfaceID), _onActivate(onActivate), _mappedObjects({}), _executionResults({})
{}

const char* Mapping::name() const {
    return _name.c_str();
}

void Mapping::setName(const char* name) {
    _name = string(name);
}

PanelID Mapping::panelID() const {
    return _panelID;
}

void Mapping::setPanelID(PanelID id) {
    _panelID = id;
}

InterfaceTypes Mapping::interfaceType() const {
    return _interfaceType;
}

void Mapping::setInterfaceType(InterfaceTypes type) {
    _interfaceType = type;
}

InterfaceID Mapping::interfaceID() const {
    return _interfaceID;
}

void Mapping::setInterfaceID(InterfaceID id) {
    _interfaceID = id;
}

bool Mapping::onActivate() const {
    return _onActivate;
}

void Mapping::setOnActivate(bool onActivate) {
    _onActivate = onActivate;
}

const MappedObject* Mapping::mappedObjects(count_t* size) const {
    *size = _mappedObjects.size();
    if (*size == 0) {
        return nullptr;
    }

    return &_mappedObjects[0];
}

void Mapping::setMappedObject(count_t size, MappedObject* mappedObjects) {
    _mappedObjects.assign(mappedObjects, mappedObjects + size);
}

Mapping::ExecutionResult* Mapping::execute(const char* value, count_t* resultCount) {
    _executionResults.reserve(_mappedObjects.size());

    for (int i = 0; i < _mappedObjects.size(); i++) {
        PanelObject* object = _mappedObjects[i].object;
        _executionResults[i].object = object;

        const char*& result = _executionResults[i].result;
        result = nullptr;

        //async_wait_to_run
        PanelAction* action = dynamic_cast<PanelAction*>(object);
        PanelSettable* settable = dynamic_cast<PanelSettable*>(object);
        PanelSource* source = dynamic_cast<PanelSource*>(object);

        if (action && _interfaceType == DIGITAL) {
            result = action->run() ? "Success" : "Failure";
        } else if (settable && _interfaceType == ANALOG) {
            result = settable->set(value) ? "Success" : "Failure";
        } else if (source && _interfaceType == DISPLAY) {
            result = source->get();
        } else {
            result = "Fatal: Unknown object type";
        }
    }

    *resultCount = _executionResults.size();

    if (*resultCount == 0) {
        return nullptr;
    }

    return &_executionResults[0];
}
