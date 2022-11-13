#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

 int size ;

//function definitions
void set_Grid(vector <char> &grid  );
int coordinate_ID( int c, int r );
int within_grid( int c, int r );
void path_generation_fun( int c, int r, vector <char> &grid );
void set_start_end(vector <char> &grid);
void display_maze(vector <char> grid);

// driver function
int main()
{
	cout << "enter the size of the maze (enter an odd number) : ";
	cin >> size;
	cout<< endl;
	
 	srand( time(0) ); 
 	vector <char> grid;
 	
 	set_Grid(grid);
 	
 	int c = 1 ;
 	path_generation_fun(c, 1 , grid);
 	
 	set_start_end(grid);
 	
 	display_maze(grid);
 	
 	ofstream file("Maze_Generated.txt");
 	for (int i = 0 ; i < size; i++)
 	{
 		for (int j = 0 ; j < size; j++)
 		{
 			file<<grid[coordinate_ID(  j,  i )]   ;
		}
		file<<endl;
	}
	file<< c <<endl;
	file.close();
 	
 	return 0;
}

 //SETTING GRID WIth initial value 1
void set_Grid(vector <char> &grid)
{  
 	char temp = '1';
 	for (int i = 0; i < size * size ; i++)
 	{
 		grid.push_back(temp);
 	}
}

//deriving a single ID for each coordinate
int coordinate_ID( int c, int r )
{
 	return r * size + c;
}

//checking border conditions 
int within_grid( int c, int r )
{
 	if (c < 0 || c >= size)
	{
	 	return false;
	} 
 	else if (r < 0 || r >= size)
	  {
 		return false;
	 }
 	else
	 {
 		return true;
	 }
}

//path generation function(recursively)
void path_generation_fun( int c, int r, vector <char> &grid  )
{
 	grid[ coordinate_ID(c,r) ] = '0';
 	
 	int direction[4];
 	for(int i = 0 ; i < 4 ; i++)
 	{
 		direction[i] = i ;
	}

	//randomizing the direction te checking to take 	
 	for (int i = 0; i < 4; i++)
	{
 		int random_num = rand() & 3;
		int temp = direction[random_num];
 		direction[random_num] = direction[i];
		direction[i] = temp;
 	}

 	//finding the possible directions to visit
	for (int i=0; i< 4; i++)
 	{
 		int col_change = 0 , row_change = 0;
 		
 		switch (direction[i])
		{
			case 0 : {  row_change = -1; break;			}
 			case 1 : {  row_change =  1; break;			}
 			case 2 : {  col_change =  1; break;			}
 			case 3 : {  col_change = -1; break;	    	}
 		}
 		
 		int new_row = r + (row_change << 1);
 		int new_col = c + (col_change << 1);
 		
 		if (within_grid(new_col, new_row) )
 		{
 			if (grid[ coordinate_ID(new_col, new_row) ] == '1')
			{
				grid[ coordinate_ID(new_col - col_change, new_row - row_change) ] = '0';
 				
 				path_generation_fun(new_col, new_row , grid );
 			}
		}
	}
}

void set_start_end(vector <char> &grid)
{
	grid[coordinate_ID( 1 , 1 ) ] = 'B';
	grid[coordinate_ID( size-2 ,  size-1 ) ] = 'A';
}

void display_maze(vector <char> grid )
{
	 // Displays the finished maze to the screen.
	 cout << "find the path from 'A' to 'B' ('A' is on the bottom border) \n";
	 cout << endl;
 	for (int row = 0; row < size; row++)
 	{
 		for (int col = 0; col < size; col++)
 		{
 			cout << grid[ coordinate_ID(col, row) ] <<" ";	
 		}
 		cout << endl;
 	}
 	
}
