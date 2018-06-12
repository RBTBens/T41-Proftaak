from ReceiverFirebase import ReceiverFirebase
from SenderFirebase import SenderFirebase
from SerialCommunication import CanSerial
from SchematicInfo import SchematicInfo as Schematic
import time


class FirebaseCommunication:
    bak = 1
    receiver = ReceiverFirebase()
    sender = SenderFirebase()
    serial = CanSerial("/dev/ttyACM0")
    currentValues = None
    currentSchematics = None
    desiredValuesSet = {}

    def __init__(self):
        self.currentValues = list(self.receiver.get_all())
        self.currentSchematics = self.receiver.get_schematics()
        self.desiredValuesSet[1] = True

    def poll_schematic_update(self):
        while(1):
            print("Polling")
            temp = list(self.receiver.get_all())
            tempSchematics = self.receiver.get_schematics()
            print(self.desiredValuesSet)
            for i in range(0, temp.__len__()):
                if isinstance(temp[i], dict):
                    newValue = temp[i]
                    try:
                        oldValue = self.currentValues[i]
                    except IndexError:
                        oldValue = {}
                    if newValue[Schematic.schematic] != oldValue[Schematic.schematic] \
                            or tempSchematics != self.currentSchematics\
                            or (i in self.desiredValuesSet and self.desiredValuesSet[i] is not None):
                        print("Ready to send.")
                        schematic = temp[i][Schematic.schematic]
                        print(schematic)
                        schematicValues = self.receiver.get_schematic(schematic)
                        self.currentSchematics = tempSchematics
                        if schematicValues is None:
                            print("Unkown Schematic")
                            self.sender.post_unkown_schematic(i, schematicValues)
                        else:
                            print("Uploading")
                            self.currentValues = list(self.receiver.get_all())
                            self.upload_schematics(i, schematicValues)
                elif temp[i] is not None:
                    self.add_new_biosphere(i)
                self.desiredValuesSet[i] = None
            time.sleep(5)

    def update_current_values(self):
        while True:
            try:
                msg = self.serial.read()
                if msg is not None:
                    print("Received:")
                    print("ID: " + msg[0] + " Data: " + msg[1])
                    if msg[1].__contains__("-1"):
                        print("Schematic request")
                        data = int(msg[0])
                        biosphereNumber = (data & 0b11111100) >> 2
                        print(biosphereNumber)
                        self.desiredValuesSet[biosphereNumber] = True
                    else:
                        data = int(msg[0])
                        controllerType = data & 0b11
                        biosphereNumber = (data & 0b11111100) >> 2
                        value = (self.switch(controllerType), float(msg[1][:msg[1].index('\x00')]))
                        print(value)
                        self.sender.post(biosphereNumber, value)
            except ValueError:
                pass

    def add_new_biosphere(self, ID):
        self.sender.post(ID, None)

    def switch(self, x):
        return {
            0: "Pi",
            1: "temperature",
            2: "lux",
            3: "groundMoisture"
        }.get(x, 0)

    def upload_schematics(self, id, values):
        try:
            print(str(values["temperature"]))
            print(str(values["lux"]))
            print(str(values["groundMoisture"]))
        except KeyError:
            return
        id = self.bak << 2
        time.sleep(1)
        self.serial.write(id=id + 1, message=str(values["temperature"]))
        time.sleep(1)
        self.serial.write(id=id + 2, message=str(values["lux"]))
        time.sleep(1)
        self.serial.write(id=id + 3, message=str(values["groundMoisture"]))
        time.sleep(1)
