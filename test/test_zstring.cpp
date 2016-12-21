// Copyright 2005, Google Inc.
// All rights reserved.
#include "gtest/gtest.h"
#include "../src/zstring.h"

using namespace ::testing;

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

TEST(Test, IsDigit1) {
    ZString s("01012");
    ASSERT_TRUE(s.isdigit());
}

TEST(Test, IsDigi2t) {
    ZString s("01012a");
    ASSERT_FALSE(s.isdigit());
}

TEST(Test, IsAlnum1) {
    ZString s("AZaz09");
    ASSERT_TRUE(s.isalnum());
}

TEST(Test, IsAlnum2) {
    ZString s("AZaz09_");
    ASSERT_FALSE(s.isalnum());
}

TEST(Test, IsAlpha1) {
    ZString s("AZaz");
    ASSERT_TRUE(s.isalpha());
}

TEST(Test, IsAlpha2) {
    ZString s("AZaz0");
    ASSERT_FALSE(s.isalpha());
}

TEST(Test, IsLower1) {
    ZString s("hellow world, i'm lower!");
    ASSERT_TRUE(s.islower());
}

TEST(Test, IsLower2) {
    ZString s("Nope,...");
    ASSERT_FALSE(s.islower());
}

TEST(Test, IsUpper1) {
    ZString s("I'M UPPER!");
    ASSERT_TRUE(s.isupper());
}

TEST(Test, IsUpper2) {
    ZString s("BUT i AM NOT");
    ASSERT_FALSE(s.isupper());
}

TEST(Test, IsPrintable1) {
    ZString s(
            "'0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\\'()*+,-./:;<=>?@[\\\\]^_`{|}~ \\t\\n\\r\\x0b\\x0c'");
    ASSERT_TRUE(s.isprintable());
}

TEST(Test, IsPrintable2) {
    ZString s("\a");
    ASSERT_FALSE(s.isprintable());
}

TEST(Test, IsSpace1) {
    ZString s(" \\t\\n\\r\\x0b\\x0c");
    ASSERT_TRUE(s.isspace());
}

TEST(Test, IsSpace2) {
    ZString s("    .");
    ASSERT_FALSE(s.isspace());
}

TEST(Test, Index) {
    ZString s("Hi, how do you do Hillary?");
    ZString sub("Hi");

    ASSERT_EQ(s.index(sub), 0);
    ASSERT_EQ(s.index(sub, 0), 0);
    ASSERT_EQ(s.index(sub, 1), 18);

    try {
        s.index(sub, 20);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const &err) {
        EXPECT_EQ(err.what(), std::string("Substring not found!"));
    }
    catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }

    ASSERT_EQ(s.index(sub, 0, 2), 0);
    try {
        s.index(sub, 0, 1);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const &err) {
        EXPECT_EQ(err.what(), std::string("Substring not found!"));
    }
    catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(Test, RIndex1) {
    ZString s("Hi, how do you do Hillary?");
    ZString sub("Hi");

    ASSERT_EQ(s.rindex(sub), 18);
    ASSERT_EQ(s.rindex(sub, 0), 18);
    ASSERT_EQ(s.rindex(sub, 1), 18);
    ASSERT_EQ(s.rindex(sub, 0, 10), 0);

    try {
        s.rindex(sub, 1, 10);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const &err) {
        EXPECT_EQ(err.what(), std::string("Substring not found!"));
    }
    catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }

    ASSERT_EQ(s.rindex(sub, 0, 2), 0);
    try {
        s.rindex(sub, 0, 1);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const &err) {
        EXPECT_EQ(err.what(), std::string("Substring not found!"));
    }
    catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(Test, RIndex2Regression) {
    ZString s("Hi, how do you do Hillary? hmmmmm....");
    ZString sub("...");
    ASSERT_EQ(s.rindex(sub), 34);
}

TEST(Test, Reverse) {
    ZString s1("Howdy");
    ASSERT_STREQ(s1.reverse().value(), "ydwoH");
    ASSERT_STREQ(s1.value(), "Howdy"); // regression test
}

TEST(Test, Find) {
    ZString s("Hi, how do you do Hillary?");
    ZString sub1("Hi");
    ZString sub2("Trumptadada");

    ASSERT_EQ(s.find(sub1), 0);
    ASSERT_EQ(s.find(sub1, 0), 0);
    ASSERT_EQ(s.find(sub1, 1), 18);
    ASSERT_EQ(s.find(sub2), -1);
}

TEST(Test, RFind) {
    ZString s("Hi, how do you do Hillary?");
    ZString sub1("Hi");
    ZString sub2("Trumptadada");

    ASSERT_EQ(s.rfind(sub1), 18);
    ASSERT_EQ(s.rfind(sub1, 0, 10), 0);
    ASSERT_EQ(s.rfind(sub2), -1);
}

TEST(Test, Count) {
    ZString s("Hi, how do you do Hillary? hmmmmm...");
    ZString sub1("Hi");
    ZString sub2("Trumptadada");
    ZString sub3("mm");

    ASSERT_EQ(s.count(sub1), 2);
    ASSERT_EQ(s.count(sub1, 5), 1);
    ASSERT_EQ(s.count(sub1, 0, 10), 1);
    ASSERT_EQ(s.count(sub2), 0);
    ASSERT_EQ(s.count(sub3), 2);
}

TEST(Test, StartsWith) {
    ZString s("Hi, how do you do Hillary? hmmmmm...");
    ZString sub1("Hi");
    ZString sub2("Him");
    ZString sub3("Hillary");
    ZString sub4("hmmmm");

    ASSERT_TRUE(s.startswith(sub1));
    ASSERT_FALSE(s.startswith(sub1, 1));

    ASSERT_FALSE(s.startswith(sub2));

    ASSERT_FALSE(s.startswith(sub3));
    ASSERT_TRUE(s.startswith(sub3, 18));

    ASSERT_TRUE(s.startswith(sub4, 27));
    ASSERT_FALSE(s.startswith(sub4, 27, 30));
}

TEST(Test, EndsWith) {
    ZString s("Hi, how do you do Hillary? hmmmmm...");
    ZString sub1("...");
    ZString sub2("Hillary");
    ZString sub3("hmmmm");

    ASSERT_TRUE(s.endswith(sub1));
    ASSERT_TRUE(s.endswith(sub1, 1));
    ASSERT_FALSE(s.endswith(sub1, 1, 10));

    ASSERT_TRUE(s.endswith(sub2, 0, 25));

    ASSERT_TRUE(s.endswith(sub3, 0, 32));
    ASSERT_FALSE(s.endswith(sub3, 30, 32));
}

TEST(Test, Lower) {
    ZString s("Hi, how Do you Do?!");
    ASSERT_STREQ(s.lower().value(), "hi, how do you do?!");
}

TEST(Test, Upper) {
    ZString s("Hi, how Do you Do?!");
    ASSERT_STREQ(s.upper().value(), "HI, HOW DO YOU DO?!");
}

TEST(Test, OutputReprezentation) {
    ZString s("C++14 is the best!");

    std::stringstream out;
    out << s;

    ASSERT_STREQ(out.str().c_str(), "C++14 is the best!");
}

TEST(Test, Iterable) {
    ZString s("1234");

    int index=0;
    for(char c: s){
        ASSERT_EQ(c, s[index++]);
    }

    ASSERT_EQ(index, 4);  // regression test
}

TEST(Test, ReplaceOne) {
    ZString s("The President of US is Obama!");
    ASSERT_STREQ(s.replace(ZString("Obama"), ZString("Trump")).value(), "The President of US is Trump!");
}

TEST(Test, ReplaceNone) {
    ZString s("Programming");
    ASSERT_STREQ(s.replace(ZString("gaming"), ZString("")).value(), "Programming");
}

TEST(Test, ReplaceMore) {
    ZString s("aabbcc");
    ASSERT_STREQ(s.replace(ZString("ab"), ZString("")).value(), "abcc");
}

TEST(Test, ReplaceShorter) {
    ZString s("A!B!C!");
    ASSERT_STREQ(s.replace(ZString("A!"), ZString("a")).value(), "aB!C!");
}

TEST(Test, ReplaceLonger) {
    ZString s("abc");
    ASSERT_STREQ(s.replace(ZString("a"), ZString("A!")).value(), "A!bc");
}

TEST(Test, ReplaceRegressionTest) {
    ZString s("a b a b a b");
    ASSERT_STREQ(s.replace(ZString("a"), ZString("#")).value(), "# b # b # b");
}

TEST(Test, ReplaceFirstTree) {
    ZString s("a b a b a b a b a");
    ASSERT_STREQ(s.replace(ZString("a"), ZString("#"), 3).value(), "# b # b # b a b a");
}

TEST(Test, Zfill) {
    ZString s("1234");
    ASSERT_STREQ(s.zfill(1).value(), "1234");
    ASSERT_STREQ(s.zfill(6).value(), "001234");
}

TEST(Test, Swapcase) {
    ZString s("Swap ... My Case!");
    ASSERT_STREQ(s.swapcase().value(), "sWAP ... mY cASE!");
}

TEST(Test, Center){
    ZString s("Hello");
    ASSERT_STREQ(s.center(2).value(), "Hello");
    ASSERT_STREQ(s.center(10).value(), "  Hello   ");
    ASSERT_STREQ(s.center(9, '#').value(), "##Hello##");
}

TEST(Test, LJust){
    ZString s("Hello");
    ASSERT_STREQ(s.ljust(2).value(), "Hello");
    ASSERT_STREQ(s.ljust(10).value(), "     Hello");
    ASSERT_STREQ(s.ljust(9, '#').value(), "####Hello");
}

TEST(Test, Title){
    ZString s("how do_you_DO?!");
    ASSERT_STREQ(s.title().value(), "How Do_You_Do?!");
}

TEST(Test, Capitalize1){
    ZString s("how do_you_DO?!");
    ASSERT_STREQ(s.capitalize().value(), "How do_you_do?!");
}

TEST(Test, Capitalize2){
    ZString s("Wow");
    ASSERT_STREQ(s.capitalize().value(), "Wow");
}

TEST(Test, Capitalize3){
    ZString s("WoW");
    ASSERT_STREQ(s.capitalize().value(), "Wow");
}

TEST(Test, Lstrip1){
    ZString s(" howdy ");
    ASSERT_STREQ(s.lstrip().value(), "howdy ");
}

TEST(Test, Lstrip2){
    ZString s("howdyh");
    ASSERT_STREQ(s.lstrip('h').value(), "owdyh");
}

TEST(Test, Lstrip3){
    char chars[] = {'h', 'o'};
    ZString s("hohohaha");
    ASSERT_STREQ(s.lstrip(chars, 2).value(), "aha");
}

TEST(Test, Rstrip1){
    ZString s(" howdy ");
    ASSERT_STREQ(s.rstrip().value(), " howdy");
}

TEST(Test, Rstrip2){
    ZString s("howdyh");
    ASSERT_STREQ(s.rstrip('h').value(), "howdy");
}

TEST(Test, Rstrip3){
    char chars[] = {'h', 'o'};
    ZString s("hahahoho");
    ASSERT_STREQ(s.rstrip(chars, 2).value(), "haha");
}

TEST(Test, Strip1){
    ZString s(" howdy ");
    ASSERT_STREQ(s.strip().value(), "howdy");
}

TEST(Test, Strip2){
    ZString s("howdyh");
    ASSERT_STREQ(s.strip('h').value(), "owdy");
}

TEST(Test, Strip3){
    char chars[] = {'h', 'o'};
    ZString s("hahahoho");
    ASSERT_STREQ(s.strip(chars, 2).value(), "aha");
}

TEST(Test, Split1){
    ZString s("How do you do?");
    std::vector <ZString> data = s.split();
    ASSERT_EQ(data.size(), 4);
    ASSERT_STREQ(data[0].value(), "How");
    ASSERT_STREQ(data[1].value(), "do");
    ASSERT_STREQ(data[2].value(), "you");
    ASSERT_STREQ(data[3].value(), "do?");
}

TEST(Test, Split2){
    ZString s("AaaBaaC");
    std::vector <ZString> data = s.split(ZString("aa"));
    ASSERT_EQ(data.size(), 3);
    ASSERT_STREQ(data[0].value(), "A");
    ASSERT_STREQ(data[1].value(), "B");
    ASSERT_STREQ(data[2].value(), "C");
}

TEST(Test, Split3){
    ZString s("AaaBaaC");
    std::vector <ZString> data = s.split(ZString("aa"), 1);
    ASSERT_EQ(data.size(), 2);
    ASSERT_STREQ(data[0].value(), "A");
    ASSERT_STREQ(data[1].value(), "BaaC");
}

TEST(Test, Rsplit1) {
    ZString s("How do you do?");
    std::vector<ZString> data = s.rsplit();
    ASSERT_EQ(data.size(), 4);
    ASSERT_STREQ(data[0].value(), "How");
    ASSERT_STREQ(data[1].value(), "do");
    ASSERT_STREQ(data[2].value(), "you");
    ASSERT_STREQ(data[3].value(), "do?");
}

TEST(Test, Rsplit2) {
    ZString s("AaaBaaC");
    std::vector<ZString> data = s.rsplit(ZString("aa"));
    ASSERT_EQ(data.size(), 3);
    ASSERT_STREQ(data[0].value(), "A");
    ASSERT_STREQ(data[1].value(), "B");
    ASSERT_STREQ(data[2].value(), "C");
}

TEST(Test, Rsplit3) {
    ZString s("AaaBaaC");
    std::vector <ZString> data = s.rsplit(ZString("aa"), 1);
    ASSERT_EQ(data.size(), 2);
    ASSERT_STREQ(data[0].value(), "AaaB");
    ASSERT_STREQ(data[1].value(), "C");
}
