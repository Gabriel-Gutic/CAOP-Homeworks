#pragma once
#include <chrono>
#include <string>


class Timer
{
public:
	Timer();
	~Timer();

	void Start();

	unsigned long long GetMicroseconds() const;
	double GetMilliseconds(unsigned int precision = 2) const;
	double GetSeconds(unsigned int precision = 2) const;
	std::string MicrosecondsToString() const;
	std::string MillisecondsToString(unsigned int precision = 2) const;
	std::string SecondsToString(unsigned int precision = 2) const;
	
	static void Wait(unsigned long ms);
private:
	bool isStopped;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
};

#define SLEEP(ms) Tomato::Timer::Wait(ms)
