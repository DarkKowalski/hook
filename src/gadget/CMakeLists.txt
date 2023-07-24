add_library(gadget SHARED 
    dll_main.cpp
    hook_dxgi.cpp
)

target_include_directories(gadget PRIVATE ${DETOURS_INCLUDE_DIRS})
target_link_libraries(gadget PRIVATE ${DETOURS_LIBRARY} util dxgi d3d11)
target_link_options(gadget PRIVATE "/EXPORT:DetourFinishHelperProcess,@1,NONAME") # Export by Ordinal
target_export_runtime_artifacts(gadget ${CMAKE_INSTALL_PREFIX})
