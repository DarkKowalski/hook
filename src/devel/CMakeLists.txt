add_executable(devel gfx.cpp main.cpp)
target_link_libraries(devel PRIVATE d3d11 dxgi util)
target_export_runtime_artifacts(devel ${CMAKE_INSTALL_PREFIX})
