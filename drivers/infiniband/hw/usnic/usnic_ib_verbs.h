<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
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
 *
 */

#अगर_अघोषित USNIC_IB_VERBS_H_
#घोषणा USNIC_IB_VERBS_H_

#समावेश "usnic_ib.h"

क्रमागत rdma_link_layer usnic_ib_port_link_layer(काष्ठा ib_device *device,
					      u32 port_num);
पूर्णांक usnic_ib_query_device(काष्ठा ib_device *ibdev,
				काष्ठा ib_device_attr *props,
			  काष्ठा ib_udata *uhw);
पूर्णांक usnic_ib_query_port(काष्ठा ib_device *ibdev, u32 port,
				काष्ठा ib_port_attr *props);
पूर्णांक usnic_ib_query_qp(काष्ठा ib_qp *qp, काष्ठा ib_qp_attr *qp_attr,
				पूर्णांक qp_attr_mask,
				काष्ठा ib_qp_init_attr *qp_init_attr);
पूर्णांक usnic_ib_query_gid(काष्ठा ib_device *ibdev, u32 port, पूर्णांक index,
				जोड़ ib_gid *gid);
पूर्णांक usnic_ib_alloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata);
पूर्णांक usnic_ib_dealloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);
काष्ठा ib_qp *usnic_ib_create_qp(काष्ठा ib_pd *pd,
					काष्ठा ib_qp_init_attr *init_attr,
					काष्ठा ib_udata *udata);
पूर्णांक usnic_ib_destroy_qp(काष्ठा ib_qp *qp, काष्ठा ib_udata *udata);
पूर्णांक usnic_ib_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
				पूर्णांक attr_mask, काष्ठा ib_udata *udata);
पूर्णांक usnic_ib_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		       काष्ठा ib_udata *udata);
पूर्णांक usnic_ib_destroy_cq(काष्ठा ib_cq *cq, काष्ठा ib_udata *udata);
काष्ठा ib_mr *usnic_ib_reg_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
				u64 virt_addr, पूर्णांक access_flags,
				काष्ठा ib_udata *udata);
पूर्णांक usnic_ib_dereg_mr(काष्ठा ib_mr *ibmr, काष्ठा ib_udata *udata);
पूर्णांक usnic_ib_alloc_ucontext(काष्ठा ib_ucontext *uctx, काष्ठा ib_udata *udata);
व्योम usnic_ib_dealloc_ucontext(काष्ठा ib_ucontext *ibcontext);
पूर्णांक usnic_ib_mmap(काष्ठा ib_ucontext *context,
			काष्ठा vm_area_काष्ठा *vma);
#पूर्ण_अगर /* !USNIC_IB_VERBS_H */
