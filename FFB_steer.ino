#define outputA 6
#define outputB 7

#define RPWM 8
#define LPWM 9
#define R_EN 10
#define L_EN 11
#define R_IS 12
#define L_IS 13

#define buttonA 4
#define buttonB 5

int counter = 0; 
int aState;
int aLastState;  

int accState = 0;
int bacState = 0;

void setup(){ 
   pinMode(outputA,INPUT);
   pinMode(outputB,INPUT);

   pinMode(buttonA,INPUT);
   pinMode(buttonB,INPUT);

   pinMode(RPWM, OUTPUT);
   pinMode(LPWM, OUTPUT);
   pinMode(R_EN, OUTPUT);
   pinMode(L_EN, OUTPUT);
   pinMode(R_IS, OUTPUT);
   pinMode(L_IS, OUTPUT);

   digitalWrite(R_IS, LOW);
   digitalWrite(L_IS, LOW);
   digitalWrite(R_EN, HIGH);
   digitalWrite(L_EN, HIGH);
   
   Serial.begin(9600);
   aLastState = digitalRead(outputA);   
} 

void loop() { 
   String msg = ":";
   
   aState = digitalRead(outputA);
   if(aState != aLastState){
     if(digitalRead(outputB) != aState) { 
       counter ++;
     }else{
       counter --;
     }
   } 
   aLastState = aState;

   accState = digitalRead(buttonA);
   if(accState==HIGH){
     msg += "1:";
   }else{
     msg += "0:";
   }

   bacState = digitalRead(buttonB);
   if(bacState==HIGH){
     msg += "1";
   }else{
     msg += "0";
   }
   
   Serial.println(counter+msg);

   int pwm = 155;
   if(counter<0){
     pwm += counter*(-1);
   }else{
     pwm += counter;
   }
   if(pwm>255) pwm = 255;

   if(counter<0){
     analogWrite(RPWM, pwm);
     analogWrite(LPWM, 0);
   }else if(counter>0){
     analogWrite(RPWM, 0);
     analogWrite(LPWM, pwm);
   }else{
     analogWrite(RPWM, 0);
     analogWrite(LPWM, 0);
   }
   delay(10);
}
