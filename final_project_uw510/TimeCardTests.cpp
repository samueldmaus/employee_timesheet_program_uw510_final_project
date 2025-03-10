﻿#include "TimeCard.h"
#include "TestHarness.h"

#include <sstream>
#include <Windows.h>

TEST(constructor, TimeCard)
{
	const auto time_point = std::chrono::system_clock::now();
	const auto now_tm = TimeCard::makeTm(time_point);
	std::stringstream date;
	date << now_tm.tm_mon << "/" << now_tm.tm_mday << "/" << now_tm.tm_year;
	
	const TimeCard card(date.str(), "Sam Maus");
	const auto clock_in_tm = TimeCard::makeTm(card.getClockIn());
	
	CHECK_EQUAL(now_tm.tm_hour, clock_in_tm.tm_hour);
	CHECK_EQUAL(now_tm.tm_min, clock_in_tm.tm_min);
	CHECK_EQUAL(now_tm.tm_mon, clock_in_tm.tm_mon);
	CHECK_EQUAL(now_tm.tm_mday, clock_in_tm.tm_mday);
}

TEST(stream, TimeCard)
{
	const auto time_point = std::chrono::system_clock::now();
	const auto now_tm = TimeCard::makeTm(time_point);
	std::stringstream date;
	date << now_tm.tm_mon << "/" << now_tm.tm_mday << "/" << now_tm.tm_year;
	std::stringstream ss;
	ss << "Date: " << now_tm.tm_mon << "/" << now_tm.tm_mday << "/" << now_tm.tm_year << " -- Clock In: " << now_tm.tm_hour << ":" << now_tm.tm_min << ":" << now_tm.tm_sec << " -- Clock Out: " << now_tm.tm_hour << ":" << now_tm.tm_min << ":" << now_tm.tm_sec;
	
	const TimeCard card(date.str(), "Sam Maus");
	std::stringstream os;
	card.print(os);
	
	CHECK_EQUAL(ss.str(), os.str());
}

TEST(clockOut, TimeCard)
{
	const auto time_point = std::chrono::system_clock::now();
	const auto now_tm = TimeCard::makeTm(time_point);
	std::stringstream date;
	date << now_tm.tm_mon << "/" << now_tm.tm_mday << "/" << now_tm.tm_year;
	
	TimeCard card(date.str(), "Sam Maus");
	Sleep(2000);
	card.clockOut();

	const std::tm addition {2};
	const auto clock_out_tm = TimeCard::makeTm(card.getClockOut());
	CHECK_EQUAL(now_tm.tm_sec + addition.tm_sec, clock_out_tm.tm_sec);
}

TEST(copyConstructor, TimeCard)
{
	const TimeCard card1("1/1/2000", "Sam Maus");
	const auto card2(card1);

	CHECK_EQUAL("1/1/2000", card2.getTitle());
}

TEST(moveConstructor, TimeCard)
{
	const TimeCard card1("1/1/2000", "Sam Maus");
	const auto card2(std::move(card1));

	CHECK_EQUAL("1/1/2000", card2.getTitle());
	CHECK_EQUAL("Sam Maus", card2.getAuthor());
}