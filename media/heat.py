from subcontrol import SubControl
from tkinter import messagebox
from graph import Canvas


class HeatControl(SubControl):
    def inits(self):
        self.master.title = "Heating Control"
        self.target_var.set("Target Temperature: 30.0C")
        self.current_var.set("Current Temperature: Unknown")

        Canvas(self.graph, "logs/heat.log", "Time/min", "Temperature/C")

    def capture(self):
        try:
            temp = float(self.entry.get())
            if not (25 <= temp and temp <= 35):
                raise ValueError
            self.target_var.set("Target Temperature: " + str(temp) + "C")
            self.ser.write("TTEM" + str(temp))
        except ValueError:
            messagebox.showerror("Error", "Target temperature can only be a number between 25 and 35")
