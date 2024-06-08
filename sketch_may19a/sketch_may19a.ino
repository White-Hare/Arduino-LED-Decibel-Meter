#include <LiquidCrystal.h>

#define SENSOR_PIN A0

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);  // Creates an LCD object. Parameters: (rs, 1, d4, d5, d6, d7)


const int sampleWindow = 70;  // Sample window width in mS (50 mS = 20Hz)
const int decibelThreshold = 72.1;


void setup() {
  lcd.begin(16, 2);
  printOpeningMessage();
}


void loop() {
  lcd.clear();

  const unsigned int sample = getDecibelSample();
  unsigned int db = map(sample, 0, 1024, 49.5, 90);
  
  printResult(db);


  delay(500);
}

unsigned int getDecibelSample() {
  unsigned long startMillis = millis();          // Start of sample window

  unsigned int max = 0;
  unsigned int min = 1024;

  while (millis() - startMillis < sampleWindow) {
    unsigned int sample = analogRead(SENSOR_PIN);  //get reading from microphone
  
    if(sample > max){
      max = sample;
    }
    
    if(sample < min){
      min = sample;
    }
  }

  return max - min;
}

void printOpeningMessage() {
  lcd.print("Made By");
  lcd.setCursor(0, 1);
  lcd.print("Mete ARSLAN");
}

void printResult(unsigned int db) {
  lcd.setCursor(0, 0);
  lcd.print("Gurultu: ");
  lcd.print(db);
  lcd.print("dB");

  lcd.setCursor(0, 1);

  if (db <= decibelThreshold) {
    lcd.print("Yogunluk: Art");
  } 
  else{
    lcd.print("Yogunluk: Azl");
  } 
}