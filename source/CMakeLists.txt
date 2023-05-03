add_library (HugeInt_lib HugeInt.cpp)
add_executable(HugeInt main.cpp)

target_link_libraries(HugeInt HugeInt_lib)