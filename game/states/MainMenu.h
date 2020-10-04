#ifndef LSOFT_MAINMENU_H
#define LSOFT_MAINMENU_H

#include "../IState.h"

#include <list>
#include <string>

namespace lsoft {

class MainMenu: public IState
{
public:
    MainMenu(IModel* model);
    virtual ~MainMenu();

    virtual void activated() override;
    virtual void onActionListener(const Action& action) override;

private:
    std::list<std::string> _menu;
    size_t _selected;
};

} // namespace lsoft

#endif // LSOFT_MAINMENU_H
