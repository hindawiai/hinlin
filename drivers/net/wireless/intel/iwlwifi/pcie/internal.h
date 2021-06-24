<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2003-2015, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_trans_पूर्णांक_pcie_h__
#घोषणा __iwl_trans_पूर्णांक_pcie_h__

#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/रुको.h>
#समावेश <linux/pci.h>
#समावेश <linux/समयr.h>
#समावेश <linux/cpu.h>

#समावेश "iwl-fh.h"
#समावेश "iwl-csr.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-debug.h"
#समावेश "iwl-io.h"
#समावेश "iwl-op-mode.h"
#समावेश "iwl-drv.h"
#समावेश "queue/tx.h"

/*
 * RX related काष्ठाures and functions
 */
#घोषणा RX_NUM_QUEUES 1
#घोषणा RX_POST_REQ_ALLOC 2
#घोषणा RX_CLAIM_REQ_ALLOC 8
#घोषणा RX_PENDING_WATERMARK 16
#घोषणा FIRST_RX_QUEUE 512

काष्ठा iwl_host_cmd;

/*This file includes the declaration that are पूर्णांकernal to the
 * trans_pcie layer */

/**
 * काष्ठा iwl_rx_mem_buffer
 * @page_dma: bus address of rxb page
 * @page: driver's poपूर्णांकer to the rxb page
 * @invalid: rxb is in driver ownership - not owned by HW
 * @vid: index of this rxb in the global table
 * @offset: indicates which offset of the page (in bytes)
 *	this buffer uses (अगर multiple RBs fit पूर्णांकo one page)
 */
काष्ठा iwl_rx_mem_buffer अणु
	dma_addr_t page_dma;
	काष्ठा page *page;
	u16 vid;
	bool invalid;
	काष्ठा list_head list;
	u32 offset;
पूर्ण;

/**
 * काष्ठा isr_statistics - पूर्णांकerrupt statistics
 *
 */
काष्ठा isr_statistics अणु
	u32 hw;
	u32 sw;
	u32 err_code;
	u32 sch;
	u32 alive;
	u32 rfसमाप्त;
	u32 ctसमाप्त;
	u32 wakeup;
	u32 rx;
	u32 tx;
	u32 unhandled;
पूर्ण;

/**
 * काष्ठा iwl_rx_transfer_desc - transfer descriptor
 * @addr: ptr to मुक्त buffer start address
 * @rbid: unique tag of the buffer
 * @reserved: reserved
 */
काष्ठा iwl_rx_transfer_desc अणु
	__le16 rbid;
	__le16 reserved[3];
	__le64 addr;
पूर्ण __packed;

#घोषणा IWL_RX_CD_FLAGS_FRAGMENTED	BIT(0)

/**
 * काष्ठा iwl_rx_completion_desc - completion descriptor
 * @reserved1: reserved
 * @rbid: unique tag of the received buffer
 * @flags: flags (0: fragmented, all others: reserved)
 * @reserved2: reserved
 */
काष्ठा iwl_rx_completion_desc अणु
	__le32 reserved1;
	__le16 rbid;
	u8 flags;
	u8 reserved2[25];
पूर्ण __packed;

/**
 * काष्ठा iwl_rxq - Rx queue
 * @id: queue index
 * @bd: driver's poपूर्णांकer to buffer of receive buffer descriptors (rbd).
 *	Address size is 32 bit in pre-9000 devices and 64 bit in 9000 devices.
 *	In AX210 devices it is a poपूर्णांकer to a list of iwl_rx_transfer_desc's
 * @bd_dma: bus address of buffer of receive buffer descriptors (rbd)
 * @ubd: driver's poपूर्णांकer to buffer of used receive buffer descriptors (rbd)
 * @ubd_dma: physical address of buffer of used receive buffer descriptors (rbd)
 * @tr_tail: driver's poपूर्णांकer to the transmission ring tail buffer
 * @tr_tail_dma: physical address of the buffer क्रम the transmission ring tail
 * @cr_tail: driver's poपूर्णांकer to the completion ring tail buffer
 * @cr_tail_dma: physical address of the buffer क्रम the completion ring tail
 * @पढ़ो: Shared index to newest available Rx buffer
 * @ग_लिखो: Shared index to oldest written Rx packet
 * @मुक्त_count: Number of pre-allocated buffers in rx_मुक्त
 * @used_count: Number of RBDs handled to allocator to use क्रम allocation
 * @ग_लिखो_actual:
 * @rx_मुक्त: list of RBDs with allocated RB पढ़ोy क्रम use
 * @rx_used: list of RBDs with no RB attached
 * @need_update: flag to indicate we need to update पढ़ो/ग_लिखो index
 * @rb_stts: driver's poपूर्णांकer to receive buffer status
 * @rb_stts_dma: bus address of receive buffer status
 * @lock:
 * @queue: actual rx queue. Not used क्रम multi-rx queue.
 * @next_rb_is_fragment: indicates that the previous RB that we handled set
 *	the fragmented flag, so the next one is still another fragment
 *
 * NOTE:  rx_मुक्त and rx_used are used as a FIFO क्रम iwl_rx_mem_buffers
 */
काष्ठा iwl_rxq अणु
	पूर्णांक id;
	व्योम *bd;
	dma_addr_t bd_dma;
	जोड़ अणु
		व्योम *used_bd;
		__le32 *bd_32;
		काष्ठा iwl_rx_completion_desc *cd;
	पूर्ण;
	dma_addr_t used_bd_dma;
	__le16 *tr_tail;
	dma_addr_t tr_tail_dma;
	__le16 *cr_tail;
	dma_addr_t cr_tail_dma;
	u32 पढ़ो;
	u32 ग_लिखो;
	u32 मुक्त_count;
	u32 used_count;
	u32 ग_लिखो_actual;
	u32 queue_size;
	काष्ठा list_head rx_मुक्त;
	काष्ठा list_head rx_used;
	bool need_update, next_rb_is_fragment;
	व्योम *rb_stts;
	dma_addr_t rb_stts_dma;
	spinlock_t lock;
	काष्ठा napi_काष्ठा napi;
	काष्ठा iwl_rx_mem_buffer *queue[RX_QUEUE_SIZE];
पूर्ण;

/**
 * काष्ठा iwl_rb_allocator - Rx allocator
 * @req_pending: number of requests the allcator had not processed yet
 * @req_पढ़ोy: number of requests honored and पढ़ोy क्रम claiming
 * @rbd_allocated: RBDs with pages allocated and पढ़ोy to be handled to
 *	the queue. This is a list of &काष्ठा iwl_rx_mem_buffer
 * @rbd_empty: RBDs with no page attached क्रम allocator use. This is a list
 *	of &काष्ठा iwl_rx_mem_buffer
 * @lock: protects the rbd_allocated and rbd_empty lists
 * @alloc_wq: work queue क्रम background calls
 * @rx_alloc: work काष्ठा क्रम background calls
 */
काष्ठा iwl_rb_allocator अणु
	atomic_t req_pending;
	atomic_t req_पढ़ोy;
	काष्ठा list_head rbd_allocated;
	काष्ठा list_head rbd_empty;
	spinlock_t lock;
	काष्ठा workqueue_काष्ठा *alloc_wq;
	काष्ठा work_काष्ठा rx_alloc;
पूर्ण;

/**
 * iwl_get_बंदd_rb_stts - get बंदd rb stts from dअगरferent काष्ठाs
 * @rxq - the rxq to get the rb stts from
 */
अटल अंतरभूत __le16 iwl_get_बंदd_rb_stts(काष्ठा iwl_trans *trans,
					    काष्ठा iwl_rxq *rxq)
अणु
	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		__le16 *rb_stts = rxq->rb_stts;

		वापस READ_ONCE(*rb_stts);
	पूर्ण अन्यथा अणु
		काष्ठा iwl_rb_status *rb_stts = rxq->rb_stts;

		वापस READ_ONCE(rb_stts->बंदd_rb_num);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
/**
 * क्रमागत iwl_fw_mon_dbgfs_state - the dअगरferent states of the monitor_data
 * debugfs file
 *
 * @IWL_FW_MON_DBGFS_STATE_CLOSED: the file is बंदd.
 * @IWL_FW_MON_DBGFS_STATE_OPEN: the file is खोलो.
 * @IWL_FW_MON_DBGFS_STATE_DISABLED: the file is disabled, once this state is
 *	set the file can no दीर्घer be used.
 */
क्रमागत iwl_fw_mon_dbgfs_state अणु
	IWL_FW_MON_DBGFS_STATE_CLOSED,
	IWL_FW_MON_DBGFS_STATE_OPEN,
	IWL_FW_MON_DBGFS_STATE_DISABLED,
पूर्ण;
#पूर्ण_अगर

/**
 * क्रमागत iwl_shared_irq_flags - level of sharing क्रम irq
 * @IWL_SHARED_IRQ_NON_RX: पूर्णांकerrupt vector serves non rx causes.
 * @IWL_SHARED_IRQ_FIRST_RSS: पूर्णांकerrupt vector serves first RSS queue.
 */
क्रमागत iwl_shared_irq_flags अणु
	IWL_SHARED_IRQ_NON_RX		= BIT(0),
	IWL_SHARED_IRQ_FIRST_RSS	= BIT(1),
पूर्ण;

/**
 * क्रमागत iwl_image_response_code - image response values
 * @IWL_IMAGE_RESP_DEF: the शेष value of the रेजिस्टर
 * @IWL_IMAGE_RESP_SUCCESS: iml was पढ़ो successfully
 * @IWL_IMAGE_RESP_FAIL: iml पढ़ोing failed
 */
क्रमागत iwl_image_response_code अणु
	IWL_IMAGE_RESP_DEF		= 0,
	IWL_IMAGE_RESP_SUCCESS		= 1,
	IWL_IMAGE_RESP_FAIL		= 2,
पूर्ण;

/**
 * काष्ठा cont_rec: continuous recording data काष्ठाure
 * @prev_wr_ptr: the last address that was पढ़ो in monitor_data
 *	debugfs file
 * @prev_wrap_cnt: the wrap count that was used during the last पढ़ो in
 *	monitor_data debugfs file
 * @state: the state of monitor_data debugfs file as described
 *	in &iwl_fw_mon_dbgfs_state क्रमागत
 * @mutex: locked जबतक पढ़ोing from monitor_data debugfs file
 */
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
काष्ठा cont_rec अणु
	u32 prev_wr_ptr;
	u32 prev_wrap_cnt;
	u8  state;
	/* Used to sync monitor_data debugfs file with driver unload flow */
	काष्ठा mutex mutex;
पूर्ण;
#पूर्ण_अगर

/**
 * काष्ठा iwl_trans_pcie - PCIe transport specअगरic data
 * @rxq: all the RX queue data
 * @rx_pool: initial pool of iwl_rx_mem_buffer क्रम all the queues
 * @global_table: table mapping received VID from hw to rxb
 * @rba: allocator क्रम RX replenishing
 * @ctxt_info: context inक्रमmation क्रम FW self init
 * @ctxt_info_gen3: context inक्रमmation क्रम gen3 devices
 * @prph_info: prph info क्रम self init
 * @prph_scratch: prph scratch क्रम self init
 * @ctxt_info_dma_addr: dma addr of context inक्रमmation
 * @prph_info_dma_addr: dma addr of prph info
 * @prph_scratch_dma_addr: dma addr of prph scratch
 * @ctxt_info_dma_addr: dma addr of context inक्रमmation
 * @init_dram: DRAM data of firmware image (including paging).
 *	Context inक्रमmation addresses will be taken from here.
 *	This is driver's local copy क्रम keeping track of size and
 *	count क्रम allocating and मुक्तing the memory.
 * @trans: poपूर्णांकer to the generic transport area
 * @scd_base_addr: scheduler sram base address in SRAM
 * @kw: keep warm address
 * @pnvm_dram: DRAM area that contains the PNVM data
 * @pci_dev: basic pci-network driver stuff
 * @hw_base: pci hardware address support
 * @ucode_ग_लिखो_complete: indicates that the ucode has been copied.
 * @ucode_ग_लिखो_रुकोq: रुको queue क्रम uCode load
 * @cmd_queue - command queue number
 * @def_rx_queue - शेष rx queue number
 * @rx_buf_size: Rx buffer size
 * @scd_set_active: should the transport configure the SCD क्रम HCMD queue
 * @rx_page_order: page order क्रम receive buffer size
 * @rx_buf_bytes: RX buffer (RB) size in bytes
 * @reg_lock: protect hw रेजिस्टर access
 * @mutex: to protect stop_device / start_fw / start_hw
 * @cmd_in_flight: true when we have a host command in flight
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
 * @fw_mon_data: fw continuous recording data
#पूर्ण_अगर
 * @msix_entries: array of MSI-X entries
 * @msix_enabled: true अगर managed to enable MSI-X
 * @shared_vec_mask: the type of causes the shared vector handles
 *	(see iwl_shared_irq_flags).
 * @alloc_vecs: the number of पूर्णांकerrupt vectors allocated by the OS
 * @def_irq: शेष irq क्रम non rx causes
 * @fh_init_mask: initial unmasked fh causes
 * @hw_init_mask: initial unmasked hw causes
 * @fh_mask: current unmasked fh causes
 * @hw_mask: current unmasked hw causes
 * @in_rescan: true अगर we have triggered a device rescan
 * @base_rb_stts: base भव address of receive buffer status क्रम all queues
 * @base_rb_stts_dma: base physical address of receive buffer status
 * @supported_dma_mask: DMA mask to validate the actual address against,
 *	will be DMA_BIT_MASK(11) or DMA_BIT_MASK(12) depending on the device
 * @alloc_page_lock: spinlock क्रम the page allocator
 * @alloc_page: allocated page to still use parts of
 * @alloc_page_used: how much of the allocated page was alपढ़ोy used (bytes)
 */
काष्ठा iwl_trans_pcie अणु
	काष्ठा iwl_rxq *rxq;
	काष्ठा iwl_rx_mem_buffer *rx_pool;
	काष्ठा iwl_rx_mem_buffer **global_table;
	काष्ठा iwl_rb_allocator rba;
	जोड़ अणु
		काष्ठा iwl_context_info *ctxt_info;
		काष्ठा iwl_context_info_gen3 *ctxt_info_gen3;
	पूर्ण;
	काष्ठा iwl_prph_info *prph_info;
	काष्ठा iwl_prph_scratch *prph_scratch;
	dma_addr_t ctxt_info_dma_addr;
	dma_addr_t prph_info_dma_addr;
	dma_addr_t prph_scratch_dma_addr;
	dma_addr_t iml_dma_addr;
	काष्ठा iwl_trans *trans;

	काष्ठा net_device napi_dev;

	/* INT ICT Table */
	__le32 *ict_tbl;
	dma_addr_t ict_tbl_dma;
	पूर्णांक ict_index;
	bool use_ict;
	bool is_करोwn, opmode_करोwn;
	s8 debug_rfसमाप्त;
	काष्ठा isr_statistics isr_stats;

	spinlock_t irq_lock;
	काष्ठा mutex mutex;
	u32 पूर्णांकa_mask;
	u32 scd_base_addr;
	काष्ठा iwl_dma_ptr kw;

	काष्ठा iwl_dram_data pnvm_dram;

	काष्ठा iwl_txq *txq_memory;

	/* PCI bus related data */
	काष्ठा pci_dev *pci_dev;
	व्योम __iomem *hw_base;

	bool ucode_ग_लिखो_complete;
	bool sx_complete;
	रुको_queue_head_t ucode_ग_लिखो_रुकोq;
	रुको_queue_head_t sx_रुकोq;

	u8 def_rx_queue;
	u8 n_no_reclaim_cmds;
	u8 no_reclaim_cmds[MAX_NO_RECLAIM_CMDS];
	u16 num_rx_bufs;

	क्रमागत iwl_amsdu_size rx_buf_size;
	bool scd_set_active;
	bool pcie_dbg_dumped_once;
	u32 rx_page_order;
	u32 rx_buf_bytes;
	u32 supported_dma_mask;

	/* allocator lock क्रम the two values below */
	spinlock_t alloc_page_lock;
	काष्ठा page *alloc_page;
	u32 alloc_page_used;

	/*protect hw रेजिस्टर */
	spinlock_t reg_lock;
	bool cmd_hold_nic_awake;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	काष्ठा cont_rec fw_mon_data;
#पूर्ण_अगर

	काष्ठा msix_entry msix_entries[IWL_MAX_RX_HW_QUEUES];
	bool msix_enabled;
	u8 shared_vec_mask;
	u32 alloc_vecs;
	u32 def_irq;
	u32 fh_init_mask;
	u32 hw_init_mask;
	u32 fh_mask;
	u32 hw_mask;
	cpumask_t affinity_mask[IWL_MAX_RX_HW_QUEUES];
	u16 tx_cmd_queue_size;
	bool in_rescan;

	व्योम *base_rb_stts;
	dma_addr_t base_rb_stts_dma;

	bool fw_reset_handshake;
	bool fw_reset_करोne;
	रुको_queue_head_t fw_reset_रुकोq;
पूर्ण;

अटल अंतरभूत काष्ठा iwl_trans_pcie *
IWL_TRANS_GET_PCIE_TRANS(काष्ठा iwl_trans *trans)
अणु
	वापस (व्योम *)trans->trans_specअगरic;
पूर्ण

अटल अंतरभूत व्योम iwl_pcie_clear_irq(काष्ठा iwl_trans *trans, पूर्णांक queue)
अणु
	/*
	 * Beक्रमe sending the पूर्णांकerrupt the HW disables it to prevent
	 * a nested पूर्णांकerrupt. This is करोne by writing 1 to the corresponding
	 * bit in the mask रेजिस्टर. After handling the पूर्णांकerrupt, it should be
	 * re-enabled by clearing this bit. This रेजिस्टर is defined as
	 * ग_लिखो 1 clear (W1C) रेजिस्टर, meaning that it's being clear
	 * by writing 1 to the bit.
	 */
	iwl_ग_लिखो32(trans, CSR_MSIX_AUTOMASK_ST_AD, BIT(queue));
पूर्ण

अटल अंतरभूत काष्ठा iwl_trans *
iwl_trans_pcie_get_trans(काष्ठा iwl_trans_pcie *trans_pcie)
अणु
	वापस container_of((व्योम *)trans_pcie, काष्ठा iwl_trans,
			    trans_specअगरic);
पूर्ण

/*
 * Convention: trans API functions: iwl_trans_pcie_XXX
 *	Other functions: iwl_pcie_XXX
 */
काष्ठा iwl_trans
*iwl_trans_pcie_alloc(काष्ठा pci_dev *pdev,
		      स्थिर काष्ठा pci_device_id *ent,
		      स्थिर काष्ठा iwl_cfg_trans_params *cfg_trans);
व्योम iwl_trans_pcie_मुक्त(काष्ठा iwl_trans *trans);

bool __iwl_trans_pcie_grab_nic_access(काष्ठा iwl_trans *trans);
#घोषणा _iwl_trans_pcie_grab_nic_access(trans)			\
	__cond_lock(nic_access_nobh,				\
		    likely(__iwl_trans_pcie_grab_nic_access(trans)))

/*****************************************************
* RX
******************************************************/
पूर्णांक iwl_pcie_rx_init(काष्ठा iwl_trans *trans);
पूर्णांक iwl_pcie_gen2_rx_init(काष्ठा iwl_trans *trans);
irqवापस_t iwl_pcie_msix_isr(पूर्णांक irq, व्योम *data);
irqवापस_t iwl_pcie_irq_handler(पूर्णांक irq, व्योम *dev_id);
irqवापस_t iwl_pcie_irq_msix_handler(पूर्णांक irq, व्योम *dev_id);
irqवापस_t iwl_pcie_irq_rx_msix_handler(पूर्णांक irq, व्योम *dev_id);
पूर्णांक iwl_pcie_rx_stop(काष्ठा iwl_trans *trans);
व्योम iwl_pcie_rx_मुक्त(काष्ठा iwl_trans *trans);
व्योम iwl_pcie_मुक्त_rbs_pool(काष्ठा iwl_trans *trans);
व्योम iwl_pcie_rx_init_rxb_lists(काष्ठा iwl_rxq *rxq);
व्योम iwl_pcie_rxq_alloc_rbs(काष्ठा iwl_trans *trans, gfp_t priority,
			    काष्ठा iwl_rxq *rxq);

/*****************************************************
* ICT - पूर्णांकerrupt handling
******************************************************/
irqवापस_t iwl_pcie_isr(पूर्णांक irq, व्योम *data);
पूर्णांक iwl_pcie_alloc_ict(काष्ठा iwl_trans *trans);
व्योम iwl_pcie_मुक्त_ict(काष्ठा iwl_trans *trans);
व्योम iwl_pcie_reset_ict(काष्ठा iwl_trans *trans);
व्योम iwl_pcie_disable_ict(काष्ठा iwl_trans *trans);

/*****************************************************
* TX / HCMD
******************************************************/
पूर्णांक iwl_pcie_tx_init(काष्ठा iwl_trans *trans);
व्योम iwl_pcie_tx_start(काष्ठा iwl_trans *trans, u32 scd_base_addr);
पूर्णांक iwl_pcie_tx_stop(काष्ठा iwl_trans *trans);
व्योम iwl_pcie_tx_मुक्त(काष्ठा iwl_trans *trans);
bool iwl_trans_pcie_txq_enable(काष्ठा iwl_trans *trans, पूर्णांक queue, u16 ssn,
			       स्थिर काष्ठा iwl_trans_txq_scd_cfg *cfg,
			       अचिन्हित पूर्णांक wdg_समयout);
व्योम iwl_trans_pcie_txq_disable(काष्ठा iwl_trans *trans, पूर्णांक queue,
				bool configure_scd);
व्योम iwl_trans_pcie_txq_set_shared_mode(काष्ठा iwl_trans *trans, u32 txq_id,
					bool shared_mode);
पूर्णांक iwl_trans_pcie_tx(काष्ठा iwl_trans *trans, काष्ठा sk_buff *skb,
		      काष्ठा iwl_device_tx_cmd *dev_cmd, पूर्णांक txq_id);
व्योम iwl_pcie_txq_check_wrptrs(काष्ठा iwl_trans *trans);
पूर्णांक iwl_trans_pcie_send_hcmd(काष्ठा iwl_trans *trans, काष्ठा iwl_host_cmd *cmd);
व्योम iwl_pcie_hcmd_complete(काष्ठा iwl_trans *trans,
			    काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_trans_pcie_tx_reset(काष्ठा iwl_trans *trans);

/*****************************************************
* Error handling
******************************************************/
व्योम iwl_pcie_dump_csr(काष्ठा iwl_trans *trans);

/*****************************************************
* Helpers
******************************************************/
अटल अंतरभूत व्योम _iwl_disable_पूर्णांकerrupts(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	clear_bit(STATUS_INT_ENABLED, &trans->status);
	अगर (!trans_pcie->msix_enabled) अणु
		/* disable पूर्णांकerrupts from uCode/NIC to host */
		iwl_ग_लिखो32(trans, CSR_INT_MASK, 0x00000000);

		/* acknowledge/clear/reset any पूर्णांकerrupts still pending
		 * from uCode or flow handler (Rx/Tx DMA) */
		iwl_ग_लिखो32(trans, CSR_INT, 0xffffffff);
		iwl_ग_लिखो32(trans, CSR_FH_INT_STATUS, 0xffffffff);
	पूर्ण अन्यथा अणु
		/* disable all the पूर्णांकerrupt we might use */
		iwl_ग_लिखो32(trans, CSR_MSIX_FH_INT_MASK_AD,
			    trans_pcie->fh_init_mask);
		iwl_ग_लिखो32(trans, CSR_MSIX_HW_INT_MASK_AD,
			    trans_pcie->hw_init_mask);
	पूर्ण
	IWL_DEBUG_ISR(trans, "Disabled interrupts\n");
पूर्ण

#घोषणा IWL_NUM_OF_COMPLETION_RINGS	31
#घोषणा IWL_NUM_OF_TRANSFER_RINGS	527

अटल अंतरभूत पूर्णांक iwl_pcie_get_num_sections(स्थिर काष्ठा fw_img *fw,
					    पूर्णांक start)
अणु
	पूर्णांक i = 0;

	जबतक (start < fw->num_sec &&
	       fw->sec[start].offset != CPU1_CPU2_SEPARATOR_SECTION &&
	       fw->sec[start].offset != PAGING_SEPARATOR_SECTION) अणु
		start++;
		i++;
	पूर्ण

	वापस i;
पूर्ण

अटल अंतरभूत व्योम iwl_pcie_ctxt_info_मुक्त_fw_img(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_self_init_dram *dram = &trans->init_dram;
	पूर्णांक i;

	अगर (!dram->fw) अणु
		WARN_ON(dram->fw_cnt);
		वापस;
	पूर्ण

	क्रम (i = 0; i < dram->fw_cnt; i++)
		dma_मुक्त_coherent(trans->dev, dram->fw[i].size,
				  dram->fw[i].block, dram->fw[i].physical);

	kमुक्त(dram->fw);
	dram->fw_cnt = 0;
	dram->fw = शून्य;
पूर्ण

अटल अंतरभूत व्योम iwl_disable_पूर्णांकerrupts(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	spin_lock_bh(&trans_pcie->irq_lock);
	_iwl_disable_पूर्णांकerrupts(trans);
	spin_unlock_bh(&trans_pcie->irq_lock);
पूर्ण

अटल अंतरभूत व्योम _iwl_enable_पूर्णांकerrupts(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	IWL_DEBUG_ISR(trans, "Enabling interrupts\n");
	set_bit(STATUS_INT_ENABLED, &trans->status);
	अगर (!trans_pcie->msix_enabled) अणु
		trans_pcie->पूर्णांकa_mask = CSR_INI_SET_MASK;
		iwl_ग_लिखो32(trans, CSR_INT_MASK, trans_pcie->पूर्णांकa_mask);
	पूर्ण अन्यथा अणु
		/*
		 * fh/hw_mask keeps all the unmasked causes.
		 * Unlike msi, in msix cause is enabled when it is unset.
		 */
		trans_pcie->hw_mask = trans_pcie->hw_init_mask;
		trans_pcie->fh_mask = trans_pcie->fh_init_mask;
		iwl_ग_लिखो32(trans, CSR_MSIX_FH_INT_MASK_AD,
			    ~trans_pcie->fh_mask);
		iwl_ग_लिखो32(trans, CSR_MSIX_HW_INT_MASK_AD,
			    ~trans_pcie->hw_mask);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम iwl_enable_पूर्णांकerrupts(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	spin_lock_bh(&trans_pcie->irq_lock);
	_iwl_enable_पूर्णांकerrupts(trans);
	spin_unlock_bh(&trans_pcie->irq_lock);
पूर्ण
अटल अंतरभूत व्योम iwl_enable_hw_पूर्णांक_msk_msix(काष्ठा iwl_trans *trans, u32 msk)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	iwl_ग_लिखो32(trans, CSR_MSIX_HW_INT_MASK_AD, ~msk);
	trans_pcie->hw_mask = msk;
पूर्ण

अटल अंतरभूत व्योम iwl_enable_fh_पूर्णांक_msk_msix(काष्ठा iwl_trans *trans, u32 msk)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	iwl_ग_लिखो32(trans, CSR_MSIX_FH_INT_MASK_AD, ~msk);
	trans_pcie->fh_mask = msk;
पूर्ण

अटल अंतरभूत व्योम iwl_enable_fw_load_पूर्णांक(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	IWL_DEBUG_ISR(trans, "Enabling FW load interrupt\n");
	अगर (!trans_pcie->msix_enabled) अणु
		trans_pcie->पूर्णांकa_mask = CSR_INT_BIT_FH_TX;
		iwl_ग_लिखो32(trans, CSR_INT_MASK, trans_pcie->पूर्णांकa_mask);
	पूर्ण अन्यथा अणु
		iwl_ग_लिखो32(trans, CSR_MSIX_HW_INT_MASK_AD,
			    trans_pcie->hw_init_mask);
		iwl_enable_fh_पूर्णांक_msk_msix(trans,
					   MSIX_FH_INT_CAUSES_D2S_CH0_NUM);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम iwl_enable_fw_load_पूर्णांक_ctx_info(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	IWL_DEBUG_ISR(trans, "Enabling ALIVE interrupt only\n");

	अगर (!trans_pcie->msix_enabled) अणु
		/*
		 * When we'll receive the ALIVE पूर्णांकerrupt, the ISR will call
		 * iwl_enable_fw_load_पूर्णांक_ctx_info again to set the ALIVE
		 * पूर्णांकerrupt (which is not really needed anymore) but also the
		 * RX पूर्णांकerrupt which will allow us to receive the ALIVE
		 * notअगरication (which is Rx) and जारी the flow.
		 */
		trans_pcie->पूर्णांकa_mask =  CSR_INT_BIT_ALIVE | CSR_INT_BIT_FH_RX;
		iwl_ग_लिखो32(trans, CSR_INT_MASK, trans_pcie->पूर्णांकa_mask);
	पूर्ण अन्यथा अणु
		iwl_enable_hw_पूर्णांक_msk_msix(trans,
					   MSIX_HW_INT_CAUSES_REG_ALIVE);
		/*
		 * Leave all the FH causes enabled to get the ALIVE
		 * notअगरication.
		 */
		iwl_enable_fh_पूर्णांक_msk_msix(trans, trans_pcie->fh_init_mask);
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *queue_name(काष्ठा device *dev,
				     काष्ठा iwl_trans_pcie *trans_p, पूर्णांक i)
अणु
	अगर (trans_p->shared_vec_mask) अणु
		पूर्णांक vec = trans_p->shared_vec_mask &
			  IWL_SHARED_IRQ_FIRST_RSS ? 1 : 0;

		अगर (i == 0)
			वापस DRV_NAME ": shared IRQ";

		वापस devm_kaप्र_लिखो(dev, GFP_KERNEL,
				      DRV_NAME ": queue %d", i + vec);
	पूर्ण
	अगर (i == 0)
		वापस DRV_NAME ": default queue";

	अगर (i == trans_p->alloc_vecs - 1)
		वापस DRV_NAME ": exception";

	वापस devm_kaप्र_लिखो(dev, GFP_KERNEL,
			      DRV_NAME  ": queue %d", i);
पूर्ण

अटल अंतरभूत व्योम iwl_enable_rfसमाप्त_पूर्णांक(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	IWL_DEBUG_ISR(trans, "Enabling rfkill interrupt\n");
	अगर (!trans_pcie->msix_enabled) अणु
		trans_pcie->पूर्णांकa_mask = CSR_INT_BIT_RF_KILL;
		iwl_ग_लिखो32(trans, CSR_INT_MASK, trans_pcie->पूर्णांकa_mask);
	पूर्ण अन्यथा अणु
		iwl_ग_लिखो32(trans, CSR_MSIX_FH_INT_MASK_AD,
			    trans_pcie->fh_init_mask);
		iwl_enable_hw_पूर्णांक_msk_msix(trans,
					   MSIX_HW_INT_CAUSES_REG_RF_KILL);
	पूर्ण

	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_9000) अणु
		/*
		 * On 9000-series devices this bit isn't enabled by शेष, so
		 * when we घातer करोwn the device we need set the bit to allow it
		 * to wake up the PCI-E bus क्रम RF-समाप्त पूर्णांकerrupts.
		 */
		iwl_set_bit(trans, CSR_GP_CNTRL,
			    CSR_GP_CNTRL_REG_FLAG_RFKILL_WAKE_L1A_EN);
	पूर्ण
पूर्ण

व्योम iwl_pcie_handle_rfसमाप्त_irq(काष्ठा iwl_trans *trans);

अटल अंतरभूत bool iwl_is_rfसमाप्त_set(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	lockdep_निश्चित_held(&trans_pcie->mutex);

	अगर (trans_pcie->debug_rfसमाप्त == 1)
		वापस true;

	वापस !(iwl_पढ़ो32(trans, CSR_GP_CNTRL) &
		CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW);
पूर्ण

अटल अंतरभूत व्योम __iwl_trans_pcie_set_bits_mask(काष्ठा iwl_trans *trans,
						  u32 reg, u32 mask, u32 value)
अणु
	u32 v;

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	WARN_ON_ONCE(value & ~mask);
#पूर्ण_अगर

	v = iwl_पढ़ो32(trans, reg);
	v &= ~mask;
	v |= value;
	iwl_ग_लिखो32(trans, reg, v);
पूर्ण

अटल अंतरभूत व्योम __iwl_trans_pcie_clear_bit(काष्ठा iwl_trans *trans,
					      u32 reg, u32 mask)
अणु
	__iwl_trans_pcie_set_bits_mask(trans, reg, mask, 0);
पूर्ण

अटल अंतरभूत व्योम __iwl_trans_pcie_set_bit(काष्ठा iwl_trans *trans,
					    u32 reg, u32 mask)
अणु
	__iwl_trans_pcie_set_bits_mask(trans, reg, mask, mask);
पूर्ण

अटल अंतरभूत bool iwl_pcie_dbg_on(काष्ठा iwl_trans *trans)
अणु
	वापस (trans->dbg.dest_tlv || iwl_trans_dbg_ini_valid(trans));
पूर्ण

व्योम iwl_trans_pcie_rf_समाप्त(काष्ठा iwl_trans *trans, bool state);
व्योम iwl_trans_pcie_dump_regs(काष्ठा iwl_trans *trans);

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
व्योम iwl_trans_pcie_dbgfs_रेजिस्टर(काष्ठा iwl_trans *trans);
#अन्यथा
अटल अंतरभूत व्योम iwl_trans_pcie_dbgfs_रेजिस्टर(काष्ठा iwl_trans *trans) अणु पूर्ण
#पूर्ण_अगर

व्योम iwl_pcie_rx_allocator_work(काष्ठा work_काष्ठा *data);

/* common functions that are used by gen2 transport */
पूर्णांक iwl_pcie_gen2_apm_init(काष्ठा iwl_trans *trans);
व्योम iwl_pcie_apm_config(काष्ठा iwl_trans *trans);
पूर्णांक iwl_pcie_prepare_card_hw(काष्ठा iwl_trans *trans);
व्योम iwl_pcie_synchronize_irqs(काष्ठा iwl_trans *trans);
bool iwl_pcie_check_hw_rf_समाप्त(काष्ठा iwl_trans *trans);
व्योम iwl_trans_pcie_handle_stop_rfसमाप्त(काष्ठा iwl_trans *trans,
				       bool was_in_rfसमाप्त);
व्योम iwl_pcie_apm_stop_master(काष्ठा iwl_trans *trans);
व्योम iwl_pcie_conf_msix_hw(काष्ठा iwl_trans_pcie *trans_pcie);
पूर्णांक iwl_pcie_alloc_dma_ptr(काष्ठा iwl_trans *trans,
			   काष्ठा iwl_dma_ptr *ptr, माप_प्रकार size);
व्योम iwl_pcie_मुक्त_dma_ptr(काष्ठा iwl_trans *trans, काष्ठा iwl_dma_ptr *ptr);
व्योम iwl_pcie_apply_destination(काष्ठा iwl_trans *trans);

/* common functions that are used by gen3 transport */
व्योम iwl_pcie_alloc_fw_monitor(काष्ठा iwl_trans *trans, u8 max_घातer);

/* transport gen 2 exported functions */
पूर्णांक iwl_trans_pcie_gen2_start_fw(काष्ठा iwl_trans *trans,
				 स्थिर काष्ठा fw_img *fw, bool run_in_rfसमाप्त);
व्योम iwl_trans_pcie_gen2_fw_alive(काष्ठा iwl_trans *trans, u32 scd_addr);
पूर्णांक iwl_trans_pcie_gen2_send_hcmd(काष्ठा iwl_trans *trans,
				  काष्ठा iwl_host_cmd *cmd);
व्योम iwl_trans_pcie_gen2_stop_device(काष्ठा iwl_trans *trans);
व्योम _iwl_trans_pcie_gen2_stop_device(काष्ठा iwl_trans *trans);
व्योम iwl_pcie_d3_complete_suspend(काष्ठा iwl_trans *trans,
				  bool test, bool reset);
पूर्णांक iwl_pcie_gen2_enqueue_hcmd(काष्ठा iwl_trans *trans,
			       काष्ठा iwl_host_cmd *cmd);
पूर्णांक iwl_pcie_enqueue_hcmd(काष्ठा iwl_trans *trans,
			  काष्ठा iwl_host_cmd *cmd);
#पूर्ण_अगर /* __iwl_trans_पूर्णांक_pcie_h__ */
