/*
Software Debounce - Use an interupt with software debounce of 0.1 seconds
Interupt no 0 is pin 2 on Uno
Interupt no 1 is pin 3 on Uno
*/

int pbIn = 0;                  // Interrupt 0 is on DIGITAL PIN 2!
volatile int state = LOW;      // The input state toggle
int rain = 0;

unsigned long microTimeCurrent = micros();
unsigned long microTimeDelay = 100000;  // IE 0.1 Second
unsigned long microTimeLast = 0;

void setup()
{                
  // Set up the digital pin 2 to an Interrupt

  //Attach the interrupt to the input pin and monitor for ANY Change 
  attachInterrupt(pbIn, stateChange, RISING);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop()                     
{
  //Simulate a long running process or complex task
  for (int i = 0; i < 100; i++)
  {
    // do nothing but waste some time
    delay(10); 
  }
  
  // Reset timers when micros() resets every 70 minutes on Uno
  if (micros() < microTimeLast) {
    microTimeLast = 0;
  }
}

void stateChange()
{
  microTimeCurrent = micros();
  if (microTimeCurrent - microTimeLast >= microTimeDelay) {
    microTimeLast = micros();
    state = !state;
    ++rain;
    Serial.println(rain);
  }
}
