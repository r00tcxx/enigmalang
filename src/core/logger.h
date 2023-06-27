#pragma once
#include <format>
#include <atomic>
#include <iostream>
#include "tk/singleton.h"

enum LogLevel {
	kDebug,
	kError,
	kInfo,
	kWarn,
};

class Logger : public tk::Singleton<Logger> {
	friend class tk::Singleton<Logger>;
public:
	NO_COPYABLE_MOVEABLE(Logger)
	void logging(
		const LogLevel lvl,
		std::string&& msg) {
		bool excepted{ false };
		while (!flag_.compare_exchange_weak(excepted, true)) excepted = false;
		std::cout << msg << std::endl;
		flag_.store(false);
	}
private:
	Logger() {};
private:
	std::atomic<bool> flag_;
};

template<typename ...Args>
void Info(
	const std::string_view fmt,
	Args ...args) {
	Logger::Instance().logging(LogLevel::kInfo, std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...)));
}

template<typename ...Args>
void Debug(
	std::string_view fmt,
	Args ...args) {
	Logger::Instance().logging(LogLevel::kDebug, std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...)));
}

template<typename ...Args>
void Error(
	std::string_view fmt,
	Args ...args) {
	Logger::Instance().logging(LogLevel::kError, std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...)));
}

template<typename ...Args>
void Warn(
	std::string_view fmt,
	Args ...args) {
	Logger::Instance().logging(LogLevel::kWarn, std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...)));
}
