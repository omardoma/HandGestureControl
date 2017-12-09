import time  # Required to use delay functions
import serial  # Serial imported for Serial communication
import pyautogui

# Create Serial port object called arduinoSerialData
ArduinoSerial = serial.Serial('/dev/cu.usbmodem1411', 9600)
time.sleep(2)  # wait for 2 seconds for the communication to get established

while 1:
    # read the serial data and print it as line
    incoming = str(ArduinoSerial.readline())
    print incoming

    if 'Play/Pause' in incoming:
        pyautogui.typewrite(['space'], 0.2)

    if 'Rewind' in incoming:
        pyautogui.hotkey('cmd', 'left')

    if 'Forward' in incoming:
        pyautogui.hotkey('cmd', 'right')

    if 'Vup' in incoming:
        pyautogui.hotkey('cmd', 'down')

    if 'Vdown' in incoming:
        pyautogui.hotkey('cmd', 'up')

    incoming = ""
