#define REG_SIZE 8
#define DRAWS 25

#define ADC2_pin 4
#define DS_pin 2
#define STCP_pin 0
#define SHCP_pin 1
#define BTN_pin 3

// 1 -> 0b00000001
// 2 -> 0b00000010
// 3 -> 0b00000011
// 4 -> 0b00000100
// 5 -> 0b00000101
// 6 -> 0b00000110

void write_reg(int reg){
    digitalWrite(SHCP_pin, LOW);
    for (int i = 0; i < REG_SIZE; i++) {
        digitalWrite(STCP_pin, LOW);
        digitalWrite(DS_pin, ((0b10000000 >> i) & reg));
        digitalWrite(STCP_pin, HIGH);
    }
    digitalWrite(SHCP_pin, HIGH);
}


void setup() {
  pinMode(ADC2_pin, INPUT);
  randomSeed(analogRead(A2)); // https://forum.arduino.cc/index.php?topic=493242.0
  
  pinMode(BTN_pin, INPUT);
  
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  
  write_reg(0);
}

void loop() {
  if(digitalRead(BTN_pin) == LOW) {
    for (int draw = 0; draw < DRAWS; draw++) {
       int reg = random(1, 7) << 1;
       reg = reg | (random(1, 7) << 5);
       write_reg(reg);
       delay(5 + 5*draw);
       // add more delay for last 3 draws
       if(draw + 3 >= DRAWS) {
         delay(100);
       }
    }
  }
  delay(10);
}
