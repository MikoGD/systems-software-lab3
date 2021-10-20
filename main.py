import os


def main():
    processes = os.popen("ps -au")
    processes.readline()
    row = processes.readline()
    print(repr(row))
# END main()


if __name__ == "__main__":
    main()
