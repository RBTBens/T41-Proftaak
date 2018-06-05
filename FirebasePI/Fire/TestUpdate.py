from threading import Thread
from FirebaseCommunication import FirebaseCommunication
from SenderFirebase import SenderFirebase

communication = FirebaseCommunication()

# pollSchematicThread = Thread(target=communication.poll_schematic_update)
# pollSchematicThread.start()

updateValuesThread = Thread(target=communication.update_current_values)
updateValuesThread.start()
