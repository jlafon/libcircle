#ifndef TOKEN_H
#define TOKEN_H

#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <mpi.h>

#include "queue.h"
#include "lib.h"
enum tags {
    WHITE,
    BLACK,
    DONE,
    TERMINATE = -1,
    WORK_REQUEST,
    WORK,
    TOKEN,
    SUCCESS,
    ABORT = -32
};

typedef struct options {
    char* beginning_path;
    int  verbose;
} options;

typedef struct CIRCLE_mpi_state_st {
    MPI_Status term_status;
    MPI_Status work_offsets_status;
    MPI_Status work_status;
    MPI_Status* request_status;

    MPI_Request term_request;
    MPI_Request work_offsets_request;
    MPI_Request work_request;
    MPI_Request* request_request;

    MPI_Comm* token_comm;
    MPI_Comm* work_comm;
} CIRCLE_mpi_state_st;

typedef struct CIRCLE_state_st {
    CIRCLE_mpi_state_st* mpi_state_st;

    int8_t verbose;
    int8_t have_token;
    int8_t token;
    uint32_t rank;
    uint32_t size;
    uint32_t next_processor;
    uint32_t token_partner;

    int8_t term_flag;
    int8_t work_flag;
    int8_t* request_flag;
    int8_t work_pending_request;
    int8_t request_pending_receive;
    int8_t term_pending_receive;
    int8_t incoming_token;

    uint32_t* work_offsets;
    uint32_t* request_offsets;

    int32_t* request_recv_buf;
    int32_t work_request_tries;
} CIRCLE_state_st;

uint32_t  CIRCLE_get_next_proc(int32_t rank, int32_t size);
void CIRCLE_send_no_work(int32_t dest);
int32_t  CIRCLE_check_for_term(CIRCLE_state_st* st);
int32_t  CIRCLE_wait_on_probe(CIRCLE_state_st* st, int32_t source, int32_t tag);

int32_t  CIRCLE_check_for_requests(CIRCLE_internal_queue_t* queue, \
                               CIRCLE_state_st* state);
int32_t  CIRCLE_request_work(CIRCLE_internal_queue_t* queue, \
                         CIRCLE_state_st* state);

void CIRCLE_send_work_to_many(CIRCLE_internal_queue_t* queue, \
                              CIRCLE_state_st* state, \
                              int* requestors, int32_t rcount);
int32_t  CIRCLE_send_work(CIRCLE_internal_queue_t* queue, \
                      CIRCLE_state_st* state, \
                      int32_t dest, int32_t count);

void CIRCLE_bcast_abort(void);

#endif /* TOKEN_H */
