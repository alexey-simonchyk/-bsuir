from math import pi, sin
import matplotlib.pyplot as plt
import numpy as np
from collections import namedtuple

SignalData = namedtuple('SignalData', 'amplitude frequency begin_phase')

LENGTH_IN_SECONDS = 5
SIGNAL_RATE = 2048
BUFFER_SIZE = SIGNAL_RATE * LENGTH_IN_SECONDS


def harmonic_value(amplitude, i, frequency, begin_phase):
    return amplitude * sin(2 * pi * i * frequency / SIGNAL_RATE + begin_phase)


def form_polyharmonic_signal(signal_data):
    buffer = np.zeros(BUFFER_SIZE)
    for i in range(BUFFER_SIZE):
        for data in signal_data:
            buffer[i] += harmonic_value(data.amplitude, i, data.frequency, data.begin_phase)
    return buffer


def form_polyharmonic_signal_increases():
    signal_data = np.array([1, 5, pi / 6])
    buffer = np.zeros(BUFFER_SIZE)
    for i in range(BUFFER_SIZE):
        for j in range(5):
            buffer[i] += harmonic_value(signal_data[0], i, signal_data[1], signal_data[2])
        signal_data *= 1.05
    return buffer


def main():
    input_data = [
        SignalData(9, 1, pi / 2),
        SignalData(9, 2, 0),
        SignalData(9, 3, pi / 4),
        SignalData(9, 4, pi / 3),
        SignalData(9, 5, pi / 6)
    ]

    input_example_1 = [
        SignalData(9, 2, 0),
        SignalData(9, 2, 0),
        SignalData(9, 2, 0),
        SignalData(9, 2, 0),
        SignalData(9, 2, 0)
    ]

    input_example_2 = [
        SignalData(9, 1, pi / 2),
        SignalData(9, 2, pi / 2),
        SignalData(9, 3, pi / 2),
        SignalData(9, 4, pi / 2),
        SignalData(9, 5, pi / 2)
    ]

    buffer = form_polyharmonic_signal(input_data)
    # buffer = form_polyharmonic_signal_increases()

    x = np.arange(BUFFER_SIZE)
    plt.plot(x, buffer, 'r-')
    plt.show()

main()
