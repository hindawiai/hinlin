<शैली गुरु>
/* QLogic qedr NIC Driver
 * Copyright (c) 2015-2016  QLogic Corporation
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
 *        disclaimer in the करोcumentation and /or other materials
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
#समावेश <linux/module.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/iw_cm.h>
#समावेश <rdma/ib_mad.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/iommu.h>
#समावेश <linux/pci.h>
#समावेश <net/addrconf.h>

#समावेश <linux/qed/qed_chain.h>
#समावेश <linux/qed/qed_अगर.h>
#समावेश "qedr.h"
#समावेश "verbs.h"
#समावेश <rdma/qedr-abi.h>
#समावेश "qedr_iw_cm.h"

MODULE_DESCRIPTION("QLogic 40G/100G ROCE Driver");
MODULE_AUTHOR("QLogic Corporation");
MODULE_LICENSE("Dual BSD/GPL");

#घोषणा QEDR_WQ_MULTIPLIER_DFT	(3)

अटल व्योम qedr_ib_dispatch_event(काष्ठा qedr_dev *dev, u32 port_num,
				   क्रमागत ib_event_type type)
अणु
	काष्ठा ib_event ibev;

	ibev.device = &dev->ibdev;
	ibev.element.port_num = port_num;
	ibev.event = type;

	ib_dispatch_event(&ibev);
पूर्ण

अटल क्रमागत rdma_link_layer qedr_link_layer(काष्ठा ib_device *device,
					    u32 port_num)
अणु
	वापस IB_LINK_LAYER_ETHERNET;
पूर्ण

अटल व्योम qedr_get_dev_fw_str(काष्ठा ib_device *ibdev, अक्षर *str)
अणु
	काष्ठा qedr_dev *qedr = get_qedr_dev(ibdev);
	u32 fw_ver = (u32)qedr->attr.fw_ver;

	snम_लिखो(str, IB_FW_VERSION_NAME_MAX, "%d.%d.%d.%d",
		 (fw_ver >> 24) & 0xFF, (fw_ver >> 16) & 0xFF,
		 (fw_ver >> 8) & 0xFF, fw_ver & 0xFF);
पूर्ण

अटल पूर्णांक qedr_roce_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
				    काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा ib_port_attr attr;
	पूर्णांक err;

	err = qedr_query_port(ibdev, port_num, &attr);
	अगर (err)
		वापस err;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;
	immutable->core_cap_flags = RDMA_CORE_PORT_IBA_ROCE |
	    RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP;
	immutable->max_mad_size = IB_MGMT_MAD_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक qedr_iw_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
				  काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा ib_port_attr attr;
	पूर्णांक err;

	err = qedr_query_port(ibdev, port_num, &attr);
	अगर (err)
		वापस err;

	immutable->gid_tbl_len = 1;
	immutable->core_cap_flags = RDMA_CORE_PORT_IWARP;
	immutable->max_mad_size = 0;

	वापस 0;
पूर्ण

/* QEDR sysfs पूर्णांकerface */
अटल sमाप_प्रकार hw_rev_show(काष्ठा device *device, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा qedr_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा qedr_dev, ibdev);

	वापस sysfs_emit(buf, "0x%x\n", dev->attr.hw_ver);
पूर्ण
अटल DEVICE_ATTR_RO(hw_rev);

अटल sमाप_प्रकार hca_type_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qedr_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा qedr_dev, ibdev);

	वापस sysfs_emit(buf, "FastLinQ QL%x %s\n", dev->pdev->device,
			  rdma_protocol_iwarp(&dev->ibdev, 1) ? "iWARP" :
								"RoCE");
पूर्ण
अटल DEVICE_ATTR_RO(hca_type);

अटल काष्ठा attribute *qedr_attributes[] = अणु
	&dev_attr_hw_rev.attr,
	&dev_attr_hca_type.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group qedr_attr_group = अणु
	.attrs = qedr_attributes,
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops qedr_iw_dev_ops = अणु
	.get_port_immutable = qedr_iw_port_immutable,
	.iw_accept = qedr_iw_accept,
	.iw_add_ref = qedr_iw_qp_add_ref,
	.iw_connect = qedr_iw_connect,
	.iw_create_listen = qedr_iw_create_listen,
	.iw_destroy_listen = qedr_iw_destroy_listen,
	.iw_get_qp = qedr_iw_get_qp,
	.iw_reject = qedr_iw_reject,
	.iw_rem_ref = qedr_iw_qp_rem_ref,
	.query_gid = qedr_iw_query_gid,
पूर्ण;

अटल पूर्णांक qedr_iw_रेजिस्टर_device(काष्ठा qedr_dev *dev)
अणु
	dev->ibdev.node_type = RDMA_NODE_RNIC;

	ib_set_device_ops(&dev->ibdev, &qedr_iw_dev_ops);

	स_नकल(dev->ibdev.iw_अगरname,
	       dev->ndev->name, माप(dev->ibdev.iw_अगरname));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ib_device_ops qedr_roce_dev_ops = अणु
	.alloc_xrcd = qedr_alloc_xrcd,
	.dealloc_xrcd = qedr_dealloc_xrcd,
	.get_port_immutable = qedr_roce_port_immutable,
	.query_pkey = qedr_query_pkey,
पूर्ण;

अटल व्योम qedr_roce_रेजिस्टर_device(काष्ठा qedr_dev *dev)
अणु
	dev->ibdev.node_type = RDMA_NODE_IB_CA;

	ib_set_device_ops(&dev->ibdev, &qedr_roce_dev_ops);
पूर्ण

अटल स्थिर काष्ठा ib_device_ops qedr_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_QEDR,
	.uverbs_abi_ver = QEDR_ABI_VERSION,

	.alloc_mr = qedr_alloc_mr,
	.alloc_pd = qedr_alloc_pd,
	.alloc_ucontext = qedr_alloc_ucontext,
	.create_ah = qedr_create_ah,
	.create_cq = qedr_create_cq,
	.create_qp = qedr_create_qp,
	.create_srq = qedr_create_srq,
	.dealloc_pd = qedr_dealloc_pd,
	.dealloc_ucontext = qedr_dealloc_ucontext,
	.dereg_mr = qedr_dereg_mr,
	.destroy_ah = qedr_destroy_ah,
	.destroy_cq = qedr_destroy_cq,
	.destroy_qp = qedr_destroy_qp,
	.destroy_srq = qedr_destroy_srq,
	.get_dev_fw_str = qedr_get_dev_fw_str,
	.get_dma_mr = qedr_get_dma_mr,
	.get_link_layer = qedr_link_layer,
	.map_mr_sg = qedr_map_mr_sg,
	.mmap = qedr_mmap,
	.mmap_मुक्त = qedr_mmap_मुक्त,
	.modअगरy_qp = qedr_modअगरy_qp,
	.modअगरy_srq = qedr_modअगरy_srq,
	.poll_cq = qedr_poll_cq,
	.post_recv = qedr_post_recv,
	.post_send = qedr_post_send,
	.post_srq_recv = qedr_post_srq_recv,
	.process_mad = qedr_process_mad,
	.query_device = qedr_query_device,
	.query_port = qedr_query_port,
	.query_qp = qedr_query_qp,
	.query_srq = qedr_query_srq,
	.reg_user_mr = qedr_reg_user_mr,
	.req_notअगरy_cq = qedr_arm_cq,
	.resize_cq = qedr_resize_cq,

	INIT_RDMA_OBJ_SIZE(ib_ah, qedr_ah, ibah),
	INIT_RDMA_OBJ_SIZE(ib_cq, qedr_cq, ibcq),
	INIT_RDMA_OBJ_SIZE(ib_pd, qedr_pd, ibpd),
	INIT_RDMA_OBJ_SIZE(ib_srq, qedr_srq, ibsrq),
	INIT_RDMA_OBJ_SIZE(ib_xrcd, qedr_xrcd, ibxrcd),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, qedr_ucontext, ibucontext),
पूर्ण;

अटल पूर्णांक qedr_रेजिस्टर_device(काष्ठा qedr_dev *dev)
अणु
	पूर्णांक rc;

	dev->ibdev.node_guid = dev->attr.node_guid;
	स_नकल(dev->ibdev.node_desc, QEDR_NODE_DESC, माप(QEDR_NODE_DESC));

	अगर (IS_IWARP(dev)) अणु
		rc = qedr_iw_रेजिस्टर_device(dev);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		qedr_roce_रेजिस्टर_device(dev);
	पूर्ण

	dev->ibdev.phys_port_cnt = 1;
	dev->ibdev.num_comp_vectors = dev->num_cnq;
	dev->ibdev.dev.parent = &dev->pdev->dev;

	rdma_set_device_sysfs_group(&dev->ibdev, &qedr_attr_group);
	ib_set_device_ops(&dev->ibdev, &qedr_dev_ops);

	rc = ib_device_set_netdev(&dev->ibdev, dev->ndev, 1);
	अगर (rc)
		वापस rc;

	dma_set_max_seg_size(&dev->pdev->dev, अच_पूर्णांक_उच्च);
	वापस ib_रेजिस्टर_device(&dev->ibdev, "qedr%d", &dev->pdev->dev);
पूर्ण

/* This function allocates fast-path status block memory */
अटल पूर्णांक qedr_alloc_mem_sb(काष्ठा qedr_dev *dev,
			     काष्ठा qed_sb_info *sb_info, u16 sb_id)
अणु
	काष्ठा status_block_e4 *sb_virt;
	dma_addr_t sb_phys;
	पूर्णांक rc;

	sb_virt = dma_alloc_coherent(&dev->pdev->dev,
				     माप(*sb_virt), &sb_phys, GFP_KERNEL);
	अगर (!sb_virt)
		वापस -ENOMEM;

	rc = dev->ops->common->sb_init(dev->cdev, sb_info,
				       sb_virt, sb_phys, sb_id,
				       QED_SB_TYPE_CNQ);
	अगर (rc) अणु
		pr_err("Status block initialization failed\n");
		dma_मुक्त_coherent(&dev->pdev->dev, माप(*sb_virt),
				  sb_virt, sb_phys);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qedr_मुक्त_mem_sb(काष्ठा qedr_dev *dev,
			     काष्ठा qed_sb_info *sb_info, पूर्णांक sb_id)
अणु
	अगर (sb_info->sb_virt) अणु
		dev->ops->common->sb_release(dev->cdev, sb_info, sb_id,
					     QED_SB_TYPE_CNQ);
		dma_मुक्त_coherent(&dev->pdev->dev, माप(*sb_info->sb_virt),
				  (व्योम *)sb_info->sb_virt, sb_info->sb_phys);
	पूर्ण
पूर्ण

अटल व्योम qedr_मुक्त_resources(काष्ठा qedr_dev *dev)
अणु
	पूर्णांक i;

	अगर (IS_IWARP(dev))
		destroy_workqueue(dev->iwarp_wq);

	क्रम (i = 0; i < dev->num_cnq; i++) अणु
		qedr_मुक्त_mem_sb(dev, &dev->sb_array[i], dev->sb_start + i);
		dev->ops->common->chain_मुक्त(dev->cdev, &dev->cnq_array[i].pbl);
	पूर्ण

	kमुक्त(dev->cnq_array);
	kमुक्त(dev->sb_array);
	kमुक्त(dev->sgid_tbl);
पूर्ण

अटल पूर्णांक qedr_alloc_resources(काष्ठा qedr_dev *dev)
अणु
	काष्ठा qed_chain_init_params params = अणु
		.mode		= QED_CHAIN_MODE_PBL,
		.पूर्णांकended_use	= QED_CHAIN_USE_TO_CONSUME,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U16,
		.elem_size	= माप(काष्ठा regpair *),
	पूर्ण;
	काष्ठा qedr_cnq *cnq;
	__le16 *cons_pi;
	पूर्णांक i, rc;

	dev->sgid_tbl = kसुस्मृति(QEDR_MAX_SGID, माप(जोड़ ib_gid),
				GFP_KERNEL);
	अगर (!dev->sgid_tbl)
		वापस -ENOMEM;

	spin_lock_init(&dev->sgid_lock);
	xa_init_flags(&dev->srqs, XA_FLAGS_LOCK_IRQ);

	अगर (IS_IWARP(dev)) अणु
		xa_init(&dev->qps);
		dev->iwarp_wq = create_singlethपढ़ो_workqueue("qedr_iwarpq");
	पूर्ण

	/* Allocate Status blocks क्रम CNQ */
	dev->sb_array = kसुस्मृति(dev->num_cnq, माप(*dev->sb_array),
				GFP_KERNEL);
	अगर (!dev->sb_array) अणु
		rc = -ENOMEM;
		जाओ err1;
	पूर्ण

	dev->cnq_array = kसुस्मृति(dev->num_cnq,
				 माप(*dev->cnq_array), GFP_KERNEL);
	अगर (!dev->cnq_array) अणु
		rc = -ENOMEM;
		जाओ err2;
	पूर्ण

	dev->sb_start = dev->ops->rdma_get_start_sb(dev->cdev);

	/* Allocate CNQ PBLs */
	params.num_elems = min_t(u32, QED_RDMA_MAX_CNQ_SIZE,
				 QEDR_ROCE_MAX_CNQ_SIZE);

	क्रम (i = 0; i < dev->num_cnq; i++) अणु
		cnq = &dev->cnq_array[i];

		rc = qedr_alloc_mem_sb(dev, &dev->sb_array[i],
				       dev->sb_start + i);
		अगर (rc)
			जाओ err3;

		rc = dev->ops->common->chain_alloc(dev->cdev, &cnq->pbl,
						   &params);
		अगर (rc)
			जाओ err4;

		cnq->dev = dev;
		cnq->sb = &dev->sb_array[i];
		cons_pi = dev->sb_array[i].sb_virt->pi_array;
		cnq->hw_cons_ptr = &cons_pi[QED_ROCE_PROTOCOL_INDEX];
		cnq->index = i;
		प्र_लिखो(cnq->name, "qedr%d@pci:%s", i, pci_name(dev->pdev));

		DP_DEBUG(dev, QEDR_MSG_INIT, "cnq[%d].cons=%d\n",
			 i, qed_chain_get_cons_idx(&cnq->pbl));
	पूर्ण

	वापस 0;
err4:
	qedr_मुक्त_mem_sb(dev, &dev->sb_array[i], dev->sb_start + i);
err3:
	क्रम (--i; i >= 0; i--) अणु
		dev->ops->common->chain_मुक्त(dev->cdev, &dev->cnq_array[i].pbl);
		qedr_मुक्त_mem_sb(dev, &dev->sb_array[i], dev->sb_start + i);
	पूर्ण
	kमुक्त(dev->cnq_array);
err2:
	kमुक्त(dev->sb_array);
err1:
	kमुक्त(dev->sgid_tbl);
	वापस rc;
पूर्ण

अटल व्योम qedr_pci_set_atomic(काष्ठा qedr_dev *dev, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक rc = pci_enable_atomic_ops_to_root(pdev,
					       PCI_EXP_DEVCAP2_ATOMIC_COMP64);

	अगर (rc) अणु
		dev->atomic_cap = IB_ATOMIC_NONE;
		DP_DEBUG(dev, QEDR_MSG_INIT, "Atomic capability disabled\n");
	पूर्ण अन्यथा अणु
		dev->atomic_cap = IB_ATOMIC_GLOB;
		DP_DEBUG(dev, QEDR_MSG_INIT, "Atomic capability enabled\n");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा qed_rdma_ops *qed_ops;

#घोषणा HILO_U64(hi, lo)		((((u64)(hi)) << 32) + (lo))

अटल irqवापस_t qedr_irq_handler(पूर्णांक irq, व्योम *handle)
अणु
	u16 hw_comp_cons, sw_comp_cons;
	काष्ठा qedr_cnq *cnq = handle;
	काष्ठा regpair *cq_handle;
	काष्ठा qedr_cq *cq;

	qed_sb_ack(cnq->sb, IGU_INT_DISABLE, 0);

	qed_sb_update_sb_idx(cnq->sb);

	hw_comp_cons = le16_to_cpu(*cnq->hw_cons_ptr);
	sw_comp_cons = qed_chain_get_cons_idx(&cnq->pbl);

	/* Align protocol-index and chain पढ़ोs */
	rmb();

	जबतक (sw_comp_cons != hw_comp_cons) अणु
		cq_handle = (काष्ठा regpair *)qed_chain_consume(&cnq->pbl);
		cq = (काष्ठा qedr_cq *)(uपूर्णांकptr_t)HILO_U64(cq_handle->hi,
				cq_handle->lo);

		अगर (cq == शून्य) अणु
			DP_ERR(cnq->dev,
			       "Received NULL CQ cq_handle->hi=%d cq_handle->lo=%d sw_comp_cons=%d hw_comp_cons=%d\n",
			       cq_handle->hi, cq_handle->lo, sw_comp_cons,
			       hw_comp_cons);

			अवरोध;
		पूर्ण

		अगर (cq->sig != QEDR_CQ_MAGIC_NUMBER) अणु
			DP_ERR(cnq->dev,
			       "Problem with cq signature, cq_handle->hi=%d ch_handle->lo=%d cq=%p\n",
			       cq_handle->hi, cq_handle->lo, cq);
			अवरोध;
		पूर्ण

		cq->arm_flags = 0;

		अगर (!cq->destroyed && cq->ibcq.comp_handler)
			(*cq->ibcq.comp_handler)
				(&cq->ibcq, cq->ibcq.cq_context);

		/* The CQ's CNQ notअगरication counter is checked beक्रमe
		 * destroying the CQ in a busy-रुको loop that रुकोs क्रम all of
		 * the CQ's CNQ पूर्णांकerrupts to be processed. It is increased
		 * here, only after the completion handler, to ensure that the
		 * the handler is not running when the CQ is destroyed.
		 */
		cq->cnq_notअगर++;

		sw_comp_cons = qed_chain_get_cons_idx(&cnq->pbl);

		cnq->n_comp++;
	पूर्ण

	qed_ops->rdma_cnq_prod_update(cnq->dev->rdma_ctx, cnq->index,
				      sw_comp_cons);

	qed_sb_ack(cnq->sb, IGU_INT_ENABLE, 1);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम qedr_sync_मुक्त_irqs(काष्ठा qedr_dev *dev)
अणु
	u32 vector;
	u16 idx;
	पूर्णांक i;

	क्रम (i = 0; i < dev->पूर्णांक_info.used_cnt; i++) अणु
		अगर (dev->पूर्णांक_info.msix_cnt) अणु
			idx = i * dev->num_hwfns + dev->affin_hwfn_idx;
			vector = dev->पूर्णांक_info.msix[idx].vector;
			synchronize_irq(vector);
			मुक्त_irq(vector, &dev->cnq_array[i]);
		पूर्ण
	पूर्ण

	dev->पूर्णांक_info.used_cnt = 0;
पूर्ण

अटल पूर्णांक qedr_req_msix_irqs(काष्ठा qedr_dev *dev)
अणु
	पूर्णांक i, rc = 0;
	u16 idx;

	अगर (dev->num_cnq > dev->पूर्णांक_info.msix_cnt) अणु
		DP_ERR(dev,
		       "Interrupt mismatch: %d CNQ queues > %d MSI-x vectors\n",
		       dev->num_cnq, dev->पूर्णांक_info.msix_cnt);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < dev->num_cnq; i++) अणु
		idx = i * dev->num_hwfns + dev->affin_hwfn_idx;
		rc = request_irq(dev->पूर्णांक_info.msix[idx].vector,
				 qedr_irq_handler, 0, dev->cnq_array[i].name,
				 &dev->cnq_array[i]);
		अगर (rc) अणु
			DP_ERR(dev, "Request cnq %d irq failed\n", i);
			qedr_sync_मुक्त_irqs(dev);
		पूर्ण अन्यथा अणु
			DP_DEBUG(dev, QEDR_MSG_INIT,
				 "Requested cnq irq for %s [entry %d]. Cookie is at %p\n",
				 dev->cnq_array[i].name, i,
				 &dev->cnq_array[i]);
			dev->पूर्णांक_info.used_cnt++;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qedr_setup_irqs(काष्ठा qedr_dev *dev)
अणु
	पूर्णांक rc;

	DP_DEBUG(dev, QEDR_MSG_INIT, "qedr_setup_irqs\n");

	/* Learn Interrupt configuration */
	rc = dev->ops->rdma_set_rdma_पूर्णांक(dev->cdev, dev->num_cnq);
	अगर (rc < 0)
		वापस rc;

	rc = dev->ops->rdma_get_rdma_पूर्णांक(dev->cdev, &dev->पूर्णांक_info);
	अगर (rc) अणु
		DP_DEBUG(dev, QEDR_MSG_INIT, "get_rdma_int failed\n");
		वापस rc;
	पूर्ण

	अगर (dev->पूर्णांक_info.msix_cnt) अणु
		DP_DEBUG(dev, QEDR_MSG_INIT, "rdma msix_cnt = %d\n",
			 dev->पूर्णांक_info.msix_cnt);
		rc = qedr_req_msix_irqs(dev);
		अगर (rc)
			वापस rc;
	पूर्ण

	DP_DEBUG(dev, QEDR_MSG_INIT, "qedr_setup_irqs succeeded\n");

	वापस 0;
पूर्ण

अटल पूर्णांक qedr_set_device_attr(काष्ठा qedr_dev *dev)
अणु
	काष्ठा qed_rdma_device *qed_attr;
	काष्ठा qedr_device_attr *attr;
	u32 page_size;

	/* Part 1 - query core capabilities */
	qed_attr = dev->ops->rdma_query_device(dev->rdma_ctx);

	/* Part 2 - check capabilities */
	page_size = ~qed_attr->page_size_caps + 1;
	अगर (page_size > PAGE_SIZE) अणु
		DP_ERR(dev,
		       "Kernel PAGE_SIZE is %ld which is smaller than minimum page size (%d) required by qedr\n",
		       PAGE_SIZE, page_size);
		वापस -ENODEV;
	पूर्ण

	/* Part 3 - copy and update capabilities */
	attr = &dev->attr;
	attr->venकरोr_id = qed_attr->venकरोr_id;
	attr->venकरोr_part_id = qed_attr->venकरोr_part_id;
	attr->hw_ver = qed_attr->hw_ver;
	attr->fw_ver = qed_attr->fw_ver;
	attr->node_guid = qed_attr->node_guid;
	attr->sys_image_guid = qed_attr->sys_image_guid;
	attr->max_cnq = qed_attr->max_cnq;
	attr->max_sge = qed_attr->max_sge;
	attr->max_अंतरभूत = qed_attr->max_अंतरभूत;
	attr->max_sqe = min_t(u32, qed_attr->max_wqe, QEDR_MAX_SQE);
	attr->max_rqe = min_t(u32, qed_attr->max_wqe, QEDR_MAX_RQE);
	attr->max_qp_resp_rd_atomic_resc = qed_attr->max_qp_resp_rd_atomic_resc;
	attr->max_qp_req_rd_atomic_resc = qed_attr->max_qp_req_rd_atomic_resc;
	attr->max_dev_resp_rd_atomic_resc =
	    qed_attr->max_dev_resp_rd_atomic_resc;
	attr->max_cq = qed_attr->max_cq;
	attr->max_qp = qed_attr->max_qp;
	attr->max_mr = qed_attr->max_mr;
	attr->max_mr_size = qed_attr->max_mr_size;
	attr->max_cqe = min_t(u64, qed_attr->max_cqe, QEDR_MAX_CQES);
	attr->max_mw = qed_attr->max_mw;
	attr->max_mr_mw_fmr_pbl = qed_attr->max_mr_mw_fmr_pbl;
	attr->max_mr_mw_fmr_size = qed_attr->max_mr_mw_fmr_size;
	attr->max_pd = qed_attr->max_pd;
	attr->max_ah = qed_attr->max_ah;
	attr->max_pkey = qed_attr->max_pkey;
	attr->max_srq = qed_attr->max_srq;
	attr->max_srq_wr = qed_attr->max_srq_wr;
	attr->dev_caps = qed_attr->dev_caps;
	attr->page_size_caps = qed_attr->page_size_caps;
	attr->dev_ack_delay = qed_attr->dev_ack_delay;
	attr->reserved_lkey = qed_attr->reserved_lkey;
	attr->bad_pkey_counter = qed_attr->bad_pkey_counter;
	attr->max_stats_queues = qed_attr->max_stats_queues;

	वापस 0;
पूर्ण

अटल व्योम qedr_unaffiliated_event(व्योम *context, u8 event_code)
अणु
	pr_err("unaffiliated event not implemented yet\n");
पूर्ण

अटल व्योम qedr_affiliated_event(व्योम *context, u8 e_code, व्योम *fw_handle)
अणु
#घोषणा EVENT_TYPE_NOT_DEFINED	0
#घोषणा EVENT_TYPE_CQ		1
#घोषणा EVENT_TYPE_QP		2
#घोषणा EVENT_TYPE_SRQ		3
	काष्ठा qedr_dev *dev = (काष्ठा qedr_dev *)context;
	काष्ठा regpair *async_handle = (काष्ठा regpair *)fw_handle;
	u64 roce_handle64 = ((u64) async_handle->hi << 32) + async_handle->lo;
	u8 event_type = EVENT_TYPE_NOT_DEFINED;
	काष्ठा ib_event event;
	काष्ठा ib_srq *ibsrq;
	काष्ठा qedr_srq *srq;
	अचिन्हित दीर्घ flags;
	काष्ठा ib_cq *ibcq;
	काष्ठा ib_qp *ibqp;
	काष्ठा qedr_cq *cq;
	काष्ठा qedr_qp *qp;
	u16 srq_id;

	अगर (IS_ROCE(dev)) अणु
		चयन (e_code) अणु
		हाल ROCE_ASYNC_EVENT_CQ_OVERFLOW_ERR:
			event.event = IB_EVENT_CQ_ERR;
			event_type = EVENT_TYPE_CQ;
			अवरोध;
		हाल ROCE_ASYNC_EVENT_SQ_DRAINED:
			event.event = IB_EVENT_SQ_DRAINED;
			event_type = EVENT_TYPE_QP;
			अवरोध;
		हाल ROCE_ASYNC_EVENT_QP_CATASTROPHIC_ERR:
			event.event = IB_EVENT_QP_FATAL;
			event_type = EVENT_TYPE_QP;
			अवरोध;
		हाल ROCE_ASYNC_EVENT_LOCAL_INVALID_REQUEST_ERR:
			event.event = IB_EVENT_QP_REQ_ERR;
			event_type = EVENT_TYPE_QP;
			अवरोध;
		हाल ROCE_ASYNC_EVENT_LOCAL_ACCESS_ERR:
			event.event = IB_EVENT_QP_ACCESS_ERR;
			event_type = EVENT_TYPE_QP;
			अवरोध;
		हाल ROCE_ASYNC_EVENT_SRQ_LIMIT:
			event.event = IB_EVENT_SRQ_LIMIT_REACHED;
			event_type = EVENT_TYPE_SRQ;
			अवरोध;
		हाल ROCE_ASYNC_EVENT_SRQ_EMPTY:
			event.event = IB_EVENT_SRQ_ERR;
			event_type = EVENT_TYPE_SRQ;
			अवरोध;
		हाल ROCE_ASYNC_EVENT_XRC_DOMAIN_ERR:
			event.event = IB_EVENT_QP_ACCESS_ERR;
			event_type = EVENT_TYPE_QP;
			अवरोध;
		हाल ROCE_ASYNC_EVENT_INVALID_XRCETH_ERR:
			event.event = IB_EVENT_QP_ACCESS_ERR;
			event_type = EVENT_TYPE_QP;
			अवरोध;
		हाल ROCE_ASYNC_EVENT_XRC_SRQ_CATASTROPHIC_ERR:
			event.event = IB_EVENT_CQ_ERR;
			event_type = EVENT_TYPE_CQ;
			अवरोध;
		शेष:
			DP_ERR(dev, "unsupported event %d on handle=%llx\n",
			       e_code, roce_handle64);
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (e_code) अणु
		हाल QED_IWARP_EVENT_SRQ_LIMIT:
			event.event = IB_EVENT_SRQ_LIMIT_REACHED;
			event_type = EVENT_TYPE_SRQ;
			अवरोध;
		हाल QED_IWARP_EVENT_SRQ_EMPTY:
			event.event = IB_EVENT_SRQ_ERR;
			event_type = EVENT_TYPE_SRQ;
			अवरोध;
		शेष:
		DP_ERR(dev, "unsupported event %d on handle=%llx\n", e_code,
		       roce_handle64);
		पूर्ण
	पूर्ण
	चयन (event_type) अणु
	हाल EVENT_TYPE_CQ:
		cq = (काष्ठा qedr_cq *)(uपूर्णांकptr_t)roce_handle64;
		अगर (cq) अणु
			ibcq = &cq->ibcq;
			अगर (ibcq->event_handler) अणु
				event.device = ibcq->device;
				event.element.cq = ibcq;
				ibcq->event_handler(&event, ibcq->cq_context);
			पूर्ण
		पूर्ण अन्यथा अणु
			WARN(1,
			     "Error: CQ event with NULL pointer ibcq. Handle=%llx\n",
			     roce_handle64);
		पूर्ण
		DP_ERR(dev, "CQ event %d on handle %p\n", e_code, cq);
		अवरोध;
	हाल EVENT_TYPE_QP:
		qp = (काष्ठा qedr_qp *)(uपूर्णांकptr_t)roce_handle64;
		अगर (qp) अणु
			ibqp = &qp->ibqp;
			अगर (ibqp->event_handler) अणु
				event.device = ibqp->device;
				event.element.qp = ibqp;
				ibqp->event_handler(&event, ibqp->qp_context);
			पूर्ण
		पूर्ण अन्यथा अणु
			WARN(1,
			     "Error: QP event with NULL pointer ibqp. Handle=%llx\n",
			     roce_handle64);
		पूर्ण
		DP_ERR(dev, "QP event %d on handle %p\n", e_code, qp);
		अवरोध;
	हाल EVENT_TYPE_SRQ:
		srq_id = (u16)roce_handle64;
		xa_lock_irqsave(&dev->srqs, flags);
		srq = xa_load(&dev->srqs, srq_id);
		अगर (srq) अणु
			ibsrq = &srq->ibsrq;
			अगर (ibsrq->event_handler) अणु
				event.device = ibsrq->device;
				event.element.srq = ibsrq;
				ibsrq->event_handler(&event,
						     ibsrq->srq_context);
			पूर्ण
		पूर्ण अन्यथा अणु
			DP_NOTICE(dev,
				  "SRQ event with NULL pointer ibsrq. Handle=%llx\n",
				  roce_handle64);
		पूर्ण
		xa_unlock_irqrestore(&dev->srqs, flags);
		DP_NOTICE(dev, "SRQ event %d on handle %p\n", e_code, srq);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक qedr_init_hw(काष्ठा qedr_dev *dev)
अणु
	काष्ठा qed_rdma_add_user_out_params out_params;
	काष्ठा qed_rdma_start_in_params *in_params;
	काष्ठा qed_rdma_cnq_params *cur_pbl;
	काष्ठा qed_rdma_events events;
	dma_addr_t p_phys_table;
	u32 page_cnt;
	पूर्णांक rc = 0;
	पूर्णांक i;

	in_params =  kzalloc(माप(*in_params), GFP_KERNEL);
	अगर (!in_params) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	in_params->desired_cnq = dev->num_cnq;
	क्रम (i = 0; i < dev->num_cnq; i++) अणु
		cur_pbl = &in_params->cnq_pbl_list[i];

		page_cnt = qed_chain_get_page_cnt(&dev->cnq_array[i].pbl);
		cur_pbl->num_pbl_pages = page_cnt;

		p_phys_table = qed_chain_get_pbl_phys(&dev->cnq_array[i].pbl);
		cur_pbl->pbl_ptr = (u64)p_phys_table;
	पूर्ण

	events.affiliated_event = qedr_affiliated_event;
	events.unaffiliated_event = qedr_unaffiliated_event;
	events.context = dev;

	in_params->events = &events;
	in_params->cq_mode = QED_RDMA_CQ_MODE_32_BITS;
	in_params->max_mtu = dev->ndev->mtu;
	dev->iwarp_max_mtu = dev->ndev->mtu;
	ether_addr_copy(&in_params->mac_addr[0], dev->ndev->dev_addr);

	rc = dev->ops->rdma_init(dev->cdev, in_params);
	अगर (rc)
		जाओ out;

	rc = dev->ops->rdma_add_user(dev->rdma_ctx, &out_params);
	अगर (rc)
		जाओ out;

	dev->db_addr = out_params.dpi_addr;
	dev->db_phys_addr = out_params.dpi_phys_addr;
	dev->db_size = out_params.dpi_size;
	dev->dpi = out_params.dpi;

	rc = qedr_set_device_attr(dev);
out:
	kमुक्त(in_params);
	अगर (rc)
		DP_ERR(dev, "Init HW Failed rc = %d\n", rc);

	वापस rc;
पूर्ण

अटल व्योम qedr_stop_hw(काष्ठा qedr_dev *dev)
अणु
	dev->ops->rdma_हटाओ_user(dev->rdma_ctx, dev->dpi);
	dev->ops->rdma_stop(dev->rdma_ctx);
पूर्ण

अटल काष्ठा qedr_dev *qedr_add(काष्ठा qed_dev *cdev, काष्ठा pci_dev *pdev,
				 काष्ठा net_device *ndev)
अणु
	काष्ठा qed_dev_rdma_info dev_info;
	काष्ठा qedr_dev *dev;
	पूर्णांक rc = 0;

	dev = ib_alloc_device(qedr_dev, ibdev);
	अगर (!dev) अणु
		pr_err("Unable to allocate ib device\n");
		वापस शून्य;
	पूर्ण

	DP_DEBUG(dev, QEDR_MSG_INIT, "qedr add device called\n");

	dev->pdev = pdev;
	dev->ndev = ndev;
	dev->cdev = cdev;

	qed_ops = qed_get_rdma_ops();
	अगर (!qed_ops) अणु
		DP_ERR(dev, "Failed to get qed roce operations\n");
		जाओ init_err;
	पूर्ण

	dev->ops = qed_ops;
	rc = qed_ops->fill_dev_info(cdev, &dev_info);
	अगर (rc)
		जाओ init_err;

	dev->user_dpm_enabled = dev_info.user_dpm_enabled;
	dev->rdma_type = dev_info.rdma_type;
	dev->num_hwfns = dev_info.common.num_hwfns;

	अगर (IS_IWARP(dev) && QEDR_IS_CMT(dev)) अणु
		rc = dev->ops->iwarp_set_engine_affin(cdev, false);
		अगर (rc) अणु
			DP_ERR(dev, "iWARP is disabled over a 100g device Enabling it may impact L2 performance. To enable it run devlink dev param set <dev> name iwarp_cmt value true cmode runtime\n");
			जाओ init_err;
		पूर्ण
	पूर्ण
	dev->affin_hwfn_idx = dev->ops->common->get_affin_hwfn_idx(cdev);

	dev->rdma_ctx = dev->ops->rdma_get_rdma_ctx(cdev);

	dev->num_cnq = dev->ops->rdma_get_min_cnq_msix(cdev);
	अगर (!dev->num_cnq) अणु
		DP_ERR(dev, "Failed. At least one CNQ is required.\n");
		rc = -ENOMEM;
		जाओ init_err;
	पूर्ण

	dev->wq_multiplier = QEDR_WQ_MULTIPLIER_DFT;

	qedr_pci_set_atomic(dev, pdev);

	rc = qedr_alloc_resources(dev);
	अगर (rc)
		जाओ init_err;

	rc = qedr_init_hw(dev);
	अगर (rc)
		जाओ alloc_err;

	rc = qedr_setup_irqs(dev);
	अगर (rc)
		जाओ irq_err;

	rc = qedr_रेजिस्टर_device(dev);
	अगर (rc) अणु
		DP_ERR(dev, "Unable to allocate register device\n");
		जाओ reg_err;
	पूर्ण

	अगर (!test_and_set_bit(QEDR_ENET_STATE_BIT, &dev->enet_state))
		qedr_ib_dispatch_event(dev, QEDR_PORT, IB_EVENT_PORT_ACTIVE);

	DP_DEBUG(dev, QEDR_MSG_INIT, "qedr driver loaded successfully\n");
	वापस dev;

reg_err:
	qedr_sync_मुक्त_irqs(dev);
irq_err:
	qedr_stop_hw(dev);
alloc_err:
	qedr_मुक्त_resources(dev);
init_err:
	ib_dealloc_device(&dev->ibdev);
	DP_ERR(dev, "qedr driver load failed rc=%d\n", rc);

	वापस शून्य;
पूर्ण

अटल व्योम qedr_हटाओ(काष्ठा qedr_dev *dev)
अणु
	/* First unरेजिस्टर with stack to stop all the active traffic
	 * of the रेजिस्टरed clients.
	 */
	ib_unरेजिस्टर_device(&dev->ibdev);

	qedr_stop_hw(dev);
	qedr_sync_मुक्त_irqs(dev);
	qedr_मुक्त_resources(dev);

	अगर (IS_IWARP(dev) && QEDR_IS_CMT(dev))
		dev->ops->iwarp_set_engine_affin(dev->cdev, true);

	ib_dealloc_device(&dev->ibdev);
पूर्ण

अटल व्योम qedr_बंद(काष्ठा qedr_dev *dev)
अणु
	अगर (test_and_clear_bit(QEDR_ENET_STATE_BIT, &dev->enet_state))
		qedr_ib_dispatch_event(dev, QEDR_PORT, IB_EVENT_PORT_ERR);
पूर्ण

अटल व्योम qedr_shutकरोwn(काष्ठा qedr_dev *dev)
अणु
	qedr_बंद(dev);
	qedr_हटाओ(dev);
पूर्ण

अटल व्योम qedr_खोलो(काष्ठा qedr_dev *dev)
अणु
	अगर (!test_and_set_bit(QEDR_ENET_STATE_BIT, &dev->enet_state))
		qedr_ib_dispatch_event(dev, QEDR_PORT, IB_EVENT_PORT_ACTIVE);
पूर्ण

अटल व्योम qedr_mac_address_change(काष्ठा qedr_dev *dev)
अणु
	जोड़ ib_gid *sgid = &dev->sgid_tbl[0];
	u8 guid[8], mac_addr[6];
	पूर्णांक rc;

	/* Update SGID */
	ether_addr_copy(&mac_addr[0], dev->ndev->dev_addr);
	guid[0] = mac_addr[0] ^ 2;
	guid[1] = mac_addr[1];
	guid[2] = mac_addr[2];
	guid[3] = 0xff;
	guid[4] = 0xfe;
	guid[5] = mac_addr[3];
	guid[6] = mac_addr[4];
	guid[7] = mac_addr[5];
	sgid->global.subnet_prefix = cpu_to_be64(0xfe80000000000000LL);
	स_नकल(&sgid->raw[8], guid, माप(guid));

	/* Update LL2 */
	rc = dev->ops->ll2_set_mac_filter(dev->cdev,
					  dev->gsi_ll2_mac_address,
					  dev->ndev->dev_addr);

	ether_addr_copy(dev->gsi_ll2_mac_address, dev->ndev->dev_addr);

	qedr_ib_dispatch_event(dev, QEDR_PORT, IB_EVENT_GID_CHANGE);

	अगर (rc)
		DP_ERR(dev, "Error updating mac filter\n");
पूर्ण

/* event handling via NIC driver ensures that all the NIC specअगरic
 * initialization करोne beक्रमe RoCE driver notअगरies
 * event to stack.
 */
अटल व्योम qedr_notअगरy(काष्ठा qedr_dev *dev, क्रमागत qede_rdma_event event)
अणु
	चयन (event) अणु
	हाल QEDE_UP:
		qedr_खोलो(dev);
		अवरोध;
	हाल QEDE_DOWN:
		qedr_बंद(dev);
		अवरोध;
	हाल QEDE_CLOSE:
		qedr_shutकरोwn(dev);
		अवरोध;
	हाल QEDE_CHANGE_ADDR:
		qedr_mac_address_change(dev);
		अवरोध;
	हाल QEDE_CHANGE_MTU:
		अगर (rdma_protocol_iwarp(&dev->ibdev, 1))
			अगर (dev->ndev->mtu != dev->iwarp_max_mtu)
				DP_NOTICE(dev,
					  "Mtu was changed from %d to %d. This will not take affect for iWARP until qedr is reloaded\n",
					  dev->iwarp_max_mtu, dev->ndev->mtu);
		अवरोध;
	शेष:
		pr_err("Event not supported\n");
	पूर्ण
पूर्ण

अटल काष्ठा qedr_driver qedr_drv = अणु
	.name = "qedr_driver",
	.add = qedr_add,
	.हटाओ = qedr_हटाओ,
	.notअगरy = qedr_notअगरy,
पूर्ण;

अटल पूर्णांक __init qedr_init_module(व्योम)
अणु
	वापस qede_rdma_रेजिस्टर_driver(&qedr_drv);
पूर्ण

अटल व्योम __निकास qedr_निकास_module(व्योम)
अणु
	qede_rdma_unरेजिस्टर_driver(&qedr_drv);
पूर्ण

module_init(qedr_init_module);
module_निकास(qedr_निकास_module);
