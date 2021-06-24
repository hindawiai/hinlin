<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*******************************************************************************
  STMMAC Common Header File

  Copyright (C) 2007-2009  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#अगर_अघोषित __COMMON_H__
#घोषणा __COMMON_H__

#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/sपंचांगmac.h>
#समावेश <linux/phy.h>
#समावेश <linux/pcs/pcs-xpcs.h>
#समावेश <linux/module.h>
#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
#घोषणा STMMAC_VLAN_TAG_USED
#समावेश <linux/अगर_vlan.h>
#पूर्ण_अगर

#समावेश "descs.h"
#समावेश "hwif.h"
#समावेश "mmc.h"

/* Synopsys Core versions */
#घोषणा	DWMAC_CORE_3_40		0x34
#घोषणा	DWMAC_CORE_3_50		0x35
#घोषणा	DWMAC_CORE_4_00		0x40
#घोषणा DWMAC_CORE_4_10		0x41
#घोषणा DWMAC_CORE_5_00		0x50
#घोषणा DWMAC_CORE_5_10		0x51
#घोषणा DWMAC_CORE_5_20		0x52
#घोषणा DWXGMAC_CORE_2_10	0x21
#घोषणा DWXLGMAC_CORE_2_00	0x20

/* Device ID */
#घोषणा DWXGMAC_ID		0x76
#घोषणा DWXLGMAC_ID		0x27

#घोषणा STMMAC_CHAN0	0	/* Always supported and शेष क्रम all chips */

/* TX and RX Descriptor Length, these need to be घातer of two.
 * TX descriptor length less than 64 may cause transmit queue समयd out error.
 * RX descriptor length less than 64 may cause inconsistent Rx chain error.
 */
#घोषणा DMA_MIN_TX_SIZE		64
#घोषणा DMA_MAX_TX_SIZE		1024
#घोषणा DMA_DEFAULT_TX_SIZE	512
#घोषणा DMA_MIN_RX_SIZE		64
#घोषणा DMA_MAX_RX_SIZE		1024
#घोषणा DMA_DEFAULT_RX_SIZE	512
#घोषणा STMMAC_GET_ENTRY(x, size)	((x + 1) & (size - 1))

#अघोषित FRAME_FILTER_DEBUG
/* #घोषणा FRAME_FILTER_DEBUG */

/* Extra statistic and debug inक्रमmation exposed by ethtool */
काष्ठा sपंचांगmac_extra_stats अणु
	/* Transmit errors */
	अचिन्हित दीर्घ tx_underflow ____cacheline_aligned;
	अचिन्हित दीर्घ tx_carrier;
	अचिन्हित दीर्घ tx_losscarrier;
	अचिन्हित दीर्घ vlan_tag;
	अचिन्हित दीर्घ tx_deferred;
	अचिन्हित दीर्घ tx_vlan;
	अचिन्हित दीर्घ tx_jabber;
	अचिन्हित दीर्घ tx_frame_flushed;
	अचिन्हित दीर्घ tx_payload_error;
	अचिन्हित दीर्घ tx_ip_header_error;
	/* Receive errors */
	अचिन्हित दीर्घ rx_desc;
	अचिन्हित दीर्घ sa_filter_fail;
	अचिन्हित दीर्घ overflow_error;
	अचिन्हित दीर्घ ipc_csum_error;
	अचिन्हित दीर्घ rx_collision;
	अचिन्हित दीर्घ rx_crc_errors;
	अचिन्हित दीर्घ dribbling_bit;
	अचिन्हित दीर्घ rx_length;
	अचिन्हित दीर्घ rx_mii;
	अचिन्हित दीर्घ rx_multicast;
	अचिन्हित दीर्घ rx_gmac_overflow;
	अचिन्हित दीर्घ rx_watchकरोg;
	अचिन्हित दीर्घ da_rx_filter_fail;
	अचिन्हित दीर्घ sa_rx_filter_fail;
	अचिन्हित दीर्घ rx_missed_cntr;
	अचिन्हित दीर्घ rx_overflow_cntr;
	अचिन्हित दीर्घ rx_vlan;
	अचिन्हित दीर्घ rx_split_hdr_pkt_n;
	/* Tx/Rx IRQ error info */
	अचिन्हित दीर्घ tx_undeflow_irq;
	अचिन्हित दीर्घ tx_process_stopped_irq;
	अचिन्हित दीर्घ tx_jabber_irq;
	अचिन्हित दीर्घ rx_overflow_irq;
	अचिन्हित दीर्घ rx_buf_unav_irq;
	अचिन्हित दीर्घ rx_process_stopped_irq;
	अचिन्हित दीर्घ rx_watchकरोg_irq;
	अचिन्हित दीर्घ tx_early_irq;
	अचिन्हित दीर्घ fatal_bus_error_irq;
	/* Tx/Rx IRQ Events */
	अचिन्हित दीर्घ rx_early_irq;
	अचिन्हित दीर्घ threshold;
	अचिन्हित दीर्घ tx_pkt_n;
	अचिन्हित दीर्घ rx_pkt_n;
	अचिन्हित दीर्घ normal_irq_n;
	अचिन्हित दीर्घ rx_normal_irq_n;
	अचिन्हित दीर्घ napi_poll;
	अचिन्हित दीर्घ tx_normal_irq_n;
	अचिन्हित दीर्घ tx_clean;
	अचिन्हित दीर्घ tx_set_ic_bit;
	अचिन्हित दीर्घ irq_receive_pmt_irq_n;
	/* MMC info */
	अचिन्हित दीर्घ mmc_tx_irq_n;
	अचिन्हित दीर्घ mmc_rx_irq_n;
	अचिन्हित दीर्घ mmc_rx_csum_offload_irq_n;
	/* EEE */
	अचिन्हित दीर्घ irq_tx_path_in_lpi_mode_n;
	अचिन्हित दीर्घ irq_tx_path_निकास_lpi_mode_n;
	अचिन्हित दीर्घ irq_rx_path_in_lpi_mode_n;
	अचिन्हित दीर्घ irq_rx_path_निकास_lpi_mode_n;
	अचिन्हित दीर्घ phy_eee_wakeup_error_n;
	/* Extended RDES status */
	अचिन्हित दीर्घ ip_hdr_err;
	अचिन्हित दीर्घ ip_payload_err;
	अचिन्हित दीर्घ ip_csum_bypassed;
	अचिन्हित दीर्घ ipv4_pkt_rcvd;
	अचिन्हित दीर्घ ipv6_pkt_rcvd;
	अचिन्हित दीर्घ no_ptp_rx_msg_type_ext;
	अचिन्हित दीर्घ ptp_rx_msg_type_sync;
	अचिन्हित दीर्घ ptp_rx_msg_type_follow_up;
	अचिन्हित दीर्घ ptp_rx_msg_type_delay_req;
	अचिन्हित दीर्घ ptp_rx_msg_type_delay_resp;
	अचिन्हित दीर्घ ptp_rx_msg_type_pdelay_req;
	अचिन्हित दीर्घ ptp_rx_msg_type_pdelay_resp;
	अचिन्हित दीर्घ ptp_rx_msg_type_pdelay_follow_up;
	अचिन्हित दीर्घ ptp_rx_msg_type_announce;
	अचिन्हित दीर्घ ptp_rx_msg_type_management;
	अचिन्हित दीर्घ ptp_rx_msg_pkt_reserved_type;
	अचिन्हित दीर्घ ptp_frame_type;
	अचिन्हित दीर्घ ptp_ver;
	अचिन्हित दीर्घ बारtamp_dropped;
	अचिन्हित दीर्घ av_pkt_rcvd;
	अचिन्हित दीर्घ av_tagged_pkt_rcvd;
	अचिन्हित दीर्घ vlan_tag_priority_val;
	अचिन्हित दीर्घ l3_filter_match;
	अचिन्हित दीर्घ l4_filter_match;
	अचिन्हित दीर्घ l3_l4_filter_no_match;
	/* PCS */
	अचिन्हित दीर्घ irq_pcs_ane_n;
	अचिन्हित दीर्घ irq_pcs_link_n;
	अचिन्हित दीर्घ irq_rgmii_n;
	अचिन्हित दीर्घ pcs_link;
	अचिन्हित दीर्घ pcs_duplex;
	अचिन्हित दीर्घ pcs_speed;
	/* debug रेजिस्टर */
	अचिन्हित दीर्घ mtl_tx_status_fअगरo_full;
	अचिन्हित दीर्घ mtl_tx_fअगरo_not_empty;
	अचिन्हित दीर्घ mmtl_fअगरo_ctrl;
	अचिन्हित दीर्घ mtl_tx_fअगरo_पढ़ो_ctrl_ग_लिखो;
	अचिन्हित दीर्घ mtl_tx_fअगरo_पढ़ो_ctrl_रुको;
	अचिन्हित दीर्घ mtl_tx_fअगरo_पढ़ो_ctrl_पढ़ो;
	अचिन्हित दीर्घ mtl_tx_fअगरo_पढ़ो_ctrl_idle;
	अचिन्हित दीर्घ mac_tx_in_छोड़ो;
	अचिन्हित दीर्घ mac_tx_frame_ctrl_xfer;
	अचिन्हित दीर्घ mac_tx_frame_ctrl_idle;
	अचिन्हित दीर्घ mac_tx_frame_ctrl_रुको;
	अचिन्हित दीर्घ mac_tx_frame_ctrl_छोड़ो;
	अचिन्हित दीर्घ mac_gmii_tx_proto_engine;
	अचिन्हित दीर्घ mtl_rx_fअगरo_fill_level_full;
	अचिन्हित दीर्घ mtl_rx_fअगरo_fill_above_thresh;
	अचिन्हित दीर्घ mtl_rx_fअगरo_fill_below_thresh;
	अचिन्हित दीर्घ mtl_rx_fअगरo_fill_level_empty;
	अचिन्हित दीर्घ mtl_rx_fअगरo_पढ़ो_ctrl_flush;
	अचिन्हित दीर्घ mtl_rx_fअगरo_पढ़ो_ctrl_पढ़ो_data;
	अचिन्हित दीर्घ mtl_rx_fअगरo_पढ़ो_ctrl_status;
	अचिन्हित दीर्घ mtl_rx_fअगरo_पढ़ो_ctrl_idle;
	अचिन्हित दीर्घ mtl_rx_fअगरo_ctrl_active;
	अचिन्हित दीर्घ mac_rx_frame_ctrl_fअगरo;
	अचिन्हित दीर्घ mac_gmii_rx_proto_engine;
	/* TSO */
	अचिन्हित दीर्घ tx_tso_frames;
	अचिन्हित दीर्घ tx_tso_nfrags;
	/* EST */
	अचिन्हित दीर्घ mtl_est_cgce;
	अचिन्हित दीर्घ mtl_est_hlbs;
	अचिन्हित दीर्घ mtl_est_hlbf;
	अचिन्हित दीर्घ mtl_est_btre;
	अचिन्हित दीर्घ mtl_est_btrlm;
पूर्ण;

/* Safety Feature statistics exposed by ethtool */
काष्ठा sपंचांगmac_safety_stats अणु
	अचिन्हित दीर्घ mac_errors[32];
	अचिन्हित दीर्घ mtl_errors[32];
	अचिन्हित दीर्घ dma_errors[32];
पूर्ण;

/* Number of fields in Safety Stats */
#घोषणा STMMAC_SAFETY_FEAT_SIZE	\
	(माप(काष्ठा sपंचांगmac_safety_stats) / माप(अचिन्हित दीर्घ))

/* CSR Frequency Access Defines*/
#घोषणा CSR_F_35M	35000000
#घोषणा CSR_F_60M	60000000
#घोषणा CSR_F_100M	100000000
#घोषणा CSR_F_150M	150000000
#घोषणा CSR_F_250M	250000000
#घोषणा CSR_F_300M	300000000

#घोषणा	MAC_CSR_H_FRQ_MASK	0x20

#घोषणा HASH_TABLE_SIZE 64
#घोषणा PAUSE_TIME 0xffff

/* Flow Control defines */
#घोषणा FLOW_OFF	0
#घोषणा FLOW_RX		1
#घोषणा FLOW_TX		2
#घोषणा FLOW_AUTO	(FLOW_TX | FLOW_RX)

/* PCS defines */
#घोषणा STMMAC_PCS_RGMII	(1 << 0)
#घोषणा STMMAC_PCS_SGMII	(1 << 1)
#घोषणा STMMAC_PCS_TBI		(1 << 2)
#घोषणा STMMAC_PCS_RTBI		(1 << 3)

#घोषणा SF_DMA_MODE 1		/* DMA STORE-AND-FORWARD Operation Mode */

/* DAM HW feature रेजिस्टर fields */
#घोषणा DMA_HW_FEAT_MIISEL	0x00000001	/* 10/100 Mbps Support */
#घोषणा DMA_HW_FEAT_GMIISEL	0x00000002	/* 1000 Mbps Support */
#घोषणा DMA_HW_FEAT_HDSEL	0x00000004	/* Half-Duplex Support */
#घोषणा DMA_HW_FEAT_EXTHASHEN	0x00000008	/* Expanded DA Hash Filter */
#घोषणा DMA_HW_FEAT_HASHSEL	0x00000010	/* HASH Filter */
#घोषणा DMA_HW_FEAT_ADDMAC	0x00000020	/* Multiple MAC Addr Reg */
#घोषणा DMA_HW_FEAT_PCSSEL	0x00000040	/* PCS रेजिस्टरs */
#घोषणा DMA_HW_FEAT_L3L4FLTREN	0x00000080	/* Layer 3 & Layer 4 Feature */
#घोषणा DMA_HW_FEAT_SMASEL	0x00000100	/* SMA(MDIO) Interface */
#घोषणा DMA_HW_FEAT_RWKSEL	0x00000200	/* PMT Remote Wakeup */
#घोषणा DMA_HW_FEAT_MGKSEL	0x00000400	/* PMT Magic Packet */
#घोषणा DMA_HW_FEAT_MMCSEL	0x00000800	/* RMON Module */
#घोषणा DMA_HW_FEAT_TSVER1SEL	0x00001000	/* Only IEEE 1588-2002 */
#घोषणा DMA_HW_FEAT_TSVER2SEL	0x00002000	/* IEEE 1588-2008 PTPv2 */
#घोषणा DMA_HW_FEAT_EEESEL	0x00004000	/* Energy Efficient Ethernet */
#घोषणा DMA_HW_FEAT_AVSEL	0x00008000	/* AV Feature */
#घोषणा DMA_HW_FEAT_TXCOESEL	0x00010000	/* Checksum Offload in Tx */
#घोषणा DMA_HW_FEAT_RXTYP1COE	0x00020000	/* IP COE (Type 1) in Rx */
#घोषणा DMA_HW_FEAT_RXTYP2COE	0x00040000	/* IP COE (Type 2) in Rx */
#घोषणा DMA_HW_FEAT_RXFIFOSIZE	0x00080000	/* Rx FIFO > 2048 Bytes */
#घोषणा DMA_HW_FEAT_RXCHCNT	0x00300000	/* No. additional Rx Channels */
#घोषणा DMA_HW_FEAT_TXCHCNT	0x00c00000	/* No. additional Tx Channels */
#घोषणा DMA_HW_FEAT_ENHDESSEL	0x01000000	/* Alternate Descriptor */
/* Timestamping with Internal System Time */
#घोषणा DMA_HW_FEAT_INTTSEN	0x02000000
#घोषणा DMA_HW_FEAT_FLEXIPPSEN	0x04000000	/* Flexible PPS Output */
#घोषणा DMA_HW_FEAT_SAVLANINS	0x08000000	/* Source Addr or VLAN */
#घोषणा DMA_HW_FEAT_ACTPHYIF	0x70000000	/* Active/selected PHY अगरace */
#घोषणा DEFAULT_DMA_PBL		8

/* MSI defines */
#घोषणा STMMAC_MSI_VEC_MAX	32

/* PCS status and mask defines */
#घोषणा	PCS_ANE_IRQ		BIT(2)	/* PCS Auto-Negotiation */
#घोषणा	PCS_LINK_IRQ		BIT(1)	/* PCS Link */
#घोषणा	PCS_RGSMIIIS_IRQ	BIT(0)	/* RGMII or SMII Interrupt */

/* Max/Min RI Watchकरोg Timer count value */
#घोषणा MAX_DMA_RIWT		0xff
#घोषणा MIN_DMA_RIWT		0x10
#घोषणा DEF_DMA_RIWT		0xa0
/* Tx coalesce parameters */
#घोषणा STMMAC_COAL_TX_TIMER	1000
#घोषणा STMMAC_MAX_COAL_TX_TICK	100000
#घोषणा STMMAC_TX_MAX_FRAMES	256
#घोषणा STMMAC_TX_FRAMES	25
#घोषणा STMMAC_RX_FRAMES	0

/* Packets types */
क्रमागत packets_types अणु
	PACKET_AVCPQ = 0x1, /* AV Untagged Control packets */
	PACKET_PTPQ = 0x2, /* PTP Packets */
	PACKET_DCBCPQ = 0x3, /* DCB Control Packets */
	PACKET_UPQ = 0x4, /* Untagged Packets */
	PACKET_MCBCQ = 0x5, /* Multicast & Broadcast Packets */
पूर्ण;

/* Rx IPC status */
क्रमागत rx_frame_status अणु
	good_frame = 0x0,
	discard_frame = 0x1,
	csum_none = 0x2,
	llc_snap = 0x4,
	dma_own = 0x8,
	rx_not_ls = 0x10,
पूर्ण;

/* Tx status */
क्रमागत tx_frame_status अणु
	tx_करोne = 0x0,
	tx_not_ls = 0x1,
	tx_err = 0x2,
	tx_dma_own = 0x4,
पूर्ण;

क्रमागत dma_irq_status अणु
	tx_hard_error = 0x1,
	tx_hard_error_bump_tc = 0x2,
	handle_rx = 0x4,
	handle_tx = 0x8,
पूर्ण;

क्रमागत dma_irq_dir अणु
	DMA_सूची_RX = 0x1,
	DMA_सूची_TX = 0x2,
	DMA_सूची_RXTX = 0x3,
पूर्ण;

क्रमागत request_irq_err अणु
	REQ_IRQ_ERR_ALL,
	REQ_IRQ_ERR_TX,
	REQ_IRQ_ERR_RX,
	REQ_IRQ_ERR_SFTY_UE,
	REQ_IRQ_ERR_SFTY_CE,
	REQ_IRQ_ERR_LPI,
	REQ_IRQ_ERR_WOL,
	REQ_IRQ_ERR_MAC,
	REQ_IRQ_ERR_NO,
पूर्ण;

/* EEE and LPI defines */
#घोषणा	CORE_IRQ_TX_PATH_IN_LPI_MODE	(1 << 0)
#घोषणा	CORE_IRQ_TX_PATH_EXIT_LPI_MODE	(1 << 1)
#घोषणा	CORE_IRQ_RX_PATH_IN_LPI_MODE	(1 << 2)
#घोषणा	CORE_IRQ_RX_PATH_EXIT_LPI_MODE	(1 << 3)

/* FPE defines */
#घोषणा FPE_EVENT_UNKNOWN		0
#घोषणा FPE_EVENT_TRSP			BIT(0)
#घोषणा FPE_EVENT_TVER			BIT(1)
#घोषणा FPE_EVENT_RRSP			BIT(2)
#घोषणा FPE_EVENT_RVER			BIT(3)

#घोषणा CORE_IRQ_MTL_RX_OVERFLOW	BIT(8)

/* Physical Coding Sublayer */
काष्ठा rgmii_adv अणु
	अचिन्हित पूर्णांक छोड़ो;
	अचिन्हित पूर्णांक duplex;
	अचिन्हित पूर्णांक lp_छोड़ो;
	अचिन्हित पूर्णांक lp_duplex;
पूर्ण;

#घोषणा STMMAC_PCS_PAUSE	1
#घोषणा STMMAC_PCS_ASYM_PAUSE	2

/* DMA HW capabilities */
काष्ठा dma_features अणु
	अचिन्हित पूर्णांक mbps_10_100;
	अचिन्हित पूर्णांक mbps_1000;
	अचिन्हित पूर्णांक half_duplex;
	अचिन्हित पूर्णांक hash_filter;
	अचिन्हित पूर्णांक multi_addr;
	अचिन्हित पूर्णांक pcs;
	अचिन्हित पूर्णांक sma_mdio;
	अचिन्हित पूर्णांक pmt_remote_wake_up;
	अचिन्हित पूर्णांक pmt_magic_frame;
	अचिन्हित पूर्णांक rmon;
	/* IEEE 1588-2002 */
	अचिन्हित पूर्णांक समय_stamp;
	/* IEEE 1588-2008 */
	अचिन्हित पूर्णांक aसमय_stamp;
	/* 802.3az - Energy-Efficient Ethernet (EEE) */
	अचिन्हित पूर्णांक eee;
	अचिन्हित पूर्णांक av;
	अचिन्हित पूर्णांक hash_tb_sz;
	अचिन्हित पूर्णांक tsoen;
	/* TX and RX csum */
	अचिन्हित पूर्णांक tx_coe;
	अचिन्हित पूर्णांक rx_coe;
	अचिन्हित पूर्णांक rx_coe_type1;
	अचिन्हित पूर्णांक rx_coe_type2;
	अचिन्हित पूर्णांक rxfअगरo_over_2048;
	/* TX and RX number of channels */
	अचिन्हित पूर्णांक number_rx_channel;
	अचिन्हित पूर्णांक number_tx_channel;
	/* TX and RX number of queues */
	अचिन्हित पूर्णांक number_rx_queues;
	अचिन्हित पूर्णांक number_tx_queues;
	/* PPS output */
	अचिन्हित पूर्णांक pps_out_num;
	/* Alternate (enhanced) DESC mode */
	अचिन्हित पूर्णांक enh_desc;
	/* TX and RX FIFO sizes */
	अचिन्हित पूर्णांक tx_fअगरo_size;
	अचिन्हित पूर्णांक rx_fअगरo_size;
	/* Automotive Safety Package */
	अचिन्हित पूर्णांक asp;
	/* RX Parser */
	अचिन्हित पूर्णांक frpsel;
	अचिन्हित पूर्णांक frpbs;
	अचिन्हित पूर्णांक frpes;
	अचिन्हित पूर्णांक addr64;
	अचिन्हित पूर्णांक rssen;
	अचिन्हित पूर्णांक vlhash;
	अचिन्हित पूर्णांक sphen;
	अचिन्हित पूर्णांक vlins;
	अचिन्हित पूर्णांक dvlan;
	अचिन्हित पूर्णांक l3l4fnum;
	अचिन्हित पूर्णांक arpoffsel;
	/* TSN Features */
	अचिन्हित पूर्णांक estwid;
	अचिन्हित पूर्णांक estdep;
	अचिन्हित पूर्णांक estsel;
	अचिन्हित पूर्णांक fpesel;
	अचिन्हित पूर्णांक tbssel;
	/* Numbers of Auxiliary Snapshot Inमाला_दो */
	अचिन्हित पूर्णांक aux_snapshot_n;
पूर्ण;

/* RX Buffer size must be multiple of 4/8/16 bytes */
#घोषणा BUF_SIZE_16KiB 16368
#घोषणा BUF_SIZE_8KiB 8188
#घोषणा BUF_SIZE_4KiB 4096
#घोषणा BUF_SIZE_2KiB 2048

/* Power Down and WOL */
#घोषणा PMT_NOT_SUPPORTED 0
#घोषणा PMT_SUPPORTED 1

/* Common MAC defines */
#घोषणा MAC_CTRL_REG		0x00000000	/* MAC Control */
#घोषणा MAC_ENABLE_TX		0x00000008	/* Transmitter Enable */
#घोषणा MAC_ENABLE_RX		0x00000004	/* Receiver Enable */

/* Default LPI समयrs */
#घोषणा STMMAC_DEFAULT_LIT_LS	0x3E8
#घोषणा STMMAC_DEFAULT_TWT_LS	0x1E
#घोषणा STMMAC_ET_MAX		0xFFFFF

#घोषणा STMMAC_CHAIN_MODE	0x1
#घोषणा STMMAC_RING_MODE	0x2

#घोषणा JUMBO_LEN		9000

/* Receive Side Scaling */
#घोषणा STMMAC_RSS_HASH_KEY_SIZE	40
#घोषणा STMMAC_RSS_MAX_TABLE_SIZE	256

/* VLAN */
#घोषणा STMMAC_VLAN_NONE	0x0
#घोषणा STMMAC_VLAN_REMOVE	0x1
#घोषणा STMMAC_VLAN_INSERT	0x2
#घोषणा STMMAC_VLAN_REPLACE	0x3

बाह्य स्थिर काष्ठा sपंचांगmac_desc_ops enh_desc_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_desc_ops ndesc_ops;

काष्ठा mac_device_info;

बाह्य स्थिर काष्ठा sपंचांगmac_hwबारtamp sपंचांगmac_ptp;
बाह्य स्थिर काष्ठा sपंचांगmac_mode_ops dwmac4_ring_mode_ops;

काष्ठा mac_link अणु
	u32 speed_mask;
	u32 speed10;
	u32 speed100;
	u32 speed1000;
	u32 speed2500;
	u32 duplex;
	काष्ठा अणु
		u32 speed2500;
		u32 speed5000;
		u32 speed10000;
	पूर्ण xgmii;
	काष्ठा अणु
		u32 speed25000;
		u32 speed40000;
		u32 speed50000;
		u32 speed100000;
	पूर्ण xlgmii;
पूर्ण;

काष्ठा mii_regs अणु
	अचिन्हित पूर्णांक addr;	/* MII Address */
	अचिन्हित पूर्णांक data;	/* MII Data */
	अचिन्हित पूर्णांक addr_shअगरt;	/* MII address shअगरt */
	अचिन्हित पूर्णांक reg_shअगरt;		/* MII reg shअगरt */
	अचिन्हित पूर्णांक addr_mask;		/* MII address mask */
	अचिन्हित पूर्णांक reg_mask;		/* MII reg mask */
	अचिन्हित पूर्णांक clk_csr_shअगरt;
	अचिन्हित पूर्णांक clk_csr_mask;
पूर्ण;

काष्ठा mac_device_info अणु
	स्थिर काष्ठा sपंचांगmac_ops *mac;
	स्थिर काष्ठा sपंचांगmac_desc_ops *desc;
	स्थिर काष्ठा sपंचांगmac_dma_ops *dma;
	स्थिर काष्ठा sपंचांगmac_mode_ops *mode;
	स्थिर काष्ठा sपंचांगmac_hwबारtamp *ptp;
	स्थिर काष्ठा sपंचांगmac_tc_ops *tc;
	स्थिर काष्ठा sपंचांगmac_mmc_ops *mmc;
	स्थिर काष्ठा mdio_xpcs_ops *xpcs;
	काष्ठा mdio_xpcs_args xpcs_args;
	काष्ठा mii_regs mii;	/* MII रेजिस्टर Addresses */
	काष्ठा mac_link link;
	व्योम __iomem *pcsr;     /* vpoपूर्णांकer to device CSRs */
	अचिन्हित पूर्णांक multicast_filter_bins;
	अचिन्हित पूर्णांक unicast_filter_entries;
	अचिन्हित पूर्णांक mcast_bits_log2;
	अचिन्हित पूर्णांक rx_csum;
	अचिन्हित पूर्णांक pcs;
	अचिन्हित पूर्णांक pmt;
	अचिन्हित पूर्णांक ps;
	अचिन्हित पूर्णांक xlgmac;
	अचिन्हित पूर्णांक num_vlan;
	u32 vlan_filter[32];
	अचिन्हित पूर्णांक promisc;
	bool vlan_fail_q_en;
	u8 vlan_fail_q;
पूर्ण;

काष्ठा sपंचांगmac_rx_routing अणु
	u32 reg_mask;
	u32 reg_shअगरt;
पूर्ण;

पूर्णांक dwmac100_setup(काष्ठा sपंचांगmac_priv *priv);
पूर्णांक dwmac1000_setup(काष्ठा sपंचांगmac_priv *priv);
पूर्णांक dwmac4_setup(काष्ठा sपंचांगmac_priv *priv);
पूर्णांक dwxgmac2_setup(काष्ठा sपंचांगmac_priv *priv);
पूर्णांक dwxlgmac2_setup(काष्ठा sपंचांगmac_priv *priv);

व्योम sपंचांगmac_set_mac_addr(व्योम __iomem *ioaddr, u8 addr[6],
			 अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low);
व्योम sपंचांगmac_get_mac_addr(व्योम __iomem *ioaddr, अचिन्हित अक्षर *addr,
			 अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low);
व्योम sपंचांगmac_set_mac(व्योम __iomem *ioaddr, bool enable);

व्योम sपंचांगmac_dwmac4_set_mac_addr(व्योम __iomem *ioaddr, u8 addr[6],
				अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low);
व्योम sपंचांगmac_dwmac4_get_mac_addr(व्योम __iomem *ioaddr, अचिन्हित अक्षर *addr,
				अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low);
व्योम sपंचांगmac_dwmac4_set_mac(व्योम __iomem *ioaddr, bool enable);

व्योम dwmac_dma_flush_tx_fअगरo(व्योम __iomem *ioaddr);

बाह्य स्थिर काष्ठा sपंचांगmac_mode_ops ring_mode_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_mode_ops chain_mode_ops;
बाह्य स्थिर काष्ठा sपंचांगmac_desc_ops dwmac4_desc_ops;

#पूर्ण_अगर /* __COMMON_H__ */
