#include "ConsoleRender.h"
#include "common/Exception.h"
#include "Action.h"

#include "log/Logger.h"

#include <algorithm>

using namespace lsoft::log;

lsoft::ConsoleRender::ConsoleRender(IManager &manager):
    m_manager(&manager)
{
}

lsoft::ConsoleRender::~ConsoleRender()
{
}

void lsoft::ConsoleRender::initialize()
{
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    raw();
    nonl();
    noecho();
    curs_set(0);
    keypad(stdscr,true);
    scrollok(stdscr, true);
    nodelay(stdscr, true);
    if(!has_colors())
        throw Exception("Your terminal does not support color");
    start_color();
    use_default_colors();

    init_pair(colorPairs::DEFAULT, COLOR_WHITE, COLOR_BLACK);     // default
    init_pair(colorPairs::MENU_SELECTION, COLOR_BLACK, COLOR_WHITE);     // selected menu
}

void lsoft::ConsoleRender::run()
{
    Logger log("ConsoleRender::run");
    int key;
    m_running = true;
    while(m_running)
    {
        while(true)
        {
            key = getch();
            // if it has no key event
            if(key == EOF)
                break;
            log.printf("Key = %2X", key);
            keyEvent(key);
        }

        update();       // update world
        draw();         // draw world
        refresh();      // refresh
        napms(10);     // some pause
    }
}

void lsoft::ConsoleRender::clean()
{
    endwin();
}

void lsoft::ConsoleRender::onEventListener(const lsoft::Event& event)
{
    Logger log("ConsoleEvent");

    switch (event.type) {
    case Event::CHANGE_STATE:
        m_state = event.changeState.type;
        switch (event.changeState.type) {
        case State::MENU:
            // Data for menu
            m_menuSelected = event.changeState.menu.selected;
            m_menuList = event.changeState.menu.list;
            m_title = event.changeState.menu.title;
            m_titleLength = getUtf8Length(m_title->c_str());
            m_menuScrolled = event.changeState.menu.scrolled;
            m_menuIt = m_menuList->cbegin();
            for(size_t i=0; i<m_menuScrolled; i++)
                m_menuIt++;
            m_menuSize = m_menuList->size();
            resizeMenu();
            drawMenu();                             // draw if change the state to menu
            break;
        default:
            throw Exception::printf("Unknown state 0x%0.2X", static_cast<uint32_t>(event.changeState.type));
            break;
        }
        break;
    case Event::EXIT:
        m_running = false;
        break;
    default:
        log.printf(Type::WARNING, "Unknown event type 0x%0.2X", static_cast<uint32_t>(event.type));
        break;
    }
}

void lsoft::ConsoleRender::update()
{
}

void lsoft::ConsoleRender::draw()
{
    switch(m_state)
    {
    case State::MENU:
        if(isTerminalResized())
            resizeMenu();
        update_panels();
        doupdate();
        break;
    default:
        throw Exception::printf("Unknown state for draw 0x%0.2X", static_cast<uint32_t>(m_state) );
        break;
    }
}

void lsoft::ConsoleRender::keyEvent(int key)
{
    switch (m_state) {
    case State::MENU:
        keyEventMenu(key);
        break;
    default:
        break;
    }
}

void lsoft::ConsoleRender::drawMenu()
{
    CursesWindow* window;
    // get console width and height
    window = getMenuWindow();

    // draw box of decoration
    box(window->decoration, 0, 0);

    // draw title
    mvwprintw( window->overlay, 0, m_titleXPosition, "%s", m_title->c_str() );
    wmove(window->overlay, 1, 0);
    for(size_t i=0; i<window->width; i++)
        waddch(window->overlay, ACS_HLINE);

    // draw menu list
    size_t line = 0;
    auto itCur = m_menuIt;
    while(line < window->height-2)
    {
        if(itCur != m_menuList->cend())
        {
            char selector = ' ';
            if(line+m_menuScrolled == m_menuSelected)
            {
                wattron(window->overlay, COLOR_PAIR(colorPairs::MENU_SELECTION));
                selector = '*';
            }
            mvwprintw( window->overlay, line+2, 0, "%c %-100s", selector, itCur->c_str() );
            if(line+m_menuScrolled == m_menuSelected)
            {
                wattroff(window->overlay, COLOR_PAIR(colorPairs::MENU_SELECTION));
            }
            itCur++;
        }
        else
        {
            // draw space
            mvwprintw( window->overlay, line+2, 0, "  %-100s", "" );
        }
        line++;
    }
}

void lsoft::ConsoleRender::keyEventMenu(int key)
{
    CursesWindow* window;
    window = getMenuWindow();
    switch (key) {
    case KEY_DOWN:
        if(m_menuSelected+1 < m_menuSize)
        {
            m_menuSelected++;
            while(m_menuScrolled+window->height-3 < m_menuSelected)
            {
                m_menuScrolled++;
                m_menuIt++;
            }
            drawMenu();
        }
        break;
    case KEY_UP:
        if(m_menuSelected > 0)
        {
            m_menuSelected--;
            while(m_menuScrolled > m_menuSelected)
            {
                m_menuScrolled--;
                m_menuIt--;
            }
            drawMenu();
        }
        break;
    case 13:    // enter
    case 10:    // other enter???
    case ' ':   // space
        // select some menu item
        m_manager->menuSelected(m_menuSelected, m_menuScrolled);
        break;
    default:
        break;
    }
}

void lsoft::ConsoleRender::resizeMenu()
{
    int terminalWidth, terminalHeight, windowWidth, windowHeight, posX, posY;
    getmaxyx(stdscr, terminalHeight, terminalWidth);
    // resize menu
    CursesWindow* window;
    window = getMenuWindow();
    windowWidth = std::min(40, terminalWidth);
    windowHeight = std::min(20, terminalHeight);
    posX = (terminalWidth - windowWidth) / 2;
    posY = (terminalHeight - windowHeight) / 2;
    wresize(window->decoration, windowHeight, windowWidth);
    wresize(window->overlay, windowHeight-2, windowWidth-2);
    move_panel(window->panel, posY, posX);
    window->width = windowWidth-2;
    window->height = windowHeight-2;
    m_titleXPosition = std::max<int>((window->width - m_titleLength)/2, 0);
    wclear(window->decoration);
    wclear(window->overlay);
    drawMenu();         // redraw if the terminal is resized
}

lsoft::ConsoleRender::CursesWindow *lsoft::ConsoleRender::getMenuWindow()
{
    static CursesWindow* window = nullptr;
    if(window == nullptr)
    {
        window = new CursesWindow();
        window->decoration = newwin(20,80, 0, 0);
        window->overlay = derwin(window->decoration, 18,78, 1, 1);
        window->panel = new_panel(window->decoration);
        // draw border
        wbkgd(window->decoration, COLOR_PAIR(colorPairs::DEFAULT));
        box(window->decoration, 0, 0);
        // draw overlay
        wbkgd(window->overlay, COLOR_PAIR(colorPairs::DEFAULT));
    }
    return window;
}

size_t lsoft::ConsoleRender::getUtf8Length(const char *text)
{
    const char *cur = text;
    size_t sz = 0;
    while(cur[0] != 0)
    {
        // if one byte
        if((cur[0] & 0x80) == 0)
        {
            cur++;
        } else
        // if two bytes
        if((cur[0] & 0xE0) == 0xC0)
        {
            cur+=2;
        } else
        // if three bytes
        if((cur[0] & 0xF0) == 0xE0)
        {
            cur+=3;
        } else
        // if four bytes
        if((cur[0] & 0xF8) == 0xF0)
        {
            cur+=4;
        } else
            cur++;
        sz++;
    }
    return sz;
}

bool lsoft::ConsoleRender::isTerminalResized()
{
    static int oldTerminalWidth=-1, oldTerminalHeight=-1;
    int terminalWidth, terminalHeight;
    getmaxyx(stdscr, terminalHeight, terminalWidth);
    if(oldTerminalWidth != terminalWidth || oldTerminalHeight != terminalHeight)
    {
        oldTerminalWidth  = terminalWidth;
        oldTerminalHeight = terminalHeight;
        return true;
    }
    return false;
}
