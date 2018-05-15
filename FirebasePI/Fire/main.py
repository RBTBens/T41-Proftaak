from threading import Thread
from FirebaseCommunication import FirebaseCommunication

communication = FirebaseCommunication()

pollSchematicThread = Thread(target=communication.poll_schematic_update)
pollSchematicThread.start()

communication.update_current_values(21, {'Days': 8, 'Temp': 21, 'Gm': 80000, 'Hum': 5})
