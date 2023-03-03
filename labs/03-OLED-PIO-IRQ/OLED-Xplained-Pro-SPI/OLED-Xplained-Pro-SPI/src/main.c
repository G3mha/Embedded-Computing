
/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include <asf.h>
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

// Configurations for the LED 1 (PA0)
#define LED1_PIO           PIOA                 // peripheral that controls the LED1
#define LED1_PIO_ID        ID_PIOA              // ID from peripheral PIOA (controls LED1)
#define LED1_PIO_IDX       0                    // ID from LED1 in PIO
#define LED1_PIO_IDX_MASK  (1 << LED1_PIO_IDX)   // Mask to CONTROL the LED1

// Configurations for the button 1 (PD28)
#define BUT1_PIO           PIOD               // peripheral that controls the BUT1
#define BUT1_PIO_ID        ID_PIOD            // ID from peripheral PIOD (controls BUT1) 
#define BUT1_PIO_IDX       28                 // ID from BUT1 in PIO
#define BUT1_PIO_IDX_MASK (1u << BUT1_PIO_IDX) // Already done

// Configurations for the button 2 (PC31)
#define BUT2_PIO           PIOC               // peripheral that controls the BUT2
#define BUT2_PIO_ID        ID_PIOC            // ID from peripheral PIOC (controls BUT2)
#define BUT2_PIO_IDX       31                 // ID from BUT2 in PIO
#define BUT2_PIO_IDX_MASK (1u << BUT2_PIO_IDX) // Already done

// Configurations for the button 3 (PA19)
#define BUT3_PIO           PIOA               // peripheral that controls the BUT3
#define BUT3_PIO_ID        ID_PIOA            // ID from peripheral PIOA (controls BUT3)
#define BUT3_PIO_IDX       19                 // ID from BUT3 in PIO
#define BUT3_PIO_IDX_MASK (1u << BUT3_PIO_IDX) // Already done

/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* flags */
/************************************************************************/
volatile char but1_flag = 0;
volatile char but2_flag = 0;
volatile char but3_flag = 0;
volatile int freq = 1;
/************************************************************************/
/* prototype                                                            */
/************************************************************************/
void pisca_led(int n, int t);
/************************************************************************/
/* handler / callbacks */
/************************************************************************/
void but1_callback(void) {
	but1_flag = 1;
}

void but2_callback(void) {
	but2_flag = !but2_flag;
}

void but3_callback(void) {
	but3_flag = 1;
}

void handle_frequency(int is_up) {
	if (freq <= 10 && is_up) {
		freq += 1;
	}
	if (freq > 1 && !is_up) {
		freq -= 1;
	}
};
/************************************************************************/
/* functions                                                              */
/************************************************************************/
// pisca led N vez no periodo T
void pisca_led(int n, int t){
  for (int i=0;i<n;i++){
    pio_clear(LED_PIO, LED_IDX_MASK);
    delay_ms(t);
    pio_set(LED_PIO, LED_IDX_MASK);
    delay_ms(t);
  }
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/




int main (void)
{
	
	board_init();
	sysclk_init();
	delay_init();

  // Init OLED
	gfx_mono_ssd1306_init();
  
  
	gfx_mono_draw_filled_circle(20, 16, 16, GFX_rXEL_SET, GFX_WHOLE);
  gfx_mono_draw_string("mundo", 50,16, &sysfont);
  
  

  /* Insert application code here, after the board has been initialized. */
	while(1) {



			// Escreve na tela um circulo e um texto
			
			for(int i=70;i<=120;i+=2){
				
				gfx_mono_draw_rect(i, 5, 2, 10, GFX_PIXEL_SET);
				delay_ms(10);
				
			}
			
			for(int i=120;i>=70;i-=2){
				
				gfx_mono_draw_rect(i, 5, 2, 10, GFX_PIXEL_CLR);
				delay_ms(10);
				
			}
			
			
	}
}
