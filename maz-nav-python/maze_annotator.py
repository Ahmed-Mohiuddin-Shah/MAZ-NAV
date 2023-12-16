import time
from typing import Any, List, Dict, Set, Tuple

import cv2
import numpy as np


class MazeAnnotator:
    CELL_SIZE = 20
    ANIMATION_DELAY_IN_MS = 300
    LINE_SIZE = 2
    POINT_RADIUS = 3

    def __init__(
        self, graph: Dict[tuple, Set[tuple]], start: tuple, end: tuple, dims: tuple
    ):
        self.graph = graph
        self.start = start
        self.end = end

        height, width = dims

        self.height = height
        self.width = width
        self._verticalCells = self.height // self.CELL_SIZE
        self._horizontalCells = self.width // self.CELL_SIZE

    def plotPointsOnImage(self, image: np.ndarray) -> np.ndarray:
        image = image.copy()

        midX = self.CELL_SIZE // 2
        midY = self.CELL_SIZE // 2

        color = (241, 196, 15)
        startColor = (46, 204, 113)
        endColor = (231, 76, 60)

        for i in range(self._verticalCells):
            for j in range(self._horizontalCells):
                center = (midX * (j + 1) + midX * j, midY * (i + 1) + midY * i)
                tempColor = color
                radius = self.POINT_RADIUS
                if (j, i) == self.start:
                    tempColor = startColor
                    radius *= 2

                if (j, i) == self.end:
                    tempColor = endColor
                    radius *= 2

                image = cv2.circle(image, center, radius, tempColor, -1)

        return image

    def plotEdgesOnImage(self, image: np.ndarray) -> np.ndarray:
        image = image.copy()
        midX = self.CELL_SIZE // 2
        midY = self.CELL_SIZE // 2
        color = (52, 152, 219)

        for node in self.graph:
            startX, startY = node

            startX = startX * self.CELL_SIZE + midX
            startY = startY * self.CELL_SIZE + midY

            for adjacent in self.graph.get(node, []):
                endX, endY = adjacent
                endX = endX * self.CELL_SIZE + midX
                endY = endY * self.CELL_SIZE + midY
                image = cv2.line(
                    image, (startX, startY), (endX, endY), color, self.LINE_SIZE
                )

        return image

    def plotPathOnImage(
        self, image: Any, path: List[Tuple[int, int]], animate: bool = False
    ) -> np.ndarray:
        image = image.copy()
        midX = self.CELL_SIZE // 2
        midY = self.CELL_SIZE // 2
        color = (219, 152, 52)

        for i in range(len(path) - 1):
            startX, startY = path[i]
            endX, endY = path[i + 1]

            startX = startX * self.CELL_SIZE + midX
            startY = startY * self.CELL_SIZE + midY

            endX = endX * self.CELL_SIZE + midX
            endY = endY * self.CELL_SIZE + midY

            image = cv2.line(
                image, (startX, startY), (endX, endY), color, self.LINE_SIZE
            )

            if animate:
                self.displayImage(image)
                time.sleep(self.ANIMATION_DELAY_IN_MS / 1000)

        return image

    def displayImage(self, image: np.ndarray) -> None:
        imageCopy = cv2.resize(image.copy(), (500, 500))
        cv2.imshow("Maze", imageCopy)
        cv2.waitKey(5)
