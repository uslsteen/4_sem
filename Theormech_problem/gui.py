#!/usr/bin/python3

from tkinter import Tk, RIGHT, BOTH, RAISED, END
from tkinter.ttk import Frame, Button, Style, Label, Entry

root = Tk()

root.title('Анализ функции Ляпунова')
root.geometry("800x600")

frame = Frame(root)

cur_row = 0


""" creating conts """ 

entries_info = {}

func_map = {}
system_map = {}

func_vals = {}
system_eqs = {}


def create_interface():

    create_entries()
    create_system()

    
def create_system():

    create_entry('dx/dt = ', system_map)
    create_entry('dy/dt = ', system_map)


def create_entries():

    create_entry('Coeff of x', func_map)
    create_entry('Coeff of y', func_map)
    create_entry('Sqr of x', func_map)
    create_entry('Sqr of y', func_map)



def create_entry(info, container):

    entry_info = Label(root, text = info, font = ("Arial", 14))
    
    container[info] = Entry(root)
    container[info].insert(END, 0)

    entry_info.grid(column = 0, row = len(func_map) + len(system_map) - 1)
    container[info].grid(column = 1, row = len(func_map) + len(system_map) - 1)


def data_process():

    accept_button = Button(root, text="Старт", command=get_data)
    accept_button.grid(column = 1, row =len(func_map) + len(system_map) + 1)


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
          

    