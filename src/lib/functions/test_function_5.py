# y=sum(n) + cooldown
import time


# y = f(n); f(n) = sum(n)
def f(n) -> float:
    time.sleep(0.1)
    return float(sum(n))


def optimal(n) -> float:
    return len(n)