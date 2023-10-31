#ifndef Header
#define Header

#include "ap_fixed.h"
#include "hls_math.h"
#include <math.h>
#include "hls_math.h"
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <ap_int.h>

typedef ap_fixed<256,128> data_t;

//#define USE_FLOAT

#ifdef USE_FLOAT
    typedef ap_axis<32,1,1,1> out_sdch_axis;
    typedef hls::stream<out_sdch_axis> out_stream;
    const float h = 0.000001f;
    const float C1 = 0.00000001f;   // 10e-8 or 10 * 10^-9
    const float C2 = 0.0000001;   // 100e-9 or 100 * 10^-9
    const float L = 0.019f;        // 19e-3 or 19 * 10^-3
    const float R = 1800.00f;
    const float m0 = -0.00037f;    // -0.37 * 10^-3
    const float m1 = -0.00068f;    // -0.68 * 10^-3
    const float Bp = 1.1f;
    const float eq1 = 100000000.0f; // 1/10e-8
    const float eq2 = 10000000.0f;  // 1/100e-9
    const float eq3 = -(1.0 / (19.0  * powf(10.0f, -3.0f)));
    const float zero = 0.0f;
    const float halfm = 0.5f;
    const float twom = 0.5f;

    const float onem=1.0f;
    const float sixm=6.0f;
    typedef union {
    	uint32_t i;
    	float f;
    } conv;

#endif

#ifndef USE_FLOAT
    typedef ap_axis<64,1,1,1> out_sdch_axis;
    typedef hls::stream<out_sdch_axis> out_stream;
    const double h = 0.000001;
    const double C1 = 0.00000001;   // 10e-8 or 10 * 10^-9
    const double C2 = 0.0000001;   // 100e-9 or 100 * 10^-9
    const double L = 0.019;        // 19e-3 or 19 * 10^-3
    const double R = 1800.00;
    const double m0 = -0.00037;    // -0.37 * 10^-3
    const double m1 = -0.00068;    // -0.68 * 10^-3
    const double Bp = 1.1;
    const double eq1 = 100000000.0; // 1/10e-8
    const double eq2 = 10000000.0;  // 1/100e-9
    const double eq3 = -(1.0 / (19.0  * pow(10.0, -3.0)));
    const double zero = 0.0;
    const double halfm = 0.5;
    const double onem=1.0;
    const float twom = 2.0;
    const double sixm=6.0;
    typedef union {
    	uint64_t i;
    	double f;
    } conv;

#endif


void CCE_B_64(out_stream &output_stream,unsigned int media,unsigned int Iterat);


#endif














