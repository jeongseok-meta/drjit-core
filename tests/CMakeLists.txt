enable_testing()

file(GLOB TEST_FILES "*.cpp")

foreach (TEST_FILE ${TEST_FILES})
  if (TEST_FILE MATCHES "test.cpp")
    continue()
  endif()
  get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
  add_executable(test_${TEST_NAME} ${TEST_NAME}.cpp test.h test.cpp ${TEST_NAME}.cpp)
  target_link_libraries(test_${TEST_NAME} PRIVATE enoki-jit)
  target_compile_definitions(test_${TEST_NAME} PRIVATE -DTEST_NAME="${TEST_NAME}")
  set_target_properties(test_${TEST_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
  add_test(
    NAME ${TEST_NAME}
    COMMAND test_${TEST_NAME}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  )
endforeach()

add_custom_target(test COMMAND CTEST_OUTPUT_ON_FAILURE=1 ${CMAKE_CTEST_COMMAND})