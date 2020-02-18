/*
 * q.h
 *
 *  Created on: 29-Jan-2020
 *      Author: rpmos
 */

#ifndef Q_H_
#define Q_H_

#include <stdint.h>

struct q *q_create(uint8_t size,uint8_t data_maxlen,uint8_t overwrite_on_full);

void q_reset(struct q *qp);
uint8_t q_isempty(struct q *qp);
uint8_t q_isfull(struct q *qp);

void q_print(struct q *qp);

int8_t q_add(struct q *qp,uint8_t *msg,uint8_t len);

#endif /* Q_H_ */
