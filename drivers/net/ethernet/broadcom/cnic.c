<शैली गुरु>
/* cnic.c: QLogic CNIC core network driver.
 *
 * Copyright (c) 2006-2014 Broadcom Corporation
 * Copyright (c) 2014-2015 QLogic Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Original skeleton written by: John(Zongxi) Chen (zongxi@broadcom.com)
 * Previously modअगरied and मुख्यtained by: Michael Chan <mchan@broadcom.com>
 * Maपूर्णांकained By: Dept-HSGLinuxNICDev@qlogic.com
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/uio_driver.h>
#समावेश <linux/in.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/अक्रमom.h>
#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
#घोषणा BCM_VLAN 1
#पूर्ण_अगर
#समावेश <net/ip.h>
#समावेश <net/tcp.h>
#समावेश <net/route.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ip6_checksum.h>
#समावेश <scsi/iscsi_अगर.h>

#घोषणा BCM_CNIC	1
#समावेश "cnic_if.h"
#समावेश "bnx2.h"
#समावेश "bnx2x/bnx2x.h"
#समावेश "bnx2x/bnx2x_reg.h"
#समावेश "bnx2x/bnx2x_fw_defs.h"
#समावेश "bnx2x/bnx2x_hsi.h"
#समावेश "../../../scsi/bnx2i/57xx_iscsi_constants.h"
#समावेश "../../../scsi/bnx2i/57xx_iscsi_hsi.h"
#समावेश "../../../scsi/bnx2fc/bnx2fc_constants.h"
#समावेश "cnic.h"
#समावेश "cnic_defs.h"

#घोषणा CNIC_MODULE_NAME	"cnic"

अटल अक्षर version[] =
	"QLogic " CNIC_MODULE_NAME "Driver v" CNIC_MODULE_VERSION " (" CNIC_MODULE_RELDATE ")\n";

MODULE_AUTHOR("Michael Chan <mchan@broadcom.com> and John(Zongxi) "
	      "Chen (zongxi@broadcom.com");
MODULE_DESCRIPTION("QLogic cnic Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(CNIC_MODULE_VERSION);

/* cnic_dev_list modअगरications are रक्षित by both rtnl and cnic_dev_lock */
अटल LIST_HEAD(cnic_dev_list);
अटल LIST_HEAD(cnic_udev_list);
अटल DEFINE_RWLOCK(cnic_dev_lock);
अटल DEFINE_MUTEX(cnic_lock);

अटल काष्ठा cnic_ulp_ops __rcu *cnic_ulp_tbl[MAX_CNIC_ULP_TYPE];

/* helper function, assuming cnic_lock is held */
अटल अंतरभूत काष्ठा cnic_ulp_ops *cnic_ulp_tbl_prot(पूर्णांक type)
अणु
	वापस rcu_dereference_रक्षित(cnic_ulp_tbl[type],
					 lockdep_is_held(&cnic_lock));
पूर्ण

अटल पूर्णांक cnic_service_bnx2(व्योम *, व्योम *);
अटल पूर्णांक cnic_service_bnx2x(व्योम *, व्योम *);
अटल पूर्णांक cnic_ctl(व्योम *, काष्ठा cnic_ctl_info *);

अटल काष्ठा cnic_ops cnic_bnx2_ops = अणु
	.cnic_owner	= THIS_MODULE,
	.cnic_handler	= cnic_service_bnx2,
	.cnic_ctl	= cnic_ctl,
पूर्ण;

अटल काष्ठा cnic_ops cnic_bnx2x_ops = अणु
	.cnic_owner	= THIS_MODULE,
	.cnic_handler	= cnic_service_bnx2x,
	.cnic_ctl	= cnic_ctl,
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *cnic_wq;

अटल व्योम cnic_shutकरोwn_rings(काष्ठा cnic_dev *);
अटल व्योम cnic_init_rings(काष्ठा cnic_dev *);
अटल पूर्णांक cnic_cm_set_pg(काष्ठा cnic_sock *);

अटल पूर्णांक cnic_uio_खोलो(काष्ठा uio_info *uinfo, काष्ठा inode *inode)
अणु
	काष्ठा cnic_uio_dev *udev = uinfo->priv;
	काष्ठा cnic_dev *dev;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (udev->uio_dev != -1)
		वापस -EBUSY;

	rtnl_lock();
	dev = udev->dev;

	अगर (!dev || !test_bit(CNIC_F_CNIC_UP, &dev->flags)) अणु
		rtnl_unlock();
		वापस -ENODEV;
	पूर्ण

	udev->uio_dev = iminor(inode);

	cnic_shutकरोwn_rings(dev);
	cnic_init_rings(dev);
	rtnl_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक cnic_uio_बंद(काष्ठा uio_info *uinfo, काष्ठा inode *inode)
अणु
	काष्ठा cnic_uio_dev *udev = uinfo->priv;

	udev->uio_dev = -1;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cnic_hold(काष्ठा cnic_dev *dev)
अणु
	atomic_inc(&dev->ref_count);
पूर्ण

अटल अंतरभूत व्योम cnic_put(काष्ठा cnic_dev *dev)
अणु
	atomic_dec(&dev->ref_count);
पूर्ण

अटल अंतरभूत व्योम csk_hold(काष्ठा cnic_sock *csk)
अणु
	atomic_inc(&csk->ref_count);
पूर्ण

अटल अंतरभूत व्योम csk_put(काष्ठा cnic_sock *csk)
अणु
	atomic_dec(&csk->ref_count);
पूर्ण

अटल काष्ठा cnic_dev *cnic_from_netdev(काष्ठा net_device *netdev)
अणु
	काष्ठा cnic_dev *cdev;

	पढ़ो_lock(&cnic_dev_lock);
	list_क्रम_each_entry(cdev, &cnic_dev_list, list) अणु
		अगर (netdev == cdev->netdev) अणु
			cnic_hold(cdev);
			पढ़ो_unlock(&cnic_dev_lock);
			वापस cdev;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&cnic_dev_lock);
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम ulp_get(काष्ठा cnic_ulp_ops *ulp_ops)
अणु
	atomic_inc(&ulp_ops->ref_count);
पूर्ण

अटल अंतरभूत व्योम ulp_put(काष्ठा cnic_ulp_ops *ulp_ops)
अणु
	atomic_dec(&ulp_ops->ref_count);
पूर्ण

अटल व्योम cnic_ctx_wr(काष्ठा cnic_dev *dev, u32 cid_addr, u32 off, u32 val)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	काष्ठा drv_ctl_info info;
	काष्ठा drv_ctl_io *io = &info.data.io;

	स_रखो(&info, 0, माप(काष्ठा drv_ctl_info));
	info.cmd = DRV_CTL_CTX_WR_CMD;
	io->cid_addr = cid_addr;
	io->offset = off;
	io->data = val;
	ethdev->drv_ctl(dev->netdev, &info);
पूर्ण

अटल व्योम cnic_ctx_tbl_wr(काष्ठा cnic_dev *dev, u32 off, dma_addr_t addr)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	काष्ठा drv_ctl_info info;
	काष्ठा drv_ctl_io *io = &info.data.io;

	स_रखो(&info, 0, माप(काष्ठा drv_ctl_info));
	info.cmd = DRV_CTL_CTXTBL_WR_CMD;
	io->offset = off;
	io->dma_addr = addr;
	ethdev->drv_ctl(dev->netdev, &info);
पूर्ण

अटल व्योम cnic_ring_ctl(काष्ठा cnic_dev *dev, u32 cid, u32 cl_id, पूर्णांक start)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	काष्ठा drv_ctl_info info;
	काष्ठा drv_ctl_l2_ring *ring = &info.data.ring;

	स_रखो(&info, 0, माप(काष्ठा drv_ctl_info));
	अगर (start)
		info.cmd = DRV_CTL_START_L2_CMD;
	अन्यथा
		info.cmd = DRV_CTL_STOP_L2_CMD;

	ring->cid = cid;
	ring->client_id = cl_id;
	ethdev->drv_ctl(dev->netdev, &info);
पूर्ण

अटल व्योम cnic_reg_wr_ind(काष्ठा cnic_dev *dev, u32 off, u32 val)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	काष्ठा drv_ctl_info info;
	काष्ठा drv_ctl_io *io = &info.data.io;

	स_रखो(&info, 0, माप(काष्ठा drv_ctl_info));
	info.cmd = DRV_CTL_IO_WR_CMD;
	io->offset = off;
	io->data = val;
	ethdev->drv_ctl(dev->netdev, &info);
पूर्ण

अटल u32 cnic_reg_rd_ind(काष्ठा cnic_dev *dev, u32 off)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	काष्ठा drv_ctl_info info;
	काष्ठा drv_ctl_io *io = &info.data.io;

	स_रखो(&info, 0, माप(काष्ठा drv_ctl_info));
	info.cmd = DRV_CTL_IO_RD_CMD;
	io->offset = off;
	ethdev->drv_ctl(dev->netdev, &info);
	वापस io->data;
पूर्ण

अटल व्योम cnic_ulp_ctl(काष्ठा cnic_dev *dev, पूर्णांक ulp_type, bool reg, पूर्णांक state)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	काष्ठा drv_ctl_info info;
	काष्ठा fcoe_capabilities *fcoe_cap =
		&info.data.रेजिस्टर_data.fcoe_features;

	स_रखो(&info, 0, माप(काष्ठा drv_ctl_info));
	अगर (reg) अणु
		info.cmd = DRV_CTL_ULP_REGISTER_CMD;
		अगर (ulp_type == CNIC_ULP_FCOE && dev->fcoe_cap)
			स_नकल(fcoe_cap, dev->fcoe_cap, माप(*fcoe_cap));
	पूर्ण अन्यथा अणु
		info.cmd = DRV_CTL_ULP_UNREGISTER_CMD;
	पूर्ण

	info.data.ulp_type = ulp_type;
	info.drv_state = state;
	ethdev->drv_ctl(dev->netdev, &info);
पूर्ण

अटल पूर्णांक cnic_in_use(काष्ठा cnic_sock *csk)
अणु
	वापस test_bit(SK_F_INUSE, &csk->flags);
पूर्ण

अटल व्योम cnic_spq_completion(काष्ठा cnic_dev *dev, पूर्णांक cmd, u32 count)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	काष्ठा drv_ctl_info info;

	स_रखो(&info, 0, माप(काष्ठा drv_ctl_info));
	info.cmd = cmd;
	info.data.credit.credit_count = count;
	ethdev->drv_ctl(dev->netdev, &info);
पूर्ण

अटल पूर्णांक cnic_get_l5_cid(काष्ठा cnic_local *cp, u32 cid, u32 *l5_cid)
अणु
	u32 i;

	अगर (!cp->ctx_tbl)
		वापस -EINVAL;

	क्रम (i = 0; i < cp->max_cid_space; i++) अणु
		अगर (cp->ctx_tbl[i].cid == cid) अणु
			*l5_cid = i;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cnic_send_nlmsg(काष्ठा cnic_local *cp, u32 type,
			   काष्ठा cnic_sock *csk)
अणु
	काष्ठा iscsi_path path_req;
	अक्षर *buf = शून्य;
	u16 len = 0;
	u32 msg_type = ISCSI_KEVENT_IF_DOWN;
	काष्ठा cnic_ulp_ops *ulp_ops;
	काष्ठा cnic_uio_dev *udev = cp->udev;
	पूर्णांक rc = 0, retry = 0;

	अगर (!udev || udev->uio_dev == -1)
		वापस -ENODEV;

	अगर (csk) अणु
		len = माप(path_req);
		buf = (अक्षर *) &path_req;
		स_रखो(&path_req, 0, len);

		msg_type = ISCSI_KEVENT_PATH_REQ;
		path_req.handle = (u64) csk->l5_cid;
		अगर (test_bit(SK_F_IPV6, &csk->flags)) अणु
			स_नकल(&path_req.dst.v6_addr, &csk->dst_ip[0],
			       माप(काष्ठा in6_addr));
			path_req.ip_addr_len = 16;
		पूर्ण अन्यथा अणु
			स_नकल(&path_req.dst.v4_addr, &csk->dst_ip[0],
			       माप(काष्ठा in_addr));
			path_req.ip_addr_len = 4;
		पूर्ण
		path_req.vlan_id = csk->vlan_id;
		path_req.pmtu = csk->mtu;
	पूर्ण

	जबतक (retry < 3) अणु
		rc = 0;
		rcu_पढ़ो_lock();
		ulp_ops = rcu_dereference(cp->ulp_ops[CNIC_ULP_ISCSI]);
		अगर (ulp_ops)
			rc = ulp_ops->iscsi_nl_send_msg(
				cp->ulp_handle[CNIC_ULP_ISCSI],
				msg_type, buf, len);
		rcu_पढ़ो_unlock();
		अगर (rc == 0 || msg_type != ISCSI_KEVENT_PATH_REQ)
			अवरोध;

		msleep(100);
		retry++;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम cnic_cm_upcall(काष्ठा cnic_local *, काष्ठा cnic_sock *, u8);

अटल पूर्णांक cnic_iscsi_nl_msg_recv(काष्ठा cnic_dev *dev, u32 msg_type,
				  अक्षर *buf, u16 len)
अणु
	पूर्णांक rc = -EINVAL;

	चयन (msg_type) अणु
	हाल ISCSI_UEVENT_PATH_UPDATE: अणु
		काष्ठा cnic_local *cp;
		u32 l5_cid;
		काष्ठा cnic_sock *csk;
		काष्ठा iscsi_path *path_resp;

		अगर (len < माप(*path_resp))
			अवरोध;

		path_resp = (काष्ठा iscsi_path *) buf;
		cp = dev->cnic_priv;
		l5_cid = (u32) path_resp->handle;
		अगर (l5_cid >= MAX_CM_SK_TBL_SZ)
			अवरोध;

		अगर (!rcu_access_poपूर्णांकer(cp->ulp_ops[CNIC_ULP_L4])) अणु
			rc = -ENODEV;
			अवरोध;
		पूर्ण
		csk = &cp->csk_tbl[l5_cid];
		csk_hold(csk);
		अगर (cnic_in_use(csk) &&
		    test_bit(SK_F_CONNECT_START, &csk->flags)) अणु

			csk->vlan_id = path_resp->vlan_id;

			स_नकल(csk->ha, path_resp->mac_addr, ETH_ALEN);
			अगर (test_bit(SK_F_IPV6, &csk->flags))
				स_नकल(&csk->src_ip[0], &path_resp->src.v6_addr,
				       माप(काष्ठा in6_addr));
			अन्यथा
				स_नकल(&csk->src_ip[0], &path_resp->src.v4_addr,
				       माप(काष्ठा in_addr));

			अगर (is_valid_ether_addr(csk->ha)) अणु
				cnic_cm_set_pg(csk);
			पूर्ण अन्यथा अगर (!test_bit(SK_F_OFFLD_SCHED, &csk->flags) &&
				!test_bit(SK_F_OFFLD_COMPLETE, &csk->flags)) अणु

				cnic_cm_upcall(cp, csk,
					L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE);
				clear_bit(SK_F_CONNECT_START, &csk->flags);
			पूर्ण
		पूर्ण
		csk_put(csk);
		rc = 0;
	पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक cnic_offld_prep(काष्ठा cnic_sock *csk)
अणु
	अगर (test_and_set_bit(SK_F_OFFLD_SCHED, &csk->flags))
		वापस 0;

	अगर (!test_bit(SK_F_CONNECT_START, &csk->flags)) अणु
		clear_bit(SK_F_OFFLD_SCHED, &csk->flags);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक cnic_बंद_prep(काष्ठा cnic_sock *csk)
अणु
	clear_bit(SK_F_CONNECT_START, &csk->flags);
	smp_mb__after_atomic();

	अगर (test_and_clear_bit(SK_F_OFFLD_COMPLETE, &csk->flags)) अणु
		जबतक (test_and_set_bit(SK_F_OFFLD_SCHED, &csk->flags))
			msleep(1);

		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cnic_पात_prep(काष्ठा cnic_sock *csk)
अणु
	clear_bit(SK_F_CONNECT_START, &csk->flags);
	smp_mb__after_atomic();

	जबतक (test_and_set_bit(SK_F_OFFLD_SCHED, &csk->flags))
		msleep(1);

	अगर (test_and_clear_bit(SK_F_OFFLD_COMPLETE, &csk->flags)) अणु
		csk->state = L4_KCQE_OPCODE_VALUE_RESET_COMP;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cnic_रेजिस्टर_driver(पूर्णांक ulp_type, काष्ठा cnic_ulp_ops *ulp_ops)
अणु
	काष्ठा cnic_dev *dev;

	अगर (ulp_type < 0 || ulp_type >= MAX_CNIC_ULP_TYPE) अणु
		pr_err("%s: Bad type %d\n", __func__, ulp_type);
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&cnic_lock);
	अगर (cnic_ulp_tbl_prot(ulp_type)) अणु
		pr_err("%s: Type %d has already been registered\n",
		       __func__, ulp_type);
		mutex_unlock(&cnic_lock);
		वापस -EBUSY;
	पूर्ण

	पढ़ो_lock(&cnic_dev_lock);
	list_क्रम_each_entry(dev, &cnic_dev_list, list) अणु
		काष्ठा cnic_local *cp = dev->cnic_priv;

		clear_bit(ULP_F_INIT, &cp->ulp_flags[ulp_type]);
	पूर्ण
	पढ़ो_unlock(&cnic_dev_lock);

	atomic_set(&ulp_ops->ref_count, 0);
	rcu_assign_poपूर्णांकer(cnic_ulp_tbl[ulp_type], ulp_ops);
	mutex_unlock(&cnic_lock);

	/* Prevent race conditions with netdev_event */
	rtnl_lock();
	list_क्रम_each_entry(dev, &cnic_dev_list, list) अणु
		काष्ठा cnic_local *cp = dev->cnic_priv;

		अगर (!test_and_set_bit(ULP_F_INIT, &cp->ulp_flags[ulp_type]))
			ulp_ops->cnic_init(dev);
	पूर्ण
	rtnl_unlock();

	वापस 0;
पूर्ण

पूर्णांक cnic_unरेजिस्टर_driver(पूर्णांक ulp_type)
अणु
	काष्ठा cnic_dev *dev;
	काष्ठा cnic_ulp_ops *ulp_ops;
	पूर्णांक i = 0;

	अगर (ulp_type < 0 || ulp_type >= MAX_CNIC_ULP_TYPE) अणु
		pr_err("%s: Bad type %d\n", __func__, ulp_type);
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&cnic_lock);
	ulp_ops = cnic_ulp_tbl_prot(ulp_type);
	अगर (!ulp_ops) अणु
		pr_err("%s: Type %d has not been registered\n",
		       __func__, ulp_type);
		जाओ out_unlock;
	पूर्ण
	पढ़ो_lock(&cnic_dev_lock);
	list_क्रम_each_entry(dev, &cnic_dev_list, list) अणु
		काष्ठा cnic_local *cp = dev->cnic_priv;

		अगर (rcu_access_poपूर्णांकer(cp->ulp_ops[ulp_type])) अणु
			pr_err("%s: Type %d still has devices registered\n",
			       __func__, ulp_type);
			पढ़ो_unlock(&cnic_dev_lock);
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&cnic_dev_lock);

	RCU_INIT_POINTER(cnic_ulp_tbl[ulp_type], शून्य);

	mutex_unlock(&cnic_lock);
	synchronize_rcu();
	जबतक ((atomic_पढ़ो(&ulp_ops->ref_count) != 0) && (i < 20)) अणु
		msleep(100);
		i++;
	पूर्ण

	अगर (atomic_पढ़ो(&ulp_ops->ref_count) != 0)
		pr_warn("%s: Failed waiting for ref count to go to zero\n",
			__func__);
	वापस 0;

out_unlock:
	mutex_unlock(&cnic_lock);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cnic_start_hw(काष्ठा cnic_dev *);
अटल व्योम cnic_stop_hw(काष्ठा cnic_dev *);

अटल पूर्णांक cnic_रेजिस्टर_device(काष्ठा cnic_dev *dev, पूर्णांक ulp_type,
				व्योम *ulp_ctx)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_ulp_ops *ulp_ops;

	अगर (ulp_type < 0 || ulp_type >= MAX_CNIC_ULP_TYPE) अणु
		pr_err("%s: Bad type %d\n", __func__, ulp_type);
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&cnic_lock);
	अगर (cnic_ulp_tbl_prot(ulp_type) == शून्य) अणु
		pr_err("%s: Driver with type %d has not been registered\n",
		       __func__, ulp_type);
		mutex_unlock(&cnic_lock);
		वापस -EAGAIN;
	पूर्ण
	अगर (rcu_access_poपूर्णांकer(cp->ulp_ops[ulp_type])) अणु
		pr_err("%s: Type %d has already been registered to this device\n",
		       __func__, ulp_type);
		mutex_unlock(&cnic_lock);
		वापस -EBUSY;
	पूर्ण

	clear_bit(ULP_F_START, &cp->ulp_flags[ulp_type]);
	cp->ulp_handle[ulp_type] = ulp_ctx;
	ulp_ops = cnic_ulp_tbl_prot(ulp_type);
	rcu_assign_poपूर्णांकer(cp->ulp_ops[ulp_type], ulp_ops);
	cnic_hold(dev);

	अगर (test_bit(CNIC_F_CNIC_UP, &dev->flags))
		अगर (!test_and_set_bit(ULP_F_START, &cp->ulp_flags[ulp_type]))
			ulp_ops->cnic_start(cp->ulp_handle[ulp_type]);

	mutex_unlock(&cnic_lock);

	cnic_ulp_ctl(dev, ulp_type, true, DRV_ACTIVE);

	वापस 0;

पूर्ण
EXPORT_SYMBOL(cnic_रेजिस्टर_driver);

अटल पूर्णांक cnic_unरेजिस्टर_device(काष्ठा cnic_dev *dev, पूर्णांक ulp_type)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	पूर्णांक i = 0;

	अगर (ulp_type < 0 || ulp_type >= MAX_CNIC_ULP_TYPE) अणु
		pr_err("%s: Bad type %d\n", __func__, ulp_type);
		वापस -EINVAL;
	पूर्ण

	अगर (ulp_type == CNIC_ULP_ISCSI)
		cnic_send_nlmsg(cp, ISCSI_KEVENT_IF_DOWN, शून्य);

	mutex_lock(&cnic_lock);
	अगर (rcu_access_poपूर्णांकer(cp->ulp_ops[ulp_type])) अणु
		RCU_INIT_POINTER(cp->ulp_ops[ulp_type], शून्य);
		cnic_put(dev);
	पूर्ण अन्यथा अणु
		pr_err("%s: device not registered to this ulp type %d\n",
		       __func__, ulp_type);
		mutex_unlock(&cnic_lock);
		वापस -EINVAL;
	पूर्ण
	mutex_unlock(&cnic_lock);

	अगर (ulp_type == CNIC_ULP_FCOE)
		dev->fcoe_cap = शून्य;

	synchronize_rcu();

	जबतक (test_bit(ULP_F_CALL_PENDING, &cp->ulp_flags[ulp_type]) &&
	       i < 20) अणु
		msleep(100);
		i++;
	पूर्ण
	अगर (test_bit(ULP_F_CALL_PENDING, &cp->ulp_flags[ulp_type]))
		netdev_warn(dev->netdev, "Failed waiting for ULP up call to complete\n");

	अगर (test_bit(ULP_F_INIT, &cp->ulp_flags[ulp_type]))
		cnic_ulp_ctl(dev, ulp_type, false, DRV_UNLOADED);
	अन्यथा
		cnic_ulp_ctl(dev, ulp_type, false, DRV_INACTIVE);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cnic_unरेजिस्टर_driver);

अटल पूर्णांक cnic_init_id_tbl(काष्ठा cnic_id_tbl *id_tbl, u32 size, u32 start_id,
			    u32 next)
अणु
	id_tbl->start = start_id;
	id_tbl->max = size;
	id_tbl->next = next;
	spin_lock_init(&id_tbl->lock);
	id_tbl->table = kसुस्मृति(BITS_TO_LONGS(size), माप(दीर्घ), GFP_KERNEL);
	अगर (!id_tbl->table)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम cnic_मुक्त_id_tbl(काष्ठा cnic_id_tbl *id_tbl)
अणु
	kमुक्त(id_tbl->table);
	id_tbl->table = शून्य;
पूर्ण

अटल पूर्णांक cnic_alloc_id(काष्ठा cnic_id_tbl *id_tbl, u32 id)
अणु
	पूर्णांक ret = -1;

	id -= id_tbl->start;
	अगर (id >= id_tbl->max)
		वापस ret;

	spin_lock(&id_tbl->lock);
	अगर (!test_bit(id, id_tbl->table)) अणु
		set_bit(id, id_tbl->table);
		ret = 0;
	पूर्ण
	spin_unlock(&id_tbl->lock);
	वापस ret;
पूर्ण

/* Returns -1 अगर not successful */
अटल u32 cnic_alloc_new_id(काष्ठा cnic_id_tbl *id_tbl)
अणु
	u32 id;

	spin_lock(&id_tbl->lock);
	id = find_next_zero_bit(id_tbl->table, id_tbl->max, id_tbl->next);
	अगर (id >= id_tbl->max) अणु
		id = -1;
		अगर (id_tbl->next != 0) अणु
			id = find_first_zero_bit(id_tbl->table, id_tbl->next);
			अगर (id >= id_tbl->next)
				id = -1;
		पूर्ण
	पूर्ण

	अगर (id < id_tbl->max) अणु
		set_bit(id, id_tbl->table);
		id_tbl->next = (id + 1) & (id_tbl->max - 1);
		id += id_tbl->start;
	पूर्ण

	spin_unlock(&id_tbl->lock);

	वापस id;
पूर्ण

अटल व्योम cnic_मुक्त_id(काष्ठा cnic_id_tbl *id_tbl, u32 id)
अणु
	अगर (id == -1)
		वापस;

	id -= id_tbl->start;
	अगर (id >= id_tbl->max)
		वापस;

	clear_bit(id, id_tbl->table);
पूर्ण

अटल व्योम cnic_मुक्त_dma(काष्ठा cnic_dev *dev, काष्ठा cnic_dma *dma)
अणु
	पूर्णांक i;

	अगर (!dma->pg_arr)
		वापस;

	क्रम (i = 0; i < dma->num_pages; i++) अणु
		अगर (dma->pg_arr[i]) अणु
			dma_मुक्त_coherent(&dev->pcidev->dev, CNIC_PAGE_SIZE,
					  dma->pg_arr[i], dma->pg_map_arr[i]);
			dma->pg_arr[i] = शून्य;
		पूर्ण
	पूर्ण
	अगर (dma->pgtbl) अणु
		dma_मुक्त_coherent(&dev->pcidev->dev, dma->pgtbl_size,
				  dma->pgtbl, dma->pgtbl_map);
		dma->pgtbl = शून्य;
	पूर्ण
	kमुक्त(dma->pg_arr);
	dma->pg_arr = शून्य;
	dma->num_pages = 0;
पूर्ण

अटल व्योम cnic_setup_page_tbl(काष्ठा cnic_dev *dev, काष्ठा cnic_dma *dma)
अणु
	पूर्णांक i;
	__le32 *page_table = (__le32 *) dma->pgtbl;

	क्रम (i = 0; i < dma->num_pages; i++) अणु
		/* Each entry needs to be in big endian क्रमmat. */
		*page_table = cpu_to_le32((u64) dma->pg_map_arr[i] >> 32);
		page_table++;
		*page_table = cpu_to_le32(dma->pg_map_arr[i] & 0xffffffff);
		page_table++;
	पूर्ण
पूर्ण

अटल व्योम cnic_setup_page_tbl_le(काष्ठा cnic_dev *dev, काष्ठा cnic_dma *dma)
अणु
	पूर्णांक i;
	__le32 *page_table = (__le32 *) dma->pgtbl;

	क्रम (i = 0; i < dma->num_pages; i++) अणु
		/* Each entry needs to be in little endian क्रमmat. */
		*page_table = cpu_to_le32(dma->pg_map_arr[i] & 0xffffffff);
		page_table++;
		*page_table = cpu_to_le32((u64) dma->pg_map_arr[i] >> 32);
		page_table++;
	पूर्ण
पूर्ण

अटल पूर्णांक cnic_alloc_dma(काष्ठा cnic_dev *dev, काष्ठा cnic_dma *dma,
			  पूर्णांक pages, पूर्णांक use_pg_tbl)
अणु
	पूर्णांक i, size;
	काष्ठा cnic_local *cp = dev->cnic_priv;

	size = pages * (माप(व्योम *) + माप(dma_addr_t));
	dma->pg_arr = kzalloc(size, GFP_ATOMIC);
	अगर (dma->pg_arr == शून्य)
		वापस -ENOMEM;

	dma->pg_map_arr = (dma_addr_t *) (dma->pg_arr + pages);
	dma->num_pages = pages;

	क्रम (i = 0; i < pages; i++) अणु
		dma->pg_arr[i] = dma_alloc_coherent(&dev->pcidev->dev,
						    CNIC_PAGE_SIZE,
						    &dma->pg_map_arr[i],
						    GFP_ATOMIC);
		अगर (dma->pg_arr[i] == शून्य)
			जाओ error;
	पूर्ण
	अगर (!use_pg_tbl)
		वापस 0;

	dma->pgtbl_size = ((pages * 8) + CNIC_PAGE_SIZE - 1) &
			  ~(CNIC_PAGE_SIZE - 1);
	dma->pgtbl = dma_alloc_coherent(&dev->pcidev->dev, dma->pgtbl_size,
					&dma->pgtbl_map, GFP_ATOMIC);
	अगर (dma->pgtbl == शून्य)
		जाओ error;

	cp->setup_pgtbl(dev, dma);

	वापस 0;

error:
	cnic_मुक्त_dma(dev, dma);
	वापस -ENOMEM;
पूर्ण

अटल व्योम cnic_मुक्त_context(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	पूर्णांक i;

	क्रम (i = 0; i < cp->ctx_blks; i++) अणु
		अगर (cp->ctx_arr[i].ctx) अणु
			dma_मुक्त_coherent(&dev->pcidev->dev, cp->ctx_blk_size,
					  cp->ctx_arr[i].ctx,
					  cp->ctx_arr[i].mapping);
			cp->ctx_arr[i].ctx = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __cnic_मुक्त_uio_rings(काष्ठा cnic_uio_dev *udev)
अणु
	अगर (udev->l2_buf) अणु
		dma_मुक्त_coherent(&udev->pdev->dev, udev->l2_buf_size,
				  udev->l2_buf, udev->l2_buf_map);
		udev->l2_buf = शून्य;
	पूर्ण

	अगर (udev->l2_ring) अणु
		dma_मुक्त_coherent(&udev->pdev->dev, udev->l2_ring_size,
				  udev->l2_ring, udev->l2_ring_map);
		udev->l2_ring = शून्य;
	पूर्ण

पूर्ण

अटल व्योम __cnic_मुक्त_uio(काष्ठा cnic_uio_dev *udev)
अणु
	uio_unरेजिस्टर_device(&udev->cnic_uinfo);

	__cnic_मुक्त_uio_rings(udev);

	pci_dev_put(udev->pdev);
	kमुक्त(udev);
पूर्ण

अटल व्योम cnic_मुक्त_uio(काष्ठा cnic_uio_dev *udev)
अणु
	अगर (!udev)
		वापस;

	ग_लिखो_lock(&cnic_dev_lock);
	list_del_init(&udev->list);
	ग_लिखो_unlock(&cnic_dev_lock);
	__cnic_मुक्त_uio(udev);
पूर्ण

अटल व्योम cnic_मुक्त_resc(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_uio_dev *udev = cp->udev;

	अगर (udev) अणु
		udev->dev = शून्य;
		cp->udev = शून्य;
		अगर (udev->uio_dev == -1)
			__cnic_मुक्त_uio_rings(udev);
	पूर्ण

	cnic_मुक्त_context(dev);
	kमुक्त(cp->ctx_arr);
	cp->ctx_arr = शून्य;
	cp->ctx_blks = 0;

	cnic_मुक्त_dma(dev, &cp->gbl_buf_info);
	cnic_मुक्त_dma(dev, &cp->kwq_info);
	cnic_मुक्त_dma(dev, &cp->kwq_16_data_info);
	cnic_मुक्त_dma(dev, &cp->kcq2.dma);
	cnic_मुक्त_dma(dev, &cp->kcq1.dma);
	kमुक्त(cp->iscsi_tbl);
	cp->iscsi_tbl = शून्य;
	kमुक्त(cp->ctx_tbl);
	cp->ctx_tbl = शून्य;

	cnic_मुक्त_id_tbl(&cp->fcoe_cid_tbl);
	cnic_मुक्त_id_tbl(&cp->cid_tbl);
पूर्ण

अटल पूर्णांक cnic_alloc_context(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;

	अगर (BNX2_CHIP(cp) == BNX2_CHIP_5709) अणु
		पूर्णांक i, k, arr_size;

		cp->ctx_blk_size = CNIC_PAGE_SIZE;
		cp->cids_per_blk = CNIC_PAGE_SIZE / 128;
		arr_size = BNX2_MAX_CID / cp->cids_per_blk *
			   माप(काष्ठा cnic_ctx);
		cp->ctx_arr = kzalloc(arr_size, GFP_KERNEL);
		अगर (cp->ctx_arr == शून्य)
			वापस -ENOMEM;

		k = 0;
		क्रम (i = 0; i < 2; i++) अणु
			u32 j, reg, off, lo, hi;

			अगर (i == 0)
				off = BNX2_PG_CTX_MAP;
			अन्यथा
				off = BNX2_ISCSI_CTX_MAP;

			reg = cnic_reg_rd_ind(dev, off);
			lo = reg >> 16;
			hi = reg & 0xffff;
			क्रम (j = lo; j < hi; j += cp->cids_per_blk, k++)
				cp->ctx_arr[k].cid = j;
		पूर्ण

		cp->ctx_blks = k;
		अगर (cp->ctx_blks >= (BNX2_MAX_CID / cp->cids_per_blk)) अणु
			cp->ctx_blks = 0;
			वापस -ENOMEM;
		पूर्ण

		क्रम (i = 0; i < cp->ctx_blks; i++) अणु
			cp->ctx_arr[i].ctx =
				dma_alloc_coherent(&dev->pcidev->dev,
						   CNIC_PAGE_SIZE,
						   &cp->ctx_arr[i].mapping,
						   GFP_KERNEL);
			अगर (cp->ctx_arr[i].ctx == शून्य)
				वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल u16 cnic_bnx2_next_idx(u16 idx)
अणु
	वापस idx + 1;
पूर्ण

अटल u16 cnic_bnx2_hw_idx(u16 idx)
अणु
	वापस idx;
पूर्ण

अटल u16 cnic_bnx2x_next_idx(u16 idx)
अणु
	idx++;
	अगर ((idx & MAX_KCQE_CNT) == MAX_KCQE_CNT)
		idx++;

	वापस idx;
पूर्ण

अटल u16 cnic_bnx2x_hw_idx(u16 idx)
अणु
	अगर ((idx & MAX_KCQE_CNT) == MAX_KCQE_CNT)
		idx++;
	वापस idx;
पूर्ण

अटल पूर्णांक cnic_alloc_kcq(काष्ठा cnic_dev *dev, काष्ठा kcq_info *info,
			  bool use_pg_tbl)
अणु
	पूर्णांक err, i, use_page_tbl = 0;
	काष्ठा kcqe **kcq;

	अगर (use_pg_tbl)
		use_page_tbl = 1;

	err = cnic_alloc_dma(dev, &info->dma, KCQ_PAGE_CNT, use_page_tbl);
	अगर (err)
		वापस err;

	kcq = (काष्ठा kcqe **) info->dma.pg_arr;
	info->kcq = kcq;

	info->next_idx = cnic_bnx2_next_idx;
	info->hw_idx = cnic_bnx2_hw_idx;
	अगर (use_pg_tbl)
		वापस 0;

	info->next_idx = cnic_bnx2x_next_idx;
	info->hw_idx = cnic_bnx2x_hw_idx;

	क्रम (i = 0; i < KCQ_PAGE_CNT; i++) अणु
		काष्ठा bnx2x_bd_chain_next *next =
			(काष्ठा bnx2x_bd_chain_next *) &kcq[i][MAX_KCQE_CNT];
		पूर्णांक j = i + 1;

		अगर (j >= KCQ_PAGE_CNT)
			j = 0;
		next->addr_hi = (u64) info->dma.pg_map_arr[j] >> 32;
		next->addr_lo = info->dma.pg_map_arr[j] & 0xffffffff;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __cnic_alloc_uio_rings(काष्ठा cnic_uio_dev *udev, पूर्णांक pages)
अणु
	काष्ठा cnic_local *cp = udev->dev->cnic_priv;

	अगर (udev->l2_ring)
		वापस 0;

	udev->l2_ring_size = pages * CNIC_PAGE_SIZE;
	udev->l2_ring = dma_alloc_coherent(&udev->pdev->dev, udev->l2_ring_size,
					   &udev->l2_ring_map,
					   GFP_KERNEL | __GFP_COMP);
	अगर (!udev->l2_ring)
		वापस -ENOMEM;

	udev->l2_buf_size = (cp->l2_rx_ring_size + 1) * cp->l2_single_buf_size;
	udev->l2_buf_size = CNIC_PAGE_ALIGN(udev->l2_buf_size);
	udev->l2_buf = dma_alloc_coherent(&udev->pdev->dev, udev->l2_buf_size,
					  &udev->l2_buf_map,
					  GFP_KERNEL | __GFP_COMP);
	अगर (!udev->l2_buf) अणु
		__cnic_मुक्त_uio_rings(udev);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक cnic_alloc_uio_rings(काष्ठा cnic_dev *dev, पूर्णांक pages)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_uio_dev *udev;

	list_क्रम_each_entry(udev, &cnic_udev_list, list) अणु
		अगर (udev->pdev == dev->pcidev) अणु
			udev->dev = dev;
			अगर (__cnic_alloc_uio_rings(udev, pages)) अणु
				udev->dev = शून्य;
				वापस -ENOMEM;
			पूर्ण
			cp->udev = udev;
			वापस 0;
		पूर्ण
	पूर्ण

	udev = kzalloc(माप(काष्ठा cnic_uio_dev), GFP_ATOMIC);
	अगर (!udev)
		वापस -ENOMEM;

	udev->uio_dev = -1;

	udev->dev = dev;
	udev->pdev = dev->pcidev;

	अगर (__cnic_alloc_uio_rings(udev, pages))
		जाओ err_udev;

	list_add(&udev->list, &cnic_udev_list);

	pci_dev_get(udev->pdev);

	cp->udev = udev;

	वापस 0;

 err_udev:
	kमुक्त(udev);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक cnic_init_uio(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_uio_dev *udev = cp->udev;
	काष्ठा uio_info *uinfo;
	पूर्णांक ret = 0;

	अगर (!udev)
		वापस -ENOMEM;

	uinfo = &udev->cnic_uinfo;

	uinfo->mem[0].addr = pci_resource_start(dev->pcidev, 0);
	uinfo->mem[0].पूर्णांकernal_addr = dev->regview;
	uinfo->mem[0].memtype = UIO_MEM_PHYS;

	अगर (test_bit(CNIC_F_BNX2_CLASS, &dev->flags)) अणु
		uinfo->mem[0].size = MB_GET_CID_ADDR(TX_TSS_CID +
						     TX_MAX_TSS_RINGS + 1);
		uinfo->mem[1].addr = (अचिन्हित दीर्घ) cp->status_blk.gen &
					CNIC_PAGE_MASK;
		अगर (cp->ethdev->drv_state & CNIC_DRV_STATE_USING_MSIX)
			uinfo->mem[1].size = BNX2_SBLK_MSIX_ALIGN_SIZE * 9;
		अन्यथा
			uinfo->mem[1].size = BNX2_SBLK_MSIX_ALIGN_SIZE;

		uinfo->name = "bnx2_cnic";
	पूर्ण अन्यथा अगर (test_bit(CNIC_F_BNX2X_CLASS, &dev->flags)) अणु
		uinfo->mem[0].size = pci_resource_len(dev->pcidev, 0);

		uinfo->mem[1].addr = (अचिन्हित दीर्घ) cp->bnx2x_def_status_blk &
			CNIC_PAGE_MASK;
		uinfo->mem[1].size = माप(*cp->bnx2x_def_status_blk);

		uinfo->name = "bnx2x_cnic";
	पूर्ण

	uinfo->mem[1].memtype = UIO_MEM_LOGICAL;

	uinfo->mem[2].addr = (अचिन्हित दीर्घ) udev->l2_ring;
	uinfo->mem[2].size = udev->l2_ring_size;
	uinfo->mem[2].memtype = UIO_MEM_LOGICAL;

	uinfo->mem[3].addr = (अचिन्हित दीर्घ) udev->l2_buf;
	uinfo->mem[3].size = udev->l2_buf_size;
	uinfo->mem[3].memtype = UIO_MEM_LOGICAL;

	uinfo->version = CNIC_MODULE_VERSION;
	uinfo->irq = UIO_IRQ_CUSTOM;

	uinfo->खोलो = cnic_uio_खोलो;
	uinfo->release = cnic_uio_बंद;

	अगर (udev->uio_dev == -1) अणु
		अगर (!uinfo->priv) अणु
			uinfo->priv = udev;

			ret = uio_रेजिस्टर_device(&udev->pdev->dev, uinfo);
		पूर्ण
	पूर्ण अन्यथा अणु
		cnic_init_rings(dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cnic_alloc_bnx2_resc(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	पूर्णांक ret;

	ret = cnic_alloc_dma(dev, &cp->kwq_info, KWQ_PAGE_CNT, 1);
	अगर (ret)
		जाओ error;
	cp->kwq = (काष्ठा kwqe **) cp->kwq_info.pg_arr;

	ret = cnic_alloc_kcq(dev, &cp->kcq1, true);
	अगर (ret)
		जाओ error;

	ret = cnic_alloc_context(dev);
	अगर (ret)
		जाओ error;

	ret = cnic_alloc_uio_rings(dev, 2);
	अगर (ret)
		जाओ error;

	ret = cnic_init_uio(dev);
	अगर (ret)
		जाओ error;

	वापस 0;

error:
	cnic_मुक्त_resc(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक cnic_alloc_bnx2x_context(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	पूर्णांक ctx_blk_size = cp->ethdev->ctx_blk_size;
	पूर्णांक total_mem, blks, i;

	total_mem = BNX2X_CONTEXT_MEM_SIZE * cp->max_cid_space;
	blks = total_mem / ctx_blk_size;
	अगर (total_mem % ctx_blk_size)
		blks++;

	अगर (blks > cp->ethdev->ctx_tbl_len)
		वापस -ENOMEM;

	cp->ctx_arr = kसुस्मृति(blks, माप(काष्ठा cnic_ctx), GFP_KERNEL);
	अगर (cp->ctx_arr == शून्य)
		वापस -ENOMEM;

	cp->ctx_blks = blks;
	cp->ctx_blk_size = ctx_blk_size;
	अगर (!CHIP_IS_E1(bp))
		cp->ctx_align = 0;
	अन्यथा
		cp->ctx_align = ctx_blk_size;

	cp->cids_per_blk = ctx_blk_size / BNX2X_CONTEXT_MEM_SIZE;

	क्रम (i = 0; i < blks; i++) अणु
		cp->ctx_arr[i].ctx =
			dma_alloc_coherent(&dev->pcidev->dev, cp->ctx_blk_size,
					   &cp->ctx_arr[i].mapping,
					   GFP_KERNEL);
		अगर (cp->ctx_arr[i].ctx == शून्य)
			वापस -ENOMEM;

		अगर (cp->ctx_align && cp->ctx_blk_size == ctx_blk_size) अणु
			अगर (cp->ctx_arr[i].mapping & (cp->ctx_align - 1)) अणु
				cnic_मुक्त_context(dev);
				cp->ctx_blk_size += cp->ctx_align;
				i = -1;
				जारी;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cnic_alloc_bnx2x_resc(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	u32 start_cid = ethdev->starting_cid;
	पूर्णांक i, j, n, ret, pages;
	काष्ठा cnic_dma *kwq_16_dma = &cp->kwq_16_data_info;

	cp->max_cid_space = MAX_ISCSI_TBL_SZ;
	cp->iscsi_start_cid = start_cid;
	cp->fcoe_start_cid = start_cid + MAX_ISCSI_TBL_SZ;

	अगर (BNX2X_CHIP_IS_E2_PLUS(bp)) अणु
		cp->max_cid_space += dev->max_fcoe_conn;
		cp->fcoe_init_cid = ethdev->fcoe_init_cid;
		अगर (!cp->fcoe_init_cid)
			cp->fcoe_init_cid = 0x10;
	पूर्ण

	cp->iscsi_tbl = kसुस्मृति(MAX_ISCSI_TBL_SZ, माप(काष्ठा cnic_iscsi),
				GFP_KERNEL);
	अगर (!cp->iscsi_tbl)
		जाओ error;

	cp->ctx_tbl = kसुस्मृति(cp->max_cid_space, माप(काष्ठा cnic_context),
			      GFP_KERNEL);
	अगर (!cp->ctx_tbl)
		जाओ error;

	क्रम (i = 0; i < MAX_ISCSI_TBL_SZ; i++) अणु
		cp->ctx_tbl[i].proto.iscsi = &cp->iscsi_tbl[i];
		cp->ctx_tbl[i].ulp_proto_id = CNIC_ULP_ISCSI;
	पूर्ण

	क्रम (i = MAX_ISCSI_TBL_SZ; i < cp->max_cid_space; i++)
		cp->ctx_tbl[i].ulp_proto_id = CNIC_ULP_FCOE;

	pages = CNIC_PAGE_ALIGN(cp->max_cid_space * CNIC_KWQ16_DATA_SIZE) /
		CNIC_PAGE_SIZE;

	ret = cnic_alloc_dma(dev, kwq_16_dma, pages, 0);
	अगर (ret)
		जाओ error;

	n = CNIC_PAGE_SIZE / CNIC_KWQ16_DATA_SIZE;
	क्रम (i = 0, j = 0; i < cp->max_cid_space; i++) अणु
		दीर्घ off = CNIC_KWQ16_DATA_SIZE * (i % n);

		cp->ctx_tbl[i].kwqe_data = kwq_16_dma->pg_arr[j] + off;
		cp->ctx_tbl[i].kwqe_data_mapping = kwq_16_dma->pg_map_arr[j] +
						   off;

		अगर ((i % n) == (n - 1))
			j++;
	पूर्ण

	ret = cnic_alloc_kcq(dev, &cp->kcq1, false);
	अगर (ret)
		जाओ error;

	अगर (CNIC_SUPPORTS_FCOE(bp)) अणु
		ret = cnic_alloc_kcq(dev, &cp->kcq2, true);
		अगर (ret)
			जाओ error;
	पूर्ण

	pages = CNIC_PAGE_ALIGN(BNX2X_ISCSI_GLB_BUF_SIZE) / CNIC_PAGE_SIZE;
	ret = cnic_alloc_dma(dev, &cp->gbl_buf_info, pages, 0);
	अगर (ret)
		जाओ error;

	ret = cnic_alloc_bnx2x_context(dev);
	अगर (ret)
		जाओ error;

	अगर (cp->ethdev->drv_state & CNIC_DRV_STATE_NO_ISCSI)
		वापस 0;

	cp->bnx2x_def_status_blk = cp->ethdev->irq_arr[1].status_blk;

	cp->l2_rx_ring_size = 15;

	ret = cnic_alloc_uio_rings(dev, 4);
	अगर (ret)
		जाओ error;

	ret = cnic_init_uio(dev);
	अगर (ret)
		जाओ error;

	वापस 0;

error:
	cnic_मुक्त_resc(dev);
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत u32 cnic_kwq_avail(काष्ठा cnic_local *cp)
अणु
	वापस cp->max_kwq_idx -
		((cp->kwq_prod_idx - cp->kwq_con_idx) & cp->max_kwq_idx);
पूर्ण

अटल पूर्णांक cnic_submit_bnx2_kwqes(काष्ठा cnic_dev *dev, काष्ठा kwqe *wqes[],
				  u32 num_wqes)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा kwqe *prod_qe;
	u16 prod, sw_prod, i;

	अगर (!test_bit(CNIC_F_CNIC_UP, &dev->flags))
		वापस -EAGAIN;		/* bnx2 is करोwn */

	spin_lock_bh(&cp->cnic_ulp_lock);
	अगर (num_wqes > cnic_kwq_avail(cp) &&
	    !test_bit(CNIC_LCL_FL_KWQ_INIT, &cp->cnic_local_flags)) अणु
		spin_unlock_bh(&cp->cnic_ulp_lock);
		वापस -EAGAIN;
	पूर्ण

	clear_bit(CNIC_LCL_FL_KWQ_INIT, &cp->cnic_local_flags);

	prod = cp->kwq_prod_idx;
	sw_prod = prod & MAX_KWQ_IDX;
	क्रम (i = 0; i < num_wqes; i++) अणु
		prod_qe = &cp->kwq[KWQ_PG(sw_prod)][KWQ_IDX(sw_prod)];
		स_नकल(prod_qe, wqes[i], माप(काष्ठा kwqe));
		prod++;
		sw_prod = prod & MAX_KWQ_IDX;
	पूर्ण
	cp->kwq_prod_idx = prod;

	CNIC_WR16(dev, cp->kwq_io_addr, cp->kwq_prod_idx);

	spin_unlock_bh(&cp->cnic_ulp_lock);
	वापस 0;
पूर्ण

अटल व्योम *cnic_get_kwqe_16_data(काष्ठा cnic_local *cp, u32 l5_cid,
				   जोड़ l5cm_specअगरic_data *l5_data)
अणु
	काष्ठा cnic_context *ctx = &cp->ctx_tbl[l5_cid];
	dma_addr_t map;

	map = ctx->kwqe_data_mapping;
	l5_data->phy_address.lo = (u64) map & 0xffffffff;
	l5_data->phy_address.hi = (u64) map >> 32;
	वापस ctx->kwqe_data;
पूर्ण

अटल पूर्णांक cnic_submit_kwqe_16(काष्ठा cnic_dev *dev, u32 cmd, u32 cid,
				u32 type, जोड़ l5cm_specअगरic_data *l5_data)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	काष्ठा l5cm_spe kwqe;
	काष्ठा kwqe_16 *kwq[1];
	u16 type_16;
	पूर्णांक ret;

	kwqe.hdr.conn_and_cmd_data =
		cpu_to_le32(((cmd << SPE_HDR_CMD_ID_SHIFT) |
			     BNX2X_HW_CID(bp, cid)));

	type_16 = (type << SPE_HDR_CONN_TYPE_SHIFT) & SPE_HDR_CONN_TYPE;
	type_16 |= (bp->pfid << SPE_HDR_FUNCTION_ID_SHIFT) &
		   SPE_HDR_FUNCTION_ID;

	kwqe.hdr.type = cpu_to_le16(type_16);
	kwqe.hdr.reserved1 = 0;
	kwqe.data.phy_address.lo = cpu_to_le32(l5_data->phy_address.lo);
	kwqe.data.phy_address.hi = cpu_to_le32(l5_data->phy_address.hi);

	kwq[0] = (काष्ठा kwqe_16 *) &kwqe;

	spin_lock_bh(&cp->cnic_ulp_lock);
	ret = cp->ethdev->drv_submit_kwqes_16(dev->netdev, kwq, 1);
	spin_unlock_bh(&cp->cnic_ulp_lock);

	अगर (ret == 1)
		वापस 0;

	वापस ret;
पूर्ण

अटल व्योम cnic_reply_bnx2x_kcqes(काष्ठा cnic_dev *dev, पूर्णांक ulp_type,
				   काष्ठा kcqe *cqes[], u32 num_cqes)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_ulp_ops *ulp_ops;

	rcu_पढ़ो_lock();
	ulp_ops = rcu_dereference(cp->ulp_ops[ulp_type]);
	अगर (likely(ulp_ops)) अणु
		ulp_ops->indicate_kcqes(cp->ulp_handle[ulp_type],
					  cqes, num_cqes);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम cnic_bnx2x_set_tcp_options(काष्ठा cnic_dev *dev, पूर्णांक समय_stamps,
				       पूर्णांक en_tcp_dack)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	u8 xstorm_flags = XSTORM_L5CM_TCP_FLAGS_WND_SCL_EN;
	u16 tstorm_flags = 0;

	अगर (समय_stamps) अणु
		xstorm_flags |= XSTORM_L5CM_TCP_FLAGS_TS_ENABLED;
		tstorm_flags |= TSTORM_L5CM_TCP_FLAGS_TS_ENABLED;
	पूर्ण
	अगर (en_tcp_dack)
		tstorm_flags |= TSTORM_L5CM_TCP_FLAGS_DELAYED_ACK_EN;

	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_TCP_VARS_FLAGS_OFFSET(bp->pfid), xstorm_flags);

	CNIC_WR16(dev, BAR_TSTRORM_INTMEM +
		  TSTORM_ISCSI_TCP_VARS_FLAGS_OFFSET(bp->pfid), tstorm_flags);
पूर्ण

अटल पूर्णांक cnic_bnx2x_iscsi_init1(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	काष्ठा iscsi_kwqe_init1 *req1 = (काष्ठा iscsi_kwqe_init1 *) kwqe;
	पूर्णांक hq_bds, pages;
	u32 pfid = bp->pfid;

	cp->num_iscsi_tasks = req1->num_tasks_per_conn;
	cp->num_ccells = req1->num_ccells_per_conn;
	cp->task_array_size = BNX2X_ISCSI_TASK_CONTEXT_SIZE *
			      cp->num_iscsi_tasks;
	cp->r2tq_size = cp->num_iscsi_tasks * BNX2X_ISCSI_MAX_PENDING_R2TS *
			BNX2X_ISCSI_R2TQE_SIZE;
	cp->hq_size = cp->num_ccells * BNX2X_ISCSI_HQ_BD_SIZE;
	pages = CNIC_PAGE_ALIGN(cp->hq_size) / CNIC_PAGE_SIZE;
	hq_bds = pages * (CNIC_PAGE_SIZE / BNX2X_ISCSI_HQ_BD_SIZE);
	cp->num_cqs = req1->num_cqs;

	अगर (!dev->max_iscsi_conn)
		वापस 0;

	/* init Tstorm RAM */
	CNIC_WR16(dev, BAR_TSTRORM_INTMEM + TSTORM_ISCSI_RQ_SIZE_OFFSET(pfid),
		  req1->rq_num_wqes);
	CNIC_WR16(dev, BAR_TSTRORM_INTMEM + TSTORM_ISCSI_PAGE_SIZE_OFFSET(pfid),
		  CNIC_PAGE_SIZE);
	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_PAGE_SIZE_LOG_OFFSET(pfid), CNIC_PAGE_BITS);
	CNIC_WR16(dev, BAR_TSTRORM_INTMEM +
		  TSTORM_ISCSI_NUM_OF_TASKS_OFFSET(pfid),
		  req1->num_tasks_per_conn);

	/* init Ustorm RAM */
	CNIC_WR16(dev, BAR_USTRORM_INTMEM +
		  USTORM_ISCSI_RQ_BUFFER_SIZE_OFFSET(pfid),
		  req1->rq_buffer_size);
	CNIC_WR16(dev, BAR_USTRORM_INTMEM + USTORM_ISCSI_PAGE_SIZE_OFFSET(pfid),
		  CNIC_PAGE_SIZE);
	CNIC_WR8(dev, BAR_USTRORM_INTMEM +
		 USTORM_ISCSI_PAGE_SIZE_LOG_OFFSET(pfid), CNIC_PAGE_BITS);
	CNIC_WR16(dev, BAR_USTRORM_INTMEM +
		  USTORM_ISCSI_NUM_OF_TASKS_OFFSET(pfid),
		  req1->num_tasks_per_conn);
	CNIC_WR16(dev, BAR_USTRORM_INTMEM + USTORM_ISCSI_RQ_SIZE_OFFSET(pfid),
		  req1->rq_num_wqes);
	CNIC_WR16(dev, BAR_USTRORM_INTMEM + USTORM_ISCSI_CQ_SIZE_OFFSET(pfid),
		  req1->cq_num_wqes);
	CNIC_WR16(dev, BAR_USTRORM_INTMEM + USTORM_ISCSI_R2TQ_SIZE_OFFSET(pfid),
		  cp->num_iscsi_tasks * BNX2X_ISCSI_MAX_PENDING_R2TS);

	/* init Xstorm RAM */
	CNIC_WR16(dev, BAR_XSTRORM_INTMEM + XSTORM_ISCSI_PAGE_SIZE_OFFSET(pfid),
		  CNIC_PAGE_SIZE);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_PAGE_SIZE_LOG_OFFSET(pfid), CNIC_PAGE_BITS);
	CNIC_WR16(dev, BAR_XSTRORM_INTMEM +
		  XSTORM_ISCSI_NUM_OF_TASKS_OFFSET(pfid),
		  req1->num_tasks_per_conn);
	CNIC_WR16(dev, BAR_XSTRORM_INTMEM + XSTORM_ISCSI_HQ_SIZE_OFFSET(pfid),
		  hq_bds);
	CNIC_WR16(dev, BAR_XSTRORM_INTMEM + XSTORM_ISCSI_SQ_SIZE_OFFSET(pfid),
		  req1->num_tasks_per_conn);
	CNIC_WR16(dev, BAR_XSTRORM_INTMEM + XSTORM_ISCSI_R2TQ_SIZE_OFFSET(pfid),
		  cp->num_iscsi_tasks * BNX2X_ISCSI_MAX_PENDING_R2TS);

	/* init Cstorm RAM */
	CNIC_WR16(dev, BAR_CSTRORM_INTMEM + CSTORM_ISCSI_PAGE_SIZE_OFFSET(pfid),
		  CNIC_PAGE_SIZE);
	CNIC_WR8(dev, BAR_CSTRORM_INTMEM +
		 CSTORM_ISCSI_PAGE_SIZE_LOG_OFFSET(pfid), CNIC_PAGE_BITS);
	CNIC_WR16(dev, BAR_CSTRORM_INTMEM +
		  CSTORM_ISCSI_NUM_OF_TASKS_OFFSET(pfid),
		  req1->num_tasks_per_conn);
	CNIC_WR16(dev, BAR_CSTRORM_INTMEM + CSTORM_ISCSI_CQ_SIZE_OFFSET(pfid),
		  req1->cq_num_wqes);
	CNIC_WR16(dev, BAR_CSTRORM_INTMEM + CSTORM_ISCSI_HQ_SIZE_OFFSET(pfid),
		  hq_bds);

	cnic_bnx2x_set_tcp_options(dev,
			req1->flags & ISCSI_KWQE_INIT1_TIME_STAMPS_ENABLE,
			req1->flags & ISCSI_KWQE_INIT1_DELAYED_ACK_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक cnic_bnx2x_iscsi_init2(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	काष्ठा iscsi_kwqe_init2 *req2 = (काष्ठा iscsi_kwqe_init2 *) kwqe;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	u32 pfid = bp->pfid;
	काष्ठा iscsi_kcqe kcqe;
	काष्ठा kcqe *cqes[1];

	स_रखो(&kcqe, 0, माप(kcqe));
	अगर (!dev->max_iscsi_conn) अणु
		kcqe.completion_status =
			ISCSI_KCQE_COMPLETION_STATUS_ISCSI_NOT_SUPPORTED;
		जाओ करोne;
	पूर्ण

	CNIC_WR(dev, BAR_TSTRORM_INTMEM +
		TSTORM_ISCSI_ERROR_BITMAP_OFFSET(pfid), req2->error_bit_map[0]);
	CNIC_WR(dev, BAR_TSTRORM_INTMEM +
		TSTORM_ISCSI_ERROR_BITMAP_OFFSET(pfid) + 4,
		req2->error_bit_map[1]);

	CNIC_WR16(dev, BAR_USTRORM_INTMEM +
		  USTORM_ISCSI_CQ_SQN_SIZE_OFFSET(pfid), req2->max_cq_sqn);
	CNIC_WR(dev, BAR_USTRORM_INTMEM +
		USTORM_ISCSI_ERROR_BITMAP_OFFSET(pfid), req2->error_bit_map[0]);
	CNIC_WR(dev, BAR_USTRORM_INTMEM +
		USTORM_ISCSI_ERROR_BITMAP_OFFSET(pfid) + 4,
		req2->error_bit_map[1]);

	CNIC_WR16(dev, BAR_CSTRORM_INTMEM +
		  CSTORM_ISCSI_CQ_SQN_SIZE_OFFSET(pfid), req2->max_cq_sqn);

	kcqe.completion_status = ISCSI_KCQE_COMPLETION_STATUS_SUCCESS;

करोne:
	kcqe.op_code = ISCSI_KCQE_OPCODE_INIT;
	cqes[0] = (काष्ठा kcqe *) &kcqe;
	cnic_reply_bnx2x_kcqes(dev, CNIC_ULP_ISCSI, cqes, 1);

	वापस 0;
पूर्ण

अटल व्योम cnic_मुक्त_bnx2x_conn_resc(काष्ठा cnic_dev *dev, u32 l5_cid)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_context *ctx = &cp->ctx_tbl[l5_cid];

	अगर (ctx->ulp_proto_id == CNIC_ULP_ISCSI) अणु
		काष्ठा cnic_iscsi *iscsi = ctx->proto.iscsi;

		cnic_मुक्त_dma(dev, &iscsi->hq_info);
		cnic_मुक्त_dma(dev, &iscsi->r2tq_info);
		cnic_मुक्त_dma(dev, &iscsi->task_array_info);
		cnic_मुक्त_id(&cp->cid_tbl, ctx->cid);
	पूर्ण अन्यथा अणु
		cnic_मुक्त_id(&cp->fcoe_cid_tbl, ctx->cid);
	पूर्ण

	ctx->cid = 0;
पूर्ण

अटल पूर्णांक cnic_alloc_bnx2x_conn_resc(काष्ठा cnic_dev *dev, u32 l5_cid)
अणु
	u32 cid;
	पूर्णांक ret, pages;
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_context *ctx = &cp->ctx_tbl[l5_cid];
	काष्ठा cnic_iscsi *iscsi = ctx->proto.iscsi;

	अगर (ctx->ulp_proto_id == CNIC_ULP_FCOE) अणु
		cid = cnic_alloc_new_id(&cp->fcoe_cid_tbl);
		अगर (cid == -1) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
		ctx->cid = cid;
		वापस 0;
	पूर्ण

	cid = cnic_alloc_new_id(&cp->cid_tbl);
	अगर (cid == -1) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	ctx->cid = cid;
	pages = CNIC_PAGE_ALIGN(cp->task_array_size) / CNIC_PAGE_SIZE;

	ret = cnic_alloc_dma(dev, &iscsi->task_array_info, pages, 1);
	अगर (ret)
		जाओ error;

	pages = CNIC_PAGE_ALIGN(cp->r2tq_size) / CNIC_PAGE_SIZE;
	ret = cnic_alloc_dma(dev, &iscsi->r2tq_info, pages, 1);
	अगर (ret)
		जाओ error;

	pages = CNIC_PAGE_ALIGN(cp->hq_size) / CNIC_PAGE_SIZE;
	ret = cnic_alloc_dma(dev, &iscsi->hq_info, pages, 1);
	अगर (ret)
		जाओ error;

	वापस 0;

error:
	cnic_मुक्त_bnx2x_conn_resc(dev, l5_cid);
	वापस ret;
पूर्ण

अटल व्योम *cnic_get_bnx2x_ctx(काष्ठा cnic_dev *dev, u32 cid, पूर्णांक init,
				काष्ठा regpair *ctx_addr)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	पूर्णांक blk = (cid - ethdev->starting_cid) / cp->cids_per_blk;
	पूर्णांक off = (cid - ethdev->starting_cid) % cp->cids_per_blk;
	अचिन्हित दीर्घ align_off = 0;
	dma_addr_t ctx_map;
	व्योम *ctx;

	अगर (cp->ctx_align) अणु
		अचिन्हित दीर्घ mask = cp->ctx_align - 1;

		अगर (cp->ctx_arr[blk].mapping & mask)
			align_off = cp->ctx_align -
				    (cp->ctx_arr[blk].mapping & mask);
	पूर्ण
	ctx_map = cp->ctx_arr[blk].mapping + align_off +
		(off * BNX2X_CONTEXT_MEM_SIZE);
	ctx = cp->ctx_arr[blk].ctx + align_off +
	      (off * BNX2X_CONTEXT_MEM_SIZE);
	अगर (init)
		स_रखो(ctx, 0, BNX2X_CONTEXT_MEM_SIZE);

	ctx_addr->lo = ctx_map & 0xffffffff;
	ctx_addr->hi = (u64) ctx_map >> 32;
	वापस ctx;
पूर्ण

अटल पूर्णांक cnic_setup_bnx2x_ctx(काष्ठा cnic_dev *dev, काष्ठा kwqe *wqes[],
				u32 num)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	काष्ठा iscsi_kwqe_conn_offload1 *req1 =
			(काष्ठा iscsi_kwqe_conn_offload1 *) wqes[0];
	काष्ठा iscsi_kwqe_conn_offload2 *req2 =
			(काष्ठा iscsi_kwqe_conn_offload2 *) wqes[1];
	काष्ठा iscsi_kwqe_conn_offload3 *req3;
	काष्ठा cnic_context *ctx = &cp->ctx_tbl[req1->iscsi_conn_id];
	काष्ठा cnic_iscsi *iscsi = ctx->proto.iscsi;
	u32 cid = ctx->cid;
	u32 hw_cid = BNX2X_HW_CID(bp, cid);
	काष्ठा iscsi_context *ictx;
	काष्ठा regpair context_addr;
	पूर्णांक i, j, n = 2, n_max;
	u8 port = BP_PORT(bp);

	ctx->ctx_flags = 0;
	अगर (!req2->num_additional_wqes)
		वापस -EINVAL;

	n_max = req2->num_additional_wqes + 2;

	ictx = cnic_get_bnx2x_ctx(dev, cid, 1, &context_addr);
	अगर (ictx == शून्य)
		वापस -ENOMEM;

	req3 = (काष्ठा iscsi_kwqe_conn_offload3 *) wqes[n++];

	ictx->xstorm_ag_context.hq_prod = 1;

	ictx->xstorm_st_context.iscsi.first_burst_length =
		ISCSI_DEF_FIRST_BURST_LEN;
	ictx->xstorm_st_context.iscsi.max_send_pdu_length =
		ISCSI_DEF_MAX_RECV_SEG_LEN;
	ictx->xstorm_st_context.iscsi.sq_pbl_base.lo =
		req1->sq_page_table_addr_lo;
	ictx->xstorm_st_context.iscsi.sq_pbl_base.hi =
		req1->sq_page_table_addr_hi;
	ictx->xstorm_st_context.iscsi.sq_curr_pbe.lo = req2->sq_first_pte.hi;
	ictx->xstorm_st_context.iscsi.sq_curr_pbe.hi = req2->sq_first_pte.lo;
	ictx->xstorm_st_context.iscsi.hq_pbl_base.lo =
		iscsi->hq_info.pgtbl_map & 0xffffffff;
	ictx->xstorm_st_context.iscsi.hq_pbl_base.hi =
		(u64) iscsi->hq_info.pgtbl_map >> 32;
	ictx->xstorm_st_context.iscsi.hq_curr_pbe_base.lo =
		iscsi->hq_info.pgtbl[0];
	ictx->xstorm_st_context.iscsi.hq_curr_pbe_base.hi =
		iscsi->hq_info.pgtbl[1];
	ictx->xstorm_st_context.iscsi.r2tq_pbl_base.lo =
		iscsi->r2tq_info.pgtbl_map & 0xffffffff;
	ictx->xstorm_st_context.iscsi.r2tq_pbl_base.hi =
		(u64) iscsi->r2tq_info.pgtbl_map >> 32;
	ictx->xstorm_st_context.iscsi.r2tq_curr_pbe_base.lo =
		iscsi->r2tq_info.pgtbl[0];
	ictx->xstorm_st_context.iscsi.r2tq_curr_pbe_base.hi =
		iscsi->r2tq_info.pgtbl[1];
	ictx->xstorm_st_context.iscsi.task_pbl_base.lo =
		iscsi->task_array_info.pgtbl_map & 0xffffffff;
	ictx->xstorm_st_context.iscsi.task_pbl_base.hi =
		(u64) iscsi->task_array_info.pgtbl_map >> 32;
	ictx->xstorm_st_context.iscsi.task_pbl_cache_idx =
		BNX2X_ISCSI_PBL_NOT_CACHED;
	ictx->xstorm_st_context.iscsi.flags.flags |=
		XSTORM_ISCSI_CONTEXT_FLAGS_B_IMMEDIATE_DATA;
	ictx->xstorm_st_context.iscsi.flags.flags |=
		XSTORM_ISCSI_CONTEXT_FLAGS_B_INITIAL_R2T;
	ictx->xstorm_st_context.common.ethernet.reserved_vlan_type =
		ETH_P_8021Q;
	अगर (BNX2X_CHIP_IS_E2_PLUS(bp) &&
	    bp->common.chip_port_mode == CHIP_2_PORT_MODE) अणु

		port = 0;
	पूर्ण
	ictx->xstorm_st_context.common.flags =
		1 << XSTORM_COMMON_CONTEXT_SECTION_PHYSQ_INITIALIZED_SHIFT;
	ictx->xstorm_st_context.common.flags =
		port << XSTORM_COMMON_CONTEXT_SECTION_PBF_PORT_SHIFT;

	ictx->tstorm_st_context.iscsi.hdr_bytes_2_fetch = ISCSI_HEADER_SIZE;
	/* TSTORM requires the base address of RQ DB & not PTE */
	ictx->tstorm_st_context.iscsi.rq_db_phy_addr.lo =
		req2->rq_page_table_addr_lo & CNIC_PAGE_MASK;
	ictx->tstorm_st_context.iscsi.rq_db_phy_addr.hi =
		req2->rq_page_table_addr_hi;
	ictx->tstorm_st_context.iscsi.iscsi_conn_id = req1->iscsi_conn_id;
	ictx->tstorm_st_context.tcp.cwnd = 0x5A8;
	ictx->tstorm_st_context.tcp.flags2 |=
		TSTORM_TCP_ST_CONTEXT_SECTION_DA_EN;
	ictx->tstorm_st_context.tcp.ooo_support_mode =
		TCP_TSTORM_OOO_DROP_AND_PROC_ACK;

	ictx->समयrs_context.flags |= TIMERS_BLOCK_CONTEXT_CONN_VALID_FLG;

	ictx->ustorm_st_context.ring.rq.pbl_base.lo =
		req2->rq_page_table_addr_lo;
	ictx->ustorm_st_context.ring.rq.pbl_base.hi =
		req2->rq_page_table_addr_hi;
	ictx->ustorm_st_context.ring.rq.curr_pbe.lo = req3->qp_first_pte[0].hi;
	ictx->ustorm_st_context.ring.rq.curr_pbe.hi = req3->qp_first_pte[0].lo;
	ictx->ustorm_st_context.ring.r2tq.pbl_base.lo =
		iscsi->r2tq_info.pgtbl_map & 0xffffffff;
	ictx->ustorm_st_context.ring.r2tq.pbl_base.hi =
		(u64) iscsi->r2tq_info.pgtbl_map >> 32;
	ictx->ustorm_st_context.ring.r2tq.curr_pbe.lo =
		iscsi->r2tq_info.pgtbl[0];
	ictx->ustorm_st_context.ring.r2tq.curr_pbe.hi =
		iscsi->r2tq_info.pgtbl[1];
	ictx->ustorm_st_context.ring.cq_pbl_base.lo =
		req1->cq_page_table_addr_lo;
	ictx->ustorm_st_context.ring.cq_pbl_base.hi =
		req1->cq_page_table_addr_hi;
	ictx->ustorm_st_context.ring.cq[0].cq_sn = ISCSI_INITIAL_SN;
	ictx->ustorm_st_context.ring.cq[0].curr_pbe.lo = req2->cq_first_pte.hi;
	ictx->ustorm_st_context.ring.cq[0].curr_pbe.hi = req2->cq_first_pte.lo;
	ictx->ustorm_st_context.task_pbe_cache_index =
		BNX2X_ISCSI_PBL_NOT_CACHED;
	ictx->ustorm_st_context.task_pdu_cache_index =
		BNX2X_ISCSI_PDU_HEADER_NOT_CACHED;

	क्रम (i = 1, j = 1; i < cp->num_cqs; i++, j++) अणु
		अगर (j == 3) अणु
			अगर (n >= n_max)
				अवरोध;
			req3 = (काष्ठा iscsi_kwqe_conn_offload3 *) wqes[n++];
			j = 0;
		पूर्ण
		ictx->ustorm_st_context.ring.cq[i].cq_sn = ISCSI_INITIAL_SN;
		ictx->ustorm_st_context.ring.cq[i].curr_pbe.lo =
			req3->qp_first_pte[j].hi;
		ictx->ustorm_st_context.ring.cq[i].curr_pbe.hi =
			req3->qp_first_pte[j].lo;
	पूर्ण

	ictx->ustorm_st_context.task_pbl_base.lo =
		iscsi->task_array_info.pgtbl_map & 0xffffffff;
	ictx->ustorm_st_context.task_pbl_base.hi =
		(u64) iscsi->task_array_info.pgtbl_map >> 32;
	ictx->ustorm_st_context.tce_phy_addr.lo =
		iscsi->task_array_info.pgtbl[0];
	ictx->ustorm_st_context.tce_phy_addr.hi =
		iscsi->task_array_info.pgtbl[1];
	ictx->ustorm_st_context.iscsi_conn_id = req1->iscsi_conn_id;
	ictx->ustorm_st_context.num_cqs = cp->num_cqs;
	ictx->ustorm_st_context.negotiated_rx |= ISCSI_DEF_MAX_RECV_SEG_LEN;
	ictx->ustorm_st_context.negotiated_rx_and_flags |=
		ISCSI_DEF_MAX_BURST_LEN;
	ictx->ustorm_st_context.negotiated_rx |=
		ISCSI_DEFAULT_MAX_OUTSTANDING_R2T <<
		USTORM_ISCSI_ST_CONTEXT_MAX_OUTSTANDING_R2TS_SHIFT;

	ictx->cstorm_st_context.hq_pbl_base.lo =
		iscsi->hq_info.pgtbl_map & 0xffffffff;
	ictx->cstorm_st_context.hq_pbl_base.hi =
		(u64) iscsi->hq_info.pgtbl_map >> 32;
	ictx->cstorm_st_context.hq_curr_pbe.lo = iscsi->hq_info.pgtbl[0];
	ictx->cstorm_st_context.hq_curr_pbe.hi = iscsi->hq_info.pgtbl[1];
	ictx->cstorm_st_context.task_pbl_base.lo =
		iscsi->task_array_info.pgtbl_map & 0xffffffff;
	ictx->cstorm_st_context.task_pbl_base.hi =
		(u64) iscsi->task_array_info.pgtbl_map >> 32;
	/* CSTORM and USTORM initialization is dअगरferent, CSTORM requires
	 * CQ DB base & not PTE addr */
	ictx->cstorm_st_context.cq_db_base.lo =
		req1->cq_page_table_addr_lo & CNIC_PAGE_MASK;
	ictx->cstorm_st_context.cq_db_base.hi = req1->cq_page_table_addr_hi;
	ictx->cstorm_st_context.iscsi_conn_id = req1->iscsi_conn_id;
	ictx->cstorm_st_context.cq_proc_en_bit_map = (1 << cp->num_cqs) - 1;
	क्रम (i = 0; i < cp->num_cqs; i++) अणु
		ictx->cstorm_st_context.cq_c_prod_sqn_arr.sqn[i] =
			ISCSI_INITIAL_SN;
		ictx->cstorm_st_context.cq_c_sqn_2_notअगरy_arr.sqn[i] =
			ISCSI_INITIAL_SN;
	पूर्ण

	ictx->xstorm_ag_context.cdu_reserved =
		CDU_RSRVD_VALUE_TYPE_A(hw_cid, CDU_REGION_NUMBER_XCM_AG,
				       ISCSI_CONNECTION_TYPE);
	ictx->ustorm_ag_context.cdu_usage =
		CDU_RSRVD_VALUE_TYPE_A(hw_cid, CDU_REGION_NUMBER_UCM_AG,
				       ISCSI_CONNECTION_TYPE);
	वापस 0;

पूर्ण

अटल पूर्णांक cnic_bnx2x_iscsi_ofld1(काष्ठा cnic_dev *dev, काष्ठा kwqe *wqes[],
				   u32 num, पूर्णांक *work)
अणु
	काष्ठा iscsi_kwqe_conn_offload1 *req1;
	काष्ठा iscsi_kwqe_conn_offload2 *req2;
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	काष्ठा cnic_context *ctx;
	काष्ठा iscsi_kcqe kcqe;
	काष्ठा kcqe *cqes[1];
	u32 l5_cid;
	पूर्णांक ret = 0;

	अगर (num < 2) अणु
		*work = num;
		वापस -EINVAL;
	पूर्ण

	req1 = (काष्ठा iscsi_kwqe_conn_offload1 *) wqes[0];
	req2 = (काष्ठा iscsi_kwqe_conn_offload2 *) wqes[1];
	अगर ((num - 2) < req2->num_additional_wqes) अणु
		*work = num;
		वापस -EINVAL;
	पूर्ण
	*work = 2 + req2->num_additional_wqes;

	l5_cid = req1->iscsi_conn_id;
	अगर (l5_cid >= MAX_ISCSI_TBL_SZ)
		वापस -EINVAL;

	स_रखो(&kcqe, 0, माप(kcqe));
	kcqe.op_code = ISCSI_KCQE_OPCODE_OFFLOAD_CONN;
	kcqe.iscsi_conn_id = l5_cid;
	kcqe.completion_status = ISCSI_KCQE_COMPLETION_STATUS_CTX_ALLOC_FAILURE;

	ctx = &cp->ctx_tbl[l5_cid];
	अगर (test_bit(CTX_FL_OFFLD_START, &ctx->ctx_flags)) अणु
		kcqe.completion_status =
			ISCSI_KCQE_COMPLETION_STATUS_CID_BUSY;
		जाओ करोne;
	पूर्ण

	अगर (atomic_inc_वापस(&cp->iscsi_conn) > dev->max_iscsi_conn) अणु
		atomic_dec(&cp->iscsi_conn);
		जाओ करोne;
	पूर्ण
	ret = cnic_alloc_bnx2x_conn_resc(dev, l5_cid);
	अगर (ret) अणु
		atomic_dec(&cp->iscsi_conn);
		जाओ करोne;
	पूर्ण
	ret = cnic_setup_bnx2x_ctx(dev, wqes, num);
	अगर (ret < 0) अणु
		cnic_मुक्त_bnx2x_conn_resc(dev, l5_cid);
		atomic_dec(&cp->iscsi_conn);
		जाओ करोne;
	पूर्ण

	kcqe.completion_status = ISCSI_KCQE_COMPLETION_STATUS_SUCCESS;
	kcqe.iscsi_conn_context_id = BNX2X_HW_CID(bp, cp->ctx_tbl[l5_cid].cid);

करोne:
	cqes[0] = (काष्ठा kcqe *) &kcqe;
	cnic_reply_bnx2x_kcqes(dev, CNIC_ULP_ISCSI, cqes, 1);
	वापस 0;
पूर्ण


अटल पूर्णांक cnic_bnx2x_iscsi_update(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा iscsi_kwqe_conn_update *req =
		(काष्ठा iscsi_kwqe_conn_update *) kwqe;
	व्योम *data;
	जोड़ l5cm_specअगरic_data l5_data;
	u32 l5_cid, cid = BNX2X_SW_CID(req->context_id);
	पूर्णांक ret;

	अगर (cnic_get_l5_cid(cp, cid, &l5_cid) != 0)
		वापस -EINVAL;

	data = cnic_get_kwqe_16_data(cp, l5_cid, &l5_data);
	अगर (!data)
		वापस -ENOMEM;

	स_नकल(data, kwqe, माप(काष्ठा kwqe));

	ret = cnic_submit_kwqe_16(dev, ISCSI_RAMROD_CMD_ID_UPDATE_CONN,
			req->context_id, ISCSI_CONNECTION_TYPE, &l5_data);
	वापस ret;
पूर्ण

अटल पूर्णांक cnic_bnx2x_destroy_ramrod(काष्ठा cnic_dev *dev, u32 l5_cid)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	काष्ठा cnic_context *ctx = &cp->ctx_tbl[l5_cid];
	जोड़ l5cm_specअगरic_data l5_data;
	पूर्णांक ret;
	u32 hw_cid;

	init_रुकोqueue_head(&ctx->रुकोq);
	ctx->रुको_cond = 0;
	स_रखो(&l5_data, 0, माप(l5_data));
	hw_cid = BNX2X_HW_CID(bp, ctx->cid);

	ret = cnic_submit_kwqe_16(dev, RAMROD_CMD_ID_COMMON_CFC_DEL,
				  hw_cid, NONE_CONNECTION_TYPE, &l5_data);

	अगर (ret == 0) अणु
		रुको_event_समयout(ctx->रुकोq, ctx->रुको_cond, CNIC_RAMROD_TMO);
		अगर (unlikely(test_bit(CTX_FL_CID_ERROR, &ctx->ctx_flags)))
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cnic_bnx2x_iscsi_destroy(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा iscsi_kwqe_conn_destroy *req =
		(काष्ठा iscsi_kwqe_conn_destroy *) kwqe;
	u32 l5_cid = req->reserved0;
	काष्ठा cnic_context *ctx = &cp->ctx_tbl[l5_cid];
	पूर्णांक ret = 0;
	काष्ठा iscsi_kcqe kcqe;
	काष्ठा kcqe *cqes[1];

	अगर (!test_bit(CTX_FL_OFFLD_START, &ctx->ctx_flags))
		जाओ skip_cfc_delete;

	अगर (!समय_after(jअगरfies, ctx->बारtamp + (2 * HZ))) अणु
		अचिन्हित दीर्घ delta = ctx->बारtamp + (2 * HZ) - jअगरfies;

		अगर (delta > (2 * HZ))
			delta = 0;

		set_bit(CTX_FL_DELETE_WAIT, &ctx->ctx_flags);
		queue_delayed_work(cnic_wq, &cp->delete_task, delta);
		जाओ destroy_reply;
	पूर्ण

	ret = cnic_bnx2x_destroy_ramrod(dev, l5_cid);

skip_cfc_delete:
	cnic_मुक्त_bnx2x_conn_resc(dev, l5_cid);

	अगर (!ret) अणु
		atomic_dec(&cp->iscsi_conn);
		clear_bit(CTX_FL_OFFLD_START, &ctx->ctx_flags);
	पूर्ण

destroy_reply:
	स_रखो(&kcqe, 0, माप(kcqe));
	kcqe.op_code = ISCSI_KCQE_OPCODE_DESTROY_CONN;
	kcqe.iscsi_conn_id = l5_cid;
	kcqe.completion_status = ISCSI_KCQE_COMPLETION_STATUS_SUCCESS;
	kcqe.iscsi_conn_context_id = req->context_id;

	cqes[0] = (काष्ठा kcqe *) &kcqe;
	cnic_reply_bnx2x_kcqes(dev, CNIC_ULP_ISCSI, cqes, 1);

	वापस 0;
पूर्ण

अटल व्योम cnic_init_storm_conn_bufs(काष्ठा cnic_dev *dev,
				      काष्ठा l4_kwq_connect_req1 *kwqe1,
				      काष्ठा l4_kwq_connect_req3 *kwqe3,
				      काष्ठा l5cm_active_conn_buffer *conn_buf)
अणु
	काष्ठा l5cm_conn_addr_params *conn_addr = &conn_buf->conn_addr_buf;
	काष्ठा l5cm_xstorm_conn_buffer *xstorm_buf =
		&conn_buf->xstorm_conn_buffer;
	काष्ठा l5cm_tstorm_conn_buffer *tstorm_buf =
		&conn_buf->tstorm_conn_buffer;
	काष्ठा regpair context_addr;
	u32 cid = BNX2X_SW_CID(kwqe1->cid);
	काष्ठा in6_addr src_ip, dst_ip;
	पूर्णांक i;
	u32 *addrp;

	addrp = (u32 *) &conn_addr->local_ip_addr;
	क्रम (i = 0; i < 4; i++, addrp++)
		src_ip.in6_u.u6_addr32[i] = cpu_to_be32(*addrp);

	addrp = (u32 *) &conn_addr->remote_ip_addr;
	क्रम (i = 0; i < 4; i++, addrp++)
		dst_ip.in6_u.u6_addr32[i] = cpu_to_be32(*addrp);

	cnic_get_bnx2x_ctx(dev, cid, 0, &context_addr);

	xstorm_buf->context_addr.hi = context_addr.hi;
	xstorm_buf->context_addr.lo = context_addr.lo;
	xstorm_buf->mss = 0xffff;
	xstorm_buf->rcv_buf = kwqe3->rcv_buf;
	अगर (kwqe1->tcp_flags & L4_KWQ_CONNECT_REQ1_NAGLE_ENABLE)
		xstorm_buf->params |= L5CM_XSTORM_CONN_BUFFER_NAGLE_ENABLE;
	xstorm_buf->pseuकरो_header_checksum =
		swab16(~csum_ipv6_magic(&src_ip, &dst_ip, 0, IPPROTO_TCP, 0));

	अगर (kwqe3->ka_समयout) अणु
		tstorm_buf->ka_enable = 1;
		tstorm_buf->ka_समयout = kwqe3->ka_समयout;
		tstorm_buf->ka_पूर्णांकerval = kwqe3->ka_पूर्णांकerval;
		tstorm_buf->ka_max_probe_count = kwqe3->ka_max_probe_count;
	पूर्ण
	tstorm_buf->max_rt_समय = 0xffffffff;
पूर्ण

अटल व्योम cnic_init_bnx2x_mac(काष्ठा cnic_dev *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	u32 pfid = bp->pfid;
	u8 *mac = dev->mac_addr;

	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_LOCAL_MAC_ADDR0_OFFSET(pfid), mac[0]);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_LOCAL_MAC_ADDR1_OFFSET(pfid), mac[1]);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_LOCAL_MAC_ADDR2_OFFSET(pfid), mac[2]);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_LOCAL_MAC_ADDR3_OFFSET(pfid), mac[3]);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_LOCAL_MAC_ADDR4_OFFSET(pfid), mac[4]);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_LOCAL_MAC_ADDR5_OFFSET(pfid), mac[5]);

	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_TCP_VARS_LSB_LOCAL_MAC_ADDR_OFFSET(pfid), mac[5]);
	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_TCP_VARS_LSB_LOCAL_MAC_ADDR_OFFSET(pfid) + 1,
		 mac[4]);
	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_TCP_VARS_MID_LOCAL_MAC_ADDR_OFFSET(pfid), mac[3]);
	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_TCP_VARS_MID_LOCAL_MAC_ADDR_OFFSET(pfid) + 1,
		 mac[2]);
	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_TCP_VARS_MSB_LOCAL_MAC_ADDR_OFFSET(pfid), mac[1]);
	CNIC_WR8(dev, BAR_TSTRORM_INTMEM +
		 TSTORM_ISCSI_TCP_VARS_MSB_LOCAL_MAC_ADDR_OFFSET(pfid) + 1,
		 mac[0]);
पूर्ण

अटल पूर्णांक cnic_bnx2x_connect(काष्ठा cnic_dev *dev, काष्ठा kwqe *wqes[],
			      u32 num, पूर्णांक *work)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	काष्ठा l4_kwq_connect_req1 *kwqe1 =
		(काष्ठा l4_kwq_connect_req1 *) wqes[0];
	काष्ठा l4_kwq_connect_req3 *kwqe3;
	काष्ठा l5cm_active_conn_buffer *conn_buf;
	काष्ठा l5cm_conn_addr_params *conn_addr;
	जोड़ l5cm_specअगरic_data l5_data;
	u32 l5_cid = kwqe1->pg_cid;
	काष्ठा cnic_sock *csk = &cp->csk_tbl[l5_cid];
	काष्ठा cnic_context *ctx = &cp->ctx_tbl[l5_cid];
	पूर्णांक ret;

	अगर (num < 2) अणु
		*work = num;
		वापस -EINVAL;
	पूर्ण

	अगर (kwqe1->conn_flags & L4_KWQ_CONNECT_REQ1_IP_V6)
		*work = 3;
	अन्यथा
		*work = 2;

	अगर (num < *work) अणु
		*work = num;
		वापस -EINVAL;
	पूर्ण

	अगर (माप(*conn_buf) > CNIC_KWQ16_DATA_SIZE) अणु
		netdev_err(dev->netdev, "conn_buf size too big\n");
		वापस -ENOMEM;
	पूर्ण
	conn_buf = cnic_get_kwqe_16_data(cp, l5_cid, &l5_data);
	अगर (!conn_buf)
		वापस -ENOMEM;

	स_रखो(conn_buf, 0, माप(*conn_buf));

	conn_addr = &conn_buf->conn_addr_buf;
	conn_addr->remote_addr_0 = csk->ha[0];
	conn_addr->remote_addr_1 = csk->ha[1];
	conn_addr->remote_addr_2 = csk->ha[2];
	conn_addr->remote_addr_3 = csk->ha[3];
	conn_addr->remote_addr_4 = csk->ha[4];
	conn_addr->remote_addr_5 = csk->ha[5];

	अगर (kwqe1->conn_flags & L4_KWQ_CONNECT_REQ1_IP_V6) अणु
		काष्ठा l4_kwq_connect_req2 *kwqe2 =
			(काष्ठा l4_kwq_connect_req2 *) wqes[1];

		conn_addr->local_ip_addr.ip_addr_hi_hi = kwqe2->src_ip_v6_4;
		conn_addr->local_ip_addr.ip_addr_hi_lo = kwqe2->src_ip_v6_3;
		conn_addr->local_ip_addr.ip_addr_lo_hi = kwqe2->src_ip_v6_2;

		conn_addr->remote_ip_addr.ip_addr_hi_hi = kwqe2->dst_ip_v6_4;
		conn_addr->remote_ip_addr.ip_addr_hi_lo = kwqe2->dst_ip_v6_3;
		conn_addr->remote_ip_addr.ip_addr_lo_hi = kwqe2->dst_ip_v6_2;
		conn_addr->params |= L5CM_CONN_ADDR_PARAMS_IP_VERSION;
	पूर्ण
	kwqe3 = (काष्ठा l4_kwq_connect_req3 *) wqes[*work - 1];

	conn_addr->local_ip_addr.ip_addr_lo_lo = kwqe1->src_ip;
	conn_addr->remote_ip_addr.ip_addr_lo_lo = kwqe1->dst_ip;
	conn_addr->local_tcp_port = kwqe1->src_port;
	conn_addr->remote_tcp_port = kwqe1->dst_port;

	conn_addr->pmtu = kwqe3->pmtu;
	cnic_init_storm_conn_bufs(dev, kwqe1, kwqe3, conn_buf);

	CNIC_WR16(dev, BAR_XSTRORM_INTMEM +
		  XSTORM_ISCSI_LOCAL_VLAN_OFFSET(bp->pfid), csk->vlan_id);

	ret = cnic_submit_kwqe_16(dev, L5CM_RAMROD_CMD_ID_TCP_CONNECT,
			kwqe1->cid, ISCSI_CONNECTION_TYPE, &l5_data);
	अगर (!ret)
		set_bit(CTX_FL_OFFLD_START, &ctx->ctx_flags);

	वापस ret;
पूर्ण

अटल पूर्णांक cnic_bnx2x_बंद(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	काष्ठा l4_kwq_बंद_req *req = (काष्ठा l4_kwq_बंद_req *) kwqe;
	जोड़ l5cm_specअगरic_data l5_data;
	पूर्णांक ret;

	स_रखो(&l5_data, 0, माप(l5_data));
	ret = cnic_submit_kwqe_16(dev, L5CM_RAMROD_CMD_ID_CLOSE,
			req->cid, ISCSI_CONNECTION_TYPE, &l5_data);
	वापस ret;
पूर्ण

अटल पूर्णांक cnic_bnx2x_reset(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	काष्ठा l4_kwq_reset_req *req = (काष्ठा l4_kwq_reset_req *) kwqe;
	जोड़ l5cm_specअगरic_data l5_data;
	पूर्णांक ret;

	स_रखो(&l5_data, 0, माप(l5_data));
	ret = cnic_submit_kwqe_16(dev, L5CM_RAMROD_CMD_ID_ABORT,
			req->cid, ISCSI_CONNECTION_TYPE, &l5_data);
	वापस ret;
पूर्ण
अटल पूर्णांक cnic_bnx2x_offload_pg(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	काष्ठा l4_kwq_offload_pg *req = (काष्ठा l4_kwq_offload_pg *) kwqe;
	काष्ठा l4_kcq kcqe;
	काष्ठा kcqe *cqes[1];

	स_रखो(&kcqe, 0, माप(kcqe));
	kcqe.pg_host_opaque = req->host_opaque;
	kcqe.pg_cid = req->host_opaque;
	kcqe.op_code = L4_KCQE_OPCODE_VALUE_OFFLOAD_PG;
	cqes[0] = (काष्ठा kcqe *) &kcqe;
	cnic_reply_bnx2x_kcqes(dev, CNIC_ULP_L4, cqes, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक cnic_bnx2x_update_pg(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	काष्ठा l4_kwq_update_pg *req = (काष्ठा l4_kwq_update_pg *) kwqe;
	काष्ठा l4_kcq kcqe;
	काष्ठा kcqe *cqes[1];

	स_रखो(&kcqe, 0, माप(kcqe));
	kcqe.pg_host_opaque = req->pg_host_opaque;
	kcqe.pg_cid = req->pg_cid;
	kcqe.op_code = L4_KCQE_OPCODE_VALUE_UPDATE_PG;
	cqes[0] = (काष्ठा kcqe *) &kcqe;
	cnic_reply_bnx2x_kcqes(dev, CNIC_ULP_L4, cqes, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक cnic_bnx2x_fcoe_stat(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	काष्ठा fcoe_kwqe_stat *req;
	काष्ठा fcoe_stat_ramrod_params *fcoe_stat;
	जोड़ l5cm_specअगरic_data l5_data;
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	पूर्णांक ret;
	u32 cid;

	req = (काष्ठा fcoe_kwqe_stat *) kwqe;
	cid = BNX2X_HW_CID(bp, cp->fcoe_init_cid);

	fcoe_stat = cnic_get_kwqe_16_data(cp, BNX2X_FCOE_L5_CID_BASE, &l5_data);
	अगर (!fcoe_stat)
		वापस -ENOMEM;

	स_रखो(fcoe_stat, 0, माप(*fcoe_stat));
	स_नकल(&fcoe_stat->stat_kwqe, req, माप(*req));

	ret = cnic_submit_kwqe_16(dev, FCOE_RAMROD_CMD_ID_STAT_FUNC, cid,
				  FCOE_CONNECTION_TYPE, &l5_data);
	वापस ret;
पूर्ण

अटल पूर्णांक cnic_bnx2x_fcoe_init1(काष्ठा cnic_dev *dev, काष्ठा kwqe *wqes[],
				 u32 num, पूर्णांक *work)
अणु
	पूर्णांक ret;
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	u32 cid;
	काष्ठा fcoe_init_ramrod_params *fcoe_init;
	काष्ठा fcoe_kwqe_init1 *req1;
	काष्ठा fcoe_kwqe_init2 *req2;
	काष्ठा fcoe_kwqe_init3 *req3;
	जोड़ l5cm_specअगरic_data l5_data;

	अगर (num < 3) अणु
		*work = num;
		वापस -EINVAL;
	पूर्ण
	req1 = (काष्ठा fcoe_kwqe_init1 *) wqes[0];
	req2 = (काष्ठा fcoe_kwqe_init2 *) wqes[1];
	req3 = (काष्ठा fcoe_kwqe_init3 *) wqes[2];
	अगर (req2->hdr.op_code != FCOE_KWQE_OPCODE_INIT2) अणु
		*work = 1;
		वापस -EINVAL;
	पूर्ण
	अगर (req3->hdr.op_code != FCOE_KWQE_OPCODE_INIT3) अणु
		*work = 2;
		वापस -EINVAL;
	पूर्ण

	अगर (माप(*fcoe_init) > CNIC_KWQ16_DATA_SIZE) अणु
		netdev_err(dev->netdev, "fcoe_init size too big\n");
		वापस -ENOMEM;
	पूर्ण
	fcoe_init = cnic_get_kwqe_16_data(cp, BNX2X_FCOE_L5_CID_BASE, &l5_data);
	अगर (!fcoe_init)
		वापस -ENOMEM;

	स_रखो(fcoe_init, 0, माप(*fcoe_init));
	स_नकल(&fcoe_init->init_kwqe1, req1, माप(*req1));
	स_नकल(&fcoe_init->init_kwqe2, req2, माप(*req2));
	स_नकल(&fcoe_init->init_kwqe3, req3, माप(*req3));
	fcoe_init->eq_pbl_base.lo = cp->kcq2.dma.pgtbl_map & 0xffffffff;
	fcoe_init->eq_pbl_base.hi = (u64) cp->kcq2.dma.pgtbl_map >> 32;
	fcoe_init->eq_pbl_size = cp->kcq2.dma.num_pages;

	fcoe_init->sb_num = cp->status_blk_num;
	fcoe_init->eq_prod = MAX_KCQ_IDX;
	fcoe_init->sb_id = HC_INDEX_FCOE_EQ_CONS;
	cp->kcq2.sw_prod_idx = 0;

	cid = BNX2X_HW_CID(bp, cp->fcoe_init_cid);
	ret = cnic_submit_kwqe_16(dev, FCOE_RAMROD_CMD_ID_INIT_FUNC, cid,
				  FCOE_CONNECTION_TYPE, &l5_data);
	*work = 3;
	वापस ret;
पूर्ण

अटल पूर्णांक cnic_bnx2x_fcoe_ofld1(काष्ठा cnic_dev *dev, काष्ठा kwqe *wqes[],
				 u32 num, पूर्णांक *work)
अणु
	पूर्णांक ret = 0;
	u32 cid = -1, l5_cid;
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	काष्ठा fcoe_kwqe_conn_offload1 *req1;
	काष्ठा fcoe_kwqe_conn_offload2 *req2;
	काष्ठा fcoe_kwqe_conn_offload3 *req3;
	काष्ठा fcoe_kwqe_conn_offload4 *req4;
	काष्ठा fcoe_conn_offload_ramrod_params *fcoe_offload;
	काष्ठा cnic_context *ctx;
	काष्ठा fcoe_context *fctx;
	काष्ठा regpair ctx_addr;
	जोड़ l5cm_specअगरic_data l5_data;
	काष्ठा fcoe_kcqe kcqe;
	काष्ठा kcqe *cqes[1];

	अगर (num < 4) अणु
		*work = num;
		वापस -EINVAL;
	पूर्ण
	req1 = (काष्ठा fcoe_kwqe_conn_offload1 *) wqes[0];
	req2 = (काष्ठा fcoe_kwqe_conn_offload2 *) wqes[1];
	req3 = (काष्ठा fcoe_kwqe_conn_offload3 *) wqes[2];
	req4 = (काष्ठा fcoe_kwqe_conn_offload4 *) wqes[3];

	*work = 4;

	l5_cid = req1->fcoe_conn_id;
	अगर (l5_cid >= dev->max_fcoe_conn)
		जाओ err_reply;

	l5_cid += BNX2X_FCOE_L5_CID_BASE;

	ctx = &cp->ctx_tbl[l5_cid];
	अगर (test_bit(CTX_FL_OFFLD_START, &ctx->ctx_flags))
		जाओ err_reply;

	ret = cnic_alloc_bnx2x_conn_resc(dev, l5_cid);
	अगर (ret) अणु
		ret = 0;
		जाओ err_reply;
	पूर्ण
	cid = ctx->cid;

	fctx = cnic_get_bnx2x_ctx(dev, cid, 1, &ctx_addr);
	अगर (fctx) अणु
		u32 hw_cid = BNX2X_HW_CID(bp, cid);
		u32 val;

		val = CDU_RSRVD_VALUE_TYPE_A(hw_cid, CDU_REGION_NUMBER_XCM_AG,
					     FCOE_CONNECTION_TYPE);
		fctx->xstorm_ag_context.cdu_reserved = val;
		val = CDU_RSRVD_VALUE_TYPE_A(hw_cid, CDU_REGION_NUMBER_UCM_AG,
					     FCOE_CONNECTION_TYPE);
		fctx->ustorm_ag_context.cdu_usage = val;
	पूर्ण
	अगर (माप(*fcoe_offload) > CNIC_KWQ16_DATA_SIZE) अणु
		netdev_err(dev->netdev, "fcoe_offload size too big\n");
		जाओ err_reply;
	पूर्ण
	fcoe_offload = cnic_get_kwqe_16_data(cp, l5_cid, &l5_data);
	अगर (!fcoe_offload)
		जाओ err_reply;

	स_रखो(fcoe_offload, 0, माप(*fcoe_offload));
	स_नकल(&fcoe_offload->offload_kwqe1, req1, माप(*req1));
	स_नकल(&fcoe_offload->offload_kwqe2, req2, माप(*req2));
	स_नकल(&fcoe_offload->offload_kwqe3, req3, माप(*req3));
	स_नकल(&fcoe_offload->offload_kwqe4, req4, माप(*req4));

	cid = BNX2X_HW_CID(bp, cid);
	ret = cnic_submit_kwqe_16(dev, FCOE_RAMROD_CMD_ID_OFFLOAD_CONN, cid,
				  FCOE_CONNECTION_TYPE, &l5_data);
	अगर (!ret)
		set_bit(CTX_FL_OFFLD_START, &ctx->ctx_flags);

	वापस ret;

err_reply:
	अगर (cid != -1)
		cnic_मुक्त_bnx2x_conn_resc(dev, l5_cid);

	स_रखो(&kcqe, 0, माप(kcqe));
	kcqe.op_code = FCOE_KCQE_OPCODE_OFFLOAD_CONN;
	kcqe.fcoe_conn_id = req1->fcoe_conn_id;
	kcqe.completion_status = FCOE_KCQE_COMPLETION_STATUS_CTX_ALLOC_FAILURE;

	cqes[0] = (काष्ठा kcqe *) &kcqe;
	cnic_reply_bnx2x_kcqes(dev, CNIC_ULP_FCOE, cqes, 1);
	वापस ret;
पूर्ण

अटल पूर्णांक cnic_bnx2x_fcoe_enable(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	काष्ठा fcoe_kwqe_conn_enable_disable *req;
	काष्ठा fcoe_conn_enable_disable_ramrod_params *fcoe_enable;
	जोड़ l5cm_specअगरic_data l5_data;
	पूर्णांक ret;
	u32 cid, l5_cid;
	काष्ठा cnic_local *cp = dev->cnic_priv;

	req = (काष्ठा fcoe_kwqe_conn_enable_disable *) kwqe;
	cid = req->context_id;
	l5_cid = req->conn_id + BNX2X_FCOE_L5_CID_BASE;

	अगर (माप(*fcoe_enable) > CNIC_KWQ16_DATA_SIZE) अणु
		netdev_err(dev->netdev, "fcoe_enable size too big\n");
		वापस -ENOMEM;
	पूर्ण
	fcoe_enable = cnic_get_kwqe_16_data(cp, l5_cid, &l5_data);
	अगर (!fcoe_enable)
		वापस -ENOMEM;

	स_रखो(fcoe_enable, 0, माप(*fcoe_enable));
	स_नकल(&fcoe_enable->enable_disable_kwqe, req, माप(*req));
	ret = cnic_submit_kwqe_16(dev, FCOE_RAMROD_CMD_ID_ENABLE_CONN, cid,
				  FCOE_CONNECTION_TYPE, &l5_data);
	वापस ret;
पूर्ण

अटल पूर्णांक cnic_bnx2x_fcoe_disable(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	काष्ठा fcoe_kwqe_conn_enable_disable *req;
	काष्ठा fcoe_conn_enable_disable_ramrod_params *fcoe_disable;
	जोड़ l5cm_specअगरic_data l5_data;
	पूर्णांक ret;
	u32 cid, l5_cid;
	काष्ठा cnic_local *cp = dev->cnic_priv;

	req = (काष्ठा fcoe_kwqe_conn_enable_disable *) kwqe;
	cid = req->context_id;
	l5_cid = req->conn_id;
	अगर (l5_cid >= dev->max_fcoe_conn)
		वापस -EINVAL;

	l5_cid += BNX2X_FCOE_L5_CID_BASE;

	अगर (माप(*fcoe_disable) > CNIC_KWQ16_DATA_SIZE) अणु
		netdev_err(dev->netdev, "fcoe_disable size too big\n");
		वापस -ENOMEM;
	पूर्ण
	fcoe_disable = cnic_get_kwqe_16_data(cp, l5_cid, &l5_data);
	अगर (!fcoe_disable)
		वापस -ENOMEM;

	स_रखो(fcoe_disable, 0, माप(*fcoe_disable));
	स_नकल(&fcoe_disable->enable_disable_kwqe, req, माप(*req));
	ret = cnic_submit_kwqe_16(dev, FCOE_RAMROD_CMD_ID_DISABLE_CONN, cid,
				  FCOE_CONNECTION_TYPE, &l5_data);
	वापस ret;
पूर्ण

अटल पूर्णांक cnic_bnx2x_fcoe_destroy(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	काष्ठा fcoe_kwqe_conn_destroy *req;
	जोड़ l5cm_specअगरic_data l5_data;
	पूर्णांक ret;
	u32 cid, l5_cid;
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_context *ctx;
	काष्ठा fcoe_kcqe kcqe;
	काष्ठा kcqe *cqes[1];

	req = (काष्ठा fcoe_kwqe_conn_destroy *) kwqe;
	cid = req->context_id;
	l5_cid = req->conn_id;
	अगर (l5_cid >= dev->max_fcoe_conn)
		वापस -EINVAL;

	l5_cid += BNX2X_FCOE_L5_CID_BASE;

	ctx = &cp->ctx_tbl[l5_cid];

	init_रुकोqueue_head(&ctx->रुकोq);
	ctx->रुको_cond = 0;

	स_रखो(&kcqe, 0, माप(kcqe));
	kcqe.completion_status = FCOE_KCQE_COMPLETION_STATUS_ERROR;
	स_रखो(&l5_data, 0, माप(l5_data));
	ret = cnic_submit_kwqe_16(dev, FCOE_RAMROD_CMD_ID_TERMINATE_CONN, cid,
				  FCOE_CONNECTION_TYPE, &l5_data);
	अगर (ret == 0) अणु
		रुको_event_समयout(ctx->रुकोq, ctx->रुको_cond, CNIC_RAMROD_TMO);
		अगर (ctx->रुको_cond)
			kcqe.completion_status = 0;
	पूर्ण

	set_bit(CTX_FL_DELETE_WAIT, &ctx->ctx_flags);
	queue_delayed_work(cnic_wq, &cp->delete_task, msecs_to_jअगरfies(2000));

	kcqe.op_code = FCOE_KCQE_OPCODE_DESTROY_CONN;
	kcqe.fcoe_conn_id = req->conn_id;
	kcqe.fcoe_conn_context_id = cid;

	cqes[0] = (काष्ठा kcqe *) &kcqe;
	cnic_reply_bnx2x_kcqes(dev, CNIC_ULP_FCOE, cqes, 1);
	वापस ret;
पूर्ण

अटल व्योम cnic_bnx2x_delete_रुको(काष्ठा cnic_dev *dev, u32 start_cid)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	u32 i;

	क्रम (i = start_cid; i < cp->max_cid_space; i++) अणु
		काष्ठा cnic_context *ctx = &cp->ctx_tbl[i];
		पूर्णांक j;

		जबतक (test_bit(CTX_FL_DELETE_WAIT, &ctx->ctx_flags))
			msleep(10);

		क्रम (j = 0; j < 5; j++) अणु
			अगर (!test_bit(CTX_FL_OFFLD_START, &ctx->ctx_flags))
				अवरोध;
			msleep(20);
		पूर्ण

		अगर (test_bit(CTX_FL_OFFLD_START, &ctx->ctx_flags))
			netdev_warn(dev->netdev, "CID %x not deleted\n",
				   ctx->cid);
	पूर्ण
पूर्ण

अटल पूर्णांक cnic_bnx2x_fcoe_fw_destroy(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	जोड़ l5cm_specअगरic_data l5_data;
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	पूर्णांक ret;
	u32 cid;

	cnic_bnx2x_delete_रुको(dev, MAX_ISCSI_TBL_SZ);

	cid = BNX2X_HW_CID(bp, cp->fcoe_init_cid);

	स_रखो(&l5_data, 0, माप(l5_data));
	ret = cnic_submit_kwqe_16(dev, FCOE_RAMROD_CMD_ID_DESTROY_FUNC, cid,
				  FCOE_CONNECTION_TYPE, &l5_data);
	वापस ret;
पूर्ण

अटल व्योम cnic_bnx2x_kwqe_err(काष्ठा cnic_dev *dev, काष्ठा kwqe *kwqe)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा kcqe kcqe;
	काष्ठा kcqe *cqes[1];
	u32 cid;
	u32 opcode = KWQE_OPCODE(kwqe->kwqe_op_flag);
	u32 layer_code = kwqe->kwqe_op_flag & KWQE_LAYER_MASK;
	u32 kcqe_op;
	पूर्णांक ulp_type;

	cid = kwqe->kwqe_info0;
	स_रखो(&kcqe, 0, माप(kcqe));

	अगर (layer_code == KWQE_FLAGS_LAYER_MASK_L5_FCOE) अणु
		u32 l5_cid = 0;

		ulp_type = CNIC_ULP_FCOE;
		अगर (opcode == FCOE_KWQE_OPCODE_DISABLE_CONN) अणु
			काष्ठा fcoe_kwqe_conn_enable_disable *req;

			req = (काष्ठा fcoe_kwqe_conn_enable_disable *) kwqe;
			kcqe_op = FCOE_KCQE_OPCODE_DISABLE_CONN;
			cid = req->context_id;
			l5_cid = req->conn_id;
		पूर्ण अन्यथा अगर (opcode == FCOE_KWQE_OPCODE_DESTROY) अणु
			kcqe_op = FCOE_KCQE_OPCODE_DESTROY_FUNC;
		पूर्ण अन्यथा अणु
			वापस;
		पूर्ण
		kcqe.kcqe_op_flag = kcqe_op << KCQE_FLAGS_OPCODE_SHIFT;
		kcqe.kcqe_op_flag |= KCQE_FLAGS_LAYER_MASK_L5_FCOE;
		kcqe.kcqe_info1 = FCOE_KCQE_COMPLETION_STATUS_PARITY_ERROR;
		kcqe.kcqe_info2 = cid;
		kcqe.kcqe_info0 = l5_cid;

	पूर्ण अन्यथा अगर (layer_code == KWQE_FLAGS_LAYER_MASK_L5_ISCSI) अणु
		ulp_type = CNIC_ULP_ISCSI;
		अगर (opcode == ISCSI_KWQE_OPCODE_UPDATE_CONN)
			cid = kwqe->kwqe_info1;

		kcqe.kcqe_op_flag = (opcode + 0x10) << KCQE_FLAGS_OPCODE_SHIFT;
		kcqe.kcqe_op_flag |= KCQE_FLAGS_LAYER_MASK_L5_ISCSI;
		kcqe.kcqe_info1 = ISCSI_KCQE_COMPLETION_STATUS_PARITY_ERR;
		kcqe.kcqe_info2 = cid;
		cnic_get_l5_cid(cp, BNX2X_SW_CID(cid), &kcqe.kcqe_info0);

	पूर्ण अन्यथा अगर (layer_code == KWQE_FLAGS_LAYER_MASK_L4) अणु
		काष्ठा l4_kcq *l4kcqe = (काष्ठा l4_kcq *) &kcqe;

		ulp_type = CNIC_ULP_L4;
		अगर (opcode == L4_KWQE_OPCODE_VALUE_CONNECT1)
			kcqe_op = L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE;
		अन्यथा अगर (opcode == L4_KWQE_OPCODE_VALUE_RESET)
			kcqe_op = L4_KCQE_OPCODE_VALUE_RESET_COMP;
		अन्यथा अगर (opcode == L4_KWQE_OPCODE_VALUE_CLOSE)
			kcqe_op = L4_KCQE_OPCODE_VALUE_CLOSE_COMP;
		अन्यथा
			वापस;

		kcqe.kcqe_op_flag = (kcqe_op << KCQE_FLAGS_OPCODE_SHIFT) |
				    KCQE_FLAGS_LAYER_MASK_L4;
		l4kcqe->status = L4_KCQE_COMPLETION_STATUS_PARITY_ERROR;
		l4kcqe->cid = cid;
		cnic_get_l5_cid(cp, BNX2X_SW_CID(cid), &l4kcqe->conn_id);
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	cqes[0] = &kcqe;
	cnic_reply_bnx2x_kcqes(dev, ulp_type, cqes, 1);
पूर्ण

अटल पूर्णांक cnic_submit_bnx2x_iscsi_kwqes(काष्ठा cnic_dev *dev,
					 काष्ठा kwqe *wqes[], u32 num_wqes)
अणु
	पूर्णांक i, work, ret;
	u32 opcode;
	काष्ठा kwqe *kwqe;

	अगर (!test_bit(CNIC_F_CNIC_UP, &dev->flags))
		वापस -EAGAIN;		/* bnx2 is करोwn */

	क्रम (i = 0; i < num_wqes; ) अणु
		kwqe = wqes[i];
		opcode = KWQE_OPCODE(kwqe->kwqe_op_flag);
		work = 1;

		चयन (opcode) अणु
		हाल ISCSI_KWQE_OPCODE_INIT1:
			ret = cnic_bnx2x_iscsi_init1(dev, kwqe);
			अवरोध;
		हाल ISCSI_KWQE_OPCODE_INIT2:
			ret = cnic_bnx2x_iscsi_init2(dev, kwqe);
			अवरोध;
		हाल ISCSI_KWQE_OPCODE_OFFLOAD_CONN1:
			ret = cnic_bnx2x_iscsi_ofld1(dev, &wqes[i],
						     num_wqes - i, &work);
			अवरोध;
		हाल ISCSI_KWQE_OPCODE_UPDATE_CONN:
			ret = cnic_bnx2x_iscsi_update(dev, kwqe);
			अवरोध;
		हाल ISCSI_KWQE_OPCODE_DESTROY_CONN:
			ret = cnic_bnx2x_iscsi_destroy(dev, kwqe);
			अवरोध;
		हाल L4_KWQE_OPCODE_VALUE_CONNECT1:
			ret = cnic_bnx2x_connect(dev, &wqes[i], num_wqes - i,
						 &work);
			अवरोध;
		हाल L4_KWQE_OPCODE_VALUE_CLOSE:
			ret = cnic_bnx2x_बंद(dev, kwqe);
			अवरोध;
		हाल L4_KWQE_OPCODE_VALUE_RESET:
			ret = cnic_bnx2x_reset(dev, kwqe);
			अवरोध;
		हाल L4_KWQE_OPCODE_VALUE_OFFLOAD_PG:
			ret = cnic_bnx2x_offload_pg(dev, kwqe);
			अवरोध;
		हाल L4_KWQE_OPCODE_VALUE_UPDATE_PG:
			ret = cnic_bnx2x_update_pg(dev, kwqe);
			अवरोध;
		हाल L4_KWQE_OPCODE_VALUE_UPLOAD_PG:
			ret = 0;
			अवरोध;
		शेष:
			ret = 0;
			netdev_err(dev->netdev, "Unknown type of KWQE(0x%x)\n",
				   opcode);
			अवरोध;
		पूर्ण
		अगर (ret < 0) अणु
			netdev_err(dev->netdev, "KWQE(0x%x) failed\n",
				   opcode);

			/* Possibly bnx2x parity error, send completion
			 * to ulp drivers with error code to speed up
			 * cleanup and reset recovery.
			 */
			अगर (ret == -EIO || ret == -EAGAIN)
				cnic_bnx2x_kwqe_err(dev, kwqe);
		पूर्ण
		i += work;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cnic_submit_bnx2x_fcoe_kwqes(काष्ठा cnic_dev *dev,
					काष्ठा kwqe *wqes[], u32 num_wqes)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	पूर्णांक i, work, ret;
	u32 opcode;
	काष्ठा kwqe *kwqe;

	अगर (!test_bit(CNIC_F_CNIC_UP, &dev->flags))
		वापस -EAGAIN;		/* bnx2 is करोwn */

	अगर (!BNX2X_CHIP_IS_E2_PLUS(bp))
		वापस -EINVAL;

	क्रम (i = 0; i < num_wqes; ) अणु
		kwqe = wqes[i];
		opcode = KWQE_OPCODE(kwqe->kwqe_op_flag);
		work = 1;

		चयन (opcode) अणु
		हाल FCOE_KWQE_OPCODE_INIT1:
			ret = cnic_bnx2x_fcoe_init1(dev, &wqes[i],
						    num_wqes - i, &work);
			अवरोध;
		हाल FCOE_KWQE_OPCODE_OFFLOAD_CONN1:
			ret = cnic_bnx2x_fcoe_ofld1(dev, &wqes[i],
						    num_wqes - i, &work);
			अवरोध;
		हाल FCOE_KWQE_OPCODE_ENABLE_CONN:
			ret = cnic_bnx2x_fcoe_enable(dev, kwqe);
			अवरोध;
		हाल FCOE_KWQE_OPCODE_DISABLE_CONN:
			ret = cnic_bnx2x_fcoe_disable(dev, kwqe);
			अवरोध;
		हाल FCOE_KWQE_OPCODE_DESTROY_CONN:
			ret = cnic_bnx2x_fcoe_destroy(dev, kwqe);
			अवरोध;
		हाल FCOE_KWQE_OPCODE_DESTROY:
			ret = cnic_bnx2x_fcoe_fw_destroy(dev, kwqe);
			अवरोध;
		हाल FCOE_KWQE_OPCODE_STAT:
			ret = cnic_bnx2x_fcoe_stat(dev, kwqe);
			अवरोध;
		शेष:
			ret = 0;
			netdev_err(dev->netdev, "Unknown type of KWQE(0x%x)\n",
				   opcode);
			अवरोध;
		पूर्ण
		अगर (ret < 0) अणु
			netdev_err(dev->netdev, "KWQE(0x%x) failed\n",
				   opcode);

			/* Possibly bnx2x parity error, send completion
			 * to ulp drivers with error code to speed up
			 * cleanup and reset recovery.
			 */
			अगर (ret == -EIO || ret == -EAGAIN)
				cnic_bnx2x_kwqe_err(dev, kwqe);
		पूर्ण
		i += work;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cnic_submit_bnx2x_kwqes(काष्ठा cnic_dev *dev, काष्ठा kwqe *wqes[],
				   u32 num_wqes)
अणु
	पूर्णांक ret = -EINVAL;
	u32 layer_code;

	अगर (!test_bit(CNIC_F_CNIC_UP, &dev->flags))
		वापस -EAGAIN;		/* bnx2x is करोwn */

	अगर (!num_wqes)
		वापस 0;

	layer_code = wqes[0]->kwqe_op_flag & KWQE_LAYER_MASK;
	चयन (layer_code) अणु
	हाल KWQE_FLAGS_LAYER_MASK_L5_ISCSI:
	हाल KWQE_FLAGS_LAYER_MASK_L4:
	हाल KWQE_FLAGS_LAYER_MASK_L2:
		ret = cnic_submit_bnx2x_iscsi_kwqes(dev, wqes, num_wqes);
		अवरोध;

	हाल KWQE_FLAGS_LAYER_MASK_L5_FCOE:
		ret = cnic_submit_bnx2x_fcoe_kwqes(dev, wqes, num_wqes);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत u32 cnic_get_kcqe_layer_mask(u32 opflag)
अणु
	अगर (unlikely(KCQE_OPCODE(opflag) == FCOE_RAMROD_CMD_ID_TERMINATE_CONN))
		वापस KCQE_FLAGS_LAYER_MASK_L4;

	वापस opflag & KCQE_FLAGS_LAYER_MASK;
पूर्ण

अटल व्योम service_kcqes(काष्ठा cnic_dev *dev, पूर्णांक num_cqes)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	पूर्णांक i, j, comp = 0;

	i = 0;
	j = 1;
	जबतक (num_cqes) अणु
		काष्ठा cnic_ulp_ops *ulp_ops;
		पूर्णांक ulp_type;
		u32 kcqe_op_flag = cp->completed_kcq[i]->kcqe_op_flag;
		u32 kcqe_layer = cnic_get_kcqe_layer_mask(kcqe_op_flag);

		अगर (unlikely(kcqe_op_flag & KCQE_RAMROD_COMPLETION))
			comp++;

		जबतक (j < num_cqes) अणु
			u32 next_op = cp->completed_kcq[i + j]->kcqe_op_flag;

			अगर (cnic_get_kcqe_layer_mask(next_op) != kcqe_layer)
				अवरोध;

			अगर (unlikely(next_op & KCQE_RAMROD_COMPLETION))
				comp++;
			j++;
		पूर्ण

		अगर (kcqe_layer == KCQE_FLAGS_LAYER_MASK_L5_RDMA)
			ulp_type = CNIC_ULP_RDMA;
		अन्यथा अगर (kcqe_layer == KCQE_FLAGS_LAYER_MASK_L5_ISCSI)
			ulp_type = CNIC_ULP_ISCSI;
		अन्यथा अगर (kcqe_layer == KCQE_FLAGS_LAYER_MASK_L5_FCOE)
			ulp_type = CNIC_ULP_FCOE;
		अन्यथा अगर (kcqe_layer == KCQE_FLAGS_LAYER_MASK_L4)
			ulp_type = CNIC_ULP_L4;
		अन्यथा अगर (kcqe_layer == KCQE_FLAGS_LAYER_MASK_L2)
			जाओ end;
		अन्यथा अणु
			netdev_err(dev->netdev, "Unknown type of KCQE(0x%x)\n",
				   kcqe_op_flag);
			जाओ end;
		पूर्ण

		rcu_पढ़ो_lock();
		ulp_ops = rcu_dereference(cp->ulp_ops[ulp_type]);
		अगर (likely(ulp_ops)) अणु
			ulp_ops->indicate_kcqes(cp->ulp_handle[ulp_type],
						  cp->completed_kcq + i, j);
		पूर्ण
		rcu_पढ़ो_unlock();
end:
		num_cqes -= j;
		i += j;
		j = 1;
	पूर्ण
	अगर (unlikely(comp))
		cnic_spq_completion(dev, DRV_CTL_RET_L5_SPQ_CREDIT_CMD, comp);
पूर्ण

अटल पूर्णांक cnic_get_kcqes(काष्ठा cnic_dev *dev, काष्ठा kcq_info *info)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	u16 i, ri, hw_prod, last;
	काष्ठा kcqe *kcqe;
	पूर्णांक kcqe_cnt = 0, last_cnt = 0;

	i = ri = last = info->sw_prod_idx;
	ri &= MAX_KCQ_IDX;
	hw_prod = *info->hw_prod_idx_ptr;
	hw_prod = info->hw_idx(hw_prod);

	जबतक ((i != hw_prod) && (kcqe_cnt < MAX_COMPLETED_KCQE)) अणु
		kcqe = &info->kcq[KCQ_PG(ri)][KCQ_IDX(ri)];
		cp->completed_kcq[kcqe_cnt++] = kcqe;
		i = info->next_idx(i);
		ri = i & MAX_KCQ_IDX;
		अगर (likely(!(kcqe->kcqe_op_flag & KCQE_FLAGS_NEXT))) अणु
			last_cnt = kcqe_cnt;
			last = i;
		पूर्ण
	पूर्ण

	info->sw_prod_idx = last;
	वापस last_cnt;
पूर्ण

अटल पूर्णांक cnic_l2_completion(काष्ठा cnic_local *cp)
अणु
	u16 hw_cons, sw_cons;
	काष्ठा cnic_uio_dev *udev = cp->udev;
	जोड़ eth_rx_cqe *cqe, *cqe_ring = (जोड़ eth_rx_cqe *)
					(udev->l2_ring + (2 * CNIC_PAGE_SIZE));
	u32 cmd;
	पूर्णांक comp = 0;

	अगर (!test_bit(CNIC_F_BNX2X_CLASS, &cp->dev->flags))
		वापस 0;

	hw_cons = *cp->rx_cons_ptr;
	अगर ((hw_cons & BNX2X_MAX_RCQ_DESC_CNT) == BNX2X_MAX_RCQ_DESC_CNT)
		hw_cons++;

	sw_cons = cp->rx_cons;
	जबतक (sw_cons != hw_cons) अणु
		u8 cqe_fp_flags;

		cqe = &cqe_ring[sw_cons & BNX2X_MAX_RCQ_DESC_CNT];
		cqe_fp_flags = cqe->fast_path_cqe.type_error_flags;
		अगर (cqe_fp_flags & ETH_FAST_PATH_RX_CQE_TYPE) अणु
			cmd = le32_to_cpu(cqe->ramrod_cqe.conn_and_cmd_data);
			cmd >>= COMMON_RAMROD_ETH_RX_CQE_CMD_ID_SHIFT;
			अगर (cmd == RAMROD_CMD_ID_ETH_CLIENT_SETUP ||
			    cmd == RAMROD_CMD_ID_ETH_HALT)
				comp++;
		पूर्ण
		sw_cons = BNX2X_NEXT_RCQE(sw_cons);
	पूर्ण
	वापस comp;
पूर्ण

अटल व्योम cnic_chk_pkt_rings(काष्ठा cnic_local *cp)
अणु
	u16 rx_cons, tx_cons;
	पूर्णांक comp = 0;

	अगर (!test_bit(CNIC_LCL_FL_RINGS_INITED, &cp->cnic_local_flags))
		वापस;

	rx_cons = *cp->rx_cons_ptr;
	tx_cons = *cp->tx_cons_ptr;
	अगर (cp->tx_cons != tx_cons || cp->rx_cons != rx_cons) अणु
		अगर (test_bit(CNIC_LCL_FL_L2_WAIT, &cp->cnic_local_flags))
			comp = cnic_l2_completion(cp);

		cp->tx_cons = tx_cons;
		cp->rx_cons = rx_cons;

		अगर (cp->udev)
			uio_event_notअगरy(&cp->udev->cnic_uinfo);
	पूर्ण
	अगर (comp)
		clear_bit(CNIC_LCL_FL_L2_WAIT, &cp->cnic_local_flags);
पूर्ण

अटल u32 cnic_service_bnx2_queues(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	u32 status_idx = (u16) *cp->kcq1.status_idx_ptr;
	पूर्णांक kcqe_cnt;

	/* status block index must be पढ़ो beक्रमe पढ़ोing other fields */
	rmb();
	cp->kwq_con_idx = *cp->kwq_con_idx_ptr;

	जबतक ((kcqe_cnt = cnic_get_kcqes(dev, &cp->kcq1))) अणु

		service_kcqes(dev, kcqe_cnt);

		/* Tell compiler that status_blk fields can change. */
		barrier();
		status_idx = (u16) *cp->kcq1.status_idx_ptr;
		/* status block index must be पढ़ो first */
		rmb();
		cp->kwq_con_idx = *cp->kwq_con_idx_ptr;
	पूर्ण

	CNIC_WR16(dev, cp->kcq1.io_addr, cp->kcq1.sw_prod_idx);

	cnic_chk_pkt_rings(cp);

	वापस status_idx;
पूर्ण

अटल पूर्णांक cnic_service_bnx2(व्योम *data, व्योम *status_blk)
अणु
	काष्ठा cnic_dev *dev = data;

	अगर (unlikely(!test_bit(CNIC_F_CNIC_UP, &dev->flags))) अणु
		काष्ठा status_block *sblk = status_blk;

		वापस sblk->status_idx;
	पूर्ण

	वापस cnic_service_bnx2_queues(dev);
पूर्ण

अटल व्योम cnic_service_bnx2_msix(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा cnic_local *cp = from_tasklet(cp, t, cnic_irq_task);
	काष्ठा cnic_dev *dev = cp->dev;

	cp->last_status_idx = cnic_service_bnx2_queues(dev);

	CNIC_WR(dev, BNX2_PCICFG_INT_ACK_CMD, cp->पूर्णांक_num |
		BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID | cp->last_status_idx);
पूर्ण

अटल व्योम cnic_करोirq(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;

	अगर (likely(test_bit(CNIC_F_CNIC_UP, &dev->flags))) अणु
		u16 prod = cp->kcq1.sw_prod_idx & MAX_KCQ_IDX;

		prefetch(cp->status_blk.gen);
		prefetch(&cp->kcq1.kcq[KCQ_PG(prod)][KCQ_IDX(prod)]);

		tasklet_schedule(&cp->cnic_irq_task);
	पूर्ण
पूर्ण

अटल irqवापस_t cnic_irq(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा cnic_dev *dev = dev_instance;
	काष्ठा cnic_local *cp = dev->cnic_priv;

	अगर (cp->ack_पूर्णांक)
		cp->ack_पूर्णांक(dev);

	cnic_करोirq(dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत व्योम cnic_ack_bnx2x_पूर्णांक(काष्ठा cnic_dev *dev, u8 id, u8 storm,
				      u16 index, u8 op, u8 update)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	u32 hc_addr = (HC_REG_COMMAND_REG + BP_PORT(bp) * 32 +
		       COMMAND_REG_INT_ACK);
	काष्ठा igu_ack_रेजिस्टर igu_ack;

	igu_ack.status_block_index = index;
	igu_ack.sb_id_and_flags =
			((id << IGU_ACK_REGISTER_STATUS_BLOCK_ID_SHIFT) |
			 (storm << IGU_ACK_REGISTER_STORM_ID_SHIFT) |
			 (update << IGU_ACK_REGISTER_UPDATE_INDEX_SHIFT) |
			 (op << IGU_ACK_REGISTER_INTERRUPT_MODE_SHIFT));

	CNIC_WR(dev, hc_addr, (*(u32 *)&igu_ack));
पूर्ण

अटल व्योम cnic_ack_igu_sb(काष्ठा cnic_dev *dev, u8 igu_sb_id, u8 segment,
			    u16 index, u8 op, u8 update)
अणु
	काष्ठा igu_regular cmd_data;
	u32 igu_addr = BAR_IGU_INTMEM + (IGU_CMD_INT_ACK_BASE + igu_sb_id) * 8;

	cmd_data.sb_id_and_flags =
		(index << IGU_REGULAR_SB_INDEX_SHIFT) |
		(segment << IGU_REGULAR_SEGMENT_ACCESS_SHIFT) |
		(update << IGU_REGULAR_BUPDATE_SHIFT) |
		(op << IGU_REGULAR_ENABLE_INT_SHIFT);


	CNIC_WR(dev, igu_addr, cmd_data.sb_id_and_flags);
पूर्ण

अटल व्योम cnic_ack_bnx2x_msix(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;

	cnic_ack_bnx2x_पूर्णांक(dev, cp->bnx2x_igu_sb_id, CSTORM_ID, 0,
			   IGU_INT_DISABLE, 0);
पूर्ण

अटल व्योम cnic_ack_bnx2x_e2_msix(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;

	cnic_ack_igu_sb(dev, cp->bnx2x_igu_sb_id, IGU_SEG_ACCESS_DEF, 0,
			IGU_INT_DISABLE, 0);
पूर्ण

अटल व्योम cnic_arm_bnx2x_msix(काष्ठा cnic_dev *dev, u32 idx)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;

	cnic_ack_bnx2x_पूर्णांक(dev, cp->bnx2x_igu_sb_id, CSTORM_ID, idx,
			   IGU_INT_ENABLE, 1);
पूर्ण

अटल व्योम cnic_arm_bnx2x_e2_msix(काष्ठा cnic_dev *dev, u32 idx)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;

	cnic_ack_igu_sb(dev, cp->bnx2x_igu_sb_id, IGU_SEG_ACCESS_DEF, idx,
			IGU_INT_ENABLE, 1);
पूर्ण

अटल u32 cnic_service_bnx2x_kcq(काष्ठा cnic_dev *dev, काष्ठा kcq_info *info)
अणु
	u32 last_status = *info->status_idx_ptr;
	पूर्णांक kcqe_cnt;

	/* status block index must be पढ़ो beक्रमe पढ़ोing the KCQ */
	rmb();
	जबतक ((kcqe_cnt = cnic_get_kcqes(dev, info))) अणु

		service_kcqes(dev, kcqe_cnt);

		/* Tell compiler that sblk fields can change. */
		barrier();

		last_status = *info->status_idx_ptr;
		/* status block index must be पढ़ो beक्रमe पढ़ोing the KCQ */
		rmb();
	पूर्ण
	वापस last_status;
पूर्ण

अटल व्योम cnic_service_bnx2x_bh(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा cnic_local *cp = from_tasklet(cp, t, cnic_irq_task);
	काष्ठा cnic_dev *dev = cp->dev;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	u32 status_idx, new_status_idx;

	अगर (unlikely(!test_bit(CNIC_F_CNIC_UP, &dev->flags)))
		वापस;

	जबतक (1) अणु
		status_idx = cnic_service_bnx2x_kcq(dev, &cp->kcq1);

		CNIC_WR16(dev, cp->kcq1.io_addr,
			  cp->kcq1.sw_prod_idx + MAX_KCQ_IDX);

		अगर (!CNIC_SUPPORTS_FCOE(bp)) अणु
			cp->arm_पूर्णांक(dev, status_idx);
			अवरोध;
		पूर्ण

		new_status_idx = cnic_service_bnx2x_kcq(dev, &cp->kcq2);

		अगर (new_status_idx != status_idx)
			जारी;

		CNIC_WR16(dev, cp->kcq2.io_addr, cp->kcq2.sw_prod_idx +
			  MAX_KCQ_IDX);

		cnic_ack_igu_sb(dev, cp->bnx2x_igu_sb_id, IGU_SEG_ACCESS_DEF,
				status_idx, IGU_INT_ENABLE, 1);

		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cnic_service_bnx2x(व्योम *data, व्योम *status_blk)
अणु
	काष्ठा cnic_dev *dev = data;
	काष्ठा cnic_local *cp = dev->cnic_priv;

	अगर (!(cp->ethdev->drv_state & CNIC_DRV_STATE_USING_MSIX))
		cnic_करोirq(dev);

	cnic_chk_pkt_rings(cp);

	वापस 0;
पूर्ण

अटल व्योम cnic_ulp_stop_one(काष्ठा cnic_local *cp, पूर्णांक अगर_type)
अणु
	काष्ठा cnic_ulp_ops *ulp_ops;

	अगर (अगर_type == CNIC_ULP_ISCSI)
		cnic_send_nlmsg(cp, ISCSI_KEVENT_IF_DOWN, शून्य);

	mutex_lock(&cnic_lock);
	ulp_ops = rcu_dereference_रक्षित(cp->ulp_ops[अगर_type],
					    lockdep_is_held(&cnic_lock));
	अगर (!ulp_ops) अणु
		mutex_unlock(&cnic_lock);
		वापस;
	पूर्ण
	set_bit(ULP_F_CALL_PENDING, &cp->ulp_flags[अगर_type]);
	mutex_unlock(&cnic_lock);

	अगर (test_and_clear_bit(ULP_F_START, &cp->ulp_flags[अगर_type]))
		ulp_ops->cnic_stop(cp->ulp_handle[अगर_type]);

	clear_bit(ULP_F_CALL_PENDING, &cp->ulp_flags[अगर_type]);
पूर्ण

अटल व्योम cnic_ulp_stop(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	पूर्णांक अगर_type;

	क्रम (अगर_type = 0; अगर_type < MAX_CNIC_ULP_TYPE; अगर_type++)
		cnic_ulp_stop_one(cp, अगर_type);
पूर्ण

अटल व्योम cnic_ulp_start(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	पूर्णांक अगर_type;

	क्रम (अगर_type = 0; अगर_type < MAX_CNIC_ULP_TYPE; अगर_type++) अणु
		काष्ठा cnic_ulp_ops *ulp_ops;

		mutex_lock(&cnic_lock);
		ulp_ops = rcu_dereference_रक्षित(cp->ulp_ops[अगर_type],
						    lockdep_is_held(&cnic_lock));
		अगर (!ulp_ops || !ulp_ops->cnic_start) अणु
			mutex_unlock(&cnic_lock);
			जारी;
		पूर्ण
		set_bit(ULP_F_CALL_PENDING, &cp->ulp_flags[अगर_type]);
		mutex_unlock(&cnic_lock);

		अगर (!test_and_set_bit(ULP_F_START, &cp->ulp_flags[अगर_type]))
			ulp_ops->cnic_start(cp->ulp_handle[अगर_type]);

		clear_bit(ULP_F_CALL_PENDING, &cp->ulp_flags[अगर_type]);
	पूर्ण
पूर्ण

अटल पूर्णांक cnic_copy_ulp_stats(काष्ठा cnic_dev *dev, पूर्णांक ulp_type)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_ulp_ops *ulp_ops;
	पूर्णांक rc;

	mutex_lock(&cnic_lock);
	ulp_ops = rcu_dereference_रक्षित(cp->ulp_ops[ulp_type],
					    lockdep_is_held(&cnic_lock));
	अगर (ulp_ops && ulp_ops->cnic_get_stats)
		rc = ulp_ops->cnic_get_stats(cp->ulp_handle[ulp_type]);
	अन्यथा
		rc = -ENODEV;
	mutex_unlock(&cnic_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक cnic_ctl(व्योम *data, काष्ठा cnic_ctl_info *info)
अणु
	काष्ठा cnic_dev *dev = data;
	पूर्णांक ulp_type = CNIC_ULP_ISCSI;

	चयन (info->cmd) अणु
	हाल CNIC_CTL_STOP_CMD:
		cnic_hold(dev);

		cnic_ulp_stop(dev);
		cnic_stop_hw(dev);

		cnic_put(dev);
		अवरोध;
	हाल CNIC_CTL_START_CMD:
		cnic_hold(dev);

		अगर (!cnic_start_hw(dev))
			cnic_ulp_start(dev);

		cnic_put(dev);
		अवरोध;
	हाल CNIC_CTL_STOP_ISCSI_CMD: अणु
		काष्ठा cnic_local *cp = dev->cnic_priv;
		set_bit(CNIC_LCL_FL_STOP_ISCSI, &cp->cnic_local_flags);
		queue_delayed_work(cnic_wq, &cp->delete_task, 0);
		अवरोध;
	पूर्ण
	हाल CNIC_CTL_COMPLETION_CMD: अणु
		काष्ठा cnic_ctl_completion *comp = &info->data.comp;
		u32 cid = BNX2X_SW_CID(comp->cid);
		u32 l5_cid;
		काष्ठा cnic_local *cp = dev->cnic_priv;

		अगर (!test_bit(CNIC_F_CNIC_UP, &dev->flags))
			अवरोध;

		अगर (cnic_get_l5_cid(cp, cid, &l5_cid) == 0) अणु
			काष्ठा cnic_context *ctx = &cp->ctx_tbl[l5_cid];

			अगर (unlikely(comp->error)) अणु
				set_bit(CTX_FL_CID_ERROR, &ctx->ctx_flags);
				netdev_err(dev->netdev,
					   "CID %x CFC delete comp error %x\n",
					   cid, comp->error);
			पूर्ण

			ctx->रुको_cond = 1;
			wake_up(&ctx->रुकोq);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल CNIC_CTL_FCOE_STATS_GET_CMD:
		ulp_type = CNIC_ULP_FCOE;
		fallthrough;
	हाल CNIC_CTL_ISCSI_STATS_GET_CMD:
		cnic_hold(dev);
		cnic_copy_ulp_stats(dev, ulp_type);
		cnic_put(dev);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cnic_ulp_init(काष्ठा cnic_dev *dev)
अणु
	पूर्णांक i;
	काष्ठा cnic_local *cp = dev->cnic_priv;

	क्रम (i = 0; i < MAX_CNIC_ULP_TYPE_EXT; i++) अणु
		काष्ठा cnic_ulp_ops *ulp_ops;

		mutex_lock(&cnic_lock);
		ulp_ops = cnic_ulp_tbl_prot(i);
		अगर (!ulp_ops || !ulp_ops->cnic_init) अणु
			mutex_unlock(&cnic_lock);
			जारी;
		पूर्ण
		ulp_get(ulp_ops);
		mutex_unlock(&cnic_lock);

		अगर (!test_and_set_bit(ULP_F_INIT, &cp->ulp_flags[i]))
			ulp_ops->cnic_init(dev);

		ulp_put(ulp_ops);
	पूर्ण
पूर्ण

अटल व्योम cnic_ulp_निकास(काष्ठा cnic_dev *dev)
अणु
	पूर्णांक i;
	काष्ठा cnic_local *cp = dev->cnic_priv;

	क्रम (i = 0; i < MAX_CNIC_ULP_TYPE_EXT; i++) अणु
		काष्ठा cnic_ulp_ops *ulp_ops;

		mutex_lock(&cnic_lock);
		ulp_ops = cnic_ulp_tbl_prot(i);
		अगर (!ulp_ops || !ulp_ops->cnic_निकास) अणु
			mutex_unlock(&cnic_lock);
			जारी;
		पूर्ण
		ulp_get(ulp_ops);
		mutex_unlock(&cnic_lock);

		अगर (test_and_clear_bit(ULP_F_INIT, &cp->ulp_flags[i]))
			ulp_ops->cnic_निकास(dev);

		ulp_put(ulp_ops);
	पूर्ण
पूर्ण

अटल पूर्णांक cnic_cm_offload_pg(काष्ठा cnic_sock *csk)
अणु
	काष्ठा cnic_dev *dev = csk->dev;
	काष्ठा l4_kwq_offload_pg *l4kwqe;
	काष्ठा kwqe *wqes[1];

	l4kwqe = (काष्ठा l4_kwq_offload_pg *) &csk->kwqe1;
	स_रखो(l4kwqe, 0, माप(*l4kwqe));
	wqes[0] = (काष्ठा kwqe *) l4kwqe;

	l4kwqe->op_code = L4_KWQE_OPCODE_VALUE_OFFLOAD_PG;
	l4kwqe->flags =
		L4_LAYER_CODE << L4_KWQ_OFFLOAD_PG_LAYER_CODE_SHIFT;
	l4kwqe->l2hdr_nbytes = ETH_HLEN;

	l4kwqe->da0 = csk->ha[0];
	l4kwqe->da1 = csk->ha[1];
	l4kwqe->da2 = csk->ha[2];
	l4kwqe->da3 = csk->ha[3];
	l4kwqe->da4 = csk->ha[4];
	l4kwqe->da5 = csk->ha[5];

	l4kwqe->sa0 = dev->mac_addr[0];
	l4kwqe->sa1 = dev->mac_addr[1];
	l4kwqe->sa2 = dev->mac_addr[2];
	l4kwqe->sa3 = dev->mac_addr[3];
	l4kwqe->sa4 = dev->mac_addr[4];
	l4kwqe->sa5 = dev->mac_addr[5];

	l4kwqe->etype = ETH_P_IP;
	l4kwqe->ipid_start = DEF_IPID_START;
	l4kwqe->host_opaque = csk->l5_cid;

	अगर (csk->vlan_id) अणु
		l4kwqe->pg_flags |= L4_KWQ_OFFLOAD_PG_VLAN_TAGGING;
		l4kwqe->vlan_tag = csk->vlan_id;
		l4kwqe->l2hdr_nbytes += 4;
	पूर्ण

	वापस dev->submit_kwqes(dev, wqes, 1);
पूर्ण

अटल पूर्णांक cnic_cm_update_pg(काष्ठा cnic_sock *csk)
अणु
	काष्ठा cnic_dev *dev = csk->dev;
	काष्ठा l4_kwq_update_pg *l4kwqe;
	काष्ठा kwqe *wqes[1];

	l4kwqe = (काष्ठा l4_kwq_update_pg *) &csk->kwqe1;
	स_रखो(l4kwqe, 0, माप(*l4kwqe));
	wqes[0] = (काष्ठा kwqe *) l4kwqe;

	l4kwqe->opcode = L4_KWQE_OPCODE_VALUE_UPDATE_PG;
	l4kwqe->flags =
		L4_LAYER_CODE << L4_KWQ_UPDATE_PG_LAYER_CODE_SHIFT;
	l4kwqe->pg_cid = csk->pg_cid;

	l4kwqe->da0 = csk->ha[0];
	l4kwqe->da1 = csk->ha[1];
	l4kwqe->da2 = csk->ha[2];
	l4kwqe->da3 = csk->ha[3];
	l4kwqe->da4 = csk->ha[4];
	l4kwqe->da5 = csk->ha[5];

	l4kwqe->pg_host_opaque = csk->l5_cid;
	l4kwqe->pg_valids = L4_KWQ_UPDATE_PG_VALIDS_DA;

	वापस dev->submit_kwqes(dev, wqes, 1);
पूर्ण

अटल पूर्णांक cnic_cm_upload_pg(काष्ठा cnic_sock *csk)
अणु
	काष्ठा cnic_dev *dev = csk->dev;
	काष्ठा l4_kwq_upload *l4kwqe;
	काष्ठा kwqe *wqes[1];

	l4kwqe = (काष्ठा l4_kwq_upload *) &csk->kwqe1;
	स_रखो(l4kwqe, 0, माप(*l4kwqe));
	wqes[0] = (काष्ठा kwqe *) l4kwqe;

	l4kwqe->opcode = L4_KWQE_OPCODE_VALUE_UPLOAD_PG;
	l4kwqe->flags =
		L4_LAYER_CODE << L4_KWQ_UPLOAD_LAYER_CODE_SHIFT;
	l4kwqe->cid = csk->pg_cid;

	वापस dev->submit_kwqes(dev, wqes, 1);
पूर्ण

अटल पूर्णांक cnic_cm_conn_req(काष्ठा cnic_sock *csk)
अणु
	काष्ठा cnic_dev *dev = csk->dev;
	काष्ठा l4_kwq_connect_req1 *l4kwqe1;
	काष्ठा l4_kwq_connect_req2 *l4kwqe2;
	काष्ठा l4_kwq_connect_req3 *l4kwqe3;
	काष्ठा kwqe *wqes[3];
	u8 tcp_flags = 0;
	पूर्णांक num_wqes = 2;

	l4kwqe1 = (काष्ठा l4_kwq_connect_req1 *) &csk->kwqe1;
	l4kwqe2 = (काष्ठा l4_kwq_connect_req2 *) &csk->kwqe2;
	l4kwqe3 = (काष्ठा l4_kwq_connect_req3 *) &csk->kwqe3;
	स_रखो(l4kwqe1, 0, माप(*l4kwqe1));
	स_रखो(l4kwqe2, 0, माप(*l4kwqe2));
	स_रखो(l4kwqe3, 0, माप(*l4kwqe3));

	l4kwqe3->op_code = L4_KWQE_OPCODE_VALUE_CONNECT3;
	l4kwqe3->flags =
		L4_LAYER_CODE << L4_KWQ_CONNECT_REQ3_LAYER_CODE_SHIFT;
	l4kwqe3->ka_समयout = csk->ka_समयout;
	l4kwqe3->ka_पूर्णांकerval = csk->ka_पूर्णांकerval;
	l4kwqe3->ka_max_probe_count = csk->ka_max_probe_count;
	l4kwqe3->tos = csk->tos;
	l4kwqe3->ttl = csk->ttl;
	l4kwqe3->snd_seq_scale = csk->snd_seq_scale;
	l4kwqe3->pmtu = csk->mtu;
	l4kwqe3->rcv_buf = csk->rcv_buf;
	l4kwqe3->snd_buf = csk->snd_buf;
	l4kwqe3->seed = csk->seed;

	wqes[0] = (काष्ठा kwqe *) l4kwqe1;
	अगर (test_bit(SK_F_IPV6, &csk->flags)) अणु
		wqes[1] = (काष्ठा kwqe *) l4kwqe2;
		wqes[2] = (काष्ठा kwqe *) l4kwqe3;
		num_wqes = 3;

		l4kwqe1->conn_flags = L4_KWQ_CONNECT_REQ1_IP_V6;
		l4kwqe2->op_code = L4_KWQE_OPCODE_VALUE_CONNECT2;
		l4kwqe2->flags =
			L4_KWQ_CONNECT_REQ2_LINKED_WITH_NEXT |
			L4_LAYER_CODE << L4_KWQ_CONNECT_REQ2_LAYER_CODE_SHIFT;
		l4kwqe2->src_ip_v6_2 = be32_to_cpu(csk->src_ip[1]);
		l4kwqe2->src_ip_v6_3 = be32_to_cpu(csk->src_ip[2]);
		l4kwqe2->src_ip_v6_4 = be32_to_cpu(csk->src_ip[3]);
		l4kwqe2->dst_ip_v6_2 = be32_to_cpu(csk->dst_ip[1]);
		l4kwqe2->dst_ip_v6_3 = be32_to_cpu(csk->dst_ip[2]);
		l4kwqe2->dst_ip_v6_4 = be32_to_cpu(csk->dst_ip[3]);
		l4kwqe3->mss = l4kwqe3->pmtu - माप(काष्ठा ipv6hdr) -
			       माप(काष्ठा tcphdr);
	पूर्ण अन्यथा अणु
		wqes[1] = (काष्ठा kwqe *) l4kwqe3;
		l4kwqe3->mss = l4kwqe3->pmtu - माप(काष्ठा iphdr) -
			       माप(काष्ठा tcphdr);
	पूर्ण

	l4kwqe1->op_code = L4_KWQE_OPCODE_VALUE_CONNECT1;
	l4kwqe1->flags =
		(L4_LAYER_CODE << L4_KWQ_CONNECT_REQ1_LAYER_CODE_SHIFT) |
		 L4_KWQ_CONNECT_REQ3_LINKED_WITH_NEXT;
	l4kwqe1->cid = csk->cid;
	l4kwqe1->pg_cid = csk->pg_cid;
	l4kwqe1->src_ip = be32_to_cpu(csk->src_ip[0]);
	l4kwqe1->dst_ip = be32_to_cpu(csk->dst_ip[0]);
	l4kwqe1->src_port = be16_to_cpu(csk->src_port);
	l4kwqe1->dst_port = be16_to_cpu(csk->dst_port);
	अगर (csk->tcp_flags & SK_TCP_NO_DELAY_ACK)
		tcp_flags |= L4_KWQ_CONNECT_REQ1_NO_DELAY_ACK;
	अगर (csk->tcp_flags & SK_TCP_KEEP_ALIVE)
		tcp_flags |= L4_KWQ_CONNECT_REQ1_KEEP_ALIVE;
	अगर (csk->tcp_flags & SK_TCP_NAGLE)
		tcp_flags |= L4_KWQ_CONNECT_REQ1_NAGLE_ENABLE;
	अगर (csk->tcp_flags & SK_TCP_TIMESTAMP)
		tcp_flags |= L4_KWQ_CONNECT_REQ1_TIME_STAMP;
	अगर (csk->tcp_flags & SK_TCP_SACK)
		tcp_flags |= L4_KWQ_CONNECT_REQ1_SACK;
	अगर (csk->tcp_flags & SK_TCP_SEG_SCALING)
		tcp_flags |= L4_KWQ_CONNECT_REQ1_SEG_SCALING;

	l4kwqe1->tcp_flags = tcp_flags;

	वापस dev->submit_kwqes(dev, wqes, num_wqes);
पूर्ण

अटल पूर्णांक cnic_cm_बंद_req(काष्ठा cnic_sock *csk)
अणु
	काष्ठा cnic_dev *dev = csk->dev;
	काष्ठा l4_kwq_बंद_req *l4kwqe;
	काष्ठा kwqe *wqes[1];

	l4kwqe = (काष्ठा l4_kwq_बंद_req *) &csk->kwqe2;
	स_रखो(l4kwqe, 0, माप(*l4kwqe));
	wqes[0] = (काष्ठा kwqe *) l4kwqe;

	l4kwqe->op_code = L4_KWQE_OPCODE_VALUE_CLOSE;
	l4kwqe->flags = L4_LAYER_CODE << L4_KWQ_CLOSE_REQ_LAYER_CODE_SHIFT;
	l4kwqe->cid = csk->cid;

	वापस dev->submit_kwqes(dev, wqes, 1);
पूर्ण

अटल पूर्णांक cnic_cm_पात_req(काष्ठा cnic_sock *csk)
अणु
	काष्ठा cnic_dev *dev = csk->dev;
	काष्ठा l4_kwq_reset_req *l4kwqe;
	काष्ठा kwqe *wqes[1];

	l4kwqe = (काष्ठा l4_kwq_reset_req *) &csk->kwqe2;
	स_रखो(l4kwqe, 0, माप(*l4kwqe));
	wqes[0] = (काष्ठा kwqe *) l4kwqe;

	l4kwqe->op_code = L4_KWQE_OPCODE_VALUE_RESET;
	l4kwqe->flags = L4_LAYER_CODE << L4_KWQ_RESET_REQ_LAYER_CODE_SHIFT;
	l4kwqe->cid = csk->cid;

	वापस dev->submit_kwqes(dev, wqes, 1);
पूर्ण

अटल पूर्णांक cnic_cm_create(काष्ठा cnic_dev *dev, पूर्णांक ulp_type, u32 cid,
			  u32 l5_cid, काष्ठा cnic_sock **csk, व्योम *context)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_sock *csk1;

	अगर (l5_cid >= MAX_CM_SK_TBL_SZ)
		वापस -EINVAL;

	अगर (cp->ctx_tbl) अणु
		काष्ठा cnic_context *ctx = &cp->ctx_tbl[l5_cid];

		अगर (test_bit(CTX_FL_OFFLD_START, &ctx->ctx_flags))
			वापस -EAGAIN;
	पूर्ण

	csk1 = &cp->csk_tbl[l5_cid];
	अगर (atomic_पढ़ो(&csk1->ref_count))
		वापस -EAGAIN;

	अगर (test_and_set_bit(SK_F_INUSE, &csk1->flags))
		वापस -EBUSY;

	csk1->dev = dev;
	csk1->cid = cid;
	csk1->l5_cid = l5_cid;
	csk1->ulp_type = ulp_type;
	csk1->context = context;

	csk1->ka_समयout = DEF_KA_TIMEOUT;
	csk1->ka_पूर्णांकerval = DEF_KA_INTERVAL;
	csk1->ka_max_probe_count = DEF_KA_MAX_PROBE_COUNT;
	csk1->tos = DEF_TOS;
	csk1->ttl = DEF_TTL;
	csk1->snd_seq_scale = DEF_SND_SEQ_SCALE;
	csk1->rcv_buf = DEF_RCV_BUF;
	csk1->snd_buf = DEF_SND_BUF;
	csk1->seed = DEF_SEED;
	csk1->tcp_flags = 0;

	*csk = csk1;
	वापस 0;
पूर्ण

अटल व्योम cnic_cm_cleanup(काष्ठा cnic_sock *csk)
अणु
	अगर (csk->src_port) अणु
		काष्ठा cnic_dev *dev = csk->dev;
		काष्ठा cnic_local *cp = dev->cnic_priv;

		cnic_मुक्त_id(&cp->csk_port_tbl, be16_to_cpu(csk->src_port));
		csk->src_port = 0;
	पूर्ण
पूर्ण

अटल व्योम cnic_बंद_conn(काष्ठा cnic_sock *csk)
अणु
	अगर (test_bit(SK_F_PG_OFFLD_COMPLETE, &csk->flags)) अणु
		cnic_cm_upload_pg(csk);
		clear_bit(SK_F_PG_OFFLD_COMPLETE, &csk->flags);
	पूर्ण
	cnic_cm_cleanup(csk);
पूर्ण

अटल पूर्णांक cnic_cm_destroy(काष्ठा cnic_sock *csk)
अणु
	अगर (!cnic_in_use(csk))
		वापस -EINVAL;

	csk_hold(csk);
	clear_bit(SK_F_INUSE, &csk->flags);
	smp_mb__after_atomic();
	जबतक (atomic_पढ़ो(&csk->ref_count) != 1)
		msleep(1);
	cnic_cm_cleanup(csk);

	csk->flags = 0;
	csk_put(csk);
	वापस 0;
पूर्ण

अटल अंतरभूत u16 cnic_get_vlan(काष्ठा net_device *dev,
				काष्ठा net_device **vlan_dev)
अणु
	अगर (is_vlan_dev(dev)) अणु
		*vlan_dev = vlan_dev_real_dev(dev);
		वापस vlan_dev_vlan_id(dev);
	पूर्ण
	*vlan_dev = dev;
	वापस 0;
पूर्ण

अटल पूर्णांक cnic_get_v4_route(काष्ठा sockaddr_in *dst_addr,
			     काष्ठा dst_entry **dst)
अणु
#अगर defined(CONFIG_INET)
	काष्ठा rtable *rt;

	rt = ip_route_output(&init_net, dst_addr->sin_addr.s_addr, 0, 0, 0);
	अगर (!IS_ERR(rt)) अणु
		*dst = &rt->dst;
		वापस 0;
	पूर्ण
	वापस PTR_ERR(rt);
#अन्यथा
	वापस -ENETUNREACH;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक cnic_get_v6_route(काष्ठा sockaddr_in6 *dst_addr,
			     काष्ठा dst_entry **dst)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा flowi6 fl6;

	स_रखो(&fl6, 0, माप(fl6));
	fl6.daddr = dst_addr->sin6_addr;
	अगर (ipv6_addr_type(&fl6.daddr) & IPV6_ADDR_LINKLOCAL)
		fl6.flowi6_oअगर = dst_addr->sin6_scope_id;

	*dst = ip6_route_output(&init_net, शून्य, &fl6);
	अगर ((*dst)->error) अणु
		dst_release(*dst);
		*dst = शून्य;
		वापस -ENETUNREACH;
	पूर्ण अन्यथा
		वापस 0;
#पूर्ण_अगर

	वापस -ENETUNREACH;
पूर्ण

अटल काष्ठा cnic_dev *cnic_cm_select_dev(काष्ठा sockaddr_in *dst_addr,
					   पूर्णांक ulp_type)
अणु
	काष्ठा cnic_dev *dev = शून्य;
	काष्ठा dst_entry *dst;
	काष्ठा net_device *netdev = शून्य;
	पूर्णांक err = -ENETUNREACH;

	अगर (dst_addr->sin_family == AF_INET)
		err = cnic_get_v4_route(dst_addr, &dst);
	अन्यथा अगर (dst_addr->sin_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *dst_addr6 =
			(काष्ठा sockaddr_in6 *) dst_addr;

		err = cnic_get_v6_route(dst_addr6, &dst);
	पूर्ण अन्यथा
		वापस शून्य;

	अगर (err)
		वापस शून्य;

	अगर (!dst->dev)
		जाओ करोne;

	cnic_get_vlan(dst->dev, &netdev);

	dev = cnic_from_netdev(netdev);

करोne:
	dst_release(dst);
	अगर (dev)
		cnic_put(dev);
	वापस dev;
पूर्ण

अटल पूर्णांक cnic_resolve_addr(काष्ठा cnic_sock *csk, काष्ठा cnic_sockaddr *saddr)
अणु
	काष्ठा cnic_dev *dev = csk->dev;
	काष्ठा cnic_local *cp = dev->cnic_priv;

	वापस cnic_send_nlmsg(cp, ISCSI_KEVENT_PATH_REQ, csk);
पूर्ण

अटल पूर्णांक cnic_get_route(काष्ठा cnic_sock *csk, काष्ठा cnic_sockaddr *saddr)
अणु
	काष्ठा cnic_dev *dev = csk->dev;
	काष्ठा cnic_local *cp = dev->cnic_priv;
	पूर्णांक is_v6, rc = 0;
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा net_device *realdev;
	__be16 local_port;
	u32 port_id;

	अगर (saddr->local.v6.sin6_family == AF_INET6 &&
	    saddr->remote.v6.sin6_family == AF_INET6)
		is_v6 = 1;
	अन्यथा अगर (saddr->local.v4.sin_family == AF_INET &&
		 saddr->remote.v4.sin_family == AF_INET)
		is_v6 = 0;
	अन्यथा
		वापस -EINVAL;

	clear_bit(SK_F_IPV6, &csk->flags);

	अगर (is_v6) अणु
		set_bit(SK_F_IPV6, &csk->flags);
		cnic_get_v6_route(&saddr->remote.v6, &dst);

		स_नकल(&csk->dst_ip[0], &saddr->remote.v6.sin6_addr,
		       माप(काष्ठा in6_addr));
		csk->dst_port = saddr->remote.v6.sin6_port;
		local_port = saddr->local.v6.sin6_port;

	पूर्ण अन्यथा अणु
		cnic_get_v4_route(&saddr->remote.v4, &dst);

		csk->dst_ip[0] = saddr->remote.v4.sin_addr.s_addr;
		csk->dst_port = saddr->remote.v4.sin_port;
		local_port = saddr->local.v4.sin_port;
	पूर्ण

	csk->vlan_id = 0;
	csk->mtu = dev->netdev->mtu;
	अगर (dst && dst->dev) अणु
		u16 vlan = cnic_get_vlan(dst->dev, &realdev);
		अगर (realdev == dev->netdev) अणु
			csk->vlan_id = vlan;
			csk->mtu = dst_mtu(dst);
		पूर्ण
	पूर्ण

	port_id = be16_to_cpu(local_port);
	अगर (port_id >= CNIC_LOCAL_PORT_MIN &&
	    port_id < CNIC_LOCAL_PORT_MAX) अणु
		अगर (cnic_alloc_id(&cp->csk_port_tbl, port_id))
			port_id = 0;
	पूर्ण अन्यथा
		port_id = 0;

	अगर (!port_id) अणु
		port_id = cnic_alloc_new_id(&cp->csk_port_tbl);
		अगर (port_id == -1) अणु
			rc = -ENOMEM;
			जाओ err_out;
		पूर्ण
		local_port = cpu_to_be16(port_id);
	पूर्ण
	csk->src_port = local_port;

err_out:
	dst_release(dst);
	वापस rc;
पूर्ण

अटल व्योम cnic_init_csk_state(काष्ठा cnic_sock *csk)
अणु
	csk->state = 0;
	clear_bit(SK_F_OFFLD_SCHED, &csk->flags);
	clear_bit(SK_F_CLOSING, &csk->flags);
पूर्ण

अटल पूर्णांक cnic_cm_connect(काष्ठा cnic_sock *csk, काष्ठा cnic_sockaddr *saddr)
अणु
	काष्ठा cnic_local *cp = csk->dev->cnic_priv;
	पूर्णांक err = 0;

	अगर (cp->ethdev->drv_state & CNIC_DRV_STATE_NO_ISCSI)
		वापस -EOPNOTSUPP;

	अगर (!cnic_in_use(csk))
		वापस -EINVAL;

	अगर (test_and_set_bit(SK_F_CONNECT_START, &csk->flags))
		वापस -EINVAL;

	cnic_init_csk_state(csk);

	err = cnic_get_route(csk, saddr);
	अगर (err)
		जाओ err_out;

	err = cnic_resolve_addr(csk, saddr);
	अगर (!err)
		वापस 0;

err_out:
	clear_bit(SK_F_CONNECT_START, &csk->flags);
	वापस err;
पूर्ण

अटल पूर्णांक cnic_cm_पात(काष्ठा cnic_sock *csk)
अणु
	काष्ठा cnic_local *cp = csk->dev->cnic_priv;
	u32 opcode = L4_KCQE_OPCODE_VALUE_RESET_COMP;

	अगर (!cnic_in_use(csk))
		वापस -EINVAL;

	अगर (cnic_पात_prep(csk))
		वापस cnic_cm_पात_req(csk);

	/* Getting here means that we haven't started connect, or
	 * connect was not successful, or it has been reset by the target.
	 */

	cp->बंद_conn(csk, opcode);
	अगर (csk->state != opcode) अणु
		/* Wait क्रम remote reset sequence to complete */
		जबतक (test_bit(SK_F_PG_OFFLD_COMPLETE, &csk->flags))
			msleep(1);

		वापस -EALREADY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cnic_cm_बंद(काष्ठा cnic_sock *csk)
अणु
	अगर (!cnic_in_use(csk))
		वापस -EINVAL;

	अगर (cnic_बंद_prep(csk)) अणु
		csk->state = L4_KCQE_OPCODE_VALUE_CLOSE_COMP;
		वापस cnic_cm_बंद_req(csk);
	पूर्ण अन्यथा अणु
		/* Wait क्रम remote reset sequence to complete */
		जबतक (test_bit(SK_F_PG_OFFLD_COMPLETE, &csk->flags))
			msleep(1);

		वापस -EALREADY;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cnic_cm_upcall(काष्ठा cnic_local *cp, काष्ठा cnic_sock *csk,
			   u8 opcode)
अणु
	काष्ठा cnic_ulp_ops *ulp_ops;
	पूर्णांक ulp_type = csk->ulp_type;

	rcu_पढ़ो_lock();
	ulp_ops = rcu_dereference(cp->ulp_ops[ulp_type]);
	अगर (ulp_ops) अणु
		अगर (opcode == L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE)
			ulp_ops->cm_connect_complete(csk);
		अन्यथा अगर (opcode == L4_KCQE_OPCODE_VALUE_CLOSE_COMP)
			ulp_ops->cm_बंद_complete(csk);
		अन्यथा अगर (opcode == L4_KCQE_OPCODE_VALUE_RESET_RECEIVED)
			ulp_ops->cm_remote_पात(csk);
		अन्यथा अगर (opcode == L4_KCQE_OPCODE_VALUE_RESET_COMP)
			ulp_ops->cm_पात_complete(csk);
		अन्यथा अगर (opcode == L4_KCQE_OPCODE_VALUE_CLOSE_RECEIVED)
			ulp_ops->cm_remote_बंद(csk);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक cnic_cm_set_pg(काष्ठा cnic_sock *csk)
अणु
	अगर (cnic_offld_prep(csk)) अणु
		अगर (test_bit(SK_F_PG_OFFLD_COMPLETE, &csk->flags))
			cnic_cm_update_pg(csk);
		अन्यथा
			cnic_cm_offload_pg(csk);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cnic_cm_process_offld_pg(काष्ठा cnic_dev *dev, काष्ठा l4_kcq *kcqe)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	u32 l5_cid = kcqe->pg_host_opaque;
	u8 opcode = kcqe->op_code;
	काष्ठा cnic_sock *csk = &cp->csk_tbl[l5_cid];

	csk_hold(csk);
	अगर (!cnic_in_use(csk))
		जाओ करोne;

	अगर (opcode == L4_KCQE_OPCODE_VALUE_UPDATE_PG) अणु
		clear_bit(SK_F_OFFLD_SCHED, &csk->flags);
		जाओ करोne;
	पूर्ण
	/* Possible PG kcqe status:  SUCCESS, OFFLOADED_PG, or CTX_ALLOC_FAIL */
	अगर (kcqe->status == L4_KCQE_COMPLETION_STATUS_CTX_ALLOC_FAIL) अणु
		clear_bit(SK_F_OFFLD_SCHED, &csk->flags);
		cnic_cm_upcall(cp, csk,
			       L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE);
		जाओ करोne;
	पूर्ण

	csk->pg_cid = kcqe->pg_cid;
	set_bit(SK_F_PG_OFFLD_COMPLETE, &csk->flags);
	cnic_cm_conn_req(csk);

करोne:
	csk_put(csk);
पूर्ण

अटल व्योम cnic_process_fcoe_term_conn(काष्ठा cnic_dev *dev, काष्ठा kcqe *kcqe)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा fcoe_kcqe *fc_kcqe = (काष्ठा fcoe_kcqe *) kcqe;
	u32 l5_cid = fc_kcqe->fcoe_conn_id + BNX2X_FCOE_L5_CID_BASE;
	काष्ठा cnic_context *ctx = &cp->ctx_tbl[l5_cid];

	ctx->बारtamp = jअगरfies;
	ctx->रुको_cond = 1;
	wake_up(&ctx->रुकोq);
पूर्ण

अटल व्योम cnic_cm_process_kcqe(काष्ठा cnic_dev *dev, काष्ठा kcqe *kcqe)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा l4_kcq *l4kcqe = (काष्ठा l4_kcq *) kcqe;
	u8 opcode = l4kcqe->op_code;
	u32 l5_cid;
	काष्ठा cnic_sock *csk;

	अगर (opcode == FCOE_RAMROD_CMD_ID_TERMINATE_CONN) अणु
		cnic_process_fcoe_term_conn(dev, kcqe);
		वापस;
	पूर्ण
	अगर (opcode == L4_KCQE_OPCODE_VALUE_OFFLOAD_PG ||
	    opcode == L4_KCQE_OPCODE_VALUE_UPDATE_PG) अणु
		cnic_cm_process_offld_pg(dev, l4kcqe);
		वापस;
	पूर्ण

	l5_cid = l4kcqe->conn_id;
	अगर (opcode & 0x80)
		l5_cid = l4kcqe->cid;
	अगर (l5_cid >= MAX_CM_SK_TBL_SZ)
		वापस;

	csk = &cp->csk_tbl[l5_cid];
	csk_hold(csk);

	अगर (!cnic_in_use(csk)) अणु
		csk_put(csk);
		वापस;
	पूर्ण

	चयन (opcode) अणु
	हाल L5CM_RAMROD_CMD_ID_TCP_CONNECT:
		अगर (l4kcqe->status != 0) अणु
			clear_bit(SK_F_OFFLD_SCHED, &csk->flags);
			cnic_cm_upcall(cp, csk,
				       L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE);
		पूर्ण
		अवरोध;
	हाल L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE:
		अगर (l4kcqe->status == 0)
			set_bit(SK_F_OFFLD_COMPLETE, &csk->flags);
		अन्यथा अगर (l4kcqe->status ==
			 L4_KCQE_COMPLETION_STATUS_PARITY_ERROR)
			set_bit(SK_F_HW_ERR, &csk->flags);

		smp_mb__beक्रमe_atomic();
		clear_bit(SK_F_OFFLD_SCHED, &csk->flags);
		cnic_cm_upcall(cp, csk, opcode);
		अवरोध;

	हाल L5CM_RAMROD_CMD_ID_CLOSE: अणु
		काष्ठा iscsi_kcqe *l5kcqe = (काष्ठा iscsi_kcqe *) kcqe;

		अगर (l4kcqe->status == 0 && l5kcqe->completion_status == 0)
			अवरोध;

		netdev_warn(dev->netdev, "RAMROD CLOSE compl with status 0x%x completion status 0x%x\n",
			    l4kcqe->status, l5kcqe->completion_status);
		opcode = L4_KCQE_OPCODE_VALUE_CLOSE_COMP;
	पूर्ण
		fallthrough;
	हाल L4_KCQE_OPCODE_VALUE_RESET_RECEIVED:
	हाल L4_KCQE_OPCODE_VALUE_CLOSE_COMP:
	हाल L4_KCQE_OPCODE_VALUE_RESET_COMP:
	हाल L5CM_RAMROD_CMD_ID_SEARCHER_DELETE:
	हाल L5CM_RAMROD_CMD_ID_TERMINATE_OFFLOAD:
		अगर (l4kcqe->status == L4_KCQE_COMPLETION_STATUS_PARITY_ERROR)
			set_bit(SK_F_HW_ERR, &csk->flags);

		cp->बंद_conn(csk, opcode);
		अवरोध;

	हाल L4_KCQE_OPCODE_VALUE_CLOSE_RECEIVED:
		/* after we alपढ़ोy sent CLOSE_REQ */
		अगर (test_bit(CNIC_F_BNX2X_CLASS, &dev->flags) &&
		    !test_bit(SK_F_OFFLD_COMPLETE, &csk->flags) &&
		    csk->state == L4_KCQE_OPCODE_VALUE_CLOSE_COMP)
			cp->बंद_conn(csk, L4_KCQE_OPCODE_VALUE_RESET_COMP);
		अन्यथा
			cnic_cm_upcall(cp, csk, opcode);
		अवरोध;
	पूर्ण
	csk_put(csk);
पूर्ण

अटल व्योम cnic_cm_indicate_kcqe(व्योम *data, काष्ठा kcqe *kcqe[], u32 num)
अणु
	काष्ठा cnic_dev *dev = data;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		cnic_cm_process_kcqe(dev, kcqe[i]);
पूर्ण

अटल काष्ठा cnic_ulp_ops cm_ulp_ops = अणु
	.indicate_kcqes		= cnic_cm_indicate_kcqe,
पूर्ण;

अटल व्योम cnic_cm_मुक्त_mem(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;

	kvमुक्त(cp->csk_tbl);
	cp->csk_tbl = शून्य;
	cnic_मुक्त_id_tbl(&cp->csk_port_tbl);
पूर्ण

अटल पूर्णांक cnic_cm_alloc_mem(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	u32 port_id;
	पूर्णांक i;

	cp->csk_tbl = kvसुस्मृति(MAX_CM_SK_TBL_SZ, माप(काष्ठा cnic_sock),
			       GFP_KERNEL);
	अगर (!cp->csk_tbl)
		वापस -ENOMEM;

	क्रम (i = 0; i < MAX_CM_SK_TBL_SZ; i++)
		atomic_set(&cp->csk_tbl[i].ref_count, 0);

	port_id = pअक्रमom_u32();
	port_id %= CNIC_LOCAL_PORT_RANGE;
	अगर (cnic_init_id_tbl(&cp->csk_port_tbl, CNIC_LOCAL_PORT_RANGE,
			     CNIC_LOCAL_PORT_MIN, port_id)) अणु
		cnic_cm_मुक्त_mem(dev);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cnic_पढ़ोy_to_बंद(काष्ठा cnic_sock *csk, u32 opcode)
अणु
	अगर (test_and_clear_bit(SK_F_OFFLD_COMPLETE, &csk->flags)) अणु
		/* Unsolicited RESET_COMP or RESET_RECEIVED */
		opcode = L4_KCQE_OPCODE_VALUE_RESET_RECEIVED;
		csk->state = opcode;
	पूर्ण

	/* 1. If event opcode matches the expected event in csk->state
	 * 2. If the expected event is CLOSE_COMP or RESET_COMP, we accept any
	 *    event
	 * 3. If the expected event is 0, meaning the connection was never
	 *    never established, we accept the opcode from cm_पात.
	 */
	अगर (opcode == csk->state || csk->state == 0 ||
	    csk->state == L4_KCQE_OPCODE_VALUE_CLOSE_COMP ||
	    csk->state == L4_KCQE_OPCODE_VALUE_RESET_COMP) अणु
		अगर (!test_and_set_bit(SK_F_CLOSING, &csk->flags)) अणु
			अगर (csk->state == 0)
				csk->state = opcode;
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cnic_बंद_bnx2_conn(काष्ठा cnic_sock *csk, u32 opcode)
अणु
	काष्ठा cnic_dev *dev = csk->dev;
	काष्ठा cnic_local *cp = dev->cnic_priv;

	अगर (opcode == L4_KCQE_OPCODE_VALUE_RESET_RECEIVED) अणु
		cnic_cm_upcall(cp, csk, opcode);
		वापस;
	पूर्ण

	clear_bit(SK_F_CONNECT_START, &csk->flags);
	cnic_बंद_conn(csk);
	csk->state = opcode;
	cnic_cm_upcall(cp, csk, opcode);
पूर्ण

अटल व्योम cnic_cm_stop_bnx2_hw(काष्ठा cnic_dev *dev)
अणु
पूर्ण

अटल पूर्णांक cnic_cm_init_bnx2_hw(काष्ठा cnic_dev *dev)
अणु
	u32 seed;

	seed = pअक्रमom_u32();
	cnic_ctx_wr(dev, 45, 0, seed);
	वापस 0;
पूर्ण

अटल व्योम cnic_बंद_bnx2x_conn(काष्ठा cnic_sock *csk, u32 opcode)
अणु
	काष्ठा cnic_dev *dev = csk->dev;
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_context *ctx = &cp->ctx_tbl[csk->l5_cid];
	जोड़ l5cm_specअगरic_data l5_data;
	u32 cmd = 0;
	पूर्णांक बंद_complete = 0;

	चयन (opcode) अणु
	हाल L4_KCQE_OPCODE_VALUE_RESET_RECEIVED:
	हाल L4_KCQE_OPCODE_VALUE_CLOSE_COMP:
	हाल L4_KCQE_OPCODE_VALUE_RESET_COMP:
		अगर (cnic_पढ़ोy_to_बंद(csk, opcode)) अणु
			अगर (test_bit(SK_F_HW_ERR, &csk->flags))
				बंद_complete = 1;
			अन्यथा अगर (test_bit(SK_F_PG_OFFLD_COMPLETE, &csk->flags))
				cmd = L5CM_RAMROD_CMD_ID_SEARCHER_DELETE;
			अन्यथा
				बंद_complete = 1;
		पूर्ण
		अवरोध;
	हाल L5CM_RAMROD_CMD_ID_SEARCHER_DELETE:
		cmd = L5CM_RAMROD_CMD_ID_TERMINATE_OFFLOAD;
		अवरोध;
	हाल L5CM_RAMROD_CMD_ID_TERMINATE_OFFLOAD:
		बंद_complete = 1;
		अवरोध;
	पूर्ण
	अगर (cmd) अणु
		स_रखो(&l5_data, 0, माप(l5_data));

		cnic_submit_kwqe_16(dev, cmd, csk->cid, ISCSI_CONNECTION_TYPE,
				    &l5_data);
	पूर्ण अन्यथा अगर (बंद_complete) अणु
		ctx->बारtamp = jअगरfies;
		cnic_बंद_conn(csk);
		cnic_cm_upcall(cp, csk, csk->state);
	पूर्ण
पूर्ण

अटल व्योम cnic_cm_stop_bnx2x_hw(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;

	अगर (!cp->ctx_tbl)
		वापस;

	अगर (!netअगर_running(dev->netdev))
		वापस;

	cnic_bnx2x_delete_रुको(dev, 0);

	cancel_delayed_work(&cp->delete_task);
	flush_workqueue(cnic_wq);

	अगर (atomic_पढ़ो(&cp->iscsi_conn) != 0)
		netdev_warn(dev->netdev, "%d iSCSI connections not destroyed\n",
			    atomic_पढ़ो(&cp->iscsi_conn));
पूर्ण

अटल पूर्णांक cnic_cm_init_bnx2x_hw(काष्ठा cnic_dev *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	u32 pfid = bp->pfid;
	u32 port = BP_PORT(bp);

	cnic_init_bnx2x_mac(dev);
	cnic_bnx2x_set_tcp_options(dev, 0, 1);

	CNIC_WR16(dev, BAR_XSTRORM_INTMEM +
		  XSTORM_ISCSI_LOCAL_VLAN_OFFSET(pfid), 0);

	CNIC_WR(dev, BAR_XSTRORM_INTMEM +
		XSTORM_TCP_GLOBAL_DEL_ACK_COUNTER_ENABLED_OFFSET(port), 1);
	CNIC_WR(dev, BAR_XSTRORM_INTMEM +
		XSTORM_TCP_GLOBAL_DEL_ACK_COUNTER_MAX_COUNT_OFFSET(port),
		DEF_MAX_DA_COUNT);

	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_TCP_VARS_TTL_OFFSET(pfid), DEF_TTL);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_TCP_VARS_TOS_OFFSET(pfid), DEF_TOS);
	CNIC_WR8(dev, BAR_XSTRORM_INTMEM +
		 XSTORM_ISCSI_TCP_VARS_ADV_WND_SCL_OFFSET(pfid), 2);
	CNIC_WR(dev, BAR_XSTRORM_INTMEM +
		XSTORM_TCP_TX_SWS_TIMER_VAL_OFFSET(pfid), DEF_SWS_TIMER);

	CNIC_WR(dev, BAR_TSTRORM_INTMEM + TSTORM_TCP_MAX_CWND_OFFSET(pfid),
		DEF_MAX_CWND);
	वापस 0;
पूर्ण

अटल व्योम cnic_delete_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cnic_local *cp;
	काष्ठा cnic_dev *dev;
	u32 i;
	पूर्णांक need_resched = 0;

	cp = container_of(work, काष्ठा cnic_local, delete_task.work);
	dev = cp->dev;

	अगर (test_and_clear_bit(CNIC_LCL_FL_STOP_ISCSI, &cp->cnic_local_flags)) अणु
		काष्ठा drv_ctl_info info;

		cnic_ulp_stop_one(cp, CNIC_ULP_ISCSI);

		स_रखो(&info, 0, माप(काष्ठा drv_ctl_info));
		info.cmd = DRV_CTL_ISCSI_STOPPED_CMD;
		cp->ethdev->drv_ctl(dev->netdev, &info);
	पूर्ण

	क्रम (i = 0; i < cp->max_cid_space; i++) अणु
		काष्ठा cnic_context *ctx = &cp->ctx_tbl[i];
		पूर्णांक err;

		अगर (!test_bit(CTX_FL_OFFLD_START, &ctx->ctx_flags) ||
		    !test_bit(CTX_FL_DELETE_WAIT, &ctx->ctx_flags))
			जारी;

		अगर (!समय_after(jअगरfies, ctx->बारtamp + (2 * HZ))) अणु
			need_resched = 1;
			जारी;
		पूर्ण

		अगर (!test_and_clear_bit(CTX_FL_DELETE_WAIT, &ctx->ctx_flags))
			जारी;

		err = cnic_bnx2x_destroy_ramrod(dev, i);

		cnic_मुक्त_bnx2x_conn_resc(dev, i);
		अगर (!err) अणु
			अगर (ctx->ulp_proto_id == CNIC_ULP_ISCSI)
				atomic_dec(&cp->iscsi_conn);

			clear_bit(CTX_FL_OFFLD_START, &ctx->ctx_flags);
		पूर्ण
	पूर्ण

	अगर (need_resched)
		queue_delayed_work(cnic_wq, &cp->delete_task,
				   msecs_to_jअगरfies(10));

पूर्ण

अटल पूर्णांक cnic_cm_खोलो(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	पूर्णांक err;

	err = cnic_cm_alloc_mem(dev);
	अगर (err)
		वापस err;

	err = cp->start_cm(dev);

	अगर (err)
		जाओ err_out;

	INIT_DELAYED_WORK(&cp->delete_task, cnic_delete_task);

	dev->cm_create = cnic_cm_create;
	dev->cm_destroy = cnic_cm_destroy;
	dev->cm_connect = cnic_cm_connect;
	dev->cm_पात = cnic_cm_पात;
	dev->cm_बंद = cnic_cm_बंद;
	dev->cm_select_dev = cnic_cm_select_dev;

	cp->ulp_handle[CNIC_ULP_L4] = dev;
	rcu_assign_poपूर्णांकer(cp->ulp_ops[CNIC_ULP_L4], &cm_ulp_ops);
	वापस 0;

err_out:
	cnic_cm_मुक्त_mem(dev);
	वापस err;
पूर्ण

अटल पूर्णांक cnic_cm_shutकरोwn(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	पूर्णांक i;

	अगर (!cp->csk_tbl)
		वापस 0;

	क्रम (i = 0; i < MAX_CM_SK_TBL_SZ; i++) अणु
		काष्ठा cnic_sock *csk = &cp->csk_tbl[i];

		clear_bit(SK_F_INUSE, &csk->flags);
		cnic_cm_cleanup(csk);
	पूर्ण
	cnic_cm_मुक्त_mem(dev);

	वापस 0;
पूर्ण

अटल व्योम cnic_init_context(काष्ठा cnic_dev *dev, u32 cid)
अणु
	u32 cid_addr;
	पूर्णांक i;

	cid_addr = GET_CID_ADDR(cid);

	क्रम (i = 0; i < CTX_SIZE; i += 4)
		cnic_ctx_wr(dev, cid_addr, i, 0);
पूर्ण

अटल पूर्णांक cnic_setup_5709_context(काष्ठा cnic_dev *dev, पूर्णांक valid)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	पूर्णांक ret = 0, i;
	u32 valid_bit = valid ? BNX2_CTX_HOST_PAGE_TBL_DATA0_VALID : 0;

	अगर (BNX2_CHIP(cp) != BNX2_CHIP_5709)
		वापस 0;

	क्रम (i = 0; i < cp->ctx_blks; i++) अणु
		पूर्णांक j;
		u32 idx = cp->ctx_arr[i].cid / cp->cids_per_blk;
		u32 val;

		स_रखो(cp->ctx_arr[i].ctx, 0, CNIC_PAGE_SIZE);

		CNIC_WR(dev, BNX2_CTX_HOST_PAGE_TBL_DATA0,
			(cp->ctx_arr[i].mapping & 0xffffffff) | valid_bit);
		CNIC_WR(dev, BNX2_CTX_HOST_PAGE_TBL_DATA1,
			(u64) cp->ctx_arr[i].mapping >> 32);
		CNIC_WR(dev, BNX2_CTX_HOST_PAGE_TBL_CTRL, idx |
			BNX2_CTX_HOST_PAGE_TBL_CTRL_WRITE_REQ);
		क्रम (j = 0; j < 10; j++) अणु

			val = CNIC_RD(dev, BNX2_CTX_HOST_PAGE_TBL_CTRL);
			अगर (!(val & BNX2_CTX_HOST_PAGE_TBL_CTRL_WRITE_REQ))
				अवरोध;
			udelay(5);
		पूर्ण
		अगर (val & BNX2_CTX_HOST_PAGE_TBL_CTRL_WRITE_REQ) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम cnic_मुक्त_irq(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;

	अगर (ethdev->drv_state & CNIC_DRV_STATE_USING_MSIX) अणु
		cp->disable_पूर्णांक_sync(dev);
		tasklet_समाप्त(&cp->cnic_irq_task);
		मुक्त_irq(ethdev->irq_arr[0].vector, dev);
	पूर्ण
पूर्ण

अटल पूर्णांक cnic_request_irq(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	पूर्णांक err;

	err = request_irq(ethdev->irq_arr[0].vector, cnic_irq, 0, "cnic", dev);
	अगर (err)
		tasklet_disable(&cp->cnic_irq_task);

	वापस err;
पूर्ण

अटल पूर्णांक cnic_init_bnx2_irq(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;

	अगर (ethdev->drv_state & CNIC_DRV_STATE_USING_MSIX) अणु
		पूर्णांक err, i = 0;
		पूर्णांक sblk_num = cp->status_blk_num;
		u32 base = ((sblk_num - 1) * BNX2_HC_SB_CONFIG_SIZE) +
			   BNX2_HC_SB_CONFIG_1;

		CNIC_WR(dev, base, BNX2_HC_SB_CONFIG_1_ONE_SHOT);

		CNIC_WR(dev, base + BNX2_HC_COMP_PROD_TRIP_OFF, (2 << 16) | 8);
		CNIC_WR(dev, base + BNX2_HC_COM_TICKS_OFF, (64 << 16) | 220);
		CNIC_WR(dev, base + BNX2_HC_CMD_TICKS_OFF, (64 << 16) | 220);

		cp->last_status_idx = cp->status_blk.bnx2->status_idx;
		tasklet_setup(&cp->cnic_irq_task, cnic_service_bnx2_msix);
		err = cnic_request_irq(dev);
		अगर (err)
			वापस err;

		जबतक (cp->status_blk.bnx2->status_completion_producer_index &&
		       i < 10) अणु
			CNIC_WR(dev, BNX2_HC_COALESCE_NOW,
				1 << (11 + sblk_num));
			udelay(10);
			i++;
			barrier();
		पूर्ण
		अगर (cp->status_blk.bnx2->status_completion_producer_index) अणु
			cnic_मुक्त_irq(dev);
			जाओ failed;
		पूर्ण

	पूर्ण अन्यथा अणु
		काष्ठा status_block *sblk = cp->status_blk.gen;
		u32 hc_cmd = CNIC_RD(dev, BNX2_HC_COMMAND);
		पूर्णांक i = 0;

		जबतक (sblk->status_completion_producer_index && i < 10) अणु
			CNIC_WR(dev, BNX2_HC_COMMAND,
				hc_cmd | BNX2_HC_COMMAND_COAL_NOW_WO_INT);
			udelay(10);
			i++;
			barrier();
		पूर्ण
		अगर (sblk->status_completion_producer_index)
			जाओ failed;

	पूर्ण
	वापस 0;

failed:
	netdev_err(dev->netdev, "KCQ index not resetting to 0\n");
	वापस -EBUSY;
पूर्ण

अटल व्योम cnic_enable_bnx2_पूर्णांक(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;

	अगर (!(ethdev->drv_state & CNIC_DRV_STATE_USING_MSIX))
		वापस;

	CNIC_WR(dev, BNX2_PCICFG_INT_ACK_CMD, cp->पूर्णांक_num |
		BNX2_PCICFG_INT_ACK_CMD_INDEX_VALID | cp->last_status_idx);
पूर्ण

अटल व्योम cnic_disable_bnx2_पूर्णांक_sync(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;

	अगर (!(ethdev->drv_state & CNIC_DRV_STATE_USING_MSIX))
		वापस;

	CNIC_WR(dev, BNX2_PCICFG_INT_ACK_CMD, cp->पूर्णांक_num |
		BNX2_PCICFG_INT_ACK_CMD_MASK_INT);
	CNIC_RD(dev, BNX2_PCICFG_INT_ACK_CMD);
	synchronize_irq(ethdev->irq_arr[0].vector);
पूर्ण

अटल व्योम cnic_init_bnx2_tx_ring(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	काष्ठा cnic_uio_dev *udev = cp->udev;
	u32 cid_addr, tx_cid, sb_id;
	u32 val, offset0, offset1, offset2, offset3;
	पूर्णांक i;
	काष्ठा bnx2_tx_bd *txbd;
	dma_addr_t buf_map, ring_map = udev->l2_ring_map;
	काष्ठा status_block *s_blk = cp->status_blk.gen;

	sb_id = cp->status_blk_num;
	tx_cid = 20;
	cp->tx_cons_ptr = &s_blk->status_tx_quick_consumer_index2;
	अगर (ethdev->drv_state & CNIC_DRV_STATE_USING_MSIX) अणु
		काष्ठा status_block_msix *sblk = cp->status_blk.bnx2;

		tx_cid = TX_TSS_CID + sb_id - 1;
		CNIC_WR(dev, BNX2_TSCH_TSS_CFG, (sb_id << 24) |
			(TX_TSS_CID << 7));
		cp->tx_cons_ptr = &sblk->status_tx_quick_consumer_index;
	पूर्ण
	cp->tx_cons = *cp->tx_cons_ptr;

	cid_addr = GET_CID_ADDR(tx_cid);
	अगर (BNX2_CHIP(cp) == BNX2_CHIP_5709) अणु
		u32 cid_addr2 = GET_CID_ADDR(tx_cid + 4) + 0x40;

		क्रम (i = 0; i < PHY_CTX_SIZE; i += 4)
			cnic_ctx_wr(dev, cid_addr2, i, 0);

		offset0 = BNX2_L2CTX_TYPE_XI;
		offset1 = BNX2_L2CTX_CMD_TYPE_XI;
		offset2 = BNX2_L2CTX_TBDR_BHADDR_HI_XI;
		offset3 = BNX2_L2CTX_TBDR_BHADDR_LO_XI;
	पूर्ण अन्यथा अणु
		cnic_init_context(dev, tx_cid);
		cnic_init_context(dev, tx_cid + 1);

		offset0 = BNX2_L2CTX_TYPE;
		offset1 = BNX2_L2CTX_CMD_TYPE;
		offset2 = BNX2_L2CTX_TBDR_BHADDR_HI;
		offset3 = BNX2_L2CTX_TBDR_BHADDR_LO;
	पूर्ण
	val = BNX2_L2CTX_TYPE_TYPE_L2 | BNX2_L2CTX_TYPE_SIZE_L2;
	cnic_ctx_wr(dev, cid_addr, offset0, val);

	val = BNX2_L2CTX_CMD_TYPE_TYPE_L2 | (8 << 16);
	cnic_ctx_wr(dev, cid_addr, offset1, val);

	txbd = udev->l2_ring;

	buf_map = udev->l2_buf_map;
	क्रम (i = 0; i < BNX2_MAX_TX_DESC_CNT; i++, txbd++) अणु
		txbd->tx_bd_haddr_hi = (u64) buf_map >> 32;
		txbd->tx_bd_haddr_lo = (u64) buf_map & 0xffffffff;
	पूर्ण
	val = (u64) ring_map >> 32;
	cnic_ctx_wr(dev, cid_addr, offset2, val);
	txbd->tx_bd_haddr_hi = val;

	val = (u64) ring_map & 0xffffffff;
	cnic_ctx_wr(dev, cid_addr, offset3, val);
	txbd->tx_bd_haddr_lo = val;
पूर्ण

अटल व्योम cnic_init_bnx2_rx_ring(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	काष्ठा cnic_uio_dev *udev = cp->udev;
	u32 cid_addr, sb_id, val, coal_reg, coal_val;
	पूर्णांक i;
	काष्ठा bnx2_rx_bd *rxbd;
	काष्ठा status_block *s_blk = cp->status_blk.gen;
	dma_addr_t ring_map = udev->l2_ring_map;

	sb_id = cp->status_blk_num;
	cnic_init_context(dev, 2);
	cp->rx_cons_ptr = &s_blk->status_rx_quick_consumer_index2;
	coal_reg = BNX2_HC_COMMAND;
	coal_val = CNIC_RD(dev, coal_reg);
	अगर (ethdev->drv_state & CNIC_DRV_STATE_USING_MSIX) अणु
		काष्ठा status_block_msix *sblk = cp->status_blk.bnx2;

		cp->rx_cons_ptr = &sblk->status_rx_quick_consumer_index;
		coal_reg = BNX2_HC_COALESCE_NOW;
		coal_val = 1 << (11 + sb_id);
	पूर्ण
	i = 0;
	जबतक (!(*cp->rx_cons_ptr != 0) && i < 10) अणु
		CNIC_WR(dev, coal_reg, coal_val);
		udelay(10);
		i++;
		barrier();
	पूर्ण
	cp->rx_cons = *cp->rx_cons_ptr;

	cid_addr = GET_CID_ADDR(2);
	val = BNX2_L2CTX_CTX_TYPE_CTX_BD_CHN_TYPE_VALUE |
	      BNX2_L2CTX_CTX_TYPE_SIZE_L2 | (0x02 << 8);
	cnic_ctx_wr(dev, cid_addr, BNX2_L2CTX_CTX_TYPE, val);

	अगर (sb_id == 0)
		val = 2 << BNX2_L2CTX_L2_STATUSB_NUM_SHIFT;
	अन्यथा
		val = BNX2_L2CTX_L2_STATUSB_NUM(sb_id);
	cnic_ctx_wr(dev, cid_addr, BNX2_L2CTX_HOST_BDIDX, val);

	rxbd = udev->l2_ring + CNIC_PAGE_SIZE;
	क्रम (i = 0; i < BNX2_MAX_RX_DESC_CNT; i++, rxbd++) अणु
		dma_addr_t buf_map;
		पूर्णांक n = (i % cp->l2_rx_ring_size) + 1;

		buf_map = udev->l2_buf_map + (n * cp->l2_single_buf_size);
		rxbd->rx_bd_len = cp->l2_single_buf_size;
		rxbd->rx_bd_flags = RX_BD_FLAGS_START | RX_BD_FLAGS_END;
		rxbd->rx_bd_haddr_hi = (u64) buf_map >> 32;
		rxbd->rx_bd_haddr_lo = (u64) buf_map & 0xffffffff;
	पूर्ण
	val = (u64) (ring_map + CNIC_PAGE_SIZE) >> 32;
	cnic_ctx_wr(dev, cid_addr, BNX2_L2CTX_NX_BDHADDR_HI, val);
	rxbd->rx_bd_haddr_hi = val;

	val = (u64) (ring_map + CNIC_PAGE_SIZE) & 0xffffffff;
	cnic_ctx_wr(dev, cid_addr, BNX2_L2CTX_NX_BDHADDR_LO, val);
	rxbd->rx_bd_haddr_lo = val;

	val = cnic_reg_rd_ind(dev, BNX2_RXP_SCRATCH_RXP_FLOOD);
	cnic_reg_wr_ind(dev, BNX2_RXP_SCRATCH_RXP_FLOOD, val | (1 << 2));
पूर्ण

अटल व्योम cnic_shutकरोwn_bnx2_rx_ring(काष्ठा cnic_dev *dev)
अणु
	काष्ठा kwqe *wqes[1], l2kwqe;

	स_रखो(&l2kwqe, 0, माप(l2kwqe));
	wqes[0] = &l2kwqe;
	l2kwqe.kwqe_op_flag = (L2_LAYER_CODE << KWQE_LAYER_SHIFT) |
			      (L2_KWQE_OPCODE_VALUE_FLUSH <<
			       KWQE_OPCODE_SHIFT) | 2;
	dev->submit_kwqes(dev, wqes, 1);
पूर्ण

अटल व्योम cnic_set_bnx2_mac(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	u32 val;

	val = cp->func << 2;

	cp->shmem_base = cnic_reg_rd_ind(dev, BNX2_SHM_HDR_ADDR_0 + val);

	val = cnic_reg_rd_ind(dev, cp->shmem_base +
			      BNX2_PORT_HW_CFG_ISCSI_MAC_UPPER);
	dev->mac_addr[0] = (u8) (val >> 8);
	dev->mac_addr[1] = (u8) val;

	CNIC_WR(dev, BNX2_EMAC_MAC_MATCH4, val);

	val = cnic_reg_rd_ind(dev, cp->shmem_base +
			      BNX2_PORT_HW_CFG_ISCSI_MAC_LOWER);
	dev->mac_addr[2] = (u8) (val >> 24);
	dev->mac_addr[3] = (u8) (val >> 16);
	dev->mac_addr[4] = (u8) (val >> 8);
	dev->mac_addr[5] = (u8) val;

	CNIC_WR(dev, BNX2_EMAC_MAC_MATCH5, val);

	val = 4 | BNX2_RPM_SORT_USER2_BC_EN;
	अगर (BNX2_CHIP(cp) != BNX2_CHIP_5709)
		val |= BNX2_RPM_SORT_USER2_PROM_VLAN;

	CNIC_WR(dev, BNX2_RPM_SORT_USER2, 0x0);
	CNIC_WR(dev, BNX2_RPM_SORT_USER2, val);
	CNIC_WR(dev, BNX2_RPM_SORT_USER2, val | BNX2_RPM_SORT_USER2_ENA);
पूर्ण

अटल पूर्णांक cnic_start_bnx2_hw(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	काष्ठा status_block *sblk = cp->status_blk.gen;
	u32 val, kcq_cid_addr, kwq_cid_addr;
	पूर्णांक err;

	cnic_set_bnx2_mac(dev);

	val = CNIC_RD(dev, BNX2_MQ_CONFIG);
	val &= ~BNX2_MQ_CONFIG_KNL_BYP_BLK_SIZE;
	अगर (CNIC_PAGE_BITS > 12)
		val |= (12 - 8)  << 4;
	अन्यथा
		val |= (CNIC_PAGE_BITS - 8)  << 4;

	CNIC_WR(dev, BNX2_MQ_CONFIG, val);

	CNIC_WR(dev, BNX2_HC_COMP_PROD_TRIP, (2 << 16) | 8);
	CNIC_WR(dev, BNX2_HC_COM_TICKS, (64 << 16) | 220);
	CNIC_WR(dev, BNX2_HC_CMD_TICKS, (64 << 16) | 220);

	err = cnic_setup_5709_context(dev, 1);
	अगर (err)
		वापस err;

	cnic_init_context(dev, KWQ_CID);
	cnic_init_context(dev, KCQ_CID);

	kwq_cid_addr = GET_CID_ADDR(KWQ_CID);
	cp->kwq_io_addr = MB_GET_CID_ADDR(KWQ_CID) + L5_KRNLQ_HOST_QIDX;

	cp->max_kwq_idx = MAX_KWQ_IDX;
	cp->kwq_prod_idx = 0;
	cp->kwq_con_idx = 0;
	set_bit(CNIC_LCL_FL_KWQ_INIT, &cp->cnic_local_flags);

	अगर (BNX2_CHIP(cp) == BNX2_CHIP_5706 || BNX2_CHIP(cp) == BNX2_CHIP_5708)
		cp->kwq_con_idx_ptr = &sblk->status_rx_quick_consumer_index15;
	अन्यथा
		cp->kwq_con_idx_ptr = &sblk->status_cmd_consumer_index;

	/* Initialize the kernel work queue context. */
	val = KRNLQ_TYPE_TYPE_KRNLQ | KRNLQ_SIZE_TYPE_SIZE |
	      (CNIC_PAGE_BITS - 8) | KRNLQ_FLAGS_QE_SELF_SEQ;
	cnic_ctx_wr(dev, kwq_cid_addr, L5_KRNLQ_TYPE, val);

	val = (CNIC_PAGE_SIZE / माप(काष्ठा kwqe) - 1) << 16;
	cnic_ctx_wr(dev, kwq_cid_addr, L5_KRNLQ_QE_SELF_SEQ_MAX, val);

	val = ((CNIC_PAGE_SIZE / माप(काष्ठा kwqe)) << 16) | KWQ_PAGE_CNT;
	cnic_ctx_wr(dev, kwq_cid_addr, L5_KRNLQ_PGTBL_NPAGES, val);

	val = (u32) ((u64) cp->kwq_info.pgtbl_map >> 32);
	cnic_ctx_wr(dev, kwq_cid_addr, L5_KRNLQ_PGTBL_HADDR_HI, val);

	val = (u32) cp->kwq_info.pgtbl_map;
	cnic_ctx_wr(dev, kwq_cid_addr, L5_KRNLQ_PGTBL_HADDR_LO, val);

	kcq_cid_addr = GET_CID_ADDR(KCQ_CID);
	cp->kcq1.io_addr = MB_GET_CID_ADDR(KCQ_CID) + L5_KRNLQ_HOST_QIDX;

	cp->kcq1.sw_prod_idx = 0;
	cp->kcq1.hw_prod_idx_ptr =
		&sblk->status_completion_producer_index;

	cp->kcq1.status_idx_ptr = &sblk->status_idx;

	/* Initialize the kernel complete queue context. */
	val = KRNLQ_TYPE_TYPE_KRNLQ | KRNLQ_SIZE_TYPE_SIZE |
	      (CNIC_PAGE_BITS - 8) | KRNLQ_FLAGS_QE_SELF_SEQ;
	cnic_ctx_wr(dev, kcq_cid_addr, L5_KRNLQ_TYPE, val);

	val = (CNIC_PAGE_SIZE / माप(काष्ठा kcqe) - 1) << 16;
	cnic_ctx_wr(dev, kcq_cid_addr, L5_KRNLQ_QE_SELF_SEQ_MAX, val);

	val = ((CNIC_PAGE_SIZE / माप(काष्ठा kcqe)) << 16) | KCQ_PAGE_CNT;
	cnic_ctx_wr(dev, kcq_cid_addr, L5_KRNLQ_PGTBL_NPAGES, val);

	val = (u32) ((u64) cp->kcq1.dma.pgtbl_map >> 32);
	cnic_ctx_wr(dev, kcq_cid_addr, L5_KRNLQ_PGTBL_HADDR_HI, val);

	val = (u32) cp->kcq1.dma.pgtbl_map;
	cnic_ctx_wr(dev, kcq_cid_addr, L5_KRNLQ_PGTBL_HADDR_LO, val);

	cp->पूर्णांक_num = 0;
	अगर (ethdev->drv_state & CNIC_DRV_STATE_USING_MSIX) अणु
		काष्ठा status_block_msix *msblk = cp->status_blk.bnx2;
		u32 sb_id = cp->status_blk_num;
		u32 sb = BNX2_L2CTX_L5_STATUSB_NUM(sb_id);

		cp->kcq1.hw_prod_idx_ptr =
			&msblk->status_completion_producer_index;
		cp->kcq1.status_idx_ptr = &msblk->status_idx;
		cp->kwq_con_idx_ptr = &msblk->status_cmd_consumer_index;
		cp->पूर्णांक_num = sb_id << BNX2_PCICFG_INT_ACK_CMD_INT_NUM_SHIFT;
		cnic_ctx_wr(dev, kwq_cid_addr, L5_KRNLQ_HOST_QIDX, sb);
		cnic_ctx_wr(dev, kcq_cid_addr, L5_KRNLQ_HOST_QIDX, sb);
	पूर्ण

	/* Enable Commnad Scheduler notअगरication when we ग_लिखो to the
	 * host producer index of the kernel contexts. */
	CNIC_WR(dev, BNX2_MQ_KNL_CMD_MASK1, 2);

	/* Enable Command Scheduler notअगरication when we ग_लिखो to either
	 * the Send Queue or Receive Queue producer indexes of the kernel
	 * bypass contexts. */
	CNIC_WR(dev, BNX2_MQ_KNL_BYP_CMD_MASK1, 7);
	CNIC_WR(dev, BNX2_MQ_KNL_BYP_WRITE_MASK1, 7);

	/* Notअगरy COM when the driver post an application buffer. */
	CNIC_WR(dev, BNX2_MQ_KNL_RX_V2P_MASK2, 0x2000);

	/* Set the CP and COM करोorbells.  These two processors polls the
	 * करोorbell क्रम a non zero value beक्रमe running.  This must be करोne
	 * after setting up the kernel queue contexts. */
	cnic_reg_wr_ind(dev, BNX2_CP_SCRATCH + 0x20, 1);
	cnic_reg_wr_ind(dev, BNX2_COM_SCRATCH + 0x20, 1);

	cnic_init_bnx2_tx_ring(dev);
	cnic_init_bnx2_rx_ring(dev);

	err = cnic_init_bnx2_irq(dev);
	अगर (err) अणु
		netdev_err(dev->netdev, "cnic_init_irq failed\n");
		cnic_reg_wr_ind(dev, BNX2_CP_SCRATCH + 0x20, 0);
		cnic_reg_wr_ind(dev, BNX2_COM_SCRATCH + 0x20, 0);
		वापस err;
	पूर्ण

	ethdev->drv_state |= CNIC_DRV_STATE_HANDLES_IRQ;

	वापस 0;
पूर्ण

अटल व्योम cnic_setup_bnx2x_context(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	u32 start_offset = ethdev->ctx_tbl_offset;
	पूर्णांक i;

	क्रम (i = 0; i < cp->ctx_blks; i++) अणु
		काष्ठा cnic_ctx *ctx = &cp->ctx_arr[i];
		dma_addr_t map = ctx->mapping;

		अगर (cp->ctx_align) अणु
			अचिन्हित दीर्घ mask = cp->ctx_align - 1;

			map = (map + mask) & ~mask;
		पूर्ण

		cnic_ctx_tbl_wr(dev, start_offset + i, map);
	पूर्ण
पूर्ण

अटल पूर्णांक cnic_init_bnx2x_irq(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	पूर्णांक err = 0;

	tasklet_setup(&cp->cnic_irq_task, cnic_service_bnx2x_bh);
	अगर (ethdev->drv_state & CNIC_DRV_STATE_USING_MSIX)
		err = cnic_request_irq(dev);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम cnic_storm_स_रखो_hc_disable(काष्ठा cnic_dev *dev,
						u16 sb_id, u8 sb_index,
						u8 disable)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);

	u32 addr = BAR_CSTRORM_INTMEM +
			CSTORM_STATUS_BLOCK_DATA_OFFSET(sb_id) +
			दुरत्व(काष्ठा hc_status_block_data_e1x, index_data) +
			माप(काष्ठा hc_index_data)*sb_index +
			दुरत्व(काष्ठा hc_index_data, flags);
	u16 flags = CNIC_RD16(dev, addr);
	/* clear and set */
	flags &= ~HC_INDEX_DATA_HC_ENABLED;
	flags |= (((~disable) << HC_INDEX_DATA_HC_ENABLED_SHIFT) &
		  HC_INDEX_DATA_HC_ENABLED);
	CNIC_WR16(dev, addr, flags);
पूर्ण

अटल व्योम cnic_enable_bnx2x_पूर्णांक(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	u8 sb_id = cp->status_blk_num;

	CNIC_WR8(dev, BAR_CSTRORM_INTMEM +
			CSTORM_STATUS_BLOCK_DATA_OFFSET(sb_id) +
			दुरत्व(काष्ठा hc_status_block_data_e1x, index_data) +
			माप(काष्ठा hc_index_data)*HC_INDEX_ISCSI_EQ_CONS +
			दुरत्व(काष्ठा hc_index_data, समयout), 64 / 4);
	cnic_storm_स_रखो_hc_disable(dev, sb_id, HC_INDEX_ISCSI_EQ_CONS, 0);
पूर्ण

अटल व्योम cnic_disable_bnx2x_पूर्णांक_sync(काष्ठा cnic_dev *dev)
अणु
पूर्ण

अटल व्योम cnic_init_bnx2x_tx_ring(काष्ठा cnic_dev *dev,
				    काष्ठा client_init_ramrod_data *data)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	काष्ठा cnic_uio_dev *udev = cp->udev;
	जोड़ eth_tx_bd_types *txbd = (जोड़ eth_tx_bd_types *) udev->l2_ring;
	dma_addr_t buf_map, ring_map = udev->l2_ring_map;
	काष्ठा host_sp_status_block *sb = cp->bnx2x_def_status_blk;
	पूर्णांक i;
	u32 cli = cp->ethdev->iscsi_l2_client_id;
	u32 val;

	स_रखो(txbd, 0, CNIC_PAGE_SIZE);

	buf_map = udev->l2_buf_map;
	क्रम (i = 0; i < BNX2_MAX_TX_DESC_CNT; i += 3, txbd += 3) अणु
		काष्ठा eth_tx_start_bd *start_bd = &txbd->start_bd;
		काष्ठा eth_tx_parse_bd_e1x *pbd_e1x =
			&((txbd + 1)->parse_bd_e1x);
		काष्ठा eth_tx_parse_bd_e2 *pbd_e2 = &((txbd + 1)->parse_bd_e2);
		काष्ठा eth_tx_bd *reg_bd = &((txbd + 2)->reg_bd);

		start_bd->addr_hi = cpu_to_le32((u64) buf_map >> 32);
		start_bd->addr_lo = cpu_to_le32(buf_map & 0xffffffff);
		reg_bd->addr_hi = start_bd->addr_hi;
		reg_bd->addr_lo = start_bd->addr_lo + 0x10;
		start_bd->nbytes = cpu_to_le16(0x10);
		start_bd->nbd = cpu_to_le16(3);
		start_bd->bd_flags.as_bitfield = ETH_TX_BD_FLAGS_START_BD;
		start_bd->general_data &= ~ETH_TX_START_BD_PARSE_NBDS;
		start_bd->general_data |= (1 << ETH_TX_START_BD_HDR_NBDS_SHIFT);

		अगर (BNX2X_CHIP_IS_E2_PLUS(bp))
			pbd_e2->parsing_data = (UNICAST_ADDRESS <<
				ETH_TX_PARSE_BD_E2_ETH_ADDR_TYPE_SHIFT);
		अन्यथा
			pbd_e1x->global_data = (UNICAST_ADDRESS <<
				ETH_TX_PARSE_BD_E1X_ETH_ADDR_TYPE_SHIFT);
	पूर्ण

	val = (u64) ring_map >> 32;
	txbd->next_bd.addr_hi = cpu_to_le32(val);

	data->tx.tx_bd_page_base.hi = cpu_to_le32(val);

	val = (u64) ring_map & 0xffffffff;
	txbd->next_bd.addr_lo = cpu_to_le32(val);

	data->tx.tx_bd_page_base.lo = cpu_to_le32(val);

	/* Other ramrod params */
	data->tx.tx_sb_index_number = HC_SP_INDEX_ETH_ISCSI_CQ_CONS;
	data->tx.tx_status_block_id = BNX2X_DEF_SB_ID;

	/* reset xstorm per client statistics */
	अगर (cli < MAX_STAT_COUNTER_ID) अणु
		data->general.statistics_zero_flg = 1;
		data->general.statistics_en_flg = 1;
		data->general.statistics_counter_id = cli;
	पूर्ण

	cp->tx_cons_ptr =
		&sb->sp_sb.index_values[HC_SP_INDEX_ETH_ISCSI_CQ_CONS];
पूर्ण

अटल व्योम cnic_init_bnx2x_rx_ring(काष्ठा cnic_dev *dev,
				    काष्ठा client_init_ramrod_data *data)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	काष्ठा cnic_uio_dev *udev = cp->udev;
	काष्ठा eth_rx_bd *rxbd = (काष्ठा eth_rx_bd *) (udev->l2_ring +
				CNIC_PAGE_SIZE);
	काष्ठा eth_rx_cqe_next_page *rxcqe = (काष्ठा eth_rx_cqe_next_page *)
				(udev->l2_ring + (2 * CNIC_PAGE_SIZE));
	काष्ठा host_sp_status_block *sb = cp->bnx2x_def_status_blk;
	पूर्णांक i;
	u32 cli = cp->ethdev->iscsi_l2_client_id;
	पूर्णांक cl_qzone_id = BNX2X_CL_QZONE_ID(bp, cli);
	u32 val;
	dma_addr_t ring_map = udev->l2_ring_map;

	/* General data */
	data->general.client_id = cli;
	data->general.activate_flg = 1;
	data->general.sp_client_id = cli;
	data->general.mtu = cpu_to_le16(cp->l2_single_buf_size - 14);
	data->general.func_id = bp->pfid;

	क्रम (i = 0; i < BNX2X_MAX_RX_DESC_CNT; i++, rxbd++) अणु
		dma_addr_t buf_map;
		पूर्णांक n = (i % cp->l2_rx_ring_size) + 1;

		buf_map = udev->l2_buf_map + (n * cp->l2_single_buf_size);
		rxbd->addr_hi = cpu_to_le32((u64) buf_map >> 32);
		rxbd->addr_lo = cpu_to_le32(buf_map & 0xffffffff);
	पूर्ण

	val = (u64) (ring_map + CNIC_PAGE_SIZE) >> 32;
	rxbd->addr_hi = cpu_to_le32(val);
	data->rx.bd_page_base.hi = cpu_to_le32(val);

	val = (u64) (ring_map + CNIC_PAGE_SIZE) & 0xffffffff;
	rxbd->addr_lo = cpu_to_le32(val);
	data->rx.bd_page_base.lo = cpu_to_le32(val);

	rxcqe += BNX2X_MAX_RCQ_DESC_CNT;
	val = (u64) (ring_map + (2 * CNIC_PAGE_SIZE)) >> 32;
	rxcqe->addr_hi = cpu_to_le32(val);
	data->rx.cqe_page_base.hi = cpu_to_le32(val);

	val = (u64) (ring_map + (2 * CNIC_PAGE_SIZE)) & 0xffffffff;
	rxcqe->addr_lo = cpu_to_le32(val);
	data->rx.cqe_page_base.lo = cpu_to_le32(val);

	/* Other ramrod params */
	data->rx.client_qzone_id = cl_qzone_id;
	data->rx.rx_sb_index_number = HC_SP_INDEX_ETH_ISCSI_RX_CQ_CONS;
	data->rx.status_block_id = BNX2X_DEF_SB_ID;

	data->rx.cache_line_alignment_log_size = L1_CACHE_SHIFT;

	data->rx.max_bytes_on_bd = cpu_to_le16(cp->l2_single_buf_size);
	data->rx.outer_vlan_removal_enable_flg = 1;
	data->rx.silent_vlan_removal_flg = 1;
	data->rx.silent_vlan_value = 0;
	data->rx.silent_vlan_mask = 0xffff;

	cp->rx_cons_ptr =
		&sb->sp_sb.index_values[HC_SP_INDEX_ETH_ISCSI_RX_CQ_CONS];
	cp->rx_cons = *cp->rx_cons_ptr;
पूर्ण

अटल व्योम cnic_init_bnx2x_kcq(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	u32 pfid = bp->pfid;

	cp->kcq1.io_addr = BAR_CSTRORM_INTMEM +
			   CSTORM_ISCSI_EQ_PROD_OFFSET(pfid, 0);
	cp->kcq1.sw_prod_idx = 0;

	अगर (BNX2X_CHIP_IS_E2_PLUS(bp)) अणु
		काष्ठा host_hc_status_block_e2 *sb = cp->status_blk.gen;

		cp->kcq1.hw_prod_idx_ptr =
			&sb->sb.index_values[HC_INDEX_ISCSI_EQ_CONS];
		cp->kcq1.status_idx_ptr =
			&sb->sb.running_index[SM_RX_ID];
	पूर्ण अन्यथा अणु
		काष्ठा host_hc_status_block_e1x *sb = cp->status_blk.gen;

		cp->kcq1.hw_prod_idx_ptr =
			&sb->sb.index_values[HC_INDEX_ISCSI_EQ_CONS];
		cp->kcq1.status_idx_ptr =
			&sb->sb.running_index[SM_RX_ID];
	पूर्ण

	अगर (BNX2X_CHIP_IS_E2_PLUS(bp)) अणु
		काष्ठा host_hc_status_block_e2 *sb = cp->status_blk.gen;

		cp->kcq2.io_addr = BAR_USTRORM_INTMEM +
					USTORM_FCOE_EQ_PROD_OFFSET(pfid);
		cp->kcq2.sw_prod_idx = 0;
		cp->kcq2.hw_prod_idx_ptr =
			&sb->sb.index_values[HC_INDEX_FCOE_EQ_CONS];
		cp->kcq2.status_idx_ptr =
			&sb->sb.running_index[SM_RX_ID];
	पूर्ण
पूर्ण

अटल पूर्णांक cnic_start_bnx2x_hw(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	पूर्णांक ret;
	u32 pfid;

	dev->stats_addr = ethdev->addr_drv_info_to_mcp;
	cp->func = bp->pf_num;

	pfid = bp->pfid;

	ret = cnic_init_id_tbl(&cp->cid_tbl, MAX_ISCSI_TBL_SZ,
			       cp->iscsi_start_cid, 0);

	अगर (ret)
		वापस -ENOMEM;

	अगर (BNX2X_CHIP_IS_E2_PLUS(bp)) अणु
		ret = cnic_init_id_tbl(&cp->fcoe_cid_tbl, dev->max_fcoe_conn,
					cp->fcoe_start_cid, 0);

		अगर (ret)
			वापस -ENOMEM;
	पूर्ण

	cp->bnx2x_igu_sb_id = ethdev->irq_arr[0].status_blk_num2;

	cnic_init_bnx2x_kcq(dev);

	/* Only 1 EQ */
	CNIC_WR16(dev, cp->kcq1.io_addr, MAX_KCQ_IDX);
	CNIC_WR(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_CONS_OFFSET(pfid, 0), 0);
	CNIC_WR(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_NEXT_PAGE_ADDR_OFFSET(pfid, 0),
		cp->kcq1.dma.pg_map_arr[1] & 0xffffffff);
	CNIC_WR(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_NEXT_PAGE_ADDR_OFFSET(pfid, 0) + 4,
		(u64) cp->kcq1.dma.pg_map_arr[1] >> 32);
	CNIC_WR(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_NEXT_EQE_ADDR_OFFSET(pfid, 0),
		cp->kcq1.dma.pg_map_arr[0] & 0xffffffff);
	CNIC_WR(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_NEXT_EQE_ADDR_OFFSET(pfid, 0) + 4,
		(u64) cp->kcq1.dma.pg_map_arr[0] >> 32);
	CNIC_WR8(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_NEXT_PAGE_ADDR_VALID_OFFSET(pfid, 0), 1);
	CNIC_WR16(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_SB_NUM_OFFSET(pfid, 0), cp->status_blk_num);
	CNIC_WR8(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_SB_INDEX_OFFSET(pfid, 0),
		HC_INDEX_ISCSI_EQ_CONS);

	CNIC_WR(dev, BAR_USTRORM_INTMEM +
		USTORM_ISCSI_GLOBAL_BUF_PHYS_ADDR_OFFSET(pfid),
		cp->gbl_buf_info.pg_map_arr[0] & 0xffffffff);
	CNIC_WR(dev, BAR_USTRORM_INTMEM +
		USTORM_ISCSI_GLOBAL_BUF_PHYS_ADDR_OFFSET(pfid) + 4,
		(u64) cp->gbl_buf_info.pg_map_arr[0] >> 32);

	CNIC_WR(dev, BAR_TSTRORM_INTMEM +
		TSTORM_ISCSI_TCP_LOCAL_ADV_WND_OFFSET(pfid), DEF_RCV_BUF);

	cnic_setup_bnx2x_context(dev);

	ret = cnic_init_bnx2x_irq(dev);
	अगर (ret)
		वापस ret;

	ethdev->drv_state |= CNIC_DRV_STATE_HANDLES_IRQ;
	वापस 0;
पूर्ण

अटल व्योम cnic_init_rings(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	काष्ठा cnic_uio_dev *udev = cp->udev;

	अगर (test_bit(CNIC_LCL_FL_RINGS_INITED, &cp->cnic_local_flags))
		वापस;

	अगर (test_bit(CNIC_F_BNX2_CLASS, &dev->flags)) अणु
		cnic_init_bnx2_tx_ring(dev);
		cnic_init_bnx2_rx_ring(dev);
		set_bit(CNIC_LCL_FL_RINGS_INITED, &cp->cnic_local_flags);
	पूर्ण अन्यथा अगर (test_bit(CNIC_F_BNX2X_CLASS, &dev->flags)) अणु
		u32 cli = cp->ethdev->iscsi_l2_client_id;
		u32 cid = cp->ethdev->iscsi_l2_cid;
		u32 cl_qzone_id;
		काष्ठा client_init_ramrod_data *data;
		जोड़ l5cm_specअगरic_data l5_data;
		काष्ठा ustorm_eth_rx_producers rx_prods = अणु0पूर्ण;
		u32 off, i, *cid_ptr;

		rx_prods.bd_prod = 0;
		rx_prods.cqe_prod = BNX2X_MAX_RCQ_DESC_CNT;
		barrier();

		cl_qzone_id = BNX2X_CL_QZONE_ID(bp, cli);

		off = BAR_USTRORM_INTMEM +
			(BNX2X_CHIP_IS_E2_PLUS(bp) ?
			 USTORM_RX_PRODS_E2_OFFSET(cl_qzone_id) :
			 USTORM_RX_PRODS_E1X_OFFSET(BP_PORT(bp), cli));

		क्रम (i = 0; i < माप(काष्ठा ustorm_eth_rx_producers) / 4; i++)
			CNIC_WR(dev, off + i * 4, ((u32 *) &rx_prods)[i]);

		set_bit(CNIC_LCL_FL_L2_WAIT, &cp->cnic_local_flags);

		data = udev->l2_buf;
		cid_ptr = udev->l2_buf + 12;

		स_रखो(data, 0, माप(*data));

		cnic_init_bnx2x_tx_ring(dev, data);
		cnic_init_bnx2x_rx_ring(dev, data);

		data->general.fp_hsi_ver =  ETH_FP_HSI_VERSION;

		l5_data.phy_address.lo = udev->l2_buf_map & 0xffffffff;
		l5_data.phy_address.hi = (u64) udev->l2_buf_map >> 32;

		set_bit(CNIC_LCL_FL_RINGS_INITED, &cp->cnic_local_flags);

		cnic_submit_kwqe_16(dev, RAMROD_CMD_ID_ETH_CLIENT_SETUP,
			cid, ETH_CONNECTION_TYPE, &l5_data);

		i = 0;
		जबतक (test_bit(CNIC_LCL_FL_L2_WAIT, &cp->cnic_local_flags) &&
		       ++i < 10)
			msleep(1);

		अगर (test_bit(CNIC_LCL_FL_L2_WAIT, &cp->cnic_local_flags))
			netdev_err(dev->netdev,
				"iSCSI CLIENT_SETUP did not complete\n");
		cnic_spq_completion(dev, DRV_CTL_RET_L2_SPQ_CREDIT_CMD, 1);
		cnic_ring_ctl(dev, cid, cli, 1);
		*cid_ptr = cid >> 4;
		*(cid_ptr + 1) = cid * bp->db_size;
		*(cid_ptr + 2) = UIO_USE_TX_DOORBELL;
	पूर्ण
पूर्ण

अटल व्योम cnic_shutकरोwn_rings(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_uio_dev *udev = cp->udev;
	व्योम *rx_ring;

	अगर (!test_bit(CNIC_LCL_FL_RINGS_INITED, &cp->cnic_local_flags))
		वापस;

	अगर (test_bit(CNIC_F_BNX2_CLASS, &dev->flags)) अणु
		cnic_shutकरोwn_bnx2_rx_ring(dev);
	पूर्ण अन्यथा अगर (test_bit(CNIC_F_BNX2X_CLASS, &dev->flags)) अणु
		u32 cli = cp->ethdev->iscsi_l2_client_id;
		u32 cid = cp->ethdev->iscsi_l2_cid;
		जोड़ l5cm_specअगरic_data l5_data;
		पूर्णांक i;

		cnic_ring_ctl(dev, cid, cli, 0);

		set_bit(CNIC_LCL_FL_L2_WAIT, &cp->cnic_local_flags);

		l5_data.phy_address.lo = cli;
		l5_data.phy_address.hi = 0;
		cnic_submit_kwqe_16(dev, RAMROD_CMD_ID_ETH_HALT,
			cid, ETH_CONNECTION_TYPE, &l5_data);
		i = 0;
		जबतक (test_bit(CNIC_LCL_FL_L2_WAIT, &cp->cnic_local_flags) &&
		       ++i < 10)
			msleep(1);

		अगर (test_bit(CNIC_LCL_FL_L2_WAIT, &cp->cnic_local_flags))
			netdev_err(dev->netdev,
				"iSCSI CLIENT_HALT did not complete\n");
		cnic_spq_completion(dev, DRV_CTL_RET_L2_SPQ_CREDIT_CMD, 1);

		स_रखो(&l5_data, 0, माप(l5_data));
		cnic_submit_kwqe_16(dev, RAMROD_CMD_ID_COMMON_CFC_DEL,
			cid, NONE_CONNECTION_TYPE, &l5_data);
		msleep(10);
	पूर्ण
	clear_bit(CNIC_LCL_FL_RINGS_INITED, &cp->cnic_local_flags);
	rx_ring = udev->l2_ring + CNIC_PAGE_SIZE;
	स_रखो(rx_ring, 0, CNIC_PAGE_SIZE);
पूर्ण

अटल पूर्णांक cnic_रेजिस्टर_netdev(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	पूर्णांक err;

	अगर (!ethdev)
		वापस -ENODEV;

	अगर (ethdev->drv_state & CNIC_DRV_STATE_REGD)
		वापस 0;

	err = ethdev->drv_रेजिस्टर_cnic(dev->netdev, cp->cnic_ops, dev);
	अगर (err)
		netdev_err(dev->netdev, "register_cnic failed\n");

	/* Read iSCSI config again.  On some bnx2x device, iSCSI config
	 * can change after firmware is करोwnloaded.
	 */
	dev->max_iscsi_conn = ethdev->max_iscsi_conn;
	अगर (ethdev->drv_state & CNIC_DRV_STATE_NO_ISCSI)
		dev->max_iscsi_conn = 0;

	वापस err;
पूर्ण

अटल व्योम cnic_unरेजिस्टर_netdev(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;

	अगर (!ethdev)
		वापस;

	ethdev->drv_unरेजिस्टर_cnic(dev->netdev);
पूर्ण

अटल पूर्णांक cnic_start_hw(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा cnic_eth_dev *ethdev = cp->ethdev;
	पूर्णांक err;

	अगर (test_bit(CNIC_F_CNIC_UP, &dev->flags))
		वापस -EALREADY;

	dev->regview = ethdev->io_base;
	pci_dev_get(dev->pcidev);
	cp->func = PCI_FUNC(dev->pcidev->devfn);
	cp->status_blk.gen = ethdev->irq_arr[0].status_blk;
	cp->status_blk_num = ethdev->irq_arr[0].status_blk_num;

	err = cp->alloc_resc(dev);
	अगर (err) अणु
		netdev_err(dev->netdev, "allocate resource failure\n");
		जाओ err1;
	पूर्ण

	err = cp->start_hw(dev);
	अगर (err)
		जाओ err1;

	err = cnic_cm_खोलो(dev);
	अगर (err)
		जाओ err1;

	set_bit(CNIC_F_CNIC_UP, &dev->flags);

	cp->enable_पूर्णांक(dev);

	वापस 0;

err1:
	अगर (ethdev->drv_state & CNIC_DRV_STATE_HANDLES_IRQ)
		cp->stop_hw(dev);
	अन्यथा
		cp->मुक्त_resc(dev);
	pci_dev_put(dev->pcidev);
	वापस err;
पूर्ण

अटल व्योम cnic_stop_bnx2_hw(काष्ठा cnic_dev *dev)
अणु
	cnic_disable_bnx2_पूर्णांक_sync(dev);

	cnic_reg_wr_ind(dev, BNX2_CP_SCRATCH + 0x20, 0);
	cnic_reg_wr_ind(dev, BNX2_COM_SCRATCH + 0x20, 0);

	cnic_init_context(dev, KWQ_CID);
	cnic_init_context(dev, KCQ_CID);

	cnic_setup_5709_context(dev, 0);
	cnic_मुक्त_irq(dev);

	cnic_मुक्त_resc(dev);
पूर्ण


अटल व्योम cnic_stop_bnx2x_hw(काष्ठा cnic_dev *dev)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	u32 hc_index = HC_INDEX_ISCSI_EQ_CONS;
	u32 sb_id = cp->status_blk_num;
	u32 idx_off, syn_off;

	cnic_मुक्त_irq(dev);

	अगर (BNX2X_CHIP_IS_E2_PLUS(bp)) अणु
		idx_off = दुरत्व(काष्ठा hc_status_block_e2, index_values) +
			  (hc_index * माप(u16));

		syn_off = CSTORM_HC_SYNC_LINE_INDEX_E2_OFFSET(hc_index, sb_id);
	पूर्ण अन्यथा अणु
		idx_off = दुरत्व(काष्ठा hc_status_block_e1x, index_values) +
			  (hc_index * माप(u16));

		syn_off = CSTORM_HC_SYNC_LINE_INDEX_E1X_OFFSET(hc_index, sb_id);
	पूर्ण
	CNIC_WR16(dev, BAR_CSTRORM_INTMEM + syn_off, 0);
	CNIC_WR16(dev, BAR_CSTRORM_INTMEM + CSTORM_STATUS_BLOCK_OFFSET(sb_id) +
		  idx_off, 0);

	*cp->kcq1.hw_prod_idx_ptr = 0;
	CNIC_WR(dev, BAR_CSTRORM_INTMEM +
		CSTORM_ISCSI_EQ_CONS_OFFSET(bp->pfid, 0), 0);
	CNIC_WR16(dev, cp->kcq1.io_addr, 0);
	cnic_मुक्त_resc(dev);
पूर्ण

अटल व्योम cnic_stop_hw(काष्ठा cnic_dev *dev)
अणु
	अगर (test_bit(CNIC_F_CNIC_UP, &dev->flags)) अणु
		काष्ठा cnic_local *cp = dev->cnic_priv;
		पूर्णांक i = 0;

		/* Need to रुको क्रम the ring shutकरोwn event to complete
		 * beक्रमe clearing the CNIC_UP flag.
		 */
		जबतक (cp->udev && cp->udev->uio_dev != -1 && i < 15) अणु
			msleep(100);
			i++;
		पूर्ण
		cnic_shutकरोwn_rings(dev);
		cp->stop_cm(dev);
		cp->ethdev->drv_state &= ~CNIC_DRV_STATE_HANDLES_IRQ;
		clear_bit(CNIC_F_CNIC_UP, &dev->flags);
		RCU_INIT_POINTER(cp->ulp_ops[CNIC_ULP_L4], शून्य);
		synchronize_rcu();
		cnic_cm_shutकरोwn(dev);
		cp->stop_hw(dev);
		pci_dev_put(dev->pcidev);
	पूर्ण
पूर्ण

अटल व्योम cnic_मुक्त_dev(काष्ठा cnic_dev *dev)
अणु
	पूर्णांक i = 0;

	जबतक ((atomic_पढ़ो(&dev->ref_count) != 0) && i < 10) अणु
		msleep(100);
		i++;
	पूर्ण
	अगर (atomic_पढ़ो(&dev->ref_count) != 0)
		netdev_err(dev->netdev, "Failed waiting for ref count to go to zero\n");

	netdev_info(dev->netdev, "Removed CNIC device\n");
	dev_put(dev->netdev);
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक cnic_get_fc_npiv_tbl(काष्ठा cnic_dev *dev,
				काष्ठा cnic_fc_npiv_tbl *npiv_tbl)
अणु
	काष्ठा cnic_local *cp = dev->cnic_priv;
	काष्ठा bnx2x *bp = netdev_priv(dev->netdev);
	पूर्णांक ret;

	अगर (!test_bit(CNIC_F_CNIC_UP, &dev->flags))
		वापस -EAGAIN;     /* bnx2x is करोwn */

	अगर (!BNX2X_CHIP_IS_E2_PLUS(bp))
		वापस -EINVAL;

	ret = cp->ethdev->drv_get_fc_npiv_tbl(dev->netdev, npiv_tbl);
	वापस ret;
पूर्ण

अटल काष्ठा cnic_dev *cnic_alloc_dev(काष्ठा net_device *dev,
				       काष्ठा pci_dev *pdev)
अणु
	काष्ठा cnic_dev *cdev;
	काष्ठा cnic_local *cp;
	पूर्णांक alloc_size;

	alloc_size = माप(काष्ठा cnic_dev) + माप(काष्ठा cnic_local);

	cdev = kzalloc(alloc_size, GFP_KERNEL);
	अगर (cdev == शून्य)
		वापस शून्य;

	cdev->netdev = dev;
	cdev->cnic_priv = (अक्षर *)cdev + माप(काष्ठा cnic_dev);
	cdev->रेजिस्टर_device = cnic_रेजिस्टर_device;
	cdev->unरेजिस्टर_device = cnic_unरेजिस्टर_device;
	cdev->iscsi_nl_msg_recv = cnic_iscsi_nl_msg_recv;
	cdev->get_fc_npiv_tbl = cnic_get_fc_npiv_tbl;
	atomic_set(&cdev->ref_count, 0);

	cp = cdev->cnic_priv;
	cp->dev = cdev;
	cp->l2_single_buf_size = 0x400;
	cp->l2_rx_ring_size = 3;

	spin_lock_init(&cp->cnic_ulp_lock);

	netdev_info(dev, "Added CNIC device\n");

	वापस cdev;
पूर्ण

अटल काष्ठा cnic_dev *init_bnx2_cnic(काष्ठा net_device *dev)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा cnic_dev *cdev;
	काष्ठा cnic_local *cp;
	काष्ठा bnx2 *bp = netdev_priv(dev);
	काष्ठा cnic_eth_dev *ethdev = शून्य;

	अगर (bp->cnic_probe)
		ethdev = (bp->cnic_probe)(dev);

	अगर (!ethdev)
		वापस शून्य;

	pdev = ethdev->pdev;
	अगर (!pdev)
		वापस शून्य;

	dev_hold(dev);
	pci_dev_get(pdev);
	अगर ((pdev->device == PCI_DEVICE_ID_NX2_5709 ||
	     pdev->device == PCI_DEVICE_ID_NX2_5709S) &&
	    (pdev->revision < 0x10)) अणु
		pci_dev_put(pdev);
		जाओ cnic_err;
	पूर्ण
	pci_dev_put(pdev);

	cdev = cnic_alloc_dev(dev, pdev);
	अगर (cdev == शून्य)
		जाओ cnic_err;

	set_bit(CNIC_F_BNX2_CLASS, &cdev->flags);
	cdev->submit_kwqes = cnic_submit_bnx2_kwqes;

	cp = cdev->cnic_priv;
	cp->ethdev = ethdev;
	cdev->pcidev = pdev;
	cp->chip_id = ethdev->chip_id;

	cdev->max_iscsi_conn = ethdev->max_iscsi_conn;

	cp->cnic_ops = &cnic_bnx2_ops;
	cp->start_hw = cnic_start_bnx2_hw;
	cp->stop_hw = cnic_stop_bnx2_hw;
	cp->setup_pgtbl = cnic_setup_page_tbl;
	cp->alloc_resc = cnic_alloc_bnx2_resc;
	cp->मुक्त_resc = cnic_मुक्त_resc;
	cp->start_cm = cnic_cm_init_bnx2_hw;
	cp->stop_cm = cnic_cm_stop_bnx2_hw;
	cp->enable_पूर्णांक = cnic_enable_bnx2_पूर्णांक;
	cp->disable_पूर्णांक_sync = cnic_disable_bnx2_पूर्णांक_sync;
	cp->बंद_conn = cnic_बंद_bnx2_conn;
	वापस cdev;

cnic_err:
	dev_put(dev);
	वापस शून्य;
पूर्ण

अटल काष्ठा cnic_dev *init_bnx2x_cnic(काष्ठा net_device *dev)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा cnic_dev *cdev;
	काष्ठा cnic_local *cp;
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा cnic_eth_dev *ethdev = शून्य;

	अगर (bp->cnic_probe)
		ethdev = bp->cnic_probe(dev);

	अगर (!ethdev)
		वापस शून्य;

	pdev = ethdev->pdev;
	अगर (!pdev)
		वापस शून्य;

	dev_hold(dev);
	cdev = cnic_alloc_dev(dev, pdev);
	अगर (cdev == शून्य) अणु
		dev_put(dev);
		वापस शून्य;
	पूर्ण

	set_bit(CNIC_F_BNX2X_CLASS, &cdev->flags);
	cdev->submit_kwqes = cnic_submit_bnx2x_kwqes;

	cp = cdev->cnic_priv;
	cp->ethdev = ethdev;
	cdev->pcidev = pdev;
	cp->chip_id = ethdev->chip_id;

	cdev->stats_addr = ethdev->addr_drv_info_to_mcp;

	अगर (!(ethdev->drv_state & CNIC_DRV_STATE_NO_ISCSI))
		cdev->max_iscsi_conn = ethdev->max_iscsi_conn;
	अगर (CNIC_SUPPORTS_FCOE(bp)) अणु
		cdev->max_fcoe_conn = ethdev->max_fcoe_conn;
		cdev->max_fcoe_exchanges = ethdev->max_fcoe_exchanges;
	पूर्ण

	अगर (cdev->max_fcoe_conn > BNX2X_FCOE_NUM_CONNECTIONS)
		cdev->max_fcoe_conn = BNX2X_FCOE_NUM_CONNECTIONS;

	स_नकल(cdev->mac_addr, ethdev->iscsi_mac, ETH_ALEN);

	cp->cnic_ops = &cnic_bnx2x_ops;
	cp->start_hw = cnic_start_bnx2x_hw;
	cp->stop_hw = cnic_stop_bnx2x_hw;
	cp->setup_pgtbl = cnic_setup_page_tbl_le;
	cp->alloc_resc = cnic_alloc_bnx2x_resc;
	cp->मुक्त_resc = cnic_मुक्त_resc;
	cp->start_cm = cnic_cm_init_bnx2x_hw;
	cp->stop_cm = cnic_cm_stop_bnx2x_hw;
	cp->enable_पूर्णांक = cnic_enable_bnx2x_पूर्णांक;
	cp->disable_पूर्णांक_sync = cnic_disable_bnx2x_पूर्णांक_sync;
	अगर (BNX2X_CHIP_IS_E2_PLUS(bp)) अणु
		cp->ack_पूर्णांक = cnic_ack_bnx2x_e2_msix;
		cp->arm_पूर्णांक = cnic_arm_bnx2x_e2_msix;
	पूर्ण अन्यथा अणु
		cp->ack_पूर्णांक = cnic_ack_bnx2x_msix;
		cp->arm_पूर्णांक = cnic_arm_bnx2x_msix;
	पूर्ण
	cp->बंद_conn = cnic_बंद_bnx2x_conn;
	वापस cdev;
पूर्ण

अटल काष्ठा cnic_dev *is_cnic_dev(काष्ठा net_device *dev)
अणु
	काष्ठा ethtool_drvinfo drvinfo;
	काष्ठा cnic_dev *cdev = शून्य;

	अगर (dev->ethtool_ops && dev->ethtool_ops->get_drvinfo) अणु
		स_रखो(&drvinfo, 0, माप(drvinfo));
		dev->ethtool_ops->get_drvinfo(dev, &drvinfo);

		अगर (!म_भेद(drvinfo.driver, "bnx2"))
			cdev = init_bnx2_cnic(dev);
		अगर (!म_भेद(drvinfo.driver, "bnx2x"))
			cdev = init_bnx2x_cnic(dev);
		अगर (cdev) अणु
			ग_लिखो_lock(&cnic_dev_lock);
			list_add(&cdev->list, &cnic_dev_list);
			ग_लिखो_unlock(&cnic_dev_lock);
		पूर्ण
	पूर्ण
	वापस cdev;
पूर्ण

अटल व्योम cnic_rcv_netevent(काष्ठा cnic_local *cp, अचिन्हित दीर्घ event,
			      u16 vlan_id)
अणु
	पूर्णांक अगर_type;

	क्रम (अगर_type = 0; अगर_type < MAX_CNIC_ULP_TYPE; अगर_type++) अणु
		काष्ठा cnic_ulp_ops *ulp_ops;
		व्योम *ctx;

		mutex_lock(&cnic_lock);
		ulp_ops = rcu_dereference_रक्षित(cp->ulp_ops[अगर_type],
						lockdep_is_held(&cnic_lock));
		अगर (!ulp_ops || !ulp_ops->indicate_netevent) अणु
			mutex_unlock(&cnic_lock);
			जारी;
		पूर्ण

		ctx = cp->ulp_handle[अगर_type];

		set_bit(ULP_F_CALL_PENDING, &cp->ulp_flags[अगर_type]);
		mutex_unlock(&cnic_lock);

		ulp_ops->indicate_netevent(ctx, event, vlan_id);

		clear_bit(ULP_F_CALL_PENDING, &cp->ulp_flags[अगर_type]);
	पूर्ण
पूर्ण

/* netdev event handler */
अटल पूर्णांक cnic_netdev_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
							 व्योम *ptr)
अणु
	काष्ठा net_device *netdev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा cnic_dev *dev;
	पूर्णांक new_dev = 0;

	dev = cnic_from_netdev(netdev);

	अगर (!dev && event == NETDEV_REGISTER) अणु
		/* Check क्रम the hot-plug device */
		dev = is_cnic_dev(netdev);
		अगर (dev) अणु
			new_dev = 1;
			cnic_hold(dev);
		पूर्ण
	पूर्ण
	अगर (dev) अणु
		काष्ठा cnic_local *cp = dev->cnic_priv;

		अगर (new_dev)
			cnic_ulp_init(dev);
		अन्यथा अगर (event == NETDEV_UNREGISTER)
			cnic_ulp_निकास(dev);

		अगर (event == NETDEV_UP) अणु
			अगर (cnic_रेजिस्टर_netdev(dev) != 0) अणु
				cnic_put(dev);
				जाओ करोne;
			पूर्ण
			अगर (!cnic_start_hw(dev))
				cnic_ulp_start(dev);
		पूर्ण

		cnic_rcv_netevent(cp, event, 0);

		अगर (event == NETDEV_GOING_DOWN) अणु
			cnic_ulp_stop(dev);
			cnic_stop_hw(dev);
			cnic_unरेजिस्टर_netdev(dev);
		पूर्ण अन्यथा अगर (event == NETDEV_UNREGISTER) अणु
			ग_लिखो_lock(&cnic_dev_lock);
			list_del_init(&dev->list);
			ग_लिखो_unlock(&cnic_dev_lock);

			cnic_put(dev);
			cnic_मुक्त_dev(dev);
			जाओ करोne;
		पूर्ण
		cnic_put(dev);
	पूर्ण अन्यथा अणु
		काष्ठा net_device *realdev;
		u16 vid;

		vid = cnic_get_vlan(netdev, &realdev);
		अगर (realdev) अणु
			dev = cnic_from_netdev(realdev);
			अगर (dev) अणु
				vid |= VLAN_CFI_MASK;	/* make non-zero */
				cnic_rcv_netevent(dev->cnic_priv, event, vid);
				cnic_put(dev);
			पूर्ण
		पूर्ण
	पूर्ण
करोne:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block cnic_netdev_notअगरier = अणु
	.notअगरier_call = cnic_netdev_event
पूर्ण;

अटल व्योम cnic_release(व्योम)
अणु
	काष्ठा cnic_uio_dev *udev;

	जबतक (!list_empty(&cnic_udev_list)) अणु
		udev = list_entry(cnic_udev_list.next, काष्ठा cnic_uio_dev,
				  list);
		cnic_मुक्त_uio(udev);
	पूर्ण
पूर्ण

अटल पूर्णांक __init cnic_init(व्योम)
अणु
	पूर्णांक rc = 0;

	pr_info("%s", version);

	rc = रेजिस्टर_netdevice_notअगरier(&cnic_netdev_notअगरier);
	अगर (rc) अणु
		cnic_release();
		वापस rc;
	पूर्ण

	cnic_wq = create_singlethपढ़ो_workqueue("cnic_wq");
	अगर (!cnic_wq) अणु
		cnic_release();
		unरेजिस्टर_netdevice_notअगरier(&cnic_netdev_notअगरier);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास cnic_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&cnic_netdev_notअगरier);
	cnic_release();
	destroy_workqueue(cnic_wq);
पूर्ण

module_init(cnic_init);
module_निकास(cnic_निकास);
