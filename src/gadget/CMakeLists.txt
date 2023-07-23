add_library(wrotei SHARED wrotei.cpp)
target_include_directories(wrotei PRIVATE ${DETOURS_INCLUDE_DIRS})
target_link_libraries(wrotei PRIVATE ${DETOURS_LIBRARY} util)
target_link_options(wrotei PRIVATE "/EXPORT:DetourFinishHelperProcess,@1,NONAME") # Export by Ordinal
target_export_runtime_artifacts(wrotei ${CMAKE_INSTALL_PREFIX})
