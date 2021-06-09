/*
 * num.h
 *
 *  Created on: 04 марта 2014 г.
 *      Author: moroz
 */

#ifndef NUM_H_
#define NUM_H_
#include    <complex>

bool calc_is_a_num(std::complex<long double> * dest, size_t * len, const char * src);

void SetVariable(const char * name, std::complex<long double> v);
#include <QString>
void SetFunction(QString name, QString f);
void ClearFunctions(void);
void ClearVariables(void);

#endif /* NUM_H_ */
