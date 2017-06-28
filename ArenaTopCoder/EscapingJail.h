#include <vector>
#include <string>

//#define toDigit(c) (c-'0')

using namespace std;

int i,j,k;
vector<vector<int> > ady;

inline int toDigit(char x)
{
    int r = int(x);
    if(r >= 48 && r <= 57) {
        r -= 48;
    } else if(r >= 65 && r <= 90) {
        r -= 29;
    } else if(r >= 97 && r <= 122) {
        r -= 87;
    } else if(x == ' ') {
        r = 62; // infinite
    }
    return r;
}

class EscapingJail
{
public:
    int getMaxDistance(vector<string> chain)
    {
        int cn = chain.size();
        

        ady.resize(cn, vector<int>(cn));
        
        for(i = 0; i < cn; i++) {
            for(j = 0; j < cn; j++) {
                ady[i][j]=62;// infinito
            }
        }
        
        for(i = 0; i < cn; i++) {
            for(j = 0; j < (int)chain[i].size(); j++) {
                ady[i][j]=toDigit(chain[i][j]);
            }
        }

        int min = floydWarshall(cn, ady);

        return min;
    }


    int floydWarshall(int cn, vector<vector<int> >& ady)
    {
        
        for(k = 0; k < cn; k++)
            for(i = 0; i < cn; i++)
                for(j = 0; j < cn; j++) {
                    int dt = ady[i][k] + ady[k][j];
                    if(ady[i][j] > dt)
                    {
                        ady[i][j] = dt;
                    }
                }
                 
        int r = -1;
        for(i=0; i<cn;i++)
        {
            for(j=0; j<cn; j++)
            {
                if(r<ady[i][j] || r==-1)
                {
                    r=ady[i][j];
                }
            }
        }
        
        return r==62?-1:r;
    }
};