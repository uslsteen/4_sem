#!/usr/bin/python3

import plotly.graph_objects as go
from plotly.subplots import make_subplots

import numpy as np
import numexpr as ne

import gui as g

### Initial constants

X_ARRAY_SIZE = 250
Y_ARRAY_SIZE = 250
X_ARRAY_LIM = 10
Y_ARRAY_LIM = 10

X_PLOT_LIM = 5
Y_PLOT_LIM = 5
Z_PLOT_LIM = 20

### Function for creating graph of Lyapunov function 

def line_by_line():

    u=np.linspace(-X_ARRAY_LIM, X_ARRAY_LIM, X_ARRAY_SIZE)
    v=np.linspace(-Y_ARRAY_LIM, Y_ARRAY_LIM, Y_ARRAY_SIZE)
    u,v=np.meshgrid(u,v)
    u=u.flatten()
    v=v.flatten()

    x = u
    y = v

    z = g.func_vals[0] * (x ** g.func_vals[2]) + g.func_vals[1] * (y ** g.func_vals[3])

    z_deriv = (g.func_vals[0] * g.func_vals[2]) * (x ** (g.func_vals[2] - 1)) * ne.evaluate(g.system_eqs[0]) + (g.func_vals[1] * g.func_vals[3]) * (y ** (g.func_vals[3] - 1)) * ne.evaluate(g.system_eqs[1])

    fig = make_subplots(rows=1, cols=2)

    fig = go.Figure()


    fig.add_trace(go.Scatter3d(x = x, y = y, z= z, mode = "lines",
                            marker = dict(color = 'green', size = 10)))

    fig.add_trace(go.Scatter3d(x=x, y=y, z = z_deriv, mode = "lines", 
                            marker = dict(color = 'red', size = 10)))

    fig.update_layout(
                    scene1 = dict(
                    xaxis = dict(nticks=4, range=[-X_PLOT_LIM, X_PLOT_LIM],),
                    yaxis = dict(nticks=4, range=[-Y_PLOT_LIM, Y_PLOT_LIM],),
                        zaxis = dict(nticks=4, range=[-Z_PLOT_LIM, Z_PLOT_LIM],),),
        title_text='3D subplots with different colorscales')


    fig.update_layout(
                    xaxis = dict(nticks=4, range=[-X_PLOT_LIM, X_PLOT_LIM],),
                    yaxis = dict(nticks=4, range=[-Y_PLOT_LIM, Y_PLOT_LIM],),
                    scene2 = dict(
                        zaxis = dict(nticks=4, range=[-Z_PLOT_LIM, Z_PLOT_LIM],),),
        title_text='3D subplots with different colorscales')

    fig.show()
