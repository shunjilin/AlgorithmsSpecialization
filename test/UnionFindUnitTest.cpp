#include <gmock/gmock.h>
#include "UnionFind.hpp"


using namespace testing;
using namespace DataStructures;

class UnionFindInitialize: public Test {
public:
    UnionFind UF = UnionFind(10);
    void SetUp() override {
        UF.doUnion(0, 1);
        UF.doUnion(1, 2);
        UF.doUnion(3, 2);
        UF.doUnion(2, 4);
        UF.doUnion(5, 3);
        UF.doUnion(6, 7);
        UF.doUnion(8, 6);
        UF.doUnion(9, 7);
    }
};

TEST(UnionFind, UnionCorrect) {
    UnionFind UF = UnionFind(4);
    UF.doUnion(0, 1);
    UF.doUnion(0, 2);
    ASSERT_EQ(UF.find(0), UF.find(1));
}

TEST(UnionFind, InitialFindReturnsSameNode) {
    UnionFind UF(3);
    EXPECT_THAT(UF.find(0), 0);
    EXPECT_THAT(UF.find(1), 1);
    EXPECT_THAT(UF.find(2), 2);
}

TEST_F(UnionFindInitialize, FindConnectedComponentsCorrectly) {
    EXPECT_TRUE(UF.sameRoot(0, 5));
    EXPECT_TRUE(UF.sameRoot(4, 3));
    EXPECT_TRUE(UF.sameRoot(8, 7));
    EXPECT_FALSE(UF.sameRoot(9, 0));
}

int main(int argc, char *argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

