## Overview
This repo contains a design for a PCB that holds an ATMEGA microcontroller and corresponding interfaces that would be useful to control an amplifier. Some possible uses:

* Convert a surround-sound receiver into a multi-channel amplifier by removing everything except the power amplifier section and power supply. Use the outputs from this controller board to drive the power supply switching relay and any speaker protection relays. Use the inputs on this controller to interface with a thermal sensor (like the LM61CIZ used in an Onkyo TX-SR705) and a trigger input to turn on the amplifier. The ATMEGA can be programmed to drive LEDs indicating the amplifier's state, and apply delays to protect the system during startup.
* Build your own power amplifier that includes thermal management, trigger inputs/outputs, and delayed relay firing at startup for protection circuits.

Some things you'll find in the repo:
* DipTrace schematic files and PCB layouts
* PCB gerbers (both for the crossover circuit PCB and a corresponding dual-rail power supply)
* Code for the ATMega
* Pictures of the results


## Isaac's DIY Project

This is simply a DIY project under work by Isaac Dooley. I am no expert in these matters, but hopefully this thing will work fine.