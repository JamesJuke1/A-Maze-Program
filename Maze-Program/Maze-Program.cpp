#include <iostream>
#include <conio.h>
#include <vector>


std::vector<char> printableMap;
const int sizeOfMap = 70;
int mapWidth = 7;
int mapHeight = 10;
int iterator;
int playerLocation = rand() % sizeOfMap;
int mapStartPoint = 0;
int columnShift = 1;
int enemyLocation = rand() % sizeOfMap;
int trapLocation = rand() % sizeOfMap;
int treasureLocation = rand() % sizeOfMap;
int aboveTheMap = -1; //to represent that the player is too far up on the screen and "above the map"
int belowTheMap = sizeOfMap; // to represent that the player is too far down the screen and "below the map"
bool isGameOver = false;
static constexpr char playerIcon = 'G';
static constexpr char treasureIcon = 'X';
static constexpr char trapIcon = 'T';
static constexpr char enemyIcon = 'E';
static constexpr char spaceIcon = '_';



void DrawMap()
{
    for (int i = 0; i < sizeOfMap;i++)
    {
        if (printableMap.size() % mapWidth == 0)
        {
            std::cout << "\n"; // to create a new row of the map
               
        }
        if (i == playerLocation)
        {
            printableMap.push_back(playerIcon);
        }
        else if (i == enemyLocation)
        {
            printableMap.push_back(enemyIcon);
        }
        else if (i == trapLocation)
        {
            printableMap.push_back(trapIcon);
        }
        else if (i == treasureLocation)
        {
            printableMap.push_back(treasureIcon);
        }
        else
        {
            printableMap.push_back(spaceIcon);
        }
        std::cout << i + 1 <<  printableMap[i];
    }
}

void RecieveInput()
{
    //to get input from the user to update the position of the player on the map.

    switch (_getch())
    {
    case 'w':
        playerLocation -= mapWidth; // to move the player up one row on the map
        std::cout << "\nPlayer moving North!\n";
        break;
    case 's':
        playerLocation += mapWidth; //to move the player down one row on the map
        std::cout << "\nPlayer moving South!\n";
        break;
    case 'a': 
        playerLocation -= columnShift; // to move the player 1 column to the left on the map
        std::cout << "\nPlayer moving East!\n";
        break;
    case 'd':
        playerLocation += columnShift; //to move the player one row to the right on the map
        std::cout << "\nPlayer moving West!\n";
        break;
    default:
        std::cout << "***Invalid Selection, please use w, a, s, or d.";
        break;
    }
}

void RandomEnemyDirection() //still need to implement this for the bonus objective
{
    //enemy can only move one space randommly each turn.
    enum potientalDirection  { kEast, kWest, kNorth, kSouth };
    int randomDirection = rand() % 4;
    switch (randomDirection)
    {
    case 1:
        --enemyLocation;
        std::cout << "Enemy moved East!";
        break;
    case 2:
        ++enemyLocation;
        std::cout << "Enemy moved West!";
        break;
    case 3:
        enemyLocation -= 7;
        std::cout << "Enemy moved North!";
        break;
    case 4:
        enemyLocation += 7;
        std::cout << "Enemy moved South!";
        break;
    default:
        std::cout << "***Invalid Direction***";
    }


}

void WinOrLoseConditions()
{
    while(!isGameOver) //without DrawMap and RecieveInput at the end of the while loop this is an infinite loop
    {
        RecieveInput();
        RandomEnemyDirection();
        DrawMap();
        std::cout << "\nPlayer current location: " << playerLocation << "\n" << "Enemy current location: " << enemyLocation << "\n";
        //check to see if the enemy or the player are out of bounds
        if (playerLocation <= aboveTheMap)
        {
            isGameOver = true;
            std::cout << "\nPlayer has gone above the map \n";
        }
        else if (playerLocation >= belowTheMap + 1)
        {
            isGameOver = true;
            std::cout << "\nPlayer has gone below the map \n";
        }

        if (playerLocation == enemyLocation)
        {
            isGameOver = true;
            std::cout << "\nPlayer touched the enemy.\n";
        }

        if (playerLocation == trapLocation)
        {
            isGameOver = true;
            std::cout << "\nPlayer fell into a trap.\n";
        }
        if (playerLocation == treasureLocation)
        {
            isGameOver = true;
            std::cout << "\nPlayer found the treasure, Congrats!!!";
        }

        printableMap.clear();
    }
}


int main()
{   
    std::cout << "\nWelcome to the Maze Program. You objective is to get the player to the treasure (_X_) \n without touching the traps or enemies\n";
    std::cout << "Press w to move up, s to move down, a to move left, d to move right. Make sure to stay in the bounds of the map.\n";
    DrawMap();
    printableMap.clear();
    while (!isGameOver)
    {
        WinOrLoseConditions();
    }
}


