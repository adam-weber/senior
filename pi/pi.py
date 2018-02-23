##########
#
# MTU Senior Project 2017-2018
# PKE via BLE
#
##########

#####
# Import Libraries
#
import serial
import sqlite3
import random

#####
# Global Variables
#
# Hardcoded token from keyfob
token = ""
# rng value to increment counter by
rng = ""
# Number of times to interate the rng
count = ""
# Token and counter received from keyfob 
tokenAndCounter = ""
# Counter received from keyfob
counter = ""

#####
# Initialize
#
# Connect to sqlite db
db = sqlite3.connect('/home/pi/TestDB2')
# Create Cursor object to execute commands on
cursor = db.cursor()
#
# Sets seed for rng (should be the same on the keyfob)
random.seed(52)
#
# Setup serial options
port = serial.Serial("/dev/ttyACM0", baudrate=115200, timeout=9999)
#
# Open the file where the count is stored
fh = open("/home/pi/Documents/count.txt","r")
# Set count to equal the int from the file
count = fh.readline()
# Cast count as an integer
count = int(count)
# Close the file
fh.close

# Iterate rng by count number of times (to keep sync with keyfob)
for i in range (0, count):
	rng = random.randint(0, 4294967295)

print rng

# Flush serial input buffer
port.flushInput()

# Get token and counter from keyfob and store to tokenAndCounter string until delimiter % is reached
while True:
	tokenAndCounter = tokenAndCounter + port.read(1)
	if tokenAndCounter[len(tokenAndCounter) - 1] == "%":
		tokenAndCounter = tokenAndCounter[:-1] #removes % from string
		port.write("Your token and counter was" + repr(tokenAndCounter))
		break

# Split received token and counter into seperate variables
temp = tokenAndCounter.split(',') 
token = temp[0]
counter = temp[1]
print counter

# Pull data from the database
cursor.execute('''SELECT type, model, version FROM dongs''')

# Pull first row from db
first_row = cursor.fetchone();
print(first_row[0])

# Unlock car if token matches the first row and counter matches
if (first_row[0] == token):
	if (int(counter) == 123456):
		print "UNLOCK"
		port.write("5318008")
	else:
		port.write("n"+ str((rng*7.65)))
else:
	print "NO"

# Close db connection
db.close()

# Increase count by 1 and rewrite to count.txt
count+=1
fh = open("/home/pi/Documents/count.txt","w")
fh.write(str(count))
fh.close