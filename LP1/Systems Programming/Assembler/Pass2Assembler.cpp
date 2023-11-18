#include <bits/stdc++.h>
using namespace std;

int main()
{

    vector<pair<string, string>> symtab;
    vector<pair<string, string>> littab;

    ifstream sym;
    sym.open("symTable.txt", ios::in);
    string line, word1, word2;
    while (getline(sym, line))
    {
        stringstream ss(line);
        ss >> word1;
        ss >> word2;
        symtab.push_back({word1, word2});
    }

    ifstream lit;
    lit.open("litTable.txt", ios::in);
    // string line, word1,word2;
    while (getline(lit, line))
    {
        stringstream ss(line);
        ss >> word1;
        ss >> word2;
        littab.push_back({word1, word2});
    }

    ifstream fin;
    fin.open("intermediate.txt", ios::in);

    ofstream fout;
    fout.open("machineCode.txt", ios::out);

    vector<string> words;
    string word;
    while (getline(fin, line))
    {
        stringstream ss(line);
        while (ss >> word)
        {
            words.push_back(word);
        }

        if (words[1][1] == 'I' && words[1][2] == 'S')
        {
            fout << words[0] << " " << words[2][0];
            if (words[2].at(1) != ')')
            {
                fout << words[2].at(1) << " ";
            }
            else
            {
                fout << " ";
            }

            if (words.size() == 6)
            {
                fout << words[3][1] << " ";
                if (words[4][1] == 'S')
                {
                    int index = words[5][0] - '0';
                    fout << symtab[index - 1].second << " " << endl;
                }
                if (words[4][1] == 'L')
                {
                    int index = words[5][0] - '0';
                    fout << littab[index - 1].second << " " << endl;
                }
            }

            if (words.size() == 5)
            {
                if (words[3][1] == 'S')
                {
                    int index = words[4][0] - '0';
                    fout << symtab[index - 1].second << " " << endl;
                }
                else
                {
                    fout << words[3].at(1) << " " << words[4].at(1)<<endl;
                }
            }
        }

        words.clear();
    }

    return 0;
}