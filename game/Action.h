#ifndef LSOFT_ACTION_H
#define LSOFT_ACTION_H

namespace lsoft {

struct Action
{
public:

    // Action type
    enum Type
    {
        Undefined
    };

    // Type of some action
    Type type;
    // Data of some action
    union
    {

    };
};

} // namespace lsoft

#endif // LSOFT_ACTION_H
