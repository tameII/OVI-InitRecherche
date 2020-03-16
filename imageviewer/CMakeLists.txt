cmake_minimum_required(VERSION 3.10.2)

project(DisplayImage)

find_package(ITK REQUIRED)

include(${ITK_USE_FILE})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)


# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")


add_executable(DisplayImage
    imageviewer.cpp
    main.cpp
    treeviewer.cpp
    mainview.cpp
)

qt5_use_modules(DisplayImage Widgets)

target_link_libraries(DisplayImage ${ITK_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5PrintSupport_LIBRARIES})


install(TARGETS DisplayImage
  DESTINATION bin/
  COMPONENT Runtime
  )

enable_testing()
add_test(NAME DisplayImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DisplayImage)

