<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright(c) 2018 Intel Corporation.
 *
 */
#समावेश "iowait.h"
#समावेश "trace_iowait.h"

/* 1 priority == 16 starve_cnt */
#घोषणा IOWAIT_PRIORITY_STARVE_SHIFT 4

व्योम ioरुको_set_flag(काष्ठा ioरुको *रुको, u32 flag)
अणु
	trace_hfi1_ioरुको_set(रुको, flag);
	set_bit(flag, &रुको->flags);
पूर्ण

bool ioरुको_flag_set(काष्ठा ioरुको *रुको, u32 flag)
अणु
	वापस test_bit(flag, &रुको->flags);
पूर्ण

अंतरभूत व्योम ioरुको_clear_flag(काष्ठा ioरुको *रुको, u32 flag)
अणु
	trace_hfi1_ioरुको_clear(रुको, flag);
	clear_bit(flag, &रुको->flags);
पूर्ण

/*
 * ioरुको_init() - initialize रुको काष्ठाure
 * @रुको: रुको काष्ठा to initialize
 * @tx_limit: limit क्रम overflow queuing
 * @func: restart function क्रम workqueue
 * @sleep: sleep function क्रम no space
 * @resume: wakeup function क्रम no space
 *
 * This function initializes the ioरुको
 * काष्ठाure embedded in the QP or PQ.
 *
 */
व्योम ioरुको_init(काष्ठा ioरुको *रुको, u32 tx_limit,
		 व्योम (*func)(काष्ठा work_काष्ठा *work),
		 व्योम (*tidfunc)(काष्ठा work_काष्ठा *work),
		 पूर्णांक (*sleep)(काष्ठा sdma_engine *sde,
			      काष्ठा ioरुको_work *रुको,
			      काष्ठा sdma_txreq *tx,
			      uपूर्णांक seq,
			      bool pkts_sent),
		 व्योम (*wakeup)(काष्ठा ioरुको *रुको, पूर्णांक reason),
		 व्योम (*sdma_drained)(काष्ठा ioरुको *रुको),
		 व्योम (*init_priority)(काष्ठा ioरुको *रुको))
अणु
	पूर्णांक i;

	रुको->count = 0;
	INIT_LIST_HEAD(&रुको->list);
	init_रुकोqueue_head(&रुको->रुको_dma);
	init_रुकोqueue_head(&रुको->रुको_pio);
	atomic_set(&रुको->sdma_busy, 0);
	atomic_set(&रुको->pio_busy, 0);
	रुको->tx_limit = tx_limit;
	रुको->sleep = sleep;
	रुको->wakeup = wakeup;
	रुको->sdma_drained = sdma_drained;
	रुको->init_priority = init_priority;
	रुको->flags = 0;
	क्रम (i = 0; i < IOWAIT_SES; i++) अणु
		रुको->रुको[i].iow = रुको;
		INIT_LIST_HEAD(&रुको->रुको[i].tx_head);
		अगर (i == IOWAIT_IB_SE)
			INIT_WORK(&रुको->रुको[i].iowork, func);
		अन्यथा
			INIT_WORK(&रुको->रुको[i].iowork, tidfunc);
	पूर्ण
पूर्ण

/**
 * ioरुको_cancel_work - cancel all work in ioरुको
 * @w: the ioरुको काष्ठा
 */
व्योम ioरुको_cancel_work(काष्ठा ioरुको *w)
अणु
	cancel_work_sync(&ioरुको_get_ib_work(w)->iowork);
	/* Make sure that the iowork क्रम TID RDMA is used */
	अगर (ioरुको_get_tid_work(w)->iowork.func)
		cancel_work_sync(&ioरुको_get_tid_work(w)->iowork);
पूर्ण

/**
 * ioरुको_set_work_flag - set work flag based on leg
 * @w: the ioरुको work काष्ठा
 */
पूर्णांक ioरुको_set_work_flag(काष्ठा ioरुको_work *w)
अणु
	अगर (w == &w->iow->रुको[IOWAIT_IB_SE]) अणु
		ioरुको_set_flag(w->iow, IOWAIT_PENDING_IB);
		वापस IOWAIT_IB_SE;
	पूर्ण
	ioरुको_set_flag(w->iow, IOWAIT_PENDING_TID);
	वापस IOWAIT_TID_SE;
पूर्ण

/**
 * ioरुको_priority_update_top - update the top priority entry
 * @w: the ioरुको काष्ठा
 * @top: a poपूर्णांकer to the top priority entry
 * @idx: the index of the current ioरुको in an array
 * @top_idx: the array index क्रम the ioरुको entry that has the top priority
 *
 * This function is called to compare the priority of a given
 * ioरुको with the given top priority entry. The top index will
 * be वापसed.
 */
uपूर्णांक ioरुको_priority_update_top(काष्ठा ioरुको *w,
				काष्ठा ioरुको *top,
				uपूर्णांक idx, uपूर्णांक top_idx)
अणु
	u8 cnt, tcnt;

	/* Convert priority पूर्णांकo starve_cnt and compare the total.*/
	cnt = (w->priority << IOWAIT_PRIORITY_STARVE_SHIFT) + w->starved_cnt;
	tcnt = (top->priority << IOWAIT_PRIORITY_STARVE_SHIFT) +
		top->starved_cnt;
	अगर (cnt > tcnt)
		वापस idx;
	अन्यथा
		वापस top_idx;
पूर्ण
