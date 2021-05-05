import gui
import subplots as splts
import graph as grph
import math

from tkinter import Tk, RIGHT, BOTH, RAISED
from tkinter.ttk import Frame, Button, Style


def main():

    gui.create_interface()

    gui.data_process()
    
    ##accept_button = Button(gui.root, text="Старт", command=gui.get_data)
    ##accept_button.grid(column = 1, row = len(gui.entries))

    gui.root.mainloop()



    grph.line_by_line(gui.func_vals, gui.system_eqs)

    ##print(gui.init_val)


if __name__ == '__main__':
    main()