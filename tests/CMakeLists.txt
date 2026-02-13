add_executable(test_abs numeric/test_abs.c)
target_link_libraries(test_abs PRIVATE arithmos)
add_test(NAME abs COMMAND test_abs)

add_executable(test_gcd numeric/test_gcd.c)
target_link_libraries(test_gcd PRIVATE arithmos)
add_test(NAME gcd COMMAND test_gcd)

add_executable(test_lcm numeric/test_lcm.c)
target_link_libraries(test_lcm PRIVATE arithmos)
add_test(NAME lcm COMMAND test_lcm)

add_executable(test_multiply numeric/test_multiply.c)
target_link_libraries(test_multiply PRIVATE arithmos)
add_test(NAME multiply COMMAND test_multiply)

add_executable(test_power numeric/test_power.c)
target_link_libraries(test_power PRIVATE arithmos)
add_test(NAME power COMMAND test_power)
