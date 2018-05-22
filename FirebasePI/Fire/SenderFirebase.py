from firebase import firebase
from ReceiverFirebase import ReceiverFirebase
import json


class SenderFirebase:
    fireURL = 'https://biosphere-47e94.firebaseio.com/'
    fb = None
    receiver = ReceiverFirebase()

    def __init__(self):
        self.fb = firebase.FirebaseApplication(self.fireURL, None)

    def post(self, ID, values):
        result = self.receiver.get(ID)
        temp = {"ActiveSchematic" : 1}
        try:
            temp["ActiveSchematic"] = result["ActiveSchematic"]
        except KeyError:
            temp["ActiveSchematic"] = "bessen"
        self.fb.put('/Biosphere/', str(ID), temp)
        res = self.fb.put('/Biosphere/' + str(ID), "CurrentValues", values)
        print(res)