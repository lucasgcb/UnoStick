/** LED mask for the first LED on the board. */
#define LEDS_LED1   (1 << PD5)

/** LED mask for the second LED on the board. */
#define LEDS_LED2   (1 << PD4)

/** LED mask for the third LED on the board. */
#define LEDS_LED3   (1 << PD4)

/** LED mask for all the LEDs on the board. */
#define LEDS_ALL_LEDS    (LEDS_LED1 | LEDS_LED2 | LEDS_LED3)

/** LED mask for none of the board LEDs. */
#define LEDS_NO_LEDS     0

/* Inline Functions: */
static inline void LEDs_Init(void)
{
    // initialize LED port pins as outputs here
    DDRD |= LEDS_LED1;

    // Initialize to off by driving high
    PORTD |= LEDS_LED1;
}

static inline void LEDs_Disable(void)
{
    // Clear the LED port pins as high impedance inputs here
    DDRD &= ~LEDS_LED1;

    PORTD &= ~LEDS_LED1;
   
}

static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
{
    // turn on LEDs given in the LEDMask mask here, leave others as-is
    PORTD &= ~(LEDMask & LEDS_LED1);
}

static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
{
    // turn off LEDs given in the LEDMask mask here, leave others as-is
    PORTD |= LEDMask & LEDS_LED1;
}

static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
{
    // turn on only LEDs given in the LEDMask mask here, all others off
    PORTB = ( (PORTD | LEDS_LED1) & ~LEDMask);
}

static inline void LEDs_ChangeLEDs(const uint8_t LEDMask, const uint8_t ActiveMask)
{
    // set the Leds in the given LEDMask to the status given in ActiveMask here
    PORTD = ( (PORTB | (LEDS_LED1 & LEDMask)) & ~ActiveMask);
 
}

static inline void LEDs_ToggleLEDs(const uint8_t LEDMask)
{
    // toggle the Leds in the given LEDMask, ignoring all others
    PIND = LEDMask & LEDS_LED1;
}

static inline uint8_t LEDs_GetLEDs(void)
{
    // return the current LEDs status' here which can be masked against LED_LED* macros
    return ((PORTD & LEDS_LED1));
}