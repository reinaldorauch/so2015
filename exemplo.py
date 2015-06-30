#!/usr/bin/python

from Tkinter import *

top = Tk()
strVar = StringVar()
inputTxt = StringVar()
label = Label(top, textvariable=strVar, relief=RAISED)
strVar.set("Digite alguma coisa")
etr = Entry(top, textvariable=inputTxt)
label.pack()
etr.pack()
top.mainloop()
