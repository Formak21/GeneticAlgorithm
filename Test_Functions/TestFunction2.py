# y=-((x1^2) + (x2^2))
# x1 in [-5;5]
# x2 in [-5;5]

# Params
a1 = -5
b1 = 5
a2 = -5
b2 = 5


# y = f(n); f(n) = -((x1^2) + (x2^2))
def f(n) -> float:
    x1 = ((int(''.join([str(i) for i in n[:len(n) // 2]]), 2) / int('1' * (len(n) // 2), 2)) * (b1 - a1)) + a1
    x2 = ((int(''.join([str(i) for i in n[len(n) // 2:]]), 2) / int('1' * (len(n) // 2), 2)) * (b2 - a2)) + a2
    return -((x1 ** 2) + (x2 ** 2))
