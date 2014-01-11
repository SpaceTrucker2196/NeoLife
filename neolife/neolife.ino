// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
}

int x    = matrix.width();
int pass = 0;

PASTEBIN  |  #1 paste tool since 2002
create new pastetoolsapiarchivefaq
PASTEBIN	 Search...
 create new paste      trending pastes
sign uploginmy alertsmy settingsmy profile
 Pastebin launched a little side project called HostCabi.net, check it out ;-)Don't like ads? PRO users don't see any ads ;-)
Public Pastes
Untitled
0 sec ago
Untitled
5 sec ago
Untitled
Java | 9 sec ago
Untitled
7 sec ago
Untitled
9 sec ago
Untitled
13 sec ago
Untitled
14 sec ago
Cashjite
29 sec ago


0
0
Guest
Andrew
BY: A GUEST ON FEB 15TH, 2008  |  SYNTAX: C  |  SIZE: 3.57 KB  |  HITS: 2,739  |  EXPIRES: NEVER
DOWNLOAD  |  RAW  |  EMBED  |  REPORT ABUSE  |  PRINT

    
/*
 * Conway's "Life"
 *
 * Adapted from the Life example
 * on the Processing.org site
 */
 
#include <FrequencyTimer2.h>
 
byte analogPin = 5;
byte col = 0;
byte leds[8][8];
 
// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[17]= {-1, 5, 4, 3, 2, 14, 15, 16, 17, 13, 12, 11, 10, 9, 8, 7, 6};
 
// col[xx] of leds = pin yy on led matrix
int cols[8] = {pins[13], pins[3], pins[4], pins[10], pins[06], pins[11], pins[15], pins[16]};
 
// row[xx] of leds = pin yy on led matrix
int rows[8] = {pins[9], pins[14], pins[8], pins[12], pins[1], pins[7], pins[2], pins[5]};
 
#define DELAY 0
#define SIZE 8
extern byte leds[SIZE][SIZE];
byte world[SIZE][SIZE][2];
long density = 50;
 
void setup() {
  setupLeds();
  randomSeed(analogRead(5));
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (random(100) < density) {
        world[i][j][0] = 1;
      }
      else {
        world[i][j][0] = 0;
      }
      world[i][j][1] = 0;
    }
  }
}
 
void loop() {
  // Display current generation
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      leds[i][j] = world[i][j][0];
    }
  }
  delay(DELAY);
 
  // Birth and death cycle
  for (int x = 0; x < SIZE; x++) {
    for (int y = 0; y < SIZE; y++) {
      // Default is for cell to stay the same
      world[x][y][1] = world[x][y][0];
      int count = neighbours(x, y);
      if (count == 3 && world[x][y][0] == 0) {
        // A new cell is born
        world[x][y][1] = 1;
      }
      if ((count < 2 || count > 3) && world[x][y][0] == 1) {
        // Cell dies
        world[x][y][1] = 0;
      }
    }
  }
 
  // Copy next generation into place
  for (int x = 0; x < SIZE; x++) {
    for (int y = 0; y < SIZE; y++) {
      world[x][y][0] = world[x][y][1];
    }
  }
}
 
int neighbours(int x, int y) {
 return world[(x + 1) % SIZE][y][0] +
         world[x][(y + 1) % SIZE][0] +
         world[(x + SIZE - 1) % SIZE][y][0] +
         world[x][(y + SIZE - 1) % SIZE][0] +
         world[(x + 1) % SIZE][(y + 1) % SIZE][0] +
         world[(x + SIZE - 1) % SIZE][(y + 1) % SIZE][0] +
         world[(x + SIZE - 1) % SIZE][(y + SIZE - 1) % SIZE][0] +
         world[(x + 1) % SIZE][(y + SIZE - 1) % SIZE][0];
}
 
void setupLeds() {
  // sets the pins as output
  for (int i = 1; i <= 16; i++) {
    pinMode(pins[i], OUTPUT);
  }
 
  // set up cols and rows
  for (int i = 1; i <= 8; i++) {
    digitalWrite(cols[i - 1], LOW);
  }
 
  for (int i = 1; i <= 8; i++) {
    digitalWrite(rows[i - 1], LOW);
  }
 
  clearLeds();
 
  // Turn off toggling of pin 11
  FrequencyTimer2::disable();
  // Set refresh rate (interrupt timeout period)
  FrequencyTimer2::setPeriod(2000);
  // Set interrupt routine to be called
  FrequencyTimer2::setOnOverflow(display);
 
}
 
void clearLeds() {
  // Clear display array
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = 0;
    }
  }
}
 
// Interrupt routine
void display() {
  digitalWrite(cols[col], LOW);  // Turn whole previous column off
  col++;
  if (col == 8) {
    col = 0;
  }
  for (int row = 0; row < 8; row++) {
    if (leds[col][7 - row] == 1) {
      digitalWrite(rows[row], LOW);  // Turn on this led
    }
    else {
      digitalWrite(rows[row], HIGH); // Turn off this led
    }
  }
  digitalWrite(cols[col], HIGH); // Turn whole column on at once (for equal lighting times)
  delayMicroseconds(900);  // Delay so that on times are longer than off time = brighter leds
}
create a new version of this paste RAW Paste Data

Pastebin.com Tools & Applications
iPhone/iPad  Windows  Firefox  Chrome  WebOS  Android  Mac  Opera  Click.to  UNIX  WinPhone
create new paste  |  api  |  trends  |  users  |  faq  |  tools  |  privacy  |  cookies policy  |  contact  |  stats  |  go pro 
Follow us: pastebin on facebook  |  pastebin on twitter  |  pastebin in the news 
Dedicated Server Hosting by Steadfast
Pastebin v3.11 rendered in: 0.007 seconds  
