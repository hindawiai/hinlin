<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित MTHCA_PROVIDER_H
#घोषणा MTHCA_PROVIDER_H

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_pack.h>

#घोषणा MTHCA_MPT_FLAG_ATOMIC        (1 << 14)
#घोषणा MTHCA_MPT_FLAG_REMOTE_WRITE  (1 << 13)
#घोषणा MTHCA_MPT_FLAG_REMOTE_READ   (1 << 12)
#घोषणा MTHCA_MPT_FLAG_LOCAL_WRITE   (1 << 11)
#घोषणा MTHCA_MPT_FLAG_LOCAL_READ    (1 << 10)

काष्ठा mthca_buf_list अणु
	व्योम *buf;
	DEFINE_DMA_UNMAP_ADDR(mapping);
पूर्ण;

जोड़ mthca_buf अणु
	काष्ठा mthca_buf_list direct;
	काष्ठा mthca_buf_list *page_list;
पूर्ण;

काष्ठा mthca_uar अणु
	अचिन्हित दीर्घ pfn;
	पूर्णांक           index;
पूर्ण;

काष्ठा mthca_user_db_table;

काष्ठा mthca_ucontext अणु
	काष्ठा ib_ucontext          ibucontext;
	काष्ठा mthca_uar            uar;
	काष्ठा mthca_user_db_table *db_tab;
	पूर्णांक			    reg_mr_warned;
पूर्ण;

काष्ठा mthca_mtt;

काष्ठा mthca_mr अणु
	काष्ठा ib_mr      ibmr;
	काष्ठा ib_umem   *umem;
	काष्ठा mthca_mtt *mtt;
पूर्ण;

काष्ठा mthca_pd अणु
	काष्ठा ib_pd    ibpd;
	u32             pd_num;
	atomic_t        sqp_count;
	काष्ठा mthca_mr nपंचांगr;
	पूर्णांक             privileged;
पूर्ण;

काष्ठा mthca_eq अणु
	काष्ठा mthca_dev      *dev;
	पूर्णांक                    eqn;
	u32                    eqn_mask;
	u32                    cons_index;
	u16                    msi_x_vector;
	u16                    msi_x_entry;
	पूर्णांक                    have_irq;
	पूर्णांक                    nent;
	काष्ठा mthca_buf_list *page_list;
	काष्ठा mthca_mr        mr;
	अक्षर		       irq_name[IB_DEVICE_NAME_MAX];
पूर्ण;

काष्ठा mthca_av;

क्रमागत mthca_ah_type अणु
	MTHCA_AH_ON_HCA,
	MTHCA_AH_PCI_POOL,
	MTHCA_AH_KMALLOC
पूर्ण;

काष्ठा mthca_ah अणु
	काष्ठा ib_ah       ibah;
	क्रमागत mthca_ah_type type;
	u32                key;
	काष्ठा mthca_av   *av;
	dma_addr_t         avdma;
पूर्ण;

/*
 * Quick description of our CQ/QP locking scheme:
 *
 * We have one global lock that protects dev->cq/qp_table.  Each
 * काष्ठा mthca_cq/qp also has its own lock.  An inभागidual qp lock
 * may be taken inside of an inभागidual cq lock.  Both cqs attached to
 * a qp may be locked, with the cq with the lower cqn locked first.
 * No other nesting should be करोne.
 *
 * Each काष्ठा mthca_cq/qp also has an ref count, रक्षित by the
 * corresponding table lock.  The poपूर्णांकer from the cq/qp_table to the
 * काष्ठा counts as one reference.  This reference also is good क्रम
 * access through the consumer API, so modअगरying the CQ/QP etc करोesn't
 * need to take another reference.  Access to a QP because of a
 * completion being polled करोes not need a reference either.
 *
 * Finally, each काष्ठा mthca_cq/qp has a रुको_queue_head_t क्रम the
 * destroy function to sleep on.
 *
 * This means that access from the consumer API requires nothing but
 * taking the काष्ठा's lock.
 *
 * Access because of a completion event should go as follows:
 * - lock cq/qp_table and look up काष्ठा
 * - increment ref count in काष्ठा
 * - drop cq/qp_table lock
 * - lock काष्ठा, करो your thing, and unlock काष्ठा
 * - decrement ref count; अगर zero, wake up रुकोers
 *
 * To destroy a CQ/QP, we can करो the following:
 * - lock cq/qp_table
 * - हटाओ poपूर्णांकer and decrement ref count
 * - unlock cq/qp_table lock
 * - रुको_event until ref count is zero
 *
 * It is the consumer's responsibilty to make sure that no QP
 * operations (WQE posting or state modअगरication) are pending when a
 * QP is destroyed.  Also, the consumer must make sure that calls to
 * qp_modअगरy are serialized.  Similarly, the consumer is responsible
 * क्रम ensuring that no CQ resize operations are pending when a CQ
 * is destroyed.
 *
 * Possible optimizations (रुको क्रम profile data to see अगर/where we
 * have locks bouncing between CPUs):
 * - split cq/qp table lock पूर्णांकo n separate (cache-aligned) locks,
 *   indexed (say) by the page in the table
 * - split QP काष्ठा lock पूर्णांकo three (one क्रम common info, one क्रम the
 *   send queue and one क्रम the receive queue)
 */

काष्ठा mthca_cq_buf अणु
	जोड़ mthca_buf		queue;
	काष्ठा mthca_mr		mr;
	पूर्णांक			is_direct;
पूर्ण;

काष्ठा mthca_cq_resize अणु
	काष्ठा mthca_cq_buf	buf;
	पूर्णांक			cqe;
	क्रमागत अणु
		CQ_RESIZE_ALLOC,
		CQ_RESIZE_READY,
		CQ_RESIZE_SWAPPED
	पूर्ण			state;
पूर्ण;

काष्ठा mthca_cq अणु
	काष्ठा ib_cq		ibcq;
	spinlock_t		lock;
	पूर्णांक			refcount;
	पूर्णांक			cqn;
	u32			cons_index;
	काष्ठा mthca_cq_buf	buf;
	काष्ठा mthca_cq_resize *resize_buf;
	पूर्णांक			is_kernel;

	/* Next fields are Arbel only */
	पूर्णांक			set_ci_db_index;
	__be32		       *set_ci_db;
	पूर्णांक			arm_db_index;
	__be32		       *arm_db;
	पूर्णांक			arm_sn;

	रुको_queue_head_t	रुको;
	काष्ठा mutex		mutex;
पूर्ण;

काष्ठा mthca_srq अणु
	काष्ठा ib_srq		ibsrq;
	spinlock_t		lock;
	पूर्णांक			refcount;
	पूर्णांक			srqn;
	पूर्णांक			max;
	पूर्णांक			max_gs;
	पूर्णांक			wqe_shअगरt;
	पूर्णांक			first_मुक्त;
	पूर्णांक			last_मुक्त;
	u16			counter;  /* Arbel only */
	पूर्णांक			db_index; /* Arbel only */
	__be32		       *db;       /* Arbel only */
	व्योम		       *last;

	पूर्णांक			is_direct;
	u64		       *wrid;
	जोड़ mthca_buf		queue;
	काष्ठा mthca_mr		mr;

	रुको_queue_head_t	रुको;
	काष्ठा mutex		mutex;
पूर्ण;

काष्ठा mthca_wq अणु
	spinlock_t lock;
	पूर्णांक        max;
	अचिन्हित   next_ind;
	अचिन्हित   last_comp;
	अचिन्हित   head;
	अचिन्हित   tail;
	व्योम      *last;
	पूर्णांक        max_gs;
	पूर्णांक        wqe_shअगरt;

	पूर्णांक        db_index;	/* Arbel only */
	__be32    *db;
पूर्ण;

काष्ठा mthca_sqp अणु
	पूर्णांक             pkey_index;
	u32             qkey;
	u32             send_psn;
	काष्ठा ib_ud_header ud_header;
	पूर्णांक             header_buf_size;
	व्योम           *header_buf;
	dma_addr_t      header_dma;
पूर्ण;

काष्ठा mthca_qp अणु
	काष्ठा ib_qp           ibqp;
	पूर्णांक                    refcount;
	u32                    qpn;
	पूर्णांक                    is_direct;
	u8                     port; /* क्रम SQP and memमुक्त use only */
	u8                     alt_port; /* क्रम memमुक्त use only */
	u8                     transport;
	u8                     state;
	u8                     atomic_rd_en;
	u8                     resp_depth;

	काष्ठा mthca_mr        mr;

	काष्ठा mthca_wq        rq;
	काष्ठा mthca_wq        sq;
	क्रमागत ib_sig_type       sq_policy;
	पूर्णांक                    send_wqe_offset;
	पूर्णांक                    max_अंतरभूत_data;

	u64                   *wrid;
	जोड़ mthca_buf	       queue;

	रुको_queue_head_t      रुको;
	काष्ठा mutex	       mutex;
	काष्ठा mthca_sqp *sqp;
पूर्ण;

अटल अंतरभूत काष्ठा mthca_ucontext *to_mucontext(काष्ठा ib_ucontext *ibucontext)
अणु
	वापस container_of(ibucontext, काष्ठा mthca_ucontext, ibucontext);
पूर्ण

अटल अंतरभूत काष्ठा mthca_mr *to_mmr(काष्ठा ib_mr *ibmr)
अणु
	वापस container_of(ibmr, काष्ठा mthca_mr, ibmr);
पूर्ण

अटल अंतरभूत काष्ठा mthca_pd *to_mpd(काष्ठा ib_pd *ibpd)
अणु
	वापस container_of(ibpd, काष्ठा mthca_pd, ibpd);
पूर्ण

अटल अंतरभूत काष्ठा mthca_ah *to_mah(काष्ठा ib_ah *ibah)
अणु
	वापस container_of(ibah, काष्ठा mthca_ah, ibah);
पूर्ण

अटल अंतरभूत काष्ठा mthca_cq *to_mcq(काष्ठा ib_cq *ibcq)
अणु
	वापस container_of(ibcq, काष्ठा mthca_cq, ibcq);
पूर्ण

अटल अंतरभूत काष्ठा mthca_srq *to_msrq(काष्ठा ib_srq *ibsrq)
अणु
	वापस container_of(ibsrq, काष्ठा mthca_srq, ibsrq);
पूर्ण

अटल अंतरभूत काष्ठा mthca_qp *to_mqp(काष्ठा ib_qp *ibqp)
अणु
	वापस container_of(ibqp, काष्ठा mthca_qp, ibqp);
पूर्ण

#पूर्ण_अगर /* MTHCA_PROVIDER_H */
