#include "wiring_private.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"

#define LED RED_LED

volatile uint8_t state = 0;

void setup(){
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);   
  
  configureTimer1A();
}

void loop(){
  // put your main code here, to run repeatedly:
  
}

void configureTimer1A(){
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1); // Enable Timer 1 Clock
  ROM_IntMasterEnable(); // Enable Interrupts
  ROM_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC); // Configure Timer Operation as Periodic
  
  // Configure Timer Frequency
  // Frequency is given by MasterClock / CustomValue
  // Examples: 120MHz / 120k = 1000 kHz ; 120MHz / 120M = 1 Hz
  ROM_TimerLoadSet(TIMER1_BASE, TIMER_A, 120000000); 
  
  ROM_IntEnable(INT_TIMER1A);  // Enable Timer 1A Interrupt
  ROM_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT); // Timer 1A Interrupt when Timeout
  ROM_TimerEnable(TIMER1_BASE, TIMER_A); // Start Timer 1A
}

void Timer1AHandler(void){
  //Required to launch next interrupt
  ROM_TimerIntClear(TIMER1_BASE, TIMER_A);
  
  state ^= 0x02; // Toggle led state
  digitalWrite(LED, state); // Blink
}
