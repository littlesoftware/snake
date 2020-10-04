#ifndef LSOFT_IACTIONOBSERVER_H
#define LSOFT_IACTIONOBSERVER_H

#include "Action.h"

namespace lsoft {

class IActionObserver
{
public:
    IActionObserver() {}
    virtual ~IActionObserver() {}

    virtual void onActionListener(const Action& action) = 0;
};

} // namespace lsoft

#endif // LSOFT_IACTIONOBSERVER_H
