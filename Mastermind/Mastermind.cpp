#include "Mastermind.h"

#include "ConsoleUtils.h"


Mastermind::Mastermind(const std::vector<PossibleColor>& possibleColors) : m_possibleColors(possibleColors)
{
	initRandomGenerator(); // intializes random number generator at program start-up
}

Mastermind::~Mastermind()
{
}

int Mastermind::Execute()
{
	printWelcomeMessage();

	char key;
	while ((key = _getch()) != ConsoleUtils::KeyCodes::ESC)
	{
		if(key == ConsoleUtils::KeyCodes::H || key == ConsoleUtils::KeyCodes::h)
		{
			printHelp();
		}
		else if (key == ConsoleUtils::KeyCodes::S || key == ConsoleUtils::KeyCodes::s)
		{
			printAndChangeSettings();
			printWelcomeMessage();
		}
		else if(key == ConsoleUtils::KeyCodes::R || key == ConsoleUtils::KeyCodes::r)
		{
			printRules();
		}
		else if (key == ConsoleUtils::KeyCodes::Enter)
		{
			startGame();
			printWelcomeMessage();
		}
	}
	return 1;
}

void Mastermind::initRandomGenerator()
{
	m_mersenneTwisterEngine = std::mt19937_64(m_randomDevice());
	m_randomColorDistribution = std::uniform_int_distribution<>(0, m_possibleColors.size() - 1);
}

void Mastermind::generateRandomColorSequence(char* inOutSequence, const int& length)
{
	for (int i = 0; i < length; ++i)
	{
		inOutSequence[i] = toChar(m_possibleColors[m_randomColorDistribution(m_mersenneTwisterEngine)]);
	}
}

std::vector<char> Mastermind::generateRandomColorSequence(const short& numOfGuessColors)
{
	std::vector<char> colors;
	for (int i = 0; i < numOfGuessColors; ++i)
	{
		colors.push_back(toChar(m_possibleColors[m_randomColorDistribution(m_mersenneTwisterEngine)]));
	}
	return colors;
}

void Mastermind::printWelcomeMessage() const
{
	ConsoleUtils::setTextColor(ConsoleUtils::Colors::WHITE);
	std::cout << "Welcome to the Game of Mastermind!" << std::endl << std::endl;
	printRules();
	printHelp();
}

void Mastermind::printHelp()
{
	auto tmp = ConsoleUtils::CurrentConsoleOutputColor;
	ConsoleUtils::setTextColor(ConsoleUtils::Colors::GREEN);

	std::cout << "Help:" << std::endl
		<< "-) Press 'H' for showing this help" << std::endl
		<< "-) Press 'ENTER' to start the game" << std::endl
		<< "-) Press 'ESC' to quit/suspend the game" << std::endl
		<< "-) Press 'S' to enter and change the settings" << std::endl
		<< "-) Press 'R' for showing the rules of Mastermind" << std::endl << std::endl;

	ConsoleUtils::setTextColor(tmp);
}

void Mastermind::printCurrentSettings() const
{
	auto tmp = ConsoleUtils::CurrentConsoleOutputColor;
	ConsoleUtils::setTextColor(ConsoleUtils::Colors::TEAL);

	std::cout << "Settings:" << std::endl
		<< "Possible Guess Attempts: " << m_possibleGuessAttempts << std::endl
		<< "Number of Sequence Colors: " << m_numOfSequenceColors << std::endl;
	std::cout << std::endl;

	ConsoleUtils::setTextColor(tmp);
}

void Mastermind::printAndChangeSettings()
{
	auto tmp = ConsoleUtils::CurrentConsoleOutputColor;
	ConsoleUtils::setTextColor(ConsoleUtils::Colors::TEAL);
	
	printCurrentSettings();
	std::cout	<< "How to change the settings:" << std::endl
				<< "-) Press 'ESC' to quit the settings." << std::endl
				<< "-) Press 'G' to change number of pussible guess attempts." << std::endl
				<< "-) Press 'C' to change number of sequence colors." << std::endl;
	
	std::cout << std::endl;
	
	char inputKey;
	while ((inputKey = _getch()) != ConsoleUtils::KeyCodes::ESC)
	{
		if(inputKey == ConsoleUtils::KeyCodes::G || inputKey == ConsoleUtils::KeyCodes::g)
		{
			int input;
			std::cout << "New number of possible guess attemps: ";
			std::cin >> input;
			if(input < 1)
			{
				std::cout << "ERROR: number needs to be bigger than 0!" << std::endl;
			}
			else
			{
				m_possibleGuessAttempts = input;
				std::cout << std::endl;
				printCurrentSettings();
			}
		}
		if (inputKey == ConsoleUtils::KeyCodes::C || inputKey == ConsoleUtils::KeyCodes::c)
		{
			int input;
			std::cout << "New number of sequence colors: ";
			std::cin >> input;
			if (input < 1)
			{
				std::cout << "ERROR: number needs to be bigger than 0!" << std::endl;
			}
			else
			{
				m_numOfSequenceColors = input;
				std::cout << std::endl;
				printCurrentSettings();
			}
		}
	}
	
	std::cout << std::endl;

	ConsoleUtils::setTextColor(tmp);
}

void Mastermind::printRules()
{
	auto tmp = ConsoleUtils::CurrentConsoleOutputColor;
	ConsoleUtils::setTextColor(ConsoleUtils::Colors::WHITE);
	
	std::cout << "Rules of Mastermind: " << std::endl;
	std::cout << "Mastermind is a game where you need to find a sequence of colors." << std::endl;

	std::cout << "There are 2 kind of players - the coder and the guesser." << std::endl; 

	ConsoleUtils::setTextColor(ConsoleUtils::Colors::RED);
	std::cout << "You are going to play the guesser and you need to find the right color sequence!" << std::endl;

	ConsoleUtils::setTextColor(ConsoleUtils::Colors::WHITE);
	std::cout	<< "At the beginning of the game you'll see all possible game colors." << std::endl
				<< "Afterwards you need to type your guesses with the shown keyboard characters." << std::endl
				<< "You can delete a guessed color with 'BACKSPACE' and submit your sequence with 'ENTER'!" << std::endl
				<< "After submitting the guess sequence, the coder responses with 'o' for a 'correct color but " << std::endl
				<< "on the wrong position' and with a 'x' for 'correct color on the correct position'!" << std::endl
				<< "The length of the sequence and number of possible guess attemps depend on your settings!" << std::endl
				<< "That's everything you need to know! GOOD LUCK!" << std::endl << std::endl;

	ConsoleUtils::setTextColor(tmp);
}

void Mastermind::printGuessColors() const
{
	auto tmp = ConsoleUtils::CurrentConsoleOutputColor;
	ConsoleUtils::setTextColor(ConsoleUtils::Colors::TEAL);
	
	std::cout	<< "Following Colors are open to guess:" << std::endl 
				<< "--------------------------------------" << std::endl
				<< "Color | Keyboard input for this color" << std::endl
				<< "--------------------------------------" << std::endl;

	for (auto color: m_possibleColors)
	{
		std::cout << " ";
		printColorRectangle(toConsoleColor(toChar(color)));
		std::cout << " |  " << toChar(color) << std::endl;
	}
	std::cout << "--------------------------------------" << std::endl << std::endl;
	ConsoleUtils::setTextColor(tmp);
}

void Mastermind::printColorRectangle(const ConsoleUtils::Colors::Color& color)
{
	auto tmp = ConsoleUtils::CurrentConsoleOutputColor;
	ConsoleUtils::setTextColor(color);
	std::cout << ConsoleUtils::FilledRectangleSymbol << ConsoleUtils::FilledRectangleSymbol << ConsoleUtils::FilledRectangleSymbol << " ";
	ConsoleUtils::setTextColor(tmp);
}

void Mastermind::printColorRectangle(const char& colorChar)
{
	printColorRectangle(toConsoleColor(colorChar));
}

void Mastermind::deleteColoredRectangleOnConsole()
{
	ConsoleUtils::offsetCursorInLine(-4);
	printColorRectangle(ConsoleUtils::Colors::BLACK);
	ConsoleUtils::offsetCursorInLine(-4);
}

void Mastermind::startGame()
{
	printGuessColors();

	bool quitGame = false;
	do
	{
		bool isWin = false;
		std::vector<char> randomColorSequence = generateRandomColorSequence(m_numOfSequenceColors);

		ConsoleUtils::setTextColor(ConsoleUtils::Colors::YELLOW);

		////print generated random color code
		//{
		//	std::cout << "generated random color code: ";
		//	for (int i = 0; i < m_numOfGuessColors; ++i)
		//	{
		//		printColorRectangle(toConsoleColor(randomColorSequence[i]));
		//		std::cout << " ";
		//	}
		//	std::cout << std::endl << std::endl;
		//}

		for (int i = 0; i < m_possibleGuessAttempts && !isWin; ++i)
		{
			std::cout << "Guess #" << i + 1 << ":" << std::endl;
			char inputKey;
			int guessedColorIndex = 0;
			std::vector<char> guessedSequence(m_numOfSequenceColors);
			while ((inputKey = _getch()) != ConsoleUtils::KeyCodes::ESC)
			{
				if (inputKey == ConsoleUtils::KeyCodes::Backspace && guessedColorIndex > 0)
				{
					deleteColoredRectangleOnConsole();
					--guessedColorIndex;
				}
				else if (inputKey == ConsoleUtils::KeyCodes::Enter && guessedColorIndex == m_numOfSequenceColors)
				{
					determineUserSequenceAndPrintHints(randomColorSequence, &guessedSequence[0]);
					break;
				}
				else if (toConsoleColor(inputKey) != ConsoleUtils::Colors::BLACK && guessedColorIndex < m_numOfSequenceColors)
				{
					guessedSequence[guessedColorIndex++] = inputKey;
					printColorRectangle(toConsoleColor(inputKey));
				}
			}
			if (inputKey == ConsoleUtils::KeyCodes::ESC)
			{
				quitGame = true;
				std::cout << "Game suspended!" << std::endl;
				break;
			}
			isWin = isRightColorSequence(randomColorSequence, &guessedSequence[0]);
		}

		std::cout << std::endl;

		//todo: beautify
		if(isWin)
		{
			ConsoleUtils::setTextColor(ConsoleUtils::Colors::GREEN);
			std::cout << "YOU WON!" << std::endl;
		}
		else
		{
			ConsoleUtils::setTextColor(ConsoleUtils::Colors::RED);
			std::cout << "SORRY - YOU LOST!" << std::endl;
		}

		std::cout << "Press 'ENTER' for a quick restart or 'ESC' for getting back to the menu!" << std::endl;
		quitGame = true;
		char inputKey;
		while ((inputKey = _getch()) != ConsoleUtils::KeyCodes::ESC)
		{
			if (inputKey == ConsoleUtils::KeyCodes::Enter)
			{
				quitGame = false;
				std::cout << "FAST GAME RESTART!! " << std::endl << std::endl;
				break;
			}
		}
	}
	while (!quitGame);

	std::cout << std::endl;
}

bool Mastermind::isRightColorSequence(const std::vector<char>& winnerCode, char* userCode)
{
	for (int i = 0; i < winnerCode.size(); ++i)
	{
		if (winnerCode[i] != userCode[i])
			return false;
	}
	return true;
}

void Mastermind::determineUserSequenceAndPrintHints(const std::vector<char>& winnerCode, char* userCode)
{
	/*
	 * Beispiel:
	 * 
	 * grün – rot – blau – grün
	 * 
	 * 1. Rateversuch: rot – gelb – rot – grün
	 * Antwort: Einmal schwarz (weil an der vierten Position grün richtig ist), 
	 * einmal weiß (weil rot im gesuchten Code einmal vorkommt, aber nicht an 
	 * der ersten oder dritten Stelle).
	 * 
	 * 2. Rateversuch: grün – grün – orange – rot
	 * Antwort: Einmal schwarz (weil grün diesmal an der ersten Position richtig 
	 * ist), zweimal weiß (weil 1. grün im gesuchten Code ein zweites Mal vorkommt, 
	 * aber nicht an der zweiten Position und 2. rot im gesuchten Code vorkommt, 
	 * aber nicht an der vierten Position).
	 */

	const char used = -1;
	std::vector<char> openWinnerColors(winnerCode);
	std::vector<char> openUserColors(userCode, userCode + winnerCode.size());

	std::cout << " | ";

	//determine black response pins -> correct color & position
	for(int i = 0; i < winnerCode.size(); ++i)
	{
		if (winnerCode[i] == userCode[i])
		{
			openWinnerColors[i] = used;
			openUserColors[i] = used;
			std::cout << "x ";
		}
	}

	//determine white response pins -> correct color but wrong position
	for(int i = 0; i < openWinnerColors.size(); ++i)
	{
		for(int x = 0; x < openUserColors.size(); ++x)
		{
			if (openUserColors[x] == used || openWinnerColors[i] == used) continue;
			if (openUserColors[x] == openWinnerColors[i])
			{
				openUserColors[x] = used;
				openWinnerColors[i] = used;
				std::cout << "o ";
			}
		}
	}

	std::cout << std::endl;
}

char Mastermind::toChar(const PossibleColor& color)
{
	switch (color)
	{
	case BLUE: return 'b';
	case GREEN: return 'g';
	case TEAL: return 't';
	case RED: return 'r';
	case PINK: return 'p';
	case YELLOW: return 'y';
	case WHITE: return 'w';
	}
	return 0;
}

ConsoleUtils::Colors::Color Mastermind::toConsoleColor(const char& color)
{
	switch (tolower(color))
	{
	case 'b': return ConsoleUtils::Colors::BLUE;
	case 'g': return ConsoleUtils::Colors::GREEN;
	case 't': return ConsoleUtils::Colors::TEAL;
	case 'r': return ConsoleUtils::Colors::RED;
	case 'p': return ConsoleUtils::Colors::PINK;
	case 'y': return ConsoleUtils::Colors::YELLOW;
	case 'w': return ConsoleUtils::Colors::WHITE;
	default: return ConsoleUtils::Colors::BLACK;
	}
}
