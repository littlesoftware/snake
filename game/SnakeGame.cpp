#include "SnakeGame.h"
#include "states/MainMenu.h"

#include "log/Logger.h"

using namespace lsoft::log;

lsoft::SnakeGame::SnakeGame()
{
    pushState( ModelStates::MAIN_MENU, new MainMenu(this) );
}

lsoft::SnakeGame::~SnakeGame()
{
}

void lsoft::SnakeGame::onActionListener(const lsoft::Action& action)
{
}

void lsoft::SnakeGame::initialize()
{
    Logger log("SnakeGame::initialize");
    // go to main menu
    gotoState( ModelStates::MAIN_MENU );
}

void lsoft::SnakeGame::clean()
{
}

void lsoft::SnakeGame::gotoState(ModelStates state)
{
    Logger log("SnakeGame::gotoState");
    if(_states.find(state) == _states.end())
        return;
    log << "finded state";
    _currentState = _states[state];
    _currentState->activated();
}

void lsoft::SnakeGame::onEventListener(const lsoft::Event &event)
{
    // send to view
    notify(event);
}

void lsoft::SnakeGame::pushState(lsoft::ModelStates stateIndex, lsoft::IState *state)
{
    _states.insert( std::pair< ModelStates, std::shared_ptr<IState> >(stateIndex, std::shared_ptr<IState>(state) ) );
    _states[stateIndex]->attach(this);
}
