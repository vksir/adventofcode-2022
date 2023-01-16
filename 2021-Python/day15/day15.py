EXAMPLE_DATA = """1163751742
1381373672
2136511328
3694931569
7463417111
1319128137
1359912421
3125421639
1293138521
2311944581"""


def main():
    with open('input.txt', 'r') as f:
        data = f.read()
    data = EXAMPLE_DATA

    num_map = [list(line) for line in data.splitlines()]
    max_y = len(num_map)
    max_x = len(num_map[0])
    num_map = [[int(row[x]) for row in num_map] for x in range(max_x)]

    cost_map = [[None for _ in range(max_y)] for _ in range(max_x)]
    cost_map[0][0] = num_map[0][0]
