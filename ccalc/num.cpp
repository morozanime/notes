/*
 * num.cpp
 *
 *  Created on: 04 марта 2014 г.
 *      Author: moroz
 */

#include	<stdlib.h>
#include	<string.h>
#include	<inttypes.h>

//#include	<stdio.h>
#include	<math.h>
#include	"num.h"
#include    "ldcalc.h"
#include "ccalc/dstack.h"

#include <QDebug>
#include <QString>
#include <QHash>
#include <QList>
#include <QPair>

struct SVar {
    char * name;
    std::complex<long double> v;
};

static QList<SVar> vars = QList<SVar>();

struct SFunc {
    QString name;
    QString f;
};

static QHash<QString, QString> functions = QHash<QString, QString>();

//-------------------------------------------------------------------
void SetVariable(const char * name, std::complex<long double> v){
    int i = 0;
    for(i = 0; i < vars.count(); i++)
        if(strcmp(name, vars[i].name) == 0)
            break;
    if(i == vars.count()){
        SVar a;
        a.name = static_cast<char*>(malloc(strlen(name) + 1));
        strcpy(a.name, name);
        a.v = v;
        vars.append(a);
    } else{
        vars[i].v = v;
    }
}

//-------------------------------------------------------------------
void SetFunction(QString name, QString f){
    functions[name] = f;
}

void ClearFunctions(void){
    functions.clear();
}

void ClearVariables(void){
    vars.clear();
}

//-------------------------------------------------------------------
static bool calc_is_a_variable(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type) {
    size_t i, j, l;
    *len = 0;
    for (i = 0; i < static_cast<size_t>(vars.count()); i++) {
        l = strlen(vars[i].name);
        for (j = 0; j < l; j++) {
            if (src[j] != vars[i].name[j])
                break;
        }
        if (j >= l) {
            if (l > *len) {
                *len = l;
                *dest = vars[i].v;
            }
        }
    }
    return (*len) != 0 ? true : false;
}

//-------------------------------------------------------------------
static bool calc_is_a_function(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type) {
    size_t l;
    *len = 0;
    QString s = QString(src);
    l = 0;
    while((long long)l < s.length() && functions.contains(s.left(l + 1)))
        l++;
    if(l > 0){
        if(ldcalc(dest, functions[s.left(l)].toLatin1().data()))
            *len = l;
    }
    return *len;
}

typedef struct {
    const char * name;
    Tcalc_num::num_type_e type_min;
    Tcalc_num (*v)(Tcalc_num::num_type_e type);
} Tcalc_const;

static Tcalc_num calc_const_pi(Tcalc_num::num_type_e type) {
    Tcalc_num v(type);
    switch(type) {
    case Tcalc_num::R:
        v.r = M_PI;
        break;
    case Tcalc_num::C:
        v.c = std::complex<long double>(M_PI, 0);
        break;
    case Tcalc_num::H:
        v.h[0] = M_PI;
        v.h[1] = 0;
        v.h[2] = 0;
        v.h[3] = 0;
        break;
    default:
        break;
    }
    return v;
}

static Tcalc_num calc_const_e(Tcalc_num::num_type_e type) {
    Tcalc_num v(type);
    switch(type) {
    case Tcalc_num::R:
        v.r = M_E;
        break;
    case Tcalc_num::C:
        v.c = std::complex<long double>(M_E, 0);
        break;
    case Tcalc_num::H:
        v.h[0] = M_E;
        v.h[1] = 0;
        v.h[2] = 0;
        v.h[3] = 0;
        break;
    default:
        break;
    }
    return v;
}

static Tcalc_num calc_const_i(Tcalc_num::num_type_e type) {
    Tcalc_num v(type);
    switch(type) {
    case Tcalc_num::C:
        v.c = std::complex<long double>(0, 1.0L);
        break;
    case Tcalc_num::H:
        v.h[0] = 0;
        v.h[1] = 1.0L;
        v.h[2] = 0;
        v.h[3] = 0;
        break;
    default:
        break;
    }
    return v;
}

static Tcalc_num calc_const_j(Tcalc_num::num_type_e type) {
    Tcalc_num v(type);
    switch(type) {
    case Tcalc_num::H:
        v.h[0] = 0;
        v.h[1] = 0;
        v.h[2] = 1.0L;
        v.h[3] = 0;
        break;
    default:
        break;
    }
    return v;
}

static Tcalc_num calc_const_k(Tcalc_num::num_type_e type) {
    Tcalc_num v(type);
    switch(type) {
    case Tcalc_num::H:
        v.h[0] = 0;
        v.h[1] = 0;
        v.h[2] = 0;
        v.h[3] = 1.0L;
        break;
    default:
        break;
    }
    return v;
}

//-------------------------------------------------------------------
static Tcalc_const calc_const[] = { //
        { "pi", Tcalc_num::R,  calc_const_pi }, //
        { "e", Tcalc_num::R, calc_const_e }, //
        { "i", Tcalc_num::C, calc_const_i }, //
        { "j", Tcalc_num::H, calc_const_j }, //
        { "k", Tcalc_num::H, calc_const_k }, //
};

//-------------------------------------------------------------------
static bool calc_is_a_numconst(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type) {
    size_t i, j, l;
	*len = 0;
    for (i = 0; i < sizeof(calc_const) / sizeof(calc_const[0]); i++) {
		l = strlen(calc_const[i].name);
		for (j = 0; j < l; j++) {
			if (src[j] != calc_const[i].name[j])
				break;
		}
		if (j >= l) {
            if (l > *len && type >= calc_const[i].type_min) {
				*len = l;
                *dest = calc_const[i].v(type);
			}
		}
	}
    return *len > 0 ? true : false;
}

//-------------------------------------------------------------------
//[0-9a-fA-F]+[hH]
static bool calc_is_a_numh(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type) {
    *len = 0;
    if(type == Tcalc_num::N || type == Tcalc_num::Z) {
        uint64_t v = 0, dv = 0;
        while (1) {
            if (src[(*len)] >= '0' && src[(*len)] <= '9') {
                dv = static_cast<uint64_t>(src[(*len)] - '0');
            } else if (src[(*len)] >= 'A' && src[(*len)] <= 'F') {
                dv = static_cast<uint64_t>(src[(*len)] - 'A' + 10);
            } else if (src[(*len)] >= 'a' && src[(*len)] <= 'f') {
                dv = static_cast<uint64_t>(src[(*len)] - 'a' + 10);
            } else if (src[(*len)] == 'h' || src[(*len)] == 'H') {
                (*len)++;
                break;
            } else {
                (*len) = 0;
                break;
            }
            v *= 16;
            v += dv;
            (*len)++;
        }
        if (*len > 1) {
            Tcalc_num result(type);
            if(type == Tcalc_num::N) {
                result.n = v;
            } else if(type == Tcalc_num::Z) {
                result.z = (int64_t) v;
            }
            *dest = result;
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------
//\$[0-9a-fA-F]
static bool calc_is_a_dollar_num(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type) {
    *len = 0;
    if (src[(*len)] == '$') {
        (*len)++;
    } else
        return false;
    if(type == Tcalc_num::N || type == Tcalc_num::Z) {
        uint64_t v = 0, dv = 0;
        while (1) {
            if (src[(*len)] >= '0' && src[(*len)] <= '9') {
                dv = static_cast<uint64_t>(src[(*len)] - '0');
            } else if (src[(*len)] >= 'A' && src[(*len)] <= 'F') {
                dv = static_cast<uint64_t>(src[(*len)] - 'A' + 10);
            } else if (src[(*len)] >= 'a' && src[(*len)] <= 'f') {
                dv = static_cast<uint64_t>(src[(*len)] - 'a' + 10);
            } else
                break;
            v *= 16;
            v += dv;
            (*len)++;
        }
        if (*len > 1) {
            Tcalc_num result(type);
            if(type == Tcalc_num::N) {
                result.n = v;
            } else if(type == Tcalc_num::Z) {
                result.z = (int64_t) v;
            }
            *dest = result;
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------
//[01]+[bB]
static bool calc_is_a_numb(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type) {
    *len = 0;
    if(type == Tcalc_num::N || type == Tcalc_num::Z) {
        uint64_t v = 0, dv = 0;
        while (1) {
            if (src[(*len)] == '0' || src[(*len)] == '1') {
                dv = static_cast<uint64_t>(src[(*len)] - '0');
            } else if (src[(*len)] == 'b' || src[(*len)] == 'B') {
                (*len)++;
                break;
            } else {
                (*len) = 0;
                break;
            }
            v *= 2;
            v += dv;
            (*len)++;
        }
        if (*len > 1) {
            Tcalc_num result(type);
            if(type == Tcalc_num::N) {
                result.n = v;
            } else if(type == Tcalc_num::Z) {
                result.z = (int64_t) v;
            }
            *dest = result;
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------
static bool calc_is_a_0num(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type) {
    uint64_t v = 0, dv = 0;
    std::complex<long double> v2 = 0;
    *len = 0;
	if (src[*len] == '0') {
		(*len)++;
	} else
        return false;
	while (1) {
		if (src[(*len)] >= '0' && src[(*len)] <= '7') {
            dv = static_cast<uint64_t>(src[(*len)] - '0');
		} else
			break;
        v *= 8;
        v += dv;
        v2 *= 8;
        v2 += dv;
        (*len)++;
    }
    *dest = (v2.real() > UINT64_MAX) ? v2 : v;
    return true;
}

//-------------------------------------------------------------------
static bool calc_is_a_dnum(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type) {
    uint64_t v = 0, dv = 0;
    std::complex<long double> v2 = 0;
    *len = 0;
	while (1) {
		if (src[(*len)] >= '0' && src[(*len)] <= '9') {
            dv = static_cast<uint64_t>(src[(*len)] - '0');
		} else
			break;
        v *= 10;
        v += dv;
        v2 *= 10;
        v2 += dv;
        (*len)++;
    }
    *dest = (v2.real() > UINT64_MAX) ? v2 : v;
    return true;
}

//-------------------------------------------------------------------
static bool calc_is_a_fnum(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type) {
    char buff[256]={0};
    bool comma = false;
	*len = 0;
    while (1) {
		if (src[(*len)] >= '0' && src[(*len)] <= '9') {
			(*len)++;
        } else if (src[(*len)] == '.' && !comma) {
			(*len)++;
            comma = true;
		} else
			break;
	}

    if(*len == 0)
        return false;
    else if(comma && (*len) <= 1)
        return false;
    else{
        memcpy(buff, src, *len);
        buff[*len] = 0;
        *dest = strtold(buff, nullptr);
    return true;
    }
}

//-------------------------------------------------------------------
static bool calc_is_a_enum(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type) {
    char buff[256]={0};
    bool comma = false, exp = false;
    int ml = 0, el = 0;
	*len = 0;
	while (1) {
		if (src[(*len)] >= '0' && src[(*len)] <= '9') {
			(*len)++;
            if(!exp)
                ml++;
            else
                el++;
        } else if (src[(*len)] == '.' && comma == 0 && !exp) {
			(*len)++;
            comma = true;
            ml++;
        } else if ((src[(*len)] == 'e' || src[(*len)] == 'E') && !exp) {
			(*len)++;
            if ((src[(*len)] == '-' || src[(*len)] == '+')) {
				(*len)++;
                el++;
				if (src[(*len)] >= '0' && src[(*len)] <= '9') {
					(*len)++;
                    el++;
				} else {
					(*len) -= 2;
                    el--;
					break;
				}
			} else if (src[(*len)] >= '0' && src[(*len)] <= '9') {
				(*len)++;
                el++;
            } else {
				(*len)--;
                el--;
				break;
			}
            exp = true;
		} else
			break;
	}

    if(ml == 0)
        return false;
    else if(comma && ml <= 1)
        return false;
    else if(el == 0)
        return false;
    else{
        memcpy(buff, src, *len);
        buff[*len] = 0;
        *dest = strtold(buff, nullptr);
    return true;
    }
}

//-------------------------------------------------------------------
static bool calc_is_a_0bnum(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type) {
    uint64_t v = 0, dv = 0;
    std::complex<long double> v2 = 0;
    *len = 0;
	if (src[*len] == '0') {
		(*len)++;
	} else
        return false;
	if (src[*len] == 'b' || src[*len] == 'B') {
		(*len)++;
	} else
        return false;
	while (1) {
		if (src[(*len)] == '0' || src[(*len)] == '1') {
            dv = static_cast<uint64_t>(src[(*len)] - '0');
		} else
			break;
        v *= 2;
        v += dv;
        v2 *= 2;
        v2 += dv;
        (*len)++;
    }
    *dest = (v2.real() > UINT64_MAX) ? v2 : v;
    return true;
}

//-------------------------------------------------------------------
static bool calc_is_a_0xnum(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type) {
    uint64_t v = 0, dv = 0;
    std::complex<long double> v2 = 0;
    *len = 0;
	if (src[*len] == '0') {
		(*len)++;
	} else
        return false;
	if (src[*len] == 'x' || src[*len] == 'X') {
		(*len)++;
	} else
        return false;
	while (1) {
		if (src[(*len)] >= '0' && src[(*len)] <= '9') {
            dv = static_cast<uint64_t>(src[(*len)] - '0');
		} else if (src[(*len)] >= 'a' && src[(*len)] <= 'f') {
            dv = static_cast<uint64_t>(src[(*len)] - 'a' + 10);
		} else if (src[(*len)] >= 'A' && src[(*len)] <= 'F') {
            dv = static_cast<uint64_t>(src[(*len)] - 'A' + 10);
		} else
			break;
        v *= 16;
        v += dv;
        v2 *= 16;
        v2 += dv;
        (*len)++;
    }
    *dest = (v2.real() > UINT64_MAX) ? v2 : v;
    return true;
}

typedef struct {
    Tcalc_num::num_type_e type_min;
    Tcalc_num::num_type_e type_max;
    bool (*f)(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type);
} Tcalc_fnum;

//-------------------------------------------------------------------
static Tcalc_fnum calc_fnum[] = { //
    { Tcalc_num::R, Tcalc_num::H, calc_is_a_numconst }, //
    { Tcalc_num::N, Tcalc_num::Z, calc_is_a_numb }, //
    { Tcalc_num::N, Tcalc_num::Z, calc_is_a_0bnum }, //
    { Tcalc_num::N, Tcalc_num::Z, calc_is_a_0num }, //
    { Tcalc_num::N, Tcalc_num::Z, calc_is_a_numh }, //
    { Tcalc_num::N, Tcalc_num::Z, calc_is_a_dollar_num }, //
    { Tcalc_num::N, Tcalc_num::Z, calc_is_a_0xnum }, //
    { Tcalc_num::N, Tcalc_num::H, calc_is_a_dnum }, //
    { Tcalc_num::R, Tcalc_num::H, calc_is_a_fnum }, //
    { Tcalc_num::R, Tcalc_num::H, calc_is_a_enum }, //
    { Tcalc_num::N, Tcalc_num::H, calc_is_a_variable }, //
    { Tcalc_num::N, Tcalc_num::H, calc_is_a_function }, //
};

//-------------------------------------------------------------------
bool calc_is_a_num(Tcalc_num * dest, size_t * len, const char * src, Tcalc_num::num_type_e type) {
    size_t i, l;
    Tcalc_num v(type);
    *len = 0;
    for (i = 0; i < sizeof(calc_fnum) / sizeof(calc_fnum[0]); i++) {
        if (type >= calc_fnum[i].type_min && type <= calc_fnum[i].type_max && calc_fnum[i].f(&v, &l, src, type)) {
            if (l > *len) {
                *len = l;
                *dest = v;
            }
        }
    }
    return *len > 0 ? true : false;
}
