#!/bin/bash

set -euo pipefail

BUILD_DIR="build"
TEST_DIR="$BUILD_DIR/test"
INSTALL_DIR="out"
TOOLCHAIN_FILE="$(echo $VCPKG_ROOT | cygpath -f -)/scripts/buildsystems/vcpkg.cmake"

setup() {
    echo "Using vcpkg root: $VCPKG_ROOT"
    echo "Using toolchain file: $TOOLCHAIN_FILE"

    echo "Installing dependencies"
    start=$SECONDS
    vcpkg install --triplet x64-windows
    duration=$(( SECONDS - start ))
    echo "Dependencies installed in $duration seconds"
}

build() {
    echo "Building - $1"
    start=$SECONDS

    if [ "$1" == "debug" ]; then
        cmake -S . -B $BUILD_DIR -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN_FILE}" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR/debug"
        cmake --build $BUILD_DIR --config Debug
    elif [ "$1" == "release" ]; then
        cmake -S . -B $BUILD_DIR -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN_FILE}" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR/release"
        cmake --build $BUILD_DIR --config Release
    elif [ "$1" == "profile" ]; then
        cmake -S . -B $BUILD_DIR -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN_FILE}" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR/profile"
        cmake --build $BUILD_DIR --config RelWithDebInfo
    else
        echo "Invalid build type"
    fi

    duration=$(( SECONDS - start ))
    echo "Build took $duration seconds"

    echo "Finished building - $1"
}

install() {
    echo "Installing - $1"
    start=$SECONDS

    if [ "$1" == "debug" ]; then
        cmake --install $BUILD_DIR --config Debug
    elif [ "$1" == "release" ]; then
        cmake --install $BUILD_DIR --config Release
    elif [ "$1" == "profile" ]; then
        cmake --install $BUILD_DIR --config RelWithDebInfo
    else
        echo "Invalid build type"
    fi

    duration=$(( SECONDS - start ))
    echo "Install took $duration seconds"

    echo "Finished installing - $1"
}

test() {
    echo "Testing - $1"

    if [ "$1" == "debug" ]; then
        ctest -C Debug --test-dir $TEST_DIR --output-on-failure
    elif [ "$1" == "release" ]; then
        ctest -C Release --test-dir  $TEST_DIR  --output-on-failure
    elif [ "$1" == "profile" ]; then
        ctest -C RelWithDebInfo --test-dir $TEST_DIR --output-on-failure
    else
        ctest -C Debug --test-dir $TEST_DIR --output-on-failure
    fi

    echo "Finished testing - $1"
}

clean() {
    echo "Cleaning build directory"
    rm -rf $BUILD_DIR
    echo "Finished cleaning build directory"
}

help() {
    echo "Usage: $0 <command> [build_type]"
    echo "Commands: setup, build, test, clean"
    echo "Build types: debug, release, profile"
}

if [ $# -gt 2 ] || [ $# -lt 1 ]; then
    echo "Invalid number of arguments, expected 1 or 2, given $#"
    help
    exit 1
fi

case "$1" in
    setup)
        setup
        ;;
    build)
        if [ $# -eq 2 ]; then
            build $2
            install $2
        else
            echo "No build type specified, defaulting to debug"
            build debug
            install debug
        fi
        ;;
    test)
        if [ $# -eq 2 ]; then
            test $2
        else
            echo "No build type specified, defaulting to debug"
            test debug
        fi
        ;;
    clean)
        clean
        ;;
    *)
        help
        exit 1
        ;;
esac
