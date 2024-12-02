#include <Controller.h>
#include <vector>

using std::vector;

namespace PanelController {
    namespace Controller {
        static bool _init = false;

        vector<OnInitializedHandler> onInitializedHandlers;
        vector<OnInitializedHandler> onDeinitializedHandlers;
        vector<OnProfileChangedHandler> onProfileChangedHandlers;
        vector<ConnectedPanel> vConnectedPanels;
        vector<Profile> vProfiles;
        vector<PanelInfo> vPanelInfos;
        scount_t _selectedProfileIndex = -1;

        void callconv addOnInitialized(OnInitializedHandler handler) {
            for (size_t i = 0; i < onInitializedHandlers.size(); i++) {
                if (onInitializedHandlers[i] == handler) {
                    return;
                }
            }
            onInitializedHandlers.push_back(handler);
        }

        void callconv RemoveOnInitialized(OnInitializedHandler handler) {
            for (size_t i = 0; i < onInitializedHandlers.size(); i++) {
                if (onInitializedHandlers[i] == handler) {
                    onInitializedHandlers.erase(onInitializedHandlers.begin() + i);
                    return;
                }
            }
        }

        void __cdecl deinitializeAtExit() { deinitialize(); }

        void callconv initialize() {
            if (_init) {
                return;
            }
            _init = true;
            atexit(deinitializeAtExit);
            for (OnInitializedHandler handler : onInitializedHandlers) {
                handler();
            }
        }

        bool callconv initialized() {
            return _init;
        }

        bool addOnProfileChanged(OnProfileChangedHandler handler) {
            for (size_t i = 0; i < onProfileChangedHandlers.size(); i++) {
                if (onProfileChangedHandlers[i] == handler) {
                    return true;
                }
            }
            onProfileChangedHandlers.push_back(handler);
            return true;
        }

        void RemoveOnProfileChanged(OnProfileChangedHandler handler) {
            for (size_t i = 0; i < onProfileChangedHandlers.size(); i++) {
                if (onProfileChangedHandlers[i] == handler) {
                    onProfileChangedHandlers.erase(onProfileChangedHandlers.begin() + i);
                    return;
                }
            }
        }

        ConnectedPanel* callconv connectedPanels(count_t* count) {
            *count = vConnectedPanels.size();
            if (*count == 0) {
                return nullptr;
            }

            return &vConnectedPanels[0];
        }

        Profile* callconv profiles(count_t* count) {
            *count = vProfiles.size();
            if (*count == 0) {
                return nullptr;
            }

            return &vProfiles[0];
        }

        PanelInfo* callconv panelInfos(count_t* count) {
            *count = vPanelInfos.size();
            if (*count == 0) {
                return nullptr;
            }

            return &vPanelInfos[0];
        }

        scount_t callconv selectedProfileIndex() {
            return _selectedProfileIndex;
        }

        bool callconv setSelectedProfileIndex(count_t index) {
            if (index >= vProfiles.size()) {
                return false;
            }
            _selectedProfileIndex = index;
            return true;
        }

        Profile* callconv currentProfile() {
            if (_selectedProfileIndex == -1) {
                return nullptr;
            }
            return &vProfiles[_selectedProfileIndex];
        }

        void callconv refreshPanels() {}

        void callconv addOnDeinitialized(OnInitializedHandler handler) {
            for (size_t i = 0; i < onDeinitializedHandlers.size(); i++) {
                if (onDeinitializedHandlers[i] == handler) {
                    return;
                }
            }
            onDeinitializedHandlers.push_back(handler);
        }

        void callconv RemoveOnDeinitialized(OnInitializedHandler handler) {
            for (size_t i = 0; i < onDeinitializedHandlers.size(); i++) {
                if (onDeinitializedHandlers[i] == handler) {
                    onDeinitializedHandlers.erase(onDeinitializedHandlers.begin() + i);
                    return;
                }
            }
        }

        void callconv deinitialize() {
            if (!_init) {
                return;
            }

            for (OnInitializedHandler handler : onDeinitializedHandlers) {
                handler();
            }
        }
    }
}