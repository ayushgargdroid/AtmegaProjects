import serial

class testSerial():
	def __init__(self):
		global ser
		ser = serial.Serial('/dev/ttyUSB0',9600)
		print(ser.name + " is initialized")
		self.main()

	def main(self):
		global ser
		print('2414')
		while(1):
			ser.write('1235a')
			a = ser.read()
			print(a)
			print(type(a))
		
testSerial()

