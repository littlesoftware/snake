#ifndef LSOFT_IEVENTOBSERVER_H
#define LSOFT_IEVENTOBSERVER_H

#include "Event.h"

namespace lsoft {

class IEventObserver
{
public:
    IEventObserver() {}
    virtual ~IEventObserver() {}

    virtual void onEventListener(const Event& event) = 0;
};

} // namespace lsoft

#endif // LSOFT_IEVENTOBSERVER_H
