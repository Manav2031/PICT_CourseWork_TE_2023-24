#include <bits/stdc++.h>
using namespace std;

class RingElection {
private:
    int total;
    vector<bool> state;

public:
    RingElection(int total_process) {
        total = total_process;
        state = vector<bool>(total, true);
    }

    void up(int pos) {
        state[pos - 1] = true;
    }

    void down(int pos) {
        state[pos - 1] = false;
    }

    void Election(int pos) {
        if (!state[pos - 1]) {
            cout << "p" << pos << " cannot start election as it is down" << endl;
            return;
        }

        cout << "Election started by p" << pos << endl;

        int start = pos - 1;
        int ptr = (start + 1) % total;
        int last_true = start;

        while (ptr != start) {
            if (state[ptr]) {
                cout << "p" << last_true + 1 << " sends election message to p" << ptr + 1 << endl;
                last_true = ptr;
            }

            ptr = (ptr + 1) % total;
        }

        cout << "p" << last_true + 1 << " sends election message to p" << start + 1 << endl;

        int max_process = -1;
        for (int i = total - 1; i >= 0; --i) {
            if (state[i]) {
                max_process = i;
                break;
            }
        }

        cout << "Election is won by: p" << max_process + 1 << endl;
        cout << "p" << max_process + 1 << " informs everyone that it is the new coordinator" << endl;
    }
};

int main() {
    int n;cout<<"Enter no. of nodes: ";cin>>n;
    RingElection algo(n);
    algo.down(n);
    // algo.down(2);
    // algo.down(4);
    // algo.down(3);
    algo.Election(n-1);

    return 0;
}