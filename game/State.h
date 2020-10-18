#ifndef LSOFT_STATE_H
#define LSOFT_STATE_H

#include <list>
#include <string>

namespace lsoft {

struct State
{
public:
    // Data for menu state
    struct MenuData
    {
        std::list<std::string>* list;
        size_t selected;
        size_t scrolled;
        std::string* title;
    };

    // State types
    enum Type {
        UNKNOWN,
        MENU,
        GAME
    };
    Type type;
    // Data for state
    union
    {
        MenuData menu;
    };
};

} // namespace lsoft

#endif // LSOFT_STATE_H
