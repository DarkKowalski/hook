include(TargetExportArtifacts)

# Import libraries
## detours
find_path(DETOURS_INCLUDE_DIRS "detours/detours.h")
find_library(DETOURS_LIBRARY detours REQUIRED)

## imgui
find_package(imgui CONFIG REQUIRED)

## glog
find_package(glog CONFIG REQUIRED)

add_subdirectory(gadget)
add_subdirectory(loader)
add_subdirectory(target)
add_subdirectory(util)
