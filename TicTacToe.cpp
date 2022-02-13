#include<iostream>
#include<Windows.h>
using namespace std;
//TIC TAC TOE GAME//

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void printTitle();
void newPos(char po[]); // init position array
void pt(const char& a);
void Desktop(char po[], int score[]);
int checkWin(char po[]);
void game(char po[]);


int main() {
	char po[10]; //position
	newPos(po); 
	game(po);
	cout << endl; //the game's already ended at this line
	system("pause");
	return 0;
}

void printTitle() {
	cout << "           ";              
	string a = "TIC TAC TOE";
	for (int i = 0; i < 11; i++) {
		SetConsoleTextAttribute(hConsole, i + 2);
		cout << a[i];
	}
	SetConsoleTextAttribute(hConsole, 15);
	cout << endl;
	return;
}

void pt(const char& a) {
	if (a == 'X') {
		SetConsoleTextAttribute(hConsole, 3);
		cout << a;
		SetConsoleTextAttribute(hConsole, 15);
		return;
	}
	if (a == 'O') {
		SetConsoleTextAttribute(hConsole, 4);
		cout << a;
		SetConsoleTextAttribute(hConsole, 15);
		return;
	}
	cout << a;
	return;
}

void Desktop(char po[], int score[]) {
	printTitle();
	cout << "\nPlayer 1: ("; pt('X'); cout << ")   |     Player 2: ("; pt('O'); cout << ")" << endl;
	cout << "Score: " << score[0] << "        |     Score: " << score[1] << endl << endl;
	cout << "\t     |     |" << endl;
	cout << "\t  "; pt(po[7]); cout << "  |  "; pt(po[8]); cout << "  |  "; pt(po[9]); cout << endl;
	cout << "\t_____|_____|_____" << endl;
	cout << "\t     |     |     " << endl;
	cout << "\t  "; pt(po[4]); cout << "  |  "; pt(po[5]); cout << "  |  "; pt(po[6]); cout << endl;
	cout << "\t_____|_____|_____" << endl;
	cout << "\t     |     |     " << endl;
	cout << "\t  "; pt(po[1]); cout << "  |  "; pt(po[2]); cout << "  |  "; pt(po[3]); cout << endl;
	cout << "\t     |     |" << endl;
	return;
}

void newPos(char po[]) {
	for (int i = 0; i < 10; i++)
		po[i] = '0' + i; // convert int to char
	return;
}

int checkWin(char po[]) {
	if (po[1] == po[2] && po[2] == po[3]) return 1;
	else if (po[4] == po[5] && po[5] == po[6]) return 1;
	else if (po[7] == po[8] && po[8] == po[9]) return 1;
	else if (po[1] == po[4] && po[4] == po[7]) return 1;
	else if (po[2] == po[5] && po[5] == po[8]) return 1;
	else if (po[3] == po[6] && po[6] == po[9]) return 1;
	else if (po[1] == po[5] && po[5] == po[9]) return 1;
	else if (po[3] == po[5] && po[5] == po[7]) return 1;
	// -> found winner

	else if (po[1] != '1' && po[2] != '2' && po[3] != '3'
		&& po[4] != '4' && po[5] != '5' && po[6] != '6'
		&& po[7] != '7' && po[8] != '8' && po[9] != '9')
		return 0; // -> game draw

	else
		return -1; // players are playing 
}

void game(char po[]) {
	int score[2] = { 0, 0 };
	unsigned short move, set = 1;

	for (int i = 2; 1; i++) {
		Desktop(po, score);
		cout << "\nSet: " << set << endl;
		cout << "Enter 0 to stop playing." << endl;
		SetConsoleTextAttribute(hConsole, 3+(i%2));
		cout << "Player " << ((i % 2) + 1);
		SetConsoleTextAttribute(hConsole, 15); 
		cout << ", enter a number: "; 
		//check move

		if ((!(cin >> move)) || ((move < 0 || move > 9 || po[move] == 'X' || po[move] == 'O'))) {
			cout << "\n   - INVALID MOVE!! - " << endl;
			i--;
			cin.clear(); //clear previous input
			cin.ignore(123, '\n'); //discard previous input
			system("pause");
			system("cls");
			continue;
		}

		if (move == 0) { cout << "\n   - GAME OVER! BYE BYE -"; return; }

		if (((i % 2) + 1) == 1)
			po[move] = 'X'; //player 1's move
		else po[move] = 'O'; //player 2's move
		//result
		system("cls");

		switch (checkWin(po)) {
			case 1: {
				Desktop(po, score);
				cout << "\n\t~~ PLAYER " << (i % 2) + 1 << " WIN! ~~\n" << endl;
				score[i % 2]++;
				set++;
				newPos(po);
				system("pause");
				system("cls");
				break;
			}
			case 0: {
				Desktop(po, score);
				cout << "\n\t~~ GAME DRAW! ~~\n" << endl;
				set++;
				newPos(po);
				system("pause");
				system("cls");
				break;
			}
			default: break;
		}
	}
	return;
}