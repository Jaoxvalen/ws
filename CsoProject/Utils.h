#pragma once
#include <string>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Utils
{
public:
    static vector<string> split(const string& text, char sep)
    {
        vector<string> tokens;
        size_t start = 0, end = 0;
        while((end = text.find(sep, start)) != string::npos) {
            tokens.push_back(text.substr(start, end - start));
            start = end + 1;
        }
        tokens.push_back(text.substr(start));
        return tokens;
    }
    
    static void getWord(ifstream &fichero, string &line)
    {
        line="";
        char c=' ';
        bool scaning=false;
        while( (c==' ' || c=='\n' || c=='\r') || scaning)
        {
            fichero.get(c);
            if(c!=' ' && c!='\n' && c!='\r')
            {
                scaning=true;
                line+=c;
            }
            else
            {
                if(scaning)
                {
                    break;
                }
            }
        }
    }
};
