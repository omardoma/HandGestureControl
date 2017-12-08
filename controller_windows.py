import time  # Required to use delay functions
import serial  # Serial imported for Serial communication
import pyautogui

# Create Serial port object called arduinoSerialData
ArduinoSerial = serial.Serial('com4', 9600)
time.sleep(2)  # wait for 2 seconds for the communication to get established

while 1:
    # read the serial data and print it as line
    print('ana running')
    incoming = str(ArduinoSerial.readline())
    print incoming

    if 'Play/Pause' in incoming:
        pyautogui.typewrite(['space'], 0.2)

    if 'Rewind' in incoming:
        pyautogui.hotkey('ctrl', 'left')

    if 'Forward' in incoming:
        pyautogui.hotkey('ctrl', 'right')

    if 'Vup' in incoming:
        pyautogui.hotkey('ctrl', 'down')

    if 'Vdown' in incoming:
        pyautogui.hotkey('ctrl', 'up')

    incoming = ""
