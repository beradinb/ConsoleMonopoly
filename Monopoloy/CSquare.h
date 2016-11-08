#ifndef __MYHEADER
#define __MYHEADER
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

class CSquare
{
	private:
		string	mPropertyName;	//Stores the name of the property of the current square
		int		mPropertyCode;	//Stores the code of the property of the current square
		int		mPropertyCost;	//Stores the cost of the property of the current square
		int		mPropertyRent;	//Stores the rent of the property of the current square
		int		mColourGroup;	//Stores the colour group of the property of the current square
		string	mPropertyOwner;	//Stores the name of the property of the current square

		bool		mPropertyOwned = false; //Bool used to test if the property is owned

		static int mCostPenalty[6];		//Penalty event costs array
		static string mEventPenalty[6]; //Penalty event string array

		static int mRewardBonus[6];		//Bonus event reward array
		static string mEventBonus[6];	//Bonus event string array

		const int mAirportBuyCost = 200;	//Buying the airport cost
		const int mAirportFee = 10;			//Airport fee		 
		const int mPassGo = 200;			//Amount for passing GO
		const int mJailFee = 50;			//Jail Fee

	public:
		CSquare(string line);	//Constructor for Square Class
		string GetSquareName();	//Getting the name of the square function
		void SetPropertyOwner(string player, bool propertyOwned); //Setting the property owner function
		bool CheckPropertyOwned(); //Checking if the property is owned bool function
		int GetPropertyCost();	//Getting the property cost
		int GetPropertyRent();	//Getting the property rent
		int GetPropertyCode();	//Getting the property code
		int GetAirportCost();	//Getting the airport buying cost
		int GetAirportFee();	//Getting the airport paying fee
		int GetPassGoAmount();	//Getting the passing GO amount
		int GetJailFee();		//Getting the jail fee
		string GetPropertyOwner();	//Getting the property owner
		int PenaltyEvent();	//Landing on penalty and getting the fee paid from a random event
		int BonusEvent();	//Landing on bonus and getting the reward collected from a random event
		int Random();

};