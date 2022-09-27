## Changes in the PCBA
The PCBA contains some minor errors, which are indicated here. If you want to reproduce the PCBA, please make sure: 
- to reverse the polarity of C5. The (-) indicator on the Silkscreen is placed on the wrong pad. Please check the Nets in the PCBA File. The (-)-Pin of C5 needs to be connected to GND.
- to keep R3 unsoldered. This constantly pulls down the BOOT Pin of the Microcontroller.