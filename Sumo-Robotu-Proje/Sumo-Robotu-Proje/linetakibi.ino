int led = 8 ;
int parlaklikSensor = A0; 
int parlaklikSensor1 = A1; 
int solmotorHiz = 3;
int solmotorYon = 12;
int sagmotorHiz = 11;
int sagmotorYon = 13;
int Buzzer = 9;

void Set_Motor(float Lval,float Rval) {
    Lval = Lval * 2.5; 
    Rval = Rval * 2.5; 
    if (Lval >= 0) {
        analogWrite(solmotorHiz, Lval); //bizim elimizdeki A/D cevirici 1024 kadar deger aldigi icin 5V icin 1024, 0V icin ) gondermemiz gerek.
        digitalWrite(solmotorYon, LOW); // motora yon pininden 1 gondererek motoru ileri hareket ettirdik.
          
    } else { //eksi bir deger gelirse motor geriye dogru hareket edecegini anlar
        Lval = abs(Lval); //fakat analog calisan pinlere eksi deger gonderilmez bunun icin abs diyerek fonksiyona eksi gelen degeri arti yapiyoruz.
        digitalWrite(solmotorYon, HIGH); // motora yon pininden 0 gondererek motoru geriye hareket ettirdik.
        analogWrite(solmotorHiz, Lval); // geri yonde verilen Lval degerine gore hareket ettirdigimiz fonksiyon.
    }
     if (Rval >= 0) {    
      analogWrite(sagmotorHiz, Rval);  
      digitalWrite(sagmotorYon, HIGH);       
      } else {
      Rval=abs(Rval);     
      digitalWrite(sagmotorYon, LOW);  
      analogWrite(sagmotorHiz, Rval); 
      }   
}

void setup () {
   pinMode(led , OUTPUT); // set the digital pin as output
   pinMode(parlaklikSensor , INPUT);
   pinMode(parlaklikSensor1 , INPUT);
   pinMode(solmotorHiz, OUTPUT);
   pinMode(solmotorYon, OUTPUT);
   pinMode(sagmotorHiz, OUTPUT);
   pinMode(sagmotorYon, OUTPUT);
   Serial.begin(9600);
    tone(9, 523, 300);
  delay(300);
  noTone(9);
}
void loop () {
  Start:

    if (analogRead(parlaklikSensor)>100 && analogRead(parlaklikSensor1)>100 ){
      Set_Motor (-50,50);
    }
    else if (analogRead(parlaklikSensor)<100 && analogRead(parlaklikSensor1)>100 ){
      Set_Motor (-50,0);
    }
    else if (analogRead(parlaklikSensor)>100 && analogRead(parlaklikSensor1)<100 ){
      Set_Motor (0,50);
    }
    else if (analogRead(parlaklikSensor)<100 && analogRead(parlaklikSensor1)<100 ){
      Set_Motor (50,-50);
    }
   // else if (analogRead(parlaklikSensor)<100 && analogRead(parlaklikSensor1)<100 ){
      //Set_Motor (0,0);
    //}
    
    goto Start;
  }
