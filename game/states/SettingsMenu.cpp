#include "SettingsMenu.h"
#include "log/Logger.h"

using namespace lsoft::log;

lsoft::SettingsMenu::SettingsMenu(lsoft::IModel *model):
    IState(model),
    m_selected(0),
    m_title("НАСТРОЙКИ")
{
    m_menu = {"Назад",
              "Язык",
              "Имя игрока"};
}

lsoft::SettingsMenu::~SettingsMenu()
{
}

void lsoft::SettingsMenu::activated()
{
    // send change state event
    Event event;
    event.type = Event::CHANGE_STATE;
    event.changeState.type = State::MENU;
    event.changeState.menu.list = &m_menu;
    event.changeState.menu.selected = m_selected;
    event.changeState.menu.title = &m_title;
    event.changeState.menu.scrolled = m_scrolled;
    // notify
    notify(event);
}

void lsoft::SettingsMenu::onActionListener(const lsoft::Action &action)
{
    Logger log("SettingsMenu::onActionListener");
    switch (action.type) {
    case Action::MENU_SELECTED:
        m_selected = action.menuSelected.selected;
        m_scrolled = action.menuSelected.scrolled;
        switch (m_selected) {
        case 0: // to back (main menu)
            m_model->gotoState(ModelStates::MAIN_MENU);
            break;
        default:
            log.printf(Type::WARNING, "Unknown menu %d", static_cast<uint32_t>(m_selected) );
            break;
        }
        break;
    default:
        log.printf(Type::WARNING, "Unknown action 0x%.2X", static_cast<uint32_t>(action.type) );
        break;
    }
}
