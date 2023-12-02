from tkinter import *


class GUI(Tk):
    def __init__(self):
        super().__init__()
        self.title("GUI")
        self.minsize(500, 400)
        self.maxsize(500, 400)
        self.configure(background="#e6e6e6")

        self.heading = Label(self, text="Welcome to GUI", bg="#e6e6e6",
                             fg="#000000", pady="10", font="Helvetica 20 bold")
        self.heading.place(x=150, y=10)

        self.label1 = Label(self, text="Enter your name", bg="#e6e6e6",
                            fg="#000000", pady="10", font="Helvetica 16 bold")
        self.label1.place(x=10, y=80)

        self.entry1 = Entry(self, width=30)
        self.entry1.place(x=200, y=80)

        self.button1 = Button(self, text="Submit", bg="#000000", fg="#ffffff",
                              pady="10", padx="10", font="Helvetica 16 bold", command=self.submit)
        self.button1.place(x=200, y=120)

        self.label2 = Label(self, text="", bg="#e6e6e6",
                            fg="#000000", pady="10", font="Helvetica 16 bold")
        self.label2.place(x=10, y=200)

    def submit(self):
        self.label2.configure(text="Hello " + self.entry1.get())
