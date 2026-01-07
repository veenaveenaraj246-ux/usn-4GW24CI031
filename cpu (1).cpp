#include <iostream>
using namespace std;

// FCFS Scheduling
void fcfs(int n, int bt[]) {
    int wt[n], tat[n];
    wt[0] = 0;

    for (int i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];

    for (int i = 0; i < n; i++)
        tat[i] = wt[i] + bt[i];

    cout << "\n--- FCFS Scheduling ---\n";
    cout << "Process\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
}

// SJF Scheduling (Non-Preemptive)
void sjf(int n, int bt[]) {
    int temp[n], wt[n], tat[n];

    for (int i = 0; i < n; i++)
        temp[i] = bt[i];

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = wt[i - 1] + temp[i - 1];

    for (int i = 0; i < n; i++)
        tat[i] = wt[i] + temp[i];

    cout << "\n--- SJF Scheduling ---\n";
    cout << "Process\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t" << temp[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
}

// Priority Scheduling
void priority(int n, int bt[], int pr[]) {
    int wt[n], tat[n];

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (pr[i] > pr[j]) {
                swap(pr[i], pr[j]);
                swap(bt[i], bt[j]);
            }
        }
    }

    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];

    for (int i = 0; i < n; i++)
        tat[i] = wt[i] + bt[i];

    cout << "\n--- Priority Scheduling ---\n";
    cout << "Process\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
}

// Round Robin Scheduling
void roundRobin(int n, int bt[], int tq) {
    int rem[n], wt[n] = {0};
    for (int i = 0; i < n; i++)
        rem[i] = bt[i];

    int time = 0;
    while (true) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (rem[i] > 0) {
                done = false;
                if (rem[i] > tq) {
                    time += tq;
                    rem[i] -= tq;
                } else {
                    time += rem[i];
                    wt[i] = time - bt[i];
                    rem[i] = 0;
                }
            }
        }
        if (done)
            break;
    }

    cout << "\n--- Round Robin Scheduling ---\n";
    cout << "Process\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t" << bt[i] << "\t" << wt[i] << "\t" << wt[i] + bt[i] << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int bt[n], pr[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> bt[i];
    }

    int choice;
    cout << "\n1. FCFS\n2. SJF\n3. Priority\n4. Round Robin\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
        fcfs(n, bt);
    else if (choice == 2)
        sjf(n, bt);
    else if (choice == 3) {
        for (int i = 0; i < n; i++) {
            cout << "Enter Priority for P" << i + 1 << ": ";
            cin >> pr[i];
        }
        priority(n, bt, pr);
    } else if (choice == 4) {
        int tq;
        cout << "Enter Time Quantum: ";
        cin >> tq;
        roundRobin(n, bt, tq);
    } else
        cout << "Invalid choice";

    return 0;
}
