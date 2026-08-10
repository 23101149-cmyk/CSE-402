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
}
;


void performSJF(Process p[], int n) {
    bool done[n];
    fill(done, done + n, false);

    int completed = 0;
    int currentTime = 0;

      while (completed < n) {
        int idx = -1;
        int minBT = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= currentTime) {
                if (p[i].bt < minBT ||
                   (p[i].bt == minBT && p[i].at < p[idx].at)) {
                    minBT = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            int nextArrival = 1e9;
            for (int i = 0; i < n; i++) {
                if (!done[i]) nextArrival = min(nextArrival, p[i].at);
            }
            currentTime = nextArrival;
            continue;
        }

        currentTime += p[idx].bt;
        p[idx].ct = currentTime;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        done[idx] = true;
        completed++;
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

    performSJF(p, n);

    sort(p, p + n, [](const Process &a, const Process &b) {
        return a.pid < b.pid;
    });

    double totalTAT = 0, totalWT = 0;

    cout << left
         << setw(6) << "PID"
         << setw(6) << "AT"
         << setw(6) << "BT"
         << setw(6) << "CT"
         << setw(6) << "TAT"
         << setw(6) << "WT" << "\n";
    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout << left
             << setw(6) << p[i].pid
             << setw(6) << p[i].at
             << setw(6) << p[i].bt
             << setw(6) << p[i].ct
             << setw(6) << p[i].tat
             << setw(6) << p[i].wt << "\n";
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    cout << "\n";
    cout << fixed << setprecision(2);
    cout << "Average Turnaround Time: " << (totalTAT / n) << "\n";
    cout << "Average Waiting Time: " << (totalWT / n) << "\n";

    return 0;
}
