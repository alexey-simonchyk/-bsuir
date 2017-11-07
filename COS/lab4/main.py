import util
import matplotlib.pyplot as plt
import numpy as np
from scipy.io.wavfile import write, read


def write_in_wav(filename, signal):
    write(filename, 44100, signal)


def read_wav():
    rate, data = read('input.wav')
    print(rate)
    return data


def main():
    length = 512 * 5
    signal = util.generate_signal(length)
    smoothed_signal_1 = util.smooth_signal_averaging(signal)
    smoothed_signal_2 = util.parabolic_smoothing(signal)
    smoothed_signal_3 = util.median_filter(signal)
    
    x = np.arange(len(length))
    plt.subplot(411)
    plt.plot(x, signal, 'b-')
    plt.subplot(412)
    plt.plot(x, smoothed_signal, 'r-')
    plt.subplot(413)
    plt.plot(x, smoothed_signal_2, 'r-')
    plt.subplot(414)
    plt.plot(x, smoothed_signal_3, 'r-')
    plt.show()


if __name__ == '__main__':
    main()
