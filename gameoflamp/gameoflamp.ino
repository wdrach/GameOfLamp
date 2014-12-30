#include <Adafruit_NeoPixel.h>
//http://www.conwaylife.com/wiki/Mazing
//http://www.conwaylife.com/wiki/Mold
#define NEOPIN 5
#define SWITCH 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, NEOPIN, NEO_GRB + NEO_KHZ800);


int lifeMatrix[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 0, 0, 0,
	0, 1, 0, 1, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 1, 0,
	0, 1, 0, 0, 0, 1, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 1, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0
};

int newMatrix[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

byte adjacency = 0;
boolean top = false;
boolean bot = true;
boolean left = false;
boolean right = true;

void setup() {
  //initialize the neopixels
  strip.begin();
  strip.show();
  strip.setBrightness(100);

  //pin
  pinMode(SWITCH, INPUT);
}

void loop(){
  int power = digitalRead(SWITCH);
  if (power == 1){
    strip.setBrightness(100);
	GoLmatrix();
	updateGoL();
	delay(1000);
  }
  else{
    strip.setBrightness(0);
  }
}


void updateGoL(){
	for (int i = 0; i < 64; i++){
		adjacency = 0;
		if (i < 8){
			top = false;
		}
		else {
			top = true;
		}
		if (i > 52){
			bot = false;
		}
		else {
			bot = true;
		}
        left  = true;
        right = true;

		for(int j = 0; j < 64; j += 8){
			if ((i - j) == 0){
				left = false;
			}
			if ((i - j) == -1){
				right = false;
			}
		}

		if (top){
			adjacency += lifeMatrix[i - 8];
			if (left){
				adjacency += lifeMatrix[i - 9];
			}
			if (right){
				adjacency += lifeMatrix[i - 7];
			}
		}
		if (bot){
			adjacency += lifeMatrix[i + 8];
			if (left){
				adjacency += lifeMatrix[i + 7];
			}
			if (right){
				adjacency += lifeMatrix[i + 9];
			}
		}
		if (left){
			adjacency += lifeMatrix[i - 1];
		}
		if (right){
			adjacency += lifeMatrix[i + 1];
		}

		if (lifeMatrix[i] == 0){
			if (adjacency == 3){
				newMatrix[i] = 1;
			}
		}

		else{
			if (adjacency < 2){
				newMatrix[i] = 0;
			}
			else if (adjacency > 3){
				newMatrix[i] = 0;
			}
			else {
				newMatrix[i] = 1;
			}
		}

	}

	for (int k = 0; k < 64; k++){
		lifeMatrix[k] = newMatrix[k];
	}
}

void GoLmatrix(){
	for (int i = 0; i < 64; i++){
		strip.setPixelColor(i, strip.Color(0,0,0));
		if (lifeMatrix[i] == 1){
			strip.setPixelColor(i, strip.Color(255, 0, 255));
		}
	}
	strip.show();
}
