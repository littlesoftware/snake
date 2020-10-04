#ifndef LSOFT_CONSOLERENDER_H
#define LSOFT_CONSOLERENDER_H

#include "IView.h"

#include "common/system.h"
#if defined(LSOFT_POSIX)
#include <ncurses.h>
#include <panel.h>
#elif defined(LSOFT_WINDOWS)
#include <curses.h>     // PDCurses for windows
#endif

namespace lsoft {

class ConsoleRender: public IView
{
public:
    ConsoleRender();
    virtual ~ConsoleRender();

    virtual void initialize() override;
    virtual void run() override;
    virtual void clean() override;
    virtual void onEventListener(const Event& event) override;

private:
    struct CursesWindow {
        WINDOW* overlay;
        WINDOW* decoration;
        PANEL* panel;
    };

    State::Type _state{State::UNKNOWN};
    // Menu data
    const std::list<std::string>* _menuList;
    size_t _menuSelected;

    void update();
    void draw();

    inline void drawMenu();

    CursesWindow* getMenuWindow();
};

} // namespace lsoft

#endif // LSOFT_CONSOLERENDER_H
