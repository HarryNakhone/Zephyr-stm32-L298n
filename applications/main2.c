#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/devicetree/gpio.h>
#include <zephyr/devicetree/pwms.h>

#define PWM_P_SEC 1000

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

static const struct gpio_dt_spec in1 = GPIO_DT_SPEC_GET(DT_NODELABEL(in1_pin),gpios);
static const struct gpio_dt_spec in2 = GPIO_DT_SPEC_GET(DT_NODELABEL(in2_pin), gpios);
static const struct pwm_dt_spec pwm_m = PWM_DT_SPEC_GET(DT_ALIAS(pmotor));

static const struct gpio_dt_spec in3 = GPIO_DT_SPEC_GET(DT_NODELABEL(in3_pin),gpios);
static const struct gpio_dt_spec in4 = GPIO_DT_SPEC_GET(DT_NODELABEL(in4_pin), gpios);
static const struct pwm_dt_spec pwm_m2 = PWM_DT_SPEC_GET(DT_ALIAS(pmotort));

void main(void){

    if (!device_is_ready(in1.port) ||!device_is_ready(in2.port) || !device_is_ready(pwm_m.dev)){
        LOG_ERR("One of the device is not ready\n");
        return;
    }

    gpio_pin_configure_dt(&in1, GPIO_OUTPUT);
    gpio_pin_configure_dt(&in2, GPIO_OUTPUT);
     gpio_pin_configure_dt(&in3, GPIO_OUTPUT);
    gpio_pin_configure_dt(&in4, GPIO_OUTPUT);

    while(1){
    gpio_pin_set_dt(&in1, 1);
    gpio_pin_set_dt(&in2, 0);
    gpio_pin_set_dt(&in3, 1);
    gpio_pin_set_dt(&in4, 0);

     pwm_set_dt(&pwm_m, PWM_USEC(1000), PWM_USEC(200));
       pwm_set_dt(&pwm_m2, PWM_USEC(1000), PWM_USEC(200));

    LOG_INF("Motor running forward at 50%% speed\n");
    k_sleep(K_SECONDS(5));

    gpio_pin_set_dt(&in1, 0);
    gpio_pin_set_dt(&in2, 1);
     gpio_pin_set_dt(&in3, 0);
    gpio_pin_set_dt(&in4, 1);

    LOG_INF("Motor is running in reverse\n");
    k_sleep(K_SECONDS(5));

     pwm_set_dt(&pwm_m, PWM_MSEC(10), 0);
     pwm_set_dt(&pwm_m2, PWM_MSEC(10), 0);
     
    LOG_INF("Motor stopped\n");
    k_sleep(K_SECONDS(5));
    }

}