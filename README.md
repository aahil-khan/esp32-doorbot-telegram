# ESP32 Telegram Doorbell

A tiny DIY smart doorbell built using an ESP32, a push button, and the Telegram Bot API.  
Whenever someone presses the physical button, the ESP32 instantly sends a Telegram notification — making this a super simple, reliable, and fun IoT project.

## Features
- Sends Telegram notifications on button press
- Built-in cooldown to prevent spam
- LED indicator that mirrors button state
- WiFi auto-connect with status logs
- Battery-powered (3.7V Li-ion + charging module)

---

## Hardware Used
- **ESP32 Dev Board**
- **Push button (tactile or toggle)**
- **LED + Resistor (220Ω recommended)**
- **3.7V Li-ion battery**
- **TP4056 charging module**
- Jumper wires

---

## Telegram Setup

1. Open Telegram and search for **@BotFather**
2. Create a bot → copy the bot token
3. Start a chat with your bot
4. Use `https://api.telegram.org/bot<token>/getUpdates` to find your `chat_id`
5. Put both in the code

---

## Getting Started

1. Install VSCode or Arduino IDE
2. Install ESP32 board package
3. Flash the code
4. Connect to WiFi
5. Press the button → Receive Telegram notification instantly

---

## How It Works

1. Button is connected to GPIO14 (with internal pull-up).
2. When pressed (LOW), ESP32 triggers LED + sends HTTP request to Telegram API.
3. Cooldown prevents multiple messages from accidental long-presses.
4. Runs beautifully from a 3.7V Li-ion battery + TP4056 module.

---
## 📎 License

MIT — feel free to fork, use, and build upon it.
