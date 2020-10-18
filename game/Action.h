#ifndef LSOFT_ACTION_H
#define LSOFT_ACTION_H

#include <cstddef>

namespace lsoft {

struct Action
{
    Action() = default;
    ~Action() = default;

    struct MenuSelected
    {
        size_t selected;
        size_t scrolled;
    };

    // --------------------------------------------------------------
    // Action type
    // --------------------------------------------------------------
    enum Type
    {
        UNDEFINED,
        MENU_SELECTED,   // data in -> menuSelected
    };

    // Type of some action
    Type type;
    // Data of some action
    union
    {
        MenuSelected menuSelected;
    };
};

} // namespace lsoft

#endif // LSOFT_ACTION_H
