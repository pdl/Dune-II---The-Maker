#pragma once
#ifndef D2TM_CLOG_H_
#define D2TM_CLOG_H_

#include <stdio.h>
#include <string>

#include "include/enums.h"


class Logger {

	public:
		void log(eLogLevel level, eLogComponent component, const char *event, const char *message);
		void log(eLogLevel level, eLogComponent component, const char *event, const char *message, eLogOutcome outcome, int playerId, int houseId);
		void log(eLogLevel level, eLogComponent component, const char *event, const char *message, eLogOutcome outcome);

		void logCommentLine(const char *txt);

		void debug(const char *txt);

		void logHeader(const char *txt);

		static Logger *getInstance();

		void renew();

	private:
		FILE *file;

		time_t current_time;

		std::string getLogLevelString(eLogLevel level);
		std::string getLogComponentString(eLogComponent component);
		std::string getLogOutcomeString(eLogOutcome outcome);

		std::string getCurrentFormattedTime();
		std::string getLogHouseString(int houseId);

		void updateTime();

		static Logger *instance;

		std::string getIntegerAsString(int value);
		std::string getLongAsString(long value);

		long startTime; // start time of logging in miliseconds

		long getTimeInMilisDifference();
	protected:
		Logger();

};

#endif
