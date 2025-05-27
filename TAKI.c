// Name - Tomer Simantov
// ID - 206841033
// Project TAKI!

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MAX_NAME 21 // max tabs in name.
#define MAX_KIND_CARDES_LENGTH  5 // max tabs in the name of the card's kind.
#define NUM_OF_FIRST_CARDS 4 // first number of cards that each player get in the first round.
#define NUM_OF_CARDS 14 // total 14 cards in the game.
#define NUM_PLUS 10 // number represent plus.
#define NUM_STOP 11 // number represent stop.
#define NUM_SWITCH 12 // number represent switch
#define NUM_TAKI 13 // number represent taki.
#define NUM_COLOR 14 //  number represent switch.
#define NUM_YELLOW 1 //  number represent yellow color.
#define NUM_RED 2 //  number represent red color.
#define NUM_BLUE 3 //  number represent blue color.
#define NUM_GREEN 4 //  number represent green color.
#define NUM_OF_WINNER_CARD 0 // the winner has 0 cards.
#define NO_COLOR 0 // the card color has no color when the player first get it.
#define TAKE_FROM_DECK 0 // the number of option that the player choose when he want to take from the deck.
#define FINISH_TURN_IN_TAKI 0 // the number the player choose that says he want to finish the taki action.
//kind//1-9 numbers ----- 10 plus ----- 11 stop ------ 12 switch directions ------- 13 taki -------- 14 switch color.
// color//1 yellow --- 2 red ---- 3 blue ----- 4 green.


struct statistic 
{
	int kind, count;
};
typedef struct statistic Statistic;

struct cards {
	int Kind;
	int Color;
};
typedef struct cards Cards;


struct player {
	char Name[MAX_NAME];
	Cards* CardesOfPlayer;
	 int NumOfCards;
	 int SizeOfArrCards; 
};
typedef struct player Player;



void Welcome(); // welcome function.
int AskForNumOfPlayers(); // function that ask for number fo players.
Player* GetArrOfPlayers(int numofplayers); // function that create dynamic arr of players.
void ValidateMalloc(Player* PlayerArr);
void AskForName(Player* arrplayers, int numofplayers); // function that ask for name for each player and put the names in the players arr.
Cards* GetArrOfCards(int NumOfCardes); // function that create arr for each player in the player's arr.
void FourCardsForEach(Player* arrplayers, int numofplayers); // function that gives 4 cardes to each player at the begining of the game.
Cards FirstCardOnTop(); // function that put the first card in the begining of the game 
bool CheckWinner(Player* arrplayers, int numofplayers , Player* winner); // function that check the winner.
void PrintCards(Player* player); // this function print the cards of the player.
void PrintregularCard(Cards Card); // this function print a regular card
void PrintSpecialCard(Cards Card);// this function print pecial card.
void Game(Player* arrplayers, int numofplayers , Player* winner , Statistic* statisticarr); // this function is the function of the game it self
int TakeOrPut(int numofcards); // this function is asking the player if he want to tkae a card from the deck or trow 1 of his card to the middle.
void AddCardToPlayer(Player p); // this function add card to the arr of cards of the player.
Cards GetOneCard(); // this function  get one card randomly.
void ValidateCardsMalloc(Cards* cards); // this function  check if the malloc succeed
void Round(Player* p, Cards* CardonTop , int* i , int numofplayers , Player* arrplayers, Statistic* statisticarr);// this function id running a player round.
void RemoveCardFromPlayer(Player* p, int choise); // this function remove the choosen card from the player arr.
void IsTaki(Player* p, Cards* cardOnTop); // this function is preforming the taki action
void IsStop(Player* p, int* i , int numofplayers);// this function is preforming the stop action
void IsPlus(Player* p, Cards* cardOnTop, Statistic* statisticarr);// this function is preforming the plus action
void IsColor(Player* p, Cards* cardOnTop);// this function is preforming the color action
void IsSwitchDirections(Player* p, int* i , int numofplayers);// this function is preforming the switch action
void CopyArr(Player* p, Player* p1, int numofplayers); // this function copy arr to another.
void StatisticCard(int* statistic , Player* p); // this function is count for each kind of card how many time he was taken from the deck.
void StatInitArr(int numofcards, Statistic* statisticarr); // this function initiate the count of each card in the statistic arr.
void MergeSortStatistic(Statistic* statisticarr, int numofcards); // this function is sorting the arr in order of the size of the count.
void merge(Statistic* s1, int size1, Statistic* s2, int size2, Statistic* res); // this function is merging.
void copyStatisticArr(Statistic* s1, Statistic* s2, int size); // this function is copy arr to another.
void printMergeSortStatistic(Statistic* statisticarr);// this function is printing the result of the statistic.




void main() {
	int NumOfPlayers, i, j;
	Player* arrPlayers;
	Player Winner;
	Statistic* StatisticOfGame = (Statistic*)malloc(NUM_OF_CARDS * sizeof(Statistic));
	srand(time(NULL));
	Welcome();
	NumOfPlayers = AskForNumOfPlayers(); 
	StatInitArr(NUM_OF_CARDS, StatisticOfGame); // מאפס מערך סטטיסטיקה
	arrPlayers = GetArrOfPlayers(NumOfPlayers);
	AskForName(arrPlayers, NumOfPlayers);
	FourCardsForEach(arrPlayers, NumOfPlayers);
	Game(arrPlayers, NumOfPlayers, &Winner , StatisticOfGame);
	printf("\nthe winner is... %s! Congratulations!\n", Winner.Name);
	MergeSortStatistic(StatisticOfGame, NUM_OF_CARDS);
	printMergeSortStatistic(StatisticOfGame);



	
	

	}
	


void Welcome(){
	printf("************ Welcome to TAKI game !!! ***********\n");
} 
int AskForNumOfPlayers() {
	int Num;
	printf("Please enter the number of players:\n");
	scanf("%d", &Num);
	return Num;
}
Player* GetArrOfPlayers(int numofplayers) {
	Player* arr = NULL;
	arr = (Player*)malloc(numofplayers * sizeof(Player));
	ValidateMalloc(arr);
		return arr;

}
void ValidateMalloc(Player* PlayerArr) // פונקציה הבודקת האם ההקצאה למערך השחקנים יצא תקין
{

	if (PlayerArr == NULL)
	{
		printf("ERROR! Memory allocation failed \n");
		exit(1);
	}
}
void AskForName(Player* arrplayers , int numofplayers) {
	int i;
	for (i = 0; i < numofplayers; i++) {
		printf("Please enter the first name of player #%d:\n", i + 1);
		scanf("%s", arrplayers[i].Name);
	}
}
Cards* GetArrOfCards(int NumOfCardes) {
	Cards* arr = NULL;
	arr = (Cards*)malloc(NumOfCardes * sizeof(Cards));
	ValidateCardsMalloc(arr);
		return arr;
}
void ValidateCardsMalloc(Cards* cards)
{

	if (cards == NULL)
	{
		printf("ERROR! Memory allocation failed \n");
		exit(1);
	}
} // פונקציה הבודקת האם ההקצאה הצליחה
void FourCardsForEach(Player* arrplayers , int numofplayers) {
	int i, j;
	for (i = 0; i < numofplayers; i++) {
		arrplayers[i].CardesOfPlayer = GetArrOfCards(NUM_OF_FIRST_CARDS);
		for (j = 0; j < NUM_OF_FIRST_CARDS; j++) {
			arrplayers[i].CardesOfPlayer[j].Kind = 1 + rand() % 14;
			arrplayers[i].CardesOfPlayer[j].Color = 1 + rand() % 4;
			if (arrplayers[i].CardesOfPlayer[j].Kind == 14) {
				arrplayers[i].CardesOfPlayer[j].Color = 0; // אם יצא משנה צבע , הערך בצבע יצא 0 מה שאומר שצריך להדפיס רווח כלומר אין צבע
			}
		}
		arrplayers[i].NumOfCards = NUM_OF_FIRST_CARDS;
		arrplayers[i].SizeOfArrCards = NUM_OF_FIRST_CARDS;

	}
}
Cards FirstCardOnTop() {
	Cards first;
	srand(time(NULL));
	first.Kind = 1 + rand() % 9;
	first.Color = 1 + rand() % 4;
	return first;

}
void PrintCardOnTop(Cards cardontop) {
	printf("Upper card:\n");
	if (cardontop.Kind < NUM_PLUS) // plus is the minimal special card . below him its regular card.
		PrintregularCard(cardontop);
	else
		PrintSpecialCard(cardontop);
}
bool CheckWinner(Player* arrplayers , int numofplayers ,Player* winner ) {
	int i;
	for (i = 0; i < numofplayers; i++) {
		if (arrplayers[i].NumOfCards == NUM_OF_WINNER_CARD) {
			*winner = arrplayers[i];
			return true;
		}
	}
	return false;
}
void PrintCards(Player* player) {
	int i;
	for (i = 0; i < player->NumOfCards; i++) {
		printf("Card #%d:\n", i+1);
		if (player->CardesOfPlayer[i].Kind < NUM_PLUS) // plus is the minimal special card . below him its regular card.
			PrintregularCard(player->CardesOfPlayer[i]);
		else
			PrintSpecialCard(player->CardesOfPlayer[i]);
	}
}
void PrintregularCard(Cards Card) {
	int  j;
	for (j = 1; j <= 6; j++) {
		if (j == 1 || j == 6) {
			printf("*********\n");
		}
		else if (j == 3)
			printf("*   %d   *\n", Card.Kind);
		else if (j == 4) {
			switch (Card.Color)
			{
			case NUM_YELLOW:
				printf("*   Y   *\n");
				break;
			case NUM_RED:
				printf("*   R   *\n");
				break;
			case NUM_BLUE:
				printf("*   B   *\n");
				break;
			case NUM_GREEN:
				printf("*   G   *\n");
				break;
			}
		}
		else
			printf("*       *\n");
	}
}
void PrintSpecialCard(Cards Card) {
	int  j;
	for (j = 1; j <= 6; j++) {
		if (j == 1 || j == 6) {
			printf("*********\n");
		}
		else if (j == 3) {
			switch (Card.Kind)
			{
			case NUM_PLUS:
				printf("*   +   *\n");
				break;
			case NUM_STOP:
				printf("*  STOP *\n");
				break;
			case NUM_SWITCH:
				printf("*  <->  *\n");
				break;
			case NUM_TAKI:
				printf("*  TAKI *\n");
				break;
			case NUM_COLOR:
				printf("* COLOR *\n");
				break;
			}
		}
		else if (j == 4) {
			switch (Card.Color)
			{
			case NUM_YELLOW:
				printf("*   Y   *\n");
				break;
			case NUM_RED:
				printf("*   R   *\n");
				break;
			case NUM_BLUE:
				printf("*   B   *\n");
				break;
			case NUM_GREEN:
				printf("*   G   *\n");
				break;
			case 0: // when the choosen card is switch color he has no color at that moment.
				printf("*       *\n");
			}
		}
		else
			printf("*       *\n");
	}
}
int TakeOrPut(int numofcards) {
	int choise;
	printf("Please enter 0 if you want to take a card from the deck or 1-%d if you want to put one of your cards in the middle:\n", numofcards);
	scanf("%d", &choise);
	return choise;
}
void Game(Player* arrplayers, int numofplayers, Player* winner , Statistic* statisticarr) {
	Cards CardonTop = FirstCardOnTop();
	while (!CheckWinner(arrplayers, numofplayers, winner)) {// while the function didnt return true the while loop will continue.
		int i;
		for (i = 0; i < numofplayers; i++) {
			PrintCardOnTop(CardonTop);
			printf("\n%s's turn:\n\n" , arrplayers[i].Name);
			Round(&arrplayers[i], &CardonTop , &i , numofplayers, arrplayers , statisticarr);
			if (arrplayers[i].NumOfCards == 0)
				break;
		}
		CheckWinner(arrplayers, numofplayers, winner);
	}
}
void AddCardToPlayer(Player* p) { // פונקציה שמוסיפה קלף למערך על פי תנאים . האם מספר הקלפים גדול או קטן הגודל הלוגי
	int i;
	Cards* tmp = NULL;
	if (p->NumOfCards + 1 > p->SizeOfArrCards) { // אם מספר הלוגי של המערך קלפים קטן ממספר הקלפים של השחקן.
		p->SizeOfArrCards *= 2;
		tmp = (Cards*)malloc(sizeof(Cards) * (p->SizeOfArrCards));
		ValidateCardsMalloc(tmp);
		for (i = 0; i < p->NumOfCards; i++) {
			tmp[i] = p->CardesOfPlayer[i];
		}
		tmp[p->NumOfCards] = GetOneCard();
		p->NumOfCards++;
		free(p->CardesOfPlayer);
		p->CardesOfPlayer = tmp;
	}
	else
	{
		p->CardesOfPlayer[p->NumOfCards] = GetOneCard();
		p->NumOfCards++;
	}
	
	
}
Cards GetOneCard() { // פונקציה המגרילה קלף אחד
	Cards c;
	c.Kind = 1 + rand() % NUM_COLOR; // color is the last card of the cards .
	c.Color = 1 + rand() % NUM_GREEN; // green has the last number in the list of colors.
	if (c.Kind == NUM_COLOR) { // if the player get color card it has no color for that moment
		c.Color = NO_COLOR;
	}
	return c;
}
void RemoveCardFromPlayer(Player* p, int choise) {
	int i;
	for (i = 0; i < p->NumOfCards-1; i++) {
		if (i >= choise - 1)
			p->CardesOfPlayer[i] = p->CardesOfPlayer[i + 1];
	}
	p->NumOfCards--;	
}
void Round(Player* p , Cards* CardonTop , int* i , int numofplayers, Player* arrplayers , Statistic* statisticarr) {
	int choise;
	PrintCards(p);
	choise = TakeOrPut(p->NumOfCards);
	if (choise == 0) {
		AddCardToPlayer(p);
		StatisticCard(statisticarr, p);
	}
	else {
		while ((p->CardesOfPlayer[choise - 1].Kind != CardonTop->Kind) && (p->CardesOfPlayer[choise - 1].Color != CardonTop->Color) && (p->CardesOfPlayer[choise - 1].Kind != 14)) {
			printf("Invalid Card. Try again\n");
			choise = TakeOrPut(p->NumOfCards);
			if (choise == TAKE_FROM_DECK) {
				AddCardToPlayer(p);
				StatisticCard(statisticarr, p);
				break;
			}
		}
		if (choise != TAKE_FROM_DECK) {
			switch (p->CardesOfPlayer[choise-1].Kind)
			{
			case NUM_PLUS:
				*CardonTop = p->CardesOfPlayer[choise - 1];
				RemoveCardFromPlayer(p, choise);
				if (p->NumOfCards == 0) {
					AddCardToPlayer(p);
					StatisticCard(statisticarr, p);
					break;
				}
				PrintCardOnTop(*CardonTop);
				PrintCards(p);
				IsPlus(p, CardonTop , statisticarr);
				break;
			case NUM_STOP:
				*CardonTop = p->CardesOfPlayer[choise - 1];
				RemoveCardFromPlayer(p, choise);
				if ((p->NumOfCards == 0)&&(numofplayers>2))
					break;
				else if ((p->NumOfCards == 0) && (numofplayers <= 2)) {
					AddCardToPlayer(p);
					StatisticCard(statisticarr, p);
					break;
				}
				else
					IsStop(p, i, numofplayers);
				break;
			case NUM_SWITCH:
				*CardonTop = p->CardesOfPlayer[choise - 1];
				RemoveCardFromPlayer(p, choise);
				if ((p->NumOfCards == 0) && (numofplayers > 2))
					break;
				else if ((p->NumOfCards == 0) && (numofplayers <= 2)) {
					AddCardToPlayer(p);
					StatisticCard(statisticarr, p);
					break;
				}
				else
					IsSwitchDirections(arrplayers, i, numofplayers);
				break;
			case NUM_TAKI:
				*CardonTop = p->CardesOfPlayer[choise - 1];
				RemoveCardFromPlayer(p, choise);
				if (p->NumOfCards==0)
					break;
				PrintCardOnTop(*CardonTop);
				PrintCards(p);
				IsTaki(p , CardonTop);
				break;
			case NUM_COLOR:
				*CardonTop = p->CardesOfPlayer[choise - 1];
				IsColor(p , CardonTop);
				RemoveCardFromPlayer(p, choise);
				break;
			default:
				*CardonTop = p->CardesOfPlayer[choise - 1];
				RemoveCardFromPlayer(p, choise);
				break;
			}
		}
	}

}
void IsTaki(Player* p, Cards* cardOnTop) {
	p->NumOfCards--;
	int choise;
	printf("Please enter 0 if you want to finish your turn or 1-%d if you want to put one of your cards in the middle:\n" , p->NumOfCards);
	scanf("%d", &choise);
	while (choise != FINISH_TURN_IN_TAKI) {
			while (p->CardesOfPlayer[choise].Color != cardOnTop->Color) {
				printf("Invalid card. Try again.\n");
				printf("Please enter 0 if you want to finish your turn or 1-%d if you want to put one of your cards in the middle:\n", p->NumOfCards);
				scanf("%d", &choise);
				if (choise == FINISH_TURN_IN_TAKI);
				break;
			}
		if(choise!= FINISH_TURN_IN_TAKI){
			*cardOnTop = p->CardesOfPlayer[choise-1];
			RemoveCardFromPlayer(p, choise);
			printf("Please enter 0 if you want to finish your turn or 1-%d if you want to put one of your cards in the middle.:\n", p->NumOfCards);
			scanf("%d", &choise);
		}
	}
		

}
void IsColor(Player* p, Cards* cardOnTop) {
	printf("Please enter your color choise:\n1 - Yellow\n2 - Red\n3 - Blue\n4 - Green\n");
	scanf("%d", &cardOnTop->Color);


}
void IsPlus(Player* p, Cards* cardOnTop , Statistic* statisticarr) {
	int choise= TakeOrPut(p->NumOfCards);
	while ((p->CardesOfPlayer[choise - 1].Kind != cardOnTop->Kind) && (p->CardesOfPlayer[choise - 1].Color != cardOnTop->Color)) {
		printf("Invalid Card. Try again\n");
		choise = TakeOrPut(p->NumOfCards);
		if (choise == TAKE_FROM_DECK) {
			AddCardToPlayer(p);
			StatisticCard(statisticarr, p);
			break;
		}
	}
	if (choise != TAKE_FROM_DECK) {
			*cardOnTop = p->CardesOfPlayer[choise - 1];
			RemoveCardFromPlayer(p, choise);
	}
}
void IsStop(Player* p, int* i , int numofplayers) {
	if (*i == numofplayers-1)
		*i = 0;  // when the index of the player is the last, the next turn will be the the second player , because the loop is adding 1 to the index.
	else
		if (*i == numofplayers-2) // when the index of the player is one before the last , the next turn will be the first player ,  , because the loop is adding 1 to the index.
			*i = -1;
		else
			if (*i == 1)
				*i = *i+1;
}
void IsSwitchDirections(Player* arrplayers, int* i, int numofplayers) {
	int j, count = 0, h;
	Player* tmp;
	tmp = GetArrOfPlayers(numofplayers);
	for (j = 0; j < numofplayers; j++) {
		if (j < (*i))
			tmp[j] = arrplayers[(*i) - 1 - j];
		else {
			tmp[j] = arrplayers[numofplayers - 1 - count];
			count++;
		}
	}
	CopyArr(arrplayers, tmp, numofplayers);
	free(tmp);
	(*i) = -1; // the index of the for loop is reset.
}
void CopyArr(Player* p, Player* p1, int numofplayers) {
	int i;
	for (i = 0; i < numofplayers; i++)
		p[i] = p1[i];
}
void StatisticCard(Statistic* statisticarr , Player* p) {
	int kind;
	kind = p->CardesOfPlayer[p->NumOfCards - 1].Kind;
	statisticarr[kind-1].count++;
}
void StatInitArr(int numofcards, Statistic* statisticarr) {// מאפס את המערך סטטיקסטיקה על מנת תחילת עבודה.
	int i;
	for (i = 0; i < numofcards; i++) {
		statisticarr[i].kind = i + 1;
		statisticarr[i].count = 0;
	}	
}
void MergeSortStatistic(Statistic* statisticarr, int numofcards) {
	Statistic* tmp = NULL;
	if (numofcards <= 1)
		return;

	MergeSortStatistic(statisticarr, numofcards/2);
	MergeSortStatistic(statisticarr + numofcards / 2, numofcards - numofcards / 2);

	tmp = (Statistic*)malloc(numofcards * sizeof(Statistic));
	if (tmp)
	{
		merge(statisticarr, numofcards / 2, statisticarr + numofcards / 2, numofcards - numofcards / 2, tmp);
		copyStatisticArr(statisticarr, tmp, numofcards);
		free(tmp);
	}
	else {
		printf("Memory allocation failure!!!\n");
		exit(1);
	}
}
void merge(Statistic* s1, int size1, Statistic* s2, int size2 , Statistic* res) {
	int i1, i2, resi;
	i1 = i2 = resi = 0;

	while ((i1 < size1) && (i2 < size2)) {
		if (s1[i1].count <= s2[i2].count) {
			res[resi] = s1[i1];
			i1++;
		}
		else {
			res[resi] = s2[i2];
			i2++;
		}
		resi++;
	}
	while (i1 < size1) {
		res[resi] = s1[i1];
		i1++;
		resi++;	
	}
	while (i2 < size2) {
		res[resi] = s2[i2];
		i2++;
		resi++;
	}
}
void copyStatisticArr(Statistic* s1, Statistic* s2, int size) {
	int i;
	for (i = 0; i < size; i++)
		s1[i] = s2[i];
		
}
void printMergeSortStatistic(Statistic* statisticarr) {
	int i;
	printf("************ Game Statistics ************\n");
	printf("Card # | Frequancy\n");
	printf("_____________________\n");
	for (i = NUM_OF_CARDS - 1; i >= 0; i--) {
		switch (statisticarr[i].kind)
		{
			case 10:
				printf("   +    |    %d\n", statisticarr[i].count);
				break;
			case 11:
				printf("  STOP  |    %d\n", statisticarr[i].count);
				break;
			case 12:
				printf("  <->   |    %d\n", statisticarr[i].count);
				break;
			case 13:
				printf("  TAKI  |    %d\n", statisticarr[i].count);
				break;
			case 14:
				printf(" COLOR  |    %d\n", statisticarr[i].count);
				break;
			default:
				printf("   %d   |    %d\n", statisticarr[i].kind , statisticarr[i].count);
				break;
		}
	}

}
