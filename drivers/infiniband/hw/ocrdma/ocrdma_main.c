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

#समावेश <linux/module.h>
#समावेश <linux/idr.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_mad.h>

#समावेश <linux/netdevice.h>
#समावेश <net/addrconf.h>

#समावेश "ocrdma.h"
#समावेश "ocrdma_verbs.h"
#समावेश "ocrdma_ah.h"
#समावेश "be_roce.h"
#समावेश "ocrdma_hw.h"
#समावेश "ocrdma_stats.h"
#समावेश <rdma/ocrdma-abi.h>

MODULE_DESCRIPTION(OCRDMA_ROCE_DRV_DESC " " OCRDMA_ROCE_DRV_VERSION);
MODULE_AUTHOR("Emulex Corporation");
MODULE_LICENSE("Dual BSD/GPL");

व्योम ocrdma_get_guid(काष्ठा ocrdma_dev *dev, u8 *guid)
अणु
	u8 mac_addr[6];

	स_नकल(&mac_addr[0], &dev->nic_info.mac_addr[0], ETH_ALEN);
	guid[0] = mac_addr[0] ^ 2;
	guid[1] = mac_addr[1];
	guid[2] = mac_addr[2];
	guid[3] = 0xff;
	guid[4] = 0xfe;
	guid[5] = mac_addr[3];
	guid[6] = mac_addr[4];
	guid[7] = mac_addr[5];
पूर्ण
अटल क्रमागत rdma_link_layer ocrdma_link_layer(काष्ठा ib_device *device,
					      u32 port_num)
अणु
	वापस IB_LINK_LAYER_ETHERNET;
पूर्ण

अटल पूर्णांक ocrdma_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
			         काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा ib_port_attr attr;
	काष्ठा ocrdma_dev *dev;
	पूर्णांक err;

	dev = get_ocrdma_dev(ibdev);
	immutable->core_cap_flags = RDMA_CORE_PORT_IBA_ROCE;
	अगर (ocrdma_is_udp_encap_supported(dev))
		immutable->core_cap_flags |= RDMA_CORE_CAP_PROT_ROCE_UDP_ENCAP;

	err = ib_query_port(ibdev, port_num, &attr);
	अगर (err)
		वापस err;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;
	immutable->max_mad_size = IB_MGMT_MAD_SIZE;

	वापस 0;
पूर्ण

अटल व्योम get_dev_fw_str(काष्ठा ib_device *device, अक्षर *str)
अणु
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(device);

	snम_लिखो(str, IB_FW_VERSION_NAME_MAX, "%s", &dev->attr.fw_ver[0]);
पूर्ण

/* OCRDMA sysfs पूर्णांकerface */
अटल sमाप_प्रकार hw_rev_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ocrdma_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा ocrdma_dev, ibdev);

	वापस sysfs_emit(buf, "0x%x\n", dev->nic_info.pdev->venकरोr);
पूर्ण
अटल DEVICE_ATTR_RO(hw_rev);

अटल sमाप_प्रकार hca_type_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ocrdma_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा ocrdma_dev, ibdev);

	वापस sysfs_emit(buf, "%s\n", &dev->model_number[0]);
पूर्ण
अटल DEVICE_ATTR_RO(hca_type);

अटल काष्ठा attribute *ocrdma_attributes[] = अणु
	&dev_attr_hw_rev.attr,
	&dev_attr_hca_type.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ocrdma_attr_group = अणु
	.attrs = ocrdma_attributes,
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops ocrdma_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_OCRDMA,
	.uverbs_abi_ver = OCRDMA_ABI_VERSION,

	.alloc_mr = ocrdma_alloc_mr,
	.alloc_pd = ocrdma_alloc_pd,
	.alloc_ucontext = ocrdma_alloc_ucontext,
	.create_ah = ocrdma_create_ah,
	.create_cq = ocrdma_create_cq,
	.create_qp = ocrdma_create_qp,
	.create_user_ah = ocrdma_create_ah,
	.dealloc_pd = ocrdma_dealloc_pd,
	.dealloc_ucontext = ocrdma_dealloc_ucontext,
	.dereg_mr = ocrdma_dereg_mr,
	.destroy_ah = ocrdma_destroy_ah,
	.destroy_cq = ocrdma_destroy_cq,
	.destroy_qp = ocrdma_destroy_qp,
	.get_dev_fw_str = get_dev_fw_str,
	.get_dma_mr = ocrdma_get_dma_mr,
	.get_link_layer = ocrdma_link_layer,
	.get_port_immutable = ocrdma_port_immutable,
	.map_mr_sg = ocrdma_map_mr_sg,
	.mmap = ocrdma_mmap,
	.modअगरy_qp = ocrdma_modअगरy_qp,
	.poll_cq = ocrdma_poll_cq,
	.post_recv = ocrdma_post_recv,
	.post_send = ocrdma_post_send,
	.process_mad = ocrdma_process_mad,
	.query_ah = ocrdma_query_ah,
	.query_device = ocrdma_query_device,
	.query_pkey = ocrdma_query_pkey,
	.query_port = ocrdma_query_port,
	.query_qp = ocrdma_query_qp,
	.reg_user_mr = ocrdma_reg_user_mr,
	.req_notअगरy_cq = ocrdma_arm_cq,
	.resize_cq = ocrdma_resize_cq,

	INIT_RDMA_OBJ_SIZE(ib_ah, ocrdma_ah, ibah),
	INIT_RDMA_OBJ_SIZE(ib_cq, ocrdma_cq, ibcq),
	INIT_RDMA_OBJ_SIZE(ib_pd, ocrdma_pd, ibpd),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, ocrdma_ucontext, ibucontext),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops ocrdma_dev_srq_ops = अणु
	.create_srq = ocrdma_create_srq,
	.destroy_srq = ocrdma_destroy_srq,
	.modअगरy_srq = ocrdma_modअगरy_srq,
	.post_srq_recv = ocrdma_post_srq_recv,
	.query_srq = ocrdma_query_srq,

	INIT_RDMA_OBJ_SIZE(ib_srq, ocrdma_srq, ibsrq),
पूर्ण;

अटल पूर्णांक ocrdma_रेजिस्टर_device(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक ret;

	ocrdma_get_guid(dev, (u8 *)&dev->ibdev.node_guid);
	BUILD_BUG_ON(माप(OCRDMA_NODE_DESC) > IB_DEVICE_NODE_DESC_MAX);
	स_नकल(dev->ibdev.node_desc, OCRDMA_NODE_DESC,
	       माप(OCRDMA_NODE_DESC));

	dev->ibdev.node_type = RDMA_NODE_IB_CA;
	dev->ibdev.phys_port_cnt = 1;
	dev->ibdev.num_comp_vectors = dev->eq_cnt;

	/* mandatory to support user space verbs consumer. */
	dev->ibdev.dev.parent = &dev->nic_info.pdev->dev;

	ib_set_device_ops(&dev->ibdev, &ocrdma_dev_ops);

	अगर (ocrdma_get_asic_type(dev) == OCRDMA_ASIC_GEN_SKH_R)
		ib_set_device_ops(&dev->ibdev, &ocrdma_dev_srq_ops);

	rdma_set_device_sysfs_group(&dev->ibdev, &ocrdma_attr_group);
	ret = ib_device_set_netdev(&dev->ibdev, dev->nic_info.netdev, 1);
	अगर (ret)
		वापस ret;

	dma_set_max_seg_size(&dev->nic_info.pdev->dev, अच_पूर्णांक_उच्च);
	वापस ib_रेजिस्टर_device(&dev->ibdev, "ocrdma%d",
				  &dev->nic_info.pdev->dev);
पूर्ण

अटल पूर्णांक ocrdma_alloc_resources(काष्ठा ocrdma_dev *dev)
अणु
	mutex_init(&dev->dev_lock);
	dev->cq_tbl = kसुस्मृति(OCRDMA_MAX_CQ, माप(काष्ठा ocrdma_cq *),
			      GFP_KERNEL);
	अगर (!dev->cq_tbl)
		जाओ alloc_err;

	अगर (dev->attr.max_qp) अणु
		dev->qp_tbl = kसुस्मृति(OCRDMA_MAX_QP,
				      माप(काष्ठा ocrdma_qp *),
				      GFP_KERNEL);
		अगर (!dev->qp_tbl)
			जाओ alloc_err;
	पूर्ण

	dev->stag_arr = kसुस्मृति(OCRDMA_MAX_STAG, माप(u64), GFP_KERNEL);
	अगर (dev->stag_arr == शून्य)
		जाओ alloc_err;

	ocrdma_alloc_pd_pool(dev);

	अगर (!ocrdma_alloc_stats_resources(dev)) अणु
		pr_err("%s: stats resource allocation failed\n", __func__);
		जाओ alloc_err;
	पूर्ण

	spin_lock_init(&dev->av_tbl.lock);
	spin_lock_init(&dev->flush_q_lock);
	वापस 0;
alloc_err:
	pr_err("%s(%d) error.\n", __func__, dev->id);
	वापस -ENOMEM;
पूर्ण

अटल व्योम ocrdma_मुक्त_resources(काष्ठा ocrdma_dev *dev)
अणु
	ocrdma_release_stats_resources(dev);
	kमुक्त(dev->stag_arr);
	kमुक्त(dev->qp_tbl);
	kमुक्त(dev->cq_tbl);
पूर्ण

अटल काष्ठा ocrdma_dev *ocrdma_add(काष्ठा be_dev_info *dev_info)
अणु
	पूर्णांक status = 0;
	u8 lstate = 0;
	काष्ठा ocrdma_dev *dev;

	dev = ib_alloc_device(ocrdma_dev, ibdev);
	अगर (!dev) अणु
		pr_err("Unable to allocate ib device\n");
		वापस शून्य;
	पूर्ण

	dev->mbx_cmd = kzalloc(माप(काष्ठा ocrdma_mqe_emb_cmd), GFP_KERNEL);
	अगर (!dev->mbx_cmd)
		जाओ init_err;

	स_नकल(&dev->nic_info, dev_info, माप(*dev_info));
	dev->id = PCI_FUNC(dev->nic_info.pdev->devfn);
	status = ocrdma_init_hw(dev);
	अगर (status)
		जाओ init_err;

	status = ocrdma_alloc_resources(dev);
	अगर (status)
		जाओ alloc_err;

	ocrdma_init_service_level(dev);
	status = ocrdma_रेजिस्टर_device(dev);
	अगर (status)
		जाओ alloc_err;

	/* Query Link state and update */
	status = ocrdma_mbx_get_link_speed(dev, शून्य, &lstate);
	अगर (!status)
		ocrdma_update_link_state(dev, lstate);

	/* Init stats */
	ocrdma_add_port_stats(dev);
	/* Interrupt Moderation */
	INIT_DELAYED_WORK(&dev->eqd_work, ocrdma_eqd_set_task);
	schedule_delayed_work(&dev->eqd_work, msecs_to_jअगरfies(1000));

	pr_info("%s %s: %s \"%s\" port %d\n",
		dev_name(&dev->nic_info.pdev->dev), hca_name(dev),
		port_speed_string(dev), dev->model_number,
		dev->hba_port_num);
	pr_info("%s ocrdma%d driver loaded successfully\n",
		dev_name(&dev->nic_info.pdev->dev), dev->id);
	वापस dev;

alloc_err:
	ocrdma_मुक्त_resources(dev);
	ocrdma_cleanup_hw(dev);
init_err:
	kमुक्त(dev->mbx_cmd);
	ib_dealloc_device(&dev->ibdev);
	pr_err("%s() leaving. ret=%d\n", __func__, status);
	वापस शून्य;
पूर्ण

अटल व्योम ocrdma_हटाओ_मुक्त(काष्ठा ocrdma_dev *dev)
अणु

	kमुक्त(dev->mbx_cmd);
	ib_dealloc_device(&dev->ibdev);
पूर्ण

अटल व्योम ocrdma_हटाओ(काष्ठा ocrdma_dev *dev)
अणु
	/* first unरेजिस्टर with stack to stop all the active traffic
	 * of the रेजिस्टरed clients.
	 */
	cancel_delayed_work_sync(&dev->eqd_work);
	ib_unरेजिस्टर_device(&dev->ibdev);

	ocrdma_rem_port_stats(dev);
	ocrdma_मुक्त_resources(dev);
	ocrdma_cleanup_hw(dev);
	ocrdma_हटाओ_मुक्त(dev);
पूर्ण

अटल पूर्णांक ocrdma_dispatch_port_active(काष्ठा ocrdma_dev *dev)
अणु
	काष्ठा ib_event port_event;

	port_event.event = IB_EVENT_PORT_ACTIVE;
	port_event.element.port_num = 1;
	port_event.device = &dev->ibdev;
	ib_dispatch_event(&port_event);
	वापस 0;
पूर्ण

अटल पूर्णांक ocrdma_dispatch_port_error(काष्ठा ocrdma_dev *dev)
अणु
	काष्ठा ib_event err_event;

	err_event.event = IB_EVENT_PORT_ERR;
	err_event.element.port_num = 1;
	err_event.device = &dev->ibdev;
	ib_dispatch_event(&err_event);
	वापस 0;
पूर्ण

अटल व्योम ocrdma_shutकरोwn(काष्ठा ocrdma_dev *dev)
अणु
	ocrdma_dispatch_port_error(dev);
	ocrdma_हटाओ(dev);
पूर्ण

/* event handling via NIC driver ensures that all the NIC specअगरic
 * initialization करोne beक्रमe RoCE driver notअगरies
 * event to stack.
 */
अटल व्योम ocrdma_event_handler(काष्ठा ocrdma_dev *dev, u32 event)
अणु
	चयन (event) अणु
	हाल BE_DEV_SHUTDOWN:
		ocrdma_shutकरोwn(dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम ocrdma_update_link_state(काष्ठा ocrdma_dev *dev, u8 lstate)
अणु
	अगर (!(dev->flags & OCRDMA_FLAGS_LINK_STATUS_INIT)) अणु
		dev->flags |= OCRDMA_FLAGS_LINK_STATUS_INIT;
		अगर (!lstate)
			वापस;
	पूर्ण

	अगर (!lstate)
		ocrdma_dispatch_port_error(dev);
	अन्यथा
		ocrdma_dispatch_port_active(dev);
पूर्ण

अटल काष्ठा ocrdma_driver ocrdma_drv = अणु
	.name			= "ocrdma_driver",
	.add			= ocrdma_add,
	.हटाओ			= ocrdma_हटाओ,
	.state_change_handler	= ocrdma_event_handler,
	.be_abi_version		= OCRDMA_BE_ROCE_ABI_VERSION,
पूर्ण;

अटल पूर्णांक __init ocrdma_init_module(व्योम)
अणु
	पूर्णांक status;

	ocrdma_init_debugfs();

	status = be_roce_रेजिस्टर_driver(&ocrdma_drv);
	अगर (status)
		जाओ err_be_reg;

	वापस 0;

err_be_reg:

	वापस status;
पूर्ण

अटल व्योम __निकास ocrdma_निकास_module(व्योम)
अणु
	be_roce_unरेजिस्टर_driver(&ocrdma_drv);
	ocrdma_rem_debugfs();
पूर्ण

module_init(ocrdma_init_module);
module_निकास(ocrdma_निकास_module);
