import sys
import can
import threading
import pyqtgraph as pg
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QLabel
from PyQt6.QtCore import QTimer

class CANBusMonitor(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

        # Set up CAN interface
        self.bus = can.interface.Bus(channel="vcan0", bustype="socketcan")

        # Live data storage
        self.speed_data = []
        self.rpm_data = []
        self.time_data = []

        # Timer for real-time updates
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_data)
        self.timer.start(1000)  # Update every second

        # Start CAN listener in a background thread
        self.listener_thread = threading.Thread(target=self.listen_can_bus, daemon=True)
        self.listener_thread.start()

    def initUI(self):
        """ Initialize GUI layout """
        self.setWindowTitle("Honda Civic Testbed GUI")
        self.setGeometry(100, 100, 600, 400)

        layout = QVBoxLayout()

        self.speed_label = QLabel("Speed: 0 mph")
        self.rpm_label = QLabel("RPM: 0")
        self.brake_label = QLabel("Brakes: OFF")

        layout.addWidget(self.speed_label)
        layout.addWidget(self.rpm_label)
        layout.addWidget(self.brake_label)

        # Add real-time graph
        self.graph = pg.PlotWidget()
        self.graph.setTitle("Engine RPM Over Time")
        self.graph.setLabel("left", "RPM")
        self.graph.setLabel("bottom", "Time (s)")
        layout.addWidget(self.graph)

        self.setLayout(layout)

    def listen_can_bus(self):
        """ Listen for CAN messages and update GUI variables """
        while True:
            msg = self.bus.recv()
            if msg:
                # Decode speed data
                if msg.arbitration_id == 0x158:
                    speed = int.from_bytes(msg.data[:2], "big")
                    self.speed_label.setText(f"Speed: {speed} mph")
                    self.speed_data.append(speed)

                # Decode RPM data
                elif msg.arbitration_id == 0x17C:
                    rpm = int.from_bytes(msg.data[:2], "big")
                    self.rpm_label.setText(f"RPM: {rpm}")
                    self.rpm_data.append(rpm)

                # Decode brake status
                elif msg.arbitration_id == 0x1FA:
                    brake_status = "ON" if msg.data[0] == 1 else "OFF"
                    self.brake_label.setText(f"Brakes: {brake_status}")

    def update_data(self):
        """ Update graph with new RPM data """
        if len(self.rpm_data) > 50:  # Keep only last 50 readings
            self.rpm_data.pop(0)
        if len(self.speed_data) > 50:
            self.speed_data.pop(0)

        self.graph.plot(self.rpm_data, clear=True)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = CANBusMonitor()
    window.show()
    sys.exit(app.exec())
