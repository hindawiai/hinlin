<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
 * Google भव Ethernet (gve) driver
 *
 * Copyright (C) 2015-2019 Google, Inc.
 */

#अगर_अघोषित _GVE_H_
#घोषणा _GVE_H_

#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश "gve_desc.h"

#अगर_अघोषित PCI_VENDOR_ID_GOOGLE
#घोषणा PCI_VENDOR_ID_GOOGLE	0x1ae0
#पूर्ण_अगर

#घोषणा PCI_DEV_ID_GVNIC	0x0042

#घोषणा GVE_REGISTER_BAR	0
#घोषणा GVE_DOORBELL_BAR	2

/* Driver can alloc up to 2 segments क्रम the header and 2 क्रम the payload. */
#घोषणा GVE_TX_MAX_IOVEC	4
/* 1 क्रम management, 1 क्रम rx, 1 क्रम tx */
#घोषणा GVE_MIN_MSIX 3

/* Numbers of gve tx/rx stats in stats report. */
#घोषणा GVE_TX_STATS_REPORT_NUM	5
#घोषणा GVE_RX_STATS_REPORT_NUM	2

/* Interval to schedule a stats report update, 20000ms. */
#घोषणा GVE_STATS_REPORT_TIMER_PERIOD	20000

/* Numbers of NIC tx/rx stats in stats report. */
#घोषणा NIC_TX_STATS_REPORT_NUM	0
#घोषणा NIC_RX_STATS_REPORT_NUM	4

#घोषणा GVE_DATA_SLOT_ADDR_PAGE_MASK (~(PAGE_SIZE - 1))

/* Each slot in the desc ring has a 1:1 mapping to a slot in the data ring */
काष्ठा gve_rx_desc_queue अणु
	काष्ठा gve_rx_desc *desc_ring; /* the descriptor ring */
	dma_addr_t bus; /* the bus क्रम the desc_ring */
	u8 seqno; /* the next expected seqno क्रम this desc*/
पूर्ण;

/* The page info क्रम a single slot in the RX data queue */
काष्ठा gve_rx_slot_page_info अणु
	काष्ठा page *page;
	व्योम *page_address;
	u8 page_offset; /* flipped to second half? */
	u8 can_flip;
पूर्ण;

/* A list of pages रेजिस्टरed with the device during setup and used by a queue
 * as buffers
 */
काष्ठा gve_queue_page_list अणु
	u32 id; /* unique id */
	u32 num_entries;
	काष्ठा page **pages; /* list of num_entries pages */
	dma_addr_t *page_buses; /* the dma addrs of the pages */
पूर्ण;

/* Each slot in the data ring has a 1:1 mapping to a slot in the desc ring */
काष्ठा gve_rx_data_queue अणु
	जोड़ gve_rx_data_slot *data_ring; /* पढ़ो by NIC */
	dma_addr_t data_bus; /* dma mapping of the slots */
	काष्ठा gve_rx_slot_page_info *page_info; /* page info of the buffers */
	काष्ठा gve_queue_page_list *qpl; /* qpl asचिन्हित to this queue */
	u8 raw_addressing; /* use raw_addressing? */
पूर्ण;

काष्ठा gve_priv;

/* An RX ring that contains a घातer-of-two sized desc and data ring. */
काष्ठा gve_rx_ring अणु
	काष्ठा gve_priv *gve;
	काष्ठा gve_rx_desc_queue desc;
	काष्ठा gve_rx_data_queue data;
	u64 rbytes; /* मुक्त-running bytes received */
	u64 rpackets; /* मुक्त-running packets received */
	u32 cnt; /* मुक्त-running total number of completed packets */
	u32 fill_cnt; /* मुक्त-running total number of descs and buffs posted */
	u32 mask; /* masks the cnt and fill_cnt to the size of the ring */
	u32 db_threshold; /* threshold क्रम posting new buffs and descs */
	u64 rx_copyअवरोध_pkt; /* मुक्त-running count of copyअवरोध packets */
	u64 rx_copied_pkt; /* मुक्त-running total number of copied packets */
	u64 rx_skb_alloc_fail; /* मुक्त-running count of skb alloc fails */
	u64 rx_buf_alloc_fail; /* मुक्त-running count of buffer alloc fails */
	u64 rx_desc_err_dropped_pkt; /* मुक्त-running count of packets dropped by descriptor error */
	u32 q_num; /* queue index */
	u32 ntfy_id; /* notअगरication block index */
	काष्ठा gve_queue_resources *q_resources; /* head and tail poपूर्णांकer idx */
	dma_addr_t q_resources_bus; /* dma address क्रम the queue resources */
	काष्ठा u64_stats_sync statss; /* sync stats क्रम 32bit archs */
पूर्ण;

/* A TX desc ring entry */
जोड़ gve_tx_desc अणु
	काष्ठा gve_tx_pkt_desc pkt; /* first desc क्रम a packet */
	काष्ठा gve_tx_seg_desc seg; /* subsequent descs क्रम a packet */
पूर्ण;

/* Tracks the memory in the fअगरo occupied by a segment of a packet */
काष्ठा gve_tx_iovec अणु
	u32 iov_offset; /* offset पूर्णांकo this segment */
	u32 iov_len; /* length */
	u32 iov_padding; /* padding associated with this segment */
पूर्ण;

काष्ठा gve_tx_dma_buf अणु
	DEFINE_DMA_UNMAP_ADDR(dma);
	DEFINE_DMA_UNMAP_LEN(len);
पूर्ण;

/* Tracks the memory in the fअगरo occupied by the skb. Mapped 1:1 to a desc
 * ring entry but only used क्रम a pkt_desc not a seg_desc
 */
काष्ठा gve_tx_buffer_state अणु
	काष्ठा sk_buff *skb; /* skb क्रम this pkt */
	जोड़ अणु
		काष्ठा gve_tx_iovec iov[GVE_TX_MAX_IOVEC]; /* segments of this pkt */
		काष्ठा gve_tx_dma_buf buf;
	पूर्ण;
पूर्ण;

/* A TX buffer - each queue has one */
काष्ठा gve_tx_fअगरo अणु
	व्योम *base; /* address of base of FIFO */
	u32 size; /* total size */
	atomic_t available; /* how much space is still available */
	u32 head; /* offset to ग_लिखो at */
	काष्ठा gve_queue_page_list *qpl; /* QPL mapped पूर्णांकo this FIFO */
पूर्ण;

/* A TX ring that contains a घातer-of-two sized desc ring and a FIFO buffer */
काष्ठा gve_tx_ring अणु
	/* Cacheline 0 -- Accessed & dirtied during transmit */
	काष्ठा gve_tx_fअगरo tx_fअगरo;
	u32 req; /* driver tracked head poपूर्णांकer */
	u32 करोne; /* driver tracked tail poपूर्णांकer */

	/* Cacheline 1 -- Accessed & dirtied during gve_clean_tx_करोne */
	__be32 last_nic_करोne ____cacheline_aligned; /* NIC tail poपूर्णांकer */
	u64 pkt_करोne; /* मुक्त-running - total packets completed */
	u64 bytes_करोne; /* मुक्त-running - total bytes completed */
	u64 dropped_pkt; /* मुक्त-running - total packets dropped */
	u64 dma_mapping_error; /* count of dma mapping errors */

	/* Cacheline 2 -- Read-mostly fields */
	जोड़ gve_tx_desc *desc ____cacheline_aligned;
	काष्ठा gve_tx_buffer_state *info; /* Maps 1:1 to a desc */
	काष्ठा netdev_queue *netdev_txq;
	काष्ठा gve_queue_resources *q_resources; /* head and tail poपूर्णांकer idx */
	काष्ठा device *dev;
	u32 mask; /* masks req and करोne करोwn to queue size */
	u8 raw_addressing; /* use raw_addressing? */

	/* Slow-path fields */
	u32 q_num ____cacheline_aligned; /* queue idx */
	u32 stop_queue; /* count of queue stops */
	u32 wake_queue; /* count of queue wakes */
	u32 ntfy_id; /* notअगरication block index */
	dma_addr_t bus; /* dma address of the descr ring */
	dma_addr_t q_resources_bus; /* dma address of the queue resources */
	काष्ठा u64_stats_sync statss; /* sync stats क्रम 32bit archs */
पूर्ण ____cacheline_aligned;

/* Wraps the info क्रम one irq including the napi काष्ठा and the queues
 * associated with that irq.
 */
काष्ठा gve_notअगरy_block अणु
	__be32 irq_db_index; /* idx पूर्णांकo Bar2 - set by device, must be 1st */
	अक्षर name[IFNAMSIZ + 16]; /* name रेजिस्टरed with the kernel */
	काष्ठा napi_काष्ठा napi; /* kernel napi काष्ठा क्रम this block */
	काष्ठा gve_priv *priv;
	काष्ठा gve_tx_ring *tx; /* tx rings on this block */
	काष्ठा gve_rx_ring *rx; /* rx rings on this block */
पूर्ण ____cacheline_aligned;

/* Tracks allowed and current queue settings */
काष्ठा gve_queue_config अणु
	u16 max_queues;
	u16 num_queues; /* current */
पूर्ण;

/* Tracks the available and used qpl IDs */
काष्ठा gve_qpl_config अणु
	u32 qpl_map_size; /* map memory size */
	अचिन्हित दीर्घ *qpl_id_map; /* biपंचांगap of used qpl ids */
पूर्ण;

काष्ठा gve_priv अणु
	काष्ठा net_device *dev;
	काष्ठा gve_tx_ring *tx; /* array of tx_cfg.num_queues */
	काष्ठा gve_rx_ring *rx; /* array of rx_cfg.num_queues */
	काष्ठा gve_queue_page_list *qpls; /* array of num qpls */
	काष्ठा gve_notअगरy_block *ntfy_blocks; /* array of num_ntfy_blks */
	dma_addr_t ntfy_block_bus;
	काष्ठा msix_entry *msix_vectors; /* array of num_ntfy_blks + 1 */
	अक्षर mgmt_msix_name[IFNAMSIZ + 16];
	u32 mgmt_msix_idx;
	__be32 *counter_array; /* array of num_event_counters */
	dma_addr_t counter_array_bus;

	u16 num_event_counters;
	u16 tx_desc_cnt; /* num desc per ring */
	u16 rx_desc_cnt; /* num desc per ring */
	u16 tx_pages_per_qpl; /* tx buffer length */
	u16 rx_data_slot_cnt; /* rx buffer length */
	u64 max_रेजिस्टरed_pages;
	u64 num_रेजिस्टरed_pages; /* num pages रेजिस्टरed with NIC */
	u32 rx_copyअवरोध; /* copy packets smaller than this */
	u16 शेष_num_queues; /* शेष num queues to set up */
	u8 raw_addressing; /* 1 अगर this dev supports raw addressing, 0 otherwise */

	काष्ठा gve_queue_config tx_cfg;
	काष्ठा gve_queue_config rx_cfg;
	काष्ठा gve_qpl_config qpl_cfg; /* map used QPL ids */
	u32 num_ntfy_blks; /* spilt between TX and RX so must be even */

	काष्ठा gve_रेजिस्टरs __iomem *reg_bar0; /* see gve_रेजिस्टर.h */
	__be32 __iomem *db_bar2; /* "array" of करोorbells */
	u32 msg_enable;	/* level क्रम netअगर* netdev prपूर्णांक macros	*/
	काष्ठा pci_dev *pdev;

	/* metrics */
	u32 tx_समयo_cnt;

	/* Admin queue - see gve_adminq.h*/
	जोड़ gve_adminq_command *adminq;
	dma_addr_t adminq_bus_addr;
	u32 adminq_mask; /* masks prod_cnt to adminq size */
	u32 adminq_prod_cnt; /* मुक्त-running count of AQ cmds executed */
	u32 adminq_cmd_fail; /* मुक्त-running count of AQ cmds failed */
	u32 adminq_समयouts; /* मुक्त-running count of AQ cmds समयouts */
	/* मुक्त-running count of per AQ cmd executed */
	u32 adminq_describe_device_cnt;
	u32 adminq_cfg_device_resources_cnt;
	u32 adminq_रेजिस्टर_page_list_cnt;
	u32 adminq_unरेजिस्टर_page_list_cnt;
	u32 adminq_create_tx_queue_cnt;
	u32 adminq_create_rx_queue_cnt;
	u32 adminq_destroy_tx_queue_cnt;
	u32 adminq_destroy_rx_queue_cnt;
	u32 adminq_dcfg_device_resources_cnt;
	u32 adminq_set_driver_parameter_cnt;
	u32 adminq_report_stats_cnt;
	u32 adminq_report_link_speed_cnt;

	/* Global stats */
	u32 पूर्णांकerface_up_cnt; /* count of बार पूर्णांकerface turned up since last reset */
	u32 पूर्णांकerface_करोwn_cnt; /* count of बार पूर्णांकerface turned करोwn since last reset */
	u32 reset_cnt; /* count of reset */
	u32 page_alloc_fail; /* count of page alloc fails */
	u32 dma_mapping_error; /* count of dma mapping errors */
	u32 stats_report_trigger_cnt; /* count of device-requested stats-reports since last reset */
	काष्ठा workqueue_काष्ठा *gve_wq;
	काष्ठा work_काष्ठा service_task;
	काष्ठा work_काष्ठा stats_report_task;
	अचिन्हित दीर्घ service_task_flags;
	अचिन्हित दीर्घ state_flags;

	काष्ठा gve_stats_report *stats_report;
	u64 stats_report_len;
	dma_addr_t stats_report_bus; /* dma address क्रम the stats report */
	अचिन्हित दीर्घ ethtool_flags;

	अचिन्हित दीर्घ stats_report_समयr_period;
	काष्ठा समयr_list stats_report_समयr;

	/* Gvnic device link speed from hypervisor. */
	u64 link_speed;
पूर्ण;

क्रमागत gve_service_task_flags_bit अणु
	GVE_PRIV_FLAGS_DO_RESET			= 1,
	GVE_PRIV_FLAGS_RESET_IN_PROGRESS	= 2,
	GVE_PRIV_FLAGS_PROBE_IN_PROGRESS	= 3,
	GVE_PRIV_FLAGS_DO_REPORT_STATS = 4,
पूर्ण;

क्रमागत gve_state_flags_bit अणु
	GVE_PRIV_FLAGS_ADMIN_QUEUE_OK		= 1,
	GVE_PRIV_FLAGS_DEVICE_RESOURCES_OK	= 2,
	GVE_PRIV_FLAGS_DEVICE_RINGS_OK		= 3,
	GVE_PRIV_FLAGS_NAPI_ENABLED		= 4,
पूर्ण;

क्रमागत gve_ethtool_flags_bit अणु
	GVE_PRIV_FLAGS_REPORT_STATS		= 0,
पूर्ण;

अटल अंतरभूत bool gve_get_करो_reset(काष्ठा gve_priv *priv)
अणु
	वापस test_bit(GVE_PRIV_FLAGS_DO_RESET, &priv->service_task_flags);
पूर्ण

अटल अंतरभूत व्योम gve_set_करो_reset(काष्ठा gve_priv *priv)
अणु
	set_bit(GVE_PRIV_FLAGS_DO_RESET, &priv->service_task_flags);
पूर्ण

अटल अंतरभूत व्योम gve_clear_करो_reset(काष्ठा gve_priv *priv)
अणु
	clear_bit(GVE_PRIV_FLAGS_DO_RESET, &priv->service_task_flags);
पूर्ण

अटल अंतरभूत bool gve_get_reset_in_progress(काष्ठा gve_priv *priv)
अणु
	वापस test_bit(GVE_PRIV_FLAGS_RESET_IN_PROGRESS,
			&priv->service_task_flags);
पूर्ण

अटल अंतरभूत व्योम gve_set_reset_in_progress(काष्ठा gve_priv *priv)
अणु
	set_bit(GVE_PRIV_FLAGS_RESET_IN_PROGRESS, &priv->service_task_flags);
पूर्ण

अटल अंतरभूत व्योम gve_clear_reset_in_progress(काष्ठा gve_priv *priv)
अणु
	clear_bit(GVE_PRIV_FLAGS_RESET_IN_PROGRESS, &priv->service_task_flags);
पूर्ण

अटल अंतरभूत bool gve_get_probe_in_progress(काष्ठा gve_priv *priv)
अणु
	वापस test_bit(GVE_PRIV_FLAGS_PROBE_IN_PROGRESS,
			&priv->service_task_flags);
पूर्ण

अटल अंतरभूत व्योम gve_set_probe_in_progress(काष्ठा gve_priv *priv)
अणु
	set_bit(GVE_PRIV_FLAGS_PROBE_IN_PROGRESS, &priv->service_task_flags);
पूर्ण

अटल अंतरभूत व्योम gve_clear_probe_in_progress(काष्ठा gve_priv *priv)
अणु
	clear_bit(GVE_PRIV_FLAGS_PROBE_IN_PROGRESS, &priv->service_task_flags);
पूर्ण

अटल अंतरभूत bool gve_get_करो_report_stats(काष्ठा gve_priv *priv)
अणु
	वापस test_bit(GVE_PRIV_FLAGS_DO_REPORT_STATS,
			&priv->service_task_flags);
पूर्ण

अटल अंतरभूत व्योम gve_set_करो_report_stats(काष्ठा gve_priv *priv)
अणु
	set_bit(GVE_PRIV_FLAGS_DO_REPORT_STATS, &priv->service_task_flags);
पूर्ण

अटल अंतरभूत व्योम gve_clear_करो_report_stats(काष्ठा gve_priv *priv)
अणु
	clear_bit(GVE_PRIV_FLAGS_DO_REPORT_STATS, &priv->service_task_flags);
पूर्ण

अटल अंतरभूत bool gve_get_admin_queue_ok(काष्ठा gve_priv *priv)
अणु
	वापस test_bit(GVE_PRIV_FLAGS_ADMIN_QUEUE_OK, &priv->state_flags);
पूर्ण

अटल अंतरभूत व्योम gve_set_admin_queue_ok(काष्ठा gve_priv *priv)
अणु
	set_bit(GVE_PRIV_FLAGS_ADMIN_QUEUE_OK, &priv->state_flags);
पूर्ण

अटल अंतरभूत व्योम gve_clear_admin_queue_ok(काष्ठा gve_priv *priv)
अणु
	clear_bit(GVE_PRIV_FLAGS_ADMIN_QUEUE_OK, &priv->state_flags);
पूर्ण

अटल अंतरभूत bool gve_get_device_resources_ok(काष्ठा gve_priv *priv)
अणु
	वापस test_bit(GVE_PRIV_FLAGS_DEVICE_RESOURCES_OK, &priv->state_flags);
पूर्ण

अटल अंतरभूत व्योम gve_set_device_resources_ok(काष्ठा gve_priv *priv)
अणु
	set_bit(GVE_PRIV_FLAGS_DEVICE_RESOURCES_OK, &priv->state_flags);
पूर्ण

अटल अंतरभूत व्योम gve_clear_device_resources_ok(काष्ठा gve_priv *priv)
अणु
	clear_bit(GVE_PRIV_FLAGS_DEVICE_RESOURCES_OK, &priv->state_flags);
पूर्ण

अटल अंतरभूत bool gve_get_device_rings_ok(काष्ठा gve_priv *priv)
अणु
	वापस test_bit(GVE_PRIV_FLAGS_DEVICE_RINGS_OK, &priv->state_flags);
पूर्ण

अटल अंतरभूत व्योम gve_set_device_rings_ok(काष्ठा gve_priv *priv)
अणु
	set_bit(GVE_PRIV_FLAGS_DEVICE_RINGS_OK, &priv->state_flags);
पूर्ण

अटल अंतरभूत व्योम gve_clear_device_rings_ok(काष्ठा gve_priv *priv)
अणु
	clear_bit(GVE_PRIV_FLAGS_DEVICE_RINGS_OK, &priv->state_flags);
पूर्ण

अटल अंतरभूत bool gve_get_napi_enabled(काष्ठा gve_priv *priv)
अणु
	वापस test_bit(GVE_PRIV_FLAGS_NAPI_ENABLED, &priv->state_flags);
पूर्ण

अटल अंतरभूत व्योम gve_set_napi_enabled(काष्ठा gve_priv *priv)
अणु
	set_bit(GVE_PRIV_FLAGS_NAPI_ENABLED, &priv->state_flags);
पूर्ण

अटल अंतरभूत व्योम gve_clear_napi_enabled(काष्ठा gve_priv *priv)
अणु
	clear_bit(GVE_PRIV_FLAGS_NAPI_ENABLED, &priv->state_flags);
पूर्ण

अटल अंतरभूत bool gve_get_report_stats(काष्ठा gve_priv *priv)
अणु
	वापस test_bit(GVE_PRIV_FLAGS_REPORT_STATS, &priv->ethtool_flags);
पूर्ण

अटल अंतरभूत व्योम gve_clear_report_stats(काष्ठा gve_priv *priv)
अणु
	clear_bit(GVE_PRIV_FLAGS_REPORT_STATS, &priv->ethtool_flags);
पूर्ण

/* Returns the address of the ntfy_blocks irq करोorbell
 */
अटल अंतरभूत __be32 __iomem *gve_irq_करोorbell(काष्ठा gve_priv *priv,
					       काष्ठा gve_notअगरy_block *block)
अणु
	वापस &priv->db_bar2[be32_to_cpu(block->irq_db_index)];
पूर्ण

/* Returns the index पूर्णांकo ntfy_blocks of the given tx ring's block
 */
अटल अंतरभूत u32 gve_tx_idx_to_ntfy(काष्ठा gve_priv *priv, u32 queue_idx)
अणु
	वापस queue_idx;
पूर्ण

/* Returns the index पूर्णांकo ntfy_blocks of the given rx ring's block
 */
अटल अंतरभूत u32 gve_rx_idx_to_ntfy(काष्ठा gve_priv *priv, u32 queue_idx)
अणु
	वापस (priv->num_ntfy_blks / 2) + queue_idx;
पूर्ण

/* Returns the number of tx queue page lists
 */
अटल अंतरभूत u32 gve_num_tx_qpls(काष्ठा gve_priv *priv)
अणु
	वापस priv->raw_addressing ? 0 : priv->tx_cfg.num_queues;
पूर्ण

/* Returns the number of rx queue page lists
 */
अटल अंतरभूत u32 gve_num_rx_qpls(काष्ठा gve_priv *priv)
अणु
	वापस priv->raw_addressing ? 0 : priv->rx_cfg.num_queues;
पूर्ण

/* Returns a poपूर्णांकer to the next available tx qpl in the list of qpls
 */
अटल अंतरभूत
काष्ठा gve_queue_page_list *gve_assign_tx_qpl(काष्ठा gve_priv *priv)
अणु
	पूर्णांक id = find_first_zero_bit(priv->qpl_cfg.qpl_id_map,
				     priv->qpl_cfg.qpl_map_size);

	/* we are out of tx qpls */
	अगर (id >= gve_num_tx_qpls(priv))
		वापस शून्य;

	set_bit(id, priv->qpl_cfg.qpl_id_map);
	वापस &priv->qpls[id];
पूर्ण

/* Returns a poपूर्णांकer to the next available rx qpl in the list of qpls
 */
अटल अंतरभूत
काष्ठा gve_queue_page_list *gve_assign_rx_qpl(काष्ठा gve_priv *priv)
अणु
	पूर्णांक id = find_next_zero_bit(priv->qpl_cfg.qpl_id_map,
				    priv->qpl_cfg.qpl_map_size,
				    gve_num_tx_qpls(priv));

	/* we are out of rx qpls */
	अगर (id == priv->qpl_cfg.qpl_map_size)
		वापस शून्य;

	set_bit(id, priv->qpl_cfg.qpl_id_map);
	वापस &priv->qpls[id];
पूर्ण

/* Unassigns the qpl with the given id
 */
अटल अंतरभूत व्योम gve_unassign_qpl(काष्ठा gve_priv *priv, पूर्णांक id)
अणु
	clear_bit(id, priv->qpl_cfg.qpl_id_map);
पूर्ण

/* Returns the correct dma direction क्रम tx and rx qpls
 */
अटल अंतरभूत क्रमागत dma_data_direction gve_qpl_dma_dir(काष्ठा gve_priv *priv,
						      पूर्णांक id)
अणु
	अगर (id < gve_num_tx_qpls(priv))
		वापस DMA_TO_DEVICE;
	अन्यथा
		वापस DMA_FROM_DEVICE;
पूर्ण

/* buffers */
पूर्णांक gve_alloc_page(काष्ठा gve_priv *priv, काष्ठा device *dev,
		   काष्ठा page **page, dma_addr_t *dma,
		   क्रमागत dma_data_direction);
व्योम gve_मुक्त_page(काष्ठा device *dev, काष्ठा page *page, dma_addr_t dma,
		   क्रमागत dma_data_direction);
/* tx handling */
netdev_tx_t gve_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
bool gve_tx_poll(काष्ठा gve_notअगरy_block *block, पूर्णांक budget);
पूर्णांक gve_tx_alloc_rings(काष्ठा gve_priv *priv);
व्योम gve_tx_मुक्त_rings(काष्ठा gve_priv *priv);
__be32 gve_tx_load_event_counter(काष्ठा gve_priv *priv,
				 काष्ठा gve_tx_ring *tx);
/* rx handling */
व्योम gve_rx_ग_लिखो_करोorbell(काष्ठा gve_priv *priv, काष्ठा gve_rx_ring *rx);
bool gve_rx_poll(काष्ठा gve_notअगरy_block *block, पूर्णांक budget);
पूर्णांक gve_rx_alloc_rings(काष्ठा gve_priv *priv);
व्योम gve_rx_मुक्त_rings(काष्ठा gve_priv *priv);
bool gve_clean_rx_करोne(काष्ठा gve_rx_ring *rx, पूर्णांक budget,
		       netdev_features_t feat);
/* Reset */
व्योम gve_schedule_reset(काष्ठा gve_priv *priv);
पूर्णांक gve_reset(काष्ठा gve_priv *priv, bool attempt_tearकरोwn);
पूर्णांक gve_adjust_queues(काष्ठा gve_priv *priv,
		      काष्ठा gve_queue_config new_rx_config,
		      काष्ठा gve_queue_config new_tx_config);
/* report stats handling */
व्योम gve_handle_report_stats(काष्ठा gve_priv *priv);
/* exported by ethtool.c */
बाह्य स्थिर काष्ठा ethtool_ops gve_ethtool_ops;
/* needed by ethtool */
बाह्य स्थिर अक्षर gve_version_str[];
#पूर्ण_अगर /* _GVE_H_ */
