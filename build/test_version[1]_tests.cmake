add_test([=[test_version.BasicAssertions]=]  /home/andrey/works/HW1_CICD/Cpp_courses/build/test_version [==[--gtest_filter=test_version.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[test_version.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY /home/andrey/works/HW1_CICD/Cpp_courses/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  test_version_TESTS test_version.BasicAssertions)
