<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright 2015-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#अगर_अघोषित ENA_COM
#घोषणा ENA_COM

#समावेश <linux/compiler.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पन.स>
#समावेश <linux/prefetch.h>
#समावेश <linux/sched.h>
#समावेश <linux/sizes.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <linux/netdevice.h>

#समावेश "ena_common_defs.h"
#समावेश "ena_admin_defs.h"
#समावेश "ena_eth_io_defs.h"
#समावेश "ena_regs_defs.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा ENA_MAX_NUM_IO_QUEUES 128U
/* We need to queues क्रम each IO (on क्रम Tx and one क्रम Rx) */
#घोषणा ENA_TOTAL_NUM_QUEUES (2 * (ENA_MAX_NUM_IO_QUEUES))

#घोषणा ENA_MAX_HANDLERS 256

#घोषणा ENA_MAX_PHYS_ADDR_SIZE_BITS 48

/* Unit in usec */
#घोषणा ENA_REG_READ_TIMEOUT 200000

#घोषणा ADMIN_SQ_SIZE(depth)	((depth) * माप(काष्ठा ena_admin_aq_entry))
#घोषणा ADMIN_CQ_SIZE(depth)	((depth) * माप(काष्ठा ena_admin_acq_entry))
#घोषणा ADMIN_AENQ_SIZE(depth)	((depth) * माप(काष्ठा ena_admin_aenq_entry))

/*****************************************************************************/
/*****************************************************************************/
/* ENA adaptive पूर्णांकerrupt moderation settings */

#घोषणा ENA_INTR_INITIAL_TX_INTERVAL_USECS 64
#घोषणा ENA_INTR_INITIAL_RX_INTERVAL_USECS 0
#घोषणा ENA_DEFAULT_INTR_DELAY_RESOLUTION 1

#घोषणा ENA_HASH_KEY_SIZE 40

#घोषणा ENA_HW_HINTS_NO_TIMEOUT	0xFFFF

#घोषणा ENA_FEATURE_MAX_QUEUE_EXT_VER 1

काष्ठा ena_llq_configurations अणु
	क्रमागत ena_admin_llq_header_location llq_header_location;
	क्रमागत ena_admin_llq_ring_entry_size llq_ring_entry_size;
	क्रमागत ena_admin_llq_stride_ctrl  llq_stride_ctrl;
	क्रमागत ena_admin_llq_num_descs_beक्रमe_header llq_num_decs_beक्रमe_header;
	u16 llq_ring_entry_size_value;
पूर्ण;

क्रमागत queue_direction अणु
	ENA_COM_IO_QUEUE_सूचीECTION_TX,
	ENA_COM_IO_QUEUE_सूचीECTION_RX
पूर्ण;

काष्ठा ena_com_buf अणु
	dma_addr_t paddr; /**< Buffer physical address */
	u16 len; /**< Buffer length in bytes */
पूर्ण;

काष्ठा ena_com_rx_buf_info अणु
	u16 len;
	u16 req_id;
पूर्ण;

काष्ठा ena_com_io_desc_addr अणु
	u8 __iomem *pbuf_dev_addr; /* LLQ address */
	u8 *virt_addr;
	dma_addr_t phys_addr;
पूर्ण;

काष्ठा ena_com_tx_meta अणु
	u16 mss;
	u16 l3_hdr_len;
	u16 l3_hdr_offset;
	u16 l4_hdr_len; /* In words */
पूर्ण;

काष्ठा ena_com_llq_info अणु
	u16 header_location_ctrl;
	u16 desc_stride_ctrl;
	u16 desc_list_entry_size_ctrl;
	u16 desc_list_entry_size;
	u16 descs_num_beक्रमe_header;
	u16 descs_per_entry;
	u16 max_entries_in_tx_burst;
	bool disable_meta_caching;
पूर्ण;

काष्ठा ena_com_io_cq अणु
	काष्ठा ena_com_io_desc_addr cdesc_addr;

	/* Interrupt unmask रेजिस्टर */
	u32 __iomem *unmask_reg;

	/* The completion queue head करोorbell रेजिस्टर */
	u32 __iomem *cq_head_db_reg;

	/* numa configuration रेजिस्टर (क्रम TPH) */
	u32 __iomem *numa_node_cfg_reg;

	/* The value to ग_लिखो to the above रेजिस्टर to unmask
	 * the पूर्णांकerrupt of this queue
	 */
	u32 msix_vector;

	क्रमागत queue_direction direction;

	/* holds the number of cdesc of the current packet */
	u16 cur_rx_pkt_cdesc_count;
	/* save the first cdesc idx of the current packet */
	u16 cur_rx_pkt_cdesc_start_idx;

	u16 q_depth;
	/* Caller qid */
	u16 qid;

	/* Device queue index */
	u16 idx;
	u16 head;
	u16 last_head_update;
	u8 phase;
	u8 cdesc_entry_size_in_bytes;

पूर्ण ____cacheline_aligned;

काष्ठा ena_com_io_bounce_buffer_control अणु
	u8 *base_buffer;
	u16 next_to_use;
	u16 buffer_size;
	u16 buffers_num;  /* Must be a घातer of 2 */
पूर्ण;

/* This काष्ठा is to keep tracking the current location of the next llq entry */
काष्ठा ena_com_llq_pkt_ctrl अणु
	u8 *curr_bounce_buf;
	u16 idx;
	u16 descs_left_in_line;
पूर्ण;

काष्ठा ena_com_io_sq अणु
	काष्ठा ena_com_io_desc_addr desc_addr;

	u32 __iomem *db_addr;
	u8 __iomem *header_addr;

	क्रमागत queue_direction direction;
	क्रमागत ena_admin_placement_policy_type mem_queue_type;

	bool disable_meta_caching;

	u32 msix_vector;
	काष्ठा ena_com_tx_meta cached_tx_meta;
	काष्ठा ena_com_llq_info llq_info;
	काष्ठा ena_com_llq_pkt_ctrl llq_buf_ctrl;
	काष्ठा ena_com_io_bounce_buffer_control bounce_buf_ctrl;

	u16 q_depth;
	u16 qid;

	u16 idx;
	u16 tail;
	u16 next_to_comp;
	u16 llq_last_copy_tail;
	u32 tx_max_header_size;
	u8 phase;
	u8 desc_entry_size;
	u8 dma_addr_bits;
	u16 entries_in_tx_burst_left;
पूर्ण ____cacheline_aligned;

काष्ठा ena_com_admin_cq अणु
	काष्ठा ena_admin_acq_entry *entries;
	dma_addr_t dma_addr;

	u16 head;
	u8 phase;
पूर्ण;

काष्ठा ena_com_admin_sq अणु
	काष्ठा ena_admin_aq_entry *entries;
	dma_addr_t dma_addr;

	u32 __iomem *db_addr;

	u16 head;
	u16 tail;
	u8 phase;

पूर्ण;

काष्ठा ena_com_stats_admin अणु
	u64 पातed_cmd;
	u64 submitted_cmd;
	u64 completed_cmd;
	u64 out_of_space;
	u64 no_completion;
पूर्ण;

काष्ठा ena_com_admin_queue अणु
	व्योम *q_dmadev;
	काष्ठा ena_com_dev *ena_dev;
	spinlock_t q_lock; /* spinlock क्रम the admin queue */

	काष्ठा ena_comp_ctx *comp_ctx;
	u32 completion_समयout;
	u16 q_depth;
	काष्ठा ena_com_admin_cq cq;
	काष्ठा ena_com_admin_sq sq;

	/* Indicate अगर the admin queue should poll क्रम completion */
	bool polling;

	/* Define अगर fallback to polling mode should occur */
	bool स्वतः_polling;

	u16 curr_cmd_id;

	/* Indicate that the ena was initialized and can
	 * process new admin commands
	 */
	bool running_state;

	/* Count the number of outstanding admin commands */
	atomic_t outstanding_cmds;

	काष्ठा ena_com_stats_admin stats;
पूर्ण;

काष्ठा ena_aenq_handlers;

काष्ठा ena_com_aenq अणु
	u16 head;
	u8 phase;
	काष्ठा ena_admin_aenq_entry *entries;
	dma_addr_t dma_addr;
	u16 q_depth;
	काष्ठा ena_aenq_handlers *aenq_handlers;
पूर्ण;

काष्ठा ena_com_mmio_पढ़ो अणु
	काष्ठा ena_admin_ena_mmio_req_पढ़ो_less_resp *पढ़ो_resp;
	dma_addr_t पढ़ो_resp_dma_addr;
	u32 reg_पढ़ो_to; /* in us */
	u16 seq_num;
	bool पढ़ोless_supported;
	/* spin lock to ensure a single outstanding पढ़ो */
	spinlock_t lock;
पूर्ण;

काष्ठा ena_rss अणु
	/* Indirect table */
	u16 *host_rss_ind_tbl;
	काष्ठा ena_admin_rss_ind_table_entry *rss_ind_tbl;
	dma_addr_t rss_ind_tbl_dma_addr;
	u16 tbl_log_size;

	/* Hash key */
	क्रमागत ena_admin_hash_functions hash_func;
	काष्ठा ena_admin_feature_rss_flow_hash_control *hash_key;
	dma_addr_t hash_key_dma_addr;
	u32 hash_init_val;

	/* Flow Control */
	काष्ठा ena_admin_feature_rss_hash_control *hash_ctrl;
	dma_addr_t hash_ctrl_dma_addr;

पूर्ण;

काष्ठा ena_host_attribute अणु
	/* Debug area */
	u8 *debug_area_virt_addr;
	dma_addr_t debug_area_dma_addr;
	u32 debug_area_size;

	/* Host inक्रमmation */
	काष्ठा ena_admin_host_info *host_info;
	dma_addr_t host_info_dma_addr;
पूर्ण;

/* Each ena_dev is a PCI function. */
काष्ठा ena_com_dev अणु
	काष्ठा ena_com_admin_queue admin_queue;
	काष्ठा ena_com_aenq aenq;
	काष्ठा ena_com_io_cq io_cq_queues[ENA_TOTAL_NUM_QUEUES];
	काष्ठा ena_com_io_sq io_sq_queues[ENA_TOTAL_NUM_QUEUES];
	u8 __iomem *reg_bar;
	व्योम __iomem *mem_bar;
	व्योम *dmadev;
	काष्ठा net_device *net_device;

	क्रमागत ena_admin_placement_policy_type tx_mem_queue_type;
	u32 tx_max_header_size;
	u16 stats_func; /* Selected function क्रम extended statistic dump */
	u16 stats_queue; /* Selected queue क्रम extended statistic dump */

	काष्ठा ena_com_mmio_पढ़ो mmio_पढ़ो;

	काष्ठा ena_rss rss;
	u32 supported_features;
	u32 dma_addr_bits;

	काष्ठा ena_host_attribute host_attr;
	bool adaptive_coalescing;
	u16 पूर्णांकr_delay_resolution;

	/* पूर्णांकerrupt moderation पूर्णांकervals are in usec भागided by
	 * पूर्णांकr_delay_resolution, which is supplied by the device.
	 */
	u32 पूर्णांकr_moder_tx_पूर्णांकerval;
	u32 पूर्णांकr_moder_rx_पूर्णांकerval;

	काष्ठा ena_पूर्णांकr_moder_entry *पूर्णांकr_moder_tbl;

	काष्ठा ena_com_llq_info llq_info;

	u32 ena_min_poll_delay_us;
पूर्ण;

काष्ठा ena_com_dev_get_features_ctx अणु
	काष्ठा ena_admin_queue_feature_desc max_queues;
	काष्ठा ena_admin_queue_ext_feature_desc max_queue_ext;
	काष्ठा ena_admin_device_attr_feature_desc dev_attr;
	काष्ठा ena_admin_feature_aenq_desc aenq;
	काष्ठा ena_admin_feature_offload_desc offload;
	काष्ठा ena_admin_ena_hw_hपूर्णांकs hw_hपूर्णांकs;
	काष्ठा ena_admin_feature_llq_desc llq;
पूर्ण;

काष्ठा ena_com_create_io_ctx अणु
	क्रमागत ena_admin_placement_policy_type mem_queue_type;
	क्रमागत queue_direction direction;
	पूर्णांक numa_node;
	u32 msix_vector;
	u16 queue_size;
	u16 qid;
पूर्ण;

प्रकार व्योम (*ena_aenq_handler)(व्योम *data,
	काष्ठा ena_admin_aenq_entry *aenq_e);

/* Holds aenq handlers. Indexed by AENQ event group */
काष्ठा ena_aenq_handlers अणु
	ena_aenq_handler handlers[ENA_MAX_HANDLERS];
	ena_aenq_handler unimplemented_handler;
पूर्ण;

/*****************************************************************************/
/*****************************************************************************/

/* ena_com_mmio_reg_पढ़ो_request_init - Init the mmio reg पढ़ो mechanism
 * @ena_dev: ENA communication layer काष्ठा
 *
 * Initialize the रेजिस्टर पढ़ो mechanism.
 *
 * @note: This method must be the first stage in the initialization sequence.
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक ena_com_mmio_reg_पढ़ो_request_init(काष्ठा ena_com_dev *ena_dev);

/* ena_com_set_mmio_पढ़ो_mode - Enable/disable the indirect mmio reg पढ़ो mechanism
 * @ena_dev: ENA communication layer काष्ठा
 * @पढ़ोless_supported: पढ़ोless mode (enable/disable)
 */
व्योम ena_com_set_mmio_पढ़ो_mode(काष्ठा ena_com_dev *ena_dev,
				bool पढ़ोless_supported);

/* ena_com_mmio_reg_पढ़ो_request_ग_लिखो_dev_addr - Write the mmio reg पढ़ो वापस
 * value physical address.
 * @ena_dev: ENA communication layer काष्ठा
 */
व्योम ena_com_mmio_reg_पढ़ो_request_ग_लिखो_dev_addr(काष्ठा ena_com_dev *ena_dev);

/* ena_com_mmio_reg_पढ़ो_request_destroy - Destroy the mmio reg पढ़ो mechanism
 * @ena_dev: ENA communication layer काष्ठा
 */
व्योम ena_com_mmio_reg_पढ़ो_request_destroy(काष्ठा ena_com_dev *ena_dev);

/* ena_com_admin_init - Init the admin and the async queues
 * @ena_dev: ENA communication layer काष्ठा
 * @aenq_handlers: Those handlers to be called upon event.
 *
 * Initialize the admin submission and completion queues.
 * Initialize the asynchronous events notअगरication queues.
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक ena_com_admin_init(काष्ठा ena_com_dev *ena_dev,
		       काष्ठा ena_aenq_handlers *aenq_handlers);

/* ena_com_admin_destroy - Destroy the admin and the async events queues.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * @note: Beक्रमe calling this method, the caller must validate that the device
 * won't send any additional admin completions/aenq.
 * To achieve that, a FLR is recommended.
 */
व्योम ena_com_admin_destroy(काष्ठा ena_com_dev *ena_dev);

/* ena_com_dev_reset - Perक्रमm device FLR to the device.
 * @ena_dev: ENA communication layer काष्ठा
 * @reset_reason: Specअगरy what is the trigger क्रम the reset in हाल of an error.
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक ena_com_dev_reset(काष्ठा ena_com_dev *ena_dev,
		      क्रमागत ena_regs_reset_reason_types reset_reason);

/* ena_com_create_io_queue - Create io queue.
 * @ena_dev: ENA communication layer काष्ठा
 * @ctx - create context काष्ठाure
 *
 * Create the submission and the completion queues.
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक ena_com_create_io_queue(काष्ठा ena_com_dev *ena_dev,
			    काष्ठा ena_com_create_io_ctx *ctx);

/* ena_com_destroy_io_queue - Destroy IO queue with the queue id - qid.
 * @ena_dev: ENA communication layer काष्ठा
 * @qid - the caller भव queue id.
 */
व्योम ena_com_destroy_io_queue(काष्ठा ena_com_dev *ena_dev, u16 qid);

/* ena_com_get_io_handlers - Return the io queue handlers
 * @ena_dev: ENA communication layer काष्ठा
 * @qid - the caller भव queue id.
 * @io_sq - IO submission queue handler
 * @io_cq - IO completion queue handler.
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक ena_com_get_io_handlers(काष्ठा ena_com_dev *ena_dev, u16 qid,
			    काष्ठा ena_com_io_sq **io_sq,
			    काष्ठा ena_com_io_cq **io_cq);

/* ena_com_admin_aenq_enable - ENAble asynchronous event notअगरications
 * @ena_dev: ENA communication layer काष्ठा
 *
 * After this method, aenq event can be received via AENQ.
 */
व्योम ena_com_admin_aenq_enable(काष्ठा ena_com_dev *ena_dev);

/* ena_com_set_admin_running_state - Set the state of the admin queue
 * @ena_dev: ENA communication layer काष्ठा
 *
 * Change the state of the admin queue (enable/disable)
 */
व्योम ena_com_set_admin_running_state(काष्ठा ena_com_dev *ena_dev, bool state);

/* ena_com_get_admin_running_state - Get the admin queue state
 * @ena_dev: ENA communication layer काष्ठा
 *
 * Retrieve the state of the admin queue (enable/disable)
 *
 * @वापस - current polling mode (enable/disable)
 */
bool ena_com_get_admin_running_state(काष्ठा ena_com_dev *ena_dev);

/* ena_com_set_admin_polling_mode - Set the admin completion queue polling mode
 * @ena_dev: ENA communication layer काष्ठा
 * @polling: ENAble/Disable polling mode
 *
 * Set the admin completion mode.
 */
व्योम ena_com_set_admin_polling_mode(काष्ठा ena_com_dev *ena_dev, bool polling);

/* ena_com_set_admin_स्वतः_polling_mode - Enable स्वतःचयन to polling mode
 * @ena_dev: ENA communication layer काष्ठा
 * @polling: Enable/Disable polling mode
 *
 * Set the स्वतःpolling mode.
 * If स्वतःpolling is on:
 * In हाल of missing पूर्णांकerrupt when data is available चयन to polling.
 */
व्योम ena_com_set_admin_स्वतः_polling_mode(काष्ठा ena_com_dev *ena_dev,
					 bool polling);

/* ena_com_admin_q_comp_पूर्णांकr_handler - admin queue पूर्णांकerrupt handler
 * @ena_dev: ENA communication layer काष्ठा
 *
 * This method goes over the admin completion queue and wakes up all the pending
 * thपढ़ोs that रुको on the commands रुको event.
 *
 * @note: Should be called after MSI-X पूर्णांकerrupt.
 */
व्योम ena_com_admin_q_comp_पूर्णांकr_handler(काष्ठा ena_com_dev *ena_dev);

/* ena_com_aenq_पूर्णांकr_handler - AENQ पूर्णांकerrupt handler
 * @ena_dev: ENA communication layer काष्ठा
 *
 * This method goes over the async event notअगरication queue and calls the proper
 * aenq handler.
 */
व्योम ena_com_aenq_पूर्णांकr_handler(काष्ठा ena_com_dev *ena_dev, व्योम *data);

/* ena_com_पात_admin_commands - Abort all the outstanding admin commands.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * This method पातs all the outstanding admin commands.
 * The caller should then call ena_com_रुको_क्रम_पात_completion to make sure
 * all the commands were completed.
 */
व्योम ena_com_पात_admin_commands(काष्ठा ena_com_dev *ena_dev);

/* ena_com_रुको_क्रम_पात_completion - Wait क्रम admin commands पात.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * This method रुकोs until all the outstanding admin commands are completed.
 */
व्योम ena_com_रुको_क्रम_पात_completion(काष्ठा ena_com_dev *ena_dev);

/* ena_com_validate_version - Validate the device parameters
 * @ena_dev: ENA communication layer काष्ठा
 *
 * This method verअगरies the device parameters are the same as the saved
 * parameters in ena_dev.
 * This method is useful after device reset, to validate the device mac address
 * and the device offloads are the same as beक्रमe the reset.
 *
 * @वापस - 0 on success negative value otherwise.
 */
पूर्णांक ena_com_validate_version(काष्ठा ena_com_dev *ena_dev);

/* ena_com_get_link_params - Retrieve physical link parameters.
 * @ena_dev: ENA communication layer काष्ठा
 * @resp: Link parameters
 *
 * Retrieve the physical link parameters,
 * like speed, स्वतः-negotiation and full duplex support.
 *
 * @वापस - 0 on Success negative value otherwise.
 */
पूर्णांक ena_com_get_link_params(काष्ठा ena_com_dev *ena_dev,
			    काष्ठा ena_admin_get_feat_resp *resp);

/* ena_com_get_dma_width - Retrieve physical dma address width the device
 * supports.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * Retrieve the maximum physical address bits the device can handle.
 *
 * @वापस: > 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_get_dma_width(काष्ठा ena_com_dev *ena_dev);

/* ena_com_set_aenq_config - Set aenq groups configurations
 * @ena_dev: ENA communication layer काष्ठा
 * @groups flag: bit fields flags of क्रमागत ena_admin_aenq_group.
 *
 * Configure which aenq event group the driver would like to receive.
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_set_aenq_config(काष्ठा ena_com_dev *ena_dev, u32 groups_flag);

/* ena_com_get_dev_attr_feat - Get device features
 * @ena_dev: ENA communication layer काष्ठा
 * @get_feat_ctx: वापसed context that contain the get features.
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_get_dev_attr_feat(काष्ठा ena_com_dev *ena_dev,
			      काष्ठा ena_com_dev_get_features_ctx *get_feat_ctx);

/* ena_com_get_dev_basic_stats - Get device basic statistics
 * @ena_dev: ENA communication layer काष्ठा
 * @stats: stats वापस value
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_get_dev_basic_stats(काष्ठा ena_com_dev *ena_dev,
				काष्ठा ena_admin_basic_stats *stats);

/* ena_com_get_eni_stats - Get extended network पूर्णांकerface statistics
 * @ena_dev: ENA communication layer काष्ठा
 * @stats: stats वापस value
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_get_eni_stats(काष्ठा ena_com_dev *ena_dev,
			  काष्ठा ena_admin_eni_stats *stats);

/* ena_com_set_dev_mtu - Configure the device mtu.
 * @ena_dev: ENA communication layer काष्ठा
 * @mtu: mtu value
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_set_dev_mtu(काष्ठा ena_com_dev *ena_dev, u32 mtu);

/* ena_com_get_offload_settings - Retrieve the device offloads capabilities
 * @ena_dev: ENA communication layer काष्ठा
 * @offlad: offload वापस value
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_get_offload_settings(काष्ठा ena_com_dev *ena_dev,
				 काष्ठा ena_admin_feature_offload_desc *offload);

/* ena_com_rss_init - Init RSS
 * @ena_dev: ENA communication layer काष्ठा
 * @log_size: indirection log size
 *
 * Allocate RSS/RFS resources.
 * The caller then can configure rss using ena_com_set_hash_function,
 * ena_com_set_hash_ctrl and ena_com_indirect_table_set.
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_rss_init(काष्ठा ena_com_dev *ena_dev, u16 log_size);

/* ena_com_rss_destroy - Destroy rss
 * @ena_dev: ENA communication layer काष्ठा
 *
 * Free all the RSS/RFS resources.
 */
व्योम ena_com_rss_destroy(काष्ठा ena_com_dev *ena_dev);

/* ena_com_get_current_hash_function - Get RSS hash function
 * @ena_dev: ENA communication layer काष्ठा
 *
 * Return the current hash function.
 * @वापस: 0 or one of the ena_admin_hash_functions values.
 */
पूर्णांक ena_com_get_current_hash_function(काष्ठा ena_com_dev *ena_dev);

/* ena_com_fill_hash_function - Fill RSS hash function
 * @ena_dev: ENA communication layer काष्ठा
 * @func: The hash function (Toeplitz or crc)
 * @key: Hash key (क्रम toeplitz hash)
 * @key_len: key length (max length 10 DW)
 * @init_val: initial value क्रम the hash function
 *
 * Fill the ena_dev resources with the desire hash function, hash key, key_len
 * and key initial value (अगर needed by the hash function).
 * To flush the key पूर्णांकo the device the caller should call
 * ena_com_set_hash_function.
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_fill_hash_function(काष्ठा ena_com_dev *ena_dev,
			       क्रमागत ena_admin_hash_functions func,
			       स्थिर u8 *key, u16 key_len, u32 init_val);

/* ena_com_set_hash_function - Flush the hash function and it dependencies to
 * the device.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * Flush the hash function and it dependencies (key, key length and
 * initial value) अगर needed.
 *
 * @note: Prior to this method the caller should call ena_com_fill_hash_function
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_set_hash_function(काष्ठा ena_com_dev *ena_dev);

/* ena_com_get_hash_function - Retrieve the hash function from the device.
 * @ena_dev: ENA communication layer काष्ठा
 * @func: hash function
 *
 * Retrieve the hash function from the device.
 *
 * @note: If the caller called ena_com_fill_hash_function but didn't flush
 * it to the device, the new configuration will be lost.
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_get_hash_function(काष्ठा ena_com_dev *ena_dev,
			      क्रमागत ena_admin_hash_functions *func);

/* ena_com_get_hash_key - Retrieve the hash key
 * @ena_dev: ENA communication layer काष्ठा
 * @key: hash key
 *
 * Retrieve the hash key.
 *
 * @note: If the caller called ena_com_fill_hash_key but didn't flush
 * it to the device, the new configuration will be lost.
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_get_hash_key(काष्ठा ena_com_dev *ena_dev, u8 *key);
/* ena_com_fill_hash_ctrl - Fill RSS hash control
 * @ena_dev: ENA communication layer काष्ठा.
 * @proto: The protocol to configure.
 * @hash_fields: bit mask of ena_admin_flow_hash_fields
 *
 * Fill the ena_dev resources with the desire hash control (the ethernet
 * fields that take part of the hash) क्रम a specअगरic protocol.
 * To flush the hash control to the device, the caller should call
 * ena_com_set_hash_ctrl.
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_fill_hash_ctrl(काष्ठा ena_com_dev *ena_dev,
			   क्रमागत ena_admin_flow_hash_proto proto,
			   u16 hash_fields);

/* ena_com_set_hash_ctrl - Flush the hash control resources to the device.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * Flush the hash control (the ethernet fields that take part of the hash)
 *
 * @note: Prior to this method the caller should call ena_com_fill_hash_ctrl.
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_set_hash_ctrl(काष्ठा ena_com_dev *ena_dev);

/* ena_com_get_hash_ctrl - Retrieve the hash control from the device.
 * @ena_dev: ENA communication layer काष्ठा
 * @proto: The protocol to retrieve.
 * @fields: bit mask of ena_admin_flow_hash_fields.
 *
 * Retrieve the hash control from the device.
 *
 * @note: If the caller called ena_com_fill_hash_ctrl but didn't flush
 * it to the device, the new configuration will be lost.
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_get_hash_ctrl(काष्ठा ena_com_dev *ena_dev,
			  क्रमागत ena_admin_flow_hash_proto proto,
			  u16 *fields);

/* ena_com_set_शेष_hash_ctrl - Set the hash control to a शेष
 * configuration.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * Fill the ena_dev resources with the शेष hash control configuration.
 * To flush the hash control to the device, the caller should call
 * ena_com_set_hash_ctrl.
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_set_शेष_hash_ctrl(काष्ठा ena_com_dev *ena_dev);

/* ena_com_indirect_table_fill_entry - Fill a single entry in the RSS
 * indirection table
 * @ena_dev: ENA communication layer काष्ठा.
 * @entry_idx - indirection table entry.
 * @entry_value - redirection value
 *
 * Fill a single entry of the RSS indirection table in the ena_dev resources.
 * To flush the indirection table to the device, the called should call
 * ena_com_indirect_table_set.
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_indirect_table_fill_entry(काष्ठा ena_com_dev *ena_dev,
				      u16 entry_idx, u16 entry_value);

/* ena_com_indirect_table_set - Flush the indirection table to the device.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * Flush the indirection hash control to the device.
 * Prior to this method the caller should call ena_com_indirect_table_fill_entry
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_indirect_table_set(काष्ठा ena_com_dev *ena_dev);

/* ena_com_indirect_table_get - Retrieve the indirection table from the device.
 * @ena_dev: ENA communication layer काष्ठा
 * @ind_tbl: indirection table
 *
 * Retrieve the RSS indirection table from the device.
 *
 * @note: If the caller called ena_com_indirect_table_fill_entry but didn't flush
 * it to the device, the new configuration will be lost.
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_indirect_table_get(काष्ठा ena_com_dev *ena_dev, u32 *ind_tbl);

/* ena_com_allocate_host_info - Allocate host info resources.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_allocate_host_info(काष्ठा ena_com_dev *ena_dev);

/* ena_com_allocate_debug_area - Allocate debug area.
 * @ena_dev: ENA communication layer काष्ठा
 * @debug_area_size - debug area size.
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_allocate_debug_area(काष्ठा ena_com_dev *ena_dev,
				u32 debug_area_size);

/* ena_com_delete_debug_area - Free the debug area resources.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * Free the allocated debug area.
 */
व्योम ena_com_delete_debug_area(काष्ठा ena_com_dev *ena_dev);

/* ena_com_delete_host_info - Free the host info resources.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * Free the allocated host info.
 */
व्योम ena_com_delete_host_info(काष्ठा ena_com_dev *ena_dev);

/* ena_com_set_host_attributes - Update the device with the host
 * attributes (debug area and host info) base address.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * @वापस: 0 on Success and negative value otherwise.
 */
पूर्णांक ena_com_set_host_attributes(काष्ठा ena_com_dev *ena_dev);

/* ena_com_create_io_cq - Create io completion queue.
 * @ena_dev: ENA communication layer काष्ठा
 * @io_cq - io completion queue handler

 * Create IO completion queue.
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक ena_com_create_io_cq(काष्ठा ena_com_dev *ena_dev,
			 काष्ठा ena_com_io_cq *io_cq);

/* ena_com_destroy_io_cq - Destroy io completion queue.
 * @ena_dev: ENA communication layer काष्ठा
 * @io_cq - io completion queue handler

 * Destroy IO completion queue.
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक ena_com_destroy_io_cq(काष्ठा ena_com_dev *ena_dev,
			  काष्ठा ena_com_io_cq *io_cq);

/* ena_com_execute_admin_command - Execute admin command
 * @admin_queue: admin queue.
 * @cmd: the admin command to execute.
 * @cmd_size: the command size.
 * @cmd_completion: command completion वापस value.
 * @cmd_comp_size: command completion size.

 * Submit an admin command and then रुको until the device वापसs a
 * completion.
 * The completion will be copied पूर्णांकo cmd_comp.
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक ena_com_execute_admin_command(काष्ठा ena_com_admin_queue *admin_queue,
				  काष्ठा ena_admin_aq_entry *cmd,
				  माप_प्रकार cmd_size,
				  काष्ठा ena_admin_acq_entry *cmd_comp,
				  माप_प्रकार cmd_comp_size);

/* ena_com_init_पूर्णांकerrupt_moderation - Init पूर्णांकerrupt moderation
 * @ena_dev: ENA communication layer काष्ठा
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक ena_com_init_पूर्णांकerrupt_moderation(काष्ठा ena_com_dev *ena_dev);

/* ena_com_पूर्णांकerrupt_moderation_supported - Return अगर पूर्णांकerrupt moderation
 * capability is supported by the device.
 *
 * @वापस - supported or not.
 */
bool ena_com_पूर्णांकerrupt_moderation_supported(काष्ठा ena_com_dev *ena_dev);

/* ena_com_update_nonadaptive_moderation_पूर्णांकerval_tx - Update the
 * non-adaptive पूर्णांकerval in Tx direction.
 * @ena_dev: ENA communication layer काष्ठा
 * @tx_coalesce_usecs: Interval in usec.
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक ena_com_update_nonadaptive_moderation_पूर्णांकerval_tx(काष्ठा ena_com_dev *ena_dev,
						      u32 tx_coalesce_usecs);

/* ena_com_update_nonadaptive_moderation_पूर्णांकerval_rx - Update the
 * non-adaptive पूर्णांकerval in Rx direction.
 * @ena_dev: ENA communication layer काष्ठा
 * @rx_coalesce_usecs: Interval in usec.
 *
 * @वापस - 0 on success, negative value on failure.
 */
पूर्णांक ena_com_update_nonadaptive_moderation_पूर्णांकerval_rx(काष्ठा ena_com_dev *ena_dev,
						      u32 rx_coalesce_usecs);

/* ena_com_get_nonadaptive_moderation_पूर्णांकerval_tx - Retrieve the
 * non-adaptive पूर्णांकerval in Tx direction.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * @वापस - पूर्णांकerval in usec
 */
अचिन्हित पूर्णांक ena_com_get_nonadaptive_moderation_पूर्णांकerval_tx(काष्ठा ena_com_dev *ena_dev);

/* ena_com_get_nonadaptive_moderation_पूर्णांकerval_rx - Retrieve the
 * non-adaptive पूर्णांकerval in Rx direction.
 * @ena_dev: ENA communication layer काष्ठा
 *
 * @वापस - पूर्णांकerval in usec
 */
अचिन्हित पूर्णांक ena_com_get_nonadaptive_moderation_पूर्णांकerval_rx(काष्ठा ena_com_dev *ena_dev);

/* ena_com_config_dev_mode - Configure the placement policy of the device.
 * @ena_dev: ENA communication layer काष्ठा
 * @llq_features: LLQ feature descriptor, retrieve via
 *		   ena_com_get_dev_attr_feat.
 * @ena_llq_config: The शेष driver LLQ parameters configurations
 */
पूर्णांक ena_com_config_dev_mode(काष्ठा ena_com_dev *ena_dev,
			    काष्ठा ena_admin_feature_llq_desc *llq_features,
			    काष्ठा ena_llq_configurations *llq_शेष_config);

/* ena_com_io_sq_to_ena_dev - Extract ena_com_dev using contained field io_sq.
 * @io_sq: IO submit queue काष्ठा
 *
 * @वापस - ena_com_dev काष्ठा extracted from io_sq
 */
अटल अंतरभूत काष्ठा ena_com_dev *ena_com_io_sq_to_ena_dev(काष्ठा ena_com_io_sq *io_sq)
अणु
	वापस container_of(io_sq, काष्ठा ena_com_dev, io_sq_queues[io_sq->qid]);
पूर्ण

/* ena_com_io_cq_to_ena_dev - Extract ena_com_dev using contained field io_cq.
 * @io_sq: IO submit queue काष्ठा
 *
 * @वापस - ena_com_dev काष्ठा extracted from io_sq
 */
अटल अंतरभूत काष्ठा ena_com_dev *ena_com_io_cq_to_ena_dev(काष्ठा ena_com_io_cq *io_cq)
अणु
	वापस container_of(io_cq, काष्ठा ena_com_dev, io_cq_queues[io_cq->qid]);
पूर्ण

अटल अंतरभूत bool ena_com_get_adaptive_moderation_enabled(काष्ठा ena_com_dev *ena_dev)
अणु
	वापस ena_dev->adaptive_coalescing;
पूर्ण

अटल अंतरभूत व्योम ena_com_enable_adaptive_moderation(काष्ठा ena_com_dev *ena_dev)
अणु
	ena_dev->adaptive_coalescing = true;
पूर्ण

अटल अंतरभूत व्योम ena_com_disable_adaptive_moderation(काष्ठा ena_com_dev *ena_dev)
अणु
	ena_dev->adaptive_coalescing = false;
पूर्ण

/* ena_com_update_पूर्णांकr_reg - Prepare पूर्णांकerrupt रेजिस्टर
 * @पूर्णांकr_reg: पूर्णांकerrupt रेजिस्टर to update.
 * @rx_delay_पूर्णांकerval: Rx पूर्णांकerval in usecs
 * @tx_delay_पूर्णांकerval: Tx पूर्णांकerval in usecs
 * @unmask: unmask enable/disable
 *
 * Prepare पूर्णांकerrupt update रेजिस्टर with the supplied parameters.
 */
अटल अंतरभूत व्योम ena_com_update_पूर्णांकr_reg(काष्ठा ena_eth_io_पूर्णांकr_reg *पूर्णांकr_reg,
					   u32 rx_delay_पूर्णांकerval,
					   u32 tx_delay_पूर्णांकerval,
					   bool unmask)
अणु
	पूर्णांकr_reg->पूर्णांकr_control = 0;
	पूर्णांकr_reg->पूर्णांकr_control |= rx_delay_पूर्णांकerval &
		ENA_ETH_IO_INTR_REG_RX_INTR_DELAY_MASK;

	पूर्णांकr_reg->पूर्णांकr_control |=
		(tx_delay_पूर्णांकerval << ENA_ETH_IO_INTR_REG_TX_INTR_DELAY_SHIFT)
		& ENA_ETH_IO_INTR_REG_TX_INTR_DELAY_MASK;

	अगर (unmask)
		पूर्णांकr_reg->पूर्णांकr_control |= ENA_ETH_IO_INTR_REG_INTR_UNMASK_MASK;
पूर्ण

अटल अंतरभूत u8 *ena_com_get_next_bounce_buffer(काष्ठा ena_com_io_bounce_buffer_control *bounce_buf_ctrl)
अणु
	u16 size, buffers_num;
	u8 *buf;

	size = bounce_buf_ctrl->buffer_size;
	buffers_num = bounce_buf_ctrl->buffers_num;

	buf = bounce_buf_ctrl->base_buffer +
		(bounce_buf_ctrl->next_to_use++ & (buffers_num - 1)) * size;

	prefetchw(bounce_buf_ctrl->base_buffer +
		(bounce_buf_ctrl->next_to_use & (buffers_num - 1)) * size);

	वापस buf;
पूर्ण

#पूर्ण_अगर /* !(ENA_COM) */
