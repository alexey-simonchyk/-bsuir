import util
import matplotlib.pyplot as plt
import numpy as np


def main():
    length = 512
    signal = util.generate_signal(length)
    smoothed_signal = util.smooth_signal_averaging(signal)
    x = np.arange(length)
    plt.plot(x, signal, 'b-', x, smoothed_signal, 'r-')
    plt.show()
    # amplitude_spectrum, begin_phase_spectrum = util.fourier(signal)


if __name__ == '__main__':
    main()
