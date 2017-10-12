import numpy as np
from math import pi
import util
import matplotlib.pyplot as plt


AMPLITUDES = [3, 5, 6, 8, 10, 13, 16]
BEGIN_PHASES = [pi/6, pi/4, pi/3, pi/2, pi/4, pi]


def main():
    signal = util.harmonic_signal(2048, 2048)
    sum_sin, sum_cos, amplitude, harmonic_begin_phase = util.fourier(signal)
    signal_2 = util.restore_signal(2048, 2048, harmonic_begin_phase, amplitude)
    x = np.arange(2048)
    plt.plot(x, signal, 'r-', x, signal_2, 'g-')
    plt.show()


main()

