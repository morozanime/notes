/*
 * suff.cpp
 *
 *  Created on: 04 марта 2014 г.
 *      Author: moroz
 */

#include	<string.h>
#include	"suff.h"

//-------------------------------------------------------------------
typedef struct {
    const char * name;
    Tcalc_num::num_type_e type_min;
    Tcalc_num (*scale)(Tcalc_num::num_type_e type);
} Tcalc_fsuff;

static Tcalc_num calc_fsuff_T(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::N:
        scale.n = 1000000000000LLU;
        break;
    case Tcalc_num::Z:
        scale.z = 1000000000000LL;
        break;
    case Tcalc_num::R:
        scale.r = 1e12L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1e12L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1e12L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_Tb(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::N:
        scale.n = 1024LLU * 1024LLU * 1024LLU * 1024LLU;
        break;
    case Tcalc_num::Z:
        scale.z = 1024LL * 1024LL * 1024LL * 1024LL;
        break;
    case Tcalc_num::R:
        scale.r = 1024.L * 1024.L * 1024.L * 1024.L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1024.L * 1024.L * 1024.L * 1024.L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1024.L * 1024.L * 1024.L * 1024.L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_G(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::N:
        scale.n = 1000000000LLU;
        break;
    case Tcalc_num::Z:
        scale.z = 1000000000LL;
        break;
    case Tcalc_num::R:
        scale.r = 1e9L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1e9L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1e9L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_Gb(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::N:
        scale.n = 1024LLU * 1024LLU * 1024LLU;
        break;
    case Tcalc_num::Z:
        scale.z = 1024LL * 1024LL * 1024LL;
        break;
    case Tcalc_num::R:
        scale.r = 1024.L * 1024.L * 1024.L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1024.L * 1024.L * 1024.L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1024.L * 1024.L * 1024.L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_M(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::N:
        scale.n = 1000000LLU;
        break;
    case Tcalc_num::Z:
        scale.z = 1000000LL;
        break;
    case Tcalc_num::R:
        scale.r = 1e6L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1e6L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1e6L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_Mb(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::N:
        scale.n = 1024LLU * 1024LLU;
        break;
    case Tcalc_num::Z:
        scale.z = 1024LL * 1024LL;
        break;
    case Tcalc_num::R:
        scale.r = 1024.L * 1024.L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1024.L * 1024.L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1024.L * 1024.L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_K(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::N:
        scale.n = 1000LLU;
        break;
    case Tcalc_num::Z:
        scale.z = 1000LL;
        break;
    case Tcalc_num::R:
        scale.r = 1e3L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1e3L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1e3L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_Kb(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::N:
        scale.n = 1024LLU;
        break;
    case Tcalc_num::Z:
        scale.z = 1024LL;
        break;
    case Tcalc_num::R:
        scale.r = 1024.L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1024.L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1024.L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_D(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::N:
        scale.n = 10LLU;
        break;
    case Tcalc_num::Z:
        scale.z = 10LL;
        break;
    case Tcalc_num::R:
        scale.r = 1e1L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1e1L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1e1L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_s(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::R:
        scale.r = 1e-2L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1e-2L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1e-2L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    default:
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_m(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::R:
        scale.r = 1e-3L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1e-3L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1e-3L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    default:
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_u(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::R:
        scale.r = 1e-6L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1e-6L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1e-6L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    default:
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_n(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::R:
        scale.r = 1e-9L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1e-9L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1e-9L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    default:
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_f(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::R:
        scale.r = 1e-15L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1e-15L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1e-15L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    default:
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_a(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::R:
        scale.r = 1e-18L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1e-18L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1e-18L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    default:
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_p(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::R:
        scale.r = 1e-12L;
        break;
    case Tcalc_num::C:
        scale.c = std::complex<long double>(1e-12L, 0);
        break;
    case Tcalc_num::H:
        scale.h[0] = 1e-12L;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    default:
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_i(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::C:
        scale.c = std::complex<long double>(0, 1.0L);
        break;
    case Tcalc_num::H:
        scale.h[0] = 0;
        scale.h[1] = 1.0L;
        scale.h[2] = 0;
        scale.h[3] = 0;
        break;
    default:
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_j(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::H:
        scale.h[0] = 0;
        scale.h[1] = 0;
        scale.h[2] = 1.0L;
        scale.h[3] = 0;
        break;
    default:
        break;
    }
    return scale;
}

static Tcalc_num calc_fsuff_k(Tcalc_num::num_type_e type) {
    Tcalc_num scale(type);
    switch(type){
    case Tcalc_num::H:
        scale.h[0] = 0;
        scale.h[1] = 0;
        scale.h[2] = 0;
        scale.h[3] = 1.0L;
        break;
    default:
        break;
    }
    return scale;
}

static Tcalc_fsuff calc_fsuff[] = { //
    { "T", Tcalc_num::N, calc_fsuff_T }, //
    { "Tb", Tcalc_num::N, calc_fsuff_Tb }, //
    { "G", Tcalc_num::N, calc_fsuff_G }, //
    { "Gb", Tcalc_num::N, calc_fsuff_Gb }, //
    { "M", Tcalc_num::N, calc_fsuff_M }, //
    { "Mb", Tcalc_num::N, calc_fsuff_Mb }, //
    { "K", Tcalc_num::N, calc_fsuff_K }, //
    { "Kb", Tcalc_num::N, calc_fsuff_Kb }, //
    { "kb", Tcalc_num::N, calc_fsuff_Kb }, //
    { "k", Tcalc_num::N, calc_fsuff_K }, //
    { "D", Tcalc_num::N, calc_fsuff_D }, //
    { "d", Tcalc_num::N, calc_fsuff_D }, //
    { "s", Tcalc_num::R, calc_fsuff_s }, //
    { "m", Tcalc_num::R, calc_fsuff_m }, //
    { "u", Tcalc_num::R, calc_fsuff_u }, //
    { "n", Tcalc_num::R, calc_fsuff_n }, //
    { "p", Tcalc_num::R, calc_fsuff_p }, //
    { "f", Tcalc_num::R, calc_fsuff_f }, //
    { "a", Tcalc_num::R, calc_fsuff_a }, //
    { "i", Tcalc_num::C, calc_fsuff_i }, //
    { "j", Tcalc_num::H, calc_fsuff_j }, //
    { "k", Tcalc_num::H, calc_fsuff_k }, //
};

//-------------------------------------------------------------------
bool calc_is_a_fsuff(Tcalc_num * scale, size_t * len, char * src, Tcalc_num::num_type_e type) {
    size_t i, j, l;
	*len = 0;
    for (i = 0; i < sizeof(calc_fsuff) / sizeof(calc_fsuff[0]); i++) {
		l = strlen(calc_fsuff[i].name);
		for (j = 0; j < l; j++) {
			if (src[j] != calc_fsuff[i].name[j])
				break;
		}
		if (j >= l) {
            if (j > *len && type >= calc_fsuff[i].type_min) {
                *len = j;
                *scale = calc_fsuff[i].scale(type);
            }
		}
	}
    return *len > 0 ? true : false;
}

