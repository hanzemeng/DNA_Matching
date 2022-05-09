#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <fstream>

using namespace std;

double m = 2;
double c = -0.5;
double d = -1;
string s1, s2;
void setup(int argc, char** argv);


int main(int argc, char** argv)
{
    setup(argc, argv);

    int n1 = s1.size();
    int n2 = s2.size();
    vector<vector<double>> dp(n1+1, vector<double>(n2+1, 0));

    for(int i=0; i<=n1; i++)
    {
        dp[i][0] = i*d;
    }
    for(int i=0; i<=n2; i++)
    {
        dp[0][i] = i*d;
    }

    for(int i=1; i<=n1; i++)
    {
        for(int j=1; j<=n2; j++)
        {
            if(s1[i-1] == s2[j-1])
            {
                dp[i][j] = dp[i-1][j-1]+m;
            }
            else
            {
                double temp = max(dp[i-1][j]+d, dp[i][j-1]+d);
                dp[i][j] = max(dp[i-1][j-1]+c, temp);
            }
        }
    }

    string res1 = "";
    string res2 = "";
    int i=n1;
    int j=n2;
    while(i!=0 && j!=0)
    {
        if(s1[i-1] == s2[j-1])
        {
            res1 += s1[i-1];
            res2 += s2[j-1];
            i--;
            j--;
        }
        else if(dp[i-1][j-1]+c == dp[i][j])
        {
            res1 += s1[i-1];
            res2 += "R";
            i--;
            j--;
        }
        else if(dp[i-1][j]+d == dp[i][j])
        {
            res1 += s1[i-1];
            res2 += "_";
            i--;
        }
        else if(dp[i][j-1]+d == dp[i][j])
        {
            res1 += "_";
            res2 += s2[j-1];
            j--;
        }
    }

    while(i>0)
    {
        res1 += s1[i-1];
        res2 += "_";
        i--;
    }
    while(j>0)
    {
        res1 += "_";
        res2 += s2[j-1];
        j--;
    }
    
    
    reverse(res1.begin(), res1.end());
    reverse(res2.begin(), res2.end());

    ofstream outFile;
    outFile.open("out.txt");
    outFile << dp[n1][n2] << endl;
    outFile << res1 << endl;
    outFile << res2 << endl;
/*
    for(int i=0; i<=n1; i++)
    {
        for(int j=0; j<=n2; j++)
        {
            cout << dp[i][j] << ", ";
        }
        cout << endl;
    }
*/
    return 0;
}

void setup(int argc, char** argv)
{
    int temp;
    char* file1;
    char* file2;
    while ((temp = getopt(argc, argv, "m:c:d:1:2:")) != -1)
    {
        switch (temp)
        {
            case 'm':
                m = atof(optarg);
                break;
            case 'c':
                c = atof(optarg);
                break;
            case 'd':
                d = atof(optarg);
                break;
            case '1':
                file1 = optarg;
                break;
            case '2':
                file2 = optarg;
                break;
        }
    }
    ifstream inputFile;
    inputFile.open(file1);
    getline(inputFile, s1);
    inputFile.close();
    inputFile.open(file2);
    getline(inputFile, s2);
    inputFile.close();
}
