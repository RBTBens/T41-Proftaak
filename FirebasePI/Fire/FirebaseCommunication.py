from ReceiverFirebase import ReceiverFirebase
from SenderFirebase import SenderFirebase
import json

receiver = ReceiverFirebase()

print(receiver.get_all())

print(receiver.get(1))

sender = SenderFirebase()

sender.post(4, {'Days':1,'Temp':1,'Gm':1,'Hum':1})
