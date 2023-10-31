#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class MNTvalues {
	int PP;
	int KP;
	int MDTP;
	int KPDTP;

public:
	MNTvalues() {
		PP = 0;
		KP = 0;
		MDTP = 0;
		KPDTP = 0;
	}

	friend class MacroProcessor;
};

class MacroProcessor {
	vector<pair<string, MNTvalues>> MNT;
	vector<pair<string, string>> KPDTAB;
	vector<vector<string>> MDT;
    vector<string> PNTAB;
	fstream file;
    fstream macro_name_table;
    fstream keyword_parameter_table;
    fstream macro_definition_table;
    fstream parameter_table;

public:
	MacroProcessor() {
		file.open("macro_input.txt", ios::in);
		if (!file.is_open()) {
			cout<<"Error opening sample file"<<endl;
		}

        macro_name_table.open("macro_name_table.txt", ios::out);
		if (!macro_name_table.is_open()) {
			cout<<"Error opening sample file"<<endl;
		}

        keyword_parameter_table.open("keyword_parameter_table.txt", ios::out);
		if (!keyword_parameter_table.is_open()) {
			cout<<"Error opening sample file"<<endl;
		}

        macro_definition_table.open("macro_definition_table.txt", ios::out);
		if (!macro_definition_table.is_open()) {
			cout<<"Error opening sample file"<<endl;
		}

        parameter_table.open("parameter_table.txt", ios::out);
		if (!parameter_table.is_open()) {
			cout<<"Error opening sample file"<<endl;
		}
	}

    int findParameter(string parameter, string name) {
        int reference;
        for (int i = 0; i < PNTAB.size(); i++) {
            if (PNTAB[i] == name) {
                reference = i;
                break;
            }
        }
        for (int i = reference; i < PNTAB.size(); i++) {
            if (PNTAB[i] == parameter) {
                return i - reference;
            }
        }
        return -1;
    }

	void passOne() {
		vector<string> words;
        vector<string> temp;
		string line;
        string name;
		int kcounter = 0;
		int pcounter = 0;
		int mcounter = 0;
		bool insideMacro = false;
		bool firstLine = false;
        MNTvalues m;
		if (file.is_open()) {
			while (!file.eof()) {
				getline(file, line);
				string w = "";
				for (int i = 0;i < int(line.size()); i++) {
					if (line[i] != ' ') {
						w += line[i];
					} else {
						words.push_back(w);
						w = "";
					}
				}
				words.push_back(w);
				if (words[0] == "MACRO"){
					insideMacro = true;
					firstLine = true;
				} else if (firstLine && insideMacro) {
                    name = words[0];
                    PNTAB.push_back(name);
					for (int i = 1; i < words.size(); i++) {
						if (words[i].at(0) == '&') {
							PNTAB.push_back(words[i]);
							pcounter++;
						} else if (words[i] == "=") {
							if (i != words.size() - 1 && words[i + 1].at(0) != '&') {
								KPDTAB.push_back({words[i - 1], words[i + 1]});
								kcounter++;
							} else if (i == words.size() - 1 || words[i + 1].at(0) == '&'){
								KPDTAB.push_back({words[i - 1], ""});
								kcounter++;
							}
						}
					}
					if (kcounter != 0) {
						m.KPDTP = KPDTAB.size() - kcounter + 1;
					}
					m.KP = kcounter;
					m.PP = pcounter - kcounter;
					m.MDTP = mcounter + 1;
					firstLine = false;
					pcounter = 0;
					kcounter = 0;
					MNT.push_back({words[0], m});
				} else if (!firstLine && insideMacro) {
                    for (int i = 0; i < words.size(); i++) {
                        if(words[i].at(0) == '&') {
                            string parameter = "(P,";
                            parameter += to_string(findParameter(words[i], name));
                            parameter += ")";
                            temp.push_back(parameter);
                        } else {
                            temp.push_back(words[i]);
                        }
                    }
                    MDT.push_back(temp);
                    temp.clear();
                    mcounter++;
                }
                if (words[0] == "MEND") {
					insideMacro = false;
				}
				words.clear();
			}
		} else {
			cout<<"Error opening file"<<endl;
		}
		file.close();
	}

    void displayMNT() {
        for (auto x: MNT) {
            macro_name_table<<x.first<<" "<<x.second.PP<<" "<<x.second.KP<<" "<<x.second.KPDTP<<" "<<x.second.MDTP<<endl;
        }
        macro_name_table.close();
    }

    void displayKPDTAB() {
        for (auto x: KPDTAB) {
            keyword_parameter_table<<x.first<<" "<<x.second<<endl;
        }
        keyword_parameter_table.close();
    }

    void displayMDT() {
        for (int i = 0; i < MDT.size(); i++) {
            for (int j = 0; j < MDT[i].size(); j++) {
                macro_definition_table<<MDT[i][j]<<" ";
            }
            macro_definition_table<<endl;
        }
        macro_definition_table.close();
    }

    void displayPNTAB() {
        for (auto x: PNTAB) {
            parameter_table<<x<<endl;
        }
        parameter_table.close();
    }
};

int main() {
	MacroProcessor m;
	m.passOne();
    m.displayMNT();
    m.displayKPDTAB();
    m.displayMDT();
    m.displayPNTAB();
	return 0;
}