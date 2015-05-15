#include <iostream>
#include <vector>

using namespace std;

class board 
{
public:
       int N;
       int position[100];
       vector<vector<int> > Y; // contains Y value of all possible solution sets
       vector<vector<int> > X;
       board(int x)
       {
          N = x;
          position[x];
       }
// Check if a position is safe
bool isSafe(int queen_number, int row_position)
{
        // Check each queen before this one
        for(int i=0; i<queen_number; i++)
        {
                // Get another queen's row_position
                int other_row_pos = position[i];

                // Now check if they're in the same row or diagonals
                if(other_row_pos == row_position || // Same row
                        other_row_pos == row_position - (queen_number-i) || // Same diagonal
                        other_row_pos == row_position + (queen_number-i))   // Same diagonal
                        return false;
        }
        return true;
}

// Recursively generate a tuple like [0 0 0 0], then [0 0 0 1] then etc...
void solve(int k)
{
        if(k == N) // We placed N-1 queens (0 included), problem solved!
        {
             vector<int> a;
             vector<int> b;
                for(int i = 0; i < N; i++)
               {
                       a.push_back(position[i] + 1); // (i+1, pos[i]+1)
                       b.push_back(i+1);
               }
               Y.push_back(a);
               X.push_back(b);
        }
        else
        {
                for(int i = 0; i < N; i++) // Generate ALL combinations
                {
                        // Before putting a queen (the k-th queen) into a row, test it for safeness
                        if(isSafe(k,i))
                        {
                                position[k] = i;
                                // Place another queen
                                solve(k+1);
                        }
                }
        }
}
void uniqueSol()
{
     int i, j = 0, num = Y.size(), k = 1, cnt, b, a, copy;
     bool flag = false; 
     copy = num; 
     cout << "Unique solutions:" << endl;
     /* Cases:
              (x,y) => (-y, x)
                      (-x, -y)
                      (-x, y)
                      (-y, -x)
                      (y, x)
                      (y, -x)
     
     */
     //90' CW, Y -> X, X -> - Y
     cnt = 0, b;
     for (i = 0; i < num; i++)
     {
         for (j = i+1; j < num; j++)
         {
           for (a = 0; a < N; a++)
           {
            for (b = 0; b < N; b++)
            {
             if (Y[i][a]==X[j][b] && Y[j][b]+X[i][a]==N+1)
             {
                cnt++;
                break; 
             }
             }
           }
           if (cnt == N)
           {
                Y.erase(Y.begin()+j);
                X.erase(X.begin()+j);
                num = Y.size();
           }
           cnt = 0; 
         }
     }
     cnt = 0; 
     //90' CCW, Y -> -Y, X -> -X
    cnt = 0, b;
     for (i = 0; i < num; i++)
     {
         for (j = i+1; j < num; j++)
         {
           for (a = 0; a < N; a++)
           {
            for (b = 0; b < N; b++)
            {
             if (Y[i][a]+Y[j][b] == N+1 && X[j][b]+X[i][a]==N+1)
             {
                cnt++;
                break; 
             }
             }
           }
           if (cnt == N)
           {
                Y.erase(Y.begin()+j);
                X.erase(X.begin()+j);
                num = Y.size();
           }
           cnt = 0; 
         }
     }
     cnt = 0; 
     //Flip vertically, Y -> Y, X -> -X
     cnt = 0, b;
     for (i = 0; i < num; i++)
     {
         for (j = i+1; j < num; j++)
         {
           for (a = 0; a < N; a++)
           {
            for (b = 0; b < N; b++)
            {
             if (Y[i][a]==Y[j][b] && X[j][b]+X[i][a]==N+1)
             {
                cnt++;
                break; 
             }
             }
           }
           if (cnt == N)
           {
                Y.erase(Y.begin()+j);
                X.erase(X.begin()+j);
                num = Y.size();
           }
           cnt = 0; 
         }
     }
     cnt = 0; 
     //Flip horizontally, X-> -Y, Y -> -X
    cnt = 0, b;
     for (i = 0; i < num; i++)
     {
         for (j = i+1; j < num; j++)
         {
           for (a = 0; a < N; a++)
           {
            for (b = 0; b < N; b++)
            {
             if (X[i][a]+Y[j][b] == N+1 && X[j][b]+Y[i][a]==N+1)
             {
                cnt++;
                break; 
             }
             }
           }
           if (cnt == N)
           {
                Y.erase(Y.begin()+j);
                X.erase(X.begin()+j);
                num = Y.size();
           }
           cnt = 0; 
         }
     }
     cnt = 0; 
     //90' CCW + Flip vertically, x -> y, y -> x 
     cnt = 0, b;
     for (i = 0; i < num; i++)
     {
         for (j = i+1; j < num; j++)
         {
           for (a = 0; a < N; a++)
           {
            for (b = 0; b < N; b++)
            {
             if (X[i][a] == Y[j][b] && X[j][b] == Y[i][a])
             {
                cnt++;
                break; 
             }
             }
           }
           if (cnt == N)
           {
                Y.erase(Y.begin()+j);
                X.erase(X.begin()+j);
                num = Y.size();
           }
           cnt = 0; 
         }
     }
     cnt = 0; 
     //X-> Y, Y-> -X
     for (i = 0; i < num; i++)
     {
         for (j = i+1; j < num; j++)
         {
           for (a = 0; a < N; a++)
           {
            for (b = 0; b < N; b++)
            {
             if (X[i][a] == Y[j][b] && (X[j][b] + Y[i][a] == N+1))
             {
                cnt++;
                break; 
             }
             }
           }
           if (cnt == N)
           {
                Y.erase(Y.begin()+j);
                X.erase(X.begin()+j);
                num = Y.size();
           }
           cnt = 0; 
         }
     }
     //Printing out solutions. 
     for (i = 0; i < num; i++)
     {
         for (j = 0; j < N; j++)
		 {
             cout << "(" << X[i][j] << ", " << Y[i][j] << ")\t|";
			 for (int l=1; l<=N; l++)
			 {
				 if (l == Y[i][j])
					 cout << " X";
				 else
					 cout <<" O";
			 }
			 cout << endl;
		 }

         cout << endl;
     }

     cout << "Total number of solutions = " << copy << endl; 
     cout << "Total number of unique solutions = " << num << endl; 
}
};

int main()
{
    int n;
    cout << "Enter n where n >= 4: ";
    cin >> n; 
    board B(n);
    B.solve(0); 
    B.uniqueSol();   
    return 0;
}
