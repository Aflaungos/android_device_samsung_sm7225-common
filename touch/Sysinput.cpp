/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "Sysinput.h"

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace samsung {

bool Sysinput::isSupported() {
    std::ifstream file(TSP_CMD_LIST_NODE);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            if (!line.compare("set_sip_mode")) return true;
        }
        file.close();
	std::cout << "Sysinput: set_sip_mode is supported" << std::endl;
    }
    return false;
}

void Screenstate() {
    while (true) {
        // Check if power key is pressed
        std::ifstream powerkeyFile("/sys/class/sec/sec_powerkey/sec_powerkey_pressed");
        std::string sec_powerkey_pressed;
        if (powerkeyFile >> sec_powerkey_pressed && sec_powerkey_pressed == "1") {
            std::cout << "Power Key pressed" << std::endl;

            // Check if TSP is enabled
            std::ifstream enabledFile("/sys/class/sec/tsp/enabled");
            std::string enabledContent;
            if (enabledFile >> enabledContent && enabledContent != "1") {
                std::cout << "TSP not enabled, skipping gesture detection" << std::endl;
                continue; // Skip to the next iteration of the loop
            }

            // Write "check_connection" to /sys/class/sec/tsp/cmd
            std::ofstream cmdFile("/sys/class/sec/tsp/cmd");
            if (cmdFile.is_open()) {
                cmdFile << "check_connection";
                std::cout << "Message 'check_connection' written to /sys/class/sec/tsp/cmd" << std::endl;

                // Write "echo 1,0" to /sys/class/sec/tsp/enabled
                std::ofstream enableFile("/sys/class/sec/tsp/enabled");
                if (enableFile.is_open()) {
                    enableFile << "1,0";
                    std::cout << "Message '1,0' written to /sys/class/sec/tsp/enabled" << std::endl;

                    // Delay if needed before writing the next message
                    // ...

                    // Write "echo 2,1" to /sys/class/sec/tsp/enabled
                    enableFile << "2,1";
                    std::cout << "Message '2,1' written to /sys/class/sec/tsp/enabled" << std::endl;
                } else {
                    std::cerr << "Error: Unable to open file /sys/class/sec/tsp/enabled for writing" << std::endl;
                }
            } else {
                std::cerr << "Error: Unable to open file /sys/class/sec/tsp/cmd for writing" << std::endl;
            }
        } else {
            std::cout << "Power Key not pressed" << std::endl;
        }

        // Sleep for a short duration before checking again
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

}  // namespace samsung
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor