import threading
import time
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from PIL import Image, ImageTk

from model import Model


class GUI(Tk):
    def __init__(self, model: Model = None) -> None:
        super().__init__()
        self.waitForRoverToCompleteThread = None
        self.model = model

        self.startSplashScreen()

        # TODO: Create a screen for unable to connect to the rover

    def startSplashScreen(self) -> None:
        self._truncateScreen()

        self.title("Maze Solver")
        self.geometry("800x600+300+300")
        self.minsize(800, 600)

        self.mainFrame = ttk.Frame(
            self, padding="8 8 8 8", width=self.winfo_width(), height=self.winfo_height())
        self.mainFrame.grid(column=0, row=0, sticky=(N, W, E, S))

        title = ttk.Label(
            self,
            text="MAZ-NAV",
            font=("Helvetica", "48", "bold"),
        )
        subtitle = ttk.Label(
            self,
            text="An interface for selecting a maze and solving it with a rover",
            font=("Helvetica", "18"),
            justify=CENTER,
            wraplength=700,
        )

        title.place(relx=0.5, rely=0.35, anchor=CENTER)
        subtitle.place(relx=0.5, rely=0.48, anchor=CENTER)

        self.loadingText = ttk.Label(
            self,
            text="Trying to connect to the rover...",
            font=("Helvetica", "18"),
        )
        self.loadingText.place(relx=0.5, rely=0.55, anchor=CENTER)

        self.loadingBar = ttk.Progressbar(
            self,
            value=0,
            orient=HORIZONTAL,
            length=200,
            mode="indeterminate",
        )
        self.loadingBar.place(relx=0.5, rely=0.60, anchor=CENTER)

        self.roverThread = threading.Thread(
            target=self.model.connectToRover
        )
        self.roverThread.start()

        self.after(50, self.updateLoadingBar)

    def updateLoadingBar(self) -> None:
        if self.roverThread.is_alive():
            self.loadingBar.step(5)
            self.after(50, self.updateLoadingBar)
            return

        self.loadingBar.stop()
        self.loadingBar.destroy()

        self.loadingText.config(text="Connected to the rover!")

        self.after(500, self.startSelectMazeScreen)

    def _truncateScreen(self) -> None:
        for child in self.winfo_children():
            child.destroy()

    def startSelectMazeScreen(self) -> None:
        self._truncateScreen()

        mainFrame = ttk.Frame(
            self, padding="8 8 8 8", width=self.winfo_width(), height=self.winfo_height())
        mainFrame.pack(expand=True)

        title = ttk.Label(
            mainFrame,
            text="Select a maze to solve",
            font=("Helvetica", "32", "bold"),
        )
        title.pack(expand=True, pady=20)

        imagePaths = [
            "./mazes/maze00.jpg",
            "./mazes/maze01.jpg",
            "./mazes/maze02.jpg",
        ]

        images = []
        for path in imagePaths:
            image = Image.open(path)
            image = image.resize((200, 200))
            image = ImageTk.PhotoImage(image)
            images.append(image)

        buttonsFrame = ttk.Frame(mainFrame)
        buttonsFrame.pack(expand=True)

        imageButtons = []
        button = ttk.Button(
            buttonsFrame,
            image=images[0],
            command=lambda: self.startChooseAlgorithmScreen(
                imagePaths[0]),
        )
        button.image = images[0]
        imageButtons.append(button)

        button = ttk.Button(
            buttonsFrame,
            image=images[1],
            command=lambda: self.startChooseAlgorithmScreen(
                imagePaths[1]),
        )
        button.image = images[1]
        imageButtons.append(button)

        button = ttk.Button(
            buttonsFrame,
            image=images[2],
            command=lambda: self.startChooseAlgorithmScreen(
                imagePaths[2]),
        )
        button.image = images[2]
        imageButtons.append(button)

        for button in imageButtons:
            button.pack(side=LEFT, padx=10)

    def startChooseAlgorithmScreen(self, mazeImagePath: str) -> None:
        self._truncateScreen()

        print(mazeImagePath)

        mainFrame = ttk.Frame(
            self, padding="8 8 8 8", width=self.winfo_width(), height=self.winfo_height())
        mainFrame.pack(expand=True)

        title = ttk.Label(
            mainFrame,
            text="Select algorithm",
            font=("Helvetica", "32", "bold"),
        )
        title.pack(expand=True, pady=20)

        algorithms = [
            "DFS",
            "BFS",
            "A*",
            "Dijkstra"
        ]

        algorithmsRadioButtonsFrame = ttk.Frame(mainFrame)
        algorithmsRadioButtonsFrame.pack(expand=True)

        style = ttk.Style()
        style.configure(
            'Accent.TButton',
            font=('Helvetica', 14, 'normal'),
        )
        style.configure(
            'Accent.TRadiobutton',
            font=('Helvetica', 14, 'normal'),
        )

        self.algorithm = StringVar()

        algorithmButtons = []
        for algorithm in algorithms:
            button = ttk.Radiobutton(
                algorithmsRadioButtonsFrame,
                text=algorithm,
                value=algorithm,
                variable=self.algorithm,
                style="Accent.TRadiobutton",
            )
            algorithmButtons.append(button)

        for button in algorithmButtons:
            button.pack(side=LEFT, expand=True, padx=10)

        otherButtonsFrame = ttk.Frame(mainFrame)
        otherButtonsFrame.pack(expand=True)

        backButton = ttk.Button(
            otherButtonsFrame,
            text="Back",
            command=self.startSelectMazeScreen,
        )
        backButton.config(style="Accent.TButton")
        backButton.pack(side=LEFT, expand=True, pady=10)

        visualizeButton = ttk.Button(
            otherButtonsFrame,
            text="Visualize",
            command=lambda: self.visualize(
                mazeImagePath, self.algorithm.get()
            ),
        )
        visualizeButton.config(style="Accent.TButton")
        visualizeButton.pack(side=LEFT, expand=True, pady=10)

        startRace = ttk.Button(
            otherButtonsFrame,
            text="Start Race",
            command=lambda: self.setupRaceScreen(
                mazeImagePath, self.algorithm.get()
            ),
        )
        startRace.config(style="Accent.TButton")
        startRace.pack(side=LEFT, expand=True, pady=10)

    def visualize(self, mazeImagePath: int, algorithm: str) -> None:
        if len(algorithm) == 0:
            messagebox.showerror("Please select an algorithm!")
            return

        self.model.visualize(mazeImagePath, algorithm)

    def setupRaceScreen(self, mazeImagePath: str, algorithm: str) -> None:
        if len(algorithm) == 0:
            messagebox.showerror("Error", "Please select an algorithm")
            return

        self._truncateScreen()

        mainFrame = ttk.Frame(
            self, padding="8 8 8 8", width=self.winfo_width(), height=self.winfo_height())
        mainFrame.pack(expand=True)

        title = ttk.Label(
            mainFrame,
            text="Place rover at the start",
            font=("Helvetica", "32", "normal"),
        )
        title.pack(expand=True, pady=20)

        buttonsFrame = ttk.Frame(mainFrame)
        buttonsFrame.pack(expand=True)

        style = ttk.Style()
        style.configure(
            'Accent.TButton',
            font=('Helvetica', 14, 'normal'),
        )

        backButton = ttk.Button(
            buttonsFrame,
            text="Back",
            style="Accent.TButton",
            command=lambda: self.startChooseAlgorithmScreen(mazeImagePath),
        )
        backButton.pack(side=LEFT, expand=True, padx=10)

        readyButton = ttk.Button(
            buttonsFrame,
            text="Start",
            style="Accent.TButton",
            command=lambda: self.setupWaitForCompletionScreen(
                mazeImagePath, algorithm),
        )
        readyButton.pack(side=LEFT, expand=True, padx=10)

    def setupWaitForCompletionScreen(self, mazeImagePath: str, algorithm: str) -> None:
        self._truncateScreen()

        mainFrame = ttk.Frame(
            self, padding="8 8 8 8", width=self.winfo_width(), height=self.winfo_height())
        mainFrame.pack(expand=True)

        title = ttk.Label(
            mainFrame,
            text="Waiting for rover to complete the maze...",
            font=("Helvetica", "32", "normal"),
            justify=CENTER,
            wraplength=500
        )
        title.pack(expand=True, pady=20)

        self.loadingBar = ttk.Progressbar(
            mainFrame,
            value=0,
            orient=HORIZONTAL,
            length=200,
            mode="indeterminate",
        )

        self.loadingBar.pack(expand=True, pady=20)
        self.loadingBar.start(10)

        if self.waitForRoverToCompleteThread is None:
            self.waitForRoverToCompleteThread = threading.Thread(
                target=self.model.runRoverToDestination(
                    mazeImagePath,
                    algorithm
                )
            )
            self.waitForRoverToCompleteThread.start()

        if self.waitForRoverToCompleteThread.is_alive():
            self.after(
                100, self.setupWaitForCompletionScreen,
                mazeImagePath, algorithm
            )
        else:
            self.setupCompletedScreen()

    def setupCompletedScreen(self) -> None:
        self._truncateScreen()

        mainFrame = ttk.Frame(
            self, padding="8 8 8 8", width=self.winfo_width(), height=self.winfo_height())
        mainFrame.pack(expand=True)

        title = ttk.Label(
            mainFrame,
            text="Rover completed the maze!",
            font=("Helvetica", "32", "normal"),
            justify=CENTER,
            wraplength=600
        )
        title.pack(expand=True, pady=20)

        style = ttk.Style()
        style.configure(
            'Accent.TButton',
            font=('Helvetica', 14, 'normal'),
        )

        backButton = ttk.Button(
            mainFrame,
            text="Back",
            style="Accent.TButton",
            command=self.startSelectMazeScreen,
        )
        backButton.pack(expand=True, pady=20)


if __name__ == "__main__":
    gui = GUI(Model())
    gui.mainloop()

    exit()
