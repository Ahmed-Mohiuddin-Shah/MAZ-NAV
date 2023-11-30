import bluetooth
import random
import time
import test

DEVICE_NAME = "MAZ-NAV"
TARGET_ADDRESS = None
STEPS_FOR_COVERING_ONE_CELL = 200

tries = 1

while TARGET_ADDRESS is None and tries > 0:
    print(f"Searching for bluetooth devices. Tries left {tries}")
    devices = bluetooth.discover_devices(lookup_names=True)

    for addr, name in devices:
        if name == DEVICE_NAME:
            print("Found %s - connecting" % DEVICE_NAME)
            TARGET_ADDRESS = addr
            break

    tries -= 1

shortestPath = test.main()

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

for y, x in shortestPath:
    if previousX is None and previousY is None:
        previousX = x
        previousY = y
        # steps.append(
        #     (x * STEPS_FOR_COVERING_ONE_CELL,
        #      y * STEPS_FOR_COVERING_ONE_CELL)
        # )
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

    # steps.append(
    #     (x * STEPS_FOR_COVERING_ONE_CELL,
    #      y * STEPS_FOR_COVERING_ONE_CELL)
    # )

    previousX = x
    previousY = y

for step in steps:
    if 'tuple' in str(type(step)):
        print(f"{step[0]},{step[1]}")
    else:
        print(step)

if TARGET_ADDRESS is not None:
    print("Connecting to target device...")
    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    sock.connect((TARGET_ADDRESS, 1))
    print("Connected!")

    shortestPath = test.main()
    # print(shortestPath)

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
