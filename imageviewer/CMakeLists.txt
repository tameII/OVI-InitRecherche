cmake_minimum_required(VERSION 3.9)

project(DisplayImage)

find_package(ITK REQUIRED)
find_package(VTK REQUIRED)

message(${ITK_USE_FILE})
message(${VTK_USE_FILE})

include(${ITK_USE_FILE})
include(${VTK_USE_FILE})

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

include_directories(src/imageviewer)
include_directories(src/imageviewer/view)
include_directories(src/imageviewer/vtkwidget)
include_directories(src/imageviewer/listener)
include_directories(src/imageviewer/model)
include_directories(src/imageviewer/model/point)


include_directories(src/mainview)
include_directories(src/mainview/view)

include_directories(src/treeviewer)
include_directories(src/treeviewer/view)


set(COMPILE_LIST
        src/imageviewer/listener/AddPointListener.h
        src/imageviewer/vtkwidget/BorderWidgetQt.cpp
        src/imageviewer/vtkwidget/BorderWidgetQt.h
        src/imageviewer/view/ImageViewer.cpp
        src/imageviewer/view/ImageViewer.h
        src/imageviewer/model/point/PointModel.cpp
        src/imageviewer/model/point/PointModel.h

        src/mainview/view/MainView.cpp
        src/mainview/view/MainView.h

        src/treeviewer/QVTree.cpp
        src/treeviewer/QVTree.h
        src/treeviewer/Tree.cpp
        src/treeviewer/Tree.h
        src/treeviewer/view/TreeViewer.cpp
        src/treeviewer/view/TreeViewer.h
)

set(UI_LIST
        src/imageviewer/vtkwidget/BorderWidgetQt.ui
)

set(EXEC_LIST
        ${COMPILE_LIST}
        src/Main.cpp)


qt5_wrap_ui(UISrcs ${UI_FILES} )

# CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
add_executable(DisplayImage ${EXEC_LIST})


qt5_use_modules(DisplayImage Core Gui Widgets)

target_link_libraries(DisplayImage ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${Qt5Widgets_LIBRARIES})


