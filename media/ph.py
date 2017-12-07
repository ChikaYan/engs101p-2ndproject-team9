from subcontrol import SubControl
from graph import Canvas


class PhControl(SubControl):
    def inits(self):
        self.master.title = "Ph Control"
        self.target_var.set("Target Ph: 5")
        self.current_var.set("Current Ph: Unknown")
        file = None  # open file here
        Canvas(self.graph, file, "Time/min", "pH")
