//
// Created by 22482 on 2024/1/24.
//

#include "shellfunc.h"



void shellInit() {
    // just an example
     shell.addCommand(F("esp env"), ESP_REF);

}

int ESP_REF(int argc, char **argv) {
    if (argc == 2) {
        shell.println("ESP32-S3");
        shell.println("Version: 1.0.0");
        shell.println("Build: 2024/1/24");
        shell.println("Author: XiaoJun");
        // print lib
        shell.println("Libraries:");
        shell.println("         CAN_ESP");
        shell.println("         ShellFunc");

    } else
        shell.println("bad argument count");
    return 1;

}
