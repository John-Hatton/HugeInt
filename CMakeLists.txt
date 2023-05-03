cmake_minimum_required(VERSION 3.25)
project(HugeInt)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)
add_subdirectory(source)
add_subdirectory(test)


#
##
#
########
#
##
#

###################
#					#
#    Google Test	#
#					#
###################



include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0 # most recent version 04/2023 Check GITHUB!
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#
##
#
########
#
##
#
