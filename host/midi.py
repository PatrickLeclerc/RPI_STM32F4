#!/usr/bin/env python3
import argparse, time, platform
import rtmidi


################################################################
from enum import Enum
NOTEOFF = 0x8 # Note-Off
NOTEON  = 0x9 # Note-On
POLYP   = 0xA # Poly Key Pressure
CC      = 0xB # Control Change (0 - 119) 
PC      = 0xC # Program Change
CP      = 0xD # Channel Pressure
PB      = 0xE # Pitch Bend

#class MidiMSG(Enum):
#    NOTEOFF =  int(0x8),
#    NOTEON  =  int(0x9),
#    POLYP   =  int(0xA),
#    CC      =  int(0xB),
#    PC      =  int(0xC),
#    CP      =  int(0xD),
#    PB      =  int(0xE)

print("ok")
def MIDI_PROCESS(data):
    #Process MSG
    da = data[0] >> 4
    if(da == NOTEOFF or da == NOTEON ): 
        key = data[1]
        vel = data[2]
        if(da == NOTEOFF or (da == NOTEON and vel == 0)): print("NOTEOFF")
        if(da == NOTEON): print("NOTEON")
    if(da == POLYP ): print("POLYP  ")
    if(da == CC ): print("CC     ")
    if(da == PC ): print("PC     ")
    if(da == CP ): print("CP     ")
    if(da == PB ): print("PB     ")


################################################################

def midi_received(data, unused):
    msg, delta_time = data
    MIDI_PROCESS(msg)
    print(msg)
    
################################################################

if __name__ == "__main__":
    midi_in = rtmidi.MidiIn()
    for idx, name in enumerate(midi_in.get_ports()):
        if "M32" in name:
            print("%d: %s" % (idx, name))
            midi_in.open_port(idx)
            midi_in.set_callback(midi_received)
            break

    if midi_in.is_port_open():
        while True:
            time.sleep(1)