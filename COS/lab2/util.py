import numpy as np
import math
from math import pi, sqrt, sin, cos
from collections import namedtuple

SignalData = namedtuple('SignalData', 'rms_1_error rms_2_error amplitude_error')


def harmonic(amplitude, length, phase):
    res = []
    for i in range(length):
        temp = math.sin(2 * pi * i / amplitude + phase)
        res.append(temp)
    return np.array(res)


# Средне квадратичное значение
def root_mean_square_one_element(signal):
    length = len(signal)
    result = 1 / (length + 1) * sum(value ** 2 for value in signal)
    return sqrt(result)


def root_mean_square_two_element(signal):
    length = len(signal)
    result = 1 / (length + 1) * sum(value ** 2 for value in signal)
    result -= (1 / (length + 1) * sum(signal)) ** 2
    return sqrt(result)


def calculate_error(root_mean_square_1, root_mean_square_2, amplitude):
    return SignalData(
        0.707 - root_mean_square_1,
        0.707 - root_mean_square_2,
        1 - amplitude
    )


def signal_amplitude(signal):
    length = len(signal)
    sum_sin = 0
    sum_cos = 0
    for i in range(length):
        temp = 2 * pi * i / length
        sum_sin += signal[i] * sin(temp)
        sum_cos += signal[i] * cos(temp)

    sum_sin *= 2 / length
    sum_cos *= 2 / length
    return sqrt(sum_sin ** 2 + sum_cos ** 2)

