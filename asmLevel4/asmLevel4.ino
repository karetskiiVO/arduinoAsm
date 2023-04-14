extern "C" {
  extern inline void       off();
  extern inline void      Init();
  extern inline void    prtDgt(uint8_t digit, uint8_t num_displ);
}
//extern uint8_t Get();

volatile long prev_time = 0;
volatile long curr_time = 0;
volatile uint8_t mode = 0;
volatile uint8_t curr_dig = 0;

static uint8_t dgt[4];

void updTime(long time) {
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

void prtTime() {
  prtDgt(dgt[curr_dig], curr_dig);
  curr_dig = (curr_dig + 1) & 0b00000011;
}

void ChangeMode() {
  prev_time = millis();
  mode = (mode + 1) % 3;
}

ISR(TIMER2_OVF_vect) {
  off();
  updTime(millis());
  prtTime();
}

void setup() {
  attachInterrupt(0, ChangeMode, RISING);
  Init();
}


void loop() {
  
}





