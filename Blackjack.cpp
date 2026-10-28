#include "Blackjack.h"
#include "Card.h"
#include "Deck.h"
#include "Input.h"
#include <cassert>
#include <expected>
#include <iostream>
#include <utility>

namespace Blackjack
{
	namespace
	{
		constexpr const Card& dealCard(Deck& deck)
		{
			const std::expected card{ deck.dealCard() };
			if (card) return *card;

			switch (card.error())
			{
			case Deck::Error::noMoreCards:
				deck.shuffle();
				return *(deck.dealCard());
			default:
				assert(!"Missing case in switch.");
			}

#ifdef _DEBUG
			assert(!"Unreachable code reached.");
			std::unreachable();
#else
			std::unreachable();
#endif
		}

		constexpr Player setupPlayer(Deck& d, const GameRules& gr)
		{
			return {
				dealCard(d),
				dealCard(d),
				gr.scoreToBust,
			};
		}

		void playPlayersTurn(Player&, Deck&);
		void playDealersTurn(Player&, Deck&, int dealerMinScore);
	}
}

namespace Blackjack
{
	Result playBlackjack(const GameRules& gameRules)
	{
		Deck deck{};
		deck.shuffle();
		Player dealer{ setupPlayer(deck, gameRules) };

		std::cout << "The dealer is showing: " << dealer.getFirstCard() << " ("
			<< getCardValue(dealer.getFirstCard()) << ")\n";

		Player player{ setupPlayer(deck, gameRules) };

		std::cout << "You have score: " << player.getFirstCard() << " "
			<< player.getSecondCard() << " (" << player.getTotalScore()
			<< ")\n";

		if (dealer.hasBlackjack())
		{
			std::cout << "The dealer flips a " << dealer.getSecondCard()
				<< ". They now have: " << dealer.getTotalScore() << "\n";

			if (player.hasBlackjack()) return Result::blackjackTie;
			return Result::dealerBlackjack;
		}

		if (player.hasBlackjack() && !dealer.hasBlackjack())
			return Result::playerBlackjack;

		playPlayersTurn(player, deck);
		if (hasBusted(player)) return Result::dealerWins;
		playDealersTurn(dealer, deck, gameRules.dealerMinScore);
		if (hasBusted(dealer)) return Result::playerWins;

		if (dealer.getTotalScore() == player.getTotalScore())
			return Result::tie;

		if (dealer.getTotalScore() > player.getTotalScore())
			return Result::dealerWins;

		return Result::playerWins;
	}
}

namespace Blackjack
{
	namespace
	{
		void playPlayersTurn(Player& player, Deck& deck)
		{
			while (!hasBusted(player))
			{
				std::cout << "(h) to hit, or (s) to stand: ";
				char input{};
				std::cin >> input;
				Input::clearBuffer();
				if (input == 's') break;
				if (input != 'h') continue;
				const auto& card{ dealCard(deck) };
				player.hit(card);

				std::cout << "You were dealt " << card << ". You now have: "
					<< player.getTotalScore() << "\n";
			}

			if (hasBusted(player))
				std::cout << "You went bust!\n";
		}

		void playDealersTurn(Player& dealer, Deck& deck, int dealerMinScore)
		{
			std::cout << "The dealer flips a " << dealer.getSecondCard()
				<< ". They now have: " << dealer.getTotalScore() << "\n";

			while (dealer.getTotalScore() < dealerMinScore)
			{
				const auto& card{ dealCard(deck) };
				dealer.hit(card);

				std::cout << "The dealer flips a " << card
					<< ". They now have: " << dealer.getTotalScore() << "\n";
			}

			if (hasBusted(dealer))
				std::cout << "The dealer went bust!\n";
		}
	}
}