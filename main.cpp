#include <avr/io.h>
#include <util/delay.h>

#define MATRIX_SIZE 6
#define DELAY_TIME 100 //kecepatan delay
#define DEBOUNCE_DELAY 50 // Debounce delay untuk tombol

volatile uint8_t state = 0;

void init_ports() {
    // Set PC0 to PC5 as output
    DDRC = 0b00111111;
    // Set PD2, PD3, PD4, and PD5 as input
    DDRD &= ~(1 << PD2);
    DDRD &= ~(1 << PD3);
    DDRD &= ~(1 << PD4);
    DDRD &= ~(1 << PD5);
    // pull-up resistors PD2, PD3, PD4, and PD5
    PORTD |= (1 << PD2);
    PORTD |= (1 << PD3);
    PORTD |= (1 << PD4);
    PORTD |= (1 << PD5);
}

void clear_matrix() {
    PORTC = 0b00000000;
}

void right_turn_signal() {
    for (uint8_t i = 0; i < MATRIX_SIZE; i++) {
        PORTC = (1 << i); //klom dari kiri
        _delay_ms(DELAY_TIME);
    }
}

void left_turn_signal() {
    for (uint8_t i = 0; i < MATRIX_SIZE; i++) {
        PORTC = (1 << (MATRIX_SIZE - 1 - i)); //klom dari kanan
        _delay_ms(DELAY_TIME);
    }
}

void top_bottom_signal(uint8_t a) {
    for (uint8_t i = 0; i < MATRIX_SIZE / 2; i++) {
        PORTC = (1 << i) | (1 << (MATRIX_SIZE - 1 - i)); //dari kanan kiri
        a == 0 ? _delay_ms(DELAY_TIME) : _delay_ms(DELAY_TIME-30); //antara hazard dan stop
    }
}

int main(void) {
    init_ports();
    clear_matrix();

    loop:
        if (!(PIND & (1 << PD2))) { // Check if PD2 is pressed
            if (!(PIND & (1 << PD2))) {
                right_turn_signal();
            }
        } else if (!(PIND & (1 << PD3))) { // Check if PD3 is pressed
            if (!(PIND & (1 << PD3))) {
                left_turn_signal();
            }
        } else if (!(PIND & (1 << PD4))) { // Check if PD4 is pressed
            _delay_ms(DEBOUNCE_DELAY); // Debounce
            if (!(PIND & (1 << PD4))) {
                top_bottom_signal(0);
            }
        } else if (!(PIND & (1 << PD5))) { // Check if PD5 is pressed
            _delay_ms(DEBOUNCE_DELAY); // Debounce
            if (!(PIND & (1 << PD5))) {
                state = !state; // Toggle state
                _delay_ms(DEBOUNCE_DELAY); // debounce
            }
        }

        if (state) {
            top_bottom_signal(1);
        } else {
            clear_matrix();
        }

        goto loop;

    return 0;
}