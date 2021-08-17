cmake_minimum_required(VERSION 3.19)
project(PathFinding)

set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_PREFIX_PATH "/opt/Qt/5.15.1/gcc_64/lib/cmake/Qt5")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

add_compile_options(-fconcepts)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/ui/GraphicsView.cpp src/ui/GraphicsView.h
        src/ui/BrushStyle.h
        src/pathfinder/IBasePathFinder.h src/pathfinder/IBasePathFinder.cpp
        src/ui/Grid.cpp src/ui/Grid.h
        src/pathfinder/IFinderAlgorithm.cpp src/pathfinder/IFinderAlgorithm.h)

#if (NOT CMAKE_PREFIX_PATH)
#    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
#            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
#endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
