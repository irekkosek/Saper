#include<windows.h>
#include <iostream>
#include <time.h>
#include <random>


using namespace std;
int loss = 0;
int Player_flag = -2; //marks the player's flag
int mines_number;//stores the amount of mines on the gameboard
int mines_numbercp; //stores copy of mines amount
int mine_rev = 0;  //says if mines should be revealed or not
int discovermd = 0; //defines if discover mode is on or off
int timecount;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //defines a handle (used for colors)


int board_sizex; // is responsible for horizontal size of the board (player given)
int board_sizey; // is responsible for vertical size of the board   (player given)
string  TextPositionX[20] = { "     A  "," B  "," C  "," D  "," E  "," F  "," G  "," H  "," I  "," J  "," K  "," L  "," M  "," N  "," O  "," P  "," Q  "," R  "," S  "," T  " }; // vertical markers for each "cell" // 4 additional spaces for A for popper display

string  TextPositionY[20] = { "1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20" }; // horizontal markers for each "cell"

int CellMarker[20][20]; //markers within array, which tell about the objects state
int CellStorage[20][20]; //stores position of mines
int CellRevealed[20][20]; //stores infomation about whether the cell was revealed or not

void Reveal(int x, int y);// recursively reveals cells

void CellContent(int CellMarker[][20], int x, int y)//puts corresponding character in right gap
{
    if (CellRevealed[x][y] == -3)
    {
        if (CellMarker[x][y] == 1) { cout << "1"; }//display figures
        if (CellMarker[x][y] == 2) { cout << "2"; }
        if (CellMarker[x][y] == 3) { cout << "3"; }
        if (CellMarker[x][y] == 4) { cout << "4"; }
        if (CellMarker[x][y] == 5) { cout << "5"; }
        if (CellMarker[x][y] == 6) { cout << "6"; }
        if (CellMarker[x][y] == 7) { cout << "7"; }
        if (CellMarker[x][y] == 8) { cout << "8"; }
    }
    if (CellRevealed[x][y] == 0)
    {
        SetConsoleTextAttribute(h, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED); //colors console text
        if (CellMarker[x][y] == 1) { cout << " "; }//do not display figures
        if (CellMarker[x][y] == 2) { cout << " "; }
        if (CellMarker[x][y] == 3) { cout << " "; }
        if (CellMarker[x][y] == 4) { cout << " "; }
        if (CellMarker[x][y] == 5) { cout << " "; }
        if (CellMarker[x][y] == 6) { cout << " "; }
        if (CellMarker[x][y] == 7) { cout << " "; }
        if (CellMarker[x][y] == 8) { cout << " "; }
        SetConsoleTextAttribute(h, 7);
    }

    if (CellMarker[x][y] == 0 && CellRevealed[x][y] == 0) //display lack of characters
    {
        SetConsoleTextAttribute(h, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
        cout << " ";
        SetConsoleTextAttribute(h, 7);
    }
    if (CellMarker[x][y] == 0 && CellRevealed[x][y] == -3) //display revealed objects
    {
        cout << " ";
    }


    if (mine_rev == 0)

    {
        SetConsoleTextAttribute(h, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
        if (CellMarker[x][y] == -1)
            cout << " ";
        SetConsoleTextAttribute(h, 7);
    }

    if (mine_rev == 1)
    {
        if (CellMarker[x][y] == -1)
        {
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_INTENSITY); //makes mines Red
            cout << "*";
            SetConsoleTextAttribute(h, 7);
        }
    }

    if (CellMarker[x][y] == -2)
    {
        SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_INTENSITY); //makes flags blue
        cout << "X";
        SetConsoleTextAttribute(h, 7);
    }
}


void GameBoard()// draws asked game board
{	//////////////////////////////////////
    for (int i = 0; i <= board_sizex - 1; i++) //board_size-1 equals to 10-1 (lowered by 1 to make loops work properly)
        cout << TextPositionX[i];
    for (int y = 0; y <= board_sizey - 1; y++)
    {
        cout << endl;
        if (y < 9) //sets proper display of 10th row and above (which is larger by one character (space) since it's two-digit number) by adding space infront any else
            cout << " " << TextPositionY[y];

        else
            cout << TextPositionY[y];


        for (int x = 0; x < board_sizex; x++)
        {
            cout << " |" << " ";
            CellContent(CellMarker, x, y);
        } //vertical line is always placed before each cell and space from last cell

        cout << " |"; //makes the last vertical line
        cout << endl << " ";

        if (y != board_sizey - 1) //does not draw a horizontal line at the end
        {
            cout << "  ";
            for (int x = 0; x < board_sizex; x++)
                cout << "+---";
            cout << "+";
        }
    }
    cout << endl << "mines left to flag:" << mines_numbercp
        << endl << "time passed: " << time(NULL) - timecount << " seconds";
}
void Inserting()
{

    int x = -1; int  y = -1; //Proper integer coordinates values
    string digit1{}; string digit2{};  //digits extracted from Coordinates(string) before converting
    string Coordinates; //user input on Coordinates
    cout << endl << "insert chosen coordinates: ";
    cin >> Coordinates;

    ///////////////////////////////////////////////////////////////
    //coordinate x:
    /////////////////////////////////////////////////////////////////
    if(((int(Coordinates[0]) - 65) >= 0) && ((int(Coordinates[0]) - 65) <= (board_sizex - 1)))
    {
        x = int(Coordinates[0]) - 65; //because ascii code for A is 65 and array starts from 0
    }

    ///////////////////////////////////////////////////////////////
    //coordinate y:
    /////////////////////////////////////////////////////////////////
    digit1 = Coordinates[1];
    digit2 = Coordinates[2];
    digit1 += digit2; //concatenates string digits
    
    try
    {
    y = stoi(digit1); //stoi converts string to integer
    }
    catch(...)
    {
        cout << " Please enter valid coordinates"; Sleep(3000); return;
    }
    y--;//decrementation to adjust to an array size

    if (x > board_sizex -1 || y > board_sizey - 1 || x < 0 || y < 0) //checks for invalid input by rejecting numbers above the given scale
    {
        cout << " Please enter valid coordinates"; Sleep(3000); return;
    }

    /////////////////////////////////////////////////////
    else if (CellMarker[x][y] == -1 && discovermd == 1)
    {
        mine_rev = 1; loss = 1;
    }
    else if (CellMarker[x][y] != -1 != -2 && discovermd == 1)
    {
        Reveal(x, y);
    }

    else if (CellMarker[x][y] == -2 && discovermd == 0) //checks if cell has been claimed already and if so displays proper message for set amount of time
    {
        CellMarker[x][y] = CellStorage[x][y]; mines_numbercp++; return;
    } //return skips switching the turns
    else if (CellMarker[x][y] == -1 || CellMarker[x][y] >= 0 && discovermd == 0)
    {
        CellMarker[x][y] = Player_flag; mines_numbercp--;
    }

    else
    {
        return;
    }
    //////////////////////////////////////////////////////

}
void Size_Menu()//lets player pick size of the gameboard
{
    for (int i = 0; i < 1;)
    {
        cout << "given gameboard horizontal size (5,20): ";
        cin >> board_sizex;
        cout << endl << "given gameboard vertical size (5,20): ";
        cin >> board_sizey;
        if (board_sizex > 20 || board_sizex < 5 || board_sizey > 20 || board_sizey < 5)
        {
            cout << "enter vaild gameboard size in range from 5 to 20"; Sleep(1500); system("CLS");
        }
        else
            i++;
    }
}
void Board_start_state()//filing the array with neutral 0
{
    for (int y = 0; y < board_sizey; y++)
        for (int x = 0; x < board_sizex; x++)
            {
                CellMarker[x][y] = 0;
                CellStorage[x][y] = 0;
                CellRevealed[x][y] = 0;
            }
}
void Mines_number_set()
{
    int i = 1;
    while (i > 0)
    {
        cout << "how many mines you wish to place?: ";
        cin >> mines_number;
        if (mines_number > board_sizex* board_sizey || mines_number <= 0)
        {
            cout << "you wish for too many or too little mines "; Sleep(1500); system("CLS");
        }
        else
            i--;
    }
    mines_numbercp = mines_number;
}
void Mines_location()

{
    mt19937 generator(time(nullptr)); //pseudo-random numbers generator
    int Mines_amount = mines_number;
    uniform_int_distribution<int> distributionx(0, board_sizex - 1); //defines range for x
    uniform_int_distribution<int> distributiony(0, board_sizey - 1); //defines range dor y
    while (Mines_amount > 0)
    {
        int x = distributionx(generator);
        int y = distributiony(generator);
        if(CellMarker[x][y] != -1)
        {
            CellMarker[x][y] = -1;
            Mines_amount--;
        }
    }

    for (int y = 0; y < board_sizey; y++)
        for (int x = 0; x < board_sizex; x++)
            CellStorage[x][y] = CellMarker[x][y];
}
void Figures()//marks the cells
{
    for (int y = 0; y < board_sizey; y++)
        for (int x = 0; x < board_sizex; x++)
        {
            if (CellMarker[x][y] != -1)
            {
                if (CellMarker[x - 1][y + 1] == -1 && x - 1 >= 0 && y + 1 <= board_sizey - 1) { CellMarker[x][y]++; }
                if (CellMarker[x][y + 1] == -1 && y + 1 <= board_sizey - 1) { CellMarker[x][y]++; }
                if (CellMarker[x + 1][y + 1] == -1 && x + 1 <= board_sizex - 1 && y + 1 <= board_sizey - 1) { CellMarker[x][y]++; }
                if (CellMarker[x - 1][y] == -1 && x - 1 >= 0) { CellMarker[x][y]++; }
                if (CellMarker[x + 1][y] == -1 && x + 1 <= board_sizex - 1) { CellMarker[x][y]++; }
                if (CellMarker[x - 1][y - 1] == -1 && x - 1 >= 0 && y - 1 >= 0) { CellMarker[x][y]++; }
                if (CellMarker[x][y - 1] == -1 && y - 1 >= 0) { CellMarker[x][y]++; }
                if (CellMarker[x + 1][y - 1] == -1 && x + 1 <= board_sizex - 1 && y - 1 >= 0) { CellMarker[x][y]++; }
            }
        }
    for (int y = 0; y < board_sizey; y++)
        for (int x = 0; x < board_sizex; x++)
            CellStorage[x][y] = CellMarker[x][y];

}

void win()
{
    int flgcounter = 0;//counts matching flags
    if (mines_numbercp == 0)
    {
        for (int y = 0; y < board_sizey; y++)
            for (int x = 0; x < board_sizex; x++)
            {
                if (CellMarker[x][y] == -2 && CellStorage[x][y] == -1)
                {
                    flgcounter++;
                }

            }
        if (flgcounter == mines_number)
        {
            mine_rev = 1;
        }
    }

}
void Reveal(int x, int y)
{
    if (x >= 0 && y >= 0 && x <= board_sizex - 1 && y <= board_sizey - 1)
    {
        if (CellMarker[x][y] == 0 && CellRevealed[x][y] == 0)
        {
            CellRevealed[x][y] = -3;
            Reveal(x - 1, y + 1);
            Reveal(x - 1, y);
            Reveal(x - 1, y - 1);

            Reveal(x, y + 1);
            Reveal(x, y);
            Reveal(x, y - 1);

            Reveal(x + 1, y + 1);
            Reveal(x + 1, y);
            Reveal(x + 1, y - 1);


        }
        if (CellMarker[x][y] > 0 && CellRevealed[x][y] == 0)
        {
            CellRevealed[x][y] = -3;
        }
    }

}
int ModeChoice()
{
    cout << endl << "do you want to discover(0) or flag(1)?:" << endl;
    string mode_input;
    while(mode_input != "1" && mode_input != "0")
    {
        cin >> mode_input;
        if(mode_input != "1" && mode_input != "0")
        {
            cout<< endl <<"Wrong input! Pick mode from 0 or 1" << endl;

        }
    }
    int mode{};
    mode = stoi(mode_input);
    return mode;
}
void StartScreen()
{
    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_INTENSITY);
cout << R"(
________________________________________________________________________        
 ________________________________________________________________________       
  _______________________________/\\\\\\\\\_______________________________      
   __/\\\\\\\\\\__/\\\\\\\\\_____/\\\/////\\\_____/\\\\\\\\___/\\/\\\\\\\__     
    _\/\\\//////__\////////\\\___\/\\\\\\\\\\____/\\\/////\\\_\/\\\/////\\\_    
     _\/\\\\\\\\\\___/\\\\\\\\\\__\/\\\//////____/\\\\\\\\\\\__\/\\\___\///__   
      _\////////\\\__/\\\/////\\\__\/\\\_________\//\\///////___\/\\\_________  
       __/\\\\\\\\\\_\//\\\\\\\\/\\_\/\\\__________\//\\\\\\\\\\_\/\\\_________ 
        _\//////////___\////////\//__\///____________\//////////__\///__________                                                                                                               
)";  
SetConsoleTextAttribute(h, 7);
    Sleep(5000);
    system("CLS");
}
int main()
{
    StartScreen();
    int restart = 1;
    while(restart == 1)
    {   
        loss = 0;
        mine_rev = 0;  //says if mines should be revealed or not
        discovermd = 0; //defines if discover mode is on or off

        int mode_choice;
        Size_Menu();
        Board_start_state();
        Mines_number_set();
        Mines_location();
        Figures();
        timecount = time(NULL);

        while (mine_rev == 0)
        {
            GameBoard();
            mode_choice = ModeChoice();
            system("CLS");

            if (mode_choice == 1)
            {
                discovermd = 0;
                GameBoard();
                cout << endl<< "you are: flagging" << endl;
                Inserting();
                win();
                system("CLS");
            }
            if (mode_choice == 0)
            {
                discovermd = 1;
                GameBoard();
                cout << endl << "you are: discovering" << endl;
                Inserting();
                system("CLS");
            }


        }
        if (mine_rev == 1 && loss == 1)
        {
            GameBoard();
            cout << endl << "You Lost!";
            cout <<endl <<"would you like to restart? (1 - yes / 0 - no)";
            cin >> restart;
            
        }
        if (mine_rev == 1 && loss == 0)
        {
            GameBoard();
            cout << endl << "You Won!";
            cout <<endl <<"would you like to restart? (1 - yes / 0 - no)";
            cin >> restart;
            
        }
    }
}



