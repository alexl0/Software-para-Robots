#include <Servo.h>
#define Y_pin A4
#define X_pin A5
#define boton_pin 10

int limite2 = 2;
int limite1 = 12;
int v = 0;
int modoAuto = 0;
int JoystickEjeX;


Servo servo;
int automat;

void setup(){
  modoAuto = 1;
  automat = 1;
  servo.attach(4);
  pinMode(boton_pin, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(limite2, INPUT); 
  pinMode(limite1, INPUT); 
  servo.write(180);
}
void loop(){

  if( digitalRead(boton_pin) == HIGH)
  {
    if(automat==1)
    automat=0;
    else
    automat=1;
  }
  
  if (automat==1)
  {
    if( LOW == digitalRead(limite2) )
    {
      v = 190;
    }
    else if( LOW == digitalRead(limite1) ){
      v = 0;
    }
   servo.write(v);
  }
 else{
      int valorX = analogRead(X_pin);
      int valorY = analogRead(Y_pin);
      JoystickEjeX = valorX;
    
      if( JoystickEjeX < 400 ){
            int v = 80;
          if(JoystickEjeX > 950){
            v = 0;
          }
          Serial.println(v);
          servo.write(v);
      }

      else if( JoystickEjeX <= 600 ){
          servo.write(90);
      }

      else {
                  int v = 80;
          if(JoystickEjeX > 950){
            v = 0;
          }
          Serial.println(v);
          servo.write(v);

      }
 }
}



