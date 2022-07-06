/*
  Quadruped Robot
  Developed by Hrithvik Maheshwari
  Last Modified on 05/07/2022
  12 Degree of Freedom

*/
// including libraries
#include "HCPCA9685.h"
#include <FlexiTimer2.h>
#define  I2CAdd 0x40
#define joyX A0
#define joyY A1
//declaring variables
unsigned long elapsedTime, previousTime;
int xValue;
int yValue;
int pos_n_0 = 180;
int pos_n_1 = 280;
int pos_n_2 = 280;
int pos_n_3 = 180;
int pos_n_4 = 110;
int pos_n_5 = 150;
int pos_n_6 = 180;
int pos_n_7 = 280;
int pos_n_8 = 240;
int pos_n_9 = 180;
int pos_n_10 = 80;
int pos_n_11 = 100;

HCPCA9685 HCPCA9685(I2CAdd);// I2C Initialization

void onTimer()// timer function to call functon in a particular interval of time
{
  static boolean state = HIGH;
  elapsedTime = millis() - previousTime;
  if (state)
  {
    // Reading Values of joystick
    xValue = analogRead(joyX);
    yValue = analogRead(joyY);
  }
  state = !state;
  previousTime = millis();
}

void setup()
{
  // Initializing Servo Driver
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  // Initializing Serial Monitor
  Serial.begin(9600);
  // Initializing FlexiTimer to run function after every 300ms. 
  FlexiTimer2::set(300, onTimer); // equivalent to FlexiTimer2::set(300, 1/1000, onTimer);
  FlexiTimer2::start();
}
void reading()// Function controlling Joystick data and processing
{
  if (xValue >= 1021)
  {
    forward();
    Serial.println("Forward");
  }
  else if (yValue <= 3  )
  {
    left();
    Serial.println("Left");
  }
  else if (yValue >= 1021)
  {
    right();
    Serial.println("Right");
  }
  else if (xValue <= 2)
  {
    ready_pos();
    Serial.println("Stand");
  }
}
void loop()
{
  reading();
}
void forward()// Function for Forward walking movement 
{
  delay(250);//250
  leg_4_oex();
  delay(125);//250
  leg_4_front();
  leg_3_mid();
  leg_2_oex();
  leg_1_back();
  delay(125);//250
  leg_2_mid();
  delay(125);//250
  leg_3_oex();
  delay(125);//250
  leg_3_front();
  leg_2_back();
  leg_1_oex();
  leg_4_mid();
  delay(125);//250
  leg_1_mid();
}
void ready_pos()// Function for making quadruped ready for walking
{
  stand();
  delay(1000);
  leg_1_mid();
  leg_4_mid();
  leg_2_back();
  leg_3_front();
  delay(1000);
}

void left()// Function for turning quadruped into left direction
{
  HCPCA9685.Servo(4, 50);
  delay(30);
  leg_2_back();
  delay(100);
  HCPCA9685.Servo(10, 20);
  delay(30);
  leg_4_front();
  HCPCA9685.Servo(11, 110);
  delay(100);
  leg_3_back();
  delay(100);
  HCPCA9685.Servo(1, 340);
  delay(30);
  leg_1_front();
  HCPCA9685.Servo(2, 270);
  delay(100);
  main_mid();
  delay(100);
}
void main_mid() // Function for turning robot body into front direction, used in left and right function 
{
  HCPCA9685.Servo(0, 180);
  HCPCA9685.Servo(3, 180);
  HCPCA9685.Servo(6, 180);
  HCPCA9685.Servo(9, 180);
}
void right()// Function for turning quadruped into right direction
{
  leg_1_back();
  delay(100);
  HCPCA9685.Servo(1, 200);
  delay(30);
  HCPCA9685.Servo(2, 260);
  delay(30);
  HCPCA9685.Servo(4, 50);
  delay(30);
  leg_2_front();
  delay(100);
  leg_3_front();
  delay(100);
  HCPCA9685.Servo(10, 10);
  delay(20);
  leg_4_back();
  delay(100);
  main_mid();
  delay(100);
}

// Functions for movement of legs of Quadruped in back direction individually.
void leg_1_back()
{
  HCPCA9685.Servo(0, 110);
  HCPCA9685.Servo(2, 210);
  HCPCA9685.Servo(1, 210);
  //  Serial.println("Leg 1 Back");
}
void leg_2_back()
{
  HCPCA9685.Servo(3, 250);
  HCPCA9685.Servo(5, 210);
  HCPCA9685.Servo(4, 180);
  //  Serial.println("Leg 2 Back");
}
void leg_3_back()
{
  HCPCA9685.Servo(7, 320);
  delay(100);
  HCPCA9685.Servo(6, 250);
  HCPCA9685.Servo(8, 200);
  HCPCA9685.Servo(7, 220);
  //  Serial.println("Leg 3 Back");
}
void leg_4_back()
{
  HCPCA9685.Servo(9, 110);
  HCPCA9685.Servo(11, 140);  //160
  HCPCA9685.Servo(10, 170);
  //  Serial.println("Leg 4 Back");
}

// Functions for movement of legs of Quadruped in front direction individually.
void leg_1_front()
{
  HCPCA9685.Servo(0, 240);
  HCPCA9685.Servo(2, 210);
  HCPCA9685.Servo(1, 210);
  //  Serial.println("Leg 1 Front");
}
void leg_2_front()
{
  HCPCA9685.Servo(3, 120);
  HCPCA9685.Servo(5, 210);
  HCPCA9685.Servo(4, 170);
  //  Serial.println("Leg 2 Front");
}
void leg_3_front()
{
  HCPCA9685.Servo(7, 360);
  delay(30);
  HCPCA9685.Servo(6, 120);
  HCPCA9685.Servo(8, 200);
  HCPCA9685.Servo(7, 240);
  //  Serial.println("Leg 3 Front");
}
void leg_4_front()
{
  HCPCA9685.Servo(10, 20);
  delay(30);
  HCPCA9685.Servo(9, 240);
  HCPCA9685.Servo(11, 140);
  HCPCA9685.Servo(10, 150);
  //  Serial.println("Leg 4 Front");
}

// Functions for movement of legs of Quadruped in mid individually.
void leg_1_mid()
{
  HCPCA9685.Servo(1, 340);
  delay(30);
  HCPCA9685.Servo(0, 180);
  HCPCA9685.Servo(2, 265);
  HCPCA9685.Servo(1, 220);
  //  Serial.println("Leg 1 Mid");
}
void leg_2_mid()
{
  HCPCA9685.Servo(4, 50);
  delay(30);
  HCPCA9685.Servo(3, 180);
  HCPCA9685.Servo(5, 155);
  HCPCA9685.Servo(4, 150);
  //  Serial.println("Leg 2 Mid");
}
void leg_3_mid()
{
  HCPCA9685.Servo(6, 180);
  HCPCA9685.Servo(8, 240);
  HCPCA9685.Servo(7, 240);
  //  Serial.println("Leg 3 Mid");
}
void leg_4_mid()
{
  HCPCA9685.Servo(9, 180);
  HCPCA9685.Servo(11, 60);
  HCPCA9685.Servo(10, 125);
  //  Serial.println("Leg 4 Mid");
}

// Functions for movement of legs of Quadruped in extended direction individually.
void leg_1_oex()
{
  HCPCA9685.Servo(2, 240);
  HCPCA9685.Servo(0, 40);
  HCPCA9685.Servo(1, 210 );
  //  Serial.println("Leg 1 Over Extended");
}
void leg_2_oex()
{
  HCPCA9685.Servo(5, 210);
  HCPCA9685.Servo(3, 340);
  HCPCA9685.Servo(4, 160);
  //  Serial.println("Leg 2 Over Extended");
}
void leg_3_oex()
{
  HCPCA9685.Servo(7, 340);
  delay(30);
  HCPCA9685.Servo(6, 80);
  HCPCA9685.Servo(8, 180);
  HCPCA9685.Servo(7, 240);
  //  Serial.println("Leg 3 Over Extended");
}
void leg_4_oex()
{
  HCPCA9685.Servo(10, 20);
  delay(30);
  HCPCA9685.Servo(9, 300);
  HCPCA9685.Servo(11, 140);
  HCPCA9685.Servo(10, 120);
  //  Serial.println("Leg 4 Over Extended");
}

void dance ()// Function for simple dance movement of Quadruped
{
  leg_1_dance();
  leg_2_dance();
  leg_3_dance();
  leg_4_dance();
}
void mid ()// Combined mid function 
{
  leg_1_mid();
  leg_2_mid();
  leg_3_mid();
  leg_4_mid();
}

// Functions for Dance routein of legs individually
void leg_1_dance()
{
  HCPCA9685.Servo(0, 180);
  delay(15);
  HCPCA9685.Servo(1, 380);
  delay(100);
  HCPCA9685.Servo(2, 235);
  //  Serial.println("Leg 1 Mid");
}
void leg_2_dance()
{
  HCPCA9685.Servo(3, 180);
  delay(15);
  HCPCA9685.Servo(5, 280);
  delay(15);
  HCPCA9685.Servo(4, 0);
  //  Serial.println("Leg 2 Mid");
}
void leg_3_dance()
{
  HCPCA9685.Servo(6, 180);
  delay(15);
  HCPCA9685.Servo(8, 160);
  delay(15);
  HCPCA9685.Servo(7, 400);
  //  Serial.println("Leg 3 Mid");
}
void leg_4_dance()
{
  HCPCA9685.Servo(9, 180);
  delay(15);
  HCPCA9685.Servo(11, 160);
  delay(15);
  HCPCA9685.Servo(10, -25);
  //  Serial.println("Leg 4 Mid");
}

// Function to make Quadruped Stand.
void stand()
{
  int pos_n_0 = 180;
  int pos_n_1 = 280;
  int pos_n_2 = 280;
  int pos_n_3 = 180;
  int pos_n_4 = 110;
  int pos_n_5 = 150;
  int pos_n_6 = 180;
  int pos_n_7 = 280;
  int pos_n_8 = 240;
  int pos_n_9 = 180;
  int pos_n_10 = 80;
  int pos_n_11 = 100;
  HCPCA9685.Servo(0, pos_n_0);
  HCPCA9685.Servo(1, pos_n_1);
  HCPCA9685.Servo(2, pos_n_2);
  HCPCA9685.Servo(3, pos_n_3);
  HCPCA9685.Servo(4, pos_n_4);
  HCPCA9685.Servo(5, pos_n_5);
  HCPCA9685.Servo(6, pos_n_6);
  HCPCA9685.Servo(7, pos_n_7);
  HCPCA9685.Servo(8, pos_n_8);
  HCPCA9685.Servo(9, pos_n_9);
  HCPCA9685.Servo(10, pos_n_10);
  HCPCA9685.Servo(11, pos_n_11);
  delay(2000);
}
