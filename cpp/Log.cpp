#include "Log.h"

// METHODES

string Log::getCurrentTime()
{
	// Get current time as a time_point
	auto now = std::chrono::system_clock::now();

	// Convert to time_t for local time conversion
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);

	// Convert to local time structure
	std::tm localTime;

#ifndef _WIN32 
	localtime_r(&now_time, &localTime);
#else
	localtime_s(&localTime, &now_time);
#endif

	// Calculate the fractional part of the second (4 digits)
	// Convert the time_since_epoch to microseconds, then get the remainder within a second
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
	int fraction = (microseconds.count() % 1000000) / 100;  // Result will be 0 to 9999

	// Use a string stream to format the output
	std::ostringstream oss;
	oss << std::put_time(&localTime, "%H:%M:%S") << ":"
		<< std::setw(4) << std::setfill('0') << fraction;

	return oss.str();
}

string Log::getTodaysDate()
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::tm localTime;

#ifndef _WIN32 
	localtime_r(&now_time, &localTime);
#else
	localtime_s(&localTime, &now_time);
#endif

	std::ostringstream oss;
	oss << std::put_time(&localTime, "%Y_%m_%d");

	return oss.str();
}

void Log::setTodaysDate()
{
	todaysDate = getTodaysDate();
}

void Log::setFileLogName()
{
#ifdef _WIN32
    const char PATH_SEP = '\\';
#else
    const char PATH_SEP = '/';
#endif

	const string folderName = Settings::logsFolderName.data();

	fileLogName = folderName + PATH_SEP + "LOG_" + todaysDate + ".log";
}

bool Log::createLogFolder()
{
	const string LogsFolderName = Settings::logsFolderName.data();

	std::filesystem::path dir(LogsFolderName);

	if (std::filesystem::exists(dir) && std::filesystem::is_directory(dir)) {
		ILog("Folder '" + LogsFolderName + "' already exists");

		return true;
	}
	else
	{
		if (std::filesystem::create_directory(dir)) {
			ILog("Folder '" + LogsFolderName + "' created successfully!");

			return true;
		}
		else {
			ILog("Failed to create '" + LogsFolderName + "' folder!");

			return false;
		}
	}
}

bool Log::checkIfLogFileExists()
{
	std::ifstream inFile(fileLogName);
	if (inFile.good()) {
		ILog("Log File exists! OK");
		inFile.close();

		return true;
	}
	else {
		ILog("Log File does NOT exist! Creating...");
		inFile.close();

		return false;
	}
}

bool Log::createLogFile(std::ofstream& stream)
{
	stream.open(fileLogName, std::ios::app);

	if (stream.is_open()) {
		stream << "=============[ LOG START ]============= \n";

		return true;
	}
	else
	{
		FLog("Unable to create a log file!");
		stream.close();

		return false;
	}
}

void Log::openStreamStatus(std::ofstream& stream)
{
	if (!stream.is_open()) {
		stream.open(fileLogName, std::ios::app);

		stream << "=============[ LOG START ]============= \n";
	}
}

void Log::reOpenFileStream(std::ofstream& stream, const string& logType, const string& str)
{
	ELog("Unable to write data to log file : " + str + '\n');
	ILog("Trying reopening stream to save data...");

	Log::openStreamStatus(stream);

	if (stream.is_open()) {
		ILog("Filestream is open again!");

		stream << "[" + Log::getCurrentTime() + "] | " + logType + " | " << str << std::endl;

		ILog("Log data has been saved!");
	}
	else
	{
		FLog("Unable to re-open filestream! FATAL");
		throw std::runtime_error("UnableToReopenLogFileStream");
	}
}

void Log::closeLogFile()
{
	try
	{
		if (outFile.is_open()) {
			outFile << "=============[ LOG END ]============= \n\n";
		}
		outFile.close();
	}
	catch (const std::exception&)
	{
		ELog("Unable to close a log file!");
		throw std::runtime_error("UnableCloseLogFileStream");
	}
}

// Main logging function
// @Param=logType			- Provide enum log type 
// @Param=str				- Provide message to log
// @DefParam=logToConsole	- Decides whether it should be logged to console or not
// @DefParam=ex				- Exception thrown by something (used only in exe type)
void log(const LogType& logType, const string& str, const bool& logToConsole, const std::exception* ex)
{
	static Log logger;

	const string curTime = logger.getCurrentTime();

	switch (logType) {
	case inf : // LOG INFORMATION
		if (logToConsole) {
			ILog("[" + curTime + "] | " + str);
		}

		if (logger.outFile.is_open()) {
			logger.outFile << "[" + curTime + "] | INFO | " << str << std::endl;
		}
		else
		{
			logger.reOpenFileStream(logger.outFile, "INFO", str);
		}

		logger.outFile.flush();
		break;
	case war : // LOG WARNING
		if (logToConsole) {
			WLog("[" + curTime + "] | " + str);
		}

		if (logger.outFile.is_open()) {
			logger.outFile << "[" + curTime + "] | WARN | " << str << std::endl;
		}
		else
		{
			logger.reOpenFileStream(logger.outFile, "WARN", str);
		}

		logger.outFile.flush();
		break;
	case err : // LOG ERROR
		if (logToConsole) {
			ELog("[" + curTime + "] | " + str);
		}

		if (logger.outFile.is_open()) {
			logger.outFile << "[" + curTime + "] | ERROR | " << str << std::endl;
		}
		else
		{
			logger.reOpenFileStream(logger.outFile, "ERROR", str);
		}

		logger.outFile.flush();
		break;
	case fat : // LOG FATAL
		if (logToConsole) {
			FLog("[" + curTime + "] | " + str);
		}

		if (logger.outFile.is_open()) {
			logger.outFile << "[" + curTime + "] | FATAL | " << str << std::endl;
		}
		else
		{
			logger.reOpenFileStream(logger.outFile, "FATAL", str);
		}

		logger.outFile.flush();
		break;
	case exe : // LOG EXCEPTION
		if (ex == nullptr) {
			string mes = "[" + curTime + "] | EXCEPTION IS NULLPTR !";
			FLog(mes);
			logger.outFile << mes << std::endl;
			break;
		}

		if (logToConsole) {
			FLog("=============[ EXCEPTION OCCURED ]=============");
			FLog("[" + curTime + "] | EXCEPTION DATA : " + ex->what());
			FLog("[" + curTime + "] | MESSAGE        : " + str);
		}

		if (logger.outFile.is_open()) {
			logger.outFile << "=============[ EXCEPTION OCCURED ]=============" << std::endl;
			logger.outFile << "[" + curTime + "] | " << "EXCEPTION DATA : " << ex->what() << std::endl;
			logger.outFile << "[" + curTime + "] | " << "MESSAGE        : " << str << std::endl;
		}
		else
		{
			logger.reOpenFileStream(logger.outFile, "FATAL", str);

			logger.outFile << "=============[ EXCEPTION OCCURED ]=============" << std::endl;
			logger.outFile << "[" + curTime + "] | " << "EXCEPTION DATA : " << ex->what() << std::endl;
			logger.outFile << "[" + curTime + "] | " << "MESSAGE        : " << str << std::endl;
		}

		logger.outFile.flush();
		break;
	}
}