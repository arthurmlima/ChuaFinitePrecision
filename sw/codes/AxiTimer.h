/*
 * AxiTimerHelper.h
 *
 *  Created on: 06/07/2015
 *      Author: laraujo
 *
 * A special thanks to the author of a code from which we have based our code
 * Whoever you are, laraujo, Cheers !
 */
#ifndef AXITIMER_H_
#define AXITIMER_H_

#include "xil_types.h"
#include "xtmrctr.h"
#include "xparameters.h"

typedef struct {
	XTmrCtr AxiTimer;
	double clockPeriodSeconds;
	double timerClockFreq;
	double ts_tx;
	double ts_hash;
	double ts_perm_seq;
	double ts_perm_sort;
	double ts_perm_scramble;
	double ts_diff;
	double ts_bitxor;
	double ts_all;
	unsigned int tick_start;
	unsigned int tick_end_tx;
	unsigned int tick_end_hash;
	unsigned int tick_end_perm_seq;
	unsigned int tick_end_perm_sort;
	unsigned int tick_end_perm_scramble;
	unsigned int tick_end_diff;
	unsigned int tick_init_bitxor;
	unsigned int tick_end_bitxor;
	unsigned int tick_last;
} AxiTimer;

// Function declarations
void AxiTimer_Init(AxiTimer* timer);
void AxiTimer_Cleanup(AxiTimer* timer);
unsigned int AxiTimer_startTimer(AxiTimer* timer);
unsigned int AxiTimer_stopTimer(AxiTimer* timer);
u32 AxiTimer_Get_end_tx(AxiTimer* timer);
u32 AxiTimer_Get_end_hash(AxiTimer* timer);
u32 AxiTimer_Get_end_perm_seq(AxiTimer* timer);
u32 AxiTimer_Get_end_perm_sort(AxiTimer* timer);
u32 AxiTimer_Get_end_perm_scramble(AxiTimer* timer);
u32 AxiTimer_Get_end_diff(AxiTimer* timer);
u32 AxiTimer_Get_init_bitxor(AxiTimer* timer);
u32 AxiTimer_Get_end_bitxor(AxiTimer* timer);
double AxiTimer_Get_ts_tx(AxiTimer* timer);
double AxiTimer_Get_ts_hash(AxiTimer* timer);
double AxiTimer_Get_ts_perm_seq(AxiTimer* timer);
double AxiTimer_Get_ts_perm_sort(AxiTimer* timer);
double AxiTimer_Get_ts_perm_scramble(AxiTimer* timer);
double AxiTimer_Get_ts_diff(AxiTimer* timer);
double AxiTimer_Get_ts_bitxor(AxiTimer* timer);
double AxiTimer_Get_ts_all(AxiTimer* timer);




#endif


