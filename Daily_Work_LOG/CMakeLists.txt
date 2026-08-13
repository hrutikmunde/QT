cmake_minimum_required(VERSION 3.16)

project(Daily_Work_LOG VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
    main.cpp

    loginpage.cpp
    loginpage.h
    loginpage.ui

    worklog.cpp
    worklog.h
    worklog.ui

    viewlogs.cpp
    viewlogs.h
    viewlogs.ui

)

qt_add_executable(Daily_Work_LOG
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    database.h database.cpp
    viewlogs.h viewlogs.cpp viewlogs.ui


)

target_link_libraries(Daily_Work_LOG PRIVATE
    Qt6::Widgets
    Qt6::Sql
)

set_target_properties(Daily_Work_LOG PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)

install(TARGETS Daily_Work_LOG
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(Daily_Work_LOG)