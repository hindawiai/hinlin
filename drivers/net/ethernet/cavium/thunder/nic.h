<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Cavium, Inc.
 */

#अगर_अघोषित NIC_H
#घोषणा	NIC_H

#समावेश <linux/netdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश "thunder_bgx.h"

/* PCI device IDs */
#घोषणा	PCI_DEVICE_ID_THUNDER_NIC_PF		0xA01E
#घोषणा	PCI_DEVICE_ID_THUNDER_PASS1_NIC_VF	0x0011
#घोषणा	PCI_DEVICE_ID_THUNDER_NIC_VF		0xA034
#घोषणा	PCI_DEVICE_ID_THUNDER_BGX		0xA026

/* Subप्रणाली device IDs */
#घोषणा PCI_SUBSYS_DEVID_88XX_NIC_PF		0xA11E
#घोषणा PCI_SUBSYS_DEVID_81XX_NIC_PF		0xA21E
#घोषणा PCI_SUBSYS_DEVID_83XX_NIC_PF		0xA31E

#घोषणा PCI_SUBSYS_DEVID_88XX_PASS1_NIC_VF	0xA11E
#घोषणा PCI_SUBSYS_DEVID_88XX_NIC_VF		0xA134
#घोषणा PCI_SUBSYS_DEVID_81XX_NIC_VF		0xA234
#घोषणा PCI_SUBSYS_DEVID_83XX_NIC_VF		0xA334


/* PCI BAR nos */
#घोषणा	PCI_CFG_REG_BAR_NUM		0
#घोषणा	PCI_MSIX_REG_BAR_NUM		4

/* NIC SRIOV VF count */
#घोषणा	MAX_NUM_VFS_SUPPORTED		128
#घोषणा	DEFAULT_NUM_VF_ENABLED		8

#घोषणा	NIC_TNS_BYPASS_MODE		0
#घोषणा	NIC_TNS_MODE			1

/* NIC priv flags */
#घोषणा	NIC_SRIOV_ENABLED		BIT(0)

/* Min/Max packet size */
#घोषणा	NIC_HW_MIN_FRS			64
#घोषणा	NIC_HW_MAX_FRS			9190 /* Excluding L2 header and FCS */

/* Max pkinds */
#घोषणा	NIC_MAX_PKIND			16

/* Max when CPI_ALG is IP dअगरfserv */
#घोषणा	NIC_MAX_CPI_PER_LMAC		64

/* NIC VF Interrupts */
#घोषणा	NICVF_INTR_CQ			0
#घोषणा	NICVF_INTR_SQ			1
#घोषणा	NICVF_INTR_RBDR			2
#घोषणा	NICVF_INTR_PKT_DROP		3
#घोषणा	NICVF_INTR_TCP_TIMER		4
#घोषणा	NICVF_INTR_MBOX			5
#घोषणा	NICVF_INTR_QS_ERR		6

#घोषणा	NICVF_INTR_CQ_SHIFT		0
#घोषणा	NICVF_INTR_SQ_SHIFT		8
#घोषणा	NICVF_INTR_RBDR_SHIFT		16
#घोषणा	NICVF_INTR_PKT_DROP_SHIFT	20
#घोषणा	NICVF_INTR_TCP_TIMER_SHIFT	21
#घोषणा	NICVF_INTR_MBOX_SHIFT		22
#घोषणा	NICVF_INTR_QS_ERR_SHIFT		23

#घोषणा	NICVF_INTR_CQ_MASK		(0xFF << NICVF_INTR_CQ_SHIFT)
#घोषणा	NICVF_INTR_SQ_MASK		(0xFF << NICVF_INTR_SQ_SHIFT)
#घोषणा	NICVF_INTR_RBDR_MASK		(0x03 << NICVF_INTR_RBDR_SHIFT)
#घोषणा	NICVF_INTR_PKT_DROP_MASK	BIT(NICVF_INTR_PKT_DROP_SHIFT)
#घोषणा	NICVF_INTR_TCP_TIMER_MASK	BIT(NICVF_INTR_TCP_TIMER_SHIFT)
#घोषणा	NICVF_INTR_MBOX_MASK		BIT(NICVF_INTR_MBOX_SHIFT)
#घोषणा	NICVF_INTR_QS_ERR_MASK		BIT(NICVF_INTR_QS_ERR_SHIFT)

/* MSI-X पूर्णांकerrupts */
#घोषणा	NIC_PF_MSIX_VECTORS		10
#घोषणा	NIC_VF_MSIX_VECTORS		20

#घोषणा NIC_PF_INTR_ID_ECC0_SBE		0
#घोषणा NIC_PF_INTR_ID_ECC0_DBE		1
#घोषणा NIC_PF_INTR_ID_ECC1_SBE		2
#घोषणा NIC_PF_INTR_ID_ECC1_DBE		3
#घोषणा NIC_PF_INTR_ID_ECC2_SBE		4
#घोषणा NIC_PF_INTR_ID_ECC2_DBE		5
#घोषणा NIC_PF_INTR_ID_ECC3_SBE		6
#घोषणा NIC_PF_INTR_ID_ECC3_DBE		7
#घोषणा NIC_PF_INTR_ID_MBOX0		8
#घोषणा NIC_PF_INTR_ID_MBOX1		9

/* Minimum FIFO level beक्रमe all packets क्रम the CQ are dropped
 *
 * This value ensures that once a packet has been "accepted"
 * क्रम reception it will not get dropped due to non-availability
 * of CQ descriptor. An errata in HW mandates this value to be
 * atleast 0x100.
 */
#घोषणा NICPF_CQM_MIN_DROP_LEVEL       0x100

/* Global समयr क्रम CQ समयr thresh पूर्णांकerrupts
 * Calculated क्रम SCLK of 700Mhz
 * value written should be a 1/16th of what is expected
 *
 * 1 tick per 0.025usec
 */
#घोषणा NICPF_CLK_PER_INT_TICK		1

/* Time to रुको beक्रमe we decide that a SQ is stuck.
 *
 * Since both pkt rx and tx notअगरications are करोne with same CQ,
 * when packets are being received at very high rate (eg: L2 क्रमwarding)
 * then मुक्तing transmitted skbs will be delayed and watchकरोg
 * will kick in, resetting पूर्णांकerface. Hence keeping this value high.
 */
#घोषणा	NICVF_TX_TIMEOUT		(50 * HZ)

काष्ठा nicvf_cq_poll अणु
	काष्ठा  nicvf *nicvf;
	u8	cq_idx;		/* Completion queue index */
	काष्ठा	napi_काष्ठा napi;
पूर्ण;

#घोषणा NIC_MAX_RSS_HASH_BITS		8
#घोषणा NIC_MAX_RSS_IDR_TBL_SIZE	(1 << NIC_MAX_RSS_HASH_BITS)
#घोषणा RSS_HASH_KEY_SIZE		5 /* 320 bit key */

काष्ठा nicvf_rss_info अणु
	bool enable;
#घोषणा	RSS_L2_EXTENDED_HASH_ENA	BIT(0)
#घोषणा	RSS_IP_HASH_ENA			BIT(1)
#घोषणा	RSS_TCP_HASH_ENA		BIT(2)
#घोषणा	RSS_TCP_SYN_DIS			BIT(3)
#घोषणा	RSS_UDP_HASH_ENA		BIT(4)
#घोषणा RSS_L4_EXTENDED_HASH_ENA	BIT(5)
#घोषणा	RSS_ROCE_ENA			BIT(6)
#घोषणा	RSS_L3_BI_सूचीECTION_ENA		BIT(7)
#घोषणा	RSS_L4_BI_सूचीECTION_ENA		BIT(8)
	u64 cfg;
	u8  hash_bits;
	u16 rss_size;
	u8  ind_tbl[NIC_MAX_RSS_IDR_TBL_SIZE];
	u64 key[RSS_HASH_KEY_SIZE];
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा nicvf_pfc अणु
	u8    स्वतःneg;
	u8    fc_rx;
	u8    fc_tx;
पूर्ण;

क्रमागत rx_stats_reg_offset अणु
	RX_OCTS = 0x0,
	RX_UCAST = 0x1,
	RX_BCAST = 0x2,
	RX_MCAST = 0x3,
	RX_RED = 0x4,
	RX_RED_OCTS = 0x5,
	RX_ORUN = 0x6,
	RX_ORUN_OCTS = 0x7,
	RX_FCS = 0x8,
	RX_L2ERR = 0x9,
	RX_DRP_BCAST = 0xa,
	RX_DRP_MCAST = 0xb,
	RX_DRP_L3BCAST = 0xc,
	RX_DRP_L3MCAST = 0xd,
	RX_STATS_ENUM_LAST,
पूर्ण;

क्रमागत tx_stats_reg_offset अणु
	TX_OCTS = 0x0,
	TX_UCAST = 0x1,
	TX_BCAST = 0x2,
	TX_MCAST = 0x3,
	TX_DROP = 0x4,
	TX_STATS_ENUM_LAST,
पूर्ण;

काष्ठा nicvf_hw_stats अणु
	u64 rx_bytes;
	u64 rx_frames;
	u64 rx_ucast_frames;
	u64 rx_bcast_frames;
	u64 rx_mcast_frames;
	u64 rx_drops;
	u64 rx_drop_red;
	u64 rx_drop_red_bytes;
	u64 rx_drop_overrun;
	u64 rx_drop_overrun_bytes;
	u64 rx_drop_bcast;
	u64 rx_drop_mcast;
	u64 rx_drop_l3_bcast;
	u64 rx_drop_l3_mcast;
	u64 rx_fcs_errors;
	u64 rx_l2_errors;

	u64 tx_bytes;
	u64 tx_frames;
	u64 tx_ucast_frames;
	u64 tx_bcast_frames;
	u64 tx_mcast_frames;
	u64 tx_drops;
पूर्ण;

काष्ठा nicvf_drv_stats अणु
	/* CQE Rx errs */
	u64 rx_bgx_truncated_pkts;
	u64 rx_jabber_errs;
	u64 rx_fcs_errs;
	u64 rx_bgx_errs;
	u64 rx_prel2_errs;
	u64 rx_l2_hdr_malक्रमmed;
	u64 rx_oversize;
	u64 rx_undersize;
	u64 rx_l2_len_mismatch;
	u64 rx_l2_pclp;
	u64 rx_ip_ver_errs;
	u64 rx_ip_csum_errs;
	u64 rx_ip_hdr_malक्रमmed;
	u64 rx_ip_payload_malक्रमmed;
	u64 rx_ip_ttl_errs;
	u64 rx_l3_pclp;
	u64 rx_l4_malक्रमmed;
	u64 rx_l4_csum_errs;
	u64 rx_udp_len_errs;
	u64 rx_l4_port_errs;
	u64 rx_tcp_flag_errs;
	u64 rx_tcp_offset_errs;
	u64 rx_l4_pclp;
	u64 rx_truncated_pkts;

	/* CQE Tx errs */
	u64 tx_desc_fault;
	u64 tx_hdr_cons_err;
	u64 tx_subdesc_err;
	u64 tx_max_size_exceeded;
	u64 tx_imm_size_oflow;
	u64 tx_data_seq_err;
	u64 tx_mem_seq_err;
	u64 tx_lock_viol;
	u64 tx_data_fault;
	u64 tx_tsपंचांगp_conflict;
	u64 tx_tsपंचांगp_समयout;
	u64 tx_mem_fault;
	u64 tx_csum_overlap;
	u64 tx_csum_overflow;

	/* driver debug stats */
	u64 tx_tso;
	u64 tx_समयout;
	u64 txq_stop;
	u64 txq_wake;

	u64 rcv_buffer_alloc_failures;
	u64 page_alloc;

	काष्ठा u64_stats_sync   syncp;
पूर्ण;

काष्ठा cavium_ptp;

काष्ठा xcast_addr_list अणु
	पूर्णांक              count;
	u64              mc[];
पूर्ण;

काष्ठा nicvf_work अणु
	काष्ठा work_काष्ठा     work;
	u8                     mode;
	काष्ठा xcast_addr_list *mc;
पूर्ण;

काष्ठा nicvf अणु
	काष्ठा nicvf		*pnicvf;
	काष्ठा net_device	*netdev;
	काष्ठा pci_dev		*pdev;
	व्योम __iomem		*reg_base;
	काष्ठा bpf_prog         *xdp_prog;
#घोषणा	MAX_QUEUES_PER_QSET			8
	काष्ठा queue_set	*qs;
	व्योम			*iommu_करोमुख्य;
	u8			vf_id;
	u8			sqs_id;
	bool                    sqs_mode;
	bool			hw_tso;
	bool			t88;

	/* Receive buffer alloc */
	u32			rb_page_offset;
	u16			rb_pageref;
	bool			rb_alloc_fail;
	bool			rb_work_scheduled;
	काष्ठा page		*rb_page;
	काष्ठा delayed_work	rbdr_work;
	काष्ठा tasklet_काष्ठा	rbdr_task;

	/* Secondary Qset */
	u8			sqs_count;
#घोषणा	MAX_SQS_PER_VF_SINGLE_NODE		5
#घोषणा	MAX_SQS_PER_VF				11
	काष्ठा nicvf		*snicvf[MAX_SQS_PER_VF];

	/* Queue count */
	u8			rx_queues;
	u8			tx_queues;
	u8			xdp_tx_queues;
	u8			max_queues;

	u8			node;
	u8			cpi_alg;
	bool			link_up;
	u8			mac_type;
	u8			duplex;
	u32			speed;
	bool			tns_mode;
	bool			loopback_supported;
	काष्ठा nicvf_rss_info	rss_info;
	काष्ठा nicvf_pfc	pfc;
	काष्ठा tasklet_काष्ठा	qs_err_task;
	काष्ठा work_काष्ठा	reset_task;
	काष्ठा nicvf_work       rx_mode_work;
	/* spinlock to protect workqueue arguments from concurrent access */
	spinlock_t              rx_mode_wq_lock;
	/* workqueue क्रम handling kernel nकरो_set_rx_mode() calls */
	काष्ठा workqueue_काष्ठा *nicvf_rx_mode_wq;
	/* mutex to protect VF's mailbox contents from concurrent access */
	काष्ठा mutex            rx_mode_mtx;
	काष्ठा delayed_work	link_change_work;
	/* PTP बारtamp */
	काष्ठा cavium_ptp	*ptp_घड़ी;
	/* Inbound बारtamping is on */
	bool			hw_rx_tstamp;
	/* When the packet that requires बारtamping is sent, hardware inserts
	 * two entries to the completion queue.  First is the regular
	 * CQE_TYPE_SEND entry that संकेतs that the packet was sent.
	 * The second is CQE_TYPE_SEND_PTP that contains the actual बारtamp
	 * क्रम that packet.
	 * `ptp_skb` is initialized in the handler क्रम the CQE_TYPE_SEND
	 * entry and is used and zeroed in the handler क्रम the CQE_TYPE_SEND_PTP
	 * entry.
	 * So `ptp_skb` is used to hold the poपूर्णांकer to the packet between
	 * the calls to CQE_TYPE_SEND and CQE_TYPE_SEND_PTP handlers.
	 */
	काष्ठा sk_buff		*ptp_skb;
	/* `tx_ptp_skbs` is set when the hardware is sending a packet that
	 * requires बारtamping.  Cavium hardware can not process more than one
	 * such packet at once so this is set each समय the driver submits
	 * a packet that requires बारtamping to the send queue and clears
	 * each समय it receives the entry on the completion queue saying
	 * that such packet was sent.
	 * So `tx_ptp_skbs` prevents driver from submitting more than one
	 * packet that requires बारtamping to the hardware क्रम transmitting.
	 */
	atomic_t		tx_ptp_skbs;

	/* Interrupt coalescing settings */
	u32			cq_coalesce_usecs;
	u32			msg_enable;

	/* Stats */
	काष्ठा nicvf_hw_stats   hw_stats;
	काष्ठा nicvf_drv_stats  __percpu *drv_stats;
	काष्ठा bgx_stats	bgx_stats;

	/* Napi */
	काष्ठा nicvf_cq_poll	*napi[8];

	/* MSI-X  */
	u8			num_vec;
	अक्षर			irq_name[NIC_VF_MSIX_VECTORS][IFNAMSIZ + 15];
	bool			irq_allocated[NIC_VF_MSIX_VECTORS];
	cpumask_var_t		affinity_mask[NIC_VF_MSIX_VECTORS];

	/* VF <-> PF mailbox communication */
	bool			pf_acked;
	bool			pf_nacked;
	bool			set_mac_pending;
पूर्ण ____cacheline_aligned_in_smp;

/* PF <--> VF Mailbox communication
 * Eight 64bit रेजिस्टरs are shared between PF and VF.
 * Separate set क्रम each VF.
 * Writing '1' पूर्णांकo last रेजिस्टर mbx7 means end of message.
 */

/* PF <--> VF mailbox communication */
#घोषणा	NIC_PF_VF_MAILBOX_SIZE		2
#घोषणा	NIC_MBOX_MSG_TIMEOUT		2000 /* ms */

/* Mailbox message types */
#घोषणा	NIC_MBOX_MSG_READY		0x01	/* Is PF पढ़ोy to rcv msgs */
#घोषणा	NIC_MBOX_MSG_ACK		0x02	/* ACK the message received */
#घोषणा	NIC_MBOX_MSG_NACK		0x03	/* NACK the message received */
#घोषणा	NIC_MBOX_MSG_QS_CFG		0x04	/* Configure Qset */
#घोषणा	NIC_MBOX_MSG_RQ_CFG		0x05	/* Configure receive queue */
#घोषणा	NIC_MBOX_MSG_SQ_CFG		0x06	/* Configure Send queue */
#घोषणा	NIC_MBOX_MSG_RQ_DROP_CFG	0x07	/* Configure receive queue */
#घोषणा	NIC_MBOX_MSG_SET_MAC		0x08	/* Add MAC ID to DMAC filter */
#घोषणा	NIC_MBOX_MSG_SET_MAX_FRS	0x09	/* Set max frame size */
#घोषणा	NIC_MBOX_MSG_CPI_CFG		0x0A	/* Config CPI, RSSI */
#घोषणा	NIC_MBOX_MSG_RSS_SIZE		0x0B	/* Get RSS indir_tbl size */
#घोषणा	NIC_MBOX_MSG_RSS_CFG		0x0C	/* Config RSS table */
#घोषणा	NIC_MBOX_MSG_RSS_CFG_CONT	0x0D	/* RSS config continuation */
#घोषणा	NIC_MBOX_MSG_RQ_BP_CFG		0x0E	/* RQ backpressure config */
#घोषणा	NIC_MBOX_MSG_RQ_SW_SYNC		0x0F	/* Flush inflight pkts to RQ */
#घोषणा	NIC_MBOX_MSG_BGX_STATS		0x10	/* Get stats from BGX */
#घोषणा	NIC_MBOX_MSG_BGX_LINK_CHANGE	0x11	/* BGX:LMAC link status */
#घोषणा	NIC_MBOX_MSG_ALLOC_SQS		0x12	/* Allocate secondary Qset */
#घोषणा	NIC_MBOX_MSG_NICVF_PTR		0x13	/* Send nicvf ptr to PF */
#घोषणा	NIC_MBOX_MSG_PNICVF_PTR		0x14	/* Get primary qset nicvf ptr */
#घोषणा	NIC_MBOX_MSG_SNICVF_PTR		0x15	/* Send sqet nicvf ptr to PVF */
#घोषणा	NIC_MBOX_MSG_LOOPBACK		0x16	/* Set पूर्णांकerface in loopback */
#घोषणा	NIC_MBOX_MSG_RESET_STAT_COUNTER 0x17	/* Reset statistics counters */
#घोषणा	NIC_MBOX_MSG_PFC		0x18	/* Pause frame control */
#घोषणा	NIC_MBOX_MSG_PTP_CFG		0x19	/* HW packet बारtamp */
#घोषणा	NIC_MBOX_MSG_CFG_DONE		0xF0	/* VF configuration करोne */
#घोषणा	NIC_MBOX_MSG_SHUTDOWN		0xF1	/* VF is being shutकरोwn */
#घोषणा	NIC_MBOX_MSG_RESET_XCAST	0xF2    /* Reset DCAM filtering mode */
#घोषणा	NIC_MBOX_MSG_ADD_MCAST		0xF3    /* Add MAC to DCAM filters */
#घोषणा	NIC_MBOX_MSG_SET_XCAST		0xF4    /* Set MCAST/BCAST RX mode */

काष्ठा nic_cfg_msg अणु
	u8    msg;
	u8    vf_id;
	u8    node_id;
	u8    tns_mode:1;
	u8    sqs_mode:1;
	u8    loopback_supported:1;
	u8    mac_addr[ETH_ALEN];
पूर्ण;

/* Qset configuration */
काष्ठा qs_cfg_msg अणु
	u8    msg;
	u8    num;
	u8    sqs_count;
	u64   cfg;
पूर्ण;

/* Receive queue configuration */
काष्ठा rq_cfg_msg अणु
	u8    msg;
	u8    qs_num;
	u8    rq_num;
	u64   cfg;
पूर्ण;

/* Send queue configuration */
काष्ठा sq_cfg_msg अणु
	u8    msg;
	u8    qs_num;
	u8    sq_num;
	bool  sqs_mode;
	u64   cfg;
पूर्ण;

/* Set VF's MAC address */
काष्ठा set_mac_msg अणु
	u8    msg;
	u8    vf_id;
	u8    mac_addr[ETH_ALEN];
पूर्ण;

/* Set Maximum frame size */
काष्ठा set_frs_msg अणु
	u8    msg;
	u8    vf_id;
	u16   max_frs;
पूर्ण;

/* Set CPI algorithm type */
काष्ठा cpi_cfg_msg अणु
	u8    msg;
	u8    vf_id;
	u8    rq_cnt;
	u8    cpi_alg;
पूर्ण;

/* Get RSS table size */
काष्ठा rss_sz_msg अणु
	u8    msg;
	u8    vf_id;
	u16   ind_tbl_size;
पूर्ण;

/* Set RSS configuration */
काष्ठा rss_cfg_msg अणु
	u8    msg;
	u8    vf_id;
	u8    hash_bits;
	u8    tbl_len;
	u8    tbl_offset;
#घोषणा RSS_IND_TBL_LEN_PER_MBX_MSG	8
	u8    ind_tbl[RSS_IND_TBL_LEN_PER_MBX_MSG];
पूर्ण;

काष्ठा bgx_stats_msg अणु
	u8    msg;
	u8    vf_id;
	u8    rx;
	u8    idx;
	u64   stats;
पूर्ण;

/* Physical पूर्णांकerface link status */
काष्ठा bgx_link_status अणु
	u8    msg;
	u8    mac_type;
	u8    link_up;
	u8    duplex;
	u32   speed;
पूर्ण;

/* Get Extra Qset IDs */
काष्ठा sqs_alloc अणु
	u8    msg;
	u8    vf_id;
	u8    qs_count;
पूर्ण;

काष्ठा nicvf_ptr अणु
	u8    msg;
	u8    vf_id;
	bool  sqs_mode;
	u8    sqs_id;
	u64   nicvf;
पूर्ण;

/* Set पूर्णांकerface in loopback mode */
काष्ठा set_loopback अणु
	u8    msg;
	u8    vf_id;
	bool  enable;
पूर्ण;

/* Reset statistics counters */
काष्ठा reset_stat_cfg अणु
	u8    msg;
	/* Biपंचांगap to select NIC_PF_VNIC(vf_id)_RX_STAT(0..13) */
	u16   rx_stat_mask;
	/* Biपंचांगap to select NIC_PF_VNIC(vf_id)_TX_STAT(0..4) */
	u8    tx_stat_mask;
	/* Biपंचांगap to select NIC_PF_QS(0..127)_RQ(0..7)_STAT(0..1)
	 * bit14, bit15 NIC_PF_QS(vf_id)_RQ7_STAT(0..1)
	 * bit12, bit13 NIC_PF_QS(vf_id)_RQ6_STAT(0..1)
	 * ..
	 * bit2, bit3 NIC_PF_QS(vf_id)_RQ1_STAT(0..1)
	 * bit0, bit1 NIC_PF_QS(vf_id)_RQ0_STAT(0..1)
	 */
	u16   rq_stat_mask;
	/* Biपंचांगap to select NIC_PF_QS(0..127)_SQ(0..7)_STAT(0..1)
	 * bit14, bit15 NIC_PF_QS(vf_id)_SQ7_STAT(0..1)
	 * bit12, bit13 NIC_PF_QS(vf_id)_SQ6_STAT(0..1)
	 * ..
	 * bit2, bit3 NIC_PF_QS(vf_id)_SQ1_STAT(0..1)
	 * bit0, bit1 NIC_PF_QS(vf_id)_SQ0_STAT(0..1)
	 */
	u16   sq_stat_mask;
पूर्ण;

काष्ठा pfc अणु
	u8    msg;
	u8    get; /* Get or set PFC settings */
	u8    स्वतःneg;
	u8    fc_rx;
	u8    fc_tx;
पूर्ण;

काष्ठा set_ptp अणु
	u8    msg;
	bool  enable;
पूर्ण;

काष्ठा xcast अणु
	u8    msg;
	u8    mode;
	u64   mac:48;
पूर्ण;

/* 128 bit shared memory between PF and each VF */
जोड़ nic_mbx अणु
	काष्ठा अणु u8 msg; पूर्ण	msg;
	काष्ठा nic_cfg_msg	nic_cfg;
	काष्ठा qs_cfg_msg	qs;
	काष्ठा rq_cfg_msg	rq;
	काष्ठा sq_cfg_msg	sq;
	काष्ठा set_mac_msg	mac;
	काष्ठा set_frs_msg	frs;
	काष्ठा cpi_cfg_msg	cpi_cfg;
	काष्ठा rss_sz_msg	rss_size;
	काष्ठा rss_cfg_msg	rss_cfg;
	काष्ठा bgx_stats_msg    bgx_stats;
	काष्ठा bgx_link_status  link_status;
	काष्ठा sqs_alloc        sqs_alloc;
	काष्ठा nicvf_ptr	nicvf;
	काष्ठा set_loopback	lbk;
	काष्ठा reset_stat_cfg	reset_stat;
	काष्ठा pfc		pfc;
	काष्ठा set_ptp		ptp;
	काष्ठा xcast            xcast;
पूर्ण;

#घोषणा NIC_NODE_ID_MASK	0x03
#घोषणा NIC_NODE_ID_SHIFT	44

अटल अंतरभूत पूर्णांक nic_get_node_id(काष्ठा pci_dev *pdev)
अणु
	u64 addr = pci_resource_start(pdev, PCI_CFG_REG_BAR_NUM);
	वापस ((addr >> NIC_NODE_ID_SHIFT) & NIC_NODE_ID_MASK);
पूर्ण

अटल अंतरभूत bool pass1_silicon(काष्ठा pci_dev *pdev)
अणु
	वापस (pdev->revision < 8) &&
		(pdev->subप्रणाली_device == PCI_SUBSYS_DEVID_88XX_NIC_PF);
पूर्ण

अटल अंतरभूत bool pass2_silicon(काष्ठा pci_dev *pdev)
अणु
	वापस (pdev->revision >= 8) &&
		(pdev->subप्रणाली_device == PCI_SUBSYS_DEVID_88XX_NIC_PF);
पूर्ण

पूर्णांक nicvf_set_real_num_queues(काष्ठा net_device *netdev,
			      पूर्णांक tx_queues, पूर्णांक rx_queues);
पूर्णांक nicvf_खोलो(काष्ठा net_device *netdev);
पूर्णांक nicvf_stop(काष्ठा net_device *netdev);
पूर्णांक nicvf_send_msg_to_pf(काष्ठा nicvf *vf, जोड़ nic_mbx *mbx);
व्योम nicvf_config_rss(काष्ठा nicvf *nic);
व्योम nicvf_set_rss_key(काष्ठा nicvf *nic);
व्योम nicvf_set_ethtool_ops(काष्ठा net_device *netdev);
व्योम nicvf_update_stats(काष्ठा nicvf *nic);
व्योम nicvf_update_lmac_stats(काष्ठा nicvf *nic);

#पूर्ण_अगर /* NIC_H */
