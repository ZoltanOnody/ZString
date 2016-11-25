// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

#include "riesenie.h"

using namespace ::testing;

//Uloha 1.
TEST_F(Test, ClassDeclaration) {
	ZString s;
	ASSERT_EQ(0, s.length());
}
