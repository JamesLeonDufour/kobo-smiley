# Kobo Smiley
Kobo Smiley is a DIY affordable, user-friendly feedback terminal built around the ESP8266 microcontroller, designed to work seamlessly with Kobo Toolbox https://www.kobotoolbox.org/ . This project provides a cost-effective solution (under $5 USD) for collecting feedback and survey responses with minimal hassle.

![WhatsApp Image 2023-11-03 at 9 47 36 PM](https://github.com/JamesLeonDufour/kobo-smiley/assets/6214012/519b8b87-c7cd-4be1-94af-86395e9f9925)


## Overview
The Kobo Smiley terminal is a versatile feedback collection device. It powers up as an Access Point, allowing easy configuration via a captive portal. After setup, it can securely transmit data directly to the Kobo Toolbox API, making it an ideal choice for organizations and individuals looking to conduct surveys, gather feedback, or collect data.

## Key Links
ESP8266 - Learn more about the ESP8266 microcontroller.
Arduino - Visit the official Arduino website for additional information.


## Workflow
1. Create a Kobo Form: Start by creating a new questionnaire or form on the Kobo Toolbox platform.
2. Configure Kobo Smiley:
- Power up the Kobo Smiley terminal, which will function as an Access Point.
- Connect to the terminal's Wi-Fi network.
- Configure the terminal's Wi-Fi settings.
- Input the necessary Kobo details, such as API keys or form identifiers.
3. Reboot and Start Collecting Data:
- The Kobo Smiley terminal will automatically reboot with the updated settings.
- It will connect to the configured Wi-Fi network and become ready to use, enabling the collection of feedback and data.

## Materials (Estimated Cost: $5 USD)

To build your Kobo Smiley feedback terminal, you'll need the following components:

- ESP8266 Microcontroller (ESP32 code to be develloped) - Approximately $1.5 USD
- Buttons, Resistors, Cables, and LEDs - Around $2 USD
- 3D-Printed Casing (under development) - Estimated cost of $1.5 USD

### to do
- add electronic schematic 
- add image first mockup
- 3D case

### Further development

- custom PCB integrating board and circuitery
- esp32 code
- detailled instruction
- add image
- add lora capabilities for long distance transmission
- Solar Powered option
  
