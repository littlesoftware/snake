#ifndef LSOFT_IMANAGER_H
#define LSOFT_IMANAGER_H

#include "IModel.h"
#include "IView.h"

#include <memory>

namespace lsoft {

class IManager
{
public:
    IManager();
    virtual ~IManager();

    virtual void run();

protected:
    std::shared_ptr<IModel> _model;
    std::shared_ptr<IView> _view;
};

} // namespace lsoft

#endif // LSOFT_IMANAGER_H
