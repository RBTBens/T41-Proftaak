from ReceiverFirebase import ReceiverFirebase
from SenderFirebase import SenderFirebase
import json
import time
from SerialCommunication import CanSerial


class FirebaseCommunication:
    bak = 1
    receiver = ReceiverFirebase()
    sender = SenderFirebase()

    #serial = CanSerial("/dev/ttyACM0")
    serial = CanSerial("COM10")

    currentValues = None

    def __init__(self):
        self.currentValues = self.receiver.get_all()

    def poll_schematic_update(self):
        while(1):
            time.sleep(5)
            temp = self.receiver.get_all()
            i = 0
            if temp != self.currentValues:
                for key in temp:

                    print(key)
                    try:
                        if key is None:
                            pass
                        else:
                            if key != self.currentValues[i]:
                                print(key)
                                #TODO Serial post new schematic
                                #serial.post(key)

                                self.serial.write(id=self.bak, message=key)
                                time.sleep(1)
                    except IndexError:
                        #TODO Alsnog posten via serial want is out of bounds geweest
                        #serial.post(key)
                        self.serial.write(id=self.bak, message=key)
                        time.sleep(1)
                        print(key)
                    i = i + 1
                self.currentValues = temp
            else:
                print("Nothing new")

    def update_current_values(self):
        while True:
            msg = self.serial.read()
            print("ahhasodijfoaisjtueu")
            if msg is not None:
                print("")
                print("Received:")
                print("ID: " + msg[0] + " Data: " + msg[1])
                print("")
                data = int(msg[0])
                controllerType = data & 0b11
                biosphereNumber = (data & 0b11111100) >> 2
                print(controllerType)
                print('\n')
                print(biosphereNumber)
                print('\n')
                value = "{'" + self.switch(controllerType) + "':" + msg[0] + "}"
                self.sender.post(biosphereNumber, value)

    def switch(self, x):
        return {
            0: "Pi",
            1: "temperature",
            2: "lux",
            3: "groundMoisture"
        }.get(x, 0)