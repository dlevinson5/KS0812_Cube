#include <avr/pgmspace.h> 
#define CUBESIZE 4
#define PLANESIZE CUBESIZE*CUBESIZE
#define PLANETIME 3333 
#define TIMECONST 20 
#define CUBECOLS 16
#define CUBEROWS 4

static int col = -1;
static int row = 0;

int LEDPin[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1 };
int PlanePin[] = { A2, A3, A4, A5 };

void setup()
{
	int pin;

	for (pin = 0; pin < PLANESIZE; pin++)
		pinMode(LEDPin[pin], OUTPUT);

	for (pin = 0; pin < CUBESIZE; pin++)
		pinMode(PlanePin[pin], OUTPUT);
}

void setPoint(int x, int y, bool on)
{
	static int last_y = NULL;

	if (last_y != y) {
		digitalWrite(PlanePin[0], y == 0 ? LOW : HIGH);
		digitalWrite(PlanePin[1], y == 1 ? LOW : HIGH);
		digitalWrite(PlanePin[2], y == 2 ? LOW : HIGH);
		digitalWrite(PlanePin[3], y == 3 ? LOW : HIGH);
		last_y = y;
	}

	digitalWrite(LEDPin[x], on ? HIGH : LOW);
}

void loop()
{
	// set the current column 
	col = (++col == CUBECOLS) ? 0 : col;

	// if at column 0 then move to the next row
	row = (col == 0 && ++row == CUBEROWS) ? 0 : row;
 
	// Turn on the point 
	setPoint(col, row, true);
 	delay(100);
	// Turn off the point 
	setPoint(col, row, false);
}