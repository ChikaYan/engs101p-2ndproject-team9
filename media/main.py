from tkinter import *
from tkinter import ttk
from heat import HeatControl


class Menu:
    def __init__(self, root):
        self.master = root
        self.master.title("Bioreactor Controller Team 9")
        self.master.geometry("200x300")

        self.heat_control, self.mix_control, self.ph_control = None, None, None

        Label(text="Bioreactor Controller", padx=1, pady=1).grid(row=0, column=1, sticky=N)
        Label(text="-- by ENGS101P 2nd Project Team 9", padx=1, pady=1).grid(row=1, column=1, sticky=N)

        self.mix_button = ttk.Button(self.master, text="Mixing Control", command=self.open_mix)
        self.mix_button.grid(row=2, column=1, sticky=N, padx=2, pady=6)
        self.heat_button = ttk.Button(self.master, text="Heating Control", command=self.open_heat)
        self.heat_button.grid(row=3, column=1, sticky=N, padx=2, pady=6)
        self.ph_button = ttk.Button(self.master, text="pH Control", command=self.open_ph)
        self.ph_button.grid(row=4, column=1, sticky=N, padx=2, pady=6)

        self.exit_button = ttk.Button(self.master, text="Exit", command=self.master.quit)
        self.exit_button.grid(row=5, column=1, sticky=N, padx=2, pady=20)
        # set_spacing(self.master, 6, 40)

    def open_mix(self):
        pass

    def open_heat(self):
        if self.heat_control is None:
            self.heat_control = HeatControl(self.master)

    def open_ph(self):
        pass


def set_spacing(root, xmin, ymin):
    y, x = root.grid_size()
    for col in range(y + 1):
        root.grid_columnconfigure(col, minsize=xmin)
    for row in range(x + 1):
        root.grid_rowconfigure(row, minsize=ymin)


def main():
    root = Tk()
    menu = Menu(root)
    root.mainloop()


if __name__ == '__main__':
    main()
