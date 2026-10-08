#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    string sentence;
    vector<string> words;
    string word;

    cout << "Enter a sentence: ";
    getline(cin, sentence);

    stringstream ss(sentence);

    while (ss >> word)
    {
        words.push_back(word);
    }

    cout << "Reversed word order: ";

    for (int i = words.size() - 1; i >= 0; i--)
    {
        cout << words[i] << " ";
    }

    cout << endl;

    return 0;
}
