#include "MainMenu.h"
#include "log/Logger.h"

using namespace lsoft::log;

lsoft::MainMenu::MainMenu(IModel *model):
    IState(model),
    m_selected(0),
    m_title("ГЛАВНОЕ МЕНЮ")
{
    m_menu = {"New game",
             "1",
             "2",
             "3",
             "4",
             "5",
             "6",
             "7",
             "8",
             "9",
             "10",
             "11",
             "12",
             "13",
             "14",
             "15",
             "16",
             "17",
             "18",
             "19",
             "20",
             "21",
             "22",
             "23",
             "24",
             "Settings",
             "Exit"};
}

lsoft::MainMenu::~MainMenu()
{
}

void lsoft::MainMenu::activated()
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

void lsoft::MainMenu::onActionListener(const Action &action)
{
    (void)action;
}
