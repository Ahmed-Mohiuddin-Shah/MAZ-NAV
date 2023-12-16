from model import Model
from gui import GUI


def main():
    model = Model()
    gui = GUI(model)
    gui.mainloop()

    exit()


if __name__ == "__main__":
    main()
