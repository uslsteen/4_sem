import gui
import graph as grph
import math

from tkinter import Tk, RIGHT, BOTH, RAISED
from tkinter.ttk import Frame, Button, Style


def main():

    gui.create_interface()

    gui.data_process()
    
    gui.root.mainloop()


if __name__ == '__main__':
    main()