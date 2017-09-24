import numpy as np
from math import sqrt, log
from functools import reduce

GAUS_STEP = 6


def generate_number(previous_number, a, m):
    next_number = (a * previous_number) % m
    return next_number, next_number / m


def random_numbers(numbers_amount, previous_number=7, a=17000, m=160001):
    result = np.zeros(numbers_amount)

    for i in range(numbers_amount):
        temp = generate_number(previous_number, a, m)
        previous_number = temp[0]
        result[i] = temp[1]
    return result


def imitate_uniform_distribution(numbers_amount, initial_number, finite_number):
    numbers = random_numbers(numbers_amount)
    result = []

    for i in range(numbers_amount):
        result.append(initial_number + (finite_number - initial_number) * numbers[i])
    return np.array(result)


def imitate_normal_distribution(numbers_amount, math_wait, standard_deviation):
    length = numbers_amount * GAUS_STEP
    numbers = random_numbers(length)
    result = []

    for i in range(0, length, GAUS_STEP):
        result.append(
            math_wait + standard_deviation * sqrt(12 / GAUS_STEP) * (np.sum(numbers[i:i + GAUS_STEP]) - GAUS_STEP / 2)
        )
    return np.array(result)


def imitate_exponential_distribution(numbers_amount, coefficient_lambda):
    numbers = random_numbers(numbers_amount)
    result = []

    for i in range(numbers_amount):
        result.append(-1 / coefficient_lambda * log(numbers[i]))
    return np.array(result)


def imitate_gamma_distribution(numbers_amount, coefficient_lambda, coefficient):
    length = numbers_amount * coefficient
    numbers = random_numbers(length)
    result = []

    for i in range(0, length, coefficient):
        result.append(
            -1 / coefficient_lambda * log(reduce(lambda x, a: x * a, numbers[i:i + coefficient]))
        )
    return np.array(result)


def imitate_triangle_distribution(numbers_amount, initial_number, finite_number):
    numbers = random_numbers(numbers_amount)
    result = []

    for i in range(0, numbers_amount, 2):
        result.append(initial_number + (finite_number - initial_number) * max(numbers[i: i + 2]))
    return np.array(result)


def imitate_simpson_distribution(numbers_amount, initial_number, finite_number):
    length = numbers_amount * 2
    numbers = imitate_uniform_distribution(length, initial_number, finite_number)
    result = []

    for i in range(0, length, 2):
        result.append(numbers[i] + numbers[i + 1])
    return np.array(result)
