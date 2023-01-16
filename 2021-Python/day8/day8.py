
EXAMPLE_DATA = """be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb | fdgacbe cefdb cefbgd gcbe
edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec | fcgedb cgb dgebacf gc
fgaebd cg bdaec gdafb agbcfd gdcbef bgcad gfac gcb cdgabef | cg cg fdcagb cbg
fbegcd cbd adcefb dageb afcb bc aefdc ecdab fgdeca fcdbega | efabcd cedba gadfec cb
aecbfdg fbg gf bafeg dbefa fcge gcbea fcaegb dgceab fcbdga | gecf egdcabf bgf bfgea
fgeab ca afcebg bdacfeg cfaedg gcfdb baec bfadeg bafgc acf | gebdcfa ecba ca fadegcb
dbcfg fgd bdegcaf fgec aegbdf ecdfab fbedc dacgb gdcebf gf | cefg dcbef fcge gbcadfe
bdfegc cbegaf gecbf dfcage bdacg ed bedf ced adcbefg gebcd | ed bcgafe cdgba cbgef
egadfb cdbfeg cegd fecab cgb gbdefca cg fgcdab egfdb bfceg | gbdfcae bgc cg cgb
gcafb gcf dcaebfg ecagb gf abcdeg gaef cafbge fdbac fegbdc | fgae cfgab fg bagce"""


def get_mapping(pattern):
    mapping = {}
    num_mapping = {}
    items = [set(i.strip()) for i in pattern.split()]
    num_mapping[1] = [i for i in items if len(i) == 2][0]
    num_mapping[7] = [i for i in items if len(i) == 3][0]
    num_mapping[4] = [i for i in items if len(i) == 4][0]
    num_mapping[8] = [i for i in items if len(i) == 7][0]
    num_mapping[235] = [i for i in items if len(i) == 5]

    mapping['a'] = num_mapping[7] - num_mapping[1]
    mapping['cf'] = num_mapping[1]
    mapping['bd'] = num_mapping[4] - num_mapping[1]

    tmp_items = [i for i in items if not i >= mapping['cf']]
    num_mapping[6] = [i for i in tmp_items if i not in num_mapping[235]][0]
    mapping['c'] = num_mapping[8] - num_mapping[6]
    mapping['f'] = mapping['cf'] - mapping['c']

    num_mapping[2] = [i for i in tmp_items
                      if i != num_mapping[6] and i > mapping['c']][0]
    num_mapping[5] = [i for i in tmp_items
                      if i != num_mapping[6] and i != num_mapping[2]][0]
    mapping['b'] = num_mapping[8] - (num_mapping[2] | mapping['f'])
    mapping['d'] = mapping['bd'] - mapping['b']
    mapping['e'] = num_mapping[8] - (num_mapping[5] | mapping['c'])

    mapping['g'] = num_mapping[8] - (mapping['a'] | mapping['b'] | mapping['c']
                                  | mapping['d'] | mapping['e'] | mapping['f'])

    reversed_mapping = {''.join(v): k for k, v in mapping.items()
                        if len(v) == 1}
    return reversed_mapping


def get_value(mapping, output):
    items = [list(i.strip()) for i in output.split()]
    items = [[''.join(mapping[i]) for i in item] for item in items]
    items = [''.join(sorted(i)) for i in items]
    num_mapping = {
        'abcefg': 0,
        'cf': 1,
        'acdeg': 2,
        'acdfg': 3,
        'bcdf': 4,
        'abdfg': 5,
        'abdefg': 6,
        'acf': 7,
        'abcdefg': 8,
        'abcdfg': 9
    }
    num = ''.join([str(num_mapping[item]) for item in items])
    return int(num)


def main():
    with open('input.txt', 'r') as f:
        data = f.read()
    # data = EXAMPLE_DATA
    # data = 'acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | cdfeb fcadb cdfeb cdbaf'

    count = 0
    for line in data.splitlines():
        output = line.split('|')[1].strip()
        count += sum(iter(1 if len(item) in [2, 3, 4, 7] else 0 for item in output.split()), 0)
    print(count)

    ans = 0
    for line in data.splitlines():
        pattern, output = line.split('|')
        mapping = get_mapping(pattern)
        num = get_value(mapping, output)
        ans += num
    print(ans)


main()
