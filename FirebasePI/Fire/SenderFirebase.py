from firebase import firebase
from ReceiverFirebase import ReceiverFirebase
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
            current = self.receiver.get(ID)["CurrentValues"]
        except:
            current = {"CO2":1,"lux":1,"groundMoisture":1, "temperature":1}
        temp = {"ActiveSchematic":1}
        test = self.receiver.get(ID)
        temp["ActiveSchematic"] = "bessen"
        self.fb.put('/Biosphere/', str(ID), temp)
        try:
            current[values[0]] = values[1]
        except TypeError:
            pass
        res = self.fb.put('/Biosphere/' + str(ID), "CurrentValues", current)

    def post(self, ID, values):
        current = None
        try:
            current = self.receiver.get(ID)["CurrentValues"]
        except:
            current = {"CO2":1,"lux":1,"groundMoisture":1, "temperature":1}
        temp = {"ActiveSchematic":1}
        test = self.receiver.get(ID)
        try:
            temp["ActiveSchematic"] = test["ActiveSchematic"]
        except TypeError:
            temp["ActiveSchematic"] = "bessen"
        self.fb.put('/Biosphere/', str(ID), temp)
        try:
            current[values[0]] = values[1]
        except TypeError:
            pass
        res = self.fb.put('/Biosphere/' + str(ID), "CurrentValues", current)
        print(res)