
import time

from maze_solver import MazeSolver
from maze_annotator import MazeAnnotator
from rover_controller import RoverController


class Model:
    def __init__(self) -> None:
        self.mazeSolver = MazeSolver()
        self.roverController = RoverController()

    def connectToRover(self):
        self.roverController.connectToRover()

    def disconnectFromRover(self):
        self.roverController.disconnectFromRover()

    def visualize(self, mazeImagePath: str, algorithm: str) -> None:
        self.mazeSolver.setMazeImage(mazeImagePath)

        height, width = self.mazeSolver.binaryImage.shape
        verticalCells = height // self.mazeSolver.CELL_SIZE
        horizontalCells = width // self.mazeSolver.CELL_SIZE
        self.mazeSolver.setStart((0, 0))
        self.mazeSolver.setEnd((horizontalCells - 1, verticalCells - 1))

        annotator = MazeAnnotator(
            self.mazeSolver.graph,
            self.mazeSolver.start,
            self.mazeSolver.end,
            self.mazeSolver.binaryImage.shape
        )
        self.mazeSolver.setAnnotator(annotator)
        self.mazeSolver.solveWithAlgorithm(algorithm, animate=True)

    def runRoverToDestination(self, mazePath: str, algorithm: str) -> None:
        self.mazeSolver.setMazeImage(mazePath)

        height, width = self.mazeSolver.binaryImage.shape
        verticalCells = height // self.mazeSolver.CELL_SIZE
        horizontalCells = width // self.mazeSolver.CELL_SIZE
        self.mazeSolver.setStart((0, 0))
        self.mazeSolver.setEnd((horizontalCells - 1, verticalCells - 1))

        path = self.mazeSolver.solveWithAlgorithm(algorithm, animate=False)

        if self.roverController.runRover(path):
            print("Rover reached destination")
