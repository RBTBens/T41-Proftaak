from ReceiverFirebase import ReceiverFirebase
from SenderFirebase import SenderFirebase
import json
import time


class FirebaseCommunication:
    receiver = ReceiverFirebase()
    sender = SenderFirebase()
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
                    except IndexError:
                        #TODO Alsnog posten via serial want is out of bounds geweest
                        #serial.post(key)
                        print(key)
                    i = i + 1
                self.currentValues = temp
            else:
                print("Nothing new")


    def update_current_values(self, ID, values):
        #TODO serial data binnen krijgen
        self.sender.post(ID, values)

