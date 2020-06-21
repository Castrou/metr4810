from controller import *
import threading
import time
import argparse

ps4 = PS4Controller()
ps4.init()

args = None

def controller_thread():
    global ps4
    ps4.listen()

def update_transmit_info():
    global ps4
    # Button Data
    byte0 = 0
    for i in range(6):
        byte0 |= (ps4.button_data[i] << (7-i))

    # Axis Data
    ## L2
    byte1 = 0 
    try:
        # print("L2: " + str(self.axis_data[L2]))
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
        # print("R2Val: " + str(R2val))
        if (ps4.axis_data[R2] < 0 ):
            byte2 |= 1 << BYTE_SIZE-1
            R2val *= -1
        byte2 |= R2val
        
    except KeyError:
        pass

    ## Left Analog Stick X
    byte3 = 0
    try:
        # print("LX: " + str(self.axis_data[LX]))
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
        # print("LY: " + str(self.axis_data[LY]))
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
        # print("RX: " + str(self.axis_data[RX]))
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
        # print("RY: " + str(self.axis_data[RY]))
        RYval = -1 * (math.floor(ps4.axis_data[RY]*100))
        if (RYval < 0 ):
            byte6 |= 1 << BYTE_SIZE-1
            RYval *= -1
        byte6 |= int(RYval)

    except KeyError:
        pass

    # ps4.tx_data = (byte0 << 0) | (byte1 << 1*BYTE_SIZE) | (byte2 << 2*BYTE_SIZE) | \
    #             (byte3 << 3*BYTE_SIZE) | (byte4 << 4*BYTE_SIZE) | \
    #             (byte5 << 5*BYTE_SIZE) | (byte6 << 6*BYTE_SIZE)

    # print("{0:b}".format(ps4.tx_data))

    ps4.tx_data = {0: byte0, 1: byte1, 2: byte2, 3: byte3, 
                4: byte4, 5: byte5, 6: byte6}
    

def tx_thread():
    global ps4, args
    comms = serial.Serial(args.serial_port, 115200)
    while True:
        update_transmit_info();
        comms.write(0xFE.to_bytes(1, 'big'))
        os.system('clear')
        for key in ps4.tx_data:
            comms.write(ps4.tx_data[key].to_bytes(1, 'big'))
            print("{0:b}".format(ps4.tx_data[key]), end="-")
            time.sleep(0.000001)
        print("|")
        comms.write(0xFF.to_bytes(1, 'big'))

    

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Controller Input Parser for METR4810 Logistics Tycoon')
    parser.add_argument('--serial', '-s', dest='serial_port', type=str, default="/dev/ttyACM0", help='Serial device to connect to')

    args = parser.parse_args()

    thread_controller = threading.Thread(target=controller_thread)
    thread_tx = threading.Thread(target=tx_thread)

    thread_controller.start()
    thread_tx.start()
