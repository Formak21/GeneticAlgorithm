
# Params
a1 = -50
b1 = 50
a2 = -50
b2 = 50
K = 500
D = 25
A1 = [0, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32]
A2 = [0, -32, -32, -32, -32, -32, -16, -16, -16, -16, -16, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 32, 32, 32, 32, 32]


def f(n) -> float:
    x1 = ((int(''.join([str(i) for i in n[:len(n) // 2]]), 2) / int('1' * (len(n) // 2), 2)) * (b1 - a1)) + a1
    x2 = ((int(''.join([str(i) for i in n[len(n) // 2:]]), 2) / int('1' * (len(n) // 2), 2)) * (b2 - a2)) + a2
    answ = 1 / K + sum([1 / (i + ((x1 - A1[i]) ** 6) + ((x2 - A2[i]) ** 6)) for i in range(1, D + 1)])
    return 1 / answ


def optimal(n) -> float:
    return 0.99800384
