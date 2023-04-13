volatile long prev_time = 0;
volatile long curr_time = 0;
volatile uint8_t mode = 0;
volatile uint8_t curr_dig = 0;

struct digit_t {
  uint8_t portd;
  uint8_t portb;
};

const digit_t digits[10] = {
  { 0b11111000, 0b00111101 },  // 0
  { 0b00110000, 0b00111100 },  // 1
  { 0b11011000, 0b00111110 },  // 2
  { 0b01111000, 0b00111110 },  // 3
  { 0b00110000, 0b00111111 },  // 4
  { 0b01101000, 0b00111111 },  // 5
  { 0b11101000, 0b00111111 },  // 6
  { 0b00111000, 0b00111100 },  // 7
  { 0b11111000, 0b00111111 },  // 8
  { 0b01111000, 0b00111111 }   // 9
};

void prtDgt (uint8_t digit, uint8_t num_displ) {
  /*
    **  digitalWrite(i, digit[i])
    */
  PORTD = digits[digit].portd;
  PORTB = digits[digit].portb;

  PORTB &= ~((1 << 2) << num_displ);  // turn on display
}

static uint8_t dgt[4];

void updTime (long time) {
  if (mode == 0) {
    for (uint8_t i = 0; i < 4; i++) { dgt[i] = 0; }
    return;
  }
  if (mode == 2) { return; }

  time -= prev_time;

  for (uint8_t i = 0; i < 4; i++) {
    time /= 10;
    dgt[3 - i] = time % 10;
  }
}

void prtTime () {
  prtDgt(dgt[curr_dig], curr_dig);
  curr_dig = (curr_dig + 1) & 0b00000011;
}

inline void off () {
  PORTD = 0b00000000;
  PORTB = 0b00000000;
}

void ChangeMode () {
  prev_time = millis();
  mode = (mode + 1) % 3;
}

ISR (TIMER2_OVF_vect) {
  off();
  updTime(millis());
  prtTime();
}

void setup () {
  attachInterrupt(0, ChangeMode, RISING);

  /*
    **  pinMode (3, 4, 5, 6, 7, OUTPUT) 
    **  ATTENTION: last byt must be zero
    */
  DDRD = 0b11111000;
  DDRD &= ~0b00000001;

  /*
    **  pinMode (8, 9, 10, 11, 12 13, OUTPUT)
    */

  DDRB = 0b00111111;

  /*
    **  TIMER 2 setup
    */
  cli();

  /*
    ** see here: https://habr.com/ru/articles/453276/
    */
  TCCR2A = 0b00000000;
  TCCR2B = 0b00000100;

  TIMSK2 = (1 << TOIE2);
  sei();
}

void loop () {
  asm("sleep");
  //delay(8000);
}

// "C:\Users\GOD\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude" 
// -C "C:\Users\GOD\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf" -v -V -patmega328p -carduino "-PCOM3" -b115200 -D 
// "-Uflash:w:C:\Users\GOD\AppData\Local\Temp\arduino\sketches\D71003BABFED4D54A2E54EA925B6D938/asmLevel3.ino.hex:i"

