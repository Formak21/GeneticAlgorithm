# y=-(x^2)
# x in [-20;20]

# Params
a = -5
b = 5


# y = f(n); f(n) = -(x^2)
def f(n) -> float:
    x = ((int(''.join([str(i) for i in n]), 2) / int('1' * len(n), 2)) * (b - a)) + a
    return -(x ** 2)


def optimal(n) -> float:
    return 0.0