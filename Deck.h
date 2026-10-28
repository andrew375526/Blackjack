#pragma once

#include "Card.h"
#include <array>
#include <expected>
#include <functional>

class Deck
{
public:
	enum class Error
	{
		noMoreCards,
	};

	using ConstCardRef = std::reference_wrapper<const Card>;
	constexpr std::expected<ConstCardRef, Error> dealCard();
	constexpr Deck();

	static constexpr auto maxCards{
		+Card::Rank::maxRanks * +Card::Suit::maxSuits
	};

	void shuffle();

private:
	std::array<Card, maxCards> m_cards{};
	int m_dealtCards{ 0 };
};

constexpr Deck::Deck()
{
	auto i{ 0 };

	for (const auto& suit : Card::g_suits)
	{
		for (const auto& rank : Card::g_ranks)
			std::data(m_cards)[i++] = Card{ .rank{rank}, .suit{suit} };
	}
}

constexpr auto Deck::dealCard() -> std::expected<ConstCardRef, Error>
{
	if (m_dealtCards >= maxCards)
		return std::unexpected(Deck::Error::noMoreCards);

	return std::data(m_cards)[m_dealtCards++];
}