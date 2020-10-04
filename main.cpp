#include "game/PlayerManager.h"
#include "log/Options.h"

using namespace lsoft::log;

int main()
{
    Options::instance().redirectToFile("snake.log");
    Options::instance().setLowType(Type::TRACE);
    Options::instance().setFlags(Flag::DEFAULT | Flag::COLOR | Flag::DATETIME | Flag::MILLISECONS);

    lsoft::PlayerManager manager;
    manager.run();
    return 0;
}
