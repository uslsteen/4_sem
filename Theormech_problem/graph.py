import plotly.graph_objects as go
from plotly.subplots import make_subplots

import numpy as np
import numexpr as ne

import gui as g

## Initial constants

X_MAX = 50
Y_MAX = 50
Z_MAX = 20

## keyboard interrupt
## fix tails of graph

# Initialize figure with 4 3D subplots


## Functon for creating two graph in different plots

def subplots(func_vals):

    fig = make_subplots(
        rows=2, cols=2,
        specs=[[{'type': 'surface'}, {'type': 'surface'}],
            [{'type': 'surface'}, {'type': 'surface'}]])


    x=np.linspace(-X_MAX, X_MAX, 100)
    y=np.linspace(-Y_MAX, Y_MAX, 100)



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
                        xaxis = dict(nticks=4, range=[-X_MAX/2, X_MAX/2],),
                        yaxis = dict(nticks=4, range=[-Y_MAX/2,Y_MAX/2],),
                        zaxis = dict(nticks=4, range=[-Z_MAX, Z_MAX],),),
        title_text='3D subplots with different colorscales',
        height=2000,
        width=2000
    )




    fig.update_layout(   
                        scene2 = dict(
                        xaxis = dict(nticks=4, range=[-2.5,2.5],),
                        yaxis = dict(nticks=4, range=[-2.5,2.5],),
                        zaxis = dict(nticks=4, range=[-25,25],),),
        title_text='3D subplots with different colorscales',

    )

    fig.show()



## Initial contants

X_MAX = 10
Y_MAX = 10
Z_MAX = 20
FREQ = 250

## Function for creating two graph in one plot

def line_by_line():

    u=np.linspace(-X_MAX, X_MAX, FREQ)
    v=np.linspace(-Y_MAX, Y_MAX, FREQ)
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



    fig.update_layout(  #scene1_aspectmode='auto',
                    scene1 = dict(
                    xaxis = dict(nticks=4, range=[-X_MAX/2, X_MAX/2],),
                    yaxis = dict(nticks=4, range=[-Y_MAX/2, Y_MAX/2],),
                        zaxis = dict(nticks=4, range=[-Z_MAX, Z_MAX],),),
        title_text='3D subplots with different colorscales'
    )


    fig.update_layout(  #scene1_aspectmode='auto',
                    xaxis = dict(nticks=4, range=[-X_MAX/2, X_MAX/2],),
                    yaxis = dict(nticks=4, range=[-Y_MAX/2, Y_MAX/2],),
                    scene2 = dict(
                        zaxis = dict(nticks=4, range=[-Z_MAX ,Z_MAX],),),
        title_text='3D subplots with different colorscales'
    )

    fig.show()
