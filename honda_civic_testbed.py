import os
import can
import cantools
import time
import random
import subprocess

def setup_can():
    os.system("sudo modprobe vcan")
    os.system("sudo ip link add dev vcan0 type vcan")
    os.system("sudo ip link set up vcan0")
    print("[✔] Virtual CAN bus initialized.")

def load_dbc():
    dbc_file = "opendbc/honda_civic_touring_2016_can.dbc"
    db = cantools.database.load_file(dbc_file)
    print("[✔] DBC file loaded successfully.")
    return db

def simulate_ecu_behavior(db, bus):
    """ Simulate dynamic ECU behavior like acceleration and braking """
    for i in range(10):
        speed = random.randint(0, 120)
        rpm = random.randint(800, 6500)
        
        speed_data = db.encode_message("DASHBOARD", {"SPEED": speed})
        speed_msg = can.Message(arbitration_id=db.get_message_by_name("DASHBOARD").frame_id, data=speed_data)
        bus.send(speed_msg)

        rpm_data = db.encode_message("ENGINE_DATA", {"ENGINE_RPM": rpm})
        rpm_msg = can.Message(arbitration_id=db.get_message_by_name("ENGINE_DATA").frame_id, data=rpm_data)
        bus.send(rpm_msg)

        print(f"Sent Speed: {speed} mph, RPM: {rpm}")
        time.sleep(1)

def replay_real_can_traffic(bus):
    """ Replay real Honda Civic CAN logs """
    with open("replay_can.log", "r") as f:
        for line in f:
            parts = line.strip().split()
            can_id = int(parts[2], 16)
            data = bytes.fromhex("".join(parts[4:]))
            
            msg = can.Message(arbitration_id=can_id, data=data)
            bus.send(msg)
            print(f"Replayed CAN Message: ID {hex(can_id)} - Data {data}")
            time.sleep(0.1)

if __name__ == "__main__":
    print("[🚗] Starting Honda Civic Testbed...")

    setup_can()
    db = load_dbc()
    bus = can.interface.Bus(channel="vcan0", bustype="socketcan")

    simulate_ecu_behavior(db, bus)  # Simulate ECUs
    replay_real_can_traffic(bus)  # Replay real-world data
