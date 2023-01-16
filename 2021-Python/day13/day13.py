import re

EXAMPLE_DATA = """6,10
0,14
9,10
0,3
10,4
4,11
6,0
6,12
4,1
0,13
10,12
3,4
3,0
8,4
1,10
2,14
8,10
9,0

fold along y=7
fold along x=5"""


def main():
    with open('input.txt', 'r') as f:
        data = f.read()
    # data = EXAMPLE_DATA
    positions = set()
    folds = []
    data_lines = iter(data.splitlines())
    while True:
        line = next(data_lines)
        if not line:
            break
        x, y = line.split(',')
        positions.add((int(x), int(y)))

    while True:
        try:
            line = next(data_lines)
            a, b = re.search(r'([xy])=(\d+)', line).groups()
            folds.append((a, int(b)))
        except StopIteration:
            break

    def f(fold):
        new_positions = set()
        tmp_positions = set()
        for x, y in positions:
            if fold[0] == 'x':
                if x > fold[1]:
                    tmp_positions.add((x, y))
                else:
                    new_positions.add((x, y))
            else:
                if y > fold[1]:
                    tmp_positions.add((x, y))
                else:
                    new_positions.add((x, y))

        for x, y in tmp_positions:
            if fold[0] == 'x':
                new_positions.add((2 * fold[1] - x, y))
            else:
                new_positions.add((x, 2 * fold[1] - y))
        return new_positions

    for fold in folds:
        positions = f(fold)

    max_x = max(pos[0] for pos in positions)
    max_y = max(pos[1] for pos in positions)
    point_map = [['.' for _ in range(max_x + 1)] for _ in range(max_y + 1)]
    for x, y in positions:
        point_map[y][x] = '#'
    for line in point_map:
        print(''.join(line))


if __name__ == '__main__':
    main()