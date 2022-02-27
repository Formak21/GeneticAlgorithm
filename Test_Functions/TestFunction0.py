# y=-(x^2)
# x in [-20;20]

# Params
a = -20
b = 20


# y = f(n); f(n) = -(x^2)
def f(n) -> float:
    x = ((int(''.join([str(i) for i in n]), 2) / int('1' * len(n), 2)) * (b - a)) + a
    return -(x ** 2)
