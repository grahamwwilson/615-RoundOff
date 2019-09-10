//
// Explore numerical estimates of the first derivative
// for different step sizes and floating point precisions.
// Inspired a bit by discussion in 
// "Numerical Methods for Physics", by Alejandro Garcia.
//
//                       Graham W. Wilson, 10-Sep-2019
//
#include <iostream>
#include <iomanip>
#include <TH1.h>
#include <TFile.h>
#include <float.h>
// Can use either "typedef" or "using" to define the specific FP type. 
// Gottschling, p134, prefers the newer C++11 variant "using" 
// given that it is easier to decipher - see section 3.4.4.
//typedef float fptype;   // Can switch among float/double/long double
//using fptype=long double; // Can switch among float/double/long double
using fptype=double;    // Can switch among float/double/long double
//using fptype=float;     // Can switch among float/double/long double
using namespace std;

fptype myf(fptype x){
// The function. In this case, x^2.
   return x*x;
}

fptype myfp(fptype x){
// First derivative of myf. Here 2x for myf = x^2.
   const fptype FACTOR = 2.0l;
   return FACTOR*x;
}

// Use forward derivative approximation for the first derivative 
// Numerical values are for f(x) = x^2 with x=1.0
fptype numder(fptype x,fptype h){
   cout << "In function numder " << endl;
   cout << "            h: " << setw(27) << h << endl;
   fptype x2 = x+h;
   cout << "          x+h: " << setw(27) << x2 << endl;
   fptype f2 = myf(x2);
   fptype f1 = myf(x);
   fptype deriv_estimate = (f2 - f1)/h;
   fptype actual_deriv = myfp(x);
   cout << "       f(x+h): " << setw(27) << f2 << endl;
   cout << "         f(x): " << setw(27) << f1 << endl;
   cout << "  f(x+h)-f(x): " << setw(27) << (f2-f1) << endl;
   cout << "Est.    f'(x): " << setw(27) << deriv_estimate << endl;
   cout << "True    f'(x): " << setw(27) << actual_deriv << endl;
   fptype val = abs(deriv_estimate - myfp(x));
   fptype relerror = (deriv_estimate - myfp(x))/myfp(x);
   cout << "Rel. error   : " << setw(27) << relerror << endl;
   return val;
}

int main(){

   cout.setf(ios::scientific);
   cout.setf(ios::showpoint);
   cout.precision(20);

// Check the values of the various round-off tolerances
   cout << "FLT_EPSILON  = " << FLT_EPSILON << endl;
   cout << "DBL_EPSILON  = " << DBL_EPSILON << endl;
   cout << "LDBL_EPSILON = " << LDBL_EPSILON << endl;

   TFile *f   = new TFile("histos.root","recreate");
   TH1F *hist = new TH1F("hist", "hist", 80, 0.5, 80.5);
   
   const fptype DIVISOR=2.0l;
   fptype x=0.33333333333333333333l;
   fptype h=1.0l;
   for (unsigned int i=1; i<=80; ++i){
      fptype delta = numder(x,h);
      hist->Fill(i,float(delta));
      h = h/DIVISOR;
      cout << " " << endl;
   }

   hist->Write();
   f->Close();

}
