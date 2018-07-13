//
//  collison.cpp
//  ECE Project1
//
//  Created by BILL on 9/26/17.
//  Copyright © 2017 BILL. All rights reserved.
//

#include "collison.hpp"
#include <stdio.h>
#define ACK 2
#define RTS 2
#define CTS 2
#define DIFS 2
#define SIFS 1
#define Frame 100
#define Slot 20
#define CW0 4
#define CW_MAX 1024
#define LogPath "/Users/xing/Desktop/WSMA.txt"
#define resultPath "/Users/xing/Desktop/OutputMathlab.txt"
int flag_idle=1;
int backoff;
int Vaules[5]={50,100,200,300,400};
int Success_A,Success_C,collision_A,collision_C;
long long current_position1,current_position2;
void PrintSeq(int frames)
{
    vector<int> A;
    vector<int> B;
    Gen_Seq(A,frames);
    cout<<"test generate result "<<endl;
    vector<int>::iterator it=A.begin();
    while(it!=A.end())
    {
        cout<<"Seq number= "<<*it<<endl;
        it++;
    }
     cout<<"size of A="<<A.size()<<endl;
    
};
void Unin_test(int type)
{
    vector<int> A;
    vector<int> C;
    // test sequnce
    A.push_back(1000);
    C.push_back(1000);
    A.push_back(2001);
    C.push_back(3000);
    if(type==1)
    {
        Simulation_ScB1(0, 0, A,C);
    }
    if(type==2)
        Simulation_ScB2(0, 0, A,C);
}

void Simulation(int type, int frames,int times_A_B)
{
    vector<int> A;
    vector<int> C;
    Gen_Seq(A,times_A_B*frames);   // generate sequence number of A
    Gen_Seq(C,frames);       // generate sequence number of C
    if(type==1)
    {
        Simulation_ScB1(frames, times_A_B, A,C);
    }
    if(type==2)
        Simulation_ScB2(frames, times_A_B, A,C);
}
// test function to detect collision , result should check the log file and see how the current_position move 
void test1(vector<int>&A, vector<int>&C)
{
    A.push_back(1000);
    C.push_back(1000);
    A.push_back(2001);
    C.push_back(3000);
    cout<<"dete collision should be 1"<<endl;
    
};
void multi_StimulateAB(int times)
{
    double Ta,Tc,sum1,sum2,coll_sum1,coll_sum2;
    coll_sum1=coll_sum2=sum1=sum2=0;
    vector<string> B;
    string p;
    B.clear();
    int V=0;
    ofstream fp;
    // result file path
   // fp.open("/Users/xing/Desktop/OutputMathlab.txt");
    fp.open(resultPath);
    fp<<"CSMA......."<<endl;
    fp<<"DeviceName Throughput(Kbps)  collision   frames/s    Fairness\n";
    int multi=2;
    vector<int> A,C;
  while(multi)
  {
      fp<<"the number frames A send ="<<multi<<"time the number of frames C send"<<endl;
    for(int j=0;j<sizeof(Vaules)/sizeof(int);j++)
    {
        V=Vaules[j];
     coll_sum1=coll_sum2=sum1=sum2=0;
    for(int i=0;i<times;i++)
    {
        Success_A=Success_C=0;
        collision_C=collision_A=0;
        current_position1=current_position2=0;
      //  Simulation_ScB1(V,multi);
        A.clear();
        C.clear();
        Simulation(1,V, multi);
        sum2=Success_C+sum2;
        sum1=sum1+Success_A;
        coll_sum1=collision_A+coll_sum1;
        coll_sum2=collision_C+coll_sum2;
        cout<<i<<" time stimulation for 1"<<endl;
    }
    double second=(double)(max(current_position1,current_position2)*20)/1000000;
   //     cout<<"secod= "<<second<<endl;
      second=second>10?10:second;
    Ta=((sum1/times)*1500*8)/(1000*second);   //average throughput
    Tc=((sum2/times)*1500*8)/(1000*second);
    string fail1=to_string(((sum1/times)/(sum2/times)));  // average fairness
   // string fail2=to_string((int)(10*V-sum2/times));
   // cout<<"Throught A="<<Ta<<"Mbps "<<" A collision times="<<collision_A<<" l="<<(2*V)<<endl;
  //  cout<<"Throught C="<<Tc<<"Mbps "<<" C collision times"<<collision_C<<"  l="<<(V)<<endl;
        fp<<"       A       "<<Ta<<"        "<<(int)(coll_sum1/times)<<"       "<<(multi*V)<<"          "<<fail1<<endl;
        p.clear();
        string  x=to_string(Tc);
        string  y=to_string((int)(coll_sum2/times));
        string  z=to_string(V);
        p="       C        "+x+"       "+y+"       "+z+"        "+fail1;
        B.push_back(p);
     //   fp<<"B      "<<Tc<<"          "<<coll_sum2/times<<"     "<<(V/10)<<endl;
    }
    for(vector<string>::iterator it=B.begin();it!=B.end();it++)
    fp<<*it<<endl;
    B.clear();
    multi--;
  }
    
    fp<<"Virtual Carrier Sensing ......"<<endl;
    fp<<"DeviceName Throughput(Mbps)  collision   frames/s    Fairness\n";
    multi=2;
   while(multi)
 {
    fp<<"the number frames A send ="<<multi<<"time the number of frames C send"<<endl;
    for(int j=0;j<sizeof(Vaules)/sizeof(int);j++)
    {
        V=Vaules[j];
      coll_sum1=coll_sum2=sum1=sum2=0;
        for(int i=0;i<times;i++)
        {
            Success_A=Success_C=0;
            collision_C=collision_A=0;
           current_position1=current_position2=0;
         //   Simulation_ScB2(V,multi);
       //     A.clear();
        //    C.clear();
            Simulation(2,V, multi);
            sum2=Success_C+sum2;
            sum1=sum1+Success_A;
            coll_sum1=collision_A+coll_sum1;
            coll_sum2=collision_C+coll_sum2;
          cout<<j<<" loop "<<i<<" time stimulation for 2"<<endl;
        }
        double second=(double)(max(current_position1,current_position2)*20)/1000000;
        second=second>10?10:second;
        Ta=((sum1/times)*1500*8)/(1000*second);
        Tc=((sum2/times)*1500*8)/(1000*second);
         string fail1=to_string(((sum1/times)/(sum2/times)));
   //     string fail2=to_string((int)(10*V-sum2/times));
     //   cout<<"Throught A="<<Ta<<"Mbps "<<" A collision times="<<collision_A<<" l="<<(2*V)<<endl;
     //   cout<<"Throught C="<<Tc<<"Mbps "<<" C collision times"<<collision_C<<"  l="<<(V)<<endl;
        fp<<"       A       "<<Ta<<"        "<<(int)(coll_sum1/times)<<"       "<<(multi*V)<<"          "<<fail1<<endl;
        p.clear();
        string  x=to_string(Tc);
        string  y=to_string((int)(coll_sum2/times));
        string  z=to_string(V);
        p="       C        "+x+"       "+y+"       "+z+"        "+fail1;
        B.push_back(p);
      //  fp<<"B      "<<Tc<<"       "<<coll_sum2/times<<"   "<<(V)<<endl;
    }
    for(vector<string>::iterator it=B.begin();it!=B.end();it++)
        fp<<*it<<endl;
    B.clear();
    multi--;
}
    fp.close();
    cout<<"success finish mutlit Stimulation for CSMA and virtula sensing "<<endl;
};
void sleep(int vaule)
{
    vaule=1000000*vaule;
    while(vaule--) ;
}
//reference Quick sort code from book
// Sort the distant
int Qucik_sort(vector<int> &X)
{
    int key,j;
    int temp;
    for(int i=1;i<X.size();i++)
    {
        key=X[i];
        temp=X[i];
        j=i-1;
        while(j>=0&&X[j]>key)
        {
            X[j+1]=X[j];
            j--;
        }
        X[j+1]=temp;
    }
    return 1;
}
int Select_backoff(int CW)
{
    int backoff;
  // srand((unsigned)time(0));
    backoff=rand()%CW;
    return backoff;
};

// Gen a Sequence for A and C
int Gen_Seq(vector<int> &A, int vaule_times)
{
    double Seq_A,temp;
    int  Seq_A_slot,random_vaules;
    int sum=0;
    srand((unsigned)time(NULL));
    random_device                  rand_dev;
    mt19937                        generator(rand_dev());
  //  default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0,1.0);
    cout<<"Generate Seq number for A ( slot )"<<endl;
    int loop_time=10;  // 10 second
   while(loop_time--)
  {
    for(int i=0;i<vaule_times;i++)
    {
        Seq_A=(double)rand()/RAND_MAX;  // union disturbing
   //    Seq_A=distribution(generator);
    //  cout<<"Seq A float number= "<<Seq_A<<endl;
        Seq_A=(double)-log(1-Seq_A);
        temp=vaule_times;
        temp=(double)(1/temp);
        Seq_A=temp*Seq_A;
      //   cout<<"Seq A float number= "<<setprecision(30)<<Seq_A<<endl;
        Seq_A_slot=Seq_A/0.00002;
        sum=sum+Seq_A_slot;
         A.push_back(sum);
      //     A.push_back(Seq_A_slot);
     
    }
}
  //  Qucik_sort(A);
    return 1;
};
// Simulation for scenario B  , implement CSMA
int Simulation_ScB1(int vaule, int times_AB,vector<int> A,vector<int> C)
{
    int backoff_A,backoff_C,CWA,CWC;
    int flag_init,flag_backoff_a,flag_backoff_c;
    Success_A=Success_C=collision_A=collision_C=0;
    long long comp_A,comp_C,curren_test;
    ofstream fp;
   // fp.open("/Users/xing/Desktop/WSMA.txt");
     fp.open(LogPath);
    if(!fp.is_open())
        cout<<"Can not open file WSMA.txt"<<endl;
     fp<<"Begin Simulation........"<<endl;
    CWA=CWC=CW0;
 //   vector<int> A;
 //   vector<int> C;
//    Gen_Seq(A,times_AB*vaule);   // generate sequence number of A
//    Gen_Seq(C,vaule);       // generate sequence number of C
    vector<int>::iterator it1=A.begin();
    vector<int>::iterator it2=C.begin();
    // initation values
    flag_init=0;
    flag_backoff_a=flag_backoff_c=-1;
    current_position1=comp_C=comp_A=current_position2=0;
    int flag_A_finish,flag_B_finsih;
    flag_A_finish=flag_B_finsih=0;
    while(A.size()>=1||C.size()>=1)
    {
        if(current_position1>500000)   // 10 second = 50 0000 slots time
            break;
        if(flag_idle)
        {
            if(!flag_init)   // deal with first frame of A and C
            {
                backoff_A=Select_backoff(CWA);
                backoff_C=Select_backoff(CWC);
                comp_A=current_position1+(*it1)+DIFS+backoff_A;
                comp_C=current_position2+(*it2)+DIFS+backoff_C;
                if(comp_C>comp_A)
                {
                 current_position1=*it1;
                 curren_test=current_position1+DIFS+backoff_A+Frame+SIFS+ACK;
                 if(comp_C>curren_test)   // A send
                  {
                      Success_A++;
                      current_position1=current_position1+DIFS+backoff_A+Frame+SIFS+ACK;
                      flag_backoff_a=2;
                      fp<<"Success in send A seq nunber "<<*it1<<"  \n";
                      A.erase(it1);
                      it1=A.begin();
                      current_position2=*it2;
                      flag_backoff_c=1;
                  }
                   else       //collison
                   {
                       collision_A++;
                       collision_C++;
                       CWA=min(2*CWA,CW_MAX);
                       CWC=min(2*CWC,CW_MAX);
                       flag_backoff_a=flag_backoff_c=0;
                       current_position1=current_position1+DIFS+backoff_A+Frame+SIFS+ACK;
                       current_position2=*it2+DIFS+backoff_C+Frame+SIFS+ACK;
                       fp<<"collison= "<<collision_A<<" Occur  current position1 "<<current_position1<<"    current position2 "<<current_position2<<endl;
                   }
                }
                else
                {
                    current_position2=*it2;
                    curren_test=current_position2+DIFS+backoff_C+Frame+SIFS+ACK;
                    if(comp_A>curren_test)    // C send
                    {
                        Success_C++;
                        current_position2=current_position2+DIFS+backoff_C+Frame+SIFS+ACK;
                        flag_backoff_c=0;
                        fp<<"Success in send C seq number "<<*it2<<"  \n";
                        C.erase(it2);
                        it2=C.begin();
                        flag_backoff_a=2;
                        current_position1=*it1;
                    }
                    else   //collison
                    {
                        collision_A++;
                        collision_C++;
                         CWA=min(2*CWA,CW_MAX);  // double backoff range
                         CWC=min(2*CWC,CW_MAX);
                        flag_backoff_a=flag_backoff_c=0;
                        current_position2=current_position2+DIFS+backoff_C+Frame+SIFS+ACK;
                        current_position1=*it1+DIFS+backoff_A+Frame+SIFS+ACK;
                        fp<<"collision= "<<collision_A<<" Occur  current position1 "<<current_position1<<"    current position2 "<<current_position2<<endl;
                    }
                }
                flag_init=1;
            }
            else
            {
                if(flag_backoff_a==0||flag_backoff_a==2) backoff_A=Select_backoff(CWA);   // select random backoff
                if(flag_backoff_c==0||flag_backoff_c==2) backoff_C=Select_backoff(CWC);
                if(flag_backoff_a==2&&(*it1>current_position1))    // sequence number biger than current , then replace current
                {
                    cout<<"test sequence number for A  currentposition"<<current_position1<<"   sequence number ="<<*it1<<endl;
                    current_position1=*it1;
                }
                if(flag_backoff_c==2&&(*it2>current_position2))
                {
                  cout<<"test sequence number for A  currentposition"<<current_position2<<"   sequence number ="<<*it2<<endl;
                    current_position2=*it2;
                }
                fp<<"Begin to tack seq number A "<<*it1<<"  B="<<*it2<<endl;
                fp<<"current position1 "<<current_position1<<" backofA "<<backoff_A<<" current position2 "<<current_position2<<" backofC  "<<backoff_C<<endl;
                comp_A=current_position1+DIFS+backoff_A+Frame+SIFS+ACK;
                comp_C=current_position2+DIFS+backoff_C+Frame+SIFS+ACK;
                curren_test=max(current_position1+DIFS+backoff_A,current_position2+DIFS+backoff_C);  // get Biger number test frame length from A and C ,compare which can send success without collison
                if((!flag_A_finish&&comp_A<curren_test)||flag_B_finsih)   // A send
                {
                    Success_A++;
                    current_position1=current_position1+DIFS+backoff_A+Frame+SIFS+ACK;
                    flag_backoff_a=2;
                    CWA=CW0;
                    fp<<"Success in send A seq number "<<*it1<<"  \n";
                    if(A.size()<=1)
                    { A.clear(); flag_A_finish=1;}   // All sequence of A send
                    else
                    {
                    A.erase(it1);     // pop sequence already sent
                    it1=A.begin();
                    }
                    flag_backoff_c=1;    // backoff C remaind
                }
                else
                    if((!flag_B_finsih&&comp_C<curren_test)||flag_A_finish)  // C send
                    {
                        Success_C++;
                        current_position2=comp_C;
                        flag_backoff_c=2;
                        CWC=CW0;
                        fp<<"Success in send C seq number "<<*it2<<"  \n";
                        if(C.size()<=1)
                        {  C.clear(); flag_B_finsih=1; }   // All Sequence of C send
                        else
                        {
                        C.erase(it2);     //pop sequence already sent
                        it2=C.begin();
                        }
                        flag_backoff_a=1;
                    }
                else
                {
                    collision_C++;
                    collision_A++;
                     CWA=min(2*CWA,CW_MAX);  //double backoff range
                     CWC=min(2*CWC,CW_MAX);
                    flag_backoff_a=flag_backoff_c=0;
                    current_position2=current_position2+DIFS+backoff_C+Frame+SIFS+ACK;
                    current_position1=current_position1+DIFS+backoff_A+Frame+SIFS+ACK;
               //     cout<<"A="<<*it1<<" B="<<*it2<<endl;
                  fp<<"collison= "<<collision_A<<" Occur  current position1 "<<current_position1<<"    current position2 "<<current_position2<<endl;
                }
            }
        }
    }
    fp.close();

    cout<<"Final A Success "<<Success_A<<"  collision="<<collision_A<<endl;
    cout<<"Final C Success "<<Success_C<<"    collision="<<collision_C<<endl;
    
    return 1;
}
// Simulation for Scenarion 2  Virtual Sensing carrier sensing
int Simulation_ScB2(int vaule,int times_AB,vector<int> A,vector<int> C)
{
    int backoff_A,backoff_C,CWA,CWC;
    int flag_init,flag_backoff_a,flag_backoff_c;
    Success_A=Success_C=collision_A=collision_C=0;
    long long comp_A,comp_C;
    ofstream fp;
  //  fp.open("/Users/xing/Desktop/WSMA.txt");
     fp.open(LogPath);
    if(!fp.is_open())
        cout<<"Can not open file WSMA.txt"<<endl;
    fp<<"Begin Simulation........"<<endl;
    CWA=CWC=CW0;
 //   vector<int> A;
 //   vector<int> C;
 //   Gen_Seq(A,times_AB*vaule);     // generate sequence number of A
  //  Gen_Seq(C,vaule);       // generate sequence number of C
 //   test1(A,C);
    vector<int>::iterator it1=A.begin();
    vector<int>::iterator it2=C.begin();
    // initation vaules
    flag_init=0;
    flag_backoff_a=flag_backoff_c=-1;
    current_position1=comp_C=comp_A=current_position2=0;
    int flag_A_finish,flag_B_finsih;
    flag_A_finish=flag_B_finsih=0;
    flag_A_finish=flag_B_finsih=0;
    cout<<"size of A="<<A.size()<<" Size of C="<<C.size()<<endl;
    while(A.size()>=1||C.size()>=1)
    {
        if(current_position1>500000)   // 10 second = 50 0000 slots time
            break;
        
            if(!flag_init)  // deal with first frame of A and C
            {
                backoff_A=Select_backoff(CWA);   // select a random backoff
                backoff_C=Select_backoff(CWC);
                comp_A=current_position1+(*it1)+DIFS+backoff_A;   // record the length of test frame
                comp_C=current_position2+(*it2)+DIFS+backoff_C;
                if(*it2>=(comp_A+RTS+SIFS+CTS))     // C sequence number big than A plus RTS SIFS CTS,  A send
                {
                     Success_A++;
               current_position1=*it1+DIFS+backoff_A+RTS+SIFS+CTS+SIFS+Frame+SIFS+ACK;
                    flag_backoff_c=0;
                    flag_backoff_a=2;
                   fp<<"Success in send A seq nunber "<<*it1<<"  \n";
                    A.erase(it1);
                    it1=A.begin();
                    current_position2=current_position1;
                    CWA=CW0;
                }
                else
                 if(*it1>=(comp_C+RTS+SIFS+CTS))    // A sequence number big than C plus RTS SIFS CTS,  C send
                {
                    Success_C++;
                    current_position2=*it2+DIFS+backoff_C+RTS+SIFS+CTS+SIFS+Frame+SIFS+ACK;
                    flag_backoff_a=0;
                    flag_backoff_c=2;
                    fp<<"Success in send C seq nunber "<<*it2<<"  \n";
                    C.erase(it2);
                    it2=C.begin();
                    current_position1=current_position2;
                    CWC=CW0;
                }
                else
                if((comp_C>(comp_A+RTS+SIFS+CTS))&&*it2<(comp_A+RTS+SIFS+CTS))   // C sequence with backoff bigger A sequence backoff++RTS+SIFS+CTS && C sequence less than A sequence backoff++RTS+SIFS+CTS
                {
                    Success_A++;
                    current_position1=*it1+DIFS+backoff_A+RTS+SIFS+CTS+SIFS+Frame+SIFS+ACK;
                    backoff_C=(comp_C-comp_A-RTS-CTS-SIFS);
                    flag_backoff_c=1;
                    flag_backoff_a=2;
                    fp<<"Success in send A seq nunber "<<*it1<<"  \n";
                    A.erase(it1);
                    it1=A.begin();
                  current_position2=current_position1;
                }
                else if((comp_A+RTS+SIFS+CTS)>=comp_C&&comp_C>=comp_A)   // C sequece with backoff between Seqence A with backoff and A sequence+backoff++RTS+SIFS+CTS
                {
                    collision_A++;
                    collision_C++;
                    CWA=min(2*CWA,CW_MAX);
                    CWC=min(2*CWC,CW_MAX);
                    flag_backoff_a=flag_backoff_c=0;
                    current_position1=*it1+DIFS+backoff_A+RTS+SIFS+CTS;
                    current_position2=*it2+DIFS+backoff_C+RTS+SIFS+CTS;
                    fp<<"collison= "<<collision_A<<" Occur  current position1 "<<current_position1<<"    current position2 "<<current_position2<<endl;
                }
                else if((comp_A>(comp_C+RTS+SIFS+CTS))&&*it1<(comp_C+RTS+SIFS+CTS)) // A sequence with backoff bigger C sequence backoff++RTS+SIFS+CTS && A sequence less than C sequence backoff++RTS+SIFS+CTS
                {
                    Success_C++;
                    current_position2=*it2+DIFS+backoff_C+RTS+SIFS+CTS+SIFS+Frame+SIFS+ACK;
                    backoff_A=(comp_A-comp_C-RTS-CTS-SIFS);
                    flag_backoff_a=1;
                    flag_backoff_c=2;
                    fp<<"Success in send C seq nunber "<<*it2<<"  \n";
                    C.erase(it2);
                    it2=C.begin();
                    current_position1=current_position2;
                }
                else if((comp_C+RTS+SIFS+CTS)>=comp_A&&comp_A>=comp_C)  // A sequece with backoff between Seqence C with backoff and C sequence+backoff++RTS+SIFS+CTS
                {
                    collision_A++;
                    collision_C++;
                    CWA=min(2*CWA,CW_MAX);
                    CWC=min(2*CWC,CW_MAX);
                    flag_backoff_a=flag_backoff_c=0;
                    current_position1=*it1+DIFS+backoff_A+RTS+SIFS+CTS;
                    current_position2=*it2+DIFS+backoff_C+RTS+SIFS+CTS;
                    fp<<"collison= "<<collision_A<<" Occur  current position1 "<<current_position1<<"    current position2 "<<current_position2<<endl;
                }
               
                flag_init=1;
            }
            else
            {
                if(flag_backoff_a==0||flag_backoff_a==2) backoff_A=Select_backoff(CWA);   // select random backoff
                if(flag_backoff_c==0||flag_backoff_c==2) backoff_C=Select_backoff(CWC);
                if(flag_backoff_a==2&&(*it1>current_position1))    // seqence number bigger than current position, replace it in order to matain newly frame timeline
                {
                    cout<<"test sequence number for A  currentposition"<<current_position1<<"   sequence number ="<<*it1<<endl;
                    current_position1=*it1;
                }
                if(flag_backoff_c==2&&(*it2>current_position2))
                {
                    cout<<"test sequence number for A  currentposition"<<current_position2<<"   sequence number ="<<*it2<<endl;
                    current_position2=*it2;
                }
                fp<<"Begin to tack sequence number A ="<<*it1<<"  B="<<*it2<<endl;
                fp<<"current position1 "<<current_position1<<" A backoff "<<backoff_A<<" current position2 "<<current_position2<<" C backoff "<<backoff_C<<endl;
                comp_A=current_position1+DIFS+backoff_A;   // test frame with backoff A and C, compare them , determinate which can send
                comp_C=current_position2+DIFS+backoff_C;
              //  curren_test=max(current_position1+DIFS+backoff_A,current_position2+DIFS+backoff_C);
             //   cout<<"flag A finish="<<flag_A_finish<<endl;
                if((!flag_A_finish)&&(*it2>=(comp_A+RTS+SIFS+CTS)))    // A send, C Sequence Bigger than A 's test frame length
                {
                    Success_A++;
                    current_position1=current_position1+DIFS+backoff_A+RTS+SIFS+CTS+SIFS+Frame+SIFS+ACK;  // more current position to the next
                    flag_backoff_c=0;  // C's is not selected
                    flag_backoff_a=2;  // reselect backoff flag
               //     cout<<"flag inside A finish="<<flag_A_finish<<endl;
                    fp<<"Success in send A seq number (C sequence big)"<<*it1<<"  \n";
                    if(A.size()<=1)
                    { A.clear(); flag_A_finish=1; }    // all frame of A sent
                    else
                    {
                        A.erase(it1);  //pop the frame sent yet
                        it1=A.begin();
                    }
                    if(current_position2<current_position1)
                    current_position2=current_position1;  // move the timeline to the next
                    CWA=CW0;
                    continue;
                }
                else
                if(!flag_B_finsih&&(*it1>=(comp_C+RTS+SIFS+CTS)))
                {
                    Success_C++;
                    current_position2=current_position2+DIFS+backoff_C+RTS+SIFS+CTS+SIFS+Frame+SIFS+ACK;
                    flag_backoff_a=0;
                    flag_backoff_c=2;
                    fp<<"Success in send C seq number  (A sequence big)"<<*it2<<"  \n";
                    if(C.size()<=1)
                    {  C.clear(); flag_B_finsih=1; }
                    else
                    {
                        C.erase(it2);
                        it2=C.begin();
                    }
                    if(current_position1<current_position2)
                    current_position1=current_position2;
                    CWC=CW0;
                     continue;
                }
                else
                if((!flag_A_finish&&((comp_C>(comp_A+RTS+SIFS+CTS))&&*it2<(comp_A+RTS+SIFS+CTS)))||flag_B_finsih)  // C current position with backoff bigger A current position+ backoff++RTS+SIFS+CTS && C current position less than A current position+ backoff++RTS+SIFS+CTS  || C finish sending all frame
                {
                    Success_A++;
                    current_position1=current_position1+DIFS+backoff_A+RTS+SIFS+CTS+SIFS+Frame+SIFS+ACK; //move timeline , A current position
                    if(!flag_B_finsih)
                    backoff_C=(comp_C-comp_A-RTS-CTS-SIFS);   // C's backoff froze ,record the rest vaule
                    CWA=CW0;
                    flag_backoff_c=1;
                    flag_backoff_a=2;
                    fp<<"Success in send A seq number "<<*it1<<"  \n";
                    if(it1==A.end())
                    { A.empty(); flag_A_finish=1;  sleep(1);}
                    else
                    {
                        A.erase(it1);
                        it1=A.begin();
                    }
                     if(current_position2<current_position1)
                     current_position2=current_position1;
                     continue;
                }
                else if((comp_A+RTS+SIFS+CTS)>=comp_C&&comp_C>=comp_A)    // C test frame in the collision are
                {
                    collision_A++;
                    collision_C++;
                    CWA=min(2*CWA,CW_MAX);
                    CWC=min(2*CWC,CW_MAX);
                    flag_backoff_a=flag_backoff_c=0;
                    current_position1=current_position1+DIFS+backoff_A+RTS+SIFS+CTS;
                    current_position2=current_position2+DIFS+backoff_C+RTS+SIFS+CTS;
                    fp<<"collison= "<<collision_A<<" Occur  current position1 "<<current_position1<<"    current position2 "<<current_position2<<endl;
                }
                else if((!flag_B_finsih&&((comp_A>(comp_C+RTS+SIFS+CTS))&&*it1<(comp_C+RTS+SIFS+CTS)))||flag_A_finish)
                {
                    Success_C++;
                    current_position2=current_position2+DIFS+backoff_C+RTS+SIFS+CTS+SIFS+Frame+SIFS+ACK;
                    if(!flag_A_finish)
                    backoff_A=(comp_A-comp_C-RTS-CTS-SIFS);
                    CWC=CW0;
                    flag_backoff_a=1;
                    flag_backoff_c=2;
                    fp<<"Success in send C seq number "<<*it2<<"  \n";
                    if(it2==C.end())
                    {  C.empty(); flag_B_finsih=1;  sleep(1); }
                    else
                    {
                        C.erase(it2);
                        it2=C.begin();
                    }
                  if(current_position1<current_position2)
                   current_position1=current_position2;
                     continue;
                }
                else if((comp_C+RTS+SIFS+CTS)>=comp_A&&comp_A>=comp_C)    // A test frame in the collision are
                {
                    collision_A++;
                    collision_C++;
                    CWA=min(2*CWA,CW_MAX);
                    CWC=min(2*CWC,CW_MAX);
                    flag_backoff_a=flag_backoff_c=0;
                    current_position1=current_position1+DIFS+backoff_A+RTS+SIFS+CTS;
                    current_position2=current_position2+DIFS+backoff_C+RTS+SIFS+CTS;
                    fp<<"collison= "<<collision_A<<" Occur  current position1 "<<current_position1<<"    current position2 "<<current_position2<<endl;
                }
             
            }
        }
    fp.close();
    cout<<"Final A Success "<<Success_A<<"  collision="<<collision_A<<endl;
    cout<<"Final C Success "<<Success_C<<"    collision="<<collision_C<<endl;
    
    return 1;
}


