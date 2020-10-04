#include "MainMenu.h"
#include "log/Logger.h"

using namespace lsoft::log;

lsoft::MainMenu::MainMenu(IModel *model):
    IState(model),
    _selected(0)
{
    _menu = {"New game",
             "Settings",
             "Exit"};
}

lsoft::MainMenu::~MainMenu()
{
}

void lsoft::MainMenu::activated()
{
    Logger log("MainMenu::activated");
    // send change state event
    Event event;
    log << "send notify 1";
    event.type = Event::CHANGE_STATE;
    log << "send notify 2";
    event.changeState.type = State::MENU;
    log << "send notify 3";
    event.changeState.menu.list = &_menu;
    log << "send notify 4";
    event.changeState.menu.selected = _selected;
    // notify
    log << "send notify 5";
    notify(event);
}

void lsoft::MainMenu::onActionListener(const Action &action)
{

}
