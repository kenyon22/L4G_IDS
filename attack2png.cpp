#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/nonfree/features2d.hpp"
//#include "opencv2/nonfree/nonfree.hpp"
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
# include <cstdlib>
# include <iomanip>
# include <fstream>
# include <cmath>
# include <ctime>
# include <cstring>
#include <sstream>
#include <string>
#include <eigen3/Eigen/Dense>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <thread>
#include <iterator>

using namespace std;
using namespace cv;
using namespace Eigen;

class MinMax
{
    public:
        std::string const& operator[](std::size_t index) const
        {
            return m_data[index];
        }
        std::size_t size() const
        {
            return m_data.size();
        }
        void readNextRow(std::istream& str)
        {
            std::string         line;
            std::getline(str, line);

            std::stringstream   lineStream(line);
            std::string         cell;

            m_data.clear();
            while(std::getline(lineStream, cell, ','))
            {
                m_data.push_back(cell);
            }
            // This checks for a trailing comma with no data after it.
            if (!lineStream && cell.empty())
            {
                // If there was a trailing comma then add an empty element.
                m_data.push_back("");
            }
        }
    private:
        std::vector<std::string>    m_data;
};

std::istream& operator>>(std::istream& str, MinMax& data)
{
    data.readNextRow(str);
    return str;
}   
int main(int argc, char** argv)
{
    ifstream myfile;
	myfile.open("KDDTrain+.csv");
    ifstream myfile1;
	myfile1.open("KDDTrain+.csv");
    ifstream myfile2;
	myfile2.open("KDDTest+.csv");
	int Number = 1;
	Mat image = Mat(7,7, CV_8U, double(0));
	string val;
	double Result;
	double max;
	double min;
	double fmax=255;
	double fmin=2;
	double max_arr[41]={0};
	double min_arr[41]={1};

	ofstream myfile3;
	myfile3.open("Train.txt");
	ofstream myfile4;
	myfile4.open("Test.txt");
	int r = 0;
	int c = 0;
	string sub = "";
	string label = "";
	int classify;


    	MinMax              row;
	while(myfile >> row)
    	{
		for(c = 0; c < 42; c++)
		{
		sub = row[c];
		istringstream ss(sub);
		ss >> Result;
		if(Result>max_arr[c]){
        	max_arr[c]=0;
		max_arr[c]=Result;
		}
		if(Result<min_arr[c]){
		min_arr[c]=0;
		min_arr[c]=Result;
		}
		}
		r++;
	}
	
	while(myfile1 >> val || myfile2 >> val )
	{
		r=0;
		c=0;
		sub="";
		int s=1;
		string label = val.substr(0,1);
		istringstream labels(label);
		labels >> classify;
		/*Attack or Normal binary class function
		--------------------------------*/
		if (classify < 5)
		classify = 0;
		else
		classify = 1;
		/*--------------------------------*/

		for(int i = 2; i < val.length(); i++)
		{
			max=max_arr[s];
			min=min_arr[s];
		
			if(val[i] != ','){

				sub += val[i];
			}
			else
			{	
				istringstream convert(sub);
				if ( !(convert >> Result) )	
					Result = 0;
				/*Dufe_n_Weili's function
				--------------------------------*/
				Result=round((log(Result+1)/log(max+1))*255);
				/*------------------------------*/
				image.at<uchar>(r,c) = Result;
				sub = "";
				c++;
				s++;
				if(c == 7)
				{
					r++;
					c = 0;
				}
				
				
			}

		
		}
		string Result;
		ostringstream convert;
		convert << Number;
		Result = convert.str();
		string dataset;
		if(Number <= 125973)
		{
			dataset = "Dataset/Train/" + Result + ".png";
			myfile3 << dataset << " " << classify << endl;
		}
		else
		{
			dataset = "Dataset/Test/" + Result + ".png";
			myfile4 << dataset << " " << classify << endl;
		}
		cout << dataset << endl;
		imwrite(dataset,image);
		

		Number++;

		
	}	
	cout << image << endl;
	waitKey(0);
	return 0;
}
