int analogPin = 5;//analog pin input on the board
int raw = 0;
int vin = 5;//Input voltage
float vout = 0; //output voltage
float Rknown = 100000;
float Runknown = 0;
float buffer = 0;
int arr[10];
int count = 0;
float Rave = 0;
float sum = 0;
int ledGreen = 4;
int ledRed = 3;
boolean hasRun = false;
void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  Serial.begin(9600);
  Serial.println("Do not remove resistor, Resistance being measured!");
}
void loop() {
  while (count <= 10) {
    digitalWrite(ledRed, HIGH);
    raw = analogRead(analogPin);
    if (raw && count != 10) {
      buffer = raw * vin;
      vout = (buffer) / 1024.0;
      buffer = (vin / vout) - 1;
      Runknown = Rknown * buffer;
      arr[count] = Runknown;
      count++;
      delay(1000);
      Serial.println(arr[count - 1]);
      sum += arr[count - 1];
    }
    if (count == 10) {
      Rave = sum / 10;
      Serial.print("R average = ");
      Serial.println(Rave);
      Serial.println("Resistor safe to remove now");
      for(int i =1; i < 10; i++){
        digitalWrite(ledRed, LOW);
        Serial.println(i);
        digitalWrite(ledGreen, HIGH);
        delay(1000);
        digitalWrite(ledGreen, LOW);
      }
      count = 0;
      sum = 0;
      Rave = 0;
      Serial.println("Do not remove resistor, Resistance being measured!");
    } 
  }
}
