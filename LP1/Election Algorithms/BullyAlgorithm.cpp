#include <iostream>
 #include <vector>
 using namespace std;

 class BullyElection {
 private:
     int total;
     vector<bool> state;

 public:
     BullyElection(int total_process) {
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
         if (pos > total) {
             return;
         }

         if (!state[pos - 1]) {
             cout << "p" << pos << " cannot start election as it is down" << endl;
             return;
         }

         cout << "Election started by p" << pos << endl;

         for (int i = pos; i < total; ++i) {
             cout << "Election message sent p" << pos << " to p" << i + 1 << endl;
         }

         for (int i = pos; i < total; ++i) {
             if (state[i]) {
                 cout << "p" << i + 1 << " responds OK to p" << pos << endl;
             }
         }

         for (int i = pos; i < total; ++i) {
             if (state[i]) {
                 Election(i + 1);
                 return;
             }
         }

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
     BullyElection algo(5);
     algo.down(5);
     algo.down(2);
     // algo.down(4);
     // algo.down(3);
     algo.Election(1);

     return 0;
 }