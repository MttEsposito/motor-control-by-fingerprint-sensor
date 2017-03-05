//**********************************************************************
//          WELCOME THANK YOU FOR DOWNLOAD THE CODE                    *
//          MADE BY MATTIA ESPOSITO                                    *
//          https://github.com/MttEsposito                             *
//          https://www.youtube.com/channel/UCPTNOyJNd_I3DN77ojzRrug   *
//          HAVE A NICE CODING                                         *
//**********************************************************************

//Library for adarfuit sensor
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

int getFingerprintIDez();


// pin #6 is IN from sensor (GREEN wire)
// pin #7 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(6, 7);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
//Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

void setup()  
{
  pinMode(12,OUTPUT); //Channel A Direction Pin Initialize
  pinMode(4,OUTPUT); //Initialize Led
  pinMode(5,OUTPUT); //Initialize Led
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  
  Serial.begin(9600);
  Serial.println("Adafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Waiting for valid finger...");
 
}

void loop()                     // run over and over again
{
  analogWrite(3,0); //motor speed off 
  digitalWrite(4,LOW); //turn led off
  digitalWrite(5,LOW);// turn led off
  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  // ID 1 Pesron finger for adding a new person finger in the code just add  || finger.fingerID == (number of the ID you have stored in the enroll)
  if(finger.fingerID == 1 || finger.fingerID == 3 || finger.fingerID == 5)
  {
    digitalWrite(12, LOW); //Channel A Direction Forward
    analogWrite(3,255); //motor run full speed
    digitalWrite(4, HIGH); //turn led on
    delay (9000);
  }
  // ID 2 Pesron finger for adding a new person finger in the code just add  || finger.fingerID == (number of the ID you have stored in the enroll)
  if(finger.fingerID == 2 || finger.fingerID == 4 || finger.fingerID == 6)
  {
    digitalWrite(12, HIGH); //Channel A Direction Reverse
    analogWrite(3,255); //motor run full speed
    digitalWrite(5,HIGH); //turn led on
    delay(9000);
  }
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
