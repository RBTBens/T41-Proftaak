from threading import Thread
from FirebaseCommunication import FirebaseCommunication
from SenderFirebase import SenderFirebase

communication = FirebaseCommunication()

communication.poll_schematic_update()