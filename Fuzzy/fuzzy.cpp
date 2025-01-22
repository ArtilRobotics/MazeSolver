
//***********************************************************************
#include <Arduino.h>

#include "fis_header.h"

// Number of inputs to the fuzzy inference system
const int fis_gcI = 4;
// Number of outputs to the fuzzy inference system
const int fis_gcO = 2;
// Number of rules to the fuzzy inference system
const int fis_gcR = 77;


FIS_TYPE g_fisInput[fis_gcI];
FIS_TYPE g_fisOutput[fis_gcO];

#include <LaberintoMotor.h>
#include <LaberintoSensores.h>

// sensores infrarrojos
int RRLed[] = {A4, A5, A6}; // RF RD RS
int RLLed[] = {A9, A8, A7}; // LF LD LS
int ELed[] = {15, 13, 14};  // F D S
int sensores[7];
// Motor_Izq
#define MA 4
#define AIN1 6
#define AIN2 5
// Motor_Der
#define MB 9
#define BIN1 7
#define BIN2 8
// Encoders
#define ED1 10
#define ED2 11
#define EI1 2
#define EI2 3
// varios
#define Led_rojo 27
#define buzz 32
#define Volt_Battery A12

// distancias
int cerca = 900;
int medio = 525;
int lejos = 150;
// velocidades
int low = 75;
int medium = 150;
int fast = 225;

int _sensor[7];
int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int val6 = 0;

LaberintoMotor motor(MA, AIN1, AIN2, MB, BIN1, BIN2);
LaberintoSensores Distancias(RRLed, RLLed, ELed);

void recto()
{
    motor.velmotor(150, 150);
    delay(50);
    motor.freno(1, 1);
}
void derecha()
{
    motor.velmotor(150, 150);
    delay(100);
    motor.freno(1, 1);
    delay(10);
    motor.velmotor(150, -150);
    delay(50);
    motor.freno(1, 1);
}
void izquierda()
{
    motor.velmotor(150, 150);
    delay(100);
    motor.freno(1, 1);
    delay(10);
    motor.velmotor(-150, 150);
    delay(50);
    motor.freno(1, 1);
}
void mediaVuelta()
{
    motor.velmotor(150, -150);
    delay(100);
    motor.freno(1, 1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//***********************************************************************
// Support functions for Fuzzy Inference System                          
//***********************************************************************
// Triangular Member Function
FIS_TYPE fis_trimf(FIS_TYPE x, FIS_TYPE* p)
{
    FIS_TYPE a = p[0], b = p[1], c = p[2];
    FIS_TYPE t1 = (x - a) / (b - a);
    FIS_TYPE t2 = (c - x) / (c - b);
    if ((a == b) && (b == c)) return (FIS_TYPE) (x == a);
    if (a == b) return (FIS_TYPE) (t2*(b <= x)*(x <= c));
    if (b == c) return (FIS_TYPE) (t1*(a <= x)*(x <= b));
    t1 = min(t1, t2);
    return (FIS_TYPE) max(t1, 0);
}

// Trapezoidal Member Function
FIS_TYPE fis_trapmf(FIS_TYPE x, FIS_TYPE* p)
{
    FIS_TYPE a = p[0], b = p[1], c = p[2], d = p[3];
    FIS_TYPE t1 = ((x <= c) ? 1 : ((d < x) ? 0 : ((c != d) ? ((d - x) / (d - c)) : 0)));
    FIS_TYPE t2 = ((b <= x) ? 1 : ((x < a) ? 0 : ((a != b) ? ((x - a) / (b - a)) : 0)));
    return (FIS_TYPE) min(t1, t2);
}

FIS_TYPE fis_min(FIS_TYPE a, FIS_TYPE b)
{
    return min(a, b);
}

FIS_TYPE fis_max(FIS_TYPE a, FIS_TYPE b)
{
    return max(a, b);
}

FIS_TYPE fis_array_operation(FIS_TYPE *array, int size, _FIS_ARR_OP pfnOp)
{
    int i;
    FIS_TYPE ret = 0;

    if (size == 0) return ret;
    if (size == 1) return array[0];

    ret = array[0];
    for (i = 1; i < size; i++)
    {
        ret = (*pfnOp)(ret, array[i]);
    }

    return ret;
}


//***********************************************************************
// Data for Fuzzy Inference System                                       
//***********************************************************************
// Pointers to the implementations of member functions
_FIS_MF fis_gMF[] =
{
    fis_trimf, fis_trapmf
};

// Count of member function for each Input
int fis_gIMFCount[] = { 3, 3, 3, 3 };

// Count of member function for each Output 
int fis_gOMFCount[] = { 2, 2 };

// Coefficients for the Input Member Functions
FIS_TYPE fis_gMFI0Coeff1[] = { 0, 0, 30.28 };
FIS_TYPE fis_gMFI0Coeff2[] = { 6.59, 56.6, 110 };
FIS_TYPE fis_gMFI0Coeff3[] = { 66.1, 266, 1023, 1023 };
FIS_TYPE* fis_gMFI0Coeff[] = { fis_gMFI0Coeff1, fis_gMFI0Coeff2, fis_gMFI0Coeff3 };
FIS_TYPE fis_gMFI1Coeff1[] = { -60.7333924441019, -60.7333924441019, 109.296607555898, 199.296607555898 };
FIS_TYPE fis_gMFI1Coeff2[] = { 147.935080956052, 247.935080956052, 347.935080956052 };
FIS_TYPE fis_gMFI1Coeff3[] = { 235.8, 405.8, 1023, 1023 };
FIS_TYPE* fis_gMFI1Coeff[] = { fis_gMFI1Coeff1, fis_gMFI1Coeff2, fis_gMFI1Coeff3 };
FIS_TYPE fis_gMFI2Coeff1[] = { -36.2838781804163, -36.2838781804163, 178.686121819584 };
FIS_TYPE fis_gMFI2Coeff2[] = { 149.375258288358, 208.805258288358, 268.845258288358 };
FIS_TYPE fis_gMFI2Coeff3[] = { 239.690824980725, 354.690824980725, 1179.69082498073, 1179.69082498073 };
FIS_TYPE* fis_gMFI2Coeff[] = { fis_gMFI2Coeff1, fis_gMFI2Coeff2, fis_gMFI2Coeff3 };
FIS_TYPE fis_gMFI3Coeff1[] = { 0, 0, 300 };
FIS_TYPE fis_gMFI3Coeff2[] = { 200, 400, 700 };
FIS_TYPE fis_gMFI3Coeff3[] = { 600, 800, 1023, 1023 };
FIS_TYPE* fis_gMFI3Coeff[] = { fis_gMFI3Coeff1, fis_gMFI3Coeff2, fis_gMFI3Coeff3 };
FIS_TYPE** fis_gMFICoeff[] = { fis_gMFI0Coeff, fis_gMFI1Coeff, fis_gMFI2Coeff, fis_gMFI3Coeff };

// Coefficients for the Output Member Functions
FIS_TYPE fis_gMFO0Coeff1[] = { 0, 0, 6.25 };
FIS_TYPE fis_gMFO0Coeff2[] = { 0, 25, 50, 50 };
FIS_TYPE* fis_gMFO0Coeff[] = { fis_gMFO0Coeff1, fis_gMFO0Coeff2 };
FIS_TYPE fis_gMFO1Coeff1[] = { 0, 0, 0, 6.25 };
FIS_TYPE fis_gMFO1Coeff2[] = { 0, 25, 50, 50 };
FIS_TYPE* fis_gMFO1Coeff[] = { fis_gMFO1Coeff1, fis_gMFO1Coeff2 };
FIS_TYPE** fis_gMFOCoeff[] = { fis_gMFO0Coeff, fis_gMFO1Coeff };

// Input membership function set
int fis_gMFI0[] = { 0, 0, 1 };
int fis_gMFI1[] = { 1, 0, 1 };
int fis_gMFI2[] = { 0, 0, 1 };
int fis_gMFI3[] = { 0, 0, 1 };
int* fis_gMFI[] = { fis_gMFI0, fis_gMFI1, fis_gMFI2, fis_gMFI3};

// Output membership function set
int fis_gMFO0[] = { 0, 1 };
int fis_gMFO1[] = { 1, 1 };
int* fis_gMFO[] = { fis_gMFO0, fis_gMFO1};

// Rule Weights
FIS_TYPE fis_gRWeight[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

// Rule Type
int fis_gRType[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

// Rule Inputs
int fis_gRI0[] = { 1, 1, 1, 2 };
int fis_gRI1[] = { 1, 1, 1, 3 };
int fis_gRI2[] = { 1, 1, 2, 1 };
int fis_gRI3[] = { 1, 1, 2, 2 };
int fis_gRI4[] = { 1, 1, 2, 3 };
int fis_gRI5[] = { 1, 1, 3, 1 };
int fis_gRI6[] = { 1, 1, 3, 2 };
int fis_gRI7[] = { 1, 1, 3, 3 };
int fis_gRI8[] = { 1, 2, 1, 1 };
int fis_gRI9[] = { 1, 2, 1, 2 };
int fis_gRI10[] = { 1, 2, 1, 3 };
int fis_gRI11[] = { 1, 2, 2, 1 };
int fis_gRI12[] = { 1, 2, 2, 2 };
int fis_gRI13[] = { 1, 2, 2, 3 };
int fis_gRI14[] = { 1, 2, 3, 1 };
int fis_gRI15[] = { 1, 2, 3, 2 };
int fis_gRI16[] = { 1, 2, 3, 3 };
int fis_gRI17[] = { 1, 3, 1, 1 };
int fis_gRI18[] = { 1, 3, 1, 2 };
int fis_gRI19[] = { 1, 3, 1, 3 };
int fis_gRI20[] = { 1, 3, 2, 1 };
int fis_gRI21[] = { 1, 3, 2, 2 };
int fis_gRI22[] = { 1, 3, 2, 3 };
int fis_gRI23[] = { 1, 3, 3, 1 };
int fis_gRI24[] = { 1, 3, 3, 2 };
int fis_gRI25[] = { 1, 3, 3, 3 };
int fis_gRI26[] = { 2, 1, 1, 1 };
int fis_gRI27[] = { 2, 1, 1, 2 };
int fis_gRI28[] = { 2, 1, 1, 3 };
int fis_gRI29[] = { 2, 1, 2, 1 };
int fis_gRI30[] = { 2, 1, 2, 2 };
int fis_gRI31[] = { 2, 1, 2, 3 };
int fis_gRI32[] = { 2, 1, 3, 1 };
int fis_gRI33[] = { 2, 1, 3, 2 };
int fis_gRI34[] = { 2, 1, 3, 3 };
int fis_gRI35[] = { 2, 2, 1, 1 };
int fis_gRI36[] = { 2, 2, 1, 2 };
int fis_gRI37[] = { 2, 2, 1, 3 };
int fis_gRI38[] = { 2, 2, 2, 1 };
int fis_gRI39[] = { 2, 2, 2, 2 };
int fis_gRI40[] = { 2, 2, 2, 3 };
int fis_gRI41[] = { 2, 2, 3, 1 };
int fis_gRI42[] = { 2, 2, 3, 2 };
int fis_gRI43[] = { 2, 2, 3, 3 };
int fis_gRI44[] = { 2, 3, 1, 1 };
int fis_gRI45[] = { 2, 3, 1, 2 };
int fis_gRI46[] = { 2, 3, 1, 3 };
int fis_gRI47[] = { 2, 3, 2, 1 };
int fis_gRI48[] = { 2, 3, 2, 2 };
int fis_gRI49[] = { 2, 3, 2, 3 };
int fis_gRI50[] = { 2, 3, 3, 1 };
int fis_gRI51[] = { 2, 3, 3, 2 };
int fis_gRI52[] = { 2, 3, 3, 3 };
int fis_gRI53[] = { 3, 1, 1, 1 };
int fis_gRI54[] = { 3, 1, 1, 2 };
int fis_gRI55[] = { 3, 1, 1, 3 };
int fis_gRI56[] = { 3, 1, 2, 1 };
int fis_gRI57[] = { 3, 1, 2, 2 };
int fis_gRI58[] = { 3, 1, 2, 3 };
int fis_gRI59[] = { 3, 1, 3, 1 };
int fis_gRI60[] = { 3, 1, 3, 2 };
int fis_gRI61[] = { 3, 1, 3, 3 };
int fis_gRI62[] = { 3, 2, 1, 1 };
int fis_gRI63[] = { 3, 2, 1, 2 };
int fis_gRI64[] = { 3, 2, 1, 3 };
int fis_gRI65[] = { 3, 2, 2, 1 };
int fis_gRI66[] = { 3, 2, 2, 2 };
int fis_gRI67[] = { 3, 2, 2, 3 };
int fis_gRI68[] = { 3, 2, 3, 1 };
int fis_gRI69[] = { 3, 2, 3, 2 };
int fis_gRI70[] = { 3, 2, 3, 3 };
int fis_gRI71[] = { 3, 3, 1, 1 };
int fis_gRI72[] = { 3, 3, 1, 2 };
int fis_gRI73[] = { 3, 3, 1, 3 };
int fis_gRI74[] = { 3, 3, 2, 1 };
int fis_gRI75[] = { 3, 3, 2, 2 };
int fis_gRI76[] = { 3, 3, 3, 1 };
int* fis_gRI[] = { fis_gRI0, fis_gRI1, fis_gRI2, fis_gRI3, fis_gRI4, fis_gRI5, fis_gRI6, fis_gRI7, fis_gRI8, fis_gRI9, fis_gRI10, fis_gRI11, fis_gRI12, fis_gRI13, fis_gRI14, fis_gRI15, fis_gRI16, fis_gRI17, fis_gRI18, fis_gRI19, fis_gRI20, fis_gRI21, fis_gRI22, fis_gRI23, fis_gRI24, fis_gRI25, fis_gRI26, fis_gRI27, fis_gRI28, fis_gRI29, fis_gRI30, fis_gRI31, fis_gRI32, fis_gRI33, fis_gRI34, fis_gRI35, fis_gRI36, fis_gRI37, fis_gRI38, fis_gRI39, fis_gRI40, fis_gRI41, fis_gRI42, fis_gRI43, fis_gRI44, fis_gRI45, fis_gRI46, fis_gRI47, fis_gRI48, fis_gRI49, fis_gRI50, fis_gRI51, fis_gRI52, fis_gRI53, fis_gRI54, fis_gRI55, fis_gRI56, fis_gRI57, fis_gRI58, fis_gRI59, fis_gRI60, fis_gRI61, fis_gRI62, fis_gRI63, fis_gRI64, fis_gRI65, fis_gRI66, fis_gRI67, fis_gRI68, fis_gRI69, fis_gRI70, fis_gRI71, fis_gRI72, fis_gRI73, fis_gRI74, fis_gRI75, fis_gRI76 };

// Rule Outputs
int fis_gRO0[] = { 1, 2 };
int fis_gRO1[] = { 1, 2 };
int fis_gRO2[] = { 2, 2 };
int fis_gRO3[] = { 2, 2 };
int fis_gRO4[] = { 2, 2 };
int fis_gRO5[] = { 2, 2 };
int fis_gRO6[] = { 2, 2 };
int fis_gRO7[] = { 2, 2 };
int fis_gRO8[] = { 1, 2 };
int fis_gRO9[] = { 1, 2 };
int fis_gRO10[] = { 1, 2 };
int fis_gRO11[] = { 2, 2 };
int fis_gRO12[] = { 2, 2 };
int fis_gRO13[] = { 2, 2 };
int fis_gRO14[] = { 2, 2 };
int fis_gRO15[] = { 2, 2 };
int fis_gRO16[] = { 2, 2 };
int fis_gRO17[] = { 1, 2 };
int fis_gRO18[] = { 1, 2 };
int fis_gRO19[] = { 1, 2 };
int fis_gRO20[] = { 1, 1 };
int fis_gRO21[] = { 1, 1 };
int fis_gRO22[] = { 1, 1 };
int fis_gRO23[] = { 2, 1 };
int fis_gRO24[] = { 2, 1 };
int fis_gRO25[] = { 2, 1 };
int fis_gRO26[] = { 1, 2 };
int fis_gRO27[] = { 1, 2 };
int fis_gRO28[] = { 1, 2 };
int fis_gRO29[] = { 2, 2 };
int fis_gRO30[] = { 2, 2 };
int fis_gRO31[] = { 2, 2 };
int fis_gRO32[] = { 2, 2 };
int fis_gRO33[] = { 2, 2 };
int fis_gRO34[] = { 2, 2 };
int fis_gRO35[] = { 1, 2 };
int fis_gRO36[] = { 1, 2 };
int fis_gRO37[] = { 1, 2 };
int fis_gRO38[] = { 2, 2 };
int fis_gRO39[] = { 2, 2 };
int fis_gRO40[] = { 2, 2 };
int fis_gRO41[] = { 2, 2 };
int fis_gRO42[] = { 2, 2 };
int fis_gRO43[] = { 2, 2 };
int fis_gRO44[] = { 1, 2 };
int fis_gRO45[] = { 1, 2 };
int fis_gRO46[] = { 1, 2 };
int fis_gRO47[] = { 1, 1 };
int fis_gRO48[] = { 1, 1 };
int fis_gRO49[] = { 1, 1 };
int fis_gRO50[] = { 2, 1 };
int fis_gRO51[] = { 2, 1 };
int fis_gRO52[] = { 2, 1 };
int fis_gRO53[] = { 1, 2 };
int fis_gRO54[] = { 1, 2 };
int fis_gRO55[] = { 1, 2 };
int fis_gRO56[] = { 2, 1 };
int fis_gRO57[] = { 2, 1 };
int fis_gRO58[] = { 2, 1 };
int fis_gRO59[] = { 2, 1 };
int fis_gRO60[] = { 2, 1 };
int fis_gRO61[] = { 2, 1 };
int fis_gRO62[] = { 1, 2 };
int fis_gRO63[] = { 1, 2 };
int fis_gRO64[] = { 1, 2 };
int fis_gRO65[] = { 2, 1 };
int fis_gRO66[] = { 2, 1 };
int fis_gRO67[] = { 2, 1 };
int fis_gRO68[] = { 2, 1 };
int fis_gRO69[] = { 2, 1 };
int fis_gRO70[] = { 2, 1 };
int fis_gRO71[] = { 1, 2 };
int fis_gRO72[] = { 1, 2 };
int fis_gRO73[] = { 1, 2 };
int fis_gRO74[] = { 2, 1 };
int fis_gRO75[] = { 2, 1 };
int fis_gRO76[] = { 2, 1 };
int* fis_gRO[] = { fis_gRO0, fis_gRO1, fis_gRO2, fis_gRO3, fis_gRO4, fis_gRO5, fis_gRO6, fis_gRO7, fis_gRO8, fis_gRO9, fis_gRO10, fis_gRO11, fis_gRO12, fis_gRO13, fis_gRO14, fis_gRO15, fis_gRO16, fis_gRO17, fis_gRO18, fis_gRO19, fis_gRO20, fis_gRO21, fis_gRO22, fis_gRO23, fis_gRO24, fis_gRO25, fis_gRO26, fis_gRO27, fis_gRO28, fis_gRO29, fis_gRO30, fis_gRO31, fis_gRO32, fis_gRO33, fis_gRO34, fis_gRO35, fis_gRO36, fis_gRO37, fis_gRO38, fis_gRO39, fis_gRO40, fis_gRO41, fis_gRO42, fis_gRO43, fis_gRO44, fis_gRO45, fis_gRO46, fis_gRO47, fis_gRO48, fis_gRO49, fis_gRO50, fis_gRO51, fis_gRO52, fis_gRO53, fis_gRO54, fis_gRO55, fis_gRO56, fis_gRO57, fis_gRO58, fis_gRO59, fis_gRO60, fis_gRO61, fis_gRO62, fis_gRO63, fis_gRO64, fis_gRO65, fis_gRO66, fis_gRO67, fis_gRO68, fis_gRO69, fis_gRO70, fis_gRO71, fis_gRO72, fis_gRO73, fis_gRO74, fis_gRO75, fis_gRO76 };

// Input range Min
FIS_TYPE fis_gIMin[] = { 0, 0, 0, 0 };

// Input range Max
FIS_TYPE fis_gIMax[] = { 1023, 1023, 1023, 1023 };

// Output range Min
FIS_TYPE fis_gOMin[] = { 0, 0 };

// Output range Max
FIS_TYPE fis_gOMax[] = { 50, 50 };

//***********************************************************************
// Data dependent support functions for Fuzzy Inference System           
//***********************************************************************
FIS_TYPE fis_MF_out(FIS_TYPE** fuzzyRuleSet, FIS_TYPE x, int o)
{
    FIS_TYPE mfOut;
    int r;

    for (r = 0; r < fis_gcR; ++r)
    {
        int index = fis_gRO[r][o];
        if (index > 0)
        {
            index = index - 1;
            mfOut = (fis_gMF[fis_gMFO[o][index]])(x, fis_gMFOCoeff[o][index]);
        }
        else if (index < 0)
        {
            index = -index - 1;
            mfOut = 1 - (fis_gMF[fis_gMFO[o][index]])(x, fis_gMFOCoeff[o][index]);
        }
        else
        {
            mfOut = 0;
        }

        fuzzyRuleSet[0][r] = fis_min(mfOut, fuzzyRuleSet[1][r]);
    }
    return fis_array_operation(fuzzyRuleSet[0], fis_gcR, fis_max);
}

FIS_TYPE fis_defuzz_centroid(FIS_TYPE** fuzzyRuleSet, int o)
{
    FIS_TYPE step = (fis_gOMax[o] - fis_gOMin[o]) / (FIS_RESOLUSION - 1);
    FIS_TYPE area = 0;
    FIS_TYPE momentum = 0;
    FIS_TYPE dist, slice;
    int i;

    // calculate the area under the curve formed by the MF outputs
    for (i = 0; i < FIS_RESOLUSION; ++i){
        dist = fis_gOMin[o] + (step * i);
        slice = step * fis_MF_out(fuzzyRuleSet, dist, o);
        area += slice;
        momentum += slice*dist;
    }

    return ((area == 0) ? ((fis_gOMax[o] + fis_gOMin[o]) / 2) : (momentum / area));
}

//***********************************************************************
// Fuzzy Inference System                                                
//***********************************************************************
void fis_evaluate()
{
    FIS_TYPE fuzzyInput0[] = { 0, 0, 0 };
    FIS_TYPE fuzzyInput1[] = { 0, 0, 0 };
    FIS_TYPE fuzzyInput2[] = { 0, 0, 0 };
    FIS_TYPE fuzzyInput3[] = { 0, 0, 0 };
    FIS_TYPE* fuzzyInput[fis_gcI] = { fuzzyInput0, fuzzyInput1, fuzzyInput2, fuzzyInput3, };
    FIS_TYPE fuzzyOutput0[] = { 0, 0 };
    FIS_TYPE fuzzyOutput1[] = { 0, 0 };
    FIS_TYPE* fuzzyOutput[fis_gcO] = { fuzzyOutput0, fuzzyOutput1, };
    FIS_TYPE fuzzyRules[fis_gcR] = { 0 };
    FIS_TYPE fuzzyFires[fis_gcR] = { 0 };
    FIS_TYPE* fuzzyRuleSet[] = { fuzzyRules, fuzzyFires };
    FIS_TYPE sW = 0;

    // Transforming input to fuzzy Input
    int i, j, r, o;
    for (i = 0; i < fis_gcI; ++i)
    {
        for (j = 0; j < fis_gIMFCount[i]; ++j)
        {
            fuzzyInput[i][j] =
                (fis_gMF[fis_gMFI[i][j]])(g_fisInput[i], fis_gMFICoeff[i][j]);
        }
    }

    int index = 0;
    for (r = 0; r < fis_gcR; ++r)
    {
        if (fis_gRType[r] == 1)
        {
            fuzzyFires[r] = FIS_MAX;
            for (i = 0; i < fis_gcI; ++i)
            {
                index = fis_gRI[r][i];
                if (index > 0)
                    fuzzyFires[r] = fis_min(fuzzyFires[r], fuzzyInput[i][index - 1]);
                else if (index < 0)
                    fuzzyFires[r] = fis_min(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
                else
                    fuzzyFires[r] = fis_min(fuzzyFires[r], 1);
            }
        }
        else
        {
            fuzzyFires[r] = FIS_MIN;
            for (i = 0; i < fis_gcI; ++i)
            {
                index = fis_gRI[r][i];
                if (index > 0)
                    fuzzyFires[r] = fis_max(fuzzyFires[r], fuzzyInput[i][index - 1]);
                else if (index < 0)
                    fuzzyFires[r] = fis_max(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
                else
                    fuzzyFires[r] = fis_max(fuzzyFires[r], 0);
            }
        }

        fuzzyFires[r] = fis_gRWeight[r] * fuzzyFires[r];
        sW += fuzzyFires[r];
    }

    if (sW == 0)
    {
        for (o = 0; o < fis_gcO; ++o)
        {
            g_fisOutput[o] = ((fis_gOMax[o] + fis_gOMin[o]) / 2);
        }
    }
    else
    {
        for (o = 0; o < fis_gcO; ++o)
        {
            g_fisOutput[o] = fis_defuzz_centroid(fuzzyRuleSet, o);
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Setup routine runs once when you press reset:
void setup()
{
    pinMode(13, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(A12, INPUT);
    Serial.begin(115200);
}

// Loop routine runs over and over again forever:
void loop()
{

    while (analogRead(A12) < 636)
    {
        digitalWrite(27, HIGH);
        // tone(buzz,104,200);
        // tone(buzz,740,200);
        // noTone(buzz);
        // Serial.println(analogRead(A12));
    }
    digitalWrite(27, LOW);

    for (int i = 0; i < 3; i++)
    {
        digitalWrite(ELed[i], HIGH);
        sensores[i * 2] = analogRead(RRLed[i]);
        sensores[i * 2 + 1] = analogRead(RLLed[i]);
        // Serial.print(sensores[i*2]);
        // Serial.print(", ");
        // Serial.println(sensores[i*2+1]);
        delay(10);
        digitalWrite(ELed[i], LOW);
    }

    val1 = sensores[0];
    val2 = sensores[1];
    val3 = sensores[2];
    val4 = sensores[3];
    val5 = sensores[4];
    val6 = sensores[5];

    Serial.println(val3);

    // Read Input: Diagonal_Derecho
    g_fisInput[0] = val5;
    // Read Input: Diagonal_Izquierdo
    g_fisInput[1] = val6;
    // Read Input: Lateral_Derecho
    g_fisInput[2] = val3;
    // Read Input: Lateral_Izquierdo
    g_fisInput[3] = val4;

    g_fisOutput[0] = 0;
    g_fisOutput[1] = 0;

    fis_evaluate();

    motor.velmotor(g_fisOutput[1],g_fisOutput[0]);
    
    // Set output vlaue: Velocidad_Derecha
    //analogWrite(2, g_fisOutput[0]);
    // Set output vlaue: Velocidad_Izquierda
    //analogWrite(3, g_fisOutput[1]);
}
