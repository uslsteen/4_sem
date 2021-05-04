#!/usr/bin/python3

from tkinter import Tk, RIGHT, BOTH, RAISED, END
from tkinter.ttk import Frame, Button, Style, Label, Entry

root = Tk()
root.title('Анализ функции Ляпунова')
root.geometry("800x600")
frame = Frame(root)

""" creating conts """ 

entries_info = {}
entries = {}
init_val = {}


def create_entry(info):

    entry_info = Label(root, text = info, font = ("Arial", 14))
    entries[info] = Entry(root)
    entries[info].insert(END, 0)

    entry_info.grid(column = 0, row = len(entries) - 1)
    entries[info].grid(column = 1, row = len(entries) - 1)


def data_process():

    accept_button = Button(root, text="Старт", command=get_data())
    accept_button.grid(column = 1, row = len(entries))

    print(init_val)


def get_data():

    i = 0

    for info in entries.keys():
        info_str = entries[info].get()

        if len(info_str) == 0:
            print("you should fill all theese gaps")

        val = float(info_str)
        init_val[i] = val
        i = i + 1