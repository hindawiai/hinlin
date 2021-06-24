<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/aer.h>

#समावेश "qlcnic.h"
#समावेश "qlcnic_sriov.h"

अटल व्योम __qlcnic_83xx_process_aen(काष्ठा qlcnic_adapter *);
अटल पूर्णांक qlcnic_83xx_clear_lb_mode(काष्ठा qlcnic_adapter *, u8);
अटल व्योम qlcnic_83xx_configure_mac(काष्ठा qlcnic_adapter *, u8 *, u8,
				      काष्ठा qlcnic_cmd_args *);
अटल पूर्णांक qlcnic_83xx_get_port_config(काष्ठा qlcnic_adapter *);
अटल irqवापस_t qlcnic_83xx_handle_aen(पूर्णांक, व्योम *);
अटल pci_ers_result_t qlcnic_83xx_io_error_detected(काष्ठा pci_dev *,
						      pci_channel_state_t);
अटल पूर्णांक qlcnic_83xx_set_port_config(काष्ठा qlcnic_adapter *);
अटल pci_ers_result_t qlcnic_83xx_io_slot_reset(काष्ठा pci_dev *);
अटल व्योम qlcnic_83xx_io_resume(काष्ठा pci_dev *);
अटल पूर्णांक qlcnic_83xx_set_lb_mode(काष्ठा qlcnic_adapter *, u8);
अटल व्योम qlcnic_83xx_set_mac_filter_count(काष्ठा qlcnic_adapter *);
अटल पूर्णांक qlcnic_83xx_resume(काष्ठा qlcnic_adapter *);
अटल पूर्णांक qlcnic_83xx_shutकरोwn(काष्ठा pci_dev *);
अटल व्योम qlcnic_83xx_get_beacon_state(काष्ठा qlcnic_adapter *);

#घोषणा RSS_HASHTYPE_IP_TCP		0x3
#घोषणा QLC_83XX_FW_MBX_CMD		0
#घोषणा QLC_SKIP_INACTIVE_PCI_REGS	7
#घोषणा QLC_MAX_LEGACY_FUNC_SUPP	8

/* 83xx Module type */
#घोषणा QLC_83XX_MODULE_FIBRE_10GBASE_LRM	0x1 /* 10GBase-LRM */
#घोषणा QLC_83XX_MODULE_FIBRE_10GBASE_LR	0x2 /* 10GBase-LR */
#घोषणा QLC_83XX_MODULE_FIBRE_10GBASE_SR	0x3 /* 10GBase-SR */
#घोषणा QLC_83XX_MODULE_DA_10GE_PASSIVE_CP	0x4 /* 10GE passive
						     * copper(compliant)
						     */
#घोषणा QLC_83XX_MODULE_DA_10GE_ACTIVE_CP	0x5 /* 10GE active limiting
						     * copper(compliant)
						     */
#घोषणा QLC_83XX_MODULE_DA_10GE_LEGACY_CP	0x6 /* 10GE passive copper
						     * (legacy, best efक्रमt)
						     */
#घोषणा QLC_83XX_MODULE_FIBRE_1000BASE_SX	0x7 /* 1000Base-SX */
#घोषणा QLC_83XX_MODULE_FIBRE_1000BASE_LX	0x8 /* 1000Base-LX */
#घोषणा QLC_83XX_MODULE_FIBRE_1000BASE_CX	0x9 /* 1000Base-CX */
#घोषणा QLC_83XX_MODULE_TP_1000BASE_T		0xa /* 1000Base-T*/
#घोषणा QLC_83XX_MODULE_DA_1GE_PASSIVE_CP	0xb /* 1GE passive copper
						     * (legacy, best efक्रमt)
						     */
#घोषणा QLC_83XX_MODULE_UNKNOWN			0xf /* Unknown module type */

/* Port types */
#घोषणा QLC_83XX_10_CAPABLE	 BIT_8
#घोषणा QLC_83XX_100_CAPABLE	 BIT_9
#घोषणा QLC_83XX_1G_CAPABLE	 BIT_10
#घोषणा QLC_83XX_10G_CAPABLE	 BIT_11
#घोषणा QLC_83XX_AUTONEG_ENABLE	 BIT_15

अटल स्थिर काष्ठा qlcnic_mailbox_metadata qlcnic_83xx_mbx_tbl[] = अणु
	अणुQLCNIC_CMD_CONFIGURE_IP_ADDR, 6, 1पूर्ण,
	अणुQLCNIC_CMD_CONFIG_INTRPT, 18, 34पूर्ण,
	अणुQLCNIC_CMD_CREATE_RX_CTX, 136, 27पूर्ण,
	अणुQLCNIC_CMD_DESTROY_RX_CTX, 2, 1पूर्ण,
	अणुQLCNIC_CMD_CREATE_TX_CTX, 54, 18पूर्ण,
	अणुQLCNIC_CMD_DESTROY_TX_CTX, 2, 1पूर्ण,
	अणुQLCNIC_CMD_CONFIGURE_MAC_LEARNING, 2, 1पूर्ण,
	अणुQLCNIC_CMD_INTRPT_TEST, 22, 12पूर्ण,
	अणुQLCNIC_CMD_SET_MTU, 3, 1पूर्ण,
	अणुQLCNIC_CMD_READ_PHY, 4, 2पूर्ण,
	अणुQLCNIC_CMD_WRITE_PHY, 5, 1पूर्ण,
	अणुQLCNIC_CMD_READ_HW_REG, 4, 1पूर्ण,
	अणुQLCNIC_CMD_GET_FLOW_CTL, 4, 2पूर्ण,
	अणुQLCNIC_CMD_SET_FLOW_CTL, 4, 1पूर्ण,
	अणुQLCNIC_CMD_READ_MAX_MTU, 4, 2पूर्ण,
	अणुQLCNIC_CMD_READ_MAX_LRO, 4, 2पूर्ण,
	अणुQLCNIC_CMD_MAC_ADDRESS, 4, 3पूर्ण,
	अणुQLCNIC_CMD_GET_PCI_INFO, 1, 129पूर्ण,
	अणुQLCNIC_CMD_GET_NIC_INFO, 2, 19पूर्ण,
	अणुQLCNIC_CMD_SET_NIC_INFO, 32, 1पूर्ण,
	अणुQLCNIC_CMD_GET_ESWITCH_CAPABILITY, 4, 3पूर्ण,
	अणुQLCNIC_CMD_TOGGLE_ESWITCH, 4, 1पूर्ण,
	अणुQLCNIC_CMD_GET_ESWITCH_STATUS, 4, 3पूर्ण,
	अणुQLCNIC_CMD_SET_PORTMIRRORING, 4, 1पूर्ण,
	अणुQLCNIC_CMD_CONFIGURE_ESWITCH, 4, 1पूर्ण,
	अणुQLCNIC_CMD_GET_ESWITCH_PORT_CONFIG, 4, 3पूर्ण,
	अणुQLCNIC_CMD_GET_ESWITCH_STATS, 5, 1पूर्ण,
	अणुQLCNIC_CMD_CONFIG_PORT, 4, 1पूर्ण,
	अणुQLCNIC_CMD_TEMP_SIZE, 1, 4पूर्ण,
	अणुQLCNIC_CMD_GET_TEMP_HDR, 5, 5पूर्ण,
	अणुQLCNIC_CMD_GET_LINK_EVENT, 2, 1पूर्ण,
	अणुQLCNIC_CMD_CONFIG_MAC_VLAN, 4, 3पूर्ण,
	अणुQLCNIC_CMD_CONFIG_INTR_COAL, 6, 1पूर्ण,
	अणुQLCNIC_CMD_CONFIGURE_RSS, 14, 1पूर्ण,
	अणुQLCNIC_CMD_CONFIGURE_LED, 2, 1पूर्ण,
	अणुQLCNIC_CMD_CONFIGURE_MAC_RX_MODE, 2, 1पूर्ण,
	अणुQLCNIC_CMD_CONFIGURE_HW_LRO, 2, 1पूर्ण,
	अणुQLCNIC_CMD_GET_STATISTICS, 2, 80पूर्ण,
	अणुQLCNIC_CMD_SET_PORT_CONFIG, 2, 1पूर्ण,
	अणुQLCNIC_CMD_GET_PORT_CONFIG, 2, 2पूर्ण,
	अणुQLCNIC_CMD_GET_LINK_STATUS, 2, 4पूर्ण,
	अणुQLCNIC_CMD_IDC_ACK, 5, 1पूर्ण,
	अणुQLCNIC_CMD_INIT_NIC_FUNC, 3, 1पूर्ण,
	अणुQLCNIC_CMD_STOP_NIC_FUNC, 2, 1पूर्ण,
	अणुQLCNIC_CMD_SET_LED_CONFIG, 5, 1पूर्ण,
	अणुQLCNIC_CMD_GET_LED_CONFIG, 1, 5पूर्ण,
	अणुQLCNIC_CMD_83XX_SET_DRV_VER, 4, 1पूर्ण,
	अणुQLCNIC_CMD_ADD_RCV_RINGS, 130, 26पूर्ण,
	अणुQLCNIC_CMD_CONFIG_VPORT, 4, 4पूर्ण,
	अणुQLCNIC_CMD_BC_EVENT_SETUP, 2, 1पूर्ण,
	अणुQLCNIC_CMD_DCB_QUERY_CAP, 1, 2पूर्ण,
	अणुQLCNIC_CMD_DCB_QUERY_PARAM, 1, 50पूर्ण,
	अणुQLCNIC_CMD_SET_INGRESS_ENCAP, 2, 1पूर्ण,
	अणुQLCNIC_CMD_83XX_EXTEND_ISCSI_DUMP_CAP, 4, 1पूर्ण,
पूर्ण;

स्थिर u32 qlcnic_83xx_ext_reg_tbl[] = अणु
	0x38CC,		/* Global Reset */
	0x38F0,		/* Wildcard */
	0x38FC,		/* Inक्रमmant */
	0x3038,		/* Host MBX ctrl */
	0x303C,		/* FW MBX ctrl */
	0x355C,		/* BOOT LOADER ADDRESS REG */
	0x3560,		/* BOOT LOADER SIZE REG */
	0x3564,		/* FW IMAGE ADDR REG */
	0x1000,		/* MBX पूर्णांकr enable */
	0x1200,		/* Default Intr mask */
	0x1204,		/* Default Interrupt ID */
	0x3780,		/* QLC_83XX_IDC_MAJ_VERSION */
	0x3784,		/* QLC_83XX_IDC_DEV_STATE */
	0x3788,		/* QLC_83XX_IDC_DRV_PRESENCE */
	0x378C,		/* QLC_83XX_IDC_DRV_ACK */
	0x3790,		/* QLC_83XX_IDC_CTRL */
	0x3794,		/* QLC_83XX_IDC_DRV_AUDIT */
	0x3798,		/* QLC_83XX_IDC_MIN_VERSION */
	0x379C,		/* QLC_83XX_RECOVER_DRV_LOCK */
	0x37A0,		/* QLC_83XX_IDC_PF_0 */
	0x37A4,		/* QLC_83XX_IDC_PF_1 */
	0x37A8,		/* QLC_83XX_IDC_PF_2 */
	0x37AC,		/* QLC_83XX_IDC_PF_3 */
	0x37B0,		/* QLC_83XX_IDC_PF_4 */
	0x37B4,		/* QLC_83XX_IDC_PF_5 */
	0x37B8,		/* QLC_83XX_IDC_PF_6 */
	0x37BC,		/* QLC_83XX_IDC_PF_7 */
	0x37C0,		/* QLC_83XX_IDC_PF_8 */
	0x37C4,		/* QLC_83XX_IDC_PF_9 */
	0x37C8,		/* QLC_83XX_IDC_PF_10 */
	0x37CC,		/* QLC_83XX_IDC_PF_11 */
	0x37D0,		/* QLC_83XX_IDC_PF_12 */
	0x37D4,		/* QLC_83XX_IDC_PF_13 */
	0x37D8,		/* QLC_83XX_IDC_PF_14 */
	0x37DC,		/* QLC_83XX_IDC_PF_15 */
	0x37E0,		/* QLC_83XX_IDC_DEV_PARTITION_INFO_1 */
	0x37E4,		/* QLC_83XX_IDC_DEV_PARTITION_INFO_2 */
	0x37F0,		/* QLC_83XX_DRV_OP_MODE */
	0x37F4,		/* QLC_83XX_VNIC_STATE */
	0x3868,		/* QLC_83XX_DRV_LOCK */
	0x386C,		/* QLC_83XX_DRV_UNLOCK */
	0x3504,		/* QLC_83XX_DRV_LOCK_ID */
	0x34A4,		/* QLC_83XX_ASIC_TEMP */
पूर्ण;

स्थिर u32 qlcnic_83xx_reg_tbl[] = अणु
	0x34A8,		/* PEG_HALT_STAT1 */
	0x34AC,		/* PEG_HALT_STAT2 */
	0x34B0,		/* FW_HEARTBEAT */
	0x3500,		/* FLASH LOCK_ID */
	0x3528,		/* FW_CAPABILITIES */
	0x3538,		/* Driver active, DRV_REG0 */
	0x3540,		/* Device state, DRV_REG1 */
	0x3544,		/* Driver state, DRV_REG2 */
	0x3548,		/* Driver scratch, DRV_REG3 */
	0x354C,		/* Device partition info, DRV_REG4 */
	0x3524,		/* Driver IDC ver, DRV_REG5 */
	0x3550,		/* FW_VER_MAJOR */
	0x3554,		/* FW_VER_MINOR */
	0x3558,		/* FW_VER_SUB */
	0x359C,		/* NPAR STATE */
	0x35FC,		/* FW_IMG_VALID */
	0x3650,		/* CMD_PEG_STATE */
	0x373C,		/* RCV_PEG_STATE */
	0x37B4,		/* ASIC TEMP */
	0x356C,		/* FW API */
	0x3570,		/* DRV OP MODE */
	0x3850,		/* FLASH LOCK */
	0x3854,		/* FLASH UNLOCK */
पूर्ण;

अटल काष्ठा qlcnic_hardware_ops qlcnic_83xx_hw_ops = अणु
	.पढ़ो_crb			= qlcnic_83xx_पढ़ो_crb,
	.ग_लिखो_crb			= qlcnic_83xx_ग_लिखो_crb,
	.पढ़ो_reg			= qlcnic_83xx_rd_reg_indirect,
	.ग_लिखो_reg			= qlcnic_83xx_wrt_reg_indirect,
	.get_mac_address		= qlcnic_83xx_get_mac_address,
	.setup_पूर्णांकr			= qlcnic_83xx_setup_पूर्णांकr,
	.alloc_mbx_args			= qlcnic_83xx_alloc_mbx_args,
	.mbx_cmd			= qlcnic_83xx_issue_cmd,
	.get_func_no			= qlcnic_83xx_get_func_no,
	.api_lock			= qlcnic_83xx_cam_lock,
	.api_unlock			= qlcnic_83xx_cam_unlock,
	.add_sysfs			= qlcnic_83xx_add_sysfs,
	.हटाओ_sysfs			= qlcnic_83xx_हटाओ_sysfs,
	.process_lb_rcv_ring_diag	= qlcnic_83xx_process_rcv_ring_diag,
	.create_rx_ctx			= qlcnic_83xx_create_rx_ctx,
	.create_tx_ctx			= qlcnic_83xx_create_tx_ctx,
	.del_rx_ctx			= qlcnic_83xx_del_rx_ctx,
	.del_tx_ctx			= qlcnic_83xx_del_tx_ctx,
	.setup_link_event		= qlcnic_83xx_setup_link_event,
	.get_nic_info			= qlcnic_83xx_get_nic_info,
	.get_pci_info			= qlcnic_83xx_get_pci_info,
	.set_nic_info			= qlcnic_83xx_set_nic_info,
	.change_macvlan			= qlcnic_83xx_sre_macaddr_change,
	.napi_enable			= qlcnic_83xx_napi_enable,
	.napi_disable			= qlcnic_83xx_napi_disable,
	.config_पूर्णांकr_coal		= qlcnic_83xx_config_पूर्णांकr_coal,
	.config_rss			= qlcnic_83xx_config_rss,
	.config_hw_lro			= qlcnic_83xx_config_hw_lro,
	.config_promisc_mode		= qlcnic_83xx_nic_set_promisc,
	.change_l2_filter		= qlcnic_83xx_change_l2_filter,
	.get_board_info			= qlcnic_83xx_get_port_info,
	.set_mac_filter_count		= qlcnic_83xx_set_mac_filter_count,
	.मुक्त_mac_list			= qlcnic_82xx_मुक्त_mac_list,
	.io_error_detected		= qlcnic_83xx_io_error_detected,
	.io_slot_reset			= qlcnic_83xx_io_slot_reset,
	.io_resume			= qlcnic_83xx_io_resume,
	.get_beacon_state		= qlcnic_83xx_get_beacon_state,
	.enable_sds_पूर्णांकr		= qlcnic_83xx_enable_sds_पूर्णांकr,
	.disable_sds_पूर्णांकr		= qlcnic_83xx_disable_sds_पूर्णांकr,
	.enable_tx_पूर्णांकr			= qlcnic_83xx_enable_tx_पूर्णांकr,
	.disable_tx_पूर्णांकr		= qlcnic_83xx_disable_tx_पूर्णांकr,
	.get_saved_state		= qlcnic_83xx_get_saved_state,
	.set_saved_state		= qlcnic_83xx_set_saved_state,
	.cache_पंचांगpl_hdr_values		= qlcnic_83xx_cache_पंचांगpl_hdr_values,
	.get_cap_size			= qlcnic_83xx_get_cap_size,
	.set_sys_info			= qlcnic_83xx_set_sys_info,
	.store_cap_mask			= qlcnic_83xx_store_cap_mask,
	.encap_rx_offload		= qlcnic_83xx_encap_rx_offload,
	.encap_tx_offload		= qlcnic_83xx_encap_tx_offload,
पूर्ण;

अटल काष्ठा qlcnic_nic_ढाँचा qlcnic_83xx_ops = अणु
	.config_bridged_mode	= qlcnic_config_bridged_mode,
	.config_led		= qlcnic_config_led,
	.request_reset          = qlcnic_83xx_idc_request_reset,
	.cancel_idc_work        = qlcnic_83xx_idc_निकास,
	.napi_add		= qlcnic_83xx_napi_add,
	.napi_del		= qlcnic_83xx_napi_del,
	.config_ipaddr		= qlcnic_83xx_config_ipaddr,
	.clear_legacy_पूर्णांकr	= qlcnic_83xx_clear_legacy_पूर्णांकr,
	.shutकरोwn		= qlcnic_83xx_shutकरोwn,
	.resume			= qlcnic_83xx_resume,
पूर्ण;

व्योम qlcnic_83xx_रेजिस्टर_map(काष्ठा qlcnic_hardware_context *ahw)
अणु
	ahw->hw_ops		= &qlcnic_83xx_hw_ops;
	ahw->reg_tbl		= (u32 *)qlcnic_83xx_reg_tbl;
	ahw->ext_reg_tbl	= (u32 *)qlcnic_83xx_ext_reg_tbl;
पूर्ण

पूर्णांक qlcnic_83xx_get_fw_version(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 fw_major, fw_minor, fw_build;
	काष्ठा pci_dev *pdev = adapter->pdev;

	fw_major = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_MAJOR);
	fw_minor = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_MINOR);
	fw_build = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_SUB);
	adapter->fw_version = QLCNIC_VERSION_CODE(fw_major, fw_minor, fw_build);

	dev_info(&pdev->dev, "Driver v%s, firmware version %d.%d.%d\n",
		 QLCNIC_LINUX_VERSIONID, fw_major, fw_minor, fw_build);

	वापस adapter->fw_version;
पूर्ण

अटल पूर्णांक __qlcnic_set_win_base(काष्ठा qlcnic_adapter *adapter, u32 addr)
अणु
	व्योम __iomem *base;
	u32 val;

	base = adapter->ahw->pci_base0 +
	       QLC_83XX_CRB_WIN_FUNC(adapter->ahw->pci_func);
	ग_लिखोl(addr, base);
	val = पढ़ोl(base);
	अगर (val != addr)
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक qlcnic_83xx_rd_reg_indirect(काष्ठा qlcnic_adapter *adapter, uदीर्घ addr,
				पूर्णांक *err)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	*err = __qlcnic_set_win_base(adapter, (u32) addr);
	अगर (!*err) अणु
		वापस QLCRDX(ahw, QLCNIC_WILDCARD);
	पूर्ण अन्यथा अणु
		dev_err(&adapter->pdev->dev,
			"%s failed, addr = 0x%lx\n", __func__, addr);
		वापस -EIO;
	पूर्ण
पूर्ण

पूर्णांक qlcnic_83xx_wrt_reg_indirect(काष्ठा qlcnic_adapter *adapter, uदीर्घ addr,
				 u32 data)
अणु
	पूर्णांक err;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	err = __qlcnic_set_win_base(adapter, (u32) addr);
	अगर (!err) अणु
		QLCWRX(ahw, QLCNIC_WILDCARD, data);
		वापस 0;
	पूर्ण अन्यथा अणु
		dev_err(&adapter->pdev->dev,
			"%s failed, addr = 0x%x data = 0x%x\n",
			__func__, (पूर्णांक)addr, data);
		वापस err;
	पूर्ण
पूर्ण

अटल व्योम qlcnic_83xx_enable_legacy(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	/* MSI-X enablement failed, use legacy पूर्णांकerrupt */
	adapter->tgt_status_reg = ahw->pci_base0 + QLC_83XX_INTX_PTR;
	adapter->tgt_mask_reg = ahw->pci_base0 + QLC_83XX_INTX_MASK;
	adapter->isr_पूर्णांक_vec = ahw->pci_base0 + QLC_83XX_INTX_TRGR;
	adapter->msix_entries[0].vector = adapter->pdev->irq;
	dev_info(&adapter->pdev->dev, "using legacy interrupt\n");
पूर्ण

अटल पूर्णांक qlcnic_83xx_calculate_msix_vector(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक num_msix;

	num_msix = adapter->drv_sds_rings;

	/* account क्रम AEN पूर्णांकerrupt MSI-X based पूर्णांकerrupts */
	num_msix += 1;

	अगर (!(adapter->flags & QLCNIC_TX_INTR_SHARED))
		num_msix += adapter->drv_tx_rings;

	वापस num_msix;
पूर्ण

पूर्णांक qlcnic_83xx_setup_पूर्णांकr(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक err, i, num_msix;

	अगर (adapter->flags & QLCNIC_TSS_RSS) अणु
		err = qlcnic_setup_tss_rss_पूर्णांकr(adapter);
		अगर (err < 0)
			वापस err;
		num_msix = ahw->num_msix;
	पूर्ण अन्यथा अणु
		num_msix = qlcnic_83xx_calculate_msix_vector(adapter);

		err = qlcnic_enable_msix(adapter, num_msix);
		अगर (err == -ENOMEM)
			वापस err;

		अगर (adapter->flags & QLCNIC_MSIX_ENABLED) अणु
			num_msix = ahw->num_msix;
		पूर्ण अन्यथा अणु
			अगर (qlcnic_sriov_vf_check(adapter))
				वापस -EINVAL;
			num_msix = 1;
			adapter->drv_sds_rings = QLCNIC_SINGLE_RING;
			adapter->drv_tx_rings = QLCNIC_SINGLE_RING;
		पूर्ण
	पूर्ण

	/* setup पूर्णांकerrupt mapping table क्रम fw */
	ahw->पूर्णांकr_tbl =
		vzalloc(array_size(num_msix,
				   माप(काष्ठा qlcnic_पूर्णांकrpt_config)));
	अगर (!ahw->पूर्णांकr_tbl)
		वापस -ENOMEM;

	अगर (!(adapter->flags & QLCNIC_MSIX_ENABLED)) अणु
		अगर (adapter->ahw->pci_func >= QLC_MAX_LEGACY_FUNC_SUPP) अणु
			dev_err(&adapter->pdev->dev, "PCI function number 8 and higher are not supported with legacy interrupt, func 0x%x\n",
				ahw->pci_func);
			वापस -EOPNOTSUPP;
		पूर्ण

		qlcnic_83xx_enable_legacy(adapter);
	पूर्ण

	क्रम (i = 0; i < num_msix; i++) अणु
		अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
			ahw->पूर्णांकr_tbl[i].type = QLCNIC_INTRPT_MSIX;
		अन्यथा
			ahw->पूर्णांकr_tbl[i].type = QLCNIC_INTRPT_INTX;
		ahw->पूर्णांकr_tbl[i].id = i;
		ahw->पूर्णांकr_tbl[i].src = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qlcnic_83xx_clear_legacy_पूर्णांकr_mask(काष्ठा qlcnic_adapter *adapter)
अणु
	ग_लिखोl(0, adapter->tgt_mask_reg);
पूर्ण

अटल अंतरभूत व्योम qlcnic_83xx_set_legacy_पूर्णांकr_mask(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (adapter->tgt_mask_reg)
		ग_लिखोl(1, adapter->tgt_mask_reg);
पूर्ण

अटल अंतरभूत व्योम qlcnic_83xx_enable_legacy_msix_mbx_पूर्णांकr(काष्ठा qlcnic_adapter
						    *adapter)
अणु
	u32 mask;

	/* Mailbox in MSI-x mode and Legacy Interrupt share the same
	 * source रेजिस्टर. We could be here beक्रमe contexts are created
	 * and sds_ring->crb_पूर्णांकr_mask has not been initialized, calculate
	 * BAR offset क्रम Interrupt Source Register
	 */
	mask = QLCRDX(adapter->ahw, QLCNIC_DEF_INT_MASK);
	ग_लिखोl(0, adapter->ahw->pci_base0 + mask);
पूर्ण

व्योम qlcnic_83xx_disable_mbx_पूर्णांकr(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 mask;

	mask = QLCRDX(adapter->ahw, QLCNIC_DEF_INT_MASK);
	ग_लिखोl(1, adapter->ahw->pci_base0 + mask);
	QLCWRX(adapter->ahw, QLCNIC_MBX_INTR_ENBL, 0);
पूर्ण

अटल अंतरभूत व्योम qlcnic_83xx_get_mbx_data(काष्ठा qlcnic_adapter *adapter,
				     काष्ठा qlcnic_cmd_args *cmd)
अणु
	पूर्णांक i;

	अगर (cmd->op_type == QLC_83XX_MBX_POST_BC_OP)
		वापस;

	क्रम (i = 0; i < cmd->rsp.num; i++)
		cmd->rsp.arg[i] = पढ़ोl(QLCNIC_MBX_FW(adapter->ahw, i));
पूर्ण

irqवापस_t qlcnic_83xx_clear_legacy_पूर्णांकr(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 पूर्णांकr_val;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक retries = 0;

	पूर्णांकr_val = पढ़ोl(adapter->tgt_status_reg);

	अगर (!QLC_83XX_VALID_INTX_BIT31(पूर्णांकr_val))
		वापस IRQ_NONE;

	अगर (QLC_83XX_INTX_FUNC(पूर्णांकr_val) != adapter->ahw->pci_func) अणु
		adapter->stats.spurious_पूर्णांकr++;
		वापस IRQ_NONE;
	पूर्ण
	/* The barrier is required to ensure ग_लिखोs to the रेजिस्टरs */
	wmb();

	/* clear the पूर्णांकerrupt trigger control रेजिस्टर */
	ग_लिखोl_relaxed(0, adapter->isr_पूर्णांक_vec);
	पूर्णांकr_val = पढ़ोl(adapter->isr_पूर्णांक_vec);
	करो अणु
		पूर्णांकr_val = पढ़ोl(adapter->tgt_status_reg);
		अगर (QLC_83XX_INTX_FUNC(पूर्णांकr_val) != ahw->pci_func)
			अवरोध;
		retries++;
	पूर्ण जबतक (QLC_83XX_VALID_INTX_BIT30(पूर्णांकr_val) &&
		 (retries < QLC_83XX_LEGACY_INTX_MAX_RETRY));

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत व्योम qlcnic_83xx_notअगरy_mbx_response(काष्ठा qlcnic_mailbox *mbx)
अणु
	mbx->rsp_status = QLC_83XX_MBX_RESPONSE_ARRIVED;
	complete(&mbx->completion);
पूर्ण

अटल व्योम qlcnic_83xx_poll_process_aen(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 resp, event, rsp_status = QLC_83XX_MBX_RESPONSE_ARRIVED;
	काष्ठा qlcnic_mailbox *mbx = adapter->ahw->mailbox;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mbx->aen_lock, flags);
	resp = QLCRDX(adapter->ahw, QLCNIC_FW_MBX_CTRL);
	अगर (!(resp & QLCNIC_SET_OWNER))
		जाओ out;

	event = पढ़ोl(QLCNIC_MBX_FW(adapter->ahw, 0));
	अगर (event &  QLCNIC_MBX_ASYNC_EVENT) अणु
		__qlcnic_83xx_process_aen(adapter);
	पूर्ण अन्यथा अणु
		अगर (mbx->rsp_status != rsp_status)
			qlcnic_83xx_notअगरy_mbx_response(mbx);
	पूर्ण
out:
	qlcnic_83xx_enable_legacy_msix_mbx_पूर्णांकr(adapter);
	spin_unlock_irqrestore(&mbx->aen_lock, flags);
पूर्ण

irqवापस_t qlcnic_83xx_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qlcnic_adapter *adapter = data;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	अगर (qlcnic_83xx_clear_legacy_पूर्णांकr(adapter) == IRQ_NONE)
		वापस IRQ_NONE;

	qlcnic_83xx_poll_process_aen(adapter);

	अगर (ahw->diag_test) अणु
		अगर (ahw->diag_test == QLCNIC_INTERRUPT_TEST)
			ahw->diag_cnt++;
		qlcnic_83xx_enable_legacy_msix_mbx_पूर्णांकr(adapter);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (!test_bit(__QLCNIC_DEV_UP, &adapter->state)) अणु
		qlcnic_83xx_enable_legacy_msix_mbx_पूर्णांकr(adapter);
	पूर्ण अन्यथा अणु
		sds_ring = &adapter->recv_ctx->sds_rings[0];
		napi_schedule(&sds_ring->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t qlcnic_83xx_पंचांगp_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qlcnic_host_sds_ring *sds_ring = data;
	काष्ठा qlcnic_adapter *adapter = sds_ring->adapter;

	अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
		जाओ करोne;

	अगर (adapter->nic_ops->clear_legacy_पूर्णांकr(adapter) == IRQ_NONE)
		वापस IRQ_NONE;

करोne:
	adapter->ahw->diag_cnt++;
	qlcnic_enable_sds_पूर्णांकr(adapter, sds_ring);

	वापस IRQ_HANDLED;
पूर्ण

व्योम qlcnic_83xx_मुक्त_mbx_पूर्णांकr(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 num_msix;

	अगर (!(adapter->flags & QLCNIC_MSIX_ENABLED))
		qlcnic_83xx_set_legacy_पूर्णांकr_mask(adapter);

	qlcnic_83xx_disable_mbx_पूर्णांकr(adapter);

	अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
		num_msix = adapter->ahw->num_msix - 1;
	अन्यथा
		num_msix = 0;

	msleep(20);

	अगर (adapter->msix_entries) अणु
		synchronize_irq(adapter->msix_entries[num_msix].vector);
		मुक्त_irq(adapter->msix_entries[num_msix].vector, adapter);
	पूर्ण
पूर्ण

पूर्णांक qlcnic_83xx_setup_mbx_पूर्णांकr(काष्ठा qlcnic_adapter *adapter)
अणु
	irq_handler_t handler;
	u32 val;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags = 0;

	अगर (!(adapter->flags & QLCNIC_MSI_ENABLED) &&
	    !(adapter->flags & QLCNIC_MSIX_ENABLED))
		flags |= IRQF_SHARED;

	अगर (adapter->flags & QLCNIC_MSIX_ENABLED) अणु
		handler = qlcnic_83xx_handle_aen;
		val = adapter->msix_entries[adapter->ahw->num_msix - 1].vector;
		err = request_irq(val, handler, flags, "qlcnic-MB", adapter);
		अगर (err) अणु
			dev_err(&adapter->pdev->dev,
				"failed to register MBX interrupt\n");
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		handler = qlcnic_83xx_पूर्णांकr;
		val = adapter->msix_entries[0].vector;
		err = request_irq(val, handler, flags, "qlcnic", adapter);
		अगर (err) अणु
			dev_err(&adapter->pdev->dev,
				"failed to register INTx interrupt\n");
			वापस err;
		पूर्ण
		qlcnic_83xx_clear_legacy_पूर्णांकr_mask(adapter);
	पूर्ण

	/* Enable mailbox पूर्णांकerrupt */
	qlcnic_83xx_enable_mbx_पूर्णांकerrupt(adapter);

	वापस err;
पूर्ण

व्योम qlcnic_83xx_get_func_no(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 val = QLCRDX(adapter->ahw, QLCNIC_INFORMANT);
	adapter->ahw->pci_func = (val >> 24) & 0xff;
पूर्ण

पूर्णांक qlcnic_83xx_cam_lock(काष्ठा qlcnic_adapter *adapter)
अणु
	व्योम __iomem *addr;
	u32 val, limit = 0;

	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	addr = ahw->pci_base0 + QLC_83XX_SEM_LOCK_FUNC(ahw->pci_func);
	करो अणु
		val = पढ़ोl(addr);
		अगर (val) अणु
			/* ग_लिखो the function number to रेजिस्टर */
			QLC_SHARED_REG_WR32(adapter, QLCNIC_FLASH_LOCK_OWNER,
					    ahw->pci_func);
			वापस 0;
		पूर्ण
		usleep_range(1000, 2000);
	पूर्ण जबतक (++limit <= QLCNIC_PCIE_SEM_TIMEOUT);

	वापस -EIO;
पूर्ण

व्योम qlcnic_83xx_cam_unlock(काष्ठा qlcnic_adapter *adapter)
अणु
	व्योम __iomem *addr;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	addr = ahw->pci_base0 + QLC_83XX_SEM_UNLOCK_FUNC(ahw->pci_func);
	पढ़ोl(addr);
पूर्ण

व्योम qlcnic_83xx_पढ़ो_crb(काष्ठा qlcnic_adapter *adapter, अक्षर *buf,
			  loff_t offset, माप_प्रकार size)
अणु
	पूर्णांक ret = 0;
	u32 data;

	अगर (qlcnic_api_lock(adapter)) अणु
		dev_err(&adapter->pdev->dev,
			"%s: failed to acquire lock. addr offset 0x%x\n",
			__func__, (u32)offset);
		वापस;
	पूर्ण

	data = QLCRD32(adapter, (u32) offset, &ret);
	qlcnic_api_unlock(adapter);

	अगर (ret == -EIO) अणु
		dev_err(&adapter->pdev->dev,
			"%s: failed. addr offset 0x%x\n",
			__func__, (u32)offset);
		वापस;
	पूर्ण
	स_नकल(buf, &data, size);
पूर्ण

व्योम qlcnic_83xx_ग_लिखो_crb(काष्ठा qlcnic_adapter *adapter, अक्षर *buf,
			   loff_t offset, माप_प्रकार size)
अणु
	u32 data;

	स_नकल(&data, buf, size);
	qlcnic_83xx_wrt_reg_indirect(adapter, (u32) offset, data);
पूर्ण

पूर्णांक qlcnic_83xx_get_port_info(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक status;

	status = qlcnic_83xx_get_port_config(adapter);
	अगर (status) अणु
		dev_err(&adapter->pdev->dev,
			"Get Port Info failed\n");
	पूर्ण अन्यथा अणु

		अगर (ahw->port_config & QLC_83XX_10G_CAPABLE) अणु
			ahw->port_type = QLCNIC_XGBE;
		पूर्ण अन्यथा अगर (ahw->port_config & QLC_83XX_10_CAPABLE ||
			   ahw->port_config & QLC_83XX_100_CAPABLE ||
			   ahw->port_config & QLC_83XX_1G_CAPABLE) अणु
			ahw->port_type = QLCNIC_GBE;
		पूर्ण अन्यथा अणु
			ahw->port_type = QLCNIC_XGBE;
		पूर्ण

		अगर (QLC_83XX_AUTONEG(ahw->port_config))
			ahw->link_स्वतःneg = AUTONEG_ENABLE;

	पूर्ण
	वापस status;
पूर्ण

अटल व्योम qlcnic_83xx_set_mac_filter_count(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u16 act_pci_fn = ahw->total_nic_func;
	u16 count;

	ahw->max_mc_count = QLC_83XX_MAX_MC_COUNT;
	अगर (act_pci_fn <= 2)
		count = (QLC_83XX_MAX_UC_COUNT - QLC_83XX_MAX_MC_COUNT) /
			 act_pci_fn;
	अन्यथा
		count = (QLC_83XX_LB_MAX_FILTERS - QLC_83XX_MAX_MC_COUNT) /
			 act_pci_fn;
	ahw->max_uc_count = count;
पूर्ण

व्योम qlcnic_83xx_enable_mbx_पूर्णांकerrupt(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 val;

	अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
		val = BIT_2 | ((adapter->ahw->num_msix - 1) << 8);
	अन्यथा
		val = BIT_2;

	QLCWRX(adapter->ahw, QLCNIC_MBX_INTR_ENBL, val);
	qlcnic_83xx_enable_legacy_msix_mbx_पूर्णांकr(adapter);
पूर्ण

व्योम qlcnic_83xx_check_vf(काष्ठा qlcnic_adapter *adapter,
			  स्थिर काष्ठा pci_device_id *ent)
अणु
	u32 op_mode, priv_level;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	ahw->fw_hal_version = 2;
	qlcnic_get_func_no(adapter);

	अगर (qlcnic_sriov_vf_check(adapter)) अणु
		qlcnic_sriov_vf_set_ops(adapter);
		वापस;
	पूर्ण

	/* Determine function privilege level */
	op_mode = QLCRDX(adapter->ahw, QLC_83XX_DRV_OP_MODE);
	अगर (op_mode == QLC_83XX_DEFAULT_OPMODE)
		priv_level = QLCNIC_MGMT_FUNC;
	अन्यथा
		priv_level = QLC_83XX_GET_FUNC_PRIVILEGE(op_mode,
							 ahw->pci_func);

	अगर (priv_level == QLCNIC_NON_PRIV_FUNC) अणु
		ahw->op_mode = QLCNIC_NON_PRIV_FUNC;
		dev_info(&adapter->pdev->dev,
			 "HAL Version: %d Non Privileged function\n",
			 ahw->fw_hal_version);
		adapter->nic_ops = &qlcnic_vf_ops;
	पूर्ण अन्यथा अणु
		अगर (pci_find_ext_capability(adapter->pdev,
					    PCI_EXT_CAP_ID_SRIOV))
			set_bit(__QLCNIC_SRIOV_CAPABLE, &adapter->state);
		adapter->nic_ops = &qlcnic_83xx_ops;
	पूर्ण
पूर्ण

अटल व्योम qlcnic_83xx_handle_link_aen(काष्ठा qlcnic_adapter *adapter,
					u32 data[]);
अटल व्योम qlcnic_83xx_handle_idc_comp_aen(काष्ठा qlcnic_adapter *adapter,
					    u32 data[]);

व्योम qlcnic_dump_mbx(काष्ठा qlcnic_adapter *adapter,
		     काष्ठा qlcnic_cmd_args *cmd)
अणु
	पूर्णांक i;

	अगर (cmd->op_type == QLC_83XX_MBX_POST_BC_OP)
		वापस;

	dev_info(&adapter->pdev->dev,
		 "Host MBX regs(%d)\n", cmd->req.num);
	क्रम (i = 0; i < cmd->req.num; i++) अणु
		अगर (i && !(i % 8))
			pr_info("\n");
		pr_info("%08x ", cmd->req.arg[i]);
	पूर्ण
	pr_info("\n");
	dev_info(&adapter->pdev->dev,
		 "FW MBX regs(%d)\n", cmd->rsp.num);
	क्रम (i = 0; i < cmd->rsp.num; i++) अणु
		अगर (i && !(i % 8))
			pr_info("\n");
		pr_info("%08x ", cmd->rsp.arg[i]);
	पूर्ण
	pr_info("\n");
पूर्ण

अटल व्योम qlcnic_83xx_poll_क्रम_mbx_completion(काष्ठा qlcnic_adapter *adapter,
						काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक opcode = LSW(cmd->req.arg[0]);
	अचिन्हित दीर्घ max_loops;

	max_loops = cmd->total_cmds * QLC_83XX_MBX_CMD_LOOP;

	क्रम (; max_loops; max_loops--) अणु
		अगर (atomic_पढ़ो(&cmd->rsp_status) ==
		    QLC_83XX_MBX_RESPONSE_ARRIVED)
			वापस;

		udelay(1);
	पूर्ण

	dev_err(&adapter->pdev->dev,
		"%s: Mailbox command timed out, cmd_op=0x%x, cmd_type=0x%x, pci_func=0x%x, op_mode=0x%x\n",
		__func__, opcode, cmd->type, ahw->pci_func, ahw->op_mode);
	flush_workqueue(ahw->mailbox->work_q);
	वापस;
पूर्ण

पूर्णांक qlcnic_83xx_issue_cmd(काष्ठा qlcnic_adapter *adapter,
			  काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_mailbox *mbx = adapter->ahw->mailbox;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक cmd_type, err, opcode;
	अचिन्हित दीर्घ समयout;

	अगर (!mbx)
		वापस -EIO;

	opcode = LSW(cmd->req.arg[0]);
	cmd_type = cmd->type;
	err = mbx->ops->enqueue_cmd(adapter, cmd, &समयout);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"%s: Mailbox not available, cmd_op=0x%x, cmd_context=0x%x, pci_func=0x%x, op_mode=0x%x\n",
			__func__, opcode, cmd->type, ahw->pci_func,
			ahw->op_mode);
		वापस err;
	पूर्ण

	चयन (cmd_type) अणु
	हाल QLC_83XX_MBX_CMD_WAIT:
		अगर (!रुको_क्रम_completion_समयout(&cmd->completion, समयout)) अणु
			dev_err(&adapter->pdev->dev,
				"%s: Mailbox command timed out, cmd_op=0x%x, cmd_type=0x%x, pci_func=0x%x, op_mode=0x%x\n",
				__func__, opcode, cmd_type, ahw->pci_func,
				ahw->op_mode);
			flush_workqueue(mbx->work_q);
		पूर्ण
		अवरोध;
	हाल QLC_83XX_MBX_CMD_NO_WAIT:
		वापस 0;
	हाल QLC_83XX_MBX_CMD_BUSY_WAIT:
		qlcnic_83xx_poll_क्रम_mbx_completion(adapter, cmd);
		अवरोध;
	शेष:
		dev_err(&adapter->pdev->dev,
			"%s: Invalid mailbox command, cmd_op=0x%x, cmd_type=0x%x, pci_func=0x%x, op_mode=0x%x\n",
			__func__, opcode, cmd_type, ahw->pci_func,
			ahw->op_mode);
		qlcnic_83xx_detach_mailbox_work(adapter);
	पूर्ण

	वापस cmd->rsp_opcode;
पूर्ण

पूर्णांक qlcnic_83xx_alloc_mbx_args(काष्ठा qlcnic_cmd_args *mbx,
			       काष्ठा qlcnic_adapter *adapter, u32 type)
अणु
	पूर्णांक i, size;
	u32 temp;
	स्थिर काष्ठा qlcnic_mailbox_metadata *mbx_tbl;

	स_रखो(mbx, 0, माप(काष्ठा qlcnic_cmd_args));
	mbx_tbl = qlcnic_83xx_mbx_tbl;
	size = ARRAY_SIZE(qlcnic_83xx_mbx_tbl);
	क्रम (i = 0; i < size; i++) अणु
		अगर (type == mbx_tbl[i].cmd) अणु
			mbx->op_type = QLC_83XX_FW_MBX_CMD;
			mbx->req.num = mbx_tbl[i].in_args;
			mbx->rsp.num = mbx_tbl[i].out_args;
			mbx->req.arg = kसुस्मृति(mbx->req.num, माप(u32),
					       GFP_ATOMIC);
			अगर (!mbx->req.arg)
				वापस -ENOMEM;
			mbx->rsp.arg = kसुस्मृति(mbx->rsp.num, माप(u32),
					       GFP_ATOMIC);
			अगर (!mbx->rsp.arg) अणु
				kमुक्त(mbx->req.arg);
				mbx->req.arg = शून्य;
				वापस -ENOMEM;
			पूर्ण
			temp = adapter->ahw->fw_hal_version << 29;
			mbx->req.arg[0] = (type | (mbx->req.num << 16) | temp);
			mbx->cmd_op = type;
			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(&adapter->pdev->dev, "%s: Invalid mailbox command opcode 0x%x\n",
		__func__, type);
	वापस -EINVAL;
पूर्ण

व्योम qlcnic_83xx_idc_aen_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlcnic_adapter *adapter;
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक i, err = 0;

	adapter = container_of(work, काष्ठा qlcnic_adapter, idc_aen_work.work);
	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_IDC_ACK);
	अगर (err)
		वापस;

	क्रम (i = 1; i < QLC_83XX_MBX_AEN_CNT; i++)
		cmd.req.arg[i] = adapter->ahw->mbox_aen[i];

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err)
		dev_info(&adapter->pdev->dev,
			 "%s: Mailbox IDC ACK failed.\n", __func__);
	qlcnic_मुक्त_mbx_args(&cmd);
पूर्ण

अटल व्योम qlcnic_83xx_handle_idc_comp_aen(काष्ठा qlcnic_adapter *adapter,
					    u32 data[])
अणु
	dev_dbg(&adapter->pdev->dev, "Completion AEN:0x%x.\n",
		QLCNIC_MBX_RSP(data[0]));
	clear_bit(QLC_83XX_IDC_COMP_AEN, &adapter->ahw->idc.status);
	वापस;
पूर्ण

अटल व्योम __qlcnic_83xx_process_aen(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u32 event[QLC_83XX_MBX_AEN_CNT];
	पूर्णांक i;

	क्रम (i = 0; i < QLC_83XX_MBX_AEN_CNT; i++)
		event[i] = पढ़ोl(QLCNIC_MBX_FW(ahw, i));

	चयन (QLCNIC_MBX_RSP(event[0])) अणु

	हाल QLCNIC_MBX_LINK_EVENT:
		qlcnic_83xx_handle_link_aen(adapter, event);
		अवरोध;
	हाल QLCNIC_MBX_COMP_EVENT:
		qlcnic_83xx_handle_idc_comp_aen(adapter, event);
		अवरोध;
	हाल QLCNIC_MBX_REQUEST_EVENT:
		क्रम (i = 0; i < QLC_83XX_MBX_AEN_CNT; i++)
			adapter->ahw->mbox_aen[i] = QLCNIC_MBX_RSP(event[i]);
		queue_delayed_work(adapter->qlcnic_wq,
				   &adapter->idc_aen_work, 0);
		अवरोध;
	हाल QLCNIC_MBX_TIME_EXTEND_EVENT:
		ahw->extend_lb_समय = event[1] >> 8 & 0xf;
		अवरोध;
	हाल QLCNIC_MBX_BC_EVENT:
		qlcnic_sriov_handle_bc_event(adapter, event[1]);
		अवरोध;
	हाल QLCNIC_MBX_SFP_INSERT_EVENT:
		dev_info(&adapter->pdev->dev, "SFP+ Insert AEN:0x%x.\n",
			 QLCNIC_MBX_RSP(event[0]));
		अवरोध;
	हाल QLCNIC_MBX_SFP_REMOVE_EVENT:
		dev_info(&adapter->pdev->dev, "SFP Removed AEN:0x%x.\n",
			 QLCNIC_MBX_RSP(event[0]));
		अवरोध;
	हाल QLCNIC_MBX_DCBX_CONFIG_CHANGE_EVENT:
		qlcnic_dcb_aen_handler(adapter->dcb, (व्योम *)&event[1]);
		अवरोध;
	शेष:
		dev_dbg(&adapter->pdev->dev, "Unsupported AEN:0x%x.\n",
			QLCNIC_MBX_RSP(event[0]));
		अवरोध;
	पूर्ण

	QLCWRX(ahw, QLCNIC_FW_MBX_CTRL, QLCNIC_CLR_OWNER);
पूर्ण

अटल व्योम qlcnic_83xx_process_aen(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 resp, event, rsp_status = QLC_83XX_MBX_RESPONSE_ARRIVED;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_mailbox *mbx = ahw->mailbox;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mbx->aen_lock, flags);
	resp = QLCRDX(ahw, QLCNIC_FW_MBX_CTRL);
	अगर (resp & QLCNIC_SET_OWNER) अणु
		event = पढ़ोl(QLCNIC_MBX_FW(ahw, 0));
		अगर (event &  QLCNIC_MBX_ASYNC_EVENT) अणु
			__qlcnic_83xx_process_aen(adapter);
		पूर्ण अन्यथा अणु
			अगर (mbx->rsp_status != rsp_status)
				qlcnic_83xx_notअगरy_mbx_response(mbx);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&mbx->aen_lock, flags);
पूर्ण

अटल व्योम qlcnic_83xx_mbx_poll_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlcnic_adapter *adapter;

	adapter = container_of(work, काष्ठा qlcnic_adapter, mbx_poll_work.work);

	अगर (!test_bit(__QLCNIC_MBX_POLL_ENABLE, &adapter->state))
		वापस;

	qlcnic_83xx_process_aen(adapter);
	queue_delayed_work(adapter->qlcnic_wq, &adapter->mbx_poll_work,
			   (HZ / 10));
पूर्ण

व्योम qlcnic_83xx_enable_mbx_poll(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (test_and_set_bit(__QLCNIC_MBX_POLL_ENABLE, &adapter->state))
		वापस;

	INIT_DELAYED_WORK(&adapter->mbx_poll_work, qlcnic_83xx_mbx_poll_work);
	queue_delayed_work(adapter->qlcnic_wq, &adapter->mbx_poll_work, 0);
पूर्ण

व्योम qlcnic_83xx_disable_mbx_poll(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (!test_and_clear_bit(__QLCNIC_MBX_POLL_ENABLE, &adapter->state))
		वापस;
	cancel_delayed_work_sync(&adapter->mbx_poll_work);
पूर्ण

अटल पूर्णांक qlcnic_83xx_add_rings(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक index, i, err, sds_mbx_size;
	u32 *buf, पूर्णांकrpt_id, पूर्णांकr_mask;
	u16 context_id;
	u8 num_sds;
	काष्ठा qlcnic_cmd_args cmd;
	काष्ठा qlcnic_host_sds_ring *sds;
	काष्ठा qlcnic_sds_mbx sds_mbx;
	काष्ठा qlcnic_add_rings_mbx_out *mbx_out;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	sds_mbx_size = माप(काष्ठा qlcnic_sds_mbx);
	context_id = recv_ctx->context_id;
	num_sds = adapter->drv_sds_rings - QLCNIC_MAX_SDS_RINGS;
	ahw->hw_ops->alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_ADD_RCV_RINGS);
	cmd.req.arg[1] = 0 | (num_sds << 8) | (context_id << 16);

	/* set up status rings, mbx 2-81 */
	index = 2;
	क्रम (i = 8; i < adapter->drv_sds_rings; i++) अणु
		स_रखो(&sds_mbx, 0, sds_mbx_size);
		sds = &recv_ctx->sds_rings[i];
		sds->consumer = 0;
		स_रखो(sds->desc_head, 0, STATUS_DESC_RINGSIZE(sds));
		sds_mbx.phy_addr_low = LSD(sds->phys_addr);
		sds_mbx.phy_addr_high = MSD(sds->phys_addr);
		sds_mbx.sds_ring_size = sds->num_desc;

		अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
			पूर्णांकrpt_id = ahw->पूर्णांकr_tbl[i].id;
		अन्यथा
			पूर्णांकrpt_id = QLCRDX(ahw, QLCNIC_DEF_INT_ID);

		अगर (adapter->ahw->diag_test != QLCNIC_LOOPBACK_TEST)
			sds_mbx.पूर्णांकrpt_id = पूर्णांकrpt_id;
		अन्यथा
			sds_mbx.पूर्णांकrpt_id = 0xffff;
		sds_mbx.पूर्णांकrpt_val = 0;
		buf = &cmd.req.arg[index];
		स_नकल(buf, &sds_mbx, sds_mbx_size);
		index += sds_mbx_size / माप(u32);
	पूर्ण

	/* send the mailbox command */
	err = ahw->hw_ops->mbx_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to add rings %d\n", err);
		जाओ out;
	पूर्ण

	mbx_out = (काष्ठा qlcnic_add_rings_mbx_out *)&cmd.rsp.arg[1];
	index = 0;
	/* status descriptor ring */
	क्रम (i = 8; i < adapter->drv_sds_rings; i++) अणु
		sds = &recv_ctx->sds_rings[i];
		sds->crb_sts_consumer = ahw->pci_base0 +
					mbx_out->host_csmr[index];
		अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
			पूर्णांकr_mask = ahw->पूर्णांकr_tbl[i].src;
		अन्यथा
			पूर्णांकr_mask = QLCRDX(ahw, QLCNIC_DEF_INT_MASK);

		sds->crb_पूर्णांकr_mask = ahw->pci_base0 + पूर्णांकr_mask;
		index++;
	पूर्ण
out:
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

व्योम qlcnic_83xx_del_rx_ctx(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err;
	u32 temp = 0;
	काष्ठा qlcnic_cmd_args cmd;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;

	अगर (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_DESTROY_RX_CTX))
		वापस;

	अगर (qlcnic_sriov_pf_check(adapter) || qlcnic_sriov_vf_check(adapter))
		cmd.req.arg[0] |= (0x3 << 29);

	अगर (qlcnic_sriov_pf_check(adapter))
		qlcnic_pf_set_पूर्णांकerface_id_del_rx_ctx(adapter, &temp);

	cmd.req.arg[1] = recv_ctx->context_id | temp;
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err)
		dev_err(&adapter->pdev->dev,
			"Failed to destroy rx ctx in firmware\n");

	recv_ctx->state = QLCNIC_HOST_CTX_STATE_FREED;
	qlcnic_मुक्त_mbx_args(&cmd);
पूर्ण

पूर्णांक qlcnic_83xx_create_rx_ctx(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक i, err, index, sds_mbx_size, rds_mbx_size;
	u8 num_sds, num_rds;
	u32 *buf, पूर्णांकrpt_id, पूर्णांकr_mask, cap = 0;
	काष्ठा qlcnic_host_sds_ring *sds;
	काष्ठा qlcnic_host_rds_ring *rds;
	काष्ठा qlcnic_sds_mbx sds_mbx;
	काष्ठा qlcnic_rds_mbx rds_mbx;
	काष्ठा qlcnic_cmd_args cmd;
	काष्ठा qlcnic_rcv_mbx_out *mbx_out;
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	num_rds = adapter->max_rds_rings;

	अगर (adapter->drv_sds_rings <= QLCNIC_MAX_SDS_RINGS)
		num_sds = adapter->drv_sds_rings;
	अन्यथा
		num_sds = QLCNIC_MAX_SDS_RINGS;

	sds_mbx_size = माप(काष्ठा qlcnic_sds_mbx);
	rds_mbx_size = माप(काष्ठा qlcnic_rds_mbx);
	cap = QLCNIC_CAP0_LEGACY_CONTEXT;

	अगर (adapter->flags & QLCNIC_FW_LRO_MSS_CAP)
		cap |= QLC_83XX_FW_CAP_LRO_MSS;

	/* set mailbox hdr and capabilities */
	err = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_CREATE_RX_CTX);
	अगर (err)
		वापस err;

	अगर (qlcnic_sriov_pf_check(adapter) || qlcnic_sriov_vf_check(adapter))
		cmd.req.arg[0] |= (0x3 << 29);

	cmd.req.arg[1] = cap;
	cmd.req.arg[5] = 1 | (num_rds << 5) | (num_sds << 8) |
			 (QLC_83XX_HOST_RDS_MODE_UNIQUE << 16);

	अगर (qlcnic_sriov_pf_check(adapter))
		qlcnic_pf_set_पूर्णांकerface_id_create_rx_ctx(adapter,
							 &cmd.req.arg[6]);
	/* set up status rings, mbx 8-57/87 */
	index = QLC_83XX_HOST_SDS_MBX_IDX;
	क्रम (i = 0; i < num_sds; i++) अणु
		स_रखो(&sds_mbx, 0, sds_mbx_size);
		sds = &recv_ctx->sds_rings[i];
		sds->consumer = 0;
		स_रखो(sds->desc_head, 0, STATUS_DESC_RINGSIZE(sds));
		sds_mbx.phy_addr_low = LSD(sds->phys_addr);
		sds_mbx.phy_addr_high = MSD(sds->phys_addr);
		sds_mbx.sds_ring_size = sds->num_desc;
		अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
			पूर्णांकrpt_id = ahw->पूर्णांकr_tbl[i].id;
		अन्यथा
			पूर्णांकrpt_id = QLCRDX(ahw, QLCNIC_DEF_INT_ID);
		अगर (adapter->ahw->diag_test != QLCNIC_LOOPBACK_TEST)
			sds_mbx.पूर्णांकrpt_id = पूर्णांकrpt_id;
		अन्यथा
			sds_mbx.पूर्णांकrpt_id = 0xffff;
		sds_mbx.पूर्णांकrpt_val = 0;
		buf = &cmd.req.arg[index];
		स_नकल(buf, &sds_mbx, sds_mbx_size);
		index += sds_mbx_size / माप(u32);
	पूर्ण
	/* set up receive rings, mbx 88-111/135 */
	index = QLCNIC_HOST_RDS_MBX_IDX;
	rds = &recv_ctx->rds_rings[0];
	rds->producer = 0;
	स_रखो(&rds_mbx, 0, rds_mbx_size);
	rds_mbx.phy_addr_reg_low = LSD(rds->phys_addr);
	rds_mbx.phy_addr_reg_high = MSD(rds->phys_addr);
	rds_mbx.reg_ring_sz = rds->dma_size;
	rds_mbx.reg_ring_len = rds->num_desc;
	/* Jumbo ring */
	rds = &recv_ctx->rds_rings[1];
	rds->producer = 0;
	rds_mbx.phy_addr_jmb_low = LSD(rds->phys_addr);
	rds_mbx.phy_addr_jmb_high = MSD(rds->phys_addr);
	rds_mbx.jmb_ring_sz = rds->dma_size;
	rds_mbx.jmb_ring_len = rds->num_desc;
	buf = &cmd.req.arg[index];
	स_नकल(buf, &rds_mbx, rds_mbx_size);

	/* send the mailbox command */
	err = ahw->hw_ops->mbx_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to create Rx ctx in firmware%d\n", err);
		जाओ out;
	पूर्ण
	mbx_out = (काष्ठा qlcnic_rcv_mbx_out *)&cmd.rsp.arg[1];
	recv_ctx->context_id = mbx_out->ctx_id;
	recv_ctx->state = mbx_out->state;
	recv_ctx->virt_port = mbx_out->vport_id;
	dev_info(&adapter->pdev->dev, "Rx Context[%d] Created, state:0x%x\n",
		 recv_ctx->context_id, recv_ctx->state);
	/* Receive descriptor ring */
	/* Standard ring */
	rds = &recv_ctx->rds_rings[0];
	rds->crb_rcv_producer = ahw->pci_base0 +
				mbx_out->host_prod[0].reg_buf;
	/* Jumbo ring */
	rds = &recv_ctx->rds_rings[1];
	rds->crb_rcv_producer = ahw->pci_base0 +
				mbx_out->host_prod[0].jmb_buf;
	/* status descriptor ring */
	क्रम (i = 0; i < num_sds; i++) अणु
		sds = &recv_ctx->sds_rings[i];
		sds->crb_sts_consumer = ahw->pci_base0 +
					mbx_out->host_csmr[i];
		अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
			पूर्णांकr_mask = ahw->पूर्णांकr_tbl[i].src;
		अन्यथा
			पूर्णांकr_mask = QLCRDX(ahw, QLCNIC_DEF_INT_MASK);
		sds->crb_पूर्णांकr_mask = ahw->pci_base0 + पूर्णांकr_mask;
	पूर्ण

	अगर (adapter->drv_sds_rings > QLCNIC_MAX_SDS_RINGS)
		err = qlcnic_83xx_add_rings(adapter);
out:
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

व्योम qlcnic_83xx_del_tx_ctx(काष्ठा qlcnic_adapter *adapter,
			    काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	u32 temp = 0;

	अगर (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_DESTROY_TX_CTX))
		वापस;

	अगर (qlcnic_sriov_pf_check(adapter) || qlcnic_sriov_vf_check(adapter))
		cmd.req.arg[0] |= (0x3 << 29);

	अगर (qlcnic_sriov_pf_check(adapter))
		qlcnic_pf_set_पूर्णांकerface_id_del_tx_ctx(adapter, &temp);

	cmd.req.arg[1] = tx_ring->ctx_id | temp;
	अगर (qlcnic_issue_cmd(adapter, &cmd))
		dev_err(&adapter->pdev->dev,
			"Failed to destroy tx ctx in firmware\n");
	qlcnic_मुक्त_mbx_args(&cmd);
पूर्ण

पूर्णांक qlcnic_83xx_create_tx_ctx(काष्ठा qlcnic_adapter *adapter,
			      काष्ठा qlcnic_host_tx_ring *tx, पूर्णांक ring)
अणु
	पूर्णांक err;
	u16 msix_id;
	u32 *buf, पूर्णांकr_mask, temp = 0;
	काष्ठा qlcnic_cmd_args cmd;
	काष्ठा qlcnic_tx_mbx mbx;
	काष्ठा qlcnic_tx_mbx_out *mbx_out;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u32 msix_vector;

	/* Reset host resources */
	tx->producer = 0;
	tx->sw_consumer = 0;
	*(tx->hw_consumer) = 0;

	स_रखो(&mbx, 0, माप(काष्ठा qlcnic_tx_mbx));

	/* setup mailbox inbox रेजिस्टरss */
	mbx.phys_addr_low = LSD(tx->phys_addr);
	mbx.phys_addr_high = MSD(tx->phys_addr);
	mbx.cnsmr_index_low = LSD(tx->hw_cons_phys_addr);
	mbx.cnsmr_index_high = MSD(tx->hw_cons_phys_addr);
	mbx.size = tx->num_desc;
	अगर (adapter->flags & QLCNIC_MSIX_ENABLED) अणु
		अगर (!(adapter->flags & QLCNIC_TX_INTR_SHARED))
			msix_vector = adapter->drv_sds_rings + ring;
		अन्यथा
			msix_vector = adapter->drv_sds_rings - 1;
		msix_id = ahw->पूर्णांकr_tbl[msix_vector].id;
	पूर्ण अन्यथा अणु
		msix_id = QLCRDX(ahw, QLCNIC_DEF_INT_ID);
	पूर्ण

	अगर (adapter->ahw->diag_test != QLCNIC_LOOPBACK_TEST)
		mbx.पूर्णांकr_id = msix_id;
	अन्यथा
		mbx.पूर्णांकr_id = 0xffff;
	mbx.src = 0;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CREATE_TX_CTX);
	अगर (err)
		वापस err;

	अगर (qlcnic_sriov_pf_check(adapter) || qlcnic_sriov_vf_check(adapter))
		cmd.req.arg[0] |= (0x3 << 29);

	अगर (qlcnic_sriov_pf_check(adapter))
		qlcnic_pf_set_पूर्णांकerface_id_create_tx_ctx(adapter, &temp);

	cmd.req.arg[1] = QLCNIC_CAP0_LEGACY_CONTEXT;
	cmd.req.arg[5] = QLCNIC_SINGLE_RING | temp;

	buf = &cmd.req.arg[6];
	स_नकल(buf, &mbx, माप(काष्ठा qlcnic_tx_mbx));
	/* send the mailbox command*/
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		netdev_err(adapter->netdev,
			   "Failed to create Tx ctx in firmware 0x%x\n", err);
		जाओ out;
	पूर्ण
	mbx_out = (काष्ठा qlcnic_tx_mbx_out *)&cmd.rsp.arg[2];
	tx->crb_cmd_producer = ahw->pci_base0 + mbx_out->host_prod;
	tx->ctx_id = mbx_out->ctx_id;
	अगर ((adapter->flags & QLCNIC_MSIX_ENABLED) &&
	    !(adapter->flags & QLCNIC_TX_INTR_SHARED)) अणु
		पूर्णांकr_mask = ahw->पूर्णांकr_tbl[adapter->drv_sds_rings + ring].src;
		tx->crb_पूर्णांकr_mask = ahw->pci_base0 + पूर्णांकr_mask;
	पूर्ण
	netdev_info(adapter->netdev,
		    "Tx Context[0x%x] Created, state:0x%x\n",
		    tx->ctx_id, mbx_out->state);
out:
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_83xx_diag_alloc_res(काष्ठा net_device *netdev, पूर्णांक test,
				      u8 num_sds_ring)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	u16 adapter_state = adapter->is_up;
	u8 ring;
	पूर्णांक ret;

	netअगर_device_detach(netdev);

	अगर (netअगर_running(netdev))
		__qlcnic_करोwn(adapter, netdev);

	qlcnic_detach(adapter);

	adapter->drv_sds_rings = QLCNIC_SINGLE_RING;
	adapter->ahw->diag_test = test;
	adapter->ahw->linkup = 0;

	ret = qlcnic_attach(adapter);
	अगर (ret) अणु
		netअगर_device_attach(netdev);
		वापस ret;
	पूर्ण

	ret = qlcnic_fw_create_ctx(adapter);
	अगर (ret) अणु
		qlcnic_detach(adapter);
		अगर (adapter_state == QLCNIC_ADAPTER_UP_MAGIC) अणु
			adapter->drv_sds_rings = num_sds_ring;
			qlcnic_attach(adapter);
		पूर्ण
		netअगर_device_attach(netdev);
		वापस ret;
	पूर्ण

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &adapter->recv_ctx->rds_rings[ring];
		qlcnic_post_rx_buffers(adapter, rds_ring, ring);
	पूर्ण

	अगर (adapter->ahw->diag_test == QLCNIC_INTERRUPT_TEST) अणु
		क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
			sds_ring = &adapter->recv_ctx->sds_rings[ring];
			qlcnic_enable_sds_पूर्णांकr(adapter, sds_ring);
		पूर्ण
	पूर्ण

	अगर (adapter->ahw->diag_test == QLCNIC_LOOPBACK_TEST) अणु
		adapter->ahw->loopback_state = 0;
		adapter->ahw->hw_ops->setup_link_event(adapter, 1);
	पूर्ण

	set_bit(__QLCNIC_DEV_UP, &adapter->state);
	वापस 0;
पूर्ण

अटल व्योम qlcnic_83xx_diag_मुक्त_res(काष्ठा net_device *netdev,
				      u8 drv_sds_rings)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	पूर्णांक ring;

	clear_bit(__QLCNIC_DEV_UP, &adapter->state);
	अगर (adapter->ahw->diag_test == QLCNIC_INTERRUPT_TEST) अणु
		क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
			sds_ring = &adapter->recv_ctx->sds_rings[ring];
			अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
				qlcnic_disable_sds_पूर्णांकr(adapter, sds_ring);
		पूर्ण
	पूर्ण

	qlcnic_fw_destroy_ctx(adapter);
	qlcnic_detach(adapter);

	adapter->ahw->diag_test = 0;
	adapter->drv_sds_rings = drv_sds_rings;

	अगर (qlcnic_attach(adapter))
		जाओ out;

	अगर (netअगर_running(netdev))
		__qlcnic_up(adapter, netdev);

out:
	netअगर_device_attach(netdev);
पूर्ण

अटल व्योम qlcnic_83xx_get_beacon_state(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_cmd_args cmd;
	u8 beacon_state;
	पूर्णांक err = 0;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_LED_CONFIG);
	अगर (!err) अणु
		err = qlcnic_issue_cmd(adapter, &cmd);
		अगर (!err) अणु
			beacon_state = cmd.rsp.arg[4];
			अगर (beacon_state == QLCNIC_BEACON_DISABLE)
				ahw->beacon_state = QLC_83XX_BEACON_OFF;
			अन्यथा अगर (beacon_state == QLC_83XX_ENABLE_BEACON)
				ahw->beacon_state = QLC_83XX_BEACON_ON;
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev_err(adapter->netdev, "Get beacon state failed, err=%d\n",
			   err);
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);

	वापस;
पूर्ण

पूर्णांक qlcnic_83xx_config_led(काष्ठा qlcnic_adapter *adapter, u32 state,
			   u32 beacon)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	u32 mbx_in;
	पूर्णांक i, status = 0;

	अगर (state) अणु
		/* Get LED configuration */
		status = qlcnic_alloc_mbx_args(&cmd, adapter,
					       QLCNIC_CMD_GET_LED_CONFIG);
		अगर (status)
			वापस status;

		status = qlcnic_issue_cmd(adapter, &cmd);
		अगर (status) अणु
			dev_err(&adapter->pdev->dev,
				"Get led config failed.\n");
			जाओ mbx_err;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < 4; i++)
				adapter->ahw->mbox_reg[i] = cmd.rsp.arg[i+1];
		पूर्ण
		qlcnic_मुक्त_mbx_args(&cmd);
		/* Set LED Configuration */
		mbx_in = (LSW(QLC_83XX_LED_CONFIG) << 16) |
			  LSW(QLC_83XX_LED_CONFIG);
		status = qlcnic_alloc_mbx_args(&cmd, adapter,
					       QLCNIC_CMD_SET_LED_CONFIG);
		अगर (status)
			वापस status;

		cmd.req.arg[1] = mbx_in;
		cmd.req.arg[2] = mbx_in;
		cmd.req.arg[3] = mbx_in;
		अगर (beacon)
			cmd.req.arg[4] = QLC_83XX_ENABLE_BEACON;
		status = qlcnic_issue_cmd(adapter, &cmd);
		अगर (status) अणु
			dev_err(&adapter->pdev->dev,
				"Set led config failed.\n");
		पूर्ण
mbx_err:
		qlcnic_मुक्त_mbx_args(&cmd);
		वापस status;

	पूर्ण अन्यथा अणु
		/* Restoring शेष LED configuration */
		status = qlcnic_alloc_mbx_args(&cmd, adapter,
					       QLCNIC_CMD_SET_LED_CONFIG);
		अगर (status)
			वापस status;

		cmd.req.arg[1] = adapter->ahw->mbox_reg[0];
		cmd.req.arg[2] = adapter->ahw->mbox_reg[1];
		cmd.req.arg[3] = adapter->ahw->mbox_reg[2];
		अगर (beacon)
			cmd.req.arg[4] = adapter->ahw->mbox_reg[3];
		status = qlcnic_issue_cmd(adapter, &cmd);
		अगर (status)
			dev_err(&adapter->pdev->dev,
				"Restoring led config failed.\n");
		qlcnic_मुक्त_mbx_args(&cmd);
		वापस status;
	पूर्ण
पूर्ण

पूर्णांक  qlcnic_83xx_set_led(काष्ठा net_device *netdev,
			 क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err = -EIO, active = 1;

	अगर (adapter->ahw->op_mode == QLCNIC_NON_PRIV_FUNC) अणु
		netdev_warn(netdev,
			    "LED test is not supported in non-privileged mode\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		अगर (test_and_set_bit(__QLCNIC_LED_ENABLE, &adapter->state))
			वापस -EBUSY;

		अगर (test_bit(__QLCNIC_RESETTING, &adapter->state))
			अवरोध;

		err = qlcnic_83xx_config_led(adapter, active, 0);
		अगर (err)
			netdev_err(netdev, "Failed to set LED blink state\n");
		अवरोध;
	हाल ETHTOOL_ID_INACTIVE:
		active = 0;

		अगर (test_bit(__QLCNIC_RESETTING, &adapter->state))
			अवरोध;

		err = qlcnic_83xx_config_led(adapter, active, 0);
		अगर (err)
			netdev_err(netdev, "Failed to reset LED blink state\n");
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!active || err)
		clear_bit(__QLCNIC_LED_ENABLE, &adapter->state);

	वापस err;
पूर्ण

व्योम qlcnic_83xx_initialize_nic(काष्ठा qlcnic_adapter *adapter, पूर्णांक enable)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक status;

	अगर (qlcnic_sriov_vf_check(adapter))
		वापस;

	अगर (enable)
		status = qlcnic_alloc_mbx_args(&cmd, adapter,
					       QLCNIC_CMD_INIT_NIC_FUNC);
	अन्यथा
		status = qlcnic_alloc_mbx_args(&cmd, adapter,
					       QLCNIC_CMD_STOP_NIC_FUNC);

	अगर (status)
		वापस;

	cmd.req.arg[1] = QLC_REGISTER_LB_IDC | QLC_INIT_FW_RESOURCES;

	अगर (adapter->dcb)
		cmd.req.arg[1] |= QLC_REGISTER_DCB_AEN;

	status = qlcnic_issue_cmd(adapter, &cmd);
	अगर (status)
		dev_err(&adapter->pdev->dev,
			"Failed to %s in NIC IDC function event.\n",
			(enable ? "register" : "unregister"));

	qlcnic_मुक्त_mbx_args(&cmd);
पूर्ण

अटल पूर्णांक qlcnic_83xx_set_port_config(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक err;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_SET_PORT_CONFIG);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = adapter->ahw->port_config;
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err)
		dev_info(&adapter->pdev->dev, "Set Port Config failed.\n");
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_83xx_get_port_config(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक err;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_PORT_CONFIG);
	अगर (err)
		वापस err;

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err)
		dev_info(&adapter->pdev->dev, "Get Port config failed\n");
	अन्यथा
		adapter->ahw->port_config = cmd.rsp.arg[1];
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

पूर्णांक qlcnic_83xx_setup_link_event(काष्ठा qlcnic_adapter *adapter, पूर्णांक enable)
अणु
	पूर्णांक err;
	u32 temp;
	काष्ठा qlcnic_cmd_args cmd;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_LINK_EVENT);
	अगर (err)
		वापस err;

	temp = adapter->recv_ctx->context_id << 16;
	cmd.req.arg[1] = (enable ? 1 : 0) | BIT_8 | temp;
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err)
		dev_info(&adapter->pdev->dev,
			 "Setup linkevent mailbox failed\n");
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

अटल व्योम qlcnic_83xx_set_पूर्णांकerface_id_promisc(काष्ठा qlcnic_adapter *adapter,
						 u32 *पूर्णांकerface_id)
अणु
	अगर (qlcnic_sriov_pf_check(adapter)) अणु
		qlcnic_alloc_lb_filters_mem(adapter);
		qlcnic_pf_set_पूर्णांकerface_id_promisc(adapter, पूर्णांकerface_id);
		adapter->rx_mac_learn = true;
	पूर्ण अन्यथा अणु
		अगर (!qlcnic_sriov_vf_check(adapter))
			*पूर्णांकerface_id = adapter->recv_ctx->context_id << 16;
	पूर्ण
पूर्ण

पूर्णांक qlcnic_83xx_nic_set_promisc(काष्ठा qlcnic_adapter *adapter, u32 mode)
अणु
	काष्ठा qlcnic_cmd_args *cmd = शून्य;
	u32 temp = 0;
	पूर्णांक err;

	अगर (adapter->recv_ctx->state == QLCNIC_HOST_CTX_STATE_FREED)
		वापस -EIO;

	cmd = kzalloc(माप(*cmd), GFP_ATOMIC);
	अगर (!cmd)
		वापस -ENOMEM;

	err = qlcnic_alloc_mbx_args(cmd, adapter,
				    QLCNIC_CMD_CONFIGURE_MAC_RX_MODE);
	अगर (err)
		जाओ out;

	cmd->type = QLC_83XX_MBX_CMD_NO_WAIT;
	qlcnic_83xx_set_पूर्णांकerface_id_promisc(adapter, &temp);

	अगर (qlcnic_84xx_check(adapter) && qlcnic_sriov_pf_check(adapter))
		mode = VPORT_MISS_MODE_ACCEPT_ALL;

	cmd->req.arg[1] = mode | temp;
	err = qlcnic_issue_cmd(adapter, cmd);
	अगर (!err)
		वापस err;

	qlcnic_मुक्त_mbx_args(cmd);

out:
	kमुक्त(cmd);
	वापस err;
पूर्ण

पूर्णांक qlcnic_83xx_loopback_test(काष्ठा net_device *netdev, u8 mode)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u8 drv_sds_rings = adapter->drv_sds_rings;
	u8 drv_tx_rings = adapter->drv_tx_rings;
	पूर्णांक ret = 0, loop = 0;

	अगर (ahw->op_mode == QLCNIC_NON_PRIV_FUNC) अणु
		netdev_warn(netdev,
			    "Loopback test not supported in non privileged mode\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (test_bit(__QLCNIC_RESETTING, &adapter->state)) अणु
		netdev_info(netdev, "Device is resetting\n");
		वापस -EBUSY;
	पूर्ण

	अगर (qlcnic_get_diag_lock(adapter)) अणु
		netdev_info(netdev, "Device is in diagnostics mode\n");
		वापस -EBUSY;
	पूर्ण

	netdev_info(netdev, "%s loopback test in progress\n",
		    mode == QLCNIC_ILB_MODE ? "internal" : "external");

	ret = qlcnic_83xx_diag_alloc_res(netdev, QLCNIC_LOOPBACK_TEST,
					 drv_sds_rings);
	अगर (ret)
		जाओ fail_diag_alloc;

	ret = qlcnic_83xx_set_lb_mode(adapter, mode);
	अगर (ret)
		जाओ मुक्त_diag_res;

	/* Poll क्रम link up event beक्रमe running traffic */
	करो अणु
		msleep(QLC_83XX_LB_MSLEEP_COUNT);

		अगर (test_bit(__QLCNIC_RESETTING, &adapter->state)) अणु
			netdev_info(netdev,
				    "Device is resetting, free LB test resources\n");
			ret = -EBUSY;
			जाओ मुक्त_diag_res;
		पूर्ण
		अगर (loop++ > QLC_83XX_LB_WAIT_COUNT) अणु
			netdev_info(netdev,
				    "Firmware didn't sent link up event to loopback request\n");
			ret = -ETIMEDOUT;
			qlcnic_83xx_clear_lb_mode(adapter, mode);
			जाओ मुक्त_diag_res;
		पूर्ण
	पूर्ण जबतक ((adapter->ahw->linkup && ahw->has_link_events) != 1);

	ret = qlcnic_करो_lb_test(adapter, mode);

	qlcnic_83xx_clear_lb_mode(adapter, mode);

मुक्त_diag_res:
	qlcnic_83xx_diag_मुक्त_res(netdev, drv_sds_rings);

fail_diag_alloc:
	adapter->drv_sds_rings = drv_sds_rings;
	adapter->drv_tx_rings = drv_tx_rings;
	qlcnic_release_diag_lock(adapter);
	वापस ret;
पूर्ण

अटल व्योम qlcnic_extend_lb_idc_cmpltn_रुको(काष्ठा qlcnic_adapter *adapter,
					     u32 *max_रुको_count)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक temp;

	netdev_info(adapter->netdev, "Received loopback IDC time extend event for 0x%x seconds\n",
		    ahw->extend_lb_समय);
	temp = ahw->extend_lb_समय * 1000;
	*max_रुको_count += temp / QLC_83XX_LB_MSLEEP_COUNT;
	ahw->extend_lb_समय = 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_set_lb_mode(काष्ठा qlcnic_adapter *adapter, u8 mode)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा net_device *netdev = adapter->netdev;
	u32 config, max_रुको_count;
	पूर्णांक status = 0, loop = 0;

	ahw->extend_lb_समय = 0;
	max_रुको_count = QLC_83XX_LB_WAIT_COUNT;
	status = qlcnic_83xx_get_port_config(adapter);
	अगर (status)
		वापस status;

	config = ahw->port_config;

	/* Check अगर port is alपढ़ोy in loopback mode */
	अगर ((config & QLC_83XX_CFG_LOOPBACK_HSS) ||
	    (config & QLC_83XX_CFG_LOOPBACK_EXT)) अणु
		netdev_err(netdev,
			   "Port already in Loopback mode.\n");
		वापस -EINPROGRESS;
	पूर्ण

	set_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);

	अगर (mode == QLCNIC_ILB_MODE)
		ahw->port_config |= QLC_83XX_CFG_LOOPBACK_HSS;
	अगर (mode == QLCNIC_ELB_MODE)
		ahw->port_config |= QLC_83XX_CFG_LOOPBACK_EXT;

	status = qlcnic_83xx_set_port_config(adapter);
	अगर (status) अणु
		netdev_err(netdev,
			   "Failed to Set Loopback Mode = 0x%x.\n",
			   ahw->port_config);
		ahw->port_config = config;
		clear_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);
		वापस status;
	पूर्ण

	/* Wait क्रम Link and IDC Completion AEN */
	करो अणु
		msleep(QLC_83XX_LB_MSLEEP_COUNT);

		अगर (test_bit(__QLCNIC_RESETTING, &adapter->state)) अणु
			netdev_info(netdev,
				    "Device is resetting, free LB test resources\n");
			clear_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);
			वापस -EBUSY;
		पूर्ण

		अगर (ahw->extend_lb_समय)
			qlcnic_extend_lb_idc_cmpltn_रुको(adapter,
							 &max_रुको_count);

		अगर (loop++ > max_रुको_count) अणु
			netdev_err(netdev, "%s: Did not receive loopback IDC completion AEN\n",
				   __func__);
			clear_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);
			qlcnic_83xx_clear_lb_mode(adapter, mode);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण जबतक (test_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status));

	qlcnic_sre_macaddr_change(adapter, adapter->mac_addr, 0,
				  QLCNIC_MAC_ADD);
	वापस status;
पूर्ण

अटल पूर्णांक qlcnic_83xx_clear_lb_mode(काष्ठा qlcnic_adapter *adapter, u8 mode)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u32 config = ahw->port_config, max_रुको_count;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक status = 0, loop = 0;

	ahw->extend_lb_समय = 0;
	max_रुको_count = QLC_83XX_LB_WAIT_COUNT;
	set_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);
	अगर (mode == QLCNIC_ILB_MODE)
		ahw->port_config &= ~QLC_83XX_CFG_LOOPBACK_HSS;
	अगर (mode == QLCNIC_ELB_MODE)
		ahw->port_config &= ~QLC_83XX_CFG_LOOPBACK_EXT;

	status = qlcnic_83xx_set_port_config(adapter);
	अगर (status) अणु
		netdev_err(netdev,
			   "Failed to Clear Loopback Mode = 0x%x.\n",
			   ahw->port_config);
		ahw->port_config = config;
		clear_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);
		वापस status;
	पूर्ण

	/* Wait क्रम Link and IDC Completion AEN */
	करो अणु
		msleep(QLC_83XX_LB_MSLEEP_COUNT);

		अगर (test_bit(__QLCNIC_RESETTING, &adapter->state)) अणु
			netdev_info(netdev,
				    "Device is resetting, free LB test resources\n");
			clear_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);
			वापस -EBUSY;
		पूर्ण

		अगर (ahw->extend_lb_समय)
			qlcnic_extend_lb_idc_cmpltn_रुको(adapter,
							 &max_रुको_count);

		अगर (loop++ > max_रुको_count) अणु
			netdev_err(netdev, "%s: Did not receive loopback IDC completion AEN\n",
				   __func__);
			clear_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण जबतक (test_bit(QLC_83XX_IDC_COMP_AEN, &ahw->idc.status));

	qlcnic_sre_macaddr_change(adapter, adapter->mac_addr, 0,
				  QLCNIC_MAC_DEL);
	वापस status;
पूर्ण

अटल व्योम qlcnic_83xx_set_पूर्णांकerface_id_ipaddr(काष्ठा qlcnic_adapter *adapter,
						u32 *पूर्णांकerface_id)
अणु
	अगर (qlcnic_sriov_pf_check(adapter)) अणु
		qlcnic_pf_set_पूर्णांकerface_id_ipaddr(adapter, पूर्णांकerface_id);
	पूर्ण अन्यथा अणु
		अगर (!qlcnic_sriov_vf_check(adapter))
			*पूर्णांकerface_id = adapter->recv_ctx->context_id << 16;
	पूर्ण
पूर्ण

व्योम qlcnic_83xx_config_ipaddr(काष्ठा qlcnic_adapter *adapter, __be32 ip,
			       पूर्णांक mode)
अणु
	पूर्णांक err;
	u32 temp = 0, temp_ip;
	काष्ठा qlcnic_cmd_args cmd;

	err = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_CONFIGURE_IP_ADDR);
	अगर (err)
		वापस;

	qlcnic_83xx_set_पूर्णांकerface_id_ipaddr(adapter, &temp);

	अगर (mode == QLCNIC_IP_UP)
		cmd.req.arg[1] = 1 | temp;
	अन्यथा
		cmd.req.arg[1] = 2 | temp;

	/*
	 * Adapter needs IP address in network byte order.
	 * But hardware mailbox रेजिस्टरs go through ग_लिखोl(), hence IP address
	 * माला_लो swapped on big endian architecture.
	 * To negate swapping of ग_लिखोl() on big endian architecture
	 * use swab32(value).
	 */

	temp_ip = swab32(ntohl(ip));
	स_नकल(&cmd.req.arg[2], &temp_ip, माप(u32));
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err != QLCNIC_RCODE_SUCCESS)
		dev_err(&adapter->netdev->dev,
			"could not notify %s IP 0x%x request\n",
			(mode == QLCNIC_IP_UP) ? "Add" : "Remove", ip);

	qlcnic_मुक्त_mbx_args(&cmd);
पूर्ण

पूर्णांक qlcnic_83xx_config_hw_lro(काष्ठा qlcnic_adapter *adapter, पूर्णांक mode)
अणु
	पूर्णांक err;
	u32 temp, arg1;
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक lro_bit_mask;

	lro_bit_mask = (mode ? (BIT_0 | BIT_1 | BIT_2 | BIT_3) : 0);

	अगर (adapter->recv_ctx->state == QLCNIC_HOST_CTX_STATE_FREED)
		वापस 0;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIGURE_HW_LRO);
	अगर (err)
		वापस err;

	temp = adapter->recv_ctx->context_id << 16;
	arg1 = lro_bit_mask | temp;
	cmd.req.arg[1] = arg1;

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err)
		dev_info(&adapter->pdev->dev, "LRO config failed\n");
	qlcnic_मुक्त_mbx_args(&cmd);

	वापस err;
पूर्ण

पूर्णांक qlcnic_83xx_config_rss(काष्ठा qlcnic_adapter *adapter, पूर्णांक enable)
अणु
	पूर्णांक err;
	u32 word;
	काष्ठा qlcnic_cmd_args cmd;
	स्थिर u64 key[] = अणु 0xbeac01fa6a42b73bULL, 0x8030f20c77cb2da3ULL,
			    0xae7b30b4d0ca2bcbULL, 0x43a38fb04167253dULL,
			    0x255b0ec26d5a56daULL पूर्ण;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIGURE_RSS);
	अगर (err)
		वापस err;
	/*
	 * RSS request:
	 * bits 3-0: Rsvd
	 *      5-4: hash_type_ipv4
	 *	7-6: hash_type_ipv6
	 *	  8: enable
	 *        9: use indirection table
	 *    16-31: indirection table mask
	 */
	word =  ((u32)(RSS_HASHTYPE_IP_TCP & 0x3) << 4) |
		((u32)(RSS_HASHTYPE_IP_TCP & 0x3) << 6) |
		((u32)(enable & 0x1) << 8) |
		((0x7ULL) << 16);
	cmd.req.arg[1] = (adapter->recv_ctx->context_id);
	cmd.req.arg[2] = word;
	स_नकल(&cmd.req.arg[4], key, माप(key));

	err = qlcnic_issue_cmd(adapter, &cmd);

	अगर (err)
		dev_info(&adapter->pdev->dev, "RSS config failed\n");
	qlcnic_मुक्त_mbx_args(&cmd);

	वापस err;

पूर्ण

अटल व्योम qlcnic_83xx_set_पूर्णांकerface_id_macaddr(काष्ठा qlcnic_adapter *adapter,
						 u32 *पूर्णांकerface_id)
अणु
	अगर (qlcnic_sriov_pf_check(adapter)) अणु
		qlcnic_pf_set_पूर्णांकerface_id_macaddr(adapter, पूर्णांकerface_id);
	पूर्ण अन्यथा अणु
		अगर (!qlcnic_sriov_vf_check(adapter))
			*पूर्णांकerface_id = adapter->recv_ctx->context_id << 16;
	पूर्ण
पूर्ण

पूर्णांक qlcnic_83xx_sre_macaddr_change(काष्ठा qlcnic_adapter *adapter, u8 *addr,
				   u16 vlan_id, u8 op)
अणु
	काष्ठा qlcnic_cmd_args *cmd = शून्य;
	काष्ठा qlcnic_macvlan_mbx mv;
	u32 *buf, temp = 0;
	पूर्णांक err;

	अगर (adapter->recv_ctx->state == QLCNIC_HOST_CTX_STATE_FREED)
		वापस -EIO;

	cmd = kzalloc(माप(*cmd), GFP_ATOMIC);
	अगर (!cmd)
		वापस -ENOMEM;

	err = qlcnic_alloc_mbx_args(cmd, adapter, QLCNIC_CMD_CONFIG_MAC_VLAN);
	अगर (err)
		जाओ out;

	cmd->type = QLC_83XX_MBX_CMD_NO_WAIT;

	अगर (vlan_id)
		op = (op == QLCNIC_MAC_ADD || op == QLCNIC_MAC_VLAN_ADD) ?
		     QLCNIC_MAC_VLAN_ADD : QLCNIC_MAC_VLAN_DEL;

	cmd->req.arg[1] = op | (1 << 8);
	qlcnic_83xx_set_पूर्णांकerface_id_macaddr(adapter, &temp);
	cmd->req.arg[1] |= temp;
	mv.vlan = vlan_id;
	mv.mac_addr0 = addr[0];
	mv.mac_addr1 = addr[1];
	mv.mac_addr2 = addr[2];
	mv.mac_addr3 = addr[3];
	mv.mac_addr4 = addr[4];
	mv.mac_addr5 = addr[5];
	buf = &cmd->req.arg[2];
	स_नकल(buf, &mv, माप(काष्ठा qlcnic_macvlan_mbx));
	err = qlcnic_issue_cmd(adapter, cmd);
	अगर (!err)
		वापस err;

	qlcnic_मुक्त_mbx_args(cmd);
out:
	kमुक्त(cmd);
	वापस err;
पूर्ण

व्योम qlcnic_83xx_change_l2_filter(काष्ठा qlcnic_adapter *adapter, u64 *addr,
				  u16 vlan_id,
				  काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	u8 mac[ETH_ALEN];
	स_नकल(&mac, addr, ETH_ALEN);
	qlcnic_83xx_sre_macaddr_change(adapter, mac, vlan_id, QLCNIC_MAC_ADD);
पूर्ण

अटल व्योम qlcnic_83xx_configure_mac(काष्ठा qlcnic_adapter *adapter, u8 *mac,
				      u8 type, काष्ठा qlcnic_cmd_args *cmd)
अणु
	चयन (type) अणु
	हाल QLCNIC_SET_STATION_MAC:
	हाल QLCNIC_SET_FAC_DEF_MAC:
		स_नकल(&cmd->req.arg[2], mac, माप(u32));
		स_नकल(&cmd->req.arg[3], &mac[4], माप(u16));
		अवरोध;
	पूर्ण
	cmd->req.arg[1] = type;
पूर्ण

पूर्णांक qlcnic_83xx_get_mac_address(काष्ठा qlcnic_adapter *adapter, u8 *mac,
				u8 function)
अणु
	पूर्णांक err, i;
	काष्ठा qlcnic_cmd_args cmd;
	u32 mac_low, mac_high;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_MAC_ADDRESS);
	अगर (err)
		वापस err;

	qlcnic_83xx_configure_mac(adapter, mac, QLCNIC_GET_CURRENT_MAC, &cmd);
	err = qlcnic_issue_cmd(adapter, &cmd);

	अगर (err == QLCNIC_RCODE_SUCCESS) अणु
		mac_low = cmd.rsp.arg[1];
		mac_high = cmd.rsp.arg[2];

		क्रम (i = 0; i < 2; i++)
			mac[i] = (u8) (mac_high >> ((1 - i) * 8));
		क्रम (i = 2; i < 6; i++)
			mac[i] = (u8) (mac_low >> ((5 - i) * 8));
	पूर्ण अन्यथा अणु
		dev_err(&adapter->pdev->dev, "Failed to get mac address%d\n",
			err);
		err = -EIO;
	पूर्ण
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_83xx_set_rx_पूर्णांकr_coal(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_nic_पूर्णांकr_coalesce *coal = &adapter->ahw->coal;
	काष्ठा qlcnic_cmd_args cmd;
	u16 temp;
	पूर्णांक err;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIG_INTR_COAL);
	अगर (err)
		वापस err;

	temp = adapter->recv_ctx->context_id;
	cmd.req.arg[1] = QLCNIC_INTR_COAL_TYPE_RX | temp << 16;
	temp = coal->rx_समय_us;
	cmd.req.arg[2] = coal->rx_packets | temp << 16;
	cmd.req.arg[3] = coal->flag;

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err != QLCNIC_RCODE_SUCCESS)
		netdev_err(adapter->netdev,
			   "failed to set interrupt coalescing parameters\n");

	qlcnic_मुक्त_mbx_args(&cmd);

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_83xx_set_tx_पूर्णांकr_coal(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_nic_पूर्णांकr_coalesce *coal = &adapter->ahw->coal;
	काष्ठा qlcnic_cmd_args cmd;
	u16 temp;
	पूर्णांक err;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIG_INTR_COAL);
	अगर (err)
		वापस err;

	temp = adapter->tx_ring->ctx_id;
	cmd.req.arg[1] = QLCNIC_INTR_COAL_TYPE_TX | temp << 16;
	temp = coal->tx_समय_us;
	cmd.req.arg[2] = coal->tx_packets | temp << 16;
	cmd.req.arg[3] = coal->flag;

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err != QLCNIC_RCODE_SUCCESS)
		netdev_err(adapter->netdev,
			   "failed to set interrupt coalescing  parameters\n");

	qlcnic_मुक्त_mbx_args(&cmd);

	वापस err;
पूर्ण

पूर्णांक qlcnic_83xx_set_rx_tx_पूर्णांकr_coal(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err = 0;

	err = qlcnic_83xx_set_rx_पूर्णांकr_coal(adapter);
	अगर (err)
		netdev_err(adapter->netdev,
			   "failed to set Rx coalescing parameters\n");

	err = qlcnic_83xx_set_tx_पूर्णांकr_coal(adapter);
	अगर (err)
		netdev_err(adapter->netdev,
			   "failed to set Tx coalescing parameters\n");

	वापस err;
पूर्ण

पूर्णांक qlcnic_83xx_config_पूर्णांकr_coal(काष्ठा qlcnic_adapter *adapter,
				 काष्ठा ethtool_coalesce *ethcoal)
अणु
	काष्ठा qlcnic_nic_पूर्णांकr_coalesce *coal = &adapter->ahw->coal;
	u32 rx_coalesce_usecs, rx_max_frames;
	u32 tx_coalesce_usecs, tx_max_frames;
	पूर्णांक err;

	अगर (adapter->recv_ctx->state == QLCNIC_HOST_CTX_STATE_FREED)
		वापस -EIO;

	tx_coalesce_usecs = ethcoal->tx_coalesce_usecs;
	tx_max_frames = ethcoal->tx_max_coalesced_frames;
	rx_coalesce_usecs = ethcoal->rx_coalesce_usecs;
	rx_max_frames = ethcoal->rx_max_coalesced_frames;
	coal->flag = QLCNIC_INTR_DEFAULT;

	अगर ((coal->rx_समय_us == rx_coalesce_usecs) &&
	    (coal->rx_packets == rx_max_frames)) अणु
		coal->type = QLCNIC_INTR_COAL_TYPE_TX;
		coal->tx_समय_us = tx_coalesce_usecs;
		coal->tx_packets = tx_max_frames;
	पूर्ण अन्यथा अगर ((coal->tx_समय_us == tx_coalesce_usecs) &&
		   (coal->tx_packets == tx_max_frames)) अणु
		coal->type = QLCNIC_INTR_COAL_TYPE_RX;
		coal->rx_समय_us = rx_coalesce_usecs;
		coal->rx_packets = rx_max_frames;
	पूर्ण अन्यथा अणु
		coal->type = QLCNIC_INTR_COAL_TYPE_RX_TX;
		coal->rx_समय_us = rx_coalesce_usecs;
		coal->rx_packets = rx_max_frames;
		coal->tx_समय_us = tx_coalesce_usecs;
		coal->tx_packets = tx_max_frames;
	पूर्ण

	चयन (coal->type) अणु
	हाल QLCNIC_INTR_COAL_TYPE_RX:
		err = qlcnic_83xx_set_rx_पूर्णांकr_coal(adapter);
		अवरोध;
	हाल QLCNIC_INTR_COAL_TYPE_TX:
		err = qlcnic_83xx_set_tx_पूर्णांकr_coal(adapter);
		अवरोध;
	हाल QLCNIC_INTR_COAL_TYPE_RX_TX:
		err = qlcnic_83xx_set_rx_tx_पूर्णांकr_coal(adapter);
		अवरोध;
	शेष:
		err = -EINVAL;
		netdev_err(adapter->netdev,
			   "Invalid Interrupt coalescing type\n");
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम qlcnic_83xx_handle_link_aen(काष्ठा qlcnic_adapter *adapter,
					u32 data[])
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u8 link_status, duplex;
	/* link speed */
	link_status = LSB(data[3]) & 1;
	अगर (link_status) अणु
		ahw->link_speed = MSW(data[2]);
		duplex = LSB(MSW(data[3]));
		अगर (duplex)
			ahw->link_duplex = DUPLEX_FULL;
		अन्यथा
			ahw->link_duplex = DUPLEX_HALF;
	पूर्ण अन्यथा अणु
		ahw->link_speed = SPEED_UNKNOWN;
		ahw->link_duplex = DUPLEX_UNKNOWN;
	पूर्ण

	ahw->link_स्वतःneg = MSB(MSW(data[3]));
	ahw->module_type = MSB(LSW(data[3]));
	ahw->has_link_events = 1;
	ahw->lb_mode = data[4] & QLCNIC_LB_MODE_MASK;
	qlcnic_advert_link_change(adapter, link_status);
पूर्ण

अटल irqवापस_t qlcnic_83xx_handle_aen(पूर्णांक irq, व्योम *data)
अणु
	u32 mask, resp, event, rsp_status = QLC_83XX_MBX_RESPONSE_ARRIVED;
	काष्ठा qlcnic_adapter *adapter = data;
	काष्ठा qlcnic_mailbox *mbx;
	अचिन्हित दीर्घ flags;

	mbx = adapter->ahw->mailbox;
	spin_lock_irqsave(&mbx->aen_lock, flags);
	resp = QLCRDX(adapter->ahw, QLCNIC_FW_MBX_CTRL);
	अगर (!(resp & QLCNIC_SET_OWNER))
		जाओ out;

	event = पढ़ोl(QLCNIC_MBX_FW(adapter->ahw, 0));
	अगर (event &  QLCNIC_MBX_ASYNC_EVENT) अणु
		__qlcnic_83xx_process_aen(adapter);
	पूर्ण अन्यथा अणु
		अगर (mbx->rsp_status != rsp_status)
			qlcnic_83xx_notअगरy_mbx_response(mbx);
		अन्यथा
			adapter->stats.mbx_spurious_पूर्णांकr++;
	पूर्ण

out:
	mask = QLCRDX(adapter->ahw, QLCNIC_DEF_INT_MASK);
	ग_लिखोl(0, adapter->ahw->pci_base0 + mask);
	spin_unlock_irqrestore(&mbx->aen_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक qlcnic_83xx_set_nic_info(काष्ठा qlcnic_adapter *adapter,
			     काष्ठा qlcnic_info *nic)
अणु
	पूर्णांक i, err = -EIO;
	काष्ठा qlcnic_cmd_args cmd;

	अगर (adapter->ahw->op_mode != QLCNIC_MGMT_FUNC) अणु
		dev_err(&adapter->pdev->dev,
			"%s: Error, invoked by non management func\n",
			__func__);
		वापस err;
	पूर्ण

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_SET_NIC_INFO);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = (nic->pci_func << 16);
	cmd.req.arg[2] = 0x1 << 16;
	cmd.req.arg[3] = nic->phys_port | (nic->चयन_mode << 16);
	cmd.req.arg[4] = nic->capabilities;
	cmd.req.arg[5] = (nic->max_mac_filters & 0xFF) | ((nic->max_mtu) << 16);
	cmd.req.arg[6] = (nic->max_tx_ques) | ((nic->max_rx_ques) << 16);
	cmd.req.arg[7] = (nic->min_tx_bw) | ((nic->max_tx_bw) << 16);
	क्रम (i = 8; i < 32; i++)
		cmd.req.arg[i] = 0;

	err = qlcnic_issue_cmd(adapter, &cmd);

	अगर (err != QLCNIC_RCODE_SUCCESS) अणु
		dev_err(&adapter->pdev->dev, "Failed to set nic info%d\n",
			err);
		err = -EIO;
	पूर्ण

	qlcnic_मुक्त_mbx_args(&cmd);

	वापस err;
पूर्ण

पूर्णांक qlcnic_83xx_get_nic_info(काष्ठा qlcnic_adapter *adapter,
			     काष्ठा qlcnic_info *npar_info, u8 func_id)
अणु
	पूर्णांक err;
	u32 temp;
	u8 op = 0;
	काष्ठा qlcnic_cmd_args cmd;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_NIC_INFO);
	अगर (err)
		वापस err;

	अगर (func_id != ahw->pci_func) अणु
		temp = func_id << 16;
		cmd.req.arg[1] = op | BIT_31 | temp;
	पूर्ण अन्यथा अणु
		cmd.req.arg[1] = ahw->pci_func << 16;
	पूर्ण
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_info(&adapter->pdev->dev,
			 "Failed to get nic info %d\n", err);
		जाओ out;
	पूर्ण

	npar_info->op_type = cmd.rsp.arg[1];
	npar_info->pci_func = cmd.rsp.arg[2] & 0xFFFF;
	npar_info->op_mode = (cmd.rsp.arg[2] & 0xFFFF0000) >> 16;
	npar_info->phys_port = cmd.rsp.arg[3] & 0xFFFF;
	npar_info->चयन_mode = (cmd.rsp.arg[3] & 0xFFFF0000) >> 16;
	npar_info->capabilities = cmd.rsp.arg[4];
	npar_info->max_mac_filters = cmd.rsp.arg[5] & 0xFF;
	npar_info->max_mtu = (cmd.rsp.arg[5] & 0xFFFF0000) >> 16;
	npar_info->max_tx_ques = cmd.rsp.arg[6] & 0xFFFF;
	npar_info->max_rx_ques = (cmd.rsp.arg[6] & 0xFFFF0000) >> 16;
	npar_info->min_tx_bw = cmd.rsp.arg[7] & 0xFFFF;
	npar_info->max_tx_bw = (cmd.rsp.arg[7] & 0xFFFF0000) >> 16;
	अगर (cmd.rsp.arg[8] & 0x1)
		npar_info->max_bw_reg_offset = (cmd.rsp.arg[8] & 0x7FFE) >> 1;
	अगर (cmd.rsp.arg[8] & 0x10000) अणु
		temp = (cmd.rsp.arg[8] & 0x7FFE0000) >> 17;
		npar_info->max_linkspeed_reg_offset = temp;
	पूर्ण

	स_नकल(ahw->extra_capability, &cmd.rsp.arg[16],
	       माप(ahw->extra_capability));

out:
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

पूर्णांक qlcnic_get_pci_func_type(काष्ठा qlcnic_adapter *adapter, u16 type,
			     u16 *nic, u16 *fcoe, u16 *iscsi)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक err = 0;

	चयन (type) अणु
	हाल QLCNIC_TYPE_NIC:
		(*nic)++;
		अवरोध;
	हाल QLCNIC_TYPE_FCOE:
		(*fcoe)++;
		अवरोध;
	हाल QLCNIC_TYPE_ISCSI:
		(*iscsi)++;
		अवरोध;
	शेष:
		dev_err(dev, "%s: Unknown PCI type[%x]\n",
			__func__, type);
		err = -EIO;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक qlcnic_83xx_get_pci_info(काष्ठा qlcnic_adapter *adapter,
			     काष्ठा qlcnic_pci_info *pci_info)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा device *dev = &adapter->pdev->dev;
	u16 nic = 0, fcoe = 0, iscsi = 0;
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक i, err = 0, j = 0;
	u32 temp;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_PCI_INFO);
	अगर (err)
		वापस err;

	err = qlcnic_issue_cmd(adapter, &cmd);

	ahw->total_nic_func = 0;
	अगर (err == QLCNIC_RCODE_SUCCESS) अणु
		ahw->max_pci_func = cmd.rsp.arg[1] & 0xFF;
		क्रम (i = 2, j = 0; j < ahw->max_vnic_func; j++, pci_info++) अणु
			pci_info->id = cmd.rsp.arg[i] & 0xFFFF;
			pci_info->active = (cmd.rsp.arg[i] & 0xFFFF0000) >> 16;
			i++;
			अगर (!pci_info->active) अणु
				i += QLC_SKIP_INACTIVE_PCI_REGS;
				जारी;
			पूर्ण
			pci_info->type = cmd.rsp.arg[i] & 0xFFFF;
			err = qlcnic_get_pci_func_type(adapter, pci_info->type,
						       &nic, &fcoe, &iscsi);
			temp = (cmd.rsp.arg[i] & 0xFFFF0000) >> 16;
			pci_info->शेष_port = temp;
			i++;
			pci_info->tx_min_bw = cmd.rsp.arg[i] & 0xFFFF;
			temp = (cmd.rsp.arg[i] & 0xFFFF0000) >> 16;
			pci_info->tx_max_bw = temp;
			i = i + 2;
			स_नकल(pci_info->mac, &cmd.rsp.arg[i], ETH_ALEN - 2);
			i++;
			स_नकल(pci_info->mac + माप(u32), &cmd.rsp.arg[i], 2);
			i = i + 3;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(dev, "Failed to get PCI Info, error = %d\n", err);
		err = -EIO;
	पूर्ण

	ahw->total_nic_func = nic;
	ahw->total_pci_func = nic + fcoe + iscsi;
	अगर (ahw->total_nic_func == 0 || ahw->total_pci_func == 0) अणु
		dev_err(dev, "%s: Invalid function count: total nic func[%x], total pci func[%x]\n",
			__func__, ahw->total_nic_func, ahw->total_pci_func);
		err = -EIO;
	पूर्ण
	qlcnic_मुक्त_mbx_args(&cmd);

	वापस err;
पूर्ण

पूर्णांक qlcnic_83xx_config_पूर्णांकrpt(काष्ठा qlcnic_adapter *adapter, bool op_type)
अणु
	पूर्णांक i, index, err;
	u8 max_पूर्णांकs;
	u32 val, temp, type;
	काष्ठा qlcnic_cmd_args cmd;

	max_पूर्णांकs = adapter->ahw->num_msix - 1;
	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIG_INTRPT);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = max_पूर्णांकs;

	अगर (qlcnic_sriov_vf_check(adapter))
		cmd.req.arg[1] |= (adapter->ahw->pci_func << 8) | BIT_16;

	क्रम (i = 0, index = 2; i < max_पूर्णांकs; i++) अणु
		type = op_type ? QLCNIC_INTRPT_ADD : QLCNIC_INTRPT_DEL;
		val = type | (adapter->ahw->पूर्णांकr_tbl[i].type << 4);
		अगर (adapter->ahw->पूर्णांकr_tbl[i].type == QLCNIC_INTRPT_MSIX)
			val |= (adapter->ahw->पूर्णांकr_tbl[i].id << 16);
		cmd.req.arg[index++] = val;
	पूर्ण
	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to configure interrupts 0x%x\n", err);
		जाओ out;
	पूर्ण

	max_पूर्णांकs = cmd.rsp.arg[1];
	क्रम (i = 0, index = 2; i < max_पूर्णांकs; i++, index += 2) अणु
		val = cmd.rsp.arg[index];
		अगर (LSB(val)) अणु
			dev_info(&adapter->pdev->dev,
				 "Can't configure interrupt %d\n",
				 adapter->ahw->पूर्णांकr_tbl[i].id);
			जारी;
		पूर्ण
		अगर (op_type) अणु
			adapter->ahw->पूर्णांकr_tbl[i].id = MSW(val);
			adapter->ahw->पूर्णांकr_tbl[i].enabled = 1;
			temp = cmd.rsp.arg[index + 1];
			adapter->ahw->पूर्णांकr_tbl[i].src = temp;
		पूर्ण अन्यथा अणु
			adapter->ahw->पूर्णांकr_tbl[i].id = i;
			adapter->ahw->पूर्णांकr_tbl[i].enabled = 0;
			adapter->ahw->पूर्णांकr_tbl[i].src = 0;
		पूर्ण
	पूर्ण
out:
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस err;
पूर्ण

पूर्णांक qlcnic_83xx_lock_flash(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक id, समयout = 0;
	u32 status = 0;

	जबतक (status == 0) अणु
		status = QLC_SHARED_REG_RD32(adapter, QLCNIC_FLASH_LOCK);
		अगर (status)
			अवरोध;

		अगर (++समयout >= QLC_83XX_FLASH_LOCK_TIMEOUT) अणु
			id = QLC_SHARED_REG_RD32(adapter,
						 QLCNIC_FLASH_LOCK_OWNER);
			dev_err(&adapter->pdev->dev,
				"%s: failed, lock held by %d\n", __func__, id);
			वापस -EIO;
		पूर्ण
		usleep_range(1000, 2000);
	पूर्ण

	QLC_SHARED_REG_WR32(adapter, QLCNIC_FLASH_LOCK_OWNER, adapter->portnum);
	वापस 0;
पूर्ण

व्योम qlcnic_83xx_unlock_flash(काष्ठा qlcnic_adapter *adapter)
अणु
	QLC_SHARED_REG_RD32(adapter, QLCNIC_FLASH_UNLOCK);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_FLASH_LOCK_OWNER, 0xFF);
पूर्ण

पूर्णांक qlcnic_83xx_lockless_flash_पढ़ो32(काष्ठा qlcnic_adapter *adapter,
				      u32 flash_addr, u8 *p_data,
				      पूर्णांक count)
अणु
	u32 word, range, flash_offset, addr = flash_addr, ret;
	uदीर्घ indirect_add, direct_winकरोw;
	पूर्णांक i, err = 0;

	flash_offset = addr & (QLCNIC_FLASH_SECTOR_SIZE - 1);
	अगर (addr & 0x3) अणु
		dev_err(&adapter->pdev->dev, "Illegal addr = 0x%x\n", addr);
		वापस -EIO;
	पूर्ण

	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_सूचीECT_WINDOW,
				     (addr & 0xFFFF0000));

	range = flash_offset + (count * माप(u32));
	/* Check अगर data is spपढ़ो across multiple sectors */
	अगर (range > (QLCNIC_FLASH_SECTOR_SIZE - 1)) अणु

		/* Multi sector पढ़ो */
		क्रम (i = 0; i < count; i++) अणु
			indirect_add = QLC_83XX_FLASH_सूचीECT_DATA(addr);
			ret = QLCRD32(adapter, indirect_add, &err);
			अगर (err == -EIO)
				वापस err;

			word = ret;
			*(u32 *)p_data  = word;
			p_data = p_data + 4;
			addr = addr + 4;
			flash_offset = flash_offset + 4;

			अगर (flash_offset > (QLCNIC_FLASH_SECTOR_SIZE - 1)) अणु
				direct_winकरोw = QLC_83XX_FLASH_सूचीECT_WINDOW;
				/* This ग_लिखो is needed once क्रम each sector */
				qlcnic_83xx_wrt_reg_indirect(adapter,
							     direct_winकरोw,
							     (addr));
				flash_offset = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Single sector पढ़ो */
		क्रम (i = 0; i < count; i++) अणु
			indirect_add = QLC_83XX_FLASH_सूचीECT_DATA(addr);
			ret = QLCRD32(adapter, indirect_add, &err);
			अगर (err == -EIO)
				वापस err;

			word = ret;
			*(u32 *)p_data  = word;
			p_data = p_data + 4;
			addr = addr + 4;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_poll_flash_status_reg(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 status;
	पूर्णांक retries = QLC_83XX_FLASH_READ_RETRY_COUNT;
	पूर्णांक err = 0;

	करो अणु
		status = QLCRD32(adapter, QLC_83XX_FLASH_STATUS, &err);
		अगर (err == -EIO)
			वापस err;

		अगर ((status & QLC_83XX_FLASH_STATUS_READY) ==
		    QLC_83XX_FLASH_STATUS_READY)
			अवरोध;

		usleep_range(1000, 1100);
	पूर्ण जबतक (--retries);

	अगर (!retries)
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक qlcnic_83xx_enable_flash_ग_लिखो(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ret;
	u32 cmd;
	cmd = adapter->ahw->fdt.ग_लिखो_statusreg_cmd;
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR,
				     (QLC_83XX_FLASH_FDT_WRITE_DEF_SIG | cmd));
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_WRDATA,
				     adapter->ahw->fdt.ग_लिखो_enable_bits);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_CONTROL,
				     QLC_83XX_FLASH_SECOND_ERASE_MS_VAL);
	ret = qlcnic_83xx_poll_flash_status_reg(adapter);
	अगर (ret)
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक qlcnic_83xx_disable_flash_ग_लिखो(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ret;

	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR,
				     (QLC_83XX_FLASH_FDT_WRITE_DEF_SIG |
				     adapter->ahw->fdt.ग_लिखो_statusreg_cmd));
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_WRDATA,
				     adapter->ahw->fdt.ग_लिखो_disable_bits);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_CONTROL,
				     QLC_83XX_FLASH_SECOND_ERASE_MS_VAL);
	ret = qlcnic_83xx_poll_flash_status_reg(adapter);
	अगर (ret)
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक qlcnic_83xx_पढ़ो_flash_mfg_id(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ret, err = 0;
	u32 mfg_id;

	अगर (qlcnic_83xx_lock_flash(adapter))
		वापस -EIO;

	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR,
				     QLC_83XX_FLASH_FDT_READ_MFG_ID_VAL);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_CONTROL,
				     QLC_83XX_FLASH_READ_CTRL);
	ret = qlcnic_83xx_poll_flash_status_reg(adapter);
	अगर (ret) अणु
		qlcnic_83xx_unlock_flash(adapter);
		वापस -EIO;
	पूर्ण

	mfg_id = QLCRD32(adapter, QLC_83XX_FLASH_RDDATA, &err);
	अगर (err == -EIO) अणु
		qlcnic_83xx_unlock_flash(adapter);
		वापस err;
	पूर्ण

	adapter->flash_mfg_id = (mfg_id & 0xFF);
	qlcnic_83xx_unlock_flash(adapter);

	वापस 0;
पूर्ण

पूर्णांक qlcnic_83xx_पढ़ो_flash_descriptor_table(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक count, fdt_size, ret = 0;

	fdt_size = माप(काष्ठा qlcnic_fdt);
	count = fdt_size / माप(u32);

	अगर (qlcnic_83xx_lock_flash(adapter))
		वापस -EIO;

	स_रखो(&adapter->ahw->fdt, 0, fdt_size);
	ret = qlcnic_83xx_lockless_flash_पढ़ो32(adapter, QLCNIC_FDT_LOCATION,
						(u8 *)&adapter->ahw->fdt,
						count);
	qlcnic_swap32_buffer((u32 *)&adapter->ahw->fdt, count);
	qlcnic_83xx_unlock_flash(adapter);
	वापस ret;
पूर्ण

पूर्णांक qlcnic_83xx_erase_flash_sector(काष्ठा qlcnic_adapter *adapter,
				   u32 sector_start_addr)
अणु
	u32 reversed_addr, addr1, addr2, cmd;
	पूर्णांक ret = -EIO;

	अगर (qlcnic_83xx_lock_flash(adapter) != 0)
		वापस -EIO;

	अगर (adapter->ahw->fdt.mfg_id == adapter->flash_mfg_id) अणु
		ret = qlcnic_83xx_enable_flash_ग_लिखो(adapter);
		अगर (ret) अणु
			qlcnic_83xx_unlock_flash(adapter);
			dev_err(&adapter->pdev->dev,
				"%s failed at %d\n",
				__func__, __LINE__);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = qlcnic_83xx_poll_flash_status_reg(adapter);
	अगर (ret) अणु
		qlcnic_83xx_unlock_flash(adapter);
		dev_err(&adapter->pdev->dev,
			"%s: failed at %d\n", __func__, __LINE__);
		वापस -EIO;
	पूर्ण

	addr1 = (sector_start_addr & 0xFF) << 16;
	addr2 = (sector_start_addr & 0xFF0000) >> 16;
	reversed_addr = addr1 | addr2 | (sector_start_addr & 0xFF00);

	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_WRDATA,
				     reversed_addr);
	cmd = QLC_83XX_FLASH_FDT_ERASE_DEF_SIG | adapter->ahw->fdt.erase_cmd;
	अगर (adapter->ahw->fdt.mfg_id == adapter->flash_mfg_id)
		qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR, cmd);
	अन्यथा
		qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR,
					     QLC_83XX_FLASH_OEM_ERASE_SIG);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_CONTROL,
				     QLC_83XX_FLASH_LAST_ERASE_MS_VAL);

	ret = qlcnic_83xx_poll_flash_status_reg(adapter);
	अगर (ret) अणु
		qlcnic_83xx_unlock_flash(adapter);
		dev_err(&adapter->pdev->dev,
			"%s: failed at %d\n", __func__, __LINE__);
		वापस -EIO;
	पूर्ण

	अगर (adapter->ahw->fdt.mfg_id == adapter->flash_mfg_id) अणु
		ret = qlcnic_83xx_disable_flash_ग_लिखो(adapter);
		अगर (ret) अणु
			qlcnic_83xx_unlock_flash(adapter);
			dev_err(&adapter->pdev->dev,
				"%s: failed at %d\n", __func__, __LINE__);
			वापस ret;
		पूर्ण
	पूर्ण

	qlcnic_83xx_unlock_flash(adapter);

	वापस 0;
पूर्ण

पूर्णांक qlcnic_83xx_flash_ग_लिखो32(काष्ठा qlcnic_adapter *adapter, u32 addr,
			      u32 *p_data)
अणु
	पूर्णांक ret = -EIO;
	u32 addr1 = 0x00800000 | (addr >> 2);

	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR, addr1);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_WRDATA, *p_data);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_CONTROL,
				     QLC_83XX_FLASH_LAST_ERASE_MS_VAL);
	ret = qlcnic_83xx_poll_flash_status_reg(adapter);
	अगर (ret) अणु
		dev_err(&adapter->pdev->dev,
			"%s: failed at %d\n", __func__, __LINE__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qlcnic_83xx_flash_bulk_ग_लिखो(काष्ठा qlcnic_adapter *adapter, u32 addr,
				 u32 *p_data, पूर्णांक count)
अणु
	u32 temp;
	पूर्णांक ret = -EIO, err = 0;

	अगर ((count < QLC_83XX_FLASH_WRITE_MIN) ||
	    (count > QLC_83XX_FLASH_WRITE_MAX)) अणु
		dev_err(&adapter->pdev->dev,
			"%s: Invalid word count\n", __func__);
		वापस -EIO;
	पूर्ण

	temp = QLCRD32(adapter, QLC_83XX_FLASH_SPI_CONTROL, &err);
	अगर (err == -EIO)
		वापस err;

	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_SPI_CONTROL,
				     (temp | QLC_83XX_FLASH_SPI_CTRL));
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR,
				     QLC_83XX_FLASH_ADDR_TEMP_VAL);

	/* First DWORD ग_लिखो */
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_WRDATA, *p_data++);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_CONTROL,
				     QLC_83XX_FLASH_FIRST_MS_PATTERN);
	ret = qlcnic_83xx_poll_flash_status_reg(adapter);
	अगर (ret) अणु
		dev_err(&adapter->pdev->dev,
			"%s: failed at %d\n", __func__, __LINE__);
		वापस -EIO;
	पूर्ण

	count--;
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR,
				     QLC_83XX_FLASH_ADDR_SECOND_TEMP_VAL);
	/* Second to N-1 DWORD ग_लिखोs */
	जबतक (count != 1) अणु
		qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_WRDATA,
					     *p_data++);
		qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_CONTROL,
					     QLC_83XX_FLASH_SECOND_MS_PATTERN);
		ret = qlcnic_83xx_poll_flash_status_reg(adapter);
		अगर (ret) अणु
			dev_err(&adapter->pdev->dev,
				"%s: failed at %d\n", __func__, __LINE__);
			वापस -EIO;
		पूर्ण
		count--;
	पूर्ण

	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR,
				     QLC_83XX_FLASH_ADDR_TEMP_VAL |
				     (addr >> 2));
	/* Last DWORD ग_लिखो */
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_WRDATA, *p_data++);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_CONTROL,
				     QLC_83XX_FLASH_LAST_MS_PATTERN);
	ret = qlcnic_83xx_poll_flash_status_reg(adapter);
	अगर (ret) अणु
		dev_err(&adapter->pdev->dev,
			"%s: failed at %d\n", __func__, __LINE__);
		वापस -EIO;
	पूर्ण

	ret = QLCRD32(adapter, QLC_83XX_FLASH_SPI_STATUS, &err);
	अगर (err == -EIO)
		वापस err;

	अगर ((ret & QLC_83XX_FLASH_SPI_CTRL) == QLC_83XX_FLASH_SPI_CTRL) अणु
		dev_err(&adapter->pdev->dev, "%s: failed at %d\n",
			__func__, __LINE__);
		/* Operation failed, clear error bit */
		temp = QLCRD32(adapter, QLC_83XX_FLASH_SPI_CONTROL, &err);
		अगर (err == -EIO)
			वापस err;

		qlcnic_83xx_wrt_reg_indirect(adapter,
					     QLC_83XX_FLASH_SPI_CONTROL,
					     (temp | QLC_83XX_FLASH_SPI_CTRL));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qlcnic_83xx_recover_driver_lock(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 val, id;

	val = QLCRDX(adapter->ahw, QLC_83XX_RECOVER_DRV_LOCK);

	/* Check अगर recovery need to be perक्रमmed by the calling function */
	अगर ((val & QLC_83XX_DRV_LOCK_RECOVERY_STATUS_MASK) == 0) अणु
		val = val & ~0x3F;
		val = val | ((adapter->portnum << 2) |
			     QLC_83XX_NEED_DRV_LOCK_RECOVERY);
		QLCWRX(adapter->ahw, QLC_83XX_RECOVER_DRV_LOCK, val);
		dev_info(&adapter->pdev->dev,
			 "%s: lock recovery initiated\n", __func__);
		msleep(QLC_83XX_DRV_LOCK_RECOVERY_DELAY);
		val = QLCRDX(adapter->ahw, QLC_83XX_RECOVER_DRV_LOCK);
		id = ((val >> 2) & 0xF);
		अगर (id == adapter->portnum) अणु
			val = val & ~QLC_83XX_DRV_LOCK_RECOVERY_STATUS_MASK;
			val = val | QLC_83XX_DRV_LOCK_RECOVERY_IN_PROGRESS;
			QLCWRX(adapter->ahw, QLC_83XX_RECOVER_DRV_LOCK, val);
			/* Force release the lock */
			QLCRDX(adapter->ahw, QLC_83XX_DRV_UNLOCK);
			/* Clear recovery bits */
			val = val & ~0x3F;
			QLCWRX(adapter->ahw, QLC_83XX_RECOVER_DRV_LOCK, val);
			dev_info(&adapter->pdev->dev,
				 "%s: lock recovery completed\n", __func__);
		पूर्ण अन्यथा अणु
			dev_info(&adapter->pdev->dev,
				 "%s: func %d to resume lock recovery process\n",
				 __func__, id);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(&adapter->pdev->dev,
			 "%s: lock recovery initiated by other functions\n",
			 __func__);
	पूर्ण
पूर्ण

पूर्णांक qlcnic_83xx_lock_driver(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 lock_alive_counter, val, id, i = 0, status = 0, temp = 0;
	पूर्णांक max_attempt = 0;

	जबतक (status == 0) अणु
		status = QLCRDX(adapter->ahw, QLC_83XX_DRV_LOCK);
		अगर (status)
			अवरोध;

		msleep(QLC_83XX_DRV_LOCK_WAIT_DELAY);
		i++;

		अगर (i == 1)
			temp = QLCRDX(adapter->ahw, QLC_83XX_DRV_LOCK_ID);

		अगर (i == QLC_83XX_DRV_LOCK_WAIT_COUNTER) अणु
			val = QLCRDX(adapter->ahw, QLC_83XX_DRV_LOCK_ID);
			अगर (val == temp) अणु
				id = val & 0xFF;
				dev_info(&adapter->pdev->dev,
					 "%s: lock to be recovered from %d\n",
					 __func__, id);
				qlcnic_83xx_recover_driver_lock(adapter);
				i = 0;
				max_attempt++;
			पूर्ण अन्यथा अणु
				dev_err(&adapter->pdev->dev,
					"%s: failed to get lock\n", __func__);
				वापस -EIO;
			पूर्ण
		पूर्ण

		/* Force निकास from जबतक loop after few attempts */
		अगर (max_attempt == QLC_83XX_MAX_DRV_LOCK_RECOVERY_ATTEMPT) अणु
			dev_err(&adapter->pdev->dev,
				"%s: failed to get lock\n", __func__);
			वापस -EIO;
		पूर्ण
	पूर्ण

	val = QLCRDX(adapter->ahw, QLC_83XX_DRV_LOCK_ID);
	lock_alive_counter = val >> 8;
	lock_alive_counter++;
	val = lock_alive_counter << 8 | adapter->portnum;
	QLCWRX(adapter->ahw, QLC_83XX_DRV_LOCK_ID, val);

	वापस 0;
पूर्ण

व्योम qlcnic_83xx_unlock_driver(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 val, lock_alive_counter, id;

	val = QLCRDX(adapter->ahw, QLC_83XX_DRV_LOCK_ID);
	id = val & 0xFF;
	lock_alive_counter = val >> 8;

	अगर (id != adapter->portnum)
		dev_err(&adapter->pdev->dev,
			"%s:Warning func %d is unlocking lock owned by %d\n",
			__func__, adapter->portnum, id);

	val = (lock_alive_counter << 8) | 0xFF;
	QLCWRX(adapter->ahw, QLC_83XX_DRV_LOCK_ID, val);
	QLCRDX(adapter->ahw, QLC_83XX_DRV_UNLOCK);
पूर्ण

पूर्णांक qlcnic_ms_mem_ग_लिखो128(काष्ठा qlcnic_adapter *adapter, u64 addr,
				u32 *data, u32 count)
अणु
	पूर्णांक i, j, ret = 0;
	u32 temp;

	/* Check alignment */
	अगर (addr & 0xF)
		वापस -EIO;

	mutex_lock(&adapter->ahw->mem_lock);
	qlcnic_ind_wr(adapter, QLCNIC_MS_ADDR_HI, 0);

	क्रम (i = 0; i < count; i++, addr += 16) अणु
		अगर (!((ADDR_IN_RANGE(addr, QLCNIC_ADDR_QDR_NET,
				     QLCNIC_ADDR_QDR_NET_MAX)) ||
		      (ADDR_IN_RANGE(addr, QLCNIC_ADDR_DDR_NET,
				     QLCNIC_ADDR_DDR_NET_MAX)))) अणु
			mutex_unlock(&adapter->ahw->mem_lock);
			वापस -EIO;
		पूर्ण

		qlcnic_ind_wr(adapter, QLCNIC_MS_ADDR_LO, addr);
		qlcnic_ind_wr(adapter, QLCNIC_MS_WRTDATA_LO, *data++);
		qlcnic_ind_wr(adapter, QLCNIC_MS_WRTDATA_HI, *data++);
		qlcnic_ind_wr(adapter, QLCNIC_MS_WRTDATA_ULO, *data++);
		qlcnic_ind_wr(adapter, QLCNIC_MS_WRTDATA_UHI, *data++);
		qlcnic_ind_wr(adapter, QLCNIC_MS_CTRL, QLCNIC_TA_WRITE_ENABLE);
		qlcnic_ind_wr(adapter, QLCNIC_MS_CTRL, QLCNIC_TA_WRITE_START);

		क्रम (j = 0; j < MAX_CTL_CHECK; j++) अणु
			temp = qlcnic_ind_rd(adapter, QLCNIC_MS_CTRL);

			अगर ((temp & TA_CTL_BUSY) == 0)
				अवरोध;
		पूर्ण

		/* Status check failure */
		अगर (j >= MAX_CTL_CHECK) अणु
			prपूर्णांकk_ratelimited(KERN_WARNING
					   "MS memory write failed\n");
			mutex_unlock(&adapter->ahw->mem_lock);
			वापस -EIO;
		पूर्ण
	पूर्ण

	mutex_unlock(&adapter->ahw->mem_lock);

	वापस ret;
पूर्ण

पूर्णांक qlcnic_83xx_flash_पढ़ो32(काष्ठा qlcnic_adapter *adapter, u32 flash_addr,
			     u8 *p_data, पूर्णांक count)
अणु
	u32 word, addr = flash_addr, ret;
	uदीर्घ  indirect_addr;
	पूर्णांक i, err = 0;

	अगर (qlcnic_83xx_lock_flash(adapter) != 0)
		वापस -EIO;

	अगर (addr & 0x3) अणु
		dev_err(&adapter->pdev->dev, "Illegal addr = 0x%x\n", addr);
		qlcnic_83xx_unlock_flash(adapter);
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		अगर (qlcnic_83xx_wrt_reg_indirect(adapter,
						 QLC_83XX_FLASH_सूचीECT_WINDOW,
						 (addr))) अणु
			qlcnic_83xx_unlock_flash(adapter);
			वापस -EIO;
		पूर्ण

		indirect_addr = QLC_83XX_FLASH_सूचीECT_DATA(addr);
		ret = QLCRD32(adapter, indirect_addr, &err);
		अगर (err == -EIO)
			वापस err;

		word = ret;
		*(u32 *)p_data  = word;
		p_data = p_data + 4;
		addr = addr + 4;
	पूर्ण

	qlcnic_83xx_unlock_flash(adapter);

	वापस 0;
पूर्ण

व्योम qlcnic_83xx_get_port_type(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_cmd_args cmd;
	u32 config;
	पूर्णांक err;

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_LINK_STATUS);
	अगर (err)
		वापस;

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_info(&adapter->pdev->dev,
			 "Get Link Status Command failed: 0x%x\n", err);
		जाओ out;
	पूर्ण अन्यथा अणु
		config = cmd.rsp.arg[3];

		चयन (QLC_83XX_SFP_MODULE_TYPE(config)) अणु
		हाल QLC_83XX_MODULE_FIBRE_1000BASE_SX:
		हाल QLC_83XX_MODULE_FIBRE_1000BASE_LX:
		हाल QLC_83XX_MODULE_FIBRE_1000BASE_CX:
		हाल QLC_83XX_MODULE_TP_1000BASE_T:
			ahw->port_type = QLCNIC_GBE;
			अवरोध;
		शेष:
			ahw->port_type = QLCNIC_XGBE;
		पूर्ण
	पूर्ण
out:
	qlcnic_मुक्त_mbx_args(&cmd);
पूर्ण

पूर्णांक qlcnic_83xx_test_link(काष्ठा qlcnic_adapter *adapter)
अणु
	u8 pci_func;
	पूर्णांक err;
	u32 config = 0, state;
	काष्ठा qlcnic_cmd_args cmd;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	अगर (qlcnic_sriov_vf_check(adapter))
		pci_func = adapter->portnum;
	अन्यथा
		pci_func = ahw->pci_func;

	state = पढ़ोl(ahw->pci_base0 + QLC_83XX_LINK_STATE(pci_func));
	अगर (!QLC_83xx_FUNC_VAL(state, pci_func)) अणु
		dev_info(&adapter->pdev->dev, "link state down\n");
		वापस config;
	पूर्ण

	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_LINK_STATUS);
	अगर (err)
		वापस err;

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		dev_info(&adapter->pdev->dev,
			 "Get Link Status Command failed: 0x%x\n", err);
		जाओ out;
	पूर्ण अन्यथा अणु
		config = cmd.rsp.arg[1];
		चयन (QLC_83XX_CURRENT_LINK_SPEED(config)) अणु
		हाल QLC_83XX_10M_LINK:
			ahw->link_speed = SPEED_10;
			अवरोध;
		हाल QLC_83XX_100M_LINK:
			ahw->link_speed = SPEED_100;
			अवरोध;
		हाल QLC_83XX_1G_LINK:
			ahw->link_speed = SPEED_1000;
			अवरोध;
		हाल QLC_83XX_10G_LINK:
			ahw->link_speed = SPEED_10000;
			अवरोध;
		शेष:
			ahw->link_speed = 0;
			अवरोध;
		पूर्ण
		config = cmd.rsp.arg[3];
		चयन (QLC_83XX_SFP_MODULE_TYPE(config)) अणु
		हाल QLC_83XX_MODULE_FIBRE_10GBASE_LRM:
		हाल QLC_83XX_MODULE_FIBRE_10GBASE_LR:
		हाल QLC_83XX_MODULE_FIBRE_10GBASE_SR:
			ahw->supported_type = PORT_FIBRE;
			ahw->port_type = QLCNIC_XGBE;
			अवरोध;
		हाल QLC_83XX_MODULE_FIBRE_1000BASE_SX:
		हाल QLC_83XX_MODULE_FIBRE_1000BASE_LX:
		हाल QLC_83XX_MODULE_FIBRE_1000BASE_CX:
			ahw->supported_type = PORT_FIBRE;
			ahw->port_type = QLCNIC_GBE;
			अवरोध;
		हाल QLC_83XX_MODULE_TP_1000BASE_T:
			ahw->supported_type = PORT_TP;
			ahw->port_type = QLCNIC_GBE;
			अवरोध;
		हाल QLC_83XX_MODULE_DA_10GE_PASSIVE_CP:
		हाल QLC_83XX_MODULE_DA_10GE_ACTIVE_CP:
		हाल QLC_83XX_MODULE_DA_10GE_LEGACY_CP:
		हाल QLC_83XX_MODULE_DA_1GE_PASSIVE_CP:
			ahw->supported_type = PORT_DA;
			ahw->port_type = QLCNIC_XGBE;
			अवरोध;
		शेष:
			ahw->supported_type = PORT_OTHER;
			ahw->port_type = QLCNIC_XGBE;
		पूर्ण
		अगर (config & 1)
			err = 1;
	पूर्ण
out:
	qlcnic_मुक्त_mbx_args(&cmd);
	वापस config;
पूर्ण

पूर्णांक qlcnic_83xx_get_link_ksettings(काष्ठा qlcnic_adapter *adapter,
				   काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u32 config = 0;
	पूर्णांक status = 0;
	u32 supported, advertising;

	अगर (!test_bit(__QLCNIC_MAINTEन_अंकCE_MODE, &adapter->state)) अणु
		/* Get port configuration info */
		status = qlcnic_83xx_get_port_info(adapter);
		/* Get Link Status related info */
		config = qlcnic_83xx_test_link(adapter);
		ahw->module_type = QLC_83XX_SFP_MODULE_TYPE(config);
	पूर्ण

	/* hard code until there is a way to get it from flash */
	ahw->board_type = QLCNIC_BRDTYPE_83XX_10G;

	अगर (netअगर_running(adapter->netdev) && ahw->has_link_events) अणु
		ecmd->base.speed = ahw->link_speed;
		ecmd->base.duplex = ahw->link_duplex;
		ecmd->base.स्वतःneg = ahw->link_स्वतःneg;
	पूर्ण अन्यथा अणु
		ecmd->base.speed = SPEED_UNKNOWN;
		ecmd->base.duplex = DUPLEX_UNKNOWN;
		ecmd->base.स्वतःneg = AUTONEG_DISABLE;
	पूर्ण

	supported = (SUPPORTED_10baseT_Full |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_10000baseT_Full |
			   SUPPORTED_Autoneg);

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						ecmd->link_modes.advertising);

	अगर (ecmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (ahw->port_config & QLC_83XX_10_CAPABLE)
			advertising |= SUPPORTED_10baseT_Full;
		अगर (ahw->port_config & QLC_83XX_100_CAPABLE)
			advertising |= SUPPORTED_100baseT_Full;
		अगर (ahw->port_config & QLC_83XX_1G_CAPABLE)
			advertising |= SUPPORTED_1000baseT_Full;
		अगर (ahw->port_config & QLC_83XX_10G_CAPABLE)
			advertising |= SUPPORTED_10000baseT_Full;
		अगर (ahw->port_config & QLC_83XX_AUTONEG_ENABLE)
			advertising |= ADVERTISED_Autoneg;
	पूर्ण अन्यथा अणु
		चयन (ahw->link_speed) अणु
		हाल SPEED_10:
			advertising = SUPPORTED_10baseT_Full;
			अवरोध;
		हाल SPEED_100:
			advertising = SUPPORTED_100baseT_Full;
			अवरोध;
		हाल SPEED_1000:
			advertising = SUPPORTED_1000baseT_Full;
			अवरोध;
		हाल SPEED_10000:
			advertising = SUPPORTED_10000baseT_Full;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

	पूर्ण

	चयन (ahw->supported_type) अणु
	हाल PORT_FIBRE:
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		ecmd->base.port = PORT_FIBRE;
		अवरोध;
	हाल PORT_TP:
		supported |= SUPPORTED_TP;
		advertising |= ADVERTISED_TP;
		ecmd->base.port = PORT_TP;
		अवरोध;
	हाल PORT_DA:
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		ecmd->base.port = PORT_DA;
		अवरोध;
	शेष:
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		ecmd->base.port = PORT_OTHER;
		अवरोध;
	पूर्ण
	ecmd->base.phy_address = ahw->physical_port;

	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.advertising,
						advertising);

	वापस status;
पूर्ण

पूर्णांक qlcnic_83xx_set_link_ksettings(काष्ठा qlcnic_adapter *adapter,
				   स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u32 config = adapter->ahw->port_config;
	पूर्णांक status = 0;

	/* 83xx devices करो not support Half duplex */
	अगर (ecmd->base.duplex == DUPLEX_HALF) अणु
		netdev_info(adapter->netdev,
			    "Half duplex mode not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ecmd->base.स्वतःneg) अणु
		ahw->port_config |= QLC_83XX_AUTONEG_ENABLE;
		ahw->port_config |= (QLC_83XX_100_CAPABLE |
				     QLC_83XX_1G_CAPABLE |
				     QLC_83XX_10G_CAPABLE);
	पूर्ण अन्यथा अणु /* क्रमce speed */
		ahw->port_config &= ~QLC_83XX_AUTONEG_ENABLE;
		चयन (ecmd->base.speed) अणु
		हाल SPEED_10:
			ahw->port_config &= ~(QLC_83XX_100_CAPABLE |
					      QLC_83XX_1G_CAPABLE |
					      QLC_83XX_10G_CAPABLE);
			ahw->port_config |= QLC_83XX_10_CAPABLE;
			अवरोध;
		हाल SPEED_100:
			ahw->port_config &= ~(QLC_83XX_10_CAPABLE |
					      QLC_83XX_1G_CAPABLE |
					      QLC_83XX_10G_CAPABLE);
			ahw->port_config |= QLC_83XX_100_CAPABLE;
			अवरोध;
		हाल SPEED_1000:
			ahw->port_config &= ~(QLC_83XX_10_CAPABLE |
					      QLC_83XX_100_CAPABLE |
					      QLC_83XX_10G_CAPABLE);
			ahw->port_config |= QLC_83XX_1G_CAPABLE;
			अवरोध;
		हाल SPEED_10000:
			ahw->port_config &= ~(QLC_83XX_10_CAPABLE |
					      QLC_83XX_100_CAPABLE |
					      QLC_83XX_1G_CAPABLE);
			ahw->port_config |= QLC_83XX_10G_CAPABLE;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	status = qlcnic_83xx_set_port_config(adapter);
	अगर (status) अणु
		netdev_info(adapter->netdev,
			    "Failed to Set Link Speed and autoneg.\n");
		ahw->port_config = config;
	पूर्ण

	वापस status;
पूर्ण

अटल अंतरभूत u64 *qlcnic_83xx_copy_stats(काष्ठा qlcnic_cmd_args *cmd,
					  u64 *data, पूर्णांक index)
अणु
	u32 low, hi;
	u64 val;

	low = cmd->rsp.arg[index];
	hi = cmd->rsp.arg[index + 1];
	val = (((u64) low) | (((u64) hi) << 32));
	*data++ = val;
	वापस data;
पूर्ण

अटल u64 *qlcnic_83xx_fill_stats(काष्ठा qlcnic_adapter *adapter,
				   काष्ठा qlcnic_cmd_args *cmd, u64 *data,
				   पूर्णांक type, पूर्णांक *ret)
अणु
	पूर्णांक err, k, total_regs;

	*ret = 0;
	err = qlcnic_issue_cmd(adapter, cmd);
	अगर (err != QLCNIC_RCODE_SUCCESS) अणु
		dev_info(&adapter->pdev->dev,
			 "Error in get statistics mailbox command\n");
		*ret = -EIO;
		वापस data;
	पूर्ण
	total_regs = cmd->rsp.num;
	चयन (type) अणु
	हाल QLC_83XX_STAT_MAC:
		/* fill in MAC tx counters */
		क्रम (k = 2; k < 28; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		/* skip 24 bytes of reserved area */
		/* fill in MAC rx counters */
		क्रम (k += 6; k < 60; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		/* skip 24 bytes of reserved area */
		/* fill in MAC rx frame stats */
		क्रम (k += 6; k < 80; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		/* fill in eSwitch stats */
		क्रम (; k < total_regs; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		अवरोध;
	हाल QLC_83XX_STAT_RX:
		क्रम (k = 2; k < 8; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		/* skip 8 bytes of reserved data */
		क्रम (k += 2; k < 24; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		/* skip 8 bytes containing RE1FBQ error data */
		क्रम (k += 2; k < total_regs; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		अवरोध;
	हाल QLC_83XX_STAT_TX:
		क्रम (k = 2; k < 10; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		/* skip 8 bytes of reserved data */
		क्रम (k += 2; k < total_regs; k += 2)
			data = qlcnic_83xx_copy_stats(cmd, data, k);
		अवरोध;
	शेष:
		dev_warn(&adapter->pdev->dev, "Unknown get statistics mode\n");
		*ret = -EIO;
	पूर्ण
	वापस data;
पूर्ण

व्योम qlcnic_83xx_get_stats(काष्ठा qlcnic_adapter *adapter, u64 *data)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक ret = 0;

	ret = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_STATISTICS);
	अगर (ret)
		वापस;
	/* Get Tx stats */
	cmd.req.arg[1] = BIT_1 | (adapter->tx_ring->ctx_id << 16);
	cmd.rsp.num = QLC_83XX_TX_STAT_REGS;
	data = qlcnic_83xx_fill_stats(adapter, &cmd, data,
				      QLC_83XX_STAT_TX, &ret);
	अगर (ret) अणु
		netdev_err(netdev, "Error getting Tx stats\n");
		जाओ out;
	पूर्ण
	/* Get MAC stats */
	cmd.req.arg[1] = BIT_2 | (adapter->portnum << 16);
	cmd.rsp.num = QLC_83XX_MAC_STAT_REGS;
	स_रखो(cmd.rsp.arg, 0, माप(u32) * cmd.rsp.num);
	data = qlcnic_83xx_fill_stats(adapter, &cmd, data,
				      QLC_83XX_STAT_MAC, &ret);
	अगर (ret) अणु
		netdev_err(netdev, "Error getting MAC stats\n");
		जाओ out;
	पूर्ण
	/* Get Rx stats */
	cmd.req.arg[1] = adapter->recv_ctx->context_id << 16;
	cmd.rsp.num = QLC_83XX_RX_STAT_REGS;
	स_रखो(cmd.rsp.arg, 0, माप(u32) * cmd.rsp.num);
	data = qlcnic_83xx_fill_stats(adapter, &cmd, data,
				      QLC_83XX_STAT_RX, &ret);
	अगर (ret)
		netdev_err(netdev, "Error getting Rx stats\n");
out:
	qlcnic_मुक्त_mbx_args(&cmd);
पूर्ण

#घोषणा QLCNIC_83XX_ADD_PORT0		BIT_0
#घोषणा QLCNIC_83XX_ADD_PORT1		BIT_1
#घोषणा QLCNIC_83XX_EXTENDED_MEM_SIZE	13 /* In MB */
पूर्णांक qlcnic_83xx_extend_md_capab(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक err;

	err = qlcnic_alloc_mbx_args(&cmd, adapter,
				    QLCNIC_CMD_83XX_EXTEND_ISCSI_DUMP_CAP);
	अगर (err)
		वापस err;

	cmd.req.arg[1] = (QLCNIC_83XX_ADD_PORT0 | QLCNIC_83XX_ADD_PORT1);
	cmd.req.arg[2] = QLCNIC_83XX_EXTENDED_MEM_SIZE;
	cmd.req.arg[3] = QLCNIC_83XX_EXTENDED_MEM_SIZE;

	err = qlcnic_issue_cmd(adapter, &cmd);
	अगर (err)
		dev_err(&adapter->pdev->dev,
			"failed to issue extend iSCSI minidump capability\n");

	वापस err;
पूर्ण

पूर्णांक qlcnic_83xx_reg_test(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 major, minor, sub;

	major = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_MAJOR);
	minor = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_MINOR);
	sub = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_SUB);

	अगर (adapter->fw_version != QLCNIC_VERSION_CODE(major, minor, sub)) अणु
		dev_info(&adapter->pdev->dev, "%s: Reg test failed\n",
			 __func__);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अंतरभूत पूर्णांक qlcnic_83xx_get_regs_len(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस (ARRAY_SIZE(qlcnic_83xx_ext_reg_tbl) *
		माप(*adapter->ahw->ext_reg_tbl)) +
		(ARRAY_SIZE(qlcnic_83xx_reg_tbl) *
		माप(*adapter->ahw->reg_tbl));
पूर्ण

पूर्णांक qlcnic_83xx_get_रेजिस्टरs(काष्ठा qlcnic_adapter *adapter, u32 *regs_buff)
अणु
	पूर्णांक i, j = 0;

	क्रम (i = QLCNIC_DEV_INFO_SIZE + 1;
	     j < ARRAY_SIZE(qlcnic_83xx_reg_tbl); i++, j++)
		regs_buff[i] = QLC_SHARED_REG_RD32(adapter, j);

	क्रम (j = 0; j < ARRAY_SIZE(qlcnic_83xx_ext_reg_tbl); j++)
		regs_buff[i++] = QLCRDX(adapter->ahw, j);
	वापस i;
पूर्ण

पूर्णांक qlcnic_83xx_पूर्णांकerrupt_test(काष्ठा net_device *netdev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_cmd_args cmd;
	u8 val, drv_sds_rings = adapter->drv_sds_rings;
	u8 drv_tx_rings = adapter->drv_tx_rings;
	u32 data;
	u16 पूर्णांकrpt_id, id;
	पूर्णांक ret;

	अगर (test_bit(__QLCNIC_RESETTING, &adapter->state)) अणु
		netdev_info(netdev, "Device is resetting\n");
		वापस -EBUSY;
	पूर्ण

	अगर (qlcnic_get_diag_lock(adapter)) अणु
		netdev_info(netdev, "Device in diagnostics mode\n");
		वापस -EBUSY;
	पूर्ण

	ret = qlcnic_83xx_diag_alloc_res(netdev, QLCNIC_INTERRUPT_TEST,
					 drv_sds_rings);
	अगर (ret)
		जाओ fail_diag_irq;

	ahw->diag_cnt = 0;
	ret = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_INTRPT_TEST);
	अगर (ret)
		जाओ fail_mbx_args;

	अगर (adapter->flags & QLCNIC_MSIX_ENABLED)
		पूर्णांकrpt_id = ahw->पूर्णांकr_tbl[0].id;
	अन्यथा
		पूर्णांकrpt_id = QLCRDX(ahw, QLCNIC_DEF_INT_ID);

	cmd.req.arg[1] = 1;
	cmd.req.arg[2] = पूर्णांकrpt_id;
	cmd.req.arg[3] = BIT_0;

	ret = qlcnic_issue_cmd(adapter, &cmd);
	data = cmd.rsp.arg[2];
	id = LSW(data);
	val = LSB(MSW(data));
	अगर (id != पूर्णांकrpt_id)
		dev_info(&adapter->pdev->dev,
			 "Interrupt generated: 0x%x, requested:0x%x\n",
			 id, पूर्णांकrpt_id);
	अगर (val)
		dev_err(&adapter->pdev->dev,
			 "Interrupt test error: 0x%x\n", val);
	अगर (ret)
		जाओ करोne;

	msleep(20);
	ret = !ahw->diag_cnt;

करोne:
	qlcnic_मुक्त_mbx_args(&cmd);

fail_mbx_args:
	qlcnic_83xx_diag_मुक्त_res(netdev, drv_sds_rings);

fail_diag_irq:
	adapter->drv_sds_rings = drv_sds_rings;
	adapter->drv_tx_rings = drv_tx_rings;
	qlcnic_release_diag_lock(adapter);
	वापस ret;
पूर्ण

व्योम qlcnic_83xx_get_छोड़ोparam(काष्ठा qlcnic_adapter *adapter,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक status = 0;
	u32 config;

	status = qlcnic_83xx_get_port_config(adapter);
	अगर (status) अणु
		dev_err(&adapter->pdev->dev,
			"%s: Get Pause Config failed\n", __func__);
		वापस;
	पूर्ण
	config = ahw->port_config;
	अगर (config & QLC_83XX_CFG_STD_PAUSE) अणु
		चयन (MSW(config)) अणु
		हाल QLC_83XX_TX_PAUSE:
			छोड़ो->tx_छोड़ो = 1;
			अवरोध;
		हाल QLC_83XX_RX_PAUSE:
			छोड़ो->rx_छोड़ो = 1;
			अवरोध;
		हाल QLC_83XX_TX_RX_PAUSE:
		शेष:
			/* Backward compatibility क्रम existing
			 * flash definitions
			 */
			छोड़ो->tx_छोड़ो = 1;
			छोड़ो->rx_छोड़ो = 1;
		पूर्ण
	पूर्ण

	अगर (QLC_83XX_AUTONEG(config))
		छोड़ो->स्वतःneg = 1;
पूर्ण

पूर्णांक qlcnic_83xx_set_छोड़ोparam(काष्ठा qlcnic_adapter *adapter,
			       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक status = 0;
	u32 config;

	status = qlcnic_83xx_get_port_config(adapter);
	अगर (status) अणु
		dev_err(&adapter->pdev->dev,
			"%s: Get Pause Config failed.\n", __func__);
		वापस status;
	पूर्ण
	config = ahw->port_config;

	अगर (ahw->port_type == QLCNIC_GBE) अणु
		अगर (छोड़ो->स्वतःneg)
			ahw->port_config |= QLC_83XX_ENABLE_AUTONEG;
		अगर (!छोड़ो->स्वतःneg)
			ahw->port_config &= ~QLC_83XX_ENABLE_AUTONEG;
	पूर्ण अन्यथा अगर ((ahw->port_type == QLCNIC_XGBE) && (छोड़ो->स्वतःneg)) अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!(config & QLC_83XX_CFG_STD_PAUSE))
		ahw->port_config |= QLC_83XX_CFG_STD_PAUSE;

	अगर (छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो) अणु
		ahw->port_config |= QLC_83XX_CFG_STD_TX_RX_PAUSE;
	पूर्ण अन्यथा अगर (छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो) अणु
		ahw->port_config &= ~QLC_83XX_CFG_STD_TX_PAUSE;
		ahw->port_config |= QLC_83XX_CFG_STD_RX_PAUSE;
	पूर्ण अन्यथा अगर (छोड़ो->tx_छोड़ो && !छोड़ो->rx_छोड़ो) अणु
		ahw->port_config &= ~QLC_83XX_CFG_STD_RX_PAUSE;
		ahw->port_config |= QLC_83XX_CFG_STD_TX_PAUSE;
	पूर्ण अन्यथा अगर (!छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो) अणु
		ahw->port_config &= ~(QLC_83XX_CFG_STD_TX_RX_PAUSE |
				      QLC_83XX_CFG_STD_PAUSE);
	पूर्ण
	status = qlcnic_83xx_set_port_config(adapter);
	अगर (status) अणु
		dev_err(&adapter->pdev->dev,
			"%s: Set Pause Config failed.\n", __func__);
		ahw->port_config = config;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक qlcnic_83xx_पढ़ो_flash_status_reg(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ret, err = 0;
	u32 temp;

	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_ADDR,
				     QLC_83XX_FLASH_OEM_READ_SIG);
	qlcnic_83xx_wrt_reg_indirect(adapter, QLC_83XX_FLASH_CONTROL,
				     QLC_83XX_FLASH_READ_CTRL);
	ret = qlcnic_83xx_poll_flash_status_reg(adapter);
	अगर (ret)
		वापस -EIO;

	temp = QLCRD32(adapter, QLC_83XX_FLASH_RDDATA, &err);
	अगर (err == -EIO)
		वापस err;

	वापस temp & 0xFF;
पूर्ण

पूर्णांक qlcnic_83xx_flash_test(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक status;

	status = qlcnic_83xx_पढ़ो_flash_status_reg(adapter);
	अगर (status == -EIO) अणु
		dev_info(&adapter->pdev->dev, "%s: EEPROM test failed.\n",
			 __func__);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = adapter->netdev;

	netअगर_device_detach(netdev);
	qlcnic_cancel_idc_work(adapter);

	अगर (netअगर_running(netdev))
		qlcnic_करोwn(adapter, netdev);

	qlcnic_83xx_disable_mbx_पूर्णांकr(adapter);
	cancel_delayed_work_sync(&adapter->idc_aen_work);

	वापस pci_save_state(pdev);
पूर्ण

अटल पूर्णांक qlcnic_83xx_resume(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlc_83xx_idc *idc = &ahw->idc;
	पूर्णांक err = 0;

	err = qlcnic_83xx_idc_init(adapter);
	अगर (err)
		वापस err;

	अगर (ahw->nic_mode == QLCNIC_VNIC_MODE) अणु
		अगर (ahw->op_mode == QLCNIC_MGMT_FUNC) अणु
			qlcnic_83xx_set_vnic_opmode(adapter);
		पूर्ण अन्यथा अणु
			err = qlcnic_83xx_check_vnic_state(adapter);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	err = qlcnic_83xx_idc_reattach_driver(adapter);
	अगर (err)
		वापस err;

	qlcnic_schedule_work(adapter, qlcnic_83xx_idc_poll_dev_state,
			     idc->delay);
	वापस err;
पूर्ण

व्योम qlcnic_83xx_reinit_mbx_work(काष्ठा qlcnic_mailbox *mbx)
अणु
	reinit_completion(&mbx->completion);
	set_bit(QLC_83XX_MBX_READY, &mbx->status);
पूर्ण

व्योम qlcnic_83xx_मुक्त_mailbox(काष्ठा qlcnic_mailbox *mbx)
अणु
	अगर (!mbx)
		वापस;

	destroy_workqueue(mbx->work_q);
	kमुक्त(mbx);
पूर्ण

अटल अंतरभूत व्योम
qlcnic_83xx_notअगरy_cmd_completion(काष्ठा qlcnic_adapter *adapter,
				  काष्ठा qlcnic_cmd_args *cmd)
अणु
	atomic_set(&cmd->rsp_status, QLC_83XX_MBX_RESPONSE_ARRIVED);

	अगर (cmd->type == QLC_83XX_MBX_CMD_NO_WAIT) अणु
		qlcnic_मुक्त_mbx_args(cmd);
		kमुक्त(cmd);
		वापस;
	पूर्ण
	complete(&cmd->completion);
पूर्ण

अटल व्योम qlcnic_83xx_flush_mbx_queue(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_mailbox *mbx = adapter->ahw->mailbox;
	काष्ठा list_head *head = &mbx->cmd_q;
	काष्ठा qlcnic_cmd_args *cmd = शून्य;

	spin_lock_bh(&mbx->queue_lock);

	जबतक (!list_empty(head)) अणु
		cmd = list_entry(head->next, काष्ठा qlcnic_cmd_args, list);
		dev_info(&adapter->pdev->dev, "%s: Mailbox command 0x%x\n",
			 __func__, cmd->cmd_op);
		list_del(&cmd->list);
		mbx->num_cmds--;
		qlcnic_83xx_notअगरy_cmd_completion(adapter, cmd);
	पूर्ण

	spin_unlock_bh(&mbx->queue_lock);
पूर्ण

अटल पूर्णांक qlcnic_83xx_check_mbx_status(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_mailbox *mbx = ahw->mailbox;
	u32 host_mbx_ctrl;

	अगर (!test_bit(QLC_83XX_MBX_READY, &mbx->status))
		वापस -EBUSY;

	host_mbx_ctrl = QLCRDX(ahw, QLCNIC_HOST_MBX_CTRL);
	अगर (host_mbx_ctrl) अणु
		clear_bit(QLC_83XX_MBX_READY, &mbx->status);
		ahw->idc.collect_dump = 1;
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qlcnic_83xx_संकेत_mbx_cmd(काष्ठा qlcnic_adapter *adapter,
					      u8 issue_cmd)
अणु
	अगर (issue_cmd)
		QLCWRX(adapter->ahw, QLCNIC_HOST_MBX_CTRL, QLCNIC_SET_OWNER);
	अन्यथा
		QLCWRX(adapter->ahw, QLCNIC_FW_MBX_CTRL, QLCNIC_CLR_OWNER);
पूर्ण

अटल व्योम qlcnic_83xx_dequeue_mbx_cmd(काष्ठा qlcnic_adapter *adapter,
					काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_mailbox *mbx = adapter->ahw->mailbox;

	spin_lock_bh(&mbx->queue_lock);

	list_del(&cmd->list);
	mbx->num_cmds--;

	spin_unlock_bh(&mbx->queue_lock);

	qlcnic_83xx_notअगरy_cmd_completion(adapter, cmd);
पूर्ण

अटल व्योम qlcnic_83xx_encode_mbx_cmd(काष्ठा qlcnic_adapter *adapter,
				       काष्ठा qlcnic_cmd_args *cmd)
अणु
	u32 mbx_cmd, fw_hal_version, hdr_size, total_size, पंचांगp;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक i, j;

	अगर (cmd->op_type != QLC_83XX_MBX_POST_BC_OP) अणु
		mbx_cmd = cmd->req.arg[0];
		ग_लिखोl(mbx_cmd, QLCNIC_MBX_HOST(ahw, 0));
		क्रम (i = 1; i < cmd->req.num; i++)
			ग_लिखोl(cmd->req.arg[i], QLCNIC_MBX_HOST(ahw, i));
	पूर्ण अन्यथा अणु
		fw_hal_version = ahw->fw_hal_version;
		hdr_size = माप(काष्ठा qlcnic_bc_hdr) / माप(u32);
		total_size = cmd->pay_size + hdr_size;
		पंचांगp = QLCNIC_CMD_BC_EVENT_SETUP | total_size << 16;
		mbx_cmd = पंचांगp | fw_hal_version << 29;
		ग_लिखोl(mbx_cmd, QLCNIC_MBX_HOST(ahw, 0));

		/* Back channel specअगरic operations bits */
		mbx_cmd = 0x1 | 1 << 4;

		अगर (qlcnic_sriov_pf_check(adapter))
			mbx_cmd |= cmd->func_num << 5;

		ग_लिखोl(mbx_cmd, QLCNIC_MBX_HOST(ahw, 1));

		क्रम (i = 2, j = 0; j < hdr_size; i++, j++)
			ग_लिखोl(*(cmd->hdr++), QLCNIC_MBX_HOST(ahw, i));
		क्रम (j = 0; j < cmd->pay_size; j++, i++)
			ग_लिखोl(*(cmd->pay++), QLCNIC_MBX_HOST(ahw, i));
	पूर्ण
पूर्ण

व्योम qlcnic_83xx_detach_mailbox_work(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_mailbox *mbx = adapter->ahw->mailbox;

	अगर (!mbx)
		वापस;

	clear_bit(QLC_83XX_MBX_READY, &mbx->status);
	complete(&mbx->completion);
	cancel_work_sync(&mbx->work);
	flush_workqueue(mbx->work_q);
	qlcnic_83xx_flush_mbx_queue(adapter);
पूर्ण

अटल पूर्णांक qlcnic_83xx_enqueue_mbx_cmd(काष्ठा qlcnic_adapter *adapter,
				       काष्ठा qlcnic_cmd_args *cmd,
				       अचिन्हित दीर्घ *समयout)
अणु
	काष्ठा qlcnic_mailbox *mbx = adapter->ahw->mailbox;

	अगर (test_bit(QLC_83XX_MBX_READY, &mbx->status)) अणु
		atomic_set(&cmd->rsp_status, QLC_83XX_MBX_RESPONSE_WAIT);
		init_completion(&cmd->completion);
		cmd->rsp_opcode = QLC_83XX_MBX_RESPONSE_UNKNOWN;

		spin_lock_bh(&mbx->queue_lock);

		list_add_tail(&cmd->list, &mbx->cmd_q);
		mbx->num_cmds++;
		cmd->total_cmds = mbx->num_cmds;
		*समयout = cmd->total_cmds * QLC_83XX_MBX_TIMEOUT;
		queue_work(mbx->work_q, &mbx->work);

		spin_unlock_bh(&mbx->queue_lock);

		वापस 0;
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक qlcnic_83xx_check_mac_rcode(काष्ठा qlcnic_adapter *adapter,
				       काष्ठा qlcnic_cmd_args *cmd)
अणु
	u8 mac_cmd_rcode;
	u32 fw_data;

	अगर (cmd->cmd_op == QLCNIC_CMD_CONFIG_MAC_VLAN) अणु
		fw_data = पढ़ोl(QLCNIC_MBX_FW(adapter->ahw, 2));
		mac_cmd_rcode = (u8)fw_data;
		अगर (mac_cmd_rcode == QLC_83XX_NO_NIC_RESOURCE ||
		    mac_cmd_rcode == QLC_83XX_MAC_PRESENT ||
		    mac_cmd_rcode == QLC_83XX_MAC_ABSENT) अणु
			cmd->rsp_opcode = QLCNIC_RCODE_SUCCESS;
			वापस QLCNIC_RCODE_SUCCESS;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम qlcnic_83xx_decode_mbx_rsp(काष्ठा qlcnic_adapter *adapter,
				       काष्ठा qlcnic_cmd_args *cmd)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा device *dev = &adapter->pdev->dev;
	u8 mbx_err_code;
	u32 fw_data;

	fw_data = पढ़ोl(QLCNIC_MBX_FW(ahw, 0));
	mbx_err_code = QLCNIC_MBX_STATUS(fw_data);
	qlcnic_83xx_get_mbx_data(adapter, cmd);

	चयन (mbx_err_code) अणु
	हाल QLCNIC_MBX_RSP_OK:
	हाल QLCNIC_MBX_PORT_RSP_OK:
		cmd->rsp_opcode = QLCNIC_RCODE_SUCCESS;
		अवरोध;
	शेष:
		अगर (!qlcnic_83xx_check_mac_rcode(adapter, cmd))
			अवरोध;

		dev_err(dev, "%s: Mailbox command failed, opcode=0x%x, cmd_type=0x%x, func=0x%x, op_mode=0x%x, error=0x%x\n",
			__func__, cmd->cmd_op, cmd->type, ahw->pci_func,
			ahw->op_mode, mbx_err_code);
		cmd->rsp_opcode = QLC_83XX_MBX_RESPONSE_FAILED;
		qlcnic_dump_mbx(adapter, cmd);
	पूर्ण

	वापस;
पूर्ण

अटल अंतरभूत व्योम qlcnic_dump_mailbox_रेजिस्टरs(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u32 offset;

	offset = QLCRDX(ahw, QLCNIC_DEF_INT_MASK);
	dev_info(&adapter->pdev->dev, "Mbx interrupt mask=0x%x, Mbx interrupt enable=0x%x, Host mbx control=0x%x, Fw mbx control=0x%x",
		 पढ़ोl(ahw->pci_base0 + offset),
		 QLCRDX(ahw, QLCNIC_MBX_INTR_ENBL),
		 QLCRDX(ahw, QLCNIC_HOST_MBX_CTRL),
		 QLCRDX(ahw, QLCNIC_FW_MBX_CTRL));
पूर्ण

अटल व्योम qlcnic_83xx_mailbox_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlcnic_mailbox *mbx = container_of(work, काष्ठा qlcnic_mailbox,
						  work);
	काष्ठा qlcnic_adapter *adapter = mbx->adapter;
	स्थिर काष्ठा qlcnic_mbx_ops *mbx_ops = mbx->ops;
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा list_head *head = &mbx->cmd_q;
	काष्ठा qlcnic_hardware_context *ahw;
	काष्ठा qlcnic_cmd_args *cmd = शून्य;
	अचिन्हित दीर्घ flags;

	ahw = adapter->ahw;

	जबतक (true) अणु
		अगर (qlcnic_83xx_check_mbx_status(adapter)) अणु
			qlcnic_83xx_flush_mbx_queue(adapter);
			वापस;
		पूर्ण

		spin_lock_irqsave(&mbx->aen_lock, flags);
		mbx->rsp_status = QLC_83XX_MBX_RESPONSE_WAIT;
		spin_unlock_irqrestore(&mbx->aen_lock, flags);

		spin_lock_bh(&mbx->queue_lock);

		अगर (list_empty(head)) अणु
			spin_unlock_bh(&mbx->queue_lock);
			वापस;
		पूर्ण
		cmd = list_entry(head->next, काष्ठा qlcnic_cmd_args, list);

		spin_unlock_bh(&mbx->queue_lock);

		mbx_ops->encode_cmd(adapter, cmd);
		mbx_ops->nofity_fw(adapter, QLC_83XX_MBX_REQUEST);

		अगर (रुको_क्रम_completion_समयout(&mbx->completion,
						QLC_83XX_MBX_TIMEOUT)) अणु
			mbx_ops->decode_resp(adapter, cmd);
			mbx_ops->nofity_fw(adapter, QLC_83XX_MBX_COMPLETION);
		पूर्ण अन्यथा अणु
			dev_err(dev, "%s: Mailbox command timeout, opcode=0x%x, cmd_type=0x%x, func=0x%x, op_mode=0x%x\n",
				__func__, cmd->cmd_op, cmd->type, ahw->pci_func,
				ahw->op_mode);
			clear_bit(QLC_83XX_MBX_READY, &mbx->status);
			qlcnic_dump_mailbox_रेजिस्टरs(adapter);
			qlcnic_83xx_get_mbx_data(adapter, cmd);
			qlcnic_dump_mbx(adapter, cmd);
			qlcnic_83xx_idc_request_reset(adapter,
						      QLCNIC_FORCE_FW_DUMP_KEY);
			cmd->rsp_opcode = QLCNIC_RCODE_TIMEOUT;
		पूर्ण
		mbx_ops->dequeue_cmd(adapter, cmd);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा qlcnic_mbx_ops qlcnic_83xx_mbx_ops = अणु
	.enqueue_cmd    = qlcnic_83xx_enqueue_mbx_cmd,
	.dequeue_cmd    = qlcnic_83xx_dequeue_mbx_cmd,
	.decode_resp    = qlcnic_83xx_decode_mbx_rsp,
	.encode_cmd     = qlcnic_83xx_encode_mbx_cmd,
	.nofity_fw      = qlcnic_83xx_संकेत_mbx_cmd,
पूर्ण;

पूर्णांक qlcnic_83xx_init_mailbox_work(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_mailbox *mbx;

	ahw->mailbox = kzalloc(माप(*mbx), GFP_KERNEL);
	अगर (!ahw->mailbox)
		वापस -ENOMEM;

	mbx = ahw->mailbox;
	mbx->ops = &qlcnic_83xx_mbx_ops;
	mbx->adapter = adapter;

	spin_lock_init(&mbx->queue_lock);
	spin_lock_init(&mbx->aen_lock);
	INIT_LIST_HEAD(&mbx->cmd_q);
	init_completion(&mbx->completion);

	mbx->work_q = create_singlethपढ़ो_workqueue("qlcnic_mailbox");
	अगर (mbx->work_q == शून्य) अणु
		kमुक्त(mbx);
		वापस -ENOMEM;
	पूर्ण

	INIT_WORK(&mbx->work, qlcnic_83xx_mailbox_worker);
	set_bit(QLC_83XX_MBX_READY, &mbx->status);
	वापस 0;
पूर्ण

अटल pci_ers_result_t qlcnic_83xx_io_error_detected(काष्ठा pci_dev *pdev,
						      pci_channel_state_t state)
अणु
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(pdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (state == pci_channel_io_normal)
		वापस PCI_ERS_RESULT_RECOVERED;

	set_bit(__QLCNIC_AER, &adapter->state);
	set_bit(__QLCNIC_RESETTING, &adapter->state);

	qlcnic_83xx_aer_stop_poll_work(adapter);

	pci_save_state(pdev);
	pci_disable_device(pdev);

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t qlcnic_83xx_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(pdev);
	पूर्णांक err = 0;

	pdev->error_state = pci_channel_io_normal;
	err = pci_enable_device(pdev);
	अगर (err)
		जाओ disconnect;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_set_master(pdev);
	pci_restore_state(pdev);

	err = qlcnic_83xx_aer_reset(adapter);
	अगर (err == 0)
		वापस PCI_ERS_RESULT_RECOVERED;
disconnect:
	clear_bit(__QLCNIC_AER, &adapter->state);
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	वापस PCI_ERS_RESULT_DISCONNECT;
पूर्ण

अटल व्योम qlcnic_83xx_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qlcnic_adapter *adapter = pci_get_drvdata(pdev);

	अगर (test_and_clear_bit(__QLCNIC_AER, &adapter->state))
		qlcnic_83xx_aer_start_poll_work(adapter);
पूर्ण
