<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* 10G controller driver क्रम Samsung SoCs
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Siva Reddy Kallam <siva.kallam@samsung.com>
 */

#अगर_अघोषित __SXGBE_COMMON_H__
#घोषणा __SXGBE_COMMON_H__

/* क्रमward references */
काष्ठा sxgbe_desc_ops;
काष्ठा sxgbe_dma_ops;
काष्ठा sxgbe_mtl_ops;

#घोषणा SXGBE_RESOURCE_NAME	"sam_sxgbeeth"
#घोषणा DRV_MODULE_VERSION	"November_2013"

/* MAX HW feature words */
#घोषणा SXGBE_HW_WORDS 3

#घोषणा SXGBE_RX_COE_NONE	0

/* CSR Frequency Access Defines*/
#घोषणा SXGBE_CSR_F_150M	150000000
#घोषणा SXGBE_CSR_F_250M	250000000
#घोषणा SXGBE_CSR_F_300M	300000000
#घोषणा SXGBE_CSR_F_350M	350000000
#घोषणा SXGBE_CSR_F_400M	400000000
#घोषणा SXGBE_CSR_F_500M	500000000

/* छोड़ो समय */
#घोषणा SXGBE_PAUSE_TIME 0x200

/* tx queues */
#घोषणा SXGBE_TX_QUEUES   8
#घोषणा SXGBE_RX_QUEUES   16

/* Calculated based how much समय करोes it take to fill 256KB Rx memory
 * at 10Gb speed at 156MHz घड़ी rate and considered little less then
 * the actual value.
 */
#घोषणा SXGBE_MAX_DMA_RIWT	0x70
#घोषणा SXGBE_MIN_DMA_RIWT	0x01

/* Tx coalesce parameters */
#घोषणा SXGBE_COAL_TX_TIMER	40000
#घोषणा SXGBE_MAX_COAL_TX_TICK	100000
#घोषणा SXGBE_TX_MAX_FRAMES	512
#घोषणा SXGBE_TX_FRAMES	128

/* SXGBE TX FIFO is 8K, Rx FIFO is 16K */
#घोषणा BUF_SIZE_16KiB 16384
#घोषणा BUF_SIZE_8KiB 8192
#घोषणा BUF_SIZE_4KiB 4096
#घोषणा BUF_SIZE_2KiB 2048

#घोषणा SXGBE_DEFAULT_LIT_LS	0x3E8
#घोषणा SXGBE_DEFAULT_TWT_LS	0x0

/* Flow Control defines */
#घोषणा SXGBE_FLOW_OFF		0
#घोषणा SXGBE_FLOW_RX		1
#घोषणा SXGBE_FLOW_TX		2
#घोषणा SXGBE_FLOW_AUTO		(SXGBE_FLOW_TX | SXGBE_FLOW_RX)

#घोषणा SF_DMA_MODE 1		/* DMA STORE-AND-FORWARD Operation Mode */

/* errors */
#घोषणा RX_GMII_ERR		0x01
#घोषणा RX_WATCHDOG_ERR		0x02
#घोषणा RX_CRC_ERR		0x03
#घोषणा RX_GAINT_ERR		0x04
#घोषणा RX_IP_HDR_ERR		0x05
#घोषणा RX_PAYLOAD_ERR		0x06
#घोषणा RX_OVERFLOW_ERR		0x07

/* pkt type */
#घोषणा RX_LEN_PKT		0x00
#घोषणा RX_MACCTL_PKT		0x01
#घोषणा RX_DCBCTL_PKT		0x02
#घोषणा RX_ARP_PKT		0x03
#घोषणा RX_OAM_PKT		0x04
#घोषणा RX_UNTAG_PKT		0x05
#घोषणा RX_OTHER_PKT		0x07
#घोषणा RX_SVLAN_PKT		0x08
#घोषणा RX_CVLAN_PKT		0x09
#घोषणा RX_DVLAN_OCVLAN_ICVLAN_PKT		0x0A
#घोषणा RX_DVLAN_OSVLAN_ISVLAN_PKT		0x0B
#घोषणा RX_DVLAN_OSVLAN_ICVLAN_PKT		0x0C
#घोषणा RX_DVLAN_OCVLAN_ISVLAN_PKT		0x0D

#घोषणा RX_NOT_IP_PKT		0x00
#घोषणा RX_IPV4_TCP_PKT		0x01
#घोषणा RX_IPV4_UDP_PKT		0x02
#घोषणा RX_IPV4_ICMP_PKT	0x03
#घोषणा RX_IPV4_UNKNOWN_PKT	0x07
#घोषणा RX_IPV6_TCP_PKT		0x09
#घोषणा RX_IPV6_UDP_PKT		0x0A
#घोषणा RX_IPV6_ICMP_PKT	0x0B
#घोषणा RX_IPV6_UNKNOWN_PKT	0x0F

#घोषणा RX_NO_PTP		0x00
#घोषणा RX_PTP_SYNC		0x01
#घोषणा RX_PTP_FOLLOW_UP	0x02
#घोषणा RX_PTP_DELAY_REQ	0x03
#घोषणा RX_PTP_DELAY_RESP	0x04
#घोषणा RX_PTP_PDELAY_REQ	0x05
#घोषणा RX_PTP_PDELAY_RESP	0x06
#घोषणा RX_PTP_PDELAY_FOLLOW_UP	0x07
#घोषणा RX_PTP_ANNOUNCE		0x08
#घोषणा RX_PTP_MGMT		0x09
#घोषणा RX_PTP_SIGNAL		0x0A
#घोषणा RX_PTP_RESV_MSG		0x0F

/* EEE-LPI mode  flags*/
#घोषणा TX_ENTRY_LPI_MODE	0x10
#घोषणा TX_EXIT_LPI_MODE	0x20
#घोषणा RX_ENTRY_LPI_MODE	0x40
#घोषणा RX_EXIT_LPI_MODE	0x80

/* EEE-LPI Interrupt status flag */
#घोषणा LPI_INT_STATUS		BIT(5)

/* EEE-LPI Default समयr values */
#घोषणा LPI_LINK_STATUS_TIMER	0x3E8
#घोषणा LPI_MAC_WAIT_TIMER	0x00

/* EEE-LPI Control and status definitions */
#घोषणा LPI_CTRL_STATUS_TXA	BIT(19)
#घोषणा LPI_CTRL_STATUS_PLSDIS	BIT(18)
#घोषणा LPI_CTRL_STATUS_PLS	BIT(17)
#घोषणा LPI_CTRL_STATUS_LPIEN	BIT(16)
#घोषणा LPI_CTRL_STATUS_TXRSTP	BIT(11)
#घोषणा LPI_CTRL_STATUS_RXRSTP	BIT(10)
#घोषणा LPI_CTRL_STATUS_RLPIST	BIT(9)
#घोषणा LPI_CTRL_STATUS_TLPIST	BIT(8)
#घोषणा LPI_CTRL_STATUS_RLPIEX	BIT(3)
#घोषणा LPI_CTRL_STATUS_RLPIEN	BIT(2)
#घोषणा LPI_CTRL_STATUS_TLPIEX	BIT(1)
#घोषणा LPI_CTRL_STATUS_TLPIEN	BIT(0)

क्रमागत dma_irq_status अणु
	tx_hard_error	= BIT(0),
	tx_bump_tc	= BIT(1),
	handle_tx	= BIT(2),
	rx_hard_error	= BIT(3),
	rx_bump_tc	= BIT(4),
	handle_rx	= BIT(5),
पूर्ण;

#घोषणा NETIF_F_HW_VLAN_ALL     (NETIF_F_HW_VLAN_CTAG_RX |	\
				 NETIF_F_HW_VLAN_STAG_RX |	\
				 NETIF_F_HW_VLAN_CTAG_TX |	\
				 NETIF_F_HW_VLAN_STAG_TX |	\
				 NETIF_F_HW_VLAN_CTAG_FILTER |	\
				 NETIF_F_HW_VLAN_STAG_FILTER)

/* MMC control defines */
#घोषणा SXGBE_MMC_CTRL_CNT_FRZ  0x00000008

/* SXGBE HW ADDR regs */
#घोषणा SXGBE_ADDR_HIGH(reg)    (((reg > 15) ? 0x00000800 : 0x00000040) + \
				 (reg * 8))
#घोषणा SXGBE_ADDR_LOW(reg)     (((reg > 15) ? 0x00000804 : 0x00000044) + \
				 (reg * 8))
#घोषणा SXGBE_MAX_PERFECT_ADDRESSES 32 /* Maximum unicast perfect filtering */
#घोषणा SXGBE_FRAME_FILTER       0x00000004      /* Frame Filter */

/* SXGBE Frame Filter defines */
#घोषणा SXGBE_FRAME_FILTER_PR    0x00000001      /* Promiscuous Mode */
#घोषणा SXGBE_FRAME_FILTER_HUC   0x00000002      /* Hash Unicast */
#घोषणा SXGBE_FRAME_FILTER_HMC   0x00000004      /* Hash Multicast */
#घोषणा SXGBE_FRAME_FILTER_DAIF  0x00000008      /* DA Inverse Filtering */
#घोषणा SXGBE_FRAME_FILTER_PM    0x00000010      /* Pass all multicast */
#घोषणा SXGBE_FRAME_FILTER_DBF   0x00000020      /* Disable Broadcast frames */
#घोषणा SXGBE_FRAME_FILTER_SAIF  0x00000100      /* Inverse Filtering */
#घोषणा SXGBE_FRAME_FILTER_SAF   0x00000200      /* Source Address Filter */
#घोषणा SXGBE_FRAME_FILTER_HPF   0x00000400      /* Hash or perfect Filter */
#घोषणा SXGBE_FRAME_FILTER_RA    0x80000000      /* Receive all mode */

#घोषणा SXGBE_HASH_TABLE_SIZE    64
#घोषणा SXGBE_HASH_HIGH          0x00000008      /* Multicast Hash Table High */
#घोषणा SXGBE_HASH_LOW           0x0000000c      /* Multicast Hash Table Low */

#घोषणा SXGBE_HI_REG_AE          0x80000000

/* Minimum and maximum MTU */
#घोषणा MIN_MTU         68
#घोषणा MAX_MTU         9000

#घोषणा SXGBE_FOR_EACH_QUEUE(max_queues, queue_num)			\
	क्रम (queue_num = 0; queue_num < max_queues; queue_num++)

#घोषणा DRV_VERSION "1.0.0"

#घोषणा SXGBE_MAX_RX_CHANNELS	16
#घोषणा SXGBE_MAX_TX_CHANNELS	16

#घोषणा START_MAC_REG_OFFSET	0x0000
#घोषणा MAX_MAC_REG_OFFSET	0x0DFC
#घोषणा START_MTL_REG_OFFSET	0x1000
#घोषणा MAX_MTL_REG_OFFSET	0x18FC
#घोषणा START_DMA_REG_OFFSET	0x3000
#घोषणा MAX_DMA_REG_OFFSET	0x38FC

#घोषणा REG_SPACE_SIZE		0x2000

/* sxgbe statistics counters */
काष्ठा sxgbe_extra_stats अणु
	/* TX/RX IRQ events */
	अचिन्हित दीर्घ tx_underflow_irq;
	अचिन्हित दीर्घ tx_process_stopped_irq;
	अचिन्हित दीर्घ tx_ctxt_desc_err;
	अचिन्हित दीर्घ tx_threshold;
	अचिन्हित दीर्घ rx_threshold;
	अचिन्हित दीर्घ tx_pkt_n;
	अचिन्हित दीर्घ rx_pkt_n;
	अचिन्हित दीर्घ normal_irq_n;
	अचिन्हित दीर्घ tx_normal_irq_n;
	अचिन्हित दीर्घ rx_normal_irq_n;
	अचिन्हित दीर्घ napi_poll;
	अचिन्हित दीर्घ tx_clean;
	अचिन्हित दीर्घ tx_reset_ic_bit;
	अचिन्हित दीर्घ rx_process_stopped_irq;
	अचिन्हित दीर्घ rx_underflow_irq;

	/* Bus access errors */
	अचिन्हित दीर्घ fatal_bus_error_irq;
	अचिन्हित दीर्घ tx_पढ़ो_transfer_err;
	अचिन्हित दीर्घ tx_ग_लिखो_transfer_err;
	अचिन्हित दीर्घ tx_desc_access_err;
	अचिन्हित दीर्घ tx_buffer_access_err;
	अचिन्हित दीर्घ tx_data_transfer_err;
	अचिन्हित दीर्घ rx_पढ़ो_transfer_err;
	अचिन्हित दीर्घ rx_ग_लिखो_transfer_err;
	अचिन्हित दीर्घ rx_desc_access_err;
	अचिन्हित दीर्घ rx_buffer_access_err;
	अचिन्हित दीर्घ rx_data_transfer_err;

	/* EEE-LPI stats */
	अचिन्हित दीर्घ tx_lpi_entry_n;
	अचिन्हित दीर्घ tx_lpi_निकास_n;
	अचिन्हित दीर्घ rx_lpi_entry_n;
	अचिन्हित दीर्घ rx_lpi_निकास_n;
	अचिन्हित दीर्घ eee_wakeup_error_n;

	/* RX specअगरic */
	/* L2 error */
	अचिन्हित दीर्घ rx_code_gmii_err;
	अचिन्हित दीर्घ rx_watchकरोg_err;
	अचिन्हित दीर्घ rx_crc_err;
	अचिन्हित दीर्घ rx_gaपूर्णांक_pkt_err;
	अचिन्हित दीर्घ ip_hdr_err;
	अचिन्हित दीर्घ ip_payload_err;
	अचिन्हित दीर्घ overflow_error;

	/* L2 Pkt type */
	अचिन्हित दीर्घ len_pkt;
	अचिन्हित दीर्घ mac_ctl_pkt;
	अचिन्हित दीर्घ dcb_ctl_pkt;
	अचिन्हित दीर्घ arp_pkt;
	अचिन्हित दीर्घ oam_pkt;
	अचिन्हित दीर्घ untag_okt;
	अचिन्हित दीर्घ other_pkt;
	अचिन्हित दीर्घ svlan_tag_pkt;
	अचिन्हित दीर्घ cvlan_tag_pkt;
	अचिन्हित दीर्घ dvlan_ocvlan_icvlan_pkt;
	अचिन्हित दीर्घ dvlan_osvlan_isvlan_pkt;
	अचिन्हित दीर्घ dvlan_osvlan_icvlan_pkt;
	अचिन्हित दीर्घ dvan_ocvlan_icvlan_pkt;

	/* L3/L4 Pkt type */
	अचिन्हित दीर्घ not_ip_pkt;
	अचिन्हित दीर्घ ip4_tcp_pkt;
	अचिन्हित दीर्घ ip4_udp_pkt;
	अचिन्हित दीर्घ ip4_icmp_pkt;
	अचिन्हित दीर्घ ip4_unknown_pkt;
	अचिन्हित दीर्घ ip6_tcp_pkt;
	अचिन्हित दीर्घ ip6_udp_pkt;
	अचिन्हित दीर्घ ip6_icmp_pkt;
	अचिन्हित दीर्घ ip6_unknown_pkt;

	/* Filter specअगरic */
	अचिन्हित दीर्घ vlan_filter_match;
	अचिन्हित दीर्घ sa_filter_fail;
	अचिन्हित दीर्घ da_filter_fail;
	अचिन्हित दीर्घ hash_filter_pass;
	अचिन्हित दीर्घ l3_filter_match;
	अचिन्हित दीर्घ l4_filter_match;

	/* RX context specअगरic */
	अचिन्हित दीर्घ बारtamp_dropped;
	अचिन्हित दीर्घ rx_msg_type_no_ptp;
	अचिन्हित दीर्घ rx_ptp_type_sync;
	अचिन्हित दीर्घ rx_ptp_type_follow_up;
	अचिन्हित दीर्घ rx_ptp_type_delay_req;
	अचिन्हित दीर्घ rx_ptp_type_delay_resp;
	अचिन्हित दीर्घ rx_ptp_type_pdelay_req;
	अचिन्हित दीर्घ rx_ptp_type_pdelay_resp;
	अचिन्हित दीर्घ rx_ptp_type_pdelay_follow_up;
	अचिन्हित दीर्घ rx_ptp_announce;
	अचिन्हित दीर्घ rx_ptp_mgmt;
	अचिन्हित दीर्घ rx_ptp_संकेत;
	अचिन्हित दीर्घ rx_ptp_resv_msg_type;
पूर्ण;

काष्ठा mac_link अणु
	पूर्णांक port;
	पूर्णांक duplex;
	पूर्णांक speed;
पूर्ण;

काष्ठा mii_regs अणु
	अचिन्हित पूर्णांक addr;	/* MII Address */
	अचिन्हित पूर्णांक data;	/* MII Data */
पूर्ण;

काष्ठा sxgbe_core_ops अणु
	/* MAC core initialization */
	व्योम (*core_init)(व्योम __iomem *ioaddr);
	/* Dump MAC रेजिस्टरs */
	व्योम (*dump_regs)(व्योम __iomem *ioaddr);
	/* Handle extra events on specअगरic पूर्णांकerrupts hw dependent */
	पूर्णांक (*host_irq_status)(व्योम __iomem *ioaddr,
			       काष्ठा sxgbe_extra_stats *x);
	/* Set घातer management mode (e.g. magic frame) */
	व्योम (*pmt)(व्योम __iomem *ioaddr, अचिन्हित दीर्घ mode);
	/* Set/Get Unicast MAC addresses */
	व्योम (*set_umac_addr)(व्योम __iomem *ioaddr, अचिन्हित अक्षर *addr,
			      अचिन्हित पूर्णांक reg_n);
	व्योम (*get_umac_addr)(व्योम __iomem *ioaddr, अचिन्हित अक्षर *addr,
			      अचिन्हित पूर्णांक reg_n);
	व्योम (*enable_rx)(व्योम __iomem *ioaddr, bool enable);
	व्योम (*enable_tx)(व्योम __iomem *ioaddr, bool enable);

	/* controller version specअगरic operations */
	पूर्णांक (*get_controller_version)(व्योम __iomem *ioaddr);

	/* If supported then get the optional core features */
	अचिन्हित पूर्णांक (*get_hw_feature)(व्योम __iomem *ioaddr,
				       अचिन्हित अक्षर feature_index);
	/* adjust SXGBE speed */
	व्योम (*set_speed)(व्योम __iomem *ioaddr, अचिन्हित अक्षर speed);

	/* EEE-LPI specअगरic operations */
	व्योम (*set_eee_mode)(व्योम __iomem *ioaddr);
	व्योम (*reset_eee_mode)(व्योम __iomem *ioaddr);
	व्योम (*set_eee_समयr)(व्योम __iomem *ioaddr, स्थिर पूर्णांक ls,
			      स्थिर पूर्णांक tw);
	व्योम (*set_eee_pls)(व्योम __iomem *ioaddr, स्थिर पूर्णांक link);

	/* Enable disable checksum offload operations */
	व्योम (*enable_rx_csum)(व्योम __iomem *ioaddr);
	व्योम (*disable_rx_csum)(व्योम __iomem *ioaddr);
	व्योम (*enable_rxqueue)(व्योम __iomem *ioaddr, पूर्णांक queue_num);
	व्योम (*disable_rxqueue)(व्योम __iomem *ioaddr, पूर्णांक queue_num);
पूर्ण;

स्थिर काष्ठा sxgbe_core_ops *sxgbe_get_core_ops(व्योम);

काष्ठा sxgbe_ops अणु
	स्थिर काष्ठा sxgbe_core_ops *mac;
	स्थिर काष्ठा sxgbe_desc_ops *desc;
	स्थिर काष्ठा sxgbe_dma_ops *dma;
	स्थिर काष्ठा sxgbe_mtl_ops *mtl;
	काष्ठा mii_regs mii;	/* MII रेजिस्टर Addresses */
	काष्ठा mac_link link;
	अचिन्हित पूर्णांक ctrl_uid;
	अचिन्हित पूर्णांक ctrl_id;
पूर्ण;

/* SXGBE निजी data काष्ठाures */
काष्ठा sxgbe_tx_queue अणु
	अचिन्हित पूर्णांक irq_no;
	काष्ठा sxgbe_priv_data *priv_ptr;
	काष्ठा sxgbe_tx_norm_desc *dma_tx;
	dma_addr_t dma_tx_phy;
	dma_addr_t *tx_skbuff_dma;
	काष्ठा sk_buff **tx_skbuff;
	काष्ठा समयr_list txसमयr;
	अचिन्हित पूर्णांक cur_tx;
	अचिन्हित पूर्णांक dirty_tx;
	u32 tx_count_frames;
	u32 tx_coal_frames;
	u32 tx_coal_समयr;
	पूर्णांक hwts_tx_en;
	u16 prev_mss;
	u8 queue_no;
पूर्ण;

काष्ठा sxgbe_rx_queue अणु
	काष्ठा sxgbe_priv_data *priv_ptr;
	काष्ठा sxgbe_rx_norm_desc *dma_rx;
	काष्ठा sk_buff **rx_skbuff;
	अचिन्हित पूर्णांक cur_rx;
	अचिन्हित पूर्णांक dirty_rx;
	अचिन्हित पूर्णांक irq_no;
	u32 rx_riwt;
	dma_addr_t *rx_skbuff_dma;
	dma_addr_t dma_rx_phy;
	u8 queue_no;
पूर्ण;

/* SXGBE HW capabilities */
काष्ठा sxgbe_hw_features अणु
	/****** CAP [0] *******/
	अचिन्हित पूर्णांक pmt_remote_wake_up;
	अचिन्हित पूर्णांक pmt_magic_frame;
	/* IEEE 1588-2008 */
	अचिन्हित पूर्णांक aसमय_stamp;

	अचिन्हित पूर्णांक eee;

	अचिन्हित पूर्णांक tx_csum_offload;
	अचिन्हित पूर्णांक rx_csum_offload;
	अचिन्हित पूर्णांक multi_macaddr;
	अचिन्हित पूर्णांक tstamp_srcselect;
	अचिन्हित पूर्णांक sa_vlan_insert;

	/****** CAP [1] *******/
	अचिन्हित पूर्णांक rxfअगरo_size;
	अचिन्हित पूर्णांक txfअगरo_size;
	अचिन्हित पूर्णांक atsपंचांगap_hword;
	अचिन्हित पूर्णांक dcb_enable;
	अचिन्हित पूर्णांक splithead_enable;
	अचिन्हित पूर्णांक tcpseg_offload;
	अचिन्हित पूर्णांक debug_mem;
	अचिन्हित पूर्णांक rss_enable;
	अचिन्हित पूर्णांक hash_tsize;
	अचिन्हित पूर्णांक l3l4_filer_size;

	/* This value is in bytes and
	 * as mentioned in HW features
	 * of SXGBE data book
	 */
	अचिन्हित पूर्णांक rx_mtl_qsize;
	अचिन्हित पूर्णांक tx_mtl_qsize;

	/****** CAP [2] *******/
	/* TX and RX number of channels */
	अचिन्हित पूर्णांक rx_mtl_queues;
	अचिन्हित पूर्णांक tx_mtl_queues;
	अचिन्हित पूर्णांक rx_dma_channels;
	अचिन्हित पूर्णांक tx_dma_channels;
	अचिन्हित पूर्णांक pps_output_count;
	अचिन्हित पूर्णांक aux_input_count;
पूर्ण;

काष्ठा sxgbe_priv_data अणु
	/* DMA descriptos */
	काष्ठा sxgbe_tx_queue *txq[SXGBE_TX_QUEUES];
	काष्ठा sxgbe_rx_queue *rxq[SXGBE_RX_QUEUES];
	u8 cur_rx_qnum;

	अचिन्हित पूर्णांक dma_tx_size;
	अचिन्हित पूर्णांक dma_rx_size;
	अचिन्हित पूर्णांक dma_buf_sz;
	u32 rx_riwt;

	काष्ठा napi_काष्ठा napi;

	व्योम __iomem *ioaddr;
	काष्ठा net_device *dev;
	काष्ठा device *device;
	काष्ठा sxgbe_ops *hw;	/* sxgbe specअगरic ops */
	पूर्णांक no_csum_insertion;
	पूर्णांक irq;
	पूर्णांक rxcsum_insertion;
	spinlock_t stats_lock;	/* lock क्रम tx/rx statatics */

	पूर्णांक oldlink;
	पूर्णांक speed;
	पूर्णांक oldduplex;
	काष्ठा mii_bus *mii;
	पूर्णांक mii_irq[PHY_MAX_ADDR];
	u8 rx_छोड़ो;
	u8 tx_छोड़ो;

	काष्ठा sxgbe_extra_stats xstats;
	काष्ठा sxgbe_plat_data *plat;
	काष्ठा sxgbe_hw_features hw_cap;

	u32 msg_enable;

	काष्ठा clk *sxgbe_clk;
	पूर्णांक clk_csr;
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक शेष_addend;

	/* advanced समय stamp support */
	u32 adv_ts;
	पूर्णांक use_riwt;
	काष्ठा ptp_घड़ी *ptp_घड़ी;

	/* tc control */
	पूर्णांक tx_tc;
	पूर्णांक rx_tc;
	/* EEE-LPI specअगरic members */
	काष्ठा समयr_list eee_ctrl_समयr;
	bool tx_path_in_lpi_mode;
	पूर्णांक lpi_irq;
	पूर्णांक eee_enabled;
	पूर्णांक eee_active;
	पूर्णांक tx_lpi_समयr;
पूर्ण;

/* Function prototypes */
काष्ठा sxgbe_priv_data *sxgbe_drv_probe(काष्ठा device *device,
					काष्ठा sxgbe_plat_data *plat_dat,
					व्योम __iomem *addr);
पूर्णांक sxgbe_drv_हटाओ(काष्ठा net_device *ndev);
व्योम sxgbe_set_ethtool_ops(काष्ठा net_device *netdev);
पूर्णांक sxgbe_mdio_unरेजिस्टर(काष्ठा net_device *ndev);
पूर्णांक sxgbe_mdio_रेजिस्टर(काष्ठा net_device *ndev);
पूर्णांक sxgbe_रेजिस्टर_platक्रमm(व्योम);
व्योम sxgbe_unरेजिस्टर_platक्रमm(व्योम);

#अगर_घोषित CONFIG_PM
पूर्णांक sxgbe_suspend(काष्ठा net_device *ndev);
पूर्णांक sxgbe_resume(काष्ठा net_device *ndev);
पूर्णांक sxgbe_मुक्तze(काष्ठा net_device *ndev);
पूर्णांक sxgbe_restore(काष्ठा net_device *ndev);
#पूर्ण_अगर /* CONFIG_PM */

स्थिर काष्ठा sxgbe_mtl_ops *sxgbe_get_mtl_ops(व्योम);

व्योम sxgbe_disable_eee_mode(काष्ठा sxgbe_priv_data * स्थिर priv);
bool sxgbe_eee_init(काष्ठा sxgbe_priv_data * स्थिर priv);
#पूर्ण_अगर /* __SXGBE_COMMON_H__ */
