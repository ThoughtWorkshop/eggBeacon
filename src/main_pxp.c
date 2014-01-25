#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"

#include "nrf_pwm.h"

#define PIN_RED_LED 29
#define PIN_GREEN_LED 25
#define PIN_BLUE_LED 28

// #define PIN_RED_LED 21
// #define PIN_GREEN_LED 22
// #define PIN_BLUE_LED 23


// static void on_ias_evt(ble_ias_t * p_ias, ble_ias_evt_t * p_evt);
// static void on_lls_evt(ble_lls_t * p_lls, ble_lls_evt_t * p_evt);
// static void on_ias_c_evt(ble_ias_c_t * p_lls, ble_ias_c_evt_t * p_evt);
// static void on_bas_evt(ble_bas_t * p_bas, ble_bas_evt_t * p_evt);
// static void advertising_init(uint8_t adv_flags);

// void app_error_handler(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name)
// {
//     nrf_gpio_pin_clear(PIN_RED_LED);

//     //NVIC_SystemReset();
// }

// void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
// {
//     app_error_handler(DEAD_BEEF, line_num, p_file_name);
// }

// static void service_error_handler(uint32_t nrf_error)
// {
//     APP_ERROR_HANDLER(nrf_error);
// }


// void ADC_IRQHandler(void)
// {
//     if (NRF_ADC->EVENTS_END != 0)
//     {
//         uint8_t     adc_result;
//         uint16_t    batt_lvl_in_milli_volts;
//         uint8_t     percentage_batt_lvl;
//         uint32_t    err_code;

//         NRF_ADC->EVENTS_END     = 0;
//         adc_result              = NRF_ADC->RESULT;
//         NRF_ADC->TASKS_STOP     = 1;

//         batt_lvl_in_milli_volts = ADC_RESULT_IN_MILLI_VOLTS(adc_result) +
//                                   DIODE_FWD_VOLT_DROP_MILLIVOLTS;
//         percentage_batt_lvl     = battery_level_in_percent(batt_lvl_in_milli_volts);

//         err_code = ble_bas_battery_level_update(&m_bas, percentage_batt_lvl);
//         if (
//             (err_code != NRF_SUCCESS)
//             &&
//             (err_code != NRF_ERROR_INVALID_STATE)
//             &&
//             (err_code != BLE_ERROR_NO_TX_BUFFERS)
//             &&
//             (err_code != BLE_ERROR_GATTS_SYS_ATTR_MISSING)
//         )
//         {
//             APP_ERROR_HANDLER(err_code);
//         }
//     }
// }

// static void adc_start(void)
// {
//     uint32_t err_code;

//     // Configure ADC
//     NRF_ADC->INTENSET   = ADC_INTENSET_END_Msk;
//     NRF_ADC->CONFIG     = (ADC_CONFIG_RES_8bit                        << ADC_CONFIG_RES_Pos)     |
//                           (ADC_CONFIG_INPSEL_SupplyOneThirdPrescaling << ADC_CONFIG_INPSEL_Pos)  |
//                           (ADC_CONFIG_REFSEL_VBG                      << ADC_CONFIG_REFSEL_Pos)  |
//                           (ADC_CONFIG_PSEL_Disabled                   << ADC_CONFIG_PSEL_Pos)    |
//                           (ADC_CONFIG_EXTREFSEL_None                  << ADC_CONFIG_EXTREFSEL_Pos);
//     NRF_ADC->EVENTS_END = 0;
//     NRF_ADC->ENABLE     = ADC_ENABLE_ENABLE_Enabled;

//     // Enable ADC interrupt
//     err_code = sd_nvic_ClearPendingIRQ(ADC_IRQn);
//     APP_ERROR_CHECK(err_code);

//     err_code = sd_nvic_SetPriority(ADC_IRQn, NRF_APP_PRIORITY_LOW);
//     APP_ERROR_CHECK(err_code);

//     err_code = sd_nvic_EnableIRQ(ADC_IRQn);
//     APP_ERROR_CHECK(err_code);

//     NRF_ADC->EVENTS_END  = 0;    // Stop any running conversions.
//     NRF_ADC->TASKS_START = 1;
// }


// static void adv_led_blink_start(void)
// {
//     if (!m_is_adv_led_blinking)
//     {
//         uint32_t             err_code;
//         static volatile bool is_led_on;
        
//         is_led_on = true;

//         nrf_gpio_pin_set(ADVERTISING_LED_PIN_NO);
        
//         is_led_on             = true;
//         m_is_adv_led_blinking = true;

//         err_code = app_timer_start(m_adv_led_blink_timer_id, ADV_LED_ON_TIME, (void *)&is_led_on);
//         APP_ERROR_CHECK(err_code);
//     }
// }


// static void adv_led_blink_stop(void)
// {
//     uint32_t err_code;

//     err_code = app_timer_stop(m_adv_led_blink_timer_id);
//     APP_ERROR_CHECK(err_code);

//     m_is_adv_led_blinking = false;

//     nrf_gpio_pin_clear(ADVERTISING_LED_PIN_NO);
// }


// static void alert_led_blink_start(void)
// {
//     if (!m_is_alert_led_blinking)
//     {
//         uint32_t             err_code;
//         static volatile bool is_led_on;

//         is_led_on = true;
        
//         nrf_gpio_pin_set(ALERT_PIN_NO);
        
//         m_is_alert_led_blinking = true;

//         err_code = app_timer_start(m_alert_led_blink_timer_id,
//                                    MILD_ALERT_LED_ON_TIME,
//                                    (void *)&is_led_on);
//         APP_ERROR_CHECK(err_code);
//     }
// }


// static void alert_led_blink_stop(void)
// {
//     uint32_t err_code;

//     err_code = app_timer_stop(m_alert_led_blink_timer_id);
//     APP_ERROR_CHECK(err_code);

//     m_is_alert_led_blinking = false;

//     nrf_gpio_pin_clear(ALERT_PIN_NO);
// }


// static void advertising_start(void)
// {
//     uint32_t             err_code;
//     ble_gap_adv_params_t adv_params;
//     ble_gap_whitelist_t  whitelist;
    
//     // Initialize advertising parameters with defaults values
//     memset(&adv_params, 0, sizeof(adv_params));
    
//     adv_params.type        = BLE_GAP_ADV_TYPE_ADV_IND;
//     adv_params.p_peer_addr = NULL;
//     adv_params.fp          = BLE_GAP_ADV_FP_ANY;
//     adv_params.p_whitelist = NULL;

//     // Configure advertisement according to current advertising state
//     switch (m_advertising_mode)
//     {
//         case BLE_NO_ADV:
//             m_advertising_mode = BLE_FAST_ADV_WHITELIST;
//             // fall through

//         case BLE_FAST_ADV_WHITELIST:
//             err_code = ble_bondmngr_whitelist_get(&whitelist);
//             APP_ERROR_CHECK(err_code);

//             if ((whitelist.addr_count != 0) || (whitelist.irk_count != 0))
//             {
//                 adv_params.fp          = BLE_GAP_ADV_FP_FILTER_CONNREQ;
//                 adv_params.p_whitelist = &whitelist;
                
//                 advertising_init(BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED);
//                 m_advertising_mode = BLE_FAST_ADV;
//             }
//             else
//             {
//                 m_advertising_mode = BLE_SLOW_ADV;
//             }
            
//             adv_params.interval = APP_ADV_INTERVAL_FAST;
//             adv_params.timeout  = APP_FAST_ADV_TIMEOUT;
//             break;
            
//         case BLE_FAST_ADV:
//             advertising_init(BLE_GAP_ADV_FLAGS_LE_ONLY_LIMITED_DISC_MODE);
            
//             adv_params.interval = APP_ADV_INTERVAL_FAST;
//             adv_params.timeout  = APP_FAST_ADV_TIMEOUT;
//             m_advertising_mode  = BLE_SLOW_ADV;            
//             break;
            
//         case BLE_SLOW_ADV:
//             advertising_init(BLE_GAP_ADV_FLAGS_LE_ONLY_LIMITED_DISC_MODE);
            
//             adv_params.interval = APP_ADV_INTERVAL_SLOW;
//             adv_params.timeout  = APP_SLOW_ADV_TIMEOUT;
//             m_advertising_mode  = BLE_SLEEP;
            
//             break;
            
//         default:
//             // No implementation needed.
//             break;
//     }

//     // Start advertising
//     err_code = sd_ble_gap_adv_start(&adv_params);
//     APP_ERROR_CHECK(err_code);
    
//     adv_led_blink_start();
// }

// static void battery_level_meas_timeout_handler(void * p_context)
// {
//     UNUSED_PARAMETER(p_context);
//     adc_start();
// }

// static void mild_alert_timeout_handler(void * p_context)
// {
//     if (m_is_alert_led_blinking)
//     {
//         bool *          p_is_led_on;
//         uint32_t        next_timer_interval;
//         uint32_t        err_code;

//         APP_ERROR_CHECK_BOOL(p_context != NULL);

//         nrf_gpio_pin_toggle(ALERT_PIN_NO);

//         p_is_led_on = (bool *)p_context;

//         *p_is_led_on = !(*p_is_led_on);

//         if(*p_is_led_on)
//         {
//             // The toggle operation above would have resulted in an ON state. So start a timer that
//             // will expire after MILD_ALERT_LED_OFF_TIME.
//             next_timer_interval = MILD_ALERT_LED_ON_TIME;
//         }
//         else
//         {
//             // The toggle operation above would have resulted in an OFF state. So start a timer that
//             // will expire after MILD_ALERT_LED_OFF_TIME.
//             next_timer_interval = MILD_ALERT_LED_OFF_TIME;
//         }

//         err_code = app_timer_start(m_alert_led_blink_timer_id,
//                                    next_timer_interval,
//                                    p_is_led_on);
//         APP_ERROR_CHECK(err_code);
//     }
// }

// static void adv_led_blink_timeout_handler(void * p_context)
// {
//     if (m_is_adv_led_blinking)
//     {
//         bool *          p_is_led_on;
//         uint32_t        next_timer_interval;
//         uint32_t        err_code;
    
//         APP_ERROR_CHECK_BOOL(p_context != NULL);

//         nrf_gpio_pin_toggle(ADVERTISING_LED_PIN_NO);

//         p_is_led_on = (bool *)(p_context);

//         *p_is_led_on = !(*p_is_led_on);

//         if(*p_is_led_on )
//         {
//             // The toggle operation above would have resulted in an ON state. So start a timer that
//             // will expire after ADV_LED_ON_TIME.
//             next_timer_interval = ADV_LED_ON_TIME;
//         }
//         else
//         {
//             // The toggle operation above would have resulted in an OFF state. So start a timer that
//             // will expire after ADV_LED_OFF_TIME.
//             next_timer_interval = ADV_LED_OFF_TIME;
//         }

//         err_code = app_timer_start(m_adv_led_blink_timer_id,
//                                    next_timer_interval,
//                                    p_is_led_on );
//         APP_ERROR_CHECK(err_code);
//     }
// }


static void leds_init(void)
{
    nrf_gpio_cfg_output(PIN_RED_LED);
    nrf_gpio_cfg_output(PIN_GREEN_LED);
    nrf_gpio_cfg_output(PIN_BLUE_LED);

    nrf_gpio_pin_set(PIN_RED_LED);
    nrf_gpio_pin_set(PIN_GREEN_LED);

    nrf_gpio_pin_clear(PIN_BLUE_LED);
}


// static void timers_init(void)
// {
//     uint32_t err_code;

//     // Initialize timer module
//     APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_MAX_TIMERS, APP_TIMER_OP_QUEUE_SIZE, false);

//     // Create battery timer
//     err_code = app_timer_create(&m_battery_timer_id,
//                                 APP_TIMER_MODE_REPEATED,
//                                 battery_level_meas_timeout_handler);
//     APP_ERROR_CHECK(err_code);
    
//     err_code = app_timer_create(&m_alert_led_blink_timer_id,
//                                 APP_TIMER_MODE_SINGLE_SHOT,
//                                 mild_alert_timeout_handler);
//     APP_ERROR_CHECK(err_code);

//     err_code = app_timer_create(&m_adv_led_blink_timer_id,
//                                 APP_TIMER_MODE_SINGLE_SHOT,
//                                 adv_led_blink_timeout_handler);
//     APP_ERROR_CHECK(err_code);
// }


// static void gap_params_init(void)
// {
//     uint32_t                err_code;
//     ble_gap_conn_params_t   gap_conn_params;
//     ble_gap_conn_sec_mode_t sec_mode;

//     BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);
    
//     err_code = sd_ble_gap_device_name_set(&sec_mode, (const uint8_t *)DEVICE_NAME, strlen(DEVICE_NAME));
//     APP_ERROR_CHECK(err_code);

//     err_code = sd_ble_gap_appearance_set(BLE_APPEARANCE_GENERIC_KEYRING);
//     APP_ERROR_CHECK(err_code);
    
//     memset(&gap_conn_params, 0, sizeof(gap_conn_params));

//     gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
//     gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
//     gap_conn_params.slave_latency     = SLAVE_LATENCY;
//     gap_conn_params.conn_sup_timeout  = CONN_SUP_TIMEOUT;

//     err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
//     APP_ERROR_CHECK(err_code);

//     err_code = sd_ble_gap_tx_power_set(TX_POWER_LEVEL);
//     APP_ERROR_CHECK(err_code);
// }


// static void advertising_init(uint8_t adv_flags)
// {
//     uint32_t      err_code;
//     ble_advdata_t advdata;
//     int8_t        tx_power_level = TX_POWER_LEVEL;
    
//     ble_uuid_t adv_uuids[] = 
//     {
//         {BLE_UUID_TX_POWER_SERVICE,        BLE_UUID_TYPE_BLE}, 
//         {BLE_UUID_IMMEDIATE_ALERT_SERVICE, BLE_UUID_TYPE_BLE}, 
//         {BLE_UUID_LINK_LOSS_SERVICE,       BLE_UUID_TYPE_BLE}
//     };

//     m_advertising_mode = BLE_NO_ADV;

//     // Build and set advertising data
//     memset(&advdata, 0, sizeof(advdata));
    
//     advdata.name_type               = BLE_ADVDATA_FULL_NAME;
//     advdata.include_appearance      = true;
//     advdata.flags.size              = sizeof(adv_flags);
//     advdata.flags.p_data            = &adv_flags;
//     advdata.p_tx_power_level        = &tx_power_level;
//     advdata.uuids_complete.uuid_cnt = sizeof(adv_uuids) / sizeof(adv_uuids[0]);
//     advdata.uuids_complete.p_uuids  = adv_uuids;
    
//     err_code = ble_advdata_set(&advdata, NULL);
//     APP_ERROR_CHECK(err_code);
// }

// static void tps_init(void)
// {
//     uint32_t       err_code;
//     ble_tps_init_t tps_init_obj;

//     memset(&tps_init_obj, 0, sizeof(tps_init_obj));
//     tps_init_obj.initial_tx_power_level = TX_POWER_LEVEL;
    
//     BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&tps_init_obj.tps_attr_md.read_perm);
//     BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&tps_init_obj.tps_attr_md.write_perm);

//     err_code = ble_tps_init(&m_tps, &tps_init_obj);
//     APP_ERROR_CHECK(err_code);
// }

// static void ias_init(void)
// {
//     uint32_t       err_code;
//     ble_ias_init_t ias_init_obj;

//     memset(&ias_init_obj, 0, sizeof(ias_init_obj));
//     ias_init_obj.evt_handler = on_ias_evt;
    
//     err_code = ble_ias_init(&m_ias, &ias_init_obj);
//     APP_ERROR_CHECK(err_code);
// }

// static void lls_init(void)
// {
//     uint32_t       err_code;
//     ble_lls_init_t lls_init_obj;

//     // Initialize Link Loss Service
//     memset(&lls_init_obj, 0, sizeof(lls_init_obj));
    
//     lls_init_obj.evt_handler         = on_lls_evt;
//     lls_init_obj.error_handler       = service_error_handler;
//     lls_init_obj.initial_alert_level = INITIAL_LLS_ALERT_LEVEL;
    
//     BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&lls_init_obj.lls_attr_md.read_perm);
//     BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&lls_init_obj.lls_attr_md.write_perm);

//     err_code = ble_lls_init(&m_lls, &lls_init_obj);
//     APP_ERROR_CHECK(err_code);
    
//     m_is_link_loss_alerting = false;
// }

// static void bas_init(void)
// {
//     uint32_t       err_code;
//     ble_bas_init_t bas_init_obj;
    
//     memset(&bas_init_obj, 0, sizeof(bas_init_obj));
    
//     bas_init_obj.evt_handler          = on_bas_evt;
//     bas_init_obj.support_notification = true;
//     bas_init_obj.p_report_ref         = NULL;
//     bas_init_obj.initial_batt_level   = 100;

//     BLE_GAP_CONN_SEC_MODE_SET_OPEN(&bas_init_obj.battery_level_char_attr_md.cccd_write_perm);
//     BLE_GAP_CONN_SEC_MODE_SET_OPEN(&bas_init_obj.battery_level_char_attr_md.read_perm);
//     BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&bas_init_obj.battery_level_char_attr_md.write_perm);

//     BLE_GAP_CONN_SEC_MODE_SET_OPEN(&bas_init_obj.battery_level_report_read_perm);
    
//     err_code = ble_bas_init(&m_bas, &bas_init_obj);
//     APP_ERROR_CHECK(err_code);
// }

// static void ias_client_init(void)
// {
//     uint32_t            err_code;
//     ble_ias_c_init_t    ias_c_init_obj;

//     memset(&ias_c_init_obj, 0, sizeof(ias_c_init_obj));

//     m_is_high_alert_signalled = false;

//     ias_c_init_obj.evt_handler    = on_ias_c_evt;
//     ias_c_init_obj.error_handler  = service_error_handler;

//     err_code = ble_ias_c_init(&m_ias_c, &ias_c_init_obj);
//     APP_ERROR_CHECK(err_code);
// }

// static void services_init(void)
// {
//     tps_init();
//     ias_init();
//     lls_init();
//     bas_init();
//     ias_client_init();
// }

// static void sec_params_init(void)
// {
//     m_sec_params.timeout      = SEC_PARAM_TIMEOUT;
//     m_sec_params.bond         = SEC_PARAM_BOND;
//     m_sec_params.mitm         = SEC_PARAM_MITM;
//     m_sec_params.io_caps      = SEC_PARAM_IO_CAPABILITIES;
//     m_sec_params.oob          = SEC_PARAM_OOB;  
//     m_sec_params.min_key_size = SEC_PARAM_MIN_KEY_SIZE;
//     m_sec_params.max_key_size = SEC_PARAM_MAX_KEY_SIZE;
// }

// static void conn_params_error_handler(uint32_t nrf_error)
// {
//     APP_ERROR_HANDLER(nrf_error);
// }

// static void conn_params_init(void)
// {
//     uint32_t               err_code;
//     ble_conn_params_init_t cp_init;
    
//     memset(&cp_init, 0, sizeof(cp_init));

//     cp_init.p_conn_params                  = NULL;
//     cp_init.first_conn_params_update_delay = FIRST_CONN_PARAMS_UPDATE_DELAY;
//     cp_init.next_conn_params_update_delay  = NEXT_CONN_PARAMS_UPDATE_DELAY;
//     cp_init.max_conn_params_update_count   = MAX_CONN_PARAMS_UPDATE_COUNT;
//     cp_init.start_on_notify_cccd_handle    = BLE_GATT_HANDLE_INVALID;
//     cp_init.disconnect_on_fail             = true;
//     cp_init.evt_handler                    = NULL;
//     cp_init.error_handler                  = conn_params_error_handler;
    
//     err_code = ble_conn_params_init(&cp_init);
//     APP_ERROR_CHECK(err_code);
// }

// static void alert_signal(uint8_t alert_level)
// {
//     switch (alert_level)
//     {
//         case BLE_CHAR_ALERT_LEVEL_NO_ALERT:
//             m_is_link_loss_alerting = false;
//             alert_led_blink_stop();
//             break;

//         case BLE_CHAR_ALERT_LEVEL_MILD_ALERT:
//             alert_led_blink_start();
//             break;

//         case BLE_CHAR_ALERT_LEVEL_HIGH_ALERT:
//             alert_led_blink_stop();
//             nrf_gpio_pin_set(ALERT_PIN_NO);
//             break;
            
//         default:
//             // No implementation needed.
//             break;
//     }
// }

// static void on_ias_evt(ble_ias_t * p_ias, ble_ias_evt_t * p_evt)
// {
//     switch (p_evt->evt_type)
//     {
//         case BLE_IAS_EVT_ALERT_LEVEL_UPDATED:
//             alert_signal(p_evt->params.alert_level);
//             break;
            
//         default:
//             // No implementation needed.
//             break;
//     }
// }

// static void on_lls_evt(ble_lls_t * p_lls, ble_lls_evt_t * p_evt)
// {
//     switch (p_evt->evt_type)
//     {
//         case BLE_LLS_EVT_LINK_LOSS_ALERT:
//             m_is_link_loss_alerting = true;
//             alert_signal(p_evt->params.alert_level);
//             break;
            
//         default:
//             // No implementation needed.
//             break;
//     }
// }

// static void on_ias_c_evt(ble_ias_c_t * p_ias_c, ble_ias_c_evt_t * p_evt)
// {
//     uint32_t err_code;

//     switch (p_evt->evt_type)
//     {
//         case BLE_IAS_C_EVT_SRV_DISCOVERED:
//             // IAS is found on peer. The Find Me Locator functionality of this app will work.
//             break;

//         case BLE_IAS_C_EVT_SRV_NOT_FOUND:
//             // IAS is not found on peer. The Find Me Locator functionality of this app will NOT work.
//             break;

//         case BLE_IAS_C_EVT_DISCONN_COMPLETE:
//             // Stop detecting button presses when not connected
//             err_code = app_button_disable();
//             APP_ERROR_CHECK(err_code);
//             break;

//         default:
//             break;
//     }
// }

// static void on_bas_evt(ble_bas_t * p_bas, ble_bas_evt_t *p_evt)
// {
//     uint32_t err_code;

//     switch (p_evt->evt_type)
//     {
//         case BLE_BAS_EVT_NOTIFICATION_ENABLED:
//             // Start battery timer
//             err_code = app_timer_start(m_battery_timer_id, BATTERY_LEVEL_MEAS_INTERVAL, NULL);
//             APP_ERROR_CHECK(err_code);
//             break;

//         case BLE_BAS_EVT_NOTIFICATION_DISABLED:
//             err_code = app_timer_stop(m_battery_timer_id);
//             APP_ERROR_CHECK(err_code);
//             break;

//         default:
//             // No implementation needed.
//             break;
//     }
// }

// static void on_ble_evt(ble_evt_t * p_ble_evt)
// {
//     uint32_t        err_code;
//     static uint16_t m_conn_handle = BLE_CONN_HANDLE_INVALID;
    
//     switch (p_ble_evt->header.evt_id)
//     {
//         case BLE_GAP_EVT_CONNECTED:
//             adv_led_blink_stop();

//             if (m_is_link_loss_alerting)
//             {
//                 alert_led_blink_stop();
//             }
            
//             m_advertising_mode = BLE_NO_ADV;
//             m_conn_handle      = p_ble_evt->evt.gap_evt.conn_handle;
            
//             // Start handling button presses
//             err_code = app_button_enable();
//             APP_ERROR_CHECK(err_code);
//             break;
            
//         case BLE_GAP_EVT_DISCONNECTED:
//             if (!m_is_link_loss_alerting)
//             {
//                 alert_led_blink_stop();
//             }

//             m_conn_handle = BLE_CONN_HANDLE_INVALID;

//             // Since we are not in a connection and have not started advertising, store bonds
//             err_code = ble_bondmngr_bonded_centrals_store();
//             APP_ERROR_CHECK(err_code);

//             advertising_start();
//             break;
            
//         case BLE_GAP_EVT_SEC_PARAMS_REQUEST:
//             err_code = sd_ble_gap_sec_params_reply(m_conn_handle, 
//                                                    BLE_GAP_SEC_STATUS_SUCCESS, 
//                                                    &m_sec_params);
//             APP_ERROR_CHECK(err_code);
//             break;

//         case BLE_GAP_EVT_TIMEOUT:
//             if (p_ble_evt->evt.gap_evt.params.timeout.src == BLE_GAP_TIMEOUT_SRC_ADVERTISEMENT)
//             { 
//                 if (m_advertising_mode == BLE_SLEEP)
//                 {
//                     m_advertising_mode = BLE_NO_ADV;
//                     adv_led_blink_stop();
//                     alert_led_blink_stop();

//                     err_code = sd_power_system_off();    
//                     APP_ERROR_CHECK(err_code);
//                 }
//                 else
//                 {
//                     advertising_start();
//                 }
//             }
//             break;

//         case BLE_GATTC_EVT_TIMEOUT:
//         case BLE_GATTS_EVT_TIMEOUT:
//             // Disconnect on GATT Server and Client timeout events.
//             err_code = sd_ble_gap_disconnect(m_conn_handle, 
//                                              BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
//             APP_ERROR_CHECK(err_code);
//             break;

//         default:
//             // No implementation needed.
//             break;
//     }
// }

// static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
// {
//     ble_bondmngr_on_ble_evt(p_ble_evt);
//     ble_conn_params_on_ble_evt(p_ble_evt);
//     ble_ias_on_ble_evt(&m_ias, p_ble_evt);
//     ble_lls_on_ble_evt(&m_lls, p_ble_evt);
//     ble_bas_on_ble_evt(&m_bas, p_ble_evt);
//     ble_ias_c_on_ble_evt(&m_ias_c, p_ble_evt);
//     on_ble_evt(p_ble_evt);
// }

// static void sys_evt_dispatch(uint32_t sys_evt)
// {
//     pstorage_sys_event_handler(sys_evt);
// }

// static void ble_stack_init(void)
// {
//     nrf_gpio_pin_clear(PIN_BLUE_LED);    

//     uint32_t err_code;
    
//     // Initialize the SoftDevice handler module.
//     SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM, false);

//     // Register with the SoftDevice handler module for BLE events.
//     err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
//     APP_ERROR_CHECK(err_code);
    
//     // Register with the SoftDevice handler module for BLE events.
//     err_code = softdevice_sys_evt_handler_set(sys_evt_dispatch);
//     APP_ERROR_CHECK(err_code);
// }

// static void bond_manager_error_handler(uint32_t nrf_error)
// {
//     APP_ERROR_HANDLER(nrf_error);
// }


// static void bond_manager_init(void)
// {
//     uint32_t            err_code;
//     ble_bondmngr_init_t bond_init_data;
//     bool                bonds_delete;
    
//     // Initialize persistent storage module.
//     err_code = pstorage_init();
//     APP_ERROR_CHECK(err_code);
        
//     // Initialize the Bond Manager
//     bond_init_data.flash_page_num_bond     = FLASH_PAGE_BOND;
//     bond_init_data.flash_page_num_sys_attr = FLASH_PAGE_SYS_ATTR;
//     bond_init_data.evt_handler             = NULL;
//     bond_init_data.error_handler           = bond_manager_error_handler;
//     bond_init_data.bonds_delete            = bonds_delete;

//     err_code = ble_bondmngr_init(&bond_init_data);
//     APP_ERROR_CHECK(err_code);
// }


// static void gpiote_init(void)
// {
//     APP_GPIOTE_INIT(APP_GPIOTE_MAX_USERS);
// }


// static void power_manage(void)
// {
//     uint32_t err_code = sd_app_evt_wait();
//     APP_ERROR_CHECK(err_code);
// }

const uint8_t sin_table[] = {0, 0,1,2,4,6,9,12,16,20,24,29,35,40,	46,	53,	59,	66,	74,	81,	88,	96,	104,112,120,128,136,144,152,160,168,175,182,190,197,203,210,216,221,227,
               232,236,240,244,247,250,252,254,255,255,255,255,255,254,252,250,247,244,240,236,232,227,221,216,210,203,197,190,182,175,168,160,152,144,136,128,120,112,104,
               96,88,81,74,66,59,	53,	46,	40,	35,	29,24,	20,	16,	12,	9,	6,	4,	2,1,0};

int main(void)
{
    uint32_t counter = 0;

    // gpiote_init();
    // Initialize
    // leds_init();
    nrf_pwm_init(PIN_RED_LED, PIN_GREEN_LED, PIN_BLUE_LED, PWM_MODE_LED_255);
    // timers_init();
    // ble_stack_init();
    // bond_manager_init();
    // gap_params_init();
    // advertising_init(BLE_GAP_ADV_FLAGS_LE_ONLY_LIMITED_DISC_MODE);
    // services_init();
    // conn_params_init();
    // sec_params_init();

    // Start execution
    // advertising_start();
    
    // Enter main loop
      
    // LED 0 and LED 1 blink alternately.
    while(true)
    {
        nrf_pwm_set_value(0, sin_table[counter]);
        nrf_pwm_set_value(1, sin_table[(counter + 33) % 100]);
        nrf_pwm_set_value(2, sin_table[(counter + 66) % 100]);
        counter = (counter + 1) % 100;
        
        // Add a delay to control the speed of the sine wave
        nrf_delay_us(16667);
        // nrf_gpio_pin_clear(PIN_RED_LED);
        // nrf_gpio_pin_set(PIN_GREEN_LED);

        // nrf_delay_ms(500);

        // nrf_gpio_pin_set(PIN_RED_LED);
        // nrf_gpio_pin_clear(PIN_GREEN_LED);

        // nrf_delay_ms(500);
    }

    // for (;;)
    // {
    //     power_manage();
    // }
}
