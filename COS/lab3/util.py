import numpy as np
from math import pi, cos, sin, sqrt, atan2


def harmonic_signal(sampling, buffer_size, begin_phase=3 * pi / 4, amplitude=30):
    result = []
    for i in range(buffer_size):
        value = amplitude * cos(2 * pi * i / sampling - begin_phase)
        result.append(value)
    return np.array(result)


def fourier(signal, j=1):
    length = len(signal)
    sum_sin = 0
    sum_cos = 0
    for i in range(length):
        temp = 2 * pi * i * j / length
        sum_sin += signal[i] * sin(temp)
        sum_cos += signal[i] * cos(temp)

    sum_sin *= 2 / length
    sum_cos *= 2 / length
    harmonic_begin_phase = atan2(sum_sin, sum_cos)
    return sum_sin, sum_cos, sqrt(sum_sin ** 2 + sum_cos ** 2), harmonic_begin_phase


def restore_signal(sampling, buffer_size, harmonic_begin_phase, harmonic_amplitude):
    result = []
    for i in range(buffer_size):
        value = harmonic_amplitude * cos(2 * pi * i / sampling - harmonic_begin_phase)
        result.append(value)
    return np.array(result)

