<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright 2015-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#अगर_अघोषित ENA_H
#घोषणा ENA_H

#समावेश <linux/bitops.h>
#समावेश <linux/dim.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>

#समावेश "ena_com.h"
#समावेश "ena_eth_com.h"

#घोषणा DRV_MODULE_GEN_MAJOR	2
#घोषणा DRV_MODULE_GEN_MINOR	1
#घोषणा DRV_MODULE_GEN_SUBMINOR 0

#घोषणा DRV_MODULE_NAME		"ena"

#घोषणा DEVICE_NAME	"Elastic Network Adapter (ENA)"

/* 1 क्रम AENQ + ADMIN */
#घोषणा ENA_ADMIN_MSIX_VEC		1
#घोषणा ENA_MAX_MSIX_VEC(io_queues)	(ENA_ADMIN_MSIX_VEC + (io_queues))

/* The ENA buffer length fields is 16 bit दीर्घ. So when PAGE_SIZE == 64kB the
 * driver passes 0.
 * Since the max packet size the ENA handles is ~9kB limit the buffer length to
 * 16kB.
 */
#अगर PAGE_SIZE > SZ_16K
#घोषणा ENA_PAGE_SIZE (_AC(SZ_16K, UL))
#अन्यथा
#घोषणा ENA_PAGE_SIZE PAGE_SIZE
#पूर्ण_अगर

#घोषणा ENA_MIN_MSIX_VEC		2

#घोषणा ENA_REG_BAR			0
#घोषणा ENA_MEM_BAR			2
#घोषणा ENA_BAR_MASK (BIT(ENA_REG_BAR) | BIT(ENA_MEM_BAR))

#घोषणा ENA_DEFAULT_RING_SIZE	(1024)
#घोषणा ENA_MIN_RING_SIZE	(256)

#घोषणा ENA_MIN_NUM_IO_QUEUES	(1)

#घोषणा ENA_TX_WAKEUP_THRESH		(MAX_SKB_FRAGS + 2)
#घोषणा ENA_DEFAULT_RX_COPYBREAK	(256 - NET_IP_ALIGN)

/* limit the buffer size to 600 bytes to handle MTU changes from very
 * small to very large, in which हाल the number of buffers per packet
 * could exceed ENA_PKT_MAX_BUFS
 */
#घोषणा ENA_DEFAULT_MIN_RX_BUFF_ALLOC_SIZE 600

#घोषणा ENA_MIN_MTU		128

#घोषणा ENA_NAME_MAX_LEN	20
#घोषणा ENA_IRQNAME_SIZE	40

#घोषणा ENA_PKT_MAX_BUFS	19

#घोषणा ENA_RX_RSS_TABLE_LOG_SIZE  7
#घोषणा ENA_RX_RSS_TABLE_SIZE	(1 << ENA_RX_RSS_TABLE_LOG_SIZE)

/* The number of tx packet completions that will be handled each NAPI poll
 * cycle is ring_size / ENA_TX_POLL_BUDGET_DIVIDER.
 */
#घोषणा ENA_TX_POLL_BUDGET_DIVIDER	4

/* Refill Rx queue when number of required descriptors is above
 * QUEUE_SIZE / ENA_RX_REFILL_THRESH_DIVIDER or ENA_RX_REFILL_THRESH_PACKET
 */
#घोषणा ENA_RX_REFILL_THRESH_DIVIDER	8
#घोषणा ENA_RX_REFILL_THRESH_PACKET	256

/* Number of queues to check क्रम missing queues per समयr service */
#घोषणा ENA_MONITORED_TX_QUEUES	4
/* Max समयout packets beक्रमe device reset */
#घोषणा MAX_NUM_OF_TIMEOUTED_PACKETS 128

#घोषणा ENA_TX_RING_IDX_NEXT(idx, ring_size) (((idx) + 1) & ((ring_size) - 1))

#घोषणा ENA_RX_RING_IDX_NEXT(idx, ring_size) (((idx) + 1) & ((ring_size) - 1))
#घोषणा ENA_RX_RING_IDX_ADD(idx, n, ring_size) \
	(((idx) + (n)) & ((ring_size) - 1))

#घोषणा ENA_IO_TXQ_IDX(q)	(2 * (q))
#घोषणा ENA_IO_RXQ_IDX(q)	(2 * (q) + 1)
#घोषणा ENA_IO_TXQ_IDX_TO_COMBINED_IDX(q)	((q) / 2)
#घोषणा ENA_IO_RXQ_IDX_TO_COMBINED_IDX(q)	(((q) - 1) / 2)

#घोषणा ENA_MGMNT_IRQ_IDX		0
#घोषणा ENA_IO_IRQ_FIRST_IDX		1
#घोषणा ENA_IO_IRQ_IDX(q)		(ENA_IO_IRQ_FIRST_IDX + (q))

#घोषणा ENA_ADMIN_POLL_DELAY_US 100

/* ENA device should send keep alive msg every 1 sec.
 * We रुको क्रम 6 sec just to be on the safe side.
 */
#घोषणा ENA_DEVICE_KALIVE_TIMEOUT	(6 * HZ)
#घोषणा ENA_MAX_NO_INTERRUPT_ITERATIONS 3

#घोषणा ENA_MMIO_DISABLE_REG_READ	BIT(0)

/* The max MTU size is configured to be the ethernet frame size without
 * the overhead of the ethernet header, which can have a VLAN header, and
 * a frame check sequence (FCS).
 * The buffer size we share with the device is defined to be ENA_PAGE_SIZE
 */

#घोषणा ENA_XDP_MAX_MTU (ENA_PAGE_SIZE - ETH_HLEN - ETH_FCS_LEN -	\
			 VLAN_HLEN - XDP_PACKET_HEADROOM -		\
			 SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)))

#घोषणा ENA_IS_XDP_INDEX(adapter, index) (((index) >= (adapter)->xdp_first_ring) && \
	((index) < (adapter)->xdp_first_ring + (adapter)->xdp_num_queues))

काष्ठा ena_irq अणु
	irq_handler_t handler;
	व्योम *data;
	पूर्णांक cpu;
	u32 vector;
	cpumask_t affinity_hपूर्णांक_mask;
	अक्षर name[ENA_IRQNAME_SIZE];
पूर्ण;

काष्ठा ena_napi अणु
	काष्ठा napi_काष्ठा napi ____cacheline_aligned;
	काष्ठा ena_ring *tx_ring;
	काष्ठा ena_ring *rx_ring;
	काष्ठा ena_ring *xdp_ring;
	bool first_पूर्णांकerrupt;
	bool पूर्णांकerrupts_masked;
	u32 qid;
	काष्ठा dim dim;
पूर्ण;

काष्ठा ena_calc_queue_size_ctx अणु
	काष्ठा ena_com_dev_get_features_ctx *get_feat_ctx;
	काष्ठा ena_com_dev *ena_dev;
	काष्ठा pci_dev *pdev;
	u32 tx_queue_size;
	u32 rx_queue_size;
	u32 max_tx_queue_size;
	u32 max_rx_queue_size;
	u16 max_tx_sgl_size;
	u16 max_rx_sgl_size;
पूर्ण;

काष्ठा ena_tx_buffer अणु
	काष्ठा sk_buff *skb;
	/* num of ena desc क्रम this specअगरic skb
	 * (includes data desc and metadata desc)
	 */
	u32 tx_descs;
	/* num of buffers used by this skb */
	u32 num_of_bufs;

	/* XDP buffer काष्ठाure which is used क्रम sending packets in
	 * the xdp queues
	 */
	काष्ठा xdp_frame *xdpf;

	/* Indicate अगर bufs[0] map the linear data of the skb. */
	u8 map_linear_data;

	/* Used क्रम detect missing tx packets to limit the number of prपूर्णांकs */
	u32 prपूर्णांक_once;
	/* Save the last jअगरfies to detect missing tx packets
	 *
	 * sets to non zero value on ena_start_xmit and set to zero on
	 * napi and समयr_Service_routine.
	 *
	 * जबतक this value is not रक्षित by lock,
	 * a given packet is not expected to be handled by ena_start_xmit
	 * and by napi/समयr_service at the same समय.
	 */
	अचिन्हित दीर्घ last_jअगरfies;
	काष्ठा ena_com_buf bufs[ENA_PKT_MAX_BUFS];
पूर्ण ____cacheline_aligned;

काष्ठा ena_rx_buffer अणु
	काष्ठा sk_buff *skb;
	काष्ठा page *page;
	u32 page_offset;
	काष्ठा ena_com_buf ena_buf;
पूर्ण ____cacheline_aligned;

काष्ठा ena_stats_tx अणु
	u64 cnt;
	u64 bytes;
	u64 queue_stop;
	u64 prepare_ctx_err;
	u64 queue_wakeup;
	u64 dma_mapping_err;
	u64 linearize;
	u64 linearize_failed;
	u64 napi_comp;
	u64 tx_poll;
	u64 करोorbells;
	u64 bad_req_id;
	u64 llq_buffer_copy;
	u64 missed_tx;
	u64 unmask_पूर्णांकerrupt;
पूर्ण;

काष्ठा ena_stats_rx अणु
	u64 cnt;
	u64 bytes;
	u64 rx_copyअवरोध_pkt;
	u64 csum_good;
	u64 refil_partial;
	u64 bad_csum;
	u64 page_alloc_fail;
	u64 skb_alloc_fail;
	u64 dma_mapping_err;
	u64 bad_desc_num;
	u64 bad_req_id;
	u64 empty_rx_ring;
	u64 csum_unchecked;
	u64 xdp_पातed;
	u64 xdp_drop;
	u64 xdp_pass;
	u64 xdp_tx;
	u64 xdp_invalid;
	u64 xdp_redirect;
पूर्ण;

काष्ठा ena_ring अणु
	/* Holds the empty requests क्रम TX/RX
	 * out of order completions
	 */
	u16 *मुक्त_ids;

	जोड़ अणु
		काष्ठा ena_tx_buffer *tx_buffer_info;
		काष्ठा ena_rx_buffer *rx_buffer_info;
	पूर्ण;

	/* cache ptr to aव्योम using the adapter */
	काष्ठा device *dev;
	काष्ठा pci_dev *pdev;
	काष्ठा napi_काष्ठा *napi;
	काष्ठा net_device *netdev;
	काष्ठा ena_com_dev *ena_dev;
	काष्ठा ena_adapter *adapter;
	काष्ठा ena_com_io_cq *ena_com_io_cq;
	काष्ठा ena_com_io_sq *ena_com_io_sq;
	काष्ठा bpf_prog *xdp_bpf_prog;
	काष्ठा xdp_rxq_info xdp_rxq;
	spinlock_t xdp_tx_lock;	/* synchronize XDP TX/Redirect traffic */

	u16 next_to_use;
	u16 next_to_clean;
	u16 rx_copyअवरोध;
	u16 rx_headroom;
	u16 qid;
	u16 mtu;
	u16 sgl_size;

	/* The maximum header length the device can handle */
	u8 tx_max_header_size;

	bool first_पूर्णांकerrupt;
	bool disable_meta_caching;
	u16 no_पूर्णांकerrupt_event_cnt;

	/* cpu क्रम TPH */
	पूर्णांक cpu;
	 /* number of tx/rx_buffer_info's entries */
	पूर्णांक ring_size;

	क्रमागत ena_admin_placement_policy_type tx_mem_queue_type;

	काष्ठा ena_com_rx_buf_info ena_bufs[ENA_PKT_MAX_BUFS];
	u32  smoothed_पूर्णांकerval;
	u32  per_napi_packets;
	u16 non_empty_napi_events;
	काष्ठा u64_stats_sync syncp;
	जोड़ अणु
		काष्ठा ena_stats_tx tx_stats;
		काष्ठा ena_stats_rx rx_stats;
	पूर्ण;

	u8 *push_buf_पूर्णांकermediate_buf;
	पूर्णांक empty_rx_queue;
पूर्ण ____cacheline_aligned;

काष्ठा ena_stats_dev अणु
	u64 tx_समयout;
	u64 suspend;
	u64 resume;
	u64 wd_expired;
	u64 पूर्णांकerface_up;
	u64 पूर्णांकerface_करोwn;
	u64 admin_q_छोड़ो;
	u64 rx_drops;
	u64 tx_drops;
पूर्ण;

क्रमागत ena_flags_t अणु
	ENA_FLAG_DEVICE_RUNNING,
	ENA_FLAG_DEV_UP,
	ENA_FLAG_LINK_UP,
	ENA_FLAG_MSIX_ENABLED,
	ENA_FLAG_TRIGGER_RESET,
	ENA_FLAG_ONGOING_RESET
पूर्ण;

/* adapter specअगरic निजी data काष्ठाure */
काष्ठा ena_adapter अणु
	काष्ठा ena_com_dev *ena_dev;
	/* OS defined काष्ठाs */
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;

	/* rx packets that लघुer that this len will be copied to the skb
	 * header
	 */
	u32 rx_copyअवरोध;
	u32 max_mtu;

	u32 num_io_queues;
	u32 max_num_io_queues;

	पूर्णांक msix_vecs;

	u32 missing_tx_completion_threshold;

	u32 requested_tx_ring_size;
	u32 requested_rx_ring_size;

	u32 max_tx_ring_size;
	u32 max_rx_ring_size;

	u32 msg_enable;

	u16 max_tx_sgl_size;
	u16 max_rx_sgl_size;

	u8 mac_addr[ETH_ALEN];

	अचिन्हित दीर्घ keep_alive_समयout;
	अचिन्हित दीर्घ missing_tx_completion_to;

	अक्षर name[ENA_NAME_MAX_LEN];

	अचिन्हित दीर्घ flags;
	/* TX */
	काष्ठा ena_ring tx_ring[ENA_MAX_NUM_IO_QUEUES]
		____cacheline_aligned_in_smp;

	/* RX */
	काष्ठा ena_ring rx_ring[ENA_MAX_NUM_IO_QUEUES]
		____cacheline_aligned_in_smp;

	काष्ठा ena_napi ena_napi[ENA_MAX_NUM_IO_QUEUES];

	काष्ठा ena_irq irq_tbl[ENA_MAX_MSIX_VEC(ENA_MAX_NUM_IO_QUEUES)];

	/* समयr service */
	काष्ठा work_काष्ठा reset_task;
	काष्ठा समयr_list समयr_service;

	bool wd_state;
	bool dev_up_beक्रमe_reset;
	bool disable_meta_caching;
	अचिन्हित दीर्घ last_keep_alive_jअगरfies;

	काष्ठा u64_stats_sync syncp;
	काष्ठा ena_stats_dev dev_stats;
	काष्ठा ena_admin_eni_stats eni_stats;
	bool eni_stats_supported;

	/* last queue index that was checked क्रम uncompleted tx packets */
	u32 last_monitored_tx_qid;

	क्रमागत ena_regs_reset_reason_types reset_reason;

	काष्ठा bpf_prog *xdp_bpf_prog;
	u32 xdp_first_ring;
	u32 xdp_num_queues;
पूर्ण;

व्योम ena_set_ethtool_ops(काष्ठा net_device *netdev);

व्योम ena_dump_stats_to_dmesg(काष्ठा ena_adapter *adapter);

व्योम ena_dump_stats_to_buf(काष्ठा ena_adapter *adapter, u8 *buf);

पूर्णांक ena_update_hw_stats(काष्ठा ena_adapter *adapter);

पूर्णांक ena_update_queue_sizes(काष्ठा ena_adapter *adapter,
			   u32 new_tx_size,
			   u32 new_rx_size);

पूर्णांक ena_update_queue_count(काष्ठा ena_adapter *adapter, u32 new_channel_count);

पूर्णांक ena_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset);

क्रमागत ena_xdp_errors_t अणु
	ENA_XDP_ALLOWED = 0,
	ENA_XDP_CURRENT_MTU_TOO_LARGE,
	ENA_XDP_NO_ENOUGH_QUEUES,
पूर्ण;

अटल अंतरभूत bool ena_xdp_queues_present(काष्ठा ena_adapter *adapter)
अणु
	वापस adapter->xdp_first_ring != 0;
पूर्ण

अटल अंतरभूत bool ena_xdp_present(काष्ठा ena_adapter *adapter)
अणु
	वापस !!adapter->xdp_bpf_prog;
पूर्ण

अटल अंतरभूत bool ena_xdp_present_ring(काष्ठा ena_ring *ring)
अणु
	वापस !!ring->xdp_bpf_prog;
पूर्ण

अटल अंतरभूत bool ena_xdp_legal_queue_count(काष्ठा ena_adapter *adapter,
					     u32 queues)
अणु
	वापस 2 * queues <= adapter->max_num_io_queues;
पूर्ण

अटल अंतरभूत क्रमागत ena_xdp_errors_t ena_xdp_allowed(काष्ठा ena_adapter *adapter)
अणु
	क्रमागत ena_xdp_errors_t rc = ENA_XDP_ALLOWED;

	अगर (adapter->netdev->mtu > ENA_XDP_MAX_MTU)
		rc = ENA_XDP_CURRENT_MTU_TOO_LARGE;
	अन्यथा अगर (!ena_xdp_legal_queue_count(adapter, adapter->num_io_queues))
		rc = ENA_XDP_NO_ENOUGH_QUEUES;

	वापस rc;
पूर्ण

#पूर्ण_अगर /* !(ENA_H) */
