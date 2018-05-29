from ReceiverFirebase import ReceiverFirebase
from SenderFirebase import SenderFirebase
import json
import time
from SerialCommunication import CanSerial


class FirebaseCommunication:
    bak = 1
    receiver = ReceiverFirebase()
    sender = SenderFirebase()

    serial = CanSerial("/dev/ttyUSB1")

    currentValues = None

    def __init__(self):
        self.currentValues = list(self.receiver.get_all())

    def poll_schematic_update(self):
        while(1):

            print("hallo")
            temp = list(self.receiver.get_all())
            for i in range(0, temp.__len__()):
                if isinstance(temp[i], dict):
                    newValue = temp[i]
                    try:
                        oldValue = self.currentValues[i]
                    except IndexError:
                        oldValue = {}
                    if newValue != oldValue:
                        schematic = temp[i]["ActiveSchematic"]
                        schematicValues = self.receiver.get_schematic(schematic)
                        if schematicValues is None:
                            print("Unkown Schematic")
                            self.sender.post_unkown_schematic(i, schematicValues)
                        else:
                            print("Uploading")
                            self.currentValues = list(self.receiver.get_all())
                            self.upload_schematics(schematicValues)
                elif temp[i] is not None:
                    self.add_new_biosphere(i)

    def update_current_values(self):
        while True:
            msg = self.serial.read()
            if msg is not None:
                print("")
                print("Received:")
                print("ID: " + msg[0] + " Data: " + msg[1])
                print("")
                data = int(msg[0])
                controllerType = data & 0b11
                biosphereNumber = (data & 0b11111100) >> 2
                value = (self.switch(controllerType), float(msg[1][:msg[1].index('\x00')]))
                print(value)
                self.sender.post(biosphereNumber, value)

    def add_new_biosphere(self, ID):
        self.sender.post(ID, None)

    def switch(self, x):
        return {
            0: "Pi",
            1: "temperature",
            2: "lux",
            3: "groundMoisture"
        }.get(x, 0)

    def upload_schematics(self, values):
        self.serial.write(id=1, message=str(values["temperature"]))
        self.serial.write(id=2, message=str(values["lux"]))
        self.serial.write(id=3, message=str(values["groundMoisture"]))
