<शैली गुरु>
/*
 * Broadcom NetXtreme-E RoCE driver.
 *
 * Copyright (c) 2016 - 2017, Broadcom. All rights reserved.  The term
 * Broadcom refers to Broadcom Limited and/or its subsidiaries.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: IB Verbs पूर्णांकerpreter (header)
 */

#अगर_अघोषित __BNXT_RE_IB_VERBS_H__
#घोषणा __BNXT_RE_IB_VERBS_H__

काष्ठा bnxt_re_gid_ctx अणु
	u32			idx;
	u32			refcnt;
पूर्ण;

#घोषणा BNXT_RE_FENCE_BYTES	64
काष्ठा bnxt_re_fence_data अणु
	u32 size;
	u8 va[BNXT_RE_FENCE_BYTES];
	dma_addr_t dma_addr;
	काष्ठा bnxt_re_mr *mr;
	काष्ठा ib_mw *mw;
	काष्ठा bnxt_qplib_swqe bind_wqe;
	u32 bind_rkey;
पूर्ण;

काष्ठा bnxt_re_pd अणु
	काष्ठा ib_pd            ib_pd;
	काष्ठा bnxt_re_dev	*rdev;
	काष्ठा bnxt_qplib_pd	qplib_pd;
	काष्ठा bnxt_re_fence_data fence;
पूर्ण;

काष्ठा bnxt_re_ah अणु
	काष्ठा ib_ah		ib_ah;
	काष्ठा bnxt_re_dev	*rdev;
	काष्ठा bnxt_qplib_ah	qplib_ah;
पूर्ण;

काष्ठा bnxt_re_srq अणु
	काष्ठा ib_srq		ib_srq;
	काष्ठा bnxt_re_dev	*rdev;
	u32			srq_limit;
	काष्ठा bnxt_qplib_srq	qplib_srq;
	काष्ठा ib_umem		*umem;
	spinlock_t		lock;		/* protect srq */
पूर्ण;

काष्ठा bnxt_re_qp अणु
	काष्ठा list_head	list;
	काष्ठा bnxt_re_dev	*rdev;
	काष्ठा ib_qp		ib_qp;
	spinlock_t		sq_lock;	/* protect sq */
	spinlock_t		rq_lock;	/* protect rq */
	काष्ठा bnxt_qplib_qp	qplib_qp;
	काष्ठा ib_umem		*sumem;
	काष्ठा ib_umem		*rumem;
	/* QP1 */
	u32			send_psn;
	काष्ठा ib_ud_header	qp1_hdr;
	काष्ठा bnxt_re_cq	*scq;
	काष्ठा bnxt_re_cq	*rcq;
पूर्ण;

काष्ठा bnxt_re_cq अणु
	काष्ठा ib_cq		ib_cq;
	काष्ठा bnxt_re_dev	*rdev;
	spinlock_t              cq_lock;	/* protect cq */
	u16			cq_count;
	u16			cq_period;
	काष्ठा bnxt_qplib_cq	qplib_cq;
	काष्ठा bnxt_qplib_cqe	*cql;
#घोषणा MAX_CQL_PER_POLL	1024
	u32			max_cql;
	काष्ठा ib_umem		*umem;
पूर्ण;

काष्ठा bnxt_re_mr अणु
	काष्ठा bnxt_re_dev	*rdev;
	काष्ठा ib_mr		ib_mr;
	काष्ठा ib_umem		*ib_umem;
	काष्ठा bnxt_qplib_mrw	qplib_mr;
	u32			npages;
	u64			*pages;
	काष्ठा bnxt_qplib_frpl	qplib_frpl;
पूर्ण;

काष्ठा bnxt_re_frpl अणु
	काष्ठा bnxt_re_dev		*rdev;
	काष्ठा bnxt_qplib_frpl		qplib_frpl;
	u64				*page_list;
पूर्ण;

काष्ठा bnxt_re_mw अणु
	काष्ठा bnxt_re_dev	*rdev;
	काष्ठा ib_mw		ib_mw;
	काष्ठा bnxt_qplib_mrw	qplib_mw;
पूर्ण;

काष्ठा bnxt_re_ucontext अणु
	काष्ठा ib_ucontext      ib_uctx;
	काष्ठा bnxt_re_dev	*rdev;
	काष्ठा bnxt_qplib_dpi	dpi;
	व्योम			*shpg;
	spinlock_t		sh_lock;	/* protect shpg */
पूर्ण;

अटल अंतरभूत u16 bnxt_re_get_swqe_size(पूर्णांक nsge)
अणु
	वापस माप(काष्ठा sq_send_hdr) + nsge * माप(काष्ठा sq_sge);
पूर्ण

अटल अंतरभूत u16 bnxt_re_get_rwqe_size(पूर्णांक nsge)
अणु
	वापस माप(काष्ठा rq_wqe_hdr) + (nsge * माप(काष्ठा sq_sge));
पूर्ण

पूर्णांक bnxt_re_query_device(काष्ठा ib_device *ibdev,
			 काष्ठा ib_device_attr *ib_attr,
			 काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_query_port(काष्ठा ib_device *ibdev, u32 port_num,
		       काष्ठा ib_port_attr *port_attr);
पूर्णांक bnxt_re_get_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
			       काष्ठा ib_port_immutable *immutable);
व्योम bnxt_re_query_fw_str(काष्ठा ib_device *ibdev, अक्षर *str);
पूर्णांक bnxt_re_query_pkey(काष्ठा ib_device *ibdev, u32 port_num,
		       u16 index, u16 *pkey);
पूर्णांक bnxt_re_del_gid(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context);
पूर्णांक bnxt_re_add_gid(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context);
पूर्णांक bnxt_re_query_gid(काष्ठा ib_device *ibdev, u32 port_num,
		      पूर्णांक index, जोड़ ib_gid *gid);
क्रमागत rdma_link_layer bnxt_re_get_link_layer(काष्ठा ib_device *ibdev,
					    u32 port_num);
पूर्णांक bnxt_re_alloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_dealloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_create_ah(काष्ठा ib_ah *ah, काष्ठा rdma_ah_init_attr *init_attr,
		      काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_modअगरy_ah(काष्ठा ib_ah *ah, काष्ठा rdma_ah_attr *ah_attr);
पूर्णांक bnxt_re_query_ah(काष्ठा ib_ah *ah, काष्ठा rdma_ah_attr *ah_attr);
पूर्णांक bnxt_re_destroy_ah(काष्ठा ib_ah *ah, u32 flags);
पूर्णांक bnxt_re_create_srq(काष्ठा ib_srq *srq,
		       काष्ठा ib_srq_init_attr *srq_init_attr,
		       काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_modअगरy_srq(काष्ठा ib_srq *srq, काष्ठा ib_srq_attr *srq_attr,
		       क्रमागत ib_srq_attr_mask srq_attr_mask,
		       काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_query_srq(काष्ठा ib_srq *srq, काष्ठा ib_srq_attr *srq_attr);
पूर्णांक bnxt_re_destroy_srq(काष्ठा ib_srq *srq, काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_post_srq_recv(काष्ठा ib_srq *srq, स्थिर काष्ठा ib_recv_wr *recv_wr,
			  स्थिर काष्ठा ib_recv_wr **bad_recv_wr);
काष्ठा ib_qp *bnxt_re_create_qp(काष्ठा ib_pd *pd,
				काष्ठा ib_qp_init_attr *qp_init_attr,
				काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_modअगरy_qp(काष्ठा ib_qp *qp, काष्ठा ib_qp_attr *qp_attr,
		      पूर्णांक qp_attr_mask, काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_query_qp(काष्ठा ib_qp *qp, काष्ठा ib_qp_attr *qp_attr,
		     पूर्णांक qp_attr_mask, काष्ठा ib_qp_init_attr *qp_init_attr);
पूर्णांक bnxt_re_destroy_qp(काष्ठा ib_qp *qp, काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_post_send(काष्ठा ib_qp *qp, स्थिर काष्ठा ib_send_wr *send_wr,
		      स्थिर काष्ठा ib_send_wr **bad_send_wr);
पूर्णांक bnxt_re_post_recv(काष्ठा ib_qp *qp, स्थिर काष्ठा ib_recv_wr *recv_wr,
		      स्थिर काष्ठा ib_recv_wr **bad_recv_wr);
पूर्णांक bnxt_re_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		      काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_destroy_cq(काष्ठा ib_cq *cq, काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_poll_cq(काष्ठा ib_cq *cq, पूर्णांक num_entries, काष्ठा ib_wc *wc);
पूर्णांक bnxt_re_req_notअगरy_cq(काष्ठा ib_cq *cq, क्रमागत ib_cq_notअगरy_flags flags);
काष्ठा ib_mr *bnxt_re_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक mr_access_flags);

पूर्णांक bnxt_re_map_mr_sg(काष्ठा ib_mr *ib_mr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		      अचिन्हित पूर्णांक *sg_offset);
काष्ठा ib_mr *bnxt_re_alloc_mr(काष्ठा ib_pd *ib_pd, क्रमागत ib_mr_type mr_type,
			       u32 max_num_sg);
पूर्णांक bnxt_re_dereg_mr(काष्ठा ib_mr *mr, काष्ठा ib_udata *udata);
काष्ठा ib_mw *bnxt_re_alloc_mw(काष्ठा ib_pd *ib_pd, क्रमागत ib_mw_type type,
			       काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_dealloc_mw(काष्ठा ib_mw *mw);
काष्ठा ib_mr *bnxt_re_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
				  u64 virt_addr, पूर्णांक mr_access_flags,
				  काष्ठा ib_udata *udata);
पूर्णांक bnxt_re_alloc_ucontext(काष्ठा ib_ucontext *ctx, काष्ठा ib_udata *udata);
व्योम bnxt_re_dealloc_ucontext(काष्ठा ib_ucontext *context);
पूर्णांक bnxt_re_mmap(काष्ठा ib_ucontext *context, काष्ठा vm_area_काष्ठा *vma);

अचिन्हित दीर्घ bnxt_re_lock_cqs(काष्ठा bnxt_re_qp *qp);
व्योम bnxt_re_unlock_cqs(काष्ठा bnxt_re_qp *qp, अचिन्हित दीर्घ flags);
#पूर्ण_अगर /* __BNXT_RE_IB_VERBS_H__ */
