# Data Display / Record in Terminal - this only applies to the Arduino Prototype Setup
## Display Data
1. Open Terminal
2. enter `screen /dev/tty.<usbdevice> <baudrate>`
3. Data is now displayed on the terminal

## Record Data with the Terminal
1. Open terminal
2. enter `script -a -t 0 <path_to_file_and_file_to_create.txt> screen /dev/tty.<usbdevice> <baudrate>`
3. Data is now recorded into the set path location
