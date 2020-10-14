#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <conio.h>


class Cards
{
private:
	int houseMoney = 100000;
	std::vector<char> oldCard_Numb;
	std::vector<char> oldCard_Color;
	std::vector<std::string> cardsHouse;
	std::vector<std::string> shown_cardsHouse;
	std::vector<std::string> cardsPlayer;
	std::vector<char> cardsNumbPlayer;
	std::vector<char> cardsNumbHouse;
public:
	bool mainGame(int* pPlayerMoney)
	{
		int bet;
		int* pBet = &bet;
		bool round_On = true;
		bool playerDraw = true;
		bool houseDraw = true;
		reset();
		if (*pPlayerMoney == 0) return false;
		do
		{
			std::cout << "\nHow much do you want to bet\nIf u want to quit bet (0)";
			std::cin >> bet;
			if (bet == 0) return false;
		} while (*pPlayerMoney < bet);
		
		system("cls");
		std::cout << "\nThe dealer is dealing\n";
		phase1(); //just player and house add cards to hand
		system("cls");
		print(pPlayerMoney ,bet ,round_On);
		round_On = checkWin(pPlayerMoney, bet, round_On);
		if (!round_On)
		{
			print(pPlayerMoney, bet);
			checkWin(pPlayerMoney, bet, !round_On);
		}
		else
		{
			do
			{
				playerDraw = player_input_Case(pBet, pPlayerMoney);
				print(pPlayerMoney, bet, playerDraw);
				if (add_PlayerPoints() >= 21)
				{
					if (add_PlayerPoints() > 21)
						houseDraw = false;
					break;
				}
			} while (playerDraw);

			if (houseDraw)
			{
				while (add_HousePoints() < 17)
				{
					cardsHouse.push_back(cardDraw_and_pointsSys(cardsHouse));
					print(pPlayerMoney, bet);
				}
			}
			houseDraw = false;
			print(pPlayerMoney, bet);
			checkWin(pPlayerMoney, bet, houseDraw);
		}
	}
private:

	void phase1() //super not effective
	{
		cardsPlayer.push_back(cardDraw_and_pointsSys(cardsPlayer));
		cardsPlayer.push_back(cardDraw_and_pointsSys(cardsPlayer));
		cardsHouse.push_back(cardDraw_and_pointsSys(cardsHouse));
		cardsHouse.push_back(cardDraw_and_pointsSys(cardsHouse));
	}

	bool player_input_Case(int* bet,int* pPlayerMoney)
	{
		std::cout << "\nDo you want to stand(s), or draw(d), or dobble down(2)";
		char player_Input = _getch();
		switch (player_Input)
		{
		case 's':
			return false;
			break;
		case 'd':
			cardsPlayer.push_back(cardDraw_and_pointsSys(cardsPlayer));
			return true;
			break;
		case '2':
			if (*bet * 2 <= *pPlayerMoney)
			{
				*bet = *bet * 2;
				cardsPlayer.push_back(cardDraw_and_pointsSys(cardsPlayer));
				return false;
			}
			else
				return true;
			break;
		default:
			return true;
			break;
		}
	}

	std::string cardDraw_and_pointsSys(std::vector<std::string> cardHolder) //this fuction is working (not optimal) but if it is more players the game will us more time and data power to genreate cars
	{
		char cardNumb[13]{'2','3','4','5','6','7','8','9','T','J','Q','K','A' };  //all Number of cards
		char cardColor[4]{ 'h','s','c','d' }; //all color of cards
		int x;	int y; 
		bool cardDrawn = true;
		do
		{
			x = random(12); //random value to pull for cardNumb
			y = random(3); //random value to pull for cardColor
			for (int i = 0; i < oldCard_Numb.size(); i++)
			{
				if (cardNumb[x] == oldCard_Numb[i])
				{
					for (int j = 0; j < oldCard_Color.size(); j++)
					{
						if (cardColor[y] == oldCard_Color[j])
							cardDrawn = false;//draw again.
						else
							cardDrawn = true;//has used same number but different color
					}
				}
				else
					cardDrawn = true;//not used the  the number
			}
		} while (!cardDrawn);

		oldCard_Numb.push_back(cardNumb[x]);
		oldCard_Color.push_back(cardColor[y]);
		std::string card = "";
		card.push_back(cardNumb[x]);
		card.push_back(cardColor[y]);
		if (cardHolder == cardsPlayer)
			cardsNumbPlayer.push_back(cardNumb[x]);
		else if (cardHolder == cardsHouse)
			cardsNumbHouse.push_back(cardNumb[x]);
		return card;
	}

	int random(int max)
	{
		int rand;
		int min = 0;
		std::mt19937 generator;
		generator.seed(std::time(0));
		std::uniform_int_distribution<uint32_t> dice(min, max);
		return rand = dice(generator);
	}

	void print(int* pPlayerMoney,int bet, bool round_On)
	{
		system("cls");
		std::cout << "\tBlackJack\n\n";
		std::cout << "House Money\t" << houseMoney << " nok" << std::endl;
		std::cout << "\tHouse Cards " << add_HouseCards(round_On) << std::endl;
		std::cout << "Houses poits " << add_HousePoints(round_On) << std::endl;
		std::cout << "\n\nYour Money\t" << *pPlayerMoney - bet << " nok\t\tYou betted " << bet << " nok" << std::endl;
		std::cout << "\tYour cards " << add_PlayerCards() << std::endl;
		std::cout << "Your Points " << add_PlayerPoints() << std::endl;
	}

	void print(int* pPlayerMoney, int bet)
	{
		system("cls");
		std::cout << "\tBlackJack\n\n";
		std::cout << "House Money " << houseMoney << " nok" << std::endl;
		std::cout << "\tHouse Cards " << add_HouseCards() << std::endl;
		std::cout << "Houses poits " << add_HousePoints() << std::endl;
		std::cout << "\n\nYour Money " << *pPlayerMoney - bet << " nok\t\tYou betted " << bet << " nok" << std::endl;
		std::cout << "\tYour cards " << add_PlayerCards() << std::endl;
		std::cout << "Your Points " << add_PlayerPoints() << std::endl;
	}

	std::string add_PlayerCards()
	{
		std::string value = "";
		for (int i = 0; i < cardsPlayer.size(); i++)
		{
			value += cardsPlayer[i] + " ";
		}
		return value;
	}

	std::string add_HouseCards()
	{
		std::string value = "";
		for (int i = 0; i < cardsHouse.size(); i++)
		{
			value += cardsHouse[i] + " ";
		}
		return value;
	}

	std::string add_HouseCards(bool round_On)
	{
		std::string value = "";
		value = cardsHouse[0] + " " + "X";
		return value;
	}

	int add_PlayerPoints()
	{
		int r = 0;
		for (int i = 0; i < cardsPlayer.size(); i++)
		{
			if(cardsNumbPlayer[i] >= 50 && cardsNumbPlayer[i] <= 57)
				r += cardsNumbPlayer[i] - 48;
			else if(cardsNumbPlayer[i] >= 74 && cardsNumbPlayer[i] <= 84)
				r += 10;
			else if (cardsNumbPlayer[i] == 65)
			{
				if (11 + r > 21)
					r += 1;
				else
					r += 11;
			}
		}
		return r;
	}

	int add_HousePoints(bool round_On)
	{
		int r = 0;
		if (cardsNumbHouse[0] >= 50 && cardsNumbHouse[0] <= 57)
			r += cardsNumbHouse[0] - 48;
		else if (cardsNumbHouse[0] >= 74 && cardsNumbHouse[0] <= 84)
			r += 10;
		else if (cardsNumbHouse[0] == 65)
		{
			if (11 + r > 21)
				r += 1;
			else
				r += 11;
		}
		return r;
	}

	int add_HousePoints()
	{
		int r = 0;
		for (int i = 0; i < cardsHouse.size(); i++)
		{
			if (cardsNumbHouse[i] >= 50 && cardsNumbHouse[i] <= 57)
				r += cardsNumbHouse[i] - 48;
			else if (cardsNumbHouse[i] >= 74 && cardsNumbHouse[i] <= 84)
				r += 10;
			else if (cardsNumbHouse[i] == 65)
			{
				if (11 + r > 21)
					r += 1;
				else
					r += 11;
			}
		}
		return r;
	}
	
	bool checkWin(int* pPlayerMoney, int bet, bool round_On)
	{
		int win = 0; // (1)house wins, (2)player wins, (3)tie, (4) player got blackJack
		if (round_On)
		{
			if (add_PlayerPoints() == 21 && add_HousePoints() == 21)
				win = 3;
			else if (add_PlayerPoints() != 21 && add_HousePoints() == 21)
				win = 1;
			else if (add_PlayerPoints() == 21 && add_HousePoints() != 21)
				win = 4;
		}
		else
		{
			if (add_HousePoints() == add_PlayerPoints() && add_HousePoints() >= 17)
				win = 3;
			else if (add_HousePoints() < 21 && (add_PlayerPoints() < add_HousePoints()) || (add_HousePoints() <= 21 && add_PlayerPoints() > 21))
				win = 1;
			else if (add_PlayerPoints() < 21 && (add_HousePoints() < add_PlayerPoints()) || (add_HousePoints() > 21 && add_PlayerPoints() <= 21))
				win = 2;
		}
		printWin(win, bet, pPlayerMoney);
		if (win == 0) return true;
		else return false;
	}

	void printWin(int win, int bet,  int* pPlayerMoney)
	{
		int pay = 0;
		switch (win)
		{
		case 1:
			std::cout << "\nHouse won";
			std::cout << "\nYou Lost " << bet << " to the House";
			houseMoney += bet;
			*pPlayerMoney -= bet;
			break;
		case 2:
			std::cout << "\nYou won";
			std::cout << "\nYou got " << bet << " from the House";
			houseMoney -= bet;
			*pPlayerMoney += bet;
			break;
		case 3:
			std::cout << "\nIt's a tie";
			std::cout << "\nYou got to keep your money";
			break;
		case 4:
			pay = (bet / 2) * 3;
			std::cout << "\nYou won";
			std::cout << "\nYou got BlackJack, pay out is then 3 to 2";
			std::cout << "\nYou got payed "<< pay << " out is then 3 to 2";
			houseMoney -= pay;
			*pPlayerMoney += pay;
			break;
		default:
			break;
		}
	}

	void reset()
	{
		cardsHouse.clear();
		shown_cardsHouse.clear();
		cardsPlayer.clear();
		cardsNumbPlayer.clear();
		cardsNumbHouse.clear();
	}
};

int main()
{
	Cards cards;
	bool game_on = true;
	int playerMoney = 0;
	int* pPlayerMoney = &playerMoney;

	system("cls");
	std::cout << "Set in money to play\ntype the amount you want to put in :\n";
	std::cin >> playerMoney;

	do
	{
		cards.mainGame(pPlayerMoney);
	} while (game_on);

	return 0;
}