#include <Arduino.h>
#include <math.h>

#define dirpin 9
#define steppin 8

#define unitDelay 1

int stepF(int s)
{
  digitalWrite(dirpin, LOW);
  for (int i = 0; i < s; i++)
  {
    digitalWrite(steppin, HIGH);
    delay(unitDelay);
    digitalWrite(steppin, LOW);
    delay(unitDelay);
  }
  return s;
}

int stepB(int s)
{
  digitalWrite(dirpin, HIGH);
  for (int i = 0; i < s; i++)
  {
    digitalWrite(steppin, HIGH);
    delay(unitDelay);
    digitalWrite(steppin, LOW);
    delay(unitDelay);
  }
  return s * -1;
}

int minAngle = 0;
int maxAngle = 180;

int minCStep = 0;
int maxCStep = 542;

void setup()
{
  pinMode(dirpin, OUTPUT);
  pinMode(steppin, OUTPUT);
  Serial.begin(9600);
}

int dir = 0;
int mdir = 0;

void loop()
{
  int r = analogRead(A0);
  dir = map(r, 0, 542, 0, 100);
  if (dir > 100)
    dir = 100;
  if (abs(mdir - dir) > 3)
  {
    dir = map(r, 0, 542, 0, 100);
    if (dir > mdir)
    {
      mdir += stepF(1);
    }
    else
    {
      mdir += stepB(1);
    }
  }
  Serial.print("wind dir=>");
  Serial.print(dir);
  Serial.print("  ");
  Serial.print("motor dir =>");
  Serial.println(mdir);
}