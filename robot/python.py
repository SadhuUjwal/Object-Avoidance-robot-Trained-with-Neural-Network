import serial
ser = serial.Serial('/dev/tty.usbmodem1d11', 9600) # Establish the connection on a specific port
counter = 32 # Below 32 everything in ASCII is gibberish
print ser.readline()
print ''
print ''
print 'f for forword'
print 's for stop'
print 'r for right'
print 'l for left'
print ''
print ''
decision= raw_input(' decision: ')
print ''
print ''
ser.write(str(decision))
print ''
print ''
print ser.readline()
print ''
print ''
decision= raw_input(' decision: ')
print ''
print ''
ser.write(str(decision))