from tkinter import *
from tkinter import ttk
import subcontrol
from heat import HeatControl
from ph import PhControl
from mix import MixControl


import serial
ser = serial.Serial("/dev/ttyACM0", 9600, timeout=0)
root = Tk()

class Menu:
    def __init__(self, root):
        self.master = root
        self.master.title("Bioreactor Controller Team 9")
        self.master.geometry("200x300")

        Label(text="Bioreactor Controller").grid(row=0, column=1, sticky=N)
        Label(text="-- by ENGS101P 2nd Project Team 9").grid(row=1, column=1, sticky=N)

        self.mix_button = ttk.Button(self.master, text="Mixing Control", command=self.open_mix)
        self.mix_button.grid(row=2, column=1, sticky=N, padx=2, pady=6)
        self.heat_button = ttk.Button(self.master, text="Heating Control", command=self.open_heat)
        self.heat_button.grid(row=3, column=1, sticky=N, padx=2, pady=6)
        self.ph_button = ttk.Button(self.master, text="pH Control", command=self.open_ph)
        self.ph_button.grid(row=4, column=1, sticky=N, padx=2, pady=6)

        self.exit_button = ttk.Button(self.master, text="Exit", command=self.master.quit)
        self.exit_button.grid(row=5, column=1, sticky=N, padx=2, pady=20)

        self.heat_control = HeatControl(self.master, "Heating Control", "Target Temperature: 30.0C",
                                        "Current Temperature: Unknown", True)
        self.mix_control = MixControl(self.master, "Mixing Control", "Target RPM: 100", "Current RPM: Unknown", True)
        self.ph_control = PhControl(self.master, "Ph Control", "Target Ph: 5", "Current Ph: Unknown", False)

        self.heat_control.hide()
        self.ph_control.hide()
        self.mix_control.hide()

    def open_mix(self):
        self.mix_control.show()

    def open_heat(self):
        self.heat_control.show()

    def open_ph(self):
        self.ph_control.show()

def read_serial(): # To write Serial, just use ser.write() as bytes
    ser_input = ser.readline() # reads bytes in
    if(ser_input != b""): # Check it didn't read nothing
        print(ser_input.decode()) # do something with the input here
    root.after(1000, read_serial) # Needed to read from Serial every 1000 ms

def main():
    menu = Menu(root)
    root.after(1000, read_serial)
    root.mainloop()

if __name__ == '__main__':
    main()
