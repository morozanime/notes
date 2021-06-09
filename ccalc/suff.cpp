/*
 * suff.cpp
 *
 *  Created on: 04 марта 2014 г.
 *      Author: moroz
 */

#include	<string.h>
#include	"suff.h"

//-------------------------------------------------------------------
static Tcalc_fsuff calc_fsuff[] = { //
    { "T", 1e12L }, //
    { "Tb", 1024.L * 1024.L * 1024.L * 1024.L }, //
    { "G", 1e9L }, //
    { "Gb", 1024.L * 1024.L * 1024.L }, //
    { "M", 1e6L }, //
    { "Mb", 1024.L * 1024.L }, //
    { "K", 1e3L }, //
    { "Kb", 1024.L }, //
    { "kb", 1024.L }, //
    { "k", 1e3L }, //
    { "D", 1e1L }, //
    { "d", 1e1L }, //
    { "s", 1e-2L }, //
    { "m", 1e-3L }, //
    { "u", 1e-6L }, //
    { "n", 1e-9L }, //
    { "p", 1e-12L }, //
    { "f", 1e-15L }, //
    { "a", 1e-18L }, //
    { "j", std::complex<long double>(0, 1) }, //
};

//-------------------------------------------------------------------
bool calc_is_a_fsuff(std::complex<long double> * scale, size_t * len, char * src) {
    size_t i, j, l;
	*len = 0;
    for (i = 0; i < sizeof(calc_fsuff) / sizeof(calc_fsuff[0]); i++) {
		l = strlen(calc_fsuff[i].name);
		for (j = 0; j < l; j++) {
			if (src[j] != calc_fsuff[i].name[j])
				break;
		}
		if (j >= l) {
			if (j > *len) {
				*len = j;
				*scale = calc_fsuff[i].scale;
			}
		}
	}
    return *len;
}

