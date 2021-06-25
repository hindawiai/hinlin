<शैली गुरु>
/************************************************************************
 * s2पन.स: A Linux PCI-X Ethernet driver क्रम Neterion 10GbE Server NIC
 * Copyright(c) 2002-2010 Exar Corp.

 * This software may be used and distributed according to the terms of
 * the GNU General Public License (GPL), incorporated herein by reference.
 * Drivers based on or derived from this code fall under the GPL and must
 * retain the authorship, copyright and license notice.  This file is not
 * a complete program and may only be used when the entire operating
 * प्रणाली is licensed under the GPL.
 * See the file COPYING in this distribution क्रम more inक्रमmation.
 ************************************************************************/
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#अगर_अघोषित _S2IO_H
#घोषणा _S2IO_H

#घोषणा TBD 0
#घोषणा s2BIT(loc)		(0x8000000000000000ULL >> (loc))
#घोषणा vBIT(val, loc, sz)	(((u64)val) << (64-loc-sz))
#घोषणा INV(d)  ((d&0xff)<<24) | (((d>>8)&0xff)<<16) | (((d>>16)&0xff)<<8)| ((d>>24)&0xff)

#अघोषित SUCCESS
#घोषणा SUCCESS 0
#घोषणा FAILURE -1
#घोषणा S2IO_MINUS_ONE 0xFFFFFFFFFFFFFFFFULL
#घोषणा S2IO_DISABLE_MAC_ENTRY 0xFFFFFFFFFFFFULL
#घोषणा S2IO_MAX_PCI_CONFIG_SPACE_REINIT 100
#घोषणा S2IO_BIT_RESET 1
#घोषणा S2IO_BIT_SET 2
#घोषणा CHECKBIT(value, nbit) (value & (1 << nbit))

/* Maximum समय to flicker LED when asked to identअगरy NIC using ethtool */
#घोषणा MAX_FLICKER_TIME	60000 /* 60 Secs */

/* Maximum outstanding splits to be configured पूर्णांकo xena. */
क्रमागत अणु
	XENA_ONE_SPLIT_TRANSACTION = 0,
	XENA_TWO_SPLIT_TRANSACTION = 1,
	XENA_THREE_SPLIT_TRANSACTION = 2,
	XENA_FOUR_SPLIT_TRANSACTION = 3,
	XENA_EIGHT_SPLIT_TRANSACTION = 4,
	XENA_TWELVE_SPLIT_TRANSACTION = 5,
	XENA_SIXTEEN_SPLIT_TRANSACTION = 6,
	XENA_THIRTYTWO_SPLIT_TRANSACTION = 7
पूर्ण;
#घोषणा XENA_MAX_OUTSTANDING_SPLITS(n) (n << 4)

/*  OS concerned variables and स्थिरants */
#घोषणा WATCH_DOG_TIMEOUT		15*HZ
#घोषणा EFILL				0x1234
#घोषणा ALIGN_SIZE			127
#घोषणा	PCIX_COMMAND_REGISTER		0x62

/*
 * Debug related variables.
 */
/* dअगरferent debug levels. */
#घोषणा	ERR_DBG		0
#घोषणा	INIT_DBG	1
#घोषणा	INFO_DBG	2
#घोषणा	TX_DBG		3
#घोषणा	INTR_DBG	4

/* Global variable that defines the present debug level of the driver. */
अटल पूर्णांक debug_level = ERR_DBG;

/* DEBUG message prपूर्णांक. */
#घोषणा DBG_PRINT(dbg_level, fmt, args...) करो अणु			\
	अगर (dbg_level <= debug_level)				\
		pr_info(fmt, ##args);				\
	पूर्ण जबतक (0)

/* Protocol assist features of the NIC */
#घोषणा L3_CKSUM_OK 0xFFFF
#घोषणा L4_CKSUM_OK 0xFFFF
#घोषणा S2IO_JUMBO_SIZE 9600

/* Driver statistics मुख्यtained by driver */
काष्ठा swStat अणु
	अचिन्हित दीर्घ दीर्घ single_ecc_errs;
	अचिन्हित दीर्घ दीर्घ द्विगुन_ecc_errs;
	अचिन्हित दीर्घ दीर्घ parity_err_cnt;
	अचिन्हित दीर्घ दीर्घ serious_err_cnt;
	अचिन्हित दीर्घ दीर्घ soft_reset_cnt;
	अचिन्हित दीर्घ दीर्घ fअगरo_full_cnt;
	अचिन्हित दीर्घ दीर्घ ring_full_cnt[8];
	/* LRO statistics */
	अचिन्हित दीर्घ दीर्घ clubbed_frms_cnt;
	अचिन्हित दीर्घ दीर्घ sending_both;
	अचिन्हित दीर्घ दीर्घ outof_sequence_pkts;
	अचिन्हित दीर्घ दीर्घ flush_max_pkts;
	अचिन्हित दीर्घ दीर्घ sum_avg_pkts_aggregated;
	अचिन्हित दीर्घ दीर्घ num_aggregations;
	/* Other statistics */
	अचिन्हित दीर्घ दीर्घ mem_alloc_fail_cnt;
	अचिन्हित दीर्घ दीर्घ pci_map_fail_cnt;
	अचिन्हित दीर्घ दीर्घ watchकरोg_समयr_cnt;
	अचिन्हित दीर्घ दीर्घ mem_allocated;
	अचिन्हित दीर्घ दीर्घ mem_मुक्तd;
	अचिन्हित दीर्घ दीर्घ link_up_cnt;
	अचिन्हित दीर्घ दीर्घ link_करोwn_cnt;
	अचिन्हित दीर्घ दीर्घ link_up_समय;
	अचिन्हित दीर्घ दीर्घ link_करोwn_समय;

	/* Transfer Code statistics */
	अचिन्हित दीर्घ दीर्घ tx_buf_पात_cnt;
	अचिन्हित दीर्घ दीर्घ tx_desc_पात_cnt;
	अचिन्हित दीर्घ दीर्घ tx_parity_err_cnt;
	अचिन्हित दीर्घ दीर्घ tx_link_loss_cnt;
	अचिन्हित दीर्घ दीर्घ tx_list_proc_err_cnt;

	अचिन्हित दीर्घ दीर्घ rx_parity_err_cnt;
	अचिन्हित दीर्घ दीर्घ rx_पात_cnt;
	अचिन्हित दीर्घ दीर्घ rx_parity_पात_cnt;
	अचिन्हित दीर्घ दीर्घ rx_rda_fail_cnt;
	अचिन्हित दीर्घ दीर्घ rx_unkn_prot_cnt;
	अचिन्हित दीर्घ दीर्घ rx_fcs_err_cnt;
	अचिन्हित दीर्घ दीर्घ rx_buf_size_err_cnt;
	अचिन्हित दीर्घ दीर्घ rx_rxd_corrupt_cnt;
	अचिन्हित दीर्घ दीर्घ rx_unkn_err_cnt;

	/* Error/alarm statistics*/
	अचिन्हित दीर्घ दीर्घ tda_err_cnt;
	अचिन्हित दीर्घ दीर्घ pfc_err_cnt;
	अचिन्हित दीर्घ दीर्घ pcc_err_cnt;
	अचिन्हित दीर्घ दीर्घ tti_err_cnt;
	अचिन्हित दीर्घ दीर्घ lso_err_cnt;
	अचिन्हित दीर्घ दीर्घ tpa_err_cnt;
	अचिन्हित दीर्घ दीर्घ sm_err_cnt;
	अचिन्हित दीर्घ दीर्घ mac_पंचांगac_err_cnt;
	अचिन्हित दीर्घ दीर्घ mac_rmac_err_cnt;
	अचिन्हित दीर्घ दीर्घ xgxs_txgxs_err_cnt;
	अचिन्हित दीर्घ दीर्घ xgxs_rxgxs_err_cnt;
	अचिन्हित दीर्घ दीर्घ rc_err_cnt;
	अचिन्हित दीर्घ दीर्घ prc_pcix_err_cnt;
	अचिन्हित दीर्घ दीर्घ rpa_err_cnt;
	अचिन्हित दीर्घ दीर्घ rda_err_cnt;
	अचिन्हित दीर्घ दीर्घ rti_err_cnt;
	अचिन्हित दीर्घ दीर्घ mc_err_cnt;

पूर्ण;

/* Xpak releated alarm and warnings */
काष्ठा xpakStat अणु
	u64 alarm_transceiver_temp_high;
	u64 alarm_transceiver_temp_low;
	u64 alarm_laser_bias_current_high;
	u64 alarm_laser_bias_current_low;
	u64 alarm_laser_output_घातer_high;
	u64 alarm_laser_output_घातer_low;
	u64 warn_transceiver_temp_high;
	u64 warn_transceiver_temp_low;
	u64 warn_laser_bias_current_high;
	u64 warn_laser_bias_current_low;
	u64 warn_laser_output_घातer_high;
	u64 warn_laser_output_घातer_low;
	u64 xpak_regs_stat;
	u32 xpak_समयr_count;
पूर्ण;


/* The statistics block of Xena */
काष्ठा stat_block अणु
/* Tx MAC statistics counters. */
	__le32 पंचांगac_data_octets;
	__le32 पंचांगac_frms;
	__le64 पंचांगac_drop_frms;
	__le32 पंचांगac_bcst_frms;
	__le32 पंचांगac_mcst_frms;
	__le64 पंचांगac_छोड़ो_ctrl_frms;
	__le32 पंचांगac_ucst_frms;
	__le32 पंचांगac_ttl_octets;
	__le32 पंचांगac_any_err_frms;
	__le32 पंचांगac_nucst_frms;
	__le64 पंचांगac_ttl_less_fb_octets;
	__le64 पंचांगac_vld_ip_octets;
	__le32 पंचांगac_drop_ip;
	__le32 पंचांगac_vld_ip;
	__le32 पंचांगac_rst_tcp;
	__le32 पंचांगac_icmp;
	__le64 पंचांगac_tcp;
	__le32 reserved_0;
	__le32 पंचांगac_udp;

/* Rx MAC Statistics counters. */
	__le32 rmac_data_octets;
	__le32 rmac_vld_frms;
	__le64 rmac_fcs_err_frms;
	__le64 rmac_drop_frms;
	__le32 rmac_vld_bcst_frms;
	__le32 rmac_vld_mcst_frms;
	__le32 rmac_out_rng_len_err_frms;
	__le32 rmac_in_rng_len_err_frms;
	__le64 rmac_दीर्घ_frms;
	__le64 rmac_छोड़ो_ctrl_frms;
	__le64 rmac_unsup_ctrl_frms;
	__le32 rmac_accepted_ucst_frms;
	__le32 rmac_ttl_octets;
	__le32 rmac_discarded_frms;
	__le32 rmac_accepted_nucst_frms;
	__le32 reserved_1;
	__le32 rmac_drop_events;
	__le64 rmac_ttl_less_fb_octets;
	__le64 rmac_ttl_frms;
	__le64 reserved_2;
	__le32 rmac_usized_frms;
	__le32 reserved_3;
	__le32 rmac_frag_frms;
	__le32 rmac_osized_frms;
	__le32 reserved_4;
	__le32 rmac_jabber_frms;
	__le64 rmac_ttl_64_frms;
	__le64 rmac_ttl_65_127_frms;
	__le64 reserved_5;
	__le64 rmac_ttl_128_255_frms;
	__le64 rmac_ttl_256_511_frms;
	__le64 reserved_6;
	__le64 rmac_ttl_512_1023_frms;
	__le64 rmac_ttl_1024_1518_frms;
	__le32 rmac_ip;
	__le32 reserved_7;
	__le64 rmac_ip_octets;
	__le32 rmac_drop_ip;
	__le32 rmac_hdr_err_ip;
	__le32 reserved_8;
	__le32 rmac_icmp;
	__le64 rmac_tcp;
	__le32 rmac_err_drp_udp;
	__le32 rmac_udp;
	__le64 rmac_xgmii_err_sym;
	__le64 rmac_frms_q0;
	__le64 rmac_frms_q1;
	__le64 rmac_frms_q2;
	__le64 rmac_frms_q3;
	__le64 rmac_frms_q4;
	__le64 rmac_frms_q5;
	__le64 rmac_frms_q6;
	__le64 rmac_frms_q7;
	__le16 rmac_full_q3;
	__le16 rmac_full_q2;
	__le16 rmac_full_q1;
	__le16 rmac_full_q0;
	__le16 rmac_full_q7;
	__le16 rmac_full_q6;
	__le16 rmac_full_q5;
	__le16 rmac_full_q4;
	__le32 reserved_9;
	__le32 rmac_छोड़ो_cnt;
	__le64 rmac_xgmii_data_err_cnt;
	__le64 rmac_xgmii_ctrl_err_cnt;
	__le32 rmac_err_tcp;
	__le32 rmac_accepted_ip;

/* PCI/PCI-X Read transaction statistics. */
	__le32 new_rd_req_cnt;
	__le32 rd_req_cnt;
	__le32 rd_rtry_cnt;
	__le32 new_rd_req_rtry_cnt;

/* PCI/PCI-X Write/Read transaction statistics. */
	__le32 wr_req_cnt;
	__le32 wr_rtry_rd_ack_cnt;
	__le32 new_wr_req_rtry_cnt;
	__le32 new_wr_req_cnt;
	__le32 wr_disc_cnt;
	__le32 wr_rtry_cnt;

/*	PCI/PCI-X Write / DMA Transaction statistics. */
	__le32 txp_wr_cnt;
	__le32 rd_rtry_wr_ack_cnt;
	__le32 txd_wr_cnt;
	__le32 txd_rd_cnt;
	__le32 rxd_wr_cnt;
	__le32 rxd_rd_cnt;
	__le32 rxf_wr_cnt;
	__le32 txf_rd_cnt;

/* Tx MAC statistics overflow counters. */
	__le32 पंचांगac_data_octets_oflow;
	__le32 पंचांगac_frms_oflow;
	__le32 पंचांगac_bcst_frms_oflow;
	__le32 पंचांगac_mcst_frms_oflow;
	__le32 पंचांगac_ucst_frms_oflow;
	__le32 पंचांगac_ttl_octets_oflow;
	__le32 पंचांगac_any_err_frms_oflow;
	__le32 पंचांगac_nucst_frms_oflow;
	__le64 पंचांगac_vlan_frms;
	__le32 पंचांगac_drop_ip_oflow;
	__le32 पंचांगac_vld_ip_oflow;
	__le32 पंचांगac_rst_tcp_oflow;
	__le32 पंचांगac_icmp_oflow;
	__le32 tpa_unknown_protocol;
	__le32 पंचांगac_udp_oflow;
	__le32 reserved_10;
	__le32 tpa_parse_failure;

/* Rx MAC Statistics overflow counters. */
	__le32 rmac_data_octets_oflow;
	__le32 rmac_vld_frms_oflow;
	__le32 rmac_vld_bcst_frms_oflow;
	__le32 rmac_vld_mcst_frms_oflow;
	__le32 rmac_accepted_ucst_frms_oflow;
	__le32 rmac_ttl_octets_oflow;
	__le32 rmac_discarded_frms_oflow;
	__le32 rmac_accepted_nucst_frms_oflow;
	__le32 rmac_usized_frms_oflow;
	__le32 rmac_drop_events_oflow;
	__le32 rmac_frag_frms_oflow;
	__le32 rmac_osized_frms_oflow;
	__le32 rmac_ip_oflow;
	__le32 rmac_jabber_frms_oflow;
	__le32 rmac_icmp_oflow;
	__le32 rmac_drop_ip_oflow;
	__le32 rmac_err_drp_udp_oflow;
	__le32 rmac_udp_oflow;
	__le32 reserved_11;
	__le32 rmac_छोड़ो_cnt_oflow;
	__le64 rmac_ttl_1519_4095_frms;
	__le64 rmac_ttl_4096_8191_frms;
	__le64 rmac_ttl_8192_max_frms;
	__le64 rmac_ttl_gt_max_frms;
	__le64 rmac_osized_alt_frms;
	__le64 rmac_jabber_alt_frms;
	__le64 rmac_gt_max_alt_frms;
	__le64 rmac_vlan_frms;
	__le32 rmac_len_discard;
	__le32 rmac_fcs_discard;
	__le32 rmac_pf_discard;
	__le32 rmac_da_discard;
	__le32 rmac_red_discard;
	__le32 rmac_rts_discard;
	__le32 reserved_12;
	__le32 rmac_ingm_full_discard;
	__le32 reserved_13;
	__le32 rmac_accepted_ip_oflow;
	__le32 reserved_14;
	__le32 link_fault_cnt;
	u8  buffer[20];
	काष्ठा swStat sw_stat;
	काष्ठा xpakStat xpak_stat;
पूर्ण;

/* Default value क्रम 'vlan_strip_tag' configuration parameter */
#घोषणा NO_STRIP_IN_PROMISC 2

/*
 * Structures representing dअगरferent init समय configuration
 * parameters of the NIC.
 */

#घोषणा MAX_TX_FIFOS 8
#घोषणा MAX_RX_RINGS 8

#घोषणा FIFO_DEFAULT_NUM	5
#घोषणा FIFO_UDP_MAX_NUM			2 /* 0 - even, 1 -odd ports */
#घोषणा FIFO_OTHER_MAX_NUM			1


#घोषणा MAX_RX_DESC_1  (MAX_RX_RINGS * MAX_RX_BLOCKS_PER_RING * 128)
#घोषणा MAX_RX_DESC_2  (MAX_RX_RINGS * MAX_RX_BLOCKS_PER_RING * 86)
#घोषणा MAX_TX_DESC    (MAX_AVAILABLE_TXDS)

/* FIFO mappings क्रम all possible number of fअगरos configured */
अटल स्थिर पूर्णांक fअगरo_map[][MAX_TX_FIFOS] = अणु
	अणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 1, 1, 1, 1पूर्ण,
	अणु0, 0, 0, 1, 1, 1, 2, 2पूर्ण,
	अणु0, 0, 1, 1, 2, 2, 3, 3पूर्ण,
	अणु0, 0, 1, 1, 2, 2, 3, 4पूर्ण,
	अणु0, 0, 1, 1, 2, 3, 4, 5पूर्ण,
	अणु0, 0, 1, 2, 3, 4, 5, 6पूर्ण,
	अणु0, 1, 2, 3, 4, 5, 6, 7पूर्ण,
पूर्ण;

अटल स्थिर u16 fअगरo_selector[MAX_TX_FIFOS] = अणु0, 1, 3, 3, 7, 7, 7, 7पूर्ण;

/* Maपूर्णांकains Per FIFO related inक्रमmation. */
काष्ठा tx_fअगरo_config अणु
#घोषणा	MAX_AVAILABLE_TXDS	8192
	u32 fअगरo_len;		/* specअगरies len of FIFO up to 8192, ie no of TxDLs */
/* Priority definition */
#घोषणा TX_FIFO_PRI_0               0	/*Highest */
#घोषणा TX_FIFO_PRI_1               1
#घोषणा TX_FIFO_PRI_2               2
#घोषणा TX_FIFO_PRI_3               3
#घोषणा TX_FIFO_PRI_4               4
#घोषणा TX_FIFO_PRI_5               5
#घोषणा TX_FIFO_PRI_6               6
#घोषणा TX_FIFO_PRI_7               7	/*lowest */
	u8 fअगरo_priority;	/* specअगरies poपूर्णांकer level क्रम FIFO */
	/* user should not set twos fअगरos with same pri */
	u8 f_no_snoop;
#घोषणा NO_SNOOP_TXD                0x01
#घोषणा NO_SNOOP_TXD_BUFFER          0x02
पूर्ण;


/* Maपूर्णांकains per Ring related inक्रमmation */
काष्ठा rx_ring_config अणु
	u32 num_rxd;		/*No of RxDs per Rx Ring */
#घोषणा RX_RING_PRI_0               0	/* highest */
#घोषणा RX_RING_PRI_1               1
#घोषणा RX_RING_PRI_2               2
#घोषणा RX_RING_PRI_3               3
#घोषणा RX_RING_PRI_4               4
#घोषणा RX_RING_PRI_5               5
#घोषणा RX_RING_PRI_6               6
#घोषणा RX_RING_PRI_7               7	/* lowest */

	u8 ring_priority;	/*Specअगरies service priority of ring */
	/* OSM should not set any two rings with same priority */
	u8 ring_org;		/*Organization of ring */
#घोषणा RING_ORG_BUFF1		0x01
#घोषणा RX_RING_ORG_BUFF3	0x03
#घोषणा RX_RING_ORG_BUFF5	0x05

	u8 f_no_snoop;
#घोषणा NO_SNOOP_RXD                0x01
#घोषणा NO_SNOOP_RXD_BUFFER         0x02
पूर्ण;

/* This काष्ठाure provides contains values of the tunable parameters
 * of the H/W
 */
काष्ठा config_param अणु
/* Tx Side */
	u32 tx_fअगरo_num;	/*Number of Tx FIFOs */

	/* 0-No steering, 1-Priority steering, 2-Default fअगरo map */
#घोषणा	NO_STEERING				0
#घोषणा	TX_PRIORITY_STEERING			0x1
#घोषणा TX_DEFAULT_STEERING 			0x2
	u8 tx_steering_type;

	u8 fअगरo_mapping[MAX_TX_FIFOS];
	काष्ठा tx_fअगरo_config tx_cfg[MAX_TX_FIFOS];	/*Per-Tx FIFO config */
	u32 max_txds;		/*Max no. of Tx buffer descriptor per TxDL */
	u64 tx_पूर्णांकr_type;
#घोषणा INTA	0
#घोषणा MSI_X	2
	u8 पूर्णांकr_type;
	u8 napi;

	/* Specअगरies अगर Tx Intr is UTILZ or PER_LIST type. */

/* Rx Side */
	u32 rx_ring_num;	/*Number of receive rings */
#घोषणा MAX_RX_BLOCKS_PER_RING  150

	काष्ठा rx_ring_config rx_cfg[MAX_RX_RINGS];	/*Per-Rx Ring config */

#घोषणा HEADER_ETHERNET_II_802_3_SIZE 14
#घोषणा HEADER_802_2_SIZE              3
#घोषणा HEADER_SNAP_SIZE               5
#घोषणा HEADER_VLAN_SIZE               4

#घोषणा MIN_MTU                       46
#घोषणा MAX_PYLD                    1500
#घोषणा MAX_MTU                     (MAX_PYLD+18)
#घोषणा MAX_MTU_VLAN                (MAX_PYLD+22)
#घोषणा MAX_PYLD_JUMBO              9600
#घोषणा MAX_MTU_JUMBO               (MAX_PYLD_JUMBO+18)
#घोषणा MAX_MTU_JUMBO_VLAN          (MAX_PYLD_JUMBO+22)
	u16 bus_speed;
	पूर्णांक max_mc_addr;	/* xena=64 herc=256 */
	पूर्णांक max_mac_addr;	/* xena=16 herc=64 */
	पूर्णांक mc_start_offset;	/* xena=16 herc=64 */
	u8 multiq;
पूर्ण;

/* Structure representing MAC Addrs */
काष्ठा mac_addr अणु
	u8 mac_addr[ETH_ALEN];
पूर्ण;

/* Structure that represent every FIFO element in the BAR1
 * Address location.
 */
काष्ठा TxFIFO_element अणु
	u64 TxDL_Poपूर्णांकer;

	u64 List_Control;
#घोषणा TX_FIFO_LAST_TXD_NUM( val)     vBIT(val,0,8)
#घोषणा TX_FIFO_FIRST_LIST             s2BIT(14)
#घोषणा TX_FIFO_LAST_LIST              s2BIT(15)
#घोषणा TX_FIFO_FIRSTNLAST_LIST        vBIT(3,14,2)
#घोषणा TX_FIFO_SPECIAL_FUNC           s2BIT(23)
#घोषणा TX_FIFO_DS_NO_SNOOP            s2BIT(31)
#घोषणा TX_FIFO_BUFF_NO_SNOOP          s2BIT(30)
पूर्ण;

/* Tx descriptor काष्ठाure */
काष्ठा TxD अणु
	u64 Control_1;
/* bit mask */
#घोषणा TXD_LIST_OWN_XENA       s2BIT(7)
#घोषणा TXD_T_CODE              (s2BIT(12)|s2BIT(13)|s2BIT(14)|s2BIT(15))
#घोषणा TXD_T_CODE_OK(val)      (|(val & TXD_T_CODE))
#घोषणा GET_TXD_T_CODE(val)     ((val & TXD_T_CODE)<<12)
#घोषणा TXD_GATHER_CODE         (s2BIT(22) | s2BIT(23))
#घोषणा TXD_GATHER_CODE_FIRST   s2BIT(22)
#घोषणा TXD_GATHER_CODE_LAST    s2BIT(23)
#घोषणा TXD_TCP_LSO_EN          s2BIT(30)
#घोषणा TXD_UDP_COF_EN          s2BIT(31)
#घोषणा TXD_UFO_EN		s2BIT(31) | s2BIT(30)
#घोषणा TXD_TCP_LSO_MSS(val)    vBIT(val,34,14)
#घोषणा TXD_UFO_MSS(val)	vBIT(val,34,14)
#घोषणा TXD_BUFFER0_SIZE(val)   vBIT(val,48,16)

	u64 Control_2;
#घोषणा TXD_TX_CKO_CONTROL      (s2BIT(5)|s2BIT(6)|s2BIT(7))
#घोषणा TXD_TX_CKO_IPV4_EN      s2BIT(5)
#घोषणा TXD_TX_CKO_TCP_EN       s2BIT(6)
#घोषणा TXD_TX_CKO_UDP_EN       s2BIT(7)
#घोषणा TXD_VLAN_ENABLE         s2BIT(15)
#घोषणा TXD_VLAN_TAG(val)       vBIT(val,16,16)
#घोषणा TXD_INT_NUMBER(val)     vBIT(val,34,6)
#घोषणा TXD_INT_TYPE_PER_LIST   s2BIT(47)
#घोषणा TXD_INT_TYPE_UTILZ      s2BIT(46)
#घोषणा TXD_SET_MARKER         vBIT(0x6,0,4)

	u64 Buffer_Poपूर्णांकer;
	u64 Host_Control;	/* reserved क्रम host */
पूर्ण;

/* Structure to hold the phy and virt addr of every TxDL. */
काष्ठा list_info_hold अणु
	dma_addr_t list_phy_addr;
	व्योम *list_virt_addr;
पूर्ण;

/* Rx descriptor काष्ठाure क्रम 1 buffer mode */
काष्ठा RxD_t अणु
	u64 Host_Control;	/* reserved क्रम host */
	u64 Control_1;
#घोषणा RXD_OWN_XENA            s2BIT(7)
#घोषणा RXD_T_CODE              (s2BIT(12)|s2BIT(13)|s2BIT(14)|s2BIT(15))
#घोषणा RXD_FRAME_PROTO         vBIT(0xFFFF,24,8)
#घोषणा RXD_FRAME_VLAN_TAG      s2BIT(24)
#घोषणा RXD_FRAME_PROTO_IPV4    s2BIT(27)
#घोषणा RXD_FRAME_PROTO_IPV6    s2BIT(28)
#घोषणा RXD_FRAME_IP_FRAG	s2BIT(29)
#घोषणा RXD_FRAME_PROTO_TCP     s2BIT(30)
#घोषणा RXD_FRAME_PROTO_UDP     s2BIT(31)
#घोषणा TCP_OR_UDP_FRAME        (RXD_FRAME_PROTO_TCP | RXD_FRAME_PROTO_UDP)
#घोषणा RXD_GET_L3_CKSUM(val)   ((u16)(val>> 16) & 0xFFFF)
#घोषणा RXD_GET_L4_CKSUM(val)   ((u16)(val) & 0xFFFF)

	u64 Control_2;
#घोषणा	THE_RXD_MARK		0x3
#घोषणा	SET_RXD_MARKER		vBIT(THE_RXD_MARK, 0, 2)
#घोषणा	GET_RXD_MARKER(ctrl)	((ctrl & SET_RXD_MARKER) >> 62)

#घोषणा MASK_VLAN_TAG           vBIT(0xFFFF,48,16)
#घोषणा SET_VLAN_TAG(val)       vBIT(val,48,16)
#घोषणा SET_NUM_TAG(val)       vBIT(val,16,32)


पूर्ण;
/* Rx descriptor काष्ठाure क्रम 1 buffer mode */
काष्ठा RxD1 अणु
	काष्ठा RxD_t h;

#घोषणा MASK_BUFFER0_SIZE_1       vBIT(0x3FFF,2,14)
#घोषणा SET_BUFFER0_SIZE_1(val)   vBIT(val,2,14)
#घोषणा RXD_GET_BUFFER0_SIZE_1(_Control_2) \
	(u16)((_Control_2 & MASK_BUFFER0_SIZE_1) >> 48)
	u64 Buffer0_ptr;
पूर्ण;
/* Rx descriptor काष्ठाure क्रम 3 or 2 buffer mode */

काष्ठा RxD3 अणु
	काष्ठा RxD_t h;

#घोषणा MASK_BUFFER0_SIZE_3       vBIT(0xFF,2,14)
#घोषणा MASK_BUFFER1_SIZE_3       vBIT(0xFFFF,16,16)
#घोषणा MASK_BUFFER2_SIZE_3       vBIT(0xFFFF,32,16)
#घोषणा SET_BUFFER0_SIZE_3(val)   vBIT(val,8,8)
#घोषणा SET_BUFFER1_SIZE_3(val)   vBIT(val,16,16)
#घोषणा SET_BUFFER2_SIZE_3(val)   vBIT(val,32,16)
#घोषणा RXD_GET_BUFFER0_SIZE_3(Control_2) \
	(u8)((Control_2 & MASK_BUFFER0_SIZE_3) >> 48)
#घोषणा RXD_GET_BUFFER1_SIZE_3(Control_2) \
	(u16)((Control_2 & MASK_BUFFER1_SIZE_3) >> 32)
#घोषणा RXD_GET_BUFFER2_SIZE_3(Control_2) \
	(u16)((Control_2 & MASK_BUFFER2_SIZE_3) >> 16)
#घोषणा BUF0_LEN	40
#घोषणा BUF1_LEN	1

	u64 Buffer0_ptr;
	u64 Buffer1_ptr;
	u64 Buffer2_ptr;
पूर्ण;


/* Structure that represents the Rx descriptor block which contains
 * 128 Rx descriptors.
 */
काष्ठा RxD_block अणु
#घोषणा MAX_RXDS_PER_BLOCK_1            127
	काष्ठा RxD1 rxd[MAX_RXDS_PER_BLOCK_1];

	u64 reserved_0;
#घोषणा END_OF_BLOCK    0xFEFFFFFFFFFFFFFFULL
	u64 reserved_1;		/* 0xFEFFFFFFFFFFFFFF to mark last
				 * Rxd in this blk */
	u64 reserved_2_pNext_RxD_block;	/* Logical ptr to next */
	u64 pNext_RxD_Blk_physical;	/* Buff0_ptr.In a 32 bit arch
					 * the upper 32 bits should
					 * be 0 */
पूर्ण;

#घोषणा SIZE_OF_BLOCK	4096

#घोषणा RXD_MODE_1	0 /* One Buffer mode */
#घोषणा RXD_MODE_3B	1 /* Two Buffer mode */

/* Structure to hold भव addresses of Buf0 and Buf1 in
 * 2buf mode. */
काष्ठा buffAdd अणु
	व्योम *ba_0_org;
	व्योम *ba_1_org;
	व्योम *ba_0;
	व्योम *ba_1;
पूर्ण;

/* Structure which stores all the MAC control parameters */

/* This काष्ठाure stores the offset of the RxD in the ring
 * from which the Rx Interrupt processor can start picking
 * up the RxDs क्रम processing.
 */
काष्ठा rx_curr_get_info अणु
	u32 block_index;
	u32 offset;
	u32 ring_len;
पूर्ण;

काष्ठा rx_curr_put_info अणु
	u32 block_index;
	u32 offset;
	u32 ring_len;
पूर्ण;

/* This काष्ठाure stores the offset of the TxDl in the FIFO
 * from which the Tx Interrupt processor can start picking
 * up the TxDLs क्रम send complete पूर्णांकerrupt processing.
 */
काष्ठा tx_curr_get_info अणु
	u32 offset;
	u32 fअगरo_len;
पूर्ण;

काष्ठा tx_curr_put_info अणु
	u32 offset;
	u32 fअगरo_len;
पूर्ण;

काष्ठा rxd_info अणु
	व्योम *virt_addr;
	dma_addr_t dma_addr;
पूर्ण;

/* Structure that holds the Phy and virt addresses of the Blocks */
काष्ठा rx_block_info अणु
	व्योम *block_virt_addr;
	dma_addr_t block_dma_addr;
	काष्ठा rxd_info *rxds;
पूर्ण;

/* Data काष्ठाure to represent a LRO session */
काष्ठा lro अणु
	काष्ठा sk_buff	*parent;
	काष्ठा sk_buff  *last_frag;
	u8		*l2h;
	काष्ठा iphdr	*iph;
	काष्ठा tcphdr	*tcph;
	u32		tcp_next_seq;
	__be32		tcp_ack;
	पूर्णांक		total_len;
	पूर्णांक		frags_len;
	पूर्णांक		sg_num;
	पूर्णांक		in_use;
	__be16		winकरोw;
	u16             vlan_tag;
	u32		cur_tsval;
	__be32		cur_tsecr;
	u8		saw_ts;
पूर्ण ____cacheline_aligned;

/* Ring specअगरic काष्ठाure */
काष्ठा ring_info अणु
	/* The ring number */
	पूर्णांक ring_no;

	/* per-ring buffer counter */
	u32 rx_bufs_left;

#घोषणा MAX_LRO_SESSIONS       32
	काष्ठा lro lro0_n[MAX_LRO_SESSIONS];
	u8		lro;

	/* copy of sp->rxd_mode flag */
	पूर्णांक rxd_mode;

	/* Number of rxds per block क्रम the rxd_mode */
	पूर्णांक rxd_count;

	/* copy of sp poपूर्णांकer */
	काष्ठा s2io_nic *nic;

	/* copy of sp->dev poपूर्णांकer */
	काष्ठा net_device *dev;

	/* copy of sp->pdev poपूर्णांकer */
	काष्ठा pci_dev *pdev;

	/* Per ring napi काष्ठा */
	काष्ठा napi_काष्ठा napi;

	अचिन्हित दीर्घ पूर्णांकerrupt_count;

	/*
	 *  Place holders क्रम the भव and physical addresses of
	 *  all the Rx Blocks
	 */
	काष्ठा rx_block_info rx_blocks[MAX_RX_BLOCKS_PER_RING];
	पूर्णांक block_count;
	पूर्णांक pkt_cnt;

	/*
	 * Put poपूर्णांकer info which indictes which RxD has to be replenished
	 * with a new buffer.
	 */
	काष्ठा rx_curr_put_info rx_curr_put_info;

	/*
	 * Get poपूर्णांकer info which indictes which is the last RxD that was
	 * processed by the driver.
	 */
	काष्ठा rx_curr_get_info rx_curr_get_info;

	/* पूर्णांकerface MTU value */
        अचिन्हित mtu;

	/* Buffer Address store. */
	काष्ठा buffAdd **ba;
पूर्ण ____cacheline_aligned;

/* Fअगरo specअगरic काष्ठाure */
काष्ठा fअगरo_info अणु
	/* FIFO number */
	पूर्णांक fअगरo_no;

	/* Maximum TxDs per TxDL */
	पूर्णांक max_txds;

	/* Place holder of all the TX List's Phy and Virt addresses. */
	काष्ठा list_info_hold *list_info;

	/*
	 * Current offset within the tx FIFO where driver would ग_लिखो
	 * new Tx frame
	 */
	काष्ठा tx_curr_put_info tx_curr_put_info;

	/*
	 * Current offset within tx FIFO from where the driver would start मुक्तing
	 * the buffers
	 */
	काष्ठा tx_curr_get_info tx_curr_get_info;
#घोषणा FIFO_QUEUE_START 0
#घोषणा FIFO_QUEUE_STOP 1
	पूर्णांक queue_state;

	/* copy of sp->dev poपूर्णांकer */
	काष्ठा net_device *dev;

	/* copy of multiq status */
	u8 multiq;

	/* Per fअगरo lock */
	spinlock_t tx_lock;

	/* Per fअगरo UFO in band काष्ठाure */
	u64 *ufo_in_band_v;

	काष्ठा s2io_nic *nic;
पूर्ण ____cacheline_aligned;

/* Inक्रमmation related to the Tx and Rx FIFOs and Rings of Xena
 * is मुख्यtained in this काष्ठाure.
 */
काष्ठा mac_info अणु
/* tx side stuff */
	/* logical poपूर्णांकer of start of each Tx FIFO */
	काष्ठा TxFIFO_element __iomem *tx_FIFO_start[MAX_TX_FIFOS];

	/* Fअगरo specअगरic काष्ठाure */
	काष्ठा fअगरo_info fअगरos[MAX_TX_FIFOS];

	/* Save भव address of TxD page with zero DMA addr(अगर any) */
	व्योम *zerodma_virt_addr;

/* rx side stuff */
	/* Ring specअगरic काष्ठाure */
	काष्ठा ring_info rings[MAX_RX_RINGS];

	u16 rmac_छोड़ो_समय;
	u16 mc_छोड़ो_threshold_q0q3;
	u16 mc_छोड़ो_threshold_q4q7;

	व्योम *stats_mem;	/* orignal poपूर्णांकer to allocated mem */
	dma_addr_t stats_mem_phy;	/* Physical address of the stat block */
	u32 stats_mem_sz;
	काष्ठा stat_block *stats_info;	/* Logical address of the stat block */
पूर्ण;

/* Default Tunable parameters of the NIC. */
#घोषणा DEFAULT_FIFO_0_LEN 4096
#घोषणा DEFAULT_FIFO_1_7_LEN 512
#घोषणा SMALL_BLK_CNT	30
#घोषणा LARGE_BLK_CNT	100

/*
 * Structure to keep track of the MSI-X vectors and the corresponding
 * argument रेजिस्टरed against each vector
 */
#घोषणा MAX_REQUESTED_MSI_X	9
काष्ठा s2io_msix_entry
अणु
	u16 vector;
	u16 entry;
	व्योम *arg;

	u8 type;
#घोषणा        MSIX_ALARM_TYPE         1
#घोषणा        MSIX_RING_TYPE          2

	u8 in_use;
#घोषणा MSIX_REGISTERED_SUCCESS	0xAA
पूर्ण;

काष्ठा msix_info_st अणु
	u64 addr;
	u64 data;
पूर्ण;

/* These flags represent the devices temporary state */
क्रमागत s2io_device_state_t
अणु
	__S2IO_STATE_LINK_TASK=0,
	__S2IO_STATE_CARD_UP
पूर्ण;

/* Structure representing one instance of the NIC */
काष्ठा s2io_nic अणु
	पूर्णांक rxd_mode;
	/*
	 * Count of packets to be processed in a given iteration, it will be indicated
	 * by the quota field of the device काष्ठाure when NAPI is enabled.
	 */
	पूर्णांक pkts_to_process;
	काष्ठा net_device *dev;
	काष्ठा mac_info mac_control;
	काष्ठा config_param config;
	काष्ठा pci_dev *pdev;
	व्योम __iomem *bar0;
	व्योम __iomem *bar1;
#घोषणा MAX_MAC_SUPPORTED   16
#घोषणा MAX_SUPPORTED_MULTICASTS MAX_MAC_SUPPORTED

	काष्ठा mac_addr def_mac_addr[256];

	काष्ठा net_device_stats stats;
	पूर्णांक high_dma_flag;
	पूर्णांक device_enabled_once;

	अक्षर name[60];

	/* Timer that handles I/O errors/exceptions */
	काष्ठा समयr_list alarm_समयr;

	/* Space to back up the PCI config space */
	u32 config_space[256 / माप(u32)];

#घोषणा PROMISC     1
#घोषणा ALL_MULTI   2

#घोषणा MAX_ADDRS_SUPPORTED 64
	u16 mc_addr_count;

	u16 m_cast_flg;
	u16 all_multi_pos;
	u16 promisc_flg;

	/*  Restart समयr, used to restart NIC अगर the device is stuck and
	 *  a schedule task that will set the correct Link state once the
	 *  NIC's PHY has stabilized after a state change.
	 */
	काष्ठा work_काष्ठा rst_समयr_task;
	काष्ठा work_काष्ठा set_link_task;

	/* Flag that can be used to turn on or turn off the Rx checksum
	 * offload feature.
	 */
	पूर्णांक rx_csum;

	/* Below variables are used क्रम fअगरo selection to transmit a packet */
	u16 fअगरo_selector[MAX_TX_FIFOS];

	/* Total fअगरos क्रम tcp packets */
	u8 total_tcp_fअगरos;

	/*
	* Beginning index of udp क्रम udp packets
	* Value will be equal to
	* (tx_fअगरo_num - FIFO_UDP_MAX_NUM - FIFO_OTHER_MAX_NUM)
	*/
	u8 udp_fअगरo_idx;

	u8 total_udp_fअगरos;

	/*
	 * Beginning index of fअगरo क्रम all other packets
	 * Value will be equal to (tx_fअगरo_num - FIFO_OTHER_MAX_NUM)
	*/
	u8 other_fअगरo_idx;

	काष्ठा napi_काष्ठा napi;
	/*  after blink, the adapter must be restored with original
	 *  values.
	 */
	u64 adapt_ctrl_org;

	/* Last known link state. */
	u16 last_link_state;
#घोषणा	LINK_DOWN	1
#घोषणा	LINK_UP		2

	पूर्णांक task_flag;
	अचिन्हित दीर्घ दीर्घ start_समय;
	पूर्णांक vlan_strip_flag;
#घोषणा MSIX_FLG                0xA5
	पूर्णांक num_entries;
	काष्ठा msix_entry *entries;
	पूर्णांक msi_detected;
	रुको_queue_head_t msi_रुको;
	काष्ठा s2io_msix_entry *s2io_entries;
	अक्षर desc[MAX_REQUESTED_MSI_X][25];

	पूर्णांक avail_msix_vectors; /* No. of MSI-X vectors granted by प्रणाली */

	काष्ठा msix_info_st msix_info[0x3f];

#घोषणा XFRAME_I_DEVICE		1
#घोषणा XFRAME_II_DEVICE	2
	u8 device_type;

	अचिन्हित दीर्घ	clubbed_frms_cnt;
	अचिन्हित दीर्घ	sending_both;
	u16		lro_max_aggr_per_sess;
	अस्थिर अचिन्हित दीर्घ state;
	u64		general_पूर्णांक_mask;

#घोषणा VPD_STRING_LEN 80
	u8  product_name[VPD_STRING_LEN];
	u8  serial_num[VPD_STRING_LEN];
पूर्ण;

#घोषणा RESET_ERROR 1
#घोषणा CMD_ERROR   2

/*
 * Some रेजिस्टरs have to be written in a particular order to
 * expect correct hardware operation. The macro SPECIAL_REG_WRITE
 * is used to perक्रमm such ordered ग_लिखोs. Defines UF (Upper First)
 * and LF (Lower First) will be used to specअगरy the required ग_लिखो order.
 */
#घोषणा UF	1
#घोषणा LF	2
अटल अंतरभूत व्योम SPECIAL_REG_WRITE(u64 val, व्योम __iomem *addr, पूर्णांक order)
अणु
	अगर (order == LF) अणु
		ग_लिखोl((u32) (val), addr);
		(व्योम) पढ़ोl(addr);
		ग_लिखोl((u32) (val >> 32), (addr + 4));
		(व्योम) पढ़ोl(addr + 4);
	पूर्ण अन्यथा अणु
		ग_लिखोl((u32) (val >> 32), (addr + 4));
		(व्योम) पढ़ोl(addr + 4);
		ग_लिखोl((u32) (val), addr);
		(व्योम) पढ़ोl(addr);
	पूर्ण
पूर्ण

/*  Interrupt related values of Xena */

#घोषणा ENABLE_INTRS    1
#घोषणा DISABLE_INTRS   2

/*  Highest level पूर्णांकerrupt blocks */
#घोषणा TX_PIC_INTR     (0x0001<<0)
#घोषणा TX_DMA_INTR     (0x0001<<1)
#घोषणा TX_MAC_INTR     (0x0001<<2)
#घोषणा TX_XGXS_INTR    (0x0001<<3)
#घोषणा TX_TRAFFIC_INTR (0x0001<<4)
#घोषणा RX_PIC_INTR     (0x0001<<5)
#घोषणा RX_DMA_INTR     (0x0001<<6)
#घोषणा RX_MAC_INTR     (0x0001<<7)
#घोषणा RX_XGXS_INTR    (0x0001<<8)
#घोषणा RX_TRAFFIC_INTR (0x0001<<9)
#घोषणा MC_INTR         (0x0001<<10)
#घोषणा ENA_ALL_INTRS    (   TX_PIC_INTR     | \
                            TX_DMA_INTR     | \
                            TX_MAC_INTR     | \
                            TX_XGXS_INTR    | \
                            TX_TRAFFIC_INTR | \
                            RX_PIC_INTR     | \
                            RX_DMA_INTR     | \
                            RX_MAC_INTR     | \
                            RX_XGXS_INTR    | \
                            RX_TRAFFIC_INTR | \
                            MC_INTR )

/*  Interrupt masks क्रम the general पूर्णांकerrupt mask रेजिस्टर */
#घोषणा DISABLE_ALL_INTRS   0xFFFFFFFFFFFFFFFFULL

#घोषणा TXPIC_INT_M         s2BIT(0)
#घोषणा TXDMA_INT_M         s2BIT(1)
#घोषणा TXMAC_INT_M         s2BIT(2)
#घोषणा TXXGXS_INT_M        s2BIT(3)
#घोषणा TXTRAFFIC_INT_M     s2BIT(8)
#घोषणा PIC_RX_INT_M        s2BIT(32)
#घोषणा RXDMA_INT_M         s2BIT(33)
#घोषणा RXMAC_INT_M         s2BIT(34)
#घोषणा MC_INT_M            s2BIT(35)
#घोषणा RXXGXS_INT_M        s2BIT(36)
#घोषणा RXTRAFFIC_INT_M     s2BIT(40)

/*  PIC level Interrupts TODO*/

/*  DMA level Inressupts */
#घोषणा TXDMA_PFC_INT_M     s2BIT(0)
#घोषणा TXDMA_PCC_INT_M     s2BIT(2)

/*  PFC block पूर्णांकerrupts */
#घोषणा PFC_MISC_ERR_1      s2BIT(0)	/* Interrupt to indicate FIFO full */

/* PCC block पूर्णांकerrupts. */
#घोषणा	PCC_FB_ECC_ERR	   vBIT(0xff, 16, 8)	/* Interrupt to indicate
						   PCC_FB_ECC Error. */

#घोषणा RXD_GET_VLAN_TAG(Control_2) (u16)(Control_2 & MASK_VLAN_TAG)
/*
 * Prototype declaration.
 */
अटल पूर्णांक s2io_init_nic(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *pre);
अटल व्योम s2io_rem_nic(काष्ठा pci_dev *pdev);
अटल पूर्णांक init_shared_mem(काष्ठा s2io_nic *sp);
अटल व्योम मुक्त_shared_mem(काष्ठा s2io_nic *sp);
अटल पूर्णांक init_nic(काष्ठा s2io_nic *nic);
अटल पूर्णांक rx_पूर्णांकr_handler(काष्ठा ring_info *ring_data, पूर्णांक budget);
अटल व्योम s2io_txpic_पूर्णांकr_handle(काष्ठा s2io_nic *sp);
अटल व्योम tx_पूर्णांकr_handler(काष्ठा fअगरo_info *fअगरo_data);
अटल व्योम s2io_handle_errors(व्योम * dev_id);

अटल व्योम s2io_tx_watchकरोg(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम s2io_set_multicast(काष्ठा net_device *dev, bool may_sleep);
अटल पूर्णांक rx_osm_handler(काष्ठा ring_info *ring_data, काष्ठा RxD_t * rxdp);
अटल व्योम s2io_link(काष्ठा s2io_nic * sp, पूर्णांक link);
अटल व्योम s2io_reset(काष्ठा s2io_nic * sp);
अटल पूर्णांक s2io_poll_msix(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
अटल पूर्णांक s2io_poll_पूर्णांकa(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
अटल व्योम s2io_init_pci(काष्ठा s2io_nic * sp);
अटल पूर्णांक करो_s2io_prog_unicast(काष्ठा net_device *dev, u8 *addr);
अटल व्योम s2io_alarm_handle(काष्ठा समयr_list *t);
अटल irqवापस_t
s2io_msix_ring_handle(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t
s2io_msix_fअगरo_handle(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t s2io_isr(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक verअगरy_xena_quiescence(काष्ठा s2io_nic *sp);
अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops;
अटल व्योम s2io_set_link(काष्ठा work_काष्ठा *work);
अटल पूर्णांक s2io_set_swapper(काष्ठा s2io_nic * sp);
अटल व्योम s2io_card_करोwn(काष्ठा s2io_nic *nic);
अटल पूर्णांक s2io_card_up(काष्ठा s2io_nic *nic);
अटल पूर्णांक रुको_क्रम_cmd_complete(व्योम __iomem *addr, u64 busy_bit,
				 पूर्णांक bit_state, bool may_sleep);
अटल पूर्णांक s2io_add_isr(काष्ठा s2io_nic * sp);
अटल व्योम s2io_rem_isr(काष्ठा s2io_nic * sp);

अटल व्योम restore_xmsi_data(काष्ठा s2io_nic *nic);
अटल व्योम करो_s2io_store_unicast_mc(काष्ठा s2io_nic *sp);
अटल व्योम करो_s2io_restore_unicast_mc(काष्ठा s2io_nic *sp);
अटल u64 करो_s2io_पढ़ो_unicast_mc(काष्ठा s2io_nic *sp, पूर्णांक offset);
अटल पूर्णांक करो_s2io_add_mc(काष्ठा s2io_nic *sp, u8 *addr);
अटल पूर्णांक करो_s2io_add_mac(काष्ठा s2io_nic *sp, u64 addr, पूर्णांक offset);
अटल पूर्णांक करो_s2io_delete_unicast_mc(काष्ठा s2io_nic *sp, u64 addr);

अटल पूर्णांक s2io_club_tcp_session(काष्ठा ring_info *ring_data, u8 *buffer,
	u8 **tcp, u32 *tcp_len, काष्ठा lro **lro, काष्ठा RxD_t *rxdp,
	काष्ठा s2io_nic *sp);
अटल व्योम clear_lro_session(काष्ठा lro *lro);
अटल व्योम queue_rx_frame(काष्ठा sk_buff *skb, u16 vlan_tag);
अटल व्योम update_L3L4_header(काष्ठा s2io_nic *sp, काष्ठा lro *lro);
अटल व्योम lro_append_pkt(काष्ठा s2io_nic *sp, काष्ठा lro *lro,
			   काष्ठा sk_buff *skb, u32 tcp_len);
अटल पूर्णांक rts_ds_steer(काष्ठा s2io_nic *nic, u8 ds_codepoपूर्णांक, u8 ring);

अटल pci_ers_result_t s2io_io_error_detected(काष्ठा pci_dev *pdev,
			                      pci_channel_state_t state);
अटल pci_ers_result_t s2io_io_slot_reset(काष्ठा pci_dev *pdev);
अटल व्योम s2io_io_resume(काष्ठा pci_dev *pdev);

#घोषणा s2io_tcp_mss(skb) skb_shinfo(skb)->gso_size
#घोषणा s2io_udp_mss(skb) skb_shinfo(skb)->gso_size
#घोषणा s2io_offload_type(skb) skb_shinfo(skb)->gso_type

#घोषणा S2IO_PARM_INT(X, def_val) \
	अटल अचिन्हित पूर्णांक X = def_val;\
		module_param(X , uपूर्णांक, 0);

#पूर्ण_अगर				/* _S2IO_H */
