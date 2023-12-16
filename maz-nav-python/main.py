from model import Model
from gui import GUI
from roverapi import RoverAPI


def main():
    model = Model()
    gui = GUI(model)
    gui.mainloop()

    exit()


if __name__ == "__main__":
    main()
