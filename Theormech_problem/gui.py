#!/usr/bin/python3



import random
import tkinter as tk


import random
import tkinter as tk

class App(tk.Tk):
    colors = ("red", "yellow", "green", "blue", "orange")

    def __init__(self):
        super().__init__()
        self.title("Удаление элементов холста")

        self.canvas = tk.Canvas(self, bg="blue")
        frame = tk.Frame(self)

        x_entry = tk.Entry(self, width = 10)
        y_entry = tk.Entry(self, width = 10)

        self.geometry("800x600")
        get_data_x = tk.Button(frame, text="Ввести степень x", command = self.get_data(frame, x_entry))
        get_data_y = tk.Button(frame, text="Ввести степень y", command = self.get_data(frame, y_entry))

        self.canvas.pack()
        frame.pack(fill=tk.BOTH)

        x_entry.pack(side = tk.LEFT, expand = True)

        get_data_x.pack(side=tk.LEFT, expand=True, fill=tk.BOTH)
        get_data_y.pack(side=tk.LEFT, expand=True, fill=tk.BOTH)

        self.update()
        self.width = self.canvas.winfo_width()
        self.height = self.canvas.winfo_height()

        self.get_data(frame, x_entry)

        ##self.canvas.bind("<Button-1>", self.on_click)
    def get_data(self, frame, entry):
        data = entry.get()

        label_data = tk.Label(text = data)
        ##self.canvas.create_window(500, 600, label_data)
        label_data.place(x = 100, y = 100)


    def clear_items(self):
        self.canvas.delete(tk.ALL)

if __name__ == "__main__":
    app = App()
    app.mainloop()
    

"""
from tkinter import *
from tkinter.ttk import Frame, Button, Style, Entry, Label
 
 
class Example(Frame, Canvas):

    def __init__(self, parent):
        Frame.__init__(self, parent)
        self.parent = parent
        self.initUI()

 
    def initUI(self):
        self.parent.title("Кнопка выхода из приложения")
        self.style = Style()
        self.style.theme_use("default")

        canvas1 = Canvas(self)
        self.pack(fill=BOTH, expand=1)
        self.init_buttons()
        
    def get_data(self, entry):
        data = entry.get()
        label_check = Label(self, text = data)
        canvas1.create_window(200, 300, window=label_check)

    def init_buttons(self):
        prog_name = Label(self, text = "Программа по анализу функций Ляпунова")
        prog_name.place(x = 300, y = 10)

        quitButton = Button(self, text="Закрыть окно", command=self.quit)
        quitButton.place(x=300, y=400)

        data_name = Label(self, text = "Степень x")
        data_name.place(x = 200, y = 100)

        data = Entry(self, width = 10)
        data.place(x = 200, y = 140)
        
        data_button = Button(self, text = "Get data:", command = self.get_data(data))
        data_button.place(x = 200, y = 300)
    


 
 
def main():
    root = Tk()

    root.geometry("800x600")
    Example(root)
    root.mainloop()

    
if __name__ == '__main__':
    main()



"""


"""
import tkinter as tk

root= tk.Tk()

canvas1 = tk.Canvas(root, width = 400, height = 300)
canvas1.pack()

entry1 = tk.Entry (root) 
canvas1.create_window(200, 140, window=entry1)

def getSquareRoot ():  
    x1 = entry1.get()
    
    label1 = tk.Label(root, text= float(x1)**0.5)
    canvas1.create_window(200, 230, window=label1)
    
button1 = tk.Button(text='Get the Square Root', command=getSquareRoot)
canvas1.create_window(200, 180, window=button1)

root.mainloop()
"""