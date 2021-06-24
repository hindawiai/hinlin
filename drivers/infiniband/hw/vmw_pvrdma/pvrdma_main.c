<शैली गुरु>
/*
 * Copyright (c) 2012-2016 VMware, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of EITHER the GNU General Public License
 * version 2 as published by the Free Software Foundation or the BSD
 * 2-Clause License. This program is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License version 2 क्रम more details at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.hपंचांगl.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program available in the file COPYING in the मुख्य
 * directory of this source tree.
 *
 * The BSD 2-Clause License
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/inetdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <net/addrconf.h>

#समावेश "pvrdma.h"

#घोषणा DRV_NAME	"vmw_pvrdma"
#घोषणा DRV_VERSION	"1.0.1.0-k"

अटल DEFINE_MUTEX(pvrdma_device_list_lock);
अटल LIST_HEAD(pvrdma_device_list);
अटल काष्ठा workqueue_काष्ठा *event_wq;

अटल पूर्णांक pvrdma_add_gid(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context);
अटल पूर्णांक pvrdma_del_gid(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context);

अटल sमाप_प्रकार hca_type_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "VMW_PVRDMA-%s\n", DRV_VERSION);
पूर्ण
अटल DEVICE_ATTR_RO(hca_type);

अटल sमाप_प्रकार hw_rev_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", PVRDMA_REV_ID);
पूर्ण
अटल DEVICE_ATTR_RO(hw_rev);

अटल sमाप_प्रकार board_id_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", PVRDMA_BOARD_ID);
पूर्ण
अटल DEVICE_ATTR_RO(board_id);

अटल काष्ठा attribute *pvrdma_class_attributes[] = अणु
	&dev_attr_hw_rev.attr,
	&dev_attr_hca_type.attr,
	&dev_attr_board_id.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pvrdma_attr_group = अणु
	.attrs = pvrdma_class_attributes,
पूर्ण;

अटल व्योम pvrdma_get_fw_ver_str(काष्ठा ib_device *device, अक्षर *str)
अणु
	काष्ठा pvrdma_dev *dev =
		container_of(device, काष्ठा pvrdma_dev, ib_dev);
	snम_लिखो(str, IB_FW_VERSION_NAME_MAX, "%d.%d.%d\n",
		 (पूर्णांक) (dev->dsr->caps.fw_ver >> 32),
		 (पूर्णांक) (dev->dsr->caps.fw_ver >> 16) & 0xffff,
		 (पूर्णांक) dev->dsr->caps.fw_ver & 0xffff);
पूर्ण

अटल पूर्णांक pvrdma_init_device(काष्ठा pvrdma_dev *dev)
अणु
	/*  Initialize some device related stuff */
	spin_lock_init(&dev->cmd_lock);
	sema_init(&dev->cmd_sema, 1);
	atomic_set(&dev->num_qps, 0);
	atomic_set(&dev->num_srqs, 0);
	atomic_set(&dev->num_cqs, 0);
	atomic_set(&dev->num_pds, 0);
	atomic_set(&dev->num_ahs, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक pvrdma_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
				 काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(ibdev);
	काष्ठा ib_port_attr attr;
	पूर्णांक err;

	अगर (dev->dsr->caps.gid_types == PVRDMA_GID_TYPE_FLAG_ROCE_V1)
		immutable->core_cap_flags |= RDMA_CORE_PORT_IBA_ROCE;
	अन्यथा अगर (dev->dsr->caps.gid_types == PVRDMA_GID_TYPE_FLAG_ROCE_V2)
		immutable->core_cap_flags |= RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP;

	err = ib_query_port(ibdev, port_num, &attr);
	अगर (err)
		वापस err;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;
	immutable->max_mad_size = IB_MGMT_MAD_SIZE;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ib_device_ops pvrdma_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_VMW_PVRDMA,
	.uverbs_abi_ver = PVRDMA_UVERBS_ABI_VERSION,

	.add_gid = pvrdma_add_gid,
	.alloc_mr = pvrdma_alloc_mr,
	.alloc_pd = pvrdma_alloc_pd,
	.alloc_ucontext = pvrdma_alloc_ucontext,
	.create_ah = pvrdma_create_ah,
	.create_cq = pvrdma_create_cq,
	.create_qp = pvrdma_create_qp,
	.dealloc_pd = pvrdma_dealloc_pd,
	.dealloc_ucontext = pvrdma_dealloc_ucontext,
	.del_gid = pvrdma_del_gid,
	.dereg_mr = pvrdma_dereg_mr,
	.destroy_ah = pvrdma_destroy_ah,
	.destroy_cq = pvrdma_destroy_cq,
	.destroy_qp = pvrdma_destroy_qp,
	.get_dev_fw_str = pvrdma_get_fw_ver_str,
	.get_dma_mr = pvrdma_get_dma_mr,
	.get_link_layer = pvrdma_port_link_layer,
	.get_port_immutable = pvrdma_port_immutable,
	.map_mr_sg = pvrdma_map_mr_sg,
	.mmap = pvrdma_mmap,
	.modअगरy_port = pvrdma_modअगरy_port,
	.modअगरy_qp = pvrdma_modअगरy_qp,
	.poll_cq = pvrdma_poll_cq,
	.post_recv = pvrdma_post_recv,
	.post_send = pvrdma_post_send,
	.query_device = pvrdma_query_device,
	.query_gid = pvrdma_query_gid,
	.query_pkey = pvrdma_query_pkey,
	.query_port = pvrdma_query_port,
	.query_qp = pvrdma_query_qp,
	.reg_user_mr = pvrdma_reg_user_mr,
	.req_notअगरy_cq = pvrdma_req_notअगरy_cq,

	INIT_RDMA_OBJ_SIZE(ib_ah, pvrdma_ah, ibah),
	INIT_RDMA_OBJ_SIZE(ib_cq, pvrdma_cq, ibcq),
	INIT_RDMA_OBJ_SIZE(ib_pd, pvrdma_pd, ibpd),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, pvrdma_ucontext, ibucontext),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops pvrdma_dev_srq_ops = अणु
	.create_srq = pvrdma_create_srq,
	.destroy_srq = pvrdma_destroy_srq,
	.modअगरy_srq = pvrdma_modअगरy_srq,
	.query_srq = pvrdma_query_srq,

	INIT_RDMA_OBJ_SIZE(ib_srq, pvrdma_srq, ibsrq),
पूर्ण;

अटल पूर्णांक pvrdma_रेजिस्टर_device(काष्ठा pvrdma_dev *dev)
अणु
	पूर्णांक ret = -1;

	dev->ib_dev.node_guid = dev->dsr->caps.node_guid;
	dev->sys_image_guid = dev->dsr->caps.sys_image_guid;
	dev->flags = 0;
	dev->ib_dev.num_comp_vectors = 1;
	dev->ib_dev.dev.parent = &dev->pdev->dev;

	dev->ib_dev.node_type = RDMA_NODE_IB_CA;
	dev->ib_dev.phys_port_cnt = dev->dsr->caps.phys_port_cnt;

	ib_set_device_ops(&dev->ib_dev, &pvrdma_dev_ops);

	mutex_init(&dev->port_mutex);
	spin_lock_init(&dev->desc_lock);

	dev->cq_tbl = kसुस्मृति(dev->dsr->caps.max_cq, माप(काष्ठा pvrdma_cq *),
			      GFP_KERNEL);
	अगर (!dev->cq_tbl)
		वापस ret;
	spin_lock_init(&dev->cq_tbl_lock);

	dev->qp_tbl = kसुस्मृति(dev->dsr->caps.max_qp, माप(काष्ठा pvrdma_qp *),
			      GFP_KERNEL);
	अगर (!dev->qp_tbl)
		जाओ err_cq_मुक्त;
	spin_lock_init(&dev->qp_tbl_lock);

	/* Check अगर SRQ is supported by backend */
	अगर (dev->dsr->caps.max_srq) अणु
		ib_set_device_ops(&dev->ib_dev, &pvrdma_dev_srq_ops);

		dev->srq_tbl = kसुस्मृति(dev->dsr->caps.max_srq,
				       माप(काष्ठा pvrdma_srq *),
				       GFP_KERNEL);
		अगर (!dev->srq_tbl)
			जाओ err_qp_मुक्त;
	पूर्ण
	ret = ib_device_set_netdev(&dev->ib_dev, dev->netdev, 1);
	अगर (ret)
		जाओ err_srq_मुक्त;
	spin_lock_init(&dev->srq_tbl_lock);
	rdma_set_device_sysfs_group(&dev->ib_dev, &pvrdma_attr_group);

	ret = ib_रेजिस्टर_device(&dev->ib_dev, "vmw_pvrdma%d", &dev->pdev->dev);
	अगर (ret)
		जाओ err_srq_मुक्त;

	dev->ib_active = true;

	वापस 0;

err_srq_मुक्त:
	kमुक्त(dev->srq_tbl);
err_qp_मुक्त:
	kमुक्त(dev->qp_tbl);
err_cq_मुक्त:
	kमुक्त(dev->cq_tbl);

	वापस ret;
पूर्ण

अटल irqवापस_t pvrdma_पूर्णांकr0_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 icr = PVRDMA_INTR_CAUSE_RESPONSE;
	काष्ठा pvrdma_dev *dev = dev_id;

	dev_dbg(&dev->pdev->dev, "interrupt 0 (response) handler\n");

	अगर (!dev->pdev->msix_enabled) अणु
		/* Legacy पूर्णांकr */
		icr = pvrdma_पढ़ो_reg(dev, PVRDMA_REG_ICR);
		अगर (icr == 0)
			वापस IRQ_NONE;
	पूर्ण

	अगर (icr == PVRDMA_INTR_CAUSE_RESPONSE)
		complete(&dev->cmd_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pvrdma_qp_event(काष्ठा pvrdma_dev *dev, u32 qpn, पूर्णांक type)
अणु
	काष्ठा pvrdma_qp *qp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->qp_tbl_lock, flags);
	qp = dev->qp_tbl[qpn % dev->dsr->caps.max_qp];
	अगर (qp)
		refcount_inc(&qp->refcnt);
	spin_unlock_irqrestore(&dev->qp_tbl_lock, flags);

	अगर (qp && qp->ibqp.event_handler) अणु
		काष्ठा ib_qp *ibqp = &qp->ibqp;
		काष्ठा ib_event e;

		e.device = ibqp->device;
		e.element.qp = ibqp;
		e.event = type; /* 1:1 mapping क्रम now. */
		ibqp->event_handler(&e, ibqp->qp_context);
	पूर्ण
	अगर (qp) अणु
		अगर (refcount_dec_and_test(&qp->refcnt))
			complete(&qp->मुक्त);
	पूर्ण
पूर्ण

अटल व्योम pvrdma_cq_event(काष्ठा pvrdma_dev *dev, u32 cqn, पूर्णांक type)
अणु
	काष्ठा pvrdma_cq *cq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->cq_tbl_lock, flags);
	cq = dev->cq_tbl[cqn % dev->dsr->caps.max_cq];
	अगर (cq)
		refcount_inc(&cq->refcnt);
	spin_unlock_irqrestore(&dev->cq_tbl_lock, flags);

	अगर (cq && cq->ibcq.event_handler) अणु
		काष्ठा ib_cq *ibcq = &cq->ibcq;
		काष्ठा ib_event e;

		e.device = ibcq->device;
		e.element.cq = ibcq;
		e.event = type; /* 1:1 mapping क्रम now. */
		ibcq->event_handler(&e, ibcq->cq_context);
	पूर्ण
	अगर (cq) अणु
		अगर (refcount_dec_and_test(&cq->refcnt))
			complete(&cq->मुक्त);
	पूर्ण
पूर्ण

अटल व्योम pvrdma_srq_event(काष्ठा pvrdma_dev *dev, u32 srqn, पूर्णांक type)
अणु
	काष्ठा pvrdma_srq *srq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->srq_tbl_lock, flags);
	अगर (dev->srq_tbl)
		srq = dev->srq_tbl[srqn % dev->dsr->caps.max_srq];
	अन्यथा
		srq = शून्य;
	अगर (srq)
		refcount_inc(&srq->refcnt);
	spin_unlock_irqrestore(&dev->srq_tbl_lock, flags);

	अगर (srq && srq->ibsrq.event_handler) अणु
		काष्ठा ib_srq *ibsrq = &srq->ibsrq;
		काष्ठा ib_event e;

		e.device = ibsrq->device;
		e.element.srq = ibsrq;
		e.event = type; /* 1:1 mapping क्रम now. */
		ibsrq->event_handler(&e, ibsrq->srq_context);
	पूर्ण
	अगर (srq) अणु
		अगर (refcount_dec_and_test(&srq->refcnt))
			complete(&srq->मुक्त);
	पूर्ण
पूर्ण

अटल व्योम pvrdma_dispatch_event(काष्ठा pvrdma_dev *dev, पूर्णांक port,
				  क्रमागत ib_event_type event)
अणु
	काष्ठा ib_event ib_event;

	स_रखो(&ib_event, 0, माप(ib_event));
	ib_event.device = &dev->ib_dev;
	ib_event.element.port_num = port;
	ib_event.event = event;
	ib_dispatch_event(&ib_event);
पूर्ण

अटल व्योम pvrdma_dev_event(काष्ठा pvrdma_dev *dev, u8 port, पूर्णांक type)
अणु
	अगर (port < 1 || port > dev->dsr->caps.phys_port_cnt) अणु
		dev_warn(&dev->pdev->dev, "event on port %d\n", port);
		वापस;
	पूर्ण

	pvrdma_dispatch_event(dev, port, type);
पूर्ण

अटल अंतरभूत काष्ठा pvrdma_eqe *get_eqe(काष्ठा pvrdma_dev *dev, अचिन्हित पूर्णांक i)
अणु
	वापस (काष्ठा pvrdma_eqe *)pvrdma_page_dir_get_ptr(
					&dev->async_pdir,
					PAGE_SIZE +
					माप(काष्ठा pvrdma_eqe) * i);
पूर्ण

अटल irqवापस_t pvrdma_पूर्णांकr1_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pvrdma_dev *dev = dev_id;
	काष्ठा pvrdma_ring *ring = &dev->async_ring_state->rx;
	पूर्णांक ring_slots = (dev->dsr->async_ring_pages.num_pages - 1) *
			 PAGE_SIZE / माप(काष्ठा pvrdma_eqe);
	अचिन्हित पूर्णांक head;

	dev_dbg(&dev->pdev->dev, "interrupt 1 (async event) handler\n");

	/*
	 * Don't process events until the IB device is रेजिस्टरed. Otherwise
	 * we'll try to ib_dispatch_event() on an invalid device.
	 */
	अगर (!dev->ib_active)
		वापस IRQ_HANDLED;

	जबतक (pvrdma_idx_ring_has_data(ring, ring_slots, &head) > 0) अणु
		काष्ठा pvrdma_eqe *eqe;

		eqe = get_eqe(dev, head);

		चयन (eqe->type) अणु
		हाल PVRDMA_EVENT_QP_FATAL:
		हाल PVRDMA_EVENT_QP_REQ_ERR:
		हाल PVRDMA_EVENT_QP_ACCESS_ERR:
		हाल PVRDMA_EVENT_COMM_EST:
		हाल PVRDMA_EVENT_SQ_DRAINED:
		हाल PVRDMA_EVENT_PATH_MIG:
		हाल PVRDMA_EVENT_PATH_MIG_ERR:
		हाल PVRDMA_EVENT_QP_LAST_WQE_REACHED:
			pvrdma_qp_event(dev, eqe->info, eqe->type);
			अवरोध;

		हाल PVRDMA_EVENT_CQ_ERR:
			pvrdma_cq_event(dev, eqe->info, eqe->type);
			अवरोध;

		हाल PVRDMA_EVENT_SRQ_ERR:
		हाल PVRDMA_EVENT_SRQ_LIMIT_REACHED:
			pvrdma_srq_event(dev, eqe->info, eqe->type);
			अवरोध;

		हाल PVRDMA_EVENT_PORT_ACTIVE:
		हाल PVRDMA_EVENT_PORT_ERR:
		हाल PVRDMA_EVENT_LID_CHANGE:
		हाल PVRDMA_EVENT_PKEY_CHANGE:
		हाल PVRDMA_EVENT_SM_CHANGE:
		हाल PVRDMA_EVENT_CLIENT_REREGISTER:
		हाल PVRDMA_EVENT_GID_CHANGE:
			pvrdma_dev_event(dev, eqe->info, eqe->type);
			अवरोध;

		हाल PVRDMA_EVENT_DEVICE_FATAL:
			pvrdma_dev_event(dev, 1, eqe->type);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		pvrdma_idx_ring_inc(&ring->cons_head, ring_slots);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत काष्ठा pvrdma_cqne *get_cqne(काष्ठा pvrdma_dev *dev,
					   अचिन्हित पूर्णांक i)
अणु
	वापस (काष्ठा pvrdma_cqne *)pvrdma_page_dir_get_ptr(
					&dev->cq_pdir,
					PAGE_SIZE +
					माप(काष्ठा pvrdma_cqne) * i);
पूर्ण

अटल irqवापस_t pvrdma_पूर्णांकrx_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pvrdma_dev *dev = dev_id;
	काष्ठा pvrdma_ring *ring = &dev->cq_ring_state->rx;
	पूर्णांक ring_slots = (dev->dsr->cq_ring_pages.num_pages - 1) * PAGE_SIZE /
			 माप(काष्ठा pvrdma_cqne);
	अचिन्हित पूर्णांक head;

	dev_dbg(&dev->pdev->dev, "interrupt x (completion) handler\n");

	जबतक (pvrdma_idx_ring_has_data(ring, ring_slots, &head) > 0) अणु
		काष्ठा pvrdma_cqne *cqne;
		काष्ठा pvrdma_cq *cq;

		cqne = get_cqne(dev, head);
		spin_lock(&dev->cq_tbl_lock);
		cq = dev->cq_tbl[cqne->info % dev->dsr->caps.max_cq];
		अगर (cq)
			refcount_inc(&cq->refcnt);
		spin_unlock(&dev->cq_tbl_lock);

		अगर (cq && cq->ibcq.comp_handler)
			cq->ibcq.comp_handler(&cq->ibcq, cq->ibcq.cq_context);
		अगर (cq) अणु
			अगर (refcount_dec_and_test(&cq->refcnt))
				complete(&cq->मुक्त);
		पूर्ण
		pvrdma_idx_ring_inc(&ring->cons_head, ring_slots);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pvrdma_मुक्त_irq(काष्ठा pvrdma_dev *dev)
अणु
	पूर्णांक i;

	dev_dbg(&dev->pdev->dev, "freeing interrupts\n");
	क्रम (i = 0; i < dev->nr_vectors; i++)
		मुक्त_irq(pci_irq_vector(dev->pdev, i), dev);
पूर्ण

अटल व्योम pvrdma_enable_पूर्णांकrs(काष्ठा pvrdma_dev *dev)
अणु
	dev_dbg(&dev->pdev->dev, "enable interrupts\n");
	pvrdma_ग_लिखो_reg(dev, PVRDMA_REG_IMR, 0);
पूर्ण

अटल व्योम pvrdma_disable_पूर्णांकrs(काष्ठा pvrdma_dev *dev)
अणु
	dev_dbg(&dev->pdev->dev, "disable interrupts\n");
	pvrdma_ग_लिखो_reg(dev, PVRDMA_REG_IMR, ~0);
पूर्ण

अटल पूर्णांक pvrdma_alloc_पूर्णांकrs(काष्ठा pvrdma_dev *dev)
अणु
	काष्ठा pci_dev *pdev = dev->pdev;
	पूर्णांक ret = 0, i;

	ret = pci_alloc_irq_vectors(pdev, 1, PVRDMA_MAX_INTERRUPTS,
			PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		ret = pci_alloc_irq_vectors(pdev, 1, 1,
				PCI_IRQ_MSI | PCI_IRQ_LEGACY);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	dev->nr_vectors = ret;

	ret = request_irq(pci_irq_vector(dev->pdev, 0), pvrdma_पूर्णांकr0_handler,
			pdev->msix_enabled ? 0 : IRQF_SHARED, DRV_NAME, dev);
	अगर (ret) अणु
		dev_err(&dev->pdev->dev,
			"failed to request interrupt 0\n");
		जाओ out_मुक्त_vectors;
	पूर्ण

	क्रम (i = 1; i < dev->nr_vectors; i++) अणु
		ret = request_irq(pci_irq_vector(dev->pdev, i),
				i == 1 ? pvrdma_पूर्णांकr1_handler :
					 pvrdma_पूर्णांकrx_handler,
				0, DRV_NAME, dev);
		अगर (ret) अणु
			dev_err(&dev->pdev->dev,
				"failed to request interrupt %d\n", i);
			जाओ मुक्त_irqs;
		पूर्ण
	पूर्ण

	वापस 0;

मुक्त_irqs:
	जबतक (--i >= 0)
		मुक्त_irq(pci_irq_vector(dev->pdev, i), dev);
out_मुक्त_vectors:
	pci_मुक्त_irq_vectors(pdev);
	वापस ret;
पूर्ण

अटल व्योम pvrdma_मुक्त_slots(काष्ठा pvrdma_dev *dev)
अणु
	काष्ठा pci_dev *pdev = dev->pdev;

	अगर (dev->resp_slot)
		dma_मुक्त_coherent(&pdev->dev, PAGE_SIZE, dev->resp_slot,
				  dev->dsr->resp_slot_dma);
	अगर (dev->cmd_slot)
		dma_मुक्त_coherent(&pdev->dev, PAGE_SIZE, dev->cmd_slot,
				  dev->dsr->cmd_slot_dma);
पूर्ण

अटल पूर्णांक pvrdma_add_gid_at_index(काष्ठा pvrdma_dev *dev,
				   स्थिर जोड़ ib_gid *gid,
				   u8 gid_type,
				   पूर्णांक index)
अणु
	पूर्णांक ret;
	जोड़ pvrdma_cmd_req req;
	काष्ठा pvrdma_cmd_create_bind *cmd_bind = &req.create_bind;

	अगर (!dev->sgid_tbl) अणु
		dev_warn(&dev->pdev->dev, "sgid table not initialized\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(cmd_bind, 0, माप(*cmd_bind));
	cmd_bind->hdr.cmd = PVRDMA_CMD_CREATE_BIND;
	स_नकल(cmd_bind->new_gid, gid->raw, 16);
	cmd_bind->mtu = ib_mtu_क्रमागत_to_पूर्णांक(IB_MTU_1024);
	cmd_bind->vlan = 0xfff;
	cmd_bind->index = index;
	cmd_bind->gid_type = gid_type;

	ret = pvrdma_cmd_post(dev, &req, शून्य, 0);
	अगर (ret < 0) अणु
		dev_warn(&dev->pdev->dev,
			 "could not create binding, error: %d\n", ret);
		वापस -EFAULT;
	पूर्ण
	स_नकल(&dev->sgid_tbl[index], gid, माप(*gid));
	वापस 0;
पूर्ण

अटल पूर्णांक pvrdma_add_gid(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(attr->device);

	वापस pvrdma_add_gid_at_index(dev, &attr->gid,
				       ib_gid_type_to_pvrdma(attr->gid_type),
				       attr->index);
पूर्ण

अटल पूर्णांक pvrdma_del_gid_at_index(काष्ठा pvrdma_dev *dev, पूर्णांक index)
अणु
	पूर्णांक ret;
	जोड़ pvrdma_cmd_req req;
	काष्ठा pvrdma_cmd_destroy_bind *cmd_dest = &req.destroy_bind;

	/* Update sgid table. */
	अगर (!dev->sgid_tbl) अणु
		dev_warn(&dev->pdev->dev, "sgid table not initialized\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(cmd_dest, 0, माप(*cmd_dest));
	cmd_dest->hdr.cmd = PVRDMA_CMD_DESTROY_BIND;
	स_नकल(cmd_dest->dest_gid, &dev->sgid_tbl[index], 16);
	cmd_dest->index = index;

	ret = pvrdma_cmd_post(dev, &req, शून्य, 0);
	अगर (ret < 0) अणु
		dev_warn(&dev->pdev->dev,
			 "could not destroy binding, error: %d\n", ret);
		वापस ret;
	पूर्ण
	स_रखो(&dev->sgid_tbl[index], 0, 16);
	वापस 0;
पूर्ण

अटल पूर्णांक pvrdma_del_gid(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(attr->device);

	dev_dbg(&dev->pdev->dev, "removing gid at index %u from %s",
		attr->index, dev->netdev->name);

	वापस pvrdma_del_gid_at_index(dev, attr->index);
पूर्ण

अटल व्योम pvrdma_netdevice_event_handle(काष्ठा pvrdma_dev *dev,
					  काष्ठा net_device *ndev,
					  अचिन्हित दीर्घ event)
अणु
	काष्ठा pci_dev *pdev_net;
	अचिन्हित पूर्णांक slot;

	चयन (event) अणु
	हाल NETDEV_REBOOT:
	हाल NETDEV_DOWN:
		pvrdma_dispatch_event(dev, 1, IB_EVENT_PORT_ERR);
		अवरोध;
	हाल NETDEV_UP:
		pvrdma_ग_लिखो_reg(dev, PVRDMA_REG_CTL,
				 PVRDMA_DEVICE_CTL_UNQUIESCE);

		mb();

		अगर (pvrdma_पढ़ो_reg(dev, PVRDMA_REG_ERR))
			dev_err(&dev->pdev->dev,
				"failed to activate device during link up\n");
		अन्यथा
			pvrdma_dispatch_event(dev, 1, IB_EVENT_PORT_ACTIVE);
		अवरोध;
	हाल NETDEV_UNREGISTER:
		ib_device_set_netdev(&dev->ib_dev, शून्य, 1);
		dev_put(dev->netdev);
		dev->netdev = शून्य;
		अवरोध;
	हाल NETDEV_REGISTER:
		/* vmxnet3 will have same bus, slot. But func will be 0 */
		slot = PCI_SLOT(dev->pdev->devfn);
		pdev_net = pci_get_slot(dev->pdev->bus,
					PCI_DEVFN(slot, 0));
		अगर ((dev->netdev == शून्य) &&
		    (pci_get_drvdata(pdev_net) == ndev)) अणु
			/* this is our netdev */
			ib_device_set_netdev(&dev->ib_dev, ndev, 1);
			dev->netdev = ndev;
			dev_hold(ndev);
		पूर्ण
		pci_dev_put(pdev_net);
		अवरोध;

	शेष:
		dev_dbg(&dev->pdev->dev, "ignore netdevice event %ld on %s\n",
			event, dev_name(&dev->ib_dev.dev));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pvrdma_netdevice_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pvrdma_netdevice_work *netdev_work;
	काष्ठा pvrdma_dev *dev;

	netdev_work = container_of(work, काष्ठा pvrdma_netdevice_work, work);

	mutex_lock(&pvrdma_device_list_lock);
	list_क्रम_each_entry(dev, &pvrdma_device_list, device_link) अणु
		अगर ((netdev_work->event == NETDEV_REGISTER) ||
		    (dev->netdev == netdev_work->event_netdev)) अणु
			pvrdma_netdevice_event_handle(dev,
						      netdev_work->event_netdev,
						      netdev_work->event);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&pvrdma_device_list_lock);

	kमुक्त(netdev_work);
पूर्ण

अटल पूर्णांक pvrdma_netdevice_event(काष्ठा notअगरier_block *this,
				  अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *event_netdev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा pvrdma_netdevice_work *netdev_work;

	netdev_work = kदो_स्मृति(माप(*netdev_work), GFP_ATOMIC);
	अगर (!netdev_work)
		वापस NOTIFY_BAD;

	INIT_WORK(&netdev_work->work, pvrdma_netdevice_event_work);
	netdev_work->event_netdev = event_netdev;
	netdev_work->event = event;
	queue_work(event_wq, &netdev_work->work);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक pvrdma_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pci_dev *pdev_net;
	काष्ठा pvrdma_dev *dev;
	पूर्णांक ret;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ len;
	dma_addr_t slot_dma = 0;

	dev_dbg(&pdev->dev, "initializing driver %s\n", pci_name(pdev));

	/* Allocate zero-out device */
	dev = ib_alloc_device(pvrdma_dev, ib_dev);
	अगर (!dev) अणु
		dev_err(&pdev->dev, "failed to allocate IB device\n");
		वापस -ENOMEM;
	पूर्ण

	mutex_lock(&pvrdma_device_list_lock);
	list_add(&dev->device_link, &pvrdma_device_list);
	mutex_unlock(&pvrdma_device_list_lock);

	ret = pvrdma_init_device(dev);
	अगर (ret)
		जाओ err_मुक्त_device;

	dev->pdev = pdev;
	pci_set_drvdata(pdev, dev);

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		जाओ err_मुक्त_device;
	पूर्ण

	dev_dbg(&pdev->dev, "PCI resource flags BAR0 %#lx\n",
		pci_resource_flags(pdev, 0));
	dev_dbg(&pdev->dev, "PCI resource len %#llx\n",
		(अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, 0));
	dev_dbg(&pdev->dev, "PCI resource start %#llx\n",
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 0));
	dev_dbg(&pdev->dev, "PCI resource flags BAR1 %#lx\n",
		pci_resource_flags(pdev, 1));
	dev_dbg(&pdev->dev, "PCI resource len %#llx\n",
		(अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, 1));
	dev_dbg(&pdev->dev, "PCI resource start %#llx\n",
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 1));

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM) ||
	    !(pci_resource_flags(pdev, 1) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev, "PCI BAR region not MMIO\n");
		ret = -ENOMEM;
		जाओ err_disable_pdev;
	पूर्ण

	ret = pci_request_regions(pdev, DRV_NAME);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot request PCI resources\n");
		जाओ err_disable_pdev;
	पूर्ण

	/* Enable 64-Bit DMA */
	अगर (pci_set_dma_mask(pdev, DMA_BIT_MASK(64)) == 0) अणु
		ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
		अगर (ret != 0) अणु
			dev_err(&pdev->dev,
				"pci_set_consistent_dma_mask failed\n");
			जाओ err_मुक्त_resource;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (ret != 0) अणु
			dev_err(&pdev->dev,
				"pci_set_dma_mask failed\n");
			जाओ err_मुक्त_resource;
		पूर्ण
	पूर्ण
	dma_set_max_seg_size(&pdev->dev, अच_पूर्णांक_उच्च);
	pci_set_master(pdev);

	/* Map रेजिस्टर space */
	start = pci_resource_start(dev->pdev, PVRDMA_PCI_RESOURCE_REG);
	len = pci_resource_len(dev->pdev, PVRDMA_PCI_RESOURCE_REG);
	dev->regs = ioremap(start, len);
	अगर (!dev->regs) अणु
		dev_err(&pdev->dev, "register mapping failed\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_resource;
	पूर्ण

	/* Setup per-device UAR. */
	dev->driver_uar.index = 0;
	dev->driver_uar.pfn =
		pci_resource_start(dev->pdev, PVRDMA_PCI_RESOURCE_UAR) >>
		PAGE_SHIFT;
	dev->driver_uar.map =
		ioremap(dev->driver_uar.pfn << PAGE_SHIFT, PAGE_SIZE);
	अगर (!dev->driver_uar.map) अणु
		dev_err(&pdev->dev, "failed to remap UAR pages\n");
		ret = -ENOMEM;
		जाओ err_unmap_regs;
	पूर्ण

	dev->dsr_version = pvrdma_पढ़ो_reg(dev, PVRDMA_REG_VERSION);
	dev_info(&pdev->dev, "device version %d, driver version %d\n",
		 dev->dsr_version, PVRDMA_VERSION);

	dev->dsr = dma_alloc_coherent(&pdev->dev, माप(*dev->dsr),
				      &dev->dsrbase, GFP_KERNEL);
	अगर (!dev->dsr) अणु
		dev_err(&pdev->dev, "failed to allocate shared region\n");
		ret = -ENOMEM;
		जाओ err_uar_unmap;
	पूर्ण

	/* Setup the shared region */
	dev->dsr->driver_version = PVRDMA_VERSION;
	dev->dsr->gos_info.gos_bits = माप(व्योम *) == 4 ?
		PVRDMA_GOS_BITS_32 :
		PVRDMA_GOS_BITS_64;
	dev->dsr->gos_info.gos_type = PVRDMA_GOS_TYPE_LINUX;
	dev->dsr->gos_info.gos_ver = 1;

	अगर (dev->dsr_version < PVRDMA_PPN64_VERSION)
		dev->dsr->uar_pfn = dev->driver_uar.pfn;
	अन्यथा
		dev->dsr->uar_pfn64 = dev->driver_uar.pfn;

	/* Command slot. */
	dev->cmd_slot = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					   &slot_dma, GFP_KERNEL);
	अगर (!dev->cmd_slot) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_dsr;
	पूर्ण

	dev->dsr->cmd_slot_dma = (u64)slot_dma;

	/* Response slot. */
	dev->resp_slot = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					    &slot_dma, GFP_KERNEL);
	अगर (!dev->resp_slot) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_slots;
	पूर्ण

	dev->dsr->resp_slot_dma = (u64)slot_dma;

	/* Async event ring */
	dev->dsr->async_ring_pages.num_pages = PVRDMA_NUM_RING_PAGES;
	ret = pvrdma_page_dir_init(dev, &dev->async_pdir,
				   dev->dsr->async_ring_pages.num_pages, true);
	अगर (ret)
		जाओ err_मुक्त_slots;
	dev->async_ring_state = dev->async_pdir.pages[0];
	dev->dsr->async_ring_pages.pdir_dma = dev->async_pdir.dir_dma;

	/* CQ notअगरication ring */
	dev->dsr->cq_ring_pages.num_pages = PVRDMA_NUM_RING_PAGES;
	ret = pvrdma_page_dir_init(dev, &dev->cq_pdir,
				   dev->dsr->cq_ring_pages.num_pages, true);
	अगर (ret)
		जाओ err_मुक्त_async_ring;
	dev->cq_ring_state = dev->cq_pdir.pages[0];
	dev->dsr->cq_ring_pages.pdir_dma = dev->cq_pdir.dir_dma;

	/*
	 * Write the PA of the shared region to the device. The ग_लिखोs must be
	 * ordered such that the high bits are written last. When the ग_लिखोs
	 * complete, the device will have filled out the capabilities.
	 */

	pvrdma_ग_लिखो_reg(dev, PVRDMA_REG_DSRLOW, (u32)dev->dsrbase);
	pvrdma_ग_लिखो_reg(dev, PVRDMA_REG_DSRHIGH,
			 (u32)((u64)(dev->dsrbase) >> 32));

	/* Make sure the ग_लिखो is complete beक्रमe पढ़ोing status. */
	mb();

	/* The driver supports RoCE V1 and V2. */
	अगर (!PVRDMA_SUPPORTED(dev)) अणु
		dev_err(&pdev->dev, "driver needs RoCE v1 or v2 support\n");
		ret = -EFAULT;
		जाओ err_मुक्त_cq_ring;
	पूर्ण

	/* Paired vmxnet3 will have same bus, slot. But func will be 0 */
	pdev_net = pci_get_slot(pdev->bus, PCI_DEVFN(PCI_SLOT(pdev->devfn), 0));
	अगर (!pdev_net) अणु
		dev_err(&pdev->dev, "failed to find paired net device\n");
		ret = -ENODEV;
		जाओ err_मुक्त_cq_ring;
	पूर्ण

	अगर (pdev_net->venकरोr != PCI_VENDOR_ID_VMWARE ||
	    pdev_net->device != PCI_DEVICE_ID_VMWARE_VMXNET3) अणु
		dev_err(&pdev->dev, "failed to find paired vmxnet3 device\n");
		pci_dev_put(pdev_net);
		ret = -ENODEV;
		जाओ err_मुक्त_cq_ring;
	पूर्ण

	dev->netdev = pci_get_drvdata(pdev_net);
	pci_dev_put(pdev_net);
	अगर (!dev->netdev) अणु
		dev_err(&pdev->dev, "failed to get vmxnet3 device\n");
		ret = -ENODEV;
		जाओ err_मुक्त_cq_ring;
	पूर्ण
	dev_hold(dev->netdev);

	dev_info(&pdev->dev, "paired device to %s\n", dev->netdev->name);

	/* Interrupt setup */
	ret = pvrdma_alloc_पूर्णांकrs(dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to allocate interrupts\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_cq_ring;
	पूर्ण

	/* Allocate UAR table. */
	ret = pvrdma_uar_table_init(dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to allocate UAR table\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_पूर्णांकrs;
	पूर्ण

	/* Allocate GID table */
	dev->sgid_tbl = kसुस्मृति(dev->dsr->caps.gid_tbl_len,
				माप(जोड़ ib_gid), GFP_KERNEL);
	अगर (!dev->sgid_tbl) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_uar_table;
	पूर्ण
	dev_dbg(&pdev->dev, "gid table len %d\n", dev->dsr->caps.gid_tbl_len);

	pvrdma_enable_पूर्णांकrs(dev);

	/* Activate pvrdma device */
	pvrdma_ग_लिखो_reg(dev, PVRDMA_REG_CTL, PVRDMA_DEVICE_CTL_ACTIVATE);

	/* Make sure the ग_लिखो is complete beक्रमe पढ़ोing status. */
	mb();

	/* Check अगर device was successfully activated */
	ret = pvrdma_पढ़ो_reg(dev, PVRDMA_REG_ERR);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "failed to activate device\n");
		ret = -EFAULT;
		जाओ err_disable_पूर्णांकr;
	पूर्ण

	/* Register IB device */
	ret = pvrdma_रेजिस्टर_device(dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register IB device\n");
		जाओ err_disable_पूर्णांकr;
	पूर्ण

	dev->nb_netdev.notअगरier_call = pvrdma_netdevice_event;
	ret = रेजिस्टर_netdevice_notअगरier(&dev->nb_netdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register netdevice events\n");
		जाओ err_unreg_ibdev;
	पूर्ण

	dev_info(&pdev->dev, "attached to device\n");
	वापस 0;

err_unreg_ibdev:
	ib_unरेजिस्टर_device(&dev->ib_dev);
err_disable_पूर्णांकr:
	pvrdma_disable_पूर्णांकrs(dev);
	kमुक्त(dev->sgid_tbl);
err_मुक्त_uar_table:
	pvrdma_uar_table_cleanup(dev);
err_मुक्त_पूर्णांकrs:
	pvrdma_मुक्त_irq(dev);
	pci_मुक्त_irq_vectors(pdev);
err_मुक्त_cq_ring:
	अगर (dev->netdev) अणु
		dev_put(dev->netdev);
		dev->netdev = शून्य;
	पूर्ण
	pvrdma_page_dir_cleanup(dev, &dev->cq_pdir);
err_मुक्त_async_ring:
	pvrdma_page_dir_cleanup(dev, &dev->async_pdir);
err_मुक्त_slots:
	pvrdma_मुक्त_slots(dev);
err_मुक्त_dsr:
	dma_मुक्त_coherent(&pdev->dev, माप(*dev->dsr), dev->dsr,
			  dev->dsrbase);
err_uar_unmap:
	iounmap(dev->driver_uar.map);
err_unmap_regs:
	iounmap(dev->regs);
err_मुक्त_resource:
	pci_release_regions(pdev);
err_disable_pdev:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
err_मुक्त_device:
	mutex_lock(&pvrdma_device_list_lock);
	list_del(&dev->device_link);
	mutex_unlock(&pvrdma_device_list_lock);
	ib_dealloc_device(&dev->ib_dev);
	वापस ret;
पूर्ण

अटल व्योम pvrdma_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pvrdma_dev *dev = pci_get_drvdata(pdev);

	अगर (!dev)
		वापस;

	dev_info(&pdev->dev, "detaching from device\n");

	unरेजिस्टर_netdevice_notअगरier(&dev->nb_netdev);
	dev->nb_netdev.notअगरier_call = शून्य;

	flush_workqueue(event_wq);

	अगर (dev->netdev) अणु
		dev_put(dev->netdev);
		dev->netdev = शून्य;
	पूर्ण

	/* Unरेजिस्टर ib device */
	ib_unरेजिस्टर_device(&dev->ib_dev);

	mutex_lock(&pvrdma_device_list_lock);
	list_del(&dev->device_link);
	mutex_unlock(&pvrdma_device_list_lock);

	pvrdma_disable_पूर्णांकrs(dev);
	pvrdma_मुक्त_irq(dev);
	pci_मुक्त_irq_vectors(pdev);

	/* Deactivate pvrdma device */
	pvrdma_ग_लिखो_reg(dev, PVRDMA_REG_CTL, PVRDMA_DEVICE_CTL_RESET);
	pvrdma_page_dir_cleanup(dev, &dev->cq_pdir);
	pvrdma_page_dir_cleanup(dev, &dev->async_pdir);
	pvrdma_मुक्त_slots(dev);
	dma_मुक्त_coherent(&pdev->dev, माप(*dev->dsr), dev->dsr,
			  dev->dsrbase);

	iounmap(dev->regs);
	kमुक्त(dev->sgid_tbl);
	kमुक्त(dev->cq_tbl);
	kमुक्त(dev->srq_tbl);
	kमुक्त(dev->qp_tbl);
	pvrdma_uar_table_cleanup(dev);
	iounmap(dev->driver_uar.map);

	ib_dealloc_device(&dev->ib_dev);

	/* Free pci resources */
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pvrdma_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_VMWARE, PCI_DEVICE_ID_VMWARE_PVRDMA), पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, pvrdma_pci_table);

अटल काष्ठा pci_driver pvrdma_driver = अणु
	.name		= DRV_NAME,
	.id_table	= pvrdma_pci_table,
	.probe		= pvrdma_pci_probe,
	.हटाओ		= pvrdma_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init pvrdma_init(व्योम)
अणु
	पूर्णांक err;

	event_wq = alloc_ordered_workqueue("pvrdma_event_wq", WQ_MEM_RECLAIM);
	अगर (!event_wq)
		वापस -ENOMEM;

	err = pci_रेजिस्टर_driver(&pvrdma_driver);
	अगर (err)
		destroy_workqueue(event_wq);

	वापस err;
पूर्ण

अटल व्योम __निकास pvrdma_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pvrdma_driver);

	destroy_workqueue(event_wq);
पूर्ण

module_init(pvrdma_init);
module_निकास(pvrdma_cleanup);

MODULE_AUTHOR("VMware, Inc");
MODULE_DESCRIPTION("VMware Paravirtual RDMA driver");
MODULE_LICENSE("Dual BSD/GPL");
