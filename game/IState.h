#ifndef LSOFT_ISTATE_H
#define LSOFT_ISTATE_H

#include "IActionObserver.h"
#include "IEventSubject.h"
#include "IModel.h"

namespace lsoft {

class IState: public IEventSubject, public IActionObserver
{
public:
    IState(IModel* model): _model(model) {}
    virtual ~IState() {}

    virtual void activated() = 0;

protected:
    IModel* _model;
};

} // namespace lsoft

#endif // LSOFT_ISTATE_H
