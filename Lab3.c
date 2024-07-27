#include "msp.h"

#define PORT1_BIT1 (P1IN & (1<<0 ) )
#define DELAY_VALUE 100000

int redPin = 1;
int button1Pressed, button2Pressed = 0;
int i = 10000; // debouncer delay
// int redPin = 1;   // Boolean for eather redPin LED or RGB LED
int count = 0; // Counter for RGB change of colors
int t = 2500000;

int main(void){

//P1SEL0 and P1SEL1 must be 0 (GPIO)
P1SEL0 &=(uint8_t)(~((1<<4) | (1<<1) | (1<<0)));
P1SEL1 &=(uint8_t)(~((1<<4) | (1<<1) | (1<<0)));
P2SEL0 &=(uint8_t)(~((1<<2) | (1<<1) | (1<<0)));
P2SEL1 &=(uint8_t)(~((1<<2) | (1<<1) | (1<<0)));

//Disable the Watchdog timer
WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

//Configure the switches (P1.1 and P1.4) as inputs.
P1DIR &=(uint8_t)(~((1<<4) | (1<<1)));

//ren
P1REN |=(uint8_t)((1<<4) | (1<<1));
P1OUT |=(uint8_t)((1<<4) | (1<<1));

//disable interrupts
P1->IE &= ~((1<<0));
P1->IE &= ~((1<<0) | (1<<1) | (1<<2));
P1->IE &= ~((1<<1) | (1<<4));


//configure interupts
P1IES |= (uint8_t)(1 << 1);
P1IFG &= (uint8_t)~(1 << 1);
P1IE |= (uint8_t)(1 << 1);   

P1IES |= (uint8_t)(1 << 4);
P1IFG &= (uint8_t)~(1 << 4);
P1IE |= (uint8_t)(1 << 4);   

//Configure NVIC
NVIC_SetPriority(PORT1_IRQn,2);
NVIC_ClearPendingIRQ(PORT1_IRQn);
NVIC_EnableIRQ(PORT1_IRQn);

// Globally enable interrupts in CPU
__ASM("CPSIE I");


//Configure the LEDs (P1.0 and P2.0, P2.1, P2.2) as outputs
P1DIR |=(uint8_t)(1<<0);
P2DIR |=(uint8_t)(((1<<2) | (1<<1) | (1<<0)));

// Initialize LEDs states (all turned off).
P1OUT &=~(uint8_t)(1<<0);
P2OUT &=~(uint8_t)(((1<<2) | (1<<1) | (1<<0)));





// Create an infinite loop
while (1)
{
i = 10000;
while ((P1->IN & (uint8_t)(1 << 4)))
{
if (redPin)
{ // Turn redPin LED ON/OFF
P1->OUT ^= (uint8_t)(1 << 0);
}
else
{ // Cycle into RGB LED colors
if (count == 0)
{ // 001 redPin
P2->OUT ^= (uint8_t)(1 << 0);
}
else if (count == 1)
{ // 010 GREEN
P2->OUT ^= (uint8_t)(1 << 0);
P2->OUT ^= (uint8_t)(1 << 1);
}
else if (count == 2)
{ // 100 BLUE
P2->OUT ^= (uint8_t)(1 << 2);
P2->OUT ^= (uint8_t)(1 << 1);
}
else if (count == 3)
{ // 011 YELLOW
P2->OUT ^= (uint8_t)(1 << 2);
P2->OUT ^= (uint8_t)(1 << 1);
P2->OUT ^= (uint8_t)(1 << 0);
}
else if (count == 4)
{ // 101 MAGENTA
P2->OUT ^= (uint8_t)(1 << 2);
P2->OUT ^= (uint8_t)(1 << 1);
}
else if (count == 5)
{ // 110 CYAN
P2->OUT ^= (uint8_t)(1 << 0);
P2->OUT ^= (uint8_t)(1 << 1);
}
else if (count == 6)
{ // 111 WHITE
P2->OUT ^= (uint8_t)(1 << 0);
}
else if (count == 7)
{ // 000 OFF
P2->OUT ^= (uint8_t)(1 << 0);
P2->OUT ^= (uint8_t)(1 << 1);
P2->OUT ^= (uint8_t)(1 << 2);
count = -1;
}
count++;
}
while (t > 0)
{
t--;
}
t=2500000;
}
while (i > 0)
{
i--;
} // Debouncer
if (!(P1->IN & (uint8_t)(1 << 1))) { // handle button 1
	if (redPin) {
		redPin = 0;
	}
else
{
redPin = 1;
}
}
while (!((P1->IN & (uint8_t)(1 << 1)) && (P1->IN & (uint8_t)(1 << 4))))
{} // waits until the switches are released
continue;
}

return 0;
}

void PORT1_IRQHandler(void) {
	int i = 10;
	while(i > 0){
		i--;
	}
	if ((P1IFG & (uint8_t)(1<<1)) != 0){
		P1IFG &= ~(uint8_t)(1<<1);
		
		if (redPin ==1){
			redPin = 0;
		}else{
			redPin = 1;
		}
	}
	
	// handle ISR
	else if ((P1IFG & (uint8_t)(1<<4)) != 0){
		P1IFG &= ~(uint8_t)(1<<4);
		if(button2Pressed == 1){
			button2Pressed = 0;
		}
		else{
			button2Pressed = 1;
		}
	
	}
}

