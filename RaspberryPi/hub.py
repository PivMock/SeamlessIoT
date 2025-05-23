import bluetooth
import csv
import os
from datetime import datetime

# Bluetooth settings
server_sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
server_sock.bind(("",1)) # Bind to any available RFCOMM port
server_sock.listen(1)

# CSV file settings
csv_file = "temperature_data.csv"
file_exists = os.path.isfile(csv_file)

# Prepare CSV file
with open(csv_file, 'a', newline = '') as f:
    writer = csv.writer(f)
    # Write header if file is new
    if not file_exists:
        writer.writerow(["Timestamp","Temperature"])

print("Waiting for Bluetooth connection...")
client_sock, client_info = server_sock.accept()
print(f"Connected to {client_info}")

try:
    while True:
        data = client_sock.recev(1024).decode('utf-8').strip()
        if data:
            print(f"Received: {data}")
            # Get current timestamp
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            # Write to CSV
            with open(csv_file, 'a', newline = '') as f:
                writer.writerow([timestamp, data])
except KeyboardInterrupt:
    print("Closing connection")
    client_sock.close()
    server_sock.close()
