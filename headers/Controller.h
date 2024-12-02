#pragma once
#include "Interoperability.h"
#include "PanelObjects.h"
#include "Profiling.h"

namespace PanelController {
    namespace Controller {
        using OnInitializedHandler = void (callconv *)();

        using OnProfileChangedHandler  = void (callconv *)(Profile*, Profile*);

        void callconv addOnInitialized(OnInitializedHandler handler);

        void callconv RemoveOnInitialized(OnInitializedHandler handler);

        void callconv initialize();

        bool callconv initialized();

        bool addOnProfileChanged(OnProfileChangedHandler handler);

        void RemoveOnProfileChanged(OnProfileChangedHandler handler);

        ConnectedPanel* callconv connectedPanels(count_t* count);

        Profile* callconv profiles(count_t* count);

        PanelInfo* callconv panelInfos(count_t* count);

        scount_t callconv selectedProfileIndex();

        bool callconv setSelectedProfileIndex(count_t index);

        Profile* callconv currentProfile();

        void callconv refreshPanels();

        void callconv addOnDeinitialized(OnInitializedHandler handler);

        void callconv RemoveOnDeinitialized(OnInitializedHandler handler);

        void callconv deinitialize();
    }
}
