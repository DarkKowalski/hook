add_library(util INTERFACE)
set_target_properties(util PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}"
    INTERFACE_LINK_LIBRARIES glog::glog
)
