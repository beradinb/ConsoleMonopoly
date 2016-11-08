#include "stdafx.h"
#include "CPlayer.h"

CPlayer::CPlayer(string counterName)
{
	mPlayerCounterName = counterName; //Passing the name of the player
	mPlayerCurrentMoney = mPlayerStartingMoney; //Initialising the players starting balance
	mPlayerCurrentPosition = 0; //Initialising the the players starting position

}

void CPlayer::DecreasePlayerMoney(int paymentVal)
{
	mPlayerCurrentMoney -= paymentVal; //Passing a value to decrease the current balance by
}
void CPlayer::IncreasePlayerMoney(int recieveVal)
{
	mPlayerCurrentMoney += recieveVal; //Passing a value to increase the current balance by
}
void CPlayer::SetPosition(int diceVal)
{
	mPlayerCurrentPosition = diceVal; //Passing a value change the players 
}
int CPlayer::GetPosition()
{
	return mPlayerCurrentPosition; //Returning the current players position
}
string CPlayer::GetName()
{
	return mPlayerCounterName; //Returning players name
}
int CPlayer::GetPlayerMoney()
{
	return mPlayerCurrentMoney; //Returning the player current balance
}

