#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "signatures.h"
#include "iostream"
#include <vector>
#include <fstream>

//function to read data into 
void readData(string filename);

//discharge and precipitation inputs
vector<double> discharge;
vector<double> precip;

void main(int argc, char* argv[]) {
	
	//read in input data
	readData("E:/Dropbox/code_tools/Signatures/C++/exampleData.txt");

	//create an instance of class Signatures
	Signatures sigs;

	//calculate different signatures, see signatures.h for parameters
	sigs.runoffCoefficient(discharge, precip);
	sigs.varianceRatio(discharge, precip);
	sigs.limbDensities(discharge);
	sigs.slopeFDC(discharge, 0.33, 0.66);
	sigs.slopePeakDist(discharge, 0.1, 0.5);

	std::cout<<"Runoff Coefficient: "<<sigs.RC<<std::endl;
	std::cout<<"Variance Ratio: "<<sigs.VR<<std::endl;
	std::cout<<"Rising Limb Denisty: "<<sigs.RLD<<std::endl;
	std::cout<<"Falling Limb Density: "<<sigs.FLD<<std::endl;
	std::cout<<"Slope of FLow Duration Curve: "<<sigs.SFDC<<std::endl;
	std::cout<<"Slope Peak Distribution: "<<sigs.SPD<<std::endl;
          	
}

//function to read the precipitation and discharge data in order to calculate  the signatures
void readData(string filename){

	char junk[30];
	double temp;
	int len;

	std::ifstream indata(filename, std::ios::in);
	
	indata>>junk;
	indata>>len;

	indata >> junk;
	indata >> junk;
	
	for (int i = 0; i <len; i++){
		indata >> temp;
		precip.push_back(temp);
		indata >> temp;
		discharge.push_back(temp);
	}

	indata.close();

} //end of readCatchmentData
