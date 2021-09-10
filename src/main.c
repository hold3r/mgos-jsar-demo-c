#include "mgos.h"
#include "mgos_jsar.h"

#define UARTno    (0)

uint8_t led_state = 0;

/* User UART callback */
void user_cb(uint16_t len, uint8_t *data, void *userdata)
{
  mgos_uart_write(UARTno, data, len);
  (void) userdata;
}

/* led_task */
static void led_task(void *arg)
{
  mgos_gpio_toggle(LED_PIN);
  mgos_jsar_expanderWriteLed(led_state++ & 1);

  (void) arg;
}


/* App init */
enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_gpio_set_mode(LED_PIN, MGOS_GPIO_MODE_OUTPUT);
  mgos_dxl_setUserUartCb(user_cb, NULL);
  mgos_jsar_begin();
  
  mgos_set_timer(333 , MGOS_TIMER_REPEAT, led_task, NULL);

  return MGOS_APP_INIT_SUCCESS;
}

