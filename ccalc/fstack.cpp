/*
 * fstack.cpp
 *
 *  Created on: 04 марта 2014 г.
 *      Author: moroz
 */

#include	<stdlib.h>
#include	"fstack.h"

//-------------------------------------------------------------------
bool calc_fpop(Tcalc_fs * *fs) {
	Tcalc_fs * fs_new;
	if (fs && *fs) {
		fs_new = (*fs)->next;
		free(*fs);
		*fs = fs_new;
        return true;
	}
    return false;
}

//-------------------------------------------------------------------
bool calc_fpush(Tcalc_fs ** fs, int f) {
    Tcalc_fs * fs_new = static_cast<Tcalc_fs *>(malloc(sizeof(Tcalc_fs)));
	if (fs && fs_new) {
		fs_new->f = f;
		fs_new->next = *fs;
		*fs = fs_new;
        return true;
	}
    return false;
}
