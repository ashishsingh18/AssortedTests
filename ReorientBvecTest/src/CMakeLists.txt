cmake_minimum_required(VERSION 3.1.0)

project(ReorientBvecTest)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

FIND_PACKAGE(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTOUIC ON)

set(SRC_FILES
main.cpp
mainwindow.cpp
vtkAnatomicalOrientation.cpp
)

set(HDR_FILES
mainwindow.h
vtkAnatomicalOrientation.h
)

set(UI_FILES
mainwindow.ui
)

add_executable(ReorientBvecTest ${SRC_FILES} ${HDR_FILES} ${UI_FILES})
target_link_libraries(ReorientBvecTest Qt5::Core Qt5::Gui Qt5::Widgets 
${VTK_LIBRARIES}
${ITK_LIBRARIES})
