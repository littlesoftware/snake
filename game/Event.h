#ifndef LSOFT_EVENT_H
#define LSOFT_EVENT_H

#include "State.h"

namespace lsoft {

struct Event
{
    Event() = default;
    ~Event() = default;

    // --------------------------------------------------------------
    // Event type
    // --------------------------------------------------------------
    enum Type
    {
        UNKNOWN,
        CHANGE_STATE,       // data in -> changeState
        EXIT
    };

    // Type of some event
    Type type;
    // Data of some event
    union
    {
        State changeState;  // data for "change state" event
    };
};

} // namespace lsoft

#endif // LSOFT_EVENT_H
