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
            if not (100 <= temp and temp <= 300):
                raise ValueError
            self.target_var.set("Target RPM: " + str(temp))
            self.ser.write("TRPM" + str(temp))
        except ValueError:
            messagebox.showerror("Error", "Target RPM can only be an integer between 100 and 300")
            pass
