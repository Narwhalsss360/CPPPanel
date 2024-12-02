#pragma once
#include "Interoperability.h"
#include "PanelObjects.h"
#include <string>
#include <vector>

namespace PanelController {
    enum InterfaceTypes : uint8_t {
        DIGITAL,
        ANALOG,
        DISPLAY
    };

    using InterfaceID = count_t;

    using PanelID = uint64_t;

    class PanelInfo {
    public:
        PanelInfo(PanelID id, const char* name, count_t digitalCount, count_t analogCount, count_t displayCount);

        PanelID id() const;

        void setID(PanelID id);

        const char* name() const;

        void setName(const char* name);

        count_t digitalCount() const;

        void setDigitalCount(count_t newValue);

        count_t analogCount() const;

        void setAnalogCount(count_t newValue);

        count_t displayCount() const;

        void setDisplayCount(count_t newValue);

    private:
        PanelID _id;
        std::string _name;
        count_t _digitalCount, _analogCount, _displayCount;
    };

    class ConnectedPanel {
    public:
        struct InterfaceUpdateInfo {
            PanelID panelID = 0;

            InterfaceTypes interfaceType = InterfaceTypes(0);

            InterfaceID interfaceID = 0;

            bool activated = false;
        };

        using InterfaceUpdatedHandler = void (callconv *)(ConnectedPanel*, InterfaceUpdateInfo);

        ConnectedPanel(PanelID id, Channel* channel);

        PanelID panelID() const;

        Channel* channel();

        bool addInterfaceUpdatedHandler(InterfaceUpdatedHandler handler);

        void removeInterfaceUpdatedHandler(InterfaceUpdatedHandler handler);

        void sendToDisplay(InterfaceID id, const char* sourceData);

    private:
        PanelID _panelID;
        Channel* _channel;
        std::vector<InterfaceUpdatedHandler> handlers;
    };

    struct MappedObject {
        PanelObject* object = nullptr;

        count_t msDelay = 0;

        const char* overrideValue = nullptr;
    };

    class Mapping {
    public:
        struct ExecutionResult {
            PanelObject* object = nullptr;

            const char* result = nullptr;
        };

        Mapping(const char* name, PanelID panelID, InterfaceTypes interfaceType, InterfaceID interfaceID, bool onActivate);

        const char* name() const;

        void setName(const char* name);

        PanelID panelID() const;

        void setPanelID(PanelID id);

        InterfaceTypes interfaceType() const;

        void setInterfaceType(InterfaceTypes type);

        InterfaceID interfaceID() const;

        void setInterfaceID(InterfaceID id);

        bool onActivate() const;

        void setOnActivate(bool onActivate);

        const MappedObject* mappedObjects(count_t* size) const;

        void setMappedObject(count_t size, MappedObject* mappedObjects);

        ExecutionResult* execute(const char* value, count_t* resultCount);

    private:
        std::string _name;
        PanelID _panelID;
        InterfaceTypes _interfaceType;
        InterfaceID _interfaceID;
        bool _onActivate;
        std::vector<MappedObject> _mappedObjects;
        std::vector<ExecutionResult> _executionResults;
    };

    class Profile {
    public:
        Profile(const char* name, Mapping* mappings, count_t count);

        const char* name() const;

        void setName(const char* name);

        const Mapping* mappings(count_t* count) const;

        void setMappings(count_t size, Mapping* mappings);

    private:
        std::string _name;
        std::vector<Mapping> _mappings;
    };
}
