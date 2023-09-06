//#include <hls_stream.h>
//#include <ap_axi_sdata.h>
#include<stdio.h>
#include"Header.h"
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <iomanip>
using namespace std;

#define USE_FLOAT

#ifdef USE_FLOAT
    typedef ap_axis<32,1,1,1> out_sdch_axis;
    typedef hls::stream<out_sdch_axis> out_stream;


#endif

#ifndef USE_FLOAT
    typedef ap_axis<64,1,1,1> out_sdch_axis;
    typedef hls::stream<out_sdch_axis> out_stream;


#endif


int main() {

out_stream output_stream;
out_sdch_axis readValOut;
float media = 0.50097;
conv cmedia;
conv cValOut;
cmedia.f = media;


RK4_LBE(output_stream,cmedia.i);

		for (int idx = 0; idx < Iterations; idx++) {
			output_stream.read(readValOut);
			cValOut.i=readValOut.data;
			cout <<cValOut.f<<endl;
		}

		return 0;
	}


