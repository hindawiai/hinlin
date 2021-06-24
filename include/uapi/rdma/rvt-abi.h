<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */

/*
 * This file contains defines, काष्ठाures, etc. that are used
 * to communicate between kernel and user code.
 */

#अगर_अघोषित RVT_ABI_USER_H
#घोषणा RVT_ABI_USER_H

#समावेश <linux/types.h>
#समावेश <rdma/ib_user_verbs.h>
#अगर_अघोषित RDMA_ATOMIC_UAPI
#घोषणा RDMA_ATOMIC_UAPI(_type, _name) काष्ठाअणु _type val; पूर्ण _name
#पूर्ण_अगर

काष्ठा rvt_wqe_sge अणु
	__aligned_u64 addr;
	__u32 length;
	__u32 lkey;
पूर्ण;

/*
 * This काष्ठाure is used to contain the head poपूर्णांकer, tail poपूर्णांकer,
 * and completion queue entries as a single memory allocation so
 * it can be mmap'ed पूर्णांकo user space.
 */
काष्ठा rvt_cq_wc अणु
	/* index of next entry to fill */
	RDMA_ATOMIC_UAPI(__u32, head);
	/* index of next ib_poll_cq() entry */
	RDMA_ATOMIC_UAPI(__u32, tail);

	/* these are actually size ibcq.cqe + 1 */
	काष्ठा ib_uverbs_wc uqueue[];
पूर्ण;

/*
 * Receive work request queue entry.
 * The size of the sg_list is determined when the QP (or SRQ) is created
 * and stored in qp->r_rq.max_sge (or srq->rq.max_sge).
 */
काष्ठा rvt_rwqe अणु
	__u64 wr_id;
	__u8 num_sge;
	__u8 padding[7];
	काष्ठा rvt_wqe_sge sg_list[];
पूर्ण;

/*
 * This काष्ठाure is used to contain the head poपूर्णांकer, tail poपूर्णांकer,
 * and receive work queue entries as a single memory allocation so
 * it can be mmap'ed पूर्णांकo user space.
 * Note that the wq array elements are variable size so you can't
 * just index पूर्णांकo the array to get the N'th element;
 * use get_rwqe_ptr() क्रम user space and rvt_get_rwqe_ptr()
 * क्रम kernel space.
 */
काष्ठा rvt_rwq अणु
	/* new work requests posted to the head */
	RDMA_ATOMIC_UAPI(__u32, head);
	/* receives pull requests from here. */
	RDMA_ATOMIC_UAPI(__u32, tail);
	काष्ठा rvt_rwqe wq[];
पूर्ण;
#पूर्ण_अगर /* RVT_ABI_USER_H */
