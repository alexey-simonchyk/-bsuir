import generator
import numpy as np
import matplotlib.pyplot as plt
from collections import namedtuple

Marks = namedtuple('Marks', 'math_wait dispersion standard_deviation')


def calculate_mark(numbers):
    math_wait = np.mean(numbers)
    dispersion = np.var(numbers, ddof=1)
    standard_deviation = np.std(numbers, ddof=1)
    return Marks(math_wait, dispersion, standard_deviation)


def draw_hist(numbers):
    plt.hist(numbers, 20)
    plt.show()


def main():
    numbers = []
    numbers_amount = int(input('Input amount of numbers '))
    method = int(input('Enter method for generation \n1 - Uniform distribution\n2 - Normal distribution\n'
                       '3 - Exponential distribution\n4 - Gamma distribution\n5 - Triangle distribution\n'
                       '6 - Simpson distribution\n'))

    if method == 1:
        initial_number = float(input('Input initial number '))
        finite_number = float(input('Input finite number '))
        numbers = generator.imitate_uniform_distribution(numbers_amount, initial_number, finite_number)
    elif method == 2:
        math_wait = float(input('Input math wait '))
        standard_deviation = float(input('Input standard deviation '))
        numbers = generator.imitate_normal_distribution(numbers_amount, math_wait, standard_deviation)
    elif method == 3:
        coefficient_lambda = float(input('Input lambda '))
        numbers = generator.imitate_exponential_distribution(numbers_amount, coefficient_lambda)
    elif method == 4:
        coefficient_lambda = float(input('Input lambda '))
        coefficient = int(input('Input coefficient '))
        numbers = generator.imitate_gamma_distribution(numbers_amount, coefficient_lambda, coefficient)
    elif method == 5:
        initial_number = float(input('Input initial number '))
        finite_number = float(input('Input finite number '))
        numbers = generator.imitate_triangle_distribution(numbers_amount, initial_number, finite_number)
    elif method == 6:
        initial_number = float(input('Input initial number '))
        finite_number = float(input('Input finite number '))
        numbers = generator.imitate_simpson_distribution(numbers_amount, initial_number, finite_number)

    marks = calculate_mark(numbers)
    print(
        '\nMath wait = ' + str(marks.math_wait) +
        '\nDispersion = ' + str(marks.dispersion) +
        '\nStandard deviation = ' + str(marks.standard_deviation)
    )

    draw_hist(numbers)


main()
