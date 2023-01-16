

def draw_map(num_map, draw_num):
    for x in range(5):
        for y in range(5):
            num_map[x][y] = num_map[x][y] if num_map[x][y] != draw_num else None


def is_success(num_map):
    for y in range(5):
        raw = [num_map[x][y] for x in range(5)]
        if raw == [None] * 5:
            return True
    for x in range(5):
        column = [num_map[x][y] for y in range(5)]
        if column == [None] * 5:
            return True
    return False


def get_score(num_map, last_num):
    left_num_sum = 0
    for x in range(5):
        for y in range(5):
            if num_map[x][y] is not None:
                left_num_sum += num_map[x][y]
    return left_num_sum * last_num


def main():
    with open('input.txt', 'r') as f:
        nums = [int(num) for num in f.readline().split(',')]

        num_maps = []
        while True:
            f.readline()
            lines = []
            for _ in range(5):
                lines.append(f.readline())
            if lines == [''] * 5:
                break
            num_map = [[int(num) for num in line.split()] for line in lines]
            num_maps.append(num_map)

    win_index = []
    for num in nums:
        for i, num_map in enumerate(num_maps):
            draw_map(num_map, num)
            if is_success(num_map) and i not in win_index:
                print(get_score(num_map, num))
                win_index.append(i)
                # return


if __name__ == '__main__':
    main()
