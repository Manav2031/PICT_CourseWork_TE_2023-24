#include <bits/stdc++.h>
using namespace std;
#define ll long long
vector<string> word(string s)
{
  vector<string> ans;
  string x = "";
  for (int i = 0; i < s.size(); ++i)
  {
    if (s[i] == ' ')
    {
      ans.push_back(x);
      x = "";
      continue;
    }
    x += s[i];
  }
  ans.push_back(x);
  return ans;
}

int strint(string s)
{
  int num = 0;
  for (int i = 0; i < s.size(); ++i)
  {
    num *= 10;
    num += s[i] - '0';
  }
  return num;
}
class pass2
{

  // input
  vector<string> mdt;
  vector<string> kpdtab;
  vector<string> mnt;

public:
  pass2()
  {

    // Input Data structure
    fstream file;
    string s;

    file.open("MDT.txt", ios::in);
    while (getline(file, s))
      mdt.push_back(s);
    file.close();

    file.open("MNT.txt", ios ::in);
    while (getline(file, s))
      mnt.push_back(s);
    file.close();

    file.open("KPDTAB.txt", ios ::in);
    while (getline(file, s))
      kpdtab.push_back(s);
    file.close();
  }

  void mainpass2(string s)
  {
    // output
    vector<string> aptab;

    vector<string> call = word(s);

    // find the macro name in MNT
    string x = "";
    for (auto child : mnt)
    {
      if (word(child)[0] == call[0])
      {
        x = child;
        break;
      }
    }
    vector<string> word1 = word(x);
    int pp = strint(word1[1]);
    int kp = strint(word1[2]);
    int mdt_index = strint(word1[3]);
    int kpdp_index = strint(word1[4]);

    // push the position parameter as it is
    for (int i = 1; i <= pp; ++i)
    {
      aptab.push_back(call[i]);
    }

    // Now to find the Keyword parameter

    // 1 ) I have taken temporary KPTAB (to get in pair format)
    vector<pair<string, string>> temp_kptab;
    for (int i = kpdp_index - 1; i < kp + (kpdp_index - 1); ++i)
    {
      string a = "";
      string b = "";
      vector<string> mn = word(kpdtab[i]);
      a = mn[0];
      if (mn.size() == 2)
      {
        b += mn[1];
      }
      temp_kptab.push_back({a, b});
    }

    // 2 ) Replace the default parameter with actual parameter
    for (int i = pp + 1; i < call.size(); ++i)
    {
      string key = "";
      string para = "";
      string keypara = call[i];
      ll key_f = 0;

      // break Keyword parameter into name_of_parameter : value_of_parameter
      for (int j = 0; j < keypara.size(); ++j)
      {
        if (keypara[j] == '&')
        {
          key_f = 0;
          continue;
        }
        if (keypara[j] == '=')
        {
          key_f = 1;
          continue;
        }
        if (key_f == 0)
          key += keypara[j];
        else
          para += keypara[j];
      }

      // Replace
      for (auto &x : temp_kptab)   //  Here & is Important to acess the address for replacement
      {
        if (x.first == key)
          x.second = para;
      }
    }

    // push the keyword parameter in Aptab
    for (auto &x : temp_kptab)
    {
      aptab.push_back(x.second);
    }

    // Expanded code
    vector<string> expanded;
    int i = mdt_index - 1;
    while (1)
    {
      vector<string> single_expand = word(mdt[i]);
      string line = "+";
      // (P,3) (P,2)
      // 01234
      for (int j = 0; j < single_expand.size(); ++j)
      {
        line += " ";
        string y = single_expand[j];
        if (j == 0)
        {
          line += y;
          continue;
        }
        if (y[1] == 'P')
        {
          string idx = "";
          idx += y[3];
          line += aptab[strint(idx) - 1];
        }
        else
        {
          line += y;
        }
      }
      expanded.push_back(line);
      if (single_expand.size() == 1)
        break;
      i++;
    }

    // final output
    cout << "  APTAB   \n";
    i = 1;
    for (auto x : aptab)
    {
      cout << i << " )  " << x << endl;
      i++;
    }
    cout << "Expanded Code : \n";
    for (auto x : expanded)
    {
      cout << x << endl;
    }
    cout << " \n\n\n ";
  }
  void calls()
  {
    fstream file;
    string s;
    file.open("call.txt", ios ::in);
    vector<string> callx;
    while (getline(file, s))
    {
      callx.push_back(s);
    }
    file.close();
    for (auto x : callx)
    {
      mainpass2(x);
    }
  }
};

int main()
{
  pass2 p1;
  p1.calls();
  return 0;
}