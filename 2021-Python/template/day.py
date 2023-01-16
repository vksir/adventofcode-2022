from util import util


class Data:
    def __init__(self, filename):
        content = util.read_input(filename)
        for line in content.splitlines():
            print(line)


class Solve1:
    def __init__(self, data: Data):
        self._data = data

    def run(self):
        pass


class Solve2:
    def __init__(self, data: Data):
        self._data = data

    def run(self):
        pass


def main():
    data = Data('input.txt')
    with util.time_it():
        print(f'Part1: {Solve1(data).run()}')
        print(f'Part2: {Solve2(data).run()}')


if __name__ == '__main__':
    main()