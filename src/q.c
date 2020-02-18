/*
 * q.c
 *
 *  Created on: 29-Jan-2020
 *      Author: rpmos
 */

#include "q.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct q{
	uint8_t front;
	uint8_t rear;
	uint8_t count;
	uint8_t size;

	uint8_t overwrite_on_full;

	uint8_t data_maxlen;
	uint8_t **data;
};


struct q *q_create(uint8_t size,uint8_t data_maxlen,uint8_t overwrite_on_full)
{
	//create a queue
	struct q *qp = malloc(sizeof(struct q));
	if(!qp){
		printf("q malloc fail\r\n");
		return 0;
	}

	if(size != 0){
		qp->size = size;
	}else{
		printf("q size 0 or empty \r\n");
		return 0;
	}
	qp->data_maxlen = data_maxlen;
	qp->overwrite_on_full = overwrite_on_full;
	qp->front = 0;
	qp->rear = 0;
	qp->count = 0;

	qp->data = malloc(qp->size*sizeof(uint8_t *));
	if(!qp->data){
		printf("q data malloc fail\r\n");
		return 0;
	}
	for(uint8_t i=0;i<qp->size;i++){
		qp->data[i] = malloc(qp->data_maxlen*sizeof(uint8_t));
		if(!qp->data[i]){
			printf("q data arr malloc fail\r\n");
			return 0;
		}
	}
	return qp;
}


void q_reset(struct q *qp)
{
	qp->front = 0;
	qp->rear = 0;
	qp->count = 0;
}

uint8_t q_isempty(struct q *qp)
{
	return (qp->front == qp->rear);
}

uint8_t q_isfull(struct q *qp)
{
	return (qp->front == (qp->rear+1)%(qp->size));
}

void q_print(struct q *qp)
{
	if(qp == NULL){
		printf("q null\r\n");
		return;
	}
	if(qp->size == 0 || qp->count == 0){
		printf("q size 0 or empty \r\n");
		return;
	}

	uint8_t itr = qp->front;
	uint8_t count = qp->count;

	for(;count;itr = (itr+1)%(qp->size),count--){

		printf("qp[%u]  :",itr);
		for(uint8_t j = 0;j < qp->data_maxlen;j++){
			printf("%x ",qp->data[itr][j]);
		}
		printf("\r\n");
	}
}

int8_t q_add(struct q *qp,uint8_t *msg,uint8_t len)
{
	if(qp == NULL){
		return -1;
	}
	if(msg == NULL || len > qp->data_maxlen){
		return -2;
	}

	if(!qp->overwrite_on_full && !q_isfull(qp)){

		memcpy(qp->data[qp->rear],msg,len);
		qp->rear = (qp->rear+1)%qp->size;
		qp->count++;
	}else{
		printf("q full \r\n");
		return -3;
	}
	return 1;
}




