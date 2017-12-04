from tkinter import *
from tkinter import ttk


class HeatControl:
    def __init__(self, root):
        self.master = Toplevel(root)
        self.master.title = "Heating Control"
        self.master.geometry("600x500")
        # self.target_v = StringVar()
        # self.target_v.set(str(target_tp))
        target_tp.set(30)

        self.graph = ttk.Frame(self.master, height=400, width=550, relief=SUNKEN)
        self.graph.grid()
        self.text_display = ttk.Frame(self.master, height=100, width=600)
        self.text_display.grid()

        self.entry = ttk.Entry(self.text_display, width=100)

        Label(self.text_display, textvariable=target_tp).grid()


    def capture(self):
        try:
            temp = float(self.entry.get())
            if not (25 <= temp and temp <= 35):
                raise ValueError
            target_tp.set(temp)

        except ValueError:
            # display error message
            pass
