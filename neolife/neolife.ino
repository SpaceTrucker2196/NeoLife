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


/*
 * Conway's "Life"
 * 
 * Adapted from the Life example
 * on the Processing.org site
 */

#define DELAY 0
#define SIZE 8
byte world[SIZE][SIZE][2];
long density = 50;

void setup() {
  // setupLeds();
  Serial.begin(9600);
  randomSeed(analogRead(0));
  // randomSeed(Date);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
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


      matrix.setPixelColor(i*j,0,0, (world[i][j][0] *100));
      //matrix.setPixelColor(i*j,0, (world[i][j][1] *100),0);


      matrix.show();
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
      if (count == 2 && world[x][y][0] == 2) {
        // A new cell is born
        world[x][y][1] = 1; 
      } 
    }
  }
  //drop random seeds
  world[random(8)][random(8)][1] = 1;
  world[random(8)][random(8)][1] = 1;
  world[random(8)][random(8)][1] = 1;

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



