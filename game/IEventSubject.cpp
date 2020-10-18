#include "IEventSubject.h"

lsoft::IEventSubject::IEventSubject()
{
}

lsoft::IEventSubject::~IEventSubject()
{
}

void lsoft::IEventSubject::attach(IEventObserver* observer)
{
    m_observers.push_back(observer);
}

void lsoft::IEventSubject::detach(IEventObserver* observer)
{
    m_observers.remove(observer);
}

void lsoft::IEventSubject::notify(const Event& event)
{
    for(auto& it : m_observers) {
        it->onEventListener(event);
    }
}
