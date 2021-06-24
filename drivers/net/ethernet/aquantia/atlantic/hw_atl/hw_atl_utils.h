<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File hw_atl_utils.h: Declaration of common functions क्रम Atlantic hardware
 * असलtraction layer.
 */

#अगर_अघोषित HW_ATL_UTILS_H
#घोषणा HW_ATL_UTILS_H

#घोषणा HW_ATL_FLUSH() अणु (व्योम)aq_hw_पढ़ो_reg(self, 0x10); पूर्ण

/* Hardware tx descriptor */
काष्ठा __packed hw_atl_txd_s अणु
	u64 buf_addr;
	u32 ctl;
	u32 ctl2; /* 63..46 - payload length, 45 - ctx enable, 44 - ctx index */
पूर्ण;

/* Hardware tx context descriptor */
काष्ठा __packed hw_atl_txc_s अणु
	u32 rsvd;
	u32 len;
	u32 ctl;
	u32 len2;
पूर्ण;

/* Hardware rx descriptor */
काष्ठा __packed hw_atl_rxd_s अणु
	u64 buf_addr;
	u64 hdr_addr;
पूर्ण;

/* Hardware rx descriptor ग_लिखोback */
काष्ठा __packed hw_atl_rxd_wb_s अणु
	u32 type;
	u32 rss_hash;
	u16 status;
	u16 pkt_len;
	u16 next_desc_ptr;
	__le16 vlan;
पूर्ण;

/* Hardware rx HW TIMESTAMP ग_लिखोback */
काष्ठा __packed hw_atl_rxd_hwts_wb_s अणु
	u32 sec_hw;
	u32 ns;
	u32 sec_lw0;
	u32 sec_lw1;
पूर्ण;

काष्ठा __packed hw_atl_stats_s अणु
	u32 uprc;
	u32 mprc;
	u32 bprc;
	u32 erpt;
	u32 uptc;
	u32 mptc;
	u32 bptc;
	u32 erpr;
	u32 mbtc;
	u32 bbtc;
	u32 mbrc;
	u32 bbrc;
	u32 ubrc;
	u32 ubtc;
	u32 dpc;
पूर्ण;

काष्ठा __packed drv_msg_enable_wakeup अणु
	जोड़ अणु
		u32 pattern_mask;

		काष्ठा अणु
			u32 reason_arp_v4_pkt : 1;
			u32 reason_ipv4_ping_pkt : 1;
			u32 reason_ipv6_ns_pkt : 1;
			u32 reason_ipv6_ping_pkt : 1;
			u32 reason_link_up : 1;
			u32 reason_link_करोwn : 1;
			u32 reason_maximum : 1;
		पूर्ण;
	पूर्ण;

	जोड़ अणु
		u32 offload_mask;
	पूर्ण;
पूर्ण;

काष्ठा __packed magic_packet_pattern_s अणु
	u8 mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा __packed drv_msg_wol_add अणु
	u32 priority;
	u32 packet_type;
	u32 pattern_id;
	u32 next_pattern_offset;

	काष्ठा magic_packet_pattern_s magic_packet_pattern;
पूर्ण;

काष्ठा __packed drv_msg_wol_हटाओ अणु
	u32 id;
पूर्ण;

काष्ठा __packed hw_atl_utils_mbox_header अणु
	u32 version;
	u32 transaction_id;
	u32 error;
पूर्ण;

काष्ठा __packed hw_atl_ptp_offset अणु
	u16 ingress_100;
	u16 egress_100;
	u16 ingress_1000;
	u16 egress_1000;
	u16 ingress_2500;
	u16 egress_2500;
	u16 ingress_5000;
	u16 egress_5000;
	u16 ingress_10000;
	u16 egress_10000;
पूर्ण;

काष्ठा __packed hw_atl_cable_diag अणु
	u8 fault;
	u8 distance;
	u8 far_distance;
	u8 reserved;
पूर्ण;

क्रमागत gpio_pin_function अणु
	GPIO_PIN_FUNCTION_NC,
	GPIO_PIN_FUNCTION_VAUX_ENABLE,
	GPIO_PIN_FUNCTION_EFUSE_BURN_ENABLE,
	GPIO_PIN_FUNCTION_SFP_PLUS_DETECT,
	GPIO_PIN_FUNCTION_TX_DISABLE,
	GPIO_PIN_FUNCTION_RATE_SEL_0,
	GPIO_PIN_FUNCTION_RATE_SEL_1,
	GPIO_PIN_FUNCTION_TX_FAULT,
	GPIO_PIN_FUNCTION_PTP0,
	GPIO_PIN_FUNCTION_PTP1,
	GPIO_PIN_FUNCTION_PTP2,
	GPIO_PIN_FUNCTION_SIZE
पूर्ण;

काष्ठा __packed hw_atl_info अणु
	u8 reserved[6];
	u16 phy_fault_code;
	u16 phy_temperature;
	u8 cable_len;
	u8 reserved1;
	काष्ठा hw_atl_cable_diag cable_diag_data[4];
	काष्ठा hw_atl_ptp_offset ptp_offset;
	u8 reserved2[12];
	u32 caps_lo;
	u32 caps_hi;
	u32 reserved_datapath;
	u32 reserved3[7];
	u32 reserved_simpleresp[3];
	u32 reserved_linkstat[7];
	u32 reserved_wakes_count;
	u32 reserved_eee_stat[12];
	u32 tx_stuck_cnt;
	u32 setting_address;
	u32 setting_length;
	u32 caps_ex;
	क्रमागत gpio_pin_function gpio_pin[3];
	u32 pcie_aer_dump[18];
	u16 snr_margin[4];
पूर्ण;

काष्ठा __packed hw_atl_utils_mbox अणु
	काष्ठा hw_atl_utils_mbox_header header;
	काष्ठा hw_atl_stats_s stats;
	काष्ठा hw_atl_info info;
पूर्ण;

काष्ठा __packed offload_ip_info अणु
	u8 v4_local_addr_count;
	u8 v4_addr_count;
	u8 v6_local_addr_count;
	u8 v6_addr_count;
	u32 v4_addr;
	u32 v4_prefix;
	u32 v6_addr;
	u32 v6_prefix;
पूर्ण;

काष्ठा __packed offload_port_info अणु
	u16 udp_port_count;
	u16 tcp_port_count;
	u32 udp_port;
	u32 tcp_port;
पूर्ण;

काष्ठा __packed offload_ka_info अणु
	u16 v4_ka_count;
	u16 v6_ka_count;
	u32 retry_count;
	u32 retry_पूर्णांकerval;
	u32 v4_ka;
	u32 v6_ka;
पूर्ण;

काष्ठा __packed offload_rr_info अणु
	u32 rr_count;
	u32 rr_buf_len;
	u32 rr_id_x;
	u32 rr_buf;
पूर्ण;

काष्ठा __packed offload_info अणु
	u32 version;
	u32 len;
	u8 mac_addr[ETH_ALEN];

	u8 reserved[2];

	काष्ठा offload_ip_info ips;
	काष्ठा offload_port_info ports;
	काष्ठा offload_ka_info kas;
	काष्ठा offload_rr_info rrs;
	u8 buf[];
पूर्ण;

काष्ठा __packed hw_atl_utils_fw_rpc अणु
	u32 msg_id;

	जोड़ अणु
		/* fw1x काष्ठाures */
		काष्ठा drv_msg_wol_add msg_wol_add;
		काष्ठा drv_msg_wol_हटाओ msg_wol_हटाओ;
		काष्ठा drv_msg_enable_wakeup msg_enable_wakeup;
		/* fw2x काष्ठाures */
		काष्ठा offload_info fw2x_offloads;
	पूर्ण;
पूर्ण;

/* Mailbox FW Request पूर्णांकerface */
काष्ठा __packed hw_fw_request_ptp_gpio_ctrl अणु
	u32 index;
	u32 period;
	u64 start;
पूर्ण;

काष्ठा __packed hw_fw_request_ptp_adj_freq अणु
	u32 ns_mac;
	u32 fns_mac;
	u32 ns_phy;
	u32 fns_phy;
	u32 mac_ns_adj;
	u32 mac_fns_adj;
पूर्ण;

काष्ठा __packed hw_fw_request_ptp_adj_घड़ी अणु
	u32 ns;
	u32 sec;
	पूर्णांक sign;
पूर्ण;

#घोषणा HW_AQ_FW_REQUEST_PTP_GPIO_CTRL	         0x11
#घोषणा HW_AQ_FW_REQUEST_PTP_ADJ_FREQ	         0x12
#घोषणा HW_AQ_FW_REQUEST_PTP_ADJ_CLOCK	         0x13

काष्ठा __packed hw_fw_request_अगरace अणु
	u32 msg_id;
	जोड़ अणु
		/* PTP FW Request */
		काष्ठा hw_fw_request_ptp_gpio_ctrl ptp_gpio_ctrl;
		काष्ठा hw_fw_request_ptp_adj_freq ptp_adj_freq;
		काष्ठा hw_fw_request_ptp_adj_घड़ी ptp_adj_घड़ी;
	पूर्ण;
पूर्ण;

काष्ठा __packed hw_atl_utils_settings अणु
	u32 mtu;
	u32 करोwnshअगरt_retry_count;
	u32 link_छोड़ो_frame_quanta_100m;
	u32 link_छोड़ो_frame_threshold_100m;
	u32 link_छोड़ो_frame_quanta_1g;
	u32 link_छोड़ो_frame_threshold_1g;
	u32 link_छोड़ो_frame_quanta_2p5g;
	u32 link_छोड़ो_frame_threshold_2p5g;
	u32 link_छोड़ो_frame_quanta_5g;
	u32 link_छोड़ो_frame_threshold_5g;
	u32 link_छोड़ो_frame_quanta_10g;
	u32 link_छोड़ो_frame_threshold_10g;
	u32 pfc_quanta_class_0;
	u32 pfc_threshold_class_0;
	u32 pfc_quanta_class_1;
	u32 pfc_threshold_class_1;
	u32 pfc_quanta_class_2;
	u32 pfc_threshold_class_2;
	u32 pfc_quanta_class_3;
	u32 pfc_threshold_class_3;
	u32 pfc_quanta_class_4;
	u32 pfc_threshold_class_4;
	u32 pfc_quanta_class_5;
	u32 pfc_threshold_class_5;
	u32 pfc_quanta_class_6;
	u32 pfc_threshold_class_6;
	u32 pfc_quanta_class_7;
	u32 pfc_threshold_class_7;
	u32 eee_link_करोwn_समयout;
	u32 eee_link_up_समयout;
	u32 eee_max_link_drops;
	u32 eee_rates_mask;
	u32 wake_समयr;
	u32 thermal_shutकरोwn_off_temp;
	u32 thermal_shutकरोwn_warning_temp;
	u32 thermal_shutकरोwn_cold_temp;
	u32 msm_options;
	u32 dac_cable_serdes_modes;
	u32 media_detect;
पूर्ण;

क्रमागत macsec_msg_type अणु
	macsec_cfg_msg = 0,
	macsec_add_rx_sc_msg,
	macsec_add_tx_sc_msg,
	macsec_add_rx_sa_msg,
	macsec_add_tx_sa_msg,
	macsec_get_stats_msg,
पूर्ण;

काष्ठा __packed macsec_cfg_request अणु
	u32 enabled;
	u32 egress_threshold;
	u32 ingress_threshold;
	u32 पूर्णांकerrupts_enabled;
पूर्ण;

काष्ठा __packed macsec_msg_fw_request अणु
	u32 msg_id; /* not used */
	u32 msg_type;
	काष्ठा macsec_cfg_request cfg;
पूर्ण;

काष्ठा __packed macsec_msg_fw_response अणु
	u32 result;
पूर्ण;

क्रमागत hw_atl_rx_action_with_traffic अणु
	HW_ATL_RX_DISCARD,
	HW_ATL_RX_HOST,
	HW_ATL_RX_MNGMNT,
	HW_ATL_RX_HOST_AND_MNGMNT,
	HW_ATL_RX_WOL
पूर्ण;

काष्ठा aq_rx_filter_vlan अणु
	u8 enable;
	u8 location;
	u16 vlan_id;
	u8 queue;
पूर्ण;

#घोषणा HW_ATL_VLAN_MAX_FILTERS         16U

काष्ठा aq_rx_filter_l2 अणु
	s8 queue;
	u8 location;
	u8 user_priority_en;
	u8 user_priority;
	u16 ethertype;
पूर्ण;

काष्ठा aq_rx_filter_l3l4 अणु
	u32 cmd;
	u8 location;
	u32 ip_dst[4];
	u32 ip_src[4];
	u16 p_dst;
	u16 p_src;
	u8 is_ipv6;
पूर्ण;

क्रमागत hw_atl_rx_protocol_value_l3l4 अणु
	HW_ATL_RX_TCP,
	HW_ATL_RX_UDP,
	HW_ATL_RX_SCTP,
	HW_ATL_RX_ICMP
पूर्ण;

क्रमागत hw_atl_rx_ctrl_रेजिस्टरs_l3l4 अणु
	HW_ATL_RX_ENABLE_MNGMNT_QUEUE_L3L4 = BIT(22),
	HW_ATL_RX_ENABLE_QUEUE_L3L4        = BIT(23),
	HW_ATL_RX_ENABLE_ARP_FLTR_L3       = BIT(24),
	HW_ATL_RX_ENABLE_CMP_PROT_L4       = BIT(25),
	HW_ATL_RX_ENABLE_CMP_DEST_PORT_L4  = BIT(26),
	HW_ATL_RX_ENABLE_CMP_SRC_PORT_L4   = BIT(27),
	HW_ATL_RX_ENABLE_CMP_DEST_ADDR_L3  = BIT(28),
	HW_ATL_RX_ENABLE_CMP_SRC_ADDR_L3   = BIT(29),
	HW_ATL_RX_ENABLE_L3_IPV6           = BIT(30),
	HW_ATL_RX_ENABLE_FLTR_L3L4         = BIT(31)
पूर्ण;

#घोषणा HW_ATL_RX_QUEUE_FL3L4_SHIFT       8U
#घोषणा HW_ATL_RX_ACTION_FL3F4_SHIFT      16U

#घोषणा HW_ATL_RX_CNT_REG_ADDR_IPV6       4U

#घोषणा HW_ATL_GET_REG_LOCATION_FL3L4(location) \
	((location) - AQ_RX_FIRST_LOC_FL3L4)

क्रमागत hal_atl_utils_fw_state_e अणु
	MPI_DEINIT = 0,
	MPI_RESET = 1,
	MPI_INIT = 2,
	MPI_POWER = 4,
पूर्ण;

#घोषणा HAL_ATLANTIC_RATE_10G        BIT(0)
#घोषणा HAL_ATLANTIC_RATE_5G         BIT(1)
#घोषणा HAL_ATLANTIC_RATE_5GSR       BIT(2)
#घोषणा HAL_ATLANTIC_RATE_2G5        BIT(3)
#घोषणा HAL_ATLANTIC_RATE_1G         BIT(4)
#घोषणा HAL_ATLANTIC_RATE_100M       BIT(5)
#घोषणा HAL_ATLANTIC_RATE_INVALID    BIT(6)

#घोषणा HAL_ATLANTIC_UTILS_FW_MSG_WOL_ADD       0x4U
#घोषणा HAL_ATLANTIC_UTILS_FW_MSG_WOL_PRIOR     0x10000000U
#घोषणा HAL_ATLANTIC_UTILS_FW_MSG_WOL_PATTERN   0x1U
#घोषणा HAL_ATLANTIC_UTILS_FW_MSG_WOL_MAG_PKT   0x2U
#घोषणा HAL_ATLANTIC_UTILS_FW_MSG_WOL_DEL       0x5U
#घोषणा HAL_ATLANTIC_UTILS_FW_MSG_ENABLE_WAKEUP 0x6U

क्रमागत hw_atl_fw2x_rate अणु
	FW2X_RATE_100M    = 0x20,
	FW2X_RATE_1G      = 0x100,
	FW2X_RATE_2G5     = 0x200,
	FW2X_RATE_5G      = 0x400,
	FW2X_RATE_10G     = 0x800,
पूर्ण;

/* 0x370
 * Link capabilities resolution रेजिस्टर
 */
क्रमागत hw_atl_fw2x_caps_lo अणु
	CAPS_LO_10BASET_HD        = 0,
	CAPS_LO_10BASET_FD,
	CAPS_LO_100BASETX_HD,
	CAPS_LO_100BASET4_HD,
	CAPS_LO_100BASET2_HD,
	CAPS_LO_100BASETX_FD      = 5,
	CAPS_LO_100BASET2_FD,
	CAPS_LO_1000BASET_HD,
	CAPS_LO_1000BASET_FD,
	CAPS_LO_2P5GBASET_FD,
	CAPS_LO_5GBASET_FD        = 10,
	CAPS_LO_10GBASET_FD,
	CAPS_LO_AUTONEG,
	CAPS_LO_SMBUS_READ,
	CAPS_LO_SMBUS_WRITE,
	CAPS_LO_MACSEC            = 15,
	CAPS_LO_RESERVED1,
	CAPS_LO_WAKE_ON_LINK_FORCED,
	CAPS_LO_HIGH_TEMP_WARNING = 29,
	CAPS_LO_DRIVER_SCRATCHPAD = 30,
	CAPS_LO_GLOBAL_FAULT      = 31
पूर्ण;

/* 0x374
 * Status रेजिस्टर
 */
क्रमागत hw_atl_fw2x_caps_hi अणु
	CAPS_HI_TPO2EN            = 0,
	CAPS_HI_10BASET_EEE,
	CAPS_HI_RESERVED2,
	CAPS_HI_PAUSE,
	CAPS_HI_ASYMMETRIC_PAUSE,
	CAPS_HI_100BASETX_EEE     = 5,
	CAPS_HI_PHY_BUF_SEND,
	CAPS_HI_PHY_BUF_RECV,
	CAPS_HI_1000BASET_FD_EEE,
	CAPS_HI_2P5GBASET_FD_EEE,
	CAPS_HI_5GBASET_FD_EEE    = 10,
	CAPS_HI_10GBASET_FD_EEE,
	CAPS_HI_FW_REQUEST,
	CAPS_HI_PHY_LOG,
	CAPS_HI_EEE_AUTO_DISABLE_SETTINGS,
	CAPS_HI_PFC               = 15,
	CAPS_HI_WAKE_ON_LINK,
	CAPS_HI_CABLE_DIAG,
	CAPS_HI_TEMPERATURE,
	CAPS_HI_DOWNSHIFT,
	CAPS_HI_PTP_AVB_EN_FW2X   = 20,
	CAPS_HI_THERMAL_SHUTDOWN,
	CAPS_HI_LINK_DROP,
	CAPS_HI_SLEEP_PROXY,
	CAPS_HI_WOL,
	CAPS_HI_MAC_STOP          = 25,
	CAPS_HI_EXT_LOOPBACK,
	CAPS_HI_INT_LOOPBACK,
	CAPS_HI_EFUSE_AGENT,
	CAPS_HI_WOL_TIMER,
	CAPS_HI_STATISTICS        = 30,
	CAPS_HI_TRANSACTION_ID,
पूर्ण;

/* 0x36C
 * Control रेजिस्टर
 */
क्रमागत hw_atl_fw2x_ctrl अणु
	CTRL_RESERVED1            = 0,
	CTRL_RESERVED2,
	CTRL_RESERVED3,
	CTRL_PAUSE,
	CTRL_ASYMMETRIC_PAUSE,
	CTRL_RESERVED4            = 5,
	CTRL_RESERVED5,
	CTRL_RESERVED6,
	CTRL_1GBASET_FD_EEE,
	CTRL_2P5GBASET_FD_EEE,
	CTRL_5GBASET_FD_EEE       = 10,
	CTRL_10GBASET_FD_EEE,
	CTRL_THERMAL_SHUTDOWN,
	CTRL_PHY_LOGS,
	CTRL_EEE_AUTO_DISABLE,
	CTRL_PFC                  = 15,
	CTRL_WAKE_ON_LINK,
	CTRL_CABLE_DIAG,
	CTRL_TEMPERATURE,
	CTRL_DOWNSHIFT,
	CTRL_PTP_AVB              = 20,
	CTRL_RESERVED7,
	CTRL_LINK_DROP,
	CTRL_SLEEP_PROXY,
	CTRL_WOL,
	CTRL_MAC_STOP             = 25,
	CTRL_EXT_LOOPBACK,
	CTRL_INT_LOOPBACK,
	CTRL_RESERVED8,
	CTRL_WOL_TIMER,
	CTRL_STATISTICS           = 30,
	CTRL_FORCE_RECONNECT,
पूर्ण;

क्रमागत hw_atl_caps_ex अणु
	CAPS_EX_LED_CONTROL       =  0,
	CAPS_EX_LED0_MODE_LO,
	CAPS_EX_LED0_MODE_HI,
	CAPS_EX_LED1_MODE_LO,
	CAPS_EX_LED1_MODE_HI,
	CAPS_EX_LED2_MODE_LO      =  5,
	CAPS_EX_LED2_MODE_HI,
	CAPS_EX_RESERVED07,
	CAPS_EX_RESERVED08,
	CAPS_EX_RESERVED09,
	CAPS_EX_RESERVED10        = 10,
	CAPS_EX_RESERVED11,
	CAPS_EX_RESERVED12,
	CAPS_EX_RESERVED13,
	CAPS_EX_RESERVED14,
	CAPS_EX_RESERVED15        = 15,
	CAPS_EX_PHY_PTP_EN,
	CAPS_EX_MAC_PTP_EN,
	CAPS_EX_EXT_CLK_EN,
	CAPS_EX_SCHED_DMA_EN,
	CAPS_EX_PTP_GPIO_EN       = 20,
	CAPS_EX_UPDATE_SETTINGS,
	CAPS_EX_PHY_CTRL_TS_PIN,
	CAPS_EX_SNR_OPERATING_MARGIN,
	CAPS_EX_RESERVED24,
	CAPS_EX_RESERVED25        = 25,
	CAPS_EX_RESERVED26,
	CAPS_EX_RESERVED27,
	CAPS_EX_RESERVED28,
	CAPS_EX_RESERVED29,
	CAPS_EX_RESERVED30        = 30,
	CAPS_EX_RESERVED31
पूर्ण;

काष्ठा aq_hw_s;
काष्ठा aq_fw_ops;
काष्ठा aq_hw_caps_s;
काष्ठा aq_hw_link_status_s;

पूर्णांक hw_atl_utils_initfw(काष्ठा aq_hw_s *self, स्थिर काष्ठा aq_fw_ops **fw_ops);

पूर्णांक hw_atl_utils_soft_reset(काष्ठा aq_hw_s *self);

व्योम hw_atl_utils_hw_chip_features_init(काष्ठा aq_hw_s *self, u32 *p);

पूर्णांक hw_atl_utils_mpi_पढ़ो_mbox(काष्ठा aq_hw_s *self,
			       काष्ठा hw_atl_utils_mbox_header *pmbox);

व्योम hw_atl_utils_mpi_पढ़ो_stats(काष्ठा aq_hw_s *self,
				 काष्ठा hw_atl_utils_mbox *pmbox);

व्योम hw_atl_utils_mpi_set(काष्ठा aq_hw_s *self,
			  क्रमागत hal_atl_utils_fw_state_e state,
			  u32 speed);

पूर्णांक hw_atl_utils_mpi_get_link_status(काष्ठा aq_hw_s *self);

पूर्णांक hw_atl_utils_get_mac_permanent(काष्ठा aq_hw_s *self,
				   u8 *mac);

अचिन्हित पूर्णांक hw_atl_utils_mbps_2_speed_index(अचिन्हित पूर्णांक mbps);

पूर्णांक hw_atl_utils_hw_get_regs(काष्ठा aq_hw_s *self,
			     स्थिर काष्ठा aq_hw_caps_s *aq_hw_caps,
			     u32 *regs_buff);

पूर्णांक hw_atl_utils_hw_set_घातer(काष्ठा aq_hw_s *self,
			      अचिन्हित पूर्णांक घातer_state);

पूर्णांक hw_atl_utils_hw_deinit(काष्ठा aq_hw_s *self);

u32 hw_atl_utils_get_fw_version(काष्ठा aq_hw_s *self);

पूर्णांक hw_atl_utils_update_stats(काष्ठा aq_hw_s *self);

काष्ठा aq_stats_s *hw_atl_utils_get_hw_stats(काष्ठा aq_hw_s *self);

पूर्णांक hw_atl_utils_fw_करोwnld_dwords(काष्ठा aq_hw_s *self, u32 a,
				  u32 *p, u32 cnt);

पूर्णांक hw_atl_ग_लिखो_fwcfg_dwords(काष्ठा aq_hw_s *self, u32 *p, u32 cnt);

पूर्णांक hw_atl_ग_लिखो_fwsettings_dwords(काष्ठा aq_hw_s *self, u32 offset, u32 *p,
				   u32 cnt);

पूर्णांक hw_atl_utils_fw_set_wol(काष्ठा aq_hw_s *self, bool wol_enabled, u8 *mac);

पूर्णांक hw_atl_utils_fw_rpc_call(काष्ठा aq_hw_s *self, अचिन्हित पूर्णांक rpc_size);

पूर्णांक hw_atl_utils_fw_rpc_रुको(काष्ठा aq_hw_s *self,
			     काष्ठा hw_atl_utils_fw_rpc **rpc);

bool hw_atl_utils_ver_match(u32 ver_expected, u32 ver_actual);

बाह्य स्थिर काष्ठा aq_fw_ops aq_fw_1x_ops;
बाह्य स्थिर काष्ठा aq_fw_ops aq_fw_2x_ops;

#पूर्ण_अगर /* HW_ATL_UTILS_H */
