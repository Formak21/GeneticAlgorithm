# y=-(1/x)
# x in [0;20]

# Params
a = 0
b = 20


# y = f(n); f(n) = -(1/x)
def f(n) -> float:
    x = ((int(''.join([str(i) for i in n]), 2) / int('1' * len(n), 2)) * (b - a)) + a
    try:
        return -(1/x)
    except ZeroDivisionError:
        return 0
