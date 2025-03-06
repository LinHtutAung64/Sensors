#define LED_PIN 13
int photoresistor = 0; // Holds the brightness of the ambient light
int threshold = 605; // Adjust this threshold based on testing

void setup() {
  Serial.begin(115200); // ESP32 uses 115200 as a common baud rate
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Set the LED to be constantly on
}

void loop() {
  photoresistor = analogRead(34); // Use GPIO 34 as an analog input (any ADC pin on ESP32)
  Serial.println(photoresistor); // Print the value to the serial monitor

  // Check if the light level drops below the threshold
  if (photoresistor < threshold) {
    Serial.println("Ball Detected");
  }

  delay(100); // Short delay to make the printout easier to read
}
