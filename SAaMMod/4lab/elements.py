import random
from collections import deque


class BaseElement:
    def __init__(self, next_element):
        self._next_element = next_element

    def handle(self):
        return None

    def process(self, bid):
        return None

    def can_accept_bid(self):
        return None

    def status(self):
        return 0

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
        self.__generated_number = 0
        self.__rejected_counter = Counter()

    @property
    def generated_number(self):
        return self.__generated_number

    def handle(self):
        temp = random.randint(0, 100)
        if temp < self.__generate_probability:
            self.__generated_number += 1
            bid = self.next_element.process(Bid())
            if bid:
                self.__rejected_counter.process(bid)


class Handler(BaseElement):

    def __init__(self, probability, next_element):
        super().__init__(next_element)
        self.__probability = probability
        self.__current_bid = None

    def status(self):
        return 1 if self.__current_bid else 0

    def process(self, bid):
        if self.__current_bid:
            return bid
        else:
            self.__current_bid = bid
            return None

    def can_accept_bid(self):
        return not self.__current_bid

    def handle(self):
        if not self.__current_bid:
            return
        temp = random.randint(0, 100)
        if temp >= self.__probability:
            self.__current_bid = self.next_element.process(self.__current_bid)


class HandlerWithReject(BaseElement):

    def __init__(self, probability, next_element):
        super().__init__(next_element)
        self.__probability = probability
        self.__rejected_counter = Counter()
        self.__current_bid = None

    def status(self):
        return 1 if self.__current_bid else 0

    @property
    def rejected_counter(self):
        return self.__rejected_counter

    def process(self, bid):
        if self.__current_bid:
            return bid
        else:
            self.__current_bid = bid
            return None

    def can_accept_bid(self):
        return not self.__current_bid

    def handle(self):
        if not self.__current_bid:
            return
        temp = random.randint(0, 100)
        if self.next_element.can_accept_bid():
            if temp >= self.__probability:
                self.__current_bid = self.next_element.process(self.__current_bid)
        else:
            if temp < self.__probability:
                self.__rejected_counter.process(self.__current_bid)
                self.__current_bid = None


class Queue(BaseElement):

    def __init__(self, capacity, next_element):
        super().__init__(next_element)
        self.__capacity = capacity
        self.__queue = deque([])
        self.__number_bids = 0

    def status(self):
        return len(self.__queue)

    @property
    def number_bids(self):
        return self.__number_bids

    def process(self, bid):
        if len(self.__queue) == self.__capacity:
            return bid
        elif self.__queue:
            self.__queue.append(bid)
            return None
        else:
            temp_bid = self.next_element.process(bid)
            if temp_bid:
                self.__queue.append(bid)
                bid.time_in_queue += 1
            return None

    def can_accept_bid(self):
        return len(self.__queue) < self.__capacity

    def handle(self):
        if self.__queue:
            self.__number_bids += len(self.__queue)
            bid = self.next_element.process(self.__queue[0])
            if not bid:
                self.__queue.popleft()
        for bid in self.__queue:
            bid.time_in_queue += 1


class Counter(BaseElement):

    def __init__(self):
        super().__init__(None)
        self.__bids = []

    @property
    def bids(self):
        return self.__bids

    def can_accept_bid(self):
        return True

    def process(self, bid):
        self.__bids.append(bid)
        return None


class Bid:

    def __init__(self):
        self.__time_in_queue = 0

    @property
    def time_in_queue(self):
        return self.__time_in_queue

    @time_in_queue.setter
    def time_in_queue(self, time_in_queue):
        self.__time_in_queue = time_in_queue
