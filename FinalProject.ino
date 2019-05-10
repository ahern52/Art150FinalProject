// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS   6
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

int photoCell = A2;
int pressure = A1;
int photoVal;
int pressureVal;
int mappedBrightness;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.

  pinMode(photoCell, INPUT);
  pinMode(pressure, INPUT);
  Serial.begin(9600);
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  photoVal = analogRead(photoCell);
  pressureVal = analogRead(pressure);

  mappedBrightness = map(photoVal, 0, 1023, 255, 0 );
  
  Serial.println(photoVal);

  pixels.setBrightness(mappedBrightness);
//  if (photoVal < 400) {
//
//    pixels.setBrightness(255);
//
//  }
//  if (photoVal > 400) {
//    pixels.setBrightness(40);
//
//  }

  if (pressureVal > 600) {
    for (int i = 0; i < NUMPIXELS; i++) {

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(200, 0, 0)); // Moderately bright green color.

      pixels.show(); // This sends the updated pixel color to the hardware.



    }

  }
  if (pressureVal < 600) {
    for (int i = 0; i < NUMPIXELS; i++) {

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0, 0, 200)); // Moderately bright green color.

      pixels.show(); // This sends the updated pixel color to the hardware.



    }
  }
}
