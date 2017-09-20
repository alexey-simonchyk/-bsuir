import math
from math import pi
import matplotlib.pyplot as plt
import numpy as np
from collections import namedtuple

SignalData = namedtuple('SignalData', 'amplitude frequency begin_phase')

SIGNAL_RATE = 2048
BUFFER_SIZE = SIGNAL_RATE


def harmonic_value(amplitude, i, frequency, begin_phase):
    return amplitude * math.sin(2 * math.pi * i * frequency / SIGNAL_RATE + begin_phase)


def form_harmonic_signal(signal_data):
    signals = []
    for data in signal_data:
        buffer = np.zeros(BUFFER_SIZE)
        for i in range(BUFFER_SIZE):
            buffer[i] = harmonic_value(data.amplitude, i, data.frequency, data.begin_phase)
        signals.append(buffer)
    return signals


def main():
    input_data_begin_phases = [
        SignalData(7, 5, pi),
        SignalData(7, 5, 0),
        SignalData(7, 5, pi / 3),
        SignalData(7, 5, pi / 6),
        SignalData(7, 5, pi / 2)
    ]

    temp = pi * 3 / 4
    input_data_frequencies = [
        SignalData(5, 1, temp),
        SignalData(5, 5, temp),
        SignalData(5, 11, temp),
        SignalData(5, 6, temp),
        SignalData(5, 3, temp)
    ]

    input_data_amplitudes = [
        SignalData(1, 3, temp),
        SignalData(2, 3, temp),
        SignalData(11, 3, temp),
        SignalData(4, 3, temp),
        SignalData(2, 3, temp)
    ]
    del temp

    result = [
        form_harmonic_signal(input_data_begin_phases),
        form_harmonic_signal(input_data_frequencies),
        form_harmonic_signal(input_data_amplitudes)
    ]

    x = np.arange(BUFFER_SIZE)
    window_counter = 0
    windows_names = [
        'Different begin phases',
        'Different frequencies',
        'Different amplitudes'
    ]

    for data in result:
        figure = plt.figure(1 + window_counter)
        figure.canvas.set_window_title(windows_names[window_counter])
        window_counter += 1

        signal_count = 0
        for signal in data:
            plt.subplot(231 + signal_count)
            signal_count += 1
            plt.plot(x, signal, 'r-')

    plt.show()


main()

