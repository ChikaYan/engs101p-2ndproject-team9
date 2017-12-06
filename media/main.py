from tkinter import *
from tkinter import ttk
from heat import HeatControl
from ph import PhControl
from mix import MixControl
import serial


class Menu:
    def __init__(self, master):
        self.master = master

        self.ser = None
        self.ser = serial.Serial("COMP4", 9600, timeout=0)
        self.master.after(1000, self.read_serial())

        self.heat_control = HeatControl(self.master, "Heating Control", "Target Temperature: 30.0C",
                                        "Current Temperature: Unknown", True, self.ser)
        self.mix_control = MixControl(self.master, "Mixing Control", "Target RPM: 100", "Current RPM: Unknown", True,
                                      self.ser)
        self.ph_control = PhControl(self.master, "Ph Control", "Target Ph: 5", "Current Ph: Unknown", False, self.ser)
        self.heat_control.hide()
        self.ph_control.hide()
        self.mix_control.hide()

        self.master.title("Bioreactor Controller Team 9")
        self.master.geometry("200x300")
        Label(text="Bioreactor Controller").grid(row=0, column=1, sticky=N)
        Label(text="-- by ENGS101P 2nd Project Team 9").grid(row=1, column=1, sticky=N)
        self.mix_button = ttk.Button(self.master, text="Mixing Control", command=self.mix_control.show)
        self.mix_button.grid(row=2, column=1, sticky=N, padx=2, pady=6)
        self.heat_button = ttk.Button(self.master, text="Heating Control", command=self.heat_control.show)
        self.heat_button.grid(row=3, column=1, sticky=N, padx=2, pady=6)
        self.ph_button = ttk.Button(self.master, text="pH Control", command=self.ph_control.show)
        self.ph_button.grid(row=4, column=1, sticky=N, padx=2, pady=6)
        self.exit_button = ttk.Button(self.master, text="Exit", command=self.master.quit)
        self.exit_button.grid(row=5, column=1, sticky=N, padx=2, pady=20)

    def read_serial(self):  # To write Serial, just use ser.write() as bytes
        ser_input = self.ser.readline()  # reads bytes in
        if ser_input != b"":  # Check it didn't read nothing
            print(ser_input.decode())  # do something with the input here
            s_input = ser_input.decode()
            if s_input.startswith("CRPM"):
                self.mix_control.set_current("Current RPM: " + s_input[4:])
            elif s_input.startswith("CTEM"):
                self.heat_control.set_current("Current Temperature: " + s_input[4:])
            elif s_input.startswith("CUPH"):
                self.ph_control.set_current("Current pH: " + s_input[4:])

        self.master.after(1000, self.read_serial)  # Needed to read from Serial every 1000 ms


def main():
    root = Tk()
    Menu(root)
    root.mainloop()


if __name__ == '__main__':
    main()
