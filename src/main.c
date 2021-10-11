#include "mgos.h"
#include "mgos_jsar.h"

static void led_task(void *arg)
{
  static uint8_t led_state = 0;
  mgos_jsar_expanderWriteLed(led_state++ % 2);
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_begin();
  mgos_set_timer(500 , MGOS_TIMER_REPEAT, led_task, NULL);

  return MGOS_APP_INIT_SUCCESS;
}

