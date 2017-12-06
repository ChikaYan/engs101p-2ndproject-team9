import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
import matplotlib.animation as animation
from matplotlib.figure import Figure
import tkinter as Tk
import time

root = Tk.Tk()
root.title("Graph Title")

figure = Figure(figsize=(5, 4), dpi=100)

graph = figure.add_subplot(111)
graph.set_title('Tk embedding')

def animate(i):
    pullData = open("test_data.txt","r").read()#read data from file - replace with rpm data
    dataArray = pullData.split('\n')
    xar = []#should store time - interval of a minute
    yar = []
    #append the y's to the graph
    #issue : if there are a bunch of y values in the list need to make sure x values are also generated
    for eachLine in dataArray:
        if len(eachLine)>1:
            y = eachLine()
            yar.append(int(y))
    graph.clear()
    graph.plot(xar, yar)
    graph.set_xlabel('X axis label')
    graph.set_ylabel('Y label')


# a tk.DrawingArea
canvas = FigureCanvasTkAgg(figure, master=root)
ani = animation.FuncAnimation(figure, animate, interval=60000)
canvas.show()
canvas.get_tk_widget().pack(side=Tk.TOP, fill=Tk.BOTH, expand=1)


#delete this if you dont the toolbar, looks pretty snazzy though
toolbar = NavigationToolbar2TkAgg(canvas, root)
toolbar.update()
canvas._tkcanvas.pack(side=Tk.TOP, fill=Tk.BOTH, expand=1)

Tk.mainloop()
# If you put root.destroy() here, it will cause an error if
# the window is closed with the window manager.