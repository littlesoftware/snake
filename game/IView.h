#ifndef LSOFT_IVIEW_H
#define LSOFT_IVIEW_H

#include "IEventObserver.h"

namespace lsoft {

class IView: public IEventObserver
{
public:
    IView() = default;
    virtual ~IView() = default;

    virtual void initialize() = 0;
    virtual void run() = 0;
    virtual void clean() = 0;
};

} // namespace lsoft

#endif // LSOFT_IVIEW_H
