/*This is the code running on the arduino end to defferentiate between fire and smoke continously and triggering 
 * the respective fire alarms accordingly. A fire flag (i.e. a 0/1 value in the form of hex code) indicating the 
 * presence of fire is sent from RPi end continously and based on this flag value along with the smoke sensor data 
 * that arduino receives, it decides whether to trigger either of the two two alarms. Thus, leadig to a  differentiation between fire and smoke detection. 
 */

int buzzer_flag = 1;
int fireRead=0;

void setup(){
  Serial.begin(9600);
  pinMode(7,OUTPUT); //For Fire
  pinMode(2,OUTPUT); //For Smoke
  pinMode(A0,INPUT);
  digitalWrite(7,LOW);
  //digitalWrite(2,LOW);
}


void loop(){
  
  int smoke_read=analogRead(A0);
  //Serial.println(smoke_read);
  if (Serial.available()){
        
    int usbRead=Serial.read()-'0'; //Converting incoming hex value to integer (It's the fire flag value 
    // coming from the raspberry pi end continously to indicate about the possibility of fire.)
    //Serial.println(usbRead);
    
    if ((smoke_read > 400) && (usbRead == 1)){
      fire_alarm();
    }
    else if((smoke_read < 400) && (usbRead == 1)){
      fire_alarm();
    }
    else if((smoke_read > 400) && (usbRead != 1)){
      buzzer_alarm();
      buzzer_flag=1;
    }
    else {Serial.println("NO SMOKE AND NO FIRE");}
  }
}


void fire_alarm(){
  for (int x=0;x<3;x++){
    digitalWrite(7,HIGH);
    delay(1000);
    digitalWrite(7,LOW);
    delay(1000);
  }
}
//these are functions not loops, so will be called once only.
void buzzer_alarm(){

  if (Serial.available())
  {
    fireRead=Serial.read()-'0';
  }
    Serial.println(fireRead);
    Serial.println(buzzer_flag);
  
  if ((fireRead==0) && (buzzer_flag==1))
  {for (int x=0;x<3;x++){
    //digitalWrite(7,HIGH);
    digitalWrite(2,HIGH);
    //tone(2, 1000, 200);
    delay(1000);
    //noTone(2);
    digitalWrite(2,LOW);
    delay(1000);
      }
  }
 
  else  {fire_alarm(); buzzer_flag = 0;} // So, even if the smoke is detected after detecting fire, only the fire_alarm will be triggered.
  
}


