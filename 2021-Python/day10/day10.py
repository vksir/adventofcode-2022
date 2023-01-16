EXAMPLE_DATA = """[({(<(())[]>[[{[]{<()<>>
[(()[<>])]({[<{<<[]>>(
{([(<{}[<>[]}>{[]{[(<()>
(((({<>}<{<{<>}{[]{[]{}
[[<[([]))<([[{}[[()]]]
[{[{({}]{}}([{[{{{}}([]
{<[[]]>}<{[{[{[]{()[[[]
[<(<(<(<{}))><([]([]()
<{([([[(<>()){}]>(<<{{
<{([{{}}[<[[[<>{}]]]>[]]"""


def main():
    with open('input.txt', 'r') as f:
        data = f.read()
    # data = EXAMPLE_DATA

    def find(text):
        stack = []

        def match(c):
            correct_match = {list(item)[1]: list(item)[0] for item in ['()', '[]', '{}', '<>']}
            return stack and stack[-1] == correct_match[c]

        for i in text:
            if i in ['(', '[', '{', '<']:
                stack.append(i)
            elif match(i):
                stack.pop()
            else:
                scores = {
                    ')': 3,
                    ']': 57,
                    '}': 1197,
                    '>': 25137
                }
                # return scores[i]
                return 0

        def complete():
            correct_complete = {list(item)[0]: list(item)[1] for item in ['()', '[]', '{}', '<>']}
            return [correct_complete[c] for c in reversed(stack)]

        scores = {
            ')': 1,
            ']': 2,
            '}': 3,
            '>': 4
        }
        cpt = complete()
        res = 0
        for c in cpt:
            res *= 5
            res += scores[c]
        return res

    res_lst = [find(line) for line in data.splitlines()]
    res_lst = sorted([i for i in res_lst if i != 0])
    # print(res_lst)

    # ans = sum(res_lst)
    ans = res_lst[int((len(res_lst) - 1) / 2)]
    print(ans)


main()
