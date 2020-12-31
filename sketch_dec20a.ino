#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#define lengthof(A) ((sizeof((A))/sizeof((A)[0])))
#define button 12
int oldstate=HIGH;
const PROGMEM uint8_t mouth_0[8][8] = {
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,6,6,6,6,0,0}, 
   {0,6,6,6,6,6,6,0},
   {6,6,0,0,0,0,6,6},
   {6,0,0,0,0,0,0,6},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0}
};
const PROGMEM uint8_t mouth_4[8][8] = {
   {0,0,7,7,7,7,0,0},
   {0,7,0,0,0,0,7,0},
   {7,0,0,0,0,0,0,7},
   {7,0,0,0,0,0,0,7},
   {7,0,0,0,0,0,0,7},
   {7,0,0,0,0,0,0,7},
   {0,7,0,0,0,0,7,0},
   {0,0,7,7,7,7,0,0}
};
const PROGMEM uint8_t mouth_3[8][8] = {
   {0,0,0,0,0,0,0,0},
   {0,0,7,7,7,7,0,0},
   {0,7,0,0,0,0,7,0},
   {7,0,0,0,0,0,0,7},
   {7,0,0,0,0,0,0,7},
   {0,7,0,0,0,0,7,0},
   {0,0,7,7,7,7,0,0},
   {0,0,0,0,0,0,0,0}
};
const PROGMEM uint8_t mouth_2[8][8] = {
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,7,7,7,7,7,7,0},
   {7,0,0,0,0,0,0,7},
   {7,0,0,0,0,0,0,7},
   {0,7,7,7,7,7,7,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0}
};
const PROGMEM uint8_t mouth_1[8][8] = {
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,7,7,0,0,0},
   {7,7,7,0,0,7,7,7},
   {7,7,7,0,0,7,7,7},
   {0,0,0,7,7,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0}
};
const PROGMEM uint8_t mouth_smile[8][8] = {
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {2,0,0,0,0,0,0,2},
   {2,2,0,0,0,0,2,2},
   {0,2,2,2,2,2,2,0},
   {0,0,2,2,2,2,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0}
};
const PROGMEM uint8_t off_set[8][8] = {
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0}
};
uint16_t palette[8] = {};
Adafruit_NeoMatrix matrix1 = Adafruit_NeoMatrix(8, 8, 6,
 NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
 NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
 NEO_GRB            + NEO_KHZ800);
Adafruit_NeoMatrix matrix2 = Adafruit_NeoMatrix(8, 8, 7,
 NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
 NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
 NEO_GRB            + NEO_KHZ800);
Adafruit_NeoMatrix matrix3 = Adafruit_NeoMatrix(8, 8, 2,
 NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
 NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
 NEO_GRB            + NEO_KHZ800); 
Adafruit_NeoMatrix matrix4 = Adafruit_NeoMatrix(8, 8, 0,
 NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
 NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
 NEO_GRB            + NEO_KHZ800); 
void drawImage(short image_addr){
   for(int x = 0; x<8; x++){
       for(int y = 0; y<8; y++){
           uint8_t index = pgm_read_byte(image_addr+x+y*8);
           matrix1.drawPixel(x, y, palette[index]); 
           matrix2.drawPixel(x, y, palette[index]); 
           matrix3.drawPixel(x, y, palette[index]);  
           matrix4.drawPixel(x, y, palette[index]);
       }
   }
   matrix1.show();
   matrix2.show();
   matrix3.show();
   matrix4.show();
}
int pop_detection = 0;
bool smiling = false;
unsigned long smiletimer = 0;
unsigned long last_face = 0;
float vol = 0;
const uint16_t samples = 128;
void setup() {
   Serial.begin(9600);
   matrix1.begin();
   matrix2.begin();
   matrix3.begin();
   matrix4.begin();
   palette[0] = matrix4.Color(0,0,0);        //No color
// palette[1] = matrix.Color(0,0,255);       //blue
   palette[2] = matrix3.Color(255,0,255);    //purple
// palette[3] = matrix.Color(0,255,0);       //green
// palette[4] = matrix.Color(255,255,255);   //white
// palette[5] = matrix.Color(255,0,0);       //red
   palette[6] = matrix1.Color(0,255,255);    //yellow 
   palette[7] = matrix2.Color(255,255,0);    //cyan
  pinMode(button,INPUT_PULLUP);
}
void loop() {
   int newstate=digitalRead(button);
     if(newstate == LOW){
   float nvol = 0;
   int previous_peak = -1;
   for (int i = 0; i<samples; i++){
       auto analog = analogRead(A7);
       auto micline = abs(analog - 512);
       nvol = max(micline, nvol);
   }
   vol = (nvol + 1.0*vol)/2.0;
   if(nvol > 200){
       pop_detection += 1;
       if(pop_detection > 5) {
           smiling = false;
           last_face = millis();
       }
   } else {
       if(pop_detection > 0 && pop_detection <= 5) {
           if(millis() > last_face + 500){
               smiling = true;
               smiletimer = millis() + 2000;
           }
       }
       pop_detection = 0;
   }
   if(millis() > smiletimer) 
   smiling = false;
     if(smiling){
       drawImage(mouth_smile);
   } else if(vol < 200){
       drawImage(mouth_0);
   } else if(vol < 250 && vol > 200){
       drawImage(mouth_1); 
   } else if(vol < 350 && vol > 250){
       drawImage(mouth_2);
   } else if(vol < 450 && vol > 350){
       drawImage(mouth_3);
   } else {
       drawImage(mouth_4);
       }
     }
     else
     {
       drawImage(off_set);
     }
}
