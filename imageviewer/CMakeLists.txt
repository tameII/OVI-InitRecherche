cmake_minimum_required(VERSION 3.10.2)

project(DisplayImage)

find_package(ITK REQUIRED)
find_package(VTK REQUIRED)


include(${ITK_USE_FILE})
include(${VTK_USE_FILE})

#include_directories(src)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5Widgets REQUIRED)


# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

file(GLOB_RECURSE CXX_FILES *.cpp)
file(GLOB_RECURSE UI_FILES *.ui)
file(GLOB_RECURSE QT_WRAP *.h)

qt5_wrap_ui(UISrcs ${UI_FILES} )

# CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
add_executable(DisplayImage ${CXX_FILES} ${UI_FILES} ${QT_WRAP} )


qt5_use_modules(DisplayImage Core Gui Widgets)

target_link_libraries(DisplayImage ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${Qt5Widgets_LIBRARIES})


