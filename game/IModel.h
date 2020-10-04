#ifndef LSOFT_IMODEL_H
#define LSOFT_IMODEL_H

#include "IEventSubject.h"
#include "IEventObserver.h"
#include "IActionObserver.h"

namespace lsoft {

// The types of state
enum class ModelStates
{
    UNKNOWN,
    MAIN_MENU,
    SETTINGS_MENU
};

class IModel: public IEventSubject, public IActionObserver, public IEventObserver
{
public:
    IModel() {}
    virtual ~IModel() {}

    virtual void initialize() = 0;
    virtual void clean() = 0;
    virtual void gotoState(ModelStates state) = 0;

};

} // namespace lsoft

#endif // LSOFT_IMODEL_H
