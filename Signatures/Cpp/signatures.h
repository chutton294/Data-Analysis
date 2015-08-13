
#ifndef SIGNATURES_H
#define SIGNATURES_H

#include <vector>
#include <string>
#include "ranker.h"
#include "limits.h"


class Signatures {

public:

	//signatures as data members
	double RC; //Runoff Coefficient
	double VR; //Variance Ratio
	double RLD; //Rising Limb Density
	double FLD; //Falling Limb Density
	double SFDC; //slope of the Flow Duration Curve
	double SPD; //slope of the Peak Distribution

	
    //Basic Vector calculations
    static double computeSum(vector<double> g);
    static double computeMax(vector<double> g);
    static double computeMin(vector<double> g);
    static double computeMean(vector<double> g);
    static double computeVariance(vector<double> g);

	//signature calculation Member Functions

	    //q = discharge
	    //r = rainfall/precipitation

		//Runoff Coefficient
		void runoffCoefficient(vector<double> q, vector<double> r);
    
		//Variance Ratio
	  void varianceRatio(vector<double> q, vector<double> r);

		//Rising and falling limb densities
		void limbDensities(vector<double> q);

		//Slope of flow duration curve between lower (ql) and upper (qu) quantiles
		void slopeFDC(vector<double> q, double ql, double qu);

		//Slope peak distribution between lower and upper quantiles
		void slopePeakDist(vector<double> q, double ql, double qu);
   
		bool isIndeterminate(double val);

		bool isInfinite(double val);

};


#endif // SIGNATURES_H
