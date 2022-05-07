cmake_minimum_required(VERSION 3.18)

IF (MSVC)
    function(create_test name)
        add_executable(${name} ${name}.cpp g_test_main.cpp ${PROD_SRC})
        target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
        target_link_libraries(${name} PRIVATE gtest gmock )

        add_test(NAME ${name} COMMAND "$<TARGET_FILE:${name}>")
    endfunction()
ELSE()
    find_package(GTest 1.11.0 CONFIG REQUIRED)

    find_program(GCOV ${CMAKE_LIBRARY_ARCHITECTURE}-gcov)
    find_program(LCOV lcov)
    find_program(GENH genhtml)

    if(GCOV AND LCOV AND GENH)
    set(COVERAGE "--coverage")
    add_custom_target(coverage
        COMMAND ${LCOV} -c -d '.' -o 'info' --ignore-errors empty
        COMMAND ${LCOV} -e 'info' '*/example/*' -o 'info' --ignore-errors empty
        COMMAND ${LCOV} -r 'info' '*/test/*' -o 'info' --ignore-errors empty
        COMMAND ${GENH} 'info' -o 'coverage' --filter branch --ignore-errors empty )
    endif()

    function(create_test name)
        add_executable(${name} ${name}.cpp ${PROD_SRC})
        target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
        target_link_libraries(${name} PRIVATE GTest::gtest GTest::gmock )
        set_target_properties(${name} PROPERTIES 
            COMPILE_FLAGS "${COVERAGE} -fsanitize=address"
            LINK_FLAGS "${COVERAGE} -fsanitize=address")

        add_test(NAME ${name} COMMAND "$<TARGET_FILE:${name}>")
    endfunction()
ENDIF()

list(REMOVE_ITEM PROD_SRC ${CMAKE_SOURCE_DIR}/src/main.cpp)

create_test(gtest_ex1) 
target_sources(gtest_ex1 PRIVATE
	gtest_ex1_1.cpp
	gtest_ex1_2.cpp
	)

create_test(gtest_ex2) 
create_test(gtest_ex3) 

