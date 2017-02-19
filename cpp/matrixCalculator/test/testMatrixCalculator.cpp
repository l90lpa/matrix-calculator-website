//
//  testBlackjackTwo.cpp
//  blackjack-two
//
//  Created by Liam on 19/10/2016.
//  Copyright © 2016 Liam. All rights reserved.
//

#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE Test: BlackjackTwo



#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <iostream>
#include "include/card.hpp"
#include "include/deck.hpp"


BOOST_AUTO_TEST_SUITE(test_suite_card)

BOOST_AUTO_TEST_CASE(printCard_cardIsAceSpade_printAS)
{
    boost::test_tools::output_test_stream output;
    std::streambuf *originalBuf; // Pointer to a stream buffer
    std::streambuf *newBuf;
    originalBuf = std::cout.rdbuf(); // Pointer to the normal stream buffer of std::cout.
    newBuf = output.rdbuf();         // Pointer to the stream buffer of "output".
    std::cout.rdbuf(newBuf);         // Set the stream buffer for std::cout to the stream buffer of "output".
    
    
    Card card{Card::RANK_ACE, Card::SUIT_SPADE};
    
    card.printCard(); // Causes data to be sent to "output's" stream buffer.
    
    std::cout.rdbuf(originalBuf);  // Set the stream buffer for std::cout back to normal.
    
    BOOST_CHECK(output.is_equal("AS")); // Check that the data in output is equal to the given data "AS".
}

BOOST_AUTO_TEST_CASE(getCardValue_cardAD_value11)
{
    Card AD{Card::CardRank::RANK_ACE, Card::CardSuit::SUIT_DIAMOND};
    BOOST_CHECK_EQUAL(AD.getCardValue(), 11);
}

BOOST_AUTO_TEST_CASE(getCardValue_card2H_value2)
{
    Card TwoH{Card::CardRank::RANK_2, Card::CardSuit::SUIT_HEART};
    BOOST_CHECK_EQUAL(TwoH.getCardValue(), 2);
}

/*
 BOOST_AUTO_TEST_CASE(getCardValue_playersScoreIs8_playersChoice)
 {
 
 BOOST_CHECK(output.is_equal("h") || output.is_equal("l"))
 }
 
 BOOST_AUTO_TEST_CASE(getCardValueWhenAce_playersScoreIs10_value11)
 {
 
 
 }
 
 BOOST_AUTO_TEST_CASE(getCardValueWhenAce_playersScoreIs13_value1)
 {
 
 }
 
 BOOST_AUTO_TEST_CASE(getCardValue_dealersScoreIs8_value11)
 {
 
 }
 
 BOOST_AUTO_TEST_CASE(getCardValueWhenAce_dealersScoreIs11_value1)
 {
 
 }
 */
BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(test_suite_deck)

BOOST_AUTO_TEST_CASE(printDeck_orderedDeck_dispalyOrderedDeck)
{
    boost::test_tools::output_test_stream output("OrderedDeckPrintPattern.txt", true);

    Deck orderedDeck;
    orderedDeck.printDeck(output);
   
    BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(shuffelDeck_alterOrderedDeckToRandomOrder_displayRandomOrderedDeck)
{
    boost::test_tools::output_test_stream output("OrderedDeckPrintPattern.txt", true);
    
    Deck orderedDeck;
    orderedDeck.shuffleDeck();
    orderedDeck.printDeck(output);
    
    BOOST_CHECK(!output.match_pattern());
}

BOOST_AUTO_TEST_CASE(dealCard_usingOrderedDeckDealFirstThreeCards_shouldDeal_2H_3H_4H)
{
    Deck orderedDeck;
    const Card TwoH{Card::CardRank::RANK_2, Card::CardSuit::SUIT_HEART};
    const Card ThreeH{Card::CardRank::RANK_3, Card::CardSuit::SUIT_HEART};
    const Card FourH{Card::CardRank::RANK_4, Card::CardSuit::SUIT_HEART};
    
    BOOST_CHECK(orderedDeck.dealCard() == TwoH);
    BOOST_CHECK(orderedDeck.dealCard() == ThreeH);
    BOOST_CHECK(orderedDeck.dealCard() == FourH);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(test_suite_players)
 
BOOST_AUTO_TEST_SUITE_END()

