🚗 Honda Civic Cybersecurity Testbed

A realistic, open-source cybersecurity testbed for the 2018 Honda Civic, designed to simulate ECU communications, replay real CAN bus data, and visualize attacks.

📌 Features

✅ Simulates real Honda Civic ECU communications

✅ Uses DBC files to ensure accurate CAN messages

✅ Supports OBD-II diagnostics and real-time responses

✅ GUI for visualizing CAN bus activity (speed, RPM, brakes)

✅ Replays real-world CAN traffic

✅ Logs and monitors CAN messages in real time

📥 Installation

1. Clone the Repository

git clone https://github.com/your-username/honda-civic-testbed.git
cd honda-civic-testbed

(Replace your-username with your actual GitHub username.)

2. Install Dependencies

pip install pyqt6 pyqtgraph matplotlib can cantools

3. Setup Virtual CAN Bus

sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

🚀 Running the Testbed

1. Start the Main Testbed

python3 honda_civic_testbed.py

✅ This initializes virtual CAN bus, starts ECU simulation, and logs messages.

2. Run the GUI

python3 testbed_gui.py

✅ The GUI will show real-time speed, RPM, and braking data.

📊 How the Testbed Works

1. Simulated ECUs

Engine ECU: Sends real-time RPM and throttle data.

Dashboard ECU: Displays speedometer readings.

Braking System ECU: Simulates ABS and braking behavior.

Infotainment ECU: Can be extended to include audio system CAN traffic.

2. Real-Time Logging

Logs all CAN messages sent between ECUs.

Uses candump for live monitoring.

candump vcan0

3. CAN Message Replay

To replay real CAN data:

python3 replay_can.py

(You can replace replay_can.log with any Honda Civic CAN dump.)

🛠️ Future Features

🔄 Live attack simulations (ECU spoofing, replay attacks)

📡 Remote control via Raspberry Pi

🎨 Better GUI visualization (Live charts, more ECUs)

🛠️ Support for real OBD-II hardware integration

👨‍💻 Contributors

Your Name (@your-username) (Replace with actual name & GitHub username.)

Feel free to contribute via Pull Requests!

📜 License

This project is licensed under the MIT License.
