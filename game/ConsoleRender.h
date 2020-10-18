#ifndef LSOFT_CONSOLERENDER_H
#define LSOFT_CONSOLERENDER_H

#include "IView.h"
#include "IManager.h"

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
    ConsoleRender(IManager& manager);
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
        size_t width, height;  // work area
    };
    // color pairs
    enum colorPairs
    {
        DEFAULT,
        MENU_SELECTION
    };

    void update();
    void draw();
    void keyEvent(int key);
    void drawMenu();
    void keyEventMenu(int key);
    void resizeMenu();

    // get working window for menu
    CursesWindow* getMenuWindow();
    // get characters of Utf8 String
    size_t getUtf8Length(const char* text);
    // return true if the terminal change a size
    bool isTerminalResized();

    // --------------------------------------------------------------
    // Member data
    // --------------------------------------------------------------
    State::Type m_state{State::UNKNOWN};
    IManager* m_manager{nullptr};
    bool m_running;
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
