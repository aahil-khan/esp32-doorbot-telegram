#include <WiFi.h>
#include <HTTPClient.h>

// ------------------ WiFi Credentials ------------------
const char* ssid = "YOUR_WIFI_SSID_HERE";
const char* password = "YOUR_WIFI_PASSWORD_HERE";

// ------------------ Telegram Credentials ------------------
const char* botToken = "YOUR_BOT_TOKEN_HERE";
const char* chatID = "YOUR_CHAT_ID_HERE";

// ------------------ Hardware Pins ------------------
const int buttonPin = 14;   // Button wired to GPIO14
const int ledPin = 12;      // LED indicator on GPIO12

// ------------------ State Variables ------------------
bool lastButtonState = HIGH;          // Track previous button state
unsigned long lastSentTime = 0;       // Timer for cooldown
const unsigned long cooldown = 3000;  // Prevent duplicate messages (3s)

// ------------------ Send Message to Telegram ------------------
void sendTelegramMessage(const String& message) {
  HTTPClient http;

  // Construct API URL
  String url = "https://api.telegram.org/bot" + String(botToken) +
               "/sendMessage?chat_id=" + String(chatID) +
               "&text=" + message;

  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.println("Message sent to Telegram!");
  } else {
    Serial.printf("Telegram error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

// ------------------ Setup ------------------
void setup() {
  Serial.begin(9600);

  // Input button with internal pull-up
  pinMode(buttonPin, INPUT_PULLUP);

  // LED as output
  pinMode(ledPin, OUTPUT);

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 50) {
    Serial.print(".");
    delay(500);
    tries++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected! IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect to WiFi.");
  }
}

// ------------------ Main Loop ------------------
void loop() {
  // Read button (LOW = pressed because INPUT_PULLUP)
  int buttonState = digitalRead(buttonPin);

  // Mirror button state to LED (pressed → LED ON)
  digitalWrite(ledPin, !buttonState);

  // Detect button press edge (HIGH → LOW)
  if (lastButtonState == HIGH && buttonState == LOW) {
    Serial.println("Button pressed!");

    // Enforce cooldown so it doesn’t spam messages
    if (millis() - lastSentTime > cooldown) {
      sendTelegramMessage("🚪 Ding Dong! Someone is at your door.");
      lastSentTime = millis();
    }

    delay(200); // debounce
  }

  lastButtonState = buttonState;
}
