#!/usr/bin/python3

from tkinter import Tk, RIGHT, BOTH, RAISED, END, BOTTOM
from tkinter.ttk import Frame, Button, Style, Label, Entry

import graph as grph

root = Tk()

root.title('Анализ функции Ляпунова')
root.geometry("300x200")

frame = Frame(root)


### containter creating 

entries_info = {}

func_map = {}
system_map = {}

func_vals = {}
system_eqs = {}

### Creating main user interface fo processing data

def create_interface():

    create_entry('Коэфф. при x', func_map, 1)
    create_entry('Коэфф. при y', func_map, 1)
    create_entry('Степень при x', func_map, 2)
    create_entry('Степень при y', func_map, 2)

    create_entry('dx/dt = ', system_map, '2*y ** 3 - x ** 5')
    create_entry('dy/dt = ', system_map, '-x - y ** 3 + y ** 5')

    
def create_entry(info, container, default_data = 0):

    entry_info = Label(root, text = info, font = ("Arial", 14))
    
    container[info] = Entry(root)
    container[info].insert(END, default_data)

    cur_row = len(func_map) + len(system_map)

    entry_info.grid(column = 0, row = cur_row - 1)
    container[info].grid(column = 1, row = cur_row - 1)


### Function for processing data by user

def data_process():

    accept_button = Button(root, text="Старт", command=get_data)
    accept_button.grid(column = 1, row =len(func_map) + len(system_map) + 1)

### Function for getting data 

def get_data():

    i = 0

    for info in func_map.keys():
        info_str = func_map[info].get()

        if len(info_str) == 0:
            print("you should fill all theese gaps")

        val = float(info_str)
        func_vals[i] = val
        i = i + 1

    i = 0

    for equal in system_map.keys():
    
        eq_str = system_map[equal].get()

        if len(eq_str) == 0:
            print("you should fill all theese gaps")

        system_eqs[i] = eq_str
        i = i + 1

    grph.line_by_line()
          

    