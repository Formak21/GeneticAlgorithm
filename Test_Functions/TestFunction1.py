# y=x

# y = f(n); f(n) = x
def f(n) -> float:
    x = int(''.join([str(i) for i in n]), 2)
    return x


def optimal(n) -> float:
    return int(''.join([str(i) for i in '1' * len(n)]), 2)
