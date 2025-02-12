#!/bin/bash

echo "🚗 Installing Honda ICSim Replacement..."

# Update system & install dependencies
echo "🔄 Updating system and installing dependencies..."
sudo apt update && sudo apt install -y libsdl2-dev libsdl2-image-dev can-utils gcc make

# Compile the program
echo "⚙ Compiling Honda ICSim..."
make clean
make

# Setup Virtual CAN
echo "🛠 Setting up Virtual CAN bus..."
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

# Move executable to /usr/local/bin
echo "📂 Installing Honda ICSim to /usr/local/bin..."
sudo cp honda_icsim /usr/local/bin/honda_icsim

# Create a desktop shortcut
echo "🖥 Creating desktop shortcut..."
echo "[Desktop Entry]
Name=Honda ICSim
Exec=/usr/local/bin/honda_icsim
Icon=car.png
Type=Application
Categories=Development" | sudo tee /usr/share/applications/honda_icsim.desktop

echo "✅ Installation Complete! Run 'honda_icsim' from terminal or find it in your applications menu."
