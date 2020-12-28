cmake_minimum_required(VERSION 2.8)
project(FirstPracticum)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_RPATH "${PROJECT_SOURCE_DIR}/bin")

if(DEBUG)
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    enable_testing()
    add_executable(Test tests.cpp solver.cpp)
    add_test(Test ${Testing_SOURCE_DIR}/bin)

    target_link_libraries(Test Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})

    install (
            TARGETS Test
            RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
    )

else()
    add_executable(FirstPracticum main.cpp solver.cpp)
    install (
            TARGETS FirstPracticum
            RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
    )
endif()