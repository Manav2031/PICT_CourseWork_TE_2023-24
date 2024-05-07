#include<bits/stdc++.h>
using namespace std;

void setData(map<string,string> &data)
{
    ifstream in("data.txt");
    string key, value;
    while (in >> key >> value)
    {
        replace(value.begin(), value.end(), '_', ' ');
        transform(key.begin(), key.end(), key.begin(), ::tolower);
        data[key] = value;
    }
    in.close();
}

int main()
{
    map<string,string>data;
    setData(data);

    cout << endl
         << "PICT Chatboat: How can I help you today!" << endl;

    string input;

    ofstream file;
    while (true)
    {
        cout << "\nYou: ";
        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        input.erase(remove_if(input.begin(), input.end(), [](unsigned char c)
                              { return isspace(c); }),
                    input.end());

        bool found = false;
        for (const auto &x : data)
        {
            if (input.find(x.first) != string::npos)
            {
                cout << "\nChatBot: " << data[x.first] << endl;
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "ChatBot: Data is not present in the data set! Please provide the answer. Enter the data in key value pairs." << endl;

            string str1, str2;
            cout << "Key: ";
            getline(cin, str1);
            cout << "Value: ";
            getline(cin, str2);
            str1.erase(remove_if(str1.begin(), str1.end(), [](unsigned char c)
                                 { return isspace(c); }),
                       str1.end());
            transform(str1.begin(), str1.end(), str1.begin(),::tolower);
            data[str1] = str2;

            replace(str2.begin(), str2.end(), ' ', '_');
            file.open("data.txt", ios::app);
            if (file.is_open())
            {

                file << endl
                     << str1 << " " << str2;
                file.close();
            }
            else
            {
                cout << "Failed to open file." << endl;
            }
            cout << "  Data remembered ! " << endl;
            found = false;
        }
    }
    return 0;
}