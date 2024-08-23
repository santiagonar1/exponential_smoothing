#include <fstream>
#include <iostream>

#include <holt_linear_trend.hpp>

struct DataPoints {
    std::vector<double> x;
    std::vector<double> y;
};

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

int main() {
    std::ifstream ifile("/home/santiago/git/holt_winters/scripts/training_data.txt",
                        std::ifstream::in);
    if (not ifile.is_open()) { throw std::runtime_error("Could not open file"); }

    const auto [x_training, y_training] = readPairs(ifile);


    // Fit the model with the best parameters and forecast
    ts::HoltLinearTrend bestModel(0, 0);
    bestModel.fit(y_training, true);
    std::vector<double> forecasted_values = bestModel.forecast(5);

    std::ofstream outputFile("/home/santiago/git/holt_winters/scripts/cpp_forecast_data.txt");
    if (not outputFile.is_open()) { throw std::runtime_error("Could not open file"); }

    writePairs(outputFile, forecasted_values);

    return 0;
}