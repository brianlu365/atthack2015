/*

// Code for read board of automated closet 
// this code should accept serial data from the mbed
// it will them move 2 stepper motors based on the data
// it will also poll an IR detector emitter pair to detect
//  when a hanger goes by

//TODO: figure out how we are going to structure serial packets
//      decide when to move new position over to the current posistion variable


  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

//motor for tops
int step_pin_top = 4;
int dir_pin_top = 5;

//motor for bottoms
int step_pin_bot = 6;
int dir_pin_bot = 7;

//store current posistion in units of hangers
int top_pos_current = 0;    
int bot_pos_current = 0;
int top_pos_new = 0;    
int bot_pos_new = 0;

//store number of hangers in each rack
int top_num = 5;
int bot_num = 5;

//variables that will be populated later
int steps_between_top;
int steps_between_bot;
int steps_to_take_top;
int steps_to_take_bot;
int dir_top;
int dir_bot;

int data;
unsigned long time;

int steps_per_rev = 200;

//for debugging
int ledpin = 13;

void setup()  
{
  //populate calculated variables
  steps_between_top = steps_per_rev / top_num;
  steps_between_bot = steps_per_rev / bot_num;
  
  digitalWrite(dir_pin_top, HIGH);
  dir_top = 0;
  digitalWrite(dir_pin_bot, HIGH);
  dir_bot = 0;
  
  pinMode(step_pin_top, OUTPUT);      // sets the digital pin as output
  pinMode(dir_pin_top, OUTPUT);      // sets the digital pin as output
  pinMode(step_pin_bot, OUTPUT);      // sets the digital pin as output
  pinMode(dir_pin_bot, OUTPUT);      // sets the digital pin as output
  
  pinMode(ledpin, OUTPUT);
  pinMode(8, INPUT_PULLUP);
  digitalWrite(ledpin, LOW);
  
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) 
  {
    ;// wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("Hello, world?");
}

void loop() // run over and over
{ 
    //if (Serial.available())
    //  mySerial.write(Serial.read());
    
  //Code for just in case button
  if(!digitalRead(8))
  {
    top_pos_new = 100;7 
    bot_pos_new = 100;
    Serial.println("oh noes!");
  }
  
  if (Serial.available())
  {
    //read serial input
    data = mySerial.read();
    //for debugging to let me use the serial monitor
    data = Serial.read();
    //parse data: the first 4 bits are for the top the second 4 bits are for the bottom
    top_pos_new = map(data & B00001111, 0, 6, 0, steps_per_rev);
    bot_pos_new = map(data & B11110000, 0, 6, 0, steps_per_rev);
    //Print to the serial monitor for debugging
    //Serial.println(top_pos_new);
    //Serial.println(bot_pos_new);
  }
    
    //Logic for figuring out steps to take for position
    //calculate steps between current and new posistions in a clockwise direction
    //top
    if(top_pos_current > top_pos_new)
      dir_top = 0;
    else
      dir_top = 1;
    steps_to_take_top = abs(top_pos_current-top_pos_new);
    if(steps_to_take_top > steps_per_rev/2)
    {
      steps_to_take_top = steps_to_take_top - steps_per_rev/2;
      if(dir_top == 0)
        dir_top = 1;
      else
        dir_top = 0;
    }
    
    //Check if our current position is equal to the desired position
    if(top_pos_current != top_pos_new)
    {
      //actually change dir pins outputs now
      digitalWrite(dir_pin_top, dir_top);
      move_step(1);
      if(dir_top == 0)
        {
          if(top_pos_current !=0)
            top_pos_current -= 1;
          else
            top_pos_current = steps_per_rev;
        }
      else
      {
          if(top_pos_current !=steps_per_rev)
            top_pos_current += 1;
          else
            top_pos_current = 0;
      }
      Serial.println(top_pos_current);
      Serial.println(top_pos_new);
    }
    
    //Check if our current position is equal to the desired position
    if(bot_pos_current != bot_pos_new)
    {
      //bottom
      //actually change dir pins outputs now
       digitalWrite(dir_pin_top, dir_top);
      move_step(2);
      if(bot_pos_current != bot_pos_new)
      {
        if(bot_pos_current > bot_pos_new)
          dir_bot = 0;
        else
          dir_bot = 1;
        steps_to_take_bot = abs(bot_pos_current-bot_pos_new);
        if(steps_to_take_bot > steps_per_rev/2)
        {
          steps_to_take_bot = steps_to_take_bot - steps_per_rev/2;
          if(dir_bot == 0)
            dir_bot = 1;
          else
            dir_bot = 0;
        }  
        digitalWrite(dir_pin_bot, dir_bot);
      }
    }
    
}
  
void move_step(int motor_num)
{
  if(motor_num == 1)
  {
      //move tops specified steps
      digitalWrite(step_pin_top, HIGH);
      delay(50);               
      digitalWrite(step_pin_top, LOW);
      delay(100);
  }    
  if(motor_num == 2)
  {
      //move tops specified steps
      digitalWrite(step_pin_bot, HIGH);
      delay(50);               
      digitalWrite(step_pin_bot, LOW);
      delay(100);
  }
  //Serial.println("returned");
  return;
}

