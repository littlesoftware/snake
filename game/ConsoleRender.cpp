#include "ConsoleRender.h"
#include "common/Exception.h"

#include "log/Logger.h"

using namespace lsoft::log;

lsoft::ConsoleRender::ConsoleRender()
{
}

lsoft::ConsoleRender::~ConsoleRender()
{
}

void lsoft::ConsoleRender::initialize()
{
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

    init_pair(1, COLOR_WHITE, COLOR_BLUE);
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
        }

        update();

        clear();
        draw();
        refresh();

        napms(100);
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
        _state = event.changeState.type;
        switch (event.changeState.type) {
        case State::MENU:
            // Data for menu
            _menuSelected = event.changeState.menu.selected;
            _menuList = event.changeState.menu.list;
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
    switch(_state)
    {
    case State::MENU:
        drawMenu();
        break;
    default:
        throw Exception::printf("Unknown state for draw 0x%0.2X", static_cast<uint32_t>(_state) );
        break;
    }
}

void lsoft::ConsoleRender::drawMenu()
{
    CursesWindow* menuWindow;
    // get console width and height
    menuWindow = getMenuWindow();
    // draw border menu


    update_panels();
    doupdate();
}

lsoft::ConsoleRender::CursesWindow *lsoft::ConsoleRender::getMenuWindow()
{
    static CursesWindow* window = nullptr;
    if(window == nullptr)
    {
        window = new CursesWindow();
        window->decoration = newwin(20,80, 1, 1);
        window->overlay = derwin(window->decoration, 18,78, 1, 1);
        window->panel = new_panel(window->decoration);
        // draw border
        wbkgd(window->decoration, COLOR_PAIR(1));
        box(window->decoration, 0,0);
        // draw overlay
        wbkgd(window->overlay, COLOR_PAIR(1));
    }
    return window;
}
