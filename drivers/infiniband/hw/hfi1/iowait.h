<शैली गुरु>
#अगर_अघोषित _HFI1_IOWAIT_H
#घोषणा _HFI1_IOWAIT_H
/*
 * Copyright(c) 2015 - 2018 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>

#समावेश "sdma_txreq.h"

/*
 * प्रकार (*restart_t)() - restart callback
 * @work: poपूर्णांकer to work काष्ठाure
 */
प्रकार व्योम (*restart_t)(काष्ठा work_काष्ठा *work);

#घोषणा IOWAIT_PENDING_IB  0x0
#घोषणा IOWAIT_PENDING_TID 0x1

/*
 * A QP can have multiple Send Engines (SEs).
 *
 * The current use हाल is क्रम supporting a TID RDMA
 * packet build/xmit mechanism independent from verbs.
 */
#घोषणा IOWAIT_SES 2
#घोषणा IOWAIT_IB_SE 0
#घोषणा IOWAIT_TID_SE 1

काष्ठा sdma_txreq;
काष्ठा sdma_engine;
/**
 * @iowork: the work काष्ठा
 * @tx_head: list of prebuilt packets
 * @iow: the parent ioरुको काष्ठाure
 *
 * This काष्ठाure is the work item (process) specअगरic
 * details associated with the each of the two SEs of the
 * QP.
 *
 * The workकाष्ठा and the queued TXs are unique to each
 * SE.
 */
काष्ठा ioरुको;
काष्ठा ioरुको_work अणु
	काष्ठा work_काष्ठा iowork;
	काष्ठा list_head tx_head;
	काष्ठा ioरुको *iow;
पूर्ण;

/**
 * @list: used to add/insert पूर्णांकo QP/PQ रुको lists
 * @tx_head: overflow list of sdma_txreq's
 * @sleep: no space callback
 * @wakeup: space callback wakeup
 * @sdma_drained: sdma count drained
 * @init_priority: callback to manipulate priority
 * @lock: lock रक्षित head of रुको queue
 * @iowork: workqueue overhead
 * @रुको_dma: रुको क्रम sdma_busy == 0
 * @रुको_pio: रुको क्रम pio_busy == 0
 * @sdma_busy: # of packets in flight
 * @count: total number of descriptors in tx_head'ed list
 * @tx_limit: limit क्रम overflow queuing
 * @tx_count: number of tx entry's in tx_head'ed list
 * @flags: रुको flags (one per QP)
 * @रुको: SE array क्रम multiple legs
 *
 * This is to be embedded in user's state काष्ठाure
 * (QP or PQ).
 *
 * The sleep and wakeup members are a
 * bit misnamed.   They करो not strictly
 * speaking sleep or wake up, but they
 * are callbacks क्रम the ULP to implement
 * what ever queuing/dequeuing of
 * the embedded ioरुको and its containing काष्ठा
 * when a resource लघुage like SDMA ring space
 * or PIO credit space is seen.
 *
 * Both potentially have locks help
 * so sleeping is not allowed and it is not
 * supported to submit txreqs from the wakeup
 * call directly because of lock conflicts.
 *
 * The रुको_dma member aदीर्घ with the iow
 *
 * The lock field is used by रुकोers to record
 * the seqlock_t that guards the list head.
 * Waiters explicity know that, but the destroy
 * code that unरुकोs QPs करोes not.
 */
काष्ठा ioरुको अणु
	काष्ठा list_head list;
	पूर्णांक (*sleep)(
		काष्ठा sdma_engine *sde,
		काष्ठा ioरुको_work *रुको,
		काष्ठा sdma_txreq *tx,
		uपूर्णांक seq,
		bool pkts_sent
		);
	व्योम (*wakeup)(काष्ठा ioरुको *रुको, पूर्णांक reason);
	व्योम (*sdma_drained)(काष्ठा ioरुको *रुको);
	व्योम (*init_priority)(काष्ठा ioरुको *रुको);
	seqlock_t *lock;
	रुको_queue_head_t रुको_dma;
	रुको_queue_head_t रुको_pio;
	atomic_t sdma_busy;
	atomic_t pio_busy;
	u32 count;
	u32 tx_limit;
	u32 tx_count;
	u8 starved_cnt;
	u8 priority;
	अचिन्हित दीर्घ flags;
	काष्ठा ioरुको_work रुको[IOWAIT_SES];
पूर्ण;

#घोषणा SDMA_AVAIL_REASON 0

व्योम ioरुको_set_flag(काष्ठा ioरुको *रुको, u32 flag);
bool ioरुको_flag_set(काष्ठा ioरुको *रुको, u32 flag);
व्योम ioरुको_clear_flag(काष्ठा ioरुको *रुको, u32 flag);

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
		 व्योम (*init_priority)(काष्ठा ioरुको *रुको));

/**
 * ioरुको_schedule() - schedule the शेष send engine work
 * @रुको: रुको काष्ठा to schedule
 * @wq: workqueue क्रम schedule
 * @cpu: cpu
 */
अटल अंतरभूत bool ioरुको_schedule(काष्ठा ioरुको *रुको,
				   काष्ठा workqueue_काष्ठा *wq, पूर्णांक cpu)
अणु
	वापस !!queue_work_on(cpu, wq, &रुको->रुको[IOWAIT_IB_SE].iowork);
पूर्ण

/**
 * ioरुको_tid_schedule - schedule the tid SE
 * @रुको: the ioरुको काष्ठाure
 * @wq: the work queue
 * @cpu: the cpu
 */
अटल अंतरभूत bool ioरुको_tid_schedule(काष्ठा ioरुको *रुको,
				       काष्ठा workqueue_काष्ठा *wq, पूर्णांक cpu)
अणु
	वापस !!queue_work_on(cpu, wq, &रुको->रुको[IOWAIT_TID_SE].iowork);
पूर्ण

/**
 * ioरुको_sdma_drain() - रुको क्रम DMAs to drain
 *
 * @रुको: ioरुको काष्ठाure
 *
 * This will delay until the ioरुको sdmas have
 * completed.
 */
अटल अंतरभूत व्योम ioरुको_sdma_drain(काष्ठा ioरुको *रुको)
अणु
	रुको_event(रुको->रुको_dma, !atomic_पढ़ो(&रुको->sdma_busy));
पूर्ण

/**
 * ioरुको_sdma_pending() - वापस sdma pending count
 *
 * @रुको: ioरुको काष्ठाure
 *
 */
अटल अंतरभूत पूर्णांक ioरुको_sdma_pending(काष्ठा ioरुको *रुको)
अणु
	वापस atomic_पढ़ो(&रुको->sdma_busy);
पूर्ण

/**
 * ioरुको_sdma_inc - note sdma io pending
 * @रुको: ioरुको काष्ठाure
 */
अटल अंतरभूत व्योम ioरुको_sdma_inc(काष्ठा ioरुको *रुको)
अणु
	atomic_inc(&रुको->sdma_busy);
पूर्ण

/**
 * ioरुको_sdma_add - add count to pending
 * @रुको: ioरुको काष्ठाure
 */
अटल अंतरभूत व्योम ioरुको_sdma_add(काष्ठा ioरुको *रुको, पूर्णांक count)
अणु
	atomic_add(count, &रुको->sdma_busy);
पूर्ण

/**
 * ioरुको_sdma_dec - note sdma complete
 * @रुको: ioरुको काष्ठाure
 */
अटल अंतरभूत पूर्णांक ioरुको_sdma_dec(काष्ठा ioरुको *रुको)
अणु
	अगर (!रुको)
		वापस 0;
	वापस atomic_dec_and_test(&रुको->sdma_busy);
पूर्ण

/**
 * ioरुको_pio_drain() - रुको क्रम pios to drain
 *
 * @रुको: ioरुको काष्ठाure
 *
 * This will delay until the ioरुको pios have
 * completed.
 */
अटल अंतरभूत व्योम ioरुको_pio_drain(काष्ठा ioरुको *रुको)
अणु
	रुको_event_समयout(रुको->रुको_pio,
			   !atomic_पढ़ो(&रुको->pio_busy),
			   HZ);
पूर्ण

/**
 * ioरुको_pio_pending() - वापस pio pending count
 *
 * @रुको: ioरुको काष्ठाure
 *
 */
अटल अंतरभूत पूर्णांक ioरुको_pio_pending(काष्ठा ioरुको *रुको)
अणु
	वापस atomic_पढ़ो(&रुको->pio_busy);
पूर्ण

/**
 * ioरुको_pio_inc - note pio pending
 * @रुको: ioरुको काष्ठाure
 */
अटल अंतरभूत व्योम ioरुको_pio_inc(काष्ठा ioरुको *रुको)
अणु
	atomic_inc(&रुको->pio_busy);
पूर्ण

/**
 * ioरुको_pio_dec - note pio complete
 * @रुको: ioरुको काष्ठाure
 */
अटल अंतरभूत पूर्णांक ioरुको_pio_dec(काष्ठा ioरुको *रुको)
अणु
	अगर (!रुको)
		वापस 0;
	वापस atomic_dec_and_test(&रुको->pio_busy);
पूर्ण

/**
 * ioरुको_drain_wakeup() - trigger ioरुको_drain() रुकोer
 *
 * @रुको: ioरुको काष्ठाure
 *
 * This will trigger any रुकोers.
 */
अटल अंतरभूत व्योम ioरुको_drain_wakeup(काष्ठा ioरुको *रुको)
अणु
	wake_up(&रुको->रुको_dma);
	wake_up(&रुको->रुको_pio);
	अगर (रुको->sdma_drained)
		रुको->sdma_drained(रुको);
पूर्ण

/**
 * ioरुको_get_txhead() - get packet off of ioरुको list
 *
 * @रुको: ioरुको_work काष्ठाure
 */
अटल अंतरभूत काष्ठा sdma_txreq *ioरुको_get_txhead(काष्ठा ioरुको_work *रुको)
अणु
	काष्ठा sdma_txreq *tx = शून्य;

	अगर (!list_empty(&रुको->tx_head)) अणु
		tx = list_first_entry(
			&रुको->tx_head,
			काष्ठा sdma_txreq,
			list);
		list_del_init(&tx->list);
	पूर्ण
	वापस tx;
पूर्ण

अटल अंतरभूत u16 ioरुको_get_desc(काष्ठा ioरुको_work *w)
अणु
	u16 num_desc = 0;
	काष्ठा sdma_txreq *tx = शून्य;

	अगर (!list_empty(&w->tx_head)) अणु
		tx = list_first_entry(&w->tx_head, काष्ठा sdma_txreq,
				      list);
		num_desc = tx->num_desc;
		अगर (tx->flags & SDMA_TXREQ_F_VIP)
			w->iow->priority++;
	पूर्ण
	वापस num_desc;
पूर्ण

अटल अंतरभूत u32 ioरुको_get_all_desc(काष्ठा ioरुको *w)
अणु
	u32 num_desc = 0;

	num_desc = ioरुको_get_desc(&w->रुको[IOWAIT_IB_SE]);
	num_desc += ioरुको_get_desc(&w->रुको[IOWAIT_TID_SE]);
	वापस num_desc;
पूर्ण

अटल अंतरभूत व्योम ioरुको_update_priority(काष्ठा ioरुको_work *w)
अणु
	काष्ठा sdma_txreq *tx = शून्य;

	अगर (!list_empty(&w->tx_head)) अणु
		tx = list_first_entry(&w->tx_head, काष्ठा sdma_txreq,
				      list);
		अगर (tx->flags & SDMA_TXREQ_F_VIP)
			w->iow->priority++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ioरुको_update_all_priority(काष्ठा ioरुको *w)
अणु
	ioरुको_update_priority(&w->रुको[IOWAIT_IB_SE]);
	ioरुको_update_priority(&w->रुको[IOWAIT_TID_SE]);
पूर्ण

अटल अंतरभूत व्योम ioरुको_init_priority(काष्ठा ioरुको *w)
अणु
	w->priority = 0;
	अगर (w->init_priority)
		w->init_priority(w);
पूर्ण

अटल अंतरभूत व्योम ioरुको_get_priority(काष्ठा ioरुको *w)
अणु
	ioरुको_init_priority(w);
	ioरुको_update_all_priority(w);
पूर्ण

/**
 * ioरुको_queue - Put the ioरुको on a रुको queue
 * @pkts_sent: have some packets been sent beक्रमe queuing?
 * @w: the ioरुको काष्ठा
 * @रुको_head: the रुको queue
 *
 * This function is called to insert an ioरुको काष्ठा पूर्णांकo a
 * रुको queue after a resource (eg, sdma descriptor or pio
 * buffer) is run out.
 */
अटल अंतरभूत व्योम ioरुको_queue(bool pkts_sent, काष्ठा ioरुको *w,
				काष्ठा list_head *रुको_head)
अणु
	/*
	 * To play fair, insert the ioरुको at the tail of the रुको queue अगर it
	 * has alपढ़ोy sent some packets; Otherwise, put it at the head.
	 * However, अगर it has priority packets to send, also put it at the
	 * head.
	 */
	अगर (pkts_sent)
		w->starved_cnt = 0;
	अन्यथा
		w->starved_cnt++;

	अगर (w->priority > 0 || !pkts_sent)
		list_add(&w->list, रुको_head);
	अन्यथा
		list_add_tail(&w->list, रुको_head);
पूर्ण

/**
 * ioरुको_starve_clear - clear the रुको queue's starve count
 * @pkts_sent: have some packets been sent?
 * @w: the ioरुको काष्ठा
 *
 * This function is called to clear the starve count. If no
 * packets have been sent, the starve count will not be cleared.
 */
अटल अंतरभूत व्योम ioरुको_starve_clear(bool pkts_sent, काष्ठा ioरुको *w)
अणु
	अगर (pkts_sent)
		w->starved_cnt = 0;
पूर्ण

/* Update the top priority index */
uपूर्णांक ioरुको_priority_update_top(काष्ठा ioरुको *w,
				काष्ठा ioरुको *top,
				uपूर्णांक idx, uपूर्णांक top_idx);

/**
 * ioरुको_packet_queued() - determine अगर a packet is queued
 * @रुको: the ioरुको_work काष्ठाure
 */
अटल अंतरभूत bool ioरुको_packet_queued(काष्ठा ioरुको_work *रुको)
अणु
	वापस !list_empty(&रुको->tx_head);
पूर्ण

/**
 * inc_रुको_count - increment रुको counts
 * @w: the log work काष्ठा
 * @n: the count
 */
अटल अंतरभूत व्योम ioरुको_inc_रुको_count(काष्ठा ioरुको_work *w, u16 n)
अणु
	अगर (!w)
		वापस;
	w->iow->tx_count++;
	w->iow->count += n;
पूर्ण

/**
 * ioरुको_get_tid_work - वापस ioरुको_work क्रम tid SE
 * @w: the ioरुको काष्ठा
 */
अटल अंतरभूत काष्ठा ioरुको_work *ioरुको_get_tid_work(काष्ठा ioरुको *w)
अणु
	वापस &w->रुको[IOWAIT_TID_SE];
पूर्ण

/**
 * ioरुको_get_ib_work - वापस ioरुको_work क्रम ib SE
 * @w: the ioरुको काष्ठा
 */
अटल अंतरभूत काष्ठा ioरुको_work *ioरुको_get_ib_work(काष्ठा ioरुको *w)
अणु
	वापस &w->रुको[IOWAIT_IB_SE];
पूर्ण

/**
 * ioरुको_ioww_to_iow - वापस ioरुको given ioरुको_work
 * @w: the ioरुको_work काष्ठा
 */
अटल अंतरभूत काष्ठा ioरुको *ioरुको_ioww_to_iow(काष्ठा ioरुको_work *w)
अणु
	अगर (likely(w))
		वापस w->iow;
	वापस शून्य;
पूर्ण

व्योम ioरुको_cancel_work(काष्ठा ioरुको *w);
पूर्णांक ioरुको_set_work_flag(काष्ठा ioरुको_work *w);

#पूर्ण_अगर
