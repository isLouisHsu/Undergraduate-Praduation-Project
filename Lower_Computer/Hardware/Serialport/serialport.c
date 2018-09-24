#include "serialport.h"


void DebugUartInit(int DBbaudrate)
{
   uart_init(DEBUG_UART,9600);  				//baud rate:9600
   set_vector_handler(UART2_RX_TX_VECTORn,uart2_handler);  
   uart_rx_irq_en (UART2);			
}

void uart2_handler(void)
{
    char ch;
    UARTn_e uratn = UART2;

    if(UART_S1_REG(UARTN[uratn]) & UART_S1_RDRF_MASK)   
    {
        uart_getchar   (UART2, &ch);                   
        uart_putchar   (UART2, ch);                   
    }
}