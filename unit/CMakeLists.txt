add_executable(test_main test_main.cc)

include_directories(${GTEST_INCLUDE_DIRS})
link_directories(${GTEST_LIBRARY_DIRS})

target_link_libraries(test_main PRIVATE ${GTEST_LIBRARIES})
add_test(NAME AntlrExprUnit COMMAND test_main  	RETURN_VALUE )
