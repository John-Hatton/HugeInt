project(Google_Tests)

add_executable(HugeInt_Tests HugeInt_tests.cpp HugeInt/AddSub/AddSub_tests.cpp)

target_link_libraries(HugeInt_Tests gtest gtest_main)