#include <Servo.h>

const int trigPin = 2;
const int echoPin = 3;
Servo myServo;
unsigned long openTime = 0; // Variabel untuk menyimpan waktu terakhir palang terbuka
const int buzzerPin = 4;

const int ledPin = 5;
const int BlueledPin = 6;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(9);
  myServo.write(0); // Set servo ke posisi awal (palang tertutup)
   pinMode(buzzerPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(BlueledPin,OUTPUT);

   Serial.begin(9600);
}

void loop() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration / 2) / 29.1;

  if (distance <= 10) { // Jarak kurang dari atau sama dengan 10 cm
    myServo.write(90); // Sudut rotasi servo untuk membuka palang
    openTime = millis(); // Simpan waktu terakhir palang terbuka
    digitalWrite(buzzerPin, HIGH);

    for (int i = 0; i < 5; i++) {
      digitalWrite(ledPin, HIGH); // Nyalakan LED
      delay(500); // Waktu LED menyala
      digitalWrite(ledPin, LOW); // Matikan LED
      delay(500); // Waktu LED mati
    }
 digitalWrite(BlueledPin, LOW); // Matikan LED

  } else {
    unsigned long currentTime = millis(); // Waktu saat ini
    if (currentTime - openTime >= 3000) { // Jika waktu terakhir palang terbuka lebih dari 10 detik yang lalu
      myServo.write(0); // Sudut rotasi servo untuk menutup palang
     digitalWrite(buzzerPin, LOW);

      digitalWrite(ledPin, LOW); // Matikan LED

 for (int i = 0; i < 5; i++) {
      digitalWrite(BlueledPin, HIGH); // Nyalakan LED
      delay(500); // Waktu LED menyala
      digitalWrite(BlueledPin, LOW); // Matikan LED
      delay(500); // Waktu LED mati
    }

    }
  }
 Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500); // Interval pembacaan sensor
}
