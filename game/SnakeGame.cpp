#include "SnakeGame.h"
#include "states/MainMenu.h"
#include "states/SettingsMenu.h"

#include "log/Logger.h"

using namespace lsoft::log;

lsoft::SnakeGame::SnakeGame()
{
    pushState( ModelStates::MAIN_MENU, new MainMenu(this) );
    pushState( ModelStates::SETTINGS_MENU, new SettingsMenu(this) );
}

lsoft::SnakeGame::~SnakeGame()
{
}

void lsoft::SnakeGame::onActionListener(const lsoft::Action& action)
{
    m_currentState->onActionListener(action);
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
    if(m_states.find(state) == m_states.end())
        return;
    log << "finded state";
    m_currentState = m_states[state];
    m_currentState->activated();
}

void lsoft::SnakeGame::onEventListener(const lsoft::Event &event)
{
    // send to view
    notify(event);
}

void lsoft::SnakeGame::pushState(lsoft::ModelStates stateIndex, lsoft::IState *state)
{
    m_states.insert( std::pair< ModelStates, std::shared_ptr<IState> >(stateIndex, std::shared_ptr<IState>(state) ) );
    m_states[stateIndex]->attach(this);
}
