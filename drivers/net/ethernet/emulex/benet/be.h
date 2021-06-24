<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
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

#अगर_अघोषित BE_H
#घोषणा BE_H

#समावेश <linux/pci.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <net/tcp.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>

#समावेश "be_hw.h"
#समावेश "be_roce.h"

#घोषणा DRV_NAME		"be2net"
#घोषणा BE_NAME			"Emulex BladeEngine2"
#घोषणा BE3_NAME		"Emulex BladeEngine3"
#घोषणा OC_NAME			"Emulex OneConnect"
#घोषणा OC_NAME_BE		OC_NAME	"(be3)"
#घोषणा OC_NAME_LANCER		OC_NAME "(Lancer)"
#घोषणा OC_NAME_SH		OC_NAME "(Skyhawk)"
#घोषणा DRV_DESC		"Emulex OneConnect NIC Driver"

#घोषणा BE_VENDOR_ID 		0x19a2
#घोषणा EMULEX_VENDOR_ID	0x10df
#घोषणा BE_DEVICE_ID1		0x211
#घोषणा BE_DEVICE_ID2		0x221
#घोषणा OC_DEVICE_ID1		0x700	/* Device Id क्रम BE2 cards */
#घोषणा OC_DEVICE_ID2		0x710	/* Device Id क्रम BE3 cards */
#घोषणा OC_DEVICE_ID3		0xe220	/* Device id क्रम Lancer cards */
#घोषणा OC_DEVICE_ID4           0xe228   /* Device id क्रम VF in Lancer */
#घोषणा OC_DEVICE_ID5		0x720	/* Device Id क्रम Skyhawk cards */
#घोषणा OC_DEVICE_ID6		0x728   /* Device id क्रम VF in SkyHawk */
#घोषणा OC_SUBSYS_DEVICE_ID1	0xE602
#घोषणा OC_SUBSYS_DEVICE_ID2	0xE642
#घोषणा OC_SUBSYS_DEVICE_ID3	0xE612
#घोषणा OC_SUBSYS_DEVICE_ID4	0xE652

/* Number of bytes of an RX frame that are copied to skb->data */
#घोषणा BE_HDR_LEN		((u16) 64)
/* allocate extra space to allow tunneling decapsulation without head पुनः_स्मृतिation */
#घोषणा BE_RX_SKB_ALLOC_SIZE	256

#घोषणा BE_MAX_JUMBO_FRAME_SIZE	9018
#घोषणा BE_MIN_MTU		256
#घोषणा BE_MAX_MTU              (BE_MAX_JUMBO_FRAME_SIZE -	\
				 (ETH_HLEN + ETH_FCS_LEN))

/* Accommodate क्रम QnQ configurations where VLAN insertion is enabled in HW */
#घोषणा BE_MAX_GSO_SIZE		(65535 - 2 * VLAN_HLEN)

#घोषणा BE_NUM_VLANS_SUPPORTED	64
#घोषणा BE_MAX_EQD		128u
#घोषणा	BE_MAX_TX_FRAG_COUNT	30

#घोषणा EVNT_Q_LEN		1024
#घोषणा TX_Q_LEN		2048
#घोषणा TX_CQ_LEN		1024
#घोषणा RX_Q_LEN		1024	/* Does not support any other value */
#घोषणा RX_CQ_LEN		1024
#घोषणा MCC_Q_LEN		128	/* total size not to exceed 8 pages */
#घोषणा MCC_CQ_LEN		256

#घोषणा BE2_MAX_RSS_QS		4
#घोषणा BE3_MAX_RSS_QS		16
#घोषणा BE3_MAX_TX_QS		16
#घोषणा BE3_MAX_EVT_QS		16
#घोषणा BE3_SRIOV_MAX_EVT_QS	8
#घोषणा SH_VF_MAX_NIC_EQS	3	/* Skyhawk VFs can have a max of 4 EQs
					 * and at least 1 is granted to either
					 * SURF/DPDK
					 */

#घोषणा MAX_PORT_RSS_TABLES	15
#घोषणा MAX_NIC_FUNCS		16
#घोषणा MAX_RX_QS		32
#घोषणा MAX_EVT_QS		32
#घोषणा MAX_TX_QS		32

#घोषणा MAX_ROCE_EQS		5
#घोषणा MAX_MSIX_VECTORS	32
#घोषणा MIN_MSIX_VECTORS	1
#घोषणा BE_NAPI_WEIGHT		64
#घोषणा MAX_RX_POST		BE_NAPI_WEIGHT /* Frags posted at a समय */
#घोषणा RX_FRAGS_REFILL_WM	(RX_Q_LEN - MAX_RX_POST)
#घोषणा MAX_NUM_POST_ERX_DB	255u

#घोषणा MAX_VFS			30 /* Max VFs supported by BE3 FW */
#घोषणा FW_VER_LEN		32
#घोषणा	CNTL_SERIAL_NUM_WORDS	8  /* Controller serial number words */
#घोषणा	CNTL_SERIAL_NUM_WORD_SZ	(माप(u16)) /* Byte-sz of serial num word */

#घोषणा	RSS_INसूची_TABLE_LEN	128
#घोषणा RSS_HASH_KEY_LEN	40

#घोषणा BE_UNKNOWN_PHY_STATE	0xFF

काष्ठा be_dma_mem अणु
	व्योम *va;
	dma_addr_t dma;
	u32 size;
पूर्ण;

काष्ठा be_queue_info अणु
	u32 len;
	u32 entry_size;	/* Size of an element in the queue */
	u32 tail, head;
	atomic_t used;	/* Number of valid elements in the queue */
	u32 id;
	काष्ठा be_dma_mem dma_mem;
	bool created;
पूर्ण;

अटल अंतरभूत u32 MODULO(u32 val, u32 limit)
अणु
	BUG_ON(limit & (limit - 1));
	वापस val & (limit - 1);
पूर्ण

अटल अंतरभूत व्योम index_adv(u32 *index, u32 val, u32 limit)
अणु
	*index = MODULO((*index + val), limit);
पूर्ण

अटल अंतरभूत व्योम index_inc(u32 *index, u32 limit)
अणु
	*index = MODULO((*index + 1), limit);
पूर्ण

अटल अंतरभूत व्योम *queue_head_node(काष्ठा be_queue_info *q)
अणु
	वापस q->dma_mem.va + q->head * q->entry_size;
पूर्ण

अटल अंतरभूत व्योम *queue_tail_node(काष्ठा be_queue_info *q)
अणु
	वापस q->dma_mem.va + q->tail * q->entry_size;
पूर्ण

अटल अंतरभूत व्योम *queue_index_node(काष्ठा be_queue_info *q, u16 index)
अणु
	वापस q->dma_mem.va + index * q->entry_size;
पूर्ण

अटल अंतरभूत व्योम queue_head_inc(काष्ठा be_queue_info *q)
अणु
	index_inc(&q->head, q->len);
पूर्ण

अटल अंतरभूत व्योम index_dec(u32 *index, u32 limit)
अणु
	*index = MODULO((*index - 1), limit);
पूर्ण

अटल अंतरभूत व्योम queue_tail_inc(काष्ठा be_queue_info *q)
अणु
	index_inc(&q->tail, q->len);
पूर्ण

काष्ठा be_eq_obj अणु
	काष्ठा be_queue_info q;
	अक्षर desc[32];

	काष्ठा be_adapter *adapter;
	काष्ठा napi_काष्ठा napi;
	u8 idx;			/* array index */
	u8 msix_idx;
	u16 spurious_पूर्णांकr;
	cpumask_var_t  affinity_mask;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा be_aic_obj अणु		/* Adaptive पूर्णांकerrupt coalescing (AIC) info */
	u32 min_eqd;		/* in usecs */
	u32 max_eqd;		/* in usecs */
	u32 prev_eqd;		/* in usecs */
	u32 et_eqd;		/* configured val when aic is off */
	uदीर्घ jअगरfies;
	u64 rx_pkts_prev;	/* Used to calculate RX pps */
	u64 tx_reqs_prev;	/* Used to calculate TX pps */
पूर्ण;

काष्ठा be_mcc_obj अणु
	काष्ठा be_queue_info q;
	काष्ठा be_queue_info cq;
	bool rearm_cq;
पूर्ण;

काष्ठा be_tx_stats अणु
	u64 tx_bytes;
	u64 tx_pkts;
	u64 tx_vxlan_offload_pkts;
	u64 tx_reqs;
	u64 tx_compl;
	u32 tx_stops;
	u32 tx_drv_drops;	/* pkts dropped by driver */
	/* the error counters are described in be_ethtool.c */
	u32 tx_hdr_parse_err;
	u32 tx_dma_err;
	u32 tx_tso_err;
	u32 tx_spoof_check_err;
	u32 tx_qinq_err;
	u32 tx_पूर्णांकernal_parity_err;
	u32 tx_sge_err;
	काष्ठा u64_stats_sync sync;
	काष्ठा u64_stats_sync sync_compl;
पूर्ण;

/* Structure to hold some data of पूर्णांकerest obtained from a TX CQE */
काष्ठा be_tx_compl_info अणु
	u8 status;		/* Completion status */
	u16 end_index;		/* Completed TXQ Index */
पूर्ण;

काष्ठा be_tx_obj अणु
	u32 db_offset;
	काष्ठा be_tx_compl_info txcp;
	काष्ठा be_queue_info q;
	काष्ठा be_queue_info cq;
	/* Remember the skbs that were transmitted */
	काष्ठा sk_buff *sent_skb_list[TX_Q_LEN];
	काष्ठा be_tx_stats stats;
	u16 pend_wrb_cnt;	/* Number of WRBs yet to be given to HW */
	u16 last_req_wrb_cnt;	/* wrb cnt of the last req in the Q */
	u16 last_req_hdr;	/* index of the last req's hdr-wrb */
पूर्ण ____cacheline_aligned_in_smp;

/* Struct to remember the pages posted क्रम rx frags */
काष्ठा be_rx_page_info अणु
	काष्ठा page *page;
	/* set to page-addr क्रम last frag of the page & frag-addr otherwise */
	DEFINE_DMA_UNMAP_ADDR(bus);
	u16 page_offset;
	bool last_frag;		/* last frag of the page */
पूर्ण;

काष्ठा be_rx_stats अणु
	u64 rx_bytes;
	u64 rx_pkts;
	u64 rx_vxlan_offload_pkts;
	u32 rx_drops_no_skbs;	/* skb allocation errors */
	u32 rx_drops_no_frags;	/* HW has no fetched frags */
	u32 rx_post_fail;	/* page post alloc failures */
	u32 rx_compl;
	u32 rx_mcast_pkts;
	u32 rx_compl_err;	/* completions with err set */
	काष्ठा u64_stats_sync sync;
पूर्ण;

काष्ठा be_rx_compl_info अणु
	u32 rss_hash;
	u16 vlan_tag;
	u16 pkt_size;
	u16 port;
	u8 vlanf;
	u8 num_rcvd;
	u8 err;
	u8 ipf;
	u8 tcpf;
	u8 udpf;
	u8 ip_csum;
	u8 l4_csum;
	u8 ipv6;
	u8 qnq;
	u8 pkt_type;
	u8 ip_frag;
	u8 tunneled;
पूर्ण;

काष्ठा be_rx_obj अणु
	काष्ठा be_adapter *adapter;
	काष्ठा be_queue_info q;
	काष्ठा be_queue_info cq;
	काष्ठा be_rx_compl_info rxcp;
	काष्ठा be_rx_page_info page_info_tbl[RX_Q_LEN];
	काष्ठा be_rx_stats stats;
	u8 rss_id;
	bool rx_post_starved;	/* Zero rx frags have been posted to BE */
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा be_drv_stats अणु
	u32 eth_red_drops;
	u32 dma_map_errors;
	u32 rx_drops_no_pbuf;
	u32 rx_drops_no_txpb;
	u32 rx_drops_no_erx_descr;
	u32 rx_drops_no_tpre_descr;
	u32 rx_drops_too_many_frags;
	u32 क्रमwarded_packets;
	u32 rx_drops_mtu;
	u32 rx_crc_errors;
	u32 rx_alignment_symbol_errors;
	u32 rx_छोड़ो_frames;
	u32 rx_priority_छोड़ो_frames;
	u32 rx_control_frames;
	u32 rx_in_range_errors;
	u32 rx_out_range_errors;
	u32 rx_frame_too_दीर्घ;
	u32 rx_address_filtered;
	u32 rx_dropped_too_small;
	u32 rx_dropped_too_लघु;
	u32 rx_dropped_header_too_small;
	u32 rx_dropped_tcp_length;
	u32 rx_dropped_runt;
	u32 rx_ip_checksum_errs;
	u32 rx_tcp_checksum_errs;
	u32 rx_udp_checksum_errs;
	u32 tx_छोड़ोframes;
	u32 tx_priority_छोड़ोframes;
	u32 tx_controlframes;
	u32 rxpp_fअगरo_overflow_drop;
	u32 rx_input_fअगरo_overflow_drop;
	u32 pmem_fअगरo_overflow_drop;
	u32 jabber_events;
	u32 rx_roce_bytes_lsd;
	u32 rx_roce_bytes_msd;
	u32 rx_roce_frames;
	u32 roce_drops_payload_len;
	u32 roce_drops_crc;
पूर्ण;

/* A vlan-id of 0xFFFF must be used to clear transparent vlan-tagging */
#घोषणा BE_RESET_VLAN_TAG_ID	0xFFFF

काष्ठा be_vf_cfg अणु
	अचिन्हित अक्षर mac_addr[ETH_ALEN];
	पूर्णांक अगर_handle;
	पूर्णांक pmac_id;
	u16 vlan_tag;
	u32 tx_rate;
	u32 plink_tracking;
	u32 privileges;
	bool spoofchk;
पूर्ण;

क्रमागत vf_state अणु
	ENABLED = 0,
	ASSIGNED = 1
पूर्ण;

#घोषणा BE_FLAGS_LINK_STATUS_INIT		BIT(1)
#घोषणा BE_FLAGS_SRIOV_ENABLED			BIT(2)
#घोषणा BE_FLAGS_WORKER_SCHEDULED		BIT(3)
#घोषणा BE_FLAGS_NAPI_ENABLED			BIT(6)
#घोषणा BE_FLAGS_QNQ_ASYNC_EVT_RCVD		BIT(7)
#घोषणा BE_FLAGS_VXLAN_OFFLOADS			BIT(8)
#घोषणा BE_FLAGS_SETUP_DONE			BIT(9)
#घोषणा BE_FLAGS_PHY_MISCONFIGURED		BIT(10)
#घोषणा BE_FLAGS_ERR_DETECTION_SCHEDULED	BIT(11)
#घोषणा BE_FLAGS_OS2BMC				BIT(12)
#घोषणा BE_FLAGS_TRY_RECOVERY			BIT(13)

#घोषणा BE_UC_PMAC_COUNT			30
#घोषणा BE_VF_UC_PMAC_COUNT			2

#घोषणा MAX_ERR_RECOVERY_RETRY_COUNT		3
#घोषणा ERR_DETECTION_DELAY			1000

/* Ethtool set_dump flags */
#घोषणा LANCER_INITIATE_FW_DUMP			0x1
#घोषणा LANCER_DELETE_FW_DUMP			0x2

काष्ठा phy_info अणु
/* From SFF-8472 spec */
#घोषणा SFP_VENDOR_NAME_LEN			17
	u8 transceiver;
	u8 स्वतःneg;
	u8 fc_स्वतःneg;
	u8 port_type;
	u16 phy_type;
	u16 पूर्णांकerface_type;
	u32 misc_params;
	u16 स्वतः_speeds_supported;
	u16 fixed_speeds_supported;
	पूर्णांक link_speed;
	u32 advertising;
	u32 supported;
	u8 cable_type;
	u8 venकरोr_name[SFP_VENDOR_NAME_LEN];
	u8 venकरोr_pn[SFP_VENDOR_NAME_LEN];
पूर्ण;

काष्ठा be_resources अणु
	u16 max_vfs;		/* Total VFs "really" supported by FW/HW */
	u16 max_mcast_mac;
	u16 max_tx_qs;
	u16 max_rss_qs;
	u16 max_rx_qs;
	u16 max_cq_count;
	u16 max_uc_mac;		/* Max UC MACs programmable */
	u16 max_vlans;		/* Number of vlans supported */
	u16 max_अगरace_count;
	u16 max_mcc_count;
	u16 max_evt_qs;
	u16 max_nic_evt_qs;	/* NIC's share of evt qs */
	u32 अगर_cap_flags;
	u32 vf_अगर_cap_flags;	/* VF अगर capability flags */
	u32 flags;
	/* Calculated PF Pool's share of RSS Tables. This is not enक्रमced by
	 * the FW, but is a self-imposed driver limitation.
	 */
	u16 max_rss_tables;
पूर्ण;

/* These are port-wide values */
काष्ठा be_port_resources अणु
	u16 max_vfs;
	u16 nic_pfs;
पूर्ण;

#घोषणा be_is_os2bmc_enabled(adapter) (adapter->flags & BE_FLAGS_OS2BMC)

काष्ठा rss_info अणु
	u8 rsstable[RSS_INसूची_TABLE_LEN];
	u8 rss_queue[RSS_INसूची_TABLE_LEN];
	u8 rss_hkey[RSS_HASH_KEY_LEN];
	u64 rss_flags;
पूर्ण;

#घोषणा BE_INVALID_DIE_TEMP	0xFF
काष्ठा be_hwmon अणु
	काष्ठा device *hwmon_dev;
	u8 be_on_die_temp;  /* Unit: millidegree Celsius */
पूर्ण;

/* Macros to पढ़ो/ग_लिखो the 'features' word of be_wrb_params काष्ठाure.
 */
#घोषणा	BE_WRB_F_BIT(name)			BE_WRB_F_##name##_BIT
#घोषणा	BE_WRB_F_MASK(name)			BIT_MASK(BE_WRB_F_##name##_BIT)

#घोषणा	BE_WRB_F_GET(word, name)	\
	(((word) & (BE_WRB_F_MASK(name))) >> BE_WRB_F_BIT(name))

#घोषणा	BE_WRB_F_SET(word, name, val)	\
	((word) |= (((val) << BE_WRB_F_BIT(name)) & BE_WRB_F_MASK(name)))

/* Feature/offload bits */
क्रमागत अणु
	BE_WRB_F_CRC_BIT,		/* Ethernet CRC */
	BE_WRB_F_IPCS_BIT,		/* IP csum */
	BE_WRB_F_TCPCS_BIT,		/* TCP csum */
	BE_WRB_F_UDPCS_BIT,		/* UDP csum */
	BE_WRB_F_LSO_BIT,		/* LSO */
	BE_WRB_F_LSO6_BIT,		/* LSO6 */
	BE_WRB_F_VLAN_BIT,		/* VLAN */
	BE_WRB_F_VLAN_SKIP_HW_BIT,	/* Skip VLAN tag (workaround) */
	BE_WRB_F_OS2BMC_BIT		/* Send packet to the management ring */
पूर्ण;

/* The काष्ठाure below provides a HW-agnostic असलtraction of WRB params
 * retrieved from a TX skb. This is in turn passed to chip specअगरic routines
 * during transmit, to set the corresponding params in the WRB.
 */
काष्ठा be_wrb_params अणु
	u32 features;	/* Feature bits */
	u16 vlan_tag;	/* VLAN tag */
	u16 lso_mss;	/* MSS क्रम LSO */
पूर्ण;

काष्ठा be_eth_addr अणु
	अचिन्हित अक्षर mac[ETH_ALEN];
पूर्ण;

#घोषणा BE_SEC	1000			/* in msec */
#घोषणा BE_MIN	(60 * BE_SEC)		/* in msec */
#घोषणा BE_HOUR	(60 * BE_MIN)		/* in msec */

#घोषणा ERR_RECOVERY_MAX_RETRY_COUNT		3
#घोषणा ERR_RECOVERY_DETECTION_DELAY		BE_SEC
#घोषणा ERR_RECOVERY_RETRY_DELAY		(30 * BE_SEC)

/* UE-detection-duration in BEx/Skyhawk:
 * All PFs must रुको क्रम this duration after they detect UE beक्रमe पढ़ोing
 * SLIPORT_SEMAPHORE रेजिस्टर. At the end of this duration, the Firmware
 * guarantees that the SLIPORT_SEMAPHORE रेजिस्टर is updated to indicate
 * अगर the UE is recoverable.
 */
#घोषणा ERR_RECOVERY_UE_DETECT_DURATION			BE_SEC

/* Initial idle समय (in msec) to elapse after driver load,
 * beक्रमe UE recovery is allowed.
 */
#घोषणा ERR_IDLE_HR			24
#घोषणा ERR_RECOVERY_IDLE_TIME		(ERR_IDLE_HR * BE_HOUR)

/* Time पूर्णांकerval (in msec) after which UE recovery can be repeated */
#घोषणा ERR_INTERVAL_HR			72
#घोषणा ERR_RECOVERY_INTERVAL		(ERR_INTERVAL_HR * BE_HOUR)

/* BEx/SH UE recovery state machine */
क्रमागत अणु
	ERR_RECOVERY_ST_NONE = 0,		/* No Recovery */
	ERR_RECOVERY_ST_DETECT = 1,		/* UE detection duration */
	ERR_RECOVERY_ST_RESET = 2,		/* Reset Phase (PF0 only) */
	ERR_RECOVERY_ST_PRE_POLL = 3,		/* Pre-Poll Phase (all PFs) */
	ERR_RECOVERY_ST_REINIT = 4		/* Re-initialize Phase */
पूर्ण;

काष्ठा be_error_recovery अणु
	जोड़ अणु
		u8 recovery_retries;	/* used क्रम Lancer		*/
		u8 recovery_state;	/* used क्रम BEx and Skyhawk	*/
	पूर्ण;

	/* BEx/Skyhawk error recovery variables */
	bool recovery_supported;
	u16 ue_to_reset_समय;		/* Time after UE, to soft reset
					 * the chip - PF0 only
					 */
	u16 ue_to_poll_समय;		/* Time after UE, to Restart Polling
					 * of SLIPORT_SEMAPHORE reg
					 */
	u16 last_err_code;
	अचिन्हित दीर्घ probe_समय;
	अचिन्हित दीर्घ last_recovery_समय;

	/* Common to both Lancer & BEx/SH error recovery */
	u32 resched_delay;
	काष्ठा delayed_work err_detection_work;
पूर्ण;

/* Ethtool priv_flags */
#घोषणा	BE_DISABLE_TPE_RECOVERY	0x1

काष्ठा be_vxlan_port अणु
	काष्ठा list_head list;
	__be16 port;		/* VxLAN UDP dst port */
	पूर्णांक port_aliases;	/* alias count */
पूर्ण;

काष्ठा be_adapter अणु
	काष्ठा pci_dev *pdev;
	काष्ठा net_device *netdev;

	u8 __iomem *csr;	/* CSR BAR used only क्रम BE2/3 */
	u8 __iomem *db;		/* Door Bell */
	u8 __iomem *pcicfg;	/* On SH,BEx only. Shaकरोw of PCI config space */

	काष्ठा mutex mbox_lock; /* For serializing mbox cmds to BE card */
	काष्ठा be_dma_mem mbox_mem;
	/* Mbox mem is adjusted to align to 16 bytes. The allocated addr
	 * is stored क्रम मुक्तing purpose */
	काष्ठा be_dma_mem mbox_mem_alloced;

	काष्ठा be_mcc_obj mcc_obj;
	काष्ठा mutex mcc_lock;	/* For serializing mcc cmds to BE card */
	spinlock_t mcc_cq_lock;

	u16 cfg_num_rx_irqs;		/* configured via set-channels */
	u16 cfg_num_tx_irqs;		/* configured via set-channels */
	u16 num_evt_qs;
	u16 num_msix_vec;
	काष्ठा be_eq_obj eq_obj[MAX_EVT_QS];
	काष्ठा msix_entry msix_entries[MAX_MSIX_VECTORS];
	bool isr_रेजिस्टरed;

	/* TX Rings */
	u16 num_tx_qs;
	काष्ठा be_tx_obj tx_obj[MAX_TX_QS];

	/* Rx rings */
	u16 num_rx_qs;
	u16 num_rss_qs;
	u16 need_def_rxq;
	काष्ठा be_rx_obj rx_obj[MAX_RX_QS];
	u32 big_page_size;	/* Compounded page size shared by rx wrbs */

	काष्ठा be_drv_stats drv_stats;
	काष्ठा be_aic_obj aic_obj[MAX_EVT_QS];
	bool aic_enabled;
	u8 vlan_prio_bmap;	/* Available Priority BitMap */
	u16 recommended_prio_bits;/* Recommended Priority bits in vlan tag */
	काष्ठा be_dma_mem rx_filter; /* Cmd DMA mem क्रम rx-filter */

	काष्ठा be_dma_mem stats_cmd;
	/* Work queue used to perक्रमm periodic tasks like getting statistics */
	काष्ठा delayed_work work;
	u16 work_counter;

	u8 recovery_retries;
	u8 err_flags;
	bool pcicfg_mapped;	/* pcicfg obtained via pci_iomap() */
	u32 flags;
	u32 cmd_privileges;
	/* Ethtool knobs and info */
	अक्षर fw_ver[FW_VER_LEN];
	अक्षर fw_on_flash[FW_VER_LEN];

	/* IFACE filtering fields */
	पूर्णांक अगर_handle;		/* Used to configure filtering */
	u32 अगर_flags;		/* Interface filtering flags */
	u32 *pmac_id;		/* MAC addr handle used by BE card */
	काष्ठा be_eth_addr *uc_list;/* list of uc-addrs programmed (not perm) */
	u32 uc_macs;		/* Count of secondary UC MAC programmed */
	काष्ठा be_eth_addr *mc_list;/* list of mcast addrs programmed */
	u32 mc_count;
	अचिन्हित दीर्घ vids[BITS_TO_LONGS(VLAN_N_VID)];
	u16 vlans_added;
	bool update_uc_list;
	bool update_mc_list;
	काष्ठा mutex rx_filter_lock;/* For protecting vids[] & mc/uc_list[] */

	u32 beacon_state;	/* क्रम set_phys_id */

	u32 port_num;
	अक्षर port_name;
	u8 mc_type;
	u32 function_mode;
	u32 function_caps;
	u32 rx_fc;		/* Rx flow control */
	u32 tx_fc;		/* Tx flow control */
	bool stats_cmd_sent;
	काष्ठा अणु
		u32 size;
		u32 total_size;
		u64 io_addr;
	पूर्ण roce_db;
	u32 num_msix_roce_vec;
	काष्ठा ocrdma_dev *ocrdma_dev;
	काष्ठा list_head entry;

	u32 flash_status;
	काष्ठा completion et_cmd_compl;

	काष्ठा be_resources pool_res;	/* resources available क्रम the port */
	काष्ठा be_resources res;	/* resources available क्रम the func */
	u16 num_vfs;			/* Number of VFs provisioned by PF */
	u8 pf_num;			/* Numbering used by FW, starts at 0 */
	u8 vf_num;			/* Numbering used by FW, starts at 1 */
	u8 virtfn;
	काष्ठा be_vf_cfg *vf_cfg;
	bool be3_native;
	u32 sli_family;
	u8 hba_port_num;
	u16 pvid;
	__be16 vxlan_port;		/* offloaded vxlan port num */
	काष्ठा phy_info phy;
	u8 wol_cap;
	bool wol_en;
	u16 asic_rev;
	u16 qnq_vid;
	u32 msg_enable;
	पूर्णांक be_get_temp_freq;
	काष्ठा be_hwmon hwmon_info;
	काष्ठा rss_info rss_info;
	/* Filters क्रम packets that need to be sent to BMC */
	u32 bmc_filt_mask;
	u32 fat_dump_len;
	u16 serial_num[CNTL_SERIAL_NUM_WORDS];
	u8 phy_state; /* state of sfp optics (functional, faulted, etc.,) */
	u8 dev_mac[ETH_ALEN];
	u32 priv_flags; /* ethtool get/set_priv_flags() */
	काष्ठा be_error_recovery error_recovery;
पूर्ण;

/* Used क्रम defered FW config cmds. Add fields to this काष्ठा as reqd */
काष्ठा be_cmd_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा be_adapter *adapter;
पूर्ण;

#घोषणा be_physfn(adapter)		(!adapter->virtfn)
#घोषणा be_virtfn(adapter)		(adapter->virtfn)
#घोषणा sriov_enabled(adapter)		(adapter->flags &	\
					 BE_FLAGS_SRIOV_ENABLED)

#घोषणा क्रम_all_vfs(adapter, vf_cfg, i)					\
	क्रम (i = 0, vf_cfg = &adapter->vf_cfg[i]; i < adapter->num_vfs;	\
		i++, vf_cfg++)

#घोषणा ON				1
#घोषणा OFF				0

#घोषणा be_max_vlans(adapter)		(adapter->res.max_vlans)
#घोषणा be_max_uc(adapter)		(adapter->res.max_uc_mac)
#घोषणा be_max_mc(adapter)		(adapter->res.max_mcast_mac)
#घोषणा be_max_vfs(adapter)		(adapter->pool_res.max_vfs)
#घोषणा be_max_rss(adapter)		(adapter->res.max_rss_qs)
#घोषणा be_max_txqs(adapter)		(adapter->res.max_tx_qs)
#घोषणा be_max_prio_txqs(adapter)	(adapter->res.max_prio_tx_qs)
#घोषणा be_max_rxqs(adapter)		(adapter->res.max_rx_qs)
/* Max number of EQs available क्रम the function (NIC + RoCE (अगर enabled)) */
#घोषणा be_max_func_eqs(adapter)	(adapter->res.max_evt_qs)
/* Max number of EQs available avaialble only क्रम NIC */
#घोषणा be_max_nic_eqs(adapter)		(adapter->res.max_nic_evt_qs)
#घोषणा be_अगर_cap_flags(adapter)	(adapter->res.अगर_cap_flags)
#घोषणा be_max_pf_pool_rss_tables(adapter)	\
				(adapter->pool_res.max_rss_tables)
/* Max irqs avaialble क्रम NIC */
#घोषणा be_max_irqs(adapter)		\
			(min_t(u16, be_max_nic_eqs(adapter), num_online_cpus()))

/* Max irqs *needed* क्रम RX queues */
अटल अंतरभूत u16 be_max_rx_irqs(काष्ठा be_adapter *adapter)
अणु
	/* If no RSS, need atleast one irq क्रम def-RXQ */
	u16 num = max_t(u16, be_max_rss(adapter), 1);

	वापस min_t(u16, num, be_max_irqs(adapter));
पूर्ण

/* Max irqs *needed* क्रम TX queues */
अटल अंतरभूत u16 be_max_tx_irqs(काष्ठा be_adapter *adapter)
अणु
	वापस min_t(u16, be_max_txqs(adapter), be_max_irqs(adapter));
पूर्ण

/* Max irqs *needed* क्रम combined queues */
अटल अंतरभूत u16 be_max_qp_irqs(काष्ठा be_adapter *adapter)
अणु
	वापस min(be_max_tx_irqs(adapter), be_max_rx_irqs(adapter));
पूर्ण

/* Max irqs *needed* क्रम RX and TX queues together */
अटल अंतरभूत u16 be_max_any_irqs(काष्ठा be_adapter *adapter)
अणु
	वापस max(be_max_tx_irqs(adapter), be_max_rx_irqs(adapter));
पूर्ण

/* Is BE in pvid_tagging mode */
#घोषणा be_pvid_tagging_enabled(adapter)	(adapter->pvid)

/* Is BE in QNQ multi-channel mode */
#घोषणा be_is_qnq_mode(adapter)		(adapter->function_mode & QNQ_MODE)

#अगर_घोषित CONFIG_BE2NET_LANCER
#घोषणा lancer_chip(adapter)	(adapter->pdev->device == OC_DEVICE_ID3 || \
				 adapter->pdev->device == OC_DEVICE_ID4)
#अन्यथा
#घोषणा lancer_chip(adapter)	(0)
#पूर्ण_अगर /* CONFIG_BE2NET_LANCER */

#अगर_घोषित CONFIG_BE2NET_SKYHAWK
#घोषणा skyhawk_chip(adapter)	(adapter->pdev->device == OC_DEVICE_ID5 || \
				 adapter->pdev->device == OC_DEVICE_ID6)
#अन्यथा
#घोषणा skyhawk_chip(adapter)	(0)
#पूर्ण_अगर /* CONFIG_BE2NET_SKYHAWK */

#अगर_घोषित CONFIG_BE2NET_BE3
#घोषणा BE3_chip(adapter)	(adapter->pdev->device == BE_DEVICE_ID2 || \
				 adapter->pdev->device == OC_DEVICE_ID2)
#अन्यथा
#घोषणा BE3_chip(adapter)	(0)
#पूर्ण_अगर /* CONFIG_BE2NET_BE3 */

#अगर_घोषित CONFIG_BE2NET_BE2
#घोषणा BE2_chip(adapter)	(adapter->pdev->device == BE_DEVICE_ID1 || \
				 adapter->pdev->device == OC_DEVICE_ID1)
#अन्यथा
#घोषणा BE2_chip(adapter)	(0)
#पूर्ण_अगर /* CONFIG_BE2NET_BE2 */

#घोषणा BEx_chip(adapter)	(BE3_chip(adapter) || BE2_chip(adapter))

#घोषणा be_roce_supported(adapter)	(skyhawk_chip(adapter) && \
					(adapter->function_mode & RDMA_ENABLED))

बाह्य स्थिर काष्ठा ethtool_ops be_ethtool_ops;

#घोषणा msix_enabled(adapter)		(adapter->num_msix_vec > 0)
#घोषणा num_irqs(adapter)		(msix_enabled(adapter) ?	\
						adapter->num_msix_vec : 1)
#घोषणा tx_stats(txo)			(&(txo)->stats)
#घोषणा rx_stats(rxo)			(&(rxo)->stats)

/* The शेष RXQ is the last RXQ */
#घोषणा शेष_rxo(adpt)		(&adpt->rx_obj[adpt->num_rx_qs - 1])

#घोषणा क्रम_all_rx_queues(adapter, rxo, i)				\
	क्रम (i = 0, rxo = &adapter->rx_obj[i]; i < adapter->num_rx_qs;	\
		i++, rxo++)

#घोषणा क्रम_all_rss_queues(adapter, rxo, i)				\
	क्रम (i = 0, rxo = &adapter->rx_obj[i]; i < adapter->num_rss_qs;	\
		i++, rxo++)

#घोषणा क्रम_all_tx_queues(adapter, txo, i)				\
	क्रम (i = 0, txo = &adapter->tx_obj[i]; i < adapter->num_tx_qs;	\
		i++, txo++)

#घोषणा क्रम_all_evt_queues(adapter, eqo, i)				\
	क्रम (i = 0, eqo = &adapter->eq_obj[i]; i < adapter->num_evt_qs; \
		i++, eqo++)

#घोषणा क्रम_all_rx_queues_on_eq(adapter, eqo, rxo, i)			\
	क्रम (i = eqo->idx, rxo = &adapter->rx_obj[i]; i < adapter->num_rx_qs;\
		 i += adapter->num_evt_qs, rxo += adapter->num_evt_qs)

#घोषणा क्रम_all_tx_queues_on_eq(adapter, eqo, txo, i)			\
	क्रम (i = eqo->idx, txo = &adapter->tx_obj[i]; i < adapter->num_tx_qs;\
		i += adapter->num_evt_qs, txo += adapter->num_evt_qs)

#घोषणा is_mcc_eqo(eqo)			(eqo->idx == 0)
#घोषणा mcc_eqo(adapter)		(&adapter->eq_obj[0])

#घोषणा PAGE_SHIFT_4K		12
#घोषणा PAGE_SIZE_4K		(1 << PAGE_SHIFT_4K)

/* Returns number of pages spanned by the data starting at the given addr */
#घोषणा PAGES_4K_SPANNED(_address, size) 				\
		((u32)((((माप_प्रकार)(_address) & (PAGE_SIZE_4K - 1)) + 	\
			(size) + (PAGE_SIZE_4K - 1)) >> PAGE_SHIFT_4K))

/* Returns bit offset within a DWORD of a bitfield */
#घोषणा AMAP_BIT_OFFSET(_काष्ठा, field)  				\
		(((माप_प्रकार)&(((_काष्ठा *)0)->field))%32)

/* Returns the bit mask of the field that is NOT shअगरted पूर्णांकo location. */
अटल अंतरभूत u32 amap_mask(u32 bitsize)
अणु
	वापस (bitsize == 32 ? 0xFFFFFFFF : (1 << bitsize) - 1);
पूर्ण

अटल अंतरभूत व्योम
amap_set(व्योम *ptr, u32 dw_offset, u32 mask, u32 offset, u32 value)
अणु
	u32 *dw = (u32 *) ptr + dw_offset;
	*dw &= ~(mask << offset);
	*dw |= (mask & value) << offset;
पूर्ण

#घोषणा AMAP_SET_BITS(_काष्ठा, field, ptr, val)				\
		amap_set(ptr,						\
			दुरत्व(_काष्ठा, field)/32,			\
			amap_mask(माप(((_काष्ठा *)0)->field)),	\
			AMAP_BIT_OFFSET(_काष्ठा, field),		\
			val)

अटल अंतरभूत u32 amap_get(व्योम *ptr, u32 dw_offset, u32 mask, u32 offset)
अणु
	u32 *dw = (u32 *) ptr;
	वापस mask & (*(dw + dw_offset) >> offset);
पूर्ण

#घोषणा AMAP_GET_BITS(_काष्ठा, field, ptr)				\
		amap_get(ptr,						\
			दुरत्व(_काष्ठा, field)/32,			\
			amap_mask(माप(((_काष्ठा *)0)->field)),	\
			AMAP_BIT_OFFSET(_काष्ठा, field))

#घोषणा GET_RX_COMPL_V0_BITS(field, ptr)				\
		AMAP_GET_BITS(काष्ठा amap_eth_rx_compl_v0, field, ptr)

#घोषणा GET_RX_COMPL_V1_BITS(field, ptr)				\
		AMAP_GET_BITS(काष्ठा amap_eth_rx_compl_v1, field, ptr)

#घोषणा GET_TX_COMPL_BITS(field, ptr)					\
		AMAP_GET_BITS(काष्ठा amap_eth_tx_compl, field, ptr)

#घोषणा SET_TX_WRB_HDR_BITS(field, ptr, val)				\
		AMAP_SET_BITS(काष्ठा amap_eth_hdr_wrb, field, ptr, val)

#घोषणा be_dws_cpu_to_le(wrb, len)	swap_dws(wrb, len)
#घोषणा be_dws_le_to_cpu(wrb, len)	swap_dws(wrb, len)
अटल अंतरभूत व्योम swap_dws(व्योम *wrb, पूर्णांक len)
अणु
#अगर_घोषित __BIG_ENDIAN
	u32 *dw = wrb;
	BUG_ON(len % 4);
	करो अणु
		*dw = cpu_to_le32(*dw);
		dw++;
		len -= 4;
	पूर्ण जबतक (len);
#पूर्ण_अगर				/* __BIG_ENDIAN */
पूर्ण

#घोषणा be_cmd_status(status)		(status > 0 ? -EIO : status)

अटल अंतरभूत u8 is_tcp_pkt(काष्ठा sk_buff *skb)
अणु
	u8 val = 0;

	अगर (ip_hdr(skb)->version == 4)
		val = (ip_hdr(skb)->protocol == IPPROTO_TCP);
	अन्यथा अगर (ip_hdr(skb)->version == 6)
		val = (ipv6_hdr(skb)->nexthdr == NEXTHDR_TCP);

	वापस val;
पूर्ण

अटल अंतरभूत u8 is_udp_pkt(काष्ठा sk_buff *skb)
अणु
	u8 val = 0;

	अगर (ip_hdr(skb)->version == 4)
		val = (ip_hdr(skb)->protocol == IPPROTO_UDP);
	अन्यथा अगर (ip_hdr(skb)->version == 6)
		val = (ipv6_hdr(skb)->nexthdr == NEXTHDR_UDP);

	वापस val;
पूर्ण

अटल अंतरभूत bool is_ipv4_pkt(काष्ठा sk_buff *skb)
अणु
	वापस skb->protocol == htons(ETH_P_IP) && ip_hdr(skb)->version == 4;
पूर्ण

अटल अंतरभूत bool is_ipv6_ext_hdr(काष्ठा sk_buff *skb)
अणु
	अगर (ip_hdr(skb)->version == 6)
		वापस ipv6_ext_hdr(ipv6_hdr(skb)->nexthdr);
	अन्यथा
		वापस false;
पूर्ण

#घोषणा be_error_recovering(adapter)	\
		(adapter->flags & BE_FLAGS_TRY_RECOVERY)

#घोषणा BE_ERROR_EEH		1
#घोषणा BE_ERROR_UE		BIT(1)
#घोषणा BE_ERROR_FW		BIT(2)
#घोषणा BE_ERROR_TX		BIT(3)
#घोषणा BE_ERROR_HW		(BE_ERROR_EEH | BE_ERROR_UE | BE_ERROR_TX)
#घोषणा BE_ERROR_ANY		(BE_ERROR_EEH | BE_ERROR_UE | BE_ERROR_FW | \
				 BE_ERROR_TX)
#घोषणा BE_CLEAR_ALL		0xFF

अटल अंतरभूत u8 be_check_error(काष्ठा be_adapter *adapter, u32 err_type)
अणु
	वापस (adapter->err_flags & err_type);
पूर्ण

अटल अंतरभूत व्योम be_set_error(काष्ठा be_adapter *adapter, पूर्णांक err_type)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	adapter->err_flags |= err_type;
	netअगर_carrier_off(netdev);

	dev_info(&adapter->pdev->dev, "%s: Link down\n", netdev->name);
पूर्ण

अटल अंतरभूत व्योम  be_clear_error(काष्ठा be_adapter *adapter, पूर्णांक err_type)
अणु
	adapter->err_flags &= ~err_type;
पूर्ण

अटल अंतरभूत bool be_multi_rxq(स्थिर काष्ठा be_adapter *adapter)
अणु
	वापस adapter->num_rx_qs > 1;
पूर्ण

व्योम be_cq_notअगरy(काष्ठा be_adapter *adapter, u16 qid, bool arm,
		  u16 num_popped);
व्योम be_link_status_update(काष्ठा be_adapter *adapter, u8 link_status);
व्योम be_parse_stats(काष्ठा be_adapter *adapter);
पूर्णांक be_load_fw(काष्ठा be_adapter *adapter, u8 *func);
bool be_is_wol_supported(काष्ठा be_adapter *adapter);
bool be_छोड़ो_supported(काष्ठा be_adapter *adapter);
u32 be_get_fw_log_level(काष्ठा be_adapter *adapter);
पूर्णांक be_update_queues(काष्ठा be_adapter *adapter);
पूर्णांक be_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
व्योम be_eqd_update(काष्ठा be_adapter *adapter, bool क्रमce_update);

/*
 * पूर्णांकernal function to initialize-cleanup roce device.
 */
व्योम be_roce_dev_add(काष्ठा be_adapter *);
व्योम be_roce_dev_हटाओ(काष्ठा be_adapter *);

/*
 * पूर्णांकernal function to खोलो-बंद roce device during अगरup-अगरकरोwn.
 */
व्योम be_roce_dev_shutकरोwn(काष्ठा be_adapter *);

#पूर्ण_अगर				/* BE_H */
