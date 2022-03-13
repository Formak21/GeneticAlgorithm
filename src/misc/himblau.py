import plotly.graph_objs as go
from numpy import linspace


def f(x):
    return -((x[0]**2 + x[1] - 7) ** 2 + (x[1] ** 2 + x[0] - 11) ** 2)


x1 = list(linspace(-5, 5, 100))
x2 = list(linspace(-5, 5, 100))
z = []
x=[]
y=[]
for i in x1:
    z.append([])
    for j in x2:
        z[-1].append(f((i, j)))
# print(z)
fig = go.Figure()
fig.add_trace(go.Surface(x=x1, y=x2, z=z))
fig.show()
