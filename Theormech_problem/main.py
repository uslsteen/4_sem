import gui
import subplots as splts
import graph as grph

from tkinter import Tk, RIGHT, BOTH, RAISED
from tkinter.ttk import Frame, Button, Style


def main():

    gui.create_entry('Coeff of x')
    gui.create_entry('Coeff of y')
    gui.create_entry('Sqr of x')
    gui.create_entry('Sqr of y')

    gui.data_process()
    
    gui.root.mainloop()


if __name__ == '__main__':
    main()