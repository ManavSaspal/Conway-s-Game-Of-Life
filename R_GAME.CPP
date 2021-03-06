#include <fstream.h>
#include <conio.h>
#include <iomanip.h>
#include <process.h>
#include <stdio.h>

char live[4]={176, 223, 176 };    //dotted box = 176
char dead[4]={176, 176, 176 };    //solid box  = 223

void about();                     //prints 'about' page
void rules();                     //prints 'rules' page
void instructions();              //prints 'instructions' page
void play();                      //plays game
void delay();                     //for time delay

class play_area
{
 private:
	int board[31][31];
	int neighbour[31][31];
	int board_size;
	void neighbour_calc();               //calculates neighbours

 public:
	play_area();                         //creates board initially
	void board_with_no();                //prints Board with row and column nos.
	void board_cout();                   //prints Board without row and column nos.
	void alive_cell(int r, int c);       //makes cell alive
	void next_gen();                     //decides the next gen.
	void gen();                          //for no. of gen. and mode of control
}b;



void play()
{
 int BoardSize, row, column, i, j, n;
 char continu, mode;

 cout<<"\n\t Play CONWAY'S GAME OF LIFE\n\n";
 cout<<"1. New Game?                               {'n'}\n";
 cout<<"2. Load Saved Game?                        {'s'}\n";
 cout<<"3. Play with pre-loaded patterns?          {'p'}\n";
 cout<<"Enter Choice: ";
 mode=getch();
 switch(mode)
 {
  case '1':
  case 'n':
  case 'N':clrscr();

	   b.board_with_no();

	   do
	   {
	    cout<<"Enter Cell's address to be made alive:";
	    cin>>row>>column;
	    cin>>continu;

	    b.alive_cell(row,column);

	    clrscr();

	    b.board_with_no();

	   }while(continu=='y'|| continu=='Y');
	   b.gen();
	   getch();

	   clrscr();
	   cout<<"Do You want to save the current state {'y'/'n'}? ";
	   cin>>continu;
	   if(continu=='y' || continu=='Y')
	   {
	    clrscr();
	    char file[35];
	    cout<<"Enter Name of File (put '.dat' extension at the end):";
	    gets(file);
	    ofstream f1;
	    f1.open(file, ios::out | ios::binary);
	    f1.write((char*)&b, sizeof(b));
	   }
	   break;

  case '2':
  case 's':
  case 'S':clrscr();
	   char file[35];
	   cout<<"Enter Name of saved File:";
	   gets(file);
	   ifstream f1;
	   f1.open(file, ios::in | ios::binary);
	   if(!f1)
	    cout<<"Error!, File Not Found.";
	   else
	   {
	    f1.read((char*)&b, sizeof(b));
	    b.board_with_no();
	    b.gen();
	   }

	   break;

  case '3':
  case 'p':
  case 'P':clrscr();
	   ifstream f2;

	   f2.open("patterns.dat", ios::in | ios::binary);
	   if(!f2)
	   {
	    cout<<"Error!, File Not Found.";
	    cout<<"\nYou might not have installed the setup correctly.";
	   }
	   else
	   {
	    cout<<"\tChoose pattern:\n\n";
	    cout<<"1. Glider\n";
	    cout<<"2. Small Exploder\n";
	    cout<<"3. Exploder\n";
	    cout<<"4. Lightweight Spaceship\n";
	    cout<<"5. Tumbler\n";
	    cout<<"6. 10 Cell Row\n";
	    cout<<"\nEnter Number of Pattern:";
	    cin>>n;
	    clrscr();
	    if(n>=1 && n<=6)
	    {
	     f2.seekg(sizeof(b)*(n-1), ios::beg); //moves the cursor to the beginning of nth record
	     f2.read((char*)&b, sizeof(b));
	     b.board_with_no();
	     getch();
	     b.gen();
	    }
	    else
	     cout<<"Invalid Code!";
	   }

	   break;

  default: cout<<"Invalid Choice!\n";
	   cout<<"Press any key to go to Home.";
	   break;

 }

}
void play_area::gen()
{
 int gen, g;
 char control;
 cout<<"Number Of Generations to be generated:";
 cin>>gen;
 clrscr();
 cout<<"Enter mode of control: \n";
 control_label:
   cout<<"( Automatic {'a'} OR Keyboard {'k'} )\n";
   control=getch();

   for(g=1;g<=gen;g++)
   {
    if(control=='k')
     getch();
    else if(control=='a')
     delay();
    else
    {
     cout<<"\nInvalid Choice!, Enter mode of control again:";
     goto control_label;
    }
    clrscr();

    next_gen();
    cout<<"\nGENERATION "<<g<<endl;
    board_cout();

   }//for(gen)
}

void main()
{
 char choice;
 home:
   clrscr();
   cout<<"\t\t\t_CONWAY'S GAME OF LIFE_\n\n";
   cout<<"\tHome:\n\n";
   cout<<"1. About The Game Of Life       {'a'}\n";
   cout<<"2. Rules                        {'r'}\n";
   cout<<"3. Instructions                 {'i'}\n";
   cout<<"4. Play                         {Enter}\n";
   cout<<"5. Quit                         {Esc}\n";
   cout<<"\nEnter Choice:";
   label1:
     choice=getch();
     switch(choice)
     {
      case '1':
      case 'a':
      case 'A':clrscr();
	       about();
	       break;
      case '2':
      case 'r':
      case 'R':clrscr();
	       rules();

		 break;
      case '3':
      case 'i':
      case 'I':clrscr();
	       instructions();
	       break;
      case '4':
      case 13 :clrscr();         // 'Enter'=13
	       play();
	       break;
      case '5':
      case 27 :exit(0);          //'Esc'   =27
	       break;
      default :cout<<"\nInvalid Choice";
	       cout<<"\nEnter Choice Again:";
	       goto label1;
 }
 cout<<"\n\nPress Tab for Home";
 cout<<"\nPress Esc for Exit\n";
 label2:

   choice=getch();
   switch(choice)
   {
    case 9  :goto home;
    case 27 :exit(0);
	     break;
    default :cout<<"Invalid Choice";
	     cout<<"\nEnter Choice Again:";
	     goto label2;
   }
   getch();
}

//play_area's Function Definitons

play_area:: play_area()
{
 int i,j;
 board_size=20;
 for(i=0;i<=board_size+2;i++)
  for(j=0;j<=board_size+2;j++)
   board[i][j]=0;
}

void play_area:: alive_cell(int r,int c)
{
 board[r][c]=1;
}

void play_area:: board_with_no()
{
 for(int i=0;i<board_size+1;i++)
  {
   for(int j=0;j<board_size+1;j++)
   {
    if(i==0 && j!=0)
     cout<<setw(3)<<j;
    else if(j==0 && i!=0)
     cout<<setw(3)<<i;
    else if(i==0 && j==0)
     cout<<setw(3)<<" ";
    else if(board[i][j]==0)
      cout<<setw(3)<<dead;
     else
      cout<<setw(3)<<live;
   }//for(j)
   cout<<"\n";
  }//for(i)
}

void play_area::board_cout()
{
 for(int i=1;i<board_size+1;i++)
 {
  for(int j=1;j<board_size+1;j++)
  {
   if(board[i][j]==0)
    cout<<setw(3)<<dead;
   else
    cout<<setw(3)<<live;
  }//for(j)
  cout<<"\n";
 }//for(i)
}

void play_area:: neighbour_calc()
{
 int p, q;
 for(int i=1;i<board_size+1;i++)
 {
  for(int j=1;j<board_size+1;j++)
  {
   if(board[i][j]==1)
    neighbour[i][j]=-1;
   else
    neighbour[i][j]=0;
   for(p=-1;p<=1;p++)
    {
     for(q=-1;q<=1;q++)
    {
      neighbour[i][j]+=board[i+p][j+q];
    }//for(q)
   }//for(p)
  }//for(j)
 }//for(i)
}

void play_area:: next_gen()
{
 neighbour_calc();
 for(int i=1;i<board_size+1;i++)
 {
  for(int j=1;j<board_size+1;j++)
  {
   if(board[i][j]==1 && (neighbour[i][j]>3 || neighbour[i][j]<2) )
    board[i][j]=0;
   else if(board[i][j]==0 && neighbour[i][j]==3 )
    board[i][j]=1;
  }//for(i)
 }//for(j)
}


//Other Function Definitions

void about()
{
 cout<<"\n\t ABOUT THE GAME OF LIFE\n";

 cout<<"\n The Game of Life is not your typical computer game. ";
 cout<<" It is a 'cellular automaton', and was invented by Cambridge mathematician John   Conway. ";
 cout<<"\n This game became widely known when it was mentioned in an article published by Scientific American in 1970. ";
 cout<<" It consists of a collection of cells which, based on a few mathematical rules, can live, die or multiply. ";
 cout<<" Depending on the initial conditions, the cells form various patterns throughout the course of the game. ";
 cout<<"\n The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input.";
 cout<<" One interacts with the Game of Life by creating an initial configuration and observing how it evolves, or, for advanced players, by creating patterns with particular properties.";
 cout<<" \nThis is just a simple simulation, made by me, of a piece of art made by John Conway.";
 cout<<" \n\nOne can see its better simulation at https://playgameoflife.com/";
}

void rules()
{
 cout<<"\n\t RULES";

 cout<<"\n The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, alive or dead, (or populated and unpopulated, respectively).";
 cout<<" Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:";
 cout<<"\n\n 1.	Any live cell with fewer than two live neighbors dies, as if by underpopulation.";
 cout<<"\n 2.	Any live cell with two or three live neighbors lives on to the next generation.";
 cout<<"\n 3.	Any live cell with more than three live neighbors dies, as if by overpopulation.";
 cout<<"\n 4.	Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.";
 cout<<"\n\n The rules continue to be applied repeatedly to create further generations.";
}

void instructions()
{
 cout<<"\n\t INSTRUCTIONS For NEW GAME";

 cout<<"\n\n The Size of the Board will always be a square grid of 20 cells.";
 cout<<" One can easily make cells alive at the initiation just by specifying the address of the cell followed by 'y' (For yes) if another cell is to be made alive or by 'n' (For no) if no other cell is to be made alive.";
 cout<<"\n In the following way:";

 cout<<"\n\n (Row Number) (Column Number) ('y' or 'n')";
 cout<<"\n To be noted that all three of them separated by a space and then enter is to be pressed.";

 cout<<"\n\n Then, number of generations to be formed is specified and then the mode of control which are:";
 cout<<"\n 1.   AUTOMATIC                 [Next gen. automatically]                 {'a'}";
 cout<<"\n 2.   MANUAL KEYBOARD CONTROL   [Next gen. after getting any key stroke]  {'k'}";
 cout<<"\n\nThen just sit back and watch your people populate and die as if you are the god.";

 cout<<"\nThen, save the last state of the board if you want to by specifying the file name followed by extension name i.e. '.dat'.";
}

void delay()
{
 for(long int w=0;w<10000000;w++); //For Time Delay
}



