from subcontrol import SubControl


class MixControl(SubControl):
    def capture(self):
        try:
            temp = int(self.entry.get())
            if not (100 <= temp and temp <= 300):
                raise ValueError
            self.target_var.set("Target RPM: " + str(temp))
            self.ser.write("TRPM"+str(temp))
        except ValueError:
            # display error message
            pass
