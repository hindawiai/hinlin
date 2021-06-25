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
 * Author: Upinder Malhi <umalhi@cisco.com>
 * Author: Anant Deepak <anadeepa@cisco.com>
 * Author: Cesare Cantu' <cantuc@cisco.com>
 * Author: Jeff Squyres <jsquyres@cisco.com>
 * Author: Kiran Thirumalai <kithirum@cisco.com>
 * Author: Xuyang Wang <xuywang@cisco.com>
 * Author: Reese Faucette <rfaucett@cisco.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>

#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_addr.h>

#समावेश "usnic_abi.h"
#समावेश "usnic_common_util.h"
#समावेश "usnic_ib.h"
#समावेश "usnic_ib_qp_grp.h"
#समावेश "usnic_log.h"
#समावेश "usnic_fwd.h"
#समावेश "usnic_debugfs.h"
#समावेश "usnic_ib_verbs.h"
#समावेश "usnic_transport.h"
#समावेश "usnic_uiom.h"
#समावेश "usnic_ib_sysfs.h"

अचिन्हित पूर्णांक usnic_log_lvl = USNIC_LOG_LVL_ERR;
अचिन्हित पूर्णांक usnic_ib_share_vf = 1;

अटल स्थिर अक्षर usnic_version[] =
	DRV_NAME ": Cisco VIC (USNIC) Verbs Driver v"
	DRV_VERSION " (" DRV_RELDATE ")\n";

अटल DEFINE_MUTEX(usnic_ib_ibdev_list_lock);
अटल LIST_HEAD(usnic_ib_ibdev_list);

/* Callback dump funcs */
अटल पूर्णांक usnic_ib_dump_vf_hdr(व्योम *obj, अक्षर *buf, पूर्णांक buf_sz)
अणु
	काष्ठा usnic_ib_vf *vf = obj;
	वापस scnम_लिखो(buf, buf_sz, "PF: %s ", dev_name(&vf->pf->ib_dev.dev));
पूर्ण
/* End callback dump funcs */

अटल व्योम usnic_ib_dump_vf(काष्ठा usnic_ib_vf *vf, अक्षर *buf, पूर्णांक buf_sz)
अणु
	usnic_vnic_dump(vf->vnic, buf, buf_sz, vf,
			usnic_ib_dump_vf_hdr,
			usnic_ib_qp_grp_dump_hdr, usnic_ib_qp_grp_dump_rows);
पूर्ण

व्योम usnic_ib_log_vf(काष्ठा usnic_ib_vf *vf)
अणु
	अक्षर *buf = kzalloc(1000, GFP_KERNEL);

	अगर (!buf)
		वापस;

	usnic_ib_dump_vf(vf, buf, 1000);
	usnic_dbg("%s\n", buf);

	kमुक्त(buf);
पूर्ण

/* Start of netdev section */
अटल व्योम usnic_ib_qp_grp_modअगरy_active_to_err(काष्ठा usnic_ib_dev *us_ibdev)
अणु
	काष्ठा usnic_ib_ucontext *ctx;
	काष्ठा usnic_ib_qp_grp *qp_grp;
	क्रमागत ib_qp_state cur_state;
	पूर्णांक status;

	BUG_ON(!mutex_is_locked(&us_ibdev->usdev_lock));

	list_क्रम_each_entry(ctx, &us_ibdev->ctx_list, link) अणु
		list_क्रम_each_entry(qp_grp, &ctx->qp_grp_list, link) अणु
			cur_state = qp_grp->state;
			अगर (cur_state == IB_QPS_INIT ||
				cur_state == IB_QPS_RTR ||
				cur_state == IB_QPS_RTS) अणु
				status = usnic_ib_qp_grp_modअगरy(qp_grp,
								IB_QPS_ERR,
								शून्य);
				अगर (status) अणु
					usnic_err("Failed to transition qp grp %u from %s to %s\n",
						qp_grp->grp_id,
						usnic_ib_qp_grp_state_to_string
						(cur_state),
						usnic_ib_qp_grp_state_to_string
						(IB_QPS_ERR));
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usnic_ib_handle_usdev_event(काष्ठा usnic_ib_dev *us_ibdev,
					अचिन्हित दीर्घ event)
अणु
	काष्ठा net_device *netdev;
	काष्ठा ib_event ib_event;

	स_रखो(&ib_event, 0, माप(ib_event));

	mutex_lock(&us_ibdev->usdev_lock);
	netdev = us_ibdev->netdev;
	चयन (event) अणु
	हाल NETDEV_REBOOT:
		usnic_info("PF Reset on %s\n", dev_name(&us_ibdev->ib_dev.dev));
		usnic_ib_qp_grp_modअगरy_active_to_err(us_ibdev);
		ib_event.event = IB_EVENT_PORT_ERR;
		ib_event.device = &us_ibdev->ib_dev;
		ib_event.element.port_num = 1;
		ib_dispatch_event(&ib_event);
		अवरोध;
	हाल NETDEV_UP:
	हाल NETDEV_DOWN:
	हाल NETDEV_CHANGE:
		अगर (!us_ibdev->ufdev->link_up &&
				netअगर_carrier_ok(netdev)) अणु
			usnic_fwd_carrier_up(us_ibdev->ufdev);
			usnic_info("Link UP on %s\n",
				   dev_name(&us_ibdev->ib_dev.dev));
			ib_event.event = IB_EVENT_PORT_ACTIVE;
			ib_event.device = &us_ibdev->ib_dev;
			ib_event.element.port_num = 1;
			ib_dispatch_event(&ib_event);
		पूर्ण अन्यथा अगर (us_ibdev->ufdev->link_up &&
				!netअगर_carrier_ok(netdev)) अणु
			usnic_fwd_carrier_करोwn(us_ibdev->ufdev);
			usnic_info("Link DOWN on %s\n",
				   dev_name(&us_ibdev->ib_dev.dev));
			usnic_ib_qp_grp_modअगरy_active_to_err(us_ibdev);
			ib_event.event = IB_EVENT_PORT_ERR;
			ib_event.device = &us_ibdev->ib_dev;
			ib_event.element.port_num = 1;
			ib_dispatch_event(&ib_event);
		पूर्ण अन्यथा अणु
			usnic_dbg("Ignoring %s on %s\n",
					netdev_cmd_to_name(event),
					dev_name(&us_ibdev->ib_dev.dev));
		पूर्ण
		अवरोध;
	हाल NETDEV_CHANGEADDR:
		अगर (!स_भेद(us_ibdev->ufdev->mac, netdev->dev_addr,
				माप(us_ibdev->ufdev->mac))) अणु
			usnic_dbg("Ignoring addr change on %s\n",
				  dev_name(&us_ibdev->ib_dev.dev));
		पूर्ण अन्यथा अणु
			usnic_info(" %s old mac: %pM new mac: %pM\n",
					dev_name(&us_ibdev->ib_dev.dev),
					us_ibdev->ufdev->mac,
					netdev->dev_addr);
			usnic_fwd_set_mac(us_ibdev->ufdev, netdev->dev_addr);
			usnic_ib_qp_grp_modअगरy_active_to_err(us_ibdev);
			ib_event.event = IB_EVENT_GID_CHANGE;
			ib_event.device = &us_ibdev->ib_dev;
			ib_event.element.port_num = 1;
			ib_dispatch_event(&ib_event);
		पूर्ण

		अवरोध;
	हाल NETDEV_CHANGEMTU:
		अगर (us_ibdev->ufdev->mtu != netdev->mtu) अणु
			usnic_info("MTU Change on %s old: %u new: %u\n",
					dev_name(&us_ibdev->ib_dev.dev),
					us_ibdev->ufdev->mtu, netdev->mtu);
			usnic_fwd_set_mtu(us_ibdev->ufdev, netdev->mtu);
			usnic_ib_qp_grp_modअगरy_active_to_err(us_ibdev);
		पूर्ण अन्यथा अणु
			usnic_dbg("Ignoring MTU change on %s\n",
				  dev_name(&us_ibdev->ib_dev.dev));
		पूर्ण
		अवरोध;
	शेष:
		usnic_dbg("Ignoring event %s on %s",
				netdev_cmd_to_name(event),
				dev_name(&us_ibdev->ib_dev.dev));
	पूर्ण
	mutex_unlock(&us_ibdev->usdev_lock);
पूर्ण

अटल पूर्णांक usnic_ib_netdevice_event(काष्ठा notअगरier_block *notअगरier,
					अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा usnic_ib_dev *us_ibdev;
	काष्ठा ib_device *ibdev;

	काष्ठा net_device *netdev = netdev_notअगरier_info_to_dev(ptr);

	ibdev = ib_device_get_by_netdev(netdev, RDMA_DRIVER_USNIC);
	अगर (!ibdev)
		वापस NOTIFY_DONE;

	us_ibdev = container_of(ibdev, काष्ठा usnic_ib_dev, ib_dev);
	usnic_ib_handle_usdev_event(us_ibdev, event);
	ib_device_put(ibdev);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block usnic_ib_netdevice_notअगरier = अणु
	.notअगरier_call = usnic_ib_netdevice_event
पूर्ण;
/* End of netdev section */

/* Start of inet section */
अटल पूर्णांक usnic_ib_handle_inet_event(काष्ठा usnic_ib_dev *us_ibdev,
					अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा in_अगरaddr *अगरa = ptr;
	काष्ठा ib_event ib_event;

	mutex_lock(&us_ibdev->usdev_lock);

	चयन (event) अणु
	हाल NETDEV_DOWN:
		usnic_info("%s via ip notifiers",
				netdev_cmd_to_name(event));
		usnic_fwd_del_ipaddr(us_ibdev->ufdev);
		usnic_ib_qp_grp_modअगरy_active_to_err(us_ibdev);
		ib_event.event = IB_EVENT_GID_CHANGE;
		ib_event.device = &us_ibdev->ib_dev;
		ib_event.element.port_num = 1;
		ib_dispatch_event(&ib_event);
		अवरोध;
	हाल NETDEV_UP:
		usnic_fwd_add_ipaddr(us_ibdev->ufdev, अगरa->अगरa_address);
		usnic_info("%s via ip notifiers: ip %pI4",
				netdev_cmd_to_name(event),
				&us_ibdev->ufdev->inaddr);
		ib_event.event = IB_EVENT_GID_CHANGE;
		ib_event.device = &us_ibdev->ib_dev;
		ib_event.element.port_num = 1;
		ib_dispatch_event(&ib_event);
		अवरोध;
	शेष:
		usnic_info("Ignoring event %s on %s",
				netdev_cmd_to_name(event),
				dev_name(&us_ibdev->ib_dev.dev));
	पूर्ण
	mutex_unlock(&us_ibdev->usdev_lock);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक usnic_ib_inetaddr_event(काष्ठा notअगरier_block *notअगरier,
					अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा usnic_ib_dev *us_ibdev;
	काष्ठा in_अगरaddr *अगरa = ptr;
	काष्ठा net_device *netdev = अगरa->अगरa_dev->dev;
	काष्ठा ib_device *ibdev;

	ibdev = ib_device_get_by_netdev(netdev, RDMA_DRIVER_USNIC);
	अगर (!ibdev)
		वापस NOTIFY_DONE;

	us_ibdev = container_of(ibdev, काष्ठा usnic_ib_dev, ib_dev);
	usnic_ib_handle_inet_event(us_ibdev, event, ptr);
	ib_device_put(ibdev);
	वापस NOTIFY_DONE;
पूर्ण
अटल काष्ठा notअगरier_block usnic_ib_inetaddr_notअगरier = अणु
	.notअगरier_call = usnic_ib_inetaddr_event
पूर्ण;
/* End of inet section*/

अटल पूर्णांक usnic_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
			        काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा ib_port_attr attr;
	पूर्णांक err;

	immutable->core_cap_flags = RDMA_CORE_PORT_USNIC;

	err = ib_query_port(ibdev, port_num, &attr);
	अगर (err)
		वापस err;

	immutable->gid_tbl_len = attr.gid_tbl_len;

	वापस 0;
पूर्ण

अटल व्योम usnic_get_dev_fw_str(काष्ठा ib_device *device, अक्षर *str)
अणु
	काष्ठा usnic_ib_dev *us_ibdev =
		container_of(device, काष्ठा usnic_ib_dev, ib_dev);
	काष्ठा ethtool_drvinfo info;

	mutex_lock(&us_ibdev->usdev_lock);
	us_ibdev->netdev->ethtool_ops->get_drvinfo(us_ibdev->netdev, &info);
	mutex_unlock(&us_ibdev->usdev_lock);

	snम_लिखो(str, IB_FW_VERSION_NAME_MAX, "%s", info.fw_version);
पूर्ण

अटल स्थिर काष्ठा ib_device_ops usnic_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_USNIC,
	.uverbs_abi_ver = USNIC_UVERBS_ABI_VERSION,

	.alloc_pd = usnic_ib_alloc_pd,
	.alloc_ucontext = usnic_ib_alloc_ucontext,
	.create_cq = usnic_ib_create_cq,
	.create_qp = usnic_ib_create_qp,
	.dealloc_pd = usnic_ib_dealloc_pd,
	.dealloc_ucontext = usnic_ib_dealloc_ucontext,
	.dereg_mr = usnic_ib_dereg_mr,
	.destroy_cq = usnic_ib_destroy_cq,
	.destroy_qp = usnic_ib_destroy_qp,
	.get_dev_fw_str = usnic_get_dev_fw_str,
	.get_link_layer = usnic_ib_port_link_layer,
	.get_port_immutable = usnic_port_immutable,
	.mmap = usnic_ib_mmap,
	.modअगरy_qp = usnic_ib_modअगरy_qp,
	.query_device = usnic_ib_query_device,
	.query_gid = usnic_ib_query_gid,
	.query_port = usnic_ib_query_port,
	.query_qp = usnic_ib_query_qp,
	.reg_user_mr = usnic_ib_reg_mr,
	INIT_RDMA_OBJ_SIZE(ib_pd, usnic_ib_pd, ibpd),
	INIT_RDMA_OBJ_SIZE(ib_cq, usnic_ib_cq, ibcq),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, usnic_ib_ucontext, ibucontext),
पूर्ण;

/* Start of PF discovery section */
अटल व्योम *usnic_ib_device_add(काष्ठा pci_dev *dev)
अणु
	काष्ठा usnic_ib_dev *us_ibdev;
	जोड़ ib_gid gid;
	काष्ठा in_device *ind;
	काष्ठा net_device *netdev;
	पूर्णांक ret;

	usnic_dbg("\n");
	netdev = pci_get_drvdata(dev);

	us_ibdev = ib_alloc_device(usnic_ib_dev, ib_dev);
	अगर (!us_ibdev) अणु
		usnic_err("Device %s context alloc failed\n",
				netdev_name(pci_get_drvdata(dev)));
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	us_ibdev->ufdev = usnic_fwd_dev_alloc(dev);
	अगर (!us_ibdev->ufdev) अणु
		usnic_err("Failed to alloc ufdev for %s\n", pci_name(dev));
		जाओ err_dealloc;
	पूर्ण

	mutex_init(&us_ibdev->usdev_lock);
	INIT_LIST_HEAD(&us_ibdev->vf_dev_list);
	INIT_LIST_HEAD(&us_ibdev->ctx_list);

	us_ibdev->pdev = dev;
	us_ibdev->netdev = pci_get_drvdata(dev);
	us_ibdev->ib_dev.node_type = RDMA_NODE_USNIC_UDP;
	us_ibdev->ib_dev.phys_port_cnt = USNIC_IB_PORT_CNT;
	us_ibdev->ib_dev.num_comp_vectors = USNIC_IB_NUM_COMP_VECTORS;
	us_ibdev->ib_dev.dev.parent = &dev->dev;

	ib_set_device_ops(&us_ibdev->ib_dev, &usnic_dev_ops);

	rdma_set_device_sysfs_group(&us_ibdev->ib_dev, &usnic_attr_group);

	ret = ib_device_set_netdev(&us_ibdev->ib_dev, us_ibdev->netdev, 1);
	अगर (ret)
		जाओ err_fwd_dealloc;

	dma_set_max_seg_size(&dev->dev, SZ_2G);
	अगर (ib_रेजिस्टर_device(&us_ibdev->ib_dev, "usnic_%d", &dev->dev))
		जाओ err_fwd_dealloc;

	usnic_fwd_set_mtu(us_ibdev->ufdev, us_ibdev->netdev->mtu);
	usnic_fwd_set_mac(us_ibdev->ufdev, us_ibdev->netdev->dev_addr);
	अगर (netअगर_carrier_ok(us_ibdev->netdev))
		usnic_fwd_carrier_up(us_ibdev->ufdev);

	rcu_पढ़ो_lock();
	ind = __in_dev_get_rcu(netdev);
	अगर (ind) अणु
		स्थिर काष्ठा in_अगरaddr *अगरa;

		अगरa = rcu_dereference(ind->अगरa_list);
		अगर (अगरa)
			usnic_fwd_add_ipaddr(us_ibdev->ufdev, अगरa->अगरa_address);
	पूर्ण
	rcu_पढ़ो_unlock();

	usnic_mac_ip_to_gid(us_ibdev->netdev->perm_addr,
				us_ibdev->ufdev->inaddr, &gid.raw[0]);
	स_नकल(&us_ibdev->ib_dev.node_guid, &gid.global.पूर्णांकerface_id,
		माप(gid.global.पूर्णांकerface_id));
	kref_init(&us_ibdev->vf_cnt);

	usnic_info("Added ibdev: %s netdev: %s with mac %pM Link: %u MTU: %u\n",
		   dev_name(&us_ibdev->ib_dev.dev),
		   netdev_name(us_ibdev->netdev), us_ibdev->ufdev->mac,
		   us_ibdev->ufdev->link_up, us_ibdev->ufdev->mtu);
	वापस us_ibdev;

err_fwd_dealloc:
	usnic_fwd_dev_मुक्त(us_ibdev->ufdev);
err_dealloc:
	usnic_err("failed -- deallocing device\n");
	ib_dealloc_device(&us_ibdev->ib_dev);
	वापस शून्य;
पूर्ण

अटल व्योम usnic_ib_device_हटाओ(काष्ठा usnic_ib_dev *us_ibdev)
अणु
	usnic_info("Unregistering %s\n", dev_name(&us_ibdev->ib_dev.dev));
	usnic_ib_sysfs_unरेजिस्टर_usdev(us_ibdev);
	usnic_fwd_dev_मुक्त(us_ibdev->ufdev);
	ib_unरेजिस्टर_device(&us_ibdev->ib_dev);
	ib_dealloc_device(&us_ibdev->ib_dev);
पूर्ण

अटल व्योम usnic_ib_undiscover_pf(काष्ठा kref *kref)
अणु
	काष्ठा usnic_ib_dev *us_ibdev, *पंचांगp;
	काष्ठा pci_dev *dev;
	bool found = false;

	dev = container_of(kref, काष्ठा usnic_ib_dev, vf_cnt)->pdev;
	mutex_lock(&usnic_ib_ibdev_list_lock);
	list_क्रम_each_entry_safe(us_ibdev, पंचांगp,
				&usnic_ib_ibdev_list, ib_dev_link) अणु
		अगर (us_ibdev->pdev == dev) अणु
			list_del(&us_ibdev->ib_dev_link);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण


	mutex_unlock(&usnic_ib_ibdev_list_lock);
	अगर (found)
		usnic_ib_device_हटाओ(us_ibdev);
	अन्यथा
		WARN(1, "Failed to remove PF %s\n", pci_name(dev));
पूर्ण

अटल काष्ठा usnic_ib_dev *usnic_ib_discover_pf(काष्ठा usnic_vnic *vnic)
अणु
	काष्ठा usnic_ib_dev *us_ibdev;
	काष्ठा pci_dev *parent_pci, *vf_pci;
	पूर्णांक err;

	vf_pci = usnic_vnic_get_pdev(vnic);
	parent_pci = pci_physfn(vf_pci);

	BUG_ON(!parent_pci);

	mutex_lock(&usnic_ib_ibdev_list_lock);
	list_क्रम_each_entry(us_ibdev, &usnic_ib_ibdev_list, ib_dev_link) अणु
		अगर (us_ibdev->pdev == parent_pci) अणु
			kref_get(&us_ibdev->vf_cnt);
			जाओ out;
		पूर्ण
	पूर्ण

	us_ibdev = usnic_ib_device_add(parent_pci);
	अगर (IS_ERR_OR_शून्य(us_ibdev)) अणु
		us_ibdev = us_ibdev ? us_ibdev : ERR_PTR(-EFAULT);
		जाओ out;
	पूर्ण

	err = usnic_ib_sysfs_रेजिस्टर_usdev(us_ibdev);
	अगर (err) अणु
		usnic_ib_device_हटाओ(us_ibdev);
		us_ibdev = ERR_PTR(err);
		जाओ out;
	पूर्ण

	list_add(&us_ibdev->ib_dev_link, &usnic_ib_ibdev_list);
out:
	mutex_unlock(&usnic_ib_ibdev_list_lock);
	वापस us_ibdev;
पूर्ण
/* End of PF discovery section */

/* Start of PCI section */

अटल स्थिर काष्ठा pci_device_id usnic_ib_pci_ids[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_CISCO, PCI_DEVICE_ID_CISCO_VIC_USPACE_NIC)पूर्ण,
	अणु0,पूर्ण
पूर्ण;

अटल पूर्णांक usnic_ib_pci_probe(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा usnic_ib_dev *pf;
	काष्ठा usnic_ib_vf *vf;
	क्रमागत usnic_vnic_res_type res_type;

	vf = kzalloc(माप(*vf), GFP_KERNEL);
	अगर (!vf)
		वापस -ENOMEM;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		usnic_err("Failed to enable %s with err %d\n",
				pci_name(pdev), err);
		जाओ out_clean_vf;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		usnic_err("Failed to request region for %s with err %d\n",
				pci_name(pdev), err);
		जाओ out_disable_device;
	पूर्ण

	pci_set_master(pdev);
	pci_set_drvdata(pdev, vf);

	vf->vnic = usnic_vnic_alloc(pdev);
	अगर (IS_ERR_OR_शून्य(vf->vnic)) अणु
		err = vf->vnic ? PTR_ERR(vf->vnic) : -ENOMEM;
		usnic_err("Failed to alloc vnic for %s with err %d\n",
				pci_name(pdev), err);
		जाओ out_release_regions;
	पूर्ण

	pf = usnic_ib_discover_pf(vf->vnic);
	अगर (IS_ERR_OR_शून्य(pf)) अणु
		usnic_err("Failed to discover pf of vnic %s with err%ld\n",
				pci_name(pdev), PTR_ERR(pf));
		err = pf ? PTR_ERR(pf) : -EFAULT;
		जाओ out_clean_vnic;
	पूर्ण

	vf->pf = pf;
	spin_lock_init(&vf->lock);
	mutex_lock(&pf->usdev_lock);
	list_add_tail(&vf->link, &pf->vf_dev_list);
	/*
	 * Save max settings (will be same क्रम each VF, easier to re-ग_लिखो than
	 * to say "अगर (!set) अणु set_values(); set=1; पूर्ण
	 */
	क्रम (res_type = USNIC_VNIC_RES_TYPE_EOL+1;
			res_type < USNIC_VNIC_RES_TYPE_MAX;
			res_type++) अणु
		pf->vf_res_cnt[res_type] = usnic_vnic_res_cnt(vf->vnic,
								res_type);
	पूर्ण

	mutex_unlock(&pf->usdev_lock);

	usnic_info("Registering usnic VF %s into PF %s\n", pci_name(pdev),
		   dev_name(&pf->ib_dev.dev));
	usnic_ib_log_vf(vf);
	वापस 0;

out_clean_vnic:
	usnic_vnic_मुक्त(vf->vnic);
out_release_regions:
	pci_set_drvdata(pdev, शून्य);
	pci_clear_master(pdev);
	pci_release_regions(pdev);
out_disable_device:
	pci_disable_device(pdev);
out_clean_vf:
	kमुक्त(vf);
	वापस err;
पूर्ण

अटल व्योम usnic_ib_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा usnic_ib_vf *vf = pci_get_drvdata(pdev);
	काष्ठा usnic_ib_dev *pf = vf->pf;

	mutex_lock(&pf->usdev_lock);
	list_del(&vf->link);
	mutex_unlock(&pf->usdev_lock);

	kref_put(&pf->vf_cnt, usnic_ib_undiscover_pf);
	usnic_vnic_मुक्त(vf->vnic);
	pci_set_drvdata(pdev, शून्य);
	pci_clear_master(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kमुक्त(vf);

	usnic_info("Removed VF %s\n", pci_name(pdev));
पूर्ण

/* PCI driver entry poपूर्णांकs */
अटल काष्ठा pci_driver usnic_ib_pci_driver = अणु
	.name = DRV_NAME,
	.id_table = usnic_ib_pci_ids,
	.probe = usnic_ib_pci_probe,
	.हटाओ = usnic_ib_pci_हटाओ,
पूर्ण;
/* End of PCI section */

/* Start of module section */
अटल पूर्णांक __init usnic_ib_init(व्योम)
अणु
	पूर्णांक err;

	prपूर्णांकk_once(KERN_INFO "%s", usnic_version);

	err = usnic_uiom_init(DRV_NAME);
	अगर (err) अणु
		usnic_err("Unable to initialize umem with err %d\n", err);
		वापस err;
	पूर्ण

	err = pci_रेजिस्टर_driver(&usnic_ib_pci_driver);
	अगर (err) अणु
		usnic_err("Unable to register with PCI\n");
		जाओ out_umem_fini;
	पूर्ण

	err = रेजिस्टर_netdevice_notअगरier(&usnic_ib_netdevice_notअगरier);
	अगर (err) अणु
		usnic_err("Failed to register netdev notifier\n");
		जाओ out_pci_unreg;
	पूर्ण

	err = रेजिस्टर_inetaddr_notअगरier(&usnic_ib_inetaddr_notअगरier);
	अगर (err) अणु
		usnic_err("Failed to register inet addr notifier\n");
		जाओ out_unreg_netdev_notअगरier;
	पूर्ण

	err = usnic_transport_init();
	अगर (err) अणु
		usnic_err("Failed to initialize transport\n");
		जाओ out_unreg_inetaddr_notअगरier;
	पूर्ण

	usnic_debugfs_init();

	वापस 0;

out_unreg_inetaddr_notअगरier:
	unरेजिस्टर_inetaddr_notअगरier(&usnic_ib_inetaddr_notअगरier);
out_unreg_netdev_notअगरier:
	unरेजिस्टर_netdevice_notअगरier(&usnic_ib_netdevice_notअगरier);
out_pci_unreg:
	pci_unरेजिस्टर_driver(&usnic_ib_pci_driver);
out_umem_fini:

	वापस err;
पूर्ण

अटल व्योम __निकास usnic_ib_destroy(व्योम)
अणु
	usnic_dbg("\n");
	usnic_debugfs_निकास();
	usnic_transport_fini();
	unरेजिस्टर_inetaddr_notअगरier(&usnic_ib_inetaddr_notअगरier);
	unरेजिस्टर_netdevice_notअगरier(&usnic_ib_netdevice_notअगरier);
	pci_unरेजिस्टर_driver(&usnic_ib_pci_driver);
पूर्ण

MODULE_DESCRIPTION("Cisco VIC (usNIC) Verbs Driver");
MODULE_AUTHOR("Upinder Malhi <umalhi@cisco.com>");
MODULE_LICENSE("Dual BSD/GPL");
module_param(usnic_log_lvl, uपूर्णांक, S_IRUGO | S_IWUSR);
module_param(usnic_ib_share_vf, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(usnic_log_lvl, " Off=0, Err=1, Info=2, Debug=3");
MODULE_PARM_DESC(usnic_ib_share_vf, "Off=0, On=1 VF sharing amongst QPs");
MODULE_DEVICE_TABLE(pci, usnic_ib_pci_ids);

module_init(usnic_ib_init);
module_निकास(usnic_ib_destroy);
/* End of module section */
