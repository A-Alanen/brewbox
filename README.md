# brewbox
A DIY smart fermentation box for homebrewing, pickling, or fermenting foods, with automatic temperature control, fan ventilation, and RGB status lighting. Built using Arduino and basic electronic components.

## Table of Contents
- [Component List](#component-list)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)

## Component List
You will need the following parts to build the box:
- 1x **Arduino Uno** (or compatible board)
- 1x **12V Fan** (for ventilation)
- 1x **Potentiometer** (to adjust set temperature)
- 1x **RGB LED** (common cathode or anode, Arduino-compatible)
- 1x **Heating Mat** (wall-powered with a relay or switch)
- 1x **Insulated Container** (cooler, mini fridge, or foam box)
- 1x **12V Power Supply** (for the fan)
- 1x **2 Channel Relay Module** (to switch heating mat and fan on/off)
- Jumper wires, breadboard or soldered PCB
- Temperature sensor (e.g., **DHT22** or **DS18B20**)

## Installation
Follow these steps to set up the project locally:
1. **Clone the Repository**
   ```bash
   git clone https://github.com/your-username/ferment-cabinet.git
   cd ferment-cabinet
    ```

2. **Install Arduino IDE**
    Download from https://www.arduino.cc/en/software
    Install the correct USB driver for your Arduino board if necessary

3. **Open the Code**
    Launch Arduino IDE
    Open the .ino file inside the arduino_files folder

4. **Install Libraries (if needed)**
    Some sensors may require external libraries (e.g., Adafruit's DHT library)
    Use Library Manager in Arduino IDE (Sketch > Include Library > Manage Libraries...)

5. **Upload to Arduino**
    Connect your Arduino board via USB
    Select the correct board and port in the Arduino IDE
    Click Upload

## Usage
Once your hardware is set up and the code is uploaded:
    Turn the potentiometer to set the desired temperature threshold.
    The heating mat turns on automatically when the temperature drops below the threshold.
    The fan activates to circulate air as needed.
    The RGB LED indicates system status:
        Blue: Cooling
        Red: Heating
        Green: Stable (ideal temp reached)
Customize the RGB behavior or control logic in the Arduino code to fit your fermentation needs.
Place your fermenting container inside the insulated chamber and monitor the environment with optional temperature readouts.

## License
This project is licensed under the GNU General Public License v3.0.
You are free to use, modify, and distribute the code, but any derivative works must also be open source and licensed under GPLv3. See the full license text in the [LICENSE](https://www.gnu.org/licenses/gpl-3.0.en.html).