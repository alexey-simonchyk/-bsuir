import numpy as np
from math import pi, cos, sin, sqrt, atan2
from random import choices
import cmath


def harmonic_signal(sampling=2048, buffer_size=2048, begin_phase=3 * pi / 4, amplitude=30, frequency=1):
    result = []
    for i in range(buffer_size):
        value = amplitude * cos(2 * pi * i * frequency / sampling - begin_phase)
        result.append(value)
    return np.array(result)


def polyharmonic_signal(number_signals, amplitudes_input, begin_phases_input, sampling=2048, buffer_size=2048):
    signal = []
    amplitudes = choices(amplitudes_input, k=number_signals)
    begin_phases = choices(begin_phases_input, k=number_signals)

    for i in range(buffer_size):
        value = 0
        for frequency, (amplitude, begin_phase) in enumerate(zip(amplitudes, begin_phases)):
            value += amplitude * cos(2 * pi * i * frequency / sampling - begin_phase)
        signal.append(value)
    return np.array(signal)


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
    return sqrt(sum_sin ** 2 + sum_cos ** 2), harmonic_begin_phase


def fft(signal):
    length = len(signal)
    if length <= 1: return signal
    even = fft(signal[0::2])
    odd = fft(signal[1::2])
    temp = [cmath.exp(-2j * cmath.pi * k / length) * odd[k] for k in range(length // 2)]
    return [even[k] + temp[k] for k in range(length // 2)] + \
           [even[k] - temp[k] for k in range(length // 2)]


def amplitude_spectrum(signal):
    return [abs(temp) for temp in fft(signal)]


def restore_signal(harmonic_begin_phase, harmonic_amplitude, sampling=2048, buffer_size=2048):
    result = []
    for i in range(buffer_size):
        value = harmonic_amplitude * cos(2 * pi * i / sampling - harmonic_begin_phase)
        result.append(value)
    return np.array(result)


def restore_polyharmonic_signal(amplitudes, begin_phases, buffer_size=2048, sampling=2048):
    restored_signal = []
    for i in range(buffer_size):
        value = amplitudes[0] / 2
        for j in range(len(amplitudes)):
            value += amplitudes[j] * cos(2 * pi * (j + 1) * i / sampling - begin_phases[j])
        restored_signal.append(value)
    return np.array(restored_signal)
