import time

class CanSerial:
    # Imports
    serial = __import__('serial')
    time = __import__('time')

    # Variables
    ser = serial.Serial()
    msg_start = False
    msg_valid = False
    msg = ''

    # Constructor
    def __init__(self, port):
        self.ser.baudrate = 115200
        self.ser.port = port
        self.ser.timeout = 1
        self.ser.open()

    # Arduino reboots upon serial connection. Wait 5 seconds to startup
    # self.time.sleep(5)

    # Methods
    def write(self, id, message):
        msg = '#'
        msg += str(id)
        msg += ':'
        msg += message
        msg += ';'
        if self.ser.is_open:
            self.ser.write(msg.encode('utf-8'))

    def read(self):
        while self.ser.in_waiting > 0:
            incoming = self.ser.read(1)
            if incoming == '#':
                self.msg = ''
                self.msg_start = True
            elif incoming == ';':
                if self.msg_start:
                    self.msg_start = False
                    self.msg_valid = True
                    break
            elif self.msg_start:
                self.msg += incoming
        if self.msg_valid:
            self.msg_valid = False
            return self.msg.split(":")

    def close(self):
        self.ser.close()
# END CanSerial
