int main() {
    Serial.begin(9600);

    byte rowPins[4] = {11, 10, 9, 8};
    byte colPins[4] = {7, 6, 5, 4};

    const char keys[4][4] = {
            {'1', '2', '3', 'A'},
            {'4', '5', '6', 'B'},
            {'7', '8', '9', 'C'},
            {'*', '0', '#', 'D'}
    };

    DDRD = B11111111;
    DDRB = B00000000;

    for (int i = 0; i < 4; i++) {
        PORTB |= 1 << i;
        PORTD |= 1 << i + 4;
    }

    while (1) {
        for (int i = 0; i < 4; i++) {
            PORTD &= ~1 << (i + 4);
            for (int j = 0; j < 4; j++) {
                if (!((PINB >> j) & 1)) {
                    Serial.print(keys[3 - j][3 - i]);
                }
            }
            PORTD |= 1 << (i + 4);
        }
    }
    return 0;
}