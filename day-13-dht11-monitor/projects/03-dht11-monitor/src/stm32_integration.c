/* STM32 integration sketch: PA1 DHT11 DATA, TIM2 at 1 MHz, USART1 at 115200. */
#include "dht11_frame.h"
#include "environment_monitor.h"
/* Implement dht11_read_frame() with GPIO output/input switching and microsecond timing.
   Read 40 bits, fill dht11_frame_t, then call environment_monitor_accept().
   Recommended read interval: 2000 ms. */
