#include <bits/stdc++.h>
using namespace std;

class Job {
	int id;
	string name;
	int burstTime;
	int arrivalTime;
	int waitingTime;
	int turnAroundTime;
	int completionTime;

public:
	Job() {
		id = 0;
		name = "";
		burstTime = 0;
		waitingTime = 0;
		turnAroundTime = 0;
		arrivalTime = 0;
		completionTime = 0;
	}

	Job(int id, string name, int arrivalTime, int burstTime) {
		this->id = id;
		this->name = name;
		this->burstTime = burstTime;
		this->arrivalTime = arrivalTime;
		waitingTime = 0;
		turnAroundTime = 0;
		completionTime = 0;
	}

	void operator=(const Job& j) {
		this->id = j.id;
		this->name = j.name;
		this->burstTime = j.burstTime;
		this->arrivalTime = j.arrivalTime;
		waitingTime = 0;
		turnAroundTime = 0;
		completionTime = 0;
	}
	friend class Schedular;
};

class Schedular {
	int n;
	Job *processes;
	vector<Job> readyQueue;

public:
	Schedular(int n) {
		this->n = n;
		processes = new Job[n];
	}

	void input() {
		string id, name;
		int at, bt;
		for (int i = 0; i < n; i++) {
			cout<<"Enter arrival time and burst time of P"<<i + 1<<endl;
			cin>>at>>bt;
			Job j(i + 1, "P" + to_string(i + 1), at, bt);
			processes[i] = j;
		}
	}

	void display() {
		cout<<"id\tTa\tTs\tTc\tTtat\tTw"<<endl;
		for (int i = 0; i < n; i++) {
			cout<<processes[i].id<<"\t"<<processes[i].arrivalTime<<"\t"<<processes[i].burstTime<<"\t"<<processes[i].completionTime<<"\t"<<processes[i].turnAroundTime<<"\t"<<processes[i].waitingTime<<endl;
		}

		double sumTat = 0;
		double sumWt = 0;
		for (int i = 0; i < n; i++) {
			sumTat += processes[i].turnAroundTime;
			sumWt += processes[i].waitingTime;
		}

		cout<<"Average turn around time: "<<sumTat / n<<endl;
		cout<<"Average waiting time: "<<sumWt / n<<endl;
	}

	void displayGantt(vector<Job>readyQueue, int currentTime) {
		cout<<"Ready queue at time "<<currentTime<<"sec"<<endl;
		for (int i = 0; i < readyQueue.size(); i++) {
			cout<<readyQueue[i].name<<"("<<readyQueue[i].burstTime<<"sec)"<<"\t";
		}
		cout<<endl<<endl;
	}

	void fisrtComeFirstServe() {
        int totalTime = 0;
        int currentTime = 0;
        int processCompleted = 0;

		sort(processes, processes + n, [] (const Job & lhs, const Job rhs) {
            return lhs.arrivalTime < rhs.arrivalTime;
        });

		for (int i = 0; i < n; i++) {
			totalTime += processes[i].burstTime;
		}

		while (currentTime <= totalTime) {
            if (processCompleted < n && processes[processCompleted].arrivalTime <= currentTime) {
                readyQueue.push_back(processes[processCompleted]);
                processCompleted++;
            }

			this->displayGantt(readyQueue, currentTime);

            if (readyQueue.size() > 0) {
                readyQueue[0].burstTime--;
                if (readyQueue[0].burstTime == 0) {
                    for (int i = 0; i < n; i++) {
                        if (readyQueue[0].id == processes[i].id) {
                            processes[i].completionTime = currentTime + 1;
                            processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
                            processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
                        }
                    }
                    readyQueue.erase(readyQueue.begin());
                }
            }
            currentTime++;
        }

		this->display();
	}

	void shortestJobFirst() {
        int currentTime = 0;
        int processComplete = 0;
        int totalTime = 0;

        sort(processes, processes + n, [] (const Job &lhs, const Job & rhs) {
            return lhs.arrivalTime < rhs.arrivalTime;
        });

        for (int i = 0; i < n; i++) {
            totalTime += processes[i].burstTime;
        }

        while (currentTime <= totalTime) {
            if (processes[processComplete].arrivalTime <= currentTime && processComplete != n) {
                readyQueue.push_back(processes[processComplete]);
                processComplete++;
            }

			sort(readyQueue.begin(), readyQueue.end(), [] (const Job &lhs, const Job & rhs) {
				return lhs.burstTime < rhs.burstTime;
			});

			this->displayGantt(readyQueue, currentTime);

            if (readyQueue.size() > 0) {
                readyQueue[0].burstTime--;
                if (readyQueue[0].burstTime == 0) {
                    for (int i = 0; i < n; i++) {
                        if (readyQueue[0].id == processes[i].id) {
                            processes[i].completionTime = currentTime + 1;
                            processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
                            processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
                        }
                    }
                    readyQueue.erase(readyQueue.begin());
                }
            }
            currentTime++;
        }
		this->display();
	}

	void priority() {
		int totalTime = 0;
        int currentTime = 0;
        int processCompleted = 0;
        int priority[n];

        cout<<"Enter priorities"<<endl;
        for (int i = 0; i < n; i++) {
            cin>>priority[i];
        }

		for (int i = 0; i <= n - 1; i++) {
            for (int j = 0; j <= n - i - 1; j++) {
                if (priority[j] > priority[j + 1]) {
                    swap(priority[j], priority[j + 1]);
                    swap(processes[j], processes[j + 1]);
                }
            }
        }

		for (int i = 0; i < n; i++) {
			totalTime += processes[i].burstTime;
		}

		while (currentTime <= totalTime) {
            if (processCompleted < n) {
                readyQueue.push_back(processes[processCompleted]);
                processCompleted++;
            }

			this->displayGantt(readyQueue, currentTime);

            if (readyQueue.size() > 0) {
                readyQueue[0].burstTime--;
                if (readyQueue[0].burstTime == 0) {
                    for (int i = 0; i < n; i++) {
                        if (readyQueue[0].id == processes[i].id) {
                            processes[i].completionTime = currentTime + 1;
                            processes[i].turnAroundTime = (processes[i].completionTime - processes[i].arrivalTime) > 0 ? processes[i].completionTime - processes[i].arrivalTime : 0;
							processes[i].waitingTime = (processes[i].turnAroundTime - processes[i].burstTime) > 0 ? processes[i].turnAroundTime - processes[i].burstTime : 0;
                        }
                    }
                    readyQueue.erase(readyQueue.begin());
                }
            }
            currentTime++;
        }

		this->display();
	}

	void roundRobin() {
		int totalTime = 0;
		int currentTime = 0;
		int processCompleted = 0;
		int interval;
		int addedBurst = 0;
		Job addedJob;
		addedJob.burstTime = 0;

		cout<<"Enter time interval: ";
		cin>>interval;

		for (int i = 0; i < n; i++) {
			totalTime += processes[i].burstTime;
		}

		sort(processes, processes + n, [] (const Job &lhs, const Job &rhs) {
			return lhs.arrivalTime < rhs.arrivalTime;
		});

		while (currentTime < totalTime) {
			while (processCompleted < n && processes[processCompleted].arrivalTime <= currentTime) {
				readyQueue.push_back(processes[processCompleted]);
				processCompleted++;
			}

			if (addedJob.burstTime > 0) {
				readyQueue.push_back(addedJob);
			}

			if (readyQueue.size() > 0) {
				addedJob = readyQueue[0];
				readyQueue.erase(readyQueue.begin());
				if (addedJob.burstTime > interval) {
					addedJob.burstTime = addedJob.burstTime - interval;
					addedBurst = interval;
				} else {
					addedBurst = addedJob.burstTime;
					addedJob.burstTime = 0;
				}

				if (addedJob.burstTime == 0) {
					for (int i = 0; i < n; i++) {
						if (addedJob.id == processes[i].id) {
							processes[i].completionTime = currentTime + addedBurst;
                            processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
                            processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
						}
					}
				}
			}
			currentTime += addedBurst;
		}
		this->display();
	}
};

int main() {
	int n;
    int choice;
	cout<<"Enter number of processes: ";
	cin>>n;
	Schedular s(n);
	s.input();
	while(true) {
        cout<<"MENU"<<endl;
        cout<<"1.First Come First Serve"<<endl;
        cout<<"2.Shortest Job First"<<endl;
        cout<<"3.Priority"<<endl;
        cout<<"4.Round Robin"<<endl;
        cout<<"5.Exit"<<endl;
        cin>>choice;
        switch (choice) {
            case 1:
            s.fisrtComeFirstServe();
            break;
            
            case 2:
            s.shortestJobFirst();
            break;

            case 3:
            s.priority();
            break;

            case 4:
            s.roundRobin();
            break;

            case 5:
            exit(0);

            default:
            cout<<"Enter valid option"<<endl;
            break;
        }
    }
}