<शैली गुरु>
/* bnx2x_cmn.h: QLogic Everest network driver.
 *
 * Copyright (c) 2007-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Eliezer Tamir
 * Based on code from Michael Chan's bnx2 driver
 * UDP CSUM errata workaround by Arik Gendelman
 * Slowpath and fastpath rework by Vladislav Zolotarov
 * Statistics and Link management by Yitchak Gertner
 *
 */
#अगर_अघोषित BNX2X_CMN_H
#घोषणा BNX2X_CMN_H

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/irq.h>

#समावेश "bnx2x.h"
#समावेश "bnx2x_sriov.h"

/* This is used as a replacement क्रम an MCP अगर it's not present */
बाह्य पूर्णांक bnx2x_load_count[2][3]; /* per-path: 0-common, 1-port0, 2-port1 */
बाह्य पूर्णांक bnx2x_num_queues;

/************************ Macros ********************************/
#घोषणा BNX2X_PCI_FREE(x, y, size) \
	करो अणु \
		अगर (x) अणु \
			dma_मुक्त_coherent(&bp->pdev->dev, size, (व्योम *)x, y); \
			x = शून्य; \
			y = 0; \
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा BNX2X_FREE(x) \
	करो अणु \
		अगर (x) अणु \
			kमुक्त((व्योम *)x); \
			x = शून्य; \
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा BNX2X_PCI_ALLOC(y, size)					\
(अणु									\
	व्योम *x = dma_alloc_coherent(&bp->pdev->dev, size, y, GFP_KERNEL); \
	अगर (x)								\
		DP(NETIF_MSG_HW,					\
		   "BNX2X_PCI_ALLOC: Physical %Lx Virtual %p\n",	\
		   (अचिन्हित दीर्घ दीर्घ)(*y), x);			\
	x;								\
पूर्ण)
#घोषणा BNX2X_PCI_FALLOC(y, size)					\
(अणु									\
	व्योम *x = dma_alloc_coherent(&bp->pdev->dev, size, y, GFP_KERNEL); \
	अगर (x) अणु							\
		स_रखो(x, 0xff, size);					\
		DP(NETIF_MSG_HW,					\
		   "BNX2X_PCI_FALLOC: Physical %Lx Virtual %p\n",	\
		   (अचिन्हित दीर्घ दीर्घ)(*y), x);			\
	पूर्ण								\
	x;								\
पूर्ण)

/*********************** Interfaces ****************************
 *  Functions that need to be implemented by each driver version
 */
/* Init */

/**
 * bnx2x_send_unload_req - request unload mode from the MCP.
 *
 * @bp:			driver handle
 * @unload_mode:	requested function's unload mode
 *
 * Return unload mode वापसed by the MCP: COMMON, PORT or FUNC.
 */
u32 bnx2x_send_unload_req(काष्ठा bnx2x *bp, पूर्णांक unload_mode);

/**
 * bnx2x_send_unload_करोne - send UNLOAD_DONE command to the MCP.
 *
 * @bp:		driver handle
 * @keep_link:		true अगरf link should be kept up
 */
व्योम bnx2x_send_unload_करोne(काष्ठा bnx2x *bp, bool keep_link);

/**
 * bnx2x_config_rss_pf - configure RSS parameters in a PF.
 *
 * @bp:			driver handle
 * @rss_obj:		RSS object to use
 * @ind_table:		indirection table to configure
 * @config_hash:	re-configure RSS hash keys configuration
 * @enable:		enabled or disabled configuration
 */
पूर्णांक bnx2x_rss(काष्ठा bnx2x *bp, काष्ठा bnx2x_rss_config_obj *rss_obj,
	      bool config_hash, bool enable);

/**
 * bnx2x__init_func_obj - init function object
 *
 * @bp:			driver handle
 *
 * Initializes the Function Object with the appropriate
 * parameters which include a function slow path driver
 * पूर्णांकerface.
 */
व्योम bnx2x__init_func_obj(काष्ठा bnx2x *bp);

/**
 * bnx2x_setup_queue - setup eth queue.
 *
 * @bp:		driver handle
 * @fp:		poपूर्णांकer to the fastpath काष्ठाure
 * @leading:	boolean
 *
 */
पूर्णांक bnx2x_setup_queue(काष्ठा bnx2x *bp, काष्ठा bnx2x_fastpath *fp,
		       bool leading);

/**
 * bnx2x_setup_leading - bring up a leading eth queue.
 *
 * @bp:		driver handle
 */
पूर्णांक bnx2x_setup_leading(काष्ठा bnx2x *bp);

/**
 * bnx2x_fw_command - send the MCP a request
 *
 * @bp:		driver handle
 * @command:	request
 * @param:	request's parameter
 *
 * block until there is a reply
 */
u32 bnx2x_fw_command(काष्ठा bnx2x *bp, u32 command, u32 param);

/**
 * bnx2x_initial_phy_init - initialize link parameters काष्ठाure variables.
 *
 * @bp:		driver handle
 * @load_mode:	current mode
 */
पूर्णांक bnx2x_initial_phy_init(काष्ठा bnx2x *bp, पूर्णांक load_mode);

/**
 * bnx2x_link_set - configure hw according to link parameters काष्ठाure.
 *
 * @bp:		driver handle
 */
व्योम bnx2x_link_set(काष्ठा bnx2x *bp);

/**
 * bnx2x_क्रमce_link_reset - Forces link reset, and put the PHY
 * in reset as well.
 *
 * @bp:		driver handle
 */
व्योम bnx2x_क्रमce_link_reset(काष्ठा bnx2x *bp);

/**
 * bnx2x_link_test - query link status.
 *
 * @bp:		driver handle
 * @is_serdes:	bool
 *
 * Returns 0 अगर link is UP.
 */
u8 bnx2x_link_test(काष्ठा bnx2x *bp, u8 is_serdes);

/**
 * bnx2x_drv_pulse - ग_लिखो driver pulse to shmem
 *
 * @bp:		driver handle
 *
 * ग_लिखोs the value in bp->fw_drv_pulse_wr_seq to drv_pulse mbox
 * in the shmem.
 */
व्योम bnx2x_drv_pulse(काष्ठा bnx2x *bp);

/**
 * bnx2x_igu_ack_sb - update IGU with current SB value
 *
 * @bp:		driver handle
 * @igu_sb_id:	SB id
 * @segment:	SB segment
 * @index:	SB index
 * @op:		SB operation
 * @update:	is HW update required
 */
व्योम bnx2x_igu_ack_sb(काष्ठा bnx2x *bp, u8 igu_sb_id, u8 segment,
		      u16 index, u8 op, u8 update);

/* Disable transactions from chip to host */
व्योम bnx2x_pf_disable(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_pretend_func(काष्ठा bnx2x *bp, u16 pretend_func_val);

/**
 * bnx2x__link_status_update - handles link status change.
 *
 * @bp:		driver handle
 */
व्योम bnx2x__link_status_update(काष्ठा bnx2x *bp);

/**
 * bnx2x_link_report - report link status to upper layer.
 *
 * @bp:		driver handle
 */
व्योम bnx2x_link_report(काष्ठा bnx2x *bp);

/* None-atomic version of bnx2x_link_report() */
व्योम __bnx2x_link_report(काष्ठा bnx2x *bp);

/**
 * bnx2x_get_mf_speed - calculate MF speed.
 *
 * @bp:		driver handle
 *
 * Takes पूर्णांकo account current linespeed and MF configuration.
 */
u16 bnx2x_get_mf_speed(काष्ठा bnx2x *bp);

/**
 * bnx2x_msix_sp_पूर्णांक - MSI-X slowpath पूर्णांकerrupt handler
 *
 * @irq:		irq number
 * @dev_instance:	निजी instance
 */
irqवापस_t bnx2x_msix_sp_पूर्णांक(पूर्णांक irq, व्योम *dev_instance);

/**
 * bnx2x_पूर्णांकerrupt - non MSI-X पूर्णांकerrupt handler
 *
 * @irq:		irq number
 * @dev_instance:	निजी instance
 */
irqवापस_t bnx2x_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);

/**
 * bnx2x_cnic_notअगरy - send command to cnic driver
 *
 * @bp:		driver handle
 * @cmd:	command
 */
पूर्णांक bnx2x_cnic_notअगरy(काष्ठा bnx2x *bp, पूर्णांक cmd);

/**
 * bnx2x_setup_cnic_irq_info - provides cnic with IRQ inक्रमmation
 *
 * @bp:		driver handle
 */
व्योम bnx2x_setup_cnic_irq_info(काष्ठा bnx2x *bp);

/**
 * bnx2x_setup_cnic_info - provides cnic with updated info
 *
 * @bp:		driver handle
 */
व्योम bnx2x_setup_cnic_info(काष्ठा bnx2x *bp);

/**
 * bnx2x_पूर्णांक_enable - enable HW पूर्णांकerrupts.
 *
 * @bp:		driver handle
 */
व्योम bnx2x_पूर्णांक_enable(काष्ठा bnx2x *bp);

/**
 * bnx2x_पूर्णांक_disable_sync - disable पूर्णांकerrupts.
 *
 * @bp:		driver handle
 * @disable_hw:	true, disable HW पूर्णांकerrupts.
 *
 * This function ensures that there are no
 * ISRs or SP DPCs (sp_task) are running after it वापसs.
 */
व्योम bnx2x_पूर्णांक_disable_sync(काष्ठा bnx2x *bp, पूर्णांक disable_hw);

/**
 * bnx2x_nic_init_cnic - init driver पूर्णांकernals क्रम cnic.
 *
 * @bp:		driver handle
 * @load_code:	COMMON, PORT or FUNCTION
 *
 * Initializes:
 *  - rings
 *  - status blocks
 *  - etc.
 */
व्योम bnx2x_nic_init_cnic(काष्ठा bnx2x *bp);

/**
 * bnx2x_preirq_nic_init - init driver पूर्णांकernals.
 *
 * @bp:		driver handle
 *
 * Initializes:
 *  - fastpath object
 *  - fastpath rings
 *  etc.
 */
व्योम bnx2x_pre_irq_nic_init(काष्ठा bnx2x *bp);

/**
 * bnx2x_postirq_nic_init - init driver पूर्णांकernals.
 *
 * @bp:		driver handle
 * @load_code:	COMMON, PORT or FUNCTION
 *
 * Initializes:
 *  - status blocks
 *  - slowpath rings
 *  - etc.
 */
व्योम bnx2x_post_irq_nic_init(काष्ठा bnx2x *bp, u32 load_code);
/**
 * bnx2x_alloc_mem_cnic - allocate driver's memory क्रम cnic.
 *
 * @bp:		driver handle
 */
पूर्णांक bnx2x_alloc_mem_cnic(काष्ठा bnx2x *bp);
/**
 * bnx2x_alloc_mem - allocate driver's memory.
 *
 * @bp:		driver handle
 */
पूर्णांक bnx2x_alloc_mem(काष्ठा bnx2x *bp);

/**
 * bnx2x_मुक्त_mem_cnic - release driver's memory क्रम cnic.
 *
 * @bp:		driver handle
 */
व्योम bnx2x_मुक्त_mem_cnic(काष्ठा bnx2x *bp);
/**
 * bnx2x_मुक्त_mem - release driver's memory.
 *
 * @bp:		driver handle
 */
व्योम bnx2x_मुक्त_mem(काष्ठा bnx2x *bp);

/**
 * bnx2x_set_num_queues - set number of queues according to mode.
 *
 * @bp:		driver handle
 */
व्योम bnx2x_set_num_queues(काष्ठा bnx2x *bp);

/**
 * bnx2x_chip_cleanup - cleanup chip पूर्णांकernals.
 *
 * @bp:			driver handle
 * @unload_mode:	COMMON, PORT, FUNCTION
 * @keep_link:		true अगरf link should be kept up.
 *
 * - Cleanup MAC configuration.
 * - Closes clients.
 * - etc.
 */
व्योम bnx2x_chip_cleanup(काष्ठा bnx2x *bp, पूर्णांक unload_mode, bool keep_link);

/**
 * bnx2x_acquire_hw_lock - acquire HW lock.
 *
 * @bp:		driver handle
 * @resource:	resource bit which was locked
 */
पूर्णांक bnx2x_acquire_hw_lock(काष्ठा bnx2x *bp, u32 resource);

/**
 * bnx2x_release_hw_lock - release HW lock.
 *
 * @bp:		driver handle
 * @resource:	resource bit which was locked
 */
पूर्णांक bnx2x_release_hw_lock(काष्ठा bnx2x *bp, u32 resource);

/**
 * bnx2x_release_leader_lock - release recovery leader lock
 *
 * @bp:		driver handle
 */
पूर्णांक bnx2x_release_leader_lock(काष्ठा bnx2x *bp);

/**
 * bnx2x_set_eth_mac - configure eth MAC address in the HW
 *
 * @bp:		driver handle
 * @set:	set or clear
 *
 * Configures according to the value in netdev->dev_addr.
 */
पूर्णांक bnx2x_set_eth_mac(काष्ठा bnx2x *bp, bool set);

/**
 * bnx2x_set_rx_mode - set MAC filtering configurations.
 *
 * @dev:	netdevice
 *
 * called with netअगर_tx_lock from dev_mcast.c
 * If bp->state is OPEN, should be called with
 * netअगर_addr_lock_bh()
 */
व्योम bnx2x_set_rx_mode_inner(काष्ठा bnx2x *bp);

/* Parity errors related */
व्योम bnx2x_set_pf_load(काष्ठा bnx2x *bp);
bool bnx2x_clear_pf_load(काष्ठा bnx2x *bp);
bool bnx2x_chk_parity_attn(काष्ठा bnx2x *bp, bool *global, bool prपूर्णांक);
bool bnx2x_reset_is_करोne(काष्ठा bnx2x *bp, पूर्णांक engine);
व्योम bnx2x_set_reset_in_progress(काष्ठा bnx2x *bp);
व्योम bnx2x_set_reset_global(काष्ठा bnx2x *bp);
व्योम bnx2x_disable_बंद_the_gate(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_init_hw_func_cnic(काष्ठा bnx2x *bp);

व्योम bnx2x_clear_vlan_info(काष्ठा bnx2x *bp);

/**
 * bnx2x_sp_event - handle ramrods completion.
 *
 * @fp:		fastpath handle क्रम the event
 * @rr_cqe:	eth_rx_cqe
 */
व्योम bnx2x_sp_event(काष्ठा bnx2x_fastpath *fp, जोड़ eth_rx_cqe *rr_cqe);

/**
 * bnx2x_ilt_set_info - prepare ILT configurations.
 *
 * @bp:		driver handle
 */
व्योम bnx2x_ilt_set_info(काष्ठा bnx2x *bp);

/**
 * bnx2x_ilt_set_cnic_info - prepare ILT configurations क्रम SRC
 * and TM.
 *
 * @bp:		driver handle
 */
व्योम bnx2x_ilt_set_info_cnic(काष्ठा bnx2x *bp);

/**
 * bnx2x_dcbx_init - initialize dcbx protocol.
 *
 * @bp:		driver handle
 */
व्योम bnx2x_dcbx_init(काष्ठा bnx2x *bp, bool update_shmem);

/**
 * bnx2x_set_घातer_state - set घातer state to the requested value.
 *
 * @bp:		driver handle
 * @state:	required state D0 or D3hot
 *
 * Currently only D0 and D3hot are supported.
 */
पूर्णांक bnx2x_set_घातer_state(काष्ठा bnx2x *bp, pci_घातer_t state);

/**
 * bnx2x_update_max_mf_config - update MAX part of MF configuration in HW.
 *
 * @bp:		driver handle
 * @value:	new value
 */
व्योम bnx2x_update_max_mf_config(काष्ठा bnx2x *bp, u32 value);
/* Error handling */
व्योम bnx2x_fw_dump_lvl(काष्ठा bnx2x *bp, स्थिर अक्षर *lvl);

/* dev_बंद मुख्य block */
पूर्णांक bnx2x_nic_unload(काष्ठा bnx2x *bp, पूर्णांक unload_mode, bool keep_link);

/* dev_खोलो मुख्य block */
पूर्णांक bnx2x_nic_load(काष्ठा bnx2x *bp, पूर्णांक load_mode);

/* hard_xmit callback */
netdev_tx_t bnx2x_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);

/* setup_tc callback */
पूर्णांक bnx2x_setup_tc(काष्ठा net_device *dev, u8 num_tc);
पूर्णांक __bnx2x_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
		     व्योम *type_data);

पूर्णांक bnx2x_get_vf_config(काष्ठा net_device *dev, पूर्णांक vf,
			काष्ठा अगरla_vf_info *ivi);
पूर्णांक bnx2x_set_vf_mac(काष्ठा net_device *dev, पूर्णांक queue, u8 *mac);
पूर्णांक bnx2x_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vf, u16 vlan, u8 qos,
		      __be16 vlan_proto);
पूर्णांक bnx2x_set_vf_spoofchk(काष्ठा net_device *dev, पूर्णांक idx, bool val);

/* select_queue callback */
u16 bnx2x_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		       काष्ठा net_device *sb_dev);

अटल अंतरभूत व्योम bnx2x_update_rx_prod(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_fastpath *fp,
					u16 bd_prod, u16 rx_comp_prod,
					u16 rx_sge_prod)
अणु
	काष्ठा ustorm_eth_rx_producers rx_prods = अणु0पूर्ण;
	u32 i;

	/* Update producers */
	rx_prods.bd_prod = bd_prod;
	rx_prods.cqe_prod = rx_comp_prod;
	rx_prods.sge_prod = rx_sge_prod;

	/* Make sure that the BD and SGE data is updated beक्रमe updating the
	 * producers since FW might पढ़ो the BD/SGE right after the producer
	 * is updated.
	 * This is only applicable क्रम weak-ordered memory model archs such
	 * as IA-64. The following barrier is also mandatory since FW will
	 * assumes BDs must have buffers.
	 */
	wmb();

	क्रम (i = 0; i < माप(rx_prods)/4; i++)
		REG_WR_RELAXED(bp, fp->ustorm_rx_prods_offset + i * 4,
			       ((u32 *)&rx_prods)[i]);

	DP(NETIF_MSG_RX_STATUS,
	   "queue[%d]:  wrote  bd_prod %u  cqe_prod %u  sge_prod %u\n",
	   fp->index, bd_prod, rx_comp_prod, rx_sge_prod);
पूर्ण

/* reload helper */
पूर्णांक bnx2x_reload_अगर_running(काष्ठा net_device *dev);

पूर्णांक bnx2x_change_mac_addr(काष्ठा net_device *dev, व्योम *p);

/* NAPI poll Tx part */
पूर्णांक bnx2x_tx_पूर्णांक(काष्ठा bnx2x *bp, काष्ठा bnx2x_fp_txdata *txdata);

बाह्य स्थिर काष्ठा dev_pm_ops bnx2x_pm_ops;

/* Release IRQ vectors */
व्योम bnx2x_मुक्त_irq(काष्ठा bnx2x *bp);

व्योम bnx2x_मुक्त_fp_mem(काष्ठा bnx2x *bp);
व्योम bnx2x_init_rx_rings(काष्ठा bnx2x *bp);
व्योम bnx2x_init_rx_rings_cnic(काष्ठा bnx2x *bp);
व्योम bnx2x_मुक्त_skbs(काष्ठा bnx2x *bp);
व्योम bnx2x_netअगर_stop(काष्ठा bnx2x *bp, पूर्णांक disable_hw);
व्योम bnx2x_netअगर_start(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_load_cnic(काष्ठा bnx2x *bp);

/**
 * bnx2x_enable_msix - set msix configuration.
 *
 * @bp:		driver handle
 *
 * fills msix_table, requests vectors, updates num_queues
 * according to number of available vectors.
 */
पूर्णांक bnx2x_enable_msix(काष्ठा bnx2x *bp);

/**
 * bnx2x_enable_msi - request msi mode from OS, updated पूर्णांकernals accordingly
 *
 * @bp:		driver handle
 */
पूर्णांक bnx2x_enable_msi(काष्ठा bnx2x *bp);

/**
 * bnx2x_alloc_mem_bp - allocate memories outsize मुख्य driver काष्ठाure
 *
 * @bp:		driver handle
 */
पूर्णांक bnx2x_alloc_mem_bp(काष्ठा bnx2x *bp);

/**
 * bnx2x_मुक्त_mem_bp - release memories outsize मुख्य driver काष्ठाure
 *
 * @bp:		driver handle
 */
व्योम bnx2x_मुक्त_mem_bp(काष्ठा bnx2x *bp);

/**
 * bnx2x_change_mtu - change mtu netdev callback
 *
 * @dev:	net device
 * @new_mtu:	requested mtu
 *
 */
पूर्णांक bnx2x_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu);

#अगर_घोषित NETDEV_FCOE_WWNN
/**
 * bnx2x_fcoe_get_wwn - वापस the requested WWN value क्रम this port
 *
 * @dev:	net_device
 * @wwn:	output buffer
 * @type:	WWN type: NETDEV_FCOE_WWNN (node) or NETDEV_FCOE_WWPN (port)
 *
 */
पूर्णांक bnx2x_fcoe_get_wwn(काष्ठा net_device *dev, u64 *wwn, पूर्णांक type);
#पूर्ण_अगर

netdev_features_t bnx2x_fix_features(काष्ठा net_device *dev,
				     netdev_features_t features);
पूर्णांक bnx2x_set_features(काष्ठा net_device *dev, netdev_features_t features);

/**
 * bnx2x_tx_समयout - tx समयout netdev callback
 *
 * @dev:	net device
 */
व्योम bnx2x_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);

/** bnx2x_get_c2s_mapping - पढ़ो inner-to-outer vlan configuration
 * c2s_map should have BNX2X_MAX_PRIORITY entries.
 * @bp:			driver handle
 * @c2s_map:		should have BNX2X_MAX_PRIORITY entries क्रम mapping
 * @c2s_शेष:	entry क्रम non-tagged configuration
 */
व्योम bnx2x_get_c2s_mapping(काष्ठा bnx2x *bp, u8 *c2s_map, u8 *c2s_शेष);

/*********************** Inlines **********************************/
/*********************** Fast path ********************************/
अटल अंतरभूत व्योम bnx2x_update_fpsb_idx(काष्ठा bnx2x_fastpath *fp)
अणु
	barrier(); /* status block is written to by the chip */
	fp->fp_hc_idx = fp->sb_running_index[SM_RX_ID];
पूर्ण

अटल अंतरभूत व्योम bnx2x_igu_ack_sb_gen(काष्ठा bnx2x *bp, u8 igu_sb_id,
					u8 segment, u16 index, u8 op,
					u8 update, u32 igu_addr)
अणु
	काष्ठा igu_regular cmd_data = अणु0पूर्ण;

	cmd_data.sb_id_and_flags =
			((index << IGU_REGULAR_SB_INDEX_SHIFT) |
			 (segment << IGU_REGULAR_SEGMENT_ACCESS_SHIFT) |
			 (update << IGU_REGULAR_BUPDATE_SHIFT) |
			 (op << IGU_REGULAR_ENABLE_INT_SHIFT));

	DP(NETIF_MSG_INTR, "write 0x%08x to IGU addr 0x%x\n",
	   cmd_data.sb_id_and_flags, igu_addr);
	REG_WR(bp, igu_addr, cmd_data.sb_id_and_flags);

	/* Make sure that ACK is written */
	barrier();
पूर्ण

अटल अंतरभूत व्योम bnx2x_hc_ack_sb(काष्ठा bnx2x *bp, u8 sb_id,
				   u8 storm, u16 index, u8 op, u8 update)
अणु
	u32 hc_addr = (HC_REG_COMMAND_REG + BP_PORT(bp)*32 +
		       COMMAND_REG_INT_ACK);
	काष्ठा igu_ack_रेजिस्टर igu_ack;

	igu_ack.status_block_index = index;
	igu_ack.sb_id_and_flags =
			((sb_id << IGU_ACK_REGISTER_STATUS_BLOCK_ID_SHIFT) |
			 (storm << IGU_ACK_REGISTER_STORM_ID_SHIFT) |
			 (update << IGU_ACK_REGISTER_UPDATE_INDEX_SHIFT) |
			 (op << IGU_ACK_REGISTER_INTERRUPT_MODE_SHIFT));

	REG_WR(bp, hc_addr, (*(u32 *)&igu_ack));

	/* Make sure that ACK is written */
	barrier();
पूर्ण

अटल अंतरभूत व्योम bnx2x_ack_sb(काष्ठा bnx2x *bp, u8 igu_sb_id, u8 storm,
				u16 index, u8 op, u8 update)
अणु
	अगर (bp->common.पूर्णांक_block == INT_BLOCK_HC)
		bnx2x_hc_ack_sb(bp, igu_sb_id, storm, index, op, update);
	अन्यथा अणु
		u8 segment;

		अगर (CHIP_INT_MODE_IS_BC(bp))
			segment = storm;
		अन्यथा अगर (igu_sb_id != bp->igu_dsb_id)
			segment = IGU_SEG_ACCESS_DEF;
		अन्यथा अगर (storm == ATTENTION_ID)
			segment = IGU_SEG_ACCESS_ATTN;
		अन्यथा
			segment = IGU_SEG_ACCESS_DEF;
		bnx2x_igu_ack_sb(bp, igu_sb_id, segment, index, op, update);
	पूर्ण
पूर्ण

अटल अंतरभूत u16 bnx2x_hc_ack_पूर्णांक(काष्ठा bnx2x *bp)
अणु
	u32 hc_addr = (HC_REG_COMMAND_REG + BP_PORT(bp)*32 +
		       COMMAND_REG_SIMD_MASK);
	u32 result = REG_RD(bp, hc_addr);

	barrier();
	वापस result;
पूर्ण

अटल अंतरभूत u16 bnx2x_igu_ack_पूर्णांक(काष्ठा bnx2x *bp)
अणु
	u32 igu_addr = (BAR_IGU_INTMEM + IGU_REG_SISR_MDPC_WMASK_LSB_UPPER*8);
	u32 result = REG_RD(bp, igu_addr);

	DP(NETIF_MSG_INTR, "read 0x%08x from IGU addr 0x%x\n",
	   result, igu_addr);

	barrier();
	वापस result;
पूर्ण

अटल अंतरभूत u16 bnx2x_ack_पूर्णांक(काष्ठा bnx2x *bp)
अणु
	barrier();
	अगर (bp->common.पूर्णांक_block == INT_BLOCK_HC)
		वापस bnx2x_hc_ack_पूर्णांक(bp);
	अन्यथा
		वापस bnx2x_igu_ack_पूर्णांक(bp);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_has_tx_work_unload(काष्ठा bnx2x_fp_txdata *txdata)
अणु
	/* Tell compiler that consumer and producer can change */
	barrier();
	वापस txdata->tx_pkt_prod != txdata->tx_pkt_cons;
पूर्ण

अटल अंतरभूत u16 bnx2x_tx_avail(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_fp_txdata *txdata)
अणु
	s16 used;
	u16 prod;
	u16 cons;

	prod = txdata->tx_bd_prod;
	cons = txdata->tx_bd_cons;

	used = SUB_S16(prod, cons);

#अगर_घोषित BNX2X_STOP_ON_ERROR
	WARN_ON(used < 0);
	WARN_ON(used > txdata->tx_ring_size);
	WARN_ON((txdata->tx_ring_size - used) > MAX_TX_AVAIL);
#पूर्ण_अगर

	वापस (s16)(txdata->tx_ring_size) - used;
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_tx_queue_has_work(काष्ठा bnx2x_fp_txdata *txdata)
अणु
	u16 hw_cons;

	/* Tell compiler that status block fields can change */
	barrier();
	hw_cons = le16_to_cpu(*txdata->tx_cons_sb);
	वापस hw_cons != txdata->tx_pkt_cons;
पूर्ण

अटल अंतरभूत bool bnx2x_has_tx_work(काष्ठा bnx2x_fastpath *fp)
अणु
	u8 cos;
	क्रम_each_cos_in_tx_queue(fp, cos)
		अगर (bnx2x_tx_queue_has_work(fp->txdata_ptr[cos]))
			वापस true;
	वापस false;
पूर्ण

#घोषणा BNX2X_IS_CQE_COMPLETED(cqe_fp) (cqe_fp->marker == 0x0)
#घोषणा BNX2X_SEED_CQE(cqe_fp) (cqe_fp->marker = 0xFFFFFFFF)
अटल अंतरभूत पूर्णांक bnx2x_has_rx_work(काष्ठा bnx2x_fastpath *fp)
अणु
	u16 cons;
	जोड़ eth_rx_cqe *cqe;
	काष्ठा eth_fast_path_rx_cqe *cqe_fp;

	cons = RCQ_BD(fp->rx_comp_cons);
	cqe = &fp->rx_comp_ring[cons];
	cqe_fp = &cqe->fast_path_cqe;
	वापस BNX2X_IS_CQE_COMPLETED(cqe_fp);
पूर्ण

/**
 * bnx2x_tx_disable - disables tx from stack poपूर्णांक of view
 *
 * @bp:		driver handle
 */
अटल अंतरभूत व्योम bnx2x_tx_disable(काष्ठा bnx2x *bp)
अणु
	netअगर_tx_disable(bp->dev);
	netअगर_carrier_off(bp->dev);
पूर्ण

अटल अंतरभूत व्योम bnx2x_मुक्त_rx_sge(काष्ठा bnx2x *bp,
				     काष्ठा bnx2x_fastpath *fp, u16 index)
अणु
	काष्ठा sw_rx_page *sw_buf = &fp->rx_page_ring[index];
	काष्ठा page *page = sw_buf->page;
	काष्ठा eth_rx_sge *sge = &fp->rx_sge_ring[index];

	/* Skip "next page" elements */
	अगर (!page)
		वापस;

	/* Since many fragments can share the same page, make sure to
	 * only unmap and मुक्त the page once.
	 */
	dma_unmap_page(&bp->pdev->dev, dma_unmap_addr(sw_buf, mapping),
		       SGE_PAGE_SIZE, DMA_FROM_DEVICE);

	put_page(page);

	sw_buf->page = शून्य;
	sge->addr_hi = 0;
	sge->addr_lo = 0;
पूर्ण

अटल अंतरभूत व्योम bnx2x_del_all_napi_cnic(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम_each_rx_queue_cnic(bp, i) अणु
		__netअगर_napi_del(&bnx2x_fp(bp, i, napi));
	पूर्ण
	synchronize_net();
पूर्ण

अटल अंतरभूत व्योम bnx2x_del_all_napi(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम_each_eth_queue(bp, i) अणु
		__netअगर_napi_del(&bnx2x_fp(bp, i, napi));
	पूर्ण
	synchronize_net();
पूर्ण

पूर्णांक bnx2x_set_पूर्णांक_mode(काष्ठा bnx2x *bp);

अटल अंतरभूत व्योम bnx2x_disable_msi(काष्ठा bnx2x *bp)
अणु
	अगर (bp->flags & USING_MSIX_FLAG) अणु
		pci_disable_msix(bp->pdev);
		bp->flags &= ~(USING_MSIX_FLAG | USING_SINGLE_MSIX_FLAG);
	पूर्ण अन्यथा अगर (bp->flags & USING_MSI_FLAG) अणु
		pci_disable_msi(bp->pdev);
		bp->flags &= ~USING_MSI_FLAG;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bnx2x_clear_sge_mask_next_elems(काष्ठा bnx2x_fastpath *fp)
अणु
	पूर्णांक i, j;

	क्रम (i = 1; i <= NUM_RX_SGE_PAGES; i++) अणु
		पूर्णांक idx = RX_SGE_CNT * i - 1;

		क्रम (j = 0; j < 2; j++) अणु
			BIT_VEC64_CLEAR_BIT(fp->sge_mask, idx);
			idx--;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bnx2x_init_sge_ring_bit_mask(काष्ठा bnx2x_fastpath *fp)
अणु
	/* Set the mask to all 1-s: it's faster to compare to 0 than to 0xf-s */
	स_रखो(fp->sge_mask, 0xff, माप(fp->sge_mask));

	/* Clear the two last indices in the page to 1:
	   these are the indices that correspond to the "next" element,
	   hence will never be indicated and should be हटाओd from
	   the calculations. */
	bnx2x_clear_sge_mask_next_elems(fp);
पूर्ण

/* note that we are not allocating a new buffer,
 * we are just moving one from cons to prod
 * we are not creating a new mapping,
 * so there is no need to check क्रम dma_mapping_error().
 */
अटल अंतरभूत व्योम bnx2x_reuse_rx_data(काष्ठा bnx2x_fastpath *fp,
				      u16 cons, u16 prod)
अणु
	काष्ठा sw_rx_bd *cons_rx_buf = &fp->rx_buf_ring[cons];
	काष्ठा sw_rx_bd *prod_rx_buf = &fp->rx_buf_ring[prod];
	काष्ठा eth_rx_bd *cons_bd = &fp->rx_desc_ring[cons];
	काष्ठा eth_rx_bd *prod_bd = &fp->rx_desc_ring[prod];

	dma_unmap_addr_set(prod_rx_buf, mapping,
			   dma_unmap_addr(cons_rx_buf, mapping));
	prod_rx_buf->data = cons_rx_buf->data;
	*prod_bd = *cons_bd;
पूर्ण

/************************* Init ******************************************/

/* वापसs func by VN क्रम current port */
अटल अंतरभूत पूर्णांक func_by_vn(काष्ठा bnx2x *bp, पूर्णांक vn)
अणु
	वापस 2 * vn + BP_PORT(bp);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_config_rss_eth(काष्ठा bnx2x *bp, bool config_hash)
अणु
	वापस bnx2x_rss(bp, &bp->rss_conf_obj, config_hash, true);
पूर्ण

/**
 * bnx2x_func_start - init function
 *
 * @bp:		driver handle
 *
 * Must be called beक्रमe sending CLIENT_SETUP क्रम the first client.
 */
अटल अंतरभूत पूर्णांक bnx2x_func_start(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_func_state_params func_params = अणुशून्यपूर्ण;
	काष्ठा bnx2x_func_start_params *start_params =
		&func_params.params.start;
	u16 port;

	/* Prepare parameters क्रम function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_START;

	/* Function parameters */
	start_params->mf_mode = bp->mf_mode;
	start_params->sd_vlan_tag = bp->mf_ov;

	/* Configure Ethertype क्रम BD mode */
	अगर (IS_MF_BD(bp)) अणु
		DP(NETIF_MSG_IFUP, "Configuring ethertype 0x88a8 for BD\n");
		start_params->sd_vlan_eth_type = ETH_P_8021AD;
		REG_WR(bp, PRS_REG_VLAN_TYPE_0, ETH_P_8021AD);
		REG_WR(bp, PBF_REG_VLAN_TYPE_0, ETH_P_8021AD);
		REG_WR(bp, NIG_REG_LLH_E1HOV_TYPE_1, ETH_P_8021AD);

		bnx2x_get_c2s_mapping(bp, start_params->c2s_pri,
				      &start_params->c2s_pri_शेष);
		start_params->c2s_pri_valid = 1;

		DP(NETIF_MSG_IFUP,
		   "Inner-to-Outer priority: %02x %02x %02x %02x %02x %02x %02x %02x [Default %02x]\n",
		   start_params->c2s_pri[0], start_params->c2s_pri[1],
		   start_params->c2s_pri[2], start_params->c2s_pri[3],
		   start_params->c2s_pri[4], start_params->c2s_pri[5],
		   start_params->c2s_pri[6], start_params->c2s_pri[7],
		   start_params->c2s_pri_शेष);
	पूर्ण

	अगर (CHIP_IS_E2(bp) || CHIP_IS_E3(bp))
		start_params->network_cos_mode = STATIC_COS;
	अन्यथा /* CHIP_IS_E1X */
		start_params->network_cos_mode = FW_WRR;
	अगर (bp->udp_tunnel_ports[BNX2X_UDP_PORT_VXLAN]) अणु
		port = bp->udp_tunnel_ports[BNX2X_UDP_PORT_VXLAN];
		start_params->vxlan_dst_port = port;
	पूर्ण
	अगर (bp->udp_tunnel_ports[BNX2X_UDP_PORT_GENEVE]) अणु
		port = bp->udp_tunnel_ports[BNX2X_UDP_PORT_GENEVE];
		start_params->geneve_dst_port = port;
	पूर्ण

	start_params->inner_rss = 1;

	अगर (IS_MF_UFP(bp) && BNX2X_IS_MF_SD_PROTOCOL_FCOE(bp)) अणु
		start_params->class_fail_ethtype = ETH_P_FIP;
		start_params->class_fail = 1;
		start_params->no_added_tags = 1;
	पूर्ण

	वापस bnx2x_func_state_change(bp, &func_params);
पूर्ण

/**
 * bnx2x_set_fw_mac_addr - fill in a MAC address in FW क्रमmat
 *
 * @fw_hi:	poपूर्णांकer to upper part
 * @fw_mid:	poपूर्णांकer to middle part
 * @fw_lo:	poपूर्णांकer to lower part
 * @mac:	poपूर्णांकer to MAC address
 */
अटल अंतरभूत व्योम bnx2x_set_fw_mac_addr(__le16 *fw_hi, __le16 *fw_mid,
					 __le16 *fw_lo, u8 *mac)
अणु
	((u8 *)fw_hi)[0]  = mac[1];
	((u8 *)fw_hi)[1]  = mac[0];
	((u8 *)fw_mid)[0] = mac[3];
	((u8 *)fw_mid)[1] = mac[2];
	((u8 *)fw_lo)[0]  = mac[5];
	((u8 *)fw_lo)[1]  = mac[4];
पूर्ण

अटल अंतरभूत व्योम bnx2x_मुक्त_rx_mem_pool(काष्ठा bnx2x *bp,
					  काष्ठा bnx2x_alloc_pool *pool)
अणु
	अगर (!pool->page)
		वापस;

	put_page(pool->page);

	pool->page = शून्य;
पूर्ण

अटल अंतरभूत व्योम bnx2x_मुक्त_rx_sge_range(काष्ठा bnx2x *bp,
					   काष्ठा bnx2x_fastpath *fp, पूर्णांक last)
अणु
	पूर्णांक i;

	अगर (fp->mode == TPA_MODE_DISABLED)
		वापस;

	क्रम (i = 0; i < last; i++)
		bnx2x_मुक्त_rx_sge(bp, fp, i);

	bnx2x_मुक्त_rx_mem_pool(bp, &fp->page_pool);
पूर्ण

अटल अंतरभूत व्योम bnx2x_set_next_page_rx_bd(काष्ठा bnx2x_fastpath *fp)
अणु
	पूर्णांक i;

	क्रम (i = 1; i <= NUM_RX_RINGS; i++) अणु
		काष्ठा eth_rx_bd *rx_bd;

		rx_bd = &fp->rx_desc_ring[RX_DESC_CNT * i - 2];
		rx_bd->addr_hi =
			cpu_to_le32(U64_HI(fp->rx_desc_mapping +
				    BCM_PAGE_SIZE*(i % NUM_RX_RINGS)));
		rx_bd->addr_lo =
			cpu_to_le32(U64_LO(fp->rx_desc_mapping +
				    BCM_PAGE_SIZE*(i % NUM_RX_RINGS)));
	पूर्ण
पूर्ण

/* Statistics ID are global per chip/path, जबतक Client IDs क्रम E1x are per
 * port.
 */
अटल अंतरभूत u8 bnx2x_stats_id(काष्ठा bnx2x_fastpath *fp)
अणु
	काष्ठा bnx2x *bp = fp->bp;
	अगर (!CHIP_IS_E1x(bp)) अणु
		/* there are special statistics counters क्रम FCoE 136..140 */
		अगर (IS_FCOE_FP(fp))
			वापस bp->cnic_base_cl_id + (bp->pf_num >> 1);
		वापस fp->cl_id;
	पूर्ण
	वापस fp->cl_id + BP_PORT(bp) * FP_SB_MAX_E1x;
पूर्ण

अटल अंतरभूत व्योम bnx2x_init_vlan_mac_fp_objs(काष्ठा bnx2x_fastpath *fp,
					       bnx2x_obj_type obj_type)
अणु
	काष्ठा bnx2x *bp = fp->bp;

	/* Configure classअगरication DBs */
	bnx2x_init_mac_obj(bp, &bnx2x_sp_obj(bp, fp).mac_obj, fp->cl_id,
			   fp->cid, BP_FUNC(bp), bnx2x_sp(bp, mac_rdata),
			   bnx2x_sp_mapping(bp, mac_rdata),
			   BNX2X_FILTER_MAC_PENDING,
			   &bp->sp_state, obj_type,
			   &bp->macs_pool);

	अगर (!CHIP_IS_E1x(bp))
		bnx2x_init_vlan_obj(bp, &bnx2x_sp_obj(bp, fp).vlan_obj,
				    fp->cl_id, fp->cid, BP_FUNC(bp),
				    bnx2x_sp(bp, vlan_rdata),
				    bnx2x_sp_mapping(bp, vlan_rdata),
				    BNX2X_FILTER_VLAN_PENDING,
				    &bp->sp_state, obj_type,
				    &bp->vlans_pool);
पूर्ण

/**
 * bnx2x_get_path_func_num - get number of active functions
 *
 * @bp:		driver handle
 *
 * Calculates the number of active (not hidden) functions on the
 * current path.
 */
अटल अंतरभूत u8 bnx2x_get_path_func_num(काष्ठा bnx2x *bp)
अणु
	u8 func_num = 0, i;

	/* 57710 has only one function per-port */
	अगर (CHIP_IS_E1(bp))
		वापस 1;

	/* Calculate a number of functions enabled on the current
	 * PATH/PORT.
	 */
	अगर (CHIP_REV_IS_SLOW(bp)) अणु
		अगर (IS_MF(bp))
			func_num = 4;
		अन्यथा
			func_num = 2;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < E1H_FUNC_MAX / 2; i++) अणु
			u32 func_config =
				MF_CFG_RD(bp,
					  func_mf_config[BP_PATH(bp) + 2 * i].
					  config);
			func_num +=
				((func_config & FUNC_MF_CFG_FUNC_HIDE) ? 0 : 1);
		पूर्ण
	पूर्ण

	WARN_ON(!func_num);

	वापस func_num;
पूर्ण

अटल अंतरभूत व्योम bnx2x_init_bp_objs(काष्ठा bnx2x *bp)
अणु
	/* RX_MODE controlling object */
	bnx2x_init_rx_mode_obj(bp, &bp->rx_mode_obj);

	/* multicast configuration controlling object */
	bnx2x_init_mcast_obj(bp, &bp->mcast_obj, bp->fp->cl_id, bp->fp->cid,
			     BP_FUNC(bp), BP_FUNC(bp),
			     bnx2x_sp(bp, mcast_rdata),
			     bnx2x_sp_mapping(bp, mcast_rdata),
			     BNX2X_FILTER_MCAST_PENDING, &bp->sp_state,
			     BNX2X_OBJ_TYPE_RX);

	/* Setup CAM credit pools */
	bnx2x_init_mac_credit_pool(bp, &bp->macs_pool, BP_FUNC(bp),
				   bnx2x_get_path_func_num(bp));

	bnx2x_init_vlan_credit_pool(bp, &bp->vlans_pool, BP_FUNC(bp),
				    bnx2x_get_path_func_num(bp));

	/* RSS configuration object */
	bnx2x_init_rss_config_obj(bp, &bp->rss_conf_obj, bp->fp->cl_id,
				  bp->fp->cid, BP_FUNC(bp), BP_FUNC(bp),
				  bnx2x_sp(bp, rss_rdata),
				  bnx2x_sp_mapping(bp, rss_rdata),
				  BNX2X_FILTER_RSS_CONF_PENDING, &bp->sp_state,
				  BNX2X_OBJ_TYPE_RX);

	bp->vlan_credit = PF_VLAN_CREDIT_E2(bp, bnx2x_get_path_func_num(bp));
पूर्ण

अटल अंतरभूत u8 bnx2x_fp_qzone_id(काष्ठा bnx2x_fastpath *fp)
अणु
	अगर (CHIP_IS_E1x(fp->bp))
		वापस fp->cl_id + BP_PORT(fp->bp) * ETH_MAX_RX_CLIENTS_E1H;
	अन्यथा
		वापस fp->cl_id;
पूर्ण

अटल अंतरभूत व्योम bnx2x_init_txdata(काष्ठा bnx2x *bp,
				     काष्ठा bnx2x_fp_txdata *txdata, u32 cid,
				     पूर्णांक txq_index, __le16 *tx_cons_sb,
				     काष्ठा bnx2x_fastpath *fp)
अणु
	txdata->cid = cid;
	txdata->txq_index = txq_index;
	txdata->tx_cons_sb = tx_cons_sb;
	txdata->parent_fp = fp;
	txdata->tx_ring_size = IS_FCOE_FP(fp) ? MAX_TX_AVAIL : bp->tx_ring_size;

	DP(NETIF_MSG_IFUP, "created tx data cid %d, txq %d\n",
	   txdata->cid, txdata->txq_index);
पूर्ण

अटल अंतरभूत u8 bnx2x_cnic_eth_cl_id(काष्ठा bnx2x *bp, u8 cl_idx)
अणु
	वापस bp->cnic_base_cl_id + cl_idx +
		(bp->pf_num >> 1) * BNX2X_MAX_CNIC_ETH_CL_ID_IDX;
पूर्ण

अटल अंतरभूत u8 bnx2x_cnic_fw_sb_id(काष्ठा bnx2x *bp)
अणु
	/* the 'first' id is allocated क्रम the cnic */
	वापस bp->base_fw_ndsb;
पूर्ण

अटल अंतरभूत u8 bnx2x_cnic_igu_sb_id(काष्ठा bnx2x *bp)
अणु
	वापस bp->igu_base_sb;
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_clean_tx_queue(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_fp_txdata *txdata)
अणु
	पूर्णांक cnt = 1000;

	जबतक (bnx2x_has_tx_work_unload(txdata)) अणु
		अगर (!cnt) अणु
			BNX2X_ERR("timeout waiting for queue[%d]: txdata->tx_pkt_prod(%d) != txdata->tx_pkt_cons(%d)\n",
				  txdata->txq_index, txdata->tx_pkt_prod,
				  txdata->tx_pkt_cons);
#अगर_घोषित BNX2X_STOP_ON_ERROR
			bnx2x_panic();
			वापस -EBUSY;
#अन्यथा
			अवरोध;
#पूर्ण_अगर
		पूर्ण
		cnt--;
		usleep_range(1000, 2000);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bnx2x_get_link_cfg_idx(काष्ठा bnx2x *bp);

अटल अंतरभूत व्योम __storm_स_रखो_काष्ठा(काष्ठा bnx2x *bp,
					 u32 addr, माप_प्रकार size, u32 *data)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < size/4; i++)
		REG_WR(bp, addr + (i * 4), data[i]);
पूर्ण

/**
 * bnx2x_रुको_sp_comp - रुको क्रम the outstanding SP commands.
 *
 * @bp:		driver handle
 * @mask:	bits that need to be cleared
 */
अटल अंतरभूत bool bnx2x_रुको_sp_comp(काष्ठा bnx2x *bp, अचिन्हित दीर्घ mask)
अणु
	पूर्णांक tout = 5000; /* Wait क्रम 5 secs tops */

	जबतक (tout--) अणु
		smp_mb();
		netअगर_addr_lock_bh(bp->dev);
		अगर (!(bp->sp_state & mask)) अणु
			netअगर_addr_unlock_bh(bp->dev);
			वापस true;
		पूर्ण
		netअगर_addr_unlock_bh(bp->dev);

		usleep_range(1000, 2000);
	पूर्ण

	smp_mb();

	netअगर_addr_lock_bh(bp->dev);
	अगर (bp->sp_state & mask) अणु
		BNX2X_ERR("Filtering completion timed out. sp_state 0x%lx, mask 0x%lx\n",
			  bp->sp_state, mask);
		netअगर_addr_unlock_bh(bp->dev);
		वापस false;
	पूर्ण
	netअगर_addr_unlock_bh(bp->dev);

	वापस true;
पूर्ण

/**
 * bnx2x_set_ctx_validation - set CDU context validation values
 *
 * @bp:		driver handle
 * @cxt:	context of the connection on the host memory
 * @cid:	SW CID of the connection to be configured
 */
व्योम bnx2x_set_ctx_validation(काष्ठा bnx2x *bp, काष्ठा eth_context *cxt,
			      u32 cid);

व्योम bnx2x_update_coalesce_sb_index(काष्ठा bnx2x *bp, u8 fw_sb_id,
				    u8 sb_index, u8 disable, u16 usec);
व्योम bnx2x_acquire_phy_lock(काष्ठा bnx2x *bp);
व्योम bnx2x_release_phy_lock(काष्ठा bnx2x *bp);

/**
 * bnx2x_extract_max_cfg - extract MAX BW part from MF configuration.
 *
 * @bp:		driver handle
 * @mf_cfg:	MF configuration
 *
 */
अटल अंतरभूत u16 bnx2x_extract_max_cfg(काष्ठा bnx2x *bp, u32 mf_cfg)
अणु
	u16 max_cfg = (mf_cfg & FUNC_MF_CFG_MAX_BW_MASK) >>
			      FUNC_MF_CFG_MAX_BW_SHIFT;
	अगर (!max_cfg) अणु
		DP(NETIF_MSG_IFUP | BNX2X_MSG_ETHTOOL,
		   "Max BW configured to 0 - using 100 instead\n");
		max_cfg = 100;
	पूर्ण
	वापस max_cfg;
पूर्ण

/* checks अगर HW supports GRO क्रम given MTU */
अटल अंतरभूत bool bnx2x_mtu_allows_gro(पूर्णांक mtu)
अणु
	/* gro frags per page */
	पूर्णांक fpp = SGE_PAGE_SIZE / (mtu - ETH_MAX_TPA_HEADER_SIZE);

	/*
	 * 1. Number of frags should not grow above MAX_SKB_FRAGS
	 * 2. Frag must fit the page
	 */
	वापस mtu <= SGE_PAGE_SIZE && (U_ETH_SGL_SIZE * fpp) <= MAX_SKB_FRAGS;
पूर्ण

/**
 * bnx2x_get_iscsi_info - update iSCSI params according to licensing info.
 *
 * @bp:		driver handle
 *
 */
व्योम bnx2x_get_iscsi_info(काष्ठा bnx2x *bp);

/**
 * bnx2x_link_sync_notअगरy - send notअगरication to other functions.
 *
 * @bp:		driver handle
 *
 */
अटल अंतरभूत व्योम bnx2x_link_sync_notअगरy(काष्ठा bnx2x *bp)
अणु
	पूर्णांक func;
	पूर्णांक vn;

	/* Set the attention towards other drivers on the same port */
	क्रम (vn = VN_0; vn < BP_MAX_VN_NUM(bp); vn++) अणु
		अगर (vn == BP_VN(bp))
			जारी;

		func = func_by_vn(bp, vn);
		REG_WR(bp, MISC_REG_AEU_GENERAL_ATTN_0 +
		       (LINK_SYNC_ATTENTION_BIT_FUNC_0 + func)*4, 1);
	पूर्ण
पूर्ण

/**
 * bnx2x_update_drv_flags - update flags in shmem
 *
 * @bp:		driver handle
 * @flags:	flags to update
 * @set:	set or clear
 *
 */
अटल अंतरभूत व्योम bnx2x_update_drv_flags(काष्ठा bnx2x *bp, u32 flags, u32 set)
अणु
	अगर (SHMEM2_HAS(bp, drv_flags)) अणु
		u32 drv_flags;
		bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_DRV_FLAGS);
		drv_flags = SHMEM2_RD(bp, drv_flags);

		अगर (set)
			SET_FLAGS(drv_flags, flags);
		अन्यथा
			RESET_FLAGS(drv_flags, flags);

		SHMEM2_WR(bp, drv_flags, drv_flags);
		DP(NETIF_MSG_IFUP, "drv_flags 0x%08x\n", drv_flags);
		bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_DRV_FLAGS);
	पूर्ण
पूर्ण



/**
 * bnx2x_fill_fw_str - Fill buffer with FW version string
 *
 * @bp:        driver handle
 * @buf:       अक्षरacter buffer to fill with the fw name
 * @buf_len:   length of the above buffer
 *
 */
व्योम bnx2x_fill_fw_str(काष्ठा bnx2x *bp, अक्षर *buf, माप_प्रकार buf_len);

पूर्णांक bnx2x_drain_tx_queues(काष्ठा bnx2x *bp);
व्योम bnx2x_squeeze_objects(काष्ठा bnx2x *bp);

व्योम bnx2x_schedule_sp_rtnl(काष्ठा bnx2x*, क्रमागत sp_rtnl_flag,
			    u32 verbose);

/**
 * bnx2x_set_os_driver_state - ग_लिखो driver state क्रम management FW usage
 *
 * @bp:		driver handle
 * @state:	OS_DRIVER_STATE_* value reflecting current driver state
 */
व्योम bnx2x_set_os_driver_state(काष्ठा bnx2x *bp, u32 state);

/**
 * bnx2x_nvram_पढ़ो - पढ़ोs data from nvram [might sleep]
 *
 * @bp:		driver handle
 * @offset:	byte offset in nvram
 * @ret_buf:	poपूर्णांकer to buffer where data is to be stored
 * @buf_size:   Length of 'ret_buf' in bytes
 */
पूर्णांक bnx2x_nvram_पढ़ो(काष्ठा bnx2x *bp, u32 offset, u8 *ret_buf,
		     पूर्णांक buf_size);

#पूर्ण_अगर /* BNX2X_CMN_H */
