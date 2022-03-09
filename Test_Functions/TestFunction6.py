# y=-(((x1+c)^2) + ((x2+d)^2))
# x1 in [-10;10]
# x2 in [-10;10]

# Params
a1 = -10
b1 = 10
a2 = -10
b2 = 10
c = -5
d = -6


# y = f(n); f(n) = -(((x1+c)^2) + ((x2+d)^2))
def f(n) -> float:
    x1 = ((int(''.join([str(i) for i in n[:len(n) // 2]]), 2) / int('1' * (len(n) // 2), 2)) * (b1 - a1)) + a1
    x2 = ((int(''.join([str(i) for i in n[len(n) // 2:]]), 2) / int('1' * (len(n) // 2), 2)) * (b2 - a2)) + a2
    return -(((x1 + c) ** 2) + ((x2 + d) ** 2))
