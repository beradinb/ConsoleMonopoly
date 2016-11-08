#ifndef __MYHEADER
#define __MYHEADER
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <string>
using namespace std;

class CPlayer
{
	private:
		string		mPlayerCounterName; //Storing the current players name
		const int	mPlayerStartingMoney = 1500; //The starting balance for a player
		int			mPlayerCurrentMoney; //Storing the current balance
		int			mPlayerCurrentPosition; //Stroing the current players currernt position

	public:
		CPlayer(string nameCounter); //Constructor for the player class
		void DecreasePlayerMoney(int paymentVal); //Decreasing the players current balance
		void IncreasePlayerMoney(int recieveVal); //Increasing the players current balance
		void SetPosition(int diceVal); //Setting the position of the player (by passing the dice value)
		int GetPosition(); //Getting the current position of the player
		string GetName(); //Getting the name of the current player
		int GetPlayerMoney(); //Getting the current balance of the player

};