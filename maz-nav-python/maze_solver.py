import heapq
from queue import Queue
from typing import Any, Dict, List, Optional, Tuple
import cv2
import numpy as np

from maze_annotator import MazeAnnotator


class AnnotatorNotFound(Exception):
    ...


class MazeSolver:
    CELL_SIZE = 20

    def __init__(self, mazeImagePath: Optional[str] = None):
        self.mazeImagePath = mazeImagePath

        if mazeImagePath:
            self.originalImage = cv2.imread(str(self.mazeImagePath))
            self.binaryImage = self.readImage(str(self.mazeImagePath))
            self._setDefaults()
            self._createGraph()

        self.annotator: Optional[MazeAnnotator] = None

    def solveWithDFS(self, animate: bool = False) -> List[Tuple[int, int]]:
        if animate and not self.annotator:
            raise AnnotatorNotFound("Please setup annotator first")

        markedImage = np.array(self.originalImage)

        if animate and self.annotator:
            markedImage = self.annotator.plotPointsOnImage(self.originalImage)
            markedImage = cv2.cvtColor(markedImage, cv2.COLOR_BGR2RGB)

        start_node = self.start
        end_node = self.end

        # push the starting node in stack and mark as visited
        stack = []
        visited = []
        parent = {}
        visited.append(start_node)
        stack.append(start_node)

        while stack:
            # pop the node at top in stack
            current_node = stack.pop()

            if current_node == end_node:
                # visited.append(current_node)
                break  # Exit the loop if the destination is reached

            # explore all the adjacent nodes of current_node
            for neighbour in self.graph[current_node]:
                # check if current_node has any valid adjacent node
                if neighbour not in visited:
                    visited.append(neighbour)  # mark as visited
                    parent[neighbour] = current_node
                    stack.append(neighbour)

            current_path = [current_node]
            while current_node != start_node:
                current_node = parent[current_node]
                current_path.insert(0, current_node)

            if animate and self.annotator:
                plotted_image = self.annotator.plotPathOnImage(
                    markedImage, current_path[:-1], animate=False
                )
                self.annotator.plotPathOnImage(
                    plotted_image, current_path[-2:], animate=True
                )
        # Reconstruct the path from end_node to start_node
        path = [end_node]
        while end_node != start_node:
            end_node = parent[end_node]
            path.insert(0, end_node)
        print("Path:", path)

        if animate and self.annotator:
            plotted_image = self.annotator.plotPathOnImage(
                markedImage, path[:-1], animate=False
            )
            self.annotator.plotPathOnImage(plotted_image, path[-2:], animate=True)

        return path

    def solveWithBFS(self, animate: bool = False) -> List[Tuple[int, int]]:
        if animate and not self.annotator:
            raise AnnotatorNotFound("Please setup annotator first")

        markedImage = np.array(self.originalImage)
        if animate and self.annotator:
            markedImage = self.annotator.plotPointsOnImage(self.originalImage)
            markedImage = cv2.cvtColor(markedImage, cv2.COLOR_BGR2RGB)

        parent = {}
        # initialize an empty Queue to keep track of adjacent nodes
        queue: Queue[Any] = Queue()
        # to keep track of visited nodes
        visited = []

        start_node = self.start
        end_node = self.end

        # append the starting node in queue and mark as visited
        visited.append(start_node)
        queue.put(start_node)

        while queue:
            # pop the node at front in queue
            current_node = queue.get()

            if current_node == end_node:
                break  # Exit the loop if the destination is reached

            # explore all the adjacent nodes of current_node
            for neighbour in self.graph[current_node]:
                # check if current_node has any valid adjacent node
                if neighbour not in visited:
                    visited.append(neighbour)  # mark as visited
                    parent[neighbour] = current_node
                    queue.put(neighbour)

            current_path = [current_node]
            while current_node != start_node:
                current_node = parent[current_node]
                current_path.insert(0, current_node)

            if animate and self.annotator:
                plotted_image = self.annotator.plotPathOnImage(
                    markedImage, current_path[:-1], animate=False
                )
                self.annotator.plotPathOnImage(
                    plotted_image, current_path[-2:], animate=True
                )

        # Reconstruct the path from end_node to start_node
        path = [end_node]
        while end_node != start_node:
            end_node = parent[end_node]
            path.insert(0, end_node)
        print("Path:", path)

        if animate and self.annotator:
            plotted_image = self.annotator.plotPathOnImage(
                markedImage, path[:-1], animate=False
            )
            self.annotator.plotPathOnImage(plotted_image, path[-2:], animate=True)

        return path

    def solveWithDijkstra(self, animate: bool = False) -> List[Tuple[int, int]]:
        if animate and not self.annotator:
            raise AnnotatorNotFound("Please setup annotator first")

        markedImage = np.array(self.originalImage)
        if animate and self.annotator:
            markedImage = self.annotator.plotPointsOnImage(self.originalImage)
            markedImage = cv2.cvtColor(markedImage, cv2.COLOR_BGR2RGB)

        queue: List[tuple] = []
        parent = {}
        distance = {}

        source = self.start
        destination = self.end

        for node in self.graph:
            distance[node] = float("inf")
        distance[source] = 0

        # enqueue source vertex in priority queue with priority 0
        heapq.heappush(queue, (0, source))

        while queue:
            current_vertex = heapq.heappop(queue)
            current_priority, current_node = current_vertex
            if current_node == destination:
                break
            for neighbor in self.graph[current_node]:
                # since graph is unweighted, we let actual cost '1'
                actual_cost = 1
                new_distance = distance[current_node] + actual_cost

                if new_distance < distance[neighbor]:
                    distance[neighbor] = new_distance
                    priority = new_distance
                    heapq.heappush(queue, (priority, neighbor))
                    parent[neighbor] = current_node

            current_path = [current_node]
            while current_node != source:
                current_node = parent[current_node]
                current_path.insert(0, current_node)

            if animate and self.annotator:
                plotted_image = self.annotator.plotPathOnImage(
                    markedImage, current_path[:-1], animate=False
                )
                self.annotator.plotPathOnImage(
                    plotted_image, current_path[-2:], animate=True
                )

        # Reconstruct the path from source to destination
        path = [destination]
        while destination != source:
            destination = parent[destination]
            path.insert(0, destination)
        print("Path:", path)

        if animate and self.annotator:
            plotted_image = self.annotator.plotPathOnImage(
                markedImage, path[:-1], animate=False
            )
            self.annotator.plotPathOnImage(plotted_image, path[-2:], animate=True)

        return path

    def solveWithAlgorithm(
        self, algorithm: str, animate: bool = False
    ) -> List[Tuple[int, int]]:
        if algorithm == "DFS":
            return self.solveWithDFS(animate)

        if algorithm == "BFS":
            return self.solveWithBFS(animate)

        if algorithm == "Dijkstra":
            return self.solveWithDijkstra(animate)

        raise Exception("Algorithm not found")

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

    def readImage(self, mazePath: str) -> np.ndarray:
        img = cv2.imread(mazePath, 0)
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
            "rightEdge": rightEdge,
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

                if isEdgePossible["leftEdge"]:
                    self.graph[(j, i)].add((j - 1, i))

                if isEdgePossible["rightEdge"]:
                    self.graph[(j, i)].add((j + 1, i))

    def setStart(self, point: Tuple[int, int]) -> None:
        self.start = point

    def setEnd(self, point: Tuple[int, int]) -> None:
        self.end = point

    def setAnnotator(self, annotator: MazeAnnotator) -> None:
        self.annotator = annotator

    def setMazeImage(self, mazeImagePath: str) -> None:
        self.mazeImagePath = mazeImagePath
        self.originalImage = cv2.imread(mazeImagePath)
        self.binaryImage = self.readImage(mazeImagePath)
        self._setDefaults()
        self._createGraph()
