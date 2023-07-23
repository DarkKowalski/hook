add_executable(comeasy comeasy.cpp)
target_link_libraries(comeasy PRIVATE util)
target_export_runtime_artifacts(comeasy ${CMAKE_INSTALL_PREFIX})
