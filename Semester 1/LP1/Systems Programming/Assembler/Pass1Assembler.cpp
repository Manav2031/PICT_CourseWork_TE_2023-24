#include <bits/stdc++.h>
using namespace std;

int main()
{
    map<string, pair<string, string>> opcode;

    opcode["STOP"] = {"IS", "00"};
    opcode["ADD"] = {"IS", "01"};
    opcode["SUB"] = {"IS", "02"};
    opcode["MULT"] = {"IS", "03"};
    opcode["MOVER"] = {"IS", "04"};
    opcode["MOVEM"] = {"IS", "05"};
    opcode["COMP"] = {"IS", "06"};
    opcode["BC"] = {"IS", "07"};
    opcode["DIV"] = {"IS", "08"};
    opcode["READ"] = {"IS", "09"};
    opcode["PRINT"] = {"IS", "10"};
    opcode["START"] = {"AD", "01"};
    opcode["END"] = {"AD", "02"};
    opcode["ORIGIN"] = {"AD", "03"};
    opcode["EQU"] = {"AD", "04"};
    opcode["LTORG"] = {"AD", "05"};
    opcode["DC"] = {"DL", "02"};
    opcode["DS"] = {"DL", "01"};

    opcode["AREG"] = {"1", ""};
    opcode["BREG"] = {"2", ""};
    opcode["CREG"] = {"3", ""};
    opcode["DREG"] = {"4", ""};

    opcode["LT"] = {"1", ""};
    opcode["LE"] = {"2", ""};
    opcode["EQ"] = {"3", ""};
    opcode["GT"] = {"4", ""};
    opcode["GE"] = {"5", ""};
    opcode["ANY"] = {"6", ""};

    ifstream fin;
    fin.open("input.txt");

    ofstream fout;
    fout.open("output.txt");

    string line, word;
    map<string, pair<int, string>> symtab;
    vector<pair<string, int>> littab;
    vector<string> pooltab;

    int litindex = 0;
    int lc = -1;
    while (getline(fin, line))
    {
        stringstream st(line);
        st >> word;
        string label = "";

        if (opcode.count(word) == 0)
        {
            if (symtab.count(word) == 0)
            {
                symtab[word] = {lc, to_string(symtab.size() + 1)};
            }
            else
            {
                symtab[word].first = lc;
            }
            label = word;
            st >> word;
        }

        string operation = word;
        if (operation == "START")
        {
            fout << "    ";
            fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";

            st >> word;
            fout << "( C, " << word << ") ";
            lc = stoi(word);
        }
        else if (operation == "END")
        {
            fout << "    ";
            fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";
            fout << endl;
            pooltab.push_back("#" + to_string(litindex + 1));
            for (; litindex < littab.size(); litindex++)
            {
                fout << lc << " ";
                fout << "( " << opcode["DC"].first << ", " << opcode["DC"].second << ") ";
                littab[litindex].second = lc;
                string literal = littab[litindex].first;
                string sublit = literal.substr(2, literal.length() - 3);
                fout << "( C, " << sublit << ") ";
                fout << endl;
                lc++;
            }
        }
        else if (operation == "LTORG")
        {
            fout << "    ";
            fout << "( " << opcode[word].first << ", " << opcode[word].second << ") ";
            fout << endl;
            pooltab.push_back("#" + to_string(litindex + 1));
            for (; litindex < littab.size(); litindex++)
            {
                fout << lc << " ";
                fout << "( " << opcode["DC"].first << ", " << opcode["DC"].second << ") ";
                littab[litindex].second = lc;
                string literal = littab[litindex].first;
                string sublit = literal.substr(2, literal.size() - 3);
                fout << "(C, " << sublit << ") ";
                fout << endl;
                lc++;
            }
        }
        else if (operation == "EQU")
        {
            fout << "    ";
            fout << "No IC generated";
            fout << endl;
            st >> word;
            int plusminusindex = 0;
            for (int i = 0; i < word.length(); i++)
            {
                if (word[i] == '+' || word[i] == '-')
                {
                    plusminusindex = i;
                    break;
                }
            }
            char plusminus = '0';
            string aftersign;
            string beforesign;
            if (plusminusindex != 0)
            {
                plusminus = word[plusminusindex];
                aftersign = word.substr(plusminusindex + 1);
                beforesign = word.substr(0, plusminusindex);
            }
            else
            {
                beforesign = word.substr(0, word.length());
            }
            symtab[label].first = symtab[beforesign].first;

            if (plusminus == '+')
            {
                symtab[label].first += stoi(aftersign);
            }
            else
            {
                symtab[label].first -= stoi(aftersign);
            }
        }
        else if (operation == "ORIGIN")
        {
            fout << "    ";
            fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";
            st >> word;
            int plusminusindex = 0;
            for (int i = 0; i < word.length(); i++)
            {
                if (word[i] == '+' || word[i] == '-')
                {
                    plusminusindex = i;
                    break;
                }
            }
            char plusminus = '0';
            string beforesign, aftersign;
            if (plusminusindex != 0)
            {
                plusminus = word[plusminusindex];
                aftersign = word.substr(plusminusindex + 1);
                beforesign = word.substr(0, plusminusindex);
            }
            else
            {
                beforesign = word.substr(0, word.length());
            }
            lc = symtab[beforesign].first;
            fout << "(S , " << symtab[beforesign].second << ")";

            if (plusminus == '+')
            {
                lc += stoi(aftersign);
                fout << "+" << aftersign << "\n";
            }
            else if (plusminus == '-')
            {
                lc -= stoi(aftersign);
                fout << "-" << aftersign << "\n";
            }
        }
        else
        {
            fout << lc << " ";
            fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";

            while (st >> word)
            {
                if (operation == "DC")
                {
                    word = word.substr(1, word.length() - 2);
                    fout << "(C, " << word << ") ";
                }
                else if (operation == "DS")
                {
                    fout << "(C, " << word << ") ";
                    lc+=stoi(word)-1;
                }
                else if (word[0] == '=')
                {
                    littab.push_back({word, lc});
                    fout << "(L, " << littab.size() << ") ";
                }
                else if (opcode.count(word) > 0)
                {
                    fout << "(" << opcode[word].first << ") ";
                }
                else
                {
                    if (symtab.count(word) == 0)
                    {
                        symtab[word] = {lc, to_string(symtab.size() + 1)};
                    }
                    fout << "(S, " << symtab[word].second << ") ";
                }
            }
            lc++;
        }
        fout << endl;
    }
    fin.close();
    fout.close();

   for(auto i :symtab){
    cout<<i.first <<"\t" <<i.second.first<<endl;
   }

    ofstream sout;
    sout.open("sym.txt");

    for (auto i : symtab)
    {
        sout << i.first << " " << i.second.first;
        sout << endl;

        
    }

    sout.close();

    ofstream lout;
    lout.open("lit.txt");

    for (auto i : littab)
    {
        lout << i.first << " " << i.second;
        lout << endl;
    }

    lout.close();

    ofstream pout;
    pout.open("pool.txt");

    for (auto i : pooltab)
    {
        pout << i;
        pout << endl;
    }

    pout.close();

    cout << "\nProgram Excuted!!" << endl;

    return 0;
}