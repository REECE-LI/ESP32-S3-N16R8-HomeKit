//
// Created by 22482 on 2024/1/23.
//

#include "can_esp.h"
#include "cstring"


void CANEsp::Init() {
    twai_general_config_t g_config =
            TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t) canTxPin, (gpio_num_t) canRxPin, TWAI_MODE_NORMAL);

    twai_filter_config_t f_config = _f_config;

    twai_timing_config_t t_config;
    switch (canBaudRate) {
        case ESP32CAN_SPEED_100KBPS:
            t_config = TWAI_TIMING_CONFIG_100KBITS();
            break;
        case ESP32CAN_SPEED_125KBPS:
            t_config = TWAI_TIMING_CONFIG_125KBITS();
            break;
        case ESP32CAN_SPEED_250KBPS:
            t_config = TWAI_TIMING_CONFIG_250KBITS();
            break;
        case ESP32CAN_SPEED_500KBPS:
            t_config = TWAI_TIMING_CONFIG_500KBITS();
            break;
        case ESP32CAN_SPEED_800KBPS:
            t_config = TWAI_TIMING_CONFIG_800KBITS();
            break;
        case ESP32CAN_SPEED_1MBPS:
            t_config = TWAI_TIMING_CONFIG_1MBITS();
            break;
        default:
            debugPrintln("TWAI: undefined buad rate");
            return;
            break;
    }

    /* install TWAI driver */
    switch (twai_driver_install(&g_config, &t_config, &f_config)) {
        case ESP_OK:
            debugPrintln("TWAI INSTALL: ok");
            break;
        case ESP_ERR_INVALID_ARG:
            debugPrintln("TWAI INSTALL: ESP_ERR_INVALID_ARG");
            return;
            break;
        case ESP_ERR_NO_MEM:
            debugPrintln("TWAI INSTALL: ESP_ERR_NO_MEM");
            return;
            break;
        case ESP_ERR_INVALID_STATE:
            debugPrintln("TWAI INSTALL: ESP_ERR_INVALID_STATE");
            return;
            break;
        default:
            debugPrintln("TWAI INSTALL: uknown error");
            return;
            break;
    }

    /* start TWAI driver */
    switch (twai_start()) {
        case ESP_OK:
            debugPrintln("TWAI START: ok");
            break;
        case ESP_ERR_INVALID_STATE:
            debugPrintln("TWAI START: ESP_ERR_INVALID_STATE");
            return;
            break;
        default:
            debugPrintln("TWAI START: uknown error");
            return;
            break;
    }
    debugPrintln("TWAI START: OK");
    return;
}

void CANEsp::SetFilter(uint16_t id) {
    uint32_t acc_code, acc_mask;
    acc_code = id << 21;
    acc_code = acc_code & 0xFFE00000;
    acc_mask = 0x001FFFFF;
    _f_config = {.acceptance_code = acc_code,
            .acceptance_mask = acc_mask,
            .single_filter = true};
}

void CANEsp::SetFilter(uint32_t acceptance_code, uint32_t acceptance_mask, bool single_filter) {
    _f_config = {.acceptance_code = acceptance_code,
            .acceptance_mask = acceptance_mask,
            .single_filter = single_filter};
}

void CANEsp::Send(uint16_t canID, uint8_t *data, uint8_t len) {

    txFrame.identifier = canID;
    txFrame.data_length_code = len;
    memcpy(txFrame.data, data, len);

    switch (twai_transmit(&txFrame, pdMS_TO_TICKS(10))) {
        case ESP_OK:
            break;
        case ESP_ERR_INVALID_ARG:
            debugPrintln("TWAI TX: ESP_ERR_INVALID_ARG");
            return;
            break;
        case ESP_ERR_TIMEOUT:
            debugPrintln("TWAI TX: ESP_ERR_TIMEOUT");
            return;
            break;
        case ESP_FAIL:
            debugPrintln("TWAI TX: ESP_FAIL");
            return;
            break;
        case ESP_ERR_INVALID_STATE:
            debugPrintln("TWAI TX: ESP_ERR_INVALID_STATE");
            return;
            break;
        case ESP_ERR_NOT_SUPPORTED:
            debugPrintln("TWAI TX: ESP_ERR_NOT_SUPPORTED");
            return;
            break;
        default:
            debugPrintln("TWAI TX: unknow error");
            return;
            break;
    }

    return;
}

void CANEsp::Receive(uint8_t *data, uint8_t len) {
    switch (twai_receive(&rxFrame, pdMS_TO_TICKS(10))) {
        case ESP_OK:
            break;
        case ESP_ERR_TIMEOUT:
            debugPrintln("TWAI RX: ESP_ERR_TIMEOUT");
            return;
            break;
        case ESP_ERR_INVALID_ARG:
            debugPrintln("TWAI RX: ESP_ERR_INVALID_ARG");
            return;
            break;
        case ESP_ERR_INVALID_STATE:
            debugPrintln("TWAI RX: ESP_ERR_INVALID_STATE");
            return;
            break;
        default:
            debugPrintln("TWAI RX: unknow error");
            return;
            break;
    }
    len = rxFrame.data_length_code;
    memcpy(data, rxFrame.data, len);
    return;
}