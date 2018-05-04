# Senior Project 2018

# Library Imports
import matplotlib.pyplot as plt
import os

# Set variables
data_dir = "/Users/adamweber/code/anechoic/data/"

# distance_vs_rssi
# no_blocking = []
# hand_blocking = []
# body_blocking = []

# for files in the directory
for filename in os.listdir(data_dir):
	rssi_values = []
	if filename.endswith("_none"):
		with open(data_dir+filename, 'rt') as file:
			for line in file:
				line_segments = line.split(',')
				for index, line_segment in enumerate(line_segments):
					if index != 0:
						try:
						    rssi_values.append(int(line.split(":")[2].strip(",Time").strip())+256)
						except IndexError:
						    print "Error"
		# remove the first value
		del rssi_values[0]
		# average the values and push to final
		no_blocking.append(float(sum(rssi_values) / float(len(rssi_values))))

	elif filename.endswith("_hand"):
		with open(data_dir+filename, 'rt') as file:
			for line in file:
				line_segments = line.split(',')
				for index, line_segment in enumerate(line_segments):
					if index != 0:
						try:
						    rssi_values.append(int(line.split(":")[2].strip(",Time").strip())+256)
						except IndexError:
						    print "Error"
		# remove the first value
		del rssi_values[0]
		# average the values and push to final
		hand_blocking.append(float(sum(rssi_values) / float(len(rssi_values))))

	elif filename.endswith("_body"):
		with open(data_dir+filename, 'rt') as file:
			for line in file:
				line_segments = line.split(',')
				for index, line_segment in enumerate(line_segments):
					if index != 0:
						try:
						    rssi_values.append(int(line.split(":")[2].strip(",Time").strip())+256)
						except IndexError:
						    print "Error"
		# remove the first value
		del rssi_values[0]
		# average the values and push to final
		body_blocking.append(float(sum(rssi_values) / float(len(rssi_values))))

print no_blocking
print hand_blocking
	
distances = [0, 1, 3, 5, 10]
plt.plot(distances, no_blocking, color='green', label="No Blocking")
plt.plot(distances, hand_blocking, color='blue', label="Hand Blocking")
plt.plot(distances, body_blocking, color='red', label="Body Blocking")
plt.legend(loc='best')
plt.xlabel('Distance (feet)')
plt.ylabel('Average RSSI (dBm)')
plt.title('Distance vs RSSI of Cypress BLE')
plt.show()



# distance_vs_latency
no_blocking = []
hand_blocking = []
body_blocking = []

# for files in the directory
for filename in os.listdir(data_dir):
	rssi_values = []
	if filename.endswith("_none"):
		with open(data_dir+filename, 'rt') as file:
			for line in file:
				line_segments = line.split(',')
				for index, line_segment in enumerate(line_segments):
					if index != 0:
						try:
						    rssi_values.append(float(line_segment.split(":")[1].split("differece")[1].strip("ms RSSI")))
						except IndexError:
						    print "Error"
		# remove the first value
		del rssi_values[0]
		# average the values and push to final
		no_blocking.append(float(sum(rssi_values) / float(len(rssi_values))))

	elif filename.endswith("_hand"):
		with open(data_dir+filename, 'rt') as file:
			for line in file:
				line_segments = line.split(',')
				for index, line_segment in enumerate(line_segments):
					if index != 0:
						try:
						    rssi_values.append(float(line_segment.split(":")[1].split("differece")[1].strip("ms RSSI")))
						except IndexError:
						    print "Error"
		# remove the first value
		del rssi_values[0]
		# average the values and push to final
		hand_blocking.append(float(sum(rssi_values) / float(len(rssi_values))))

	elif filename.endswith("_body"):
		with open(data_dir+filename, 'rt') as file:
			for line in file:
				line_segments = line.split(',')
				for index, line_segment in enumerate(line_segments):
					if index != 0:
						try:
						    rssi_values.append(float(line_segment.split(":")[1].split("differece")[1].strip("ms RSSI")))
						except IndexError:
						    print "Error"
		# remove the first value
		del rssi_values[0]
		# average the values and push to final
		body_blocking.append(float(sum(rssi_values) / float(len(rssi_values))))

	
distances = [0, 1, 3, 5, 10]
plt.plot(distances, no_blocking, color='green', label="No Blocking")
plt.plot(distances, hand_blocking, color='blue', label="Hand Blocking")
plt.plot(distances, body_blocking, color='red', label="Body Blocking")
plt.legend(loc='best')
plt.xlabel('Distance (feet)')
plt.ylabel('Average Latency (ms)')
plt.title('Distance vs Latency of Cypress BLE')
plt.show()
