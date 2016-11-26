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
