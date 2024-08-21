#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <holt_linear_trend.hpp>

using ::testing::Eq;
using namespace ts;

TEST(HoltLinearTrend, ForecastsValues) {
    HoltLinearTrend model(0.1, 0.2);
    model.fit({1.0, 2.0, 1.5});

    EXPECT_THAT(model.forecast(1), Eq(std::vector{3.8200000000000003}));
}

TEST(HoltLinearTrend, RequiresAtLeastTwoDatapoints) {
    HoltLinearTrend model(0.1, 0.2);
    EXPECT_THROW(model.fit({1.0}), std::invalid_argument);
}

TEST(HoltLinearTrend, CanCalculateMSE) {
    HoltLinearTrend model(0.1, 0.2);
    EXPECT_THAT(model.calculateMSE({1.0, 2.0, 1.5}), Eq(1.125));
}
