import random


class BaseElement:
    def __init__(self, next_element):
        self._status = 0
        self._next_element = next_element

    def handle(self):
        print()

    @property
    def status(self):
        return self._status

    @status.setter
    def status(self, status):
        self._status = status

    @property
    def next_element(self):
        return self._next_element

    @next_element.setter
    def next_element(self, next_element):
        self._next_element = next_element


class Generator(BaseElement):

    def __init__(self, generate_probability, next_element):
        super().__init__(next_element)
        self.__generate_probability = generate_probability

    def handle(self):
        temp = random.randint(0, 100)
        if temp < self.__generate_probability:
            if type(self.next_element) is Queue:
                self.next_element.put_in_queue()
            elif self.next_element.status == 0:
                self.next_element.status += 1


class Handler(BaseElement):

    def __init__(self, probability, next_element):
        super().__init__(next_element)
        self.__probability = probability

    def handle(self):
        if self.status == 0:
            return
        temp = random.randint(0, 100)
        if self.next_element.status == 0 or type(self.next_element) is Counter:
            if temp >= self.__probability:
                self.status = 0
                self.next_element.status += 1


class HandlerWithReject(BaseElement):

    def __init__(self, probability, next_element):
        super().__init__(next_element)
        self.__probability = probability

    def handle(self):
        if self.status == 0:
            return
        temp = random.randint(0, 100)
        if self.next_element.status == 0 or type(self.next_element) is Counter:
            if temp >= self.__probability:
                self.status = 0
                self.next_element.status += 1
                return
        if temp < self.__probability and self.next_element.status > 0:
            self.status = 0
            return


class Queue(BaseElement):

    def __init__(self, capacity, next_element):
        super().__init__(next_element)
        self.__capacity = capacity
        self.__busy_places = 0
        self.__number_elements = 0

    def is_empty(self):
        return self._status == 0

    def put_in_queue(self):
        if self.status == 0 and self.next_element.status == 0:
            self.next_element.status += 1
        elif not self.is_full():
            self.status += 1

    def is_full(self):
        return self._status == self.__capacity

    @property
    def number_elements(self):
        return self.__number_elements

    def handle(self):
        if self.status == 0:
            return
        self.__number_elements += self.status
        if self.next_element.status == 0:
            self.next_element.status += 1
            self.status -= 1


class Counter(BaseElement):

    def __init__(self):
        super().__init__(None)
