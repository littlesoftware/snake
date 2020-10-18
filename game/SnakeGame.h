#ifndef LSOFT_SNAKEGAME_H
#define LSOFT_SNAKEGAME_H

#include "IModel.h"
#include "IState.h"

#include <map>
#include <memory>

namespace lsoft {

class SnakeGame: public IModel
{
public:
    SnakeGame();
    virtual ~SnakeGame();

    virtual void onActionListener(const Action& action) override;
    virtual void initialize() override;
    virtual void clean() override;
    virtual void gotoState(ModelStates state) override;
    virtual void onEventListener(const Event& event) override;

private:
    inline void pushState(ModelStates stateIndex, IState* state);

    // --------------------------------------------------------------
    // Member data
    std::map<ModelStates, std::shared_ptr<IState> > m_states;
    std::shared_ptr<IState> m_currentState;
};

} // namespace lsoft

#endif // LSOFT_SNAKEGAME_H
