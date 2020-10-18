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

    void exitEvent();

    // --------------------------------------------------------------
    // Member data
    // --------------------------------------------------------------
    std::list<std::string> m_menu;      // List of menu
    size_t m_selected;                  // Selected item of menu
    size_t m_scrolled;                  // Scrolled of menu
    std::string m_title;                // Title of menu
};

} // namespace lsoft

#endif // LSOFT_MAINMENU_H
