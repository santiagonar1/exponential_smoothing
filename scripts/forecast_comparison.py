import matplotlib.pyplot as plt
import argparse
from statsmodels.tsa.holtwinters import ExponentialSmoothing
import numpy as np


def parse_arguments():
    parser = argparse.ArgumentParser(description="A script to handle num_forecasts flag.")
    parser.add_argument('--num_forecasts', type=int, default=5, help="Number of forecasts (default: 5)")

    args = parser.parse_args()
    return args


def main():
    args = parse_arguments()
    num_forecasts: int = args.num_forecasts

    training = np.loadtxt("training_data.txt")
    real_forecast = np.loadtxt("real_forecast_data.txt")
    y_cpp_forecast = np.loadtxt("cpp_forecast_data.txt")

    x_training = training[:, 0]
    y_training = training[:, 1]

    x_real_forecast = real_forecast[:, 0]
    y_real_forecast = real_forecast[:, 1]

    model = ExponentialSmoothing(y_training, trend="additive").fit(optimized=True)
    y_forecast = model.forecast(num_forecasts)

    print("Parameters values:")
    print(model.params)

    plt.figure(1)  # optional: initializes a new figure

    plt.plot(x_training, y_training, 'x', label='Training data')
    plt.plot(x_real_forecast[:num_forecasts], y_forecast, 'r', label='Forecast')
    plt.plot(x_real_forecast[:len(y_cpp_forecast)], y_cpp_forecast, label='C++ forecast')
    plt.plot(x_real_forecast, y_real_forecast, 'g', label='Real data')

    plt.title('Model output')
    plt.xlabel('X values')
    plt.ylabel('Y values')
    plt.legend()

    plt.show()

    plt.figure(2)

    plt.plot(abs(y_cpp_forecast - y_forecast))
    plt.title('Error: CPP values - python values')

    plt.show()


if __name__ == "__main__":
    main()
