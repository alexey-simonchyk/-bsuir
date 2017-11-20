import elements

input_intensity = 1 / 60
service_time = 2 * 60
queue_length = 7
number_handlers = 2


def main():

    counter = elements.Counter()
    handlers = []

    for i in range(number_handlers):
        handlers.append(elements.Handler(service_time, counter))
    queue = elements.Queue(queue_length, handlers)
    generator = elements.Generator(input_intensity, queue)

    all_elements = [
        handlers,
        [queue],
        [generator]
    ]

    probabilities = dict()
    for i in range(number_handlers + queue_length + 1):
        probabilities[i] = 0

    number_seconds = 10000 * 60

    for i in range(number_seconds):
        for element in all_elements:
            for temp in element:
                temp.handle()
        queue.count_queue()
        temp = handlers[0].is_handling() + handlers[1].is_handling() + queue.current
        probabilities[temp] += 1

    for i in range(2 + queue_length + 1):
        probabilities[i] = float(probabilities[i] / number_seconds)
        print(str(i) + ' - ' + str(probabilities[i]))

    l = float(queue.number_cars / number_seconds)
    p = float(generator.rejected_cars / generator.generated_cars)

    print('\nL = ' + str(l))
    print('P = ' + str(p))


if __name__ == '__main__':
    main()
