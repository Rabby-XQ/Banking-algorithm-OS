#include <iostream>
using namespace std;

const int MAX = 10;

int main()
{
    int n, m, i, j, k;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resources: ";
    cin >> m;

    int alloc[MAX][MAX], max[MAX][MAX], avail[MAX];
    int need[MAX][MAX], finish[MAX], safeSeq[MAX];
    int work[MAX];

    cout << "\nEnter Allocation Matrix:\n";
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "\nEnter Maximum Matrix:\n";
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            cin >> max[i][j];

    cout << "\nEnter Available Resources:\n";
    for (i = 0; i < m; i++)
        cin >> avail[i];

    // Calculate Need Matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Initialize Finish and Work arrays
    for (i = 0; i < n; i++)
        finish[i] = 0;
    for (i = 0; i < m; i++)
        work[i] = avail[i];

    // Banker's Algorithm
    int count = 0;
    while (count < n)
    {
        bool found = false;
        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == m)
                {
                    for (k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }

        if (!found)
        {
            cout << "\nSystem is in **unsafe state** (Deadlock may occur).\n";
            return 1;
        }
    }

    cout << "\nSystem is in a **safe state**.\nSafe sequence: ";
    for (i = 0; i < n; i++)
        cout << "P" << safeSeq[i] << " ";
    cout << endl;

    return 0;
}
