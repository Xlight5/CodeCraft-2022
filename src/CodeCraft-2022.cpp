#include <iostream>

#include "log/Logger.h"

int main() {
    Logger::Instance().SetMode(LOG_CONSLOE);
	return 0;
}
