import numpy as np
import matplotlib.pyplot as plt
import math
from collections import namedtuple

Marks = namedtuple('Marks', 'math_wait dispersion standard_deviation')
IndirectResult = namedtuple('IndirectResult', 'actual expected')


def generate_number(previous_number, a, m):
    next_number = (a * previous_number) % m
    return next_number, next_number / m


def calculate_mark(numbers):
    math_wait = np.mean(numbers)
    dispersion = np.var(numbers, ddof=1)
    standard_deviation = np.std(numbers, ddof=1)
    return Marks(math_wait, dispersion, standard_deviation)


def generate_number_sequence(number_count, previous_number, a, m):
    result = np.zeros(number_count)

    for i in range(number_count):
        temp = generate_number(previous_number, a, m)
        previous_number = temp[0]
        result[i] = temp[1]
    return result


def indirect_test(numbers):
    length = len(numbers) if len(numbers) % 2 == 0 else len(numbers) - 1
    number_pairs = 0
    for i in range(0, length, 2):
        temp = numbers[i]**2 + numbers[i + 1]**2
        if temp < 1:
            number_pairs += 1
    actual = 2 * number_pairs / len(numbers)
    expected = math.pi / 4
    return IndirectResult(actual, expected)


def find_period(numbers):
    temp = numbers[len(numbers) - 1]
    first_number = -1
    for i in range(len(numbers)):
        if numbers[i] == temp:
            if first_number == -1:
                first_number = i
            else:
                return i - first_number


def find_aperiodicity(sequence, period):
    length = len(sequence)
    for i in range(length):
        if i + period <= length - 1:
            if sequence[i] == sequence[i + period]:
                return i + period
        else:
            return 0
    return 0


def main():
    previous_number = float(input("Enter x0 : "))
    a = float(input("Enter a : "))
    m = float(input("Enter m : "))
    number_count = int(input("Enter number count : "))

    number_sequence = generate_number_sequence(number_count, previous_number, a, m)

    marks = calculate_mark(number_sequence)
    print(
        '\nMath wait = ' + str(marks.math_wait) +
        '\nDispersion = ' + str(marks.dispersion) +
        '\nStandard deviation = ' + str(marks.standard_deviation)
    )

    indirect_result = indirect_test(number_sequence)
    print(
        '\nActual value = ' + str(indirect_result.actual) +
        '\nExpected value = ' + str(indirect_result.expected)
    )

    period = find_period(number_sequence)

    if period is not None:
        aperiodicity = find_aperiodicity(number_sequence, period)

        print(
            "\nPeriod = " + str(period) +
            "\nAperiodicity = " + str(aperiodicity)
        )
    else:
        print('\nPeriod is larger than count of generated numbers')

    plt.hist(number_sequence, 20)
    plt.show()


main()

# period = 160000 with a = 17000, m = 160001 and x0 = 7
