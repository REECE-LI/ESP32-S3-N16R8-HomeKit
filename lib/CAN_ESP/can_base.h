//
// Created by 22482 on 2024/1/23.
//

#ifndef CAN_BASE_H
#define CAN_BASE_H


#include <cstdint>

class CANBase {
public:
    virtual void Init() = 0;

    virtual void Send(uint16_t canID, uint8_t *data, uint8_t len) = 0;

    virtual void Receive(uint8_t *data, uint8_t len) = 0;

};


#endif //ESP32_S3_EXAMPLE_CAN_BASE_H
