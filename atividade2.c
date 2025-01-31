#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

const uint led_pin_blue  = 11;
const uint led_pin_red   = 12;
const uint led_pin_green = 13;

#define BTN 5

int state = 0;
alarm_id_t alarm_id = 0;

int64_t turn_off_callback(alarm_id_t id, void *user_data);

int main()
{
    stdio_init_all();

    gpio_init(led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);
    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);
    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);

    gpio_set_function(BTN, GPIO_FUNC_SIO);
    gpio_set_dir(BTN, GPIO_IN);
    gpio_pull_up(BTN);

    gpio_put(led_pin_blue, false);
    gpio_put(led_pin_green, false);
    gpio_put(led_pin_red, false);

    add_alarm_in_ms(3000, turn_off_callback, NULL, false);

    while (true) {
        if (gpio_get(BTN) == 0) {
            printf("Botão pressionado!\n");
            gpio_put(led_pin_blue, true);
            gpio_put(led_pin_green, true);
            gpio_put(led_pin_red, true);

            state = 0;

            if (alarm_id) cancel_alarm(alarm_id);
            alarm_id = add_alarm_in_ms(3000, turn_off_callback, NULL, false);
        }
        sleep_ms(200);
    }
}

int64_t turn_off_callback(alarm_id_t id, void *user_data){

    if (state == 0){
        gpio_put(led_pin_blue, false);
        state = 1;
    }
    else if (state == 1){
        gpio_put(led_pin_red, false);
        state = 2;
    }
    else if (state == 2){
        gpio_put(led_pin_green, false);
        state = 0;
        return 0;
    }

    return 3000000;
}
