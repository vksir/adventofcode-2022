import re


def get_line_positions(x1, y1, x2, y2):
    if x1 == x2:
        x = x1
        return [(x, y) for y in range(min(y1, y2), max(y1, y2) + 1)]
    elif y1 == y2:
        y = y1
        return [(x, y) for x in range(min(x1, x2), max(x1, x2) + 1)]
    elif y1 - y2 == x1 - x2:
        c = abs(x1 - x2)
        return [(min(x1, x2) + i, min(y1, y2) + i) for i in range(c + 1)]
    elif y1 - y2 == -(x1 - x2):
        c = abs(x1 - x2)
        return [(max(x1, x2) - i, min(y1, y2) + i) for i in range(c + 1)]
    else:
        return []


def main():
    with open('input.txt', 'r') as f:
        data = f.read()
#     data = """0,9 -> 5,9
# 8,0 -> 0,8
# 9,4 -> 3,4
# 2,2 -> 2,1
# 7,0 -> 7,4
# 6,4 -> 2,0
# 0,9 -> 2,9
# 3,4 -> 1,4
# 0,0 -> 8,8
# 5,5 -> 8,2"""
    lines = data.splitlines()
    data = []
    pattern = re.compile(r'([0-9]+),([0-9]+) -> ([0-9]+),([0-9]+)')
    for line in lines:
        res = pattern.findall(line)
        x1, y1, x2, y2 = [int(num) for num in res[0]]
        data.append([x1, y1, x2, y2])

    position_counts = {}
    for line in data:
        positions = get_line_positions(*line)
        for pos in positions:
            position_counts.setdefault(pos, 0)
            position_counts[pos] += 1

    point_count = 0
    for position_count in position_counts.values():
        if position_count >= 2:
            point_count += 1
    print(point_count)


if __name__ == '__main__':
    print(get_line_positions(1, 1, 3, 3))
    print(get_line_positions(1, 3, 3, 1))
    main()
