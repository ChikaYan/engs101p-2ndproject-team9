from tkinter import *
from tkinter import ttk


class SubControl:
    def __init__(self, root, title, target_init, current_init):
        self.master = Toplevel(root)
        self.master.title = title
        self.master.geometry("600x500")

        self.master.protocol("WM_DELETE_WINDOW", self.hide)  # overide the "X" button method to hide the windows instead

        self.target_var, self.current_var = StringVar(), StringVar()
        self.target_var.set(target_init)
        self.current_var.set(current_init)

        self.graph = ttk.Frame(self.master, height=400, width=550, relief=SUNKEN)
        self.graph.grid(padx=25)
        self.text_display = ttk.Frame(self.master, height=100, width=600)
        self.text_display.grid()

        self.entry = ttk.Entry(self.text_display, width=100)

        Label(self.text_display, textvariable=self.target_var).grid(row=0, column=0,padx=25)
        Label(self.text_display, textvariable=self.current_var).grid(row=0, column=1, padx=25)

    def hide(self):
        self.master.withdraw()

    def show(self):
        self.master.iconify()

    def capture(self):
        "should be overriden"
        try:
            temp = float(self.entry.get())
            if not (25 <= temp and temp <= 35):
                raise ValueError
            self.target_var.set("Target Temperature: " + str(temp))
        except ValueError:
            # display error message
            pass
