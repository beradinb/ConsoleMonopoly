#include "stdafx.h"
#include "CSquare.h"

CSquare::CSquare(string line)
{
	//Splitting the line up and putting each string the appropriate class property variable

	istringstream ss(line); //Splitting the string by space
	int counter = 0; //Substring counter

	do
	{
		string sub; 
		ss >> sub; //Putting the broken down string into a new string

		if (counter == 0) //Testing if it's the first value
		{
			mPropertyCode = atoi(sub.c_str()); //Converting the sub string into a int and then storing it in mPropertyCode int variable
		}

		if (mPropertyCode != 7) //Testing if its not Go To Jail
		{
			//Testing which sub string it is
			if (counter == 1) 
			{
				mPropertyName = sub; //Putting the property name sub string into mPropertyName string variable
			}
			if (counter == 2)
			{
				mPropertyName = mPropertyName + " " + sub; //Putting the second part of the name into mPropertyName as well
			}

			if (counter == 3)
			{
				mPropertyCost = atoi(sub.c_str()); //Converting the cost into a int and then storing into mPropertyCost
			}
			if (counter == 4)
			{
				mPropertyRent = atoi(sub.c_str()); //Converting the rent into a int  and then storing it into mPropertyRent
			}
			if (counter == 5)
			{
				mColourGroup = atoi(sub.c_str()); //Converting the colour group into a int and then storing it in mColourGroup
			}
		}
		else
		{
			//Testing which substring it is then putting the three substrings of Go To Jail together
			if (counter == 1)
			{
				mPropertyName = sub;
			}
			if (counter == 2)
			{
				mPropertyName = mPropertyName + " " + sub;
			}
			if (counter == 3)
			{
				mPropertyName = mPropertyName + " " + sub;
			}
		}
		counter++; //Increase sub counter

	} while (ss);

};
string CSquare::GetSquareName()
{
	//Getting square name
	return mPropertyName;
}
void CSquare::SetPropertyOwner(string propertyOwner, bool propertyOwned)
{
	mPropertyOwner = propertyOwner; //Setting the property owner
	mPropertyOwned = propertyOwned; //Setting the bool for property owned
}
bool CSquare::CheckPropertyOwned()
{
	return mPropertyOwned; //Getting the bool to test if property is owned
}
int CSquare::GetPropertyCost()
{
	return mPropertyCost; //Getting the cost of the property
}
int CSquare::GetPropertyRent()
{
	return mPropertyRent; //Getting the rent of the property
}
int CSquare::GetPropertyCode()
{
	return mPropertyCode; //Getting the code of the property
}
string CSquare::GetPropertyOwner()
{
	return mPropertyOwner; //Getting the property owner
}
int CSquare::Random()
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1);
}
int CSquare::PenaltyEvent()
{
	int randomEvent; //storing the random number
	randomEvent = Random();
	randomEvent = randomEvent - 1;
	cout << mEventPenalty[randomEvent] << ". Player loses \x9C" << mCostPenalty[randomEvent] << endl; //Outputs the event and the cost of the event
	return mCostPenalty[randomEvent]; //Returns the cost
}
int CSquare::BonusEvent()
{
	int randomEvent; //storing the random number
	randomEvent = Random();
	randomEvent = randomEvent - 1;
	cout << mEventBonus[randomEvent] << ". Player gains \x9C" << mRewardBonus[randomEvent] << endl; //Outputs the event and the reward of the event
	return mRewardBonus[randomEvent]; //Returns the reward
}
int CSquare::GetAirportCost()
{
	return mAirportBuyCost; //Gets the cost of buying the airport
}
int CSquare::GetAirportFee()
{
	return mAirportFee; //Gets the fee of landing on the airport
}
int CSquare::GetPassGoAmount()
{
	return mPassGo; //Return GO amount
}
int CSquare::GetJailFee()
{
	return mJailFee; //Return the jail fee
}

int CSquare::mCostPenalty[6] = { 20, 50, 100, 150, 200, 300 }; //Penalty cost array
string CSquare::mEventPenalty[6] = { "Pay food bill",
"Pay phone bill",
"Pay heating bill",
"Pay vehicle tax",
"Pay fuel bill",
"Pay windfall tax" }; //Penalty event array
 
int CSquare::mRewardBonus[6] = { 20, 50, 100, 150, 200, 300 }; //Bonus reward array
string CSquare::mEventBonus[6] = { "Find some money",
"Win competition",
"Tax rebate",
"Win lottery",
"Bequest",
"Birthday" }; //Bonus event array
