#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"

#include "nrf_pwm.h"

#include "ble_advdata.h"

#include "nordic_common.h"
#include "softdevice_handler.h"

// #define DONGLE

#ifdef DONGLE
#define PIN_RED_LED 21
#define PIN_GREEN_LED 22
#define PIN_BLUE_LED 23
#else
#define PIN_RED_LED 29
#define PIN_GREEN_LED 25
#define PIN_BLUE_LED 28
#endif


#define ADVERTISING_LED_PIN_NO        PIN_BLUE_LED                             /**< Is on when device is advertising. */
#define ASSERT_LED_PIN_NO             PIN_RED_LED                             /**< Is on when application has asserted. */

#define APP_CFG_NON_CONN_ADV_TIMEOUT  0                                 /**< Time for which the device must be advertising in non-connectable mode (in seconds). 0 disables timeout. */
#define NON_CONNECTABLE_ADV_INTERVAL  MSEC_TO_UNITS(100, UNIT_0_625_MS) /**< The advertising interval for non-connectable advertisement (100 ms). This value can vary between 100ms to 10.24s). */

#define APP_CLBEACON_INFO_LENGTH      0x17                              /**< Total length of information advertised by the iBeacon. */
#define APP_ADV_DATA_LENGTH           0x15                              /**< Length of manufacturer specific data in the advertisement. */
#define APP_DEVICE_TYPE               0x02                              /**< 0x02 refers to iBeacon. */
#define APP_MEASURED_RSSI             0xC3                              /**< The iBeacon's measured RSSI at 1 meter distance in dBm. */
#define APP_COMPANY_IDENTIFIER        0x004C                            /**< Company identifier for Apple Inc. as per www.bluetooth.org. */
#define APP_MAJOR_VALUE               0x01, 0x02                        /**< Major value used to identify iBeacons. */ 
#define APP_MINOR_VALUE               0x03, 0x04                        /**< Minor value used to identify iBeacons. */ 
#define APP_IBEACON_UUID              0xC9, 0xFE, 0x03, 0x85, \
                                      0xEE, 0x9C, 0x4F, 0x98, \
                                      0xBD, 0xB3, 0x3F, 0x04, \
                                      0x53, 0x1C, 0x1D, 0x10            /**< Proprietary UUID for iBeacon. */

#define DEAD_BEEF                     0xDEADBEEF                        /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */


static ble_gap_adv_params_t m_adv_params;                               /**< Parameters to be passed to the stack when starting advertising. */
static uint8_t clbeacon_info[APP_CLBEACON_INFO_LENGTH] =                /**< Information advertised by the iBeacon. */
{
    APP_DEVICE_TYPE,     // Manufacturer specific information. Specifies the device type in this 
                         // implementation. 
    APP_ADV_DATA_LENGTH, // Manufacturer specific information. Specifies the length of the 
                         // manufacturer specific data in this implementation.
    APP_IBEACON_UUID,    // 128 bit UUID value. 
    APP_MAJOR_VALUE,     // Major arbitrary value that can be used to distinguish between iBeacons. 
    APP_MINOR_VALUE,     // Minor arbitrary value that can be used to distinguish between iBeacons. 
    APP_MEASURED_RSSI    // Manufacturer specific information. The iBeacon's measured TX power in 
                         // this implementation. 
};

void app_error_handler(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
    nrf_gpio_pin_clear(ASSERT_LED_PIN_NO);

    NVIC_SystemReset();
}

void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
    app_error_handler(DEAD_BEEF, line_num, p_file_name);
}

static void leds_init(void)
{
    nrf_gpio_cfg_output(PIN_RED_LED);
    nrf_gpio_cfg_output(PIN_GREEN_LED);
    nrf_gpio_cfg_output(PIN_BLUE_LED);

    nrf_gpio_pin_set(PIN_RED_LED);
    nrf_gpio_pin_set(PIN_GREEN_LED);
    nrf_gpio_pin_set(PIN_BLUE_LED);
}

static void advertising_init(void)
{
    uint32_t        err_code;
    ble_advdata_t   advdata;
    uint8_t         flags = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;

    ble_advdata_manuf_data_t manuf_specific_data;
    manuf_specific_data.company_identifier = APP_COMPANY_IDENTIFIER;
    manuf_specific_data.data.p_data        = (uint8_t *) clbeacon_info;
    manuf_specific_data.data.size          = APP_CLBEACON_INFO_LENGTH;

    // Build and set advertising data.
    memset(&advdata, 0, sizeof(advdata));

    advdata.name_type               = BLE_ADVDATA_NO_NAME;
    advdata.flags.size              = sizeof(flags);
    advdata.flags.p_data            = &flags;
    advdata.p_manuf_specific_data   = &manuf_specific_data;

    err_code = ble_advdata_set(&advdata, NULL);
    APP_ERROR_CHECK(err_code);

    // Initialize advertising parameters (used when starting advertising).
    memset(&m_adv_params, 0, sizeof(m_adv_params));

    m_adv_params.type        = BLE_GAP_ADV_TYPE_ADV_NONCONN_IND;
    m_adv_params.p_peer_addr = NULL;                             // Undirected advertisement.
    m_adv_params.fp          = BLE_GAP_ADV_FP_ANY;
    m_adv_params.interval    = NON_CONNECTABLE_ADV_INTERVAL;
    m_adv_params.timeout     = APP_CFG_NON_CONN_ADV_TIMEOUT;
}

static void advertising_start(void)
{
    uint32_t err_code;

    err_code = sd_ble_gap_adv_start(&m_adv_params);
    APP_ERROR_CHECK(err_code);

    nrf_gpio_pin_clear(ADVERTISING_LED_PIN_NO);
}

static void ble_stack_init(void)
{
    // Initialize the SoftDevice handler module.
    SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_SYNTH_250_PPM, false);
}

static void power_manage(void)
{
    uint32_t err_code = sd_app_evt_wait();
    APP_ERROR_CHECK(err_code);
}

int main(void)
{
    // Initialize.
    leds_init();

    ble_stack_init();

    advertising_init();

    // Start execution.
    advertising_start();

    // Enter main loop.
    for (;;)
    {
        power_manage();
    }
}