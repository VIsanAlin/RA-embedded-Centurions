//*
 * hello.c              Copyright NXP 2016
 * Description:  Simple program to exercise GPIO
 * 2015 Mar 31 S Mihalik/ O Romero - initial version
 *
 */

/*	Include headers */
#include "features.h"	 /* include features flags */
#include "embedded101.h" /* include peripheral declarations S32K144 */
#include "functions.h"   /* include functions */


int main(void) {
  int counter = 0;
  WDOG_disable();             /* Disable Watchdog in case it is not done in startup code */

  /* When you want to enable an output port
   * 1) enable clock  ---> PCC
   * 2) pin direction ---> PDDR
   * 3) Port function ---> PCR
   * 4) turn on LED   ---> PSOR/PCOR
   */

  // 1) Port clock control ---> enable
  *(PCC_PORT_D) |= PCC_ENABLE_PORT_MASK;

  // 2) Pin Direction ---> PDDR 1 << x
  (((GPIO_map_tp) PORT_D)->PDDR) |= LED_RED;
  (((GPIO_map_tp) PORT_D)->PDDR) |= LED_GREEN;
  (((GPIO_map_tp) PORT_D)->PDDR) |= LED_BLUE;

  // 3) Port function ---> PCR.Mux : 001b = GPIO
  PCR_PORT_D[PTD0] |= PCR_GPIO_MODE_MASK;
  PCR_PORT_D[PTD15] |= PCR_GPIO_MODE_MASK;
  PCR_PORT_D[PTD16] |= PCR_GPIO_MODE_MASK;

  // 4) Turn on LED
  ((GPIO_map_tp) PORT_D)->PCOR |= LED_RED;
  ((GPIO_map_tp) PORT_D)->PCOR |= LED_GREEN;
  ((GPIO_map_tp) PORT_D)->PCOR |= LED_BLUE;
  //5)Turn off LED
  ((GPIO_map_tp) PORT_D)->PSOR |= LED_RED;
  ((GPIO_map_tp) PORT_D)->PSOR |= LED_GREEN;
  ((GPIO_map_tp) PORT_D)->PSOR |= LED_BLUE;

  /*When you want to enable an input port
   * 1)enable clock  --->PCC
   * 2)pin direction --->PDDR
   * 3)port function --->PCR
   */

  //1) Port clock control ---> enable
  *(PCC_PORT_C) |= PCC_ENABLE_PORT_MASK;

  //2)Pin Direction --->PDDR 0<<x
  (((GPIO_map_tp) PORT_C)->PDDR) &= ~(1<<12U);
  (((GPIO_map_tp) PORT_C)->PDDR) &= ~(1<<13U);

  //3)Port function ---> PCR.Mux :001b=GPIO
  PCR_PORT_C[12U] |= PCR_GPIO_MODE_MASK;
  PCR_PORT_C[13U] |= PCR_GPIO_MODE_MASK;

  for(;;) {

	  if(((((GPIO_map_tp) PORT_C)->PDIR) & (1<<13))&&((((GPIO_map_tp) PORT_C)->PDIR) & (1<<12)))
	  	  {
	  		  ((GPIO_map_tp) PORT_D)->PCOR |= LED_BLUE;
	  		  ((GPIO_map_tp) PORT_D)->PSOR |= LED_GREEN;
	  		  ((GPIO_map_tp) PORT_D)->PSOR |= LED_RED;
	  	  }
	  else{

	  if((((GPIO_map_tp) PORT_C)->PDIR) & (1<<12))
	  {
		  ((GPIO_map_tp) PORT_D)->PCOR |= LED_RED;
	  }

	  if((((GPIO_map_tp) PORT_C)->PDIR) & (1<<13))
	  	  {
	  		  ((GPIO_map_tp) PORT_D)->PCOR |= LED_GREEN;
	  	  }

	  }
	  ((GPIO_map_tp) PORT_D)->PSOR |= LED_GREEN;
	  ((GPIO_map_tp) PORT_D)->PSOR |= LED_RED;
	  ((GPIO_map_tp) PORT_D)->PSOR |= LED_BLUE;
    counter++;
  }

}
