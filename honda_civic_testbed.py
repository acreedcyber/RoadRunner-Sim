import os
import can
import cantools
import time
import random
import subprocess

def setup_can():
    """ Initialize virtual CAN bus interfaces """
    os.system("sudo modprobe vcan")
    os.system("sudo ip link add dev vcan0 type vcan")
    os.system("sudo ip link set up vcan0")
    print("[✔] Virtual CAN bus initialized.")

def load_dbc():
    """ Load Honda Civic DBC file for accurate CAN message encoding """
    dbc_file = "opendbc/honda_civic_touring_2016_can.dbc"
    try:
        db = cantools.database.load_file(dbc_file)
        print("[✔] DBC file loaded successfully.")
        return db
    except Exception as e:
        print(f"[✘] Error loading DBC file: {e}")
        exit(1)

def simulate_ecu_behavior(db, bus):
    """ Simulate realistic ECU behavior: acceleration, braking, RPM changes """

    speed = 0  # Start at 0 mph
    rpm = 800  # Idle RPM

    for i in range(30):  # Simulate 30 seconds of driving
        if i < 10:
            speed += 5  # Accelerating
            rpm += 300
        elif i < 20:
            speed = speed  # Maintain speed
            rpm = rpm
        else:
            speed -= 5  # Decelerating
            rpm -= 300

        speed = max(0, speed)  # Prevent negative values
        rpm = max(800, rpm)  # Keep RPM at idle minimum

        try:
            # Encode Speed Data
            speed_data = db.encode_message("DASHBOARD", {"SPEED": speed})
            speed_msg = can.Message(arbitration_id=db.get_message_by_name("DASHBOARD").frame_id,
                                    data=speed_data, is_extended_id=False)
            bus.send(speed_msg)

            # Encode RPM Data
            rpm_data = db.encode_message("ENGINE_DATA", {"ENGINE_RPM": rpm})
            rpm_msg = can.Message(arbitration_id=db.get_message_by_name("ENGINE_DATA").frame_id,
                                  data=rpm_data, is_extended_id=False)
            bus.send(rpm_msg)

            print(f"Speed: {speed} mph | RPM: {rpm}")
            time.sleep(1)  # Simulate real-time interval

        except KeyError as e:
            print(f"[✘] Error encoding CAN message: {e}")
        except can.CanError as e:
            print(f"[✘] CAN Error: {e}")

def replay_real_can_traffic(bus):
    """ Replay real Honda Civic CAN logs to simulate actual driving data """
    try:
        with open("replay_can.log", "r") as f:
            for line in f:
                parts = line.strip().split()
                can_id = int(parts[2], 16)
                data = bytes.fromhex("".join(parts[4:]))

                msg = can.Message(arbitration_id=can_id, data=data)
                bus.send(msg)
                print(f"Replayed CAN Message: ID {hex(can_id)} - Data {data}")
                time.sleep(0.1)  # Real-time interval

    except FileNotFoundError:
        print("[✘] Error: replay_can.log not found!")

def obd_response_simulation(bus, db):
    """ Simulate ECU responding to OBD-II diagnostic requests """
    print("[✔] Listening for OBD-II requests...")
    while True:
        msg = bus.recv(timeout=5)  # Wait for request
        if msg:
            if msg.arbitration_id == 0x7DF:  # 0x7DF is the global OBD-II request ID
                print(f"[🛠] ECU received diagnostic request: {msg}")

                try:
                    # Respond with Engine Temperature and Throttle Position
                    response = db.encode_message("ENGINE_DATA", {"ENGINE_TEMP": 90, "THROTTLE_POS": 40})
                    response_msg = can.Message(arbitration_id=0x7E8, data=response, is_extended_id=False)
                    bus.send(response_msg)
                    print("[✔] Sent OBD-II ECU response")

                except KeyError as e:
                    print(f"[✘] Error encoding OBD-II response: {e}")

if __name__ == "__main__":
    print("[🚗] Starting Honda Civic Testbed...")

    setup_can()
    db = load_dbc()
    bus = can.interface.Bus(channel="vcan0", bustype="socketcan")

    simulate_ecu_behavior(db, bus)  # Simulate ECUs
    replay_real_can_traffic(bus)  # Replay real-world data

    # Optional: Start OBD-II response simulation in a separate process
    obd_thread = subprocess.Popen(["python3", "-c", "import testbed; testbed.obd_response_simulation(testbed.bus, testbed.db)"])
