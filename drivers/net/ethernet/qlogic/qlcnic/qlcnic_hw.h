<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#अगर_अघोषित __QLCNIC_HW_H
#घोषणा __QLCNIC_HW_H

/* Common रेजिस्टरs in 83xx and 82xx */
क्रमागत qlcnic_regs अणु
	QLCNIC_PEG_HALT_STATUS1 = 0,
	QLCNIC_PEG_HALT_STATUS2,
	QLCNIC_PEG_ALIVE_COUNTER,
	QLCNIC_FLASH_LOCK_OWNER,
	QLCNIC_FW_CAPABILITIES,
	QLCNIC_CRB_DRV_ACTIVE,
	QLCNIC_CRB_DEV_STATE,
	QLCNIC_CRB_DRV_STATE,
	QLCNIC_CRB_DRV_SCRATCH,
	QLCNIC_CRB_DEV_PARTITION_INFO,
	QLCNIC_CRB_DRV_IDC_VER,
	QLCNIC_FW_VERSION_MAJOR,
	QLCNIC_FW_VERSION_MINOR,
	QLCNIC_FW_VERSION_SUB,
	QLCNIC_CRB_DEV_NPAR_STATE,
	QLCNIC_FW_IMG_VALID,
	QLCNIC_CMDPEG_STATE,
	QLCNIC_RCVPEG_STATE,
	QLCNIC_ASIC_TEMP,
	QLCNIC_FW_API,
	QLCNIC_DRV_OP_MODE,
	QLCNIC_FLASH_LOCK,
	QLCNIC_FLASH_UNLOCK,
पूर्ण;

/* Read from an address offset from BAR0, existing रेजिस्टरs */
#घोषणा QLC_SHARED_REG_RD32(a, addr)			\
	पढ़ोl(((a)->ahw->pci_base0) + ((a)->ahw->reg_tbl[addr]))

/* Write to an address offset from BAR0, existing रेजिस्टरs */
#घोषणा QLC_SHARED_REG_WR32(a, addr, value)		\
	ग_लिखोl(value, ((a)->ahw->pci_base0) + ((a)->ahw->reg_tbl[addr]))

/* Read from a direct address offset from BAR0, additional रेजिस्टरs */
#घोषणा QLCRDX(ahw, addr)	\
	पढ़ोl(((ahw)->pci_base0) + ((ahw)->ext_reg_tbl[addr]))

/* Write to a direct address offset from BAR0, additional रेजिस्टरs */
#घोषणा QLCWRX(ahw, addr, value)	\
	ग_लिखोl(value, (((ahw)->pci_base0) + ((ahw)->ext_reg_tbl[addr])))

#घोषणा QLCNIC_CMD_CONFIGURE_IP_ADDR		0x1
#घोषणा QLCNIC_CMD_CONFIG_INTRPT		0x2
#घोषणा QLCNIC_CMD_CREATE_RX_CTX		0x7
#घोषणा QLCNIC_CMD_DESTROY_RX_CTX		0x8
#घोषणा QLCNIC_CMD_CREATE_TX_CTX		0x9
#घोषणा QLCNIC_CMD_DESTROY_TX_CTX		0xa
#घोषणा QLCNIC_CMD_CONFIGURE_LRO		0xC
#घोषणा QLCNIC_CMD_CONFIGURE_MAC_LEARNING	0xD
#घोषणा QLCNIC_CMD_GET_STATISTICS		0xF
#घोषणा QLCNIC_CMD_INTRPT_TEST			0x11
#घोषणा QLCNIC_CMD_SET_MTU			0x12
#घोषणा QLCNIC_CMD_READ_PHY			0x13
#घोषणा QLCNIC_CMD_WRITE_PHY			0x14
#घोषणा QLCNIC_CMD_READ_HW_REG			0x15
#घोषणा QLCNIC_CMD_GET_FLOW_CTL			0x16
#घोषणा QLCNIC_CMD_SET_FLOW_CTL			0x17
#घोषणा QLCNIC_CMD_READ_MAX_MTU			0x18
#घोषणा QLCNIC_CMD_READ_MAX_LRO			0x19
#घोषणा QLCNIC_CMD_MAC_ADDRESS			0x1f
#घोषणा QLCNIC_CMD_GET_PCI_INFO			0x20
#घोषणा QLCNIC_CMD_GET_NIC_INFO			0x21
#घोषणा QLCNIC_CMD_SET_NIC_INFO			0x22
#घोषणा QLCNIC_CMD_GET_ESWITCH_CAPABILITY	0x24
#घोषणा QLCNIC_CMD_TOGGLE_ESWITCH		0x25
#घोषणा QLCNIC_CMD_GET_ESWITCH_STATUS		0x26
#घोषणा QLCNIC_CMD_SET_PORTMIRRORING		0x27
#घोषणा QLCNIC_CMD_CONFIGURE_ESWITCH		0x28
#घोषणा QLCNIC_CMD_GET_ESWITCH_PORT_CONFIG	0x29
#घोषणा QLCNIC_CMD_GET_ESWITCH_STATS		0x2a
#घोषणा QLCNIC_CMD_CONFIG_PORT			0x2e
#घोषणा QLCNIC_CMD_TEMP_SIZE			0x2f
#घोषणा QLCNIC_CMD_GET_TEMP_HDR			0x30
#घोषणा QLCNIC_CMD_BC_EVENT_SETUP		0x31
#घोषणा	QLCNIC_CMD_CONFIG_VPORT			0x32
#घोषणा	QLCNIC_CMD_DCB_QUERY_CAP		0x34
#घोषणा	QLCNIC_CMD_DCB_QUERY_PARAM		0x35
#घोषणा QLCNIC_CMD_GET_MAC_STATS		0x37
#घोषणा QLCNIC_CMD_82XX_SET_DRV_VER		0x38
#घोषणा QLCNIC_CMD_MQ_TX_CONFIG_INTR		0x39
#घोषणा QLCNIC_CMD_GET_LED_STATUS		0x3C
#घोषणा QLCNIC_CMD_CONFIGURE_RSS		0x41
#घोषणा QLCNIC_CMD_CONFIG_INTR_COAL		0x43
#घोषणा QLCNIC_CMD_CONFIGURE_LED		0x44
#घोषणा QLCNIC_CMD_CONFIG_MAC_VLAN		0x45
#घोषणा QLCNIC_CMD_GET_LINK_EVENT		0x48
#घोषणा QLCNIC_CMD_CONFIGURE_MAC_RX_MODE	0x49
#घोषणा QLCNIC_CMD_CONFIGURE_HW_LRO		0x4A
#घोषणा QLCNIC_CMD_SET_INGRESS_ENCAP		0x4E
#घोषणा QLCNIC_CMD_INIT_NIC_FUNC		0x60
#घोषणा QLCNIC_CMD_STOP_NIC_FUNC		0x61
#घोषणा QLCNIC_CMD_IDC_ACK			0x63
#घोषणा QLCNIC_CMD_SET_PORT_CONFIG		0x66
#घोषणा QLCNIC_CMD_GET_PORT_CONFIG		0x67
#घोषणा QLCNIC_CMD_GET_LINK_STATUS		0x68
#घोषणा QLCNIC_CMD_SET_LED_CONFIG		0x69
#घोषणा QLCNIC_CMD_GET_LED_CONFIG		0x6A
#घोषणा QLCNIC_CMD_83XX_SET_DRV_VER		0x6F
#घोषणा QLCNIC_CMD_ADD_RCV_RINGS		0x0B
#घोषणा QLCNIC_CMD_83XX_EXTEND_ISCSI_DUMP_CAP	0x37

#घोषणा QLCNIC_INTRPT_INTX			1
#घोषणा QLCNIC_INTRPT_MSIX			3
#घोषणा QLCNIC_INTRPT_ADD			1
#घोषणा QLCNIC_INTRPT_DEL			2

#घोषणा QLCNIC_GET_CURRENT_MAC			1
#घोषणा QLCNIC_SET_STATION_MAC			2
#घोषणा QLCNIC_GET_DEFAULT_MAC			3
#घोषणा QLCNIC_GET_FAC_DEF_MAC			4
#घोषणा QLCNIC_SET_FAC_DEF_MAC			5

#घोषणा QLCNIC_MBX_LINK_EVENT		0x8001
#घोषणा QLCNIC_MBX_BC_EVENT		0x8002
#घोषणा QLCNIC_MBX_COMP_EVENT		0x8100
#घोषणा QLCNIC_MBX_REQUEST_EVENT	0x8101
#घोषणा QLCNIC_MBX_TIME_EXTEND_EVENT	0x8102
#घोषणा QLCNIC_MBX_DCBX_CONFIG_CHANGE_EVENT	0x8110
#घोषणा QLCNIC_MBX_SFP_INSERT_EVENT	0x8130
#घोषणा QLCNIC_MBX_SFP_REMOVE_EVENT	0x8131

काष्ठा qlcnic_mailbox_metadata अणु
	u32 cmd;
	u32 in_args;
	u32 out_args;
पूर्ण;

/* Mailbox ownership */
#घोषणा QLCNIC_GET_OWNER(val)	((val) & (BIT_0 | BIT_1))

#घोषणा QLCNIC_SET_OWNER        1
#घोषणा QLCNIC_CLR_OWNER        0
#घोषणा QLCNIC_MBX_TIMEOUT      5000

#घोषणा QLCNIC_MBX_RSP_OK	1
#घोषणा QLCNIC_MBX_PORT_RSP_OK	0x1a
#घोषणा QLCNIC_MBX_ASYNC_EVENT	BIT_15

/* Set HW Tx ring limit क्रम 82xx adapter. */
#घोषणा QLCNIC_MAX_HW_TX_RINGS		8
#घोषणा QLCNIC_MAX_HW_VNIC_TX_RINGS	4
#घोषणा QLCNIC_MAX_TX_RINGS		8
#घोषणा QLCNIC_MAX_SDS_RINGS		8

काष्ठा qlcnic_pci_info;
काष्ठा qlcnic_info;
काष्ठा qlcnic_cmd_args;
काष्ठा ethtool_stats;
काष्ठा pci_device_id;
काष्ठा qlcnic_host_sds_ring;
काष्ठा qlcnic_host_tx_ring;
काष्ठा qlcnic_hardware_context;
काष्ठा qlcnic_adapter;
काष्ठा qlcnic_fw_dump;

पूर्णांक qlcnic_82xx_hw_पढ़ो_wx_2M(काष्ठा qlcnic_adapter *adapter, uदीर्घ, पूर्णांक *);
पूर्णांक qlcnic_82xx_hw_ग_लिखो_wx_2M(काष्ठा qlcnic_adapter *, uदीर्घ, u32);
पूर्णांक qlcnic_82xx_config_hw_lro(काष्ठा qlcnic_adapter *adapter, पूर्णांक);
पूर्णांक qlcnic_82xx_nic_set_promisc(काष्ठा qlcnic_adapter *adapter, u32);
पूर्णांक qlcnic_82xx_napi_add(काष्ठा qlcnic_adapter *adapter,
			 काष्ठा net_device *netdev);
व्योम qlcnic_82xx_get_beacon_state(काष्ठा qlcnic_adapter *);
व्योम qlcnic_82xx_change_filter(काष्ठा qlcnic_adapter *adapter,
			       u64 *uaddr, u16 vlan_id,
			       काष्ठा qlcnic_host_tx_ring *tx_ring);
पूर्णांक qlcnic_82xx_config_पूर्णांकr_coalesce(काष्ठा qlcnic_adapter *,
				     काष्ठा ethtool_coalesce *);
पूर्णांक qlcnic_82xx_set_rx_coalesce(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_82xx_config_rss(काष्ठा qlcnic_adapter *adapter, पूर्णांक);
व्योम qlcnic_82xx_config_ipaddr(काष्ठा qlcnic_adapter *adapter,
			       __be32, पूर्णांक);
पूर्णांक qlcnic_82xx_linkevent_request(काष्ठा qlcnic_adapter *adapter, पूर्णांक);
व्योम qlcnic_82xx_process_rcv_ring_diag(काष्ठा qlcnic_host_sds_ring *sds_ring);
पूर्णांक qlcnic_82xx_clear_lb_mode(काष्ठा qlcnic_adapter *adapter, u8);
पूर्णांक qlcnic_82xx_set_lb_mode(काष्ठा qlcnic_adapter *, u8);
व्योम qlcnic_82xx_ग_लिखो_crb(काष्ठा qlcnic_adapter *, अक्षर *, loff_t, माप_प्रकार);
व्योम qlcnic_82xx_पढ़ो_crb(काष्ठा qlcnic_adapter *, अक्षर *, loff_t, माप_प्रकार);
पूर्णांक qlcnic_82xx_issue_cmd(काष्ठा qlcnic_adapter *adapter,
			  काष्ठा qlcnic_cmd_args *);
पूर्णांक qlcnic_82xx_mq_पूर्णांकrpt(काष्ठा qlcnic_adapter *, पूर्णांक);
पूर्णांक qlcnic_82xx_config_पूर्णांकrpt(काष्ठा qlcnic_adapter *, u8);
पूर्णांक qlcnic_82xx_fw_cmd_create_rx_ctx(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_82xx_fw_cmd_create_tx_ctx(काष्ठा qlcnic_adapter *,
				     काष्ठा qlcnic_host_tx_ring *tx_ring, पूर्णांक);
व्योम qlcnic_82xx_fw_cmd_del_rx_ctx(काष्ठा qlcnic_adapter *);
व्योम qlcnic_82xx_fw_cmd_del_tx_ctx(काष्ठा qlcnic_adapter *,
				   काष्ठा qlcnic_host_tx_ring *);
पूर्णांक qlcnic_82xx_sre_macaddr_change(काष्ठा qlcnic_adapter *, u8 *, u16, u8);
पूर्णांक qlcnic_82xx_get_mac_address(काष्ठा qlcnic_adapter *, u8*, u8);
पूर्णांक qlcnic_82xx_get_nic_info(काष्ठा qlcnic_adapter *, काष्ठा qlcnic_info *, u8);
पूर्णांक qlcnic_82xx_set_nic_info(काष्ठा qlcnic_adapter *, काष्ठा qlcnic_info *);
पूर्णांक qlcnic_82xx_get_pci_info(काष्ठा qlcnic_adapter *, काष्ठा qlcnic_pci_info*);
पूर्णांक qlcnic_82xx_alloc_mbx_args(काष्ठा qlcnic_cmd_args *,
			       काष्ठा qlcnic_adapter *, u32);
पूर्णांक qlcnic_82xx_hw_ग_लिखो_wx_2M(काष्ठा qlcnic_adapter *, uदीर्घ, u32);
पूर्णांक qlcnic_82xx_get_board_info(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_82xx_config_led(काष्ठा qlcnic_adapter *, u32, u32);
व्योम qlcnic_82xx_get_func_no(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_82xx_api_lock(काष्ठा qlcnic_adapter *);
व्योम qlcnic_82xx_api_unlock(काष्ठा qlcnic_adapter *);
व्योम qlcnic_82xx_napi_enable(काष्ठा qlcnic_adapter *);
व्योम qlcnic_82xx_napi_disable(काष्ठा qlcnic_adapter *);
व्योम qlcnic_82xx_napi_del(काष्ठा qlcnic_adapter *);
पूर्णांक qlcnic_82xx_shutकरोwn(काष्ठा pci_dev *);
पूर्णांक qlcnic_82xx_resume(काष्ठा qlcnic_adapter *);
व्योम qlcnic_clr_all_drv_state(काष्ठा qlcnic_adapter *adapter, u8 failed);
व्योम qlcnic_fw_poll_work(काष्ठा work_काष्ठा *work);

u32 qlcnic_82xx_get_saved_state(व्योम *, u32);
व्योम qlcnic_82xx_set_saved_state(व्योम *, u32, u32);
व्योम qlcnic_82xx_cache_पंचांगpl_hdr_values(काष्ठा qlcnic_fw_dump *);
u32 qlcnic_82xx_get_cap_size(व्योम *, पूर्णांक);
व्योम qlcnic_82xx_set_sys_info(व्योम *, पूर्णांक, u32);
व्योम qlcnic_82xx_store_cap_mask(व्योम *, u32);
#पूर्ण_अगर				/* __QLCNIC_HW_H_ */
