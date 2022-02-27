# y=-((x1^2) + (x2^2))
# x1 in [-20;20]
# x2 in [-20;20]

# Params
a = -20
b = 20


# y = f(n); f(n) = -((x1^2) + (x2^2))
def f(n) -> float:
    x1 = ((int(''.join([str(i) for i in n[:len(n) // 2]]), 2) / int('1' * (len(n) // 2), 2)) * (b - a)) + a
    x2 = ((int(''.join([str(i) for i in n[len(n) // 2:]]), 2) / int('1' * (len(n) // 2), 2)) * (b - a)) + a
    return -((x1 ** 2) + (x2 ** 2))
