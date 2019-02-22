
set(TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/main.cpp)
add_executable(TestThreadHandler ${TEST_SOURCES})
set_target_properties(TestThreadHandler PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(TestThreadHandler PosixThreadHandler -lpthread)
