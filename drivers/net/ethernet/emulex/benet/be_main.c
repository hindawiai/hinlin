<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005 - 2016 Broadcom
 * All rights reserved.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

#समावेश <linux/prefetch.h>
#समावेश <linux/module.h>
#समावेश "be.h"
#समावेश "be_cmds.h"
#समावेश <यंत्र/भाग64.h>
#समावेश <linux/aer.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <net/busy_poll.h>
#समावेश <net/vxlan.h>

MODULE_DESCRIPTION(DRV_DESC);
MODULE_AUTHOR("Emulex Corporation");
MODULE_LICENSE("GPL");

/* num_vfs module param is obsolete.
 * Use sysfs method to enable/disable VFs.
 */
अटल अचिन्हित पूर्णांक num_vfs;
module_param(num_vfs, uपूर्णांक, 0444);
MODULE_PARM_DESC(num_vfs, "Number of PCI VFs to initialize");

अटल uलघु rx_frag_size = 2048;
module_param(rx_frag_size, uलघु, 0444);
MODULE_PARM_DESC(rx_frag_size, "Size of a fragment that holds rcvd data.");

/* Per-module error detection/recovery workq shared across all functions.
 * Each function schedules its own work request on this shared workq.
 */
अटल काष्ठा workqueue_काष्ठा *be_err_recovery_workq;

अटल स्थिर काष्ठा pci_device_id be_dev_ids[] = अणु
#अगर_घोषित CONFIG_BE2NET_BE2
	अणु PCI_DEVICE(BE_VENDOR_ID, BE_DEVICE_ID1) पूर्ण,
	अणु PCI_DEVICE(BE_VENDOR_ID, OC_DEVICE_ID1) पूर्ण,
#पूर्ण_अगर /* CONFIG_BE2NET_BE2 */
#अगर_घोषित CONFIG_BE2NET_BE3
	अणु PCI_DEVICE(BE_VENDOR_ID, BE_DEVICE_ID2) पूर्ण,
	अणु PCI_DEVICE(BE_VENDOR_ID, OC_DEVICE_ID2) पूर्ण,
#पूर्ण_अगर /* CONFIG_BE2NET_BE3 */
#अगर_घोषित CONFIG_BE2NET_LANCER
	अणु PCI_DEVICE(EMULEX_VENDOR_ID, OC_DEVICE_ID3)पूर्ण,
	अणु PCI_DEVICE(EMULEX_VENDOR_ID, OC_DEVICE_ID4)पूर्ण,
#पूर्ण_अगर /* CONFIG_BE2NET_LANCER */
#अगर_घोषित CONFIG_BE2NET_SKYHAWK
	अणु PCI_DEVICE(EMULEX_VENDOR_ID, OC_DEVICE_ID5)पूर्ण,
	अणु PCI_DEVICE(EMULEX_VENDOR_ID, OC_DEVICE_ID6)पूर्ण,
#पूर्ण_अगर /* CONFIG_BE2NET_SKYHAWK */
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, be_dev_ids);

/* Workqueue used by all functions क्रम defering cmd calls to the adapter */
अटल काष्ठा workqueue_काष्ठा *be_wq;

/* UE Status Low CSR */
अटल स्थिर अक्षर * स्थिर ue_status_low_desc[] = अणु
	"CEV",
	"CTX",
	"DBUF",
	"ERX",
	"Host",
	"MPU",
	"NDMA",
	"PTC ",
	"RDMA ",
	"RXF ",
	"RXIPS ",
	"RXULP0 ",
	"RXULP1 ",
	"RXULP2 ",
	"TIM ",
	"TPOST ",
	"TPRE ",
	"TXIPS ",
	"TXULP0 ",
	"TXULP1 ",
	"UC ",
	"WDMA ",
	"TXULP2 ",
	"HOST1 ",
	"P0_OB_LINK ",
	"P1_OB_LINK ",
	"HOST_GPIO ",
	"MBOX ",
	"ERX2 ",
	"SPARE ",
	"JTAG ",
	"MPU_INTPEND "
पूर्ण;

/* UE Status High CSR */
अटल स्थिर अक्षर * स्थिर ue_status_hi_desc[] = अणु
	"LPCMEMHOST",
	"MGMT_MAC",
	"PCS0ONLINE",
	"MPU_IRAM",
	"PCS1ONLINE",
	"PCTL0",
	"PCTL1",
	"PMEM",
	"RR",
	"TXPB",
	"RXPP",
	"XAUI",
	"TXP",
	"ARM",
	"IPC",
	"HOST2",
	"HOST3",
	"HOST4",
	"HOST5",
	"HOST6",
	"HOST7",
	"ECRC",
	"Poison TLP",
	"NETC",
	"PERIPH",
	"LLTXULP",
	"D2P",
	"RCON",
	"LDMA",
	"LLTXP",
	"LLTXPB",
	"Unknown"
पूर्ण;

#घोषणा BE_VF_IF_EN_FLAGS	(BE_IF_FLAGS_UNTAGGED | \
				 BE_IF_FLAGS_BROADCAST | \
				 BE_IF_FLAGS_MULTICAST | \
				 BE_IF_FLAGS_PASS_L3L4_ERRORS)

अटल व्योम be_queue_मुक्त(काष्ठा be_adapter *adapter, काष्ठा be_queue_info *q)
अणु
	काष्ठा be_dma_mem *mem = &q->dma_mem;

	अगर (mem->va) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev, mem->size, mem->va,
				  mem->dma);
		mem->va = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक be_queue_alloc(काष्ठा be_adapter *adapter, काष्ठा be_queue_info *q,
			  u16 len, u16 entry_size)
अणु
	काष्ठा be_dma_mem *mem = &q->dma_mem;

	स_रखो(q, 0, माप(*q));
	q->len = len;
	q->entry_size = entry_size;
	mem->size = len * entry_size;
	mem->va = dma_alloc_coherent(&adapter->pdev->dev, mem->size,
				     &mem->dma, GFP_KERNEL);
	अगर (!mem->va)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम be_reg_पूर्णांकr_set(काष्ठा be_adapter *adapter, bool enable)
अणु
	u32 reg, enabled;

	pci_पढ़ो_config_dword(adapter->pdev, PCICFG_MEMBAR_CTRL_INT_CTRL_OFFSET,
			      &reg);
	enabled = reg & MEMBAR_CTRL_INT_CTRL_HOSTINTR_MASK;

	अगर (!enabled && enable)
		reg |= MEMBAR_CTRL_INT_CTRL_HOSTINTR_MASK;
	अन्यथा अगर (enabled && !enable)
		reg &= ~MEMBAR_CTRL_INT_CTRL_HOSTINTR_MASK;
	अन्यथा
		वापस;

	pci_ग_लिखो_config_dword(adapter->pdev,
			       PCICFG_MEMBAR_CTRL_INT_CTRL_OFFSET, reg);
पूर्ण

अटल व्योम be_पूर्णांकr_set(काष्ठा be_adapter *adapter, bool enable)
अणु
	पूर्णांक status = 0;

	/* On lancer पूर्णांकerrupts can't be controlled via this रेजिस्टर */
	अगर (lancer_chip(adapter))
		वापस;

	अगर (be_check_error(adapter, BE_ERROR_EEH))
		वापस;

	status = be_cmd_पूर्णांकr_set(adapter, enable);
	अगर (status)
		be_reg_पूर्णांकr_set(adapter, enable);
पूर्ण

अटल व्योम be_rxq_notअगरy(काष्ठा be_adapter *adapter, u16 qid, u16 posted)
अणु
	u32 val = 0;

	अगर (be_check_error(adapter, BE_ERROR_HW))
		वापस;

	val |= qid & DB_RQ_RING_ID_MASK;
	val |= posted << DB_RQ_NUM_POSTED_SHIFT;

	wmb();
	ioग_लिखो32(val, adapter->db + DB_RQ_OFFSET);
पूर्ण

अटल व्योम be_txq_notअगरy(काष्ठा be_adapter *adapter, काष्ठा be_tx_obj *txo,
			  u16 posted)
अणु
	u32 val = 0;

	अगर (be_check_error(adapter, BE_ERROR_HW))
		वापस;

	val |= txo->q.id & DB_TXULP_RING_ID_MASK;
	val |= (posted & DB_TXULP_NUM_POSTED_MASK) << DB_TXULP_NUM_POSTED_SHIFT;

	wmb();
	ioग_लिखो32(val, adapter->db + txo->db_offset);
पूर्ण

अटल व्योम be_eq_notअगरy(काष्ठा be_adapter *adapter, u16 qid,
			 bool arm, bool clear_पूर्णांक, u16 num_popped,
			 u32 eq_delay_mult_enc)
अणु
	u32 val = 0;

	val |= qid & DB_EQ_RING_ID_MASK;
	val |= ((qid & DB_EQ_RING_ID_EXT_MASK) << DB_EQ_RING_ID_EXT_MASK_SHIFT);

	अगर (be_check_error(adapter, BE_ERROR_HW))
		वापस;

	अगर (arm)
		val |= 1 << DB_EQ_REARM_SHIFT;
	अगर (clear_पूर्णांक)
		val |= 1 << DB_EQ_CLR_SHIFT;
	val |= 1 << DB_EQ_EVNT_SHIFT;
	val |= num_popped << DB_EQ_NUM_POPPED_SHIFT;
	val |= eq_delay_mult_enc << DB_EQ_R2I_DLY_SHIFT;
	ioग_लिखो32(val, adapter->db + DB_EQ_OFFSET);
पूर्ण

व्योम be_cq_notअगरy(काष्ठा be_adapter *adapter, u16 qid, bool arm, u16 num_popped)
अणु
	u32 val = 0;

	val |= qid & DB_CQ_RING_ID_MASK;
	val |= ((qid & DB_CQ_RING_ID_EXT_MASK) <<
			DB_CQ_RING_ID_EXT_MASK_SHIFT);

	अगर (be_check_error(adapter, BE_ERROR_HW))
		वापस;

	अगर (arm)
		val |= 1 << DB_CQ_REARM_SHIFT;
	val |= num_popped << DB_CQ_NUM_POPPED_SHIFT;
	ioग_लिखो32(val, adapter->db + DB_CQ_OFFSET);
पूर्ण

अटल पूर्णांक be_dev_mac_add(काष्ठा be_adapter *adapter, u8 *mac)
अणु
	पूर्णांक i;

	/* Check अगर mac has alपढ़ोy been added as part of uc-list */
	क्रम (i = 0; i < adapter->uc_macs; i++) अणु
		अगर (ether_addr_equal(adapter->uc_list[i].mac, mac)) अणु
			/* mac alपढ़ोy added, skip addition */
			adapter->pmac_id[0] = adapter->pmac_id[i + 1];
			वापस 0;
		पूर्ण
	पूर्ण

	वापस be_cmd_pmac_add(adapter, mac, adapter->अगर_handle,
			       &adapter->pmac_id[0], 0);
पूर्ण

अटल व्योम be_dev_mac_del(काष्ठा be_adapter *adapter, पूर्णांक pmac_id)
अणु
	पूर्णांक i;

	/* Skip deletion अगर the programmed mac is
	 * being used in uc-list
	 */
	क्रम (i = 0; i < adapter->uc_macs; i++) अणु
		अगर (adapter->pmac_id[i + 1] == pmac_id)
			वापस;
	पूर्ण
	be_cmd_pmac_del(adapter, adapter->अगर_handle, pmac_id, 0);
पूर्ण

अटल पूर्णांक be_mac_addr_set(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा sockaddr *addr = p;
	पूर्णांक status;
	u8 mac[ETH_ALEN];
	u32 old_pmac_id = adapter->pmac_id[0];

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	/* Proceed further only अगर, User provided MAC is dअगरferent
	 * from active MAC
	 */
	अगर (ether_addr_equal(addr->sa_data, adapter->dev_mac))
		वापस 0;

	/* BE3 VFs without FILTMGMT privilege are not allowed to set its MAC
	 * address
	 */
	अगर (BEx_chip(adapter) && be_virtfn(adapter) &&
	    !check_privilege(adapter, BE_PRIV_FILTMGMT))
		वापस -EPERM;

	/* अगर device is not running, copy MAC to netdev->dev_addr */
	अगर (!netअगर_running(netdev))
		जाओ करोne;

	/* The PMAC_ADD cmd may fail अगर the VF करोesn't have FILTMGMT
	 * privilege or अगर PF did not provision the new MAC address.
	 * On BE3, this cmd will always fail अगर the VF करोesn't have the
	 * FILTMGMT privilege. This failure is OK, only अगर the PF programmed
	 * the MAC क्रम the VF.
	 */
	mutex_lock(&adapter->rx_filter_lock);
	status = be_dev_mac_add(adapter, (u8 *)addr->sa_data);
	अगर (!status) अणु

		/* Delete the old programmed MAC. This call may fail अगर the
		 * old MAC was alपढ़ोy deleted by the PF driver.
		 */
		अगर (adapter->pmac_id[0] != old_pmac_id)
			be_dev_mac_del(adapter, old_pmac_id);
	पूर्ण

	mutex_unlock(&adapter->rx_filter_lock);
	/* Decide अगर the new MAC is successfully activated only after
	 * querying the FW
	 */
	status = be_cmd_get_active_mac(adapter, adapter->pmac_id[0], mac,
				       adapter->अगर_handle, true, 0);
	अगर (status)
		जाओ err;

	/* The MAC change did not happen, either due to lack of privilege
	 * or PF didn't pre-provision.
	 */
	अगर (!ether_addr_equal(addr->sa_data, mac)) अणु
		status = -EPERM;
		जाओ err;
	पूर्ण

	/* Remember currently programmed MAC */
	ether_addr_copy(adapter->dev_mac, addr->sa_data);
करोne:
	ether_addr_copy(netdev->dev_addr, addr->sa_data);
	dev_info(dev, "MAC address changed to %pM\n", addr->sa_data);
	वापस 0;
err:
	dev_warn(dev, "MAC address change to %pM failed\n", addr->sa_data);
	वापस status;
पूर्ण

/* BE2 supports only v0 cmd */
अटल व्योम *hw_stats_from_cmd(काष्ठा be_adapter *adapter)
अणु
	अगर (BE2_chip(adapter)) अणु
		काष्ठा be_cmd_resp_get_stats_v0 *cmd = adapter->stats_cmd.va;

		वापस &cmd->hw_stats;
	पूर्ण अन्यथा अगर (BE3_chip(adapter)) अणु
		काष्ठा be_cmd_resp_get_stats_v1 *cmd = adapter->stats_cmd.va;

		वापस &cmd->hw_stats;
	पूर्ण अन्यथा अणु
		काष्ठा be_cmd_resp_get_stats_v2 *cmd = adapter->stats_cmd.va;

		वापस &cmd->hw_stats;
	पूर्ण
पूर्ण

/* BE2 supports only v0 cmd */
अटल व्योम *be_erx_stats_from_cmd(काष्ठा be_adapter *adapter)
अणु
	अगर (BE2_chip(adapter)) अणु
		काष्ठा be_hw_stats_v0 *hw_stats = hw_stats_from_cmd(adapter);

		वापस &hw_stats->erx;
	पूर्ण अन्यथा अगर (BE3_chip(adapter)) अणु
		काष्ठा be_hw_stats_v1 *hw_stats = hw_stats_from_cmd(adapter);

		वापस &hw_stats->erx;
	पूर्ण अन्यथा अणु
		काष्ठा be_hw_stats_v2 *hw_stats = hw_stats_from_cmd(adapter);

		वापस &hw_stats->erx;
	पूर्ण
पूर्ण

अटल व्योम populate_be_v0_stats(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_hw_stats_v0 *hw_stats = hw_stats_from_cmd(adapter);
	काष्ठा be_pmem_stats *pmem_sts = &hw_stats->pmem;
	काष्ठा be_rxf_stats_v0 *rxf_stats = &hw_stats->rxf;
	काष्ठा be_port_rxf_stats_v0 *port_stats =
					&rxf_stats->port[adapter->port_num];
	काष्ठा be_drv_stats *drvs = &adapter->drv_stats;

	be_dws_le_to_cpu(hw_stats, माप(*hw_stats));
	drvs->rx_छोड़ो_frames = port_stats->rx_छोड़ो_frames;
	drvs->rx_crc_errors = port_stats->rx_crc_errors;
	drvs->rx_control_frames = port_stats->rx_control_frames;
	drvs->rx_in_range_errors = port_stats->rx_in_range_errors;
	drvs->rx_frame_too_दीर्घ = port_stats->rx_frame_too_दीर्घ;
	drvs->rx_dropped_runt = port_stats->rx_dropped_runt;
	drvs->rx_ip_checksum_errs = port_stats->rx_ip_checksum_errs;
	drvs->rx_tcp_checksum_errs = port_stats->rx_tcp_checksum_errs;
	drvs->rx_udp_checksum_errs = port_stats->rx_udp_checksum_errs;
	drvs->rxpp_fअगरo_overflow_drop = port_stats->rx_fअगरo_overflow;
	drvs->rx_dropped_tcp_length = port_stats->rx_dropped_tcp_length;
	drvs->rx_dropped_too_small = port_stats->rx_dropped_too_small;
	drvs->rx_dropped_too_लघु = port_stats->rx_dropped_too_लघु;
	drvs->rx_out_range_errors = port_stats->rx_out_range_errors;
	drvs->rx_input_fअगरo_overflow_drop = port_stats->rx_input_fअगरo_overflow;
	drvs->rx_dropped_header_too_small =
		port_stats->rx_dropped_header_too_small;
	drvs->rx_address_filtered =
					port_stats->rx_address_filtered +
					port_stats->rx_vlan_filtered;
	drvs->rx_alignment_symbol_errors =
		port_stats->rx_alignment_symbol_errors;

	drvs->tx_छोड़ोframes = port_stats->tx_छोड़ोframes;
	drvs->tx_controlframes = port_stats->tx_controlframes;

	अगर (adapter->port_num)
		drvs->jabber_events = rxf_stats->port1_jabber_events;
	अन्यथा
		drvs->jabber_events = rxf_stats->port0_jabber_events;
	drvs->rx_drops_no_pbuf = rxf_stats->rx_drops_no_pbuf;
	drvs->rx_drops_no_erx_descr = rxf_stats->rx_drops_no_erx_descr;
	drvs->क्रमwarded_packets = rxf_stats->क्रमwarded_packets;
	drvs->rx_drops_mtu = rxf_stats->rx_drops_mtu;
	drvs->rx_drops_no_tpre_descr = rxf_stats->rx_drops_no_tpre_descr;
	drvs->rx_drops_too_many_frags = rxf_stats->rx_drops_too_many_frags;
	adapter->drv_stats.eth_red_drops = pmem_sts->eth_red_drops;
पूर्ण

अटल व्योम populate_be_v1_stats(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_hw_stats_v1 *hw_stats = hw_stats_from_cmd(adapter);
	काष्ठा be_pmem_stats *pmem_sts = &hw_stats->pmem;
	काष्ठा be_rxf_stats_v1 *rxf_stats = &hw_stats->rxf;
	काष्ठा be_port_rxf_stats_v1 *port_stats =
					&rxf_stats->port[adapter->port_num];
	काष्ठा be_drv_stats *drvs = &adapter->drv_stats;

	be_dws_le_to_cpu(hw_stats, माप(*hw_stats));
	drvs->pmem_fअगरo_overflow_drop = port_stats->pmem_fअगरo_overflow_drop;
	drvs->rx_priority_छोड़ो_frames = port_stats->rx_priority_छोड़ो_frames;
	drvs->rx_छोड़ो_frames = port_stats->rx_छोड़ो_frames;
	drvs->rx_crc_errors = port_stats->rx_crc_errors;
	drvs->rx_control_frames = port_stats->rx_control_frames;
	drvs->rx_in_range_errors = port_stats->rx_in_range_errors;
	drvs->rx_frame_too_दीर्घ = port_stats->rx_frame_too_दीर्घ;
	drvs->rx_dropped_runt = port_stats->rx_dropped_runt;
	drvs->rx_ip_checksum_errs = port_stats->rx_ip_checksum_errs;
	drvs->rx_tcp_checksum_errs = port_stats->rx_tcp_checksum_errs;
	drvs->rx_udp_checksum_errs = port_stats->rx_udp_checksum_errs;
	drvs->rx_dropped_tcp_length = port_stats->rx_dropped_tcp_length;
	drvs->rx_dropped_too_small = port_stats->rx_dropped_too_small;
	drvs->rx_dropped_too_लघु = port_stats->rx_dropped_too_लघु;
	drvs->rx_out_range_errors = port_stats->rx_out_range_errors;
	drvs->rx_dropped_header_too_small =
		port_stats->rx_dropped_header_too_small;
	drvs->rx_input_fअगरo_overflow_drop =
		port_stats->rx_input_fअगरo_overflow_drop;
	drvs->rx_address_filtered = port_stats->rx_address_filtered;
	drvs->rx_alignment_symbol_errors =
		port_stats->rx_alignment_symbol_errors;
	drvs->rxpp_fअगरo_overflow_drop = port_stats->rxpp_fअगरo_overflow_drop;
	drvs->tx_छोड़ोframes = port_stats->tx_छोड़ोframes;
	drvs->tx_controlframes = port_stats->tx_controlframes;
	drvs->tx_priority_छोड़ोframes = port_stats->tx_priority_छोड़ोframes;
	drvs->jabber_events = port_stats->jabber_events;
	drvs->rx_drops_no_pbuf = rxf_stats->rx_drops_no_pbuf;
	drvs->rx_drops_no_erx_descr = rxf_stats->rx_drops_no_erx_descr;
	drvs->क्रमwarded_packets = rxf_stats->क्रमwarded_packets;
	drvs->rx_drops_mtu = rxf_stats->rx_drops_mtu;
	drvs->rx_drops_no_tpre_descr = rxf_stats->rx_drops_no_tpre_descr;
	drvs->rx_drops_too_many_frags = rxf_stats->rx_drops_too_many_frags;
	adapter->drv_stats.eth_red_drops = pmem_sts->eth_red_drops;
पूर्ण

अटल व्योम populate_be_v2_stats(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_hw_stats_v2 *hw_stats = hw_stats_from_cmd(adapter);
	काष्ठा be_pmem_stats *pmem_sts = &hw_stats->pmem;
	काष्ठा be_rxf_stats_v2 *rxf_stats = &hw_stats->rxf;
	काष्ठा be_port_rxf_stats_v2 *port_stats =
					&rxf_stats->port[adapter->port_num];
	काष्ठा be_drv_stats *drvs = &adapter->drv_stats;

	be_dws_le_to_cpu(hw_stats, माप(*hw_stats));
	drvs->pmem_fअगरo_overflow_drop = port_stats->pmem_fअगरo_overflow_drop;
	drvs->rx_priority_छोड़ो_frames = port_stats->rx_priority_छोड़ो_frames;
	drvs->rx_छोड़ो_frames = port_stats->rx_छोड़ो_frames;
	drvs->rx_crc_errors = port_stats->rx_crc_errors;
	drvs->rx_control_frames = port_stats->rx_control_frames;
	drvs->rx_in_range_errors = port_stats->rx_in_range_errors;
	drvs->rx_frame_too_दीर्घ = port_stats->rx_frame_too_दीर्घ;
	drvs->rx_dropped_runt = port_stats->rx_dropped_runt;
	drvs->rx_ip_checksum_errs = port_stats->rx_ip_checksum_errs;
	drvs->rx_tcp_checksum_errs = port_stats->rx_tcp_checksum_errs;
	drvs->rx_udp_checksum_errs = port_stats->rx_udp_checksum_errs;
	drvs->rx_dropped_tcp_length = port_stats->rx_dropped_tcp_length;
	drvs->rx_dropped_too_small = port_stats->rx_dropped_too_small;
	drvs->rx_dropped_too_लघु = port_stats->rx_dropped_too_लघु;
	drvs->rx_out_range_errors = port_stats->rx_out_range_errors;
	drvs->rx_dropped_header_too_small =
		port_stats->rx_dropped_header_too_small;
	drvs->rx_input_fअगरo_overflow_drop =
		port_stats->rx_input_fअगरo_overflow_drop;
	drvs->rx_address_filtered = port_stats->rx_address_filtered;
	drvs->rx_alignment_symbol_errors =
		port_stats->rx_alignment_symbol_errors;
	drvs->rxpp_fअगरo_overflow_drop = port_stats->rxpp_fअगरo_overflow_drop;
	drvs->tx_छोड़ोframes = port_stats->tx_छोड़ोframes;
	drvs->tx_controlframes = port_stats->tx_controlframes;
	drvs->tx_priority_छोड़ोframes = port_stats->tx_priority_छोड़ोframes;
	drvs->jabber_events = port_stats->jabber_events;
	drvs->rx_drops_no_pbuf = rxf_stats->rx_drops_no_pbuf;
	drvs->rx_drops_no_erx_descr = rxf_stats->rx_drops_no_erx_descr;
	drvs->क्रमwarded_packets = rxf_stats->क्रमwarded_packets;
	drvs->rx_drops_mtu = rxf_stats->rx_drops_mtu;
	drvs->rx_drops_no_tpre_descr = rxf_stats->rx_drops_no_tpre_descr;
	drvs->rx_drops_too_many_frags = rxf_stats->rx_drops_too_many_frags;
	adapter->drv_stats.eth_red_drops = pmem_sts->eth_red_drops;
	अगर (be_roce_supported(adapter)) अणु
		drvs->rx_roce_bytes_lsd = port_stats->roce_bytes_received_lsd;
		drvs->rx_roce_bytes_msd = port_stats->roce_bytes_received_msd;
		drvs->rx_roce_frames = port_stats->roce_frames_received;
		drvs->roce_drops_crc = port_stats->roce_drops_crc;
		drvs->roce_drops_payload_len =
			port_stats->roce_drops_payload_len;
	पूर्ण
पूर्ण

अटल व्योम populate_lancer_stats(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_drv_stats *drvs = &adapter->drv_stats;
	काष्ठा lancer_pport_stats *pport_stats = pport_stats_from_cmd(adapter);

	be_dws_le_to_cpu(pport_stats, माप(*pport_stats));
	drvs->rx_छोड़ो_frames = pport_stats->rx_छोड़ो_frames_lo;
	drvs->rx_crc_errors = pport_stats->rx_crc_errors_lo;
	drvs->rx_control_frames = pport_stats->rx_control_frames_lo;
	drvs->rx_in_range_errors = pport_stats->rx_in_range_errors;
	drvs->rx_frame_too_दीर्घ = pport_stats->rx_frames_too_दीर्घ_lo;
	drvs->rx_dropped_runt = pport_stats->rx_dropped_runt;
	drvs->rx_ip_checksum_errs = pport_stats->rx_ip_checksum_errors;
	drvs->rx_tcp_checksum_errs = pport_stats->rx_tcp_checksum_errors;
	drvs->rx_udp_checksum_errs = pport_stats->rx_udp_checksum_errors;
	drvs->rx_dropped_tcp_length =
				pport_stats->rx_dropped_invalid_tcp_length;
	drvs->rx_dropped_too_small = pport_stats->rx_dropped_too_small;
	drvs->rx_dropped_too_लघु = pport_stats->rx_dropped_too_लघु;
	drvs->rx_out_range_errors = pport_stats->rx_out_of_range_errors;
	drvs->rx_dropped_header_too_small =
				pport_stats->rx_dropped_header_too_small;
	drvs->rx_input_fअगरo_overflow_drop = pport_stats->rx_fअगरo_overflow;
	drvs->rx_address_filtered =
					pport_stats->rx_address_filtered +
					pport_stats->rx_vlan_filtered;
	drvs->rx_alignment_symbol_errors = pport_stats->rx_symbol_errors_lo;
	drvs->rxpp_fअगरo_overflow_drop = pport_stats->rx_fअगरo_overflow;
	drvs->tx_छोड़ोframes = pport_stats->tx_छोड़ो_frames_lo;
	drvs->tx_controlframes = pport_stats->tx_control_frames_lo;
	drvs->jabber_events = pport_stats->rx_jabbers;
	drvs->क्रमwarded_packets = pport_stats->num_क्रमwards_lo;
	drvs->rx_drops_mtu = pport_stats->rx_drops_mtu_lo;
	drvs->rx_drops_too_many_frags =
				pport_stats->rx_drops_too_many_frags_lo;
पूर्ण

अटल व्योम accumulate_16bit_val(u32 *acc, u16 val)
अणु
#घोषणा lo(x)			(x & 0xFFFF)
#घोषणा hi(x)			(x & 0xFFFF0000)
	bool wrapped = val < lo(*acc);
	u32 newacc = hi(*acc) + val;

	अगर (wrapped)
		newacc += 65536;
	WRITE_ONCE(*acc, newacc);
पूर्ण

अटल व्योम populate_erx_stats(काष्ठा be_adapter *adapter,
			       काष्ठा be_rx_obj *rxo, u32 erx_stat)
अणु
	अगर (!BEx_chip(adapter))
		rx_stats(rxo)->rx_drops_no_frags = erx_stat;
	अन्यथा
		/* below erx HW counter can actually wrap around after
		 * 65535. Driver accumulates a 32-bit value
		 */
		accumulate_16bit_val(&rx_stats(rxo)->rx_drops_no_frags,
				     (u16)erx_stat);
पूर्ण

व्योम be_parse_stats(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_erx_stats_v2 *erx = be_erx_stats_from_cmd(adapter);
	काष्ठा be_rx_obj *rxo;
	पूर्णांक i;
	u32 erx_stat;

	अगर (lancer_chip(adapter)) अणु
		populate_lancer_stats(adapter);
	पूर्ण अन्यथा अणु
		अगर (BE2_chip(adapter))
			populate_be_v0_stats(adapter);
		अन्यथा अगर (BE3_chip(adapter))
			/* क्रम BE3 */
			populate_be_v1_stats(adapter);
		अन्यथा
			populate_be_v2_stats(adapter);

		/* erx_v2 is दीर्घer than v0, v1. use v2 क्रम v0, v1 access */
		क्रम_all_rx_queues(adapter, rxo, i) अणु
			erx_stat = erx->rx_drops_no_fragments[rxo->q.id];
			populate_erx_stats(adapter, rxo, erx_stat);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम be_get_stats64(काष्ठा net_device *netdev,
			   काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा be_drv_stats *drvs = &adapter->drv_stats;
	काष्ठा be_rx_obj *rxo;
	काष्ठा be_tx_obj *txo;
	u64 pkts, bytes;
	अचिन्हित पूर्णांक start;
	पूर्णांक i;

	क्रम_all_rx_queues(adapter, rxo, i) अणु
		स्थिर काष्ठा be_rx_stats *rx_stats = rx_stats(rxo);

		करो अणु
			start = u64_stats_fetch_begin_irq(&rx_stats->sync);
			pkts = rx_stats(rxo)->rx_pkts;
			bytes = rx_stats(rxo)->rx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&rx_stats->sync, start));
		stats->rx_packets += pkts;
		stats->rx_bytes += bytes;
		stats->multicast += rx_stats(rxo)->rx_mcast_pkts;
		stats->rx_dropped += rx_stats(rxo)->rx_drops_no_skbs +
					rx_stats(rxo)->rx_drops_no_frags;
	पूर्ण

	क्रम_all_tx_queues(adapter, txo, i) अणु
		स्थिर काष्ठा be_tx_stats *tx_stats = tx_stats(txo);

		करो अणु
			start = u64_stats_fetch_begin_irq(&tx_stats->sync);
			pkts = tx_stats(txo)->tx_pkts;
			bytes = tx_stats(txo)->tx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&tx_stats->sync, start));
		stats->tx_packets += pkts;
		stats->tx_bytes += bytes;
	पूर्ण

	/* bad pkts received */
	stats->rx_errors = drvs->rx_crc_errors +
		drvs->rx_alignment_symbol_errors +
		drvs->rx_in_range_errors +
		drvs->rx_out_range_errors +
		drvs->rx_frame_too_दीर्घ +
		drvs->rx_dropped_too_small +
		drvs->rx_dropped_too_लघु +
		drvs->rx_dropped_header_too_small +
		drvs->rx_dropped_tcp_length +
		drvs->rx_dropped_runt;

	/* detailed rx errors */
	stats->rx_length_errors = drvs->rx_in_range_errors +
		drvs->rx_out_range_errors +
		drvs->rx_frame_too_दीर्घ;

	stats->rx_crc_errors = drvs->rx_crc_errors;

	/* frame alignment errors */
	stats->rx_frame_errors = drvs->rx_alignment_symbol_errors;

	/* receiver fअगरo overrun */
	/* drops_no_pbuf is no per i/f, it's per BE card */
	stats->rx_fअगरo_errors = drvs->rxpp_fअगरo_overflow_drop +
				drvs->rx_input_fअगरo_overflow_drop +
				drvs->rx_drops_no_pbuf;
पूर्ण

व्योम be_link_status_update(काष्ठा be_adapter *adapter, u8 link_status)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (!(adapter->flags & BE_FLAGS_LINK_STATUS_INIT)) अणु
		netअगर_carrier_off(netdev);
		adapter->flags |= BE_FLAGS_LINK_STATUS_INIT;
	पूर्ण

	अगर (link_status)
		netअगर_carrier_on(netdev);
	अन्यथा
		netअगर_carrier_off(netdev);

	netdev_info(netdev, "Link is %s\n", link_status ? "Up" : "Down");
पूर्ण

अटल पूर्णांक be_gso_hdr_len(काष्ठा sk_buff *skb)
अणु
	अगर (skb->encapsulation)
		वापस skb_inner_transport_offset(skb) +
		       inner_tcp_hdrlen(skb);
	वापस skb_transport_offset(skb) + tcp_hdrlen(skb);
पूर्ण

अटल व्योम be_tx_stats_update(काष्ठा be_tx_obj *txo, काष्ठा sk_buff *skb)
अणु
	काष्ठा be_tx_stats *stats = tx_stats(txo);
	u32 tx_pkts = skb_shinfo(skb)->gso_segs ? : 1;
	/* Account क्रम headers which get duplicated in TSO pkt */
	u32 dup_hdr_len = tx_pkts > 1 ? be_gso_hdr_len(skb) * (tx_pkts - 1) : 0;

	u64_stats_update_begin(&stats->sync);
	stats->tx_reqs++;
	stats->tx_bytes += skb->len + dup_hdr_len;
	stats->tx_pkts += tx_pkts;
	अगर (skb->encapsulation && skb->ip_summed == CHECKSUM_PARTIAL)
		stats->tx_vxlan_offload_pkts += tx_pkts;
	u64_stats_update_end(&stats->sync);
पूर्ण

/* Returns number of WRBs needed क्रम the skb */
अटल u32 skb_wrb_cnt(काष्ठा sk_buff *skb)
अणु
	/* +1 क्रम the header wrb */
	वापस 1 + (skb_headlen(skb) ? 1 : 0) + skb_shinfo(skb)->nr_frags;
पूर्ण

अटल अंतरभूत व्योम wrb_fill(काष्ठा be_eth_wrb *wrb, u64 addr, पूर्णांक len)
अणु
	wrb->frag_pa_hi = cpu_to_le32(upper_32_bits(addr));
	wrb->frag_pa_lo = cpu_to_le32(lower_32_bits(addr));
	wrb->frag_len = cpu_to_le32(len & ETH_WRB_FRAG_LEN_MASK);
	wrb->rsvd0 = 0;
पूर्ण

/* A dummy wrb is just all zeros. Using a separate routine क्रम dummy-wrb
 * to aव्योम the swap and shअगरt/mask operations in wrb_fill().
 */
अटल अंतरभूत व्योम wrb_fill_dummy(काष्ठा be_eth_wrb *wrb)
अणु
	wrb->frag_pa_hi = 0;
	wrb->frag_pa_lo = 0;
	wrb->frag_len = 0;
	wrb->rsvd0 = 0;
पूर्ण

अटल अंतरभूत u16 be_get_tx_vlan_tag(काष्ठा be_adapter *adapter,
				     काष्ठा sk_buff *skb)
अणु
	u8 vlan_prio;
	u16 vlan_tag;

	vlan_tag = skb_vlan_tag_get(skb);
	vlan_prio = skb_vlan_tag_get_prio(skb);
	/* If vlan priority provided by OS is NOT in available bmap */
	अगर (!(adapter->vlan_prio_bmap & (1 << vlan_prio)))
		vlan_tag = (vlan_tag & ~VLAN_PRIO_MASK) |
				adapter->recommended_prio_bits;

	वापस vlan_tag;
पूर्ण

/* Used only क्रम IP tunnel packets */
अटल u16 skb_inner_ip_proto(काष्ठा sk_buff *skb)
अणु
	वापस (inner_ip_hdr(skb)->version == 4) ?
		inner_ip_hdr(skb)->protocol : inner_ipv6_hdr(skb)->nexthdr;
पूर्ण

अटल u16 skb_ip_proto(काष्ठा sk_buff *skb)
अणु
	वापस (ip_hdr(skb)->version == 4) ?
		ip_hdr(skb)->protocol : ipv6_hdr(skb)->nexthdr;
पूर्ण

अटल अंतरभूत bool be_is_txq_full(काष्ठा be_tx_obj *txo)
अणु
	वापस atomic_पढ़ो(&txo->q.used) + BE_MAX_TX_FRAG_COUNT >= txo->q.len;
पूर्ण

अटल अंतरभूत bool be_can_txq_wake(काष्ठा be_tx_obj *txo)
अणु
	वापस atomic_पढ़ो(&txo->q.used) < txo->q.len / 2;
पूर्ण

अटल अंतरभूत bool be_is_tx_compl_pending(काष्ठा be_tx_obj *txo)
अणु
	वापस atomic_पढ़ो(&txo->q.used) > txo->pend_wrb_cnt;
पूर्ण

अटल व्योम be_get_wrb_params_from_skb(काष्ठा be_adapter *adapter,
				       काष्ठा sk_buff *skb,
				       काष्ठा be_wrb_params *wrb_params)
अणु
	u16 proto;

	अगर (skb_is_gso(skb)) अणु
		BE_WRB_F_SET(wrb_params->features, LSO, 1);
		wrb_params->lso_mss = skb_shinfo(skb)->gso_size;
		अगर (skb_is_gso_v6(skb) && !lancer_chip(adapter))
			BE_WRB_F_SET(wrb_params->features, LSO6, 1);
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		अगर (skb->encapsulation) अणु
			BE_WRB_F_SET(wrb_params->features, IPCS, 1);
			proto = skb_inner_ip_proto(skb);
		पूर्ण अन्यथा अणु
			proto = skb_ip_proto(skb);
		पूर्ण
		अगर (proto == IPPROTO_TCP)
			BE_WRB_F_SET(wrb_params->features, TCPCS, 1);
		अन्यथा अगर (proto == IPPROTO_UDP)
			BE_WRB_F_SET(wrb_params->features, UDPCS, 1);
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		BE_WRB_F_SET(wrb_params->features, VLAN, 1);
		wrb_params->vlan_tag = be_get_tx_vlan_tag(adapter, skb);
	पूर्ण

	BE_WRB_F_SET(wrb_params->features, CRC, 1);
पूर्ण

अटल व्योम wrb_fill_hdr(काष्ठा be_adapter *adapter,
			 काष्ठा be_eth_hdr_wrb *hdr,
			 काष्ठा be_wrb_params *wrb_params,
			 काष्ठा sk_buff *skb)
अणु
	स_रखो(hdr, 0, माप(*hdr));

	SET_TX_WRB_HDR_BITS(crc, hdr,
			    BE_WRB_F_GET(wrb_params->features, CRC));
	SET_TX_WRB_HDR_BITS(ipcs, hdr,
			    BE_WRB_F_GET(wrb_params->features, IPCS));
	SET_TX_WRB_HDR_BITS(tcpcs, hdr,
			    BE_WRB_F_GET(wrb_params->features, TCPCS));
	SET_TX_WRB_HDR_BITS(udpcs, hdr,
			    BE_WRB_F_GET(wrb_params->features, UDPCS));

	SET_TX_WRB_HDR_BITS(lso, hdr,
			    BE_WRB_F_GET(wrb_params->features, LSO));
	SET_TX_WRB_HDR_BITS(lso6, hdr,
			    BE_WRB_F_GET(wrb_params->features, LSO6));
	SET_TX_WRB_HDR_BITS(lso_mss, hdr, wrb_params->lso_mss);

	/* Hack to skip HW VLAN tagging needs evt = 1, compl = 0. When this
	 * hack is not needed, the evt bit is set जबतक ringing DB.
	 */
	SET_TX_WRB_HDR_BITS(event, hdr,
			    BE_WRB_F_GET(wrb_params->features, VLAN_SKIP_HW));
	SET_TX_WRB_HDR_BITS(vlan, hdr,
			    BE_WRB_F_GET(wrb_params->features, VLAN));
	SET_TX_WRB_HDR_BITS(vlan_tag, hdr, wrb_params->vlan_tag);

	SET_TX_WRB_HDR_BITS(num_wrb, hdr, skb_wrb_cnt(skb));
	SET_TX_WRB_HDR_BITS(len, hdr, skb->len);
	SET_TX_WRB_HDR_BITS(mgmt, hdr,
			    BE_WRB_F_GET(wrb_params->features, OS2BMC));
पूर्ण

अटल व्योम unmap_tx_frag(काष्ठा device *dev, काष्ठा be_eth_wrb *wrb,
			  bool unmap_single)
अणु
	dma_addr_t dma;
	u32 frag_len = le32_to_cpu(wrb->frag_len);


	dma = (u64)le32_to_cpu(wrb->frag_pa_hi) << 32 |
		(u64)le32_to_cpu(wrb->frag_pa_lo);
	अगर (frag_len) अणु
		अगर (unmap_single)
			dma_unmap_single(dev, dma, frag_len, DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_page(dev, dma, frag_len, DMA_TO_DEVICE);
	पूर्ण
पूर्ण

/* Grab a WRB header क्रम xmit */
अटल u32 be_tx_get_wrb_hdr(काष्ठा be_tx_obj *txo)
अणु
	u32 head = txo->q.head;

	queue_head_inc(&txo->q);
	वापस head;
पूर्ण

/* Set up the WRB header क्रम xmit */
अटल व्योम be_tx_setup_wrb_hdr(काष्ठा be_adapter *adapter,
				काष्ठा be_tx_obj *txo,
				काष्ठा be_wrb_params *wrb_params,
				काष्ठा sk_buff *skb, u16 head)
अणु
	u32 num_frags = skb_wrb_cnt(skb);
	काष्ठा be_queue_info *txq = &txo->q;
	काष्ठा be_eth_hdr_wrb *hdr = queue_index_node(txq, head);

	wrb_fill_hdr(adapter, hdr, wrb_params, skb);
	be_dws_cpu_to_le(hdr, माप(*hdr));

	BUG_ON(txo->sent_skb_list[head]);
	txo->sent_skb_list[head] = skb;
	txo->last_req_hdr = head;
	atomic_add(num_frags, &txq->used);
	txo->last_req_wrb_cnt = num_frags;
	txo->pend_wrb_cnt += num_frags;
पूर्ण

/* Setup a WRB fragment (buffer descriptor) क्रम xmit */
अटल व्योम be_tx_setup_wrb_frag(काष्ठा be_tx_obj *txo, dma_addr_t busaddr,
				 पूर्णांक len)
अणु
	काष्ठा be_eth_wrb *wrb;
	काष्ठा be_queue_info *txq = &txo->q;

	wrb = queue_head_node(txq);
	wrb_fill(wrb, busaddr, len);
	queue_head_inc(txq);
पूर्ण

/* Bring the queue back to the state it was in beक्रमe be_xmit_enqueue() routine
 * was invoked. The producer index is restored to the previous packet and the
 * WRBs of the current packet are unmapped. Invoked to handle tx setup errors.
 */
अटल व्योम be_xmit_restore(काष्ठा be_adapter *adapter,
			    काष्ठा be_tx_obj *txo, u32 head, bool map_single,
			    u32 copied)
अणु
	काष्ठा device *dev;
	काष्ठा be_eth_wrb *wrb;
	काष्ठा be_queue_info *txq = &txo->q;

	dev = &adapter->pdev->dev;
	txq->head = head;

	/* skip the first wrb (hdr); it's not mapped */
	queue_head_inc(txq);
	जबतक (copied) अणु
		wrb = queue_head_node(txq);
		unmap_tx_frag(dev, wrb, map_single);
		map_single = false;
		copied -= le32_to_cpu(wrb->frag_len);
		queue_head_inc(txq);
	पूर्ण

	txq->head = head;
पूर्ण

/* Enqueue the given packet क्रम transmit. This routine allocates WRBs क्रम the
 * packet, dma maps the packet buffers and sets up the WRBs. Returns the number
 * of WRBs used up by the packet.
 */
अटल u32 be_xmit_enqueue(काष्ठा be_adapter *adapter, काष्ठा be_tx_obj *txo,
			   काष्ठा sk_buff *skb,
			   काष्ठा be_wrb_params *wrb_params)
अणु
	u32 i, copied = 0, wrb_cnt = skb_wrb_cnt(skb);
	काष्ठा device *dev = &adapter->pdev->dev;
	bool map_single = false;
	u32 head;
	dma_addr_t busaddr;
	पूर्णांक len;

	head = be_tx_get_wrb_hdr(txo);

	अगर (skb->len > skb->data_len) अणु
		len = skb_headlen(skb);

		busaddr = dma_map_single(dev, skb->data, len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, busaddr))
			जाओ dma_err;
		map_single = true;
		be_tx_setup_wrb_frag(txo, busaddr, len);
		copied += len;
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		len = skb_frag_size(frag);

		busaddr = skb_frag_dma_map(dev, frag, 0, len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, busaddr))
			जाओ dma_err;
		be_tx_setup_wrb_frag(txo, busaddr, len);
		copied += len;
	पूर्ण

	be_tx_setup_wrb_hdr(adapter, txo, wrb_params, skb, head);

	be_tx_stats_update(txo, skb);
	वापस wrb_cnt;

dma_err:
	adapter->drv_stats.dma_map_errors++;
	be_xmit_restore(adapter, txo, head, map_single, copied);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक qnq_async_evt_rcvd(काष्ठा be_adapter *adapter)
अणु
	वापस adapter->flags & BE_FLAGS_QNQ_ASYNC_EVT_RCVD;
पूर्ण

अटल काष्ठा sk_buff *be_insert_vlan_in_pkt(काष्ठा be_adapter *adapter,
					     काष्ठा sk_buff *skb,
					     काष्ठा be_wrb_params
					     *wrb_params)
अणु
	bool insert_vlan = false;
	u16 vlan_tag = 0;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस skb;

	अगर (skb_vlan_tag_present(skb)) अणु
		vlan_tag = be_get_tx_vlan_tag(adapter, skb);
		insert_vlan = true;
	पूर्ण

	अगर (qnq_async_evt_rcvd(adapter) && adapter->pvid) अणु
		अगर (!insert_vlan) अणु
			vlan_tag = adapter->pvid;
			insert_vlan = true;
		पूर्ण
		/* f/w workaround to set skip_hw_vlan = 1, inक्रमms the F/W to
		 * skip VLAN insertion
		 */
		BE_WRB_F_SET(wrb_params->features, VLAN_SKIP_HW, 1);
	पूर्ण

	अगर (insert_vlan) अणु
		skb = vlan_insert_tag_set_proto(skb, htons(ETH_P_8021Q),
						vlan_tag);
		अगर (unlikely(!skb))
			वापस skb;
		__vlan_hwaccel_clear_tag(skb);
	पूर्ण

	/* Insert the outer VLAN, अगर any */
	अगर (adapter->qnq_vid) अणु
		vlan_tag = adapter->qnq_vid;
		skb = vlan_insert_tag_set_proto(skb, htons(ETH_P_8021Q),
						vlan_tag);
		अगर (unlikely(!skb))
			वापस skb;
		BE_WRB_F_SET(wrb_params->features, VLAN_SKIP_HW, 1);
	पूर्ण

	वापस skb;
पूर्ण

अटल bool be_ipv6_exthdr_check(काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *eh = (काष्ठा ethhdr *)skb->data;
	u16 offset = ETH_HLEN;

	अगर (eh->h_proto == htons(ETH_P_IPV6)) अणु
		काष्ठा ipv6hdr *ip6h = (काष्ठा ipv6hdr *)(skb->data + offset);

		offset += माप(काष्ठा ipv6hdr);
		अगर (ip6h->nexthdr != NEXTHDR_TCP &&
		    ip6h->nexthdr != NEXTHDR_UDP) अणु
			काष्ठा ipv6_opt_hdr *ehdr =
				(काष्ठा ipv6_opt_hdr *)(skb->data + offset);

			/* offending pkt: 2nd byte following IPv6 hdr is 0xff */
			अगर (ehdr->hdrlen == 0xff)
				वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक be_vlan_tag_tx_chk(काष्ठा be_adapter *adapter, काष्ठा sk_buff *skb)
अणु
	वापस skb_vlan_tag_present(skb) || adapter->pvid || adapter->qnq_vid;
पूर्ण

अटल पूर्णांक be_ipv6_tx_stall_chk(काष्ठा be_adapter *adapter, काष्ठा sk_buff *skb)
अणु
	वापस BE3_chip(adapter) && be_ipv6_exthdr_check(skb);
पूर्ण

अटल काष्ठा sk_buff *be_lancer_xmit_workarounds(काष्ठा be_adapter *adapter,
						  काष्ठा sk_buff *skb,
						  काष्ठा be_wrb_params
						  *wrb_params)
अणु
	काष्ठा vlan_ethhdr *veh = (काष्ठा vlan_ethhdr *)skb->data;
	अचिन्हित पूर्णांक eth_hdr_len;
	काष्ठा iphdr *ip;

	/* For padded packets, BE HW modअगरies tot_len field in IP header
	 * incorrecly when VLAN tag is inserted by HW.
	 * For padded packets, Lancer computes incorrect checksum.
	 */
	eth_hdr_len = ntohs(skb->protocol) == ETH_P_8021Q ?
						VLAN_ETH_HLEN : ETH_HLEN;
	अगर (skb->len <= 60 &&
	    (lancer_chip(adapter) || skb_vlan_tag_present(skb)) &&
	    is_ipv4_pkt(skb)) अणु
		ip = (काष्ठा iphdr *)ip_hdr(skb);
		pskb_trim(skb, eth_hdr_len + ntohs(ip->tot_len));
	पूर्ण

	/* If vlan tag is alपढ़ोy अंतरभूतd in the packet, skip HW VLAN
	 * tagging in pvid-tagging mode
	 */
	अगर (be_pvid_tagging_enabled(adapter) &&
	    veh->h_vlan_proto == htons(ETH_P_8021Q))
		BE_WRB_F_SET(wrb_params->features, VLAN_SKIP_HW, 1);

	/* HW has a bug wherein it will calculate CSUM क्रम VLAN
	 * pkts even though it is disabled.
	 * Manually insert VLAN in pkt.
	 */
	अगर (skb->ip_summed != CHECKSUM_PARTIAL &&
	    skb_vlan_tag_present(skb)) अणु
		skb = be_insert_vlan_in_pkt(adapter, skb, wrb_params);
		अगर (unlikely(!skb))
			जाओ err;
	पूर्ण

	/* HW may lockup when VLAN HW tagging is requested on
	 * certain ipv6 packets. Drop such pkts अगर the HW workaround to
	 * skip HW tagging is not enabled by FW.
	 */
	अगर (unlikely(be_ipv6_tx_stall_chk(adapter, skb) &&
		     (adapter->pvid || adapter->qnq_vid) &&
		     !qnq_async_evt_rcvd(adapter)))
		जाओ tx_drop;

	/* Manual VLAN tag insertion to prevent:
	 * ASIC lockup when the ASIC inserts VLAN tag पूर्णांकo
	 * certain ipv6 packets. Insert VLAN tags in driver,
	 * and set event, completion, vlan bits accordingly
	 * in the Tx WRB.
	 */
	अगर (be_ipv6_tx_stall_chk(adapter, skb) &&
	    be_vlan_tag_tx_chk(adapter, skb)) अणु
		skb = be_insert_vlan_in_pkt(adapter, skb, wrb_params);
		अगर (unlikely(!skb))
			जाओ err;
	पूर्ण

	वापस skb;
tx_drop:
	dev_kमुक्त_skb_any(skb);
err:
	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *be_xmit_workarounds(काष्ठा be_adapter *adapter,
					   काष्ठा sk_buff *skb,
					   काष्ठा be_wrb_params *wrb_params)
अणु
	पूर्णांक err;

	/* Lancer, SH and BE3 in SRIOV mode have a bug wherein
	 * packets that are 32b or less may cause a transmit stall
	 * on that port. The workaround is to pad such packets
	 * (len <= 32 bytes) to a minimum length of 36b.
	 */
	अगर (skb->len <= 32) अणु
		अगर (skb_put_padto(skb, 36))
			वापस शून्य;
	पूर्ण

	अगर (BEx_chip(adapter) || lancer_chip(adapter)) अणु
		skb = be_lancer_xmit_workarounds(adapter, skb, wrb_params);
		अगर (!skb)
			वापस शून्य;
	पूर्ण

	/* The stack can send us skbs with length greater than
	 * what the HW can handle. Trim the extra bytes.
	 */
	WARN_ON_ONCE(skb->len > BE_MAX_GSO_SIZE);
	err = pskb_trim(skb, BE_MAX_GSO_SIZE);
	WARN_ON(err);

	वापस skb;
पूर्ण

अटल व्योम be_xmit_flush(काष्ठा be_adapter *adapter, काष्ठा be_tx_obj *txo)
अणु
	काष्ठा be_queue_info *txq = &txo->q;
	काष्ठा be_eth_hdr_wrb *hdr = queue_index_node(txq, txo->last_req_hdr);

	/* Mark the last request eventable अगर it hasn't been marked alपढ़ोy */
	अगर (!(hdr->dw[2] & cpu_to_le32(TX_HDR_WRB_EVT)))
		hdr->dw[2] |= cpu_to_le32(TX_HDR_WRB_EVT | TX_HDR_WRB_COMPL);

	/* compose a dummy wrb अगर there are odd set of wrbs to notअगरy */
	अगर (!lancer_chip(adapter) && (txo->pend_wrb_cnt & 1)) अणु
		wrb_fill_dummy(queue_head_node(txq));
		queue_head_inc(txq);
		atomic_inc(&txq->used);
		txo->pend_wrb_cnt++;
		hdr->dw[2] &= ~cpu_to_le32(TX_HDR_WRB_NUM_MASK <<
					   TX_HDR_WRB_NUM_SHIFT);
		hdr->dw[2] |= cpu_to_le32((txo->last_req_wrb_cnt + 1) <<
					  TX_HDR_WRB_NUM_SHIFT);
	पूर्ण
	be_txq_notअगरy(adapter, txo, txo->pend_wrb_cnt);
	txo->pend_wrb_cnt = 0;
पूर्ण

/* OS2BMC related */

#घोषणा DHCP_CLIENT_PORT	68
#घोषणा DHCP_SERVER_PORT	67
#घोषणा NET_BIOS_PORT1		137
#घोषणा NET_BIOS_PORT2		138
#घोषणा DHCPV6_RAS_PORT		547

#घोषणा is_mc_allowed_on_bmc(adapter, eh)	\
	(!is_multicast_filt_enabled(adapter) &&	\
	 is_multicast_ether_addr(eh->h_dest) &&	\
	 !is_broadcast_ether_addr(eh->h_dest))

#घोषणा is_bc_allowed_on_bmc(adapter, eh)	\
	(!is_broadcast_filt_enabled(adapter) &&	\
	 is_broadcast_ether_addr(eh->h_dest))

#घोषणा is_arp_allowed_on_bmc(adapter, skb)	\
	(is_arp(skb) && is_arp_filt_enabled(adapter))

#घोषणा is_arp(skb)	(skb->protocol == htons(ETH_P_ARP))

#घोषणा is_arp_filt_enabled(adapter)	\
		(adapter->bmc_filt_mask & (BMC_FILT_BROADCAST_ARP))

#घोषणा is_dhcp_client_filt_enabled(adapter)	\
		(adapter->bmc_filt_mask & BMC_FILT_BROADCAST_DHCP_CLIENT)

#घोषणा is_dhcp_srvr_filt_enabled(adapter)	\
		(adapter->bmc_filt_mask & BMC_FILT_BROADCAST_DHCP_SERVER)

#घोषणा is_nbios_filt_enabled(adapter)	\
		(adapter->bmc_filt_mask & BMC_FILT_BROADCAST_NET_BIOS)

#घोषणा is_ipv6_na_filt_enabled(adapter)	\
		(adapter->bmc_filt_mask &	\
			BMC_FILT_MULTICAST_IPV6_NEIGH_ADVER)

#घोषणा is_ipv6_ra_filt_enabled(adapter)	\
		(adapter->bmc_filt_mask & BMC_FILT_MULTICAST_IPV6_RA)

#घोषणा is_ipv6_ras_filt_enabled(adapter)	\
		(adapter->bmc_filt_mask & BMC_FILT_MULTICAST_IPV6_RAS)

#घोषणा is_broadcast_filt_enabled(adapter)	\
		(adapter->bmc_filt_mask & BMC_FILT_BROADCAST)

#घोषणा is_multicast_filt_enabled(adapter)	\
		(adapter->bmc_filt_mask & BMC_FILT_MULTICAST)

अटल bool be_send_pkt_to_bmc(काष्ठा be_adapter *adapter,
			       काष्ठा sk_buff **skb)
अणु
	काष्ठा ethhdr *eh = (काष्ठा ethhdr *)(*skb)->data;
	bool os2bmc = false;

	अगर (!be_is_os2bmc_enabled(adapter))
		जाओ करोne;

	अगर (!is_multicast_ether_addr(eh->h_dest))
		जाओ करोne;

	अगर (is_mc_allowed_on_bmc(adapter, eh) ||
	    is_bc_allowed_on_bmc(adapter, eh) ||
	    is_arp_allowed_on_bmc(adapter, (*skb))) अणु
		os2bmc = true;
		जाओ करोne;
	पूर्ण

	अगर ((*skb)->protocol == htons(ETH_P_IPV6)) अणु
		काष्ठा ipv6hdr *hdr = ipv6_hdr((*skb));
		u8 nexthdr = hdr->nexthdr;

		अगर (nexthdr == IPPROTO_ICMPV6) अणु
			काष्ठा icmp6hdr *icmp6 = icmp6_hdr((*skb));

			चयन (icmp6->icmp6_type) अणु
			हाल NDISC_ROUTER_ADVERTISEMENT:
				os2bmc = is_ipv6_ra_filt_enabled(adapter);
				जाओ करोne;
			हाल NDISC_NEIGHBOUR_ADVERTISEMENT:
				os2bmc = is_ipv6_na_filt_enabled(adapter);
				जाओ करोne;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (is_udp_pkt((*skb))) अणु
		काष्ठा udphdr *udp = udp_hdr((*skb));

		चयन (ntohs(udp->dest)) अणु
		हाल DHCP_CLIENT_PORT:
			os2bmc = is_dhcp_client_filt_enabled(adapter);
			जाओ करोne;
		हाल DHCP_SERVER_PORT:
			os2bmc = is_dhcp_srvr_filt_enabled(adapter);
			जाओ करोne;
		हाल NET_BIOS_PORT1:
		हाल NET_BIOS_PORT2:
			os2bmc = is_nbios_filt_enabled(adapter);
			जाओ करोne;
		हाल DHCPV6_RAS_PORT:
			os2bmc = is_ipv6_ras_filt_enabled(adapter);
			जाओ करोne;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
करोne:
	/* For packets over a vlan, which are destined
	 * to BMC, asic expects the vlan to be अंतरभूत in the packet.
	 */
	अगर (os2bmc)
		*skb = be_insert_vlan_in_pkt(adapter, *skb, शून्य);

	वापस os2bmc;
पूर्ण

अटल netdev_tx_t be_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	u16 q_idx = skb_get_queue_mapping(skb);
	काष्ठा be_tx_obj *txo = &adapter->tx_obj[q_idx];
	काष्ठा be_wrb_params wrb_params = अणु 0 पूर्ण;
	bool flush = !netdev_xmit_more();
	u16 wrb_cnt;

	skb = be_xmit_workarounds(adapter, skb, &wrb_params);
	अगर (unlikely(!skb))
		जाओ drop;

	be_get_wrb_params_from_skb(adapter, skb, &wrb_params);

	wrb_cnt = be_xmit_enqueue(adapter, txo, skb, &wrb_params);
	अगर (unlikely(!wrb_cnt)) अणु
		dev_kमुक्त_skb_any(skb);
		जाओ drop;
	पूर्ण

	/* अगर os2bmc is enabled and अगर the pkt is destined to bmc,
	 * enqueue the pkt a 2nd समय with mgmt bit set.
	 */
	अगर (be_send_pkt_to_bmc(adapter, &skb)) अणु
		BE_WRB_F_SET(wrb_params.features, OS2BMC, 1);
		wrb_cnt = be_xmit_enqueue(adapter, txo, skb, &wrb_params);
		अगर (unlikely(!wrb_cnt))
			जाओ drop;
		अन्यथा
			skb_get(skb);
	पूर्ण

	अगर (be_is_txq_full(txo)) अणु
		netअगर_stop_subqueue(netdev, q_idx);
		tx_stats(txo)->tx_stops++;
	पूर्ण

	अगर (flush || __netअगर_subqueue_stopped(netdev, q_idx))
		be_xmit_flush(adapter, txo);

	वापस NETDEV_TX_OK;
drop:
	tx_stats(txo)->tx_drv_drops++;
	/* Flush the alपढ़ोy enqueued tx requests */
	अगर (flush && txo->pend_wrb_cnt)
		be_xmit_flush(adapter, txo);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम be_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा be_tx_obj *txo;
	काष्ठा sk_buff *skb;
	काष्ठा tcphdr *tcphdr;
	काष्ठा udphdr *udphdr;
	u32 *entry;
	पूर्णांक status;
	पूर्णांक i, j;

	क्रम_all_tx_queues(adapter, txo, i) अणु
		dev_info(dev, "TXQ Dump: %d H: %d T: %d used: %d, qid: 0x%x\n",
			 i, txo->q.head, txo->q.tail,
			 atomic_पढ़ो(&txo->q.used), txo->q.id);

		entry = txo->q.dma_mem.va;
		क्रम (j = 0; j < TX_Q_LEN * 4; j += 4) अणु
			अगर (entry[j] != 0 || entry[j + 1] != 0 ||
			    entry[j + 2] != 0 || entry[j + 3] != 0) अणु
				dev_info(dev, "Entry %d 0x%x 0x%x 0x%x 0x%x\n",
					 j, entry[j], entry[j + 1],
					 entry[j + 2], entry[j + 3]);
			पूर्ण
		पूर्ण

		entry = txo->cq.dma_mem.va;
		dev_info(dev, "TXCQ Dump: %d  H: %d T: %d used: %d\n",
			 i, txo->cq.head, txo->cq.tail,
			 atomic_पढ़ो(&txo->cq.used));
		क्रम (j = 0; j < TX_CQ_LEN * 4; j += 4) अणु
			अगर (entry[j] != 0 || entry[j + 1] != 0 ||
			    entry[j + 2] != 0 || entry[j + 3] != 0) अणु
				dev_info(dev, "Entry %d 0x%x 0x%x 0x%x 0x%x\n",
					 j, entry[j], entry[j + 1],
					 entry[j + 2], entry[j + 3]);
			पूर्ण
		पूर्ण

		क्रम (j = 0; j < TX_Q_LEN; j++) अणु
			अगर (txo->sent_skb_list[j]) अणु
				skb = txo->sent_skb_list[j];
				अगर (ip_hdr(skb)->protocol == IPPROTO_TCP) अणु
					tcphdr = tcp_hdr(skb);
					dev_info(dev, "TCP source port %d\n",
						 ntohs(tcphdr->source));
					dev_info(dev, "TCP dest port %d\n",
						 ntohs(tcphdr->dest));
					dev_info(dev, "TCP sequence num %d\n",
						 ntohs(tcphdr->seq));
					dev_info(dev, "TCP ack_seq %d\n",
						 ntohs(tcphdr->ack_seq));
				पूर्ण अन्यथा अगर (ip_hdr(skb)->protocol ==
					   IPPROTO_UDP) अणु
					udphdr = udp_hdr(skb);
					dev_info(dev, "UDP source port %d\n",
						 ntohs(udphdr->source));
					dev_info(dev, "UDP dest port %d\n",
						 ntohs(udphdr->dest));
				पूर्ण
				dev_info(dev, "skb[%d] %p len %d proto 0x%x\n",
					 j, skb, skb->len, skb->protocol);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (lancer_chip(adapter)) अणु
		dev_info(dev, "Initiating reset due to tx timeout\n");
		dev_info(dev, "Resetting adapter\n");
		status = lancer_physdev_ctrl(adapter,
					     PHYSDEV_CONTROL_FW_RESET_MASK);
		अगर (status)
			dev_err(dev, "Reset failed .. Reboot server\n");
	पूर्ण
पूर्ण

अटल अंतरभूत bool be_in_all_promisc(काष्ठा be_adapter *adapter)
अणु
	वापस (adapter->अगर_flags & BE_IF_FLAGS_ALL_PROMISCUOUS) ==
			BE_IF_FLAGS_ALL_PROMISCUOUS;
पूर्ण

अटल पूर्णांक be_set_vlan_promisc(काष्ठा be_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक status;

	अगर (adapter->अगर_flags & BE_IF_FLAGS_VLAN_PROMISCUOUS)
		वापस 0;

	status = be_cmd_rx_filter(adapter, BE_IF_FLAGS_VLAN_PROMISCUOUS, ON);
	अगर (!status) अणु
		dev_info(dev, "Enabled VLAN promiscuous mode\n");
		adapter->अगर_flags |= BE_IF_FLAGS_VLAN_PROMISCUOUS;
	पूर्ण अन्यथा अणु
		dev_err(dev, "Failed to enable VLAN promiscuous mode\n");
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक be_clear_vlan_promisc(काष्ठा be_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक status;

	status = be_cmd_rx_filter(adapter, BE_IF_FLAGS_VLAN_PROMISCUOUS, OFF);
	अगर (!status) अणु
		dev_info(dev, "Disabling VLAN promiscuous mode\n");
		adapter->अगर_flags &= ~BE_IF_FLAGS_VLAN_PROMISCUOUS;
	पूर्ण
	वापस status;
पूर्ण

/*
 * A max of 64 (BE_NUM_VLANS_SUPPORTED) vlans can be configured in BE.
 * If the user configures more, place BE in vlan promiscuous mode.
 */
अटल पूर्णांक be_vid_config(काष्ठा be_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	u16 vids[BE_NUM_VLANS_SUPPORTED];
	u16 num = 0, i = 0;
	पूर्णांक status = 0;

	/* No need to change the VLAN state अगर the I/F is in promiscuous */
	अगर (adapter->netdev->flags & IFF_PROMISC)
		वापस 0;

	अगर (adapter->vlans_added > be_max_vlans(adapter))
		वापस be_set_vlan_promisc(adapter);

	अगर (adapter->अगर_flags & BE_IF_FLAGS_VLAN_PROMISCUOUS) अणु
		status = be_clear_vlan_promisc(adapter);
		अगर (status)
			वापस status;
	पूर्ण
	/* Conकाष्ठा VLAN Table to give to HW */
	क्रम_each_set_bit(i, adapter->vids, VLAN_N_VID)
		vids[num++] = cpu_to_le16(i);

	status = be_cmd_vlan_config(adapter, adapter->अगर_handle, vids, num, 0);
	अगर (status) अणु
		dev_err(dev, "Setting HW VLAN filtering failed\n");
		/* Set to VLAN promisc mode as setting VLAN filter failed */
		अगर (addl_status(status) == MCC_ADDL_STATUS_INSUFFICIENT_VLANS ||
		    addl_status(status) ==
				MCC_ADDL_STATUS_INSUFFICIENT_RESOURCES)
			वापस be_set_vlan_promisc(adapter);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक be_vlan_add_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	पूर्णांक status = 0;

	mutex_lock(&adapter->rx_filter_lock);

	/* Packets with VID 0 are always received by Lancer by शेष */
	अगर (lancer_chip(adapter) && vid == 0)
		जाओ करोne;

	अगर (test_bit(vid, adapter->vids))
		जाओ करोne;

	set_bit(vid, adapter->vids);
	adapter->vlans_added++;

	status = be_vid_config(adapter);
करोne:
	mutex_unlock(&adapter->rx_filter_lock);
	वापस status;
पूर्ण

अटल पूर्णांक be_vlan_rem_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	पूर्णांक status = 0;

	mutex_lock(&adapter->rx_filter_lock);

	/* Packets with VID 0 are always received by Lancer by शेष */
	अगर (lancer_chip(adapter) && vid == 0)
		जाओ करोne;

	अगर (!test_bit(vid, adapter->vids))
		जाओ करोne;

	clear_bit(vid, adapter->vids);
	adapter->vlans_added--;

	status = be_vid_config(adapter);
करोne:
	mutex_unlock(&adapter->rx_filter_lock);
	वापस status;
पूर्ण

अटल व्योम be_set_all_promisc(काष्ठा be_adapter *adapter)
अणु
	be_cmd_rx_filter(adapter, BE_IF_FLAGS_ALL_PROMISCUOUS, ON);
	adapter->अगर_flags |= BE_IF_FLAGS_ALL_PROMISCUOUS;
पूर्ण

अटल व्योम be_set_mc_promisc(काष्ठा be_adapter *adapter)
अणु
	पूर्णांक status;

	अगर (adapter->अगर_flags & BE_IF_FLAGS_MCAST_PROMISCUOUS)
		वापस;

	status = be_cmd_rx_filter(adapter, BE_IF_FLAGS_MCAST_PROMISCUOUS, ON);
	अगर (!status)
		adapter->अगर_flags |= BE_IF_FLAGS_MCAST_PROMISCUOUS;
पूर्ण

अटल व्योम be_set_uc_promisc(काष्ठा be_adapter *adapter)
अणु
	पूर्णांक status;

	अगर (adapter->अगर_flags & BE_IF_FLAGS_PROMISCUOUS)
		वापस;

	status = be_cmd_rx_filter(adapter, BE_IF_FLAGS_PROMISCUOUS, ON);
	अगर (!status)
		adapter->अगर_flags |= BE_IF_FLAGS_PROMISCUOUS;
पूर्ण

अटल व्योम be_clear_uc_promisc(काष्ठा be_adapter *adapter)
अणु
	पूर्णांक status;

	अगर (!(adapter->अगर_flags & BE_IF_FLAGS_PROMISCUOUS))
		वापस;

	status = be_cmd_rx_filter(adapter, BE_IF_FLAGS_PROMISCUOUS, OFF);
	अगर (!status)
		adapter->अगर_flags &= ~BE_IF_FLAGS_PROMISCUOUS;
पूर्ण

/* The below 2 functions are the callback args क्रम __dev_mc_sync/dev_uc_sync().
 * We use a single callback function क्रम both sync and unsync. We really करोn't
 * add/हटाओ addresses through this callback. But, we use it to detect changes
 * to the uc/mc lists. The entire uc/mc list is programmed in be_set_rx_mode().
 */
अटल पूर्णांक be_uc_list_update(काष्ठा net_device *netdev,
			     स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	adapter->update_uc_list = true;
	वापस 0;
पूर्ण

अटल पूर्णांक be_mc_list_update(काष्ठा net_device *netdev,
			     स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	adapter->update_mc_list = true;
	वापस 0;
पूर्ण

अटल व्योम be_set_mc_list(काष्ठा be_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा netdev_hw_addr *ha;
	bool mc_promisc = false;
	पूर्णांक status;

	netअगर_addr_lock_bh(netdev);
	__dev_mc_sync(netdev, be_mc_list_update, be_mc_list_update);

	अगर (netdev->flags & IFF_PROMISC) अणु
		adapter->update_mc_list = false;
	पूर्ण अन्यथा अगर (netdev->flags & IFF_ALLMULTI ||
		   netdev_mc_count(netdev) > be_max_mc(adapter)) अणु
		/* Enable multicast promisc अगर num configured exceeds
		 * what we support
		 */
		mc_promisc = true;
		adapter->update_mc_list = false;
	पूर्ण अन्यथा अगर (adapter->अगर_flags & BE_IF_FLAGS_MCAST_PROMISCUOUS) अणु
		/* Update mc-list unconditionally अगर the अगरace was previously
		 * in mc-promisc mode and now is out of that mode.
		 */
		adapter->update_mc_list = true;
	पूर्ण

	अगर (adapter->update_mc_list) अणु
		पूर्णांक i = 0;

		/* cache the mc-list in adapter */
		netdev_क्रम_each_mc_addr(ha, netdev) अणु
			ether_addr_copy(adapter->mc_list[i].mac, ha->addr);
			i++;
		पूर्ण
		adapter->mc_count = netdev_mc_count(netdev);
	पूर्ण
	netअगर_addr_unlock_bh(netdev);

	अगर (mc_promisc) अणु
		be_set_mc_promisc(adapter);
	पूर्ण अन्यथा अगर (adapter->update_mc_list) अणु
		status = be_cmd_rx_filter(adapter, BE_IF_FLAGS_MULTICAST, ON);
		अगर (!status)
			adapter->अगर_flags &= ~BE_IF_FLAGS_MCAST_PROMISCUOUS;
		अन्यथा
			be_set_mc_promisc(adapter);

		adapter->update_mc_list = false;
	पूर्ण
पूर्ण

अटल व्योम be_clear_mc_list(काष्ठा be_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	__dev_mc_unsync(netdev, शून्य);
	be_cmd_rx_filter(adapter, BE_IF_FLAGS_MULTICAST, OFF);
	adapter->mc_count = 0;
पूर्ण

अटल पूर्णांक be_uc_mac_add(काष्ठा be_adapter *adapter, पूर्णांक uc_idx)
अणु
	अगर (ether_addr_equal(adapter->uc_list[uc_idx].mac, adapter->dev_mac)) अणु
		adapter->pmac_id[uc_idx + 1] = adapter->pmac_id[0];
		वापस 0;
	पूर्ण

	वापस be_cmd_pmac_add(adapter, adapter->uc_list[uc_idx].mac,
			       adapter->अगर_handle,
			       &adapter->pmac_id[uc_idx + 1], 0);
पूर्ण

अटल व्योम be_uc_mac_del(काष्ठा be_adapter *adapter, पूर्णांक pmac_id)
अणु
	अगर (pmac_id == adapter->pmac_id[0])
		वापस;

	be_cmd_pmac_del(adapter, adapter->अगर_handle, pmac_id, 0);
पूर्ण

अटल व्योम be_set_uc_list(काष्ठा be_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा netdev_hw_addr *ha;
	bool uc_promisc = false;
	पूर्णांक curr_uc_macs = 0, i;

	netअगर_addr_lock_bh(netdev);
	__dev_uc_sync(netdev, be_uc_list_update, be_uc_list_update);

	अगर (netdev->flags & IFF_PROMISC) अणु
		adapter->update_uc_list = false;
	पूर्ण अन्यथा अगर (netdev_uc_count(netdev) > (be_max_uc(adapter) - 1)) अणु
		uc_promisc = true;
		adapter->update_uc_list = false;
	पूर्ण  अन्यथा अगर (adapter->अगर_flags & BE_IF_FLAGS_PROMISCUOUS) अणु
		/* Update uc-list unconditionally अगर the अगरace was previously
		 * in uc-promisc mode and now is out of that mode.
		 */
		adapter->update_uc_list = true;
	पूर्ण

	अगर (adapter->update_uc_list) अणु
		/* cache the uc-list in adapter array */
		i = 0;
		netdev_क्रम_each_uc_addr(ha, netdev) अणु
			ether_addr_copy(adapter->uc_list[i].mac, ha->addr);
			i++;
		पूर्ण
		curr_uc_macs = netdev_uc_count(netdev);
	पूर्ण
	netअगर_addr_unlock_bh(netdev);

	अगर (uc_promisc) अणु
		be_set_uc_promisc(adapter);
	पूर्ण अन्यथा अगर (adapter->update_uc_list) अणु
		be_clear_uc_promisc(adapter);

		क्रम (i = 0; i < adapter->uc_macs; i++)
			be_uc_mac_del(adapter, adapter->pmac_id[i + 1]);

		क्रम (i = 0; i < curr_uc_macs; i++)
			be_uc_mac_add(adapter, i);
		adapter->uc_macs = curr_uc_macs;
		adapter->update_uc_list = false;
	पूर्ण
पूर्ण

अटल व्योम be_clear_uc_list(काष्ठा be_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक i;

	__dev_uc_unsync(netdev, शून्य);
	क्रम (i = 0; i < adapter->uc_macs; i++)
		be_uc_mac_del(adapter, adapter->pmac_id[i + 1]);

	adapter->uc_macs = 0;
पूर्ण

अटल व्योम __be_set_rx_mode(काष्ठा be_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	mutex_lock(&adapter->rx_filter_lock);

	अगर (netdev->flags & IFF_PROMISC) अणु
		अगर (!be_in_all_promisc(adapter))
			be_set_all_promisc(adapter);
	पूर्ण अन्यथा अगर (be_in_all_promisc(adapter)) अणु
		/* We need to re-program the vlan-list or clear
		 * vlan-promisc mode (अगर needed) when the पूर्णांकerface
		 * comes out of promisc mode.
		 */
		be_vid_config(adapter);
	पूर्ण

	be_set_uc_list(adapter);
	be_set_mc_list(adapter);

	mutex_unlock(&adapter->rx_filter_lock);
पूर्ण

अटल व्योम be_work_set_rx_mode(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा be_cmd_work *cmd_work =
				container_of(work, काष्ठा be_cmd_work, work);

	__be_set_rx_mode(cmd_work->adapter);
	kमुक्त(cmd_work);
पूर्ण

अटल पूर्णांक be_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा be_vf_cfg *vf_cfg = &adapter->vf_cfg[vf];
	पूर्णांक status;

	अगर (!sriov_enabled(adapter))
		वापस -EPERM;

	अगर (!is_valid_ether_addr(mac) || vf >= adapter->num_vfs)
		वापस -EINVAL;

	/* Proceed further only अगर user provided MAC is dअगरferent
	 * from active MAC
	 */
	अगर (ether_addr_equal(mac, vf_cfg->mac_addr))
		वापस 0;

	अगर (BEx_chip(adapter)) अणु
		be_cmd_pmac_del(adapter, vf_cfg->अगर_handle, vf_cfg->pmac_id,
				vf + 1);

		status = be_cmd_pmac_add(adapter, mac, vf_cfg->अगर_handle,
					 &vf_cfg->pmac_id, vf + 1);
	पूर्ण अन्यथा अणु
		status = be_cmd_set_mac(adapter, mac, vf_cfg->अगर_handle,
					vf + 1);
	पूर्ण

	अगर (status) अणु
		dev_err(&adapter->pdev->dev, "MAC %pM set on VF %d Failed: %#x",
			mac, vf, status);
		वापस be_cmd_status(status);
	पूर्ण

	ether_addr_copy(vf_cfg->mac_addr, mac);

	वापस 0;
पूर्ण

अटल पूर्णांक be_get_vf_config(काष्ठा net_device *netdev, पूर्णांक vf,
			    काष्ठा अगरla_vf_info *vi)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा be_vf_cfg *vf_cfg = &adapter->vf_cfg[vf];

	अगर (!sriov_enabled(adapter))
		वापस -EPERM;

	अगर (vf >= adapter->num_vfs)
		वापस -EINVAL;

	vi->vf = vf;
	vi->max_tx_rate = vf_cfg->tx_rate;
	vi->min_tx_rate = 0;
	vi->vlan = vf_cfg->vlan_tag & VLAN_VID_MASK;
	vi->qos = vf_cfg->vlan_tag >> VLAN_PRIO_SHIFT;
	स_नकल(&vi->mac, vf_cfg->mac_addr, ETH_ALEN);
	vi->linkstate = adapter->vf_cfg[vf].plink_tracking;
	vi->spoofchk = adapter->vf_cfg[vf].spoofchk;

	वापस 0;
पूर्ण

अटल पूर्णांक be_set_vf_tvt(काष्ठा be_adapter *adapter, पूर्णांक vf, u16 vlan)
अणु
	काष्ठा be_vf_cfg *vf_cfg = &adapter->vf_cfg[vf];
	u16 vids[BE_NUM_VLANS_SUPPORTED];
	पूर्णांक vf_अगर_id = vf_cfg->अगर_handle;
	पूर्णांक status;

	/* Enable Transparent VLAN Tagging */
	status = be_cmd_set_hsw_config(adapter, vlan, vf + 1, vf_अगर_id, 0, 0);
	अगर (status)
		वापस status;

	/* Clear pre-programmed VLAN filters on VF अगर any, अगर TVT is enabled */
	vids[0] = 0;
	status = be_cmd_vlan_config(adapter, vf_अगर_id, vids, 1, vf + 1);
	अगर (!status)
		dev_info(&adapter->pdev->dev,
			 "Cleared guest VLANs on VF%d", vf);

	/* After TVT is enabled, disallow VFs to program VLAN filters */
	अगर (vf_cfg->privileges & BE_PRIV_FILTMGMT) अणु
		status = be_cmd_set_fn_privileges(adapter, vf_cfg->privileges &
						  ~BE_PRIV_FILTMGMT, vf + 1);
		अगर (!status)
			vf_cfg->privileges &= ~BE_PRIV_FILTMGMT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक be_clear_vf_tvt(काष्ठा be_adapter *adapter, पूर्णांक vf)
अणु
	काष्ठा be_vf_cfg *vf_cfg = &adapter->vf_cfg[vf];
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक status;

	/* Reset Transparent VLAN Tagging. */
	status = be_cmd_set_hsw_config(adapter, BE_RESET_VLAN_TAG_ID, vf + 1,
				       vf_cfg->अगर_handle, 0, 0);
	अगर (status)
		वापस status;

	/* Allow VFs to program VLAN filtering */
	अगर (!(vf_cfg->privileges & BE_PRIV_FILTMGMT)) अणु
		status = be_cmd_set_fn_privileges(adapter, vf_cfg->privileges |
						  BE_PRIV_FILTMGMT, vf + 1);
		अगर (!status) अणु
			vf_cfg->privileges |= BE_PRIV_FILTMGMT;
			dev_info(dev, "VF%d: FILTMGMT priv enabled", vf);
		पूर्ण
	पूर्ण

	dev_info(dev,
		 "Disable/re-enable i/f in VM to clear Transparent VLAN tag");
	वापस 0;
पूर्ण

अटल पूर्णांक be_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vf, u16 vlan, u8 qos,
			  __be16 vlan_proto)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा be_vf_cfg *vf_cfg = &adapter->vf_cfg[vf];
	पूर्णांक status;

	अगर (!sriov_enabled(adapter))
		वापस -EPERM;

	अगर (vf >= adapter->num_vfs || vlan > 4095 || qos > 7)
		वापस -EINVAL;

	अगर (vlan_proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;

	अगर (vlan || qos) अणु
		vlan |= qos << VLAN_PRIO_SHIFT;
		status = be_set_vf_tvt(adapter, vf, vlan);
	पूर्ण अन्यथा अणु
		status = be_clear_vf_tvt(adapter, vf);
	पूर्ण

	अगर (status) अणु
		dev_err(&adapter->pdev->dev,
			"VLAN %d config on VF %d failed : %#x\n", vlan, vf,
			status);
		वापस be_cmd_status(status);
	पूर्ण

	vf_cfg->vlan_tag = vlan;
	वापस 0;
पूर्ण

अटल पूर्णांक be_set_vf_tx_rate(काष्ठा net_device *netdev, पूर्णांक vf,
			     पूर्णांक min_tx_rate, पूर्णांक max_tx_rate)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक percent_rate, status = 0;
	u16 link_speed = 0;
	u8 link_status;

	अगर (!sriov_enabled(adapter))
		वापस -EPERM;

	अगर (vf >= adapter->num_vfs)
		वापस -EINVAL;

	अगर (min_tx_rate)
		वापस -EINVAL;

	अगर (!max_tx_rate)
		जाओ config_qos;

	status = be_cmd_link_status_query(adapter, &link_speed,
					  &link_status, 0);
	अगर (status)
		जाओ err;

	अगर (!link_status) अणु
		dev_err(dev, "TX-rate setting not allowed when link is down\n");
		status = -ENETDOWN;
		जाओ err;
	पूर्ण

	अगर (max_tx_rate < 100 || max_tx_rate > link_speed) अणु
		dev_err(dev, "TX-rate must be between 100 and %d Mbps\n",
			link_speed);
		status = -EINVAL;
		जाओ err;
	पूर्ण

	/* On Skyhawk the QOS setting must be करोne only as a % value */
	percent_rate = link_speed / 100;
	अगर (skyhawk_chip(adapter) && (max_tx_rate % percent_rate)) अणु
		dev_err(dev, "TX-rate must be a multiple of %d Mbps\n",
			percent_rate);
		status = -EINVAL;
		जाओ err;
	पूर्ण

config_qos:
	status = be_cmd_config_qos(adapter, max_tx_rate, link_speed, vf + 1);
	अगर (status)
		जाओ err;

	adapter->vf_cfg[vf].tx_rate = max_tx_rate;
	वापस 0;

err:
	dev_err(dev, "TX-rate setting of %dMbps on VF%d failed\n",
		max_tx_rate, vf);
	वापस be_cmd_status(status);
पूर्ण

अटल पूर्णांक be_set_vf_link_state(काष्ठा net_device *netdev, पूर्णांक vf,
				पूर्णांक link_state)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	पूर्णांक status;

	अगर (!sriov_enabled(adapter))
		वापस -EPERM;

	अगर (vf >= adapter->num_vfs)
		वापस -EINVAL;

	status = be_cmd_set_logical_link_config(adapter, link_state, vf+1);
	अगर (status) अणु
		dev_err(&adapter->pdev->dev,
			"Link state change on VF %d failed: %#x\n", vf, status);
		वापस be_cmd_status(status);
	पूर्ण

	adapter->vf_cfg[vf].plink_tracking = link_state;

	वापस 0;
पूर्ण

अटल पूर्णांक be_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf, bool enable)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा be_vf_cfg *vf_cfg = &adapter->vf_cfg[vf];
	u8 spoofchk;
	पूर्णांक status;

	अगर (!sriov_enabled(adapter))
		वापस -EPERM;

	अगर (vf >= adapter->num_vfs)
		वापस -EINVAL;

	अगर (BEx_chip(adapter))
		वापस -EOPNOTSUPP;

	अगर (enable == vf_cfg->spoofchk)
		वापस 0;

	spoofchk = enable ? ENABLE_MAC_SPOOFCHK : DISABLE_MAC_SPOOFCHK;

	status = be_cmd_set_hsw_config(adapter, 0, vf + 1, vf_cfg->अगर_handle,
				       0, spoofchk);
	अगर (status) अणु
		dev_err(&adapter->pdev->dev,
			"Spoofchk change on VF %d failed: %#x\n", vf, status);
		वापस be_cmd_status(status);
	पूर्ण

	vf_cfg->spoofchk = enable;
	वापस 0;
पूर्ण

अटल व्योम be_aic_update(काष्ठा be_aic_obj *aic, u64 rx_pkts, u64 tx_pkts,
			  uदीर्घ now)
अणु
	aic->rx_pkts_prev = rx_pkts;
	aic->tx_reqs_prev = tx_pkts;
	aic->jअगरfies = now;
पूर्ण

अटल पूर्णांक be_get_new_eqd(काष्ठा be_eq_obj *eqo)
अणु
	काष्ठा be_adapter *adapter = eqo->adapter;
	पूर्णांक eqd, start;
	काष्ठा be_aic_obj *aic;
	काष्ठा be_rx_obj *rxo;
	काष्ठा be_tx_obj *txo;
	u64 rx_pkts = 0, tx_pkts = 0;
	uदीर्घ now;
	u32 pps, delta;
	पूर्णांक i;

	aic = &adapter->aic_obj[eqo->idx];
	अगर (!adapter->aic_enabled) अणु
		अगर (aic->jअगरfies)
			aic->jअगरfies = 0;
		eqd = aic->et_eqd;
		वापस eqd;
	पूर्ण

	क्रम_all_rx_queues_on_eq(adapter, eqo, rxo, i) अणु
		करो अणु
			start = u64_stats_fetch_begin_irq(&rxo->stats.sync);
			rx_pkts += rxo->stats.rx_pkts;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&rxo->stats.sync, start));
	पूर्ण

	क्रम_all_tx_queues_on_eq(adapter, eqo, txo, i) अणु
		करो अणु
			start = u64_stats_fetch_begin_irq(&txo->stats.sync);
			tx_pkts += txo->stats.tx_reqs;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&txo->stats.sync, start));
	पूर्ण

	/* Skip, अगर wrapped around or first calculation */
	now = jअगरfies;
	अगर (!aic->jअगरfies || समय_beक्रमe(now, aic->jअगरfies) ||
	    rx_pkts < aic->rx_pkts_prev ||
	    tx_pkts < aic->tx_reqs_prev) अणु
		be_aic_update(aic, rx_pkts, tx_pkts, now);
		वापस aic->prev_eqd;
	पूर्ण

	delta = jअगरfies_to_msecs(now - aic->jअगरfies);
	अगर (delta == 0)
		वापस aic->prev_eqd;

	pps = (((u32)(rx_pkts - aic->rx_pkts_prev) * 1000) / delta) +
		(((u32)(tx_pkts - aic->tx_reqs_prev) * 1000) / delta);
	eqd = (pps / 15000) << 2;

	अगर (eqd < 8)
		eqd = 0;
	eqd = min_t(u32, eqd, aic->max_eqd);
	eqd = max_t(u32, eqd, aic->min_eqd);

	be_aic_update(aic, rx_pkts, tx_pkts, now);

	वापस eqd;
पूर्ण

/* For Skyhawk-R only */
अटल u32 be_get_eq_delay_mult_enc(काष्ठा be_eq_obj *eqo)
अणु
	काष्ठा be_adapter *adapter = eqo->adapter;
	काष्ठा be_aic_obj *aic = &adapter->aic_obj[eqo->idx];
	uदीर्घ now = jअगरfies;
	पूर्णांक eqd;
	u32 mult_enc;

	अगर (!adapter->aic_enabled)
		वापस 0;

	अगर (jअगरfies_to_msecs(now - aic->jअगरfies) < 1)
		eqd = aic->prev_eqd;
	अन्यथा
		eqd = be_get_new_eqd(eqo);

	अगर (eqd > 100)
		mult_enc = R2I_DLY_ENC_1;
	अन्यथा अगर (eqd > 60)
		mult_enc = R2I_DLY_ENC_2;
	अन्यथा अगर (eqd > 20)
		mult_enc = R2I_DLY_ENC_3;
	अन्यथा
		mult_enc = R2I_DLY_ENC_0;

	aic->prev_eqd = eqd;

	वापस mult_enc;
पूर्ण

व्योम be_eqd_update(काष्ठा be_adapter *adapter, bool क्रमce_update)
अणु
	काष्ठा be_set_eqd set_eqd[MAX_EVT_QS];
	काष्ठा be_aic_obj *aic;
	काष्ठा be_eq_obj *eqo;
	पूर्णांक i, num = 0, eqd;

	क्रम_all_evt_queues(adapter, eqo, i) अणु
		aic = &adapter->aic_obj[eqo->idx];
		eqd = be_get_new_eqd(eqo);
		अगर (क्रमce_update || eqd != aic->prev_eqd) अणु
			set_eqd[num].delay_multiplier = (eqd * 65)/100;
			set_eqd[num].eq_id = eqo->q.id;
			aic->prev_eqd = eqd;
			num++;
		पूर्ण
	पूर्ण

	अगर (num)
		be_cmd_modअगरy_eqd(adapter, set_eqd, num);
पूर्ण

अटल व्योम be_rx_stats_update(काष्ठा be_rx_obj *rxo,
			       काष्ठा be_rx_compl_info *rxcp)
अणु
	काष्ठा be_rx_stats *stats = rx_stats(rxo);

	u64_stats_update_begin(&stats->sync);
	stats->rx_compl++;
	stats->rx_bytes += rxcp->pkt_size;
	stats->rx_pkts++;
	अगर (rxcp->tunneled)
		stats->rx_vxlan_offload_pkts++;
	अगर (rxcp->pkt_type == BE_MULTICAST_PACKET)
		stats->rx_mcast_pkts++;
	अगर (rxcp->err)
		stats->rx_compl_err++;
	u64_stats_update_end(&stats->sync);
पूर्ण

अटल अंतरभूत bool csum_passed(काष्ठा be_rx_compl_info *rxcp)
अणु
	/* L4 checksum is not reliable क्रम non TCP/UDP packets.
	 * Also ignore ipcksm क्रम ipv6 pkts
	 */
	वापस (rxcp->tcpf || rxcp->udpf) && rxcp->l4_csum &&
		(rxcp->ip_csum || rxcp->ipv6) && !rxcp->err;
पूर्ण

अटल काष्ठा be_rx_page_info *get_rx_page_info(काष्ठा be_rx_obj *rxo)
अणु
	काष्ठा be_adapter *adapter = rxo->adapter;
	काष्ठा be_rx_page_info *rx_page_info;
	काष्ठा be_queue_info *rxq = &rxo->q;
	u32 frag_idx = rxq->tail;

	rx_page_info = &rxo->page_info_tbl[frag_idx];
	BUG_ON(!rx_page_info->page);

	अगर (rx_page_info->last_frag) अणु
		dma_unmap_page(&adapter->pdev->dev,
			       dma_unmap_addr(rx_page_info, bus),
			       adapter->big_page_size, DMA_FROM_DEVICE);
		rx_page_info->last_frag = false;
	पूर्ण अन्यथा अणु
		dma_sync_single_क्रम_cpu(&adapter->pdev->dev,
					dma_unmap_addr(rx_page_info, bus),
					rx_frag_size, DMA_FROM_DEVICE);
	पूर्ण

	queue_tail_inc(rxq);
	atomic_dec(&rxq->used);
	वापस rx_page_info;
पूर्ण

/* Throwaway the data in the Rx completion */
अटल व्योम be_rx_compl_discard(काष्ठा be_rx_obj *rxo,
				काष्ठा be_rx_compl_info *rxcp)
अणु
	काष्ठा be_rx_page_info *page_info;
	u16 i, num_rcvd = rxcp->num_rcvd;

	क्रम (i = 0; i < num_rcvd; i++) अणु
		page_info = get_rx_page_info(rxo);
		put_page(page_info->page);
		स_रखो(page_info, 0, माप(*page_info));
	पूर्ण
पूर्ण

/*
 * skb_fill_rx_data क्रमms a complete skb क्रम an ether frame
 * indicated by rxcp.
 */
अटल व्योम skb_fill_rx_data(काष्ठा be_rx_obj *rxo, काष्ठा sk_buff *skb,
			     काष्ठा be_rx_compl_info *rxcp)
अणु
	काष्ठा be_rx_page_info *page_info;
	u16 i, j;
	u16 hdr_len, curr_frag_len, reमुख्यing;
	u8 *start;

	page_info = get_rx_page_info(rxo);
	start = page_address(page_info->page) + page_info->page_offset;
	prefetch(start);

	/* Copy data in the first descriptor of this completion */
	curr_frag_len = min(rxcp->pkt_size, rx_frag_size);

	skb->len = curr_frag_len;
	अगर (curr_frag_len <= BE_HDR_LEN) अणु /* tiny packet */
		स_नकल(skb->data, start, curr_frag_len);
		/* Complete packet has now been moved to data */
		put_page(page_info->page);
		skb->data_len = 0;
		skb->tail += curr_frag_len;
	पूर्ण अन्यथा अणु
		hdr_len = ETH_HLEN;
		स_नकल(skb->data, start, hdr_len);
		skb_shinfo(skb)->nr_frags = 1;
		skb_frag_set_page(skb, 0, page_info->page);
		skb_frag_off_set(&skb_shinfo(skb)->frags[0],
				 page_info->page_offset + hdr_len);
		skb_frag_size_set(&skb_shinfo(skb)->frags[0],
				  curr_frag_len - hdr_len);
		skb->data_len = curr_frag_len - hdr_len;
		skb->truesize += rx_frag_size;
		skb->tail += hdr_len;
	पूर्ण
	page_info->page = शून्य;

	अगर (rxcp->pkt_size <= rx_frag_size) अणु
		BUG_ON(rxcp->num_rcvd != 1);
		वापस;
	पूर्ण

	/* More frags present क्रम this completion */
	reमुख्यing = rxcp->pkt_size - curr_frag_len;
	क्रम (i = 1, j = 0; i < rxcp->num_rcvd; i++) अणु
		page_info = get_rx_page_info(rxo);
		curr_frag_len = min(reमुख्यing, rx_frag_size);

		/* Coalesce all frags from the same physical page in one slot */
		अगर (page_info->page_offset == 0) अणु
			/* Fresh page */
			j++;
			skb_frag_set_page(skb, j, page_info->page);
			skb_frag_off_set(&skb_shinfo(skb)->frags[j],
					 page_info->page_offset);
			skb_frag_size_set(&skb_shinfo(skb)->frags[j], 0);
			skb_shinfo(skb)->nr_frags++;
		पूर्ण अन्यथा अणु
			put_page(page_info->page);
		पूर्ण

		skb_frag_size_add(&skb_shinfo(skb)->frags[j], curr_frag_len);
		skb->len += curr_frag_len;
		skb->data_len += curr_frag_len;
		skb->truesize += rx_frag_size;
		reमुख्यing -= curr_frag_len;
		page_info->page = शून्य;
	पूर्ण
	BUG_ON(j > MAX_SKB_FRAGS);
पूर्ण

/* Process the RX completion indicated by rxcp when GRO is disabled */
अटल व्योम be_rx_compl_process(काष्ठा be_rx_obj *rxo, काष्ठा napi_काष्ठा *napi,
				काष्ठा be_rx_compl_info *rxcp)
अणु
	काष्ठा be_adapter *adapter = rxo->adapter;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा sk_buff *skb;

	skb = netdev_alloc_skb_ip_align(netdev, BE_RX_SKB_ALLOC_SIZE);
	अगर (unlikely(!skb)) अणु
		rx_stats(rxo)->rx_drops_no_skbs++;
		be_rx_compl_discard(rxo, rxcp);
		वापस;
	पूर्ण

	skb_fill_rx_data(rxo, skb, rxcp);

	अगर (likely((netdev->features & NETIF_F_RXCSUM) && csum_passed(rxcp)))
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	अन्यथा
		skb_checksum_none_निश्चित(skb);

	skb->protocol = eth_type_trans(skb, netdev);
	skb_record_rx_queue(skb, rxo - &adapter->rx_obj[0]);
	अगर (netdev->features & NETIF_F_RXHASH)
		skb_set_hash(skb, rxcp->rss_hash, PKT_HASH_TYPE_L3);

	skb->csum_level = rxcp->tunneled;
	skb_mark_napi_id(skb, napi);

	अगर (rxcp->vlanf)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), rxcp->vlan_tag);

	netअगर_receive_skb(skb);
पूर्ण

/* Process the RX completion indicated by rxcp when GRO is enabled */
अटल व्योम be_rx_compl_process_gro(काष्ठा be_rx_obj *rxo,
				    काष्ठा napi_काष्ठा *napi,
				    काष्ठा be_rx_compl_info *rxcp)
अणु
	काष्ठा be_adapter *adapter = rxo->adapter;
	काष्ठा be_rx_page_info *page_info;
	काष्ठा sk_buff *skb = शून्य;
	u16 reमुख्यing, curr_frag_len;
	u16 i, j;

	skb = napi_get_frags(napi);
	अगर (!skb) अणु
		be_rx_compl_discard(rxo, rxcp);
		वापस;
	पूर्ण

	reमुख्यing = rxcp->pkt_size;
	क्रम (i = 0, j = -1; i < rxcp->num_rcvd; i++) अणु
		page_info = get_rx_page_info(rxo);

		curr_frag_len = min(reमुख्यing, rx_frag_size);

		/* Coalesce all frags from the same physical page in one slot */
		अगर (i == 0 || page_info->page_offset == 0) अणु
			/* First frag or Fresh page */
			j++;
			skb_frag_set_page(skb, j, page_info->page);
			skb_frag_off_set(&skb_shinfo(skb)->frags[j],
					 page_info->page_offset);
			skb_frag_size_set(&skb_shinfo(skb)->frags[j], 0);
		पूर्ण अन्यथा अणु
			put_page(page_info->page);
		पूर्ण
		skb_frag_size_add(&skb_shinfo(skb)->frags[j], curr_frag_len);
		skb->truesize += rx_frag_size;
		reमुख्यing -= curr_frag_len;
		स_रखो(page_info, 0, माप(*page_info));
	पूर्ण
	BUG_ON(j > MAX_SKB_FRAGS);

	skb_shinfo(skb)->nr_frags = j + 1;
	skb->len = rxcp->pkt_size;
	skb->data_len = rxcp->pkt_size;
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb_record_rx_queue(skb, rxo - &adapter->rx_obj[0]);
	अगर (adapter->netdev->features & NETIF_F_RXHASH)
		skb_set_hash(skb, rxcp->rss_hash, PKT_HASH_TYPE_L3);

	skb->csum_level = rxcp->tunneled;

	अगर (rxcp->vlanf)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), rxcp->vlan_tag);

	napi_gro_frags(napi);
पूर्ण

अटल व्योम be_parse_rx_compl_v1(काष्ठा be_eth_rx_compl *compl,
				 काष्ठा be_rx_compl_info *rxcp)
अणु
	rxcp->pkt_size = GET_RX_COMPL_V1_BITS(pktsize, compl);
	rxcp->vlanf = GET_RX_COMPL_V1_BITS(vtp, compl);
	rxcp->err = GET_RX_COMPL_V1_BITS(err, compl);
	rxcp->tcpf = GET_RX_COMPL_V1_BITS(tcpf, compl);
	rxcp->udpf = GET_RX_COMPL_V1_BITS(udpf, compl);
	rxcp->ip_csum = GET_RX_COMPL_V1_BITS(ipcksm, compl);
	rxcp->l4_csum = GET_RX_COMPL_V1_BITS(l4_cksm, compl);
	rxcp->ipv6 = GET_RX_COMPL_V1_BITS(ip_version, compl);
	rxcp->num_rcvd = GET_RX_COMPL_V1_BITS(numfrags, compl);
	rxcp->pkt_type = GET_RX_COMPL_V1_BITS(cast_enc, compl);
	rxcp->rss_hash = GET_RX_COMPL_V1_BITS(rsshash, compl);
	अगर (rxcp->vlanf) अणु
		rxcp->qnq = GET_RX_COMPL_V1_BITS(qnq, compl);
		rxcp->vlan_tag = GET_RX_COMPL_V1_BITS(vlan_tag, compl);
	पूर्ण
	rxcp->port = GET_RX_COMPL_V1_BITS(port, compl);
	rxcp->tunneled =
		GET_RX_COMPL_V1_BITS(tunneled, compl);
पूर्ण

अटल व्योम be_parse_rx_compl_v0(काष्ठा be_eth_rx_compl *compl,
				 काष्ठा be_rx_compl_info *rxcp)
अणु
	rxcp->pkt_size = GET_RX_COMPL_V0_BITS(pktsize, compl);
	rxcp->vlanf = GET_RX_COMPL_V0_BITS(vtp, compl);
	rxcp->err = GET_RX_COMPL_V0_BITS(err, compl);
	rxcp->tcpf = GET_RX_COMPL_V0_BITS(tcpf, compl);
	rxcp->udpf = GET_RX_COMPL_V0_BITS(udpf, compl);
	rxcp->ip_csum = GET_RX_COMPL_V0_BITS(ipcksm, compl);
	rxcp->l4_csum = GET_RX_COMPL_V0_BITS(l4_cksm, compl);
	rxcp->ipv6 = GET_RX_COMPL_V0_BITS(ip_version, compl);
	rxcp->num_rcvd = GET_RX_COMPL_V0_BITS(numfrags, compl);
	rxcp->pkt_type = GET_RX_COMPL_V0_BITS(cast_enc, compl);
	rxcp->rss_hash = GET_RX_COMPL_V0_BITS(rsshash, compl);
	अगर (rxcp->vlanf) अणु
		rxcp->qnq = GET_RX_COMPL_V0_BITS(qnq, compl);
		rxcp->vlan_tag = GET_RX_COMPL_V0_BITS(vlan_tag, compl);
	पूर्ण
	rxcp->port = GET_RX_COMPL_V0_BITS(port, compl);
	rxcp->ip_frag = GET_RX_COMPL_V0_BITS(ip_frag, compl);
पूर्ण

अटल काष्ठा be_rx_compl_info *be_rx_compl_get(काष्ठा be_rx_obj *rxo)
अणु
	काष्ठा be_eth_rx_compl *compl = queue_tail_node(&rxo->cq);
	काष्ठा be_rx_compl_info *rxcp = &rxo->rxcp;
	काष्ठा be_adapter *adapter = rxo->adapter;

	/* For checking the valid bit it is Ok to use either definition as the
	 * valid bit is at the same position in both v0 and v1 Rx compl */
	अगर (compl->dw[दुरत्व(काष्ठा amap_eth_rx_compl_v1, valid) / 32] == 0)
		वापस शून्य;

	rmb();
	be_dws_le_to_cpu(compl, माप(*compl));

	अगर (adapter->be3_native)
		be_parse_rx_compl_v1(compl, rxcp);
	अन्यथा
		be_parse_rx_compl_v0(compl, rxcp);

	अगर (rxcp->ip_frag)
		rxcp->l4_csum = 0;

	अगर (rxcp->vlanf) अणु
		/* In QNQ modes, अगर qnq bit is not set, then the packet was
		 * tagged only with the transparent outer vlan-tag and must
		 * not be treated as a vlan packet by host
		 */
		अगर (be_is_qnq_mode(adapter) && !rxcp->qnq)
			rxcp->vlanf = 0;

		अगर (!lancer_chip(adapter))
			rxcp->vlan_tag = swab16(rxcp->vlan_tag);

		अगर (adapter->pvid == (rxcp->vlan_tag & VLAN_VID_MASK) &&
		    !test_bit(rxcp->vlan_tag, adapter->vids))
			rxcp->vlanf = 0;
	पूर्ण

	/* As the compl has been parsed, reset it; we wont touch it again */
	compl->dw[दुरत्व(काष्ठा amap_eth_rx_compl_v1, valid) / 32] = 0;

	queue_tail_inc(&rxo->cq);
	वापस rxcp;
पूर्ण

अटल अंतरभूत काष्ठा page *be_alloc_pages(u32 size, gfp_t gfp)
अणु
	u32 order = get_order(size);

	अगर (order > 0)
		gfp |= __GFP_COMP;
	वापस  alloc_pages(gfp, order);
पूर्ण

/*
 * Allocate a page, split it to fragments of size rx_frag_size and post as
 * receive buffers to BE
 */
अटल व्योम be_post_rx_frags(काष्ठा be_rx_obj *rxo, gfp_t gfp, u32 frags_needed)
अणु
	काष्ठा be_adapter *adapter = rxo->adapter;
	काष्ठा be_rx_page_info *page_info = शून्य, *prev_page_info = शून्य;
	काष्ठा be_queue_info *rxq = &rxo->q;
	काष्ठा page *pagep = शून्य;
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा be_eth_rx_d *rxd;
	u64 page_dmaaddr = 0, frag_dmaaddr;
	u32 posted, page_offset = 0, notअगरy = 0;

	page_info = &rxo->page_info_tbl[rxq->head];
	क्रम (posted = 0; posted < frags_needed && !page_info->page; posted++) अणु
		अगर (!pagep) अणु
			pagep = be_alloc_pages(adapter->big_page_size, gfp);
			अगर (unlikely(!pagep)) अणु
				rx_stats(rxo)->rx_post_fail++;
				अवरोध;
			पूर्ण
			page_dmaaddr = dma_map_page(dev, pagep, 0,
						    adapter->big_page_size,
						    DMA_FROM_DEVICE);
			अगर (dma_mapping_error(dev, page_dmaaddr)) अणु
				put_page(pagep);
				pagep = शून्य;
				adapter->drv_stats.dma_map_errors++;
				अवरोध;
			पूर्ण
			page_offset = 0;
		पूर्ण अन्यथा अणु
			get_page(pagep);
			page_offset += rx_frag_size;
		पूर्ण
		page_info->page_offset = page_offset;
		page_info->page = pagep;

		rxd = queue_head_node(rxq);
		frag_dmaaddr = page_dmaaddr + page_info->page_offset;
		rxd->fragpa_lo = cpu_to_le32(frag_dmaaddr & 0xFFFFFFFF);
		rxd->fragpa_hi = cpu_to_le32(upper_32_bits(frag_dmaaddr));

		/* Any space left in the current big page क्रम another frag? */
		अगर ((page_offset + rx_frag_size + rx_frag_size) >
					adapter->big_page_size) अणु
			pagep = शून्य;
			page_info->last_frag = true;
			dma_unmap_addr_set(page_info, bus, page_dmaaddr);
		पूर्ण अन्यथा अणु
			dma_unmap_addr_set(page_info, bus, frag_dmaaddr);
		पूर्ण

		prev_page_info = page_info;
		queue_head_inc(rxq);
		page_info = &rxo->page_info_tbl[rxq->head];
	पूर्ण

	/* Mark the last frag of a page when we अवरोध out of the above loop
	 * with no more slots available in the RXQ
	 */
	अगर (pagep) अणु
		prev_page_info->last_frag = true;
		dma_unmap_addr_set(prev_page_info, bus, page_dmaaddr);
	पूर्ण

	अगर (posted) अणु
		atomic_add(posted, &rxq->used);
		अगर (rxo->rx_post_starved)
			rxo->rx_post_starved = false;
		करो अणु
			notअगरy = min(MAX_NUM_POST_ERX_DB, posted);
			be_rxq_notअगरy(adapter, rxq->id, notअगरy);
			posted -= notअगरy;
		पूर्ण जबतक (posted);
	पूर्ण अन्यथा अगर (atomic_पढ़ो(&rxq->used) == 0) अणु
		/* Let be_worker replenish when memory is available */
		rxo->rx_post_starved = true;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम be_update_tx_err(काष्ठा be_tx_obj *txo, u8 status)
अणु
	चयन (status) अणु
	हाल BE_TX_COMP_HDR_PARSE_ERR:
		tx_stats(txo)->tx_hdr_parse_err++;
		अवरोध;
	हाल BE_TX_COMP_NDMA_ERR:
		tx_stats(txo)->tx_dma_err++;
		अवरोध;
	हाल BE_TX_COMP_ACL_ERR:
		tx_stats(txo)->tx_spoof_check_err++;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम lancer_update_tx_err(काष्ठा be_tx_obj *txo, u8 status)
अणु
	चयन (status) अणु
	हाल LANCER_TX_COMP_LSO_ERR:
		tx_stats(txo)->tx_tso_err++;
		अवरोध;
	हाल LANCER_TX_COMP_HSW_DROP_MAC_ERR:
	हाल LANCER_TX_COMP_HSW_DROP_VLAN_ERR:
		tx_stats(txo)->tx_spoof_check_err++;
		अवरोध;
	हाल LANCER_TX_COMP_QINQ_ERR:
		tx_stats(txo)->tx_qinq_err++;
		अवरोध;
	हाल LANCER_TX_COMP_PARITY_ERR:
		tx_stats(txo)->tx_पूर्णांकernal_parity_err++;
		अवरोध;
	हाल LANCER_TX_COMP_DMA_ERR:
		tx_stats(txo)->tx_dma_err++;
		अवरोध;
	हाल LANCER_TX_COMP_SGE_ERR:
		tx_stats(txo)->tx_sge_err++;
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा be_tx_compl_info *be_tx_compl_get(काष्ठा be_adapter *adapter,
						काष्ठा be_tx_obj *txo)
अणु
	काष्ठा be_queue_info *tx_cq = &txo->cq;
	काष्ठा be_tx_compl_info *txcp = &txo->txcp;
	काष्ठा be_eth_tx_compl *compl = queue_tail_node(tx_cq);

	अगर (compl->dw[दुरत्व(काष्ठा amap_eth_tx_compl, valid) / 32] == 0)
		वापस शून्य;

	/* Ensure load ordering of valid bit dword and other dwords below */
	rmb();
	be_dws_le_to_cpu(compl, माप(*compl));

	txcp->status = GET_TX_COMPL_BITS(status, compl);
	txcp->end_index = GET_TX_COMPL_BITS(wrb_index, compl);

	अगर (txcp->status) अणु
		अगर (lancer_chip(adapter)) अणु
			lancer_update_tx_err(txo, txcp->status);
			/* Reset the adapter inहाल of TSO,
			 * SGE or Parity error
			 */
			अगर (txcp->status == LANCER_TX_COMP_LSO_ERR ||
			    txcp->status == LANCER_TX_COMP_PARITY_ERR ||
			    txcp->status == LANCER_TX_COMP_SGE_ERR)
				be_set_error(adapter, BE_ERROR_TX);
		पूर्ण अन्यथा अणु
			be_update_tx_err(txo, txcp->status);
		पूर्ण
	पूर्ण

	अगर (be_check_error(adapter, BE_ERROR_TX))
		वापस शून्य;

	compl->dw[दुरत्व(काष्ठा amap_eth_tx_compl, valid) / 32] = 0;
	queue_tail_inc(tx_cq);
	वापस txcp;
पूर्ण

अटल u16 be_tx_compl_process(काष्ठा be_adapter *adapter,
			       काष्ठा be_tx_obj *txo, u16 last_index)
अणु
	काष्ठा sk_buff **sent_skbs = txo->sent_skb_list;
	काष्ठा be_queue_info *txq = &txo->q;
	काष्ठा sk_buff *skb = शून्य;
	bool unmap_skb_hdr = false;
	काष्ठा be_eth_wrb *wrb;
	u16 num_wrbs = 0;
	u32 frag_index;

	करो अणु
		अगर (sent_skbs[txq->tail]) अणु
			/* Free skb from prev req */
			अगर (skb)
				dev_consume_skb_any(skb);
			skb = sent_skbs[txq->tail];
			sent_skbs[txq->tail] = शून्य;
			queue_tail_inc(txq);  /* skip hdr wrb */
			num_wrbs++;
			unmap_skb_hdr = true;
		पूर्ण
		wrb = queue_tail_node(txq);
		frag_index = txq->tail;
		unmap_tx_frag(&adapter->pdev->dev, wrb,
			      (unmap_skb_hdr && skb_headlen(skb)));
		unmap_skb_hdr = false;
		queue_tail_inc(txq);
		num_wrbs++;
	पूर्ण जबतक (frag_index != last_index);
	dev_consume_skb_any(skb);

	वापस num_wrbs;
पूर्ण

/* Return the number of events in the event queue */
अटल अंतरभूत पूर्णांक events_get(काष्ठा be_eq_obj *eqo)
अणु
	काष्ठा be_eq_entry *eqe;
	पूर्णांक num = 0;

	करो अणु
		eqe = queue_tail_node(&eqo->q);
		अगर (eqe->evt == 0)
			अवरोध;

		rmb();
		eqe->evt = 0;
		num++;
		queue_tail_inc(&eqo->q);
	पूर्ण जबतक (true);

	वापस num;
पूर्ण

/* Leaves the EQ is disarmed state */
अटल व्योम be_eq_clean(काष्ठा be_eq_obj *eqo)
अणु
	पूर्णांक num = events_get(eqo);

	be_eq_notअगरy(eqo->adapter, eqo->q.id, false, true, num, 0);
पूर्ण

/* Free posted rx buffers that were not used */
अटल व्योम be_rxq_clean(काष्ठा be_rx_obj *rxo)
अणु
	काष्ठा be_queue_info *rxq = &rxo->q;
	काष्ठा be_rx_page_info *page_info;

	जबतक (atomic_पढ़ो(&rxq->used) > 0) अणु
		page_info = get_rx_page_info(rxo);
		put_page(page_info->page);
		स_रखो(page_info, 0, माप(*page_info));
	पूर्ण
	BUG_ON(atomic_पढ़ो(&rxq->used));
	rxq->tail = 0;
	rxq->head = 0;
पूर्ण

अटल व्योम be_rx_cq_clean(काष्ठा be_rx_obj *rxo)
अणु
	काष्ठा be_queue_info *rx_cq = &rxo->cq;
	काष्ठा be_rx_compl_info *rxcp;
	काष्ठा be_adapter *adapter = rxo->adapter;
	पूर्णांक flush_रुको = 0;

	/* Consume pending rx completions.
	 * Wait क्रम the flush completion (identअगरied by zero num_rcvd)
	 * to arrive. Notअगरy CQ even when there are no more CQ entries
	 * क्रम HW to flush partially coalesced CQ entries.
	 * In Lancer, there is no need to रुको क्रम flush compl.
	 */
	क्रम (;;) अणु
		rxcp = be_rx_compl_get(rxo);
		अगर (!rxcp) अणु
			अगर (lancer_chip(adapter))
				अवरोध;

			अगर (flush_रुको++ > 50 ||
			    be_check_error(adapter,
					   BE_ERROR_HW)) अणु
				dev_warn(&adapter->pdev->dev,
					 "did not receive flush compl\n");
				अवरोध;
			पूर्ण
			be_cq_notअगरy(adapter, rx_cq->id, true, 0);
			mdelay(1);
		पूर्ण अन्यथा अणु
			be_rx_compl_discard(rxo, rxcp);
			be_cq_notअगरy(adapter, rx_cq->id, false, 1);
			अगर (rxcp->num_rcvd == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	/* After cleanup, leave the CQ in unarmed state */
	be_cq_notअगरy(adapter, rx_cq->id, false, 0);
पूर्ण

अटल व्योम be_tx_compl_clean(काष्ठा be_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	u16 cmpl = 0, समयo = 0, num_wrbs = 0;
	काष्ठा be_tx_compl_info *txcp;
	काष्ठा be_queue_info *txq;
	u32 end_idx, notअगरied_idx;
	काष्ठा be_tx_obj *txo;
	पूर्णांक i, pending_txqs;

	/* Stop polling क्रम compls when HW has been silent क्रम 10ms */
	करो अणु
		pending_txqs = adapter->num_tx_qs;

		क्रम_all_tx_queues(adapter, txo, i) अणु
			cmpl = 0;
			num_wrbs = 0;
			txq = &txo->q;
			जबतक ((txcp = be_tx_compl_get(adapter, txo))) अणु
				num_wrbs +=
					be_tx_compl_process(adapter, txo,
							    txcp->end_index);
				cmpl++;
			पूर्ण
			अगर (cmpl) अणु
				be_cq_notअगरy(adapter, txo->cq.id, false, cmpl);
				atomic_sub(num_wrbs, &txq->used);
				समयo = 0;
			पूर्ण
			अगर (!be_is_tx_compl_pending(txo))
				pending_txqs--;
		पूर्ण

		अगर (pending_txqs == 0 || ++समयo > 10 ||
		    be_check_error(adapter, BE_ERROR_HW))
			अवरोध;

		mdelay(1);
	पूर्ण जबतक (true);

	/* Free enqueued TX that was never notअगरied to HW */
	क्रम_all_tx_queues(adapter, txo, i) अणु
		txq = &txo->q;

		अगर (atomic_पढ़ो(&txq->used)) अणु
			dev_info(dev, "txq%d: cleaning %d pending tx-wrbs\n",
				 i, atomic_पढ़ो(&txq->used));
			notअगरied_idx = txq->tail;
			end_idx = txq->tail;
			index_adv(&end_idx, atomic_पढ़ो(&txq->used) - 1,
				  txq->len);
			/* Use the tx-compl process logic to handle requests
			 * that were not sent to the HW.
			 */
			num_wrbs = be_tx_compl_process(adapter, txo, end_idx);
			atomic_sub(num_wrbs, &txq->used);
			BUG_ON(atomic_पढ़ो(&txq->used));
			txo->pend_wrb_cnt = 0;
			/* Since hw was never notअगरied of these requests,
			 * reset TXQ indices
			 */
			txq->head = notअगरied_idx;
			txq->tail = notअगरied_idx;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम be_evt_queues_destroy(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_eq_obj *eqo;
	पूर्णांक i;

	क्रम_all_evt_queues(adapter, eqo, i) अणु
		अगर (eqo->q.created) अणु
			be_eq_clean(eqo);
			be_cmd_q_destroy(adapter, &eqo->q, QTYPE_EQ);
			netअगर_napi_del(&eqo->napi);
			मुक्त_cpumask_var(eqo->affinity_mask);
		पूर्ण
		be_queue_मुक्त(adapter, &eqo->q);
	पूर्ण
पूर्ण

अटल पूर्णांक be_evt_queues_create(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_queue_info *eq;
	काष्ठा be_eq_obj *eqo;
	काष्ठा be_aic_obj *aic;
	पूर्णांक i, rc;

	/* need enough EQs to service both RX and TX queues */
	adapter->num_evt_qs = min_t(u16, num_irqs(adapter),
				    max(adapter->cfg_num_rx_irqs,
					adapter->cfg_num_tx_irqs));

	adapter->aic_enabled = true;

	क्रम_all_evt_queues(adapter, eqo, i) अणु
		पूर्णांक numa_node = dev_to_node(&adapter->pdev->dev);

		aic = &adapter->aic_obj[i];
		eqo->adapter = adapter;
		eqo->idx = i;
		aic->max_eqd = BE_MAX_EQD;

		eq = &eqo->q;
		rc = be_queue_alloc(adapter, eq, EVNT_Q_LEN,
				    माप(काष्ठा be_eq_entry));
		अगर (rc)
			वापस rc;

		rc = be_cmd_eq_create(adapter, eqo);
		अगर (rc)
			वापस rc;

		अगर (!zalloc_cpumask_var(&eqo->affinity_mask, GFP_KERNEL))
			वापस -ENOMEM;
		cpumask_set_cpu(cpumask_local_spपढ़ो(i, numa_node),
				eqo->affinity_mask);
		netअगर_napi_add(adapter->netdev, &eqo->napi, be_poll,
			       BE_NAPI_WEIGHT);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम be_mcc_queues_destroy(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_queue_info *q;

	q = &adapter->mcc_obj.q;
	अगर (q->created)
		be_cmd_q_destroy(adapter, q, QTYPE_MCCQ);
	be_queue_मुक्त(adapter, q);

	q = &adapter->mcc_obj.cq;
	अगर (q->created)
		be_cmd_q_destroy(adapter, q, QTYPE_CQ);
	be_queue_मुक्त(adapter, q);
पूर्ण

/* Must be called only after TX qs are created as MCC shares TX EQ */
अटल पूर्णांक be_mcc_queues_create(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_queue_info *q, *cq;

	cq = &adapter->mcc_obj.cq;
	अगर (be_queue_alloc(adapter, cq, MCC_CQ_LEN,
			   माप(काष्ठा be_mcc_compl)))
		जाओ err;

	/* Use the शेष EQ क्रम MCC completions */
	अगर (be_cmd_cq_create(adapter, cq, &mcc_eqo(adapter)->q, true, 0))
		जाओ mcc_cq_मुक्त;

	q = &adapter->mcc_obj.q;
	अगर (be_queue_alloc(adapter, q, MCC_Q_LEN, माप(काष्ठा be_mcc_wrb)))
		जाओ mcc_cq_destroy;

	अगर (be_cmd_mccq_create(adapter, q, cq))
		जाओ mcc_q_मुक्त;

	वापस 0;

mcc_q_मुक्त:
	be_queue_मुक्त(adapter, q);
mcc_cq_destroy:
	be_cmd_q_destroy(adapter, cq, QTYPE_CQ);
mcc_cq_मुक्त:
	be_queue_मुक्त(adapter, cq);
err:
	वापस -1;
पूर्ण

अटल व्योम be_tx_queues_destroy(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_queue_info *q;
	काष्ठा be_tx_obj *txo;
	u8 i;

	क्रम_all_tx_queues(adapter, txo, i) अणु
		q = &txo->q;
		अगर (q->created)
			be_cmd_q_destroy(adapter, q, QTYPE_TXQ);
		be_queue_मुक्त(adapter, q);

		q = &txo->cq;
		अगर (q->created)
			be_cmd_q_destroy(adapter, q, QTYPE_CQ);
		be_queue_मुक्त(adapter, q);
	पूर्ण
पूर्ण

अटल पूर्णांक be_tx_qs_create(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_queue_info *cq;
	काष्ठा be_tx_obj *txo;
	काष्ठा be_eq_obj *eqo;
	पूर्णांक status, i;

	adapter->num_tx_qs = min(adapter->num_evt_qs, adapter->cfg_num_tx_irqs);

	क्रम_all_tx_queues(adapter, txo, i) अणु
		cq = &txo->cq;
		status = be_queue_alloc(adapter, cq, TX_CQ_LEN,
					माप(काष्ठा be_eth_tx_compl));
		अगर (status)
			वापस status;

		u64_stats_init(&txo->stats.sync);
		u64_stats_init(&txo->stats.sync_compl);

		/* If num_evt_qs is less than num_tx_qs, then more than
		 * one txq share an eq
		 */
		eqo = &adapter->eq_obj[i % adapter->num_evt_qs];
		status = be_cmd_cq_create(adapter, cq, &eqo->q, false, 3);
		अगर (status)
			वापस status;

		status = be_queue_alloc(adapter, &txo->q, TX_Q_LEN,
					माप(काष्ठा be_eth_wrb));
		अगर (status)
			वापस status;

		status = be_cmd_txq_create(adapter, txo);
		अगर (status)
			वापस status;

		netअगर_set_xps_queue(adapter->netdev, eqo->affinity_mask,
				    eqo->idx);
	पूर्ण

	dev_info(&adapter->pdev->dev, "created %d TX queue(s)\n",
		 adapter->num_tx_qs);
	वापस 0;
पूर्ण

अटल व्योम be_rx_cqs_destroy(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_queue_info *q;
	काष्ठा be_rx_obj *rxo;
	पूर्णांक i;

	क्रम_all_rx_queues(adapter, rxo, i) अणु
		q = &rxo->cq;
		अगर (q->created)
			be_cmd_q_destroy(adapter, q, QTYPE_CQ);
		be_queue_मुक्त(adapter, q);
	पूर्ण
पूर्ण

अटल पूर्णांक be_rx_cqs_create(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_queue_info *eq, *cq;
	काष्ठा be_rx_obj *rxo;
	पूर्णांक rc, i;

	adapter->num_rss_qs =
			min(adapter->num_evt_qs, adapter->cfg_num_rx_irqs);

	/* We'll use RSS only अगर atleast 2 RSS rings are supported. */
	अगर (adapter->num_rss_qs < 2)
		adapter->num_rss_qs = 0;

	adapter->num_rx_qs = adapter->num_rss_qs + adapter->need_def_rxq;

	/* When the पूर्णांकerface is not capable of RSS rings (and there is no
	 * need to create a शेष RXQ) we'll still need one RXQ
	 */
	अगर (adapter->num_rx_qs == 0)
		adapter->num_rx_qs = 1;

	adapter->big_page_size = (1 << get_order(rx_frag_size)) * PAGE_SIZE;
	क्रम_all_rx_queues(adapter, rxo, i) अणु
		rxo->adapter = adapter;
		cq = &rxo->cq;
		rc = be_queue_alloc(adapter, cq, RX_CQ_LEN,
				    माप(काष्ठा be_eth_rx_compl));
		अगर (rc)
			वापस rc;

		u64_stats_init(&rxo->stats.sync);
		eq = &adapter->eq_obj[i % adapter->num_evt_qs].q;
		rc = be_cmd_cq_create(adapter, cq, eq, false, 3);
		अगर (rc)
			वापस rc;
	पूर्ण

	dev_info(&adapter->pdev->dev,
		 "created %d RX queue(s)\n", adapter->num_rx_qs);
	वापस 0;
पूर्ण

अटल irqवापस_t be_पूर्णांकx(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा be_eq_obj *eqo = dev;
	काष्ठा be_adapter *adapter = eqo->adapter;
	पूर्णांक num_evts = 0;

	/* IRQ is not expected when NAPI is scheduled as the EQ
	 * will not be armed.
	 * But, this can happen on Lancer INTx where it takes
	 * a जबतक to de-निश्चित INTx or in BE2 where occasionaly
	 * an पूर्णांकerrupt may be उठाओd even when EQ is unarmed.
	 * If NAPI is alपढ़ोy scheduled, then counting & notअगरying
	 * events will orphan them.
	 */
	अगर (napi_schedule_prep(&eqo->napi)) अणु
		num_evts = events_get(eqo);
		__napi_schedule(&eqo->napi);
		अगर (num_evts)
			eqo->spurious_पूर्णांकr = 0;
	पूर्ण
	be_eq_notअगरy(adapter, eqo->q.id, false, true, num_evts, 0);

	/* Return IRQ_HANDLED only क्रम the the first spurious पूर्णांकr
	 * after a valid पूर्णांकr to stop the kernel from bअक्रमing
	 * this irq as a bad one!
	 */
	अगर (num_evts || eqo->spurious_पूर्णांकr++ == 0)
		वापस IRQ_HANDLED;
	अन्यथा
		वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t be_msix(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा be_eq_obj *eqo = dev;

	be_eq_notअगरy(eqo->adapter, eqo->q.id, false, true, 0, 0);
	napi_schedule(&eqo->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत bool करो_gro(काष्ठा be_rx_compl_info *rxcp)
अणु
	वापस (rxcp->tcpf && !rxcp->err && rxcp->l4_csum) ? true : false;
पूर्ण

अटल पूर्णांक be_process_rx(काष्ठा be_rx_obj *rxo, काष्ठा napi_काष्ठा *napi,
			 पूर्णांक budget)
अणु
	काष्ठा be_adapter *adapter = rxo->adapter;
	काष्ठा be_queue_info *rx_cq = &rxo->cq;
	काष्ठा be_rx_compl_info *rxcp;
	u32 work_करोne;
	u32 frags_consumed = 0;

	क्रम (work_करोne = 0; work_करोne < budget; work_करोne++) अणु
		rxcp = be_rx_compl_get(rxo);
		अगर (!rxcp)
			अवरोध;

		/* Is it a flush compl that has no data */
		अगर (unlikely(rxcp->num_rcvd == 0))
			जाओ loop_जारी;

		/* Discard compl with partial DMA Lancer B0 */
		अगर (unlikely(!rxcp->pkt_size)) अणु
			be_rx_compl_discard(rxo, rxcp);
			जाओ loop_जारी;
		पूर्ण

		/* On BE drop pkts that arrive due to imperfect filtering in
		 * promiscuous mode on some skews
		 */
		अगर (unlikely(rxcp->port != adapter->port_num &&
			     !lancer_chip(adapter))) अणु
			be_rx_compl_discard(rxo, rxcp);
			जाओ loop_जारी;
		पूर्ण

		अगर (करो_gro(rxcp))
			be_rx_compl_process_gro(rxo, napi, rxcp);
		अन्यथा
			be_rx_compl_process(rxo, napi, rxcp);

loop_जारी:
		frags_consumed += rxcp->num_rcvd;
		be_rx_stats_update(rxo, rxcp);
	पूर्ण

	अगर (work_करोne) अणु
		be_cq_notअगरy(adapter, rx_cq->id, true, work_करोne);

		/* When an rx-obj माला_लो पूर्णांकo post_starved state, just
		 * let be_worker करो the posting.
		 */
		अगर (atomic_पढ़ो(&rxo->q.used) < RX_FRAGS_REFILL_WM &&
		    !rxo->rx_post_starved)
			be_post_rx_frags(rxo, GFP_ATOMIC,
					 max_t(u32, MAX_RX_POST,
					       frags_consumed));
	पूर्ण

	वापस work_करोne;
पूर्ण


अटल व्योम be_process_tx(काष्ठा be_adapter *adapter, काष्ठा be_tx_obj *txo,
			  पूर्णांक idx)
अणु
	पूर्णांक num_wrbs = 0, work_करोne = 0;
	काष्ठा be_tx_compl_info *txcp;

	जबतक ((txcp = be_tx_compl_get(adapter, txo))) अणु
		num_wrbs += be_tx_compl_process(adapter, txo, txcp->end_index);
		work_करोne++;
	पूर्ण

	अगर (work_करोne) अणु
		be_cq_notअगरy(adapter, txo->cq.id, true, work_करोne);
		atomic_sub(num_wrbs, &txo->q.used);

		/* As Tx wrbs have been मुक्तd up, wake up netdev queue
		 * अगर it was stopped due to lack of tx wrbs.  */
		अगर (__netअगर_subqueue_stopped(adapter->netdev, idx) &&
		    be_can_txq_wake(txo)) अणु
			netअगर_wake_subqueue(adapter->netdev, idx);
		पूर्ण

		u64_stats_update_begin(&tx_stats(txo)->sync_compl);
		tx_stats(txo)->tx_compl += work_करोne;
		u64_stats_update_end(&tx_stats(txo)->sync_compl);
	पूर्ण
पूर्ण

पूर्णांक be_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा be_eq_obj *eqo = container_of(napi, काष्ठा be_eq_obj, napi);
	काष्ठा be_adapter *adapter = eqo->adapter;
	पूर्णांक max_work = 0, work, i, num_evts;
	काष्ठा be_rx_obj *rxo;
	काष्ठा be_tx_obj *txo;
	u32 mult_enc = 0;

	num_evts = events_get(eqo);

	क्रम_all_tx_queues_on_eq(adapter, eqo, txo, i)
		be_process_tx(adapter, txo, i);

	/* This loop will iterate twice क्रम EQ0 in which
	 * completions of the last RXQ (शेष one) are also processed
	 * For other EQs the loop iterates only once
	 */
	क्रम_all_rx_queues_on_eq(adapter, eqo, rxo, i) अणु
		work = be_process_rx(rxo, napi, budget);
		max_work = max(work, max_work);
	पूर्ण

	अगर (is_mcc_eqo(eqo))
		be_process_mcc(adapter);

	अगर (max_work < budget) अणु
		napi_complete_करोne(napi, max_work);

		/* Skyhawk EQ_DB has a provision to set the rearm to पूर्णांकerrupt
		 * delay via a delay multiplier encoding value
		 */
		अगर (skyhawk_chip(adapter))
			mult_enc = be_get_eq_delay_mult_enc(eqo);

		be_eq_notअगरy(adapter, eqo->q.id, true, false, num_evts,
			     mult_enc);
	पूर्ण अन्यथा अणु
		/* As we'll जारी in polling mode, count and clear events */
		be_eq_notअगरy(adapter, eqo->q.id, false, false, num_evts, 0);
	पूर्ण
	वापस max_work;
पूर्ण

व्योम be_detect_error(काष्ठा be_adapter *adapter)
अणु
	u32 ue_lo = 0, ue_hi = 0, ue_lo_mask = 0, ue_hi_mask = 0;
	u32 sliport_status = 0, sliport_err1 = 0, sliport_err2 = 0;
	काष्ठा device *dev = &adapter->pdev->dev;
	u16 val;
	u32 i;

	अगर (be_check_error(adapter, BE_ERROR_HW))
		वापस;

	अगर (lancer_chip(adapter)) अणु
		sliport_status = ioपढ़ो32(adapter->db + SLIPORT_STATUS_OFFSET);
		अगर (sliport_status & SLIPORT_STATUS_ERR_MASK) अणु
			be_set_error(adapter, BE_ERROR_UE);
			sliport_err1 = ioपढ़ो32(adapter->db +
						SLIPORT_ERROR1_OFFSET);
			sliport_err2 = ioपढ़ो32(adapter->db +
						SLIPORT_ERROR2_OFFSET);
			/* Do not log error messages अगर its a FW reset */
			अगर (sliport_err1 == SLIPORT_ERROR_FW_RESET1 &&
			    sliport_err2 == SLIPORT_ERROR_FW_RESET2) अणु
				dev_info(dev, "Reset is in progress\n");
			पूर्ण अन्यथा अणु
				dev_err(dev, "Error detected in the card\n");
				dev_err(dev, "ERR: sliport status 0x%x\n",
					sliport_status);
				dev_err(dev, "ERR: sliport error1 0x%x\n",
					sliport_err1);
				dev_err(dev, "ERR: sliport error2 0x%x\n",
					sliport_err2);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ue_lo = ioपढ़ो32(adapter->pcicfg + PCICFG_UE_STATUS_LOW);
		ue_hi = ioपढ़ो32(adapter->pcicfg + PCICFG_UE_STATUS_HIGH);
		ue_lo_mask = ioपढ़ो32(adapter->pcicfg +
				      PCICFG_UE_STATUS_LOW_MASK);
		ue_hi_mask = ioपढ़ो32(adapter->pcicfg +
				      PCICFG_UE_STATUS_HI_MASK);

		ue_lo = (ue_lo & ~ue_lo_mask);
		ue_hi = (ue_hi & ~ue_hi_mask);

		अगर (ue_lo || ue_hi) अणु
			/* On certain platक्रमms BE3 hardware can indicate
			 * spurious UEs. In हाल of a UE in the chip,
			 * the POST रेजिस्टर correctly reports either a
			 * FAT_LOG_START state (FW is currently dumping
			 * FAT log data) or a ARMFW_UE state. Check क्रम the
			 * above states to ascertain अगर the UE is valid or not.
			 */
			अगर (BE3_chip(adapter)) अणु
				val = be_POST_stage_get(adapter);
				अगर ((val & POST_STAGE_FAT_LOG_START)
				     != POST_STAGE_FAT_LOG_START &&
				    (val & POST_STAGE_ARMFW_UE)
				     != POST_STAGE_ARMFW_UE &&
				    (val & POST_STAGE_RECOVERABLE_ERR)
				     != POST_STAGE_RECOVERABLE_ERR)
					वापस;
			पूर्ण

			dev_err(dev, "Error detected in the adapter");
			be_set_error(adapter, BE_ERROR_UE);

			क्रम (i = 0; ue_lo; ue_lo >>= 1, i++) अणु
				अगर (ue_lo & 1)
					dev_err(dev, "UE: %s bit set\n",
						ue_status_low_desc[i]);
			पूर्ण
			क्रम (i = 0; ue_hi; ue_hi >>= 1, i++) अणु
				अगर (ue_hi & 1)
					dev_err(dev, "UE: %s bit set\n",
						ue_status_hi_desc[i]);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम be_msix_disable(काष्ठा be_adapter *adapter)
अणु
	अगर (msix_enabled(adapter)) अणु
		pci_disable_msix(adapter->pdev);
		adapter->num_msix_vec = 0;
		adapter->num_msix_roce_vec = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक be_msix_enable(काष्ठा be_adapter *adapter)
अणु
	अचिन्हित पूर्णांक i, max_roce_eqs;
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक num_vec;

	/* If RoCE is supported, program the max number of vectors that
	 * could be used क्रम NIC and RoCE, अन्यथा, just program the number
	 * we'll use initially.
	 */
	अगर (be_roce_supported(adapter)) अणु
		max_roce_eqs =
			be_max_func_eqs(adapter) - be_max_nic_eqs(adapter);
		max_roce_eqs = min(max_roce_eqs, num_online_cpus());
		num_vec = be_max_any_irqs(adapter) + max_roce_eqs;
	पूर्ण अन्यथा अणु
		num_vec = max(adapter->cfg_num_rx_irqs,
			      adapter->cfg_num_tx_irqs);
	पूर्ण

	क्रम (i = 0; i < num_vec; i++)
		adapter->msix_entries[i].entry = i;

	num_vec = pci_enable_msix_range(adapter->pdev, adapter->msix_entries,
					MIN_MSIX_VECTORS, num_vec);
	अगर (num_vec < 0)
		जाओ fail;

	अगर (be_roce_supported(adapter) && num_vec > MIN_MSIX_VECTORS) अणु
		adapter->num_msix_roce_vec = num_vec / 2;
		dev_info(dev, "enabled %d MSI-x vector(s) for RoCE\n",
			 adapter->num_msix_roce_vec);
	पूर्ण

	adapter->num_msix_vec = num_vec - adapter->num_msix_roce_vec;

	dev_info(dev, "enabled %d MSI-x vector(s) for NIC\n",
		 adapter->num_msix_vec);
	वापस 0;

fail:
	dev_warn(dev, "MSIx enable failed\n");

	/* INTx is not supported in VFs, so fail probe अगर enable_msix fails */
	अगर (be_virtfn(adapter))
		वापस num_vec;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक be_msix_vec_get(काष्ठा be_adapter *adapter,
				  काष्ठा be_eq_obj *eqo)
अणु
	वापस adapter->msix_entries[eqo->msix_idx].vector;
पूर्ण

अटल पूर्णांक be_msix_रेजिस्टर(काष्ठा be_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा be_eq_obj *eqo;
	पूर्णांक status, i, vec;

	क्रम_all_evt_queues(adapter, eqo, i) अणु
		प्र_लिखो(eqo->desc, "%s-q%d", netdev->name, i);
		vec = be_msix_vec_get(adapter, eqo);
		status = request_irq(vec, be_msix, 0, eqo->desc, eqo);
		अगर (status)
			जाओ err_msix;

		irq_set_affinity_hपूर्णांक(vec, eqo->affinity_mask);
	पूर्ण

	वापस 0;
err_msix:
	क्रम (i--; i >= 0; i--) अणु
		eqo = &adapter->eq_obj[i];
		मुक्त_irq(be_msix_vec_get(adapter, eqo), eqo);
	पूर्ण
	dev_warn(&adapter->pdev->dev, "MSIX Request IRQ failed - err %d\n",
		 status);
	be_msix_disable(adapter);
	वापस status;
पूर्ण

अटल पूर्णांक be_irq_रेजिस्टर(काष्ठा be_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक status;

	अगर (msix_enabled(adapter)) अणु
		status = be_msix_रेजिस्टर(adapter);
		अगर (status == 0)
			जाओ करोne;
		/* INTx is not supported क्रम VF */
		अगर (be_virtfn(adapter))
			वापस status;
	पूर्ण

	/* INTx: only the first EQ is used */
	netdev->irq = adapter->pdev->irq;
	status = request_irq(netdev->irq, be_पूर्णांकx, IRQF_SHARED, netdev->name,
			     &adapter->eq_obj[0]);
	अगर (status) अणु
		dev_err(&adapter->pdev->dev,
			"INTx request IRQ failed - err %d\n", status);
		वापस status;
	पूर्ण
करोne:
	adapter->isr_रेजिस्टरed = true;
	वापस 0;
पूर्ण

अटल व्योम be_irq_unरेजिस्टर(काष्ठा be_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा be_eq_obj *eqo;
	पूर्णांक i, vec;

	अगर (!adapter->isr_रेजिस्टरed)
		वापस;

	/* INTx */
	अगर (!msix_enabled(adapter)) अणु
		मुक्त_irq(netdev->irq, &adapter->eq_obj[0]);
		जाओ करोne;
	पूर्ण

	/* MSIx */
	क्रम_all_evt_queues(adapter, eqo, i) अणु
		vec = be_msix_vec_get(adapter, eqo);
		irq_set_affinity_hपूर्णांक(vec, शून्य);
		मुक्त_irq(vec, eqo);
	पूर्ण

करोne:
	adapter->isr_रेजिस्टरed = false;
पूर्ण

अटल व्योम be_rx_qs_destroy(काष्ठा be_adapter *adapter)
अणु
	काष्ठा rss_info *rss = &adapter->rss_info;
	काष्ठा be_queue_info *q;
	काष्ठा be_rx_obj *rxo;
	पूर्णांक i;

	क्रम_all_rx_queues(adapter, rxo, i) अणु
		q = &rxo->q;
		अगर (q->created) अणु
			/* If RXQs are destroyed जबतक in an "out of buffer"
			 * state, there is a possibility of an HW stall on
			 * Lancer. So, post 64 buffers to each queue to relieve
			 * the "out of buffer" condition.
			 * Make sure there's space in the RXQ beक्रमe posting.
			 */
			अगर (lancer_chip(adapter)) अणु
				be_rx_cq_clean(rxo);
				अगर (atomic_पढ़ो(&q->used) == 0)
					be_post_rx_frags(rxo, GFP_KERNEL,
							 MAX_RX_POST);
			पूर्ण

			be_cmd_rxq_destroy(adapter, q);
			be_rx_cq_clean(rxo);
			be_rxq_clean(rxo);
		पूर्ण
		be_queue_मुक्त(adapter, q);
	पूर्ण

	अगर (rss->rss_flags) अणु
		rss->rss_flags = RSS_ENABLE_NONE;
		be_cmd_rss_config(adapter, rss->rsstable, rss->rss_flags,
				  128, rss->rss_hkey);
	पूर्ण
पूर्ण

अटल व्योम be_disable_अगर_filters(काष्ठा be_adapter *adapter)
अणु
	/* Don't delete MAC on BE3 VFs without FILTMGMT privilege  */
	अगर (!BEx_chip(adapter) || !be_virtfn(adapter) ||
	    check_privilege(adapter, BE_PRIV_FILTMGMT)) अणु
		be_dev_mac_del(adapter, adapter->pmac_id[0]);
		eth_zero_addr(adapter->dev_mac);
	पूर्ण

	be_clear_uc_list(adapter);
	be_clear_mc_list(adapter);

	/* The IFACE flags are enabled in the खोलो path and cleared
	 * in the बंद path. When a VF माला_लो detached from the host and
	 * asचिन्हित to a VM the following happens:
	 *	- VF's IFACE flags get cleared in the detach path
	 *	- IFACE create is issued by the VF in the attach path
	 * Due to a bug in the BE3/Skyhawk-R FW
	 * (Lancer FW करोesn't have the bug), the IFACE capability flags
	 * specअगरied aदीर्घ with the IFACE create cmd issued by a VF are not
	 * honoured by FW.  As a consequence, अगर a *new* driver
	 * (that enables/disables IFACE flags in खोलो/बंद)
	 * is loaded in the host and an *old* driver is * used by a VM/VF,
	 * the IFACE माला_लो created *without* the needed flags.
	 * To aव्योम this, disable RX-filter flags only क्रम Lancer.
	 */
	अगर (lancer_chip(adapter)) अणु
		be_cmd_rx_filter(adapter, BE_IF_ALL_FILT_FLAGS, OFF);
		adapter->अगर_flags &= ~BE_IF_ALL_FILT_FLAGS;
	पूर्ण
पूर्ण

अटल पूर्णांक be_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा be_eq_obj *eqo;
	पूर्णांक i;

	/* This protection is needed as be_बंद() may be called even when the
	 * adapter is in cleared state (after eeh perm failure)
	 */
	अगर (!(adapter->flags & BE_FLAGS_SETUP_DONE))
		वापस 0;

	/* Beक्रमe attempting cleanup ensure all the pending cmds in the
	 * config_wq have finished execution
	 */
	flush_workqueue(be_wq);

	be_disable_अगर_filters(adapter);

	अगर (adapter->flags & BE_FLAGS_NAPI_ENABLED) अणु
		क्रम_all_evt_queues(adapter, eqo, i) अणु
			napi_disable(&eqo->napi);
		पूर्ण
		adapter->flags &= ~BE_FLAGS_NAPI_ENABLED;
	पूर्ण

	be_async_mcc_disable(adapter);

	/* Wait क्रम all pending tx completions to arrive so that
	 * all tx skbs are मुक्तd.
	 */
	netअगर_tx_disable(netdev);
	be_tx_compl_clean(adapter);

	be_rx_qs_destroy(adapter);

	क्रम_all_evt_queues(adapter, eqo, i) अणु
		अगर (msix_enabled(adapter))
			synchronize_irq(be_msix_vec_get(adapter, eqo));
		अन्यथा
			synchronize_irq(netdev->irq);
		be_eq_clean(eqo);
	पूर्ण

	be_irq_unरेजिस्टर(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक be_rx_qs_create(काष्ठा be_adapter *adapter)
अणु
	काष्ठा rss_info *rss = &adapter->rss_info;
	u8 rss_key[RSS_HASH_KEY_LEN];
	काष्ठा be_rx_obj *rxo;
	पूर्णांक rc, i, j;

	क्रम_all_rx_queues(adapter, rxo, i) अणु
		rc = be_queue_alloc(adapter, &rxo->q, RX_Q_LEN,
				    माप(काष्ठा be_eth_rx_d));
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (adapter->need_def_rxq || !adapter->num_rss_qs) अणु
		rxo = शेष_rxo(adapter);
		rc = be_cmd_rxq_create(adapter, &rxo->q, rxo->cq.id,
				       rx_frag_size, adapter->अगर_handle,
				       false, &rxo->rss_id);
		अगर (rc)
			वापस rc;
	पूर्ण

	क्रम_all_rss_queues(adapter, rxo, i) अणु
		rc = be_cmd_rxq_create(adapter, &rxo->q, rxo->cq.id,
				       rx_frag_size, adapter->अगर_handle,
				       true, &rxo->rss_id);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (be_multi_rxq(adapter)) अणु
		क्रम (j = 0; j < RSS_INसूची_TABLE_LEN; j += adapter->num_rss_qs) अणु
			क्रम_all_rss_queues(adapter, rxo, i) अणु
				अगर ((j + i) >= RSS_INसूची_TABLE_LEN)
					अवरोध;
				rss->rsstable[j + i] = rxo->rss_id;
				rss->rss_queue[j + i] = i;
			पूर्ण
		पूर्ण
		rss->rss_flags = RSS_ENABLE_TCP_IPV4 | RSS_ENABLE_IPV4 |
			RSS_ENABLE_TCP_IPV6 | RSS_ENABLE_IPV6;

		अगर (!BEx_chip(adapter))
			rss->rss_flags |= RSS_ENABLE_UDP_IPV4 |
				RSS_ENABLE_UDP_IPV6;

		netdev_rss_key_fill(rss_key, RSS_HASH_KEY_LEN);
		rc = be_cmd_rss_config(adapter, rss->rsstable, rss->rss_flags,
				       RSS_INसूची_TABLE_LEN, rss_key);
		अगर (rc) अणु
			rss->rss_flags = RSS_ENABLE_NONE;
			वापस rc;
		पूर्ण

		स_नकल(rss->rss_hkey, rss_key, RSS_HASH_KEY_LEN);
	पूर्ण अन्यथा अणु
		/* Disable RSS, अगर only शेष RX Q is created */
		rss->rss_flags = RSS_ENABLE_NONE;
	पूर्ण


	/* Post 1 less than RXQ-len to aव्योम head being equal to tail,
	 * which is a queue empty condition
	 */
	क्रम_all_rx_queues(adapter, rxo, i)
		be_post_rx_frags(rxo, GFP_KERNEL, RX_Q_LEN - 1);

	वापस 0;
पूर्ण

अटल पूर्णांक be_enable_अगर_filters(काष्ठा be_adapter *adapter)
अणु
	पूर्णांक status;

	status = be_cmd_rx_filter(adapter, BE_IF_FILT_FLAGS_BASIC, ON);
	अगर (status)
		वापस status;

	/* Normally this condition usually true as the ->dev_mac is zeroed.
	 * But on BE3 VFs the initial MAC is pre-programmed by PF and
	 * subsequent be_dev_mac_add() can fail (after fresh boot)
	 */
	अगर (!ether_addr_equal(adapter->dev_mac, adapter->netdev->dev_addr)) अणु
		पूर्णांक old_pmac_id = -1;

		/* Remember old programmed MAC अगर any - can happen on BE3 VF */
		अगर (!is_zero_ether_addr(adapter->dev_mac))
			old_pmac_id = adapter->pmac_id[0];

		status = be_dev_mac_add(adapter, adapter->netdev->dev_addr);
		अगर (status)
			वापस status;

		/* Delete the old programmed MAC as we successfully programmed
		 * a new MAC
		 */
		अगर (old_pmac_id >= 0 && old_pmac_id != adapter->pmac_id[0])
			be_dev_mac_del(adapter, old_pmac_id);

		ether_addr_copy(adapter->dev_mac, adapter->netdev->dev_addr);
	पूर्ण

	अगर (adapter->vlans_added)
		be_vid_config(adapter);

	__be_set_rx_mode(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक be_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा be_eq_obj *eqo;
	काष्ठा be_rx_obj *rxo;
	काष्ठा be_tx_obj *txo;
	u8 link_status;
	पूर्णांक status, i;

	status = be_rx_qs_create(adapter);
	अगर (status)
		जाओ err;

	status = be_enable_अगर_filters(adapter);
	अगर (status)
		जाओ err;

	status = be_irq_रेजिस्टर(adapter);
	अगर (status)
		जाओ err;

	क्रम_all_rx_queues(adapter, rxo, i)
		be_cq_notअगरy(adapter, rxo->cq.id, true, 0);

	क्रम_all_tx_queues(adapter, txo, i)
		be_cq_notअगरy(adapter, txo->cq.id, true, 0);

	be_async_mcc_enable(adapter);

	क्रम_all_evt_queues(adapter, eqo, i) अणु
		napi_enable(&eqo->napi);
		be_eq_notअगरy(adapter, eqo->q.id, true, true, 0, 0);
	पूर्ण
	adapter->flags |= BE_FLAGS_NAPI_ENABLED;

	status = be_cmd_link_status_query(adapter, शून्य, &link_status, 0);
	अगर (!status)
		be_link_status_update(adapter, link_status);

	netअगर_tx_start_all_queues(netdev);

	udp_tunnel_nic_reset_ntf(netdev);

	वापस 0;
err:
	be_बंद(adapter->netdev);
	वापस -EIO;
पूर्ण

अटल व्योम be_vf_eth_addr_generate(काष्ठा be_adapter *adapter, u8 *mac)
अणु
	u32 addr;

	addr = jhash(adapter->netdev->dev_addr, ETH_ALEN, 0);

	mac[5] = (u8)(addr & 0xFF);
	mac[4] = (u8)((addr >> 8) & 0xFF);
	mac[3] = (u8)((addr >> 16) & 0xFF);
	/* Use the OUI from the current MAC address */
	स_नकल(mac, adapter->netdev->dev_addr, 3);
पूर्ण

/*
 * Generate a seed MAC address from the PF MAC Address using jhash.
 * MAC Address क्रम VFs are asचिन्हित incrementally starting from the seed.
 * These addresses are programmed in the ASIC by the PF and the VF driver
 * queries क्रम the MAC address during its probe.
 */
अटल पूर्णांक be_vf_eth_addr_config(काष्ठा be_adapter *adapter)
अणु
	u32 vf;
	पूर्णांक status = 0;
	u8 mac[ETH_ALEN];
	काष्ठा be_vf_cfg *vf_cfg;

	be_vf_eth_addr_generate(adapter, mac);

	क्रम_all_vfs(adapter, vf_cfg, vf) अणु
		अगर (BEx_chip(adapter))
			status = be_cmd_pmac_add(adapter, mac,
						 vf_cfg->अगर_handle,
						 &vf_cfg->pmac_id, vf + 1);
		अन्यथा
			status = be_cmd_set_mac(adapter, mac, vf_cfg->अगर_handle,
						vf + 1);

		अगर (status)
			dev_err(&adapter->pdev->dev,
				"Mac address assignment failed for VF %d\n",
				vf);
		अन्यथा
			स_नकल(vf_cfg->mac_addr, mac, ETH_ALEN);

		mac[5] += 1;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक be_vfs_mac_query(काष्ठा be_adapter *adapter)
अणु
	पूर्णांक status, vf;
	u8 mac[ETH_ALEN];
	काष्ठा be_vf_cfg *vf_cfg;

	क्रम_all_vfs(adapter, vf_cfg, vf) अणु
		status = be_cmd_get_active_mac(adapter, vf_cfg->pmac_id,
					       mac, vf_cfg->अगर_handle,
					       false, vf+1);
		अगर (status)
			वापस status;
		स_नकल(vf_cfg->mac_addr, mac, ETH_ALEN);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम be_vf_clear(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_vf_cfg *vf_cfg;
	u32 vf;

	अगर (pci_vfs_asचिन्हित(adapter->pdev)) अणु
		dev_warn(&adapter->pdev->dev,
			 "VFs are assigned to VMs: not disabling VFs\n");
		जाओ करोne;
	पूर्ण

	pci_disable_sriov(adapter->pdev);

	क्रम_all_vfs(adapter, vf_cfg, vf) अणु
		अगर (BEx_chip(adapter))
			be_cmd_pmac_del(adapter, vf_cfg->अगर_handle,
					vf_cfg->pmac_id, vf + 1);
		अन्यथा
			be_cmd_set_mac(adapter, शून्य, vf_cfg->अगर_handle,
				       vf + 1);

		be_cmd_अगर_destroy(adapter, vf_cfg->अगर_handle, vf + 1);
	पूर्ण

	अगर (BE3_chip(adapter))
		be_cmd_set_hsw_config(adapter, 0, 0,
				      adapter->अगर_handle,
				      PORT_FWD_TYPE_PASSTHRU, 0);
करोne:
	kमुक्त(adapter->vf_cfg);
	adapter->num_vfs = 0;
	adapter->flags &= ~BE_FLAGS_SRIOV_ENABLED;
पूर्ण

अटल व्योम be_clear_queues(काष्ठा be_adapter *adapter)
अणु
	be_mcc_queues_destroy(adapter);
	be_rx_cqs_destroy(adapter);
	be_tx_queues_destroy(adapter);
	be_evt_queues_destroy(adapter);
पूर्ण

अटल व्योम be_cancel_worker(काष्ठा be_adapter *adapter)
अणु
	अगर (adapter->flags & BE_FLAGS_WORKER_SCHEDULED) अणु
		cancel_delayed_work_sync(&adapter->work);
		adapter->flags &= ~BE_FLAGS_WORKER_SCHEDULED;
	पूर्ण
पूर्ण

अटल व्योम be_cancel_err_detection(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_error_recovery *err_rec = &adapter->error_recovery;

	अगर (!be_err_recovery_workq)
		वापस;

	अगर (adapter->flags & BE_FLAGS_ERR_DETECTION_SCHEDULED) अणु
		cancel_delayed_work_sync(&err_rec->err_detection_work);
		adapter->flags &= ~BE_FLAGS_ERR_DETECTION_SCHEDULED;
	पूर्ण
पूर्ण

/* VxLAN offload Notes:
 *
 * The stack defines tunnel offload flags (hw_enc_features) क्रम IP and करोesn't
 * distinguish various types of transports (VxLAN, GRE, NVGRE ..). So, offload
 * is expected to work across all types of IP tunnels once exported. Skyhawk
 * supports offloads क्रम either VxLAN or NVGRE, exclusively. So we export VxLAN
 * offloads in hw_enc_features only when a VxLAN port is added. If other (non
 * VxLAN) tunnels are configured जबतक VxLAN offloads are enabled, offloads क्रम
 * those other tunnels are unexported on the fly through nकरो_features_check().
 */
अटल पूर्णांक be_vxlan_set_port(काष्ठा net_device *netdev, अचिन्हित पूर्णांक table,
			     अचिन्हित पूर्णांक entry, काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक status;

	status = be_cmd_manage_अगरace(adapter, adapter->अगर_handle,
				     OP_CONVERT_NORMAL_TO_TUNNEL);
	अगर (status) अणु
		dev_warn(dev, "Failed to convert normal interface to tunnel\n");
		वापस status;
	पूर्ण
	adapter->flags |= BE_FLAGS_VXLAN_OFFLOADS;

	status = be_cmd_set_vxlan_port(adapter, ti->port);
	अगर (status) अणु
		dev_warn(dev, "Failed to add VxLAN port\n");
		वापस status;
	पूर्ण
	adapter->vxlan_port = ti->port;

	netdev->hw_enc_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				   NETIF_F_TSO | NETIF_F_TSO6 |
				   NETIF_F_GSO_UDP_TUNNEL;

	dev_info(dev, "Enabled VxLAN offloads for UDP port %d\n",
		 be16_to_cpu(ti->port));
	वापस 0;
पूर्ण

अटल पूर्णांक be_vxlan_unset_port(काष्ठा net_device *netdev, अचिन्हित पूर्णांक table,
			       अचिन्हित पूर्णांक entry, काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->flags & BE_FLAGS_VXLAN_OFFLOADS)
		be_cmd_manage_अगरace(adapter, adapter->अगर_handle,
				    OP_CONVERT_TUNNEL_TO_NORMAL);

	अगर (adapter->vxlan_port)
		be_cmd_set_vxlan_port(adapter, 0);

	adapter->flags &= ~BE_FLAGS_VXLAN_OFFLOADS;
	adapter->vxlan_port = 0;

	netdev->hw_enc_features = 0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info be_udp_tunnels = अणु
	.set_port	= be_vxlan_set_port,
	.unset_port	= be_vxlan_unset_port,
	.flags		= UDP_TUNNEL_NIC_INFO_MAY_SLEEP |
			  UDP_TUNNEL_NIC_INFO_OPEN_ONLY,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN, पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम be_calculate_vf_res(काष्ठा be_adapter *adapter, u16 num_vfs,
				काष्ठा be_resources *vft_res)
अणु
	काष्ठा be_resources res = adapter->pool_res;
	u32 vf_अगर_cap_flags = res.vf_अगर_cap_flags;
	काष्ठा be_resources res_mod = अणु0पूर्ण;
	u16 num_vf_qs = 1;

	/* Distribute the queue resources among the PF and it's VFs */
	अगर (num_vfs) अणु
		/* Divide the rx queues evenly among the VFs and the PF, capped
		 * at VF-EQ-count. Any reमुख्यder queues beदीर्घ to the PF.
		 */
		num_vf_qs = min(SH_VF_MAX_NIC_EQS,
				res.max_rss_qs / (num_vfs + 1));

		/* Skyhawk-R chip supports only MAX_PORT_RSS_TABLES
		 * RSS Tables per port. Provide RSS on VFs, only अगर number of
		 * VFs requested is less than it's PF Pool's RSS Tables limit.
		 */
		अगर (num_vfs >= be_max_pf_pool_rss_tables(adapter))
			num_vf_qs = 1;
	पूर्ण

	/* Resource with fields set to all '1's by GET_PROखाता_CONFIG cmd,
	 * which are modअगरiable using SET_PROखाता_CONFIG cmd.
	 */
	be_cmd_get_profile_config(adapter, &res_mod, शून्य, ACTIVE_PROखाता_TYPE,
				  RESOURCE_MODIFIABLE, 0);

	/* If RSS IFACE capability flags are modअगरiable क्रम a VF, set the
	 * capability flag as valid and set RSS and DEFQ_RSS IFACE flags अगर
	 * more than 1 RSSQ is available क्रम a VF.
	 * Otherwise, provision only 1 queue pair क्रम VF.
	 */
	अगर (res_mod.vf_अगर_cap_flags & BE_IF_FLAGS_RSS) अणु
		vft_res->flags |= BIT(IF_CAPS_FLAGS_VALID_SHIFT);
		अगर (num_vf_qs > 1) अणु
			vf_अगर_cap_flags |= BE_IF_FLAGS_RSS;
			अगर (res.अगर_cap_flags & BE_IF_FLAGS_DEFQ_RSS)
				vf_अगर_cap_flags |= BE_IF_FLAGS_DEFQ_RSS;
		पूर्ण अन्यथा अणु
			vf_अगर_cap_flags &= ~(BE_IF_FLAGS_RSS |
					     BE_IF_FLAGS_DEFQ_RSS);
		पूर्ण
	पूर्ण अन्यथा अणु
		num_vf_qs = 1;
	पूर्ण

	अगर (res_mod.vf_अगर_cap_flags & BE_IF_FLAGS_VLAN_PROMISCUOUS) अणु
		vft_res->flags |= BIT(IF_CAPS_FLAGS_VALID_SHIFT);
		vf_अगर_cap_flags &= ~BE_IF_FLAGS_VLAN_PROMISCUOUS;
	पूर्ण

	vft_res->vf_अगर_cap_flags = vf_अगर_cap_flags;
	vft_res->max_rx_qs = num_vf_qs;
	vft_res->max_rss_qs = num_vf_qs;
	vft_res->max_tx_qs = res.max_tx_qs / (num_vfs + 1);
	vft_res->max_cq_count = res.max_cq_count / (num_vfs + 1);

	/* Distribute unicast MACs, VLANs, IFACE count and MCCQ count equally
	 * among the PF and it's VFs, अगर the fields are changeable
	 */
	अगर (res_mod.max_uc_mac == FIELD_MODIFIABLE)
		vft_res->max_uc_mac = res.max_uc_mac / (num_vfs + 1);

	अगर (res_mod.max_vlans == FIELD_MODIFIABLE)
		vft_res->max_vlans = res.max_vlans / (num_vfs + 1);

	अगर (res_mod.max_अगरace_count == FIELD_MODIFIABLE)
		vft_res->max_अगरace_count = res.max_अगरace_count / (num_vfs + 1);

	अगर (res_mod.max_mcc_count == FIELD_MODIFIABLE)
		vft_res->max_mcc_count = res.max_mcc_count / (num_vfs + 1);
पूर्ण

अटल व्योम be_अगर_destroy(काष्ठा be_adapter *adapter)
अणु
	be_cmd_अगर_destroy(adapter, adapter->अगर_handle,  0);

	kमुक्त(adapter->pmac_id);
	adapter->pmac_id = शून्य;

	kमुक्त(adapter->mc_list);
	adapter->mc_list = शून्य;

	kमुक्त(adapter->uc_list);
	adapter->uc_list = शून्य;
पूर्ण

अटल पूर्णांक be_clear(काष्ठा be_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा  be_resources vft_res = अणु0पूर्ण;

	be_cancel_worker(adapter);

	flush_workqueue(be_wq);

	अगर (sriov_enabled(adapter))
		be_vf_clear(adapter);

	/* Re-configure FW to distribute resources evenly across max-supported
	 * number of VFs, only when VFs are not alपढ़ोy enabled.
	 */
	अगर (skyhawk_chip(adapter) && be_physfn(adapter) &&
	    !pci_vfs_asचिन्हित(pdev)) अणु
		be_calculate_vf_res(adapter,
				    pci_sriov_get_totalvfs(pdev),
				    &vft_res);
		be_cmd_set_sriov_config(adapter, adapter->pool_res,
					pci_sriov_get_totalvfs(pdev),
					&vft_res);
	पूर्ण

	be_vxlan_unset_port(adapter->netdev, 0, 0, शून्य);

	be_अगर_destroy(adapter);

	be_clear_queues(adapter);

	be_msix_disable(adapter);
	adapter->flags &= ~BE_FLAGS_SETUP_DONE;
	वापस 0;
पूर्ण

अटल पूर्णांक be_vfs_अगर_create(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_resources res = अणु0पूर्ण;
	u32 cap_flags, en_flags, vf;
	काष्ठा be_vf_cfg *vf_cfg;
	पूर्णांक status;

	/* If a FW profile exists, then cap_flags are updated */
	cap_flags = BE_VF_IF_EN_FLAGS;

	क्रम_all_vfs(adapter, vf_cfg, vf) अणु
		अगर (!BE3_chip(adapter)) अणु
			status = be_cmd_get_profile_config(adapter, &res, शून्य,
							   ACTIVE_PROखाता_TYPE,
							   RESOURCE_LIMITS,
							   vf + 1);
			अगर (!status) अणु
				cap_flags = res.अगर_cap_flags;
				/* Prevent VFs from enabling VLAN promiscuous
				 * mode
				 */
				cap_flags &= ~BE_IF_FLAGS_VLAN_PROMISCUOUS;
			पूर्ण
		पूर्ण

		/* PF should enable IF flags during proxy अगर_create call */
		en_flags = cap_flags & BE_VF_IF_EN_FLAGS;
		status = be_cmd_अगर_create(adapter, cap_flags, en_flags,
					  &vf_cfg->अगर_handle, vf + 1);
		अगर (status)
			वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक be_vf_setup_init(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_vf_cfg *vf_cfg;
	पूर्णांक vf;

	adapter->vf_cfg = kसुस्मृति(adapter->num_vfs, माप(*vf_cfg),
				  GFP_KERNEL);
	अगर (!adapter->vf_cfg)
		वापस -ENOMEM;

	क्रम_all_vfs(adapter, vf_cfg, vf) अणु
		vf_cfg->अगर_handle = -1;
		vf_cfg->pmac_id = -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक be_vf_setup(काष्ठा be_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा be_vf_cfg *vf_cfg;
	पूर्णांक status, old_vfs, vf;
	bool spoofchk;

	old_vfs = pci_num_vf(adapter->pdev);

	status = be_vf_setup_init(adapter);
	अगर (status)
		जाओ err;

	अगर (old_vfs) अणु
		क्रम_all_vfs(adapter, vf_cfg, vf) अणु
			status = be_cmd_get_अगर_id(adapter, vf_cfg, vf);
			अगर (status)
				जाओ err;
		पूर्ण

		status = be_vfs_mac_query(adapter);
		अगर (status)
			जाओ err;
	पूर्ण अन्यथा अणु
		status = be_vfs_अगर_create(adapter);
		अगर (status)
			जाओ err;

		status = be_vf_eth_addr_config(adapter);
		अगर (status)
			जाओ err;
	पूर्ण

	क्रम_all_vfs(adapter, vf_cfg, vf) अणु
		/* Allow VFs to programs MAC/VLAN filters */
		status = be_cmd_get_fn_privileges(adapter, &vf_cfg->privileges,
						  vf + 1);
		अगर (!status && !(vf_cfg->privileges & BE_PRIV_FILTMGMT)) अणु
			status = be_cmd_set_fn_privileges(adapter,
							  vf_cfg->privileges |
							  BE_PRIV_FILTMGMT,
							  vf + 1);
			अगर (!status) अणु
				vf_cfg->privileges |= BE_PRIV_FILTMGMT;
				dev_info(dev, "VF%d has FILTMGMT privilege\n",
					 vf);
			पूर्ण
		पूर्ण

		/* Allow full available bandwidth */
		अगर (!old_vfs)
			be_cmd_config_qos(adapter, 0, 0, vf + 1);

		status = be_cmd_get_hsw_config(adapter, शून्य, vf + 1,
					       vf_cfg->अगर_handle, शून्य,
					       &spoofchk);
		अगर (!status)
			vf_cfg->spoofchk = spoofchk;

		अगर (!old_vfs) अणु
			be_cmd_enable_vf(adapter, vf + 1);
			be_cmd_set_logical_link_config(adapter,
						       IFLA_VF_LINK_STATE_AUTO,
						       vf+1);
		पूर्ण
	पूर्ण

	अगर (!old_vfs) अणु
		status = pci_enable_sriov(adapter->pdev, adapter->num_vfs);
		अगर (status) अणु
			dev_err(dev, "SRIOV enable failed\n");
			adapter->num_vfs = 0;
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (BE3_chip(adapter)) अणु
		/* On BE3, enable VEB only when SRIOV is enabled */
		status = be_cmd_set_hsw_config(adapter, 0, 0,
					       adapter->अगर_handle,
					       PORT_FWD_TYPE_VEB, 0);
		अगर (status)
			जाओ err;
	पूर्ण

	adapter->flags |= BE_FLAGS_SRIOV_ENABLED;
	वापस 0;
err:
	dev_err(dev, "VF setup failed\n");
	be_vf_clear(adapter);
	वापस status;
पूर्ण

/* Converting function_mode bits on BE3 to SH mc_type क्रमागतs */

अटल u8 be_convert_mc_type(u32 function_mode)
अणु
	अगर (function_mode & VNIC_MODE && function_mode & QNQ_MODE)
		वापस vNIC1;
	अन्यथा अगर (function_mode & QNQ_MODE)
		वापस FLEX10;
	अन्यथा अगर (function_mode & VNIC_MODE)
		वापस vNIC2;
	अन्यथा अगर (function_mode & UMC_ENABLED)
		वापस UMC;
	अन्यथा
		वापस MC_NONE;
पूर्ण

/* On BE2/BE3 FW करोes not suggest the supported limits */
अटल व्योम BEx_get_resources(काष्ठा be_adapter *adapter,
			      काष्ठा be_resources *res)
अणु
	bool use_sriov = adapter->num_vfs ? 1 : 0;

	अगर (be_physfn(adapter))
		res->max_uc_mac = BE_UC_PMAC_COUNT;
	अन्यथा
		res->max_uc_mac = BE_VF_UC_PMAC_COUNT;

	adapter->mc_type = be_convert_mc_type(adapter->function_mode);

	अगर (be_is_mc(adapter)) अणु
		/* Assuming that there are 4 channels per port,
		 * when multi-channel is enabled
		 */
		अगर (be_is_qnq_mode(adapter))
			res->max_vlans = BE_NUM_VLANS_SUPPORTED/8;
		अन्यथा
			/* In a non-qnq multichannel mode, the pvid
			 * takes up one vlan entry
			 */
			res->max_vlans = (BE_NUM_VLANS_SUPPORTED / 4) - 1;
	पूर्ण अन्यथा अणु
		res->max_vlans = BE_NUM_VLANS_SUPPORTED;
	पूर्ण

	res->max_mcast_mac = BE_MAX_MC;

	/* 1) For BE3 1Gb ports, FW करोes not support multiple TXQs
	 * 2) Create multiple TX rings on a BE3-R multi-channel पूर्णांकerface
	 *    *only* अगर it is RSS-capable.
	 */
	अगर (BE2_chip(adapter) || use_sriov ||  (adapter->port_num > 1) ||
	    be_virtfn(adapter) ||
	    (be_is_mc(adapter) &&
	     !(adapter->function_caps & BE_FUNCTION_CAPS_RSS))) अणु
		res->max_tx_qs = 1;
	पूर्ण अन्यथा अगर (adapter->function_caps & BE_FUNCTION_CAPS_SUPER_NIC) अणु
		काष्ठा be_resources super_nic_res = अणु0पूर्ण;

		/* On a SuperNIC profile, the driver needs to use the
		 * GET_PROखाता_CONFIG cmd to query the per-function TXQ limits
		 */
		be_cmd_get_profile_config(adapter, &super_nic_res, शून्य,
					  ACTIVE_PROखाता_TYPE, RESOURCE_LIMITS,
					  0);
		/* Some old versions of BE3 FW करोn't report max_tx_qs value */
		res->max_tx_qs = super_nic_res.max_tx_qs ? : BE3_MAX_TX_QS;
	पूर्ण अन्यथा अणु
		res->max_tx_qs = BE3_MAX_TX_QS;
	पूर्ण

	अगर ((adapter->function_caps & BE_FUNCTION_CAPS_RSS) &&
	    !use_sriov && be_physfn(adapter))
		res->max_rss_qs = (adapter->be3_native) ?
					   BE3_MAX_RSS_QS : BE2_MAX_RSS_QS;
	res->max_rx_qs = res->max_rss_qs + 1;

	अगर (be_physfn(adapter))
		res->max_evt_qs = (be_max_vfs(adapter) > 0) ?
					BE3_SRIOV_MAX_EVT_QS : BE3_MAX_EVT_QS;
	अन्यथा
		res->max_evt_qs = 1;

	res->अगर_cap_flags = BE_IF_CAP_FLAGS_WANT;
	res->अगर_cap_flags &= ~BE_IF_FLAGS_DEFQ_RSS;
	अगर (!(adapter->function_caps & BE_FUNCTION_CAPS_RSS))
		res->अगर_cap_flags &= ~BE_IF_FLAGS_RSS;
पूर्ण

अटल व्योम be_setup_init(काष्ठा be_adapter *adapter)
अणु
	adapter->vlan_prio_bmap = 0xff;
	adapter->phy.link_speed = -1;
	adapter->अगर_handle = -1;
	adapter->be3_native = false;
	adapter->अगर_flags = 0;
	adapter->phy_state = BE_UNKNOWN_PHY_STATE;
	अगर (be_physfn(adapter))
		adapter->cmd_privileges = MAX_PRIVILEGES;
	अन्यथा
		adapter->cmd_privileges = MIN_PRIVILEGES;
पूर्ण

/* HW supports only MAX_PORT_RSS_TABLES RSS Policy Tables per port.
 * However, this HW limitation is not exposed to the host via any SLI cmd.
 * As a result, in the हाल of SRIOV and in particular multi-partition configs
 * the driver needs to calcuate a proportional share of RSS Tables per PF-pool
 * क्रम distribution between the VFs. This self-imposed limit will determine the
 * no: of VFs क्रम which RSS can be enabled.
 */
अटल व्योम be_calculate_pf_pool_rss_tables(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_port_resources port_res = अणु0पूर्ण;
	u8 rss_tables_on_port;
	u16 max_vfs = be_max_vfs(adapter);

	be_cmd_get_profile_config(adapter, शून्य, &port_res, SAVED_PROखाता_TYPE,
				  RESOURCE_LIMITS, 0);

	rss_tables_on_port = MAX_PORT_RSS_TABLES - port_res.nic_pfs;

	/* Each PF Pool's RSS Tables limit =
	 * PF's Max VFs / Total_Max_VFs on Port * RSS Tables on Port
	 */
	adapter->pool_res.max_rss_tables =
		max_vfs * rss_tables_on_port / port_res.max_vfs;
पूर्ण

अटल पूर्णांक be_get_sriov_config(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_resources res = अणु0पूर्ण;
	पूर्णांक max_vfs, old_vfs;

	be_cmd_get_profile_config(adapter, &res, शून्य, ACTIVE_PROखाता_TYPE,
				  RESOURCE_LIMITS, 0);

	/* Some old versions of BE3 FW करोn't report max_vfs value */
	अगर (BE3_chip(adapter) && !res.max_vfs) अणु
		max_vfs = pci_sriov_get_totalvfs(adapter->pdev);
		res.max_vfs = max_vfs > 0 ? min(MAX_VFS, max_vfs) : 0;
	पूर्ण

	adapter->pool_res = res;

	/* If during previous unload of the driver, the VFs were not disabled,
	 * then we cannot rely on the PF POOL limits क्रम the TotalVFs value.
	 * Instead use the TotalVFs value stored in the pci-dev काष्ठा.
	 */
	old_vfs = pci_num_vf(adapter->pdev);
	अगर (old_vfs) अणु
		dev_info(&adapter->pdev->dev, "%d VFs are already enabled\n",
			 old_vfs);

		adapter->pool_res.max_vfs =
			pci_sriov_get_totalvfs(adapter->pdev);
		adapter->num_vfs = old_vfs;
	पूर्ण

	अगर (skyhawk_chip(adapter) && be_max_vfs(adapter) && !old_vfs) अणु
		be_calculate_pf_pool_rss_tables(adapter);
		dev_info(&adapter->pdev->dev,
			 "RSS can be enabled for all VFs if num_vfs <= %d\n",
			 be_max_pf_pool_rss_tables(adapter));
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम be_alloc_sriov_res(काष्ठा be_adapter *adapter)
अणु
	पूर्णांक old_vfs = pci_num_vf(adapter->pdev);
	काष्ठा  be_resources vft_res = अणु0पूर्ण;
	पूर्णांक status;

	be_get_sriov_config(adapter);

	अगर (!old_vfs)
		pci_sriov_set_totalvfs(adapter->pdev, be_max_vfs(adapter));

	/* When the HW is in SRIOV capable configuration, the PF-pool
	 * resources are given to PF during driver load, अगर there are no
	 * old VFs. This facility is not available in BE3 FW.
	 * Also, this is करोne by FW in Lancer chip.
	 */
	अगर (skyhawk_chip(adapter) && be_max_vfs(adapter) && !old_vfs) अणु
		be_calculate_vf_res(adapter, 0, &vft_res);
		status = be_cmd_set_sriov_config(adapter, adapter->pool_res, 0,
						 &vft_res);
		अगर (status)
			dev_err(&adapter->pdev->dev,
				"Failed to optimize SRIOV resources\n");
	पूर्ण
पूर्ण

अटल पूर्णांक be_get_resources(काष्ठा be_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा be_resources res = अणु0पूर्ण;
	पूर्णांक status;

	/* For Lancer, SH etc पढ़ो per-function resource limits from FW.
	 * GET_FUNC_CONFIG वापसs per function guaranteed limits.
	 * GET_PROखाता_CONFIG वापसs PCI-E related limits PF-pool limits
	 */
	अगर (BEx_chip(adapter)) अणु
		BEx_get_resources(adapter, &res);
	पूर्ण अन्यथा अणु
		status = be_cmd_get_func_config(adapter, &res);
		अगर (status)
			वापस status;

		/* If a deafault RXQ must be created, we'll use up one RSSQ*/
		अगर (res.max_rss_qs && res.max_rss_qs == res.max_rx_qs &&
		    !(res.अगर_cap_flags & BE_IF_FLAGS_DEFQ_RSS))
			res.max_rss_qs -= 1;
	पूर्ण

	/* If RoCE is supported stash away half the EQs क्रम RoCE */
	res.max_nic_evt_qs = be_roce_supported(adapter) ?
				res.max_evt_qs / 2 : res.max_evt_qs;
	adapter->res = res;

	/* If FW supports RSS शेष queue, then skip creating non-RSS
	 * queue क्रम non-IP traffic.
	 */
	adapter->need_def_rxq = (be_अगर_cap_flags(adapter) &
				 BE_IF_FLAGS_DEFQ_RSS) ? 0 : 1;

	dev_info(dev, "Max: txqs %d, rxqs %d, rss %d, eqs %d, vfs %d\n",
		 be_max_txqs(adapter), be_max_rxqs(adapter),
		 be_max_rss(adapter), be_max_nic_eqs(adapter),
		 be_max_vfs(adapter));
	dev_info(dev, "Max: uc-macs %d, mc-macs %d, vlans %d\n",
		 be_max_uc(adapter), be_max_mc(adapter),
		 be_max_vlans(adapter));

	/* Ensure RX and TX queues are created in pairs at init समय */
	adapter->cfg_num_rx_irqs =
				min_t(u16, netअगर_get_num_शेष_rss_queues(),
				      be_max_qp_irqs(adapter));
	adapter->cfg_num_tx_irqs = adapter->cfg_num_rx_irqs;
	वापस 0;
पूर्ण

अटल पूर्णांक be_get_config(काष्ठा be_adapter *adapter)
अणु
	पूर्णांक status, level;
	u16 profile_id;

	status = be_cmd_get_cntl_attributes(adapter);
	अगर (status)
		वापस status;

	status = be_cmd_query_fw_cfg(adapter);
	अगर (status)
		वापस status;

	अगर (!lancer_chip(adapter) && be_physfn(adapter))
		be_cmd_get_fat_dump_len(adapter, &adapter->fat_dump_len);

	अगर (BEx_chip(adapter)) अणु
		level = be_cmd_get_fw_log_level(adapter);
		adapter->msg_enable =
			level <= FW_LOG_LEVEL_DEFAULT ? NETIF_MSG_HW : 0;
	पूर्ण

	be_cmd_get_acpi_wol_cap(adapter);
	pci_enable_wake(adapter->pdev, PCI_D3hot, adapter->wol_en);
	pci_enable_wake(adapter->pdev, PCI_D3cold, adapter->wol_en);

	be_cmd_query_port_name(adapter);

	अगर (be_physfn(adapter)) अणु
		status = be_cmd_get_active_profile(adapter, &profile_id);
		अगर (!status)
			dev_info(&adapter->pdev->dev,
				 "Using profile 0x%x\n", profile_id);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक be_mac_setup(काष्ठा be_adapter *adapter)
अणु
	u8 mac[ETH_ALEN];
	पूर्णांक status;

	अगर (is_zero_ether_addr(adapter->netdev->dev_addr)) अणु
		status = be_cmd_get_perm_mac(adapter, mac);
		अगर (status)
			वापस status;

		स_नकल(adapter->netdev->dev_addr, mac, ETH_ALEN);
		स_नकल(adapter->netdev->perm_addr, mac, ETH_ALEN);

		/* Initial MAC क्रम BE3 VFs is alपढ़ोy programmed by PF */
		अगर (BEx_chip(adapter) && be_virtfn(adapter))
			स_नकल(adapter->dev_mac, mac, ETH_ALEN);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम be_schedule_worker(काष्ठा be_adapter *adapter)
अणु
	queue_delayed_work(be_wq, &adapter->work, msecs_to_jअगरfies(1000));
	adapter->flags |= BE_FLAGS_WORKER_SCHEDULED;
पूर्ण

अटल व्योम be_destroy_err_recovery_workq(व्योम)
अणु
	अगर (!be_err_recovery_workq)
		वापस;

	flush_workqueue(be_err_recovery_workq);
	destroy_workqueue(be_err_recovery_workq);
	be_err_recovery_workq = शून्य;
पूर्ण

अटल व्योम be_schedule_err_detection(काष्ठा be_adapter *adapter, u32 delay)
अणु
	काष्ठा be_error_recovery *err_rec = &adapter->error_recovery;

	अगर (!be_err_recovery_workq)
		वापस;

	queue_delayed_work(be_err_recovery_workq, &err_rec->err_detection_work,
			   msecs_to_jअगरfies(delay));
	adapter->flags |= BE_FLAGS_ERR_DETECTION_SCHEDULED;
पूर्ण

अटल पूर्णांक be_setup_queues(काष्ठा be_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक status;

	status = be_evt_queues_create(adapter);
	अगर (status)
		जाओ err;

	status = be_tx_qs_create(adapter);
	अगर (status)
		जाओ err;

	status = be_rx_cqs_create(adapter);
	अगर (status)
		जाओ err;

	status = be_mcc_queues_create(adapter);
	अगर (status)
		जाओ err;

	status = netअगर_set_real_num_rx_queues(netdev, adapter->num_rx_qs);
	अगर (status)
		जाओ err;

	status = netअगर_set_real_num_tx_queues(netdev, adapter->num_tx_qs);
	अगर (status)
		जाओ err;

	वापस 0;
err:
	dev_err(&adapter->pdev->dev, "queue_setup failed\n");
	वापस status;
पूर्ण

अटल पूर्णांक be_अगर_create(काष्ठा be_adapter *adapter)
अणु
	u32 en_flags = BE_IF_FLAGS_RSS | BE_IF_FLAGS_DEFQ_RSS;
	u32 cap_flags = be_अगर_cap_flags(adapter);

	/* alloc required memory क्रम other filtering fields */
	adapter->pmac_id = kसुस्मृति(be_max_uc(adapter),
				   माप(*adapter->pmac_id), GFP_KERNEL);
	अगर (!adapter->pmac_id)
		वापस -ENOMEM;

	adapter->mc_list = kसुस्मृति(be_max_mc(adapter),
				   माप(*adapter->mc_list), GFP_KERNEL);
	अगर (!adapter->mc_list)
		वापस -ENOMEM;

	adapter->uc_list = kसुस्मृति(be_max_uc(adapter),
				   माप(*adapter->uc_list), GFP_KERNEL);
	अगर (!adapter->uc_list)
		वापस -ENOMEM;

	अगर (adapter->cfg_num_rx_irqs == 1)
		cap_flags &= ~(BE_IF_FLAGS_DEFQ_RSS | BE_IF_FLAGS_RSS);

	en_flags &= cap_flags;
	/* will enable all the needed filter flags in be_खोलो() */
	वापस be_cmd_अगर_create(adapter, be_अगर_cap_flags(adapter), en_flags,
				  &adapter->अगर_handle, 0);
पूर्ण

पूर्णांक be_update_queues(काष्ठा be_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक status;

	अगर (netअगर_running(netdev)) अणु
		/* be_tx_समयout() must not run concurrently with this
		 * function, synchronize with an alपढ़ोy-running dev_watchकरोg
		 */
		netअगर_tx_lock_bh(netdev);
		/* device cannot transmit now, aव्योम dev_watchकरोg समयouts */
		netअगर_carrier_off(netdev);
		netअगर_tx_unlock_bh(netdev);

		be_बंद(netdev);
	पूर्ण

	be_cancel_worker(adapter);

	/* If any vectors have been shared with RoCE we cannot re-program
	 * the MSIx table.
	 */
	अगर (!adapter->num_msix_roce_vec)
		be_msix_disable(adapter);

	be_clear_queues(adapter);
	status = be_cmd_अगर_destroy(adapter, adapter->अगर_handle,  0);
	अगर (status)
		वापस status;

	अगर (!msix_enabled(adapter)) अणु
		status = be_msix_enable(adapter);
		अगर (status)
			वापस status;
	पूर्ण

	status = be_अगर_create(adapter);
	अगर (status)
		वापस status;

	status = be_setup_queues(adapter);
	अगर (status)
		वापस status;

	be_schedule_worker(adapter);

	/* The IF was destroyed and re-created. We need to clear
	 * all promiscuous flags valid क्रम the destroyed IF.
	 * Without this promisc mode is not restored during
	 * be_खोलो() because the driver thinks that it is
	 * alपढ़ोy enabled in HW.
	 */
	adapter->अगर_flags &= ~BE_IF_FLAGS_ALL_PROMISCUOUS;

	अगर (netअगर_running(netdev))
		status = be_खोलो(netdev);

	वापस status;
पूर्ण

अटल अंतरभूत पूर्णांक fw_major_num(स्थिर अक्षर *fw_ver)
अणु
	पूर्णांक fw_major = 0, i;

	i = माला_पूछो(fw_ver, "%d.", &fw_major);
	अगर (i != 1)
		वापस 0;

	वापस fw_major;
पूर्ण

/* If it is error recovery, FLR the PF
 * Else अगर any VFs are alपढ़ोy enabled करोn't FLR the PF
 */
अटल bool be_reset_required(काष्ठा be_adapter *adapter)
अणु
	अगर (be_error_recovering(adapter))
		वापस true;
	अन्यथा
		वापस pci_num_vf(adapter->pdev) == 0;
पूर्ण

/* Wait क्रम the FW to be पढ़ोy and perक्रमm the required initialization */
अटल पूर्णांक be_func_init(काष्ठा be_adapter *adapter)
अणु
	पूर्णांक status;

	status = be_fw_रुको_पढ़ोy(adapter);
	अगर (status)
		वापस status;

	/* FW is now पढ़ोy; clear errors to allow cmds/करोorbell */
	be_clear_error(adapter, BE_CLEAR_ALL);

	अगर (be_reset_required(adapter)) अणु
		status = be_cmd_reset_function(adapter);
		अगर (status)
			वापस status;

		/* Wait क्रम पूर्णांकerrupts to quiesce after an FLR */
		msleep(100);
	पूर्ण

	/* Tell FW we're पढ़ोy to fire cmds */
	status = be_cmd_fw_init(adapter);
	अगर (status)
		वापस status;

	/* Allow पूर्णांकerrupts क्रम other ULPs running on NIC function */
	be_पूर्णांकr_set(adapter, true);

	वापस 0;
पूर्ण

अटल पूर्णांक be_setup(काष्ठा be_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक status;

	status = be_func_init(adapter);
	अगर (status)
		वापस status;

	be_setup_init(adapter);

	अगर (!lancer_chip(adapter))
		be_cmd_req_native_mode(adapter);

	/* invoke this cmd first to get pf_num and vf_num which are needed
	 * क्रम issuing profile related cmds
	 */
	अगर (!BEx_chip(adapter)) अणु
		status = be_cmd_get_func_config(adapter, शून्य);
		अगर (status)
			वापस status;
	पूर्ण

	status = be_get_config(adapter);
	अगर (status)
		जाओ err;

	अगर (!BE2_chip(adapter) && be_physfn(adapter))
		be_alloc_sriov_res(adapter);

	status = be_get_resources(adapter);
	अगर (status)
		जाओ err;

	status = be_msix_enable(adapter);
	अगर (status)
		जाओ err;

	/* will enable all the needed filter flags in be_खोलो() */
	status = be_अगर_create(adapter);
	अगर (status)
		जाओ err;

	/* Updating real_num_tx/rx_queues() requires rtnl_lock() */
	rtnl_lock();
	status = be_setup_queues(adapter);
	rtnl_unlock();
	अगर (status)
		जाओ err;

	be_cmd_get_fn_privileges(adapter, &adapter->cmd_privileges, 0);

	status = be_mac_setup(adapter);
	अगर (status)
		जाओ err;

	be_cmd_get_fw_ver(adapter);
	dev_info(dev, "FW version is %s\n", adapter->fw_ver);

	अगर (BE2_chip(adapter) && fw_major_num(adapter->fw_ver) < 4) अणु
		dev_err(dev, "Firmware on card is old(%s), IRQs may not work",
			adapter->fw_ver);
		dev_err(dev, "Please upgrade firmware to version >= 4.0\n");
	पूर्ण

	status = be_cmd_set_flow_control(adapter, adapter->tx_fc,
					 adapter->rx_fc);
	अगर (status)
		be_cmd_get_flow_control(adapter, &adapter->tx_fc,
					&adapter->rx_fc);

	dev_info(&adapter->pdev->dev, "HW Flow control - TX:%d RX:%d\n",
		 adapter->tx_fc, adapter->rx_fc);

	अगर (be_physfn(adapter))
		be_cmd_set_logical_link_config(adapter,
					       IFLA_VF_LINK_STATE_AUTO, 0);

	/* BE3 EVB echoes broadcast/multicast packets back to PF's vport
	 * confusing a linux bridge or OVS that it might be connected to.
	 * Set the EVB to PASSTHRU mode which effectively disables the EVB
	 * when SRIOV is not enabled.
	 */
	अगर (BE3_chip(adapter))
		be_cmd_set_hsw_config(adapter, 0, 0, adapter->अगर_handle,
				      PORT_FWD_TYPE_PASSTHRU, 0);

	अगर (adapter->num_vfs)
		be_vf_setup(adapter);

	status = be_cmd_get_phy_info(adapter);
	अगर (!status && be_छोड़ो_supported(adapter))
		adapter->phy.fc_स्वतःneg = 1;

	अगर (be_physfn(adapter) && !lancer_chip(adapter))
		be_cmd_set_features(adapter);

	be_schedule_worker(adapter);
	adapter->flags |= BE_FLAGS_SETUP_DONE;
	वापस 0;
err:
	be_clear(adapter);
	वापस status;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम be_netpoll(काष्ठा net_device *netdev)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);
	काष्ठा be_eq_obj *eqo;
	पूर्णांक i;

	क्रम_all_evt_queues(adapter, eqo, i) अणु
		be_eq_notअगरy(eqo->adapter, eqo->q.id, false, true, 0, 0);
		napi_schedule(&eqo->napi);
	पूर्ण
पूर्ण
#पूर्ण_अगर

पूर्णांक be_load_fw(काष्ठा be_adapter *adapter, u8 *fw_file)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक status;

	अगर (!netअगर_running(adapter->netdev)) अणु
		dev_err(&adapter->pdev->dev,
			"Firmware load not allowed (interface is down)\n");
		वापस -ENETDOWN;
	पूर्ण

	status = request_firmware(&fw, fw_file, &adapter->pdev->dev);
	अगर (status)
		जाओ fw_निकास;

	dev_info(&adapter->pdev->dev, "Flashing firmware file %s\n", fw_file);

	अगर (lancer_chip(adapter))
		status = lancer_fw_करोwnload(adapter, fw);
	अन्यथा
		status = be_fw_करोwnload(adapter, fw);

	अगर (!status)
		be_cmd_get_fw_ver(adapter);

fw_निकास:
	release_firmware(fw);
	वापस status;
पूर्ण

अटल पूर्णांक be_nकरो_bridge_setlink(काष्ठा net_device *dev, काष्ठा nlmsghdr *nlh,
				 u16 flags, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(dev);
	काष्ठा nlattr *attr, *br_spec;
	पूर्णांक rem;
	पूर्णांक status = 0;
	u16 mode = 0;

	अगर (!sriov_enabled(adapter))
		वापस -EOPNOTSUPP;

	br_spec = nlmsg_find_attr(nlh, माप(काष्ठा अगरinfomsg), IFLA_AF_SPEC);
	अगर (!br_spec)
		वापस -EINVAL;

	nla_क्रम_each_nested(attr, br_spec, rem) अणु
		अगर (nla_type(attr) != IFLA_BRIDGE_MODE)
			जारी;

		अगर (nla_len(attr) < माप(mode))
			वापस -EINVAL;

		mode = nla_get_u16(attr);
		अगर (BE3_chip(adapter) && mode == BRIDGE_MODE_VEPA)
			वापस -EOPNOTSUPP;

		अगर (mode != BRIDGE_MODE_VEPA && mode != BRIDGE_MODE_VEB)
			वापस -EINVAL;

		status = be_cmd_set_hsw_config(adapter, 0, 0,
					       adapter->अगर_handle,
					       mode == BRIDGE_MODE_VEPA ?
					       PORT_FWD_TYPE_VEPA :
					       PORT_FWD_TYPE_VEB, 0);
		अगर (status)
			जाओ err;

		dev_info(&adapter->pdev->dev, "enabled switch mode: %s\n",
			 mode == BRIDGE_MODE_VEPA ? "VEPA" : "VEB");

		वापस status;
	पूर्ण
err:
	dev_err(&adapter->pdev->dev, "Failed to set switch mode %s\n",
		mode == BRIDGE_MODE_VEPA ? "VEPA" : "VEB");

	वापस status;
पूर्ण

अटल पूर्णांक be_nकरो_bridge_getlink(काष्ठा sk_buff *skb, u32 pid, u32 seq,
				 काष्ठा net_device *dev, u32 filter_mask,
				 पूर्णांक nlflags)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(dev);
	पूर्णांक status = 0;
	u8 hsw_mode;

	/* BE and Lancer chips support VEB mode only */
	अगर (BEx_chip(adapter) || lancer_chip(adapter)) अणु
		/* VEB is disabled in non-SR-IOV profiles on BE3/Lancer */
		अगर (!pci_sriov_get_totalvfs(adapter->pdev))
			वापस 0;
		hsw_mode = PORT_FWD_TYPE_VEB;
	पूर्ण अन्यथा अणु
		status = be_cmd_get_hsw_config(adapter, शून्य, 0,
					       adapter->अगर_handle, &hsw_mode,
					       शून्य);
		अगर (status)
			वापस 0;

		अगर (hsw_mode == PORT_FWD_TYPE_PASSTHRU)
			वापस 0;
	पूर्ण

	वापस nकरो_dflt_bridge_getlink(skb, pid, seq, dev,
				       hsw_mode == PORT_FWD_TYPE_VEPA ?
				       BRIDGE_MODE_VEPA : BRIDGE_MODE_VEB,
				       0, 0, nlflags, filter_mask, शून्य);
पूर्ण

अटल काष्ठा be_cmd_work *be_alloc_work(काष्ठा be_adapter *adapter,
					 व्योम (*func)(काष्ठा work_काष्ठा *))
अणु
	काष्ठा be_cmd_work *work;

	work = kzalloc(माप(*work), GFP_ATOMIC);
	अगर (!work) अणु
		dev_err(&adapter->pdev->dev,
			"be_work memory allocation failed\n");
		वापस शून्य;
	पूर्ण

	INIT_WORK(&work->work, func);
	work->adapter = adapter;
	वापस work;
पूर्ण

अटल netdev_features_t be_features_check(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev,
					   netdev_features_t features)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(dev);
	u8 l4_hdr = 0;

	अगर (skb_is_gso(skb)) अणु
		/* IPv6 TSO requests with extension hdrs are a problem
		 * to Lancer and BE3 HW. Disable TSO6 feature.
		 */
		अगर (!skyhawk_chip(adapter) && is_ipv6_ext_hdr(skb))
			features &= ~NETIF_F_TSO6;

		/* Lancer cannot handle the packet with MSS less than 256.
		 * Also it can't handle a TSO packet with a single segment
		 * Disable the GSO support in such हालs
		 */
		अगर (lancer_chip(adapter) &&
		    (skb_shinfo(skb)->gso_size < 256 ||
		     skb_shinfo(skb)->gso_segs == 1))
			features &= ~NETIF_F_GSO_MASK;
	पूर्ण

	/* The code below restricts offload features क्रम some tunneled and
	 * Q-in-Q packets.
	 * Offload features क्रम normal (non tunnel) packets are unchanged.
	 */
	features = vlan_features_check(skb, features);
	अगर (!skb->encapsulation ||
	    !(adapter->flags & BE_FLAGS_VXLAN_OFFLOADS))
		वापस features;

	/* It's an encapsulated packet and VxLAN offloads are enabled. We
	 * should disable tunnel offload features अगर it's not a VxLAN packet,
	 * as tunnel offloads have been enabled only क्रम VxLAN. This is करोne to
	 * allow other tunneled traffic like GRE work fine जबतक VxLAN
	 * offloads are configured in Skyhawk-R.
	 */
	चयन (vlan_get_protocol(skb)) अणु
	हाल htons(ETH_P_IP):
		l4_hdr = ip_hdr(skb)->protocol;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		l4_hdr = ipv6_hdr(skb)->nexthdr;
		अवरोध;
	शेष:
		वापस features;
	पूर्ण

	अगर (l4_hdr != IPPROTO_UDP ||
	    skb->inner_protocol_type != ENCAP_TYPE_ETHER ||
	    skb->inner_protocol != htons(ETH_P_TEB) ||
	    skb_inner_mac_header(skb) - skb_transport_header(skb) !=
		माप(काष्ठा udphdr) + माप(काष्ठा vxlanhdr) ||
	    !adapter->vxlan_port ||
	    udp_hdr(skb)->dest != adapter->vxlan_port)
		वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);

	वापस features;
पूर्ण

अटल पूर्णांक be_get_phys_port_id(काष्ठा net_device *dev,
			       काष्ठा netdev_phys_item_id *ppid)
अणु
	पूर्णांक i, id_len = CNTL_SERIAL_NUM_WORDS * CNTL_SERIAL_NUM_WORD_SZ + 1;
	काष्ठा be_adapter *adapter = netdev_priv(dev);
	u8 *id;

	अगर (MAX_PHYS_ITEM_ID_LEN < id_len)
		वापस -ENOSPC;

	ppid->id[0] = adapter->hba_port_num + 1;
	id = &ppid->id[1];
	क्रम (i = CNTL_SERIAL_NUM_WORDS - 1; i >= 0;
	     i--, id += CNTL_SERIAL_NUM_WORD_SZ)
		स_नकल(id, &adapter->serial_num[i], CNTL_SERIAL_NUM_WORD_SZ);

	ppid->id_len = id_len;

	वापस 0;
पूर्ण

अटल व्योम be_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(dev);
	काष्ठा be_cmd_work *work;

	work = be_alloc_work(adapter, be_work_set_rx_mode);
	अगर (work)
		queue_work(be_wq, &work->work);
पूर्ण

अटल स्थिर काष्ठा net_device_ops be_netdev_ops = अणु
	.nकरो_खोलो		= be_खोलो,
	.nकरो_stop		= be_बंद,
	.nकरो_start_xmit		= be_xmit,
	.nकरो_set_rx_mode	= be_set_rx_mode,
	.nकरो_set_mac_address	= be_mac_addr_set,
	.nकरो_get_stats64	= be_get_stats64,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_vlan_rx_add_vid	= be_vlan_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= be_vlan_rem_vid,
	.nकरो_set_vf_mac		= be_set_vf_mac,
	.nकरो_set_vf_vlan	= be_set_vf_vlan,
	.nकरो_set_vf_rate	= be_set_vf_tx_rate,
	.nकरो_get_vf_config	= be_get_vf_config,
	.nकरो_set_vf_link_state  = be_set_vf_link_state,
	.nकरो_set_vf_spoofchk    = be_set_vf_spoofchk,
	.nकरो_tx_समयout		= be_tx_समयout,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= be_netpoll,
#पूर्ण_अगर
	.nकरो_bridge_setlink	= be_nकरो_bridge_setlink,
	.nकरो_bridge_getlink	= be_nकरो_bridge_getlink,
	.nकरो_features_check	= be_features_check,
	.nकरो_get_phys_port_id   = be_get_phys_port_id,
पूर्ण;

अटल व्योम be_netdev_init(काष्ठा net_device *netdev)
अणु
	काष्ठा be_adapter *adapter = netdev_priv(netdev);

	netdev->hw_features |= NETIF_F_SG | NETIF_F_TSO | NETIF_F_TSO6 |
		NETIF_F_GSO_UDP_TUNNEL |
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | NETIF_F_RXCSUM |
		NETIF_F_HW_VLAN_CTAG_TX;
	अगर ((be_अगर_cap_flags(adapter) & BE_IF_FLAGS_RSS))
		netdev->hw_features |= NETIF_F_RXHASH;

	netdev->features |= netdev->hw_features |
		NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_HW_VLAN_CTAG_FILTER;

	netdev->vlan_features |= NETIF_F_SG | NETIF_F_TSO | NETIF_F_TSO6 |
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;

	netdev->priv_flags |= IFF_UNICAST_FLT;

	netdev->flags |= IFF_MULTICAST;

	netअगर_set_gso_max_size(netdev, BE_MAX_GSO_SIZE - ETH_HLEN);

	netdev->netdev_ops = &be_netdev_ops;

	netdev->ethtool_ops = &be_ethtool_ops;

	अगर (!lancer_chip(adapter) && !BEx_chip(adapter) && !be_is_mc(adapter))
		netdev->udp_tunnel_nic_info = &be_udp_tunnels;

	/* MTU range: 256 - 9000 */
	netdev->min_mtu = BE_MIN_MTU;
	netdev->max_mtu = BE_MAX_MTU;
पूर्ण

अटल व्योम be_cleanup(काष्ठा be_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	rtnl_lock();
	netअगर_device_detach(netdev);
	अगर (netअगर_running(netdev))
		be_बंद(netdev);
	rtnl_unlock();

	be_clear(adapter);
पूर्ण

अटल पूर्णांक be_resume(काष्ठा be_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक status;

	status = be_setup(adapter);
	अगर (status)
		वापस status;

	rtnl_lock();
	अगर (netअगर_running(netdev))
		status = be_खोलो(netdev);
	rtnl_unlock();

	अगर (status)
		वापस status;

	netअगर_device_attach(netdev);

	वापस 0;
पूर्ण

अटल व्योम be_soft_reset(काष्ठा be_adapter *adapter)
अणु
	u32 val;

	dev_info(&adapter->pdev->dev, "Initiating chip soft reset\n");
	val = ioपढ़ो32(adapter->pcicfg + SLIPORT_SOFTRESET_OFFSET);
	val |= SLIPORT_SOFTRESET_SR_MASK;
	ioग_लिखो32(val, adapter->pcicfg + SLIPORT_SOFTRESET_OFFSET);
पूर्ण

अटल bool be_err_is_recoverable(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_error_recovery *err_rec = &adapter->error_recovery;
	अचिन्हित दीर्घ initial_idle_समय =
		msecs_to_jअगरfies(ERR_RECOVERY_IDLE_TIME);
	अचिन्हित दीर्घ recovery_पूर्णांकerval =
		msecs_to_jअगरfies(ERR_RECOVERY_INTERVAL);
	u16 ue_err_code;
	u32 val;

	val = be_POST_stage_get(adapter);
	अगर ((val & POST_STAGE_RECOVERABLE_ERR) != POST_STAGE_RECOVERABLE_ERR)
		वापस false;
	ue_err_code = val & POST_ERR_RECOVERY_CODE_MASK;
	अगर (ue_err_code == 0)
		वापस false;

	dev_err(&adapter->pdev->dev, "Recoverable HW error code: 0x%x\n",
		ue_err_code);

	अगर (समय_beक्रमe_eq(jअगरfies - err_rec->probe_समय, initial_idle_समय)) अणु
		dev_err(&adapter->pdev->dev,
			"Cannot recover within %lu sec from driver load\n",
			jअगरfies_to_msecs(initial_idle_समय) / MSEC_PER_SEC);
		वापस false;
	पूर्ण

	अगर (err_rec->last_recovery_समय && समय_beक्रमe_eq(
		jअगरfies - err_rec->last_recovery_समय, recovery_पूर्णांकerval)) अणु
		dev_err(&adapter->pdev->dev,
			"Cannot recover within %lu sec from last recovery\n",
			jअगरfies_to_msecs(recovery_पूर्णांकerval) / MSEC_PER_SEC);
		वापस false;
	पूर्ण

	अगर (ue_err_code == err_rec->last_err_code) अणु
		dev_err(&adapter->pdev->dev,
			"Cannot recover from a consecutive TPE error\n");
		वापस false;
	पूर्ण

	err_rec->last_recovery_समय = jअगरfies;
	err_rec->last_err_code = ue_err_code;
	वापस true;
पूर्ण

अटल पूर्णांक be_tpe_recover(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_error_recovery *err_rec = &adapter->error_recovery;
	पूर्णांक status = -EAGAIN;
	u32 val;

	चयन (err_rec->recovery_state) अणु
	हाल ERR_RECOVERY_ST_NONE:
		err_rec->recovery_state = ERR_RECOVERY_ST_DETECT;
		err_rec->resched_delay = ERR_RECOVERY_UE_DETECT_DURATION;
		अवरोध;

	हाल ERR_RECOVERY_ST_DETECT:
		val = be_POST_stage_get(adapter);
		अगर ((val & POST_STAGE_RECOVERABLE_ERR) !=
		    POST_STAGE_RECOVERABLE_ERR) अणु
			dev_err(&adapter->pdev->dev,
				"Unrecoverable HW error detected: 0x%x\n", val);
			status = -EINVAL;
			err_rec->resched_delay = 0;
			अवरोध;
		पूर्ण

		dev_err(&adapter->pdev->dev, "Recoverable HW error detected\n");

		/* Only PF0 initiates Chip Soft Reset. But PF0 must रुको UE2SR
		 * milliseconds beक्रमe it checks क्रम final error status in
		 * SLIPORT_SEMAPHORE to determine अगर recovery criteria is met.
		 * If it करोes, then PF0 initiates a Soft Reset.
		 */
		अगर (adapter->pf_num == 0) अणु
			err_rec->recovery_state = ERR_RECOVERY_ST_RESET;
			err_rec->resched_delay = err_rec->ue_to_reset_समय -
					ERR_RECOVERY_UE_DETECT_DURATION;
			अवरोध;
		पूर्ण

		err_rec->recovery_state = ERR_RECOVERY_ST_PRE_POLL;
		err_rec->resched_delay = err_rec->ue_to_poll_समय -
					ERR_RECOVERY_UE_DETECT_DURATION;
		अवरोध;

	हाल ERR_RECOVERY_ST_RESET:
		अगर (!be_err_is_recoverable(adapter)) अणु
			dev_err(&adapter->pdev->dev,
				"Failed to meet recovery criteria\n");
			status = -EIO;
			err_rec->resched_delay = 0;
			अवरोध;
		पूर्ण
		be_soft_reset(adapter);
		err_rec->recovery_state = ERR_RECOVERY_ST_PRE_POLL;
		err_rec->resched_delay = err_rec->ue_to_poll_समय -
					err_rec->ue_to_reset_समय;
		अवरोध;

	हाल ERR_RECOVERY_ST_PRE_POLL:
		err_rec->recovery_state = ERR_RECOVERY_ST_REINIT;
		err_rec->resched_delay = 0;
		status = 0;			/* करोne */
		अवरोध;

	शेष:
		status = -EINVAL;
		err_rec->resched_delay = 0;
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक be_err_recover(काष्ठा be_adapter *adapter)
अणु
	पूर्णांक status;

	अगर (!lancer_chip(adapter)) अणु
		अगर (!adapter->error_recovery.recovery_supported ||
		    adapter->priv_flags & BE_DISABLE_TPE_RECOVERY)
			वापस -EIO;
		status = be_tpe_recover(adapter);
		अगर (status)
			जाओ err;
	पूर्ण

	/* Wait क्रम adapter to reach quiescent state beक्रमe
	 * destroying queues
	 */
	status = be_fw_रुको_पढ़ोy(adapter);
	अगर (status)
		जाओ err;

	adapter->flags |= BE_FLAGS_TRY_RECOVERY;

	be_cleanup(adapter);

	status = be_resume(adapter);
	अगर (status)
		जाओ err;

	adapter->flags &= ~BE_FLAGS_TRY_RECOVERY;

err:
	वापस status;
पूर्ण

अटल व्योम be_err_detection_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा be_error_recovery *err_rec =
			container_of(work, काष्ठा be_error_recovery,
				     err_detection_work.work);
	काष्ठा be_adapter *adapter =
			container_of(err_rec, काष्ठा be_adapter,
				     error_recovery);
	u32 resched_delay = ERR_RECOVERY_DETECTION_DELAY;
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक recovery_status;

	be_detect_error(adapter);
	अगर (!be_check_error(adapter, BE_ERROR_HW))
		जाओ reschedule_task;

	recovery_status = be_err_recover(adapter);
	अगर (!recovery_status) अणु
		err_rec->recovery_retries = 0;
		err_rec->recovery_state = ERR_RECOVERY_ST_NONE;
		dev_info(dev, "Adapter recovery successful\n");
		जाओ reschedule_task;
	पूर्ण अन्यथा अगर (!lancer_chip(adapter) && err_rec->resched_delay) अणु
		/* BEx/SH recovery state machine */
		अगर (adapter->pf_num == 0 &&
		    err_rec->recovery_state > ERR_RECOVERY_ST_DETECT)
			dev_err(&adapter->pdev->dev,
				"Adapter recovery in progress\n");
		resched_delay = err_rec->resched_delay;
		जाओ reschedule_task;
	पूर्ण अन्यथा अगर (lancer_chip(adapter) && be_virtfn(adapter)) अणु
		/* For VFs, check अगर PF have allocated resources
		 * every second.
		 */
		dev_err(dev, "Re-trying adapter recovery\n");
		जाओ reschedule_task;
	पूर्ण अन्यथा अगर (lancer_chip(adapter) && err_rec->recovery_retries++ <
		   ERR_RECOVERY_MAX_RETRY_COUNT) अणु
		/* In हाल of another error during recovery, it takes 30 sec
		 * क्रम adapter to come out of error. Retry error recovery after
		 * this समय पूर्णांकerval.
		 */
		dev_err(&adapter->pdev->dev, "Re-trying adapter recovery\n");
		resched_delay = ERR_RECOVERY_RETRY_DELAY;
		जाओ reschedule_task;
	पूर्ण अन्यथा अणु
		dev_err(dev, "Adapter recovery failed\n");
		dev_err(dev, "Please reboot server to recover\n");
	पूर्ण

	वापस;

reschedule_task:
	be_schedule_err_detection(adapter, resched_delay);
पूर्ण

अटल व्योम be_log_sfp_info(काष्ठा be_adapter *adapter)
अणु
	पूर्णांक status;

	status = be_cmd_query_sfp_info(adapter);
	अगर (!status) अणु
		dev_err(&adapter->pdev->dev,
			"Port %c: %s Vendor: %s part no: %s",
			adapter->port_name,
			be_misconfig_evt_port_state[adapter->phy_state],
			adapter->phy.venकरोr_name,
			adapter->phy.venकरोr_pn);
	पूर्ण
	adapter->flags &= ~BE_FLAGS_PHY_MISCONFIGURED;
पूर्ण

अटल व्योम be_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा be_adapter *adapter =
		container_of(work, काष्ठा be_adapter, work.work);
	काष्ठा be_rx_obj *rxo;
	पूर्णांक i;

	अगर (be_physfn(adapter) &&
	    MODULO(adapter->work_counter, adapter->be_get_temp_freq) == 0)
		be_cmd_get_die_temperature(adapter);

	/* when पूर्णांकerrupts are not yet enabled, just reap any pending
	 * mcc completions
	 */
	अगर (!netअगर_running(adapter->netdev)) अणु
		be_process_mcc(adapter);
		जाओ reschedule;
	पूर्ण

	अगर (!adapter->stats_cmd_sent) अणु
		अगर (lancer_chip(adapter))
			lancer_cmd_get_pport_stats(adapter,
						   &adapter->stats_cmd);
		अन्यथा
			be_cmd_get_stats(adapter, &adapter->stats_cmd);
	पूर्ण

	क्रम_all_rx_queues(adapter, rxo, i) अणु
		/* Replenish RX-queues starved due to memory
		 * allocation failures.
		 */
		अगर (rxo->rx_post_starved)
			be_post_rx_frags(rxo, GFP_KERNEL, MAX_RX_POST);
	पूर्ण

	/* EQ-delay update क्रम Skyhawk is करोne जबतक notअगरying EQ */
	अगर (!skyhawk_chip(adapter))
		be_eqd_update(adapter, false);

	अगर (adapter->flags & BE_FLAGS_PHY_MISCONFIGURED)
		be_log_sfp_info(adapter);

reschedule:
	adapter->work_counter++;
	queue_delayed_work(be_wq, &adapter->work, msecs_to_jअगरfies(1000));
पूर्ण

अटल व्योम be_unmap_pci_bars(काष्ठा be_adapter *adapter)
अणु
	अगर (adapter->csr)
		pci_iounmap(adapter->pdev, adapter->csr);
	अगर (adapter->db)
		pci_iounmap(adapter->pdev, adapter->db);
	अगर (adapter->pcicfg && adapter->pcicfg_mapped)
		pci_iounmap(adapter->pdev, adapter->pcicfg);
पूर्ण

अटल पूर्णांक db_bar(काष्ठा be_adapter *adapter)
अणु
	अगर (lancer_chip(adapter) || be_virtfn(adapter))
		वापस 0;
	अन्यथा
		वापस 4;
पूर्ण

अटल पूर्णांक be_roce_map_pci_bars(काष्ठा be_adapter *adapter)
अणु
	अगर (skyhawk_chip(adapter)) अणु
		adapter->roce_db.size = 4096;
		adapter->roce_db.io_addr = pci_resource_start(adapter->pdev,
							      db_bar(adapter));
		adapter->roce_db.total_size = pci_resource_len(adapter->pdev,
							       db_bar(adapter));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक be_map_pci_bars(काष्ठा be_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	u8 __iomem *addr;
	u32 sli_पूर्णांकf;

	pci_पढ़ो_config_dword(adapter->pdev, SLI_INTF_REG_OFFSET, &sli_पूर्णांकf);
	adapter->sli_family = (sli_पूर्णांकf & SLI_INTF_FAMILY_MASK) >>
				SLI_INTF_FAMILY_SHIFT;
	adapter->virtfn = (sli_पूर्णांकf & SLI_INTF_FT_MASK) ? 1 : 0;

	अगर (BEx_chip(adapter) && be_physfn(adapter)) अणु
		adapter->csr = pci_iomap(pdev, 2, 0);
		अगर (!adapter->csr)
			वापस -ENOMEM;
	पूर्ण

	addr = pci_iomap(pdev, db_bar(adapter), 0);
	अगर (!addr)
		जाओ pci_map_err;
	adapter->db = addr;

	अगर (skyhawk_chip(adapter) || BEx_chip(adapter)) अणु
		अगर (be_physfn(adapter)) अणु
			/* PCICFG is the 2nd BAR in BE2 */
			addr = pci_iomap(pdev, BE2_chip(adapter) ? 1 : 0, 0);
			अगर (!addr)
				जाओ pci_map_err;
			adapter->pcicfg = addr;
			adapter->pcicfg_mapped = true;
		पूर्ण अन्यथा अणु
			adapter->pcicfg = adapter->db + SRIOV_VF_PCICFG_OFFSET;
			adapter->pcicfg_mapped = false;
		पूर्ण
	पूर्ण

	be_roce_map_pci_bars(adapter);
	वापस 0;

pci_map_err:
	dev_err(&pdev->dev, "Error in mapping PCI BARs\n");
	be_unmap_pci_bars(adapter);
	वापस -ENOMEM;
पूर्ण

अटल व्योम be_drv_cleanup(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_dma_mem *mem = &adapter->mbox_mem_alloced;
	काष्ठा device *dev = &adapter->pdev->dev;

	अगर (mem->va)
		dma_मुक्त_coherent(dev, mem->size, mem->va, mem->dma);

	mem = &adapter->rx_filter;
	अगर (mem->va)
		dma_मुक्त_coherent(dev, mem->size, mem->va, mem->dma);

	mem = &adapter->stats_cmd;
	अगर (mem->va)
		dma_मुक्त_coherent(dev, mem->size, mem->va, mem->dma);
पूर्ण

/* Allocate and initialize various fields in be_adapter काष्ठा */
अटल पूर्णांक be_drv_init(काष्ठा be_adapter *adapter)
अणु
	काष्ठा be_dma_mem *mbox_mem_alloc = &adapter->mbox_mem_alloced;
	काष्ठा be_dma_mem *mbox_mem_align = &adapter->mbox_mem;
	काष्ठा be_dma_mem *rx_filter = &adapter->rx_filter;
	काष्ठा be_dma_mem *stats_cmd = &adapter->stats_cmd;
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक status = 0;

	mbox_mem_alloc->size = माप(काष्ठा be_mcc_mailbox) + 16;
	mbox_mem_alloc->va = dma_alloc_coherent(dev, mbox_mem_alloc->size,
						&mbox_mem_alloc->dma,
						GFP_KERNEL);
	अगर (!mbox_mem_alloc->va)
		वापस -ENOMEM;

	mbox_mem_align->size = माप(काष्ठा be_mcc_mailbox);
	mbox_mem_align->va = PTR_ALIGN(mbox_mem_alloc->va, 16);
	mbox_mem_align->dma = PTR_ALIGN(mbox_mem_alloc->dma, 16);

	rx_filter->size = माप(काष्ठा be_cmd_req_rx_filter);
	rx_filter->va = dma_alloc_coherent(dev, rx_filter->size,
					   &rx_filter->dma, GFP_KERNEL);
	अगर (!rx_filter->va) अणु
		status = -ENOMEM;
		जाओ मुक्त_mbox;
	पूर्ण

	अगर (lancer_chip(adapter))
		stats_cmd->size = माप(काष्ठा lancer_cmd_req_pport_stats);
	अन्यथा अगर (BE2_chip(adapter))
		stats_cmd->size = माप(काष्ठा be_cmd_req_get_stats_v0);
	अन्यथा अगर (BE3_chip(adapter))
		stats_cmd->size = माप(काष्ठा be_cmd_req_get_stats_v1);
	अन्यथा
		stats_cmd->size = माप(काष्ठा be_cmd_req_get_stats_v2);
	stats_cmd->va = dma_alloc_coherent(dev, stats_cmd->size,
					   &stats_cmd->dma, GFP_KERNEL);
	अगर (!stats_cmd->va) अणु
		status = -ENOMEM;
		जाओ मुक्त_rx_filter;
	पूर्ण

	mutex_init(&adapter->mbox_lock);
	mutex_init(&adapter->mcc_lock);
	mutex_init(&adapter->rx_filter_lock);
	spin_lock_init(&adapter->mcc_cq_lock);
	init_completion(&adapter->et_cmd_compl);

	pci_save_state(adapter->pdev);

	INIT_DELAYED_WORK(&adapter->work, be_worker);

	adapter->error_recovery.recovery_state = ERR_RECOVERY_ST_NONE;
	adapter->error_recovery.resched_delay = 0;
	INIT_DELAYED_WORK(&adapter->error_recovery.err_detection_work,
			  be_err_detection_task);

	adapter->rx_fc = true;
	adapter->tx_fc = true;

	/* Must be a घातer of 2 or अन्यथा MODULO will BUG_ON */
	adapter->be_get_temp_freq = 64;

	वापस 0;

मुक्त_rx_filter:
	dma_मुक्त_coherent(dev, rx_filter->size, rx_filter->va, rx_filter->dma);
मुक्त_mbox:
	dma_मुक्त_coherent(dev, mbox_mem_alloc->size, mbox_mem_alloc->va,
			  mbox_mem_alloc->dma);
	वापस status;
पूर्ण

अटल व्योम be_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा be_adapter *adapter = pci_get_drvdata(pdev);

	अगर (!adapter)
		वापस;

	be_roce_dev_हटाओ(adapter);
	be_पूर्णांकr_set(adapter, false);

	be_cancel_err_detection(adapter);

	unरेजिस्टर_netdev(adapter->netdev);

	be_clear(adapter);

	अगर (!pci_vfs_asचिन्हित(adapter->pdev))
		be_cmd_reset_function(adapter);

	/* tell fw we're करोne with firing cmds */
	be_cmd_fw_clean(adapter);

	be_unmap_pci_bars(adapter);
	be_drv_cleanup(adapter);

	pci_disable_pcie_error_reporting(pdev);

	pci_release_regions(pdev);
	pci_disable_device(pdev);

	मुक्त_netdev(adapter->netdev);
पूर्ण

अटल sमाप_प्रकार be_hwmon_show_temp(काष्ठा device *dev,
				  काष्ठा device_attribute *dev_attr,
				  अक्षर *buf)
अणु
	काष्ठा be_adapter *adapter = dev_get_drvdata(dev);

	/* Unit: millidegree Celsius */
	अगर (adapter->hwmon_info.be_on_die_temp == BE_INVALID_DIE_TEMP)
		वापस -EIO;
	अन्यथा
		वापस प्र_लिखो(buf, "%u\n",
			       adapter->hwmon_info.be_on_die_temp * 1000);
पूर्ण

अटल SENSOR_DEVICE_ATTR(temp1_input, 0444,
			  be_hwmon_show_temp, शून्य, 1);

अटल काष्ठा attribute *be_hwmon_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(be_hwmon);

अटल अक्षर *mc_name(काष्ठा be_adapter *adapter)
अणु
	अक्षर *str = "";	/* शेष */

	चयन (adapter->mc_type) अणु
	हाल UMC:
		str = "UMC";
		अवरोध;
	हाल FLEX10:
		str = "FLEX10";
		अवरोध;
	हाल vNIC1:
		str = "vNIC-1";
		अवरोध;
	हाल nPAR:
		str = "nPAR";
		अवरोध;
	हाल UFP:
		str = "UFP";
		अवरोध;
	हाल vNIC2:
		str = "vNIC-2";
		अवरोध;
	शेष:
		str = "";
	पूर्ण

	वापस str;
पूर्ण

अटल अंतरभूत अक्षर *func_name(काष्ठा be_adapter *adapter)
अणु
	वापस be_physfn(adapter) ? "PF" : "VF";
पूर्ण

अटल अंतरभूत अक्षर *nic_name(काष्ठा pci_dev *pdev)
अणु
	चयन (pdev->device) अणु
	हाल OC_DEVICE_ID1:
		वापस OC_NAME;
	हाल OC_DEVICE_ID2:
		वापस OC_NAME_BE;
	हाल OC_DEVICE_ID3:
	हाल OC_DEVICE_ID4:
		वापस OC_NAME_LANCER;
	हाल BE_DEVICE_ID2:
		वापस BE3_NAME;
	हाल OC_DEVICE_ID5:
	हाल OC_DEVICE_ID6:
		वापस OC_NAME_SH;
	शेष:
		वापस BE_NAME;
	पूर्ण
पूर्ण

अटल पूर्णांक be_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *pdev_id)
अणु
	काष्ठा be_adapter *adapter;
	काष्ठा net_device *netdev;
	पूर्णांक status = 0;

	status = pci_enable_device(pdev);
	अगर (status)
		जाओ करो_none;

	status = pci_request_regions(pdev, DRV_NAME);
	अगर (status)
		जाओ disable_dev;
	pci_set_master(pdev);

	netdev = alloc_etherdev_mqs(माप(*adapter), MAX_TX_QS, MAX_RX_QS);
	अगर (!netdev) अणु
		status = -ENOMEM;
		जाओ rel_reg;
	पूर्ण
	adapter = netdev_priv(netdev);
	adapter->pdev = pdev;
	pci_set_drvdata(pdev, adapter);
	adapter->netdev = netdev;
	SET_NETDEV_DEV(netdev, &pdev->dev);

	status = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (!status) अणु
		netdev->features |= NETIF_F_HIGHDMA;
	पूर्ण अन्यथा अणु
		status = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (status) अणु
			dev_err(&pdev->dev, "Could not set PCI DMA Mask\n");
			जाओ मुक्त_netdev;
		पूर्ण
	पूर्ण

	status = pci_enable_pcie_error_reporting(pdev);
	अगर (!status)
		dev_info(&pdev->dev, "PCIe error reporting enabled\n");

	status = be_map_pci_bars(adapter);
	अगर (status)
		जाओ मुक्त_netdev;

	status = be_drv_init(adapter);
	अगर (status)
		जाओ unmap_bars;

	status = be_setup(adapter);
	अगर (status)
		जाओ drv_cleanup;

	be_netdev_init(netdev);
	status = रेजिस्टर_netdev(netdev);
	अगर (status != 0)
		जाओ unsetup;

	be_roce_dev_add(adapter);

	be_schedule_err_detection(adapter, ERR_DETECTION_DELAY);
	adapter->error_recovery.probe_समय = jअगरfies;

	/* On Die temperature not supported क्रम VF. */
	अगर (be_physfn(adapter) && IS_ENABLED(CONFIG_BE2NET_HWMON)) अणु
		adapter->hwmon_info.hwmon_dev =
			devm_hwmon_device_रेजिस्टर_with_groups(&pdev->dev,
							       DRV_NAME,
							       adapter,
							       be_hwmon_groups);
		adapter->hwmon_info.be_on_die_temp = BE_INVALID_DIE_TEMP;
	पूर्ण

	dev_info(&pdev->dev, "%s: %s %s port %c\n", nic_name(pdev),
		 func_name(adapter), mc_name(adapter), adapter->port_name);

	वापस 0;

unsetup:
	be_clear(adapter);
drv_cleanup:
	be_drv_cleanup(adapter);
unmap_bars:
	be_unmap_pci_bars(adapter);
मुक्त_netdev:
	pci_disable_pcie_error_reporting(pdev);
	मुक्त_netdev(netdev);
rel_reg:
	pci_release_regions(pdev);
disable_dev:
	pci_disable_device(pdev);
करो_none:
	dev_err(&pdev->dev, "%s initialization failed\n", nic_name(pdev));
	वापस status;
पूर्ण

अटल पूर्णांक __maybe_unused be_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा be_adapter *adapter = dev_get_drvdata(dev_d);

	be_पूर्णांकr_set(adapter, false);
	be_cancel_err_detection(adapter);

	be_cleanup(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused be_pci_resume(काष्ठा device *dev_d)
अणु
	काष्ठा be_adapter *adapter = dev_get_drvdata(dev_d);
	पूर्णांक status = 0;

	status = be_resume(adapter);
	अगर (status)
		वापस status;

	be_schedule_err_detection(adapter, ERR_DETECTION_DELAY);

	वापस 0;
पूर्ण

/*
 * An FLR will stop BE from DMAing any data.
 */
अटल व्योम be_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा be_adapter *adapter = pci_get_drvdata(pdev);

	अगर (!adapter)
		वापस;

	be_roce_dev_shutकरोwn(adapter);
	cancel_delayed_work_sync(&adapter->work);
	be_cancel_err_detection(adapter);

	netअगर_device_detach(adapter->netdev);

	be_cmd_reset_function(adapter);

	pci_disable_device(pdev);
पूर्ण

अटल pci_ers_result_t be_eeh_err_detected(काष्ठा pci_dev *pdev,
					    pci_channel_state_t state)
अणु
	काष्ठा be_adapter *adapter = pci_get_drvdata(pdev);

	dev_err(&adapter->pdev->dev, "EEH error detected\n");

	be_roce_dev_हटाओ(adapter);

	अगर (!be_check_error(adapter, BE_ERROR_EEH)) अणु
		be_set_error(adapter, BE_ERROR_EEH);

		be_cancel_err_detection(adapter);

		be_cleanup(adapter);
	पूर्ण

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	pci_disable_device(pdev);

	/* The error could cause the FW to trigger a flash debug dump.
	 * Resetting the card जबतक flash dump is in progress
	 * can cause it not to recover; रुको क्रम it to finish.
	 * Wait only क्रम first function as it is needed only once per
	 * adapter.
	 */
	अगर (pdev->devfn == 0)
		ssleep(30);

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t be_eeh_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा be_adapter *adapter = pci_get_drvdata(pdev);
	पूर्णांक status;

	dev_info(&adapter->pdev->dev, "EEH reset\n");

	status = pci_enable_device(pdev);
	अगर (status)
		वापस PCI_ERS_RESULT_DISCONNECT;

	pci_set_master(pdev);
	pci_restore_state(pdev);

	/* Check अगर card is ok and fw is पढ़ोy */
	dev_info(&adapter->pdev->dev,
		 "Waiting for FW to be ready after EEH reset\n");
	status = be_fw_रुको_पढ़ोy(adapter);
	अगर (status)
		वापस PCI_ERS_RESULT_DISCONNECT;

	be_clear_error(adapter, BE_CLEAR_ALL);
	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल व्योम be_eeh_resume(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक status = 0;
	काष्ठा be_adapter *adapter = pci_get_drvdata(pdev);

	dev_info(&adapter->pdev->dev, "EEH resume\n");

	pci_save_state(pdev);

	status = be_resume(adapter);
	अगर (status)
		जाओ err;

	be_roce_dev_add(adapter);

	be_schedule_err_detection(adapter, ERR_DETECTION_DELAY);
	वापस;
err:
	dev_err(&adapter->pdev->dev, "EEH resume failed\n");
पूर्ण

अटल पूर्णांक be_pci_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा be_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा be_resources vft_res = अणु0पूर्ण;
	पूर्णांक status;

	अगर (!num_vfs)
		be_vf_clear(adapter);

	adapter->num_vfs = num_vfs;

	अगर (adapter->num_vfs == 0 && pci_vfs_asचिन्हित(pdev)) अणु
		dev_warn(&pdev->dev,
			 "Cannot disable VFs while they are assigned\n");
		वापस -EBUSY;
	पूर्ण

	/* When the HW is in SRIOV capable configuration, the PF-pool resources
	 * are equally distributed across the max-number of VFs. The user may
	 * request only a subset of the max-vfs to be enabled.
	 * Based on num_vfs, redistribute the resources across num_vfs so that
	 * each VF will have access to more number of resources.
	 * This facility is not available in BE3 FW.
	 * Also, this is करोne by FW in Lancer chip.
	 */
	अगर (skyhawk_chip(adapter) && !pci_num_vf(pdev)) अणु
		be_calculate_vf_res(adapter, adapter->num_vfs,
				    &vft_res);
		status = be_cmd_set_sriov_config(adapter, adapter->pool_res,
						 adapter->num_vfs, &vft_res);
		अगर (status)
			dev_err(&pdev->dev,
				"Failed to optimize SR-IOV resources\n");
	पूर्ण

	status = be_get_resources(adapter);
	अगर (status)
		वापस be_cmd_status(status);

	/* Updating real_num_tx/rx_queues() requires rtnl_lock() */
	rtnl_lock();
	status = be_update_queues(adapter);
	rtnl_unlock();
	अगर (status)
		वापस be_cmd_status(status);

	अगर (adapter->num_vfs)
		status = be_vf_setup(adapter);

	अगर (!status)
		वापस adapter->num_vfs;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers be_eeh_handlers = अणु
	.error_detected = be_eeh_err_detected,
	.slot_reset = be_eeh_reset,
	.resume = be_eeh_resume,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(be_pci_pm_ops, be_suspend, be_pci_resume);

अटल काष्ठा pci_driver be_driver = अणु
	.name = DRV_NAME,
	.id_table = be_dev_ids,
	.probe = be_probe,
	.हटाओ = be_हटाओ,
	.driver.pm = &be_pci_pm_ops,
	.shutकरोwn = be_shutकरोwn,
	.sriov_configure = be_pci_sriov_configure,
	.err_handler = &be_eeh_handlers
पूर्ण;

अटल पूर्णांक __init be_init_module(व्योम)
अणु
	पूर्णांक status;

	अगर (rx_frag_size != 8192 && rx_frag_size != 4096 &&
	    rx_frag_size != 2048) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME
			" : Module param rx_frag_size must be 2048/4096/8192."
			" Using 2048\n");
		rx_frag_size = 2048;
	पूर्ण

	अगर (num_vfs > 0) अणु
		pr_info(DRV_NAME " : Module param num_vfs is obsolete.");
		pr_info(DRV_NAME " : Use sysfs method to enable VFs\n");
	पूर्ण

	be_wq = create_singlethपढ़ो_workqueue("be_wq");
	अगर (!be_wq) अणु
		pr_warn(DRV_NAME "workqueue creation failed\n");
		वापस -1;
	पूर्ण

	be_err_recovery_workq =
		create_singlethपढ़ो_workqueue("be_err_recover");
	अगर (!be_err_recovery_workq)
		pr_warn(DRV_NAME "Could not create error recovery workqueue\n");

	status = pci_रेजिस्टर_driver(&be_driver);
	अगर (status) अणु
		destroy_workqueue(be_wq);
		be_destroy_err_recovery_workq();
	पूर्ण
	वापस status;
पूर्ण
module_init(be_init_module);

अटल व्योम __निकास be_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&be_driver);

	be_destroy_err_recovery_workq();

	अगर (be_wq)
		destroy_workqueue(be_wq);
पूर्ण
module_निकास(be_निकास_module);
