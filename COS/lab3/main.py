import numpy as np
from math import pi
import util
import matplotlib.pyplot as plt


AMPLITUDES = [3, 5, 6, 8, 10, 13, 16]
BEGIN_PHASES = [pi/6, pi/4, pi/3, pi/2, pi/4, pi]

NUMBER_HARMONICS = 30


def main():

    # uncomment for harmonic/polyharmonic signal
    signal, restored_signal, restored_signal_without_begin_phase = harmonic()
    # signal, restored_signal, restored_signal_without_begin_phase = polyharmonic()
    x = np.arange(len(signal))
    plt.plot(x, signal, 'r-', x, restored_signal, 'g--', x, restored_signal_without_begin_phase, 'b--')
    plt.show()


def harmonic():
    signal = util.harmonic_signal()
    amplitude, harmonic_begin_phase = util.fourier(signal)
    restored_signal = util.restore_signal(harmonic_begin_phase, amplitude)
    restored_signal_without_begin_phase = util.restore_signal(0, amplitude)
    return signal, restored_signal, restored_signal_without_begin_phase


def polyharmonic():
    signal = util.polyharmonic_signal(NUMBER_HARMONICS, AMPLITUDES, BEGIN_PHASES)
    results = list(util.fourier(signal, j) for j in range(1, int(len(signal) / 2)))
    amplitudes = list(temp[0] for temp in results)
    begin_phases = list(temp[1] for temp in results)
    restored_signal = util.restore_polyharmonic_signal(amplitudes, begin_phases)
    restored_signal_without_begin_phases = util.restore_polyharmonic_signal(amplitudes, np.zeros(len(results)))
    return signal, restored_signal, restored_signal_without_begin_phases


main()

