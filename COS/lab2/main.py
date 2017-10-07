import util
from math import pi
import numpy as np
import matplotlib.pyplot as plt


AMPLITUDE = 64
BEGIN_PHASE = pi / 8
K = int(3 * AMPLITUDE / 4)
STEP = 15


def make_good_things(plot_name, subplot, phase=0):
    signals_data = []

    for m in range(K, AMPLITUDE * 2, STEP):
        signal = util.harmonic(AMPLITUDE, m, phase)
        amplitude = util.signal_amplitude(signal)
        rms_1 = util.root_mean_square_one_element(signal)
        rms_2 = util.root_mean_square_two_element(signal)

        signals_data.append(util.calculate_error(rms_1, rms_2, amplitude))

    rms_errors_1 = np.array(list(temp.rms_1_error for temp in signals_data))
    rms_errors_2 = np.array(list(temp.rms_2_error for temp in signals_data))
    amplitude_errors = np.array(list(temp.amplitude_error for temp in signals_data))
    x = np.array(range(K, AMPLITUDE * 2, STEP))

    plt.subplot(subplot)
    plt.plot(x, rms_errors_1, 'r--', x, rms_errors_2, 'g--', x, amplitude_errors, 'b--')
    plt.title(plot_name)


def main():
    make_good_things('Without begin phase', 211)
    make_good_things('With begin phase', 212, BEGIN_PHASE)
    plt.show()



main()

