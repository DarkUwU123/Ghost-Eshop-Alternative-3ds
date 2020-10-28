#include "config.hpp"
#include "logging.hpp"

#include <memory>

extern std::unique_ptr<Config> config;

std::string Logging::format(const std::string& fmt_str, ...) {
	va_list ap;
	char* fp = NULL;
	va_start(ap, fmt_str);
	vasprintf(&fp, fmt_str.c_str(), ap);
	va_end(ap);
	std::unique_ptr<char, decltype(free)*> formatted(fp, free);
	return std::string(formatted.get());
}

std::string Logging::logDate(void) {
	time_t unixTime;
	struct tm timeStruct;
	time(&unixTime);
	localtime_r(&unixTime, &timeStruct);
	return format("%04i-%02i-%02i %02i:%02i:%02i", timeStruct.tm_year + 1900, timeStruct.tm_mon + 1, timeStruct.tm_mday, timeStruct.tm_hour, timeStruct.tm_min, timeStruct.tm_sec);
}

void Logging::createLogFile(void) {
	if ((access("sdmc:/3ds/Ghost-Eshop/Log.log", F_OK) != 0)) {
		FILE* logFile = fopen(("sdmc:/3ds/Ghost-Eshop/Log.log"), "w");
		fclose(logFile);
	}
}

// Only write to the Log, if it is enabled in the Settings File!
void Logging::writeToLog(std::string debugText) {
	if (config->logging()) {
		std::ofstream logFile;
		logFile.open(("sdmc:/3ds/Ghost-Eshop/Log.log"), std::ofstream::app);
		std::string writeDebug = "[ ";
		writeDebug += logDate();
		writeDebug += " ] ";
		writeDebug += debugText.c_str();
		logFile << writeDebug << std::endl;
		logFile.close();
	}
}