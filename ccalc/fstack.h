/*
 * fstack.h
 *
 *  Created on: 04 марта 2014 г.
 *      Author: moroz
 */

#ifndef FSTACK_H_
#define FSTACK_H_

typedef struct Tcalc_fs {
	int f;
	Tcalc_fs * next;
} Tcalc_fs;

bool calc_fpop(Tcalc_fs ** fs);
bool calc_fpush(Tcalc_fs ** fs, int f);

#endif /* FSTACK_H_ */
