


#include "HomeSpan.h"
#include "DEV_LED.h"
#include "FastLED.h"

#define NUM_LEDS 1
#define DATA_PIN 48

CRGB leds[NUM_LEDS];

void setup() {

    LEDS.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

    Serial.begin(115200);

    homeSpan.begin(Category::Lighting, "WS2812");

//    new SpanAccessory();
//    new Service::AccessoryInformation();
//    new Characteristic::Identify();
//    new DEV_LED(16);

    new SpanAccessory();
    new Service::AccessoryInformation();
    new Characteristic::Identify();
    new DEV_RgbLED(17, 18, 19);

    leds[0] = CRGB::Black;
    FastLED.show();

} // end of setup()

//////////////////////////////////////

void loop() {

    homeSpan.poll();

} // end of loop()
