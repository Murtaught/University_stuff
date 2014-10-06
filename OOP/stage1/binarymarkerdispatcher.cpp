#include "binarymarkerdispatcher.h"

BinaryMarkerDispatcher *BinaryMarkerDispatcher::instance_ = 0;

BinaryMarkerDispatcher* BinaryMarkerDispatcher::instance()
{
    if (instance_ == 0)
        instance_ = new BinaryMarkerDispatcher;

    return instance_;
}

bool BinaryMarkerDispatcher::isKnown(int marker) const
{
    return known_types_.find(marker) != known_types_.end();
}

void BinaryMarkerDispatcher::addNewType(const BinarySerializable *type_sample)
{
    removeType(type_sample->binaryMarker());
    known_types_[type_sample->binaryMarker()] = type_sample;
}

void BinaryMarkerDispatcher::removeType(int marker)
{
    if (isKnown(marker))
    {
        delete known_types_[marker];
        known_types_[marker] = 0;
    }
}

BinarySerializable* BinaryMarkerDispatcher::dispatchMarker(int marker) const
{
    // isKnown() here would worsen performance
    ContainerType::const_iterator it = known_types_.find(marker);

    if (it != known_types_.end())
        return it->second->clone();

    throw "No type is known for given binary marker!";
}
