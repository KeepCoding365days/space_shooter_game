#include <iostream>
#include<windows.h>
#include <conio.h>
#include<stdlib.h>
#include <time.h>
#include <cstring>
#include <fstream>
# define width 100 //macros
# define height 40
using namespace std;
int x = 50, y = 38;
int lives = 3,level=1,score=0;
char scr = score + 48;
char liv = lives+48, lev = level+48;
bool done = 1;
char area[height][width] = { { ' ' }, { ' ' } };
char area_new[height][width] = { { ' ' }, { ' ' } };
char card[100] =  "                Lives Left :                   Your score :                      Level:       ";
char ship = char(202);
void killing();//Hassan Mehmood
void instructions();    //Hassan Mehmood
void setCursorPosition(int i, int j); 
void change_area();
void ClearScreen();
int freq(char); //Hassan Mehmood
int vertical_motion(char);
void enemies(); 
void bullets(); //Zoraiz Awan
int area_assign( );  //Zoraiz Awan
int position_input();//Hamza Ashfaq
void change(int);   //Hamza Ashfaq
void pos_spaceship(int a, int b);//Hamza Ashfaq
int random();   //Hassan Mehmood

int main()
{
    system("Color 02");
strt:
    instructions();
    int input = 0;
    area_assign();
    

    while (lives > 0 && level <= 5) {
        
        input = position_input();
        if (input == 32) {
            bullets();
        }
        else {
            change(input);
        }

        pos_spaceship(x, y);
        area_assign();
        ClearScreen();
        change_area();
        Sleep(50);
        enemies();
        vertical_motion('!');

        area_assign();

        ClearScreen();
        change_area();

    }

    if (lives == 0) {

        int desc = 0;
        system("CLS");
        cout << "Your scores are: " << score << endl;
        ofstream output("scores.txt");
        output << score;
        output.close();
        cout << "If you want to play again, Please enter 5. Enter any other number to exit:";
        cin >> desc;
        if (desc == 5) {
            lives = 3;
            score = 0;
            level = 1;
            goto strt;
        }
        else {
            exit(0);
        }
    }


    else if (level > 5) {
        int desc = 0;
        system("CLS");
        cout << "You have won. Your scores are: " << score << endl;
        ifstream input("scores.txt");
        input >> score;
        input.close();
        cout << "If you want to play again, Please enter 5. Enter any other umber to exit:";
        cin >> desc;
        if (desc == 5) {
            lives = 3;
            score = 0;
            level = 1;
            goto strt;
        }
    
    }
    system("pause");

    return 0; 
}

int area_assign( )
{
    scr = score + 48;
    liv = lives + 48;
    lev = level + 48;
    card[90] = lev;
    card[30] = liv;
    card[60] = scr; //can't show score in double figures

        for (int i = 0; i < height; i++) {
            int m=0;
            for (int j = 0; j < width; j++) {
                if (j == 0 ) {
                    area[i][j] = '#';
                }
                else if (i == 2 && j!= width-1 ) {
                    if (card[m] != '\0') {
                        area[i][j] = card[m];

                        m++;
                    }

                }
            
                
                else if (i == 0 || i == height - 1|| i==4) {
                    area[i][j] = '#';

                }
                else if (j == width - 1) {
                    area[i][j] = '#';
                }
              
             
                else if((j!=x|| i!=y )&& (area[i][j]!='!'|| i==6) && (area[i][j] != '*' || i == 38)) {
                    area[i][j] = ' ';
                }
                
                
                
            }
            
        
        
    }

    return 0;
}
    int position_input() {
        int input=0;
        while (1) {

            if (_kbhit()) {
                input = _getch();
                break;
            }
        }
    return input;
}
        void change(int input){
            if (input == 50) {//2
                y-=2;
            }
            else if (input ==56 ) {//8
                y+=2;
            }
            else if (input == 52) {//4
                x-=2;
            }
            else if (input == 54) {//6
                x+=2;
            }
        }
        void instructions() {
            cout << "\t Instructions\t\t\t" << endl;
            cout << "1. Press 4 to move space-ship left." << endl;
            cout << "2. Press 6 to move space-ship right." << endl << "3. Press Space key to Firing the bullets." << endl;
            cout << "4. Press 2 to move space ship upward and press 8 to move downward." << endl;
            cout << "Press any key to start the game." << endl;

        }
        void bullets() {
          
            for (int i = 0; i < height;i++) {
                for (int j = 0; j < width; j++) {
                    if (j == x && i == y - 1 && i != 0) {
                        area[i][j] = '!';
                    }
                    
                }

            }
        }
 
        void pos_spaceship(int a, int b) {
            if (x >= width) {
                x = width - 2;
            }
            else if (x <=2) {
                x = 2;
            }
            if (y >= height) {
                y = height - 2;
            }
            else if (y <= 5) {
                y = 6;
            }
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (i == y && j == x) {
                        area[i][j] = ship;

                    
                    }
                }
            }

        }
        int random() {
            int num = 0;
            srand(time(0));
            num = (rand() % width) + 1;
            return num;
        }
        void enemies() {
            int w_1 = random();
            Sleep(200);
            int w_2 = random();
            Sleep(200);
            int w_3 = random();
            if (level < 3) {
                area[5][w_1] = '*';
                area[5][w_2] = '*';
            }
            else {
                area[5][w_1] = '*';
                area[5][w_2] = '*';
                area[5][w_3] = '*';
            }

           

        }
        int vertical_motion(char item) {
            int p = 0, q = 0, frequency = freq(item);
            int enemy_check=0;
            while (frequency>0&& !_kbhit() && lives>0 && level <= 5) {

                for (int i = 6, m = 38; i < height || m>0; i++) {
                   
                    for (int j = 0; j < width; j++) {
                        if (area[i][j] == item && i > 2) {
                            area[i][j] = ' ';
                            p = i - 1;
                            area[p][j] = item;
                        }


                        if (area[m][j] == '*') {
                            area[m][j] = ' ';
                            q = m + 1;
                            area[q][j] = '*';
                        }
                    }
                    m--;
                    
                }
                killing();
                if(enemy_check!=0&&(enemy_check%2==0))
                enemies();
                area_assign();
                ClearScreen();
                change_area();
                enemy_check++;
                        
                   
                   }
                
            
        return 0;
}
        void killing()
        {
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (area[i][j] == '*')//enemy
                    {
                        if (area[i + 1][j] == '!'||area[i+2][j]=='!')
                        {
                            area[i][j] = ' ';
                            area[i + 1][j] = ' ';
                            area[i + 2][j] = ' ';
                            score++;
                            if (score > level * 10) {
                                level++;
                            }
                        }
                        else if (area[i + 1][j] == ship)
                        {
                            area[i][j] = ' ';
                            area[i + 1][j] = ' ';
                            lives--;
                            pos_spaceship(50, 48);
                            if (lives == 0) {
                                break;
                            }

                        }
                    }
                }
            }
        }
        int freq(char item) {
            int frequency=0;
            for (int i = 0; i < height;i++) {
                for (int j = 0; j < width; j++) {
                    if (i > 2 && area[i][j] == item) {
                        frequency++;
                    }
                }
            }
                return frequency;
        }
        void change_area() {
            for (int i = 0;i < height;i++) {
                for (int j = 0; j < width; j++) {
                    area_new[i][j] = area[i][j];
                }
            }
        }
        void setCursorPosition(int i, int j)
        {
            static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            std::cout.flush();
            COORD cord = { (SHORT)i, (SHORT)j };
            SetConsoleCursorPosition(hOut, cord);
        }
        void ClearScreen()
        {
            std::memset((char*)area_new, 0, width * height);

            

            for (int i = 0; i != height; ++i)
            {
                for (int j = 0;j  != width; ++j)
                {
                    if (area[i][j] == area_new[i][j]) {
                        continue;
                    }
                    setCursorPosition(j, i);
                    std::cout << area[i][j];
                }
            }
            std::cout.flush();
           std::memcpy((char*)area_new, (char const*)area, width * height);
        }