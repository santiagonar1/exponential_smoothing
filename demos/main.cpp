#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <ranges>

#include <holt_linear_trend.hpp>

struct DataPoints {
    std::vector<double> x;
    std::vector<double> y;
};

std::pair<double, double> gridSearch(const std::vector<double> &data,
                                     const std::vector<double> &alphas,
                                     const std::vector<double> &betas) {
    double bestAlpha = 0.0;
    double bestBeta = 0.0;
    double bestMSE = std::numeric_limits<double>::max();

    for (double alpha: alphas) {
        for (double beta: betas) {
            ts::HoltLinearTrend model(alpha, beta);
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

DataPoints readPairs(std::istream &input) {
    std::vector<double> x{};
    std::vector<double> y{};

    double first{}, second{};

    // Read pairs of numbers directly from the input stream
    while (input >> first >> second) {
        x.push_back(first);
        y.push_back(second);
    }

    return {x, y};
}

void writePairs(std::ostream &output, const std::vector<double> &values) {
    for (const auto val: values) { output << val << std::endl; }
}

std::vector<double> generateDoubles(double start, double end, double step) {
    auto range = std::views::iota(0) |
                 std::views::transform([start, step](int i) { return start + i * step; }) |
                 std::views::take_while([end](double value) { return value <= end; });

    std::vector<double> values;
    std::ranges::copy(range, std::back_inserter(values));
    return values;
}

int main() {
    std::ifstream ifile("/home/santiago/git/holt_winters/scripts/training_data.txt",
                        std::ifstream::in);
    if (not ifile.is_open()) { throw std::runtime_error("Could not open file"); }

    const auto [x_training, y_training] = readPairs(ifile);

    // Range of alpha and beta values to test
    const auto alphas = generateDoubles(0.01, 0.99, 0.01);
    const auto betas = alphas;

    // Perform grid search to find the best alpha and beta
    auto [bestAlpha, bestBeta] = gridSearch(y_training, alphas, betas);

    std::cout << "Best alpha: " << bestAlpha << "\n";
    std::cout << "Best beta: " << bestBeta << "\n";

    // Fit the model with the best parameters and forecast
    //     ts::HoltLinearTrend bestModel(0.9999999850988388, 0.9999999850988388);
    ts::HoltLinearTrend bestModel(bestAlpha, bestBeta);
    bestModel.fit(y_training);

    std::vector<double> forecasted_values = bestModel.forecast(5);

    std::ofstream outputFile("/home/santiago/git/holt_winters/scripts/cpp_forecast_data.txt");
    if (not outputFile.is_open()) { throw std::runtime_error("Could not open file"); }

    writePairs(outputFile, forecasted_values);

    return 0;
}