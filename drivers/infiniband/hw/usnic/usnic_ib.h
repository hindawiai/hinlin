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

#अगर_अघोषित USNIC_IB_H_
#घोषणा USNIC_IB_H_

#समावेश <linux/iommu.h>
#समावेश <linux/netdevice.h>

#समावेश <rdma/ib_verbs.h>


#समावेश "usnic.h"
#समावेश "usnic_abi.h"
#समावेश "usnic_vnic.h"

#घोषणा USNIC_IB_PORT_CNT		1
#घोषणा USNIC_IB_NUM_COMP_VECTORS	1

बाह्य अचिन्हित पूर्णांक usnic_ib_share_vf;

काष्ठा usnic_ib_ucontext अणु
	काष्ठा ib_ucontext		ibucontext;
	/* Protected by usnic_ib_dev->usdev_lock */
	काष्ठा list_head		qp_grp_list;
	काष्ठा list_head		link;
पूर्ण;

काष्ठा usnic_ib_pd अणु
	काष्ठा ib_pd			ibpd;
	काष्ठा usnic_uiom_pd		*umem_pd;
पूर्ण;

काष्ठा usnic_ib_cq अणु
	काष्ठा ib_cq			ibcq;
पूर्ण;

काष्ठा usnic_ib_mr अणु
	काष्ठा ib_mr			ibmr;
	काष्ठा usnic_uiom_reg		*umem;
पूर्ण;

काष्ठा usnic_ib_dev अणु
	काष्ठा ib_device		ib_dev;
	काष्ठा pci_dev			*pdev;
	काष्ठा net_device		*netdev;
	काष्ठा usnic_fwd_dev		*ufdev;
	काष्ठा list_head		ib_dev_link;
	काष्ठा list_head		vf_dev_list;
	काष्ठा list_head		ctx_list;
	काष्ठा mutex			usdev_lock;

	/* provisioning inक्रमmation */
	काष्ठा kref			vf_cnt;
	अचिन्हित पूर्णांक			vf_res_cnt[USNIC_VNIC_RES_TYPE_MAX];

	/* sysfs vars क्रम QPN reporting */
	काष्ठा kobject *qpn_kobj;
पूर्ण;

काष्ठा usnic_ib_vf अणु
	काष्ठा usnic_ib_dev		*pf;
	spinlock_t			lock;
	काष्ठा usnic_vnic		*vnic;
	अचिन्हित पूर्णांक			qp_grp_ref_cnt;
	काष्ठा usnic_ib_pd		*pd;
	काष्ठा list_head		link;
पूर्ण;

अटल अंतरभूत
काष्ठा usnic_ib_dev *to_usdev(काष्ठा ib_device *ibdev)
अणु
	वापस container_of(ibdev, काष्ठा usnic_ib_dev, ib_dev);
पूर्ण

अटल अंतरभूत
काष्ठा usnic_ib_ucontext *to_ucontext(काष्ठा ib_ucontext *ibucontext)
अणु
	वापस container_of(ibucontext, काष्ठा usnic_ib_ucontext, ibucontext);
पूर्ण

अटल अंतरभूत
काष्ठा usnic_ib_pd *to_upd(काष्ठा ib_pd *ibpd)
अणु
	वापस container_of(ibpd, काष्ठा usnic_ib_pd, ibpd);
पूर्ण

अटल अंतरभूत
काष्ठा usnic_ib_ucontext *to_uucontext(काष्ठा ib_ucontext *ibucontext)
अणु
	वापस container_of(ibucontext, काष्ठा usnic_ib_ucontext, ibucontext);
पूर्ण

अटल अंतरभूत
काष्ठा usnic_ib_mr *to_umr(काष्ठा ib_mr *ibmr)
अणु
	वापस container_of(ibmr, काष्ठा usnic_ib_mr, ibmr);
पूर्ण
व्योम usnic_ib_log_vf(काष्ठा usnic_ib_vf *vf);

#घोषणा UPDATE_PTR_LEFT(N, P, L)			\
करो अणु							\
	L -= (N);					\
	P += (N);					\
पूर्ण जबतक (0)

#पूर्ण_अगर /* USNIC_IB_H_ */
