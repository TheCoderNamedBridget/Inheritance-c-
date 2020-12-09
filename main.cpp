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
#include "LostFoundPile.h"
#include "Deck.h"
#include <iomanip>
#include <string>
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
void buildBigDeck( int numDecks, MegaDeck &bigDeck );

void printEndResults ( vector<Player> players );

void playersAddCardWarPile( int &numPlayers, vector<Player> &players, WarPile &warDeck );

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
        buildBigDeck( numDecks, bigDeck );
    }
    
    cout<<"Enter number of players: ";
    cin>>numPlayers;
    for ( int i = 0; i < numPlayers; i ++ )
    {
        Player newPlayer = Player();
        players.push_back( newPlayer );
    }
    
    int numCardsPerPlayer = ((numDecks * 52) / numPlayers) - 1;
    int itr = 0;
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
            playersAddCardWarPile( numPlayers, players, warDeck);
            
            if ( warDeck.warPile.size() == 0 || numPlayers == 0)
            {
                cout<<"done "<<endl;
                
                return 0;
            }
            if ( warDeck.warPile.size() == 1 )
            {
                cout<<"winner found"<<endl;
                
                return 0;
                //declare winner
            }
            
            LostFoundPile bin;
            // compare cards
            int indexOfWinner = warDeck.compare();
            if ( indexOfWinner != -1 )
            {
                // add battles to all players and wins to other players
                for ( int i = 0; i < players.size(); i ++ )
                {
                    if ( i == indexOfWinner )
                    {
                        //cout<<"Player "<<i<<" won"<<endl;
                        players.at(i).numBattlesWon++;
                        for ( int i = 0; i < warDeck.warPile.size() ; i++ )
                        {
                            players.at(i).add( warDeck.Remove() );
                        }
                    }
                    players.at(i).calculateFierceness();
                    players.at(i).numBattlesPlayed++;
                    
                }
                winnerOfBattle = true;
            }
            else if ( indexOfWinner == -1 ) 
            {
                //put warDeck in lost and found pile
                //play another battle
                for ( int i = 0; i < warDeck.warPile.size(); i++ )
                {
                    bin.add( warDeck.Remove() );
                }
            }
            cout<<"warDeck found"<<warDeck.warPile.size()<<endl;
            cout<<"lostf found"<<bin.pile.size()<<endl;
            // print out results
            printEndResults( players );
            
        }
    }

    return 0;
}


void buildBigDeck( int numDecks, MegaDeck &bigDeck )
{
    for ( int i = 0; i < numDecks; i ++ )
    {
        Deck deck = Deck();
        bigDeck.add( deck );
    }
    bigDeck.shuffle( numDecks );
}

void printEndResults ( vector<Player> players )
{
    for ( int i = 0; i < players.size(); i ++ )
    {
        cout<<"Player: "<<i<<" Fierceness = "<<setprecision(3)<<left << setw(5)<<players.at(i).handFierceness
        <<" Cards = "<<players.at(i).pile.size()<<" Battles = "<<
        players.at(i).numBattlesPlayed<<" Won = "<<players.at(i).numBattlesWon<<endl;
    }
}

void playersAddCardWarPile( int &numPlayers, vector<Player> &players, WarPile &warDeck )
{
    for ( int i = 0; i < numPlayers; i++)
    {
        if ( players.at(i).pile.size() != 0 )//player is not out of cards
        {
            cout<<"FR "<<i<<endl;
            warDeck.add( players.at(i).Remove() ) ;
        }
        else
        {
            cout<<"numPlayers-- found"<<endl;
            numPlayers--;
        }
    }
}
