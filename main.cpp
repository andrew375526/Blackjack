#include "Blackjack.h"
#include "Input.h"
#include <cassert>
#include <iostream>
#include <string_view>
#include <utility>

namespace
{
	char getInput(std::string_view prompt = "")
	{
		while (true)
		{
			std::cout << prompt;
			char input{};
			std::cin >> input;
			Input::clearBuffer();
			if (input == 'n') return 'n';
			if (input != 'y') continue;
			std::cout << "\n";
			return 'y';
		}
	}
}

int main()
{
	do
	{
		switch (Blackjack::playBlackjack())
		{
		case Blackjack::Result::playerWins:
			std::cout << "You win!";
			break;
		case Blackjack::Result::dealerWins:
			std::cout << "You lose!";
			break;
		case Blackjack::Result::tie:
			std::cout << "Tie!";
			break;
		case Blackjack::Result::playerBlackjack:
			std::cout << "You win with blackjack!";
			break;
		case Blackjack::Result::dealerBlackjack:
			std::cout << "You lose! Dealer has blackjack!";
			break;
		case Blackjack::Result::blackjackTie:
			std::cout << "Tie with Blackjack!";
			break;
		default:
#ifdef _DEBUG
			assert(!"Missing case in switch.");
#else
			std::unreachable();
#endif
		}

		std::cout << "\n";
	} while (getInput("Continue playing? (y/n): ") == 'y');

	return 0;
}