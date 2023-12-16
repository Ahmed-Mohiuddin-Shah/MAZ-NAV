from typing import List
import bluetooth  # type: ignore


class UnableToConnectToRoverException(Exception):
    ...


class RoverController:
    TRIES = 1
    DEVICE_NAME = "MAZ-NAV"

    def connectToRover(self) -> bool:
        TARGET_ADDRESS = None

        tries = RoverController.TRIES
        while TARGET_ADDRESS is None and tries > 0:
            print(f"Searching for bluetooth devices. Tries left {tries}")
            devices = bluetooth.discover_devices(lookup_names=True)

            for addr, name in devices:
                if name == RoverController.DEVICE_NAME:
                    print("Found %s - connecting" % RoverController.DEVICE_NAME)
                    TARGET_ADDRESS = addr
                    break

            tries -= 1

        if TARGET_ADDRESS is None:
            return False

        print("Connecting to target device...")
        sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        try:
            sock.connect((TARGET_ADDRESS, 1))
        except OSError:
            return False

        self.roverSocket = sock
        print("Connected!")

        return True

    def disconnectFromRover(self):
        self.roverSocket.close()

    def convertPathToRoverSteps(self, path):
        steps = []
        currentDir = "right"
        previousX = None
        previousY = None

        rotations = {
            "left": {"up": "right", "down": "left"},
            "right": {"up": "left", "down": "right"},
            "up": {"left": "left", "right": "right"},
            "down": {"left": "right", "right": "left"},
        }

        for x, y in path:
            if previousX is None and previousY is None:
                previousX, previousY = x, y
                continue

            forwardDir = None

            if x > previousX:
                forwardDir = "right"
            elif x < previousX:
                forwardDir = "left"
            if y > previousY:
                forwardDir = "down"
            elif y < previousY:
                forwardDir = "up"

            if forwardDir != currentDir and forwardDir is not None:
                steps.append(rotations[currentDir][forwardDir])
                currentDir = forwardDir

            steps.append("move")

            previousX = x
            previousY = y

        return steps

    def runRover(self, path: List[tuple]) -> bool:
        steps = self.convertPathToRoverSteps(path)
        self.roverSocket.send(" ".join(steps))
        data = self.roverSocket.recv(1024)
        print("Received: %s" % data)
        return True
