/*******************************************************************************
*  Name: main.cpp                                                              *
*  Author: Christian Chavarria                                                 *
*  Date: 15/11/05 16:59                                                        *
*  Compiler: Dev C++ 4.9.9.2                                                   *
*  Description:                                                                *
*    This computes the wavelet decomposition into 5 levels                     *
*    The original signal is equal to the sum of the coarsest approximation (a5)*
*    and the details at levels 1 to 5 (d1 ... d5)                              *
*    s = a5 + d5 + d4 + d3 + d2 + d1                                           *
*******************************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include "FiltersDB4.h"

using namespace std;

ifstream filein; // input signal file
char buffer[81]; // buffer

ofstream fileout0; // output file for aproximatin 5
ofstream fileout1; // output file for detail 1
ofstream fileout2; // output file for detail 2
ofstream fileout3; // output file for detail 3 
ofstream fileout4; // output file for detail 4
ofstream fileout5; // output file for detail 5

float fD1=0; // detail 1
float fD2=0; // detail 2
float fD3=0; // detail 3
float fD4=0; // detail 4
float fD5=0; // detail 5
float fA5=0; // aproximation 5

float fA5LO_D0[8]={0,0,0,0,0,0,0,0}; // filters for aproximation 5
float fA5LO_R0[8]={0,0,0,0,0,0,0,0};

float fD1HI_D0[8]={0,0,0,0,0,0,0,0}; // filters for detail 1
float fD1LO_D0[8]={0,0,0,0,0,0,0,0};
float fD1LO_R0[8]={0,0,0,0,0,0,0,0};
float fD1HI_R0[8]={0,0,0,0,0,0,0,0};

float fD2HI_D0[8]={0,0,0,0,0,0,0,0}; // filters for detail 2
float fD2HI_D1[8]={0,0,0,0,0,0,0,0};
float fD2LO_D0[8]={0,0,0,0,0,0,0,0};
float fD2LO_R0[8]={0,0,0,0,0,0,0,0};
float fD2HI_R1[8]={0,0,0,0,0,0,0,0};
float fD2HI_R0[8]={0,0,0,0,0,0,0,0};

float fD3HI_D0[8]={0,0,0,0,0,0,0,0}; // filters for detail 3
float fD3HI_D1[8]={0,0,0,0,0,0,0,0};
float fD3HI_D2[8]={0,0,0,0,0,0,0,0};
float fD3LO_D0[8]={0,0,0,0,0,0,0,0};
float fD3LO_R0[8]={0,0,0,0,0,0,0,0};
float fD3HI_R2[8]={0,0,0,0,0,0,0,0};
float fD3HI_R1[8]={0,0,0,0,0,0,0,0};
float fD3HI_R0[8]={0,0,0,0,0,0,0,0};

float fD4HI_D0[8]={0,0,0,0,0,0,0,0}; // filters for detail 4
float fD4HI_D1[8]={0,0,0,0,0,0,0,0};
float fD4HI_D2[8]={0,0,0,0,0,0,0,0};
float fD4HI_D3[8]={0,0,0,0,0,0,0,0};
float fD4LO_D0[8]={0,0,0,0,0,0,0,0};
float fD4LO_R0[8]={0,0,0,0,0,0,0,0};
float fD4HI_R3[8]={0,0,0,0,0,0,0,0};
float fD4HI_R2[8]={0,0,0,0,0,0,0,0};
float fD4HI_R1[8]={0,0,0,0,0,0,0,0};
float fD4HI_R0[8]={0,0,0,0,0,0,0,0};

float fD5HI_D0[8]={0,0,0,0,0,0,0,0}; // filters for detail 5
float fD5HI_D1[8]={0,0,0,0,0,0,0,0};
float fD5HI_D2[8]={0,0,0,0,0,0,0,0};
float fD5HI_D3[8]={0,0,0,0,0,0,0,0};
float fD5HI_D4[8]={0,0,0,0,0,0,0,0};
float fD5HI_R4[8]={0,0,0,0,0,0,0,0};
float fD5HI_R3[8]={0,0,0,0,0,0,0,0};
float fD5HI_R2[8]={0,0,0,0,0,0,0,0};
float fD5HI_R1[8]={0,0,0,0,0,0,0,0};
float fD5HI_R0[8]={0,0,0,0,0,0,0,0};

filterDB4 filter;    // filter object
bool bSampling=true; // up and down sampling

// function headers
void openFiles();
void closeFiles();
void getWavDB4(float fData);

// main
int main(int argc, char *argv[]){
    argc!=1? // input signal from file
       filein.open(argv[1], ios::in):filein.open("SIGNAL.TXT", ios::in);
    if (!filein){
       cout<<"File does not exist."<<endl;
       system("PAUSE");
       exit(1);
    }
    openFiles();
    while (!filein.eof()){
          filein.getline(buffer,80,'\n');
          getWavDB4(atof(buffer));
    }
    for (int i=0;i<6;i++)
        getWavDB4(atof(buffer));
    closeFiles();
    filein.close();
    return EXIT_SUCCESS;
}

// function bodies
void openFiles(){
     fileout0.open("APROX_5.TXT", ios::out);
     fileout1.open("DETAIL_1.TXT", ios::out);
     fileout2.open("DETAIL_2.TXT", ios::out);
     fileout3.open("DETAIL_3.TXT", ios::out);
     fileout4.open("DETAIL_4.TXT", ios::out);
     fileout5.open("DETAIL_5.TXT", ios::out);
}

void closeFiles(){
     fileout0.close();
     fileout1.close();
     fileout2.close();
     fileout3.close();
     fileout4.close();
     fileout5.close();
}

void getWavDB4(float fData){
     // aproximation 5
     float fY0=0;
     fY0=filter.applyLO_D(fData,&fA5LO_D0);
     if (bSampling)
        fA5=filter.applyLO_R(fY0,&fA5LO_R0);
     else
        fA5=filter.applyLO_R(0,&fA5LO_R0);
     fileout0<<fA5<<endl;

     // detail 1
     float fY1=0, fY2=0, fY3=0;
     fY1=filter.applyHI_D(fData,&fD1HI_D0);
     if (bSampling){
        fY2=filter.applyLO_D(fY1,&fD1LO_D0);
        fY3=filter.applyLO_R(fY2,&fD1LO_R0);
        fD1=filter.applyHI_R(fY3,&fD1HI_R0);
     }else{
        fY2=filter.applyLO_D(0,&fD1LO_D0);
        fY3=filter.applyLO_R(0,&fD1LO_R0);
        fD1=filter.applyHI_R(0,&fD1HI_R0);
     }
     fileout1<<fD1<<endl;

     // detail 2
     float fY4=0, fY5=0, fY6=0, fY7=0, fY8=0;
     fY4=filter.applyHI_D(fData,&fD2HI_D0);
     if (bSampling){
        fY5=filter.applyHI_D(fY4,&fD2HI_D1);
        fY6=filter.applyLO_D(fY5,&fD2LO_D0);
        fY7=filter.applyLO_R(fY6,&fD2LO_R0);
        fY8=filter.applyHI_R(fY7,&fD2HI_R1);
        fD2=filter.applyHI_R(fY8,&fD2HI_R0);
     }else{
        fY5=filter.applyHI_D(0,&fD2HI_D1);
        fY6=filter.applyLO_D(0,&fD2LO_D0);
        fY7=filter.applyLO_R(0,&fD2LO_R0);
        fY8=filter.applyHI_R(0,&fD2HI_R1);
        fD2=filter.applyHI_R(0,&fD2HI_R0);
     }
     fileout2<<fD2<<endl;

     // detail 3
     float fY9=0, fY10=0, fY11=0, fY12=0, fY13=0, fY14=0, fY15=0;
     fY9=filter.applyHI_D(fData,&fD3HI_D0);
     if (bSampling){
        fY10=filter.applyHI_D(fY9,&fD3HI_D1);
        fY11=filter.applyHI_D(fY10,&fD3HI_D2);
        fY12=filter.applyLO_R(fY11,&fD3LO_R0);
        fY13=filter.applyLO_D(fY12,&fD3LO_D0);
        fY14=filter.applyHI_R(fY13,&fD3HI_R2);
        fY15=filter.applyHI_R(fY14,&fD3HI_R1);
        fD3=filter.applyHI_R(fY15,&fD3HI_R0);
     }else{
        fY10=filter.applyHI_D(0,&fD3HI_D1);
        fY11=filter.applyHI_D(0,&fD3HI_D2);
        fY12=filter.applyLO_R(0,&fD3LO_R0);
        fY13=filter.applyLO_D(0,&fD3LO_D0);
        fY14=filter.applyHI_R(0,&fD3HI_R2);
        fY15=filter.applyHI_R(0,&fD3HI_R1);
        fD3=filter.applyHI_R(0,&fD3HI_R0);
     }
     fileout3<<fD3<<endl;

     // detail 4
     float fY16=0, fY17=0, fY18=0, fY19=0, fY20=0, fY21=0, fY22=0,
           fY23=0, fY24=0;
     fY16=filter.applyHI_D(fData,&fD4HI_D0);
     if (bSampling){
        fY17=filter.applyHI_D(fY16,&fD4HI_D1);
        fY18=filter.applyHI_D(fY17,&fD4HI_D2);
        fY19=filter.applyHI_D(fY18,&fD4HI_R3);
        fY20=filter.applyLO_D(fY19,&fD4LO_D0);
        fY21=filter.applyLO_R(fY20,&fD4LO_R0);
        fY22=filter.applyHI_R(fY21,&fD4HI_D3);
        fY23=filter.applyHI_R(fY22,&fD4HI_R2);
        fY24=filter.applyHI_R(fY23,&fD4HI_D1);
        fD4=filter.applyHI_R(fY24,&fD4HI_R0);
     }else{
        fY17=filter.applyHI_D(0,&fD4HI_D1);
        fY18=filter.applyHI_D(0,&fD4HI_D2);
        fY19=filter.applyHI_D(0,&fD4HI_R3);
        fY20=filter.applyLO_D(0,&fD4LO_D0);
        fY21=filter.applyLO_R(0,&fD4LO_R0);
        fY22=filter.applyHI_R(0,&fD4HI_D3);
        fY23=filter.applyHI_R(0,&fD4HI_R2);
        fY24=filter.applyHI_R(0,&fD4HI_D1);
        fD4=filter.applyHI_R(0,&fD4HI_R0);
     }
     fileout4<<fD4<<endl;

     // detail 5
     float fY25=0, fY26=0, fY27=0, fY28=0, fY29=0, fY30=0, fY31=0,
           fY32=0, fY33=0;
     fY25=filter.applyHI_D(fData,&fD5HI_D0);
     if (bSampling){
        fY26=filter.applyHI_D(fY16,&fD5HI_D1);
        fY27=filter.applyHI_D(fY17,&fD5HI_D2);
        fY28=filter.applyHI_D(fY18,&fD5HI_D3);
        fY29=filter.applyHI_D(fY19,&fD5HI_D4);
        fY30=filter.applyHI_R(fY20,&fD5HI_R4);
        fY31=filter.applyHI_R(fY21,&fD5HI_R3);
        fY32=filter.applyHI_R(fY22,&fD5HI_R2);
        fY33=filter.applyHI_R(fY23,&fD5HI_R1);
        fD5=filter.applyHI_R(fY24,&fD5HI_R0);
     }else{
        fY26=filter.applyHI_D(0,&fD5HI_D1);
        fY27=filter.applyHI_D(0,&fD5HI_D2);
        fY28=filter.applyHI_D(0,&fD5HI_D3);
        fY29=filter.applyHI_D(0,&fD5HI_D4);
        fY30=filter.applyHI_R(0,&fD5HI_R4);
        fY31=filter.applyHI_R(0,&fD5HI_R3);
        fY32=filter.applyHI_R(0,&fD5HI_R2);
        fY33=filter.applyHI_R(0,&fD5HI_R1);
        fD5=filter.applyHI_R(0,&fD5HI_R0);
     }
     fileout5<<fD5<<endl;
     
// up and down sampling
     bSampling?bSampling=false:bSampling=true;
///*Measuring time routine*/
//double c=clock();
//c=c/1000000; //CLOCKS_PER_SEC
//cout<<"Processing Time: "<<c<<" seconds."<<endl;
//system("PAUSE");
//exit(0);
///*END - Measuring time routine*/
}
