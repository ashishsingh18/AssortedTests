
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(LinePlot)

find_package(VTK COMPONENTS 
  vtkChartsCore
  vtkCommonCore
  vtkCommonDataModel
  vtkInteractionStyle
  vtkRenderingContext2D
  vtkRenderingContextOpenGL2
  vtkRenderingCore
  vtkRenderingFreeType
  vtkRenderingGL2PSOpenGL2
  vtkRenderingOpenGL2
  vtkViewsContext2D QUIET)
if (NOT VTK_FOUND)
  message("Skipping LinePlot: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(LinePlot MACOSX_BUNDLE LinePlot.cxx )
  target_link_libraries(LinePlot PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(LinePlot MACOSX_BUNDLE LinePlot.cxx )
  target_link_libraries(LinePlot PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS LinePlot
    MODULES ${VTK_LIBRARIES}
    )
endif () 
