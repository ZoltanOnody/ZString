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
