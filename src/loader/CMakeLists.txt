add_executable(withdll withdll.cpp)
target_include_directories(withdll PRIVATE ${DETOURS_INCLUDE_DIRS})
target_link_libraries(withdll PRIVATE ${DETOURS_LIBRARY})
target_export_runtime_artifacts(withdll ${CMAKE_INSTALL_PREFIX})
