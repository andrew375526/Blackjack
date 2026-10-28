#pragma once

#include <iterator>
#include <utility>

struct Card
{
	enum class Error
	{
		invalidCard,
	};

	enum class Rank
	{
		ace,
		two,
		three,
		four,
		five,
		six,
		seven,
		eight,
		nine,
		ten,
		jack,
		queen,
		king,

		maxRanks
	};

	enum class Suit
	{
		club,
		diamond,
		heart,
		spade,

		maxSuits
	};

	Rank rank{};
	Suit suit{};
	using enum Rank;

	static constexpr Rank g_ranks[]{
		ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king
	};

	using enum Suit;
	static constexpr Suit g_suits[]{ club, diamond, heart, spade };
};

constexpr auto operator+(Card::Rank cardRank) noexcept
{
	return std::to_underlying(cardRank);
}

constexpr auto operator+(Card::Suit cardSuit) noexcept
{
	return std::to_underlying(cardSuit);
}

static_assert(std::ssize(Card::g_ranks) == +Card::Rank::maxRanks);
static_assert(std::ssize(Card::g_suits) == +Card::Suit::maxSuits);

constexpr bool isValid(const Card& card)
{
	return card.rank >= Card::Rank{} && card.rank < Card::Rank::maxRanks
		&& card.suit >= Card::Suit{} && card.suit < Card::Suit::maxSuits;
}

std::ostream& operator<<(std::ostream& out, const Card& card);