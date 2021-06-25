<शैली गुरु>
/*
 * Copyright (c) 2009-2010 Chelsio, Inc. All rights reserved.
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
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <rdma/iw_cm.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_user_verbs.h>

#समावेश "iw_cxgb4.h"

अटल पूर्णांक fastreg_support = 1;
module_param(fastreg_support, पूर्णांक, 0644);
MODULE_PARM_DESC(fastreg_support, "Advertise fastreg support (default=1)");

अटल व्योम c4iw_dealloc_ucontext(काष्ठा ib_ucontext *context)
अणु
	काष्ठा c4iw_ucontext *ucontext = to_c4iw_ucontext(context);
	काष्ठा c4iw_dev *rhp;
	काष्ठा c4iw_mm_entry *mm, *पंचांगp;

	pr_debug("context %p\n", context);
	rhp = to_c4iw_dev(ucontext->ibucontext.device);

	list_क्रम_each_entry_safe(mm, पंचांगp, &ucontext->mmaps, entry)
		kमुक्त(mm);
	c4iw_release_dev_ucontext(&rhp->rdev, &ucontext->uctx);
पूर्ण

अटल पूर्णांक c4iw_alloc_ucontext(काष्ठा ib_ucontext *ucontext,
			       काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ucontext->device;
	काष्ठा c4iw_ucontext *context = to_c4iw_ucontext(ucontext);
	काष्ठा c4iw_dev *rhp = to_c4iw_dev(ibdev);
	काष्ठा c4iw_alloc_ucontext_resp uresp;
	पूर्णांक ret = 0;
	काष्ठा c4iw_mm_entry *mm = शून्य;

	pr_debug("ibdev %p\n", ibdev);
	c4iw_init_dev_ucontext(&rhp->rdev, &context->uctx);
	INIT_LIST_HEAD(&context->mmaps);
	spin_lock_init(&context->mmap_lock);

	अगर (udata->outlen < माप(uresp) - माप(uresp.reserved)) अणु
		pr_err_once("Warning - downlevel libcxgb4 (non-fatal), device status page disabled\n");
		rhp->rdev.flags |= T4_STATUS_PAGE_DISABLED;
	पूर्ण अन्यथा अणु
		mm = kदो_स्मृति(माप(*mm), GFP_KERNEL);
		अगर (!mm) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		uresp.status_page_size = PAGE_SIZE;

		spin_lock(&context->mmap_lock);
		uresp.status_page_key = context->key;
		context->key += PAGE_SIZE;
		spin_unlock(&context->mmap_lock);

		ret = ib_copy_to_udata(udata, &uresp,
				       माप(uresp) - माप(uresp.reserved));
		अगर (ret)
			जाओ err_mm;

		mm->key = uresp.status_page_key;
		mm->addr = virt_to_phys(rhp->rdev.status_page);
		mm->len = PAGE_SIZE;
		insert_mmap(context, mm);
	पूर्ण
	वापस 0;
err_mm:
	kमुक्त(mm);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक c4iw_mmap(काष्ठा ib_ucontext *context, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक len = vma->vm_end - vma->vm_start;
	u32 key = vma->vm_pgoff << PAGE_SHIFT;
	काष्ठा c4iw_rdev *rdev;
	पूर्णांक ret = 0;
	काष्ठा c4iw_mm_entry *mm;
	काष्ठा c4iw_ucontext *ucontext;
	u64 addr;

	pr_debug("pgoff 0x%lx key 0x%x len %d\n", vma->vm_pgoff,
		 key, len);

	अगर (vma->vm_start & (PAGE_SIZE-1))
		वापस -EINVAL;

	rdev = &(to_c4iw_dev(context->device)->rdev);
	ucontext = to_c4iw_ucontext(context);

	mm = हटाओ_mmap(ucontext, key, len);
	अगर (!mm)
		वापस -EINVAL;
	addr = mm->addr;
	kमुक्त(mm);

	अगर ((addr >= pci_resource_start(rdev->lldi.pdev, 0)) &&
	    (addr < (pci_resource_start(rdev->lldi.pdev, 0) +
		    pci_resource_len(rdev->lldi.pdev, 0)))) अणु

		/*
		 * MA_SYNC रेजिस्टर...
		 */
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
		ret = io_remap_pfn_range(vma, vma->vm_start,
					 addr >> PAGE_SHIFT,
					 len, vma->vm_page_prot);
	पूर्ण अन्यथा अगर ((addr >= pci_resource_start(rdev->lldi.pdev, 2)) &&
		   (addr < (pci_resource_start(rdev->lldi.pdev, 2) +
		    pci_resource_len(rdev->lldi.pdev, 2)))) अणु

		/*
		 * Map user DB or OCQP memory...
		 */
		अगर (addr >= rdev->oc_mw_pa)
			vma->vm_page_prot = t4_pgprot_wc(vma->vm_page_prot);
		अन्यथा अणु
			अगर (!is_t4(rdev->lldi.adapter_type))
				vma->vm_page_prot =
					t4_pgprot_wc(vma->vm_page_prot);
			अन्यथा
				vma->vm_page_prot =
					pgprot_noncached(vma->vm_page_prot);
		पूर्ण
		ret = io_remap_pfn_range(vma, vma->vm_start,
					 addr >> PAGE_SHIFT,
					 len, vma->vm_page_prot);
	पूर्ण अन्यथा अणु

		/*
		 * Map WQ or CQ contig dma memory...
		 */
		ret = remap_pfn_range(vma, vma->vm_start,
				      addr >> PAGE_SHIFT,
				      len, vma->vm_page_prot);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक c4iw_deallocate_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata)
अणु
	काष्ठा c4iw_dev *rhp;
	काष्ठा c4iw_pd *php;

	php = to_c4iw_pd(pd);
	rhp = php->rhp;
	pr_debug("ibpd %p pdid 0x%x\n", pd, php->pdid);
	c4iw_put_resource(&rhp->rdev.resource.pdid_table, php->pdid);
	mutex_lock(&rhp->rdev.stats.lock);
	rhp->rdev.stats.pd.cur--;
	mutex_unlock(&rhp->rdev.stats.lock);
	वापस 0;
पूर्ण

अटल पूर्णांक c4iw_allocate_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata)
अणु
	काष्ठा c4iw_pd *php = to_c4iw_pd(pd);
	काष्ठा ib_device *ibdev = pd->device;
	u32 pdid;
	काष्ठा c4iw_dev *rhp;

	pr_debug("ibdev %p\n", ibdev);
	rhp = (काष्ठा c4iw_dev *) ibdev;
	pdid =  c4iw_get_resource(&rhp->rdev.resource.pdid_table);
	अगर (!pdid)
		वापस -EINVAL;

	php->pdid = pdid;
	php->rhp = rhp;
	अगर (udata) अणु
		काष्ठा c4iw_alloc_pd_resp uresp = अणु.pdid = php->pdidपूर्ण;

		अगर (ib_copy_to_udata(udata, &uresp, माप(uresp))) अणु
			c4iw_deallocate_pd(&php->ibpd, udata);
			वापस -EFAULT;
		पूर्ण
	पूर्ण
	mutex_lock(&rhp->rdev.stats.lock);
	rhp->rdev.stats.pd.cur++;
	अगर (rhp->rdev.stats.pd.cur > rhp->rdev.stats.pd.max)
		rhp->rdev.stats.pd.max = rhp->rdev.stats.pd.cur;
	mutex_unlock(&rhp->rdev.stats.lock);
	pr_debug("pdid 0x%0x ptr 0x%p\n", pdid, php);
	वापस 0;
पूर्ण

अटल पूर्णांक c4iw_query_gid(काष्ठा ib_device *ibdev, u32 port, पूर्णांक index,
			  जोड़ ib_gid *gid)
अणु
	काष्ठा c4iw_dev *dev;

	pr_debug("ibdev %p, port %u, index %d, gid %p\n",
		 ibdev, port, index, gid);
	अगर (!port)
		वापस -EINVAL;
	dev = to_c4iw_dev(ibdev);
	स_रखो(&(gid->raw[0]), 0, माप(gid->raw));
	स_नकल(&(gid->raw[0]), dev->rdev.lldi.ports[port-1]->dev_addr, 6);
	वापस 0;
पूर्ण

अटल पूर्णांक c4iw_query_device(काष्ठा ib_device *ibdev, काष्ठा ib_device_attr *props,
			     काष्ठा ib_udata *uhw)
अणु

	काष्ठा c4iw_dev *dev;

	pr_debug("ibdev %p\n", ibdev);

	अगर (uhw->inlen || uhw->outlen)
		वापस -EINVAL;

	dev = to_c4iw_dev(ibdev);
	स_नकल(&props->sys_image_guid, dev->rdev.lldi.ports[0]->dev_addr, 6);
	props->hw_ver = CHELSIO_CHIP_RELEASE(dev->rdev.lldi.adapter_type);
	props->fw_ver = dev->rdev.lldi.fw_vers;
	props->device_cap_flags = dev->device_cap_flags;
	props->page_size_cap = T4_PAGESIZE_MASK;
	props->venकरोr_id = (u32)dev->rdev.lldi.pdev->venकरोr;
	props->venकरोr_part_id = (u32)dev->rdev.lldi.pdev->device;
	props->max_mr_size = T4_MAX_MR_SIZE;
	props->max_qp = dev->rdev.lldi.vr->qp.size / 2;
	props->max_srq = dev->rdev.lldi.vr->srq.size;
	props->max_qp_wr = dev->rdev.hw_queue.t4_max_qp_depth;
	props->max_srq_wr = dev->rdev.hw_queue.t4_max_qp_depth;
	props->max_send_sge = min(T4_MAX_SEND_SGE, T4_MAX_WRITE_SGE);
	props->max_recv_sge = T4_MAX_RECV_SGE;
	props->max_srq_sge = T4_MAX_RECV_SGE;
	props->max_sge_rd = 1;
	props->max_res_rd_atom = dev->rdev.lldi.max_ird_adapter;
	props->max_qp_rd_atom = min(dev->rdev.lldi.max_ordird_qp,
				    c4iw_max_पढ़ो_depth);
	props->max_qp_init_rd_atom = props->max_qp_rd_atom;
	props->max_cq = dev->rdev.lldi.vr->qp.size;
	props->max_cqe = dev->rdev.hw_queue.t4_max_cq_depth;
	props->max_mr = c4iw_num_stags(&dev->rdev);
	props->max_pd = T4_MAX_NUM_PD;
	props->local_ca_ack_delay = 0;
	props->max_fast_reg_page_list_len =
		t4_max_fr_depth(dev->rdev.lldi.ulptx_memग_लिखो_dsgl && use_dsgl);

	वापस 0;
पूर्ण

अटल पूर्णांक c4iw_query_port(काष्ठा ib_device *ibdev, u32 port,
			   काष्ठा ib_port_attr *props)
अणु
	पूर्णांक ret = 0;
	pr_debug("ibdev %p\n", ibdev);
	ret = ib_get_eth_speed(ibdev, port, &props->active_speed,
			       &props->active_width);

	props->port_cap_flags =
	    IB_PORT_CM_SUP |
	    IB_PORT_SNMP_TUNNEL_SUP |
	    IB_PORT_REINIT_SUP |
	    IB_PORT_DEVICE_MGMT_SUP |
	    IB_PORT_VENDOR_CLASS_SUP | IB_PORT_BOOT_MGMT_SUP;
	props->gid_tbl_len = 1;
	props->max_msg_sz = -1;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार hw_rev_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा c4iw_dev *c4iw_dev =
			rdma_device_to_drv_device(dev, काष्ठा c4iw_dev, ibdev);

	pr_debug("dev 0x%p\n", dev);
	वापस sysfs_emit(
		buf, "%d\n",
		CHELSIO_CHIP_RELEASE(c4iw_dev->rdev.lldi.adapter_type));
पूर्ण
अटल DEVICE_ATTR_RO(hw_rev);

अटल sमाप_प्रकार hca_type_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा c4iw_dev *c4iw_dev =
			rdma_device_to_drv_device(dev, काष्ठा c4iw_dev, ibdev);
	काष्ठा ethtool_drvinfo info;
	काष्ठा net_device *lldev = c4iw_dev->rdev.lldi.ports[0];

	pr_debug("dev 0x%p\n", dev);
	lldev->ethtool_ops->get_drvinfo(lldev, &info);
	वापस sysfs_emit(buf, "%s\n", info.driver);
पूर्ण
अटल DEVICE_ATTR_RO(hca_type);

अटल sमाप_प्रकार board_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा c4iw_dev *c4iw_dev =
			rdma_device_to_drv_device(dev, काष्ठा c4iw_dev, ibdev);

	pr_debug("dev 0x%p\n", dev);
	वापस sysfs_emit(buf, "%x.%x\n", c4iw_dev->rdev.lldi.pdev->venकरोr,
			  c4iw_dev->rdev.lldi.pdev->device);
पूर्ण
अटल DEVICE_ATTR_RO(board_id);

क्रमागत counters अणु
	IP4INSEGS,
	IP4OUTSEGS,
	IP4RETRANSSEGS,
	IP4OUTRSTS,
	IP6INSEGS,
	IP6OUTSEGS,
	IP6RETRANSSEGS,
	IP6OUTRSTS,
	NR_COUNTERS
पूर्ण;

अटल स्थिर अक्षर * स्थिर names[] = अणु
	[IP4INSEGS] = "ip4InSegs",
	[IP4OUTSEGS] = "ip4OutSegs",
	[IP4RETRANSSEGS] = "ip4RetransSegs",
	[IP4OUTRSTS] = "ip4OutRsts",
	[IP6INSEGS] = "ip6InSegs",
	[IP6OUTSEGS] = "ip6OutSegs",
	[IP6RETRANSSEGS] = "ip6RetransSegs",
	[IP6OUTRSTS] = "ip6OutRsts"
पूर्ण;

अटल काष्ठा rdma_hw_stats *c4iw_alloc_stats(काष्ठा ib_device *ibdev,
					      u32 port_num)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(names) != NR_COUNTERS);

	अगर (port_num != 0)
		वापस शून्य;

	वापस rdma_alloc_hw_stats_काष्ठा(names, NR_COUNTERS,
					  RDMA_HW_STATS_DEFAULT_LIFESPAN);
पूर्ण

अटल पूर्णांक c4iw_get_mib(काष्ठा ib_device *ibdev,
			काष्ठा rdma_hw_stats *stats,
			u32 port, पूर्णांक index)
अणु
	काष्ठा tp_tcp_stats v4, v6;
	काष्ठा c4iw_dev *c4iw_dev = to_c4iw_dev(ibdev);

	cxgb4_get_tcp_stats(c4iw_dev->rdev.lldi.pdev, &v4, &v6);
	stats->value[IP4INSEGS] = v4.tcp_in_segs;
	stats->value[IP4OUTSEGS] = v4.tcp_out_segs;
	stats->value[IP4RETRANSSEGS] = v4.tcp_retrans_segs;
	stats->value[IP4OUTRSTS] = v4.tcp_out_rsts;
	stats->value[IP6INSEGS] = v6.tcp_in_segs;
	stats->value[IP6OUTSEGS] = v6.tcp_out_segs;
	stats->value[IP6RETRANSSEGS] = v6.tcp_retrans_segs;
	stats->value[IP6OUTRSTS] = v6.tcp_out_rsts;

	वापस stats->num_counters;
पूर्ण

अटल काष्ठा attribute *c4iw_class_attributes[] = अणु
	&dev_attr_hw_rev.attr,
	&dev_attr_hca_type.attr,
	&dev_attr_board_id.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group c4iw_attr_group = अणु
	.attrs = c4iw_class_attributes,
पूर्ण;

अटल पूर्णांक c4iw_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
			       काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा ib_port_attr attr;
	पूर्णांक err;

	immutable->core_cap_flags = RDMA_CORE_PORT_IWARP;

	err = ib_query_port(ibdev, port_num, &attr);
	अगर (err)
		वापस err;

	immutable->gid_tbl_len = attr.gid_tbl_len;

	वापस 0;
पूर्ण

अटल व्योम get_dev_fw_str(काष्ठा ib_device *dev, अक्षर *str)
अणु
	काष्ठा c4iw_dev *c4iw_dev = container_of(dev, काष्ठा c4iw_dev,
						 ibdev);
	pr_debug("dev 0x%p\n", dev);

	snम_लिखो(str, IB_FW_VERSION_NAME_MAX, "%u.%u.%u.%u",
		 FW_HDR_FW_VER_MAJOR_G(c4iw_dev->rdev.lldi.fw_vers),
		 FW_HDR_FW_VER_MINOR_G(c4iw_dev->rdev.lldi.fw_vers),
		 FW_HDR_FW_VER_MICRO_G(c4iw_dev->rdev.lldi.fw_vers),
		 FW_HDR_FW_VER_BUILD_G(c4iw_dev->rdev.lldi.fw_vers));
पूर्ण

अटल स्थिर काष्ठा ib_device_ops c4iw_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_CXGB4,
	.uverbs_abi_ver = C4IW_UVERBS_ABI_VERSION,

	.alloc_hw_stats = c4iw_alloc_stats,
	.alloc_mr = c4iw_alloc_mr,
	.alloc_pd = c4iw_allocate_pd,
	.alloc_ucontext = c4iw_alloc_ucontext,
	.create_cq = c4iw_create_cq,
	.create_qp = c4iw_create_qp,
	.create_srq = c4iw_create_srq,
	.dealloc_pd = c4iw_deallocate_pd,
	.dealloc_ucontext = c4iw_dealloc_ucontext,
	.dereg_mr = c4iw_dereg_mr,
	.destroy_cq = c4iw_destroy_cq,
	.destroy_qp = c4iw_destroy_qp,
	.destroy_srq = c4iw_destroy_srq,
	.fill_res_cq_entry = c4iw_fill_res_cq_entry,
	.fill_res_cm_id_entry = c4iw_fill_res_cm_id_entry,
	.fill_res_mr_entry = c4iw_fill_res_mr_entry,
	.get_dev_fw_str = get_dev_fw_str,
	.get_dma_mr = c4iw_get_dma_mr,
	.get_hw_stats = c4iw_get_mib,
	.get_port_immutable = c4iw_port_immutable,
	.iw_accept = c4iw_accept_cr,
	.iw_add_ref = c4iw_qp_add_ref,
	.iw_connect = c4iw_connect,
	.iw_create_listen = c4iw_create_listen,
	.iw_destroy_listen = c4iw_destroy_listen,
	.iw_get_qp = c4iw_get_qp,
	.iw_reject = c4iw_reject_cr,
	.iw_rem_ref = c4iw_qp_rem_ref,
	.map_mr_sg = c4iw_map_mr_sg,
	.mmap = c4iw_mmap,
	.modअगरy_qp = c4iw_ib_modअगरy_qp,
	.modअगरy_srq = c4iw_modअगरy_srq,
	.poll_cq = c4iw_poll_cq,
	.post_recv = c4iw_post_receive,
	.post_send = c4iw_post_send,
	.post_srq_recv = c4iw_post_srq_recv,
	.query_device = c4iw_query_device,
	.query_gid = c4iw_query_gid,
	.query_port = c4iw_query_port,
	.query_qp = c4iw_ib_query_qp,
	.reg_user_mr = c4iw_reg_user_mr,
	.req_notअगरy_cq = c4iw_arm_cq,

	INIT_RDMA_OBJ_SIZE(ib_cq, c4iw_cq, ibcq),
	INIT_RDMA_OBJ_SIZE(ib_mw, c4iw_mw, ibmw),
	INIT_RDMA_OBJ_SIZE(ib_pd, c4iw_pd, ibpd),
	INIT_RDMA_OBJ_SIZE(ib_srq, c4iw_srq, ibsrq),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, c4iw_ucontext, ibucontext),
पूर्ण;

अटल पूर्णांक set_netdevs(काष्ठा ib_device *ib_dev, काष्ठा c4iw_rdev *rdev)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < rdev->lldi.nports; i++) अणु
		ret = ib_device_set_netdev(ib_dev, rdev->lldi.ports[i],
					   i + 1);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

व्योम c4iw_रेजिस्टर_device(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा uld_ctx *ctx = container_of(work, काष्ठा uld_ctx, reg_work);
	काष्ठा c4iw_dev *dev = ctx->dev;

	pr_debug("c4iw_dev %p\n", dev);
	स_रखो(&dev->ibdev.node_guid, 0, माप(dev->ibdev.node_guid));
	स_नकल(&dev->ibdev.node_guid, dev->rdev.lldi.ports[0]->dev_addr, 6);
	dev->device_cap_flags = IB_DEVICE_LOCAL_DMA_LKEY | IB_DEVICE_MEM_WINDOW;
	अगर (fastreg_support)
		dev->device_cap_flags |= IB_DEVICE_MEM_MGT_EXTENSIONS;
	dev->ibdev.local_dma_lkey = 0;
	dev->ibdev.node_type = RDMA_NODE_RNIC;
	BUILD_BUG_ON(माप(C4IW_NODE_DESC) > IB_DEVICE_NODE_DESC_MAX);
	स_नकल(dev->ibdev.node_desc, C4IW_NODE_DESC, माप(C4IW_NODE_DESC));
	dev->ibdev.phys_port_cnt = dev->rdev.lldi.nports;
	dev->ibdev.num_comp_vectors =  dev->rdev.lldi.nciq;
	dev->ibdev.dev.parent = &dev->rdev.lldi.pdev->dev;

	स_नकल(dev->ibdev.iw_अगरname, dev->rdev.lldi.ports[0]->name,
	       माप(dev->ibdev.iw_अगरname));

	rdma_set_device_sysfs_group(&dev->ibdev, &c4iw_attr_group);
	ib_set_device_ops(&dev->ibdev, &c4iw_dev_ops);
	ret = set_netdevs(&dev->ibdev, &dev->rdev);
	अगर (ret)
		जाओ err_dealloc_ctx;
	dma_set_max_seg_size(&dev->rdev.lldi.pdev->dev, अच_पूर्णांक_उच्च);
	ret = ib_रेजिस्टर_device(&dev->ibdev, "cxgb4_%d",
				 &dev->rdev.lldi.pdev->dev);
	अगर (ret)
		जाओ err_dealloc_ctx;
	वापस;

err_dealloc_ctx:
	pr_err("%s - Failed registering iwarp device: %d\n",
	       pci_name(ctx->lldi.pdev), ret);
	c4iw_dealloc(ctx);
	वापस;
पूर्ण

व्योम c4iw_unरेजिस्टर_device(काष्ठा c4iw_dev *dev)
अणु
	pr_debug("c4iw_dev %p\n", dev);
	ib_unरेजिस्टर_device(&dev->ibdev);
	वापस;
पूर्ण
