#ifndef LSOFT_PLAYERMANAGER_H
#define LSOFT_PLAYERMANAGER_H

#include "IManager.h"

namespace lsoft {

class PlayerManager: public IManager
{
public:
    PlayerManager();
    virtual ~PlayerManager();
};

} // namespace lsoft

#endif // LSOFT_PLAYERMANAGER_H
