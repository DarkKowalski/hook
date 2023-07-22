enable_testing()

find_package(GTest CONFIG REQUIRED)

add_executable(simple_test simple_test.cpp)
target_link_libraries(simple_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)    
add_test(AllTestsInMain simple_test)
