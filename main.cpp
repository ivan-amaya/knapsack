#include <iostream>
#define max(a,b) a>b?a:b

using namespace std;

int knapsack(int *a,               //the input integers
             int n,                //the number of input integers
             int s,                //knapsack size
             int *subset,          //subset elements
             int &size_of_subset   //the number of items in the subset
);

int main()
{
    int a[] = {5,23,27,37,48,51,63,67,71,75,79,83,89,91,101,112,121,132,137,141,143,147,153,159,171,181,190,191};
    int n = sizeof(a)/sizeof(a[0]); //Number of items in input list
    int s = 595; //knapsack size
    int subset[n] = {0}; //subset of items for knapsack
    int size_of_subset = 0;
    cout << "Knapsack result (sum of elements): " << knapsack(a,n,s,subset,size_of_subset) << endl;
    cout << "Items chosen: ";
    for(int i=0;i<n;i++)
        if(subset[i]==1)
            cout << a[i] << " ";
    cout << endl;
    cout << "Size of the subset: " << size_of_subset;
    return 0;
}

int knapsack(int *a, int n, int s, int *subset, int &size_of_subset)
{
    int matrix[n+1][s+1] = {0};
    int taken[n+1][s+1] = {0};

    // Build table matrix[][] in bottom up manner
    for (int i=1; i<=n; i++)
    {
        for (int j=0; j<=s; j++)
        {
            if (a[i-1] <= j){
                  matrix[i][j] = max(a[i-1] + matrix[i-1][j-a[i-1]],  matrix[i-1][j]);
                  if (a[i-1]+matrix[i-1][j-a[i-1]] > matrix[i-1][j])
                    taken[i][j] = 1;
                  else
                    taken[i][j] = -1;
            }
            else{
                taken[i][j] = -1;
                matrix[i][j] = matrix[i-1][j];
            }
        }
    }

    //Fill the subset array, according to the taken[][] matrix
    int m = n, z = s;
    while(m>0){
        if (taken[m][z]==1){
            m--;
            subset[m] = 1;
            z -= a[m];
        }
        else
            m--;
    }

    //Get size of the subset
    for(int i=0;i<n;i++)
        if(subset[i]==1)
            size_of_subset++;

    //Knapsack result
    return matrix[n][s];
}
