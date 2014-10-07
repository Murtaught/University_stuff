#ifndef BINARYMARKERDISPATCHER_H
#define BINARYMARKERDISPATCHER_H

#include "binaryserializable.h"
#include <map>

class BinaryMarkerDispatcher
{
    friend class BinaryMarkerDispatcherKiller;
    typedef std::map<int, const BinarySerializable*> ContainerType;

public:
    static BinaryMarkerDispatcher* instance();

    bool isKnown(int marker) const;
    void addNewType(const BinarySerializable *type_sample);
    void removeType(int marker);
    BinarySerializable* dispatchMarker(int marker) const;

private:
    ContainerType known_types_;

    BinaryMarkerDispatcher() {}
    ~BinaryMarkerDispatcher();
    static BinaryMarkerDispatcher *instance_;
};

#endif // BINARYMARKERDISPATCHER_H
