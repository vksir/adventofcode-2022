def grow(fish_counts):
    new_fish_counts = {}
    for fish, count in fish_counts.items():
        if fish == 0:
            new_fish_counts.setdefault(6, 0)
            new_fish_counts[6] += count
            new_fish_counts.setdefault(8, 0)
            new_fish_counts[8] += count
        else:
            new_fish_counts.setdefault(fish - 1, 0)
            new_fish_counts[fish - 1] += count
    return new_fish_counts


def main():
    with open('input.txt', 'r') as f:
        data = f.read()
    # data = '3,4,3,1,2'
    fish_lst = [int(i) for i in data.split(',')]

    fish_counts = {}
    for fish in fish_lst:
        fish_counts.setdefault(fish, 0)
        fish_counts[fish] += 1

    for i in range(256):
        fish_counts = grow(fish_counts)

    all_count = sum(item[1] for item in fish_counts.items())
    print(all_count)


main()
