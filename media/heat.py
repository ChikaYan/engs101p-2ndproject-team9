from tkinter import *
from tkinter import ttk


class HeatControl:
    def __init__(self, root):
        self.master = Toplevel(root)
        self.master.title = "Heating Control"
        self.master.geometry("600x500")
