#pragma once

#include "Card.h"
#include <array>

namespace Blackjack
{
	struct GameRules
	{
		int scoreToBust{ 22 };
		int dealerMinScore{ 17 };
	};

	enum class Result
	{
		playerWins,
		dealerWins,
		tie,
		playerBlackjack,
		dealerBlackjack,
		blackjackTie,
	};

	Result playBlackjack(const GameRules & = {});
}

namespace Blackjack
{
	class Player
	{
	public:
		constexpr Player(const Card&, const Card&, int scoreToBust);
		constexpr void hit(const Card&);
		constexpr int getTotalScore() const;
		constexpr const Card& getFirstCard() const;
		constexpr const Card& getSecondCard() const;
		constexpr bool hasBlackjack() const;
		constexpr int getScoreToBust() const;

	private:
		Card m_firstCard{};
		Card m_secondCard{};
		int m_totalScore{ 0 };
		int m_acesInHand{ 0 };
		int m_scoreToBust{};
		bool m_hasBlackjack{ false };
		constexpr void setAceValuesToOne();
	};
}

namespace Blackjack
{
	constexpr int getCardValue(const Card& c)
	{
		static constexpr std::array s_cVals{
			11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10
		};

		if (!isValid(c)) return 0;
		return std::data(s_cVals)[+c.rank];
	}

	constexpr bool isFaceCardOrTen(const Card& c)
	{
		using enum Card::Rank;

		switch (c.rank)
		{
		case ten:
		case jack:
		case queen:
		case king:
			break;
		default:
			return false;
		}

		return true;
	}

	constexpr bool eitherIsAce(const Card& c1, const Card& c2)
	{
		using enum Card::Rank;
		return (c1.rank == ace) || (c2.rank == ace);
	}

	constexpr bool eitherIsTen(const Card& c1, const Card& c2)
	{
		return isFaceCardOrTen(c1) || isFaceCardOrTen(c2);
	}

	constexpr bool hasBusted(const Player& p)
	{
		return p.getTotalScore() >= p.getScoreToBust();
	}
}

namespace Blackjack
{
	constexpr void Player::setAceValuesToOne()
	{
		m_totalScore -= (getCardValue({ Card::Rank::ace }) - 1);
	}

	constexpr Player::Player(
		const Card& c1,
		const Card& c2,
		int scoreToBust
	)
		: m_firstCard{ c1 }
		, m_secondCard{ c2 }
		, m_scoreToBust{ scoreToBust }
	{
		// Automatic hit of initial hand in blackjack.
		this->hit(getFirstCard());
		this->hit(getSecondCard());

		if (!eitherIsAce(getFirstCard(), getSecondCard())) return;
		if (!eitherIsTen(getFirstCard(), getSecondCard())) return;
		m_hasBlackjack = true;
	}

	constexpr void Player::hit(const Card& card)
	{
		m_totalScore += getCardValue(card);
		if (card.rank == Card::Rank::ace) ++m_acesInHand;

		for (; m_acesInHand > 0; --m_acesInHand)
		{
			if (getTotalScore() <= getScoreToBust()) break;
			setAceValuesToOne();
		}
	}

	constexpr int Player::getTotalScore() const
	{
		return m_totalScore;
	}

	constexpr const Card& Player::getFirstCard() const
	{
		return m_firstCard;
	}

	constexpr const Card& Player::getSecondCard() const
	{
		return m_secondCard;
	}

	constexpr bool Player::hasBlackjack() const
	{
		return m_hasBlackjack;
	}

	constexpr int Player::getScoreToBust() const
	{
		return m_scoreToBust;
	}
}