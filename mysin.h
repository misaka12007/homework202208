#define MYSIN

#include<cmath>

#define PI 3.1415926535897932384626433832795029

inline double sinToCos(double sinx){
    return sqrt(1-sinx*sinx);
};

inline double sinHalf(double sinx){
    return sqrt((1-sinToCos(sinx))/2.0);
};

inline double sinPlus(double sina,double sinb){
    return sina*sinToCos(sinb)+sinb*sinToCos(sina);
};

//Slow but accurate
#include<cmath>
double mySin1(double rad){
    double upper=PI/2;
    double upper_sin=1;
    double lower=0;
    double lower_sin=0;
    for(unsigned char i=0;i<48;++i){
        double medium=(upper+lower)/2.0;
        double medium_sin=sinHalf(sinPlus(upper_sin,lower_sin));
        if(rad<medium){
            upper=medium;
            upper_sin=medium_sin;
        }else if(rad>medium){
            lower=medium;
            lower_sin=medium_sin;
        }else{
            return medium_sin;
        };
    };
    return sinHalf(sinPlus(upper_sin,lower_sin));
};

//1E-8 precision, fast but eats ram
#include<cmath>
#include "mySinData.h"
double mySin2(double rad){
    #define sinToCos(sinx) (sqrt(1-sinx*sinx))
    unsigned char i=rad/0.006159985595274104;
    rad-=i*0.006159985595274104;
    unsigned char j=rad/2.415680625597688e-05;
    return mySin2Data1[i]*sinToCos(mySin2Data2[j])+mySin2Data2[j]*sinToCos(mySin2Data1[i]);
};


//1E-6 precision, very fast
double mySin3(double rad){
    #define x2(x) ((x)*(x))
    #define x3(x) ((x)*(x)*(x))
    #define x4(x) (x2(x2(x)))
    #define x5(x) (x2(x)*x3(x))
    #define x6(x) (x2(x3(x)))
    return -0.001*x6(rad)+0.0103*x5(rad)-0.002*x4(rad)-0.1655*x3(rad)-0.0003*x2(rad)+rad-(1e-6);
    #undef x2
    #undef x3
    #undef x4
    #undef x5
    #undef x6
};

//
#include<cmath>
double mySin4(double rad){
    if(abs(rad)<1E-14) return rad;
    double sin_=mySin4(rad/3.0);
    return 3*sin_-4*sin_*sin_*sin_;
};

//Taylor
double mySin5(double rad){
    #define odd(n) ((bool)((n)&1))
    double ans;
    for(unsigned char i=0;i<16;++i){
        unsigned long a=1;
        double b=1;
        for(unsigned char j=1;j<=2*i+1;++j){
            a*=j;
            b*=rad;
        };
        if(odd(i)) ans-=b/a;
        else ans+=b/a;
    };
    return ans;
};