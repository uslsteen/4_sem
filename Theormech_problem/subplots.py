#!/usr/bin/python3

import plotly.graph_objects as go
from plotly.subplots import make_subplots

import numpy as np

# Initialize figure with 4 3D subplots
fig = make_subplots(
    rows=2, cols=2,
    specs=[[{'type': 'surface'}, {'type': 'surface'}],
           [{'type': 'surface'}, {'type': 'surface'}]])


x=np.linspace(-50, 50, 100)
y=np.linspace(-50, 50, 100)


xGrid, yGrid = np.meshgrid(y, x)


z = -2 * (xGrid ** 6) + 4 * (yGrid ** 8) - 4 * (yGrid ** 6)


fig.add_trace(
    go.Surface(x=x, y=y, z=z, colorscale='phase', showscale=False),
    row=1, col=1)


z1 = xGrid ** 2 + yGrid ** 4

# adding surfaces to subplots.



fig.add_trace(
    go.Surface(x=x, y=y, z=z1, colorscale='turbo', showscale=False),
    row=1, col=2)



fig.update_layout(    
                    scene1 = dict(
                    xaxis = dict(nticks=4, range=[-25,25],),
                    yaxis = dict(nticks=4, range=[-25,25],),
                    zaxis = dict(nticks=4, range=[-20,20],),),
    title_text='3D subplots with different colorscales',
    height=2000,
    width=2000
)




fig.update_layout(   
                    scene2 = dict(
                    xaxis = dict(nticks=4, range=[-2,2.5],),
                    yaxis = dict(nticks=4, range=[-2,2.5],),
                    zaxis = dict(nticks=4, range=[-5,25],),),
    title_text='3D subplots with different colorscales',

)


fig.show()