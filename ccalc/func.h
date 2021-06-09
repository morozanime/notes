/*
 * func.h
 *
 *  Created on: 04 марта 2014 г.
 *      Author: moroz
 */

#ifndef FUNC_H_
#define FUNC_H_

#include	"dstack.h"

typedef struct {
    const char * name;
	int prior;
	bool (*f)(Tcalc_ds ** ds);
    int type;
} Tcalc_func;

extern Tcalc_func calc_func[];

bool calc_is_a_func(int * func, size_t * len, char * src, int last);
bool calc_func_index(int index, Tcalc_ds * *ds);

#endif /* FUNC_H_ */
