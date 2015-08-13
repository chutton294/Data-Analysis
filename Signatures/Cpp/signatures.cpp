
#include "signatures.h"
#include <cfloat>
#include <math.h>
#include <cmath>
#include <limits>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#define isinf(x) (!_finite(x))


double Signatures::computeSum(vector<double> g){
    double z = 0.0;
    for(unsigned int i=0; i<g.size(); i++){
        z = z + g[i];
    }
    return z;
}

double Signatures::computeMax(vector<double> g){
    double m = -1*numeric_limits<double>::max( );
    for(unsigned int i=0; i<g.size(); i++){
        if(g[i]>m){
            m = g[i];
        }
    }
    return m;
}

double Signatures::computeMin(vector<double> g){
    double m = numeric_limits<double>::max( );
    for(unsigned int i=0; i<g.size(); i++){
        if(g[i]<m){
            m = g[i];
        }
    }
    return m;
}

double Signatures::computeMean(vector<double> g){
    double z = computeSum(g)/g.size();
    return z;
}

double Signatures::computeVariance(vector<double> g){
    double v = 0.0;
    double M = computeMean(g);
    for(unsigned int i=0; i<g.size(); i++){
        v += ( g[i]-M )*( g[i]-M );
    }
    return v/g.size();
}

void Signatures::runoffCoefficient(vector<double> q, vector<double> r){

	RC = computeMean(q)/computeMean(r);

	//if (isinf(RC)) RC = 0;
	
}

 void Signatures::varianceRatio(vector<double> q, vector<double> r){

	 VR = computeVariance(q)/computeVariance(r);
	 
	 //if (isinf(VR)) VR = 0;
 }

 void Signatures::limbDensities(vector<double> q){

	 int nPeaks = 0;
	 int nRising = 0;
	 int nFalling = 0;
	 unsigned int end = q.size() - 1;
	 
	 for(unsigned int i=1; i<end; i++){
		 
		 if(q[i] > q[i-1]){ 
			 nRising += 1;
			 if(q[i] > q[i+1]){
				 nPeaks += 1;
			 }
		 }
		 
		 if(q[i] > q[i+1]){ 
			 nFalling += 1;
		 }

	 }
	
	 if(nRising > 0) RLD = nPeaks/(double)nRising;
	 if(nFalling > 0) FLD = nPeaks/(double)nFalling;

	 	
  } //end of function limbDensities

 void Signatures::slopeFDC(vector<double> q, double ql, double qu){
	 
	 SFDC = 0;
	 if (q.size() > 0){
		 double pLower = quantile(q, (1 - ql));
		 double pUpper = quantile(q, (1 - qu));
		 SFDC = (log(pLower) - log(pUpper)) / ((qu - ql) * 100);
	 }
	 if (isIndeterminate(SFDC)) SFDC = 0;
	 if (isInfinite(SFDC)) SFDC = 0;
 }

 void Signatures::slopePeakDist(vector<double> q, double ql, double qu){

	 unsigned int end = q.size() - 1;
	 vector<double> peaks;
	 SPD = 0;
	 if (q.size() > 0){
		 for (unsigned int i = 1; i<end; i++){

			 if (q[i] > q[i - 1]){
				 if (q[i] > q[i + 1]){
					 peaks.push_back(q[i]);
				 }
			 }
		 }
		 //std::cout << "peaks.size: " << peaks.size() << std::endl;
		 if (peaks.size() != 0){
			 double pLower = quantile(peaks, (1 - ql));
			 double pUpper = quantile(peaks, (1 - qu));

			 SPD = (log(pLower) - log(pUpper)) / ((qu - ql) * 100);
		 }
	 }
	 if (isIndeterminate(SFDC)) SFDC = 0;
	 if (isInfinite(SFDC)) SFDC = 0;;
 } //end of slopePeakDist

 bool Signatures::isIndeterminate(double val)
 {
	 return (val != val);
 }

 bool Signatures::isInfinite(const double val)
 {
	 return (isinf(val));
 }
