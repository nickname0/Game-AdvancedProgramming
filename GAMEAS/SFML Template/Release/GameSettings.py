from tkinter import *
from tkinter import messagebox

from tkinter import filedialog
import os

def writeFileScreen():
    file = open('ScreenSize.txt','w')
    file.write(sizeX.get() + " "+ sizeY.get())
    file.close()

def readFileScreen():
    with open("ScreenSize.txt","r") as screen:
        Label(window,text=screen.read(), fg='Green').grid(column = 1, row = 2)

def writeFileKeybinds():
    file = open("KeyBinds.txt", "w")
    file.write(keyL.get() + " " + keyR.get() + " " + keyU.get() + " " + keyD.get())
    file.close()
    
def readFileKeybinds():
    with open("KeyBinds.txt", "r") as screen:
        Label(window,text=screen.read(), fg = 'red').grid(column = 1, row =7)

def writeFileTextures():
    file = open("Textures.txt", "w")
    file.write(tex1.get() + " " + tex2.get() + " " + tex3.get() + " " + tex4.get() + " " + tex5.get())
    file.close()

def readFilesTextures():
    with open("Textures.txt", "r") as screen:
        Label(window,text=screen.read(), fg = 'blue').grid(column= 1, row = 13)

def openfile():
    try:
        os.startfile("Game.exe")
    except Exception as e:
            print (e)

window = Tk()
 
window.title("Settings")
 
window.geometry('500x350')
 
screenLX = Label(window, text="SizeX")
screenLY = Label(window, text = "SizeY")

keyUL = Label(window,text = "Up Key ")
keyDL = Label(window,text = "Down Key ")
keyLL = Label(window, text = "Left Key ")
keyRL = Label(window,text = "Right Key ")

tex1L = Label(window, text = "Player Texture ")
tex2L = Label(window, text = "Not Used Texture ")
tex3L = Label(window, text = "Middle Line Texture ")
tex4L = Label(window, text = "Box Texture")
tex5L = Label(window, text = "Background Texture")

screenLX.grid(column=0, row=0)
screenLY.grid(column=0, row=1)
keyUL.grid(column=0,row =3 )
keyDL.grid(column=0,row =4 )
keyLL.grid(column=0,row =5 )
keyRL.grid(column=0,row =6 )
tex1L.grid(column= 0, row = 8)
tex2L.grid(column= 0, row = 9)
tex3L.grid(column= 0, row = 10)
tex4L.grid(column= 0, row = 11)
tex5L.grid(column= 0, row = 12)


sizeX = Entry(window,width=10)
sizeY = Entry(window, width = 10)
keyU = Entry(window,width = 2)
keyD = Entry(window,width = 2)
keyL = Entry(window,width = 2)
keyR = Entry(window,width = 2)
tex1 = Entry(window,width = 20)
tex2 = Entry(window,width = 20)
tex3 = Entry(window,width = 20)
tex4 = Entry(window,width = 20)
tex5 = Entry(window,width = 20)

sizeX.grid(column=1, row=0)
sizeY.grid(column=1,row=1)
keyU.grid(column = 1,row = 3)
keyD.grid(column = 1,row = 4)
keyL.grid(column = 1,row = 5)
keyR.grid(column = 1,row = 6)
tex1.grid(column= 1, row = 8)
tex2.grid(column= 1, row = 9)
tex3.grid(column= 1, row = 10)
tex4.grid(column= 1, row = 11)
tex5.grid(column= 1, row = 12)
 

buttonSizeW = Button(window)
buttonSizeW.config(text="Set New Value", command=writeFileScreen)
buttonSizeR = Button(window,text = "Click to Read Size", command = readFileScreen)

buttonKeyW = Button(window)
buttonKeyW.config(text = "Set New Keybinds", command = writeFileKeybinds)
buttonKeyR = Button(window,text = "Click to Read KeyBinds", command = readFileKeybinds)

buttonTexW = Button(window)
buttonTexW.config(text = "Set New Textures", command = writeFileTextures)
buttonTexR = Button(window,text = "Click to Read Textures", command = readFilesTextures)

quitButton = Button(window,text = "Quit", command =quit)
playButton = Button(window,text = "Play", command = openfile)
 
buttonSizeW.grid(column=2, row=0)
buttonSizeR.grid(column=2, row=1)

buttonKeyW.grid(column=2, row =4 )
buttonKeyR.grid(column=2, row =6)

buttonTexW.grid ( column = 2, row = 8)
buttonTexR.grid(column = 2, row = 10)

quitButton.grid(column = 1, row = 17)
playButton.grid(column = 1 , row =16)


window.mainloop()
