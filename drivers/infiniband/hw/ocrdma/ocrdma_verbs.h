<शैली गुरु>
/* This file is part of the Emulex RoCE Device Driver क्रम
 * RoCE (RDMA over Converged Ethernet) adapters.
 * Copyright (C) 2012-2015 Emulex. All rights reserved.
 * EMULEX and SLI are trademarks of Emulex.
 * www.emulex.com
 *
 * This software is available to you under a choice of one of two licenses.
 * You may choose to be licensed under the terms of the GNU General Public
 * License (GPL) Version 2, available from the file COPYING in the मुख्य
 * directory of this source tree, or the BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary क्रमm must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

#अगर_अघोषित __OCRDMA_VERBS_H__
#घोषणा __OCRDMA_VERBS_H__

पूर्णांक ocrdma_post_send(काष्ठा ib_qp *, स्थिर काष्ठा ib_send_wr *,
		     स्थिर काष्ठा ib_send_wr **bad_wr);
पूर्णांक ocrdma_post_recv(काष्ठा ib_qp *, स्थिर काष्ठा ib_recv_wr *,
		     स्थिर काष्ठा ib_recv_wr **bad_wr);

पूर्णांक ocrdma_poll_cq(काष्ठा ib_cq *, पूर्णांक num_entries, काष्ठा ib_wc *wc);
पूर्णांक ocrdma_arm_cq(काष्ठा ib_cq *, क्रमागत ib_cq_notअगरy_flags flags);

पूर्णांक ocrdma_query_device(काष्ठा ib_device *, काष्ठा ib_device_attr *props,
			काष्ठा ib_udata *uhw);
पूर्णांक ocrdma_query_port(काष्ठा ib_device *ibdev, u32 port,
		      काष्ठा ib_port_attr *props);

क्रमागत rdma_protocol_type
ocrdma_query_protocol(काष्ठा ib_device *device, u32 port_num);

व्योम ocrdma_get_guid(काष्ठा ocrdma_dev *, u8 *guid);
पूर्णांक ocrdma_query_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index, u16 *pkey);

पूर्णांक ocrdma_alloc_ucontext(काष्ठा ib_ucontext *uctx, काष्ठा ib_udata *udata);
व्योम ocrdma_dealloc_ucontext(काष्ठा ib_ucontext *uctx);

पूर्णांक ocrdma_mmap(काष्ठा ib_ucontext *, काष्ठा vm_area_काष्ठा *vma);

पूर्णांक ocrdma_alloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);
पूर्णांक ocrdma_dealloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);

पूर्णांक ocrdma_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		     काष्ठा ib_udata *udata);
पूर्णांक ocrdma_resize_cq(काष्ठा ib_cq *, पूर्णांक cqe, काष्ठा ib_udata *);
पूर्णांक ocrdma_destroy_cq(काष्ठा ib_cq *ibcq, काष्ठा ib_udata *udata);

काष्ठा ib_qp *ocrdma_create_qp(काष्ठा ib_pd *,
			       काष्ठा ib_qp_init_attr *attrs,
			       काष्ठा ib_udata *);
पूर्णांक _ocrdma_modअगरy_qp(काष्ठा ib_qp *, काष्ठा ib_qp_attr *attr,
		      पूर्णांक attr_mask);
पूर्णांक ocrdma_modअगरy_qp(काष्ठा ib_qp *, काष्ठा ib_qp_attr *attr,
		     पूर्णांक attr_mask, काष्ठा ib_udata *udata);
पूर्णांक ocrdma_query_qp(काष्ठा ib_qp *,
		    काष्ठा ib_qp_attr *qp_attr,
		    पूर्णांक qp_attr_mask, काष्ठा ib_qp_init_attr *);
पूर्णांक ocrdma_destroy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_udata *udata);
व्योम ocrdma_del_flush_qp(काष्ठा ocrdma_qp *qp);

पूर्णांक ocrdma_create_srq(काष्ठा ib_srq *srq, काष्ठा ib_srq_init_attr *attr,
		      काष्ठा ib_udata *udata);
पूर्णांक ocrdma_modअगरy_srq(काष्ठा ib_srq *, काष्ठा ib_srq_attr *,
		      क्रमागत ib_srq_attr_mask, काष्ठा ib_udata *);
पूर्णांक ocrdma_query_srq(काष्ठा ib_srq *, काष्ठा ib_srq_attr *);
पूर्णांक ocrdma_destroy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_udata *udata);
पूर्णांक ocrdma_post_srq_recv(काष्ठा ib_srq *, स्थिर काष्ठा ib_recv_wr *,
			 स्थिर काष्ठा ib_recv_wr **bad_recv_wr);

पूर्णांक ocrdma_dereg_mr(काष्ठा ib_mr *ib_mr, काष्ठा ib_udata *udata);
काष्ठा ib_mr *ocrdma_get_dma_mr(काष्ठा ib_pd *, पूर्णांक acc);
काष्ठा ib_mr *ocrdma_reg_user_mr(काष्ठा ib_pd *, u64 start, u64 length,
				 u64 virt, पूर्णांक acc, काष्ठा ib_udata *);
काष्ठा ib_mr *ocrdma_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			      u32 max_num_sg);
पूर्णांक ocrdma_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg, पूर्णांक sg_nents,
		     अचिन्हित पूर्णांक *sg_offset);

#पूर्ण_अगर				/* __OCRDMA_VERBS_H__ */
