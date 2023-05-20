#include "Timer.h"

#include <iostream>


Timer::Timer() : beg_(clock_::now()) {}

void Timer::reset()
{
	beg_ = clock_::now();
}

std::chrono::seconds Timer::elapsed() const
{
	return std::chrono::duration_cast<std::chrono::seconds>(clock_::now() - beg_);
}

std::chrono::milliseconds Timer::elapsedMILI() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(clock_::now() - beg_);
}
std::chrono::microseconds Timer::elapsedMICROS() const
{
	return std::chrono::duration_cast<std::chrono::microseconds>(clock_::now() - beg_);
}

std::chrono::nanoseconds Timer::elapsedNANO() const
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(clock_::now() - beg_);
}

void Timer::printVar(const char* a, const bool reset)
{
	auto time = elapsedMICROS().count();

	std::string name = " microseconds";

	if (time > 1000000)
	{
		time /= 1000000;
		name = " s";
	}
	else if (time < 1000000 && time > 1000)
	{
		time /= 1000;
		name = " ms";
	}

	//LOG_TIME(std::string{ a } + std::to_string(time) + name);
	//std::cout << std::string{ a } + std::to_string(time) + name << std::endl;
	std::cout << a << " " <<  time << " " << name << "\n";

	if (reset)
		this->reset();
}

void Timer::printMICROS(const std::string_view text) const
{
	const auto time = elapsedMICROS().count();

	std::cout << text << " " << time << " Microseconds" << "\n";
}

void Timer::printNANO(std::string_view text) const
{
	const auto time = elapsedNANO().count();

	std::cout << text << " " << time << " Nanoseconds" << "\n";
}