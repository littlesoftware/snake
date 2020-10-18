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
    // window structure
    struct CursesWindow {
        WINDOW* overlay;
        WINDOW* decoration;
        PANEL* panel;
        int width, height;  // work area
    };
    // color pairs
    enum pairs
    {
        DEFAULT,
        MENU_SELECT
    };

    void update();
    void draw();
    void keyEvent(int key);

    inline void drawMenu();
    inline void keyEventMenu(int key);

    // get working window for menu
    CursesWindow* getMenuWindow();
    // get characters of Utf8 String
    size_t getUtf8Length(const char* text);

    // --------------------------------------------------------------
    // Member data
    // --------------------------------------------------------------
    State::Type m_state{State::UNKNOWN};
    // Menu data
    const std::list<std::string>* m_menuList;
    std::list<std::string>::const_iterator m_menuIt;
    size_t m_menuSelected;
    const std::string *m_title;
    size_t m_titleLength;
    size_t m_titleXPosition;
    size_t m_menuScrolled;
    size_t m_menuSize;
};

} // namespace lsoft

#endif // LSOFT_CONSOLERENDER_H
