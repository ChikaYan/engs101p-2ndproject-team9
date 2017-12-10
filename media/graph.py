import matplotlib

matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
import matplotlib.animation as animation
from matplotlib.figure import Figure
import tkinter as Tk
import time


class Canvas:
    def __init__(self, root, log_path, ylabel):
        self.log_path, self.ylabel = log_path, ylabel

        figure = Figure(figsize=(5, 4), dpi=100)
        self.graph = figure.add_subplot(111)

        # a tk.DrawingArea
        self.master = FigureCanvasTkAgg(figure, master=root)
        self.ani = animation.FuncAnimation(figure, self.animate, interval=5000)
        self.master.get_tk_widget().pack(side=Tk.TOP, fill=Tk.BOTH, expand=1)

        # toolbar
        self.toolbar = NavigationToolbar2TkAgg(self.master, root)
        self.toolbar.update()
        self.master._tkcanvas.pack(side=Tk.TOP, fill=Tk.BOTH, expand=1)

    def animate(self, i):
        file = open(self.log_path, "r")
        xar = []  # should store time - interval of a minute
        yar = []
        # append the y's to the graph
        # issue : if there are a bunch of y values in the list need to make sure x values are also generated
        for log in file:
            if ":" in log:
                log_ls = log.split(":")
                xar.append(float(log_ls[0]))
                yar.append(float(log_ls[1]))
        self.graph.clear()
        self.graph.plot(xar, yar)
        self.graph.set_xlabel("Time/sec")
        self.graph.set_ylabel(self.ylabel)
        file.close()
