#include "IEventSubject.h"

lsoft::IEventSubject::IEventSubject()
{
}

lsoft::IEventSubject::~IEventSubject()
{
}

void lsoft::IEventSubject::attach(IEventObserver* observer)
{
    _observers.push_back(observer);
}

void lsoft::IEventSubject::detach(IEventObserver* observer)
{
    _observers.remove(observer);
}

void lsoft::IEventSubject::notify(const Event& event)
{
    for(auto& it : _observers) {
        it->onEventListener(event);
    }
}
