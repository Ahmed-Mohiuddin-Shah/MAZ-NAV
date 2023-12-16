from typing import List
import bluetooth


class UnableToConnectToRoverException(Exception):
    ...


class RoverController:
    def __init__(self) -> None:
        self.roverSocket = None

    def connectToRover(self):
        DEVICE_NAME = "MAZ-NAV"
        TARGET_ADDRESS = None
        STEPS_FOR_COVERING_ONE_CELL = 200

        tries = 1
        while TARGET_ADDRESS is None and tries > 0:
            print(f"Searching for bluetooth devices. Tries left {tries}")
            devices = bluetooth.discover_devices(lookup_names=True)

            print(devices)

            for addr, name in devices:
                if name == DEVICE_NAME:
                    print("Found %s - connecting" % DEVICE_NAME)
                    TARGET_ADDRESS = addr
                    break

            tries -= 1

        if TARGET_ADDRESS is None:
            raise UnableToConnectToRoverException()

        print("Connecting to target device...")
        sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        sock.connect((TARGET_ADDRESS, 1))
        print("Connected!")

        self.roverSocket = sock

    def disconnectFromRover(self):
        self.roverSocket.close()

    def convertPathToRoverSteps(self, path):
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

        return steps

    def runRover(self, path: List[tuple]) -> bool:
        steps = self.convertPathToRoverSteps(path)
        self.roverSocket.send(' '.join(steps))
        data = self.roverSocket.recv(1024)
        print("Received: %s" % data)
        return True
