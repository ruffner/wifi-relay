# wifi-relay
custom firmware and qt interface for the cheap esp8266 based [WIFI Relay Module](https://www.amazon.com/ATIMOSOS-ESP8266-module-Things-control/dp/B073TVR3QT/ref=sr_1_8?s=industrial&ie=UTF8&qid=1521219507&sr=1-8&keywords=esp8266+relay)

<img width="400" src="doc/images/enclosure.jpg"/>

## Hardware Setup
#### Arduino IDE configuration

If not already done, the ESP8266 addon package needs to be added to the Arduino IDE. Sparkfun has a good [guide](https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/installing-the-esp8266-arduino-addon) for this.

#### Prepare ESP8266 for upload

In order up upload the custom WiFi Relay firmware to the ESP8266, GPIO0 must be held low while the RESET pin rises from low to high.

The schematic from [this](https://www.allaboutcircuits.com/projects/update-the-firmware-in-your-esp8266-wi-fi-module/) site shows a two button setup to put the ESP8266 in this bootloading state. This needs to be done before each upload.

A USB to serial converter needs to be connected to the TX/RX pins broken out on the side of the relay module, as well as ground.

#### Upload

Set the access point name and password of your choosing in the sketch, then upload. Thats it!

## Software Setup
#### Install Qt 
Needs `CONFIG += network` in `.pro` file.
#### Use `TCPRelayWidget`
The following slots are available for controlling the relay over WiFi
- `void onSetRelayState(bool state)`
- `void onSetRelayOn()`
- `void onSetRelayOff()`

The following signals are provided to inform the user of the relay's status
- `void emitRelayError(QString)`
- `void emitRelayState(bool)`
- `void emitDeviceVerified(bool)`

## Enclosure
There is a two part enclosure that fits around the module, the STL files are available in the enclosure folder.
