#include <Servo.h>

Servo leftServo;
Servo rightServo;
const int IRSensorsPins[4] = {10, 2, 3, 11};
const int leftServoPin = 8;
const int rightServoPin = 9;
const int leftServoForwardSlow = 20;
const int rightServoForwardSlow = 160;
const int NO_LINE = LOW;
int IRSensorsValues[4];
const int LINE = HIGH;
const int GO_BACKWARD_A_LITTLE_TIME = 100;
const int GO_FORWARD_CHECK_CROSSING_TIME = 350;
const int leftServoForward = 0;
const int rightServoForward = 180;
const int LITTLE_DELAY_STOP_ROBOT_TIME = 300;
const int leftServoBackward = 180;
const int rightServoBackward = 0;
const int stopServo = 90;
const int STOP_ROBOT_REACH_GOAL_TIME = 5000;
const int TURN_AROUND_TIME = 1400;

void setup()
{
  Serial.begin(9600);

  int i = 0;
  while (i < 4)
  {
    pinMode(IRSensorsPins[i], INPUT);
    i++;
  }
  rightServo.attach(rightServoPin);
  leftServo.attach(leftServoPin);
  delay(2000);
}

void loop()
{
  updateAllIRSensors();

  if (assertIRSensorsValues(NO_LINE, LINE, LINE, NO_LINE))
  {
    goForward();
  }
  else if (assertIRSensorsValues(LINE, LINE, LINE, LINE))
  {
    checkTypeOfCrossingAllLine();
  }
  else if (assertIRSensorsValues(NO_LINE, LINE, LINE, LINE))
  {
    checkTypeOfCrossingRight();
  }
  else if (assertIRSensorsValues(NO_LINE, NO_LINE, LINE, NO_LINE))
  {
    correctionToTheRight();
  }
  else if (assertIRSensorsValues(LINE, LINE, LINE, NO_LINE))
  {
    turnLeft();
  }
  else if (assertIRSensorsValues(NO_LINE, LINE, NO_LINE, NO_LINE))
  {
    correctionToTheLeft();
  }

  else if (assertIRSensorsValues(NO_LINE, LINE, LINE, LINE) == false)
  {
    turnAround();
  }
}

boolean assertIRSensorsValues(int IRSensor0, int IRSensor1, int IRSensor2, int IRSensor3)
{
  return (IRSensorsValues[2] == IRSensor2 && IRSensorsValues[3] == IRSensor3 && IRSensorsValues[0] == IRSensor0 && IRSensorsValues[1] == IRSensor1);
}
void stopRobotAndDelayALittle()
{
  stopRobot();
  delay(LITTLE_DELAY_STOP_ROBOT_TIME);
}
void stopRobot()
{
  leftServo.write(stopServo);
  rightServo.write(stopServo);
}

void turnAround()
{
  leftServo.write(leftServoBackward);
  rightServo.write(rightServoForward);
  delay(TURN_AROUND_TIME);
  stopRobotAndDelayALittle();
}
void goForward()
{
  leftServo.write(leftServoForwardSlow);
  rightServo.write(rightServoForwardSlow);
}

void correctionToTheRight()
{
  leftServo.write(leftServoForward);
  rightServo.write(stopServo);
}
void correctionToTheLeft()
{
  leftServo.write(stopServo);
  rightServo.write(rightServoForward);
}

void turnLeft()
{
  rightServo.write(rightServoForward);
  leftServo.write(leftServoBackward);
  delay(TURN_AROUND_TIME / 2);
  stopRobotAndDelayALittle();
}

void turnRight()
{
  rightServo.write(rightServoBackward);
  leftServo.write(leftServoForward);
  delay(TURN_AROUND_TIME / 2);
  stopRobotAndDelayALittle();
}

void checkTypeOfCrossingRight()
{

  goForwardAndUpdateAllIRSensors(400);
  if (assertIRSensorsValues(NO_LINE, LINE, LINE, NO_LINE) == false)
  {
    turnRight();
  }
  else if (assertIRSensorsValues(NO_LINE, LINE, LINE, NO_LINE) == true)
    ;
  {
    goForward();
  }
}

void checkTypeOfCrossingAllLine()
{

  goForwardAndUpdateAllIRSensors(400);
  if (assertIRSensorsValues(LINE, LINE, LINE, LINE) == false)
  {
    turnLeft();
  }
  else if (assertIRSensorsValues(LINE, LINE, LINE, LINE) == true)
  {
    robotReachesTheGoal();
  }
}

void goForwardAndUpdateAllIRSensors(int delayValue)
{
  int delayToWait;
  if (delayValue != 0)
    delayToWait = delayValue;
  else if (delayValue == 0)
    delayToWait = GO_FORWARD_CHECK_CROSSING_TIME;

  goForward();
  delay(delayToWait);

  stopRobot();
  delay(delayToWait);

  updateAllIRSensors();

  goBackwardALittle();
}

void goBackwardALittle()
{
  rightServo.write(rightServoBackward);
  leftServo.write(leftServoBackward);
  delay(GO_BACKWARD_A_LITTLE_TIME);
  stopRobot();

  delay(GO_BACKWARD_A_LITTLE_TIME);
}

void updateAllIRSensors()
{
  int i = 0;
  while (i < 4)
  {
    IRSensorsValues[i] = digitalRead(IRSensorsPins[i]);
    i++;
  }
  i = 0;
  while (i < 4)
  {

    delay(10);

    for (int i2 = 0; i2 < 4; i2++)
    {
      if (digitalRead(IRSensorsPins[i2]) == LINE)
        IRSensorsValues[i2] = LINE;
    }

    i++;
  }
}

void robotReachesTheGoal()
{
  stopRobot();
  delay(STOP_ROBOT_REACH_GOAL_TIME);
}
