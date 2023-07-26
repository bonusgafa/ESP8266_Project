//Mustafa Taha Küyük - Proje Motor Sensör

#include <Stepper.h>

int LED = D1;              // D1 pinindeki LED
int isObstaclePin = D2;    // Engel sensörü pin
int isObstacle = HIGH;     // YÜKSEK DEĞER ENGEL YOK DEMEKTİR
int Button = D4;           // Buton Pin   
const int stepMotorPin1 = D5; // Adım motoru kontrol pini 1 için GPIO8'i kullan
const int stepMotorPin2 = D6; // Adım motoru kontrol pini 2 için GPIO10'u kullan
const int stepMotorPin3 = D7; // Adım motoru kontrol pini 3 için GPIO9'u kullan
const int stepMotorPin4 = D8; // Adım motoru kontrol pini 4 için GPIO11'i kullan

const int stepsPerRevolution = 2048; // Adım motoru için bir devirdeki adım sayısı
Stepper myStepper(stepsPerRevolution, stepMotorPin2, stepMotorPin4, stepMotorPin1, stepMotorPin3);

volatile int encoderPos = 0;
volatile int encoderLastPos = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Button, INPUT_PULLUP); // Dahili Pull-up direnç kullanarak butonu bağlayın
  pinMode(isObstaclePin, INPUT);
  Serial.begin(9600);
}

void loop() {
  kizilotesi();
  motor();
}

void kizilotesi() {
  isObstacle = digitalRead(isObstaclePin);
  if (isObstacle == LOW) {
    Serial.println("ENGEL!!, ENGEL!!");
  } else {
    Serial.println("temiz");
  }
}

void motor() {
  int sensorValue = digitalRead(isObstaclePin); // Sensör değerini oku
  int buttonState = digitalRead(Button); // Buton durumunu oku

  if (sensorValue == LOW && buttonState == LOW) { // Eğer sensör değeri LOW ve buton basılıysa (hem sensör hem de buton aktifse)
    // LED'i hızlıca yanıp söndür
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(100);
    }
    return; // Fonksiyonu burada sonlandır
  }

  if (sensorValue == LOW) { // Eğer sensör değeri LOW ise (engel algılandıysa)
    digitalWrite(LED, HIGH); // Ledi kapat
    myStepper.setSpeed(10); // Motor hızını 5 RPM olarak ayarla (isterseniz farklı bir hız verebilirsiniz)
    myStepper.step(100); // 100 adım ileriye hareket ettir (isterseniz farklı adet adım verebilirsiniz)
  } 
  else if (buttonState == LOW){ // Eğer butona basılmışsa (hem sensör hem de buton aktifse)
    digitalWrite(LED, LOW); // Ledi yak
    myStepper.setSpeed(10); // Motor hızını 5 RPM olarak ayarla (isterseniz farklı bir hız verebilirsiniz)
    myStepper.step(-100); // 100 adım geriye hareket ettir (isterseniz farklı adet adım verebilirsiniz)
  }
  else{
    digitalWrite(LED, LOW);
  }
}