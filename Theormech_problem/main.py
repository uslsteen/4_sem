import numpy as np
import plotly.graph_objs as go


u=np.linspace(-10, 10, 500)
v=np.linspace(-10, 10, 500)
u,v=np.meshgrid(u,v)
u=u.flatten()
v=v.flatten()

x = u
y = v
z = np.power(x, 2) + np.power(y, 2)

z1 = -2 * np.power(x, 6) + 4 * np.power(y, 8) - 4 * np.power(y, 6)



fig = go.Figure()

fig.add_trace(
    go.Scatter3d(
        x = x,
        y = y,
        z= z,
        mode = "lines",
        marker = dict(color = 'green', size = 10)


    )
)

fig.add_trace(
    go.Scatter3d(
        x=x,
        y=y,
        z=z1,
        mode = "lines",
        marker = dict(color = 'red', size = 10)

    )
)



fig.show()



