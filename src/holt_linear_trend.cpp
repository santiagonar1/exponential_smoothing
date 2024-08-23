#include "holt_linear_trend.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>

namespace ts {
    std::vector<double> generateDoubles(double start, double end, double step) {
        std::vector<double> values{};
        double value = start;

        while (value < end) {
            values.push_back(value);
            value += step;
        }

        return values;
    }

    std::pair<double, double> gridSearch(const std::vector<double> &data,
                                         const std::vector<double> &alphas,
                                         const std::vector<double> &betas) {
        double bestAlpha = 0.0;
        double bestBeta = 0.0;
        double bestMSE = std::numeric_limits<double>::max();

        for (double alpha: alphas) {
            for (double beta: betas) {
                HoltLinearTrend model(alpha, beta);
                double mse = model.calculateMSE(data);
                if (mse < bestMSE) {
                    bestMSE = mse;
                    bestAlpha = alpha;
                    bestBeta = beta;
                }
            }
        }

        return {bestAlpha, bestBeta};
    }

    HoltLinearTrend::HoltLinearTrend(double alpha, double beta)
        : _alpha(alpha), _beta(beta), _level(0.0), _trend(0.0) {}

    void HoltLinearTrend::fit(const std::vector<double> &data, bool optimize) {
        if (data.size() < 2) {
            throw std::invalid_argument("Data should contain at least two points.");
        }

        if (optimize) { optimize_parameters(data); }

        // Initialize level and trend
        initialize(data);

        // Update level and trend for each observation in the data
        for (size_t i = 1; i < data.size(); ++i) { update(data[i]); }
    }

    std::vector<double> HoltLinearTrend::forecast(int steps_ahead) const {
        std::vector<double> forecasted_values{};
        for (int i = 1; i <= steps_ahead; ++i) { forecasted_values.push_back(_level + i * _trend); }
        return forecasted_values;
    }

    void HoltLinearTrend::initialize(const std::vector<double> &data) {
        _level = data[0];
        _trend = data[1] - data[0];
    }

    void HoltLinearTrend::update(double observation) {
        const auto previous_level = _level;
        // Update the level
        _level = _alpha * observation + (1 - _alpha) * (_level + _trend);
        // Update the trend
        _trend = _beta * (_level - previous_level) + (1 - _beta) * _trend;
    }

    void HoltLinearTrend::optimize_parameters(const std::vector<double> &data) {
        // Range of alpha and beta values to test
        const auto possible_parameters = generateDoubles(0.01, 0.99, 0.01);

        // Perform grid search to find the best alpha and beta
        const auto [bestAlpha, bestBeta] =
                gridSearch(data, possible_parameters, possible_parameters);
        _alpha = bestAlpha;
        _beta = bestBeta;
    }


    double HoltLinearTrend::calculateMSE(const std::vector<double> &data) {
        double mse = 0.0;
        initialize(data);
        for (size_t i = 1; i < data.size() - 1; ++i) {
            update(data[i]);
            const double forecast = _level + _trend;
            const double error = data[i + 1] - forecast;
            mse += error * error;
        }
        return mse / (data.size() - 1);
    }
}// namespace ts
