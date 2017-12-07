import matplotlib

matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
import matplotlib.animation as animation
from matplotlib.figure import Figure
import tkinter as Tk
import time


class Canvas:
    def __init__(self, root):
        figure = Figure(figsize=(5, 4), dpi=100)

        self.graph = figure.add_subplot(111)
        self.graph.set_title('Tk embedding')

        # a tk.DrawingArea
        self.master = FigureCanvasTkAgg(figure, master=root)
        self.ani = animation.FuncAnimation(figure, self.animate, interval=10)
        # self.master.show()
        self.master.get_tk_widget().pack(side=Tk.TOP, fill=Tk.BOTH, expand=1)

        # toolbar
        self.toolbar = NavigationToolbar2TkAgg(self.master, root)
        self.toolbar.update()
        self.master._tkcanvas.pack(side=Tk.TOP, fill=Tk.BOTH, expand=1)

    def animate(self, i):
        pull_data = open("test_data.txt", "r").read()  # read data from file - replace with rpm data
        dataArray = pull_data.split('\n')
        xar = [1, 2, 3, 4, 5, 6, 7, 8, 9]  # should store time - interval of a minute
        yar = [1, 2, 3, 4, 5, 6, 7, 8, 9]
        # append the y's to the graph
        # issue : if there are a bunch of y values in the list need to make sure x values are also generated
        # for eachLine in dataArray:
        #     if len(eachLine) > 1:
        #         y = eachLine
        #         yar.append(int(y))
        self.graph.clear()
        self.graph.plot(xar, yar)
        self.graph.set_xlabel('X axis label')
        self.graph.set_ylabel('Y label')

# If you put root.destroy() here, it will cause an error if
# the window is closed with the window manager.
