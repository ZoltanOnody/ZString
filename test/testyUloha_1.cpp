// Copyright 2005, Google Inc.
// All rights reserved.

#include "gtest/gtest.h"
#include "../src/riesenie.h"

using namespace ::testing;

//Uloha 1.
TEST_F(Test, EmptyClassDeclaration) {
    ZString s;
    ASSERT_EQ(0, s.length());
    ASSERT_STREQ("", s.value());
}

TEST_F(Test, ClassDeclaration) {
    ZString s("four");
    ASSERT_EQ(4, s.length());
    ASSERT_STREQ("four", s.value());
}

TEST_F(Test, AccessOperatorSquareBracket) {
    ZString s("ab");
    ASSERT_EQ(s[0], 'a');
    ASSERT_EQ(s[1], 'b');

    try {
        s[2];
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(err.what(), std::string("Index out of range!"));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range";
    }
}

TEST_F(Test, ConcatZStrings) {
    ZString s1("AB");
    ZString s2("CD");

    ZString tmp = s1 + s2;
    ASSERT_STREQ(tmp.value(), "ABCD");

    ZString s3;
    ASSERT_STREQ((tmp + s3).value(), "ABCD");
}

TEST_F(Test, AppendZStrings) {
    ZString s1("AB");
    ZString s2("CD");

    s1 += s2;
    ASSERT_STREQ(s1.value(), "ABCD");
}

TEST_F(Test, MultiplyZStrings) {
    ZString s("AB");
    ASSERT_STREQ((s * 0).value(), "");
    ASSERT_STREQ((s * 1).value(), "AB");
    ASSERT_STREQ((s * 3).value(), "ABABAB");

    try {
        s * -1;
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const &err) {
        EXPECT_EQ(err.what(), std::string("Multiplication cannot be negative!"));
    }
    catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }

    s *= 2;
    ASSERT_STREQ(s.value(), "ABAB");
}

TEST_F(Test, LessZString) {
    ZString s1("AB");
    ZString s2("AC");
    ZString s3("ABC");

    ASSERT_TRUE(s1 < s2);
    ASSERT_TRUE(s1 < s3);

    ASSERT_FALSE(s1 < s1);
    ASSERT_FALSE(s2 < s3);
    ASSERT_FALSE(s3 < s1);
}

TEST_F(Test, GreaterZString) {
    ZString s1("AB");
    ZString s2("AC");
    ZString s3("ABC");

    ASSERT_TRUE(s2 > s1);
    ASSERT_TRUE(s3 > s1);

    ASSERT_FALSE(s1 > s1);
    ASSERT_FALSE(s3 > s2);
    ASSERT_FALSE(s1 > s3);
}

TEST_F(Test, EqualZString) {
    ZString s1("AB");
    ZString s2("AC");

    ASSERT_TRUE(s1 == s1);
    ASSERT_FALSE(s1 == s2);
}

TEST_F(Test, LessOrEqualZString) {
    ZString s1("AB");
    ZString s2("AC");

    ASSERT_TRUE(s1 <= s1);
    ASSERT_TRUE(s1 <= s2);

    ASSERT_FALSE(s2 <= s1);
}

TEST_F(Test, GreaterOrEqualZString) {
    ZString s1("AB");
    ZString s2("AC");

    ASSERT_TRUE(s1 >= s1);
    ASSERT_TRUE(s2 >= s1);

    ASSERT_FALSE(s1 >= s2);
}

TEST_F(Test, NotEqualZString) {
    ZString s1("AB");
    ZString s2("AC");

    ASSERT_TRUE(s1 != s2);
    ASSERT_FALSE(s1 != s1);
}
