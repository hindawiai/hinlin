<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2007 - 2009 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/crc32.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <linux/fs.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/workqueue.h>
#समावेश <net/dcbnl.h>
#समावेश <net/dcbevent.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsicam.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_fc.h>
#समावेश <net/rtnetlink.h>

#समावेश <scsi/fc/fc_encaps.h>
#समावेश <scsi/fc/fc_fip.h>
#समावेश <scsi/fc/fc_fcoe.h>

#समावेश <scsi/libfc.h>
#समावेश <scsi/fc_frame.h>
#समावेश <scsi/libfcoe.h>

#समावेश "fcoe.h"

MODULE_AUTHOR("Open-FCoE.org");
MODULE_DESCRIPTION("FCoE");
MODULE_LICENSE("GPL v2");

/* Perक्रमmance tuning parameters क्रम fcoe */
अटल अचिन्हित पूर्णांक fcoe_ddp_min = 4096;
module_param_named(ddp_min, fcoe_ddp_min, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ddp_min, "Minimum I/O size in bytes for "	\
		 "Direct Data Placement (DDP).");

अचिन्हित पूर्णांक fcoe_debug_logging;
module_param_named(debug_logging, fcoe_debug_logging, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(debug_logging, "a bit mask of logging levels");

अटल अचिन्हित पूर्णांक fcoe_e_d_tov = 2 * 1000;
module_param_named(e_d_tov, fcoe_e_d_tov, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(e_d_tov, "E_D_TOV in ms, default 2000");

अटल अचिन्हित पूर्णांक fcoe_r_a_tov = 2 * 2 * 1000;
module_param_named(r_a_tov, fcoe_r_a_tov, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(r_a_tov, "R_A_TOV in ms, default 4000");

अटल DEFINE_MUTEX(fcoe_config_mutex);

अटल काष्ठा workqueue_काष्ठा *fcoe_wq;

/* fcoe host list */
/* must only by accessed under the RTNL mutex */
अटल LIST_HEAD(fcoe_hostlist);
अटल DEFINE_PER_CPU(काष्ठा fcoe_percpu_s, fcoe_percpu);

/* Function Prototypes */
अटल पूर्णांक fcoe_reset(काष्ठा Scsi_Host *);
अटल पूर्णांक fcoe_xmit(काष्ठा fc_lport *, काष्ठा fc_frame *);
अटल पूर्णांक fcoe_rcv(काष्ठा sk_buff *, काष्ठा net_device *,
		    काष्ठा packet_type *, काष्ठा net_device *);
अटल व्योम fcoe_percpu_clean(काष्ठा fc_lport *);
अटल पूर्णांक fcoe_link_ok(काष्ठा fc_lport *);

अटल काष्ठा fc_lport *fcoe_hostlist_lookup(स्थिर काष्ठा net_device *);
अटल पूर्णांक fcoe_hostlist_add(स्थिर काष्ठा fc_lport *);
अटल व्योम fcoe_hostlist_del(स्थिर काष्ठा fc_lport *);

अटल पूर्णांक fcoe_device_notअगरication(काष्ठा notअगरier_block *, uदीर्घ, व्योम *);
अटल व्योम fcoe_dev_setup(व्योम);
अटल व्योम fcoe_dev_cleanup(व्योम);
अटल काष्ठा fcoe_पूर्णांकerface
*fcoe_hostlist_lookup_port(स्थिर काष्ठा net_device *);

अटल पूर्णांक fcoe_fip_recv(काष्ठा sk_buff *, काष्ठा net_device *,
			 काष्ठा packet_type *, काष्ठा net_device *);
अटल पूर्णांक fcoe_fip_vlan_recv(काष्ठा sk_buff *, काष्ठा net_device *,
			      काष्ठा packet_type *, काष्ठा net_device *);

अटल व्योम fcoe_fip_send(काष्ठा fcoe_ctlr *, काष्ठा sk_buff *);
अटल व्योम fcoe_update_src_mac(काष्ठा fc_lport *, u8 *);
अटल u8 *fcoe_get_src_mac(काष्ठा fc_lport *);
अटल व्योम fcoe_destroy_work(काष्ठा work_काष्ठा *);

अटल पूर्णांक fcoe_ddp_setup(काष्ठा fc_lport *, u16, काष्ठा scatterlist *,
			  अचिन्हित पूर्णांक);
अटल पूर्णांक fcoe_ddp_करोne(काष्ठा fc_lport *, u16);
अटल पूर्णांक fcoe_ddp_target(काष्ठा fc_lport *, u16, काष्ठा scatterlist *,
			   अचिन्हित पूर्णांक);
अटल पूर्णांक fcoe_dcb_app_notअगरication(काष्ठा notअगरier_block *notअगरier,
				     uदीर्घ event, व्योम *ptr);

अटल bool fcoe_match(काष्ठा net_device *netdev);
अटल पूर्णांक fcoe_create(काष्ठा net_device *netdev, क्रमागत fip_mode fip_mode);
अटल पूर्णांक fcoe_destroy(काष्ठा net_device *netdev);
अटल पूर्णांक fcoe_enable(काष्ठा net_device *netdev);
अटल पूर्णांक fcoe_disable(काष्ठा net_device *netdev);

/* fcoe_syfs control पूर्णांकerface handlers */
अटल पूर्णांक fcoe_ctlr_alloc(काष्ठा net_device *netdev);
अटल पूर्णांक fcoe_ctlr_enabled(काष्ठा fcoe_ctlr_device *cdev);
अटल व्योम fcoe_ctlr_mode(काष्ठा fcoe_ctlr_device *ctlr_dev);

अटल काष्ठा fc_seq *fcoe_elsct_send(काष्ठा fc_lport *,
				      u32 did, काष्ठा fc_frame *,
				      अचिन्हित पूर्णांक op,
				      व्योम (*resp)(काष्ठा fc_seq *,
						   काष्ठा fc_frame *,
						   व्योम *),
				      व्योम *, u32 समयout);
अटल व्योम fcoe_recv_frame(काष्ठा sk_buff *skb);

/* notअगरication function क्रम packets from net device */
अटल काष्ठा notअगरier_block fcoe_notअगरier = अणु
	.notअगरier_call = fcoe_device_notअगरication,
पूर्ण;

/* notअगरication function क्रम DCB events */
अटल काष्ठा notअगरier_block dcb_notअगरier = अणु
	.notअगरier_call = fcoe_dcb_app_notअगरication,
पूर्ण;

अटल काष्ठा scsi_transport_ढाँचा *fcoe_nport_scsi_transport;
अटल काष्ठा scsi_transport_ढाँचा *fcoe_vport_scsi_transport;

अटल पूर्णांक fcoe_vport_destroy(काष्ठा fc_vport *);
अटल पूर्णांक fcoe_vport_create(काष्ठा fc_vport *, bool disabled);
अटल पूर्णांक fcoe_vport_disable(काष्ठा fc_vport *, bool disable);
अटल व्योम fcoe_set_vport_symbolic_name(काष्ठा fc_vport *);
अटल व्योम fcoe_set_port_id(काष्ठा fc_lport *, u32, काष्ठा fc_frame *);
अटल व्योम fcoe_fcf_get_vlan_id(काष्ठा fcoe_fcf_device *);
अटल व्योम fcoe_vport_हटाओ(काष्ठा fc_lport *);

अटल काष्ठा fcoe_sysfs_function_ढाँचा fcoe_sysfs_templ = अणु
	.set_fcoe_ctlr_mode = fcoe_ctlr_mode,
	.set_fcoe_ctlr_enabled = fcoe_ctlr_enabled,
	.get_fcoe_ctlr_link_fail = fcoe_ctlr_get_lesb,
	.get_fcoe_ctlr_vlink_fail = fcoe_ctlr_get_lesb,
	.get_fcoe_ctlr_miss_fka = fcoe_ctlr_get_lesb,
	.get_fcoe_ctlr_symb_err = fcoe_ctlr_get_lesb,
	.get_fcoe_ctlr_err_block = fcoe_ctlr_get_lesb,
	.get_fcoe_ctlr_fcs_error = fcoe_ctlr_get_lesb,

	.get_fcoe_fcf_selected = fcoe_fcf_get_selected,
	.get_fcoe_fcf_vlan_id = fcoe_fcf_get_vlan_id,
पूर्ण;

अटल काष्ठा libfc_function_ढाँचा fcoe_libfc_fcn_templ = अणु
	.frame_send = fcoe_xmit,
	.ddp_setup = fcoe_ddp_setup,
	.ddp_करोne = fcoe_ddp_करोne,
	.ddp_target = fcoe_ddp_target,
	.elsct_send = fcoe_elsct_send,
	.get_lesb = fcoe_get_lesb,
	.lport_set_port_id = fcoe_set_port_id,
पूर्ण;

अटल काष्ठा fc_function_ढाँचा fcoe_nport_fc_functions = अणु
	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_supported_fc4s = 1,
	.show_host_active_fc4s = 1,
	.show_host_maxframe_size = 1,
	.show_host_serial_number = 1,
	.show_host_manufacturer = 1,
	.show_host_model = 1,
	.show_host_model_description = 1,
	.show_host_hardware_version = 1,
	.show_host_driver_version = 1,
	.show_host_firmware_version = 1,
	.show_host_optionrom_version = 1,

	.show_host_port_id = 1,
	.show_host_supported_speeds = 1,
	.get_host_speed = fc_get_host_speed,
	.show_host_speed = 1,
	.show_host_port_type = 1,
	.get_host_port_state = fc_get_host_port_state,
	.show_host_port_state = 1,
	.show_host_symbolic_name = 1,

	.dd_fcrport_size = माप(काष्ठा fc_rport_libfc_priv),
	.show_rport_maxframe_size = 1,
	.show_rport_supported_classes = 1,

	.show_host_fabric_name = 1,
	.show_starget_node_name = 1,
	.show_starget_port_name = 1,
	.show_starget_port_id = 1,
	.set_rport_dev_loss_पंचांगo = fc_set_rport_loss_पंचांगo,
	.show_rport_dev_loss_पंचांगo = 1,
	.get_fc_host_stats = fc_get_host_stats,
	.issue_fc_host_lip = fcoe_reset,

	.terminate_rport_io = fc_rport_terminate_io,

	.vport_create = fcoe_vport_create,
	.vport_delete = fcoe_vport_destroy,
	.vport_disable = fcoe_vport_disable,
	.set_vport_symbolic_name = fcoe_set_vport_symbolic_name,

	.bsg_request = fc_lport_bsg_request,
पूर्ण;

अटल काष्ठा fc_function_ढाँचा fcoe_vport_fc_functions = अणु
	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_supported_fc4s = 1,
	.show_host_active_fc4s = 1,
	.show_host_maxframe_size = 1,
	.show_host_serial_number = 1,
	.show_host_manufacturer = 1,
	.show_host_model = 1,
	.show_host_model_description = 1,
	.show_host_hardware_version = 1,
	.show_host_driver_version = 1,
	.show_host_firmware_version = 1,
	.show_host_optionrom_version = 1,

	.show_host_port_id = 1,
	.show_host_supported_speeds = 1,
	.get_host_speed = fc_get_host_speed,
	.show_host_speed = 1,
	.show_host_port_type = 1,
	.get_host_port_state = fc_get_host_port_state,
	.show_host_port_state = 1,
	.show_host_symbolic_name = 1,

	.dd_fcrport_size = माप(काष्ठा fc_rport_libfc_priv),
	.show_rport_maxframe_size = 1,
	.show_rport_supported_classes = 1,

	.show_host_fabric_name = 1,
	.show_starget_node_name = 1,
	.show_starget_port_name = 1,
	.show_starget_port_id = 1,
	.set_rport_dev_loss_पंचांगo = fc_set_rport_loss_पंचांगo,
	.show_rport_dev_loss_पंचांगo = 1,
	.get_fc_host_stats = fc_get_host_stats,
	.issue_fc_host_lip = fcoe_reset,

	.terminate_rport_io = fc_rport_terminate_io,

	.bsg_request = fc_lport_bsg_request,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा fcoe_shost_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = "FCoE Driver",
	.proc_name = FCOE_NAME,
	.queuecommand = fc_queuecommand,
	.eh_समयd_out = fc_eh_समयd_out,
	.eh_पात_handler = fc_eh_पात,
	.eh_device_reset_handler = fc_eh_device_reset,
	.eh_host_reset_handler = fc_eh_host_reset,
	.slave_alloc = fc_slave_alloc,
	.change_queue_depth = scsi_change_queue_depth,
	.this_id = -1,
	.cmd_per_lun = 3,
	.can_queue = FCOE_MAX_OUTSTANDING_COMMANDS,
	.sg_tablesize = SG_ALL,
	.max_sectors = 0xffff,
	.track_queue_depth = 1,
पूर्ण;

/**
 * fcoe_पूर्णांकerface_setup() - Setup a FCoE पूर्णांकerface
 * @fcoe:   The new FCoE पूर्णांकerface
 * @netdev: The net device that the fcoe पूर्णांकerface is on
 *
 * Returns : 0 क्रम success
 * Locking: must be called with the RTNL mutex held
 */
अटल पूर्णांक fcoe_पूर्णांकerface_setup(काष्ठा fcoe_पूर्णांकerface *fcoe,
				काष्ठा net_device *netdev)
अणु
	काष्ठा fcoe_ctlr *fip = fcoe_to_ctlr(fcoe);
	काष्ठा netdev_hw_addr *ha;
	काष्ठा net_device *real_dev;
	u8 flogi_maddr[ETH_ALEN];
	स्थिर काष्ठा net_device_ops *ops;

	fcoe->netdev = netdev;

	/* Let LLD initialize क्रम FCoE */
	ops = netdev->netdev_ops;
	अगर (ops->nकरो_fcoe_enable) अणु
		अगर (ops->nकरो_fcoe_enable(netdev))
			FCOE_NETDEV_DBG(netdev, "Failed to enable FCoE"
					" specific feature for LLD.\n");
	पूर्ण

	/* Do not support क्रम bonding device */
	अगर (netdev->priv_flags & IFF_BONDING && netdev->flags & IFF_MASTER) अणु
		FCOE_NETDEV_DBG(netdev, "Bonded interfaces not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* look क्रम SAN MAC address, अगर multiple SAN MACs exist, only
	 * use the first one क्रम SPMA */
	real_dev = is_vlan_dev(netdev) ? vlan_dev_real_dev(netdev) : netdev;
	fcoe->realdev = real_dev;
	rcu_पढ़ो_lock();
	क्रम_each_dev_addr(real_dev, ha) अणु
		अगर ((ha->type == NETDEV_HW_ADDR_T_SAN) &&
		    (is_valid_ether_addr(ha->addr))) अणु
			स_नकल(fip->ctl_src_addr, ha->addr, ETH_ALEN);
			fip->spma = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	/* setup Source Mac Address */
	अगर (!fip->spma)
		स_नकल(fip->ctl_src_addr, netdev->dev_addr, netdev->addr_len);

	/*
	 * Add FCoE MAC address as second unicast MAC address
	 * or enter promiscuous mode अगर not capable of listening
	 * क्रम multiple unicast MACs.
	 */
	स_नकल(flogi_maddr, (u8[6]) FC_FCOE_FLOGI_MAC, ETH_ALEN);
	dev_uc_add(netdev, flogi_maddr);
	अगर (fip->spma)
		dev_uc_add(netdev, fip->ctl_src_addr);
	अगर (fip->mode == FIP_MODE_VN2VN) अणु
		dev_mc_add(netdev, FIP_ALL_VN2VN_MACS);
		dev_mc_add(netdev, FIP_ALL_P2P_MACS);
	पूर्ण अन्यथा
		dev_mc_add(netdev, FIP_ALL_ENODE_MACS);

	/*
	 * setup the receive function from ethernet driver
	 * on the ethertype क्रम the given device
	 */
	fcoe->fcoe_packet_type.func = fcoe_rcv;
	fcoe->fcoe_packet_type.type = htons(ETH_P_FCOE);
	fcoe->fcoe_packet_type.dev = netdev;
	dev_add_pack(&fcoe->fcoe_packet_type);

	fcoe->fip_packet_type.func = fcoe_fip_recv;
	fcoe->fip_packet_type.type = htons(ETH_P_FIP);
	fcoe->fip_packet_type.dev = netdev;
	dev_add_pack(&fcoe->fip_packet_type);

	अगर (netdev != real_dev) अणु
		fcoe->fip_vlan_packet_type.func = fcoe_fip_vlan_recv;
		fcoe->fip_vlan_packet_type.type = htons(ETH_P_FIP);
		fcoe->fip_vlan_packet_type.dev = real_dev;
		dev_add_pack(&fcoe->fip_vlan_packet_type);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * fcoe_पूर्णांकerface_create() - Create a FCoE पूर्णांकerface on a net device
 * @netdev: The net device to create the FCoE पूर्णांकerface on
 * @fip_mode: The mode to use क्रम FIP
 *
 * Returns: poपूर्णांकer to a काष्ठा fcoe_पूर्णांकerface or शून्य on error
 */
अटल काष्ठा fcoe_पूर्णांकerface *fcoe_पूर्णांकerface_create(काष्ठा net_device *netdev,
						    क्रमागत fip_mode fip_mode)
अणु
	काष्ठा fcoe_ctlr_device *ctlr_dev;
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	पूर्णांक size;
	पूर्णांक err;

	अगर (!try_module_get(THIS_MODULE)) अणु
		FCOE_NETDEV_DBG(netdev,
				"Could not get a reference to the module\n");
		fcoe = ERR_PTR(-EBUSY);
		जाओ out;
	पूर्ण

	size = माप(काष्ठा fcoe_ctlr) + माप(काष्ठा fcoe_पूर्णांकerface);
	ctlr_dev = fcoe_ctlr_device_add(&netdev->dev, &fcoe_sysfs_templ,
					size);
	अगर (!ctlr_dev) अणु
		FCOE_DBG("Failed to add fcoe_ctlr_device\n");
		fcoe = ERR_PTR(-ENOMEM);
		जाओ out_puपंचांगod;
	पूर्ण

	ctlr = fcoe_ctlr_device_priv(ctlr_dev);
	ctlr->cdev = ctlr_dev;
	fcoe = fcoe_ctlr_priv(ctlr);

	dev_hold(netdev);

	/*
	 * Initialize FIP.
	 */
	fcoe_ctlr_init(ctlr, fip_mode);
	ctlr->send = fcoe_fip_send;
	ctlr->update_mac = fcoe_update_src_mac;
	ctlr->get_src_addr = fcoe_get_src_mac;

	err = fcoe_पूर्णांकerface_setup(fcoe, netdev);
	अगर (err) अणु
		fcoe_ctlr_destroy(ctlr);
		fcoe_ctlr_device_delete(ctlr_dev);
		dev_put(netdev);
		fcoe = ERR_PTR(err);
		जाओ out_puपंचांगod;
	पूर्ण

	जाओ out;

out_puपंचांगod:
	module_put(THIS_MODULE);
out:
	वापस fcoe;
पूर्ण

/**
 * fcoe_पूर्णांकerface_हटाओ() - हटाओ FCoE पूर्णांकerface from netdev
 * @fcoe: The FCoE पूर्णांकerface to be cleaned up
 *
 * Caller must be holding the RTNL mutex
 */
अटल व्योम fcoe_पूर्णांकerface_हटाओ(काष्ठा fcoe_पूर्णांकerface *fcoe)
अणु
	काष्ठा net_device *netdev = fcoe->netdev;
	काष्ठा fcoe_ctlr *fip = fcoe_to_ctlr(fcoe);
	u8 flogi_maddr[ETH_ALEN];
	स्थिर काष्ठा net_device_ops *ops;

	/*
	 * Don't listen क्रम Ethernet packets anymore.
	 * synchronize_net() ensures that the packet handlers are not running
	 * on another CPU. dev_हटाओ_pack() would करो that, this calls the
	 * unsyncronized version __dev_हटाओ_pack() to aव्योम multiple delays.
	 */
	__dev_हटाओ_pack(&fcoe->fcoe_packet_type);
	__dev_हटाओ_pack(&fcoe->fip_packet_type);
	अगर (netdev != fcoe->realdev)
		__dev_हटाओ_pack(&fcoe->fip_vlan_packet_type);
	synchronize_net();

	/* Delete secondary MAC addresses */
	स_नकल(flogi_maddr, (u8[6]) FC_FCOE_FLOGI_MAC, ETH_ALEN);
	dev_uc_del(netdev, flogi_maddr);
	अगर (fip->spma)
		dev_uc_del(netdev, fip->ctl_src_addr);
	अगर (fip->mode == FIP_MODE_VN2VN) अणु
		dev_mc_del(netdev, FIP_ALL_VN2VN_MACS);
		dev_mc_del(netdev, FIP_ALL_P2P_MACS);
	पूर्ण अन्यथा
		dev_mc_del(netdev, FIP_ALL_ENODE_MACS);

	/* Tell the LLD we are करोne w/ FCoE */
	ops = netdev->netdev_ops;
	अगर (ops->nकरो_fcoe_disable) अणु
		अगर (ops->nकरो_fcoe_disable(netdev))
			FCOE_NETDEV_DBG(netdev, "Failed to disable FCoE"
					" specific feature for LLD.\n");
	पूर्ण
	fcoe->हटाओd = 1;
पूर्ण


/**
 * fcoe_पूर्णांकerface_cleanup() - Clean up a FCoE पूर्णांकerface
 * @fcoe: The FCoE पूर्णांकerface to be cleaned up
 */
अटल व्योम fcoe_पूर्णांकerface_cleanup(काष्ठा fcoe_पूर्णांकerface *fcoe)
अणु
	काष्ठा net_device *netdev = fcoe->netdev;
	काष्ठा fcoe_ctlr *fip = fcoe_to_ctlr(fcoe);

	/* Release the self-reference taken during fcoe_पूर्णांकerface_create() */
	/* tear-करोwn the FCoE controller */
	fcoe_ctlr_destroy(fip);
	scsi_host_put(fip->lp->host);
	dev_put(netdev);
	module_put(THIS_MODULE);
पूर्ण

/**
 * fcoe_fip_recv() - Handler क्रम received FIP frames
 * @skb:      The receive skb
 * @netdev:   The associated net device
 * @ptype:    The packet_type काष्ठाure which was used to रेजिस्टर this handler
 * @orig_dev: The original net_device the skb was received on.
 *	      (in हाल dev is a bond)
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_fip_recv(काष्ठा sk_buff *skb, काष्ठा net_device *netdev,
			 काष्ठा packet_type *ptype,
			 काष्ठा net_device *orig_dev)
अणु
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	काष्ठा fcoe_ctlr *ctlr;

	fcoe = container_of(ptype, काष्ठा fcoe_पूर्णांकerface, fip_packet_type);
	ctlr = fcoe_to_ctlr(fcoe);
	fcoe_ctlr_recv(ctlr, skb);
	वापस 0;
पूर्ण

/**
 * fcoe_fip_vlan_recv() - Handler क्रम received FIP VLAN discovery frames
 * @skb:      The receive skb
 * @netdev:   The associated net device
 * @ptype:    The packet_type काष्ठाure which was used to रेजिस्टर this handler
 * @orig_dev: The original net_device the skb was received on.
 *	      (in हाल dev is a bond)
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_fip_vlan_recv(काष्ठा sk_buff *skb, काष्ठा net_device *netdev,
			      काष्ठा packet_type *ptype,
			      काष्ठा net_device *orig_dev)
अणु
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	काष्ठा fcoe_ctlr *ctlr;

	fcoe = container_of(ptype, काष्ठा fcoe_पूर्णांकerface, fip_vlan_packet_type);
	ctlr = fcoe_to_ctlr(fcoe);
	fcoe_ctlr_recv(ctlr, skb);
	वापस 0;
पूर्ण

/**
 * fcoe_port_send() - Send an Ethernet-encapsulated FIP/FCoE frame
 * @port: The FCoE port
 * @skb: The FIP/FCoE packet to be sent
 */
अटल व्योम fcoe_port_send(काष्ठा fcoe_port *port, काष्ठा sk_buff *skb)
अणु
	अगर (port->fcoe_pending_queue.qlen)
		fcoe_check_रुको_queue(port->lport, skb);
	अन्यथा अगर (fcoe_start_io(skb))
		fcoe_check_रुको_queue(port->lport, skb);
पूर्ण

/**
 * fcoe_fip_send() - Send an Ethernet-encapsulated FIP frame
 * @fip: The FCoE controller
 * @skb: The FIP packet to be sent
 */
अटल व्योम fcoe_fip_send(काष्ठा fcoe_ctlr *fip, काष्ठा sk_buff *skb)
अणु
	काष्ठा fcoe_पूर्णांकerface *fcoe = fcoe_from_ctlr(fip);
	काष्ठा fip_frame अणु
		काष्ठा ethhdr eth;
		काष्ठा fip_header fip;
	पूर्ण __packed *frame;

	/*
	 * Use शेष VLAN क्रम FIP VLAN discovery protocol
	 */
	frame = (काष्ठा fip_frame *)skb->data;
	अगर (ntohs(frame->eth.h_proto) == ETH_P_FIP &&
	    ntohs(frame->fip.fip_op) == FIP_OP_VLAN &&
	    fcoe->realdev != fcoe->netdev)
		skb->dev = fcoe->realdev;
	अन्यथा
		skb->dev = fcoe->netdev;
	fcoe_port_send(lport_priv(fip->lp), skb);
पूर्ण

/**
 * fcoe_update_src_mac() - Update the Ethernet MAC filters
 * @lport: The local port to update the source MAC on
 * @addr:  Unicast MAC address to add
 *
 * Remove any previously-set unicast MAC filter.
 * Add secondary FCoE MAC address filter क्रम our OUI.
 */
अटल व्योम fcoe_update_src_mac(काष्ठा fc_lport *lport, u8 *addr)
अणु
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा fcoe_पूर्णांकerface *fcoe = port->priv;

	अगर (!is_zero_ether_addr(port->data_src_addr))
		dev_uc_del(fcoe->netdev, port->data_src_addr);
	अगर (!is_zero_ether_addr(addr))
		dev_uc_add(fcoe->netdev, addr);
	स_नकल(port->data_src_addr, addr, ETH_ALEN);
पूर्ण

/**
 * fcoe_get_src_mac() - वापस the Ethernet source address क्रम an lport
 * @lport: libfc lport
 */
अटल u8 *fcoe_get_src_mac(काष्ठा fc_lport *lport)
अणु
	काष्ठा fcoe_port *port = lport_priv(lport);

	वापस port->data_src_addr;
पूर्ण

/**
 * fcoe_lport_config() - Set up a local port
 * @lport: The local port to be setup
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_lport_config(काष्ठा fc_lport *lport)
अणु
	lport->link_up = 0;
	lport->qfull = 0;
	lport->max_retry_count = 3;
	lport->max_rport_retry_count = 3;
	lport->e_d_tov = fcoe_e_d_tov;
	lport->r_a_tov = fcoe_r_a_tov;
	lport->service_params = (FCP_SPPF_INIT_FCN | FCP_SPPF_RD_XRDY_DIS |
				 FCP_SPPF_RETRY | FCP_SPPF_CONF_COMPL);
	lport->करोes_npiv = 1;

	fc_lport_init_stats(lport);

	/* lport fc_lport related configuration */
	fc_lport_config(lport);

	/* offload related configuration */
	lport->crc_offload = 0;
	lport->seq_offload = 0;
	lport->lro_enabled = 0;
	lport->lro_xid = 0;
	lport->lso_max = 0;

	वापस 0;
पूर्ण

/*
 * fcoe_netdev_features_change - Updates the lport's offload flags based
 * on the LLD netdev's FCoE feature flags
 */
अटल व्योम fcoe_netdev_features_change(काष्ठा fc_lport *lport,
					काष्ठा net_device *netdev)
अणु
	mutex_lock(&lport->lp_mutex);

	अगर (netdev->features & NETIF_F_SG)
		lport->sg_supp = 1;
	अन्यथा
		lport->sg_supp = 0;

	अगर (netdev->features & NETIF_F_FCOE_CRC) अणु
		lport->crc_offload = 1;
		FCOE_NETDEV_DBG(netdev, "Supports FCCRC offload\n");
	पूर्ण अन्यथा अणु
		lport->crc_offload = 0;
	पूर्ण

	अगर (netdev->features & NETIF_F_FSO) अणु
		lport->seq_offload = 1;
		lport->lso_max = netdev->gso_max_size;
		FCOE_NETDEV_DBG(netdev, "Supports LSO for max len 0x%x\n",
				lport->lso_max);
	पूर्ण अन्यथा अणु
		lport->seq_offload = 0;
		lport->lso_max = 0;
	पूर्ण

	अगर (netdev->fcoe_ddp_xid) अणु
		lport->lro_enabled = 1;
		lport->lro_xid = netdev->fcoe_ddp_xid;
		FCOE_NETDEV_DBG(netdev, "Supports LRO for max xid 0x%x\n",
				lport->lro_xid);
	पूर्ण अन्यथा अणु
		lport->lro_enabled = 0;
		lport->lro_xid = 0;
	पूर्ण

	mutex_unlock(&lport->lp_mutex);
पूर्ण

/**
 * fcoe_netdev_config() - Set up net devive क्रम SW FCoE
 * @lport:  The local port that is associated with the net device
 * @netdev: The associated net device
 *
 * Must be called after fcoe_lport_config() as it will use local port mutex
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_netdev_config(काष्ठा fc_lport *lport, काष्ठा net_device *netdev)
अणु
	u32 mfs;
	u64 wwnn, wwpn;
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_port *port;

	/* Setup lport निजी data to poपूर्णांक to fcoe softc */
	port = lport_priv(lport);
	fcoe = port->priv;
	ctlr = fcoe_to_ctlr(fcoe);

	/* Figure out the VLAN ID, अगर any */
	अगर (is_vlan_dev(netdev))
		lport->vlan = vlan_dev_vlan_id(netdev);
	अन्यथा
		lport->vlan = 0;

	/*
	 * Determine max frame size based on underlying device and optional
	 * user-configured limit.  If the MFS is too low, fcoe_link_ok()
	 * will वापस 0, so करो this first.
	 */
	mfs = netdev->mtu;
	अगर (netdev->features & NETIF_F_FCOE_MTU) अणु
		mfs = FCOE_MTU;
		FCOE_NETDEV_DBG(netdev, "Supports FCOE_MTU of %d bytes\n", mfs);
	पूर्ण
	mfs -= (माप(काष्ठा fcoe_hdr) + माप(काष्ठा fcoe_crc_eof));
	अगर (fc_set_mfs(lport, mfs))
		वापस -EINVAL;

	/* offload features support */
	fcoe_netdev_features_change(lport, netdev);

	skb_queue_head_init(&port->fcoe_pending_queue);
	port->fcoe_pending_queue_active = 0;
	समयr_setup(&port->समयr, fcoe_queue_समयr, 0);

	fcoe_link_speed_update(lport);

	अगर (!lport->vport) अणु
		अगर (fcoe_get_wwn(netdev, &wwnn, NETDEV_FCOE_WWNN))
			wwnn = fcoe_wwn_from_mac(ctlr->ctl_src_addr, 1, 0);
		fc_set_wwnn(lport, wwnn);
		अगर (fcoe_get_wwn(netdev, &wwpn, NETDEV_FCOE_WWPN))
			wwpn = fcoe_wwn_from_mac(ctlr->ctl_src_addr,
						 2, 0);
		fc_set_wwpn(lport, wwpn);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * fcoe_shost_config() - Set up the SCSI host associated with a local port
 * @lport: The local port
 * @dev:   The device associated with the SCSI host
 *
 * Must be called after fcoe_lport_config() and fcoe_netdev_config()
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_shost_config(काष्ठा fc_lport *lport, काष्ठा device *dev)
अणु
	पूर्णांक rc = 0;

	/* lport scsi host config */
	lport->host->max_lun = FCOE_MAX_LUN;
	lport->host->max_id = FCOE_MAX_FCP_TARGET;
	lport->host->max_channel = 0;
	lport->host->max_cmd_len = FCOE_MAX_CMD_LEN;

	अगर (lport->vport)
		lport->host->transportt = fcoe_vport_scsi_transport;
	अन्यथा
		lport->host->transportt = fcoe_nport_scsi_transport;

	/* add the new host to the SCSI-ml */
	rc = scsi_add_host(lport->host, dev);
	अगर (rc) अणु
		FCOE_NETDEV_DBG(fcoe_netdev(lport), "fcoe_shost_config: "
				"error on scsi_add_host\n");
		वापस rc;
	पूर्ण

	अगर (!lport->vport)
		fc_host_max_npiv_vports(lport->host) = अच_लघु_उच्च;

	snम_लिखो(fc_host_symbolic_name(lport->host), FC_SYMBOLIC_NAME_SIZE,
		 "%s v%s over %s", FCOE_NAME, FCOE_VERSION,
		 fcoe_netdev(lport)->name);

	वापस 0;
पूर्ण


/**
 * fcoe_fdmi_info() - Get FDMI related info from net devive क्रम SW FCoE
 * @lport:  The local port that is associated with the net device
 * @netdev: The associated net device
 *
 * Must be called after fcoe_shost_config() as it will use local port mutex
 *
 */
अटल व्योम fcoe_fdmi_info(काष्ठा fc_lport *lport, काष्ठा net_device *netdev)
अणु
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	काष्ठा fcoe_port *port;
	काष्ठा net_device *realdev;
	पूर्णांक rc;

	port = lport_priv(lport);
	fcoe = port->priv;
	realdev = fcoe->realdev;

	/* No FDMI state m/c क्रम NPIV ports */
	अगर (lport->vport)
		वापस;

	अगर (realdev->netdev_ops->nकरो_fcoe_get_hbainfo) अणु
		काष्ठा netdev_fcoe_hbainfo *fdmi;
		fdmi = kzalloc(माप(*fdmi), GFP_KERNEL);
		अगर (!fdmi)
			वापस;

		rc = realdev->netdev_ops->nकरो_fcoe_get_hbainfo(realdev,
							       fdmi);
		अगर (rc) अणु
			prपूर्णांकk(KERN_INFO "fcoe: Failed to retrieve FDMI "
					"information from netdev.\n");
			वापस;
		पूर्ण

		snम_लिखो(fc_host_serial_number(lport->host),
			 FC_SERIAL_NUMBER_SIZE,
			 "%s",
			 fdmi->serial_number);
		snम_लिखो(fc_host_manufacturer(lport->host),
			 FC_SERIAL_NUMBER_SIZE,
			 "%s",
			 fdmi->manufacturer);
		snम_लिखो(fc_host_model(lport->host),
			 FC_SYMBOLIC_NAME_SIZE,
			 "%s",
			 fdmi->model);
		snम_लिखो(fc_host_model_description(lport->host),
			 FC_SYMBOLIC_NAME_SIZE,
			 "%s",
			 fdmi->model_description);
		snम_लिखो(fc_host_hardware_version(lport->host),
			 FC_VERSION_STRING_SIZE,
			 "%s",
			 fdmi->hardware_version);
		snम_लिखो(fc_host_driver_version(lport->host),
			 FC_VERSION_STRING_SIZE,
			 "%s",
			 fdmi->driver_version);
		snम_लिखो(fc_host_optionrom_version(lport->host),
			 FC_VERSION_STRING_SIZE,
			 "%s",
			 fdmi->optionrom_version);
		snम_लिखो(fc_host_firmware_version(lport->host),
			 FC_VERSION_STRING_SIZE,
			 "%s",
			 fdmi->firmware_version);

		/* Enable FDMI lport states */
		lport->fdmi_enabled = 1;
		kमुक्त(fdmi);
	पूर्ण अन्यथा अणु
		lport->fdmi_enabled = 0;
		prपूर्णांकk(KERN_INFO "fcoe: No FDMI support.\n");
	पूर्ण
पूर्ण

/**
 * fcoe_oem_match() - The match routine क्रम the offloaded exchange manager
 * @fp: The I/O frame
 *
 * This routine will be associated with an exchange manager (EM). When
 * the libfc exchange handling code is looking क्रम an EM to use it will
 * call this routine and pass it the frame that it wishes to send. This
 * routine will वापस True अगर the associated EM is to be used and False
 * अगर the echange code should जारी looking क्रम an EM.
 *
 * The offload EM that this routine is associated with will handle any
 * packets that are क्रम SCSI पढ़ो requests.
 *
 * This has been enhanced to work when FCoE stack is operating in target
 * mode.
 *
 * Returns: True क्रम पढ़ो types I/O, otherwise वापसs false.
 */
अटल bool fcoe_oem_match(काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_frame_header *fh = fc_frame_header_get(fp);
	काष्ठा fcp_cmnd *fcp;

	अगर (fc_fcp_is_पढ़ो(fr_fsp(fp)) &&
	    (fr_fsp(fp)->data_len > fcoe_ddp_min))
		वापस true;
	अन्यथा अगर ((fr_fsp(fp) == शून्य) &&
		 (fh->fh_r_ctl == FC_RCTL_DD_UNSOL_CMD) &&
		 (ntohs(fh->fh_rx_id) == FC_XID_UNKNOWN)) अणु
		fcp = fc_frame_payload_get(fp, माप(*fcp));
		अगर ((fcp->fc_flags & FCP_CFL_WRDATA) &&
		    (ntohl(fcp->fc_dl) > fcoe_ddp_min))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * fcoe_em_config() - Allocate and configure an exchange manager
 * @lport: The local port that the new EM will be associated with
 *
 * Returns: 0 on success
 */
अटल अंतरभूत पूर्णांक fcoe_em_config(काष्ठा fc_lport *lport)
अणु
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा fcoe_पूर्णांकerface *fcoe = port->priv;
	काष्ठा fcoe_पूर्णांकerface *oldfcoe = शून्य;
	काष्ठा net_device *old_real_dev, *cur_real_dev;
	u16 min_xid = FCOE_MIN_XID;
	u16 max_xid = FCOE_MAX_XID;

	/*
	 * Check अगर need to allocate an em instance क्रम
	 * offload exchange ids to be shared across all VN_PORTs/lport.
	 */
	अगर (!lport->lro_enabled || !lport->lro_xid ||
	    (lport->lro_xid >= max_xid)) अणु
		lport->lro_xid = 0;
		जाओ skip_oem;
	पूर्ण

	/*
	 * Reuse existing offload em instance in हाल
	 * it is alपढ़ोy allocated on real eth device
	 */
	अगर (is_vlan_dev(fcoe->netdev))
		cur_real_dev = vlan_dev_real_dev(fcoe->netdev);
	अन्यथा
		cur_real_dev = fcoe->netdev;

	list_क्रम_each_entry(oldfcoe, &fcoe_hostlist, list) अणु
		अगर (is_vlan_dev(oldfcoe->netdev))
			old_real_dev = vlan_dev_real_dev(oldfcoe->netdev);
		अन्यथा
			old_real_dev = oldfcoe->netdev;

		अगर (cur_real_dev == old_real_dev) अणु
			fcoe->oem = oldfcoe->oem;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (fcoe->oem) अणु
		अगर (!fc_exch_mgr_add(lport, fcoe->oem, fcoe_oem_match)) अणु
			prपूर्णांकk(KERN_ERR "fcoe_em_config: failed to add "
			       "offload em:%p on interface:%s\n",
			       fcoe->oem, fcoe->netdev->name);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		fcoe->oem = fc_exch_mgr_alloc(lport, FC_CLASS_3,
					      FCOE_MIN_XID, lport->lro_xid,
					      fcoe_oem_match);
		अगर (!fcoe->oem) अणु
			prपूर्णांकk(KERN_ERR "fcoe_em_config: failed to allocate "
			       "em for offload exches on interface:%s\n",
			       fcoe->netdev->name);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/*
	 * Exclude offload EM xid range from next EM xid range.
	 */
	min_xid += lport->lro_xid + 1;

skip_oem:
	अगर (!fc_exch_mgr_alloc(lport, FC_CLASS_3, min_xid, max_xid, शून्य)) अणु
		prपूर्णांकk(KERN_ERR "fcoe_em_config: failed to "
		       "allocate em on interface %s\n", fcoe->netdev->name);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * fcoe_अगर_destroy() - Tear करोwn a SW FCoE instance
 * @lport: The local port to be destroyed
 *
 * Locking: Must be called with the RTNL mutex held.
 *
 */
अटल व्योम fcoe_अगर_destroy(काष्ठा fc_lport *lport)
अणु
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा fcoe_पूर्णांकerface *fcoe = port->priv;
	काष्ठा net_device *netdev = fcoe->netdev;

	FCOE_NETDEV_DBG(netdev, "Destroying interface\n");

	/* Logout of the fabric */
	fc_fabric_logoff(lport);

	/* Cleanup the fc_lport */
	fc_lport_destroy(lport);

	/* Stop the transmit retry समयr */
	del_समयr_sync(&port->समयr);

	/* Free existing transmit skbs */
	fcoe_clean_pending_queue(lport);

	अगर (!is_zero_ether_addr(port->data_src_addr))
		dev_uc_del(netdev, port->data_src_addr);
	अगर (lport->vport)
		synchronize_net();
	अन्यथा
		fcoe_पूर्णांकerface_हटाओ(fcoe);

	/* Free queued packets क्रम the per-CPU receive thपढ़ोs */
	fcoe_percpu_clean(lport);

	/* Detach from the scsi-ml */
	fc_हटाओ_host(lport->host);
	scsi_हटाओ_host(lport->host);

	/* Destroy lport scsi_priv */
	fc_fcp_destroy(lport);

	/* There are no more rports or I/O, मुक्त the EM */
	fc_exch_mgr_मुक्त(lport);

	/* Free memory used by statistical counters */
	fc_lport_मुक्त_stats(lport);

	/*
	 * Release the Scsi_Host क्रम vport but hold on to
	 * master lport until it fcoe पूर्णांकerface fully cleaned-up.
	 */
	अगर (lport->vport)
		scsi_host_put(lport->host);
पूर्ण

/**
 * fcoe_ddp_setup() - Call a LLD's ddp_setup through the net device
 * @lport: The local port to setup DDP क्रम
 * @xid:   The exchange ID क्रम this DDP transfer
 * @sgl:   The scatterlist describing this transfer
 * @sgc:   The number of sg items
 *
 * Returns: 0 अगर the DDP context was not configured
 */
अटल पूर्णांक fcoe_ddp_setup(काष्ठा fc_lport *lport, u16 xid,
			  काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sgc)
अणु
	काष्ठा net_device *netdev = fcoe_netdev(lport);

	अगर (netdev->netdev_ops->nकरो_fcoe_ddp_setup)
		वापस netdev->netdev_ops->nकरो_fcoe_ddp_setup(netdev,
							      xid, sgl,
							      sgc);

	वापस 0;
पूर्ण

/**
 * fcoe_ddp_target() - Call a LLD's ddp_target through the net device
 * @lport: The local port to setup DDP क्रम
 * @xid:   The exchange ID क्रम this DDP transfer
 * @sgl:   The scatterlist describing this transfer
 * @sgc:   The number of sg items
 *
 * Returns: 0 अगर the DDP context was not configured
 */
अटल पूर्णांक fcoe_ddp_target(काष्ठा fc_lport *lport, u16 xid,
			   काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sgc)
अणु
	काष्ठा net_device *netdev = fcoe_netdev(lport);

	अगर (netdev->netdev_ops->nकरो_fcoe_ddp_target)
		वापस netdev->netdev_ops->nकरो_fcoe_ddp_target(netdev, xid,
							       sgl, sgc);

	वापस 0;
पूर्ण


/**
 * fcoe_ddp_करोne() - Call a LLD's ddp_करोne through the net device
 * @lport: The local port to complete DDP on
 * @xid:   The exchange ID क्रम this DDP transfer
 *
 * Returns: the length of data that have been completed by DDP
 */
अटल पूर्णांक fcoe_ddp_करोne(काष्ठा fc_lport *lport, u16 xid)
अणु
	काष्ठा net_device *netdev = fcoe_netdev(lport);

	अगर (netdev->netdev_ops->nकरो_fcoe_ddp_करोne)
		वापस netdev->netdev_ops->nकरो_fcoe_ddp_करोne(netdev, xid);
	वापस 0;
पूर्ण

/**
 * fcoe_अगर_create() - Create a FCoE instance on an पूर्णांकerface
 * @fcoe:   The FCoE पूर्णांकerface to create a local port on
 * @parent: The device poपूर्णांकer to be the parent in sysfs क्रम the SCSI host
 * @npiv:   Indicates अगर the port is a vport or not
 *
 * Creates a fc_lport instance and a Scsi_Host instance and configure them.
 *
 * Returns: The allocated fc_lport or an error poपूर्णांकer
 */
अटल काष्ठा fc_lport *fcoe_अगर_create(काष्ठा fcoe_पूर्णांकerface *fcoe,
				       काष्ठा device *parent, पूर्णांक npiv)
अणु
	काष्ठा fcoe_ctlr *ctlr = fcoe_to_ctlr(fcoe);
	काष्ठा net_device *netdev = fcoe->netdev;
	काष्ठा fc_lport *lport, *n_port;
	काष्ठा fcoe_port *port;
	काष्ठा Scsi_Host *shost;
	पूर्णांक rc;
	/*
	 * parent is only a vport अगर npiv is 1,
	 * but we'll only use vport in that हाल so go ahead and set it
	 */
	काष्ठा fc_vport *vport = dev_to_vport(parent);

	FCOE_NETDEV_DBG(netdev, "Create Interface\n");

	अगर (!npiv)
		lport = libfc_host_alloc(&fcoe_shost_ढाँचा, माप(*port));
	अन्यथा
		lport = libfc_vport_create(vport, माप(*port));

	अगर (!lport) अणु
		FCOE_NETDEV_DBG(netdev, "Could not allocate host structure\n");
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	port = lport_priv(lport);
	port->lport = lport;
	port->priv = fcoe;
	port->get_netdev = fcoe_netdev;
	port->max_queue_depth = FCOE_MAX_QUEUE_DEPTH;
	port->min_queue_depth = FCOE_MIN_QUEUE_DEPTH;
	INIT_WORK(&port->destroy_work, fcoe_destroy_work);

	/*
	 * Need to add the lport to the hostlist
	 * so we catch NETDEV_CHANGE events.
	 */
	fcoe_hostlist_add(lport);

	/* configure a fc_lport including the exchange manager */
	rc = fcoe_lport_config(lport);
	अगर (rc) अणु
		FCOE_NETDEV_DBG(netdev, "Could not configure lport for the "
				"interface\n");
		जाओ out_host_put;
	पूर्ण

	अगर (npiv) अणु
		FCOE_NETDEV_DBG(netdev, "Setting vport names, "
				"%16.16llx %16.16llx\n",
				vport->node_name, vport->port_name);
		fc_set_wwnn(lport, vport->node_name);
		fc_set_wwpn(lport, vport->port_name);
	पूर्ण

	/* configure lport network properties */
	rc = fcoe_netdev_config(lport, netdev);
	अगर (rc) अणु
		FCOE_NETDEV_DBG(netdev, "Could not configure netdev for the "
				"interface\n");
		जाओ out_lp_destroy;
	पूर्ण

	/* configure lport scsi host properties */
	rc = fcoe_shost_config(lport, parent);
	अगर (rc) अणु
		FCOE_NETDEV_DBG(netdev, "Could not configure shost for the "
				"interface\n");
		जाओ out_lp_destroy;
	पूर्ण

	/* Initialize the library */
	rc = fcoe_libfc_config(lport, ctlr, &fcoe_libfc_fcn_templ, 1);
	अगर (rc) अणु
		FCOE_NETDEV_DBG(netdev, "Could not configure libfc for the "
				"interface\n");
		जाओ out_lp_destroy;
	पूर्ण

	/* Initialized FDMI inक्रमmation */
	fcoe_fdmi_info(lport, netdev);

	/*
	 * fcoe_em_alloc() and fcoe_hostlist_add() both
	 * need to be atomic with respect to other changes to the
	 * hostlist since fcoe_em_alloc() looks क्रम an existing EM
	 * instance on host list updated by fcoe_hostlist_add().
	 *
	 * This is currently handled through the fcoe_config_mutex
	 * begin held.
	 */
	अगर (!npiv)
		/* lport exch manager allocation */
		rc = fcoe_em_config(lport);
	अन्यथा अणु
		shost = vport_to_shost(vport);
		n_port = shost_priv(shost);
		rc = fc_exch_mgr_list_clone(n_port, lport);
	पूर्ण

	अगर (rc) अणु
		FCOE_NETDEV_DBG(netdev, "Could not configure the EM\n");
		जाओ out_lp_destroy;
	पूर्ण

	वापस lport;

out_lp_destroy:
	fc_exch_mgr_मुक्त(lport);
out_host_put:
	fcoe_hostlist_del(lport);
	scsi_host_put(lport->host);
out:
	वापस ERR_PTR(rc);
पूर्ण

/**
 * fcoe_अगर_init() - Initialization routine क्रम fcoe.ko
 *
 * Attaches the SW FCoE transport to the FC transport
 *
 * Returns: 0 on success
 */
अटल पूर्णांक __init fcoe_अगर_init(व्योम)
अणु
	/* attach to scsi transport */
	fcoe_nport_scsi_transport =
		fc_attach_transport(&fcoe_nport_fc_functions);
	अगर (!fcoe_nport_scsi_transport)
		जाओ err;

	fcoe_vport_scsi_transport =
		fc_attach_transport(&fcoe_vport_fc_functions);
	अगर (!fcoe_vport_scsi_transport)
		जाओ err_vport;

	वापस 0;

err_vport:
	fc_release_transport(fcoe_nport_scsi_transport);
err:
	prपूर्णांकk(KERN_ERR "fcoe: Failed to attach to the FC transport\n");
	वापस -ENODEV;
पूर्ण

/**
 * fcoe_अगर_निकास() - Tear करोwn fcoe.ko
 *
 * Detaches the SW FCoE transport from the FC transport
 *
 * Returns: 0 on success
 */
अटल पूर्णांक __निकास fcoe_अगर_निकास(व्योम)
अणु
	fc_release_transport(fcoe_nport_scsi_transport);
	fc_release_transport(fcoe_vport_scsi_transport);
	fcoe_nport_scsi_transport = शून्य;
	fcoe_vport_scsi_transport = शून्य;
	वापस 0;
पूर्ण

अटल व्योम fcoe_thपढ़ो_cleanup_local(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा page *crc_eof;
	काष्ठा fcoe_percpu_s *p;

	p = per_cpu_ptr(&fcoe_percpu, cpu);
	spin_lock_bh(&p->fcoe_rx_list.lock);
	crc_eof = p->crc_eof_page;
	p->crc_eof_page = शून्य;
	p->crc_eof_offset = 0;
	spin_unlock_bh(&p->fcoe_rx_list.lock);

	अगर (crc_eof)
		put_page(crc_eof);
	flush_work(&p->work);
पूर्ण

/**
 * fcoe_select_cpu() - Selects CPU to handle post-processing of incoming
 *			command.
 *
 * This routine selects next CPU based on cpumask to distribute
 * incoming requests in round robin.
 *
 * Returns: पूर्णांक CPU number
 */
अटल अंतरभूत अचिन्हित पूर्णांक fcoe_select_cpu(व्योम)
अणु
	अटल अचिन्हित पूर्णांक selected_cpu;

	selected_cpu = cpumask_next(selected_cpu, cpu_online_mask);
	अगर (selected_cpu >= nr_cpu_ids)
		selected_cpu = cpumask_first(cpu_online_mask);

	वापस selected_cpu;
पूर्ण

/**
 * fcoe_rcv() - Receive packets from a net device
 * @skb:    The received packet
 * @netdev: The net device that the packet was received on
 * @ptype:  The packet type context
 * @olddev: The last device net device
 *
 * This routine is called by NET_RX_SOFTIRQ. It receives a packet, builds a
 * FC frame and passes the frame to libfc.
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *netdev,
	     काष्ठा packet_type *ptype, काष्ठा net_device *olddev)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fcoe_rcv_info *fr;
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	काष्ठा fc_frame_header *fh;
	काष्ठा fcoe_percpu_s *fps;
	काष्ठा ethhdr *eh;
	अचिन्हित पूर्णांक cpu;

	fcoe = container_of(ptype, काष्ठा fcoe_पूर्णांकerface, fcoe_packet_type);
	ctlr = fcoe_to_ctlr(fcoe);
	lport = ctlr->lp;
	अगर (unlikely(!lport)) अणु
		FCOE_NETDEV_DBG(netdev, "Cannot find hba structure\n");
		जाओ err2;
	पूर्ण
	अगर (!lport->link_up)
		जाओ err2;

	FCOE_NETDEV_DBG(netdev,
			"skb_info: len:%d data_len:%d head:%p data:%p tail:%p end:%p sum:%d dev:%s\n",
			skb->len, skb->data_len, skb->head, skb->data,
			skb_tail_poपूर्णांकer(skb), skb_end_poपूर्णांकer(skb),
			skb->csum, skb->dev ? skb->dev->name : "<NULL>");


	skb = skb_share_check(skb, GFP_ATOMIC);

	अगर (skb == शून्य)
		वापस NET_RX_DROP;

	eh = eth_hdr(skb);

	अगर (is_fip_mode(ctlr) &&
	    !ether_addr_equal(eh->h_source, ctlr->dest_addr)) अणु
		FCOE_NETDEV_DBG(netdev, "wrong source mac address:%pM\n",
				eh->h_source);
		जाओ err;
	पूर्ण

	/*
	 * Check क्रम minimum frame length, and make sure required FCoE
	 * and FC headers are pulled पूर्णांकo the linear data area.
	 */
	अगर (unlikely((skb->len < FCOE_MIN_FRAME) ||
		     !pskb_may_pull(skb, FCOE_HEADER_LEN)))
		जाओ err;

	skb_set_transport_header(skb, माप(काष्ठा fcoe_hdr));
	fh = (काष्ठा fc_frame_header *) skb_transport_header(skb);

	अगर (ntoh24(&eh->h_dest[3]) != ntoh24(fh->fh_d_id)) अणु
		FCOE_NETDEV_DBG(netdev, "FC frame d_id mismatch with MAC:%pM\n",
				eh->h_dest);
		जाओ err;
	पूर्ण

	fr = fcoe_dev_from_skb(skb);
	fr->fr_dev = lport;

	/*
	 * In हाल the incoming frame's exchange is originated from
	 * the initiator, then received frame's exchange id is ANDed
	 * with fc_cpu_mask bits to get the same cpu on which exchange
	 * was originated, otherwise select cpu using rx exchange id
	 * or fcoe_select_cpu().
	 */
	अगर (ntoh24(fh->fh_f_ctl) & FC_FC_EX_CTX)
		cpu = ntohs(fh->fh_ox_id) & fc_cpu_mask;
	अन्यथा अणु
		अगर (ntohs(fh->fh_rx_id) == FC_XID_UNKNOWN)
			cpu = fcoe_select_cpu();
		अन्यथा
			cpu = ntohs(fh->fh_rx_id) & fc_cpu_mask;
	पूर्ण

	अगर (cpu >= nr_cpu_ids)
		जाओ err;

	fps = &per_cpu(fcoe_percpu, cpu);
	spin_lock(&fps->fcoe_rx_list.lock);
	/*
	 * We now have a valid CPU that we're targeting क्रम
	 * this skb. We also have this receive thपढ़ो locked,
	 * so we're free to queue skbs into it's queue.
	 */

	/*
	 * Note: We used to have a set of conditions under which we would
	 * call fcoe_recv_frame directly, rather than queuing to the rx list
	 * as it could save a few cycles, but करोing so is prohibited, as
	 * fcoe_recv_frame has several paths that may sleep, which is क्रमbidden
	 * in softirq context.
	 */
	__skb_queue_tail(&fps->fcoe_rx_list, skb);
	schedule_work_on(cpu, &fps->work);
	spin_unlock(&fps->fcoe_rx_list.lock);

	वापस NET_RX_SUCCESS;
err:
	per_cpu_ptr(lport->stats, get_cpu())->ErrorFrames++;
	put_cpu();
err2:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

/**
 * fcoe_alloc_paged_crc_eof() - Allocate a page to be used क्रम the trailer CRC
 * @skb:  The packet to be transmitted
 * @tlen: The total length of the trailer
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_alloc_paged_crc_eof(काष्ठा sk_buff *skb, पूर्णांक tlen)
अणु
	काष्ठा fcoe_percpu_s *fps;
	पूर्णांक rc;

	fps = &get_cpu_var(fcoe_percpu);
	rc = fcoe_get_paged_crc_eof(skb, tlen, fps);
	put_cpu_var(fcoe_percpu);

	वापस rc;
पूर्ण

/**
 * fcoe_xmit() - Transmit a FCoE frame
 * @lport: The local port that the frame is to be transmitted क्रम
 * @fp:	   The frame to be transmitted
 *
 * Return: 0 क्रम success
 */
अटल पूर्णांक fcoe_xmit(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	पूर्णांक wlen;
	u32 crc;
	काष्ठा ethhdr *eh;
	काष्ठा fcoe_crc_eof *cp;
	काष्ठा sk_buff *skb;
	काष्ठा fc_stats *stats;
	काष्ठा fc_frame_header *fh;
	अचिन्हित पूर्णांक hlen;		/* header length implies the version */
	अचिन्हित पूर्णांक tlen;		/* trailer length */
	अचिन्हित पूर्णांक elen;		/* eth header, may include vlan */
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा fcoe_पूर्णांकerface *fcoe = port->priv;
	काष्ठा fcoe_ctlr *ctlr = fcoe_to_ctlr(fcoe);
	u8 sof, eof;
	काष्ठा fcoe_hdr *hp;

	WARN_ON((fr_len(fp) % माप(u32)) != 0);

	fh = fc_frame_header_get(fp);
	skb = fp_skb(fp);
	wlen = skb->len / FCOE_WORD_TO_BYTE;

	अगर (!lport->link_up) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (unlikely(fh->fh_type == FC_TYPE_ELS) &&
	    fcoe_ctlr_els_send(ctlr, lport, skb))
		वापस 0;

	sof = fr_sof(fp);
	eof = fr_eof(fp);

	elen = माप(काष्ठा ethhdr);
	hlen = माप(काष्ठा fcoe_hdr);
	tlen = माप(काष्ठा fcoe_crc_eof);
	wlen = (skb->len - tlen + माप(crc)) / FCOE_WORD_TO_BYTE;

	/* crc offload */
	अगर (likely(lport->crc_offload)) अणु
		skb->ip_summed = CHECKSUM_PARTIAL;
		skb->csum_start = skb_headroom(skb);
		skb->csum_offset = skb->len;
		crc = 0;
	पूर्ण अन्यथा अणु
		skb->ip_summed = CHECKSUM_NONE;
		crc = fcoe_fc_crc(fp);
	पूर्ण

	/* copy port crc and eof to the skb buff */
	अगर (skb_is_nonlinear(skb)) अणु
		skb_frag_t *frag;
		अगर (fcoe_alloc_paged_crc_eof(skb, tlen)) अणु
			kमुक्त_skb(skb);
			वापस -ENOMEM;
		पूर्ण
		frag = &skb_shinfo(skb)->frags[skb_shinfo(skb)->nr_frags - 1];
		cp = kmap_atomic(skb_frag_page(frag)) + skb_frag_off(frag);
	पूर्ण अन्यथा अणु
		cp = skb_put(skb, tlen);
	पूर्ण

	स_रखो(cp, 0, माप(*cp));
	cp->fcoe_eof = eof;
	cp->fcoe_crc32 = cpu_to_le32(~crc);

	अगर (skb_is_nonlinear(skb)) अणु
		kunmap_atomic(cp);
		cp = शून्य;
	पूर्ण

	/* adjust skb network/transport offsets to match mac/fcoe/port */
	skb_push(skb, elen + hlen);
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb->mac_len = elen;
	skb->protocol = htons(ETH_P_FCOE);
	skb->priority = fcoe->priority;

	अगर (is_vlan_dev(fcoe->netdev) &&
	    fcoe->realdev->features & NETIF_F_HW_VLAN_CTAG_TX) अणु
		/* must set skb->dev beक्रमe calling vlan_put_tag */
		skb->dev = fcoe->realdev;
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       vlan_dev_vlan_id(fcoe->netdev));
	पूर्ण अन्यथा
		skb->dev = fcoe->netdev;

	/* fill up mac and fcoe headers */
	eh = eth_hdr(skb);
	eh->h_proto = htons(ETH_P_FCOE);
	स_नकल(eh->h_dest, ctlr->dest_addr, ETH_ALEN);
	अगर (ctlr->map_dest)
		स_नकल(eh->h_dest + 3, fh->fh_d_id, 3);

	अगर (unlikely(ctlr->flogi_oxid != FC_XID_UNKNOWN))
		स_नकल(eh->h_source, ctlr->ctl_src_addr, ETH_ALEN);
	अन्यथा
		स_नकल(eh->h_source, port->data_src_addr, ETH_ALEN);

	hp = (काष्ठा fcoe_hdr *)(eh + 1);
	स_रखो(hp, 0, माप(*hp));
	अगर (FC_FCOE_VER)
		FC_FCOE_ENCAPS_VER(hp, FC_FCOE_VER);
	hp->fcoe_sof = sof;

	/* fcoe lso, mss is in max_payload which is non-zero क्रम FCP data */
	अगर (lport->seq_offload && fr_max_payload(fp)) अणु
		skb_shinfo(skb)->gso_type = SKB_GSO_FCOE;
		skb_shinfo(skb)->gso_size = fr_max_payload(fp);
	पूर्ण अन्यथा अणु
		skb_shinfo(skb)->gso_type = 0;
		skb_shinfo(skb)->gso_size = 0;
	पूर्ण
	/* update tx stats: regardless अगर LLD fails */
	stats = per_cpu_ptr(lport->stats, get_cpu());
	stats->TxFrames++;
	stats->TxWords += wlen;
	put_cpu();

	/* send करोwn to lld */
	fr_dev(fp) = lport;
	fcoe_port_send(port, skb);
	वापस 0;
पूर्ण

/**
 * fcoe_filter_frames() - filter out bad fcoe frames, i.e. bad CRC
 * @lport: The local port the frame was received on
 * @fp:	   The received frame
 *
 * Return: 0 on passing filtering checks
 */
अटल अंतरभूत पूर्णांक fcoe_filter_frames(काष्ठा fc_lport *lport,
				     काष्ठा fc_frame *fp)
अणु
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	काष्ठा fc_frame_header *fh;
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)fp;
	काष्ठा fc_stats *stats;

	/*
	 * We only check CRC अगर no offload is available and अगर it is
	 * it's solicited data, in which हाल, the FCP layer would
	 * check it during the copy.
	 */
	अगर (lport->crc_offload && skb->ip_summed == CHECKSUM_UNNECESSARY)
		fr_flags(fp) &= ~FCPHF_CRC_UNCHECKED;
	अन्यथा
		fr_flags(fp) |= FCPHF_CRC_UNCHECKED;

	fh = fc_frame_header_get(fp);
	अगर (fh->fh_r_ctl == FC_RCTL_DD_SOL_DATA && fh->fh_type == FC_TYPE_FCP)
		वापस 0;

	fcoe = ((काष्ठा fcoe_port *)lport_priv(lport))->priv;
	ctlr = fcoe_to_ctlr(fcoe);
	अगर (is_fip_mode(ctlr) && fc_frame_payload_op(fp) == ELS_LOGO &&
	    ntoh24(fh->fh_s_id) == FC_FID_FLOGI) अणु
		FCOE_DBG("fcoe: dropping FCoE lport LOGO in fip mode\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!(fr_flags(fp) & FCPHF_CRC_UNCHECKED) ||
	    le32_to_cpu(fr_crc(fp)) == ~crc32(~0, skb->data, skb->len)) अणु
		fr_flags(fp) &= ~FCPHF_CRC_UNCHECKED;
		वापस 0;
	पूर्ण

	stats = per_cpu_ptr(lport->stats, get_cpu());
	stats->InvalidCRCCount++;
	अगर (stats->InvalidCRCCount < 5)
		prपूर्णांकk(KERN_WARNING "fcoe: dropping frame with CRC error\n");
	put_cpu();
	वापस -EINVAL;
पूर्ण

/**
 * fcoe_recv_frame() - process a single received frame
 * @skb: frame to process
 */
अटल व्योम fcoe_recv_frame(काष्ठा sk_buff *skb)
अणु
	u32 fr_len;
	काष्ठा fc_lport *lport;
	काष्ठा fcoe_rcv_info *fr;
	काष्ठा fc_stats *stats;
	काष्ठा fcoe_crc_eof crc_eof;
	काष्ठा fc_frame *fp;
	काष्ठा fcoe_hdr *hp;

	fr = fcoe_dev_from_skb(skb);
	lport = fr->fr_dev;
	अगर (unlikely(!lport)) अणु
		FCOE_NETDEV_DBG(skb->dev, "NULL lport in skb\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	FCOE_NETDEV_DBG(skb->dev,
			"skb_info: len:%d data_len:%d head:%p data:%p tail:%p end:%p sum:%d dev:%s\n",
			skb->len, skb->data_len,
			skb->head, skb->data, skb_tail_poपूर्णांकer(skb),
			skb_end_poपूर्णांकer(skb), skb->csum,
			skb->dev ? skb->dev->name : "<NULL>");

	skb_linearize(skb); /* check क्रम skb_is_nonlinear is within skb_linearize */

	/*
	 * Frame length checks and setting up the header poपूर्णांकers
	 * was करोne in fcoe_rcv alपढ़ोy.
	 */
	hp = (काष्ठा fcoe_hdr *) skb_network_header(skb);

	stats = per_cpu_ptr(lport->stats, get_cpu());
	अगर (unlikely(FC_FCOE_DECAPS_VER(hp) != FC_FCOE_VER)) अणु
		अगर (stats->ErrorFrames < 5)
			prपूर्णांकk(KERN_WARNING "fcoe: FCoE version "
			       "mismatch: The frame has "
			       "version %x, but the "
			       "initiator supports version "
			       "%x\n", FC_FCOE_DECAPS_VER(hp),
			       FC_FCOE_VER);
		जाओ drop;
	पूर्ण

	skb_pull(skb, माप(काष्ठा fcoe_hdr));
	fr_len = skb->len - माप(काष्ठा fcoe_crc_eof);

	stats->RxFrames++;
	stats->RxWords += fr_len / FCOE_WORD_TO_BYTE;

	fp = (काष्ठा fc_frame *)skb;
	fc_frame_init(fp);
	fr_dev(fp) = lport;
	fr_sof(fp) = hp->fcoe_sof;

	/* Copy out the CRC and खातापूर्ण trailer क्रम access */
	अगर (skb_copy_bits(skb, fr_len, &crc_eof, माप(crc_eof)))
		जाओ drop;
	fr_eof(fp) = crc_eof.fcoe_eof;
	fr_crc(fp) = crc_eof.fcoe_crc32;
	अगर (pskb_trim(skb, fr_len))
		जाओ drop;

	अगर (!fcoe_filter_frames(lport, fp)) अणु
		put_cpu();
		fc_exch_recv(lport, fp);
		वापस;
	पूर्ण
drop:
	stats->ErrorFrames++;
	put_cpu();
	kमुक्त_skb(skb);
पूर्ण

/**
 * fcoe_receive_work() - The per-CPU worker
 * @work: The work काष्ठा
 *
 */
अटल व्योम fcoe_receive_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fcoe_percpu_s *p;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head पंचांगp;

	p = container_of(work, काष्ठा fcoe_percpu_s, work);
	skb_queue_head_init(&पंचांगp);

	spin_lock_bh(&p->fcoe_rx_list.lock);
	skb_queue_splice_init(&p->fcoe_rx_list, &पंचांगp);
	spin_unlock_bh(&p->fcoe_rx_list.lock);

	अगर (!skb_queue_len(&पंचांगp))
		वापस;

	जबतक ((skb = __skb_dequeue(&पंचांगp)))
		fcoe_recv_frame(skb);
पूर्ण

/**
 * fcoe_dev_setup() - Setup the link change notअगरication पूर्णांकerface
 */
अटल व्योम fcoe_dev_setup(व्योम)
अणु
	रेजिस्टर_dcbevent_notअगरier(&dcb_notअगरier);
	रेजिस्टर_netdevice_notअगरier(&fcoe_notअगरier);
पूर्ण

/**
 * fcoe_dev_cleanup() - Cleanup the link change notअगरication पूर्णांकerface
 */
अटल व्योम fcoe_dev_cleanup(व्योम)
अणु
	unरेजिस्टर_dcbevent_notअगरier(&dcb_notअगरier);
	unरेजिस्टर_netdevice_notअगरier(&fcoe_notअगरier);
पूर्ण

अटल काष्ठा fcoe_पूर्णांकerface *
fcoe_hostlist_lookup_realdev_port(काष्ठा net_device *netdev)
अणु
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	काष्ठा net_device *real_dev;

	list_क्रम_each_entry(fcoe, &fcoe_hostlist, list) अणु
		अगर (is_vlan_dev(fcoe->netdev))
			real_dev = vlan_dev_real_dev(fcoe->netdev);
		अन्यथा
			real_dev = fcoe->netdev;

		अगर (netdev == real_dev)
			वापस fcoe;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक fcoe_dcb_app_notअगरication(काष्ठा notअगरier_block *notअगरier,
				     uदीर्घ event, व्योम *ptr)
अणु
	काष्ठा dcb_app_type *entry = ptr;
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	काष्ठा net_device *netdev;
	पूर्णांक prio;

	अगर (entry->app.selector != DCB_APP_IDTYPE_ETHTYPE)
		वापस NOTIFY_OK;

	netdev = dev_get_by_index(&init_net, entry->अगरindex);
	अगर (!netdev)
		वापस NOTIFY_OK;

	fcoe = fcoe_hostlist_lookup_realdev_port(netdev);
	dev_put(netdev);
	अगर (!fcoe)
		वापस NOTIFY_OK;

	ctlr = fcoe_to_ctlr(fcoe);

	अगर (entry->dcbx & DCB_CAP_DCBX_VER_CEE)
		prio = ffs(entry->app.priority) - 1;
	अन्यथा
		prio = entry->app.priority;

	अगर (prio < 0)
		वापस NOTIFY_OK;

	अगर (entry->app.protocol == ETH_P_FIP ||
	    entry->app.protocol == ETH_P_FCOE)
		ctlr->priority = prio;

	अगर (entry->app.protocol == ETH_P_FCOE)
		fcoe->priority = prio;

	वापस NOTIFY_OK;
पूर्ण

/**
 * fcoe_device_notअगरication() - Handler क्रम net device events
 * @notअगरier: The context of the notअगरication
 * @event:    The type of event
 * @ptr:      The net device that the event was on
 *
 * This function is called by the Ethernet driver in हाल of link change event.
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_device_notअगरication(काष्ठा notअगरier_block *notअगरier,
				    uदीर्घ event, व्योम *ptr)
अणु
	काष्ठा fcoe_ctlr_device *cdev;
	काष्ठा fc_lport *lport = शून्य;
	काष्ठा net_device *netdev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	काष्ठा fc_stats *stats;
	u32 link_possible = 1;
	u32 mfs;
	पूर्णांक rc = NOTIFY_OK;

	list_क्रम_each_entry(fcoe, &fcoe_hostlist, list) अणु
		अगर (fcoe->netdev == netdev) अणु
			ctlr = fcoe_to_ctlr(fcoe);
			lport = ctlr->lp;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!lport) अणु
		rc = NOTIFY_DONE;
		जाओ out;
	पूर्ण

	चयन (event) अणु
	हाल NETDEV_DOWN:
	हाल NETDEV_GOING_DOWN:
		link_possible = 0;
		अवरोध;
	हाल NETDEV_UP:
	हाल NETDEV_CHANGE:
		अवरोध;
	हाल NETDEV_CHANGEMTU:
		अगर (netdev->features & NETIF_F_FCOE_MTU)
			अवरोध;
		mfs = netdev->mtu - (माप(काष्ठा fcoe_hdr) +
				     माप(काष्ठा fcoe_crc_eof));
		अगर (mfs >= FC_MIN_MAX_FRAME)
			fc_set_mfs(lport, mfs);
		अवरोध;
	हाल NETDEV_REGISTER:
		अवरोध;
	हाल NETDEV_UNREGISTER:
		list_del(&fcoe->list);
		fcoe_vport_हटाओ(lport);
		mutex_lock(&fcoe_config_mutex);
		fcoe_अगर_destroy(lport);
		अगर (!fcoe->हटाओd)
			fcoe_पूर्णांकerface_हटाओ(fcoe);
		fcoe_पूर्णांकerface_cleanup(fcoe);
		mutex_unlock(&fcoe_config_mutex);
		fcoe_ctlr_device_delete(fcoe_ctlr_to_ctlr_dev(ctlr));
		जाओ out;
	हाल NETDEV_FEAT_CHANGE:
		fcoe_netdev_features_change(lport, netdev);
		अवरोध;
	शेष:
		FCOE_NETDEV_DBG(netdev, "Unknown event %ld "
				"from netdev netlink\n", event);
	पूर्ण

	fcoe_link_speed_update(lport);

	cdev = fcoe_ctlr_to_ctlr_dev(ctlr);

	अगर (link_possible && !fcoe_link_ok(lport)) अणु
		चयन (cdev->enabled) अणु
		हाल FCOE_CTLR_DISABLED:
			pr_info("Link up while interface is disabled.\n");
			अवरोध;
		हाल FCOE_CTLR_ENABLED:
		हाल FCOE_CTLR_UNUSED:
			fcoe_ctlr_link_up(ctlr);
		पूर्ण
	पूर्ण अन्यथा अगर (fcoe_ctlr_link_करोwn(ctlr)) अणु
		चयन (cdev->enabled) अणु
		हाल FCOE_CTLR_DISABLED:
			pr_info("Link down while interface is disabled.\n");
			अवरोध;
		हाल FCOE_CTLR_ENABLED:
		हाल FCOE_CTLR_UNUSED:
			stats = per_cpu_ptr(lport->stats, get_cpu());
			stats->LinkFailureCount++;
			put_cpu();
			fcoe_clean_pending_queue(lport);
		पूर्ण
	पूर्ण
out:
	वापस rc;
पूर्ण

/**
 * fcoe_disable() - Disables a FCoE पूर्णांकerface
 * @netdev  : The net_device object the Ethernet पूर्णांकerface to create on
 *
 * Called from fcoe transport.
 *
 * Returns: 0 क्रम success
 *
 * Deprecated: use fcoe_ctlr_enabled()
 */
अटल पूर्णांक fcoe_disable(काष्ठा net_device *netdev)
अणु
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	पूर्णांक rc = 0;

	mutex_lock(&fcoe_config_mutex);

	rtnl_lock();
	fcoe = fcoe_hostlist_lookup_port(netdev);
	rtnl_unlock();

	अगर (fcoe) अणु
		ctlr = fcoe_to_ctlr(fcoe);
		fcoe_ctlr_link_करोwn(ctlr);
		fcoe_clean_pending_queue(ctlr->lp);
	पूर्ण अन्यथा
		rc = -ENODEV;

	mutex_unlock(&fcoe_config_mutex);
	वापस rc;
पूर्ण

/**
 * fcoe_enable() - Enables a FCoE पूर्णांकerface
 * @netdev  : The net_device object the Ethernet पूर्णांकerface to create on
 *
 * Called from fcoe transport.
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_enable(काष्ठा net_device *netdev)
अणु
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	पूर्णांक rc = 0;

	mutex_lock(&fcoe_config_mutex);
	rtnl_lock();
	fcoe = fcoe_hostlist_lookup_port(netdev);
	rtnl_unlock();

	अगर (!fcoe) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	ctlr = fcoe_to_ctlr(fcoe);

	अगर (!fcoe_link_ok(ctlr->lp))
		fcoe_ctlr_link_up(ctlr);

out:
	mutex_unlock(&fcoe_config_mutex);
	वापस rc;
पूर्ण

/**
 * fcoe_ctlr_enabled() - Enable or disable an FCoE Controller
 * @cdev: The FCoE Controller that is being enabled or disabled
 *
 * fcoe_sysfs will ensure that the state of 'enabled' has
 * changed, so no checking is necessary here. This routine simply
 * calls fcoe_enable or fcoe_disable, both of which are deprecated.
 * When those routines are हटाओd the functionality can be merged
 * here.
 */
अटल पूर्णांक fcoe_ctlr_enabled(काष्ठा fcoe_ctlr_device *cdev)
अणु
	काष्ठा fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(cdev);
	काष्ठा fc_lport *lport = ctlr->lp;
	काष्ठा net_device *netdev = fcoe_netdev(lport);

	चयन (cdev->enabled) अणु
	हाल FCOE_CTLR_ENABLED:
		वापस fcoe_enable(netdev);
	हाल FCOE_CTLR_DISABLED:
		वापस fcoe_disable(netdev);
	हाल FCOE_CTLR_UNUSED:
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

/**
 * fcoe_ctlr_mode() - Switch FIP mode
 * @ctlr_dev: The FCoE Controller that is being modअगरied
 *
 * When the FIP mode has been changed we need to update
 * the multicast addresses to ensure we get the correct
 * frames.
 */
अटल व्योम fcoe_ctlr_mode(काष्ठा fcoe_ctlr_device *ctlr_dev)
अणु
	काष्ठा fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(ctlr_dev);
	काष्ठा fcoe_पूर्णांकerface *fcoe = fcoe_ctlr_priv(ctlr);

	अगर (ctlr_dev->mode == FIP_CONN_TYPE_VN2VN &&
	    ctlr->mode != FIP_MODE_VN2VN) अणु
		dev_mc_del(fcoe->netdev, FIP_ALL_ENODE_MACS);
		dev_mc_add(fcoe->netdev, FIP_ALL_VN2VN_MACS);
		dev_mc_add(fcoe->netdev, FIP_ALL_P2P_MACS);
	पूर्ण अन्यथा अगर (ctlr->mode != FIP_MODE_FABRIC) अणु
		dev_mc_del(fcoe->netdev, FIP_ALL_VN2VN_MACS);
		dev_mc_del(fcoe->netdev, FIP_ALL_P2P_MACS);
		dev_mc_add(fcoe->netdev, FIP_ALL_ENODE_MACS);
	पूर्ण
	fcoe_ctlr_set_fip_mode(ctlr_dev);
पूर्ण

/**
 * fcoe_destroy() - Destroy a FCoE पूर्णांकerface
 * @netdev  : The net_device object the Ethernet पूर्णांकerface to create on
 *
 * Called from fcoe transport
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_destroy(काष्ठा net_device *netdev)
अणु
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	काष्ठा fc_lport *lport;
	काष्ठा fcoe_port *port;
	पूर्णांक rc = 0;

	mutex_lock(&fcoe_config_mutex);
	rtnl_lock();
	fcoe = fcoe_hostlist_lookup_port(netdev);
	अगर (!fcoe) अणु
		rc = -ENODEV;
		जाओ out_nodev;
	पूर्ण
	ctlr = fcoe_to_ctlr(fcoe);
	lport = ctlr->lp;
	port = lport_priv(lport);
	list_del(&fcoe->list);
	queue_work(fcoe_wq, &port->destroy_work);
out_nodev:
	rtnl_unlock();
	mutex_unlock(&fcoe_config_mutex);
	वापस rc;
पूर्ण

/**
 * fcoe_destroy_work() - Destroy a FCoE port in a deferred work context
 * @work: Handle to the FCoE port to be destroyed
 */
अटल व्योम fcoe_destroy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fcoe_ctlr_device *cdev;
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_port *port;
	काष्ठा fcoe_पूर्णांकerface *fcoe;

	port = container_of(work, काष्ठा fcoe_port, destroy_work);

	fcoe_vport_हटाओ(port->lport);

	mutex_lock(&fcoe_config_mutex);

	fcoe = port->priv;
	ctlr = fcoe_to_ctlr(fcoe);
	cdev = fcoe_ctlr_to_ctlr_dev(ctlr);

	rtnl_lock();
	fcoe_अगर_destroy(port->lport);
	अगर (!fcoe->हटाओd)
		fcoe_पूर्णांकerface_हटाओ(fcoe);
	rtnl_unlock();
	fcoe_पूर्णांकerface_cleanup(fcoe);

	mutex_unlock(&fcoe_config_mutex);

	fcoe_ctlr_device_delete(cdev);
पूर्ण

/**
 * fcoe_match() - Check अगर the FCoE is supported on the given netdevice
 * @netdev  : The net_device object the Ethernet पूर्णांकerface to create on
 *
 * Called from fcoe transport.
 *
 * Returns: always वापसs true as this is the शेष FCoE transport,
 * i.e., support all netdevs.
 */
अटल bool fcoe_match(काष्ठा net_device *netdev)
अणु
	वापस true;
पूर्ण

/**
 * fcoe_dcb_create() - Initialize DCB attributes and hooks
 * @fcoe:   The new FCoE पूर्णांकerface
 */
अटल व्योम fcoe_dcb_create(काष्ठा fcoe_पूर्णांकerface *fcoe)
अणु
	पूर्णांक ctlr_prio = TC_PRIO_BESTEFFORT;
	पूर्णांक fcoe_prio = TC_PRIO_INTERACTIVE;
	काष्ठा fcoe_ctlr *ctlr = fcoe_to_ctlr(fcoe);
#अगर_घोषित CONFIG_DCB
	पूर्णांक dcbx;
	u8 fup, up;
	काष्ठा net_device *netdev = fcoe->realdev;
	काष्ठा dcb_app app = अणु
				.priority = 0,
				.protocol = ETH_P_FCOE
			     पूर्ण;

	/* setup DCB priority attributes. */
	अगर (netdev && netdev->dcbnl_ops && netdev->dcbnl_ops->getdcbx) अणु
		dcbx = netdev->dcbnl_ops->getdcbx(netdev);

		अगर (dcbx & DCB_CAP_DCBX_VER_IEEE) अणु
			app.selector = IEEE_8021QAZ_APP_SEL_ETHERTYPE;
			up = dcb_ieee_getapp_mask(netdev, &app);
			app.protocol = ETH_P_FIP;
			fup = dcb_ieee_getapp_mask(netdev, &app);
		पूर्ण अन्यथा अणु
			app.selector = DCB_APP_IDTYPE_ETHTYPE;
			up = dcb_getapp(netdev, &app);
			app.protocol = ETH_P_FIP;
			fup = dcb_getapp(netdev, &app);
		पूर्ण

		fcoe_prio = ffs(up) ? ffs(up) - 1 : 0;
		ctlr_prio = ffs(fup) ? ffs(fup) - 1 : fcoe_prio;
	पूर्ण
#पूर्ण_अगर
	fcoe->priority = fcoe_prio;
	ctlr->priority = ctlr_prio;
पूर्ण

क्रमागत fcoe_create_link_state अणु
	FCOE_CREATE_LINK_DOWN,
	FCOE_CREATE_LINK_UP,
पूर्ण;

/**
 * _fcoe_create() - (पूर्णांकernal) Create a fcoe पूर्णांकerface
 * @netdev  :   The net_device object the Ethernet पूर्णांकerface to create on
 * @fip_mode:   The FIP mode क्रम this creation
 * @link_state: The ctlr link state on creation
 *
 * Called from either the libfcoe 'create' module parameter
 * via fcoe_create or from fcoe_syfs's ctlr_create file.
 *
 * libfcoe's 'create' module parameter is deprecated so some
 * consolidation of code can be करोne when that पूर्णांकerface is
 * हटाओd.
 */
अटल पूर्णांक _fcoe_create(काष्ठा net_device *netdev, क्रमागत fip_mode fip_mode,
			क्रमागत fcoe_create_link_state link_state)
अणु
	पूर्णांक rc = 0;
	काष्ठा fcoe_ctlr_device *ctlr_dev;
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	काष्ठा fc_lport *lport;

	mutex_lock(&fcoe_config_mutex);
	rtnl_lock();

	/* look क्रम existing lport */
	अगर (fcoe_hostlist_lookup(netdev)) अणु
		rc = -EEXIST;
		जाओ out_nodev;
	पूर्ण

	fcoe = fcoe_पूर्णांकerface_create(netdev, fip_mode);
	अगर (IS_ERR(fcoe)) अणु
		rc = PTR_ERR(fcoe);
		जाओ out_nodev;
	पूर्ण

	ctlr = fcoe_to_ctlr(fcoe);
	ctlr_dev = fcoe_ctlr_to_ctlr_dev(ctlr);
	lport = fcoe_अगर_create(fcoe, &ctlr_dev->dev, 0);
	अगर (IS_ERR(lport)) अणु
		prपूर्णांकk(KERN_ERR "fcoe: Failed to create interface (%s)\n",
		       netdev->name);
		rc = -EIO;
		अगर (!fcoe->हटाओd)
			fcoe_पूर्णांकerface_हटाओ(fcoe);
		rtnl_unlock();
		fcoe_पूर्णांकerface_cleanup(fcoe);
		mutex_unlock(&fcoe_config_mutex);
		fcoe_ctlr_device_delete(ctlr_dev);
		वापस rc;
	पूर्ण

	/* Make this the "master" N_Port */
	ctlr->lp = lport;

	/* setup DCB priority attributes. */
	fcoe_dcb_create(fcoe);

	/* start FIP Discovery and FLOGI */
	lport->boot_समय = jअगरfies;
	fc_fabric_login(lport);

	/*
	 * If the fcoe_ctlr_device is to be set to DISABLED
	 * it must be करोne after the lport is added to the
	 * hostlist, but beक्रमe the rtnl_lock is released.
	 * This is because the rtnl_lock protects the
	 * hostlist that fcoe_device_notअगरication uses. If
	 * the FCoE Controller is पूर्णांकended to be created
	 * DISABLED then 'enabled' needs to be considered
	 * handling link events. 'enabled' must be set
	 * beक्रमe the lport can be found in the hostlist
	 * when a link up event is received.
	 */
	अगर (link_state == FCOE_CREATE_LINK_UP)
		ctlr_dev->enabled = FCOE_CTLR_ENABLED;
	अन्यथा
		ctlr_dev->enabled = FCOE_CTLR_DISABLED;

	अगर (link_state == FCOE_CREATE_LINK_UP &&
	    !fcoe_link_ok(lport)) अणु
		rtnl_unlock();
		fcoe_ctlr_link_up(ctlr);
		mutex_unlock(&fcoe_config_mutex);
		वापस rc;
	पूर्ण

out_nodev:
	rtnl_unlock();
	mutex_unlock(&fcoe_config_mutex);

	वापस rc;
पूर्ण

/**
 * fcoe_create() - Create a fcoe पूर्णांकerface
 * @netdev  : The net_device object the Ethernet पूर्णांकerface to create on
 * @fip_mode: The FIP mode क्रम this creation
 *
 * Called from fcoe transport
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_create(काष्ठा net_device *netdev, क्रमागत fip_mode fip_mode)
अणु
	वापस _fcoe_create(netdev, fip_mode, FCOE_CREATE_LINK_UP);
पूर्ण

/**
 * fcoe_ctlr_alloc() - Allocate a fcoe पूर्णांकerface from fcoe_sysfs
 * @netdev: The net_device to be used by the allocated FCoE Controller
 *
 * This routine is called from fcoe_sysfs. It will start the fcoe_ctlr
 * in a link_करोwn state. The allows the user an opportunity to configure
 * the FCoE Controller from sysfs beक्रमe enabling the FCoE Controller.
 *
 * Creating in with this routine starts the FCoE Controller in Fabric
 * mode. The user can change to VN2VN or another mode beक्रमe enabling.
 */
अटल पूर्णांक fcoe_ctlr_alloc(काष्ठा net_device *netdev)
अणु
	वापस _fcoe_create(netdev, FIP_MODE_FABRIC,
			    FCOE_CREATE_LINK_DOWN);
पूर्ण

/**
 * fcoe_link_ok() - Check अगर the link is OK क्रम a local port
 * @lport: The local port to check link on
 *
 * Returns: 0 अगर link is UP and OK, -1 अगर not
 *
 */
अटल पूर्णांक fcoe_link_ok(काष्ठा fc_lport *lport)
अणु
	काष्ठा net_device *netdev = fcoe_netdev(lport);

	अगर (netअगर_oper_up(netdev))
		वापस 0;
	वापस -1;
पूर्ण

/**
 * fcoe_percpu_clean() - Clear all pending skbs क्रम an local port
 * @lport: The local port whose skbs are to be cleared
 *
 * Must be called with fcoe_create_mutex held to single-thपढ़ो completion.
 *
 * This flushes the pending skbs by flush the work item क्रम each CPU. The work
 * item on each possible CPU is flushed because we may have used the per-CPU
 * काष्ठा of an offline CPU.
 */
अटल व्योम fcoe_percpu_clean(काष्ठा fc_lport *lport)
अणु
	काष्ठा fcoe_percpu_s *pp;
	अचिन्हित पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		pp = &per_cpu(fcoe_percpu, cpu);

		flush_work(&pp->work);
	पूर्ण
पूर्ण

/**
 * fcoe_reset() - Reset a local port
 * @shost: The SCSI host associated with the local port to be reset
 *
 * Returns: Always 0 (वापस value required by FC transport ढाँचा)
 */
अटल पूर्णांक fcoe_reset(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा fc_lport *lport = shost_priv(shost);
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा fcoe_पूर्णांकerface *fcoe = port->priv;
	काष्ठा fcoe_ctlr *ctlr = fcoe_to_ctlr(fcoe);
	काष्ठा fcoe_ctlr_device *cdev = fcoe_ctlr_to_ctlr_dev(ctlr);

	fcoe_ctlr_link_करोwn(ctlr);
	fcoe_clean_pending_queue(ctlr->lp);

	अगर (cdev->enabled != FCOE_CTLR_DISABLED &&
	    !fcoe_link_ok(ctlr->lp))
		fcoe_ctlr_link_up(ctlr);
	वापस 0;
पूर्ण

/**
 * fcoe_hostlist_lookup_port() - Find the FCoE पूर्णांकerface associated with a net device
 * @netdev: The net device used as a key
 *
 * Locking: Must be called with the RNL mutex held.
 *
 * Returns: शून्य or the FCoE पूर्णांकerface
 */
अटल काष्ठा fcoe_पूर्णांकerface *
fcoe_hostlist_lookup_port(स्थिर काष्ठा net_device *netdev)
अणु
	काष्ठा fcoe_पूर्णांकerface *fcoe;

	list_क्रम_each_entry(fcoe, &fcoe_hostlist, list) अणु
		अगर (fcoe->netdev == netdev)
			वापस fcoe;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * fcoe_hostlist_lookup() - Find the local port associated with a
 *			    given net device
 * @netdev: The netdevice used as a key
 *
 * Locking: Must be called with the RTNL mutex held
 *
 * Returns: शून्य or the local port
 */
अटल काष्ठा fc_lport *fcoe_hostlist_lookup(स्थिर काष्ठा net_device *netdev)
अणु
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_पूर्णांकerface *fcoe;

	fcoe = fcoe_hostlist_lookup_port(netdev);
	ctlr = fcoe_to_ctlr(fcoe);
	वापस (fcoe) ? ctlr->lp : शून्य;
पूर्ण

/**
 * fcoe_hostlist_add() - Add the FCoE पूर्णांकerface identअगरied by a local
 *			 port to the hostlist
 * @lport: The local port that identअगरies the FCoE पूर्णांकerface to be added
 *
 * Locking: must be called with the RTNL mutex held
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_hostlist_add(स्थिर काष्ठा fc_lport *lport)
अणु
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	काष्ठा fcoe_port *port;

	fcoe = fcoe_hostlist_lookup_port(fcoe_netdev(lport));
	अगर (!fcoe) अणु
		port = lport_priv(lport);
		fcoe = port->priv;
		list_add_tail(&fcoe->list, &fcoe_hostlist);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * fcoe_hostlist_del() - Remove the FCoE पूर्णांकerface identअगरied by a local
 *			 port to the hostlist
 * @lport: The local port that identअगरies the FCoE पूर्णांकerface to be added
 *
 * Locking: must be called with the RTNL mutex held
 *
 */
अटल व्योम fcoe_hostlist_del(स्थिर काष्ठा fc_lport *lport)
अणु
	काष्ठा fcoe_पूर्णांकerface *fcoe;
	काष्ठा fcoe_port *port;

	port = lport_priv(lport);
	fcoe = port->priv;
	list_del(&fcoe->list);
	वापस;
पूर्ण

अटल काष्ठा fcoe_transport fcoe_sw_transport = अणु
	.name = अणुFCOE_TRANSPORT_DEFAULTपूर्ण,
	.attached = false,
	.list = LIST_HEAD_INIT(fcoe_sw_transport.list),
	.match = fcoe_match,
	.alloc = fcoe_ctlr_alloc,
	.create = fcoe_create,
	.destroy = fcoe_destroy,
	.enable = fcoe_enable,
	.disable = fcoe_disable,
पूर्ण;

/**
 * fcoe_init() - Initialize fcoe.ko
 *
 * Returns: 0 on success, or a negative value on failure
 */
अटल पूर्णांक __init fcoe_init(व्योम)
अणु
	काष्ठा fcoe_percpu_s *p;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक rc = 0;

	fcoe_wq = alloc_workqueue("fcoe", 0, 0);
	अगर (!fcoe_wq)
		वापस -ENOMEM;

	/* रेजिस्टर as a fcoe transport */
	rc = fcoe_transport_attach(&fcoe_sw_transport);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "failed to register an fcoe transport, check "
			"if libfcoe is loaded\n");
		जाओ out_destroy;
	पूर्ण

	mutex_lock(&fcoe_config_mutex);

	क्रम_each_possible_cpu(cpu) अणु
		p = per_cpu_ptr(&fcoe_percpu, cpu);
		INIT_WORK(&p->work, fcoe_receive_work);
		skb_queue_head_init(&p->fcoe_rx_list);
	पूर्ण

	/* Setup link change notअगरication */
	fcoe_dev_setup();

	rc = fcoe_अगर_init();
	अगर (rc)
		जाओ out_मुक्त;

	mutex_unlock(&fcoe_config_mutex);
	वापस 0;

out_मुक्त:
	mutex_unlock(&fcoe_config_mutex);
out_destroy:
	destroy_workqueue(fcoe_wq);
	वापस rc;
पूर्ण
module_init(fcoe_init);

/**
 * fcoe_निकास() - Clean up fcoe.ko
 *
 * Returns: 0 on success or a  negative value on failure
 */
अटल व्योम __निकास fcoe_निकास(व्योम)
अणु
	काष्ठा fcoe_पूर्णांकerface *fcoe, *पंचांगp;
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_port *port;
	अचिन्हित पूर्णांक cpu;

	mutex_lock(&fcoe_config_mutex);

	fcoe_dev_cleanup();

	/* releases the associated fcoe hosts */
	rtnl_lock();
	list_क्रम_each_entry_safe(fcoe, पंचांगp, &fcoe_hostlist, list) अणु
		ctlr = fcoe_to_ctlr(fcoe);
		port = lport_priv(ctlr->lp);
		fcoe_hostlist_del(port->lport);
		queue_work(fcoe_wq, &port->destroy_work);
	पूर्ण
	rtnl_unlock();

	क्रम_each_possible_cpu(cpu)
		fcoe_thपढ़ो_cleanup_local(cpu);

	mutex_unlock(&fcoe_config_mutex);

	/*
	 * destroy_work's may be chained but destroy_workqueue()
	 * can take care of them. Just समाप्त the fcoe_wq.
	 */
	destroy_workqueue(fcoe_wq);

	/*
	 * Detaching from the scsi transport must happen after all
	 * destroys are करोne on the fcoe_wq. destroy_workqueue will
	 * enusre the fcoe_wq is flushed.
	 */
	fcoe_अगर_निकास();

	/* detach from fcoe transport */
	fcoe_transport_detach(&fcoe_sw_transport);
पूर्ण
module_निकास(fcoe_निकास);

/**
 * fcoe_flogi_resp() - FCoE specअगरic FLOGI and FDISC response handler
 * @seq: active sequence in the FLOGI or FDISC exchange
 * @fp: response frame, or error encoded in a poपूर्णांकer (समयout)
 * @arg: poपूर्णांकer to the fcoe_ctlr काष्ठाure
 *
 * This handles MAC address management क्रम FCoE, then passes control on to
 * the libfc FLOGI response handler.
 */
अटल व्योम fcoe_flogi_resp(काष्ठा fc_seq *seq, काष्ठा fc_frame *fp, व्योम *arg)
अणु
	काष्ठा fcoe_ctlr *fip = arg;
	काष्ठा fc_exch *exch = fc_seq_exch(seq);
	काष्ठा fc_lport *lport = exch->lp;
	u8 *mac;

	अगर (IS_ERR(fp))
		जाओ करोne;

	mac = fr_cb(fp)->granted_mac;
	/* pre-FIP */
	अगर (is_zero_ether_addr(mac))
		fcoe_ctlr_recv_flogi(fip, lport, fp);
	अगर (!is_zero_ether_addr(mac))
		fcoe_update_src_mac(lport, mac);
करोne:
	fc_lport_flogi_resp(seq, fp, lport);
पूर्ण

/**
 * fcoe_logo_resp() - FCoE specअगरic LOGO response handler
 * @seq: active sequence in the LOGO exchange
 * @fp: response frame, or error encoded in a poपूर्णांकer (समयout)
 * @arg: poपूर्णांकer to the fcoe_ctlr काष्ठाure
 *
 * This handles MAC address management क्रम FCoE, then passes control on to
 * the libfc LOGO response handler.
 */
अटल व्योम fcoe_logo_resp(काष्ठा fc_seq *seq, काष्ठा fc_frame *fp, व्योम *arg)
अणु
	काष्ठा fc_lport *lport = arg;
	अटल u8 zero_mac[ETH_ALEN] = अणु 0 पूर्ण;

	अगर (!IS_ERR(fp))
		fcoe_update_src_mac(lport, zero_mac);
	fc_lport_logo_resp(seq, fp, lport);
पूर्ण

/*
 * fcoe_elsct_send - FCoE specअगरic ELS handler
 *
 * This करोes special हाल handling of FIP encapsualted ELS exchanges क्रम FCoE,
 * using FCoE specअगरic response handlers and passing the FIP controller as
 * the argument (the lport is still available from the exchange).
 *
 * Most of the work here is just handed off to the libfc routine.
 */
अटल काष्ठा fc_seq *fcoe_elsct_send(काष्ठा fc_lport *lport, u32 did,
				      काष्ठा fc_frame *fp, अचिन्हित पूर्णांक op,
				      व्योम (*resp)(काष्ठा fc_seq *,
						   काष्ठा fc_frame *,
						   व्योम *),
				      व्योम *arg, u32 समयout)
अणु
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा fcoe_पूर्णांकerface *fcoe = port->priv;
	काष्ठा fcoe_ctlr *fip = fcoe_to_ctlr(fcoe);
	काष्ठा fc_frame_header *fh = fc_frame_header_get(fp);

	चयन (op) अणु
	हाल ELS_FLOGI:
	हाल ELS_FDISC:
		अगर (lport->poपूर्णांक_to_multipoपूर्णांक)
			अवरोध;
		वापस fc_elsct_send(lport, did, fp, op, fcoe_flogi_resp,
				     fip, समयout);
	हाल ELS_LOGO:
		/* only hook onto fabric logouts, not port logouts */
		अगर (ntoh24(fh->fh_d_id) != FC_FID_FLOGI)
			अवरोध;
		वापस fc_elsct_send(lport, did, fp, op, fcoe_logo_resp,
				     lport, समयout);
	पूर्ण
	वापस fc_elsct_send(lport, did, fp, op, resp, arg, समयout);
पूर्ण

/**
 * fcoe_vport_create() - create an fc_host/scsi_host क्रम a vport
 * @vport: fc_vport object to create a new fc_host क्रम
 * @disabled: start the new fc_host in a disabled state by शेष?
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_vport_create(काष्ठा fc_vport *vport, bool disabled)
अणु
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);
	काष्ठा fc_lport *n_port = shost_priv(shost);
	काष्ठा fcoe_port *port = lport_priv(n_port);
	काष्ठा fcoe_पूर्णांकerface *fcoe = port->priv;
	काष्ठा net_device *netdev = fcoe->netdev;
	काष्ठा fc_lport *vn_port;
	पूर्णांक rc;
	अक्षर buf[32];

	rc = fcoe_validate_vport_create(vport);
	अगर (rc) अणु
		fcoe_wwn_to_str(vport->port_name, buf, माप(buf));
		prपूर्णांकk(KERN_ERR "fcoe: Failed to create vport, "
			"WWPN (0x%s) already exists\n",
			buf);
		वापस rc;
	पूर्ण

	mutex_lock(&fcoe_config_mutex);
	rtnl_lock();
	vn_port = fcoe_अगर_create(fcoe, &vport->dev, 1);
	rtnl_unlock();
	mutex_unlock(&fcoe_config_mutex);

	अगर (IS_ERR(vn_port)) अणु
		prपूर्णांकk(KERN_ERR "fcoe: fcoe_vport_create(%s) failed\n",
		       netdev->name);
		वापस -EIO;
	पूर्ण

	अगर (disabled) अणु
		fc_vport_set_state(vport, FC_VPORT_DISABLED);
	पूर्ण अन्यथा अणु
		vn_port->boot_समय = jअगरfies;
		fc_fabric_login(vn_port);
		fc_vport_setlink(vn_port);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * fcoe_vport_destroy() - destroy the fc_host/scsi_host क्रम a vport
 * @vport: fc_vport object that is being destroyed
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक fcoe_vport_destroy(काष्ठा fc_vport *vport)
अणु
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);
	काष्ठा fc_lport *n_port = shost_priv(shost);
	काष्ठा fc_lport *vn_port = vport->dd_data;

	mutex_lock(&n_port->lp_mutex);
	list_del(&vn_port->list);
	mutex_unlock(&n_port->lp_mutex);

	mutex_lock(&fcoe_config_mutex);
	rtnl_lock();
	fcoe_अगर_destroy(vn_port);
	rtnl_unlock();
	mutex_unlock(&fcoe_config_mutex);

	वापस 0;
पूर्ण

/**
 * fcoe_vport_हटाओ() - हटाओ attached vports
 * @lport: lport क्रम which the vports should be हटाओd
 */
अटल व्योम fcoe_vport_हटाओ(काष्ठा fc_lport *lport)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा fc_host_attrs *fc_host;
	अचिन्हित दीर्घ flags;
	काष्ठा fc_vport *vport;
	काष्ठा fc_vport *next_vport;

	shost = lport->host;
	fc_host = shost_to_fc_host(shost);

	/* Loop through all the vports and mark them क्रम deletion */
	spin_lock_irqsave(shost->host_lock, flags);
	list_क्रम_each_entry_safe(vport, next_vport, &fc_host->vports, peers) अणु
		अगर (vport->flags & (FC_VPORT_DEL | FC_VPORT_CREATING)) अणु
			जारी;
		पूर्ण अन्यथा अणु
			vport->flags |= FC_VPORT_DELETING;
			queue_work(fc_host_work_q(shost),
				   &vport->vport_delete_work);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);

	flush_workqueue(fc_host_work_q(shost));
पूर्ण

/**
 * fcoe_vport_disable() - change vport state
 * @vport: vport to bring online/offline
 * @disable: should the vport be disabled?
 */
अटल पूर्णांक fcoe_vport_disable(काष्ठा fc_vport *vport, bool disable)
अणु
	काष्ठा fc_lport *lport = vport->dd_data;

	अगर (disable) अणु
		fc_vport_set_state(vport, FC_VPORT_DISABLED);
		fc_fabric_logoff(lport);
	पूर्ण अन्यथा अणु
		lport->boot_समय = jअगरfies;
		fc_fabric_login(lport);
		fc_vport_setlink(lport);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * fcoe_set_vport_symbolic_name() - append vport string to symbolic name
 * @vport: fc_vport with a new symbolic name string
 *
 * After generating a new symbolic name string, a new RSPN_ID request is
 * sent to the name server.  There is no response handler, so अगर it fails
 * क्रम some reason it will not be retried.
 */
अटल व्योम fcoe_set_vport_symbolic_name(काष्ठा fc_vport *vport)
अणु
	काष्ठा fc_lport *lport = vport->dd_data;
	काष्ठा fc_frame *fp;
	माप_प्रकार len;

	snम_लिखो(fc_host_symbolic_name(lport->host), FC_SYMBOLIC_NAME_SIZE,
		 "%s v%s over %s : %s", FCOE_NAME, FCOE_VERSION,
		 fcoe_netdev(lport)->name, vport->symbolic_name);

	अगर (lport->state != LPORT_ST_READY)
		वापस;

	len = strnlen(fc_host_symbolic_name(lport->host), 255);
	fp = fc_frame_alloc(lport,
			    माप(काष्ठा fc_ct_hdr) +
			    माप(काष्ठा fc_ns_rspn) + len);
	अगर (!fp)
		वापस;
	lport->tt.elsct_send(lport, FC_FID_सूची_SERV, fp, FC_NS_RSPN_ID,
			     शून्य, शून्य, 3 * lport->r_a_tov);
पूर्ण

अटल व्योम fcoe_fcf_get_vlan_id(काष्ठा fcoe_fcf_device *fcf_dev)
अणु
	काष्ठा fcoe_ctlr_device *ctlr_dev =
		fcoe_fcf_dev_to_ctlr_dev(fcf_dev);
	काष्ठा fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(ctlr_dev);
	काष्ठा fcoe_पूर्णांकerface *fcoe = fcoe_ctlr_priv(ctlr);

	fcf_dev->vlan_id = vlan_dev_vlan_id(fcoe->netdev);
पूर्ण

/**
 * fcoe_set_port_id() - Callback from libfc when Port_ID is set.
 * @lport: the local port
 * @port_id: the port ID
 * @fp: the received frame, अगर any, that caused the port_id to be set.
 *
 * This routine handles the हाल where we received a FLOGI and are
 * entering poपूर्णांक-to-poपूर्णांक mode.  We need to call fcoe_ctlr_recv_flogi()
 * so it can set the non-mapped mode and gateway address.
 *
 * The FLOGI LS_ACC is handled by fcoe_flogi_resp().
 */
अटल व्योम fcoe_set_port_id(काष्ठा fc_lport *lport,
			     u32 port_id, काष्ठा fc_frame *fp)
अणु
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा fcoe_पूर्णांकerface *fcoe = port->priv;
	काष्ठा fcoe_ctlr *ctlr = fcoe_to_ctlr(fcoe);

	अगर (fp && fc_frame_payload_op(fp) == ELS_FLOGI)
		fcoe_ctlr_recv_flogi(ctlr, lport, fp);
पूर्ण
