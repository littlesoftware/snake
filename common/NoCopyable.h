#ifndef LSOFT_NOCOPYABLE_H
#define LSOFT_NOCOPYABLE_H

namespace lsoft {

class NoCopyable
{
protected:
    NoCopyable() {}
    ~NoCopyable() {}

private:
    NoCopyable(const NoCopyable&) = delete;
    NoCopyable(const NoCopyable&&) = delete;
    NoCopyable& operator= (const NoCopyable&) = delete;
    NoCopyable& operator= (const NoCopyable&&) = delete;
};

} // namespace lsoft

#endif // LSOFT_NOCOPYABLE_H
