# Hook (with Detours)

Detours playground

## My Environment

- AMD Ryzen 9 7900X
- Windows 11
- CMake 3.26.4
- Git Bash (from Visual Studio 2022)
- vcpkg 2023-03-29 (from Visual Studio 2022)
- MSVC v143 (from Visual Studio 2022)

## Setup

- Use `C:\Program Files\Microsoft Visual Studio\2022\Community\VC\vcpkg`

- `VCPKG_ROOT` environment variable is set to `C:\Program Files\Microsoft Visual Studio\2022\Community\VC\vcpkg`

## Usage

### Build
```bash
./build.sh build debug
```

### Run
```
cd build/src/Debug/
./withdll.exe -d:wrotei.dll comeasy.exe
```
