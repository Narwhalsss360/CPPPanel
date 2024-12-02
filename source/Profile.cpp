#include <Profiling.h>

using namespace PanelController;
using std::vector;
using std::string;

Profile::Profile(const char* name, Mapping* mappings, count_t count)
    : _name(name), _mappings(vector<Mapping>(mappings, mappings + count))
{}

const char* Profile::name() const {
    return _name.c_str();
}

void Profile::setName(const char* name) {
    _name = string(name);
}

const Mapping* Profile::mappings(count_t* count) const {
    *count = _mappings.size();
    if (*count == 0) {
        return nullptr;
    }

    return &_mappings[0];
}

void Profile::setMappings(count_t size, Mapping* mappings) {
    _mappings.assign(mappings, mappings + size);
}
