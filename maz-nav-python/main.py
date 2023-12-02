import bluetooth
import random

import cv2
from maze_annotator import MazeAnnotator
from maze_solver import MazeSolver


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

DEVICE_NAME = "MAZ-NAV"
TARGET_ADDRESS = None
STEPS_FOR_COVERING_ONE_CELL = 200

tries = 0

while TARGET_ADDRESS is None and tries > 0:
    print(f"Searching for bluetooth devices. Tries left {tries}")
    devices = bluetooth.discover_devices(lookup_names=True)

    for addr, name in devices:
        if name == DEVICE_NAME:
            print("Found %s - connecting" % DEVICE_NAME)
            TARGET_ADDRESS = addr
            break

    tries -= 1


steps = []
currentDir = "right"
previousX = None
previousY = None

rotations = {
    "left": {
        "up": "right",
        "down": "left"
    },
    "right": {
        "up": "left",
        "down": "right"
    },
    "up": {
        "left": "left",
        "right": "right"
    },
    "down": {
        "left": "right",
        "right": "left"
    }
}

for x, y in path:
    if previousX is None and previousY is None:
        previousX, previousY = x, y
        continue

    forwardDir = None

    if x > previousX:
        forwardDir = "right"
    if x < previousX:
        forwardDir = "left"
    if y > previousY:
        forwardDir = "down"
    if y < previousY:
        forwardDir = "up"

    if forwardDir != currentDir:
        steps.append(rotations[currentDir][forwardDir])
        currentDir = forwardDir

    steps.append("move")

    previousX = x
    previousY = y

print(path)
print(steps)

exit()

# for step in steps:
#     if 'tuple' in str(type(step)):
#         print(f"{step[0]},{step[1]}")
#     else:
#         print(step)

if TARGET_ADDRESS is not None:
    print("Connecting to target device...")
    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    sock.connect((TARGET_ADDRESS, 1))
    print("Connected!")

    sock.send(" ".join(steps))
    data = sock.recv(1024)
    print("Received: %s" % data)

    # for step in steps:
    #     sock.send(step)
    #     data = sock.recv(1024)
    #     print("Received: %s" % data)

    print("Closing connection...")

    # while True:
    #     sock.send(input("Enter value for which you want to move it: "))
    #     data = sock.recv(1024)
    #     print("Received: %s" % data)

    sock.close()
