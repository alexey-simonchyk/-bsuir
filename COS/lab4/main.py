import util
import matplotlib.pyplot as plt
import numpy as np


def main():
    length = 512
    signal = util.generate_signal(length)

    # smoothed_signal = util.smooth_signal_averaging(signal)
    smoothed_signal = util.parabolic_smoothing(signal)
    # smoothed_signal = util.median_smooth(signal)

    x = np.arange(length)
    plt.subplot(211)
    plt.plot(x, signal, 'b-')
    plt.subplot(212)
    plt.plot(x, smoothed_signal, 'r-')
    plt.show()


if __name__ == '__main__':
    main()
