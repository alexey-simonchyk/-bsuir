import random
from collections import deque
import math


class Car:

    def __init__(self):
        self.__time_in_queue = 0


class Generator:

    def __init__(self, number_cars_per_minute, next_element):
        self.__lambda = number_cars_per_minute
        self.__next_element = next_element
        self.__generated_cars = 0
        self.__rejected_cars = 0
        self.__current_time = 0
        self.set_time()

    @property
    def rejected_cars(self):
        return self.__rejected_cars

    @property
    def generated_cars(self):
        return self.__generated_cars

    def set_time(self):
        self.__current_time = float((-1 / self.__lambda) * math.log(random.uniform(0, 1)))

    def handle(self):
        self.__current_time -= 1
        if self.__current_time <= 0:
            self.__generated_cars += 1
            self.set_time()
            car = self.__next_element.process(Car())
            if car:
                self.__rejected_cars += 1


class Counter:

    def __init__(self):
        self.__number_cars = 0

    def process(self, car):
        if car:
            self.__number_cars += 1
        return None

    @property
    def number_cars(self):
        return self.__number_cars


class Handler:

    def __init__(self, service_time, counter):
        self.__lambda = 1 / service_time
        self.__current_car = None
        self.__current_time = 0
        self.__counter = counter

    def handle(self):
        if self.__current_car:
            self.__current_time -= 1
            if self.__current_time <= 0:
                self.__current_car = self.__counter.process(self.__current_car)

    def set_time(self):
        self.__current_time = float((-1 / self.__lambda) * math.log(random.uniform(0, 1)))

    def is_handling(self):
        if self.__current_car:
            return 1
        else:
            return 0

    def process(self, car):
        if self.__current_car:
            return car
        else:
            self.set_time()
            self.__current_car = car
            return None


class Queue:

    def __init__(self, capacity, handlers):
        self.__capacity = capacity
        self.__queue = deque([])
        self.__handlers = handlers
        self.__number_cars = 0

    @property
    def number_cars(self):
        return self.__number_cars

    @property
    def current(self):
        return len(self.__queue)

    def handle(self):
        for handler in self.__handlers:
            if not self.__queue:
                return
            else:
                car = handler.process(self.__queue[0])
                if not car:
                    self.__queue.popleft()

    def count_queue(self):
        self.__number_cars += len(self.__queue)

    def process(self, car):
        for handler in self.__handlers:
            car = handler.process(car)
            if not car:
                return None

        if len(self.__queue) < self.__capacity:
            self.__queue.append(car)
            return None
        else:
            return car
