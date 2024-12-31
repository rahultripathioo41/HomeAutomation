#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN    9
#define SS_PIN     10
#define inputpin   6
#define motor      1
#define outpin     7
#define light      3
#define motor2     2
#define doorbeeper 5

Servo door;
Servo window;
int person = 0;
int flag = 0;

// Initialize the RFID module
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(inputpin, INPUT);
  pinMode(outpin, INPUT);
  door.attach(motor);
  pinMode(doorbeeper, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(light, OUTPUT);

  Serial.println("System Ready. Waiting for RFID cards...");
}

void lighton() {
  digitalWrite(light, HIGH);
}

void lightoff() {
  digitalWrite(light, LOW);
}

void dooropen() {
  for (int i = 180; i > 90; i--) {
    door.write(i);
    delay(15);
  }
  tone(doorbeeper, 1000);
  delay(500);
  noTone(doorbeeper);
}

void doorclose() {
  for (int i = 90; i < 180; i++) {
    door.write(i);
    delay(15);
  }
}

// Function to check RFID card access
bool checkRFIDAccess() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return false; // No RFID card detected
  }

  String cardID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    cardID += String(rfid.uid.uidByte[i], HEX); // Convert RFID UID to a string
  }
  cardID.toUpperCase();
  rfid.PICC_HaltA();

  // Check against a predefined valid card ID
  String validCard = "F347EE11"; // Replace with the valid card's UID
  return cardID == validCard;
}

void loop() {
  if (person < 0) {
    person = 0;
  }
  
  Serial.println(person);

  if (person > 0) {
    lighton();
  } else {
    lightoff();
  }
  

  if (checkRFIDAccess()) { // Access granted by RFID card
    dooropen();
    int c = 0;

    while (digitalRead(outpin) != LOW && c < 5000) {
      delay(250);
      c += 250;
    }

    if (c >= 5000 && flag == 0) {
      flag = 1;
    }

    if (flag == 1) {
      delay(250);
      flag = 0;
    } else if (c < 5000) {
      delay(500);
      person += 1;
      doorclose();
    }
  }

  if (digitalRead(outpin) == LOW) {
    dooropen();
    int c = 0;

    while (digitalRead(inputpin) != LOW && c < 2000) {
      delay(250);
      c += 250;
    }

    if (c < 2000) {
      delay(500);
      person -= 1;
      doorclose();
    } else {
      doorclose();
    }
  }
}
