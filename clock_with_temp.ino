#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h> // Include the TimeLib library

#define DHTPIN A3     // Pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize LCD

bool manualTimeSet = false; // Flag to indicate if manual time has been set

void setup() {
  Serial.begin(9600);
  Serial.println("Temperature Sensor Test");

  dht.begin();
  lcd.init();
  lcd.backlight();

  setManualTime(); // Set manual time initially
}

void loop() {
  float temperature = dht.readTemperature(); // Read temperature

  if (isnan(temperature)) { // Check if reading is valid
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temp: "); // Change "Temperature" to "Temp"
  Serial.print(temperature);
  Serial.println(" °C");

  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.setCursor(6, 0); // Move cursor to the 7th column of the 1st row
  lcd.print(temperature); // Print temperature value
  lcd.print(" C");

  if (!manualTimeSet) {
    setManualTime(); // Set manual time if it hasn't been set yet
  }

  // Get the current time
  int currentHour = hour();
  int currentMinute = minute();

  // Print the hour and minute on the second row
  lcd.setCursor(0, 1); // Set cursor to the first column of the second row
  lcd.print("Time: ");
  lcd.print(currentHour);
  lcd.print(":");
  if (currentMinute < 10) {
    lcd.print("0");
  }
  lcd.print(currentMinute);

  delay(1000);
}

void setManualTime() {
  // Manual time setting
  int manualHour = 11; // <--- Manually edit the hour here
  int manualMinute = 7; // <--- Manually edit the minute here

  setTime(manualHour, manualMinute, 0, 1, 1, 2022); // Set manual time
  manualTimeSet = true; // Update flag to indicate manual time has been set
}
