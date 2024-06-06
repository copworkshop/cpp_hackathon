include(GoogleTest)

find_package(GTest REQUIRED)

add_executable(test_project)

target_sources(test_project
    PRIVATE
        main.cpp
        PWTests.cpp
        test_PWInventory.cpp
)

target_link_libraries(test_project
    PRIVATE
    PW::SERVER
    GTest::GTest
    GTest::gtest_main
)

if(ENABLE_CODE_COVERAGE)
    if(CMAKE_COMPILER_IS_GNUCXX)
        message("Preparing code coverage")

        if(CI_CD_COVERAGE)
            setup_target_for_coverage_lcov(
                NAME ctest_coverage
                EXECUTABLE  ctest -j ${PROCESSOR_COUNT}
                DEPENDENCIES test_project 
                BASE_DIRECTORY ../
            )
        else()
            setup_target_for_coverage_gcovr_html(NAME ctest_coverage
                EXECUTABLE  ctest -j ${PROCESSOR_COUNT}
                DEPENDENCIES test_project 
                BASE_DIRECTORY ../
            )
            target_link_libraries(test_project
                PRIVATE
                    gcov
            )
        endif()
    endif()
endif()

gtest_discover_tests(test_project)

add_custom_target(unit_tests
    COMMAND
        ctest -V
    DEPENDS
        test_project
)


install(FILES dummy_inventory.json
    DESTINATION .
)
