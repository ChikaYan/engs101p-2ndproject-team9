from subcontrol import SubControl


class HeatControl(SubControl):
    def capture(self):
        try:
            temp = float(self.entry.get())
            if not (25 <= temp and temp <= 35):
                raise ValueError
            self.target_var.set("Target Temperature: " + str(temp)+"C")
        except ValueError:
            # display error message
            pass
