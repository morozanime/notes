/*
 * func.cpp
 *
 *  Created on: 04 марта 2014 г.
 *      Author: moroz
 */

#include	<inttypes.h>
#include	<string.h>
#include    <complex>
#include	<math.h>
#include	"dstack.h"
#include	"func.h"

//-------------------------------------------------------------------
static bool calc_f_lor(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
	a = calc_dpop_ld(ds);
	b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, (b != 0.0L) || (a != 0.0L));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_land(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
    a = calc_dpop_ld(ds);
	b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, (b != 0.0L) && (a != 0.0L));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_bor(Tcalc_ds ** ds) {
	uint64_t a, b;
    a = static_cast<uint64_t>(calc_dpop_ld(ds).real());
    b = static_cast<uint64_t>(calc_dpop_ld(ds).real());
    calc_dpush_ld(ds, (b | a));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_bxor(Tcalc_ds ** ds) {
	uint64_t a, b;
    a = static_cast<uint64_t>(calc_dpop_ld(ds).real());
    b = static_cast<uint64_t>(calc_dpop_ld(ds).real());
    calc_dpush_ld(ds, (b ^ a));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_band(Tcalc_ds ** ds) {
	uint64_t a, b;
    a = static_cast<uint64_t>(calc_dpop_ld(ds).real());
    b = static_cast<uint64_t>(calc_dpop_ld(ds).real());
    calc_dpush_ld(ds, (b & a));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_eq(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
	a = calc_dpop_ld(ds);
	b = calc_dpop_ld(ds);
	calc_dpush_ld(ds, (b == a) ? 1 : 0);
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_ne(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
    a = calc_dpop_ld(ds);
    b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, (b != a) ? 1 : 0);
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_lt(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
    a = calc_dpop_ld(ds);
    b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, (a.real() > b.real()) ? 1 : 0);
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_le(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
    a = calc_dpop_ld(ds);
    b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, (a.real() >= b.real()) ? 1 : 0);
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_gt(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
    a = calc_dpop_ld(ds);
    b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, (a.real() < b.real()) ? 1 : 0);
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_ge(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
    a = calc_dpop_ld(ds);
    b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, (a.real() <= b.real()) ? 1 : 0);
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_bsr(Tcalc_ds ** ds) {
	uint64_t a, b;
    a = static_cast<uint64_t>(calc_dpop_ld(ds).real());
    b = static_cast<uint64_t>(calc_dpop_ld(ds).real());
    calc_dpush_ld(ds, (b >> a));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_bsl(Tcalc_ds ** ds) {
	uint64_t a, b;
    a = static_cast<uint64_t>(calc_dpop_ld(ds).real());
    b = static_cast<uint64_t>(calc_dpop_ld(ds).real());
    calc_dpush_ld(ds, (b << a));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_add(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
    a = calc_dpop_ld(ds);
    b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, b + a);
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_sub(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
    a = calc_dpop_ld(ds);
    b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, b - a);
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_mul(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
    a = calc_dpop_ld(ds);
    b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, b * a);
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_div(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
    a = calc_dpop_ld(ds);
    b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, b / a);
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_mod(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
    a = calc_dpop_ld(ds);
    b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, fmodl(b.real(), a.real()));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_pow(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
    a = calc_dpop_ld(ds);
    b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, pow(b, a));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_bnot(Tcalc_ds ** ds) {
	uint64_t a;
    a = ~(static_cast<uint64_t>(calc_dpop_ld(ds).real()));
    calc_dpush_ld(ds, a);
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_lnot(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, (calc_dpop_ld(ds).real() == 0.0L ? 0 : 1));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_minus(Tcalc_ds ** ds) {
	calc_dpush_ld(ds, -calc_dpop_ld(ds));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_sqrt(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, pow(calc_dpop_ld(ds), 0.5));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_abs(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, abs(calc_dpop_ld(ds)));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_arg(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, arg(calc_dpop_ld(ds)));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_Re(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, calc_dpop_ld(ds).real());
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_Im(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, calc_dpop_ld(ds).imag());
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_lg(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, log10(calc_dpop_ld(ds)));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_ln(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, log(calc_dpop_ld(ds)));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_sin(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, sin(calc_dpop_ld(ds)));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_cos(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, cos(calc_dpop_ld(ds)));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_tan(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, tan(calc_dpop_ld(ds)));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_sinh(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, sinh(calc_dpop_ld(ds)));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_cosh(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, cosh(calc_dpop_ld(ds)));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_tanh(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, tanh(calc_dpop_ld(ds)));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_conj(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, conj(calc_dpop_ld(ds)));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_exp(Tcalc_ds ** ds) {
    calc_dpush_ld(ds, exp(calc_dpop_ld(ds)));
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_comma(Tcalc_ds ** ds) {
    if(ds){}
    return true;
}

//-------------------------------------------------------------------
static bool calc_f_polar(Tcalc_ds ** ds) {
    std::complex<long double> a, b;
    a = calc_dpop_ld(ds);
    b = calc_dpop_ld(ds);
    calc_dpush_ld(ds, std::polar(b.real(),a.real()));
    return true;
}

//-------------------------------------------------------------------
Tcalc_func calc_func[] = { //
    { "polar", 130, calc_f_polar, 1 }, //
    { "exp", 130, calc_f_exp, 1 }, //
    { "conj", 130, calc_f_conj, 1 }, //
    { "cosh", 130, calc_f_cosh, 1 }, //
    { "sinh", 130, calc_f_sinh, 1 }, //
    { "tanh", 130, calc_f_tanh, 1 }, //
    { "cos", 130, calc_f_cos, 1 }, //
    { "sin", 130, calc_f_sin, 1 }, //
    { "tan", 130, calc_f_tan, 1 }, //
    { "ln", 130, calc_f_ln, 1 }, //
    { "lg", 130, calc_f_lg, 1 }, //
    { "abs", 130, calc_f_abs, 1 }, //
    { "arg", 130, calc_f_arg, 1 }, //
    { "Re", 130, calc_f_Re, 1 }, //
    { "Im", 130, calc_f_Im, 1 }, //
    { "sqrt", 130, calc_f_sqrt, 1 }, //
    { "!", 130, calc_f_lnot, 1 }, //
    { "~", 130, calc_f_bnot, 1 }, //
    { "+", 130, nullptr, 1 }, //
    { "-", 130, calc_f_minus, 1 }, //
    { "^", 120, calc_f_pow, 0 }, //
    { "%", 110, calc_f_mod, 0 }, //
    { "/", 110, calc_f_div, 0 }, //
    { "*", 110, calc_f_mul, 0 }, //
    { "-", 100, calc_f_sub, 0 }, //
    { "+", 100, calc_f_add, 0 }, //
    { "<<", 90, calc_f_bsl, 0 }, //
    { ">>", 90, calc_f_bsr, 0 }, //
    { ">=", 80, calc_f_ge, 0 }, //
    { ">", 80, calc_f_gt, 0 }, //
    { "<=", 80, calc_f_le, 0 }, //
    { "<", 80, calc_f_lt, 0 }, //
    { "!=", 70, calc_f_ne, 0 }, //
    { "==", 70, calc_f_eq, 0 }, //
    { "&", 60, calc_f_band, 0 }, //
    { "#", 50, calc_f_bxor, 0 }, //
    { "|", 40, calc_f_bor, 0 }, //
    { "&&", 30, calc_f_land, 0 }, //
    { "||", 20, calc_f_lor, 0 }, //
    { ",", 11, calc_f_comma, 0 }, //
    { ")", 10, nullptr, -1 }, //
    { "(", 0, nullptr, 0 }, //
};

//-------------------------------------------------------------------
bool calc_func_index(int index, Tcalc_ds * *ds) {
    if (calc_func[index].f) {
        if (calc_func[index].type == 0 && calc_ddepth(ds) < 2) {
            return 0;
        } else if (calc_func[index].type == 1 && calc_ddepth(ds) < 1) {
            return 0;
        } else {
            calc_func[index].f(ds);
            return true;
        }
    } else
        return false;
}

//-------------------------------------------------------------------
bool calc_is_a_func(int * func, size_t * len, char * src, int last) {
    size_t i, j, l;
    *len = 0;
    for (i = 0; i < sizeof(calc_func) / sizeof(calc_func[0]); i++) {
        if (calc_func[i].type == 1 && last != 0)
            continue;
        l = strlen(calc_func[i].name);
        for (j = 0; j < l; j++) {
            if (src[j] != calc_func[i].name[j])
                break;
        }
        if (j >= l) {
            if (j > *len) {
                *len = j;
                *func = static_cast<int>(i);
            }
        }
    }
    return *len;
}
