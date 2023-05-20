#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<double, std::ratio<1> > second_;
	std::chrono::time_point<clock_> beg_;

public:
	Timer();
	void reset();

	std::chrono::seconds elapsed() const;
	std::chrono::microseconds elapsedMICROS() const;
	std::chrono::nanoseconds elapsedNANO() const;
	std::chrono::milliseconds elapsedMILI() const;

	void printVar(const std::string_view& text, const bool reset = false) { printVar(text.data(), reset); }

	void printVar(const char* a = "", bool reset = false);
	void printNANO(std::string_view text = "") const;
	void printMICROS(std::string_view text = "") const;
};

#endif // TIMER_H
