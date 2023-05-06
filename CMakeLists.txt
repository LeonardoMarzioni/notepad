project (notepad)

# CMake 3.9 necessario per Qt
cmake_minimum_required (VERSION 3.9)

# attivazione funzionalità specifiche di CMake per Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# verifico esistenza delle librerie Qt necessarie
find_package(Qt5 CONFIG REQUIRED REQUIRED COMPONENTS Widgets)
find_package(Qt5 CONFIG REQUIRED REQUIRED COMPONENTS PrintSupport)

# ottengo i tutti sorgenti
file(GLOB my_sources *.h *.cpp *.qrc *.ui)

# aggiungo eseguibile
add_executable (MyPad ${my_sources})

# collego le librerie Qt con l' eseguibile
target_link_libraries(MyPad Qt5::Widgets Qt5::PrintSupport)