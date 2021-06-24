<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause */

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/* Copyright (c) 2008-2019, IBM Corporation */

#अगर_अघोषित _SIW_VERBS_H
#घोषणा _SIW_VERBS_H

#समावेश <linux/त्रुटिसं.स>

#समावेश <rdma/iw_cm.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>

#समावेश "siw.h"
#समावेश "siw_cm.h"

/*
 * siw_copy_sgl()
 *
 * Copy SGL from RDMA core representation to local
 * representation.
 */
अटल अंतरभूत व्योम siw_copy_sgl(काष्ठा ib_sge *sge, काष्ठा siw_sge *siw_sge,
				पूर्णांक num_sge)
अणु
	जबतक (num_sge--) अणु
		siw_sge->laddr = sge->addr;
		siw_sge->length = sge->length;
		siw_sge->lkey = sge->lkey;

		siw_sge++;
		sge++;
	पूर्ण
पूर्ण

पूर्णांक siw_alloc_ucontext(काष्ठा ib_ucontext *base_ctx, काष्ठा ib_udata *udata);
व्योम siw_dealloc_ucontext(काष्ठा ib_ucontext *base_ctx);
पूर्णांक siw_query_port(काष्ठा ib_device *base_dev, u32 port,
		   काष्ठा ib_port_attr *attr);
पूर्णांक siw_get_port_immutable(काष्ठा ib_device *base_dev, u32 port,
			   काष्ठा ib_port_immutable *port_immutable);
पूर्णांक siw_query_device(काष्ठा ib_device *base_dev, काष्ठा ib_device_attr *attr,
		     काष्ठा ib_udata *udata);
पूर्णांक siw_create_cq(काष्ठा ib_cq *base_cq, स्थिर काष्ठा ib_cq_init_attr *attr,
		  काष्ठा ib_udata *udata);
पूर्णांक siw_query_port(काष्ठा ib_device *base_dev, u32 port,
		   काष्ठा ib_port_attr *attr);
पूर्णांक siw_query_gid(काष्ठा ib_device *base_dev, u32 port, पूर्णांक idx,
		  जोड़ ib_gid *gid);
पूर्णांक siw_alloc_pd(काष्ठा ib_pd *base_pd, काष्ठा ib_udata *udata);
पूर्णांक siw_dealloc_pd(काष्ठा ib_pd *base_pd, काष्ठा ib_udata *udata);
काष्ठा ib_qp *siw_create_qp(काष्ठा ib_pd *base_pd,
			    काष्ठा ib_qp_init_attr *attr,
			    काष्ठा ib_udata *udata);
पूर्णांक siw_query_qp(काष्ठा ib_qp *base_qp, काष्ठा ib_qp_attr *qp_attr,
		 पूर्णांक qp_attr_mask, काष्ठा ib_qp_init_attr *qp_init_attr);
पूर्णांक siw_verbs_modअगरy_qp(काष्ठा ib_qp *base_qp, काष्ठा ib_qp_attr *attr,
			पूर्णांक attr_mask, काष्ठा ib_udata *udata);
पूर्णांक siw_destroy_qp(काष्ठा ib_qp *base_qp, काष्ठा ib_udata *udata);
पूर्णांक siw_post_send(काष्ठा ib_qp *base_qp, स्थिर काष्ठा ib_send_wr *wr,
		  स्थिर काष्ठा ib_send_wr **bad_wr);
पूर्णांक siw_post_receive(काष्ठा ib_qp *base_qp, स्थिर काष्ठा ib_recv_wr *wr,
		     स्थिर काष्ठा ib_recv_wr **bad_wr);
पूर्णांक siw_destroy_cq(काष्ठा ib_cq *base_cq, काष्ठा ib_udata *udata);
पूर्णांक siw_poll_cq(काष्ठा ib_cq *base_cq, पूर्णांक num_entries, काष्ठा ib_wc *wc);
पूर्णांक siw_req_notअगरy_cq(काष्ठा ib_cq *base_cq, क्रमागत ib_cq_notअगरy_flags flags);
काष्ठा ib_mr *siw_reg_user_mr(काष्ठा ib_pd *base_pd, u64 start, u64 len,
			      u64 rnic_va, पूर्णांक rights, काष्ठा ib_udata *udata);
काष्ठा ib_mr *siw_alloc_mr(काष्ठा ib_pd *base_pd, क्रमागत ib_mr_type mr_type,
			   u32 max_sge);
काष्ठा ib_mr *siw_get_dma_mr(काष्ठा ib_pd *base_pd, पूर्णांक rights);
पूर्णांक siw_map_mr_sg(काष्ठा ib_mr *base_mr, काष्ठा scatterlist *sl, पूर्णांक num_sle,
		  अचिन्हित पूर्णांक *sg_off);
पूर्णांक siw_dereg_mr(काष्ठा ib_mr *base_mr, काष्ठा ib_udata *udata);
पूर्णांक siw_create_srq(काष्ठा ib_srq *base_srq, काष्ठा ib_srq_init_attr *attr,
		   काष्ठा ib_udata *udata);
पूर्णांक siw_modअगरy_srq(काष्ठा ib_srq *base_srq, काष्ठा ib_srq_attr *attr,
		   क्रमागत ib_srq_attr_mask mask, काष्ठा ib_udata *udata);
पूर्णांक siw_query_srq(काष्ठा ib_srq *base_srq, काष्ठा ib_srq_attr *attr);
पूर्णांक siw_destroy_srq(काष्ठा ib_srq *base_srq, काष्ठा ib_udata *udata);
पूर्णांक siw_post_srq_recv(काष्ठा ib_srq *base_srq, स्थिर काष्ठा ib_recv_wr *wr,
		      स्थिर काष्ठा ib_recv_wr **bad_wr);
पूर्णांक siw_mmap(काष्ठा ib_ucontext *ctx, काष्ठा vm_area_काष्ठा *vma);
व्योम siw_mmap_मुक्त(काष्ठा rdma_user_mmap_entry *rdma_entry);
व्योम siw_qp_event(काष्ठा siw_qp *qp, क्रमागत ib_event_type type);
व्योम siw_cq_event(काष्ठा siw_cq *cq, क्रमागत ib_event_type type);
व्योम siw_srq_event(काष्ठा siw_srq *srq, क्रमागत ib_event_type type);
व्योम siw_port_event(काष्ठा siw_device *dev, u32 port, क्रमागत ib_event_type type);

#पूर्ण_अगर
