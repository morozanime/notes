/*
 * dstack.h
 *
 *  Created on: 04 марта 2014 г.
 *      Author: moroz
 */

#ifndef DSTACK_H_
#define DSTACK_H_

#include    <complex>
#include    <inttypes.h>

class Tcalc_num {
public:
    enum num_type_e {
        N = 0,
        Z,
        R,
        C,
        H
    };

    Tcalc_num(num_type_e type) {
        this->type = type;
        switch (type) {
        case N:
            n = 0;
            break;
        case Z:
            z = 0;
            break;
        case R:
            r = 0.0;
            break;
        case C:
            c = std::complex<long double>(0.0, 0.0);
            break;
        case H:
            h[0] = 0.0;
            h[1] = 0.0;
            h[2] = 0.0;
            h[3] = 0.0;
            break;
        default:
            break;
        }
    }
    num_type_e type;
    union {
        uint64_t n;
        int64_t z;
        long double r;
        std::complex<long double> c;
        long double h[4];
    };
};

typedef struct Tcalc_ds {
	Tcalc_num n;
	Tcalc_ds * next;
} Tcalc_ds;

std::complex<long double> calc_dpop_ld(Tcalc_ds ** ds);
bool calc_dpush_ld(Tcalc_ds ** ds, std::complex<long double> ld);
int calc_ddepth(Tcalc_ds * *ds);

#endif /* DSTACK_H_ */
