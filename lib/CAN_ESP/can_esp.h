//
// Created by 22482 on 2024/1/23.
//

#ifndef CAN_ESP_H
#define CAN_ESP_H

#include "can_base.h"
//#include "Arduino.h"
#include "driver/gpio.h"
#include "driver/twai.h"

// #define ESP32CAN_DEBUG     /* serial print debug info */

#ifdef ESP32CAN_DEBUG
#define debugPrint(x) 	    Serial.print(x)
#define debugPrintln(x)	    Serial.println(x)
#else
#define debugPrint(x)
#define debugPrintln(x)
#endif

class CANEsp : public CANBase {
public:
    typedef enum {
        ESP32CAN_SPEED_100KBPS = 100,
        ESP32CAN_SPEED_125KBPS = 125,
        ESP32CAN_SPEED_250KBPS = 250,
        ESP32CAN_SPEED_500KBPS = 500,
        ESP32CAN_SPEED_800KBPS = 800,
        ESP32CAN_SPEED_1MBPS = 1000,
    } ESP32CAN_BAUDRATE_e;

    typedef enum {
        ESP32CAN_ERR = 0,  /* not ok, something is wrong */
        ESP32CAN_OK = 1   /* ok, all seems well */
    } ESP32CAN_STATUS_e;

    explicit CANEsp(uint8_t _canTxPin, uint8_t _canRxPin, ESP32CAN_BAUDRATE_e _canBaudRate) : canTxPin(_canTxPin),
                                                                                              canRxPin(_canRxPin),
                                                                                              canBaudRate(
                                                                                                      _canBaudRate) {};

    void Init() override;

    // 若不设置滤波器的话，会接收到所有的报文
    void SetFilter(uint16_t id);

    // 规则有待完善
    void SetFilter(uint32_t acceptance_code, uint32_t acceptance_mask, bool single_filter);

    void Send(uint16_t canID, uint8_t *data, uint8_t len) override;

    void Receive(uint8_t *data, uint8_t len) override;

private:
    uint8_t canTxPin;

    uint8_t canRxPin;

    twai_message_t txFrame {
//        .extd = 0,
//        .rtr = 0,
//        .ss = 0,
    };

    twai_message_t rxFrame;

    ESP32CAN_BAUDRATE_e canBaudRate;

    twai_filter_config_t _f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
};


#endif //ESP32_S3_EXAMPLE_CAN_ESP_H
