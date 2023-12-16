import bluetooth
import random
from fastapi import FastAPI

import cv2
from maze_annotator import MazeAnnotator
from maze_solver import MazeSolver

from gui import GUI
from roverapi import RoverAPI


def main():
    gui = GUI()
    gui.mainloop()

    exit()


if __name__ == "__main__":
    main()

mazeSolver = MazeSolver(mazeImagePath='./mazes/maze01.jpg')

height, width = mazeSolver.binaryImage.shape
verticalCells = height // mazeSolver.CELL_SIZE
horizontalCells = width // mazeSolver.CELL_SIZE
mazeSolver.setStart((0, 0))
mazeSolver.setEnd((horizontalCells - 1, verticalCells - 2))

annotator = MazeAnnotator(
    mazeSolver.graph,
    mazeSolver.start,
    mazeSolver.end,
    mazeSolver.binaryImage.shape
)

mazeSolver.setAnnotator(annotator)
path = mazeSolver.solveWithDFS(animate=True)
cv2.destroyAllWindows()


print(path)
print(steps)

exit()

# for step in steps:
#     if 'tuple' in str(type(step)):
#         print(f"{step[0]},{step[1]}")
#     else:
#         print(step)

# sock.send(" ".join(steps))
# data = sock.recv(1024)
# print("Received: %s" % data)

# # for step in steps:
# #     sock.send(step)
# #     data = sock.recv(1024)
# #     print("Received: %s" % data)

# print("Closing connection...")

# # while True:
# #     sock.send(input("Enter value for which you want to move it: "))
# #     data = sock.recv(1024)
# #     print("Received: %s" % data)

# sock.close()
