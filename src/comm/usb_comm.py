import serial

class USB():
	def __init__(self, baudrate, path = None):
		self.path = path
		self.baudrate = baudrate
		self.ser = serial.Serial(path, baudrate)
		
	def write(self, num):
		mstr = str(num)
		self.ser.write(str.encode(mstr))
		self.ser.write(str.encode('\n'))

	def write_char(self, char):
		self.ser.write(str.encode(char))
		
	def read(self):
		stringa = self.ser.readline().strip()
		return int(stringa)
