const int CrvenaPinNo = 13;
const int ZutaPinNo = 12;
const int ZelenaPinNo = 11;
const int CrvenaPinNo2 = 6;
const int ZelenaPinNo2 = 5;
const int DugmePinNo = 2;

volatile int stanjeZuta = LOW; // u neaktivnom stanju zuta dioda treperi

const int VremeZeleno = 10000;
const int VremeZuto = 3000;
const int VremeZelenoPesak = 10000;
const int VremeZaPromenu = 2000;
const int VremeZaPromenu2 = 1000;
const int VremeZutaTreperi = 500;

unsigned long pocetno;
unsigned long trenutno;
unsigned long vreme;

String poruka = "";

volatile bool dugmeAktivno = false;
bool pocetnoStanje = false;
bool neaktivnoStanje = false;

void promeni(){
  if(!neaktivnoStanje){//ukoliko je deaktiviran semafor
  	dugmeAktivno = true;//pritisak na dugme nema funkciju
  } 
}

void setup()
{
  Serial.begin(9600);
  pinMode(CrvenaPinNo, OUTPUT);
  pinMode(ZutaPinNo, OUTPUT);
  pinMode(ZelenaPinNo, OUTPUT);
  pinMode(CrvenaPinNo2, OUTPUT);
  pinMode(ZelenaPinNo2, OUTPUT);
  pinMode(DugmePinNo, INPUT);
  
  digitalWrite(CrvenaPinNo, LOW);
  digitalWrite(ZutaPinNo, LOW);
  digitalWrite(ZelenaPinNo, LOW);
  digitalWrite(CrvenaPinNo2, LOW);
  digitalWrite(ZelenaPinNo2, LOW);
  
  attachInterrupt(digitalPinToInterrupt(DugmePinNo), promeni, FALLING);
  
}

void aktivan(){
  	trenutno = millis();
    vreme = trenutno - pocetno;
    while(vreme<VremeZeleno){//provera da li je proslo 10s
      trenutno = millis();
      vreme = trenutno - pocetno;
   	}
 	
    digitalWrite(ZelenaPinNo, LOW);
    digitalWrite(ZutaPinNo, HIGH);
    delay(VremeZuto);
 
    digitalWrite(ZutaPinNo, LOW);
    digitalWrite(CrvenaPinNo, HIGH);
   	delay(VremeZaPromenu);
    
    digitalWrite(CrvenaPinNo2, LOW);
    digitalWrite(ZelenaPinNo2, HIGH);
    delay(VremeZelenoPesak);
    
    digitalWrite(ZelenaPinNo2, LOW);
    digitalWrite(CrvenaPinNo2, HIGH);
    delay(VremeZaPromenu2);
    
    digitalWrite(CrvenaPinNo, LOW);
    digitalWrite(ZutaPinNo, HIGH);
    delay(VremeZuto);
    
    digitalWrite(ZutaPinNo, LOW);
    digitalWrite(ZelenaPinNo, HIGH); 
  	
  	pocetno = millis();
  
    dugmeAktivno = false;
}

void neaktivan(){
  //gase se sve lampice
  digitalWrite(CrvenaPinNo, LOW);
  digitalWrite(ZutaPinNo, LOW);
  digitalWrite(ZelenaPinNo, LOW);
  digitalWrite(CrvenaPinNo2, LOW);
  digitalWrite(ZelenaPinNo2, LOW);
  
  //promenljiva koja onemogucava pešaka da promeni stanje na semaforu 
  neaktivnoStanje = true;
  
  while(poruka=="0"){
  	stanjeZuta = !stanjeZuta;
  	digitalWrite(ZutaPinNo, stanjeZuta);
  	delay(VremeZutaTreperi);
    if(Serial.available()>0){
  	  poruka = Serial.readString();
  	}
  }
}

void loop()
{
  if(Serial.available()>0){
  	poruka = Serial.readString();
  }
    if(poruka == "1"){
      if(!pocetnoStanje){
        digitalWrite(CrvenaPinNo, LOW);
        digitalWrite(ZutaPinNo, LOW);
        digitalWrite(ZelenaPinNo, HIGH);
        digitalWrite(CrvenaPinNo2, HIGH);
        digitalWrite(ZelenaPinNo2, LOW);
        pocetno = millis();//pocinje da meri vreme za zeleno svetlo za vozila
        pocetnoStanje = true;
      }
      if(dugmeAktivno){
        aktivan();
      }
    }else if(poruka == "0"){
      neaktivan();
      pocetnoStanje = false;
      neaktivnoStanje = false;
    }
  
}