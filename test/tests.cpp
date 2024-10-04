#include <gtest/gtest.h>
#include "../src/Eleven.cpp"

TEST(test_01, eleven_tests){
    Eleven a1;
    ASSERT_EQ(a1.get_size(), 1);
    ASSERT_EQ(a1.get_data()[0], '0');
}

TEST(test_02, eleven_tests){
    Eleven a2(6, '4');
    ASSERT_EQ(a2.get_size(), 6);
    ASSERT_EQ(a2.get_data()[0], '4');
}


TEST(test_03, eleven_tests){
    Eleven a3("91A40");
    ASSERT_EQ(a3.get_size(), 5);
    ASSERT_EQ(a3.get_data()[2], 'A');
}

TEST(test_04, eleven_tests){
    Eleven a4 = {'0', '5', 'A', '0', '0'};
    ASSERT_EQ(a4.get_size(), 4);
    ASSERT_EQ(a4.get_data()[0], '5');
}

TEST(test_05, eleven_tests){
    Eleven sub("97A10A");
    Eleven a5(sub);
    ASSERT_EQ(a5.get_size(), 6);
    ASSERT_EQ(a5.get_data()[1], '7');
    ASSERT_TRUE(a5 == sub);
    ASSERT_FALSE(a5 > sub);
    ASSERT_FALSE(a5 < sub);
}

TEST(test_06, eleven_tests){
    Eleven a6("9876");
    Eleven sub("00AA1");
    a6 = sub;
    ASSERT_EQ(a6.get_size(), 3);
    ASSERT_EQ(a6.get_data()[1], 'A');
    ASSERT_TRUE(a6 == sub);
    ASSERT_FALSE(a6 > sub);
    ASSERT_FALSE(a6 < sub);

}

TEST(test_07, eleven_tests){
    Eleven a7("001944AA9");
    Eleven sub("09A13");
    a7 += sub;
    ASSERT_EQ(a7.get_size(), 7);
    ASSERT_EQ(a7.get_data()[1], '9');
    ASSERT_FALSE(a7 == sub);
    ASSERT_TRUE(a7 > sub);
    ASSERT_FALSE(a7 < sub);
}

TEST(test_08, eleven_tests){
    Eleven a8("0A049167");
    Eleven sub("1234A");
    a8 -= sub;
    ASSERT_EQ(a8.get_size(), 7);
    ASSERT_EQ(a8.get_data()[0], 'A');
    ASSERT_TRUE(a8 > sub);
    ASSERT_TRUE(sub < a8);
}