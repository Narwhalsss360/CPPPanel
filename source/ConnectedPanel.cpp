#include <Profiling.h>

using namespace PanelController;

ConnectedPanel::ConnectedPanel(PanelID id, Channel* channel)
    : _panelID(id), _channel(channel), handlers({})
{}

PanelID ConnectedPanel::panelID() const {
    return _panelID;
}

Channel* ConnectedPanel::channel() {
    return _channel;
}

bool ConnectedPanel::addInterfaceUpdatedHandler(InterfaceUpdatedHandler handler) {
    if (find(handlers.begin(), handlers.end(), handler) != handlers.end()) {
        return false;
    }

    handlers.push_back(handler);

    return true;
}

void ConnectedPanel::removeInterfaceUpdatedHandler(InterfaceUpdatedHandler handler) {
    auto hanlderIterator = find(handlers.begin(), handlers.end(), handler);

    if (hanlderIterator == handlers.end()) {
        return;
    }

    handlers.erase(hanlderIterator);
}

void ConnectedPanel::sendToDisplay(InterfaceID id, const char* sourceData) {
    //TODO
}
