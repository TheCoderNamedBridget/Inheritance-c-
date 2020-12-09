/*
Bridget Naylor
Date:12/5/2020
Class: CECS 282 Section 04
Lab: 6
Honesty statement:
I certify that this program is my own original work. I did not copy any part of this program from
any other source. I further certify that I typed each and every line of code in this program.
*/
#include <stdio.h>
#include "Player.h"
#include "Card.h"
#include "MegaDeck.h"
#include "WarPile.h"
#include "Deck.h"
#include <vector>
#include <iostream>
using namespace std;

/*
Game Play:
get num player and num decks
divide num cards in all decks among players
each player puts down a cards
highest value card wins

players lose when they have no cards left

if cards are same value then players battle by putting 3 
cards down and comparing the last one if one person has 
a higher value they take the 10 cards if tie then go again
if both or all players run out of cards in the battle then 
the warpile does to the lot and found pile
*/
int main()
{

    
    vector<Player> players;
    MegaDeck bigDeck;
    
    int numDecks;
    int numPlayers;
    bool winner = false;
    
    cout<<"Enter number of decks: ";
    cin>>numDecks;
    
    if ( numDecks > 1 )
    {
        
        //cout<<"seg fault11"<<endl;
        
        //cout<<"seg fault22"<<endl;
        for ( int i = 0; i < numDecks; i ++ )
        {
            //cout<<"seg fault1"<<endl;
            Deck deck = Deck();
            //deck.shuffle( 52, deck.pile );
            bigDeck.add( deck );
        }
        //TODO Figure out why shuffle isn't working
        //bigDeck.shuffle( numDecks );
        //check MegaDeck
        for ( int i = 0; i < numDecks * 52; i ++ )
        {
            bigDeck.megaPile.at(i).showCard();
        }
        //cout<<"seg fault1"<<endl;
    }
    cout<<"Enter number of players: ";
    cin>>numPlayers;
    for ( int i = 0; i < numPlayers; i ++ )
    {
        Player newPlayer = Player();
        players.push_back( newPlayer );
    }
    
    
    //TODO Split up megadeck to give each player cards
    int numCardsPerPlayer = ((numDecks * 52) / numPlayers) - 1;
    cout<<"numCardsPerPlayer "<<numCardsPerPlayer<<endl;
    //cout<<"Enter number of players: ";
    int itr = 0;
    //cout<<"Enter number of players: ";
    int curPlayerIndex = 0;
    
    for ( int i = 0; i < numDecks * 52; i++)
    {
        //cout<<"GHHplayers: "<<players.at( curPlayerIndex ).pile.size()<<" "<<curPlayerIndex<<endl;
    
        if ( itr < numCardsPerPlayer  )
        {
            players.at( curPlayerIndex ).add( bigDeck.Remove() );
            itr ++;
            
        }
        else if ( itr == numCardsPerPlayer )
        {
            
            curPlayerIndex++;
            if ( curPlayerIndex < numPlayers )
            {
                 itr = 0;
                //cout<<"Gplayers: "<<players.at( curPlayerIndex ).pile.size()<<" "<<curPlayerIndex<<endl;
                players.at( curPlayerIndex ).add( bigDeck.Remove() );
            }
        }
    }

    //cout<<"Enter number of players: ";
    WarPile warDeck;
    // //players lose when they have no cards left
    while ( !winner )
    {
        // players each draw card
        bool winnerOfBattle = false;
        while ( !winnerOfBattle )
        {
            for ( int i = 0; i < numPlayers; i++)
            {
                cout<<"FR "<<i<<endl;
                warDeck.add( players.at(i).Remove() ) ;
            }
            // compare cards
            //cout<<<<endl;
            if ( warDeck.compare() != -1 )
            {
                winnerOfBattle = true;
            }
        }
        
        exit(0);
        
        // add battles to all players and wins to other players
        // print out results
        // end over when all players cards =0  or when all but one players cards equal 0
    }

    return 0;
}

