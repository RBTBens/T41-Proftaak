from firebase import firebase
from ReceiverFirebase import ReceiverFirebase
from SchematicInfo import SchematicInfo as Schematic
import json


class SenderFirebase:
    fireURL = 'https://biosphere-47e94.firebaseio.com/'
    fb = None
    receiver = ReceiverFirebase()

    def __init__(self):
        self.fb = firebase.FirebaseApplication(self.fireURL, None)

    def post_unkown_schematic(self, ID, values):
        current = None
        try:
            current = self.receiver.get(ID)[Schematic.current]
        except:
            current = {Schematic.CO2:1,Schematic.lux:1,
                       Schematic.ground:1, Schematic.temp:1}
        temp = {Schematic.schematic:1}
        test = self.receiver.get(ID)
        temp[Schematic.schematic] = Schematic.mainSchematic
        self.fb.put('/Biosphere/', str(ID), temp)
        try:
            current[values[0]] = values[1]
        except TypeError:
            pass
        res = self.fb.put('/Biosphere/' + str(ID), Schematic.current, current)

    def post(self, ID, values):
        current = None
        try:
            current = self.receiver.get(ID)[Schematic.current]
        except:
            current = {Schematic.CO2:1,Schematic.lux:1,
                       Schematic.ground:1, Schematic.temp:1}
        temp = {Schematic.schematic:1}
        test = self.receiver.get(ID)
        try:
            temp[Schematic.schematic] = test[Schematic.schematic]
        except TypeError:
            temp[Schematic.schematic] = Schematic.mainSchematic
        self.fb.put('/Biosphere/', str(ID), temp)
        try:
            current[values[0]] = values[1]
        except TypeError:
            pass
        res = self.fb.put('/Biosphere/' + str(ID), Schematic.current, current)