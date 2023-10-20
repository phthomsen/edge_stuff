
#include <Arduino_HTS221.h>


// define the rgb leds
# define RED 22
# define BLUE 24
# define GREEN 23
# define LED_PWR 25

float old_temp = 0;
float old_hum = 0;

void setup() {
  // initialize the digital Pin as an output
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(LED_PWR, OUTPUT);
    
  Serial.begin(9600);
  while (!Serial);

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
}

void loop() {
  // read all the sensor values
  float temperature = HTS.readTemperature();
  float humidity    = HTS.readHumidity();

  // check if the range values in temperature are bigger than 0,5 ºC
  // and if the range values in humidity are bigger than 1%
  if (abs(old_temp - temperature) >= 0.5 || abs(old_hum - humidity) >= 1 )
  {
    old_temp = temperature;
    old_hum = humidity;
    // print each of the sensor values
    Serial.print("Something is happening here. What the fuck\n");
//    digitalWrite(RED, HIGH);
//    digitalWrite(RED, LOW);

  } else if (temperature > 30) {
   Serial.print("oof, it's getting hot in heeeeere\n");
  }
  else {
    Serial.print("Everything seems normal \n");
    digitalWrite(GREEN, LOW); 
    }
   

  // print each of the sensor values
  digitalWrite(BLUE, HIGH); // blink blue to indicate a new cycle
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println(" %");

  // print an empty line
  Serial.println();

  // wait a bit to print again
  delay(2000);
}

