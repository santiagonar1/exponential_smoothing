#ifndef HOLT_LINEAR_TREND_HPP
#define HOLT_LINEAR_TREND_HPP

#include <vector>

namespace ts {
    class HoltLinearTrend {
    public:
        // Constructor with smoothing parameters
        HoltLinearTrend(double alpha, double beta);

        // Fit the model
        void fit(const std::vector<double> &data, bool optimize);

        // Forecast a certain number of steps ahead
        [[nodiscard]] std::vector<double> forecast(int steps_ahead) const;

        // Calculate Mean Squared Error (MSE) for given data
        [[nodiscard]] double calculateMSE(const std::vector<double> &data);

    private:
        double _alpha;// Smoothing parameter for level
        double _beta; // Smoothing parameter for trend
        double _level;
        double _trend;

        // Helper methods to initialize level and trend
        void initialize(const std::vector<double> &data);
        void update(double observation);

        void optimize_parameters(const std::vector<double> &data);
    };
}// namespace ts

#endif// HOLT_LINEAR_TREND_HPP
