#include <PanelObjects.h>
#include <algorithm>

using namespace PanelController;
using std::find;

Channel::Channel()
    : PanelObject(ObjectTypeCode::CHANNEL), handlers({})
{}

bool Channel::addBytesReceivedHandler(BytesReceivedHandler handler) {
    if (find(handlers.begin(), handlers.end(), handler) != handlers.end()) {
        return false;
    }

    handlers.push_back(handler);

    return true;
}

void Channel::removeBytesReceivedHandler(BytesReceivedHandler handler) {
    auto hanlderIterator = find(handlers.begin(), handlers.end(), handler);

    if (hanlderIterator == handlers.end()) {
        return;
    }

    handlers.erase(hanlderIterator);
}

void Channel::invokeBytesReceived(uint8_t* data, count_t count) {
    for (BytesReceivedHandler handler : handlers) {
        handler(this, data, count);
    }
}
