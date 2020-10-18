#include "ConsoleRender.h"
#include "common/Exception.h"

#include "log/Logger.h"

#include <algorithm>

using namespace lsoft::log;

lsoft::ConsoleRender::ConsoleRender()
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

    init_pair(pairs::DEFAULT, COLOR_WHITE, COLOR_BLACK);     // default
    init_pair(pairs::MENU_SELECT, COLOR_WHITE, COLOR_BLUE);     // selected menu
}

void lsoft::ConsoleRender::run()
{
    Logger log("ConsoleRender::run");
    int key;
    char buffer[1024];
    while(true)
    {
        while(true)
        {
            key = getch();
            if(key == EOF)
                break;
            snprintf(buffer, 1000, "Key = %2X", key);
            log << buffer;
            switch (key) {
            case 'q':
            case 'Q':
                return;
                break;
            }
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
    log << event.type;

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
            break;
        default:
            throw Exception::printf("Unknown state 0x%0.2X", static_cast<uint32_t>(event.changeState.type));
            break;
        }
        break;
    default:
        log.printf(Type::INFO, "Unknown event type 0x%0.2X", static_cast<uint32_t>(event.type));
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
        drawMenu();
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
    CursesWindow* menuWindow;
    // get console width and height
    menuWindow = getMenuWindow();
    // draw title

    mvwprintw( menuWindow->overlay, 0, m_titleXPosition, "%s", m_title->c_str() );
    wmove(menuWindow->overlay, 1, 0);
    for(int i=0; i<menuWindow->width; i++)
        waddch(menuWindow->overlay, ACS_HLINE);

    // draw menu list
    int line = 0;
    auto itCur = m_menuIt;
    while(line < menuWindow->height-2 && itCur != m_menuList->cend())
    {
        char selector = ' ';
        if(line+m_menuScrolled == m_menuSelected)
        {
            wattron(menuWindow->overlay, COLOR_PAIR(pairs::MENU_SELECT));
            selector = '*';
        }
        mvwprintw( menuWindow->overlay, line+2, 0, "%c %-100s", selector, itCur->c_str() );
        if(line+m_menuScrolled == m_menuSelected)
        {
            wattroff(menuWindow->overlay, COLOR_PAIR(pairs::MENU_SELECT));
        }
        line++;
        itCur++;
    }

    update_panels();
    doupdate();
}

void lsoft::ConsoleRender::keyEventMenu(int key)
{
    CursesWindow* menuWindow;
    menuWindow = getMenuWindow();
    switch (key) {
    case KEY_DOWN:
        if(m_menuSelected+1 < m_menuSize)
        {
            m_menuSelected++;
            while(m_menuScrolled+menuWindow->height-3 < m_menuSelected)
            {
                m_menuScrolled++;
                m_menuIt++;
            }
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
        }
        break;
    default:
        break;
    }
}

lsoft::ConsoleRender::CursesWindow *lsoft::ConsoleRender::getMenuWindow()
{
    static CursesWindow* window = nullptr;
    static int oldTerminalWidth=-1, oldTerminalHeight=-1;
    if(window == nullptr)
    {
        window = new CursesWindow();
        window->decoration = newwin(20,80, 0, 0);
        window->overlay = derwin(window->decoration, 18,78, 1, 1);
        window->panel = new_panel(window->decoration);
        // draw border
        wbkgd(window->decoration, COLOR_PAIR(pairs::DEFAULT));
        box(window->decoration, 0, 0);
        // draw overlay
        wbkgd(window->overlay, COLOR_PAIR(pairs::DEFAULT));
    }
    // if update size of terminal
    int terminalWidth, terminalHeight, windowWidth, windowHeight, posX, posY;
    getmaxyx(stdscr, terminalHeight, terminalWidth);
    if(oldTerminalWidth != terminalWidth || oldTerminalHeight != terminalHeight)
    {
        wclear(window->decoration); // clear window
        wclear(window->overlay);
        windowWidth = std::min(40, terminalWidth);
        windowHeight = std::min(20, terminalHeight);
        posX = (terminalWidth - windowWidth) / 2;
        posY = (terminalHeight - windowHeight) / 2;
        wresize(window->decoration, windowHeight, windowWidth);
        wresize(window->overlay, windowHeight-2, windowWidth-2);
        move_panel(window->panel, posY, posX);
        box(window->decoration, 0, 0);
        window->width = windowWidth-2;
        window->height = windowHeight-2;
        m_titleXPosition = std::max<int>((window->width - m_titleLength)/2, 0);
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
            sz++;
            cur++;
            continue;
        }
        // if two bytes
        if((cur[0] & 0xE0) == 0xC0)
        {
            sz+=2;
            cur+=2;
        }
        // if three bytes
        if((cur[0] & 0xF0) == 0xE0)
        {
            sz+=3;
            cur+=3;
        }
        // if four bytes
        if((cur[0] & 0xF8) == 0xF0)
        {
            sz+=4;
            cur+=4;
        }
        sz++;
        cur++;
    }
    return sz;
}
