#include <Servo.h>

Servo leftServo;
Servo rightServo;
const int IRSensorsPins[4] = {10, 2, 3, 11};
int IRSensorsValues[4];
const int rightServoPin = 9;
const int leftServoPin = 8;
const int NO_LINE = LOW;
const int LINE = HIGH;
const int leftServoForward = 0;
const int rightServoForward = 180;
const int leftServoBackward = 180;
const int rightServoBackward = 0;
const int stopServo = 90;
const int leftServoForwardSlow = 20;
const int rightServoForwardSlow = 160;
const int INITIAL_STOP_ROBOT_TIME = 2000;
const int TURN_AROUND_TIME = 1400;
const int GO_FORWARD_CHECK_CROSSING_TIME = 350;
const int STOP_ROBOT_REACH_GOAL_TIME = 5000;
const int GO_BACKWARD_A_LITTLE_TIME = 100;
const int LITTLE_DELAY_STOP_ROBOT_TIME = 300;
String robotDecisions = "";
int isFirstRound = 1;
int currentDecision = 0;

void setup()
{
  Serial.begin(9600);

  int i = 0;
  while (i < 4)
  {
    pinMode(IRSensorsPins[i], INPUT);
    i++;
  }

  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);

  delay(INITIAL_STOP_ROBOT_TIME);
}

void loop()
{
  updateAllIRSensors();

  if (assertIRSensorsValues(NO_LINE, LINE, LINE, NO_LINE))
  {
    goForward();
  }
  else if (assertIRSensorsValues(LINE, LINE, LINE, NO_LINE))
  {
    checkTypeOfCrossingLeft();
  }
  else if (assertIRSensorsValues(NO_LINE, NO_LINE, LINE, NO_LINE))
  {
    correctionToTheRight();
  }
  else if (assertIRSensorsValues(LINE, LINE, LINE, LINE))
  {
    checkTypeOfCrossingAllLine();
  }

  else if (assertIRSensorsValues(NO_LINE, LINE, LINE, LINE))
  {
    checkTypeOfCrossingRight();
  }
  else if (assertIRSensorsValues(NO_LINE, LINE, NO_LINE, NO_LINE))
  {
    correctionToTheLeft();
  }

  else
  {
    turnAround();
  }
}

boolean assertIRSensorsValues(int IRSensor0, int IRSensor1, int IRSensor2, int IRSensor3)
{
  return (IRSensorsValues[2] == IRSensor2 && IRSensorsValues[3] == IRSensor3 && IRSensorsValues[0] == IRSensor0 && IRSensorsValues[1] == IRSensor1);
}

void stopRobot()
{
  leftServo.write(stopServo);
  rightServo.write(stopServo);
}

void stopRobotAndDelayALittle()
{
  stopRobot();
  delay(LITTLE_DELAY_STOP_ROBOT_TIME);
}

void goForward()
{
  leftServo.write(leftServoForwardSlow);
  rightServo.write(rightServoForwardSlow);
}

void turnAround()
{
  leftServo.write(leftServoBackward);
  rightServo.write(rightServoForward);
  delay(TURN_AROUND_TIME);
  stopRobotAndDelayALittle();

  if (isFirstRound == 0)
    Serial.println(robotDecisions);
  else if (isFirstRound == 1)
    robotDecisions += "R";
}

void correctionToTheLeft()
{
  leftServo.write(stopServo);
  rightServo.write(rightServoForward);
}

void correctionToTheRight()
{
  leftServo.write(leftServoForward);
  rightServo.write(stopServo);
}

void turnLeft()
{
  leftServo.write(leftServoBackward);
  rightServo.write(rightServoForward);
  delay(TURN_AROUND_TIME / 2);
  stopRobotAndDelayALittle();
}

void turnRight()
{
  leftServo.write(leftServoForward);
  rightServo.write(rightServoBackward);
  delay(TURN_AROUND_TIME / 2);
  stopRobotAndDelayALittle();
}

void checkTypeOfCrossingRight()
{
  goForwardAndUpdateAllIRSensors(400);

  if (assertIRSensorsValues(NO_LINE, LINE, LINE, NO_LINE))
  {
    if (isFirstRound == 1)
    {
      goForward();
      robotDecisions += "A";
    }
    else
      followStoredDecision();
  }
  else
  {
    turnRight();
  }
}

void checkTypeOfCrossingLeft()
{
  goForwardAndUpdateAllIRSensors(0);

  if (assertIRSensorsValues(NO_LINE, LINE, LINE, NO_LINE) == false)
  {

    turnLeft();
  }
  else if (assertIRSensorsValues(NO_LINE, LINE, LINE, NO_LINE) == true)
  {
    if (isFirstRound != 1)
    {
      followStoredDecision();
    }
    else if (isFirstRound == 1)
    {
      turnLeft();
      robotDecisions += "I";
    }
  }
}

void checkTypeOfCrossingAllLine()
{
  goForwardAndUpdateAllIRSensors(400);

  if (assertIRSensorsValues(LINE, LINE, LINE, LINE))
  {
    robotReachesTheGoal();
  }
  else
  {
    if (isFirstRound == 1)
    {
      turnLeft();
      robotDecisions += "I";
    }
    else
      followStoredDecision();
  }
}

void goForwardAndUpdateAllIRSensors(int delayValue)
{
  int delayToWait;
  if (delayValue == 0)
    delayToWait = GO_FORWARD_CHECK_CROSSING_TIME;
  else
    delayToWait = delayValue;

  goForward();
  delay(delayToWait);

  stopRobot();
  delay(delayToWait);

  updateAllIRSensors();

  goBackwardALittle();
}

void goBackwardALittle()
{
  leftServo.write(leftServoBackward);
  rightServo.write(rightServoBackward);
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
  if (isFirstRound == 1)
  {
    reduceDecisions();
    isFirstRound = 0;
  }
  delay(STOP_ROBOT_REACH_GOAL_TIME);
}
void followStoredDecision()
{
  String decision = robotDecisions.substring(currentDecision, currentDecision + 1);

  if (decision == "I")
    goForward();
  else if (decision == "A")
    turnRight();
  else if (decision == "D")
    turnLeft();
  currentDecision++;
}

void applyReduction(int i, String reduction)
{
  robotDecisions = robotDecisions.substring(0, i) + reduction + robotDecisions.substring(i + 3);
}
void reduceDecisions()
{
  int i = 0;

  while (i <= robotDecisions.length() - 3)
  {
    if (robotDecisions.substring(i, i + 3) == "ARI")
    {
      applyReduction(i, "D");
      return reduceDecisions();
    }
    else if (robotDecisions.substring(i, i + 3) == "IRA")
    {
      applyReduction(i, "D");
      return reduceDecisions();
    }
    else if (robotDecisions.substring(i, i + 3) == "IRI")
    {
      applyReduction(i, "A");
      return reduceDecisions();
    }
    else if (robotDecisions.substring(i, i + 3) == "DRI")
    {
      applyReduction(i, "R");
      return reduceDecisions();
    }
    i++;
  }
}
