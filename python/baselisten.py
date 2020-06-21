from controller import *
import threading
import time
import argparse


""" Initialise Globals """
ps4 = PS4Controller()
ps4.init()
args = None


def controller_thread():
    """Listens and updates self based on controller event"""
    global ps4
    ps4.listen()



def update_transmit_info():
    """Update transmit string"""
    global ps4
    # Button Data
    byte0 = 0
    for i in range(6):
        byte0 |= (ps4.button_data[i] << (7-i))

    # Axis Data
    ## L2
    byte1 = 0 
    try:
        L2val = math.floor(ps4.axis_data[L2]*100)
        if (ps4.axis_data[L2] < 0 ):
            byte1 |= 1 << BYTE_SIZE-1
            L2val *= -1
        byte1 |= int(L2val)

    except KeyError:
        pass

    ## R2
    byte2 = 0
    try:
        R2val = math.floor(ps4.axis_data[R2]*100)
        if (ps4.axis_data[R2] < 0 ):
            byte2 |= 1 << BYTE_SIZE-1
            R2val *= -1
        byte2 |= R2val
        
    except KeyError:
        pass

    ## Left Analog Stick X
    byte3 = 0
    try:
        LXval = math.floor(ps4.axis_data[LX]*100)
        if (ps4.axis_data[LX] < 0 ):
            byte3 |= 1 << BYTE_SIZE-1
            LXval *= -1
        byte3 |= int(LXval)

    except KeyError:
        pass

    ## LY
    byte4 = 0
    try:
        LYval = -(math.floor(ps4.axis_data[LY]*100))
        if (LYval < 0 ):
            byte4 |= 1 << BYTE_SIZE-1
            LYval *= -1
        byte4 |= int(LYval)

    except KeyError:
        pass

    ## RX
    byte5 = 0
    try:
        RXval = math.floor(ps4.axis_data[RX]*100)
        if (ps4.axis_data[RX] < 0 ):
            byte5 |= 1 << BYTE_SIZE-1
            RXval *= -1
        byte5 |= int(RXval)

    except KeyError:
        pass

    ## RY
    byte6 = 0
    try:
        RYval = -1 * (math.floor(ps4.axis_data[RY]*100))
        if (RYval < 0 ):
            byte6 |= 1 << BYTE_SIZE-1
            RYval *= -1
        byte6 |= int(RYval)

    except KeyError:
        pass

    ps4.tx_data = {0: byte0, 1: byte1, 2: byte2, 3: byte3, 
                4: byte4, 5: byte5, 6: byte6}
    

def tx_thread():
    """Transmit over serial"""
    global ps4, args
    comms = serial.Serial(args.serial_port, 115200)
    while True:
        update_transmit_info();

        comms.write(0xFE.to_bytes(1, 'big')) # Preamble

        os.system('clear') # Stops text flooding screen
        for key in ps4.tx_data:
            comms.write(ps4.tx_data[key].to_bytes(1, 'big'))
            print((ps4.tx_data[key] & 0b01111111), end="-")
            time.sleep(0.000001)
        print("|")

        comms.write(0xFF.to_bytes(1, 'big')) # Postamble

    

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Controller Input Parser for METR4810 Logistics Tycoon')
    parser.add_argument('--serial', '-s', dest='serial_port', type=str, default="/dev/ttyACM0", help='Serial device to connect to')

    args = parser.parse_args()

    thread_controller = threading.Thread(target=controller_thread)
    thread_tx = threading.Thread(target=tx_thread)

    thread_controller.start()
    thread_tx.start()
