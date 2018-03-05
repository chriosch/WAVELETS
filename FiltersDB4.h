/*******************************************************************************
*  Name: FiltersDB4.h                                                          *
*  Author: Christian Chavarria                                                 *
*  Date: 15/11/05 19:40                                                        *
*  Description:                                                                *
*    This computes four filters associated with the orthogonal                 *
*    or biorthogonal wavelet.                                                  *
*    The four output filters are:                                              *
*        LO_D, the decomposition low-pass filter                               *
*        HI_D, the decomposition high-pass filter                              *
*        LO_R, the reconstruction low-pass filter                              *
*        HI_R, the reconstruction high-pass filter                             *
*******************************************************************************/

#ifndef __FILTERSDB4_H__
#define __FILTERSDB4_H__

class filterDB4{
private:
   float fY; // filter output
public:
   filterDB4(){ fY=0; }
   float applyLO_D(float value, float (*x)[8]);
   float applyHI_D(float value, float (*x)[8]);
   float applyLO_R(float value, float (*x)[8]);
   float applyHI_R(float value, float (*x)[8]);
};

float filterDB4::applyLO_D(float value, float (*x)[8]){
//LO_D = -0.0106 0.0329 0.0308 -0.1870 -0.0280 0.6309 0.7148 0.2304
      (*x)[0]=value;
      fY=-0.0106*(*x)[0]+0.0329*(*x)[1]+0.0308*(*x)[2]-0.1870*(*x)[3]+
         -0.0280*(*x)[4]+0.6309*(*x)[5]+0.7148*(*x)[6]+0.2304*(*x)[7];
      (*x)[7]=(*x)[6]; (*x)[6]=(*x)[5]; (*x)[5]=(*x)[4];
      (*x)[4]=(*x)[3]; (*x)[3]=(*x)[2]; (*x)[2]=(*x)[1];
      (*x)[1]=(*x)[0];
      return fY;
}

float filterDB4::applyHI_D(float value, float (*x)[8]){
//HI_D = -0.2304 0.7148 -0.6309 -0.0280 0.1870 0.0308 -0.0329 -0.0106
      (*x)[0]=value;
      fY=-0.2304*(*x)[0]+0.7148*(*x)[1]-0.6309*(*x)[2]-0.0280*(*x)[3]
         +0.1870*(*x)[4]+0.0308*(*x)[5]-0.0329*(*x)[6]-0.0106*(*x)[7];
      (*x)[7]=(*x)[6]; (*x)[6]=(*x)[5]; (*x)[5]=(*x)[4];
      (*x)[4]=(*x)[3]; (*x)[3]=(*x)[2]; (*x)[2]=(*x)[1];
      (*x)[1]=(*x)[0];
      return fY;
}

float filterDB4::applyLO_R(float value, float (*x)[8]){
//LO_R = 0.2304 0.7148 0.6309 -0.0280 -0.1870 0.0308 0.0329 -0.0106
      (*x)[0]=value;
      fY= 0.2304*(*x)[0]+0.7148*(*x)[1]+0.6309*(*x)[2]-0.0280*(*x)[3]
         -0.1870*(*x)[4]+0.0308*(*x)[5]+0.0329*(*x)[6]-0.0106*(*x)[7];
      (*x)[7]=(*x)[6]; (*x)[6]=(*x)[5]; (*x)[5]=(*x)[4];
      (*x)[4]=(*x)[3]; (*x)[3]=(*x)[2]; (*x)[2]=(*x)[1];
      (*x)[1]=(*x)[0];
      return fY;
}

float filterDB4::applyHI_R(float value, float (*x)[8]){
//HI_R = -0.0106 -0.0329 0.0308 0.1870 -0.0280 -0.6309 0.7148 -0.2304
      (*x)[0]=value;
      fY=-0.0106*(*x)[0]-0.0329*(*x)[1]+0.0308*(*x)[2]+0.1870*(*x)[3]
         -0.0280*(*x)[4]-0.6309*(*x)[5]+0.7148*(*x)[6]-0.2304*(*x)[7];
      (*x)[7]=(*x)[6]; (*x)[6]=(*x)[5]; (*x)[5]=(*x)[4];
      (*x)[4]=(*x)[3]; (*x)[3]=(*x)[2]; (*x)[2]=(*x)[1];
      (*x)[1]=(*x)[0];
      return fY;
}

#endif
