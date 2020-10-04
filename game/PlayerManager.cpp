#include "PlayerManager.h"

#include "SnakeGame.h"
#include "ConsoleRender.h"

lsoft::PlayerManager::PlayerManager()
{
    _model = std::shared_ptr<IModel>( new SnakeGame() );
    _view = std::shared_ptr<IView>( new ConsoleRender() );
}

lsoft::PlayerManager::~PlayerManager()
{
}

