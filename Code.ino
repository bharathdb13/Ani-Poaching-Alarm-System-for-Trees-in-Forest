#define xPin A0
#define yPin A1
#define zPin A2

//use calibration.ino file to get these values
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMM
int xMin = 266;
int xMax = 400;
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMM
int yMin = 273;
int yMax = 408;
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMM
int zMin = 269;
int zMax = 402;
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//--------------------------------------------------------------
// Take multiple samples to reduce noise
const int samples = 10;

int FLAME = 3;
int SOUND = A3;
int BUZZER = 13;
int RELAY = 5;

int isFlame = HIGH;
int micValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(FLAME, INPUT);
  pinMode(SOUND, INPUT);
  pinMode(RELAY, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //accelerometer 
  int xRaw=0,yRaw=0,zRaw=0;
  for(int i=0;i<samples;i++)
  {
    xRaw+=analogRead(xPin);
    yRaw+=analogRead(yPin);
    zRaw+=analogRead(zPin);
  }
  xRaw/=samples;
  yRaw/=samples;
  zRaw/=samples;

  //--------------------------------------------------------------
  //Convert raw values to 'milli-Gs"
  //Convert value of RawMin to -1000
  //Convert value of RawMax to 1000
  long xMilliG = map(xRaw, xMin, xMax, -1000, 1000);
  long yMilliG = map(yRaw, yMin, yMax, -1000, 1000);
  long zMilliG = map(zRaw, zMin, zMax, -1000, 1000);

  Serial.print(xRaw);
  //Serial.print(x_g_value,2);
  Serial.print("G");
  Serial.print("\t");
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  Serial.print(yRaw);
  //Serial.print(y_g_value,2);
  Serial.print("G");
  Serial.print("\t");
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  Serial.print(zRaw);
  //Serial.print(z_g_value,2);
  Serial.println("G");
  //Serial.println();
  delay(1000);
  //acceleometer ends here

  micValue = analogRead(SOUND);
  int x = micValue*50;
  isFlame = digitalRead(FLAME);
  Serial.print("Flame Value is: "); Serial.println(isFlame);
  Serial.print("Sound value in dB is: "); Serial.println(x);
  //delay(1000); //1 sec of delay
  if((isFlame == LOW) )
  {
    //digitalWrite(BUZZER, HIGH);
    digitalWrite(RELAY, LOW);
    Serial.println("TEMPERATURE is increased.....!!!");
    delay(1000);
  }
  else if(x >= 20000)
  {
    digitalWrite(BUZZER, HIGH);
    Serial.println("SOUND is detected......!!!!");
    delay(1000);
  }
  else
  {
    digitalWrite(BUZZER, LOW);
    digitalWrite(RELAY,HIGH);
    Serial.println("Normal condition.......!!!!");
    delay(1000);
  }

  
}
