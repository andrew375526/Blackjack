#include "Deck.h"
#include "Random.h"
#include <algorithm>

void Deck::shuffle()
{
	std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
	m_dealtCards = 0;
}