#

import serial
import time


def test_led_strip():
    t = serial.Serial('/dev/ttyUSB0', 9600, timeout=2)
    for i in range(184):
        send_data = ("%03d" % (i)) + chr(0x5) + chr(0x0) + chr(0x0) + chr(0xfe)
        print(send_data)
        t.write(send_data)
        time.sleep(0.02)

    for i in range(184):
        send_data = ("%03d" % (184 - i)) + chr(0x0) + chr(0x5) + chr(0x0) + chr(0xfe)
        print(send_data)
        t.write(send_data)
        time.sleep(0.02)

    for i in range(184):
        send_data = ("%03d" % (i)) + chr(0x0) + chr(0x0) + chr(0x5) + chr(0xfe)
        print(send_data)
        t.write(send_data)
        time.sleep(0.02)

    t.close()
    return


test_led_strip()

