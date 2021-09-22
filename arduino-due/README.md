# Getting Started with the Arduino-Due Benchmark

## Introduction
This tutorial includes step-by-step information about how to get started with the `arduino-due` benchmark, including both setting up the boards and demonstrating the attacks.

For this benchmark, there are two versions of boards (as shown below): the  `malicious` version and the `reference` version. The `reference` version uses the exact same schematic design of the original [Arduino Due board](https://store.arduino.cc/usa/due). 
Note that we slightly modify the layout of the original design to ease inserting the Trojans and implementing the attacks. The `malicious` version is the same as the `reference` version (both schematic and layout) except the inserted malicious circuit, which means once the malicious circuits and related routings are removed, the `malicious` version board will be completely the same as the `reference` version board.

In this benchmark we implement three malicious attacks (as shown above):
1. A malicious MOSFET is connected to the UART transmitter to leak information through LED (subfigure c);
2. The maliciously programmed ATtiny microcontroller monitors the UART and generates Flash erase signal when triggered (subfigure d); 
3. Two XOR logic chips output a signal to reset the board once triggered (subfigure e).

## Initialize the boards
### Install the firmware of the Arduino Due programming port
#### Use the Atmel programmer to install the firmware:
1. Follow the instruction of https://www.arduino.cc/en/Hacking/DFUProgramming8U2


2. For the firmware files, the `hex` files can be found in
https://github.com/arduino/ArduinoCore-sam/tree/master/firmwares/atmega16u2

3. After programming the flash, you will see the programming port of the Arduino Due board in your Device manager.
![Alt text](./1603210029998.png)

### Test the functionality of the boards
1. Install the Arduino SAM Boards (32-bits ARM Cortex M3) from the tools->board->boards manager.
#### Program through the Programming Port
1. Connect the Programming Port.
2. Upload and Run the `Blink` example.

#### Program through the Native USB Port

1. Connect the native USB port.
2. Program directly using the native USB port, upload and Run the `Blink` example.

## Demonstrate the attacks
### 1. Malicious MOSFET
**Goal:**<br> A malicious MOSFET is connected to the UART transmit pin to leak information through LED.

**Configuration:**<br> In this demonstration, the datapath is as follows:
User input into the reference board's Serial Monitor is sent directly to the Serial1 port on the victim board. This Serial1 port (on the victim board) is directly connected to the LED that is used to leak the data. Once the victim board receives data from the reference board, it mirrors the characters back over the same Serial1 port to be leaked through the LED. The data is also mirrored to the SerialUSB port which will display on the victim board's Serial Monitor if connected.

**Demonstration:**<br>

1. Connect Pins

| Reference Board | <------------> | Victim Board |
| ----------- | ----------- | ----------- |
| Serial1 TX (18) | <------------> | Serial1 RX (19) |
| Serial1 RX (19) | <------------> | Serial1 TX (18) |
| GND | <------------> | GND |

2. Upload Source Code

* Attach the victim board via USB and upload the following [source code](attacks/malicious_MOSFET/victim_board_src/victim_board_src.ino)
* Attach the reference board via USB and upload the following [source code](attacks/malicious_MOSFET/reference_board_src/reference_board_src.ino)

3. Testing

* Connect the reference board via USB
* Open the Serial Monitor (this is accessed by clicking the plus button in the top right corner on the Arduino IDE)
* Click the hardware reset button (located next to the USB port) on the reference board
* Wait 5 seconds for the board to initialize until you see an information printout
* Try entering various characters into the Serial Monitor
* Take note of the LED blinking on the victim board whenever characters are sent via the reference board
* To confirm that characters are being sent, connect the reference board via USB and open another Serial Monitor to track the mirrored characters being sent from the reference board

**Vulnerability:**<br> The flashing of the LED corresponds to the 1's and 0's of the ASCII being transmitted through UART. This data could be sensed and decoded by another system to monitor sensitive UART data packets.


### 2. Malicious ATtiny
**Goal:**<br> A maliciously programmed ATtiny microcontroller monitors the UART and generates a Flash erase signal when triggered.

**Generalized Configuration:**<br> In this demonstration, the datapath is as follows:
User input into the reference board's Serial Monitor is sent directly to the Serial2 port on the victim board. This Serial2 port (on the victim board) is directly monitored by the malicious ATtiny. Once the trigger word is inputted by the user and subsequently read by the ATtiny, the ATtiny triggers a master reset of the victim board's flash memory. Throughout this process, the victim board's LED will continuously blink to show that it is still functional and has not yet been attacked. Once it is attacked, the LED will stop blinking and the board will have to be re-flashed before it can perform another test.

**Technical Configuration:**<br>
* The ATtiny102 constantly monitors the victim board's UART RX pin at 4800 baud
    * This connection configuration is undetectable by the victim board itself or any reference boards
* A reference board is used to connect to the Serial 2 UART Port of the victim board (TX-16 RX-17)
    * The reference board can trigger the ATtiny102 to erase the flash of the victim board by sending the command "ATTACK"
* A 6-character buffer array is maintined on the ATtiny102 to keep track of incoming UART characters
    * Each time a new character is read, it is placed at the end of the array
    * Subsequently, all remaining characters are shifted one index to the left in the array
    * This process discards the oldest (leftmost) character
* Once the buffer array contains the string "ATTACK" the ERASE sequence is triggered:
    * The ATtiny102 pulls the ERASE pin of the victim board LOW for 2 seconds to erase the FLASH
    * At this point, the victim board is in a paralyzed state and the ATtiny102 resumes normal listening operation

**Demonstration:**
1. Connect Pins

| Reference Board | <------------> | Victim Board |
| ----------- | ----------- | ----------- |
| Serial2 TX (16) | <------------> | Serial1 RX (17) |
| Serial1 RX (17) | <------------> | Serial1 TX (16) |
| GND | <------------> | GND |

2. Upload Source Code

* Attach the victim board via USB and upload the following [source code](attacks/malicious_ATtiny/victim_board_src/victim_board_src.ino)
* Attach the reference board via USB and upload the following [source code](attacks/malicious_ATtiny/reference_board_src/reference_board_src.ino)
* If the ATtiny needs to be flashed, use Atmel/Microchip Studio to upload the following [source code](attacks/malicious_ATtiny/ATtiny_src)

3. Testing

* Connect the reference board via USB
* Open the Serial Monitor (this is accessed by clicking the plus button in the top right corner on the Arduino IDE)
* Click the hardware reset button (located next to the USB port) on the reference board
* Wait 5 seconds for the board to initialize until you see an information printout
* Try entering various characters (not the trigger word) into the Serial Monitor
* Take note of the LED blinking on the victim board which signifies that it has not yet been attacked
* Enter the trigger word into the Serial Monitor
* Confirm that the attack was successful be ensuring that the victim board's LED stopped blinking

**Vulnerability:**<br> The ATtiny can erase the Flash of the victim board, rendering it useless, if the trigger command is sent to the victim board over UART.

### 3. Malicious XORs
**Goal:**<br> Two XOR logic chips output a signal to reset the victim board's Flash once triggered.

**Generalized Configuration:**<br> In this demonstration, the datapath is as follows:
User input into the reference board's Serial Monitor is monitored internally by the reference board. Once the trigger word is inputted by the user, a sequence of code executes that triggers a flash reset on the victim board. This is accomplished by setting pins 44, 45, and 46 on the victim board to a specific sequence of logic levels that trigger the flash reset. Throughout this process, the victim board's LED will continuously blink to show that it is still functional and has not yet been attacked. Once it is attacked, the LED will stop blinking and the board will have to be re-flashed before it can perform another test.

**Technical Configuration:**<br>
* The XOR chips have pins 44, 45, 46 from the victim board as inputs. In the default state, these pins are logical level HIGH so as to not trigger the Flash reset.
* The following truth table represents the various logic level inputs to the victim board and what output they trigger

| Pin 44      | Pin 45      | Pin 46      | Flash Reset |
| ----------- | ----------- | ----------- | -----------  |
|0|0|0|NO|
|0|0|1|<mark>YES<mark>|
|0|1|0|<mark>YES<mark>|
|0|1|1|NO|
|1|0|0|<mark>YES<mark>|
|1|0|1|NO|
|1|1|0|NO|
|1|1|1|<mark>YES<mark>|

**Demonstration:**
1. Connect Pins

| Reference Board | <------------> | Victim Board |
| ----------- | ----------- | ----------- |
| D10 | <------------> | D44 |
| D11 | <------------> | D45 |
| D12 | <------------> | D46 |
| GND | <------------> | GND |

2. Upload Source Code

* Attach the victim board via USB and upload the following [source code](attacks/malicious_ATtiny/victim_board_src/victim_board_src.ino)
* Attach the reference board via USB and upload the following [source code](attacks/malicious_ATtiny/reference_board_src/reference_board_src.ino)

3. Testing

* Connect the reference board via USB
* Open the Serial Monitor (this is accessed by clicking the plus button in the top right corner on the Arduino IDE)
* Click the hardware reset button (located next to the USB port) on the reference board
* Wait 5 seconds for the board to initialize until you see an information printout
* Try entering various characters (not the trigger word) into the Serial Monitor
* Take note of the LED blinking on the victim board which signifies that it has not yet been attacked
* Enter the trigger word into the Serial Monitor
* Confirm that the attack was successful be ensuring that the victim board's LED stopped blinking

**Vulnerability:**<br> An external board can change the state of these input pins which would trigger a Flash reset of the victim board, rendering is useless.


## Developer Notes
* For an 8MHz internal clock on the ATtiny102, the prescaler sets the clock in the code to 1MHz
    * 1 MHz is not considered fast enough to communicated over UART at 9600 baud becuase data becomes corrupted
    * 4800 is the maximum clean baud rate for this internal clock
* ATtiny102 TX trace should be removed in final design
* Use other, non-programming pin, for the resetting functionality on the ATtiny102 (recommend PB1/Pin 5)
* The programming port on the test boards does not work due to a an error in the original Arduino Due design documentation

## References
1. Pinout of the Arduino Due Board: https://content.arduino.cc/assets/Pinout-Due_latest.pdf
