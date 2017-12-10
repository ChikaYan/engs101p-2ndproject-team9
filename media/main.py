from tkinter import *
from tkinter import ttk
from heat import HeatControl
from ph import PhControl
from mix import MixControl
import datetime
import serial

READ_INTERVAL = 5000  # in milliseconds


class Menu:
    def __init__(self, master):
        self.master = master

        self.ser = None
        # self.ser = serial.Serial("/dev/ttyACM0", 9600, timeout=0)
        # self.master.after(1000, self.read_serial())

        self.heat_control = HeatControl(self.master, True, self.ser)
        self.mix_control = MixControl(self.master, True,self.ser)
        self.ph_control = PhControl(self.master, False, self.ser)
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
        for i in range(3):  # take three readings every time
            ser_input = self.ser.readline()  # reads bytes in
            if ser_input != b"":  # Check it didn't read nothing
                data = float(ser_input.decode())
                file = None
                # distinguish the data from range
                if 500 <= data <= 1500:
                    self.mix_control.set_current("Current RPM: " + str(data))
                    file = open("logs/mix.log", "a")
                elif 25 <= data <= 35:
                    self.heat_control.set_current("Current Temperature: " + str(data))
                    file = open("logs/heat.log", "a")
                elif 0 <= data <= 14:
                    self.ph_control.set_current("Current pH: " + str(data))
                    file = open("logs/ph.log", "a")
                if file:
                    now = datetime.datetime.now()
                    file.write(str(now.minute) + ":" + str(data))
                    file.close()

        self.master.after(READ_INTERVAL, self.read_serial)  # Needed to read from Serial every 1000 ms


def main():
    root = Tk()
    main = Menu(root)
    root.mainloop()


if __name__ == '__main__':
    main()
