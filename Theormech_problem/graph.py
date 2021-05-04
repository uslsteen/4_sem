import plotly.graph_objects as go
from plotly.subplots import make_subplots

import numpy as np

# Initialize figure with 4 3D subplots


def subplots(init_vals):

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






def line_by_line(init_vals):

    u=np.linspace(-10, 10, 250)
    v=np.linspace(-10, 10, 250)
    u,v=np.meshgrid(u,v)
    u=u.flatten()
    v=v.flatten()

    x = u
    y = v
    z = init_vals[0] * np.power(x, init_vals[2]) + init_vals[1] * np.power(y, init_vals[3])

    z1 = -2 * np.power(x, 6) + 4 * np.power(y, 8) - 4 * np.power(y, 6)


    fig = make_subplots(rows=1, cols=2)


    fig = go.Figure()


    fig.add_trace(go.Scatter3d(x = x, y = y, z= z, mode = "lines",
                            marker = dict(color = 'green', size = 10)))

    fig.add_trace(go.Scatter3d(x=x, y=y, z=z1, mode = "lines", 
                            marker = dict(color = 'red', size = 10)))



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

"""

    print(init_vals['Coeff of x'])
    print(init_vals['Coeff of y'])
    print(init_vals['Sqr of x'])
    print(init_vals['Sqr of y'])
    """