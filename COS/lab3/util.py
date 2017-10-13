import numpy as np
from math import pi, cos, sin, sqrt, atan2, hypot
from random import choices
import cmath


def harmonic_signal(buffer_size=2048):
    result = [harmonic(i) for i in range(buffer_size)]
    return np.array(result)


def harmonic(i, amplitude=30, frequency=1, begin_phase=3*pi/4, sampling=2048):
    return amplitude * cos(2 * pi * i * frequency / sampling - begin_phase)


def polyharmonic_signal(number_signals, amplitudes_input, begin_phases_input, buffer_size=2048):
    signal = []
    amplitudes = choices(amplitudes_input, k=number_signals)
    begin_phases = choices(begin_phases_input, k=number_signals)

    for i in range(buffer_size):
        value = sum([
            harmonic(i, amplitude, frequency, begin_phase)
            for frequency, (amplitude, begin_phase) in enumerate(zip(amplitudes, begin_phases))
        ])
        signal.append(value)
    return np.array(signal)


def fourier(signal):
    length = len(signal)
    harmonic_begin_phases = []
    harmonic_amplitudes = []
    for i in range(length):
        sum_sin = 0
        sum_cos = 0
        for j in range(length):
            temp = 2 * pi * j * i / length
            sum_sin += signal[j] * sin(temp)
            sum_cos += signal[j] * cos(temp)

        sum_sin *= 2 / length
        sum_cos *= 2 / length

        harmonic_begin_phases.append(atan2(sum_sin, sum_cos))
        harmonic_amplitudes.append(hypot(sum_sin, sum_cos))
    return np.array(harmonic_amplitudes), np.array(harmonic_begin_phases)


def fft(signal):
    length = len(signal)
    if length <= 1:
        return signal
    even = fft(signal[0::2])
    odd = fft(signal[1::2])
    temp = [cmath.exp(-2j * cmath.pi * k / length) * odd[k] for k in range(length // 2)]
    return [even[k] + temp[k] for k in range(length // 2)] + \
           [even[k] - temp[k] for k in range(length // 2)]


def amplitude_spectrum(signal):
    return np.array([abs(temp) for temp in fft(signal)]) / 1000


def restore_signal(harmonic_begin_phases, harmonic_amplitudes, buffer_size=2048):
    result = []
    for i in range(buffer_size):
        value = sum([
            harmonic(i, harmonic_amplitudes[j], j, harmonic_begin_phases[j])
            for j in range(buffer_size // 2 - 1)
        ])
        result.append(value)
    return np.array(result)


def restore_polyharmonic_signal(amplitudes, begin_phases, buffer_size=2048, sampling=2048):
    restored_signal = []
    for i in range(buffer_size):
        value = sum([
            harmonic(i, amplitudes[j], j, begin_phases[j])
            for j in range(1, buffer_size // 2 - 1)
        ]) + amplitudes[0] / 2
        restored_signal.append(value)
    return np.array(restored_signal)
