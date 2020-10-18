cmake_minimum_required(VERSION 3.2)

project(snake)

set ( SOURCES
    log/Options.cpp
    log/Logger.cpp
    common/Exception.cpp
    game/IEventSubject.cpp
    game/ConsoleRender.cpp
    game/IManager.cpp
    game/PlayerManager.cpp
    game/SnakeGame.cpp
    game/states/MainMenu.cpp
    main.cpp
)

set ( PROJECT_LIBS
    pthread
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

include_directories(.)

if ( WIN32 )
    list(APPEND PROJECT_LIBS pdcurses)
else ( WIN32 )
    list(APPEND PROJECT_LIBS ncursesw panelw)
endif ( WIN32 )

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})
