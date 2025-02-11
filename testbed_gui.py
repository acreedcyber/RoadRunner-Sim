import sys
import can
import threading
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QLabel, QSlider, QHBoxLayout
from PyQt6.QtCore import Qt

class CarDashboard(QWidget):
    def __init__(self, bus):
        super().__init__()
        self.bus = bus
        self.speed = 0
        self.rpm = 800
        self.lights_on = False
        self.brakes_on = False
        self.steering_angle = 0

        self.initUI()

        # Start CAN listener in a separate thread
        self.listener_thread = threading.Thread(target=self.listen_can_bus, daemon=True)
        self.listener_thread.start()

    def initUI(self):
        """ Set up the user interface for the car dashboard """
        self.setWindowTitle("Honda Civic Testbed - Interactive Dashboard")
        self.setGeometry(100, 100, 500, 400)

        layout = QVBoxLayout()

        # Speed & RPM Display
        self.speed_label = QLabel(f"Speed: {self.speed} mph")
        self.rpm_label = QLabel(f"RPM: {self.rpm}")
        layout.addWidget(self.speed_label)
        layout.addWidget(self.rpm_label)

        # Speed Slider
        self.speed_slider = QSlider(Qt.Orientation.Horizontal)
        self.speed_slider.setMinimum(0)
        self.speed_slider.setMaximum(120)
        self.speed_slider.setValue(self.speed)
        self.speed_slider.valueChanged.connect(self.update_speed)
        layout.addWidget(QLabel("Adjust Speed"))
        layout.addWidget(self.speed_slider)

        # Brake Button
        self.brake_button = QPushButton("Brake")
        self.brake_button.setCheckable(True)
        self.brake_button.clicked.connect(self.toggle_brakes)
        layout.addWidget(self.brake_button)

        # Steering Controls
        steering_layout = QHBoxLayout()
        self.left_button = QPushButton("← Turn Left")
        self.left_button.clicked.connect(lambda: self.steer(-10))
        self.right_button = QPushButton("Turn Right →")
        self.right_button.clicked.connect(lambda: self.steer(10))
        steering_layout.addWidget(self.left_button)
        steering_layout.addWidget(self.right_button)
        layout.addLayout(steering_layout)

        # Lights Toggle
        self.lights_button = QPushButton("Toggle Headlights")
        self.lights_button.setCheckable(True)
        self.lights_button.clicked.connect(self.toggle_lights)
        layout.addWidget(self.lights_button)

        # Lock/Unlock Doors
        self.lock_button = QPushButton("Lock Doors")
        self.lock_button.clicked.connect(lambda: self.send_can_message(0x3E9, [1]))
        self.unlock_button = QPushButton("Unlock Doors")
        self.unlock_button.clicked.connect(lambda: self.send_can_message(0x3E9, [0]))
        layout.addWidget(self.lock_button)
        layout.addWidget(self.unlock_button)

        self.setLayout(layout)

    def update_speed(self):
        """ Update speed based on slider and send CAN message """
        self.speed = self.speed_slider.value()
        self.rpm = max(800, 800 + (self.speed * 50))  # Simulating RPM increase with speed
        self.speed_label.setText(f"Speed: {self.speed} mph")
        self.rpm_label.setText(f"RPM: {self.rpm}")

        # Send CAN message
        self.send_can_message(0x158, [self.speed])
        self.send_can_message(0x17C, [self.rpm])

    def toggle_brakes(self):
        """ Simulate braking and send CAN message """
        self.brakes_on = not self.brakes_on
        self.brake_button.setText("Braking..." if self.brakes_on else "Brake")
        self.send_can_message(0x1FA, [1 if self.brakes_on else 0])

    def steer(self, angle):
        """ Simulate steering and send CAN message """
        self.steering_angle += angle
        self.send_can_message(0x123, [self.steering_angle])

    def toggle_lights(self):
        """ Toggle headlights and send CAN message """
        self.lights_on = not self.lights_on
        self.send_can_message(0x3D0, [1 if self.lights_on else 0])

    def send_can_message(self, arbitration_id, data):
        """ Send CAN message to the virtual CAN bus """
        msg = can.Message(arbitration_id=arbitration_id, data=bytearray(data), is_extended_id=False)
        self.bus.send(msg)

    def listen_can_bus(self):
        """ Listen for incoming CAN messages and update UI if necessary """
        while True:
            msg = self.bus.recv()
            if msg:
                print(f"Received CAN Message: {msg.arbitration_id} - {msg.data}")

if __name__ == "__main__":
    app = QApplication(sys.argv)

    # Initialize CAN bus
    bus = can.interface.Bus(channel="vcan0", bustype="socketcan")

    # Start GUI
    window = CarDashboard(bus)
    window.show()

    sys.exit(app.exec())
