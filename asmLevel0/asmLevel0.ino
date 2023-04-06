class NUMpad {
  #define SEGM_SIZE 7
  #define DIGT_SIZE 4

  //uint8_t a, b, c, d, e, f, d1, d2, d3, d4;
  uint8_t _segment[SEGM_SIZE], _digit[DIGT_SIZE]; 

  const byte _digits[10] = 
    {0b00111111, 0b00000110,
     0b01011011, 0b01001111,
     0b01100110, 0b01101101,
     0b01111101, 0b00000111,
     0b01111111, 0b01101111};

public:
  NUMpad (uint8_t a, uint8_t b,
          uint8_t c, uint8_t d,
          uint8_t e, uint8_t f,
          uint8_t g,
          uint8_t d1, uint8_t d2,
          uint8_t d3, uint8_t d4) {
    _segment[0] = a;
    _segment[1] = b;
    _segment[2] = c;
    _segment[3] = d;
    _segment[4] = e;
    _segment[5] = f;
    _segment[6] = g;

    _digit[0] = d1;
    _digit[1] = d2;
    _digit[2] = d3;
    _digit[3] = d4;

    for (int i = 0; i < SEGM_SIZE; i++) {
      pinMode(_segment[i], OUTPUT);
    }

    for (int i = 0; i < 4; i++) {
      pinMode(_digit[i], OUTPUT);
    }
  }

  NUMpad (uint8_t start_segment, uint8_t start_digit)
  : NUMpad (start_segment + 0, start_segment + 1,
            start_segment + 2, start_segment + 3,
            start_segment + 4, start_segment + 5,
            start_segment + 6,
            start_digit + 0,   start_digit + 1,
            start_digit + 2,   start_digit + 3) {
  }

  void printDigit (uint8_t num, uint8_t digit) {
    for (int i = 0; i < 4; i++) {
      if (i == digit) {
        digitalWrite(_digit[i], LOW);
      } else {
        digitalWrite(_digit[i], HIGH);
      }
    }

    for (int i = 0; i < SEGM_SIZE; i++) {
      digitalWrite(_segment[i], (_digits[num] >> i) & 1);
    }
  }

  void _off () {
    for (int i = 0; i < SEGM_SIZE; i++) {
      digitalWrite(_segment[i], LOW);
    }
    for (int i = 0; i < DIGT_SIZE; i++) {
      digitalWrite(_digit[i], HIGH);
    }
  }

  void off () {
    for (int i = 0; i < DIGT_SIZE; i++) {
      digitalWrite(_digit[i], HIGH);
    }
  }

  /*
  **  time in mileseconds
  */
  void printtimef (unsigned long time) {
    byte buf[DIGT_SIZE];
    for (int i = DIGT_SIZE - 1; i >= 0; i--) {
      time /= 10;
      buf[i] = time % 10;
    }

    for (int i = 0; i < DIGT_SIZE; i++) {
      this->printDigit(buf[i], i);
      delayMicroseconds(10);
      this->_off();
    }
  }

  void _printtimef (unsigned long time) {
    byte buf[DIGT_SIZE];
    time /= 1000;
    unsigned long sec = time % 60;
    time /= 60;
    unsigned long min = time;

    buf[3] = sec % 10;
    buf[2] = sec / 10;
    buf[1] = min % 10;
    buf[0] = min / 10; 


    for (int i = 0; i < DIGT_SIZE; i++) {
      this->printDigit(buf[i], i);
      delay(1);
      this->_off();
    }
  }
};

NUMpad aboba(2, 9);

void setup() {

}

void loop() {
  aboba.printtimef(millis());
  delay(1);
}

