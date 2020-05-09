const int CrvenaPinNo = 13;
const int ZelenaPinNo = 12;
const int DugmePinNo = 2;

volatile int stanjeCrvena = LOW;
volatile int stanjeZelena = HIGH;

void promeni(){
  stanjeCrvena = !stanjeCrvena;
  stanjeZelena = !stanjeZelena;
  digitalWrite(CrvenaPinNo, stanjeCrvena);
  digitalWrite(ZelenaPinNo, stanjeZelena);
  if(stanjeZelena){
  	Serial.print(1,DEC);//salje poruku da aktivira semafor
  }else{
  	Serial.print(0,DEC);//salje poruku da deaktivira semafor
  }
}

void setup()
{
  Serial.begin(9600);
  
  pinMode(CrvenaPinNo, OUTPUT);
  pinMode(ZelenaPinNo, OUTPUT);
  pinMode(DugmePinNo, INPUT);
  
  digitalWrite(CrvenaPinNo, stanjeCrvena);
  digitalWrite(ZelenaPinNo, stanjeZelena);
  
  Serial.print(1,DEC);//salje poruku da aktivira semafor
  attachInterrupt(digitalPinToInterrupt(DugmePinNo), promeni, FALLING);
}

void loop()
{
}