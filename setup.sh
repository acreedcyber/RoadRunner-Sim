#!/bin/bash

# Honda Civic Cybersecurity Testbed Setup Script
# This script installs dependencies, sets up the virtual CAN bus, and runs the testbed and GUI

echo "🚗 Setting up Honda Civic Cybersecurity Testbed..."

# Update package lists
echo "🔄 Updating system packages..."
sudo apt update && sudo apt upgrade -y

# Install required dependencies
echo "📦 Installing required dependencies..."
sudo apt install -y python3 python3-pip can-utils
pip3 install pyqt6 pyqtgraph matplotlib can cantools

# Setup Virtual CAN Bus
echo "🛠 Setting up Virtual CAN Bus..."
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

# Run the Testbed and GUI
echo "🚀 Launching the Honda Civic Cybersecurity Testbed..."
python3 honda_civic_testbed.py &
sleep 5  # Allow time for the testbed to start
python3 testbed_gui.py &

echo "✅ Setup complete! The testbed and GUI are now running."
