#include "PlayerManager.h"

#include "SnakeGame.h"
#include "ConsoleRender.h"

lsoft::PlayerManager::PlayerManager()
{
    m_model = std::shared_ptr<IModel>( new SnakeGame() );
    m_view = std::shared_ptr<IView>( new ConsoleRender(*this) );
}

lsoft::PlayerManager::~PlayerManager()
{
}

