#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <string>
#include <sstream>
#include "../headers/Eigen/Dense"
#include "../headers/Eigen/src/LU/Inverse.h"

using namespace std;
using namespace Eigen;

int poly=6;
int num_rows;

int main()
{
        cout.precision(8);
        cout.setf(ios::fixed);
        vector <long double> Tsigma;
        vector <long double> sigma;
        num_rows = 0;
        ifstream fin("data.dat");
        vector<vector <long double> > allData;
        string line;
        while(getline(fin,line))
        {
                vector<long double> lineData;
                long double val;
                istringstream lineStream(line);
                while (lineStream >> val)
                {
                        lineData.push_back(val);
                }
                allData.push_back(lineData);
                ++num_rows;
        }

        for (int i=0; i<num_rows; i++)
        {
                Tsigma.push_back(allData[i][0]);
                sigma.push_back(allData[i][1]);
        }



        MatrixXd Y(num_rows,1);
        for (int i = 0; i < num_rows; i++)
        {
                Y(i) = sigma[i];
        }

        MatrixXd X(num_rows,poly+1);
        for (int i = 0; i < num_rows; i++)
        {
                for (int j = 0; j <= poly; j++)
                {
                        X(i,j) = pow(Tsigma[i],j);
                }
        }

        MatrixXd TXX(poly+1,num_rows);
        TXX = X.transpose()*X;

        MatrixXd TXY(poly+1,1);
        TXY = X.transpose()*Y;

        MatrixXd beta(poly+1,1);
        beta = TXX.inverse()*TXY;

        cout << "beta\n" << scientific;
        cout << beta << endl;
        return 0;
}
