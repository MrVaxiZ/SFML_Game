#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "Aliases.h"
#include "Settings.h"

enum LogType
{
	inf, // INFORMATION
	war, // WARNING
	err, // ERROR
	fat, // FATAL
	exe  // EXCEPTION
};

struct Log {
private:
	string getTodaysDate();
	bool checkIfLogFileExists();
	bool createLogFile(std::ofstream& stream);
	bool createLogFolder();
	void closeLogFile();
	void setTodaysDate();
	void setFileLogName();
public:
	static string getCurrentTime();
	static void openStreamStatus(std::ofstream& stream);
	static void reOpenFileStream(std::ofstream& stream, const string& logTypeStr, const string& str);

	inline static string todaysDate; // Format : "YYYY_MM_DD"
	inline static string fileLogName;
	std::ofstream outFile;

	Log()
	{
		setTodaysDate();
		setFileLogName();
		if (createLogFolder()) {
			if (!checkIfLogFileExists()) {
				if (!createLogFile(outFile)) {
					throw std::runtime_error("LogFileCannotBeCreatedException");
				}
			}
		}
		else
		{
			throw std::runtime_error("LogFolderCannotBeCreatedException");
		}

		openStreamStatus(outFile);
	}
	~Log() {
		closeLogFile();
	}
};

// Main logging function
// @Param=logType			- Provide enum log type 
// @Param=str				- Provide message to log
// @DefParam=logToConsole	- Decides whether it should be logged to console or not
// @DefParam=ex				- Exception thrown by something (used only in exe type)
void log(
	const LogType& logtype,
	const string& str,
	const bool& logToConsole = false,
	const std::exception* ex = nullptr
);