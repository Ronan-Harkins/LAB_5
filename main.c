#include <msp430.h>
#include <stdint.h>

#define CALADC_15V_30C  *((unsigned int *)0x1A1A)                 // Temperature Sensor Calibration-30 C
                                                                  // See device datasheet for TLV table memory mapping
#define CALADC_15V_85C  *((unsigned int *)0x1A1C)                 // Temperature Sensor Calibration-High Temperature (85 for Industrial, 105 for Extended)

volatile long temp, tempRaw;

volatile float PhotoOut;

volatile float IntDegF;
volatile float IntDegC;
volatile float PhotoOut;

int count;

volatile int i = 0;

void Sensor1();
void Sensor2();

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                                   // Stop WDT

    PM5CTL0 &= ~LOCKLPM5;
    P1DIR &= ~(BIT1);

    // Configure the ADC A1 pin
    P1SEL0 |=  BIT1;
    P1SEL1 |=  BIT1;

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    TB0CCTL0 |= CCIE;                                             // TBCCR0 interrupt enabled
    TB0CCR0 = 65535;
    TB0CTL = TBSSEL__ACLK | MC__UP;                               // ACLK, UP mode

    // Configure ADC - Pulse sample mode; ADCSC trigger
    ADCCTL0 |= ADCSHT_8 | ADCON;                                  // ADC ON,temperature sample period>30us
    ADCCTL1 |= ADCSHS_0 | ADCCONSEQ_0 | ADCSHP;                   // s/w trig, single ch/conv, MODOSC
    ADCCTL2 &= ~ADCRES;                                           // clear ADCRES in ADCCTL
    ADCCTL2 |= ADCRES_2;                                          // 12-bit conversion results
    ADCMCTL0 |= ADCSREF_1 | ADCINCH_12;                           // ADC input ch A12 => temp sense
    ADCIE |=ADCIE0;
    ADCCTL0 |= ADCENC | ADCSC;


    // Configure reference
    PMMCTL0_H = PMMPW_H;                                          // Unlock the PMM registers
    PMMCTL2 |= INTREFEN | TSENSOREN;                              // Enable internal reference and temperature sensor
    __delay_cycles(400);                                          // Delay for reference settling

    Sensor1();

    while(1)
    {
        if(i == 0)
        {
            Sensor2();
            i = 1;
        }
        else if(i == 1)
        {
            Sensor1();
            i = 0;
        }
    }

}


void Sensor1()
{
     //ADCCTL0 &= ~(ADCENC);
     //ADCCTL0 &= ~(ADCSC);
     //ADCMCTL0 &= ~(ADCINCH_1);
    //ADCCTL0 &= ~(ADCSHT_6);
    //ADCCTL0 &= ~(ADCON);
    //Call As A Function For Each Sensor
    // Configure ADC - Pulse sample mode; ADCSC trigger
     //ADCCTL0 |= ADCSHT_8;                                          // ADC ON,temperature sample period>30us
    //ADCCTL1 |= ADCSHS_0 | ADCCONSEQ_2 | ADCSHP;                 // s/w trig, single ch/conv, MODOSC
     //ADCCTL2 &= ~ADCRES;                                           // clear ADCRES in ADCCTL
     //ADCCTL2 |= ADCRES_2;                                          // 12-bit conversion results
     //ADCMCTL0 |= ADCINCH_12;                                       // ADC input ch A12 => temp sense
    ADCCTL0 &= ~ADCENC;
    ADCCTL0 |= ADCSHT_8;                                           // ADC ON,temperature sample period>30us
    ADCCTL1 |= ADCSHP;                                            // s/w trig, single ch/conv, MODOSC
    ADCCTL2 &= ~ADCRES;                                           // clear ADCRES in ADCCTL
    ADCCTL2 |= ADCRES_2;                                          // 12-bit conversion results
    ADCMCTL0 &= ~ADCINCH_1;
    ADCMCTL0 |= ADCSREF_1 | ADCINCH_12;
    ADCCTL0 |= ADCENC + ADCSC + ADCMSC;
    ADCIE |= ADCIE0;
    //while (!(ADCIFG & ADCIFG0));
    while ((ADCIFG & ADCIFG0) == 0);
    //_delay_cycles(200000);

    temp = ADCMEM0;
    ADCCTL0 &= ~ADCIFG;
    ADCIE &= ~ADCIE0;
    // The temperature (Temp, C)=
    IntDegC = (temp-CALADC_15V_30C)*(85-30)/(CALADC_15V_85C-CALADC_15V_30C)+30;
                           // Temperature in Fahrenheit
                           // Tf = (9/5)*Tc | 32
    IntDegF = 9*IntDegC/5+32;
    __delay_cycles(400);
}

void Sensor2()
{
    //ADCCTL0 &= ~(ADCENC);
    //ADCCTL0 &= ~(ADCSC);
    //ADCMCTL0 &= ~(ADCINCH_12);
    //ADCCTL0 &= ~(ADCSC);
    //ADCCTL0 &= ~(ADCSHT_8);
    //ADCCTL0 &= ~(ADCON);
    ADCCTL0 &= ~ADCENC;
    ADCCTL0 |= ADCSHT_6;
    //ADCCTL1 = ADCSHS_0 | ADCCONSEQ_2 | ADCSHP; //ADCCONSEQ_0 try ADCCONSEQ_2
    ADCCTL2 &= ~ADCRES;
    ADCCTL2 |= ADCRES_2;
    ADCMCTL0 &= ~ADCINCH_12;
    ADCMCTL0 &= ~ADCSREF_1;
    ADCMCTL0 |= ADCINCH_1;
    ADCCTL0 |= ADCENC | ADCSC;
    ADCIE |= ADCIE0;
    //ADCCTL0 &= ~(ADCSC);
    //ADCCTL0 |= (ADCSC);
    while (!(ADCIFG & ADCIFG0)); //Wait For Sample to finish
    //while ((ADCIFG & ADCIFG0) == 0);
    //uint16_t reading_once;
    //reading_once = adcRead();
    PhotoOut = ADCMEM0;
    ADCCTL0 &= ~ADCIFG;
    ADCIE &= ~ADCIE0;
    __delay_cycles(400);
}
