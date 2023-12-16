import asyncio
import threading
import time

from fastapi import FastAPI

from model import Model

import asyncio
from fastapi import FastAPI

from rover_controller import RoverController

rover = RoverController()
app = FastAPI()



@app.get("/connect")
async def connect():
    try:
        rover.connectToRover()
    except Exception as e:
        return {"message": "Unable to connect to rover"}
    return {"message": "Connected"}

@app.get("/disconnect")
async def disconnect():
    rover.disconnectFromRover()
    return {"message": "Disconnected"}
