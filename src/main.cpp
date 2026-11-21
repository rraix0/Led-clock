#include <Arduino.h>
#include <FastLED.h>
#include <WiFi.h>
#include <time.h>
#include <numbers.h>


// CONFIG
#define LED_PIN     0 // Number of pin connected to Din - Data in
#define LED_TYPE    WS2812B // Type of led strip
#define COLOR_ORDER GRB // Green Red Blue
#define BRIGHTNESS 60 // FROM 0 - 255
// WiFi
const char *ssid = "";
const char *password = "";

CRGB main_color = CRGB::Black;
// Brightness of background effect (0-255)
#define BACKGROUND_BRIGHTNESS 255


// LEDS OFFSETS
#define NUM_LEDS    128

const int leds_rows[7] = {17, 18, 19, 20, 19, 18, 17};
const int lines[7] = {16, 17, 53, 54, 92, 93, 127};
const int straight_offsets[7] = {0, 0, 1, 1, 1, 0, 0};
const int start_offset = 17;
const int dot_count[5] = {2, 3, 2, 3, 2};
const int offsets[4][5] = {
    {1,1,2,1,1},
    {5,5,6,5,5},
    {11,11,12,11,11},
    {15,15,16,15,15},
};
const int dots[] = {17 + 18 + 9, 17 + 18 + 19 + 20 + 9};
bool dot_visible = true;

CRGB leds[NUM_LEDS];


uint8_t baseHue = 0;

void show_dots (bool visible) {
    for (int dot : dots) {
        if (visible) {
            leds[dot] = main_color;
        }
    }
}

void show_number(int num, int value) {
    int number_offset = 0;
    for (int i = 0; i < 5; i++) {
        for(int j = 0; j < dot_count[i]; j ++) {
            if (number_shapes[value][number_offset]) {
                int led_number = lines[i + 1];
                if (i%2 == 0) {
                    led_number += offsets[num][i] + j;
                } else {
                    led_number -= offsets[num][i] + j;
                }

                leds[led_number] = main_color;
            }
            number_offset += 1;
        }
    }
}

void setup() {
      FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    fill_solid(leds, NUM_LEDS, CHSV(0, 0, 50));
    FastLED.show();
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    IPAddress dns1(1,1,1,1);
    IPAddress dns2(8,8,8,8);

    WiFi.setDNS(dns1, dns2);

    configTzTime(
        "CET-1CEST,M3.5.0/2,M10.5.0/3",
        "pool.ntp.org"
    );

 

    struct tm timeinfo;
    while (!getLocalTime(&timeinfo)) {
        Serial.println("Nie udalo sie pobrac czasu");
        fill_solid(leds, NUM_LEDS, CRGB::Red);
        FastLED.show();
        delay(10000);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
    }



    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
}

void loop() {    
    EVERY_N_MILLIS(200) {
        struct tm t;
        int h1, h2, m1, m2;
        if (getLocalTime(&t)) {
            h1 = t.tm_hour / 10;
            h2 = t.tm_hour % 10;
            m1 = t.tm_min / 10;
            m2 = t.tm_min % 10;
        }
        Serial.print(h1);
        Serial.print(h2);
        Serial.print(m1);
        Serial.println(m2);
        
        fill_solid(leds, NUM_LEDS, CRGB::Black);

        int even = false;
        for (int i = 0; i < 7; i++) {
            int direction = -1;
            if (even) {
                direction = 1;
            }

            for(int j = 0; j < leds_rows[i]; j ++) {
                leds[lines[i] + (direction * j)] = CHSV((j - straight_offsets[i] + baseHue) * 1, 255, BACKGROUND_BRIGHTNESS);
            }

            even = !even;
        }
        baseHue--;
        
        show_number(0, h1);
        show_number(1, h2);
        show_number(2, m1);
        show_number(3, m2);
        
        
        show_dots(dot_visible);
        FastLED.show();
        
    }
    EVERY_N_SECONDS(1) {
        dot_visible = !dot_visible;
    }
    
}