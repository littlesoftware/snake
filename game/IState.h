#ifndef LSOFT_ISTATE_H
#define LSOFT_ISTATE_H

#include "IActionObserver.h"
#include "IEventSubject.h"
#include "IModel.h"

namespace lsoft {

class IState: public IEventSubject, public IActionObserver
{
public:
    IState(IModel* model): m_model(model) {}
    virtual ~IState() = default;

    virtual void activated() = 0;

protected:
    IModel* m_model;
};

} // namespace lsoft

#endif // LSOFT_ISTATE_H
