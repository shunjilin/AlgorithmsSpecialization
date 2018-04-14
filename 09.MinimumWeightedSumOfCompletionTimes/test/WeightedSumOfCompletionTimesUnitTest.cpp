#include <gmock/gmock.h>
#include "WeightedSumOfCompletionTimes.hpp"

using namespace testing;
using namespace WeightedSumOfCompletionTimes;

class InitializeJobs : public Test {
public:
    std::vector<Job> jobs = {{8, 50}, {74, 59}, {31, 73}, {45, 79}, {24, 10},
                             {41, 66}, {93, 43}, {88, 4}, {28, 30}, {41, 13},
                             {4, 70}, {10, 58}};
};

TEST(WeightedSumOfCompletionTimes, ReturnCorrectDifferenceScore) {
    ASSERT_THAT(differenceScore(Job{5, 8}), -3);
}

TEST(WeightedSumOfCompletionTimes, DifferenceScoreTieBreakCorrect) {
    std::vector<Job> jobs = {{3, 2}, {2, 1}};
    std::sort(std::begin(jobs), std::end(jobs), DifferenceComparator());
    ASSERT_THAT(jobs[0].weight, 3);
}

TEST_F(InitializeJobs, CorrectedWeightedSumForDifferenceScore) {
    ASSERT_THAT(computeWeightedSumOfCompletionTimes(std::begin(jobs),
                                                    std::end(jobs),
                                                    DifferenceComparator()),
                68615);
}

TEST(WeightedSumOfCompletionTimes, ReturnCorrectRatioScore) {
    ASSERT_DOUBLE_EQ(ratioScore(Job{10,3}), static_cast<double>(10)/3);
}

TEST_F(InitializeJobs, CorrectedWeightedSumForRatioeScore) {
    ASSERT_THAT(computeWeightedSumOfCompletionTimes(std::begin(jobs),
                                                    std::end(jobs),
                                                    RatioComparator()),
                67247);
}

int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
