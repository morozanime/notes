/*
 * ldcalc.cpp
 *
 *  Created on: 04 марта 2014 г.
 *      Author: moroz
 */

#include	<stdlib.h>
#include	<string.h>
#include    <complex>
#include	"suff.h"
#include	"num.h"
#include	"func.h"
#include	"dstack.h"
#include	"fstack.h"
#include	"ldcalc.h"

//-------------------------------------------------------------------
bool ldcalc(std::complex<long double> *dest, char * src) {
	bool r = 1;
    std::complex<long double> v, scale;
    Tcalc_ds * ds = nullptr;
    Tcalc_fs * fs = nullptr;
    size_t p = 0, len = strlen(src), l, lsuff;
    int f, last = 0;
	while (r && p < len) {
		l = 0;
        if(false){

        } else if (calc_is_a_func(&f, &l, src + p, last)) {
            last = calc_func[f].type;
            if (calc_func[f].prior == 10) {
                while (r && fs) {
                    if (calc_func[fs->f].prior) {
                        r &= calc_func_index(fs->f, &ds);
                        calc_fpop(&fs);
                    } else {
                        calc_fpop(&fs);
                        break;
                    }
                }
            } else if (fs == nullptr)
                calc_fpush(&fs, f);
            else if (calc_func[f].prior == 0)
                calc_fpush(&fs, f);
            else {
                while (r && fs) {
                    if ((calc_func[fs->f].prior >= calc_func[f].prior) && ((calc_func[fs->f].prior != 120) || (calc_func[f].prior != 120))) { /*if not x^y^z*/
                        r &= calc_func_index(fs->f, &ds);
                        calc_fpop(&fs);
                    } else
                        break;
                }
                calc_fpush(&fs, f);
            }
        } else if (calc_is_a_num(&v, &l, src + p)) {
			if (calc_is_a_fsuff(&scale, &lsuff, src + p + l)) {
				l += lsuff;
				v *= scale;
			}
			calc_dpush_ld(&ds, v);
			last = 1;
		} else
			r = 0;
		p += l;
	}
	while (fs) {
		r &= calc_func_index(fs->f, &ds);
		calc_fpop(&fs);
	}
	v = calc_dpop_ld(&ds);
	while (ds) {
		calc_dpop_ld(&ds);
		r = 0;
	}
	*dest = v;
	return r;
}

