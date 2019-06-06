#include <fstream.h>
#include <conio.h>
#include <iomanip.h>

class play_area
{
 private:
	int board[31][31];
	int neighbour[31][31];
	int board_size;
	void neighbour_calc();               //calculates neighbours

 public:
	play_area(int Bsize);                //creates board initially
	void board_with_no();                //prints Board with row and column nos.
	void board_cout();                   //prints Board without row and column nos.
	void alive_cell(int r, int c);       //makes cell alive
	void next_gen();                     //decides the next gen.
};

play_area:: play_area(int Bsize)
{
 int i,j;
 board_size=Bsize;
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
     cout<<setw(2)<<j;
    else if(j==0 && i!=0)
     cout<<setw(2)<<i;
    else if(i==0 && j==0)
     cout<<setw(2)<<" ";
    else if(board[i][j]==0)
      cout<<setw(2)<<"_";
     else
      cout<<setw(2)<<"*";
   }
   cout<<"\n";
  }
}

void play_area::board_cout()
{
 for(int i=1;i<board_size+1;i++)
 {
  for(int j=1;j<board_size+1;j++)
  {
   if(board[i][j]==0)
    cout<<setw(2)<<"_";
   else
    cout<<setw(2)<<"*";
  }
  cout<<"\n";
 }
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

void main()
{
 clrscr();
 int row, column;
 char continu;
 play_area b(20);
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
 ofstream fout;
 fout.open("patterns.dat", ios::app | ios::binary);
 fout.write((char*)&b,sizeof(b));
 cout<<"File has been written.";
 getch();
}