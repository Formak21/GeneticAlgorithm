# y=sum(n) + cooldown
import time

# y = f(n); f(n) = sum(n)
def f(n) -> float:
    time.sleep(1)
    return float(sum(n))
