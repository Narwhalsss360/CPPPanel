#include <Profiling.h>

using namespace PanelController;
using std::string;

PanelInfo::PanelInfo(PanelID id, const char* name, count_t digitalCount, count_t analogCount, count_t displayCount)
    : _id(id), _name(name), _digitalCount(digitalCount), _analogCount(analogCount), _displayCount(displayCount)
{}

PanelID PanelInfo::id() const {
    return _id;
}

void PanelInfo::setID(PanelID id) {
    _id = id;
}

const char* PanelInfo::name() const {
    return _name.c_str();
}

void PanelInfo::setName(const char* name) {
    _name = string(name);
}

count_t PanelInfo::digitalCount() const {
    return _digitalCount;
}

void PanelInfo::setDigitalCount(count_t newValue) {
    _digitalCount = newValue;
}

count_t PanelInfo::analogCount() const {
    return _analogCount;
}

void PanelInfo::setAnalogCount(count_t newValue) {
    _analogCount = newValue;
}

count_t PanelInfo::displayCount() const {
    return _displayCount;
}

void PanelInfo::setDisplayCount(count_t newValue) {
    _displayCount = newValue;
}
