//
// Created by 22482 on 2024/1/24.
//

#ifndef SHELLFUNC_H
#define SHELLFUNC_H
#include "SimpleSerialShell.h"

/*
    before use this lib, you should add this code in your main.cpp:
    setup():
    shell.attach(Serial);
    shellInit();

    loop():
    shell.executeIfInput();
*/

void shellInit();

int ESP_REF(int argc, char **argv);

#endif //SHELLFUNC_H
