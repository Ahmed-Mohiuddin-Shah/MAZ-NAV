from collections import deque
import json
from typing import Dict, List
import cv2
import numpy as np
import time

from maze_annotator import MazeAnnotator


class AnnotatorNotFound(Exception):
    ...


class MazeSolver:
    CELL_SIZE = 20

    def __init__(self, mazeImagePath: str | None = None):
        self.mazeImagePath = mazeImagePath

        if mazeImagePath:
            self.originalImage = cv2.imread(self.mazeImagePath)
            self.binaryImage = self.readImage()
            self._setDefaults()
            self._createGraph()

        self.annotator = None

    def solveWithDFS(self, animate: bool = False) -> List[tuple]:
        if animate and not self.annotator:
            raise AnnotatorNotFound("Please setup annotator first")

        if animate and self.annotator:
            markedImage = self.annotator.plotPointsOnImage(self.originalImage)
            markedImage = cv2.cvtColor(markedImage, cv2.COLOR_BGR2RGB)

        stack = [(self.start, [self.start])]
        visited = set()

        while stack:
            (vertex, path) = stack.pop()
            if vertex not in visited:
                if animate:
                    prevoius = self.annotator.plotPathOnImage(
                        markedImage, path[:-1], animate=False)
                    self.annotator.plotPathOnImage(
                        prevoius, path[-2:], animate=True)

                if vertex == self.end:
                    return path

                visited.add(vertex)

                for neighbor in self.graph[vertex]:
                    stack.append((neighbor, path + [neighbor]))

    def solveWithAlgorithm(self, algorithm: str, animate: bool = False) -> List[tuple]:
        if algorithm == "DFS":
            return self.solveWithDFS(animate)

        if algorithm == "BFS":
            return self.solveWithBFS(animate)

        raise Exception("Algorithm not found")

        # if algorithm == "A*":
        #     return self.solveWithAStar()

        # if algorithm == "Dijkstra":
        #     return self.solveWithDijkstra()

        # if algorithm == "Greedy":
        #     return self.solveWithGreedy()

        # if algorithm == "IDA*":
        #     return self.solveWithIDAStar()

        # if algorithm == "Bidirectional":
        #     return self.solveWithBidirectional()

    def solveWithBFS(self, animate: bool = False) -> List[tuple]:
        if animate and not self.annotator:
            raise AnnotatorNotFound("Please setup annotator first")

        if animate and self.annotator:
            markedImage = self.annotator.plotPointsOnImage(self.originalImage)
            markedImage = cv2.cvtColor(markedImage, cv2.COLOR_BGR2RGB)

        queue = deque([(self.start, [self.start])])
        visited = set()

        while queue:
            (vertex, path) = queue.popleft()
            if vertex not in visited:
                if animate:
                    prevoius = self.annotator.plotPathOnImage(
                        markedImage, path[:-1], animate=False)
                    self.annotator.plotPathOnImage(
                        prevoius, path[-2:], animate=True)

                if vertex == self.end:
                    return path

                visited.add(vertex)

                for neighbor in self.graph[vertex]:
                    queue.append((neighbor, path + [neighbor]))

    def _setDefaults(self) -> None:
        height, width = self.binaryImage.shape
        verticalCells = height // self.CELL_SIZE
        horizontalCells = width // self.CELL_SIZE

        self._height = height
        self._width = width
        self._verticalCells = verticalCells
        self._horizontalCells = horizontalCells

        self.start = (0, 0)
        self.end = (self._horizontalCells - 1, self._verticalCells - 1)

    def readImage(self) -> cv2.Mat:
        img = cv2.imread(self.mazeImagePath, 0)
        ret, img = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)
        return img

    def _createGraph(self) -> None:
        self.graph: Dict[tuple, set] = {}
        self._createEdges()

    def _processBlock(self, blockIndices: tuple) -> Dict[str, bool]:
        xStart = blockIndices[1] * self.CELL_SIZE
        yStart = blockIndices[0] * self.CELL_SIZE
        xEnd = xStart + self.CELL_SIZE
        yEnd = yStart + self.CELL_SIZE

        block = self.binaryImage[xStart:xEnd, yStart:yEnd]
        block = np.array(block)

        upperEdge = bool(block[0, self.CELL_SIZE // 2])
        lowerEdge = bool(block[self.CELL_SIZE - 1, self.CELL_SIZE // 2])
        leftEdge = bool(block[self.CELL_SIZE // 2, 0])
        rightEdge = bool(block[self.CELL_SIZE // 2, self.CELL_SIZE - 1])

        return {
            "upperEdge": upperEdge,
            "lowerEdge": lowerEdge,
            "leftEdge": leftEdge,
            "rightEdge": rightEdge
        }

    def _createEdges(self) -> None:
        for i in range(self._verticalCells):
            for j in range(self._horizontalCells):
                """j is considered as x axis and i is y axis"""

                isEdgePossible = self._processBlock((j, i))
                self.graph[(j, i)] = set()

                if isEdgePossible["upperEdge"]:
                    self.graph[(j, i)].add((j, i - 1))

                if isEdgePossible["lowerEdge"]:
                    self.graph[(j, i)].add((j, i + 1))

                if isEdgePossible['leftEdge']:
                    self.graph[(j, i)].add((j - 1, i))

                if isEdgePossible['rightEdge']:
                    self.graph[(j, i)].add((j + 1, i))

    def setStart(self, point: tuple) -> None:
        self.start = point

    def setEnd(self, point: tuple) -> None:
        self.end = point

    def setAnnotator(self, annotator: MazeAnnotator) -> None:
        self.annotator = annotator

    def setMazeImage(self, mazeImagePath: str) -> None:
        self.mazeImagePath = mazeImagePath
        self.originalImage = cv2.imread(self.mazeImagePath)
        self.binaryImage = self.readImage()
        self._setDefaults()
        self._createGraph()
