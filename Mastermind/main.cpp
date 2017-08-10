#include "Mastermind.h"

int main(int argc, char** argv)
{
	SetConsoleTitle(TEXT("Mastermind"));	// set console title
	Mastermind mastermindGame(
		{	Mastermind::PossibleColor::BLUE, Mastermind::PossibleColor::GREEN, 
			/*Mastermind::PossibleColor::PINK,*/ Mastermind::PossibleColor::RED, 
			Mastermind::PossibleColor::TEAL, Mastermind::PossibleColor::WHITE, 
			Mastermind::PossibleColor::YELLOW
		}
	);
	return mastermindGame.Execute();
}