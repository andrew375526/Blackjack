#include "Card.h"
#include <array>
#include <ostream>

std::ostream& operator<<(std::ostream& os, const Card& card)
{
	static constexpr std::array s_ranksInitials{
		'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'
	};

	static_assert(std::ssize(s_ranksInitials) == +Card::Rank::maxRanks);

	static constexpr std::array s_suitsInitials{ 'C', 'D', 'H', 'S' };
	static_assert(std::ssize(s_suitsInitials) == +Card::Suit::maxSuits);

	return os << std::data(s_ranksInitials)[+card.rank]
		<< std::data(s_suitsInitials)[+card.suit];
}