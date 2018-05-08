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
        try:
            values["ActiveSchematic"] = result["ActiveSchematic"]
        except TypeError:
            values["ActiveSchematic"] = "De standaard (besjes)"
        res = self.fb.put('/Biosphere', str(ID), values)
        print(res)