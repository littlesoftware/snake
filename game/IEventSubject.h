#ifndef LSOFT_IEVENTSUBJECT_H
#define LSOFT_IEVENTSUBJECT_H

#include "IEventObserver.h"
#include "Event.h"

#include <list>

namespace lsoft {

class IEventSubject
{
public:
    IEventSubject();
    virtual ~IEventSubject();

    void attach(IEventObserver* observer);
    void detach(IEventObserver* observer);
    void notify(const Event& event);

private:
    std::list<IEventObserver*> _observers;
};

} // namespace lsoft

#endif // LSOFT_IEVENTSUBJECT_H
