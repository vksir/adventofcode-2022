EXAMPLE_DATA = """NNCB

CH -> B
HH -> N
CB -> H
NH -> C
HB -> C
HC -> B
HN -> C
NN -> C
BH -> H
NC -> B
NB -> B
BN -> B
BB -> N
BC -> B
CC -> N
CN -> C"""


def insert(msg, pattern, char_counts):
    new_msg = {}
    for sub_pattern, count in msg.items():
        if sub_pattern in pattern:
            insert_char = pattern[sub_pattern]
            char_counts.setdefault(insert_char, 0)
            char_counts[insert_char] += count
            new_msg.setdefault(sub_pattern[0] + insert_char, 0)
            new_msg[sub_pattern[0] + insert_char] += count
            new_msg.setdefault(insert_char + sub_pattern[1], 0)
            new_msg[insert_char + sub_pattern[1]] += count
        else:
            new_msg.setdefault(sub_pattern, 0)
            new_msg[sub_pattern] += count
    return new_msg


def main():
    with open('input.txt', 'r') as f:
        data = f.read()
    data = EXAMPLE_DATA

    origin_msg = data.splitlines()[0]
    char_counts = {}
    for c in origin_msg:
        if c not in char_counts:
            char_counts[c] = origin_msg.count(c)
    msg = {}
    for i in range(1, len(origin_msg)):
        msg.setdefault(origin_msg[i - 1:i + 1], 0)
        msg[origin_msg[i - 1:i + 1]] += 1

    origin_pattern = data.splitlines()[2:]
    pattern = {}
    for line in origin_pattern:
        a, b = line.split('->')
        pattern[a.strip()] = b.strip()

    for _ in range(40):
        msg = insert(msg, pattern, char_counts)
        # print(msg)

    char_count_items = sorted(char_counts.items(), key=lambda item: item[1])
    print(char_count_items[-1][1] - char_count_items[0][1])


if __name__ == '__main__':
    main()
