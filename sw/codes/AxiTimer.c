/*
 * A special thanks to the author of a code from which we have based our code
 * Whoever you are, laraujo, Cheers !
 */

#include "parameters.h"


void AxiTimer_Init(AxiTimer* timer) {
	XTmrCtr_Initialize(&(timer->AxiTimer), XPAR_TMRCTR_0_DEVICE_ID);
	timer->timerClockFreq = (double) XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ;
	timer->clockPeriodSeconds = (double)1 / timer->timerClockFreq;
}

void AxiTimer_Cleanup(AxiTimer* timer) {
	// If you have anything to cleanup, do it here
}

unsigned int AxiTimer_startTimer(AxiTimer* timer) {
	XTmrCtr_Reset(&(timer->AxiTimer), 0);
	timer->tick_start = XTmrCtr_GetValue(&(timer->AxiTimer), 0);
	XTmrCtr_Start(&(timer->AxiTimer), 0);
	return timer->tick_start;
}

unsigned int AxiTimer_stopTimer(AxiTimer* timer) {
	XTmrCtr_Stop(&(timer->AxiTimer), 0);
	timer->tick_last = XTmrCtr_GetValue(&(timer->AxiTimer), 0);
	return timer->tick_last;
}

unsigned int AxiTimer_Get_end_tx(AxiTimer* timer) {
	timer->tick_end_tx = XTmrCtr_GetValue(&(timer->AxiTimer), 0);
	return timer->tick_end_tx;
}
// can you help me with next function ?
unsigned int AxiTimer_Get_end_hash(AxiTimer* timer) {
	timer->tick_end_hash = XTmrCtr_GetValue(&(timer->AxiTimer), 0);
	return timer->tick_end_hash;
}
unsigned int AxiTimer_Get_end_perm_seq(AxiTimer* timer) {
	timer->tick_end_perm_seq = XTmrCtr_GetValue(&(timer->AxiTimer), 0);
	return timer->tick_end_perm_seq;
}
unsigned int AxiTimer_Get_end_perm_sort(AxiTimer* timer) {
	timer->tick_end_perm_sort = XTmrCtr_GetValue(&(timer->AxiTimer), 0);
	return timer->tick_end_perm_sort;
}
unsigned int AxiTimer_Get_end_perm_scramble(AxiTimer* timer) {
	timer->tick_end_perm_scramble = XTmrCtr_GetValue(&(timer->AxiTimer), 0);
	return timer->tick_end_perm_scramble;
}
unsigned int AxiTimer_Get_end_diff(AxiTimer* timer) {
	timer->tick_end_diff = XTmrCtr_GetValue(&(timer->AxiTimer), 0);
	return timer->tick_end_diff;
}
unsigned int AxiTimer_Get_init_bitxor(AxiTimer* timer) {
	timer->tick_init_bitxor = XTmrCtr_GetValue(&(timer->AxiTimer), 0);
	return timer->tick_init_bitxor;
}
unsigned int AxiTimer_Get_end_bitxor(AxiTimer* timer) {
	timer->tick_end_bitxor = XTmrCtr_GetValue(&(timer->AxiTimer), 0);
	return timer->tick_end_bitxor;
}
// can you continue ?
double AxiTimer_Get_ts_tx(AxiTimer* timer) {
	timer->ts_tx = (double)(timer->tick_end_tx - timer->tick_start) * timer->clockPeriodSeconds;
	return timer->ts_tx;
}
double AxiTimer_Get_ts_hash(AxiTimer* timer) {
	timer->ts_hash = (double)(timer->tick_end_hash - timer->tick_end_tx) * timer->clockPeriodSeconds;
	return timer->ts_hash;
}
double AxiTimer_Get_ts_perm_seq(AxiTimer* timer) {
	timer->ts_perm_seq = (double)(timer->tick_end_perm_seq - timer->tick_end_hash) * timer->clockPeriodSeconds;
	return timer->ts_perm_seq;
}
double AxiTimer_Get_ts_perm_sort(AxiTimer* timer) {
	timer->ts_perm_sort = (double)(timer->tick_end_perm_sort - timer->tick_end_perm_seq) * timer->clockPeriodSeconds;
	return timer->ts_perm_sort;
}
double AxiTimer_Get_ts_perm_scramble(AxiTimer* timer) {
	timer->ts_perm_scramble = (double)(timer->tick_end_perm_scramble - timer->tick_end_perm_sort) * timer->clockPeriodSeconds;
	return timer->ts_perm_scramble;
}
double AxiTimer_Get_ts_diff(AxiTimer* timer) {
	timer->ts_diff = (double)(timer->tick_end_diff - timer->tick_end_hash) * timer->clockPeriodSeconds;
	return timer->ts_diff;
}
double AxiTimer_Get_ts_bitxor(AxiTimer* timer) {
	timer->ts_bitxor = (double)(timer->tick_end_bitxor - timer->tick_init_bitxor) * timer->clockPeriodSeconds;
	return timer->ts_bitxor;
}
double AxiTimer_Get_ts_all(AxiTimer* timer) {
	timer->ts_all = (double)(timer->tick_end_bitxor - timer->tick_start) * timer->clockPeriodSeconds;
	return timer->ts_all;
}
