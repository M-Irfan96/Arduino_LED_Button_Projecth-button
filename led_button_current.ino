//Arduino_LED_Button_Project


const int ledPin = A0;    
const int buttonPin = 2;  
const int currentPin = A1; 

const float VREF = 5.0;    
const float ZERO_CURRENT_VOLTAGE = 2.5; 
const float SENSITIVITY = 100.0;        
const float R1 = 1000.0;   
const float R2 = 1000.0;   

bool ledState = false;

void setup() {
  pinMode(ledPin, OUTPUT);     
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);          
  digitalWrite(ledPin, LOW);   
}
void loop() {
  static bool lastButtonState = HIGH; 
  bool currentButtonState = digitalRead(buttonPin);

  
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    delay(50); 
    if (digitalRead(buttonPin) == LOW) { 
      ledState = !ledState;             
      digitalWrite(ledPin, ledState);   
    }
  }

  lastButtonState = currentButtonState; 
  
  int rawValue = analogRead(currentPin); 
  float voltage = (rawValue / 1023.0) * VREF; 
  float current = (voltage - ZERO_CURRENT_VOLTAGE) * 1000 / SENSITIVITY; 
  
  int rawVoltage = analogRead(ledPin); 
  float voltageAcrossLoad = (rawVoltage / 1023.0) * VREF * ((R1 + R2) / R2); 

  
  Serial.print("Current: ");
  Serial.print(current, 3);
  Serial.print(" A\t");

  Serial.print("Voltage: ");
  Serial.print(voltageAcrossLoad, 3); 
  Serial.println(" V");

  delay(100); 
}

 

