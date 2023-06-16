#include "gtest-1.8.1/gtest.h"
//#include "../src/string_map.h"

TEST(TestSuite, Primero) {
    EXPECT_EQ(1,1);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
