#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};


void performFCFS(Process p[], int n) {
     sort(p, p + n, [](const Process &a, const Process &b) {
        if (a.at != b.at) return a.at < b.at;
        return a.pid < b.pid;
    });

    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at) {
            currentTime = p[i].at;
        }

        currentTime += p[i].bt;
        p[i].ct = currentTime;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

int main() {
    int n = 5;
    Process p[5] = {
        {1, 3, 3, 0, 0, 0},
        {2, 2, 5, 0, 0, 0},
        {3, 5, 4, 0, 0, 0},
        {4, 1, 3, 0, 0, 0},
        {5, 6, 2, 0, 0, 0}
    };

    performFCFS(p, n);

    // Sort by pid for display
    sort(p, p + n, [](const Process &a, const Process &b) {
        return a.pid < b.pid;
    });

    double totalTAT = 0, totalWT = 0;

    cout << left
         << setw(6)  << "PID"
         << setw(6)  << "AT"
         << setw(6)  << "BT"
         << setw(6)  << "CT"
         << setw(6)  << "TAT"
         << setw(6)  << "WT" << "\n";
    cout << "--------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << left
             << setw(6) << p[i].pid
             << setw(6) << p[i].at
             << setw(6) << p[i].bt
             << setw(6) << p[i].ct
             << setw(6) << p[i].tat
             << setw(6) << p[i].wt << "\n";
        totalTAT += p[i].tat;
        totalWT  += p[i].wt;
    }

    cout << "--------------------------------\n";
    cout << fixed << setprecision(2);
    cout << "Average Turnaround Time: " << (totalTAT / n) << "\n";
    cout << "Average Waiting Time:    " << (totalWT / n) << "\n";

    return 0;
}
