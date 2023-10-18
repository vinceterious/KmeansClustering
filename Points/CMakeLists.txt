add_library(points STATIC Points.cpp)

################################
# Unit Tests
################################
# Add test cpp file
add_executable( runPointsTests ut/TestPoints.cpp )
# Link test executable against gtest & gtest_main
target_link_libraries(runPointsTests gtest gtest_main)
add_test( runPointsTests runPointsTests )