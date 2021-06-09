/*
 * suff.h
 *
 *  Created on: 04 марта 2014 г.
 *      Author: moroz
 */

#ifndef SUFF_H_
#define SUFF_H_

#include <complex>
typedef struct {
    const char * name;
    std::complex<long double> scale;
} Tcalc_fsuff;

#include    <inttypes.h>
bool calc_is_a_fsuff(std::complex<long double> * scale, size_t * len, char * src);

#endif /* SUFF_H_ */
