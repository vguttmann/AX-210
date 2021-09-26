/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "sdkconfig.h"
#include "string.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"
#include "esp_types.h"

/* Can use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO CONFIG_BLINK_GPIO
#define BLINK2_GPIO CONFIG_BLINK2_GPIO
#define ECHO_TEST_TXD (GPIO_NUM_1)
#define ECHO_TEST_RXD (GPIO_NUM_3)
#define ECHO_TEST_RTS (GPIO_NUM_2)
#define ECHO_TEST_CTS (GPIO_NUM_15)
#define BUF_SIZE (4096)

#define TIMER_DIVIDER 8000                           //  Hardware timer clock divider
#define TIMER_SCALE (TIMER_BASE_CLK / TIMER_DIVIDER) // convert counter value to seconds
#define TIMER_INTERVAL0_SEC (3.4179)                 // sample test interval for the first timer
#define TIMER_INTERVAL1_SEC (5.78)                   // sample test interval for the second timer

#define PIN_0 GPIO_NUM_13
#define PIN_1 GPIO_NUM_12
#define PIN_2 GPIO_NUM_14
#define PIN_3 GPIO_NUM_27
#define PIN_4 GPIO_NUM_26
#define PIN_5 GPIO_NUM_25
#define PIN_6 GPIO_NUM_33
#define PIN_7 GPIO_NUM_32
#define PIN_8 GPIO_NUM_16
#define PIN_9 GPIO_NUM_17
#define PIN_10 GPIO_NUM_5
#define PIN_11 GPIO_NUM_18
#define PIN_12 GPIO_NUM_19
#define PIN_13 GPIO_NUM_21
#define PIN_14 GPIO_NUM_22
#define PIN_15 GPIO_NUM_23
#define IO_LOCKOUT GPIO_NUM_4
/* LOW is input, HIGH is OUTPUT */
#define TOGGLE_IO GPIO_NUM_2

int getIn1(const char *datb)
{
    if (strcmp(datb, (const char *)"0") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"1") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"2") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"3") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"4") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"5") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"6") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"7") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"8") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"9") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"_") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"-") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)",") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)";") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)":") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"!") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"?") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)".") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"'") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"\"") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"(") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)")") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"§") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"*") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"/") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"&") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"#") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"%") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"`") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"´") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"°") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"↞") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"↠") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"↤") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"↥") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"↧") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"↲") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"⇁") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"⇥") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"⇼") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"+") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"⇍") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"⇜") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"⇎") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"=") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"|") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"├") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"↽") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"↺") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"$") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"①") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"⑩") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"⨸") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"⑫") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"²") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"②") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"³") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"A") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"a") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"Ä") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"ä") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"⎇") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"B") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"b") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"C") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"c") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"⇬") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"𝄌") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"D") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"d") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"E") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"e") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"F") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"f") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"G") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"g") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"H") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"h") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"I") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"i") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"J") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"j") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"K") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"k") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"L") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"l") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"┴") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"M") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"m") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"N") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"n") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"O") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"o") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"Ö") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"ö") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"P") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"p") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"Q") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"q") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"R") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"r") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"⇒") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"S") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"s") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"⇫") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"⇪") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"\\") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"ß") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"T") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"t") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"⊖") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"⊕") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"U") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"u") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"Ü") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"ü") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"V") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"v") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"W") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"w") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"X") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"x") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"♠") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"♢") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"Y") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"y") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"Z") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"z") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"↹") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"⇑") == 0)
    {
        return (PIN_14);
    }
    else
    {
        return (PIN_15);
    }
}

int getIn2(const char *datb)
{
    if (strcmp(datb, (const char *)"0") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"1") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"2") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"3") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"4") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"5") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"6") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"7") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"8") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"9") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"_") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"-") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)",") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)";") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)":") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"!") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"?") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)".") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"'") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"\"") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"(") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)")") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"§") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"*") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"/") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"&") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"#") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"%") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"`") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"´") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"°") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"↞") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"↠") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"↤") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"↥") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"↧") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"↲") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"⇁") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"⇥") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"⇼") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"+") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"⇍") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"⇜") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"⇎") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"=") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"|") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"├") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"↽") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"↺") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"$") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"①") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"⑩") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"⨸") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"⑫") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"²") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"②") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"³") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"A") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"a") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"Ä") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"ä") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"⎇") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"B") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"b") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"C") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"c") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"⇬") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"𝄌") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"D") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"d") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"E") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"e") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"F") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"f") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"G") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"g") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"H") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"h") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"I") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"i") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"J") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"j") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"K") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"k") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"L") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"l") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"┴") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"M") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"m") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"N") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"n") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"O") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"o") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"Ö") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"ö") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"P") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"p") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"Q") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"q") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"R") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"r") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"⇒") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"S") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"s") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"⇫") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"⇪") == 0)
    {
        return (PIN_15);
    }
    else if (strcmp(datb, (const char *)"\\") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"ß") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"T") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"t") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"⊖") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"⊕") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"U") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"u") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"Ü") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"ü") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"V") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"v") == 0)
    {
        return (PIN_10);
    }
    else if (strcmp(datb, (const char *)"W") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"w") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"X") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"x") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"♠") == 0)
    {
        return (PIN_9);
    }
    else if (strcmp(datb, (const char *)"♢") == 0)
    {
        return (PIN_14);
    }
    else if (strcmp(datb, (const char *)"Y") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"y") == 0)
    {
        return (PIN_11);
    }
    else if (strcmp(datb, (const char *)"Z") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"z") == 0)
    {
        return (PIN_12);
    }
    else if (strcmp(datb, (const char *)"↹") == 0)
    {
        return (PIN_13);
    }
    else if (strcmp(datb, (const char *)"⇑") == 0)
    {
        return (PIN_11);
    }
    else
    {
        return (PIN_8);
    }
}

int getOu1(const char *datb)
{
    if (strcmp(datb, (const char *)"0") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"1") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"2") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"3") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"4") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"5") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"6") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"7") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"8") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"9") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"_") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"-") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)",") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)");") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)":") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"!") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"?") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)".") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"'") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"\"") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"(") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)")") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"§") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"*") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"/") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"&") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"#") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"%") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"`") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"´") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"°") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"↞") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"↠") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"↤") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"↥") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"↧") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"↲") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"⇁") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"⇥") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"⇼") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"+") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"⇍") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"⇜") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"⇎") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"=") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"|") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"├") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"↽") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"↺") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"$") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"①") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"⑩") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"⨸") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"⑫") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"²") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"②") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"³") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"A") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"a") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"Ä") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"ä") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"⎇") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"B") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"b") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"C") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"c") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"⇬") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"𝄌") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"D") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"d") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"E") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"e") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"F") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"f") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"G") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"g") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"H") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"h") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"I") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"i") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"J") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"j") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"K") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"k") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"L") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"l") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"┴") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"M") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"m") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"N") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"n") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"O") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"o") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"Ö") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"ö") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"P") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"p") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"Q") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"q") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"R") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"r") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"⇒") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"S") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"s") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"⇫") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"⇪") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"\\") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"ß") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"T") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"t") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"⊖") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"⊕") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"U") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"u") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"Ü") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"ü") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"V") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"v") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"W") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"w") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"X") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"x") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"♠") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"♢") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"Y") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"y") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"Z") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"z") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"↹") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"⇑") == 0)
    {
        return (PIN_7);
    }
    else
    {
        return (PIN_0);
    }
}

int getOu2(const char *datb)
{
    if (strcmp(datb, (const char *)"0") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"1") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"2") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"3") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"4") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"5") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"6") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"7") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"8") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"9") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"_") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"-") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)",") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)");") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)":") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"!") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"?") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)".") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"'") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"\"") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"(") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)")") == 0)
    {
        return (PIN_8);
    }
    else if (strcmp(datb, (const char *)"§") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"*") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"/") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"&") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"#") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"%") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"`") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"´") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"°") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"↞") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"↠") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"↤") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"↥") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"↧") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"↲") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"⇁") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"⇥") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"⇼") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"+") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"⇍") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"⇜") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"⇎") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"=") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"|") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"├") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"↽") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"↺") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"$") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"①") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"⑩") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"⨸") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"⑫") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"²") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"②") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"³") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"A") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"a") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"Ä") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"ä") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"⎇") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"B") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"b") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"C") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"c") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"⇬") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"𝄌") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"D") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"d") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"E") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"e") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"F") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"f") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"G") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"g") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"H") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"h") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"I") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"i") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"J") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"j") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"K") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"k") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"L") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"l") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"┴") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"M") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"m") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"N") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"n") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"O") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"o") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"Ö") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"ö") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"P") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"p") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"Q") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"q") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"R") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"r") == 0)
    {
        return (PIN_2);
    }
    else if (strcmp(datb, (const char *)"⇒") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"S") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"s") == 0)
    {
        return (PIN_4);
    }
    else if (strcmp(datb, (const char *)"⇫") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"⇪") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"\\") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"ß") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"T") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"t") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"⊖") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"⊕") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"U") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"u") == 0)
    {
        return (PIN_5);
    }
    else if (strcmp(datb, (const char *)"Ü") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"ü") == 0)
    {
        return (PIN_0);
    }
    else if (strcmp(datb, (const char *)"V") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"v") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"W") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"w") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"X") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"x") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"♠") == 0)
    {
        return (PIN_6);
    }
    else if (strcmp(datb, (const char *)"♢") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"Y") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"y") == 0)
    {
        return (PIN_1);
    }
    else if (strcmp(datb, (const char *)"Z") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"z") == 0)
    {
        return (PIN_3);
    }
    else if (strcmp(datb, (const char *)"↹") == 0)
    {
        return (PIN_7);
    }
    else if (strcmp(datb, (const char *)"⇑") == 0)
    {
        return (PIN_4);
    }
    else
    {
        return (PIN_6);
    }
}

void setOutput()
{
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(PIN_0, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_3, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_4, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_5, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_6, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_7, GPIO_MODE_OUTPUT);
    gpio_set_level(TOGGLE_IO, 1);
}

void setInput()
{
    /* Set the GPIO as an input */
    gpio_set_direction(PIN_0, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_1, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_2, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_3, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_4, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_5, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_6, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_7, GPIO_MODE_INPUT);
    gpio_set_level(TOGGLE_IO, 0);
}

void resetTimer()
{
    timer_pause(TIMER_GROUP_0, 0);
    timer_set_counter_value(TIMER_GROUP_0, 0, 0);
    timer_start(TIMER_GROUP_0, 0);
}
int len;
char key;

void app_main(void)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */

    int in1;
    int in2;
    int ou1;
    int ou2;

    gpio_pad_select_gpio(PIN_0);
    gpio_pad_select_gpio(PIN_1);
    gpio_pad_select_gpio(PIN_2);
    gpio_pad_select_gpio(PIN_3);
    gpio_pad_select_gpio(PIN_4);
    gpio_pad_select_gpio(PIN_5);
    gpio_pad_select_gpio(PIN_6);
    gpio_pad_select_gpio(PIN_7);
    gpio_pad_select_gpio(PIN_8);
    gpio_pad_select_gpio(PIN_9);
    gpio_pad_select_gpio(PIN_10);
    gpio_pad_select_gpio(PIN_11);
    gpio_pad_select_gpio(PIN_12);
    gpio_pad_select_gpio(PIN_13);
    gpio_pad_select_gpio(PIN_14);
    gpio_pad_select_gpio(PIN_15);
    gpio_pad_select_gpio(IO_LOCKOUT);
    gpio_pad_select_gpio(TOGGLE_IO);

    gpio_set_direction(IO_LOCKOUT, GPIO_MODE_OUTPUT);
    gpio_set_direction(TOGGLE_IO, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_8, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_9, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_10, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_11, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_12, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_13, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_14, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_15, GPIO_MODE_INPUT);

    gpio_set_pull_mode(PIN_8, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(PIN_9, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(PIN_10, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(PIN_11, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(PIN_12, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(PIN_13, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(PIN_14, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(PIN_15, GPIO_PULLUP_ONLY);

    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_0, &uart_config);
    uart_set_pin(UART_NUM_0, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);

    timer_config_t config = {
        .divider = TIMER_DIVIDER,
        .counter_dir = TIMER_COUNT_UP,
        .counter_en = TIMER_START,
        .alarm_en = TIMER_ALARM_DIS,
        .auto_reload = TIMER_AUTORELOAD_EN,
    }; // default clock source is APB

    timer_init(TIMER_GROUP_0, 0, &config);
    uint64_t *timervalue = malloc(64);

    // Configure a temporary buffer for the incoming data
    // malloc allocates memory in the given size and returns a pointer to that location.
    uint8_t *data = (uint8_t *)malloc(BUF_SIZE);
    char *datb = (char *)malloc(64);
    char *bufstring = (char *)malloc(BUF_SIZE);
    char *bufstringbuf = (char *)malloc(BUF_SIZE);
    snprintf(bufstring, 1, "%s", (const char *)"");

    // Read data from the UART
    // reads data from the given uart number, stores it at the pointer (name here is data),
    // and buffer size. timeout is given last
    uart_flush_input(UART_NUM_0);
    while (true)
    {
        setOutput();
        printf("waiting for input\n");
        len = uart_read_bytes(UART_NUM_0, data, BUF_SIZE, 2000 / portTICK_RATE_MS);

        while (len < 0)
        {
            len = uart_read_bytes(UART_NUM_0, data, BUF_SIZE, 2000 / portTICK_RATE_MS);
            uart_write_bytes(UART_NUM_0, (const char *)data, len);
        }

        snprintf(bufstringbuf, len + 1, "%s", (const char *)data);
        strcat(bufstring, bufstringbuf);
        uart_flush(UART_NUM_0);
        snprintf(datb, 2, "%s", (const char *)bufstring);
        memmove(bufstring, bufstring + 1, strlen(bufstring));
        // Write data back to the UART, and cast the data into a char.
        // uart_write_bytes(UART_NUM_0, (const char *)data, len);
        printf("datblen\n%d\n%s\n", strlen(datb), datb);

        if (strlen(datb) > 0)
        {
            in1 = getIn1((const char *)datb);
            in2 = getIn2((const char *)datb);
            ou1 = getOu1((const char *)datb);
            ou2 = getOu2((const char *)datb);

            printf("exited ifs successfully\n");

            resetTimer();

            while (*timervalue < 10000) //output for 10s. For debugging purposes only!
            {
                gpio_set_level(ou1, gpio_get_level(in1));
                gpio_set_level(ou2, gpio_get_level(in2));
                timer_get_counter_value(TIMER_GROUP_0, 0, timervalue);
            }
            printf("exited timer successfully\n");
        }
        // Configure the outputs to the MCU to be inputs.
        setInput();

        /* Explanation what the following code does and why:
        * That code is supposed to turn keyboard matrix readings into actual keypresses
        * We first define a counterArray. This array holds the number of times that each
        * Keyboard *AND* MCU input line have been high for each combination. Since the pulse length
        * for this key matrix is 2 milliseconds, a simple for loop iterating over the inputs should
        * be more than enough. Because the input pins aren't linear, I used an array to map the pins
        * from their line numbers to their actual pin number. To determine what buttons are pressed,
        * we compute the average of the array, and count every count value above that as a pressed
        * button. Because we can't be sure how many buttons are pressed, we iterate over the array 
        * and store the result in another variable. If the value is above 2, we immediately discard
        * this result. 
        */

        //first index is the keyboard input lines (line 0 to 7), second is the MCU input lines (line 8 to 15)
        int counterArray[8][8] = {0};

        int ioArray[16] = {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9, PIN_10, PIN_11, PIN_12, PIN_13, PIN_14, PIN_15};

        /*         for (int i = 0; i < 8); i++)
        {
            printf("Line %d: ", i);
            for (int j = 0; j < 8); j++)
            {
                printf("Input %d: %d, ", j, counterArray[i][j]);
            }
            printf("\n");
        } */

        resetTimer();

        // This bit does the counting
        while (*timervalue < 100)
        {
            for (int i = 0; i < 7; i++)
            {
                for (int j = 8; j < 15; j++)
                {
                    if (gpio_get_level(ioArray[i]) == 1 && gpio_get_level(ioArray[j]) == 1)
                    {
                        counterArray[i][j - 8]++;
                    }
                }
            }
        }

        // This just prints the counterArray to Serial.
        for (int i = 0; i < 8; i++)
        {
            printf("Line %d: ", i);
            for (int j = 0; j < 8; j++)
            {
                printf("Input %d: %d, ", j, counterArray[i][j]);
            }
            printf("\n");
        }

        uint64_t sum = 0;

        // Here we compute the sum. Uint64_t so that we don't have a possible overflow problem.
        for (int i = 0; i < 8; i++)
        {
            printf("Line %d: ", i);
            for (int j = 0; j < 8; j++)
            {
                sum += counterArray[i][j];
            }
        }

        //calculate the average as the sum over the array size
        float average = sum / 64;

        printf("counter: %d\n", (int)sum);

        // This bit does the counting of how many buttons are pressed

        int buttonCounter = 0;
        for (int i = 0; i < 8; i++)
        {
            printf("Line %d: ", i);
            for (int j = 0; j < 8; j++)
            {
                if (counterArray[i][j] > average)
                {
                    buttonCounter++;
                }
            }
        }

        if (buttonCounter == 1)
        {
            int button1Index;
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (counterArray[i][j] > average)
                    {
                        button1Index = i * 8 + j;
                    }
                }
            }
            button1Index++;

            char buttonMap[64] = {
                ",",
                ".",
                "ü",
                "ö",
                "+",
                "ä",
                " ",
                "" //NONE
                "-",
                "#",
                "q",
                "y",
                "w",
                "a",
                "\n",
                "", //NONE
                "1",
                "2",
                "e",
                "f",
                "r",
                "g",
                "", //NONE
                "", //NONE
                "3",
                "4",
                "t",
                "h",
                "z",
                "j",
                "↠", //RIGHT ARROW
                "7",
                "8",
                "o",
                "s",
                "p",
                "d",
                "↧", //ARROW DOWN
                "5",
                "6",
                "u",
                "k",
                "i",
                "l",
                "↤", //BACKSPACE
                "ß",
                "´",
                "n",
                "x",
                "m",
                "lid", //NONE
                "<x|", //NONE
                "9",
                "0",
                "v",
                "c",
                "b",
                "⇥", //TAB
                "",  //NONE
                "",  //NONE
                "",  //NONE
                "",  //NONE
                "",  //NONE
                "",  //NONE
            };
            key = buttonMap[button1Index];
        }
        else if (buttonCounter == 2)
        {
            int button1Index = 0;
            int button2Index;
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (counterArray[i][j] > average)
                    {

                        button2Index = button1Index;
                        button1Index = i * 8 + j;
                    }
                }
            }

            buttonMap[64][64] = {
                {"", "", "", "", "", "", "", ";", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", ":", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "Ü", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "Ö", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "*", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "Ä", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {";", ":", "Ü", "Ö", "*", "Ä", "", "", "_", "'", "Q", "Y", "W", "A", "", "", "!", "“", "E", "F", "R", "G", "", "", "§", "$", "T", "H", "Z", "J", "", "/", "(", "O", "S", "P", "D", "", "%", "&", "U", "K", "I", "L", "", "?", "`", "N", "X", "M", "", "", ")", "=", "V", "C", "B", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "_", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "'", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "Q", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "Y", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "W", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "°", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "A", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "!", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "“", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "E", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "F", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "R", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "G", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "§", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "$", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "T", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "H", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "Z", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "J", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "|-<-|", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "/", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "(", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "O", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "S", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "P", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "D", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "↥", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "%", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "&", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "U", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "K", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "I", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "L", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "?", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "`", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "N", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "X", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "²", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "M", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", ")", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "=", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "V", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "³", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "C", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "B", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "°", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "|-<-|", "", "", "", "", "", "", "↥", "", "", "", "", "", "", "", "", "", "", "²", "", "", "", "", "", "³", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
                {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}};

            key = buttonMap[button1Index][button2Index];
        }
        else
        {
            /*
            * Something has fucked up, but I don't know what.
            * No course of action necessary.
            */
        }
    }
}