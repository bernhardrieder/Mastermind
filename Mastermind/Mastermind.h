#pragma once
#include "ConsoleUtils.h"
#include <vector>
#include <random>

class Mastermind
{
public:
	enum PossibleColor
	{
		BLUE, GREEN, TEAL, RED, PINK, YELLOW, WHITE
	};
	Mastermind(const std::vector<PossibleColor>& possibleColors);
	~Mastermind();

	int Execute();

private:
	void initRandomGenerator();
	void generateRandomColorSequence(char* inOutSequence, const int& length);
	std::vector<char> generateRandomColorSequence(const short& numOfGuessColors);

	void printWelcomeMessage() const;
	static void printHelp();
	void printCurrentSettings() const;
	void printAndChangeSettings();
	static void printRules();
	void printGuessColors() const;
	static void printColorRectangle(const ConsoleUtils::Colors::Color& color);
	static void printColorRectangle(const char& colorChar);
	static void deleteColoredRectangleOnConsole();

	void startGame();

	static bool isRightColorSequence(const std::vector<char>& winnerCode, char* userCode);
	static void determineUserSequenceAndPrintHints(const std::vector<char>& winnerCode, char* userCode);

	static char toChar(const PossibleColor& color);
	static ConsoleUtils::Colors::Color toConsoleColor(const char& color);
	
	const std::vector<PossibleColor> m_possibleColors;
	//take a look at https://stackoverflow.com/questions/38367976/do-stdrandom-device-and-stdmt19937-follow-an-uniform-distribution
	std::random_device m_randomDevice;
	std::mt19937_64 m_mersenneTwisterEngine;
	std::uniform_int_distribution<> m_randomColorDistribution;

	int m_possibleGuessAttempts = 12;
	int m_numOfSequenceColors = 4;

};

