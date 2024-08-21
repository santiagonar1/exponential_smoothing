import numpy as np
import argparse
from typing import Union


def gaussian(x: Union[float, np.ndarray],
             peak: float,
             mean: float,
             deviation: float) -> Union[float, np.ndarray]:
    denominator = np.sqrt(2 * np.pi) * deviation
    return peak * (np.exp(-0.5 * ((x - mean) / deviation) ** 2) / denominator)


def generate_data(x: np.ndarray, means: np.ndarray, standard_deviations: np.ndarray,
                  proportions: np.ndarray) -> np.ndarray:
    y = np.zeros(len(x))

    for mean, deviation, peak in zip(means, standard_deviations, proportions):
        y += gaussian(x, peak, mean, deviation)

    return y


def parse_arguments():
    parser = argparse.ArgumentParser(description="Script to parse train_size.")
    parser.add_argument(
        '--train_size',
        type=float,
        default=0.64,
        help='Size of the training set as a float (default: 0.64)'
    )
    return parser.parse_args()


def main():
    args = parse_arguments()

    train_size: float = args.train_size

    means = np.array([30, 69, 50, 88], dtype=float)
    standard_deviations = np.array([3.8, 6.5, 14, 6], dtype=float)
    proportions = np.array([0.19, 0.3, 0.45, 0.06], dtype=float)

    x = np.linspace(0, 110, 110)
    y = generate_data(x, means, standard_deviations, proportions) * 1000

    num_training_values = int(len(y) * train_size)

    x_training = x[:num_training_values]
    y_training = y[:num_training_values]
    np.savetxt("training_data.txt", np.column_stack((x_training, y_training)), fmt='%.4f')

    x_real_forecast = x[num_training_values:]
    y_real_forecast = y[num_training_values:]
    np.savetxt("real_forecast_data.txt", np.column_stack((x_real_forecast, y_real_forecast)), fmt='%.4f')


if __name__ == "__main__":
    main()
