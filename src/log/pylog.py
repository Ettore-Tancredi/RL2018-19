import time


class Log():
    def __init__(self, path, run_id):
        self.path = path
        self.filename = run_id + "_log.txt"

    def write(self, string):
        pass

    def start_milli_chrono(self):
        self.start_time = int(round(time.time() * 1000))
    def end_milli_chrono(self):
        self.end_time = int(round(time.time() * 1000))
        #to be multithreaded
        self.write(str(self.start_time - self.end_time) + "ms")

    