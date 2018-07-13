//
//  collison.hpp
//  ECE Project1
//
//  Created by BILL on 9/26/17.
//  Copyright © 2017 BILL. All rights reserved.
//

#ifndef collison_hpp
#define collison_hpp

#include <stdio.h>
#include<iostream>
#include<cmath>
#include<math.h>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include <iomanip>
#include <unistd.h>
#include <random>

using namespace std;
void PrintSeq(int frames);
void multi_StimulateAB(int times);
int Gen_Seq(vector<int> &A, int vaule_times);
int Qucik_sort(vector<int> &X);
int Select_backoff(int CW);
int Simulation_ScB1(int vaule, int times_AB,vector<int> A,vector<int> C);
int Simulation_ScB2(int vaule, int times_AB,vector<int> A,vector<int> C);
void sleep(int vaule);
void Signal_Simulate(int frames, int topology,int times);
void Simulation(int type, int frames,int times_A_B,vector<int> &A,vector<int> &C);
void Unin_test(int type);
#endif /* collison_hpp */

