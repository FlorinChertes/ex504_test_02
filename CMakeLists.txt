cmake_minimum_required(VERSION 3.18)
project(produc VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "Current OS          \t: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Host system         \t: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "Target System       \t: ${CMAKE_SYSTEM_PROCESSOR}")

message(STATUS "Compiler            \t: ${CMAKE_CXX_COMPILER}")
message(STATUS "Compiler ID         \t: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler Version    \t: ${CMAKE_CXX_COMPILER_VERSION}")

# require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

IF (MSVC)
    # Avoid error LNK2038
    set(gtest_force_shared_crt on)

    # Activate C++ exception handling 
    IF (NOT CMAKE_CXX_FLAGS MATCHES "/EHsc") 
	    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc") 
    ENDIF ()
ENDIF()

option(USE_GOOGLE_TEST "Add Google Test based tests" ON)
message(STATUS "Use USE_GOOGLE_TEST: ${USE_GOOGLE_TEST}")

if (NOT USE_APPROVAL_TESTS)
    message(STATUS "No Approval tests")
endif ()

include(FetchContent)

if (USE_GOOGLE_TEST)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)
endif ()

file (GLOB_RECURSE PROD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${PROD_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

if(NOT CMAKE_BUILD_TYPE MATCHES release)
    enable_testing()
    add_subdirectory(test)
endif()

