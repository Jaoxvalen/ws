#pragma once

/* general parameters*/
static const int nClassMax = 50;
static const int nTeachersMax = 100;
/* parameters of the CSO algorithm */
static const int nSMP = 2;
static const int nSRD = 10;
static const int nCDC = 10;
static const int nSPS = 1;
static const int nMR = 4;
static const int nCats = 30;
static const int nIterations = 5000;
/* basic parameters of the fitness function */
static const float nBASE = 1.3;
static const int nHCW = 10;
static const int inf = 10e13; // worst (maximum) value of the fitness function
static const int bigNumber = 2000;

// Penalities Weights values
static double HCW = 10; // Hard constraints violation
static double ICDW = 0.95; // Ideal Classes Dispersion Weight
static double ITDW = 0.6; // Ideal Teachers Dispersion Weight
static double TEPW = 0.06; // Teachers’ Empty Periods Weight
// end Penalities Weights values