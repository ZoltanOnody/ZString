#include "gtest/gtest.h"
#include "../src/helpers.h"

using namespace ::testing;


TEST_F(Test, IsLowerLetter) {
    ASSERT_TRUE(is_lower_letter('a'));
    ASSERT_TRUE(is_lower_letter('z'));
    ASSERT_FALSE(is_lower_letter('a'-1));
    ASSERT_FALSE(is_lower_letter('z'+1));
}

TEST_F(Test, IsUpperLetter) {
    ASSERT_TRUE(is_upper_letter('A'));
    ASSERT_TRUE(is_upper_letter('Z'));
    ASSERT_FALSE(is_upper_letter('A'-1));
    ASSERT_FALSE(is_upper_letter('Z'+1));
}

TEST_F(Test, ToLowerLetter) {
    ASSERT_EQ(to_lower_letter('A'), 'a');
    ASSERT_EQ(to_lower_letter('Z'), 'z');
    ASSERT_EQ(to_lower_letter('c'), 'c');
    ASSERT_EQ(to_lower_letter('#'), '#');
}

TEST_F(Test, ToUpperLetter) {
    ASSERT_EQ(to_upper_letter('a'), 'A');
    ASSERT_EQ(to_upper_letter('z'), 'Z');
    ASSERT_EQ(to_upper_letter('C'), 'C');
    ASSERT_EQ(to_upper_letter('#'), '#');
}
