// Monopoloy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSquare.h"
#include "CPlayer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

int Random();
void OpenTextFile(ifstream& textFile, string& path); //OPening the text file function
void CheckPassedGo(int& newPos, int squareMax, CPlayer* playerArr, CSquare* squareArr[]); //Checking if GO has been passed
void SquareTypeCheck(CSquare* squareArr, CPlayer* playerArr[], int i); //Buying and Renting properties function
void GoToJailCheck(CSquare* squareArr[], CPlayer* playerArr, int& newPos); //Go To Jail function
void PenaltyBonusCheck(CSquare* squareArr, CPlayer* playerArr[], int i, int seedValue); //Penalty and Bonus checck and events handle
void MonopolyGetLine(ifstream& textFile, string line, CSquare* squaresArr[]); //Getting the line of the monopoly file


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Welcome to Monopoly" << endl;
	cout << endl;

	const int squareMax = 26; //Number of squares

	const int roundsNum = 20; //Number of rounds
	//File Input
	ifstream monopolyFile; //Storing the Monopoly text file
	ifstream seedFile; //Storing the Seed file 
	string monopolyFileName = "Monopoly.txt"; //Monopoly text file path
	string seedFileName = "seed.txt"; //Seed text file path
	OpenTextFile(monopolyFile, monopolyFileName); //Opening the Monopoly text files 
	OpenTextFile(seedFile, seedFileName); //Opening the Seed text file

	CSquare* monopolySquaresArr[squareMax]; //Squares array
	CPlayer* playerArray[2]; //Creating a player array;
	playerArray[0] = new CPlayer("dog"); //car player
	playerArray[1] = new CPlayer("car"); //dog player

	string line; //Storing the line
	MonopolyGetLine(monopolyFile, line, monopolySquaresArr); //Storing each line in a array

	int seedVal; //Storing the seed value
	string seedLine; //Storing the line
	if (seedFile.is_open())
	{
		getline(seedFile, seedLine); //Getting the line from the file
		istringstream ss(seedLine);
		ss >> seedVal; //Storing the seed value in the seedVal variable
		//cout << "Seed Value: " << seedVal << endl; //Outputting the seed value
	}

	srand(seedVal); //Creating a sequence of numbers
	//ROUNDS FOR LOOP
	for (int i = 0; i < roundsNum; i++)
	{
		cout << "Round: " << i + 1 << endl; //Displaying the round number
		
		//PLAYER FOR LOOP WITHIN A ROUND
		for (int j = 0; j < 2; j++)
		{
			int diceRollVal = Random(); //Getting a random value for the dice for each player
			cout  << playerArray[j]->GetName() << " rolls " << diceRollVal << endl; //Displaying the player name and value of the dice generated
			int currentPosition = playerArray[j]->GetPosition(); // Storing the players current position
			int newPosition = currentPosition + diceRollVal; //Storing the position after the dice value has been added on
			CheckPassedGo(newPosition, squareMax, playerArray[j], monopolySquaresArr); //Checking if GO has been passed
			playerArray[j]->SetPosition(newPosition); //Setting the player position to the new postion
			cout << playerArray[j]->GetName() << " lands on " << monopolySquaresArr[newPosition]->GetSquareName() <<  endl; //Displaying the player name and square name
			PenaltyBonusCheck(monopolySquaresArr[newPosition], playerArray, j, seedVal); //Checking if player has landed on Penalty or bonus
			SquareTypeCheck(monopolySquaresArr[newPosition], playerArray, j); //Buying, renting and handling other squares.
			GoToJailCheck(monopolySquaresArr, playerArray[j], newPosition); //Handling Go To Jail

			cout << playerArray[j]->GetName() << " has \x9C" << playerArray[j]->GetPlayerMoney() << endl; //Displaying the name of the player and their current money balance
		}
		cout << endl;
	}

	system("pause");
	return 0;
}

void OpenTextFile(ifstream& textFile, string& path)
{
	//Opeining a text file
	textFile.open(path);
	if (!textFile)
	{
		//Error message if file not found
		cout << "ERROR: ";
		cout << "Can't open input file\n";
	}
}

void MonopolyGetLine(ifstream& textFile, string line, CSquare* squaresArr[])
{
	//Getting the line of the text file
	if (textFile.is_open()) //checking if its open
	{
		int i = 0; //line counter
		while (!textFile.eof())
		{
			getline(textFile, line);//Getting the line
			squaresArr[i] = new CSquare(line); //Storing each line in the squares array
			++i; //Line counter incremmented
		}
	}
}

void CheckPassedGo(int& newPos, int squareMax, CPlayer* playerArr, CSquare* squareArr[])
{
	//End of the board check
	if (newPos > squareMax - 1)
	{
		newPos = newPos - squareMax; // Changing the position so the player isn't outside the square array
		playerArr->IncreasePlayerMoney(squareArr[newPos]->GetPassGoAmount()); //Increasing the players money for passing GO
		cout << playerArr->GetName() << " has passed GO and collects \x9C" << squareArr[newPos]->GetPassGoAmount() << endl; //Displaying the player name and the amount collected
	}
}

void GoToJailCheck(CSquare* squareArr[], CPlayer* playerArr, int& newPos)
{
	//Checking if the player has landed on Go To Jail
	if (squareArr[newPos]->GetPropertyCode() == 7)
	{
		//Setting the new position to  where the Jail square is
		newPos = 6; //Jail square number
		playerArr->SetPosition(newPos); //Setting player psotion to the Jail square
		cout << playerArr->GetName() << " goes to " << squareArr[newPos]->GetSquareName() << endl; //Outputting player name going to Jail square
		cout << playerArr->GetName() << " pays \x9C" << squareArr[newPos]->GetJailFee() << endl; //Outputting player name and the jail fee paid
		playerArr->DecreasePlayerMoney(squareArr[newPos]->GetJailFee()); //Decrease the players money balance by the jail fee
	}
}

void PenaltyBonusCheck(CSquare* squareArr, CPlayer* playerArr[], int i, int seedValue)
{
	//Checking if the player has landed on Penalty
	if (squareArr->GetPropertyCode() == 5)
	{
		playerArr[i]->DecreasePlayerMoney(squareArr->PenaltyEvent()); //Decreasing the players money balance by the random event
	}
	//Checking if the player has landed on Bonus
	else if (squareArr->GetPropertyCode() == 4)
	{
		playerArr[i]->IncreasePlayerMoney(squareArr->BonusEvent()); //Increasing the players money balance by the random event
	}

}

void SquareTypeCheck(CSquare* squareArr, CPlayer* playerArr[], int i)
{
	///////////HANDLING PROPERTY//////////
	if (squareArr->GetPropertyCode() == 1 && (playerArr[i]->GetPlayerMoney() >= 0 ))
	{
		//Checking if property isn't owned
		if (!squareArr->CheckPropertyOwned()) 
		{
			squareArr->SetPropertyOwner(playerArr[i]->GetName(), true); //Setting the property to owned and assigning the property owners name
			playerArr[i]->DecreasePlayerMoney(squareArr->GetPropertyCost()); //Decreasing the players amount by the property cost
			cout << playerArr[i]->GetName() << " buys " << squareArr->GetSquareName() << " for cost \x9C" << squareArr->GetPropertyCost() << endl; //Displaying the players name, the property bought and the amount paid
		}
		//if the property is owned
		else
		{
			//Making sure player isn't the property owner
			if (playerArr[i]->GetName() != squareArr->GetPropertyOwner())
			{
				playerArr[i]->DecreasePlayerMoney(squareArr->GetPropertyRent()); //Getting property rent and decreasing it from the current balance
				cout << playerArr[i]->GetName() << " pays \x9C" << squareArr->GetPropertyRent() << " rent" << endl; //Dispplaying the player name and the amount of rent paid
				int j = 0;
				bool otherPlayer = false; //Bool for used for other player recieving rent
				while (!otherPlayer)
				{
					//Testing if player name matches with property owner
					if (playerArr[j]->GetName() == squareArr->GetPropertyOwner())
					{
						playerArr[j]->IncreasePlayerMoney(squareArr->GetPropertyRent()); //Increasing the amount by rent they recieve
						//cout << playerArr[j]->GetName() << " recieves <\x9C" << squareArr->GetPropertyRent() << " rent" << endl;
						otherPlayer = true; // Changing the bool for the other player
					}
					j++; //Incremting the counter 
				}
			}
		}

	}
	//////////HANDLING AIRPORTS//////////
	else if (squareArr->GetPropertyCode() == 3 && (playerArr[i]->GetPlayerMoney() >= 0))
	{
		//Checking if aiport isn't owned
		if (!squareArr->CheckPropertyOwned())
		{
			squareArr->SetPropertyOwner(playerArr[i]->GetName(), true); //Setting the airport as owned
			playerArr[i]->DecreasePlayerMoney(squareArr->GetAirportCost()); //Decreasing the players money balance by the airport cost
			cout << playerArr[i]->GetName() << " buys " <<  squareArr->GetSquareName() << "for cost \x9C" << squareArr->GetAirportCost() << endl; //Displaying the players name, the airport bought and the amount paid
		}
		//If the airport is owned
		else
		{
			//Checking the player doesn't own the airport
			if (playerArr[i]->GetName() != squareArr->GetPropertyOwner())
			{
				playerArr[i]->DecreasePlayerMoney(squareArr->GetAirportFee()); //Decreasing the player
				cout << playerArr[i]->GetName() << " pays \x9C" << squareArr->GetAirportFee() << " of goods" << endl; //Displaying the player buying the airport and the cost of buying it
				int j = 0;
				bool otherPlayer = false; //Bool for used for other player recieving rent
				while (!otherPlayer)
				{
					//Testing if player name matches with airport owner
					if (playerArr[j]->GetName() == squareArr->GetPropertyOwner())
					{
						playerArr[j]->IncreasePlayerMoney(squareArr->GetAirportFee()); //Increasing the amount by fee they recieve
						//cout << playerArr[j]->GetName() << " recieves \x9C" << squareArr->GetAirportFee() << " of goods." << endl;
						otherPlayer = true; // Changing the bool for the other player
					}
					j++; //Incremting the counter 
				}
			}
		}
	}
	///////////HANDLING JAIL///////////
	else if (squareArr->GetPropertyCode() == 6)
	{
		cout << playerArr[i]->GetName() << " is just visiting" << endl; //Outputting player is just visting
	}
	//////////HANDLING FREE PARKING//////////
	else if (squareArr->GetPropertyCode() == 8)
	{
		cout << playerArr[i]->GetName() << " is resting" << endl; //Outputting player is resting
	}
}

int Random()
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1);
}



