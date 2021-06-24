<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश <rdma/rdma_netlink.h>
#समावेश <net/addrconf.h>
#समावेश "rxe.h"
#समावेश "rxe_loc.h"

MODULE_AUTHOR("Bob Pearson, Frank Zago, John Groves, Kamal Heib");
MODULE_DESCRIPTION("Soft RDMA transport");
MODULE_LICENSE("Dual BSD/GPL");

bool rxe_initialized;

/* मुक्त resources क्रम a rxe device all objects created क्रम this device must
 * have been destroyed
 */
व्योम rxe_dealloc(काष्ठा ib_device *ib_dev)
अणु
	काष्ठा rxe_dev *rxe = container_of(ib_dev, काष्ठा rxe_dev, ib_dev);

	rxe_pool_cleanup(&rxe->uc_pool);
	rxe_pool_cleanup(&rxe->pd_pool);
	rxe_pool_cleanup(&rxe->ah_pool);
	rxe_pool_cleanup(&rxe->srq_pool);
	rxe_pool_cleanup(&rxe->qp_pool);
	rxe_pool_cleanup(&rxe->cq_pool);
	rxe_pool_cleanup(&rxe->mr_pool);
	rxe_pool_cleanup(&rxe->mw_pool);
	rxe_pool_cleanup(&rxe->mc_grp_pool);
	rxe_pool_cleanup(&rxe->mc_elem_pool);

	अगर (rxe->tfm)
		crypto_मुक्त_shash(rxe->tfm);
पूर्ण

/* initialize rxe device parameters */
अटल व्योम rxe_init_device_param(काष्ठा rxe_dev *rxe)
अणु
	rxe->max_अंतरभूत_data			= RXE_MAX_INLINE_DATA;

	rxe->attr.venकरोr_id			= RXE_VENDOR_ID;
	rxe->attr.max_mr_size			= RXE_MAX_MR_SIZE;
	rxe->attr.page_size_cap			= RXE_PAGE_SIZE_CAP;
	rxe->attr.max_qp			= RXE_MAX_QP;
	rxe->attr.max_qp_wr			= RXE_MAX_QP_WR;
	rxe->attr.device_cap_flags		= RXE_DEVICE_CAP_FLAGS;
	rxe->attr.max_send_sge			= RXE_MAX_SGE;
	rxe->attr.max_recv_sge			= RXE_MAX_SGE;
	rxe->attr.max_sge_rd			= RXE_MAX_SGE_RD;
	rxe->attr.max_cq			= RXE_MAX_CQ;
	rxe->attr.max_cqe			= (1 << RXE_MAX_LOG_CQE) - 1;
	rxe->attr.max_mr			= RXE_MAX_MR;
	rxe->attr.max_pd			= RXE_MAX_PD;
	rxe->attr.max_qp_rd_atom		= RXE_MAX_QP_RD_ATOM;
	rxe->attr.max_res_rd_atom		= RXE_MAX_RES_RD_ATOM;
	rxe->attr.max_qp_init_rd_atom		= RXE_MAX_QP_INIT_RD_ATOM;
	rxe->attr.atomic_cap			= IB_ATOMIC_HCA;
	rxe->attr.max_mcast_grp			= RXE_MAX_MCAST_GRP;
	rxe->attr.max_mcast_qp_attach		= RXE_MAX_MCAST_QP_ATTACH;
	rxe->attr.max_total_mcast_qp_attach	= RXE_MAX_TOT_MCAST_QP_ATTACH;
	rxe->attr.max_ah			= RXE_MAX_AH;
	rxe->attr.max_srq			= RXE_MAX_SRQ;
	rxe->attr.max_srq_wr			= RXE_MAX_SRQ_WR;
	rxe->attr.max_srq_sge			= RXE_MAX_SRQ_SGE;
	rxe->attr.max_fast_reg_page_list_len	= RXE_MAX_FMR_PAGE_LIST_LEN;
	rxe->attr.max_pkeys			= RXE_MAX_PKEYS;
	rxe->attr.local_ca_ack_delay		= RXE_LOCAL_CA_ACK_DELAY;
	addrconf_addr_eui48((अचिन्हित अक्षर *)&rxe->attr.sys_image_guid,
			rxe->ndev->dev_addr);

	rxe->max_ucontext			= RXE_MAX_UCONTEXT;
पूर्ण

/* initialize port attributes */
अटल व्योम rxe_init_port_param(काष्ठा rxe_port *port)
अणु
	port->attr.state		= IB_PORT_DOWN;
	port->attr.max_mtu		= IB_MTU_4096;
	port->attr.active_mtu		= IB_MTU_256;
	port->attr.gid_tbl_len		= RXE_PORT_GID_TBL_LEN;
	port->attr.port_cap_flags	= RXE_PORT_PORT_CAP_FLAGS;
	port->attr.max_msg_sz		= RXE_PORT_MAX_MSG_SZ;
	port->attr.bad_pkey_cntr	= RXE_PORT_BAD_PKEY_CNTR;
	port->attr.qkey_viol_cntr	= RXE_PORT_QKEY_VIOL_CNTR;
	port->attr.pkey_tbl_len		= RXE_PORT_PKEY_TBL_LEN;
	port->attr.lid			= RXE_PORT_LID;
	port->attr.sm_lid		= RXE_PORT_SM_LID;
	port->attr.lmc			= RXE_PORT_LMC;
	port->attr.max_vl_num		= RXE_PORT_MAX_VL_NUM;
	port->attr.sm_sl		= RXE_PORT_SM_SL;
	port->attr.subnet_समयout	= RXE_PORT_SUBNET_TIMEOUT;
	port->attr.init_type_reply	= RXE_PORT_INIT_TYPE_REPLY;
	port->attr.active_width		= RXE_PORT_ACTIVE_WIDTH;
	port->attr.active_speed		= RXE_PORT_ACTIVE_SPEED;
	port->attr.phys_state		= RXE_PORT_PHYS_STATE;
	port->mtu_cap			= ib_mtu_क्रमागत_to_पूर्णांक(IB_MTU_256);
	port->subnet_prefix		= cpu_to_be64(RXE_PORT_SUBNET_PREFIX);
पूर्ण

/* initialize port state, note IB convention that HCA ports are always
 * numbered from 1
 */
अटल व्योम rxe_init_ports(काष्ठा rxe_dev *rxe)
अणु
	काष्ठा rxe_port *port = &rxe->port;

	rxe_init_port_param(port);
	addrconf_addr_eui48((अचिन्हित अक्षर *)&port->port_guid,
			    rxe->ndev->dev_addr);
	spin_lock_init(&port->port_lock);
पूर्ण

/* init pools of managed objects */
अटल पूर्णांक rxe_init_pools(काष्ठा rxe_dev *rxe)
अणु
	पूर्णांक err;

	err = rxe_pool_init(rxe, &rxe->uc_pool, RXE_TYPE_UC,
			    rxe->max_ucontext);
	अगर (err)
		जाओ err1;

	err = rxe_pool_init(rxe, &rxe->pd_pool, RXE_TYPE_PD,
			    rxe->attr.max_pd);
	अगर (err)
		जाओ err2;

	err = rxe_pool_init(rxe, &rxe->ah_pool, RXE_TYPE_AH,
			    rxe->attr.max_ah);
	अगर (err)
		जाओ err3;

	err = rxe_pool_init(rxe, &rxe->srq_pool, RXE_TYPE_SRQ,
			    rxe->attr.max_srq);
	अगर (err)
		जाओ err4;

	err = rxe_pool_init(rxe, &rxe->qp_pool, RXE_TYPE_QP,
			    rxe->attr.max_qp);
	अगर (err)
		जाओ err5;

	err = rxe_pool_init(rxe, &rxe->cq_pool, RXE_TYPE_CQ,
			    rxe->attr.max_cq);
	अगर (err)
		जाओ err6;

	err = rxe_pool_init(rxe, &rxe->mr_pool, RXE_TYPE_MR,
			    rxe->attr.max_mr);
	अगर (err)
		जाओ err7;

	err = rxe_pool_init(rxe, &rxe->mw_pool, RXE_TYPE_MW,
			    rxe->attr.max_mw);
	अगर (err)
		जाओ err8;

	err = rxe_pool_init(rxe, &rxe->mc_grp_pool, RXE_TYPE_MC_GRP,
			    rxe->attr.max_mcast_grp);
	अगर (err)
		जाओ err9;

	err = rxe_pool_init(rxe, &rxe->mc_elem_pool, RXE_TYPE_MC_ELEM,
			    rxe->attr.max_total_mcast_qp_attach);
	अगर (err)
		जाओ err10;

	वापस 0;

err10:
	rxe_pool_cleanup(&rxe->mc_grp_pool);
err9:
	rxe_pool_cleanup(&rxe->mw_pool);
err8:
	rxe_pool_cleanup(&rxe->mr_pool);
err7:
	rxe_pool_cleanup(&rxe->cq_pool);
err6:
	rxe_pool_cleanup(&rxe->qp_pool);
err5:
	rxe_pool_cleanup(&rxe->srq_pool);
err4:
	rxe_pool_cleanup(&rxe->ah_pool);
err3:
	rxe_pool_cleanup(&rxe->pd_pool);
err2:
	rxe_pool_cleanup(&rxe->uc_pool);
err1:
	वापस err;
पूर्ण

/* initialize rxe device state */
अटल पूर्णांक rxe_init(काष्ठा rxe_dev *rxe)
अणु
	पूर्णांक err;

	/* init शेष device parameters */
	rxe_init_device_param(rxe);

	rxe_init_ports(rxe);

	err = rxe_init_pools(rxe);
	अगर (err)
		वापस err;

	/* init pending mmap list */
	spin_lock_init(&rxe->mmap_offset_lock);
	spin_lock_init(&rxe->pending_lock);
	INIT_LIST_HEAD(&rxe->pending_mmaps);

	mutex_init(&rxe->usdev_lock);

	वापस 0;
पूर्ण

व्योम rxe_set_mtu(काष्ठा rxe_dev *rxe, अचिन्हित पूर्णांक ndev_mtu)
अणु
	काष्ठा rxe_port *port = &rxe->port;
	क्रमागत ib_mtu mtu;

	mtu = eth_mtu_पूर्णांक_to_क्रमागत(ndev_mtu);

	/* Make sure that new MTU in range */
	mtu = mtu ? min_t(क्रमागत ib_mtu, mtu, IB_MTU_4096) : IB_MTU_256;

	port->attr.active_mtu = mtu;
	port->mtu_cap = ib_mtu_क्रमागत_to_पूर्णांक(mtu);
पूर्ण

/* called by अगरc layer to create new rxe device.
 * The caller should allocate memory क्रम rxe by calling ib_alloc_device.
 */
पूर्णांक rxe_add(काष्ठा rxe_dev *rxe, अचिन्हित पूर्णांक mtu, स्थिर अक्षर *ibdev_name)
अणु
	पूर्णांक err;

	err = rxe_init(rxe);
	अगर (err)
		वापस err;

	rxe_set_mtu(rxe, mtu);

	वापस rxe_रेजिस्टर_device(rxe, ibdev_name);
पूर्ण

अटल पूर्णांक rxe_newlink(स्थिर अक्षर *ibdev_name, काष्ठा net_device *ndev)
अणु
	काष्ठा rxe_dev *exists;
	पूर्णांक err = 0;

	अगर (is_vlan_dev(ndev)) अणु
		pr_err("rxe creation allowed on top of a real device only\n");
		err = -EPERM;
		जाओ err;
	पूर्ण

	exists = rxe_get_dev_from_net(ndev);
	अगर (exists) अणु
		ib_device_put(&exists->ib_dev);
		pr_err("already configured on %s\n", ndev->name);
		err = -EEXIST;
		जाओ err;
	पूर्ण

	err = rxe_net_add(ibdev_name, ndev);
	अगर (err) अणु
		pr_err("failed to add %s\n", ndev->name);
		जाओ err;
	पूर्ण
err:
	वापस err;
पूर्ण

अटल काष्ठा rdma_link_ops rxe_link_ops = अणु
	.type = "rxe",
	.newlink = rxe_newlink,
पूर्ण;

अटल पूर्णांक __init rxe_module_init(व्योम)
अणु
	पूर्णांक err;

	err = rxe_net_init();
	अगर (err)
		वापस err;

	rdma_link_रेजिस्टर(&rxe_link_ops);
	rxe_initialized = true;
	pr_info("loaded\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास rxe_module_निकास(व्योम)
अणु
	rdma_link_unरेजिस्टर(&rxe_link_ops);
	ib_unरेजिस्टर_driver(RDMA_DRIVER_RXE);
	rxe_net_निकास();

	rxe_initialized = false;
	pr_info("unloaded\n");
पूर्ण

late_initcall(rxe_module_init);
module_निकास(rxe_module_निकास);

MODULE_ALIAS_RDMA_LINK("rxe");
