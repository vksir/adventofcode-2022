

with open('input.txt', 'r') as f:
    data = f.read()
# data = """5483143223
# 2745854711
# 5264556173
# 6141336146
# 6357385478
# 4167524645
# 2176841721
# 6882881134
# 4846848554
# 5283751526"""

lines = data.splitlines()
max_x = len(lines)
max_y = len(lines[0])
nums = [[int(num) for num in list(line)] for line in lines]


def is_illegal(x, y):
    return 0 <= x < max_x and 0 <= y < max_y


def run():
    shine_times = 0

    for y in range(max_y):
        for x in range(max_x):
            nums[x][y] += 1

    shine_nums = [[False for _ in range(max_y)] for _ in range(max_x)]
    while True:
        is_shine = False
        for y in range(max_y):
            for x in range(max_x):
                if nums[x][y] > 9 and not shine_nums[x][y]:
                    shine_nums[x][y] = True
                    is_shine = True
                    shine_times += 1

                    for new_x in [x - 1, x, x + 1]:
                        for new_y in [y - 1, y, y + 1]:
                            if is_illegal(new_x, new_y):
                                nums[new_x][new_y] += 1
        if not is_shine:
            break

    for y in range(max_y):
        for x in range(max_x):
            if nums[x][y] > 9:
                nums[x][y] = 0
    if shine_times == 100:
        a = 3
    return shine_times


def main():
    shine_times = 0
    for i in range(1, 100000):
        res = run()
        if res == max_x * max_y:
            print(i)
            break
        shine_times += res
    # print(shine_times)


if __name__ == '__main__':
    main()




