import subprocess
from datetime import datetime

# --- Settings ---
raspberry_pi_user = "hubdevice"
raspberry_pi_ip = "172.20.10.10"
remote_file_path = "/home/hubdevice/bluetooth_data_log.csv"

# --- Generate timestamped filename ---
timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
local_save_path = f"/Users/harry/Downloads/bluetooth_data_log_{timestamp}.csv"

# --- Command to run ---
scp_command = [
    "scp",
    f"{raspberry_pi_user}@{raspberry_pi_ip}:{remote_file_path}",
    local_save_path
]

# --- Run the command ---
try:
    print(f"Transferring file to: {local_save_path}")
    subprocess.run(scp_command, check=True)
    print("File transferred successfully!")
except subprocess.CalledProcessError as e:
    print("Error occurred during SCP transfer:", e)