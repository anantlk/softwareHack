import time
import serial

try:
	ser=serial.Serial('COM9',9600)	
	while True:
		message=ser.readline()
		print(message)

except serial.SerialException:
	print("Check the device Port")
	print
	
