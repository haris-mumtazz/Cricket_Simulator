//#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;
void toss(char* batting);
void DetermineTeam(string teamA[][2][7], string teamB[][2][7]);
void Initial(string teamA[][2][7], string teamB[][2][7], string* currentBatsman, string* currentBowler, char* batting);
void DrawScorecard(string teamA[][2][7], string teamB[][2][7], char* batting, int* overs, string* currentBatsman, string* currentBowler, int tOvers, int* target, char* chase);
void DrawBatting(string team[][2][7], string* currentBatsman);
void DrawTotal(string teamA[][2][7], string teamB[][2][7], char* batting, int* overs, int tOvers, int* target, char* chase);
void NewBatsman(string team[][2][7], int i);
int CalculateTotalScore(string team[][2][7]);
float CalculateTotalOvers(string team[][2][7]);
int CalculateTotalWickets(string team[][2][7]);
void DrawBowling(string team[][2][7], string* currentBowler);
void Gameplay(string teamA[][2][7], string teamB[][2][7], char* batting, int* overs, string* currentBatsman, string* currentBowler, int tOvers, int* target, char* chase);
void BallCalculator(string teamA[][2][7], string teamB[][2][7], char* batting, int* overs, string* currentBatsman, string* currentBowler, int tOvers);
void RunCalculator(string teamBat[][2][7], string teamBowl[][2][7], char* batting, int* overs, string* currentBatsman, string* currentBowler, int tOvers);
void SwapBatsman(string team[][2][7], string* currentBatsman);
void SwapBowler(string team[][2][7], string* currentBowler, int* overs, int bowler, int tOvers);
void OverCalculator(string teamBat[][2][7], string teamBowl[][2][7], char* batting, int* overs, string* currentBatsman, string* currentBowler, int tOvers);
void FallOfWicket(string teamBat[][2][7], int batsman);
void SrCalculator(string teamBat[][2][7], int batsman);
void EconCalculator(string teamBowl[][2][7], int bowler);
float RunRateCalculator(float overs, int runs);
void MatchSummary(string teamA[][2][7], string teamB[][2][7], char* batting);
int HighestRun(string team[][2][7], int num);
int HighestWicket(string team[][2][7], int num);


int main()
{
	srand(time(0));
	string teamA[11][2][7] = {}, teamB[11][2][7] = {};
	string currentBatsman, currentBowler;
	int t, overs, target, choice;
	char batting, chase = 'N';

	DetermineTeam(teamA, teamB);

	ofstream myfile("teama.txt", ios::app);
	if (myfile.is_open())
	{

		for (int i = 0; i < 11; i++)
		{
			myfile << teamA[i];
		}
		for (int i = 0; i < 11; i++)
		{
			myfile << teamB[i];
		}

	}

	myfile.close();
	srand(time(NULL));
	toss(&batting);
	cout << "___________________________" << endl;
	cout << "Enter Number of Overs:";
	cin >> overs;
	cout << "___________________________" << endl;

	int overs2 = overs;
	int tOvers = overs;

	Initial(teamA, teamB, &currentBatsman, &currentBowler, &batting);
	DrawScorecard(teamA, teamB, &batting, &overs, &currentBatsman, &currentBowler, tOvers, &target, &chase);

	cin.get();


	while (overs > 0)
	{
		Gameplay(teamA, teamB, &batting, &overs, &currentBatsman, &currentBowler, tOvers, &target, &chase);
	}

	system("clear");
	cout << "\n\t\t\t End Of First Innings" << endl;
	DrawScorecard(teamA, teamB, &batting, &overs, &currentBatsman, &currentBowler, tOvers, &target, &chase);
	cout << "Press any key to continue: ";
	cin.get();

	chase = 'Y';
	if (batting == 'A') batting = 'B';
	else batting = 'A';

	Initial(teamA, teamB, &currentBatsman, &currentBowler, &batting);
	DrawScorecard(teamA, teamB, &batting, &overs, &currentBatsman, &currentBowler, tOvers, &target, &chase);

	while (overs2 > 0)
	{
		Gameplay(teamA, teamB, &batting, &overs2, &currentBatsman, &currentBowler, tOvers, &target, &chase);
	}
	chase = 'N';

	char ch;
	do
	{
		cout << endl << "Select Option: " << endl;
		cout << "1. Show First Innings Summary" << endl;
		cout << "2. Show Second Innings Summary" << endl;
		cout << "3. Show Match Summary" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:	if (batting == 'A') batting = 'B';
			  else batting = 'A';
			DrawScorecard(teamA, teamB, &batting, &overs, &currentBatsman, &currentBowler, tOvers, &target, &chase);
			if (batting == 'A') batting = 'B';
			else batting = 'A';
			break;

		case 2:	DrawScorecard(teamA, teamB, &batting, &overs, &currentBatsman, &currentBowler, tOvers, &target, &chase);
			break;

		case 3:	MatchSummary(teamA, teamB, &batting);
			break;

		default: cout << "Wrong Choice" << endl;
		}
		cout << "Do you want to end: ";
		cin >> ch;
	} while (ch != 'y');


	cout << "\n\t RESULT " << endl << endl;
	if (CalculateTotalScore(teamB) > CalculateTotalScore(teamA))	cout << "WINNER: TEAM B" << endl;
	else	cout << "WINNER: TEAM A" << endl;

	if (stoi(teamA[HighestWicket(teamA, 1)][1][4]) > stoi(teamB[HighestWicket(teamB, 1)][1][4]))
	{
		cout << "BOWLER OF THE MATCH: " << teamA[HighestWicket(teamA, 1)][1][0] << endl;
	}
	else
	{
		cout << "BOWLER OF THE MATCH: " << teamB[HighestWicket(teamB, 1)][1][0] << endl;
	}

	if (stoi(teamA[HighestRun(teamA, 1)][0][2]) > stoi(teamB[HighestRun(teamB, 1)][0][2]))
	{
		cout << "BATSMAN OF THE MATCH: " << teamA[HighestRun(teamA, 1)][0][0] << endl;
	}
	else
	{
		cout << "BATSMAN OF THE MATCH: " << teamB[HighestRun(teamB, 1)][0][0] << endl;
	}

	return 0;
}


void toss(char* batting)
{

	int t, toss;
	t = 1 + rand() % 100;
	//srand(time(0));
	if (t > 50)
	{
		//srand(time(0));
		cout << "Team A won the toss!!" << endl;
		toss = 1 + rand() % 1000;
		if (toss < 500)
		{
			cout << "Team A Chose to Bowl first." << endl;
			*batting = 'B';
		}
		else
		{
			cout << "Team A Chose to Bat first." << endl;
			*batting = 'A';
		}
	}
	else
	{
		//srand(time(0));
		cout << "Team B won the toss!!" << endl;
		toss = 1 + rand() % 1000;
		if (toss < 500)
		{
			cout << "Team B Chose to Bowl first." << endl;
			*batting = 'A';
		}
		else
		{
			cout << "Team B Chose to Bat first." << endl;
			*batting = 'B';
		}
	}

}


void DetermineTeam(string teamA[][2][7], string teamB[][2][7])
{
	/*
	cout<<"-----------------------------"<<endl;
	cout<<"           TEAM A            "<<endl;
	cout<<"-----------------------------"<<endl;
	for(int i=0;i<11;i++)
	{
		cout<<"Enter Player "<<i+1<<" name: ";
		cin>>teamA[i][0][0];
		teamA[i][1][0]=teamA[i][0][0];
	}

	cout<<"-----------------------------"<<endl;
	cout<<"           TEAM B            "<<endl;
	cout<<"-----------------------------"<<endl;
	for(int i=0;i<11;i++)
	{
		cout<<"Enter Player "<<i+1<<" name: ";
		cin>>teamB[i][0][0];
		teamB[i][1][0]=teamB[i][0][0];
	}
	*/

	char a = 'A', b = 'a';
	for (int i = 0; i < 11; i++)
	{
		teamA[i][0][0] = a + i;
		teamB[i][0][0] = b + i;
		if (i >= 6)
		{
			teamA[10 - i][1][0] = teamA[i][0][0];
			teamB[10 - i][1][0] = teamB[i][0][0];
		}
	}
}

void Initial(string teamA[][2][7], string teamB[][2][7], string* currentBatsman, string* currentBowler, char* batting)
{
	if (*batting == 'A')
	{
		*currentBatsman = teamA[0][0][0];
		NewBatsman(teamA, 0);
		NewBatsman(teamA, 1);
		*currentBowler = teamB[0][1][0];
		for (int j = 0; j < 5; j++)
		{
			for (int i = 1; i < 7; i++)
			{
				teamB[j][1][i] = to_string(0);
			}
		}

	}
	else
	{
		*currentBatsman = teamB[0][0][0];
		NewBatsman(teamB, 0);
		NewBatsman(teamB, 1);
		*currentBowler = teamA[0][1][0];
		for (int j = 0; j < 5; j++)
		{
			for (int i = 1; i < 7; i++)
			{
				teamA[j][1][i] = to_string(0);
			}
		}
	}

	/*for (int j=0; j<5; j++)
	{
		for (int i=1; i<7; i++)
		{
			teamA[j][1][i]=to_string(0);
			teamB[j][1][i]=to_string(0);
		}
	}*/
}

void NewBatsman(string team[][2][7], int i)
{
	team[i][0][1] = "not out";
	team[i][0][2] = to_string(0);
	team[i][0][3] = to_string(0);
	team[i][0][4] = to_string(0);
	team[i][0][5] = to_string(0);
	team[i][0][6] = to_string(0);

}

void DrawScorecard(string teamA[][2][7], string teamB[][2][7], char* batting, int* overs, string* currentBatsman, string* currentBowler, int tOvers, int* target, char* chase)
{
	if (*batting == 'A')
	{
		cout << endl << "TEAM A INNINGS (" << tOvers << " overs maximum)" << endl;
		DrawBatting(teamA, currentBatsman);
		DrawTotal(teamA, teamB, batting, overs, tOvers, target, chase);
		DrawBowling(teamB, currentBowler);
	}
	else
	{
		cout << endl << "TEAM B INNINGS (" << tOvers << " overs maximum)" << endl;
		DrawBatting(teamB, currentBatsman);
		DrawTotal(teamA, teamB, batting, overs, tOvers, target, chase);
		DrawBowling(teamA, currentBowler);
	}
}

void DrawBatting(string team[][2][7], string* currentBatsman)
{
	cout << " " << left << setw(18) << "BATTING " << left << setw(18) << "" << right << setw(5) << "R" << right << setw(5) << "B" << right << setw(5) << "4s" << right << setw(5) << "6s" << right << setw(10) << "SR" << endl;
	for (int i = 0; i < 11; i++)
	{
		if (team[i][0][0] == *currentBatsman) cout << "*";
		else cout << " ";
		cout << setw(18) << left << team[i][0][0] << left << setw(18) << team[i][0][1] << right << setw(5) << team[i][0][2] << right << setw(5) << team[i][0][3] << right << setw(5) << team[i][0][4] << right << setw(5) << team[i][0][5];
		if (team[i][0][6] != "") cout << right << setw(10) << fixed << setprecision(2) << stof(team[i][0][6]) << endl;
		else cout << right << setw(10) << fixed << setprecision(2) << team[i][0][6] << endl;
	}
}

void DrawTotal(string teamA[][2][7], string teamB[][2][7], char* batting, int* overs, int tOvers, int* target, char* chase)
{
	int totalScore, totalWickets;
	float runRate, totalOvers, remOvers, RrunRate;
	double intPart;
	if (*batting == 'A')
	{
		totalScore = CalculateTotalScore(teamA);
		totalOvers = CalculateTotalOvers(teamB);
		totalWickets = CalculateTotalWickets(teamB);
		if (*chase == 'N') *target = totalScore + 1;
		runRate = RunRateCalculator(totalOvers, totalScore);
		cout << endl << " " << left << setw(10) << "TOTAL" << left << fixed << setprecision(1) << totalOvers << " Ov (CRR: " << fixed << setprecision(2) << runRate << ")" << right << setw(5) << totalScore << "/" << totalWickets;
		if (*chase == 'Y')
		{
			cout << "\t TARGET: " << *target << endl << " ";
			if (modf(totalOvers, &intPart) >= 0.1 && modf(totalOvers, &intPart) <= 0.5)	remOvers = tOvers - totalOvers - 0.4;
			else remOvers = tOvers - totalOvers;
			cout << *target - totalScore << " runs are needed to win from " << setprecision(1) << remOvers << " overs. \t";
			RrunRate = RunRateCalculator(remOvers, *target - totalScore);
			cout << "(RRR: " << setprecision(2) << RrunRate << ")" << endl;
			if (totalScore >= *target) *overs = 0;
		}
		else cout << endl;

	}
	else
	{
		totalScore = CalculateTotalScore(teamB);
		totalOvers = CalculateTotalOvers(teamA);
		totalWickets = CalculateTotalWickets(teamA);
		if (*chase == 'N') *target = totalScore + 1;
		runRate = RunRateCalculator(totalOvers, totalScore);
		cout << endl << " " << left << setw(10) << "TOTAL" << left << fixed << setprecision(1) << totalOvers << " Ov (CRR: " << fixed << setprecision(2) << runRate << ")" << right << setw(5) << totalScore << "/" << totalWickets;
		if (*chase == 'Y')
		{
			cout << "\t TARGET: " << *target << endl << " ";
			if (modf(totalOvers, &intPart) >= 0.1 && modf(totalOvers, &intPart) <= 0.5)	remOvers = tOvers - totalOvers - 0.4;
			else remOvers = tOvers - totalOvers;
			cout << *target - totalScore << " runs are needed to win from " << setprecision(1) << remOvers << " overs. \t";
			RrunRate = RunRateCalculator(remOvers, *target - totalScore);
			cout << "(RRR: " << setprecision(2) << RrunRate << ")" << endl;
			if (totalScore >= *target) *overs = 0;
		}
		else cout << endl;

	}
}


int CalculateTotalScore(string team[][2][7])
{
	int sum = 0;
	for (int i = 0; i < 11; ++i)
	{
		if (team[i][0][2] != "")sum = sum + stoi(team[i][0][2]);
	}
	return sum;
}

float CalculateTotalOvers(string team[][2][7])
{
	float sum = 0;
	for (int i = 0; i < 5; ++i)
	{
		sum = sum + stof(team[i][1][1]);
	}
	return sum;
}

int CalculateTotalWickets(string team[][2][7])
{
	int sum = 0;
	for (int i = 0; i < 5; ++i)
	{
		sum = sum + stoi(team[i][1][4]);
	}
	return sum;
}


void DrawBowling(string team[][2][7], string* currentBowler)
{
	cout << endl << " " << left << setw(20) << "BOWLING" << right << setw(5) << "O" << right << setw(5) << "M" << right << setw(5) << "R" << right << setw(5) << "W" << right << setw(10) << "ECON" << endl;
	for (int i = 0; i < 5; i++)
	{
		if (team[i][1][0] == *currentBowler) cout << "*";
		else cout << " ";
		cout << setw(20) << left << team[i][1][0] << setw(5) << right << fixed << setprecision(1) << stof(team[i][1][1]) << right << setw(5) << team[i][1][2] << right << setw(5) << team[i][1][3] << right << setw(5) << team[i][1][4] << right << setw(10) << fixed << setprecision(2) << stof(team[i][1][5]) << endl;
	}
}


void Gameplay(string teamA[][2][7], string teamB[][2][7], char* batting, int* overs, string* currentBatsman, string* currentBowler, int tOvers, int* target, char* chase)
{
	//srand(time(0));
	char choice[2];
	int ch;

	cout << endl << "Press ENTER to bowl a ball or press S to simulate the match: ";

	cin.getline(choice, 2);
	//getline(cin> choic);

	if (choice[0] == 'S' || choice[0] == 's')
		//if (cin.get()=="s" || cin.get()=="S")
	{
		system("clear");
		cout << "Enter the desired over you want the match to be simulated: ";
		cin >> ch;
		while (*overs > (tOvers - ch))
		{
			system("clear");
			BallCalculator(teamA, teamB, batting, overs, currentBatsman, currentBowler, tOvers);
			DrawScorecard(teamA, teamB, batting, overs, currentBatsman, currentBowler, tOvers, target, chase);
		}
	}
	else
	{
		system("clear");
		BallCalculator(teamA, teamB, batting, overs, currentBatsman, currentBowler, tOvers);
		DrawScorecard(teamA, teamB, batting, overs, currentBatsman, currentBowler, tOvers, target, chase);
	}
}


void BallCalculator(string teamA[][2][7], string teamB[][2][7], char* batting, int* overs, string* currentBatsman, string* currentBowler, int tOvers)
{
	//srand(time(0));
	int random;
	if (*batting == 'A')
	{
		RunCalculator(teamA, teamB, batting, overs, currentBatsman, currentBowler, tOvers);
		OverCalculator(teamA, teamB, batting, overs, currentBatsman, currentBowler, tOvers);
	}
	else
	{
		RunCalculator(teamB, teamA, batting, overs, currentBatsman, currentBowler, tOvers);
		OverCalculator(teamB, teamA, batting, overs, currentBatsman, currentBowler, tOvers);
	}

}

void RunCalculator(string teamBat[][2][7], string teamBowl[][2][7], char* batting, int* overs, string* currentBatsman, string* currentBowler, int tOvers)
{
	//srand(time(0));
	int batsman, bowler, random, runs;
	for (int i = 0; i < 11; ++i)
	{
		if (teamBat[i][0][0] == *currentBatsman) batsman = i;
		if (teamBowl[i][1][0] == *currentBowler) bowler = i;
	}

	if (batsman <= 5)
	{
		random = 1 + rand() % 70;
		switch (random)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9: runs = 0;
			break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18: runs = 1;
			break;
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27: runs = 2;
			break;
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36: runs = 3;
			break;
		case 37:
		case 38:
		case 39:
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
		case 45: runs = 4;
			break;
		case 46:
		case 47:
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54: runs = 5;
			break;
		case 55:
		case 56:
		case 57:
		case 58:
		case 59:
		case 60:
		case 61:
		case 62:
		case 63: runs = 6;
			break;
		case 64:
		case 65:
		case 66:
		case 67:
		case 68:
		case 69:
		case 70: runs = -1;
			break;
		}
	}
	else
	{
		random = 1 + rand() % 70;
		switch (random)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5: runs = 0;
			break;
		case 6:
		case 7:
		case 8:
		case 9:
		case 10: runs = 1;
			break;
		case 11:
		case 12:
		case 13:
		case 14:
		case 15: runs = 2;
			break;
		case 16:
		case 17:
		case 18:
		case 19:
		case 20: runs = 3;
			break;
		case 21:
		case 22:
		case 23:
		case 24:
		case 25: runs = 4;
			break;
		case 26:
		case 27:
		case 28:
		case 29:
		case 30: runs = 5;
			break;
		case 31:
		case 32:
		case 33:
		case 34:
		case 35: runs = 6;
			break;
		case 36:
		case 37:
		case 38:
		case 39:
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
		case 58:
		case 59:
		case 60:
		case 61:
		case 62:
		case 63:
		case 64:
		case 65:
		case 66:
		case 67:
		case 68:
		case 69:
		case 70: runs = -1;
			break;
		}
	}
	int i = 0;
	switch (runs)
	{
	case -1:	teamBat[batsman][0][1] = "b " + *currentBowler;
		teamBat[batsman][0][3] = to_string(stoi(teamBat[batsman][0][3]) + 1);
		teamBowl[bowler][1][4] = to_string(stoi(teamBowl[bowler][1][4]) + 1);
		SrCalculator(teamBat, batsman);
		FallOfWicket(teamBat, batsman);
		if (CalculateTotalWickets(teamBowl) == 10) *overs = 0;
		else
		{
			do
			{
				++i;
				*currentBatsman = teamBat[batsman + i][0][0];
			} while (teamBat[batsman + i][0][1] != "");
			NewBatsman(teamBat, batsman + i);
		}
		break;
	case 0:		teamBat[batsman][0][3] = to_string(stoi(teamBat[batsman][0][3]) + 1);
		break;
	case 1:		teamBat[batsman][0][2] = to_string(stoi(teamBat[batsman][0][2]) + 1);
		teamBat[batsman][0][3] = to_string(stoi(teamBat[batsman][0][3]) + 1);
		teamBowl[bowler][1][3] = to_string(stoi(teamBowl[bowler][1][3]) + 1);
		SwapBatsman(teamBat, currentBatsman);
		break;
	case 2:		teamBat[batsman][0][2] = to_string(stoi(teamBat[batsman][0][2]) + 2);
		teamBat[batsman][0][3] = to_string(stoi(teamBat[batsman][0][3]) + 1);
		teamBowl[bowler][1][3] = to_string(stoi(teamBowl[bowler][1][3]) + 2);
		break;
	case 3:		teamBat[batsman][0][2] = to_string(stoi(teamBat[batsman][0][2]) + 3);
		teamBat[batsman][0][3] = to_string(stoi(teamBat[batsman][0][3]) + 1);
		teamBowl[bowler][1][3] = to_string(stoi(teamBowl[bowler][1][3]) + 3);
		SwapBatsman(teamBat, currentBatsman);
		break;
	case 4:		teamBat[batsman][0][2] = to_string(stoi(teamBat[batsman][0][2]) + 4);
		teamBat[batsman][0][3] = to_string(stoi(teamBat[batsman][0][3]) + 1);
		teamBat[batsman][0][4] = to_string(stoi(teamBat[batsman][0][4]) + 1);
		teamBowl[bowler][1][3] = to_string(stoi(teamBowl[bowler][1][3]) + 4);
		break;
	case 5: 	teamBat[batsman][0][2] = to_string(stoi(teamBat[batsman][0][2]) + 5);
		teamBat[batsman][0][3] = to_string(stoi(teamBat[batsman][0][3]) + 1);
		teamBowl[bowler][1][3] = to_string(stoi(teamBowl[bowler][1][3]) + 5);
		SwapBatsman(teamBat, currentBatsman);
		break;
	case 6:		teamBat[batsman][0][2] = to_string(stoi(teamBat[batsman][0][2]) + 6);
		teamBat[batsman][0][3] = to_string(stoi(teamBat[batsman][0][3]) + 1);
		teamBat[batsman][0][5] = to_string(stoi(teamBat[batsman][0][5]) + 1);
		teamBowl[bowler][1][3] = to_string(stoi(teamBowl[bowler][1][3]) + 6);
		break;
	}
	SrCalculator(teamBat, batsman);

}

void SrCalculator(string teamBat[][2][7], int batsman)
{
	teamBat[batsman][0][6] = to_string((stof(teamBat[batsman][0][2]) / stof(teamBat[batsman][0][3])) * 100);
}

void FallOfWicket(string teamBat[][2][7], int batsman)
{
	system("clear");
	string ran;
	string* wicket;
	wicket = new string[7];
	for (int i = 0; i < 7; ++i)
	{
		wicket[i] = teamBat[batsman][0][i];
	}
	cout << "Fall of Wicket";
	cout << "\n  " << setw(15) << left << wicket[0] << left << setw(18) << wicket[1] << setw(5) << wicket[2];
	cout << right << setw(5) << wicket[3] << right << setw(5) << wicket[4] << right << setw(5) << wicket[5];
	cout << right << setw(10) << fixed << setprecision(2) << stof(wicket[6]) << endl;
	cout << endl << "Press any key to continue";
	cin.get();
	delete[] wicket;

}


void SwapBatsman(string team[][2][7], string* currentBatsman)
{
	for (int i = 0; i < 11; i++)
	{
		if ((team[i][0][0] != *currentBatsman) && (team[i][0][1] == "not out"))
		{
			*currentBatsman = team[i][0][0];
			break;
		}
	}
}

void SwapBowler(string team[][2][7], string* currentBowler, int* overs, int bowler, int tOvers)
{
	int random;
	float limit = tOvers / 5.0;

	if (*overs > 0)
	{

		do
		{
			random = 0 + rand() % 5;
			*currentBowler = team[random][1][0];
		} while ((stof(team[random][1][1]) >= limit) || (random == bowler));
	}
	/*if (bowler==4) *currentBowler=team[0][1][0];
	else	*currentBowler=team[bowler+1][1][0];*/
}

void OverCalculator(string teamBat[][2][7], string teamBowl[][2][7], char* batting, int* overs, string* currentBatsman, string* currentBowler, int tOvers)
{
	int bowler;
	float x, y;
	double intPart;
	for (int i = 0; i < 5; ++i)
	{
		if (teamBowl[i][1][0] == *currentBowler) bowler = i;
	}
	if (modf(stof(teamBowl[bowler][1][1]), &intPart) < 0.5)
	{
		teamBowl[bowler][1][1] = to_string(stof(teamBowl[bowler][1][1]) + 0.1);
	}
	else
	{
		teamBowl[bowler][1][1] = to_string(stof(teamBowl[bowler][1][1]) + 0.5);
		*overs -= 1;
		SwapBowler(teamBowl, currentBowler, overs, bowler, tOvers);
		SwapBatsman(teamBat, currentBatsman);

	}
	//EconCalculator(teamBowl, bowler);
	teamBowl[bowler][1][5] = to_string(RunRateCalculator(stof(teamBowl[bowler][1][1]), stoi(teamBowl[bowler][1][3])));
}

/*
void EconCalculator(string teamBowl[][2][7], int bowler)
{
	double intPart;
	if (modf(stof(teamBowl[bowler][1][1]), &intPart) >= 0.1 && modf(stof(teamBowl[bowler][1][1]), &intPart) <= 0.5)	teamBowl[bowler][1][5]=to_string(stof(teamBowl[bowler][1][3])/((stof(teamBowl[bowler][1][1]))*(10.0/6.0)));
	else teamBowl[bowler][1][5]=to_string(stof(teamBowl[bowler][1][3])/stof(teamBowl[bowler][1][1]));

}
*/

float RunRateCalculator(float overs, int runs)
{
	float RunRate;
	double intPart;
	int overWholeNum = overs;
	if (modf(overs, &intPart) >= 0.1 && modf(overs, &intPart) <= 0.5) RunRate = runs / (overWholeNum + (modf(overs, &intPart) * (10.0 / 6.0)));
	else RunRate = runs / overs;
	return RunRate;
}


void MatchSummary(string teamA[][2][7], string teamB[][2][7], char* batting)
{
	cout << "\t\t\t Match Summary " << endl << endl;

	if (*batting == 'B')
	{
		cout << "TEAM A \t\t\t" << setprecision(1) << CalculateTotalOvers(teamB) << " OVERS\t" << CalculateTotalScore(teamA) << "/" << CalculateTotalWickets(teamB) << endl;
		cout << teamA[HighestRun(teamA, 1)][0][0] << "\t" << teamA[HighestRun(teamA, 1)][0][2] << " " << teamA[HighestRun(teamA, 1)][0][3] << "\t\t";
		cout << teamB[HighestWicket(teamB, 1)][1][0] << "\t" << teamB[HighestWicket(teamB, 1)][1][4] << "-" << teamB[HighestWicket(teamB, 1)][1][3] << endl;
		cout << teamA[HighestRun(teamA, 2)][0][0] << "\t" << teamA[HighestRun(teamA, 2)][0][2] << " " << teamA[HighestRun(teamA, 2)][0][3] << "\t\t";
		cout << teamB[HighestWicket(teamB, 2)][1][0] << "\t" << teamB[HighestWicket(teamB, 2)][1][4] << "-" << teamB[HighestWicket(teamB, 2)][1][3] << endl;
		cout << teamA[HighestRun(teamA, 3)][0][0] << "\t" << teamA[HighestRun(teamA, 3)][0][2] << " " << teamA[HighestRun(teamA, 3)][0][3] << "\t\t";
		cout << teamB[HighestWicket(teamB, 3)][1][0] << "\t" << teamB[HighestWicket(teamB, 3)][1][4] << "-" << teamB[HighestWicket(teamB, 3)][1][3] << endl;
		cout << endl;

		cout << "TEAM B \t\t\t" << setprecision(1) << CalculateTotalOvers(teamA) << " OVERS\t" << CalculateTotalScore(teamB) << "/" << CalculateTotalWickets(teamA) << endl;
		cout << teamB[HighestRun(teamB, 1)][0][0] << "\t" << teamB[HighestRun(teamB, 1)][0][2] << " " << teamB[HighestRun(teamB, 1)][0][3] << "\t\t";
		cout << teamA[HighestWicket(teamA, 1)][1][0] << "\t" << teamA[HighestWicket(teamA, 1)][1][4] << "-" << teamA[HighestWicket(teamA, 1)][1][3] << endl;
		cout << teamB[HighestRun(teamB, 2)][0][0] << "\t" << teamB[HighestRun(teamB, 2)][0][2] << " " << teamB[HighestRun(teamB, 2)][0][3] << "\t\t";
		cout << teamA[HighestWicket(teamA, 2)][1][0] << "\t" << teamA[HighestWicket(teamA, 2)][1][4] << "-" << teamA[HighestWicket(teamA, 2)][1][3] << endl;
		cout << teamB[HighestRun(teamB, 3)][0][0] << "\t" << teamB[HighestRun(teamB, 3)][0][2] << " " << teamB[HighestRun(teamB, 3)][0][3] << "\t\t";
		cout << teamA[HighestWicket(teamA, 3)][1][0] << "\t" << teamA[HighestWicket(teamA, 3)][1][4] << "-" << teamA[HighestWicket(teamA, 3)][1][3] << endl;
		cout << endl;
	}
	else
	{
		cout << "TEAM B \t\t\t" << setprecision(1) << CalculateTotalOvers(teamA) << " OVERS\t" << CalculateTotalScore(teamB) << "/" << CalculateTotalWickets(teamA) << endl;
		cout << teamB[HighestRun(teamB, 1)][0][0] << "\t" << teamB[HighestRun(teamB, 1)][0][2] << " " << teamB[HighestRun(teamB, 1)][0][3] << "\t\t";
		cout << teamA[HighestWicket(teamA, 1)][1][0] << "\t" << teamA[HighestWicket(teamA, 1)][1][4] << "-" << teamA[HighestWicket(teamA, 1)][1][3] << endl;
		cout << teamB[HighestRun(teamB, 2)][0][0] << "\t" << teamB[HighestRun(teamB, 2)][0][2] << " " << teamB[HighestRun(teamB, 2)][0][3] << "\t\t";
		cout << teamA[HighestWicket(teamA, 2)][1][0] << "\t" << teamA[HighestWicket(teamA, 2)][1][4] << "-" << teamA[HighestWicket(teamA, 2)][1][3] << endl;
		cout << teamB[HighestRun(teamB, 3)][0][0] << "\t" << teamB[HighestRun(teamB, 3)][0][2] << " " << teamB[HighestRun(teamB, 3)][0][3] << "\t\t";
		cout << teamA[HighestWicket(teamA, 3)][1][0] << "\t" << teamA[HighestWicket(teamA, 3)][1][4] << "-" << teamA[HighestWicket(teamA, 3)][1][3] << endl;
		cout << endl;

		cout << "TEAM A \t\t\t" << setprecision(1) << CalculateTotalOvers(teamB) << " OVERS\t" << CalculateTotalScore(teamA) << "/" << CalculateTotalWickets(teamB) << endl;
		cout << teamA[HighestRun(teamA, 1)][0][0] << "\t" << teamA[HighestRun(teamA, 1)][0][2] << " " << teamA[HighestRun(teamA, 1)][0][3] << "\t\t";
		cout << teamB[HighestWicket(teamB, 1)][1][0] << "\t" << teamB[HighestWicket(teamB, 1)][1][4] << "-" << teamB[HighestWicket(teamB, 1)][1][3] << endl;
		cout << teamA[HighestRun(teamA, 2)][0][0] << "\t" << teamA[HighestRun(teamA, 2)][0][2] << " " << teamA[HighestRun(teamA, 2)][0][3] << "\t\t";
		cout << teamB[HighestWicket(teamB, 2)][1][0] << "\t" << teamB[HighestWicket(teamB, 2)][1][4] << "-" << teamB[HighestWicket(teamB, 2)][1][3] << endl;
		cout << teamA[HighestRun(teamA, 3)][0][0] << "\t" << teamA[HighestRun(teamA, 3)][0][2] << " " << teamA[HighestRun(teamA, 3)][0][3] << "\t\t";
		cout << teamB[HighestWicket(teamB, 3)][1][0] << "\t" << teamB[HighestWicket(teamB, 3)][1][4] << "-" << teamB[HighestWicket(teamB, 3)][1][3] << endl;
		cout << endl;
	}
	if (CalculateTotalScore(teamB) > CalculateTotalScore(teamA))
	{
		cout << "TEAM B WON THE MATCH" << endl;
	}
	else
	{
		cout << "TEAM A WON THE MATCH" << endl;
	}
}


int HighestRun(string team[][2][7], int num)
{
	int highest1 = -1, highest1index=0, highest2 = -1, highest2index, highest3 = -1, highest3index;
	for (int i = 0; i < 11; ++i)
	{
		if (team[i][0][2] != "")
		{
			if (stoi(team[i][0][2]) > highest1)
			{
				highest3 = highest2;
				highest3index = highest2index;
				highest2 = highest1;
				highest2index = highest1index;
				highest1 = stoi(team[i][0][2]);
				highest1index = i;
			}
			else if (stoi(team[i][0][2]) > highest2)
			{
				highest3 = highest2;
				highest3index = highest2index;
				highest2 = stoi(team[i][0][2]);
				highest2index = i;
			}
			else if (stoi(team[i][0][2]) > highest3)
			{
				highest3 = stoi(team[i][0][2]);
				highest3index = i;
			}
		}
	}

	if (num == 1)
	{
		return highest1index;
	}
	if (num == 2)
	{
		return highest2index;
	}
	if (num == 3)
	{
		return highest3index;
	}
	return 0;
}

int HighestWicket(string team[][2][7], int num)
{
	int highest1 = -1, highest1index=0, highest2 = -1, highest2index, highest3 = -1, highest3index;
	for (int i = 0; i < 5; ++i)
	{
		if (team[i][1][4] != "")
		{
			if (stoi(team[i][1][4]) > highest1)
			{
				highest3 = highest2;
				highest3index = highest2index;
				highest2 = highest1;
				highest2index = highest1index;
				highest1 = stoi(team[i][1][4]);
				highest1index = i;
			}
			else if (stoi(team[i][1][4]) > highest2)
			{
				highest3 = highest2;
				highest3index = highest2index;
				highest2 = stoi(team[i][1][4]);
				highest2index = i;
			}
			else if (stoi(team[i][1][4]) > highest3)
			{
				highest3 = stoi(team[i][1][4]);
				highest3index = i;
			}
		}
	}

	if (num == 1)
	{
		return highest1index;
	}
	if (num == 2)
	{
		return highest2index;
	}
	if (num == 3)
	{
		return highest3index;
	}
	return 0;
}




