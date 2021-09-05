#!/usr/bin/python3

from tkinter import Tk, RIGHT, BOTH, RAISED, END, BOTTOM, IntVar
from tkinter.ttk import Frame, Button, Style, Label, Entry, Scale

import graph as grph


class FuncAnalyzer():

    def __init__(self):

        self.root = Tk()

        self.root.title("Анализ функции Ляпунова")
        self.root.geometry("400x300")

        self.frame = Frame(self.root)

        self.entries_info = list()

        self.func_map = dict()
        self.system_map = dict()

        self.func_vals = list()
        self.system_eqs = list()

        self.cur_row = 0
        self.x_n_y_scl = IntVar()
        self.z_scl = IntVar()

    def analise(self):

        self.create_interface()
        self.data_process()
        self.root.mainloop()

    def create_entry(self, info, container, default_data=0):

        entry_info = Label(self.root, text=info, font=("Arial", 14))

        container[info] = Entry(self.root)
        container[info].insert(END, default_data)

        entry_info.grid(column=0, row=self.cur_row)
        container[info].grid(column=1, row=self.cur_row)

        self.cur_row += 1

    ##
    def create_scale(self, info, mode, default_val):

        info_label = Label(self.root, text=info, font=("Arial", 14))
        info_label.grid(column=0, row=self.cur_row)

        scale = Scale()

        if (mode == "x_n_y"):
            scale = Scale(self.root, from_=0, to=30, command=self.onScale_x_n_y)
        elif (mode == "z"):
            scale = Scale(self.root, from_=0, to=50, command=self.onScale_z)
        
        scale.grid(column=1, row=self.cur_row)

        scale_label = Label()

        if (mode == "x_n_y"):
            scale_label = Label(self.root, text=0, textvariable=self.x_n_y_scl)
        elif (mode == "z"):
            scale_label = Label(self.root, text=0, textvariable=self.z_scl)
        
        scale_label.grid(column=2, row=self.cur_row)

        self.cur_row += 1

    #
    #
    def onScale_x_n_y(self, val):
        v = int(float(val))
        self.x_n_y_scl.set(v)


    def onScale_z(self, val):
        v = int(float(val))
        self.z_scl.set(v)


    #
    # Creating main user interface fo processing data
    def create_interface(self):

        self.create_entry('Коэфф. при x', self.func_map, 1)
        self.create_entry('Коэфф. при y', self.func_map, 1)
        self.create_entry('Степень при x', self.func_map, 2)
        self.create_entry('Степень при y', self.func_map, 2)

        self.create_entry('dx/dt = ', self.system_map, '2*y ** 3 - x ** 5')
        self.create_entry('dy/dt = ', self.system_map, '-x - y ** 3 + y ** 5')

        self.create_scale("Масштаб по осям x, y:", "x_n_y", 5)
        self.create_scale("Масштаб по оси z:", "z", 5)

    #
    # Function for processing data by user
    def data_process(self):

        accept_button = Button(self.root, text="Старт", command=self.get_data)
        accept_button.grid(column=1, row=self.cur_row)

    #
    # Function for getting data
    def get_data(self):

        for info in self.func_map.keys():
            info_str = self.func_map[info].get()

            if len(info_str) == 0:
                print("you should fill all theese gaps")

            val = float(info_str)
            self.func_vals.append(val)

        for equal in self.system_map.keys():

            eq_str = self.system_map[equal].get()

            if len(eq_str) == 0:
                print("you should fill all theese gaps")

            self.system_eqs.append(eq_str)
        
        limits_tuple = (self.x_n_y_scl, self.z_scl)

        grph.GraphBuilder(self.func_vals, self.system_eqs, limits_tuple)
