cmake_minimum_required(VERSION 3.16)
project(PersonalCashflowGame VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt 6 components
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Sql Charts)

# Application sources
set(SOURCES
    src/main.cpp
    src/models/Player.cpp
    src/models/Transaction.cpp
    src/models/Asset.cpp
    src/models/Liability.cpp
    src/models/GameState.cpp
    src/models/DailyExpense.cpp
    src/models/Investment.cpp
    src/models/FinancialGoal.cpp
    src/services/DatabaseManager.cpp
    src/services/FinancialCalculator.cpp
    src/services/GameEngine.cpp
    src/controllers/GameController.cpp
)

set(HEADERS
    src/models/Player.h
    src/models/Transaction.h
    src/models/Asset.h
    src/models/Liability.h
    src/models/GameState.h
    src/models/DailyExpense.h
    src/models/Investment.h
    src/models/FinancialGoal.h
    src/services/DatabaseManager.h
    src/services/FinancialCalculator.h
    src/services/GameEngine.h
    src/controllers/GameController.h
)

# Resources
set(RESOURCES resources/resources.qrc)

# Application
qt_add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} resources.qrc)

# Qt linking
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Sql
    Qt6::Charts
)

# Enable testing
enable_testing()

# Test executable
add_executable(test_financialcalculator tests/test_financialcalculator.cpp
    src/services/FinancialCalculator.cpp
    src/services/GameEngine.cpp
)
target_link_libraries(test_financialcalculator PRIVATE Qt6::Core Qt6::Sql)
add_test(NAME test_financialcalculator COMMAND test_financialcalculator)

add_executable(test_gameengine tests/test_gameengine.cpp
    src/services/GameEngine.cpp
    src/services/FinancialCalculator.cpp
)
target_link_libraries(test_gameengine PRIVATE Qt6::Core Qt6::Sql)
add_test(NAME test_gameengine COMMAND test_gameengine)

# Installation
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
