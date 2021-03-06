from firebase import firebase
import json


class ReceiverFirebase:

    fireURL = 'https://biosphere-47e94.firebaseio.com/'
    fb = None

    def __init__(self):
        self.fb = firebase.FirebaseApplication(self.fireURL, None)

    def get_all(self):
        res = self.fb.get('/Biosphere/', None)
        return res

    def get(self, ID):
        res = self.fb.get('/Biosphere/' + str(ID), None)
        return res

    def get_schematic(self, schematicname):
        res = None
        try:
            res = self.fb.get('/Schematics/' + schematicname, None)["values"]
        except:
            pass
        return res

    def get_schematics(self):
        res = self.fb.get('/Schematics/', None)
        return res
