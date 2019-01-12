// Made By Berat Dikmen
const int trigger_pin_sol= 3; 
const int echo_pin_sol=4;
const int trigger_pin_sag=7;
const int echo_pin_sag=8;
const int trigger_pin_on=5;
const int echo_pin_on=6;


int sol_motor=0;
int sag_motor=1;

const int sol_i = 9; // motor sürücü pinleri 
const int sol_g = 10;
const int sag_i = 11;
const int sag_g = 12;
long sure_sol;
long sure_on;
long sure_sag;

int mesafe_sol; //sensörlerin algıladığı mesafeler
int mesafe_sag;
int mesafe_on;

void sol_mesafe(){
  digitalWrite(trigger_pin_sol, LOW); //sensör pasif hale getirildi
  delayMicroseconds(5);
  digitalWrite(trigger_pin_sol, HIGH); //Sensore ses dalgasının üretmesi için emir verildi
  delayMicroseconds(10);
  digitalWrite(trigger_pin_sol, LOW); //Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi
  sure_sol=pulseIn(echo_pin_sol,HIGH);
  mesafe_sol=sure_sol/29.1/2;
}
void sag_mesafe(){
  digitalWrite(trigger_pin_sag, LOW); //sensör pasif hale getirildi
  delayMicroseconds(5);
  digitalWrite(trigger_pin_sag, HIGH); //Sensore ses dalgasının üretmesi için emir verildi
  delayMicroseconds(10);
  digitalWrite(trigger_pin_sag, LOW); //Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi
  sure_sag=pulseIn(echo_pin_sag,HIGH);
  mesafe_sag=sure_sag/29.1/2;
}
void on_mesafe(){
  digitalWrite(trigger_pin_on, LOW); //sensör pasif hale getirildi
  delayMicroseconds(5);
  digitalWrite(trigger_pin_on, HIGH); //Sensore ses dalgasının üretmesi için emir verildi
  delayMicroseconds(10);
  digitalWrite(trigger_pin_on, LOW); //Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi
  sure_on=pulseIn(echo_pin_on,HIGH);
  mesafe_on=sure_on/29.1/2;
}
void sola_don(){
     digitalWrite(sol_i ,  LOW);//sola dön
     digitalWrite(sol_g , HIGH);
     analogWrite(sol_motor,150);
     digitalWrite(sag_i , HIGH);
     digitalWrite(sag_g , LOW);
     analogWrite(sag_motor,150);
}

void saga_don(){
     digitalWrite(sol_i ,  HIGH);//sağa dön
     digitalWrite(sol_g , LOW);
     analogWrite(sol_motor,150);
     digitalWrite(sag_i , LOW);
     digitalWrite(sag_g , HIGH);
     analogWrite(sag_motor,150);
     
}
void geri(){
     digitalWrite(sol_i ,  LOW);
     digitalWrite(sol_g , HIGH);
     analogWrite(sol_motor,100 );
     digitalWrite(sag_i ,  LOW);
     digitalWrite(sag_g , HIGH);
     analogWrite(sag_motor,100);
  
}
void ileri(){
     digitalWrite(sol_i ,  HIGH);
     digitalWrite(sol_g , LOW);
     analogWrite(sol_motor,150);
     digitalWrite(sag_i ,  HIGH);
     digitalWrite(sag_g , LOW);
     analogWrite(sag_motor,150);
}

void setup() {
  Serial.begin(9600);
  pinMode(trigger_pin_sol,OUTPUT);
  pinMode(trigger_pin_sag,OUTPUT);
  pinMode(trigger_pin_on,OUTPUT);
  pinMode(echo_pin_on,INPUT); 
  pinMode(echo_pin_sag,INPUT);
  pinMode(echo_pin_sol,INPUT);
  pinMode(sol_motor,OUTPUT);
  pinMode(sag_motor,OUTPUT);
  pinMode(sol_i,OUTPUT);
  pinMode(sol_g,OUTPUT);
  pinMode(sag_i,OUTPUT);
  pinMode(sag_g,OUTPUT);
  ileri();
}

void loop() {
  sol_mesafe();
  sag_mesafe();
  on_mesafe();
  


  if ( mesafe_on < 25 && mesafe_sag  <25 && mesafe_sol <25) // obstacle infront of all 3 sides
{
geri (); //then reverse
delay(100);
}
else if (mesafe_on <22 && mesafe_sag  <22 && mesafe_sol >22) // obstacle on right and front sides
{
sola_don (); // turn left side
delay(100);
}
else if ( mesafe_on < 22 && mesafe_sag >22 && mesafe_sol <22) // obstacle on left and front sides
{
saga_don ();
delay(100);
}
else if ( mesafe_on < 22 && mesafe_sag  >22 && mesafe_sol >22) // obstacle on front sides
{
saga_don ();
delay(100);
}
else if ( mesafe_on > 22 && mesafe_sag  >22 && mesafe_sol <22) // obstacle on left sides
{
saga_don ();
// then turn right and then forward
delay(100);
}
else if ( mesafe_on > 22 && mesafe_sag  <22 && mesafe_sol >22) // obstacle on right sides
{
sola_don ();
delay(100);
}
 else{
    ileri();
  }

}
