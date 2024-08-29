#include <gtest/gtest.h>
#include "ip_filter.h"

TEST(ip_filter_unit_test, split_test) {

   const std::string phrase = "Some Cognac Would Be Nice Now";

    std::vector<std::string> words = split(phrase, ' ');
    std::vector<std::vector<std::string>> ip_pool= {{}};
    std::vector<std::vector<int>> intVec= {{}};
    convert_to_int(&ip_pool, &intVec);

    EXPECT_EQ(words[0], "Some");
    EXPECT_EQ(words[3], "Be");
    EXPECT_EQ(words[5], "Now");
}

TEST(ip_filter_unit_test, ip_sort_test) {

  std::vector<std::vector<int>> intVec = {{55, 4, 67, 6}, {0, 0, 0}, {7, 6}};

  ip_sort(&intVec);

    EXPECT_EQ(intVec[0][0], 0);
    EXPECT_EQ(intVec[1][1], 6);
    EXPECT_EQ(intVec[2][3], 55);
}
