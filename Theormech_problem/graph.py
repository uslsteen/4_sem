#!/usr/bin/python3

import plotly.graph_objects as go
from plotly.subplots import make_subplots

import numpy as np
import numexpr as ne

# Initial constants

X_ARRAY_SIZE = 250
Y_ARRAY_SIZE = 250
X_ARRAY_LIM = 10
Y_ARRAY_LIM = 10

X_PLOT_LIM = 5
Y_PLOT_LIM = 5
Z_PLOT_LIM = 20


class GraphBuilder():

    def __init__(self, func_vals, system_eqs):

        self.func_vals = func_vals
        self.system_eqs = system_eqs

        self.line_by_line()

    #
    #
    #
    def funcs_init(self, x, y):

        z = self.func_vals[0] * (x ** self.func_vals[2]) + \
            self.func_vals[1] * (y ** self.func_vals[3])

        z_deriv = (self.func_vals[0] * self.func_vals[2]) * (x ** (self.func_vals[2] - 1)) * ne.evaluate(self.system_eqs[0]) + \
                  (self.func_vals[1] * self.func_vals[3]) * (y ** (self.func_vals[3] - 1)) * ne.evaluate(self.system_eqs[1])

        return z, z_deriv

    #
    #
    def add_trace_n_upd(self, fig, x, y, z, cur_marker):

        fig.add_trace(go.Scatter3d(
            x=x, y=y, z=z, mode="lines", marker=cur_marker))

        fig.update_layout(
            scene1=dict(
                xaxis=dict(nticks=4, range=[-X_PLOT_LIM, X_PLOT_LIM],),
                yaxis=dict(nticks=4, range=[-Y_PLOT_LIM, Y_PLOT_LIM],),
                zaxis=dict(nticks=4, range=[-Z_PLOT_LIM, Z_PLOT_LIM],),),
            title_text='3D subplots with different colorscales')

    #
    #
    # Function for creating graph of Lyapunov function

    def line_by_line(self):

        u = np.linspace(-X_ARRAY_LIM, X_ARRAY_LIM, X_ARRAY_SIZE)
        v = np.linspace(-Y_ARRAY_LIM, Y_ARRAY_LIM, Y_ARRAY_SIZE)
        u, v = np.meshgrid(u, v)
        u = u.flatten()
        v = v.flatten()

        x = u
        y = v

        z, z_deriv = self.funcs_init(x, y)

        fig = make_subplots(rows=1, cols=2)

        fig = go.Figure()

        self.add_trace_n_upd(fig, x, y, z, dict(color="green", size=10))
        self.add_trace_n_upd(fig, x, y, z_deriv, dict(color="red", size=10))

        fig.show()
