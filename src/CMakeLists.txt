# import detours
find_path(DETOURS_INCLUDE_DIRS "detours/detours.h")
find_library(DETOURS_LIBRARY detours REQUIRED)

add_executable(comeasy comeasy.cpp)

add_executable(withdll withdll.cpp)
target_include_directories(withdll PRIVATE ${DETOURS_INCLUDE_DIRS})
target_link_libraries(withdll PRIVATE ${DETOURS_LIBRARY})

add_library(wrotei SHARED wrotei.cpp)
target_include_directories(wrotei PRIVATE ${DETOURS_INCLUDE_DIRS})
target_link_libraries(wrotei PRIVATE ${DETOURS_LIBRARY})
target_link_options(wrotei PRIVATE "/EXPORT:DetourFinishHelperProcess,@1,NONAME") # Export by Ordinal
