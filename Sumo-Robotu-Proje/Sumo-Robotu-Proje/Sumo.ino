
//MOTOR CONTROL
int RPwm = 11;
int RDir = 13;
int LPwm = 3;
int LDir = 12;

//LED & BUZZER
int Buzzer = 9;
int ArduLed = 8;

//EDGE & CONTRAST SENSORS
int Redge = A0;
int Ledge = A1;

//TRIMPOTS
int SPD = A7;
int TRN = A6;

//OPPONENT SENSORS
int LSens = A2;
int RSens = A4;
int MSens = A3;

int LFSens = A5;
int RFSens = 4;

//VALUES
int Speed =50;
int MaxSpeed = 50; // Idle Speed while no sensor giving data.
int TurnSpeed = 55; // Left and Right Forward Turning Speed
int EdgeTurn = 190; // Turning Time variable when minisumo sees white line
int Duration; // Turning Time at minisumo starting.
int LastValue = 5; // Last Value Variable for remembering last Opponent sensor sense.

void setup()
{

pinMode(LSens, INPUT);    // Left Opponent Sensor Input
pinMode(RSens, INPUT);    // Right Opponent Sensor Input
pinMode(MSens, INPUT);    // Middle Opponent Sensor Input

pinMode(Buzzer, OUTPUT);  // Buzzer Declared as Output
pinMode(ArduLed, OUTPUT); // Buzzer Declared as Output

pinMode(RPwm, OUTPUT);  // Four PWM Channel Declared as Output
pinMode(RDir, OUTPUT); 
pinMode(LPwm, OUTPUT); 
pinMode(LDir, OUTPUT); 

digitalWrite(Buzzer, LOW); // Buzzer Pin Made Low for Silence :)
digitalWrite(ArduLed, LOW);  // Arduino Mode Led Made Low


digitalWrite(LSens, HIGH); // Opponent Sensor Pullups Made
digitalWrite(RSens, HIGH); 
digitalWrite(LFSens, HIGH); 
digitalWrite(RFSens, HIGH); 
digitalWrite(MSens, HIGH); 
Serial.begin(9600);
 tone(9, 523, 300);
  delay(300);
  noTone(9);
}

//Motor Control Function
void Set_Motor (float Lval, float Rval, int timex){
  Lval = Lval*2.5;
  Rval = Rval*2.5; 
  if (Lval >=0) { 
      analogWrite(LPwm, Lval);  
      digitalWrite(LDir, LOW);       
      } else {
      Lval=abs(Lval); 
      digitalWrite(LDir, HIGH);  
      analogWrite(LPwm, Lval); 
      }
   if (Rval >=0) {    
      analogWrite(RPwm, Rval);  
      digitalWrite(RDir, HIGH);       
      } else {
      Rval=abs(Rval);     
      digitalWrite(RDir, LOW);  
      analogWrite(RPwm, Rval); 
      }   
   delay(timex);  
}
void loop() {
Start:
  /// Edge Sensor Control Routine ///
  digitalWrite(ArduLed, LOW);
 if (analogRead(Ledge) < 100 && analogRead(Redge) > 100) {
   digitalWrite(Buzzer, LOW);
   digitalWrite(ArduLed, HIGH);
   Set_Motor(-50, -50,35); // Geri   
   Set_Motor(-50, 50, EdgeTurn); // Left Backward, Right Forward, Turning Time Based on ETRN Trimpot
   LastValue=5;
 }
   else  if (analogRead(Ledge) > 100 && analogRead(Redge) < 100) {
     digitalWrite(Buzzer, LOW);
     digitalWrite(ArduLed, HIGH);
   Set_Motor(-50, -50,35); // Back 35 Milliseconds
   Set_Motor(50, -50, EdgeTurn); // Right Backward, Left Forward, Turning Time Based on ETRN Trimpot
   LastValue=5;
  }
   else  if (analogRead(Ledge) < 100 && analogRead(Redge) < 100) {
     digitalWrite(Buzzer, LOW);
     digitalWrite(ArduLed, HIGH);
   Set_Motor(50, 50,35); // Back 35 Milliseconds    
   Set_Motor(50, -50, EdgeTurn); // Right Backward, Left Forward, Turning Time Based on ETRN Trimpot
    LastValue=5; 
    
 }else
/// Opponent Sensor Control Routine ///
if (digitalRead(MSens)==LOW) {Set_Motor(MaxSpeed, MaxSpeed,1); digitalWrite(Buzzer, HIGH); LastValue=5;} else
if (digitalRead(LSens)== LOW) {Set_Motor(-40, TurnSpeed,1); digitalWrite(Buzzer, HIGH); LastValue=7;} else
if (digitalRead(RSens)==LOW) {Set_Motor(TurnSpeed, -40,1); digitalWrite(Buzzer, HIGH); LastValue=3;} else
if (digitalRead(LFSens)== LOW) {Set_Motor(-40, TurnSpeed,1); digitalWrite(Buzzer, HIGH); LastValue=7;} else
if (digitalRead(RFSens)==LOW) {Set_Motor(TurnSpeed, -40,1); digitalWrite(Buzzer, HIGH); LastValue=3;} else
{
digitalWrite(Buzzer, LOW);

Speed=(analogRead(SPD)/10.3); // This raw speed value comes with 0 to 1023 so we divide to 10.3 After that it is 0 to 99 integer.
Speed=100-Speed; // This is used for reversing trimpot dial direction at board.

if (LastValue==5) { Set_Motor(Speed, Speed,1);} else // Forward, Based on SPD (A7) Trimpot
if (LastValue==7) { Set_Motor(-20, Speed,2);} else // Left Turning Based on SPD (A7) Trimpot
if (LastValue==3) { Set_Motor(Speed, -20,2);} // Right Turning Based on SPD (A7) Trimpot
}
goto Start;
}
