#ifndef LSOFT_SETTINGSMENU_H
#define LSOFT_SETTINGSMENU_H

#include "../IState.h"

#include <list>
#include <string>

namespace lsoft {

class SettingsMenu: public IState
{
public:
    SettingsMenu(IModel* model);
    virtual ~SettingsMenu();

    virtual void activated() override;
    virtual void onActionListener(const Action& action) override;

private:

    // --------------------------------------------------------------
    // Member data
    // --------------------------------------------------------------
    std::list<std::string> m_menu;      // List of menu
    size_t m_selected;                  // Selected item of menu
    size_t m_scrolled;                  // Scrolled of menu
    std::string m_title;                // Title of menu
};

} // namespace lsoft

#endif // LSOFT_SETTINGSMENU_H
