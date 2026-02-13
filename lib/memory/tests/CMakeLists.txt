enable_testing()

# Add the executable for unit tests
add_executable(memory_unit_tests
    test.c
    ../src/memory.c
)

# Link the library and dependencies to the executable
target_link_libraries(memory_unit_tests PRIVATE memory_lib unity::unity m)

# Add a test to be run by CTest
add_test(NAME memory_unit_tests COMMAND memory_unit_tests)

set_target_properties(memory_unit_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

set_tests_properties(memory_unit_tests PROPERTIES WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
