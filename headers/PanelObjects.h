#pragma once
#include <stdint.h>
#include <vector>
#include "Interoperability.h"

namespace PanelController {
    enum class ObjectTypeCode : uint8_t {
        GENERIC,
        ACTION,
        SETTABLE,
        SOURCE,
        CHANNEL
    };

    class PanelObject {
    public:
        PanelObject();

        virtual const char* status();

        virtual const char* name();

        const ObjectTypeCode typeCode() const;

    protected:
        PanelObject(ObjectTypeCode typeCode);

    private:
        const ObjectTypeCode _typeCode;
    };

    class PanelAction : public PanelObject {
    public:
        PanelAction();

        virtual bool run() = 0;
    };

    class PanelSettable : public PanelObject {
    public:
        PanelSettable();

        virtual bool set(const char* value) = 0;
    };

    class PanelSource : public PanelObject {
    public:
        PanelSource();

        virtual char* get() = 0;
    };

    class Channel : public PanelObject {
    public:
        using BytesReceivedHandler = void (callconv *)(Channel*, uint8_t*, count_t);

        using Detector = count_t (callconv *)(Channel*);

        Channel();

        bool addBytesReceivedHandler(BytesReceivedHandler handler);

        void removeBytesReceivedHandler(BytesReceivedHandler handler);

        virtual bool communicating() = 0;

        virtual const char* open() = 0;

        virtual const char* send(uint8_t* bytes, count_t size) = 0;

        virtual void close() = 0;

    protected:
        void invokeBytesReceived(uint8_t* data, count_t count);

    private:
        std::vector<BytesReceivedHandler> handlers;
    };
}
