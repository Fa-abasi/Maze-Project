//Data Structure ... Maze Project ... Fatemeh Abbasi
#include"stdafx.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stack>
using namespace std;

struct coordinate
{
	int i, j;

}S,E;
struct item {
	int i, j;
	char Direction;//r=right-l=left-u=up-d=down
}temp;

vector<vector<char>> file_to_vector(string filename)
{
	ifstream input(filename, ios::in);
	if (!input)
	{
		cout << "Oops!!The file will not open!\nTry another time.\n";
		abort();
	}
	int row, column;
	char temp;
	input >> row >> column;
	vector <vector<char>> maze(row,vector<char> (column));
	for (int h = 0; h < row; h++) {
		for (int g = 0; g < column; g++)
		{
			input >> temp;
			if (temp != 'S' && temp != 'E')
				maze[h][g] = temp;
			else
			{
				(temp == 'S') ? (S.i = h, S.j = g ): (E.i = h, E.j = g);
				maze[h][g] = '0';
			}
		}
	}
	input.close();
	return maze;
}

stack<item> FindBestWay(vector<vector<char>> maze) {
	vector<vector<char>> orginalMaze = maze;
	
	int I = S.i;
	int J = S.j;
	int row = maze.size();
	int column = maze[0].size();
	char check;
	stack<item> Bway;//Best way
	while (I != E.i || J != E.j)
	{
		check = '0';
		if (J + 1 < column && J+1>=0) {
			if (maze[I][J + 1] != '1') {
				if (maze[I][J + 1] == '2' && check == '0')
					check = 'r';
				if (maze[I][J + 1] < '2')
				{
					temp.Direction = 'r';
					temp.i = I;
					temp.j = J;
					Bway.push(temp);
					maze[I][J] = '2';
					J++;
					continue;
				}


			}
			
		}
		//....
		if (I + 1 < row && I + 1 >=0) {
			if (maze[I + 1][J] != '1')
			{
				if (maze[I + 1][J] == '2' && check == '0')
					check = 'd';
				if (maze[I + 1][J] < '2')
				{
					temp.Direction = 'd';
					temp.i = I;
					temp.j = J;
					Bway.push(temp);
					maze[I][J] = '2';
					I++;
					continue;

				}

			}
			
		}
		//....
		if (J - 1 >= 0 && J-1<column) {
			if (maze[I][J - 1] != '1')
			{
				if (maze[I][J - 1] == '2' && check == '0')
					check = 'l';
				if (maze[I][J - 1] < '2')
				{
					temp.Direction = 'l';
					temp.i = I;
					temp.j = J;
					Bway.push(temp);
					maze[I][J] = '2';
					J--;
					
					continue;
				}

			}
			
		}
		//...
		if (I - 1 >= 0 && I-1 < row) {
			if (maze[I - 1][J] != '1')
			{
				if (maze[I - 1][J] == '2' && check == '0')
					check = 'u';
				if (maze[I - 1][J] < '2')
				{
					temp.Direction = 'u';
					temp.i = I;
					temp.j = J;
					Bway.push(temp);
					maze[I][J] = '2';
					I--;
					continue;

				}

			}
			
		}
		//...
		if (check != '0')
		{
			Bway.pop();
			maze[I][J] = '3';
			switch (check)
			{
			case 'l':
				J--;
				break;

			case 'r':
				J++;
				break;
			case 'u':
				I--;
				break;
			case 'd':
				I++;
				break;
			}
		}
		//...
		if (check == '0')
			throw invalid_argument("impossible");

		
	}
	return Bway;
}

int main() {
	while (true) {
		string name;
		cout << "Enter the Name of the Maze File : ";
		cin >> name;
		vector<vector<char>> maze = file_to_vector(name + ".txt");
		cout << "S : ( " << S.i << " , " << S.j << " ) " << endl;
		cout << "E : ( " << E.i << " , " << E.j << " ) " << endl;
		cout << "\n";
		for (int h = 0; h < maze.size(); h++) {
			for (int g = 0; g < maze[h].size(); g++)
				cout << maze[h][g] << "  ";
			cout << endl;
		}
		ofstream output("result" + name + ".txt", ios::app);
		if (!output)
		{
			cout << "Oops!!The file will not open!\nTry another time.\n";
			abort();
		}
		try {
			stack<item> answerMaze;
			answerMaze = FindBestWay(maze);
			stack<item> answerMaze2 = answerMaze;
			item t;
			int R = maze.size();//row
			int C = maze[0].size();//column
			cout << "\n\nAnswer\n\n";
			while (!answerMaze.empty())
			{
				t = answerMaze.top();
				output << "(" << t.i << "," << t.j << ") <- ";
				answerMaze.pop();
			}
			maze[S.i][S.j] = 'S';
			maze[E.i][E.j] = 'E';
			while (!answerMaze2.empty()) {
				item x = answerMaze2.top();
				switch (x.Direction)
				{
				case 'r':
					maze[x.i][x.j] = '>';
					break;
				case 'd':
					maze[x.i][x.j] = 'v';
					break;
				case 'u':
					maze[x.i][x.j] = '^';
					break;
				case 'l':
					maze[x.i][x.j] = '<';
					break;
				}
				answerMaze2.pop();
			}

			for (int h = 0; h < R; h++) {
				for (int g = 0; g < C; g++) {
					cout << maze[h][g] << "  ";

				}
				cout << endl;
			}
		}
		catch (invalid_argument ia)
		{
			cout << "\n\n The Maze has no answer\n\n";
			output << " *****IMPOSSIBLE***** ";
		}
		output.close();
		char ans;
		cout << "Do you want to continue ? (y|n)";
		cin >> ans;
		if (ans == 'n')
			break;
	}
	cin.get();
	return 0;
}

 