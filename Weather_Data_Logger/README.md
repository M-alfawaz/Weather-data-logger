# Weather Data Logger 🌦️

## Project Overview
An **Arduino-based weather data logger** that records temperature and humidity using a **DHT11 sensor** and timestamps each reading with a **DS3231 Real-Time Clock (RTC)**.  
The system logs measurements every 15 minutes to the serial monitor, which can be saved to a text file using **CoolTerm** or a Python script.

## Components Used
- Arduino Uno R3
- DHT11 Temperature & Humidity Sensor
- DS3231 RTC Module
- Breadboard & Jumper wires

## Features
- Real-time temperature and humidity monitoring
- Accurate timekeeping with DS3231 RTC
- Logs data every 15 minutes (0, 15, 30, 45)
- Serial output for PC logging with CoolTerm or Python

## How to Run
1. Open `src/weather_logger.ino` in Arduino IDE.
2. Install libraries: `Wire.h`, `DS3231.h`, `SimpleDHT.h`.
3. Upload the code to Arduino Uno.
4. Run CoolTerm or the included Python script to capture logs.

## Documentation
Full project report is available in [`docs/Weather_Data_Logger.pdf`](docs/Weather_Data_Logger.pdf).
