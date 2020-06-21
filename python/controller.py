import os
import pprint
import pygame
import math
import serial


### Definitions 
BYTE_SIZE = 8

PAD = 0xFF

L2 = 2
R2 = 5
LX = 0
LY = 1
RX = 3
RY = 4
###

class PS4Controller(object):
    """Class representing the PS4 controller."""

    controller = None
    axis_data = None
    button_data = None
    # hat_data = None
    tx_data = None
    tx_state = 0

    def init(self):
        """Initialize the joystick components"""
        
        pygame.init()
        pygame.joystick.init()
        self.controller = pygame.joystick.Joystick(0)
        self.controller.init()

    def listen(self):
        """Listen for events to happen"""
        
        if not self.axis_data:
            self.axis_data = {}

        if not self.button_data:
            self.button_data = {}
            for i in range(self.controller.get_numbuttons()):
                self.button_data[i] = 0

        while True:
            for event in pygame.event.get():
                if event.type == pygame.JOYAXISMOTION:
                    self.axis_data[event.axis] = round(event.value,2)
                elif event.type == pygame.JOYBUTTONDOWN:
                    self.button_data[event.button] = 1
                elif event.type == pygame.JOYBUTTONUP:
                    self.button_data[event.button] = 0


if __name__ == "__main__":
    ps4 = PS4Controller()
    ps4.init()
    ps4.listen()
