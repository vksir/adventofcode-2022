def cal(x):
    return int((1 + x) * x / 2)


def get_res(nums, n):
    return sum(cal(abs(num - n)) for num in nums)


def main():
    with open('input.txt', 'r') as f:
        data = f.read()
    # data = '16,1,2,0,4,2,7,1,2,14'

    nums = [int(i) for i in data.split(',')]
    min_res = float('inf')
    ans = None
    for n in range(min(nums), max(nums) + 1):
        res = get_res(nums, n)
        if res < min_res:
            min_res = res
            ans = n
    print(ans, min_res)


main()
