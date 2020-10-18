#ifndef LSOFT_IACTIONOBSERVER_H
#define LSOFT_IACTIONOBSERVER_H

#include "Action.h"

namespace lsoft {

class IActionObserver
{
public:
    IActionObserver() = default;
    virtual ~IActionObserver() = default;

    virtual void onActionListener(const Action& action) = 0;
};

} // namespace lsoft

#endif // LSOFT_IACTIONOBSERVER_H
