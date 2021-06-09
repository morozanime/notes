/*
 * dstack.h
 *
 *  Created on: 04 марта 2014 г.
 *      Author: moroz
 */

#ifndef DSTACK_H_
#define DSTACK_H_

#include    <inttypes.h>

typedef struct {
    size_t size;
	int type;
	void * data;
} Tcalc_num;

typedef struct Tcalc_ds {
	Tcalc_num n;
	Tcalc_ds * next;
} Tcalc_ds;

#include    <complex>

std::complex<long double> calc_dpop_ld(Tcalc_ds ** ds);
bool calc_dpush_ld(Tcalc_ds ** ds, std::complex<long double> ld);
int calc_ddepth(Tcalc_ds * *ds);

#endif /* DSTACK_H_ */
