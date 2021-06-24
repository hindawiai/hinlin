<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2021 Intel Corporation. */

#अगर_अघोषित _I40E_DCB_H_
#घोषणा _I40E_DCB_H_

#समावेश "i40e_type.h"

#घोषणा I40E_DCBX_STATUS_NOT_STARTED	0
#घोषणा I40E_DCBX_STATUS_IN_PROGRESS	1
#घोषणा I40E_DCBX_STATUS_DONE		2
#घोषणा I40E_DCBX_STATUS_MULTIPLE_PEERS	3
#घोषणा I40E_DCBX_STATUS_DISABLED	7

#घोषणा I40E_TLV_TYPE_END		0
#घोषणा I40E_TLV_TYPE_ORG		127

#घोषणा I40E_IEEE_8021QAZ_OUI		0x0080C2
#घोषणा I40E_IEEE_SUBTYPE_ETS_CFG	9
#घोषणा I40E_IEEE_SUBTYPE_ETS_REC	10
#घोषणा I40E_IEEE_SUBTYPE_PFC_CFG	11
#घोषणा I40E_IEEE_SUBTYPE_APP_PRI	12

#घोषणा I40E_CEE_DCBX_OUI		0x001b21
#घोषणा I40E_CEE_DCBX_TYPE		2

#घोषणा I40E_CEE_SUBTYPE_CTRL		1
#घोषणा I40E_CEE_SUBTYPE_PG_CFG		2
#घोषणा I40E_CEE_SUBTYPE_PFC_CFG	3
#घोषणा I40E_CEE_SUBTYPE_APP_PRI	4

#घोषणा I40E_CEE_MAX_FEAT_TYPE		3
#घोषणा I40E_LLDP_CURRENT_STATUS_XL710_OFFSET	0x2B
#घोषणा I40E_LLDP_CURRENT_STATUS_X722_OFFSET	0x31
#घोषणा I40E_LLDP_CURRENT_STATUS_OFFSET		1
#घोषणा I40E_LLDP_CURRENT_STATUS_SIZE		1

/* Defines क्रम LLDP TLV header */
#घोषणा I40E_LLDP_TLV_LEN_SHIFT		0
#घोषणा I40E_LLDP_TLV_LEN_MASK		(0x01FF << I40E_LLDP_TLV_LEN_SHIFT)
#घोषणा I40E_LLDP_TLV_TYPE_SHIFT	9
#घोषणा I40E_LLDP_TLV_TYPE_MASK		(0x7F << I40E_LLDP_TLV_TYPE_SHIFT)
#घोषणा I40E_LLDP_TLV_SUBTYPE_SHIFT	0
#घोषणा I40E_LLDP_TLV_SUBTYPE_MASK	(0xFF << I40E_LLDP_TLV_SUBTYPE_SHIFT)
#घोषणा I40E_LLDP_TLV_OUI_SHIFT		8
#घोषणा I40E_LLDP_TLV_OUI_MASK		(0xFFFFFF << I40E_LLDP_TLV_OUI_SHIFT)

/* Defines क्रम IEEE ETS TLV */
#घोषणा I40E_IEEE_ETS_MAXTC_SHIFT	0
#घोषणा I40E_IEEE_ETS_MAXTC_MASK	(0x7 << I40E_IEEE_ETS_MAXTC_SHIFT)
#घोषणा I40E_IEEE_ETS_CBS_SHIFT		6
#घोषणा I40E_IEEE_ETS_CBS_MASK		BIT(I40E_IEEE_ETS_CBS_SHIFT)
#घोषणा I40E_IEEE_ETS_WILLING_SHIFT	7
#घोषणा I40E_IEEE_ETS_WILLING_MASK	BIT(I40E_IEEE_ETS_WILLING_SHIFT)
#घोषणा I40E_IEEE_ETS_PRIO_0_SHIFT	0
#घोषणा I40E_IEEE_ETS_PRIO_0_MASK	(0x7 << I40E_IEEE_ETS_PRIO_0_SHIFT)
#घोषणा I40E_IEEE_ETS_PRIO_1_SHIFT	4
#घोषणा I40E_IEEE_ETS_PRIO_1_MASK	(0x7 << I40E_IEEE_ETS_PRIO_1_SHIFT)
#घोषणा I40E_CEE_PGID_PRIO_0_SHIFT	0
#घोषणा I40E_CEE_PGID_PRIO_0_MASK	(0xF << I40E_CEE_PGID_PRIO_0_SHIFT)
#घोषणा I40E_CEE_PGID_PRIO_1_SHIFT	4
#घोषणा I40E_CEE_PGID_PRIO_1_MASK	(0xF << I40E_CEE_PGID_PRIO_1_SHIFT)
#घोषणा I40E_CEE_PGID_STRICT		15

/* Defines क्रम IEEE TSA types */
#घोषणा I40E_IEEE_TSA_STRICT		0
#घोषणा I40E_IEEE_TSA_ETS		2

/* Defines क्रम IEEE PFC TLV */
#घोषणा I40E_DCB_PFC_ENABLED		2
#घोषणा I40E_DCB_PFC_FORCED_NUM_TC	2
#घोषणा I40E_IEEE_PFC_CAP_SHIFT		0
#घोषणा I40E_IEEE_PFC_CAP_MASK		(0xF << I40E_IEEE_PFC_CAP_SHIFT)
#घोषणा I40E_IEEE_PFC_MBC_SHIFT		6
#घोषणा I40E_IEEE_PFC_MBC_MASK		BIT(I40E_IEEE_PFC_MBC_SHIFT)
#घोषणा I40E_IEEE_PFC_WILLING_SHIFT	7
#घोषणा I40E_IEEE_PFC_WILLING_MASK	BIT(I40E_IEEE_PFC_WILLING_SHIFT)

/* Defines क्रम IEEE APP TLV */
#घोषणा I40E_IEEE_APP_SEL_SHIFT		0
#घोषणा I40E_IEEE_APP_SEL_MASK		(0x7 << I40E_IEEE_APP_SEL_SHIFT)
#घोषणा I40E_IEEE_APP_PRIO_SHIFT	5
#घोषणा I40E_IEEE_APP_PRIO_MASK		(0x7 << I40E_IEEE_APP_PRIO_SHIFT)

/* TLV definitions क्रम preparing MIB */
#घोषणा I40E_TLV_ID_CHASSIS_ID		0
#घोषणा I40E_TLV_ID_PORT_ID		1
#घोषणा I40E_TLV_ID_TIME_TO_LIVE	2
#घोषणा I40E_IEEE_TLV_ID_ETS_CFG	3
#घोषणा I40E_IEEE_TLV_ID_ETS_REC	4
#घोषणा I40E_IEEE_TLV_ID_PFC_CFG	5
#घोषणा I40E_IEEE_TLV_ID_APP_PRI	6
#घोषणा I40E_TLV_ID_END_OF_LLDPPDU	7
#घोषणा I40E_TLV_ID_START		I40E_IEEE_TLV_ID_ETS_CFG

#घोषणा I40E_IEEE_TLV_HEADER_LENGTH	2
#घोषणा I40E_IEEE_ETS_TLV_LENGTH	25
#घोषणा I40E_IEEE_PFC_TLV_LENGTH	6
#घोषणा I40E_IEEE_APP_TLV_LENGTH	11

/* Defines क्रम शेष SW DCB config */
#घोषणा I40E_IEEE_DEFAULT_ETS_TCBW	100
#घोषणा I40E_IEEE_DEFAULT_ETS_WILLING	1
#घोषणा I40E_IEEE_DEFAULT_PFC_WILLING	1
#घोषणा I40E_IEEE_DEFAULT_NUM_APPS	1
#घोषणा I40E_IEEE_DEFAULT_APP_PRIO	3

#आशय pack(1)
/* IEEE 802.1AB LLDP Organization specअगरic TLV */
काष्ठा i40e_lldp_org_tlv अणु
	__be16 typelength;
	__be32 ouisubtype;
	u8 tlvinfo[1];
पूर्ण;

काष्ठा i40e_cee_tlv_hdr अणु
	__be16 typelen;
	u8 operver;
	u8 maxver;
पूर्ण;

काष्ठा i40e_cee_ctrl_tlv अणु
	काष्ठा i40e_cee_tlv_hdr hdr;
	__be32 seqno;
	__be32 ackno;
पूर्ण;

काष्ठा i40e_cee_feat_tlv अणु
	काष्ठा i40e_cee_tlv_hdr hdr;
	u8 en_will_err; /* Bits: |En|Will|Err|Reserved(5)| */
#घोषणा I40E_CEE_FEAT_TLV_ENABLE_MASK	0x80
#घोषणा I40E_CEE_FEAT_TLV_WILLING_MASK	0x40
#घोषणा I40E_CEE_FEAT_TLV_ERR_MASK	0x20
	u8 subtype;
	u8 tlvinfo[1];
पूर्ण;

काष्ठा i40e_cee_app_prio अणु
	__be16 protocol;
	u8 upper_oui_sel; /* Bits: |Upper OUI(6)|Selector(2)| */
#घोषणा I40E_CEE_APP_SELECTOR_MASK	0x03
	__be16 lower_oui;
	u8 prio_map;
पूर्ण;
#आशय pack()

क्रमागत i40e_get_fw_lldp_status_resp अणु
	I40E_GET_FW_LLDP_STATUS_DISABLED = 0,
	I40E_GET_FW_LLDP_STATUS_ENABLED = 1
पूर्ण;

/* Data काष्ठाures to pass क्रम SW DCBX */
काष्ठा i40e_rx_pb_config अणु
	u32	shared_pool_size;
	u32	shared_pool_high_wm;
	u32	shared_pool_low_wm;
	u32	shared_pool_high_thresh[I40E_MAX_TRAFFIC_CLASS];
	u32	shared_pool_low_thresh[I40E_MAX_TRAFFIC_CLASS];
	u32	tc_pool_size[I40E_MAX_TRAFFIC_CLASS];
	u32	tc_pool_high_wm[I40E_MAX_TRAFFIC_CLASS];
	u32	tc_pool_low_wm[I40E_MAX_TRAFFIC_CLASS];
पूर्ण;

क्रमागत i40e_dcb_arbiter_mode अणु
	I40E_DCB_ARB_MODE_STRICT_PRIORITY = 0,
	I40E_DCB_ARB_MODE_ROUND_ROBIN = 1
पूर्ण;

#घोषणा I40E_DCB_DEFAULT_MAX_EXPONENT		0xB
#घोषणा I40E_DEFAULT_PAUSE_TIME			0xffff
#घोषणा I40E_MAX_FRAME_SIZE			4608 /* 4.5 KB */

#घोषणा I40E_DEVICE_RPB_SIZE			968000 /* 968 KB */

/* BitTimes (BT) conversion */
#घोषणा I40E_BT2KB(BT) (((BT) + (8 * 1024 - 1)) / (8 * 1024))
#घोषणा I40E_B2BT(BT) ((BT) * 8)
#घोषणा I40E_BT2B(BT) (((BT) + (8 - 1)) / 8)

/* Max Frame(TC) = MFS(max) + MFS(TC) */
#घोषणा I40E_MAX_FRAME_TC(mfs_max, mfs_tc)	I40E_B2BT((mfs_max) + (mfs_tc))

/* EEE Tx LPI Exit समय in Bit Times */
#घोषणा I40E_EEE_TX_LPI_EXIT_TIME		142500

/* PCI Round Trip Time in Bit Times */
#घोषणा I40E_PCIRTT_LINK_SPEED_10G		20000
#घोषणा I40E_PCIRTT_BYTE_LINK_SPEED_20G		40000
#घोषणा I40E_PCIRTT_BYTE_LINK_SPEED_40G		80000

/* PFC Frame Delay Bit Times */
#घोषणा I40E_PFC_FRAME_DELAY			672

/* Worst हाल Cable (10GBase-T) Delay Bit Times */
#घोषणा I40E_CABLE_DELAY			5556

/* Higher Layer Delay @10G Bit Times */
#घोषणा I40E_HIGHER_LAYER_DELAY_10G		6144

/* Interface Delays in Bit Times */
/* TODO: Add क्रम other link speeds 20G/40G/etc. */
#घोषणा I40E_INTERFACE_DELAY_10G_MAC_CONTROL	8192
#घोषणा I40E_INTERFACE_DELAY_10G_MAC		8192
#घोषणा I40E_INTERFACE_DELAY_10G_RS		8192

#घोषणा I40E_INTERFACE_DELAY_XGXS		2048
#घोषणा I40E_INTERFACE_DELAY_XAUI		2048

#घोषणा I40E_INTERFACE_DELAY_10G_BASEX_PCS	2048
#घोषणा I40E_INTERFACE_DELAY_10G_BASER_PCS	3584
#घोषणा I40E_INTERFACE_DELAY_LX4_PMD		512
#घोषणा I40E_INTERFACE_DELAY_CX4_PMD		512
#घोषणा I40E_INTERFACE_DELAY_SERIAL_PMA		512
#घोषणा I40E_INTERFACE_DELAY_PMD		512

#घोषणा I40E_INTERFACE_DELAY_10G_BASET		25600

/* Hardware RX DCB config related defines */
#घोषणा I40E_DCB_1_PORT_THRESHOLD		0xF
#घोषणा I40E_DCB_1_PORT_FIFO_SIZE		0x10
#घोषणा I40E_DCB_2_PORT_THRESHOLD_LOW_NUM_TC	0xF
#घोषणा I40E_DCB_2_PORT_FIFO_SIZE_LOW_NUM_TC	0x10
#घोषणा I40E_DCB_2_PORT_THRESHOLD_HIGH_NUM_TC	0xC
#घोषणा I40E_DCB_2_PORT_FIFO_SIZE_HIGH_NUM_TC	0x8
#घोषणा I40E_DCB_4_PORT_THRESHOLD_LOW_NUM_TC	0x9
#घोषणा I40E_DCB_4_PORT_FIFO_SIZE_LOW_NUM_TC	0x8
#घोषणा I40E_DCB_4_PORT_THRESHOLD_HIGH_NUM_TC	0x6
#घोषणा I40E_DCB_4_PORT_FIFO_SIZE_HIGH_NUM_TC	0x4
#घोषणा I40E_DCB_WATERMARK_START_FACTOR		0x2

/* delay values क्रम with 10G BaseT in Bit Times */
#घोषणा I40E_INTERFACE_DELAY_10G_COPPER	\
	(I40E_INTERFACE_DELAY_10G_MAC + (2 * I40E_INTERFACE_DELAY_XAUI) \
	 + I40E_INTERFACE_DELAY_10G_BASET)
#घोषणा I40E_DV_TC(mfs_max, mfs_tc) \
		((2 * I40E_MAX_FRAME_TC(mfs_max, mfs_tc)) \
		 + I40E_PFC_FRAME_DELAY \
		 + (2 * I40E_CABLE_DELAY) \
		 + (2 * I40E_INTERFACE_DELAY_10G_COPPER) \
		 + I40E_HIGHER_LAYER_DELAY_10G)
अटल अंतरभूत u32 I40E_STD_DV_TC(u32 mfs_max, u32 mfs_tc)
अणु
	वापस I40E_DV_TC(mfs_max, mfs_tc) + I40E_B2BT(mfs_max);
पूर्ण

/* APIs क्रम SW DCBX */
व्योम i40e_dcb_hw_rx_fअगरo_config(काष्ठा i40e_hw *hw,
				क्रमागत i40e_dcb_arbiter_mode ets_mode,
				क्रमागत i40e_dcb_arbiter_mode non_ets_mode,
				u32 max_exponent, u8 lltc_map);
व्योम i40e_dcb_hw_rx_cmd_monitor_config(काष्ठा i40e_hw *hw,
				       u8 num_tc, u8 num_ports);
व्योम i40e_dcb_hw_pfc_config(काष्ठा i40e_hw *hw,
			    u8 pfc_en, u8 *prio_tc);
व्योम i40e_dcb_hw_set_num_tc(काष्ठा i40e_hw *hw, u8 num_tc);
u8 i40e_dcb_hw_get_num_tc(काष्ठा i40e_hw *hw);
व्योम i40e_dcb_hw_rx_ets_bw_config(काष्ठा i40e_hw *hw, u8 *bw_share,
				  u8 *mode, u8 *prio_type);
व्योम i40e_dcb_hw_rx_up2tc_config(काष्ठा i40e_hw *hw, u8 *prio_tc);
व्योम i40e_dcb_hw_calculate_pool_sizes(काष्ठा i40e_hw *hw,
				      u8 num_ports, bool eee_enabled,
				      u8 pfc_en, u32 *mfs_tc,
				      काष्ठा i40e_rx_pb_config *pb_cfg);
व्योम i40e_dcb_hw_rx_pb_config(काष्ठा i40e_hw *hw,
			      काष्ठा i40e_rx_pb_config *old_pb_cfg,
			      काष्ठा i40e_rx_pb_config *new_pb_cfg);
i40e_status i40e_get_dcbx_status(काष्ठा i40e_hw *hw,
				 u16 *status);
i40e_status i40e_lldp_to_dcb_config(u8 *lldpmib,
				    काष्ठा i40e_dcbx_config *dcbcfg);
i40e_status i40e_aq_get_dcb_config(काष्ठा i40e_hw *hw, u8 mib_type,
				   u8 bridgetype,
				   काष्ठा i40e_dcbx_config *dcbcfg);
i40e_status i40e_get_dcb_config(काष्ठा i40e_hw *hw);
i40e_status i40e_init_dcb(काष्ठा i40e_hw *hw,
			  bool enable_mib_change);
क्रमागत i40e_status_code
i40e_get_fw_lldp_status(काष्ठा i40e_hw *hw,
			क्रमागत i40e_get_fw_lldp_status_resp *lldp_status);
i40e_status i40e_set_dcb_config(काष्ठा i40e_hw *hw);
i40e_status i40e_dcb_config_to_lldp(u8 *lldpmib, u16 *miblen,
				    काष्ठा i40e_dcbx_config *dcbcfg);
#पूर्ण_अगर /* _I40E_DCB_H_ */
