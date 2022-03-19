#include <iostream>

#include "log/Logger.h"

int main() {
    Logger::Instance().SetMode(LogMode::LOG_CONSLOE | LogMode::LOG_FILE, "./CodeCraft-2022.log");
    LOG_INFO << "Hello World";
	return 0;
}
