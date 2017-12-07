from subcontrol import SubControl
from tkinter import messagebox
from graph import Canvas


class MixControl(SubControl):
    def inits(self):
        self.master.title = "Mixing Control"
        self.target_var.set("Target RPM: 100")
        self.current_var.set("Current RPM: Unknown")

        Canvas(self.graph, "logs/mix.log", "Time/min", "RPM")

    def capture(self):
        try:
            temp = int(self.entry.get())
            if not (500 <= temp and temp <= 1500):
                raise ValueError
            self.target_var.set("Target RPM: " + str(temp))
            self.ser.write(str(temp))
        except ValueError:
            messagebox.showerror("Error", "Target RPM can only be an integer between 500 and 1500")
            pass
