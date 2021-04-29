

import numpy as np
import plotly.graph_objs as go
from plotly.subplots import make_subplots

# Initialize figure with 4 3D subplots
"""fig = make_subplots(
    rows=2, cols=2,
    specs=[[{'type': 'surface'}, {'type': 'surface'}],
           [{'type': 'surface'}, {'type': 'surface'}]])"""




u=np.linspace(-10, 10, 250)
v=np.linspace(-10, 10, 250)
u,v=np.meshgrid(u,v)
u=u.flatten()
v=v.flatten()

x = u
y = v
z = np.power(x, 2) + np.power(y, 2)

z1 = -2 * np.power(x, 6) + 4 * np.power(y, 8) - 4 * np.power(y, 6)


fig = make_subplots(rows=1, cols=2)


fig = go.Figure()


fig.add_trace(go.Scatter3d(x = x, y = y, z= z, mode = "lines",
                           marker = dict(color = 'green', size = 10)))

fig.add_trace(go.Scatter3d(x=x, y=y, z=z1, mode = "lines", 
                           marker = dict(color = 'red', size = 10)))


"""
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
"""




fig.update_layout(  #scene1_aspectmode='auto',
                   scene1 = dict(
                   xaxis = dict(nticks=4, range=[-5,5],),
                   yaxis = dict(nticks=4, range=[-5,5],),
                    zaxis = dict(nticks=4, range=[-20,20],),),
    title_text='3D subplots with different colorscales'
)


fig.update_layout(  #scene1_aspectmode='auto',
                   xaxis = dict(nticks=4, range=[-5,5],),
                   yaxis = dict(nticks=4, range=[-5,5],),
                   scene2 = dict(
                    zaxis = dict(nticks=4, range=[-20,20],),),
    title_text='3D subplots with different colorscales'
)

fig.show()

 
