#include <LiquidCrystal.h> 
#include <dht_nonblocking.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11 //This tell the computer what type of sensor it has//

static const int DHT_SENSOR_PIN = 8;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

int Contrast=0;

//This sets all the var for the pins//
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
 const int HumidiferPin = 7;
 const int ButtonPin = 10;
 const int SensorPin = 8;
 const int LightPin = 9;
 const int X_pin = A0; // analog pin connected to X output
 const int Y_pin = A1; 

 bool isOn = false;

 void setup()
 {
    analogWrite(6,Contrast);
    lcd.begin(16, 2);

//This sets up the humidifer pin and turns it off ///
    pinMode(HumidiferPin, OUTPUT);
    digitalWrite(HumidiferPin, HIGH);

//This sets up the screen pin and turns it off (High is Off and Low is On) //
   pinMode(LED_BUILTIN, OUTPUT);

//This sets up the button pin and turns it off //
    pinMode(ButtonPin, INPUT);
    Serial.begin(9600);


//This sets up the sensor pin and turns it off //
    pinMode(SensorPin, INPUT);

//This sets up the Light pin and turns it off //
    pinMode(LightPin, OUTPUT);
    digitalWrite(LightPin, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("Up to grow ");
   
    lcd.setCursor(0, 1);
    lcd.print("Oyster Mushrooms");



  } 

  /*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}

     void loop()
 { 

   float temperature;
  float humidity;

    if (analogRead(Y_pin) == 0){

      if (isOn == false){
        
        isOn = true;
      }
    }

    if (analogRead(Y_pin) == 900){
      if (isOn == true){
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(LightPin, HIGH);
        isOn = false;
      }
    }
 if( measure_environment( &temperature, &humidity ) == true )
  {
    if (isOn == true){

      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(LightPin, LOW);

      lcd.setCursor(0, 0);
      lcd.print("Temperature: ");
      temperature = (temperature * 9/5) + 32;
      lcd.print(temperature);
      lcd.print(" ");

      lcd.setCursor(0, 1);
      lcd.print("Humidity: ");
      lcd.print(humidity);
      lcd.print("%");

      if (humidity <= 80){
          digitalWrite(HumidiferPin, LOW);
          Serial.print("HumidiferOn");
      }



    }
  }
    if (isOn == false){

     lcd.setCursor(0, 0);
     lcd.print("Up to grow ");
   
     lcd.setCursor(0, 1);
     lcd.print("Oyster Mushrooms");

    }
 }


