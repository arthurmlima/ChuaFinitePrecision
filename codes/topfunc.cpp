#include"Header.h"
#include<stdio.h>
#include "hls_math.h"

//#define USE_FLOAT
//#define ORBIT_1_ONLY
//#define ORBIT_2_ONLY
#define BOTH_ORBITS

void RK4_LBE_B_64(out_stream &output_stream,unsigned int media) {
#pragma HLS INTERFACE axis port=output_stream
#pragma HLS INTERFACE s_axilite port=media bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL




#ifdef USE_FLOAT
	conv c;
	c.i=media;
	float K1 = 0, K2 = 0, K3 = 0, K4 = 0, L1 = 0, L2 = 0, L3 = 0, L4 = 0, M1 = 0, M2 = 0, M3 = 0, M4 = 0;


	float x,y,z;
	x = c.f;
	y = -0.2;
	z = 0.0;

	float x2,y2,z2;
	x2 = c.f;
	y2 = -0.2;
	z2 = 0.0;

	float xeqabs=0.0,xeq=0.0;

	float xd = 0;

	float yd = 0;

	float zd = 0;

	float id;

#else
	conv c;
	c.i=media;
	double K1 = 0, K2 = 0, K3 = 0, K4 = 0, L1 = 0, L2 = 0, L3 = 0, L4 = 0, M1 = 0, M2 = 0, M3 = 0, M4 = 0;


	double x,y,z;
	x = c.f;
	y = -0.2;
	z = 0.0;

	double x2,y2,z2;
	x2 = c.f;
	y2 = -0.2;
	z2 = 0.0;

	double xeqabs=0.0,xeq=0.0;

	double xd = 0;

	double yd = 0;

	double zd = 0;

	double id;

#endif

for (int i = 0; i < Iterations; i++){
#pragma HLS PIPELINE off

    out_sdch_axis output;
    conv dataui;

    #ifdef ORBIT_1_ONLY
        // computations for pseudo-orbit-1
        K1 = 0;
		K2 = 0;
		K3 = 0;
		K4 = 0;
		L1 = 0;
		L2 = 0;
		L3 = 0;
		L4 = 0;
		M1 = 0;
		M2 = 0;
		M3 = 0;
		M4 = 0;

        xd=0;
        yd=0;
        zd=0;

		/*This is the begin of pseudo-orbit-1*/
		if (x > Bp) {
			id = (m0 * x + Bp * (m1 - m0));
		}
		else if (x < -Bp) {
			id = (m0 * x + Bp * (m0 - m1));
		}
		else {
			id = (m1 * x);
		}

		K1 = eq1*((y - x)/R - id);
		L1 = eq2 * ( (x - y)/R+z );
		M1 = eq3 * y;

		xd = x + h * (0.5) * K1;
		yd = y + h * (0.5) * L1;
		zd = z + (0.5) * h * M1;

		if (xd > Bp) {
			id = m0 * xd + Bp * (m1 - m0);
		}
		else if (xd < (-Bp)) {
			id = m0 * xd + Bp * (m0 - m1);
		}
		else {
			id = m1 * xd;
		}

		K2=  eq1 * ((yd - xd)/R - id);
		L2 = eq2 * ((xd - yd)/R+zd );
		M2 = eq3 *  yd;


		xd = x + h * (0.5) * K2;
		yd = y + h * (0.5) * L2;
		zd = z + (0.5) * h * M2;

		if (xd > Bp) {
			id = m0 * xd + Bp * (m1 - m0);
		}
		else if (xd < (-Bp)) {
			id = m0 * xd + Bp * (m0 - m1);
		}
		else {
			id = m1 * xd;
		}
		K3 = eq1*((yd - xd)/R - id);
		L3 = eq2 * ( (xd - yd)/R+zd );
		M3 = eq3 * yd;

		xd = x + h * K3;
		yd = y + h * L3;
		zd = z + h * M3;

		if (xd > Bp) {
			id = m0 * xd + Bp * (m1 - m0);
		}
		else if (xd < (-Bp)) {
			id = m0 * xd + Bp * (m0 - m1);
		}
		else {
			id = m1 * xd;
		}

		K4 = eq1*((yd - xd)/R - id);
		L4 = eq2 * ( (xd - yd)/R+zd );
		M4 = eq3 * yd;

		x = x + h * (1.0 / 6.0) * (K1 + (2.0) * K2 + (2.0) * K3 + K4);
		y = y + h * (1.0 / 6.0) * (L1 + (2.0) * L2 + (2.0) * L3 + L4);
		z = z + h * (1.0 / 6.0) * (M1 + (2.0) * M2 + (2.0) * M3 + M4);
/*This is the end of pseudo-orbit-1*/

        dataui.f = x;
    #endif

    #ifdef ORBIT_2_ONLY
        // computations for pseudo-orbit-2
		K1 = 0;
		K2 = 0;
		K3 = 0;
		K4 = 0;
		L1 = 0;
		L2 = 0;
		L3 = 0;
		L4 = 0;
		M1 = 0;
		M2 = 0;
		M3 = 0;
		M4 = 0;

        xd=0;
        yd=0;
        zd=0;

		/*This is the begin of pseudo-orbit-2*/
		if (x2 > Bp) {
			id = (m0 * x2 + Bp * (m1 - m0));
		}
		else if (x2 < -Bp) {
			id = (m0 * x2 + Bp * (m0 - m1));
		}
		else {
			id = (m1 * x2);
		}


		K1 = eq1*(y2/R - x2/R - id);
		L1 = eq2 * ( (x2 - y2)/R+z2 );
		M1 = eq3 * y2;


		xd = x2 + h * (0.5) * K1;
		yd = y2 + h * (0.5) * L1;
		zd = z2 + (0.5) * h * M1;


		if (xd > Bp) {
			id = m0 * xd + Bp * (m1 - m0);
		}
		else if (xd < (-Bp)) {
			id = m0 * xd + Bp * (m0 - m1);
		}
		else {
			id = m1 * xd;
		}

		K2 = eq1*(yd/R - xd/R - id);
		L2 = eq2 * ( (xd - yd)/R+zd );
		M2 = eq3 * yd;

		xd = x2 + h * (0.5) * K2;
		yd = y2 + h * (0.5) * L2;
		zd = z2 + (0.5) * h * M2;

		if (xd > Bp) {
			id = m0 * xd + Bp * (m1 - m0);
		}
		else if (xd < (-Bp)) {
			id = m0 * xd + Bp * (m0 - m1);
		}
		else {
			id = m1 * xd;
		}
		K3 = eq1*(yd/R - xd/R - id);
		L3 = eq2 * ( (xd - yd)/R+zd );
		M3 = eq3 * yd;


		xd = x2 + h * K3;
		yd = y2 + h * L3;
		zd = z2 + h * M3;


		if (xd > Bp) {
			id = m0 * xd + Bp * (m1 - m0);
		}
		else if (xd < (-Bp)) {
			id = m0 * xd + Bp * (m0 - m1);
		}
		else {
			id = m1 * xd;
		}

		K4 = eq1*(yd/R - xd/R - id);
		L4 = eq2 * ( (xd - yd)/R+zd );
		M4 = eq3 * yd;


		x2 = x2 + h * (1.0 / 6.0) * (K1 + (2.0) * K2 + (2.0) * K3 + K4);
		y2 = y2 + h * (1.0 / 6.0) * (L1 + (2.0) * L2 + (2.0) * L3 + L4);
		z2 = z2 + h * (1.0 / 6.0) * (M1 + (2.0) * M2 + (2.0) * M3 + M4);
/*this is the end of pseudo-orbit-2*/
        dataui.f = x2;
    #endif

    #ifdef BOTH_ORBITS
		K1 = 0;
		K2 = 0;
		K3 = 0;
		K4 = 0;
		L1 = 0;
		L2 = 0;
		L3 = 0;
		L4 = 0;
		M1 = 0;
		M2 = 0;
		M3 = 0;
		M4 = 0;

        xd=0;
        yd=0;
        zd=0;
        // computations for pseudo-orbit-1
		/*This is the begin of pseudo-orbit-1*/
		if (x > Bp) {
			id = (m0 * x + Bp * (m1 - m0));
		}
		else if (x < -Bp) {
			id = (m0 * x + Bp * (m0 - m1));
		}
		else {
			id = (m1 * x);
		}

		K1 = eq1*((y - x)/R - id);
		L1 = eq2 * ( (x - y)/R+z );
		M1 = eq3 * y;

		xd = x + h * (0.5) * K1;
		yd = y + h * (0.5) * L1;
		zd = z + (0.5) * h * M1;

		if (xd > Bp) {
			id = m0 * xd + Bp * (m1 - m0);
		}
		else if (xd < (-Bp)) {
			id = m0 * xd + Bp * (m0 - m1);
		}
		else {
			id = m1 * xd;
		}

		K2=  eq1 * ((yd - xd)/R - id);
		L2 = eq2 * ((xd - yd)/R+zd );
		M2 = eq3 *  yd;


		xd = x + h * (0.5) * K2;
		yd = y + h * (0.5) * L2;
		zd = z + (0.5) * h * M2;

		if (xd > Bp) {
			id = m0 * xd + Bp * (m1 - m0);
		}
		else if (xd < (-Bp)) {
			id = m0 * xd + Bp * (m0 - m1);
		}
		else {
			id = m1 * xd;
		}
		K3 = eq1*((yd - xd)/R - id);
		L3 = eq2 * ( (xd - yd)/R+zd );
		M3 = eq3 * yd;

		xd = x + h * K3;
		yd = y + h * L3;
		zd = z + h * M3;

		if (xd > Bp) {
			id = m0 * xd + Bp * (m1 - m0);
		}
		else if (xd < (-Bp)) {
			id = m0 * xd + Bp * (m0 - m1);
		}
		else {
			id = m1 * xd;
		}

		K4 = eq1*((yd - xd)/R - id);
		L4 = eq2 * ( (xd - yd)/R+zd );
		M4 = eq3 * yd;

		x = x + h * (1.0 / 6.0) * (K1 + (2.0) * K2 + (2.0) * K3 + K4);
		y = y + h * (1.0 / 6.0) * (L1 + (2.0) * L2 + (2.0) * L3 + L4);
		z = z + h * (1.0 / 6.0) * (M1 + (2.0) * M2 + (2.0) * M3 + M4);
/*This is the end of pseudo-orbit-1*/


		K1 = 0;
		K2 = 0;
		K3 = 0;
		K4 = 0;
		L1 = 0;
		L2 = 0;
		L3 = 0;
		L4 = 0;
		M1 = 0;
		M2 = 0;
		M3 = 0;
		M4 = 0;

        xd=0;
        yd=0;
        zd=0;



/*This is the begin of pseudo-orbit-2*/
		if (x2 > Bp) {
			id = (m0 * x2 + Bp * (m1 - m0));
		}
		else if (x2 < -Bp) {
			id = (m0 * x2 + Bp * (m0 - m1));
		}
		else {
			id = (m1 * x2);
		}


		K1 = eq1*(y2/R - x2/R - id);
		L1 = eq2 * ( (x2 - y2)/R+z2 );
		M1 = eq3 * y2;


		xd = x2 + h * (0.5) * K1;
		yd = y2 + h * (0.5) * L1;
		zd = z2 + (0.5) * h * M1;


		if (xd > Bp) {
			id = m0 * xd + Bp * (m1 - m0);
		}
		else if (xd < (-Bp)) {
			id = m0 * xd + Bp * (m0 - m1);
		}
		else {
			id = m1 * xd;
		}

		K2 = eq1*(yd/R - xd/R - id);
		L2 = eq2 * ( (xd - yd)/R+zd );
		M2 = eq3 * yd;

		xd = x2 + h * (0.5) * K2;
		yd = y2 + h * (0.5) * L2;
		zd = z2 + (0.5) * h * M2;

		if (xd > Bp) {
			id = m0 * xd + Bp * (m1 - m0);
		}
		else if (xd < (-Bp)) {
			id = m0 * xd + Bp * (m0 - m1);
		}
		else {
			id = m1 * xd;
		}
		K3 = eq1*(yd/R - xd/R - id);
		L3 = eq2 * ( (xd - yd)/R+zd );
		M3 = eq3 * yd;


		xd = x2 + h * K3;
		yd = y2 + h * L3;
		zd = z2 + h * M3;


		if (xd > Bp) {
			id = m0 * xd + Bp * (m1 - m0);
		}
		else if (xd < (-Bp)) {
			id = m0 * xd + Bp * (m0 - m1);
		}
		else {
			id = m1 * xd;
		}

		K4 = eq1*(yd/R - xd/R - id);
		L4 = eq2 * ( (xd - yd)/R+zd );
		M4 = eq3 * yd;


		x2 = x2 + h * (1.0 / 6.0) * (K1 + (2.0) * K2 + (2.0) * K3 + K4);
		y2 = y2 + h * (1.0 / 6.0) * (L1 + (2.0) * L2 + (2.0) * L3 + L4);
		z2 = z2 + h * (1.0 / 6.0) * (M1 + (2.0) * M2 + (2.0) * M3 + M4);
/*this is the end of pseudo-orbit-2*/

        dataui.f = (x-x2)/2;

    #endif

    output.data = dataui.i;
    output.last = (i == (Iterations - 1)) ? 1 : 0;
    output.strb = 0xff;
    output.keep = 0xff;
    output_stream.write(output);
}
}





























































