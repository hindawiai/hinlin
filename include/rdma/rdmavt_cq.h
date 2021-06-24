<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright(c) 2016 - 2018 Intel Corporation.
 */

#अगर_अघोषित DEF_RDMAVT_INCCQ_H
#घोषणा DEF_RDMAVT_INCCQ_H

#समावेश <linux/kthपढ़ो.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_verbs.h>

/*
 * Define an ib_cq_notअगरy value that is not valid so we know when CQ
 * notअगरications are armed.
 */
#घोषणा RVT_CQ_NONE      (IB_CQ_NEXT_COMP + 1)

/*
 * Define पढ़ो macro that apply smp_load_acquire memory barrier
 * when पढ़ोing indice of circular buffer that mmaped to user space.
 */
#घोषणा RDMA_READ_UAPI_ATOMIC(member) smp_load_acquire(&(member).val)

/*
 * Define ग_लिखो macro that uses smp_store_release memory barrier
 * when writing indice of circular buffer that mmaped to user space.
 */
#घोषणा RDMA_WRITE_UAPI_ATOMIC(member, x) smp_store_release(&(member).val, x)
#समावेश <rdma/rvt-abi.h>

/*
 * This काष्ठाure is used to contain the head poपूर्णांकer, tail poपूर्णांकer,
 * and completion queue entries as a single memory allocation so
 * it can be mmap'ed पूर्णांकo user space.
 */
काष्ठा rvt_k_cq_wc अणु
	u32 head;               /* index of next entry to fill */
	u32 tail;               /* index of next ib_poll_cq() entry */
	काष्ठा ib_wc kqueue[];
पूर्ण;

/*
 * The completion queue काष्ठाure.
 */
काष्ठा rvt_cq अणु
	काष्ठा ib_cq ibcq;
	काष्ठा work_काष्ठा comptask;
	spinlock_t lock; /* protect changes in this काष्ठा */
	u8 notअगरy;
	u8 triggered;
	u8 cq_full;
	पूर्णांक comp_vector_cpu;
	काष्ठा rvt_dev_info *rdi;
	काष्ठा rvt_cq_wc *queue;
	काष्ठा rvt_mmap_info *ip;
	काष्ठा rvt_k_cq_wc *kqueue;
पूर्ण;

अटल अंतरभूत काष्ठा rvt_cq *ibcq_to_rvtcq(काष्ठा ib_cq *ibcq)
अणु
	वापस container_of(ibcq, काष्ठा rvt_cq, ibcq);
पूर्ण

bool rvt_cq_enter(काष्ठा rvt_cq *cq, काष्ठा ib_wc *entry, bool solicited);

#पूर्ण_अगर          /* DEF_RDMAVT_INCCQH */
