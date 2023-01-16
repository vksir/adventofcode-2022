import queue

EXAMPLE_DATA = """2199943210
3987894921
9856789892
8767896789
9899965678"""


def main():
    with open('input.txt', 'r') as f:
        data = f.read()
    # data = EXAMPLE_DATA

    num_map = [list(line) for line in data.splitlines()]
    max_y = len(num_map)
    max_x = len(num_map[0])
    num_map = [[int(row[x]) for row in num_map] for x in range(max_x)]

    def is_illegal(x, y):
        return 0 <= x < max_x and 0 <= y < max_y

    def is_larger(num, x, y):
        return not is_illegal(x, y) or num_map[x][y] > num

    ans = 0
    for x in range(max_x):
        for y in range(max_y):
            num = num_map[x][y]
            if is_larger(num, x - 1, y) \
                    and is_larger(num, x + 1, y) \
                    and is_larger(num, x, y - 1) \
                    and is_larger(num, x, y + 1):
                ans += num + 1
    print(ans)

    def bfs(x, y):
        que = queue.Queue()
        que.put((x, y))
        walked = {(x, y)}

        def walk(x, y):
            if is_illegal(x, y) and num_map[x][y] != 9 and (x, y) not in walked:
                que.put((x, y))
                walked.add((x, y))

        while not que.empty():
            x, y = que.get()
            walk(x - 1, y)
            walk(x + 1, y)
            walk(x, y - 1)
            walk(x, y + 1)

        return walked

    sizes = []
    walked = set()
    for x in range(max_x):
        for y in range(max_y):
            num = num_map[x][y]
            if is_larger(num, x - 1, y) \
                    and is_larger(num, x + 1, y) \
                    and is_larger(num, x, y - 1) \
                    and is_larger(num, x, y + 1):
                if (x, y) not in walked:
                    this_walked = bfs(x, y)
                    walked |= this_walked
                    sizes.append(len(this_walked))
    sizes = sorted(sizes, reverse=True)
    print(sizes[0] * sizes[1] * sizes[2])


main()
