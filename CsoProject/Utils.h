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

    static int randint(int lower, int upper)
    { // returns a random integer between lower and upper
        return lower + rand() % (upper - lower + 1);
    }
    
    static double randdouble(double a, double b) { //retorna un random double entre a y b
        return a + (b - a) * rand() / ((double) RAND_MAX);
    }
    static int initialize_randomness(int seed)
    { // initializes the seed, if seed is -1 then it uses system time as seed
        int seed1;
        time_t* tp;
        tp = NULL;
        if(seed == -1)
            seed1 = time(tp);
        else
            seed1 = seed;
        srand(seed1);
        return seed1;
    }
};
