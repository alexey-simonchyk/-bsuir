from math import pi, sin, atan2, cos, hypot
import numpy
import random


SAMPLE_RATE = 512
B1 = 10
B2 = 100000
HARMONIC_RANGE = range(50, 71)


def generate_signal(length):
    result = []
    for i in range(length):
        temp = B1 * sin(2 * pi * i / SAMPLE_RATE)
        for j in HARMONIC_RANGE:
            random_number = random.randint(0, 1)
            temp += (-1) ** random_number * B2 * sin(2 * pi * i * j / SAMPLE_RATE)
        result.append(temp)
    return numpy.array(result)


def parabolic_smoothing(signal):
    result = [temp for temp in signal]
    for i in range(3, len(result) - 3):
        result[i] = (1 / 231) * (5 * result[i - 3] - 30 * result[i - 2] + 75 * result[i - 1] + 131 *
                                 result[i] + 75 * result[i + 1] - 30 * result[i + 2] + 5 * result[i + 3])
    return numpy.array(result)


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
    return harmonic_amplitudes, harmonic_begin_phases


def median_filter(signal, N=7):
    result = [temp for temp in signal]
    step = N // 2
    for i in range(step, len(signal) - step):
        temp = signal[i - step: i + step + 1]
        window = sorted(temp)
        result[i] = window[N // 2 + 1]
    return numpy.array(result)


def median_smooth(signal, N=7, K=5):
    step = int((N - 1) / 2 + K)
    result = [temp for temp in signal]
    for i in range(step, len(result) - step - 1):
        result[i] = sum([result[i] for i in range(i - step, i + step + 1)]) / (N - 2 * K)
    return numpy.array(result)


def smooth_signal_averaging(signal):
    return numpy.array([signal[0]] + [numpy.mean(signal[i - 1] + signal[i] + signal[i + 1]) for i in range(1, len(signal) - 1)] + [signal[-1]])
