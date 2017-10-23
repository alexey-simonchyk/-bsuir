from elements import Queue, Handler, HandlerWithReject, Counter, Generator


STATES_PROBABILITY = {'000': 0, '010': 0, '001': 0, '110': 0, '011': 0, '111': 0, '211': 0, '210': 0}


def main():
    # q = int(input('Enter q: '))
    # pi1 = int(input('Enter pi1: '))
    # pi2 = int(input('Enter pi2: '))
    # queue_capacity = int(input('Enter queue capacity: '))
    q = 50.0
    pi1 = 40.0
    pi2 = 40.0
    queue_capacity = 2
    number_steps = 100000

    counter = Counter()
    handler = Handler(pi2, counter)
    handler_with_reject = HandlerWithReject(pi1, handler)
    queue = Queue(queue_capacity, handler_with_reject)
    generator = Generator(q, queue)

    elements = [
        handler,
        handler_with_reject,
        queue,
        generator
    ]
    for i in range(number_steps):
        for element in elements:
            element.handle()
        state = str(queue.status()) + str(handler_with_reject.status()) + str(handler.status())
        STATES_PROBABILITY[state] += 1

    a = len(counter.bids) / number_steps
    l = queue.number_bids / number_steps
    q = len(counter.bids) / generator.generated_number

    print()
    for key, value in STATES_PROBABILITY.items():
        print('%s : %s' % (key, str(value / number_steps)))
        STATES_PROBABILITY[key] = float(value / number_steps)

    bids_time_in_queue = [bid.time_in_queue for bid in handler_with_reject.rejected_counter.bids + counter.bids]
    w = sum(bids_time_in_queue) / generator.generated_number

    print('\nA = ' + str(a))
    print('L = ' + str(l))
    print('W = ' + str(w))
    print('Q = ' + str(q))


if __name__ == '__main__':
    main()
