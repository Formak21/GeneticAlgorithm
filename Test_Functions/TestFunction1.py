# y=x
# x in [-10^9;10^9]

# Params
a = -(10**9)
b = (10**9)


# y = f(n); f(n) = x
def f(n) -> float:
    x = ((int(''.join([str(i) for i in n]), 2) / int('1' * len(n), 2)) * (b - a)) + a
    return x
