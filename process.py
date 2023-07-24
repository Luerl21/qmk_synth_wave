import win32gui
import psutil
import win32process
import sys
import hid

def get_active_window_process():
    window = win32gui.GetForegroundWindow()
    _, pid = win32process.GetWindowThreadProcessId(window)
    for proc in psutil.process_iter():
        if proc.pid == pid:
            return proc.name()

vid = 0x0002
pid = 0x4148
usage_page = 0xFF60
usage      = 0x61

def get_raw_hid_interface():
    device_interfaces = hid.enumerate(vid, pid)
    raw_hid_interfaces = [i for i in device_interfaces if i['usage_page'] == usage_page and i['usage'] == usage]

    if len(raw_hid_interfaces) == 0:
        return None

    interface = hid.Device(path=raw_hid_interfaces[0]['path'])

    print("Manufacturer: %s" % interface.manufacturer)
    print("Product: %s" % interface.product)

    return interface

def send_raw_packet(data):
    interface = get_raw_hid_interface()

    if interface is None:
        print("No device found")
        sys.exit(1)

    request_data = [0x00] * 33 # First byte is Report ID
    request_data[1:len(data) + 1] = data
    request_packet = bytes(request_data)

    print("Request:")
    print(request_packet)

    try:
        interface.write(request_packet)

        response_packet = interface.read(32, timeout=1000)

        print("Response:")
        print(response_packet)
    finally:
        interface.close()

def word_to_hex(word):
    hex_list = [ord(char) for char in word]
    return hex_list

if __name__ == '__main__':
    datalast = ""
    while True:
        active_process = get_active_window_process()
        datas = str(active_process.split(".exe")[0])
        hex_representation = word_to_hex(datas)
        if datas != datalast and datas != "explorer":
            send_raw_packet(hex_representation)