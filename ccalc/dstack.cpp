/*
 * dstack.cpp
 *
 *  Created on: 04 марта 2014 г.
 *      Author: moroz
 */

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include    <complex>
#include	"dstack.h"

//-------------------------------------------------------------------
int calc_ddepth(Tcalc_ds * *ds) {
	Tcalc_ds * ds_new;
	int d = 0;
	if (ds && *ds) {
		d++;
		ds_new = (*ds)->next;
		while (ds_new) {
			ds_new = ds_new->next;
			d++;
		}
	}
	return d;
}

//-------------------------------------------------------------------
static bool calc_dpop(Tcalc_ds * *ds) {
	Tcalc_ds * ds_new;
	if (ds && *ds) {
		if ((*ds)->n.data)
			free((*ds)->n.data);
		ds_new = (*ds)->next;
		free(*ds);
		(*ds) = ds_new;
        return true;
	}
    return false;
}

//-------------------------------------------------------------------
static bool calc_dpush(Tcalc_ds ** ds, size_t size, int type, void * data) {
    Tcalc_ds * ds_new = static_cast<Tcalc_ds *>(malloc(sizeof(Tcalc_ds)));
	if (ds && ds_new) {
		ds_new->n.data = malloc(size);
		if (ds_new->n.data) {
			memcpy(ds_new->n.data, data, size);
			ds_new->n.size = size;
			ds_new->n.type = type;
			ds_new->next = *ds;
			*ds = ds_new;
            return true;
		} else
			free(ds_new);
	}
    return false;
}

//-------------------------------------------------------------------
std::complex<long double> calc_dpop_ld(Tcalc_ds ** ds) {
    std::complex<long double> v = 0;
	if (*ds) {
		if ((*ds)->n.type == 0 && (*ds)->n.size == sizeof(v))
			memcpy(&v, (*ds)->n.data, sizeof(v));
		calc_dpop(ds);
	}
	return v;
}

//-------------------------------------------------------------------
bool calc_dpush_ld(Tcalc_ds ** ds, std::complex<long double> v) {
	if (ds)
		return calc_dpush(ds, sizeof(v), 0, &v);
    return false;
}
