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

    void menuSelected(size_t selection, size_t scrolled=0);

protected:
    std::shared_ptr<IModel> m_model;
    std::shared_ptr<IView> m_view;
};

} // namespace lsoft

#endif // LSOFT_IMANAGER_H
