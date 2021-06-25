<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_DP_H
#घोषणा ATH11K_DP_H

#समावेश "hal_rx.h"

#घोषणा MAX_RXDMA_PER_PDEV     2

काष्ठा ath11k_base;
काष्ठा ath11k_peer;
काष्ठा ath11k_dp;
काष्ठा ath11k_vअगर;
काष्ठा hal_tcl_status_ring;
काष्ठा ath11k_ext_irq_grp;

काष्ठा dp_rx_tid अणु
	u8 tid;
	u32 *vaddr;
	dma_addr_t paddr;
	u32 size;
	u32 ba_win_sz;
	bool active;

	/* Info related to rx fragments */
	u32 cur_sn;
	u16 last_frag_no;
	u16 rx_frag_biपंचांगap;

	काष्ठा sk_buff_head rx_frags;
	काष्ठा hal_reo_dest_ring *dst_ring_desc;

	/* Timer info related to fragments */
	काष्ठा समयr_list frag_समयr;
	काष्ठा ath11k_base *ab;
पूर्ण;

#घोषणा DP_REO_DESC_FREE_THRESHOLD  64
#घोषणा DP_REO_DESC_FREE_TIMEOUT_MS 1000
#घोषणा DP_MON_PURGE_TIMEOUT_MS     100
#घोषणा DP_MON_SERVICE_BUDGET       128

काष्ठा dp_reo_cache_flush_elem अणु
	काष्ठा list_head list;
	काष्ठा dp_rx_tid data;
	अचिन्हित दीर्घ ts;
पूर्ण;

काष्ठा dp_reo_cmd अणु
	काष्ठा list_head list;
	काष्ठा dp_rx_tid data;
	पूर्णांक cmd_num;
	व्योम (*handler)(काष्ठा ath11k_dp *, व्योम *,
			क्रमागत hal_reo_cmd_status status);
पूर्ण;

काष्ठा dp_srng अणु
	u32 *vaddr_unaligned;
	u32 *vaddr;
	dma_addr_t paddr_unaligned;
	dma_addr_t paddr;
	पूर्णांक size;
	u32 ring_id;
पूर्ण;

काष्ठा dp_rxdma_ring अणु
	काष्ठा dp_srng refill_buf_ring;
	काष्ठा idr bufs_idr;
	/* Protects bufs_idr */
	spinlock_t idr_lock;
	पूर्णांक bufs_max;
पूर्ण;

#घोषणा ATH11K_TX_COMPL_NEXT(x)	(((x) + 1) % DP_TX_COMP_RING_SIZE)

काष्ठा dp_tx_ring अणु
	u8 tcl_data_ring_id;
	काष्ठा dp_srng tcl_data_ring;
	काष्ठा dp_srng tcl_comp_ring;
	काष्ठा idr txbuf_idr;
	/* Protects txbuf_idr and num_pending */
	spinlock_t tx_idr_lock;
	काष्ठा hal_wbm_release_ring *tx_status;
	पूर्णांक tx_status_head;
	पूर्णांक tx_status_tail;
पूर्ण;

काष्ठा ath11k_pdev_mon_stats अणु
	u32 status_ppdu_state;
	u32 status_ppdu_start;
	u32 status_ppdu_end;
	u32 status_ppdu_compl;
	u32 status_ppdu_start_mis;
	u32 status_ppdu_end_mis;
	u32 status_ppdu_करोne;
	u32 dest_ppdu_करोne;
	u32 dest_mpdu_करोne;
	u32 dest_mpdu_drop;
	u32 dup_mon_linkdesc_cnt;
	u32 dup_mon_buf_cnt;
पूर्ण;

काष्ठा dp_link_desc_bank अणु
	व्योम *vaddr_unaligned;
	व्योम *vaddr;
	dma_addr_t paddr_unaligned;
	dma_addr_t paddr;
	u32 size;
पूर्ण;

/* Size to enक्रमce scatter idle list mode */
#घोषणा DP_LINK_DESC_ALLOC_SIZE_THRESH 0x200000
#घोषणा DP_LINK_DESC_BANKS_MAX 8

#घोषणा DP_RX_DESC_COOKIE_INDEX_MAX		0x3ffff
#घोषणा DP_RX_DESC_COOKIE_POOL_ID_MAX		0x1c0000
#घोषणा DP_RX_DESC_COOKIE_MAX	\
	(DP_RX_DESC_COOKIE_INDEX_MAX | DP_RX_DESC_COOKIE_POOL_ID_MAX)
#घोषणा DP_NOT_PPDU_ID_WRAP_AROUND 20000

क्रमागत ath11k_dp_ppdu_state अणु
	DP_PPDU_STATUS_START,
	DP_PPDU_STATUS_DONE,
पूर्ण;

काष्ठा ath11k_mon_data अणु
	काष्ठा dp_link_desc_bank link_desc_banks[DP_LINK_DESC_BANKS_MAX];
	काष्ठा hal_rx_mon_ppdu_info mon_ppdu_info;

	u32 mon_ppdu_status;
	u32 mon_last_buf_cookie;
	u64 mon_last_linkdesc_paddr;
	u16 chan_noise_न्यूनमान;

	काष्ठा ath11k_pdev_mon_stats rx_mon_stats;
	/* lock क्रम monitor data */
	spinlock_t mon_lock;
	काष्ठा sk_buff_head rx_status_q;
पूर्ण;

काष्ठा ath11k_pdev_dp अणु
	u32 mac_id;
	atomic_t num_tx_pending;
	रुको_queue_head_t tx_empty_रुकोq;
	काष्ठा dp_rxdma_ring rx_refill_buf_ring;
	काष्ठा dp_srng rx_mac_buf_ring[MAX_RXDMA_PER_PDEV];
	काष्ठा dp_srng rxdma_err_dst_ring[MAX_RXDMA_PER_PDEV];
	काष्ठा dp_srng rxdma_mon_dst_ring;
	काष्ठा dp_srng rxdma_mon_desc_ring;

	काष्ठा dp_rxdma_ring rxdma_mon_buf_ring;
	काष्ठा dp_rxdma_ring rx_mon_status_refill_ring[MAX_RXDMA_PER_PDEV];
	काष्ठा ieee80211_rx_status rx_status;
	काष्ठा ath11k_mon_data mon_data;
पूर्ण;

#घोषणा DP_NUM_CLIENTS_MAX 64
#घोषणा DP_AVG_TIDS_PER_CLIENT 2
#घोषणा DP_NUM_TIDS_MAX (DP_NUM_CLIENTS_MAX * DP_AVG_TIDS_PER_CLIENT)
#घोषणा DP_AVG_MSDUS_PER_FLOW 128
#घोषणा DP_AVG_FLOWS_PER_TID 2
#घोषणा DP_AVG_MPDUS_PER_TID_MAX 128
#घोषणा DP_AVG_MSDUS_PER_MPDU 4

#घोषणा DP_RX_HASH_ENABLE	1 /* Enable hash based Rx steering */

#घोषणा DP_BA_WIN_SZ_MAX	256

#घोषणा DP_TCL_NUM_RING_MAX	3

#घोषणा DP_IDLE_SCATTER_BUFS_MAX 16

#घोषणा DP_WBM_RELEASE_RING_SIZE	64
#घोषणा DP_TCL_DATA_RING_SIZE		512
#घोषणा DP_TX_COMP_RING_SIZE		32768
#घोषणा DP_TX_IDR_SIZE			DP_TX_COMP_RING_SIZE
#घोषणा DP_TCL_CMD_RING_SIZE		32
#घोषणा DP_TCL_STATUS_RING_SIZE		32
#घोषणा DP_REO_DST_RING_MAX		4
#घोषणा DP_REO_DST_RING_SIZE		2048
#घोषणा DP_REO_REINJECT_RING_SIZE	32
#घोषणा DP_RX_RELEASE_RING_SIZE		1024
#घोषणा DP_REO_EXCEPTION_RING_SIZE	128
#घोषणा DP_REO_CMD_RING_SIZE		128
#घोषणा DP_REO_STATUS_RING_SIZE		2048
#घोषणा DP_RXDMA_BUF_RING_SIZE		4096
#घोषणा DP_RXDMA_REFILL_RING_SIZE	2048
#घोषणा DP_RXDMA_ERR_DST_RING_SIZE	1024
#घोषणा DP_RXDMA_MON_STATUS_RING_SIZE	1024
#घोषणा DP_RXDMA_MONITOR_BUF_RING_SIZE	4096
#घोषणा DP_RXDMA_MONITOR_DST_RING_SIZE	2048
#घोषणा DP_RXDMA_MONITOR_DESC_RING_SIZE	4096

#घोषणा DP_RX_BUFFER_SIZE	2048
#घोषणा DP_RX_BUFFER_ALIGN_SIZE	128

#घोषणा DP_RXDMA_BUF_COOKIE_BUF_ID	GENMASK(17, 0)
#घोषणा DP_RXDMA_BUF_COOKIE_PDEV_ID	GENMASK(20, 18)

#घोषणा DP_HW2SW_MACID(mac_id) ((mac_id) ? ((mac_id) - 1) : 0)
#घोषणा DP_SW2HW_MACID(mac_id) ((mac_id) + 1)

#घोषणा DP_TX_DESC_ID_MAC_ID  GENMASK(1, 0)
#घोषणा DP_TX_DESC_ID_MSDU_ID GENMASK(18, 2)
#घोषणा DP_TX_DESC_ID_POOL_ID GENMASK(20, 19)

#घोषणा ATH11K_SHADOW_DP_TIMER_INTERVAL 20
#घोषणा ATH11K_SHADOW_CTRL_TIMER_INTERVAL 10

काष्ठा ath11k_hp_update_समयr अणु
	काष्ठा समयr_list समयr;
	bool started;
	bool init;
	u32 tx_num;
	u32 समयr_tx_num;
	u32 ring_id;
	u32 पूर्णांकerval;
	काष्ठा ath11k_base *ab;
पूर्ण;

काष्ठा ath11k_dp अणु
	काष्ठा ath11k_base *ab;
	क्रमागत ath11k_htc_ep_id eid;
	काष्ठा completion htt_tgt_version_received;
	u8 htt_tgt_ver_major;
	u8 htt_tgt_ver_minor;
	काष्ठा dp_link_desc_bank link_desc_banks[DP_LINK_DESC_BANKS_MAX];
	काष्ठा dp_srng wbm_idle_ring;
	काष्ठा dp_srng wbm_desc_rel_ring;
	काष्ठा dp_srng tcl_cmd_ring;
	काष्ठा dp_srng tcl_status_ring;
	काष्ठा dp_srng reo_reinject_ring;
	काष्ठा dp_srng rx_rel_ring;
	काष्ठा dp_srng reo_except_ring;
	काष्ठा dp_srng reo_cmd_ring;
	काष्ठा dp_srng reo_status_ring;
	काष्ठा dp_srng reo_dst_ring[DP_REO_DST_RING_MAX];
	काष्ठा dp_tx_ring tx_ring[DP_TCL_NUM_RING_MAX];
	काष्ठा hal_wbm_idle_scatter_list scatter_list[DP_IDLE_SCATTER_BUFS_MAX];
	काष्ठा list_head reo_cmd_list;
	काष्ठा list_head reo_cmd_cache_flush_list;
	u32 reo_cmd_cache_flush_count;
	/**
	 * protects access to below fields,
	 * - reo_cmd_list
	 * - reo_cmd_cache_flush_list
	 * - reo_cmd_cache_flush_count
	 */
	spinlock_t reo_cmd_lock;
	काष्ठा ath11k_hp_update_समयr reo_cmd_समयr;
	काष्ठा ath11k_hp_update_समयr tx_ring_समयr[DP_TCL_NUM_RING_MAX];
पूर्ण;

/* HTT definitions */

#घोषणा HTT_TCL_META_DATA_TYPE			BIT(0)
#घोषणा HTT_TCL_META_DATA_VALID_HTT		BIT(1)

/* vdev meta data */
#घोषणा HTT_TCL_META_DATA_VDEV_ID		GENMASK(9, 2)
#घोषणा HTT_TCL_META_DATA_PDEV_ID		GENMASK(11, 10)
#घोषणा HTT_TCL_META_DATA_HOST_INSPECTED	BIT(12)

/* peer meta data */
#घोषणा HTT_TCL_META_DATA_PEER_ID		GENMASK(15, 2)

#घोषणा HTT_TX_WBM_COMP_STATUS_OFFSET 8

/* HTT tx completion is overlayed in wbm_release_ring */
#घोषणा HTT_TX_WBM_COMP_INFO0_STATUS		GENMASK(12, 9)
#घोषणा HTT_TX_WBM_COMP_INFO0_REINJECT_REASON	GENMASK(16, 13)
#घोषणा HTT_TX_WBM_COMP_INFO0_REINJECT_REASON	GENMASK(16, 13)

#घोषणा HTT_TX_WBM_COMP_INFO1_ACK_RSSI		GENMASK(31, 24)

काष्ठा htt_tx_wbm_completion अणु
	u32 info0;
	u32 info1;
	u32 info2;
	u32 info3;
पूर्ण __packed;

क्रमागत htt_h2t_msg_type अणु
	HTT_H2T_MSG_TYPE_VERSION_REQ		= 0,
	HTT_H2T_MSG_TYPE_SRING_SETUP		= 0xb,
	HTT_H2T_MSG_TYPE_RX_RING_SELECTION_CFG	= 0xc,
	HTT_H2T_MSG_TYPE_EXT_STATS_CFG		= 0x10,
	HTT_H2T_MSG_TYPE_PPDU_STATS_CFG		= 0x11,
पूर्ण;

#घोषणा HTT_VER_REQ_INFO_MSG_ID		GENMASK(7, 0)

काष्ठा htt_ver_req_cmd अणु
	u32 ver_reg_info;
पूर्ण __packed;

क्रमागत htt_srng_ring_type अणु
	HTT_HW_TO_SW_RING,
	HTT_SW_TO_HW_RING,
	HTT_SW_TO_SW_RING,
पूर्ण;

क्रमागत htt_srng_ring_id अणु
	HTT_RXDMA_HOST_BUF_RING,
	HTT_RXDMA_MONITOR_STATUS_RING,
	HTT_RXDMA_MONITOR_BUF_RING,
	HTT_RXDMA_MONITOR_DESC_RING,
	HTT_RXDMA_MONITOR_DEST_RING,
	HTT_HOST1_TO_FW_RXBUF_RING,
	HTT_HOST2_TO_FW_RXBUF_RING,
	HTT_RXDMA_NON_MONITOR_DEST_RING,
पूर्ण;

/* host -> target  HTT_SRING_SETUP message
 *
 * After target is booted up, Host can send SRING setup message क्रम
 * each host facing LMAC SRING. Target setups up HW रेजिस्टरs based
 * on setup message and confirms back to Host अगर response_required is set.
 * Host should रुको क्रम confirmation message beक्रमe sending new SRING
 * setup message
 *
 * The message would appear as follows:
 *
 * |31            24|23    20|19|18 16|15|14          8|7                0|
 * |--------------- +-----------------+----------------+------------------|
 * |    ring_type   |      ring_id    |    pdev_id     |     msg_type     |
 * |----------------------------------------------------------------------|
 * |                          ring_base_addr_lo                           |
 * |----------------------------------------------------------------------|
 * |                         ring_base_addr_hi                            |
 * |----------------------------------------------------------------------|
 * |ring_misc_cfg_flag|ring_entry_size|            ring_size              |
 * |----------------------------------------------------------------------|
 * |                         ring_head_offset32_remote_addr_lo            |
 * |----------------------------------------------------------------------|
 * |                         ring_head_offset32_remote_addr_hi            |
 * |----------------------------------------------------------------------|
 * |                         ring_tail_offset32_remote_addr_lo            |
 * |----------------------------------------------------------------------|
 * |                         ring_tail_offset32_remote_addr_hi            |
 * |----------------------------------------------------------------------|
 * |                          ring_msi_addr_lo                            |
 * |----------------------------------------------------------------------|
 * |                          ring_msi_addr_hi                            |
 * |----------------------------------------------------------------------|
 * |                          ring_msi_data                               |
 * |----------------------------------------------------------------------|
 * |         पूर्णांकr_समयr_th            |IM|      पूर्णांकr_batch_counter_th     |
 * |----------------------------------------------------------------------|
 * |          reserved        |RR|PTCF|        पूर्णांकr_low_threshold         |
 * |----------------------------------------------------------------------|
 * Where
 *     IM = sw_पूर्णांकr_mode
 *     RR = response_required
 *     PTCF = prefetch_समयr_cfg
 *
 * The message is पूर्णांकerpreted as follows:
 * dword0  - b'0:7   - msg_type: This will be set to
 *                     HTT_H2T_MSG_TYPE_SRING_SETUP
 *           b'8:15  - pdev_id:
 *                     0 (क्रम rings at SOC/UMAC level),
 *                     1/2/3 mac id (क्रम rings at LMAC level)
 *           b'16:23 - ring_id: identअगरy which ring is to setup,
 *                     more details can be got from क्रमागत htt_srng_ring_id
 *           b'24:31 - ring_type: identअगरy type of host rings,
 *                     more details can be got from क्रमागत htt_srng_ring_type
 * dword1  - b'0:31  - ring_base_addr_lo: Lower 32bits of ring base address
 * dword2  - b'0:31  - ring_base_addr_hi: Upper 32bits of ring base address
 * dword3  - b'0:15  - ring_size: size of the ring in unit of 4-bytes words
 *           b'16:23 - ring_entry_size: Size of each entry in 4-byte word units
 *           b'24:31 - ring_misc_cfg_flag: Valid only क्रम HW_TO_SW_RING and
 *                     SW_TO_HW_RING.
 *                     Refer to HTT_SRING_SETUP_RING_MISC_CFG_RING defs.
 * dword4  - b'0:31  - ring_head_off32_remote_addr_lo:
 *                     Lower 32 bits of memory address of the remote variable
 *                     storing the 4-byte word offset that identअगरies the head
 *                     element within the ring.
 *                     (The head offset variable has type u32.)
 *                     Valid क्रम HW_TO_SW and SW_TO_SW rings.
 * dword5  - b'0:31  - ring_head_off32_remote_addr_hi:
 *                     Upper 32 bits of memory address of the remote variable
 *                     storing the 4-byte word offset that identअगरies the head
 *                     element within the ring.
 *                     (The head offset variable has type u32.)
 *                     Valid क्रम HW_TO_SW and SW_TO_SW rings.
 * dword6  - b'0:31  - ring_tail_off32_remote_addr_lo:
 *                     Lower 32 bits of memory address of the remote variable
 *                     storing the 4-byte word offset that identअगरies the tail
 *                     element within the ring.
 *                     (The tail offset variable has type u32.)
 *                     Valid क्रम HW_TO_SW and SW_TO_SW rings.
 * dword7  - b'0:31  - ring_tail_off32_remote_addr_hi:
 *                     Upper 32 bits of memory address of the remote variable
 *                     storing the 4-byte word offset that identअगरies the tail
 *                     element within the ring.
 *                     (The tail offset variable has type u32.)
 *                     Valid क्रम HW_TO_SW and SW_TO_SW rings.
 * dword8  - b'0:31  - ring_msi_addr_lo: Lower 32bits of MSI cfg address
 *                     valid only क्रम HW_TO_SW_RING and SW_TO_HW_RING
 * dword9  - b'0:31  - ring_msi_addr_hi: Upper 32bits of MSI cfg address
 *                     valid only क्रम HW_TO_SW_RING and SW_TO_HW_RING
 * dword10 - b'0:31  - ring_msi_data: MSI data
 *                     Refer to HTT_SRING_SETUP_RING_MSC_CFG_xxx defs
 *                     valid only क्रम HW_TO_SW_RING and SW_TO_HW_RING
 * dword11 - b'0:14  - पूर्णांकr_batch_counter_th:
 *                     batch counter threshold is in units of 4-byte words.
 *                     HW पूर्णांकernally मुख्यtains and increments batch count.
 *                     (see SRING spec क्रम detail description).
 *                     When batch count reaches threshold value, an पूर्णांकerrupt
 *                     is generated by HW.
 *           b'15    - sw_पूर्णांकr_mode:
 *                     This configuration shall be अटल.
 *                     Only programmed at घातer up.
 *                     0: generate pulse style sw पूर्णांकerrupts
 *                     1: generate level style sw पूर्णांकerrupts
 *           b'16:31 - पूर्णांकr_समयr_th:
 *                     The समयr init value when समयr is idle or is
 *                     initialized to start करोwncounting.
 *                     In 8us units (to cover a range of 0 to 524 ms)
 * dword12 - b'0:15  - पूर्णांकr_low_threshold:
 *                     Used only by Consumer ring to generate ring_sw_पूर्णांक_p.
 *                     Ring entries low threshold water mark, that is used
 *                     in combination with the पूर्णांकerrupt समयr as well as
 *                     the clearing of the level पूर्णांकerrupt.
 *           b'16:18 - prefetch_समयr_cfg:
 *                     Used only by Consumer ring to set समयr mode to
 *                     support Application prefetch handling.
 *                     The बाह्यal tail offset/poपूर्णांकer will be updated
 *                     at following पूर्णांकervals:
 *                     3'b000: (Prefetch feature disabled; used only क्रम debug)
 *                     3'b001: 1 usec
 *                     3'b010: 4 usec
 *                     3'b011: 8 usec (शेष)
 *                     3'b100: 16 usec
 *                     Others: Reserverd
 *           b'19    - response_required:
 *                     Host needs HTT_T2H_MSG_TYPE_SRING_SETUP_DONE as response
 *           b'20:31 - reserved:  reserved क्रम future use
 */

#घोषणा HTT_SRNG_SETUP_CMD_INFO0_MSG_TYPE	GENMASK(7, 0)
#घोषणा HTT_SRNG_SETUP_CMD_INFO0_PDEV_ID	GENMASK(15, 8)
#घोषणा HTT_SRNG_SETUP_CMD_INFO0_RING_ID	GENMASK(23, 16)
#घोषणा HTT_SRNG_SETUP_CMD_INFO0_RING_TYPE	GENMASK(31, 24)

#घोषणा HTT_SRNG_SETUP_CMD_INFO1_RING_SIZE			GENMASK(15, 0)
#घोषणा HTT_SRNG_SETUP_CMD_INFO1_RING_ENTRY_SIZE		GENMASK(23, 16)
#घोषणा HTT_SRNG_SETUP_CMD_INFO1_RING_LOOP_CNT_DIS		BIT(25)
#घोषणा HTT_SRNG_SETUP_CMD_INFO1_RING_FLAGS_MSI_SWAP		BIT(27)
#घोषणा HTT_SRNG_SETUP_CMD_INFO1_RING_FLAGS_HOST_FW_SWAP	BIT(28)
#घोषणा HTT_SRNG_SETUP_CMD_INFO1_RING_FLAGS_TLV_SWAP		BIT(29)

#घोषणा HTT_SRNG_SETUP_CMD_INTR_INFO_BATCH_COUNTER_THRESH	GENMASK(14, 0)
#घोषणा HTT_SRNG_SETUP_CMD_INTR_INFO_SW_INTR_MODE		BIT(15)
#घोषणा HTT_SRNG_SETUP_CMD_INTR_INFO_INTR_TIMER_THRESH		GENMASK(31, 16)

#घोषणा HTT_SRNG_SETUP_CMD_INFO2_INTR_LOW_THRESH	GENMASK(15, 0)
#घोषणा HTT_SRNG_SETUP_CMD_INFO2_PRE_FETCH_TIMER_CFG	BIT(16)
#घोषणा HTT_SRNG_SETUP_CMD_INFO2_RESPONSE_REQUIRED	BIT(19)

काष्ठा htt_srng_setup_cmd अणु
	u32 info0;
	u32 ring_base_addr_lo;
	u32 ring_base_addr_hi;
	u32 info1;
	u32 ring_head_off32_remote_addr_lo;
	u32 ring_head_off32_remote_addr_hi;
	u32 ring_tail_off32_remote_addr_lo;
	u32 ring_tail_off32_remote_addr_hi;
	u32 ring_msi_addr_lo;
	u32 ring_msi_addr_hi;
	u32 msi_data;
	u32 पूर्णांकr_info;
	u32 info2;
पूर्ण __packed;

/* host -> target FW  PPDU_STATS config message
 *
 * @details
 * The following field definitions describe the क्रमmat of the HTT host
 * to target FW क्रम PPDU_STATS_CFG msg.
 * The message allows the host to configure the PPDU_STATS_IND messages
 * produced by the target.
 *
 * |31          24|23          16|15           8|7            0|
 * |-----------------------------------------------------------|
 * |    REQ bit mask             |   pdev_mask  |   msg type   |
 * |-----------------------------------------------------------|
 * Header fields:
 *  - MSG_TYPE
 *    Bits 7:0
 *    Purpose: identअगरies this is a req to configure ppdu_stats_ind from target
 *    Value: 0x11
 *  - PDEV_MASK
 *    Bits 8:15
 *    Purpose: identअगरies which pdevs this PPDU stats configuration applies to
 *    Value: This is a overloaded field, refer to usage and पूर्णांकerpretation of
 *           PDEV in पूर्णांकerface करोcument.
 *           Bit   8    :  Reserved क्रम SOC stats
 *           Bit 9 - 15 :  Indicates PDEV_MASK in DBDC
 *                         Indicates MACID_MASK in DBS
 *  - REQ_TLV_BIT_MASK
 *    Bits 16:31
 *    Purpose: each set bit indicates the corresponding PPDU stats TLV type
 *        needs to be included in the target's PPDU_STATS_IND messages.
 *    Value: refer htt_ppdu_stats_tlv_tag_t <<<???
 *
 */

काष्ठा htt_ppdu_stats_cfg_cmd अणु
	u32 msg;
पूर्ण __packed;

#घोषणा HTT_PPDU_STATS_CFG_MSG_TYPE		GENMASK(7, 0)
#घोषणा HTT_PPDU_STATS_CFG_PDEV_ID		GENMASK(15, 8)
#घोषणा HTT_PPDU_STATS_CFG_TLV_TYPE_BITMASK	GENMASK(31, 16)

क्रमागत htt_ppdu_stats_tag_type अणु
	HTT_PPDU_STATS_TAG_COMMON,
	HTT_PPDU_STATS_TAG_USR_COMMON,
	HTT_PPDU_STATS_TAG_USR_RATE,
	HTT_PPDU_STATS_TAG_USR_MPDU_ENQ_BITMAP_64,
	HTT_PPDU_STATS_TAG_USR_MPDU_ENQ_BITMAP_256,
	HTT_PPDU_STATS_TAG_SCH_CMD_STATUS,
	HTT_PPDU_STATS_TAG_USR_COMPLTN_COMMON,
	HTT_PPDU_STATS_TAG_USR_COMPLTN_BA_BITMAP_64,
	HTT_PPDU_STATS_TAG_USR_COMPLTN_BA_BITMAP_256,
	HTT_PPDU_STATS_TAG_USR_COMPLTN_ACK_BA_STATUS,
	HTT_PPDU_STATS_TAG_USR_COMPLTN_FLUSH,
	HTT_PPDU_STATS_TAG_USR_COMMON_ARRAY,
	HTT_PPDU_STATS_TAG_INFO,
	HTT_PPDU_STATS_TAG_TX_MGMTCTRL_PAYLOAD,

	/* New TLV's are added above to this line */
	HTT_PPDU_STATS_TAG_MAX,
पूर्ण;

#घोषणा HTT_PPDU_STATS_TAG_DEFAULT (BIT(HTT_PPDU_STATS_TAG_COMMON) \
				   | BIT(HTT_PPDU_STATS_TAG_USR_COMMON) \
				   | BIT(HTT_PPDU_STATS_TAG_USR_RATE) \
				   | BIT(HTT_PPDU_STATS_TAG_SCH_CMD_STATUS) \
				   | BIT(HTT_PPDU_STATS_TAG_USR_COMPLTN_COMMON) \
				   | BIT(HTT_PPDU_STATS_TAG_USR_COMPLTN_ACK_BA_STATUS) \
				   | BIT(HTT_PPDU_STATS_TAG_USR_COMPLTN_FLUSH) \
				   | BIT(HTT_PPDU_STATS_TAG_USR_COMMON_ARRAY))

#घोषणा HTT_PPDU_STATS_TAG_PKTLOG  (BIT(HTT_PPDU_STATS_TAG_USR_MPDU_ENQ_BITMAP_64) | \
				    BIT(HTT_PPDU_STATS_TAG_USR_MPDU_ENQ_BITMAP_256) | \
				    BIT(HTT_PPDU_STATS_TAG_USR_COMPLTN_BA_BITMAP_64) | \
				    BIT(HTT_PPDU_STATS_TAG_USR_COMPLTN_BA_BITMAP_256) | \
				    BIT(HTT_PPDU_STATS_TAG_INFO) | \
				    BIT(HTT_PPDU_STATS_TAG_TX_MGMTCTRL_PAYLOAD) | \
				    HTT_PPDU_STATS_TAG_DEFAULT)

/* HTT_H2T_MSG_TYPE_RX_RING_SELECTION_CFG Message
 *
 * details:
 *    HTT_H2T_MSG_TYPE_RX_RING_SELECTION_CFG message is sent by host to
 *    configure RXDMA rings.
 *    The configuration is per ring based and includes both packet subtypes
 *    and PPDU/MPDU TLVs.
 *
 *    The message would appear as follows:
 *
 *    |31       26|25|24|23            16|15             8|7             0|
 *    |-----------------+----------------+----------------+---------------|
 *    |   rsvd1   |PS|SS|     ring_id    |     pdev_id    |    msg_type   |
 *    |-------------------------------------------------------------------|
 *    |              rsvd2               |           ring_buffer_size     |
 *    |-------------------------------------------------------------------|
 *    |                        packet_type_enable_flags_0                 |
 *    |-------------------------------------------------------------------|
 *    |                        packet_type_enable_flags_1                 |
 *    |-------------------------------------------------------------------|
 *    |                        packet_type_enable_flags_2                 |
 *    |-------------------------------------------------------------------|
 *    |                        packet_type_enable_flags_3                 |
 *    |-------------------------------------------------------------------|
 *    |                         tlv_filter_in_flags                       |
 *    |-------------------------------------------------------------------|
 * Where:
 *     PS = pkt_swap
 *     SS = status_swap
 * The message is पूर्णांकerpreted as follows:
 * dword0 - b'0:7   - msg_type: This will be set to
 *                    HTT_H2T_MSG_TYPE_RX_RING_SELECTION_CFG
 *          b'8:15  - pdev_id:
 *                    0 (क्रम rings at SOC/UMAC level),
 *                    1/2/3 mac id (क्रम rings at LMAC level)
 *          b'16:23 - ring_id : Identअगरy the ring to configure.
 *                    More details can be got from क्रमागत htt_srng_ring_id
 *          b'24    - status_swap: 1 is to swap status TLV
 *          b'25    - pkt_swap:  1 is to swap packet TLV
 *          b'26:31 - rsvd1:  reserved क्रम future use
 * dword1 - b'0:16  - ring_buffer_size: size of bufferes referenced by rx ring,
 *                    in byte units.
 *                    Valid only क्रम HW_TO_SW_RING and SW_TO_HW_RING
 *        - b'16:31 - rsvd2: Reserved क्रम future use
 * dword2 - b'0:31  - packet_type_enable_flags_0:
 *                    Enable MGMT packet from 0b0000 to 0b1001
 *                    bits from low to high: FP, MD, MO - 3 bits
 *                        FP: Filter_Pass
 *                        MD: Monitor_Direct
 *                        MO: Monitor_Other
 *                    10 mgmt subtypes * 3 bits -> 30 bits
 *                    Refer to PKT_TYPE_ENABLE_FLAG0_xxx_MGMT_xxx defs
 * dword3 - b'0:31  - packet_type_enable_flags_1:
 *                    Enable MGMT packet from 0b1010 to 0b1111
 *                    bits from low to high: FP, MD, MO - 3 bits
 *                    Refer to PKT_TYPE_ENABLE_FLAG1_xxx_MGMT_xxx defs
 * dword4 - b'0:31 -  packet_type_enable_flags_2:
 *                    Enable CTRL packet from 0b0000 to 0b1001
 *                    bits from low to high: FP, MD, MO - 3 bits
 *                    Refer to PKT_TYPE_ENABLE_FLAG2_xxx_CTRL_xxx defs
 * dword5 - b'0:31  - packet_type_enable_flags_3:
 *                    Enable CTRL packet from 0b1010 to 0b1111,
 *                    MCAST_DATA, UCAST_DATA, शून्य_DATA
 *                    bits from low to high: FP, MD, MO - 3 bits
 *                    Refer to PKT_TYPE_ENABLE_FLAG3_xxx_CTRL_xxx defs
 * dword6 - b'0:31 -  tlv_filter_in_flags:
 *                    Filter in Attention/MPDU/PPDU/Header/User tlvs
 *                    Refer to CFG_TLV_FILTER_IN_FLAG defs
 */

#घोषणा HTT_RX_RING_SELECTION_CFG_CMD_INFO0_MSG_TYPE	GENMASK(7, 0)
#घोषणा HTT_RX_RING_SELECTION_CFG_CMD_INFO0_PDEV_ID	GENMASK(15, 8)
#घोषणा HTT_RX_RING_SELECTION_CFG_CMD_INFO0_RING_ID	GENMASK(23, 16)
#घोषणा HTT_RX_RING_SELECTION_CFG_CMD_INFO0_SS		BIT(24)
#घोषणा HTT_RX_RING_SELECTION_CFG_CMD_INFO0_PS		BIT(25)

#घोषणा HTT_RX_RING_SELECTION_CFG_CMD_INFO1_BUF_SIZE	GENMASK(15, 0)

क्रमागत htt_rx_filter_tlv_flags अणु
	HTT_RX_FILTER_TLV_FLAGS_MPDU_START		= BIT(0),
	HTT_RX_FILTER_TLV_FLAGS_MSDU_START		= BIT(1),
	HTT_RX_FILTER_TLV_FLAGS_RX_PACKET		= BIT(2),
	HTT_RX_FILTER_TLV_FLAGS_MSDU_END		= BIT(3),
	HTT_RX_FILTER_TLV_FLAGS_MPDU_END		= BIT(4),
	HTT_RX_FILTER_TLV_FLAGS_PACKET_HEADER		= BIT(5),
	HTT_RX_FILTER_TLV_FLAGS_PER_MSDU_HEADER		= BIT(6),
	HTT_RX_FILTER_TLV_FLAGS_ATTENTION		= BIT(7),
	HTT_RX_FILTER_TLV_FLAGS_PPDU_START		= BIT(8),
	HTT_RX_FILTER_TLV_FLAGS_PPDU_END		= BIT(9),
	HTT_RX_FILTER_TLV_FLAGS_PPDU_END_USER_STATS	= BIT(10),
	HTT_RX_FILTER_TLV_FLAGS_PPDU_END_USER_STATS_EXT	= BIT(11),
	HTT_RX_FILTER_TLV_FLAGS_PPDU_END_STATUS_DONE	= BIT(12),
पूर्ण;

क्रमागत htt_rx_mgmt_pkt_filter_tlv_flags0 अणु
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_ASSOC_REQ		= BIT(0),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_ASSOC_REQ		= BIT(1),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_ASSOC_REQ		= BIT(2),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_ASSOC_RESP		= BIT(3),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_ASSOC_RESP		= BIT(4),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_ASSOC_RESP		= BIT(5),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_REASSOC_REQ	= BIT(6),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_REASSOC_REQ	= BIT(7),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_REASSOC_REQ	= BIT(8),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_REASSOC_RESP	= BIT(9),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_REASSOC_RESP	= BIT(10),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_REASSOC_RESP	= BIT(11),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_REQ		= BIT(12),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_REQ		= BIT(13),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_REQ		= BIT(14),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_RESP		= BIT(15),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_RESP		= BIT(16),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_RESP		= BIT(17),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_TIMING_ADV	= BIT(18),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_TIMING_ADV	= BIT(19),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_TIMING_ADV	= BIT(20),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_RESERVED_7		= BIT(21),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_RESERVED_7		= BIT(22),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_RESERVED_7		= BIT(23),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_BEACON		= BIT(24),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_BEACON		= BIT(25),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_BEACON		= BIT(26),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_ATIM		= BIT(27),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_ATIM		= BIT(28),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_ATIM		= BIT(29),
पूर्ण;

क्रमागत htt_rx_mgmt_pkt_filter_tlv_flags1 अणु
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS1_DISASSOC		= BIT(0),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS1_DISASSOC		= BIT(1),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS1_DISASSOC		= BIT(2),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS1_AUTH		= BIT(3),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS1_AUTH		= BIT(4),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS1_AUTH		= BIT(5),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS1_DEAUTH		= BIT(6),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS1_DEAUTH		= BIT(7),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS1_DEAUTH		= BIT(8),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS1_ACTION		= BIT(9),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS1_ACTION		= BIT(10),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS1_ACTION		= BIT(11),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS1_ACTION_NOACK	= BIT(12),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS1_ACTION_NOACK	= BIT(13),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS1_ACTION_NOACK	= BIT(14),
	HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS1_RESERVED_15	= BIT(15),
	HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS1_RESERVED_15	= BIT(16),
	HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS1_RESERVED_15	= BIT(17),
पूर्ण;

क्रमागत htt_rx_ctrl_pkt_filter_tlv_flags2 अणु
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_1	= BIT(0),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_1	= BIT(1),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_1	= BIT(2),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_2	= BIT(3),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_2	= BIT(4),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_2	= BIT(5),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_TRIGGER	= BIT(6),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_TRIGGER	= BIT(7),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_TRIGGER	= BIT(8),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_4	= BIT(9),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_4	= BIT(10),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_4	= BIT(11),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_BF_REP_POLL	= BIT(12),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_BF_REP_POLL	= BIT(13),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_BF_REP_POLL	= BIT(14),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_VHT_NDP	= BIT(15),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_VHT_NDP	= BIT(16),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_VHT_NDP	= BIT(17),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_FRAME_EXT	= BIT(18),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_FRAME_EXT	= BIT(19),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_FRAME_EXT	= BIT(20),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_WRAPPER	= BIT(21),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_WRAPPER	= BIT(22),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_WRAPPER	= BIT(23),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_BAR		= BIT(24),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS2_BAR		= BIT(25),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_BAR		= BIT(26),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_BA			= BIT(27),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS2_BA			= BIT(28),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_BA			= BIT(29),
पूर्ण;

क्रमागत htt_rx_ctrl_pkt_filter_tlv_flags3 अणु
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS3_PSPOLL		= BIT(0),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS3_PSPOLL		= BIT(1),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS3_PSPOLL		= BIT(2),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS3_RTS		= BIT(3),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS3_RTS		= BIT(4),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS3_RTS		= BIT(5),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS3_CTS		= BIT(6),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS3_CTS		= BIT(7),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS3_CTS		= BIT(8),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS3_ACK		= BIT(9),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS3_ACK		= BIT(10),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS3_ACK		= BIT(11),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS3_CFEND		= BIT(12),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS3_CFEND		= BIT(13),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS3_CFEND		= BIT(14),
	HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS3_CFEND_ACK		= BIT(15),
	HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS3_CFEND_ACK		= BIT(16),
	HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS3_CFEND_ACK		= BIT(17),
पूर्ण;

क्रमागत htt_rx_data_pkt_filter_tlv_flasg3 अणु
	HTT_RX_FP_DATA_PKT_FILTER_TLV_FLASG3_MCAST	= BIT(18),
	HTT_RX_MD_DATA_PKT_FILTER_TLV_FLASG3_MCAST	= BIT(19),
	HTT_RX_MO_DATA_PKT_FILTER_TLV_FLASG3_MCAST	= BIT(20),
	HTT_RX_FP_DATA_PKT_FILTER_TLV_FLASG3_UCAST	= BIT(21),
	HTT_RX_MD_DATA_PKT_FILTER_TLV_FLASG3_UCAST	= BIT(22),
	HTT_RX_MO_DATA_PKT_FILTER_TLV_FLASG3_UCAST	= BIT(23),
	HTT_RX_FP_DATA_PKT_FILTER_TLV_FLASG3_शून्य_DATA	= BIT(24),
	HTT_RX_MD_DATA_PKT_FILTER_TLV_FLASG3_शून्य_DATA	= BIT(25),
	HTT_RX_MO_DATA_PKT_FILTER_TLV_FLASG3_शून्य_DATA	= BIT(26),
पूर्ण;

#घोषणा HTT_RX_FP_MGMT_FILTER_FLAGS0 \
	(HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_ASSOC_REQ \
	| HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_ASSOC_RESP \
	| HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_REASSOC_REQ \
	| HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_REASSOC_RESP \
	| HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_REQ \
	| HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_RESP \
	| HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_TIMING_ADV \
	| HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_BEACON \
	| HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_ATIM)

#घोषणा HTT_RX_MD_MGMT_FILTER_FLAGS0 \
	(HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_ASSOC_REQ \
	| HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_ASSOC_RESP \
	| HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_REASSOC_REQ \
	| HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_REASSOC_RESP \
	| HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_REQ \
	| HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_RESP \
	| HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_TIMING_ADV \
	| HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_BEACON \
	| HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS0_ATIM)

#घोषणा HTT_RX_MO_MGMT_FILTER_FLAGS0 \
	(HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_ASSOC_REQ \
	| HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_ASSOC_RESP \
	| HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_REASSOC_REQ \
	| HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_REASSOC_RESP \
	| HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_REQ \
	| HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_RESP \
	| HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_PROBE_TIMING_ADV \
	| HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_BEACON \
	| HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_ATIM)

#घोषणा HTT_RX_FP_MGMT_FILTER_FLAGS1 (HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS1_DISASSOC \
				     | HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS1_AUTH \
				     | HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS1_DEAUTH \
				     | HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS1_ACTION \
				     | HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS1_ACTION_NOACK)

#घोषणा HTT_RX_MD_MGMT_FILTER_FLAGS1 (HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS1_DISASSOC \
				     | HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS1_AUTH \
				     | HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS1_DEAUTH \
				     | HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS1_ACTION \
				     | HTT_RX_MD_MGMT_PKT_FILTER_TLV_FLAGS1_ACTION_NOACK)

#घोषणा HTT_RX_MO_MGMT_FILTER_FLAGS1 (HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS1_DISASSOC \
				     | HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS1_AUTH \
				     | HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS1_DEAUTH \
				     | HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS1_ACTION \
				     | HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS1_ACTION_NOACK)

#घोषणा HTT_RX_FP_CTRL_FILTER_FLASG2 (HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_WRAPPER \
				     | HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_BAR \
				     | HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_BA)

#घोषणा HTT_RX_MD_CTRL_FILTER_FLASG2 (HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_WRAPPER \
				     | HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS2_BAR \
				     | HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS2_BA)

#घोषणा HTT_RX_MO_CTRL_FILTER_FLASG2 (HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_WRAPPER \
				     | HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_BAR \
				     | HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_BA)

#घोषणा HTT_RX_FP_CTRL_FILTER_FLASG3 (HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS3_PSPOLL \
				     | HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS3_RTS \
				     | HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS3_CTS \
				     | HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS3_ACK \
				     | HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS3_CFEND \
				     | HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS3_CFEND_ACK)

#घोषणा HTT_RX_MD_CTRL_FILTER_FLASG3 (HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS3_PSPOLL \
				     | HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS3_RTS \
				     | HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS3_CTS \
				     | HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS3_ACK \
				     | HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS3_CFEND \
				     | HTT_RX_MD_CTRL_PKT_FILTER_TLV_FLAGS3_CFEND_ACK)

#घोषणा HTT_RX_MO_CTRL_FILTER_FLASG3 (HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS3_PSPOLL \
				     | HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS3_RTS \
				     | HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS3_CTS \
				     | HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS3_ACK \
				     | HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS3_CFEND \
				     | HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS3_CFEND_ACK)

#घोषणा HTT_RX_FP_DATA_FILTER_FLASG3 (HTT_RX_FP_DATA_PKT_FILTER_TLV_FLASG3_MCAST \
				     | HTT_RX_FP_DATA_PKT_FILTER_TLV_FLASG3_UCAST \
				     | HTT_RX_FP_DATA_PKT_FILTER_TLV_FLASG3_शून्य_DATA)

#घोषणा HTT_RX_MD_DATA_FILTER_FLASG3 (HTT_RX_MD_DATA_PKT_FILTER_TLV_FLASG3_MCAST \
				     | HTT_RX_MD_DATA_PKT_FILTER_TLV_FLASG3_UCAST \
				     | HTT_RX_MD_DATA_PKT_FILTER_TLV_FLASG3_शून्य_DATA)

#घोषणा HTT_RX_MO_DATA_FILTER_FLASG3 (HTT_RX_MO_DATA_PKT_FILTER_TLV_FLASG3_MCAST \
				     | HTT_RX_MO_DATA_PKT_FILTER_TLV_FLASG3_UCAST \
				     | HTT_RX_MO_DATA_PKT_FILTER_TLV_FLASG3_शून्य_DATA)

#घोषणा HTT_RX_MON_FP_MGMT_FILTER_FLAGS0 \
		(HTT_RX_FP_MGMT_FILTER_FLAGS0 | \
		HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS0_RESERVED_7)

#घोषणा HTT_RX_MON_MO_MGMT_FILTER_FLAGS0 \
		(HTT_RX_MO_MGMT_FILTER_FLAGS0 | \
		HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS0_RESERVED_7)

#घोषणा HTT_RX_MON_FP_MGMT_FILTER_FLAGS1 \
		(HTT_RX_FP_MGMT_FILTER_FLAGS1 | \
		HTT_RX_FP_MGMT_PKT_FILTER_TLV_FLAGS1_RESERVED_15)

#घोषणा HTT_RX_MON_MO_MGMT_FILTER_FLAGS1 \
		(HTT_RX_MO_MGMT_FILTER_FLAGS1 | \
		HTT_RX_MO_MGMT_PKT_FILTER_TLV_FLAGS1_RESERVED_15)

#घोषणा HTT_RX_MON_FP_CTRL_FILTER_FLASG2 \
		(HTT_RX_FP_CTRL_FILTER_FLASG2 | \
		HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_1 | \
		HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_2 | \
		HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_TRIGGER | \
		HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_4 | \
		HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_BF_REP_POLL | \
		HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_VHT_NDP | \
		HTT_RX_FP_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_FRAME_EXT)

#घोषणा HTT_RX_MON_MO_CTRL_FILTER_FLASG2 \
		(HTT_RX_MO_CTRL_FILTER_FLASG2 | \
		HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_1 | \
		HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_2 | \
		HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_TRIGGER | \
		HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_RESERVED_4 | \
		HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_BF_REP_POLL | \
		HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_VHT_NDP | \
		HTT_RX_MO_CTRL_PKT_FILTER_TLV_FLAGS2_CTRL_FRAME_EXT)

#घोषणा HTT_RX_MON_FP_CTRL_FILTER_FLASG3 HTT_RX_FP_CTRL_FILTER_FLASG3

#घोषणा HTT_RX_MON_MO_CTRL_FILTER_FLASG3 HTT_RX_MO_CTRL_FILTER_FLASG3

#घोषणा HTT_RX_MON_FP_DATA_FILTER_FLASG3 HTT_RX_FP_DATA_FILTER_FLASG3

#घोषणा HTT_RX_MON_MO_DATA_FILTER_FLASG3 HTT_RX_MO_DATA_FILTER_FLASG3

#घोषणा HTT_RX_MON_FILTER_TLV_FLAGS \
		(HTT_RX_FILTER_TLV_FLAGS_MPDU_START | \
		HTT_RX_FILTER_TLV_FLAGS_PPDU_START | \
		HTT_RX_FILTER_TLV_FLAGS_PPDU_END | \
		HTT_RX_FILTER_TLV_FLAGS_PPDU_END_USER_STATS | \
		HTT_RX_FILTER_TLV_FLAGS_PPDU_END_USER_STATS_EXT | \
		HTT_RX_FILTER_TLV_FLAGS_PPDU_END_STATUS_DONE)

#घोषणा HTT_RX_MON_FILTER_TLV_FLAGS_MON_STATUS_RING \
		(HTT_RX_FILTER_TLV_FLAGS_MPDU_START | \
		HTT_RX_FILTER_TLV_FLAGS_PPDU_START | \
		HTT_RX_FILTER_TLV_FLAGS_PPDU_END | \
		HTT_RX_FILTER_TLV_FLAGS_PPDU_END_USER_STATS | \
		HTT_RX_FILTER_TLV_FLAGS_PPDU_END_USER_STATS_EXT | \
		HTT_RX_FILTER_TLV_FLAGS_PPDU_END_STATUS_DONE)

#घोषणा HTT_RX_MON_FILTER_TLV_FLAGS_MON_BUF_RING \
		(HTT_RX_FILTER_TLV_FLAGS_MPDU_START | \
		HTT_RX_FILTER_TLV_FLAGS_MSDU_START | \
		HTT_RX_FILTER_TLV_FLAGS_RX_PACKET | \
		HTT_RX_FILTER_TLV_FLAGS_MSDU_END | \
		HTT_RX_FILTER_TLV_FLAGS_MPDU_END | \
		HTT_RX_FILTER_TLV_FLAGS_PACKET_HEADER | \
		HTT_RX_FILTER_TLV_FLAGS_PER_MSDU_HEADER | \
		HTT_RX_FILTER_TLV_FLAGS_ATTENTION)

काष्ठा htt_rx_ring_selection_cfg_cmd अणु
	u32 info0;
	u32 info1;
	u32 pkt_type_en_flags0;
	u32 pkt_type_en_flags1;
	u32 pkt_type_en_flags2;
	u32 pkt_type_en_flags3;
	u32 rx_filter_tlv;
पूर्ण __packed;

काष्ठा htt_rx_ring_tlv_filter अणु
	u32 rx_filter; /* see htt_rx_filter_tlv_flags */
	u32 pkt_filter_flags0; /* MGMT */
	u32 pkt_filter_flags1; /* MGMT */
	u32 pkt_filter_flags2; /* CTRL */
	u32 pkt_filter_flags3; /* DATA */
पूर्ण;

/* HTT message target->host */

क्रमागत htt_t2h_msg_type अणु
	HTT_T2H_MSG_TYPE_VERSION_CONF,
	HTT_T2H_MSG_TYPE_PEER_MAP	= 0x3,
	HTT_T2H_MSG_TYPE_PEER_UNMAP	= 0x4,
	HTT_T2H_MSG_TYPE_RX_ADDBA	= 0x5,
	HTT_T2H_MSG_TYPE_PKTLOG		= 0x8,
	HTT_T2H_MSG_TYPE_SEC_IND	= 0xb,
	HTT_T2H_MSG_TYPE_PEER_MAP2	= 0x1e,
	HTT_T2H_MSG_TYPE_PEER_UNMAP2	= 0x1f,
	HTT_T2H_MSG_TYPE_PPDU_STATS_IND = 0x1d,
	HTT_T2H_MSG_TYPE_EXT_STATS_CONF = 0x1c,
	HTT_T2H_MSG_TYPE_BKPRESSURE_EVENT_IND = 0x24,
पूर्ण;

#घोषणा HTT_TARGET_VERSION_MAJOR 3

#घोषणा HTT_T2H_MSG_TYPE		GENMASK(7, 0)
#घोषणा HTT_T2H_VERSION_CONF_MINOR	GENMASK(15, 8)
#घोषणा HTT_T2H_VERSION_CONF_MAJOR	GENMASK(23, 16)

काष्ठा htt_t2h_version_conf_msg अणु
	u32 version;
पूर्ण __packed;

#घोषणा HTT_T2H_PEER_MAP_INFO_VDEV_ID	GENMASK(15, 8)
#घोषणा HTT_T2H_PEER_MAP_INFO_PEER_ID	GENMASK(31, 16)
#घोषणा HTT_T2H_PEER_MAP_INFO1_MAC_ADDR_H16	GENMASK(15, 0)
#घोषणा HTT_T2H_PEER_MAP_INFO1_HW_PEER_ID	GENMASK(31, 16)
#घोषणा HTT_T2H_PEER_MAP_INFO2_AST_HASH_VAL	GENMASK(15, 0)
#घोषणा HTT_T2H_PEER_MAP_INFO2_NEXT_HOP_M	BIT(16)
#घोषणा HTT_T2H_PEER_MAP_INFO2_NEXT_HOP_S	16

काष्ठा htt_t2h_peer_map_event अणु
	u32 info;
	u32 mac_addr_l32;
	u32 info1;
	u32 info2;
पूर्ण __packed;

#घोषणा HTT_T2H_PEER_UNMAP_INFO_VDEV_ID	HTT_T2H_PEER_MAP_INFO_VDEV_ID
#घोषणा HTT_T2H_PEER_UNMAP_INFO_PEER_ID	HTT_T2H_PEER_MAP_INFO_PEER_ID
#घोषणा HTT_T2H_PEER_UNMAP_INFO1_MAC_ADDR_H16 \
					HTT_T2H_PEER_MAP_INFO1_MAC_ADDR_H16
#घोषणा HTT_T2H_PEER_MAP_INFO1_NEXT_HOP_M HTT_T2H_PEER_MAP_INFO2_NEXT_HOP_M
#घोषणा HTT_T2H_PEER_MAP_INFO1_NEXT_HOP_S HTT_T2H_PEER_MAP_INFO2_NEXT_HOP_S

काष्ठा htt_t2h_peer_unmap_event अणु
	u32 info;
	u32 mac_addr_l32;
	u32 info1;
पूर्ण __packed;

काष्ठा htt_resp_msg अणु
	जोड़ अणु
		काष्ठा htt_t2h_version_conf_msg version_msg;
		काष्ठा htt_t2h_peer_map_event peer_map_ev;
		काष्ठा htt_t2h_peer_unmap_event peer_unmap_ev;
	पूर्ण;
पूर्ण __packed;

#घोषणा HTT_BACKPRESSURE_EVENT_PDEV_ID_M GENMASK(15, 8)
#घोषणा HTT_BACKPRESSURE_EVENT_RING_TYPE_M GENMASK(23, 16)
#घोषणा HTT_BACKPRESSURE_EVENT_RING_ID_M GENMASK(31, 24)

#घोषणा HTT_BACKPRESSURE_EVENT_HP_M GENMASK(15, 0)
#घोषणा HTT_BACKPRESSURE_EVENT_TP_M GENMASK(31, 16)

#घोषणा HTT_BACKPRESSURE_UMAC_RING_TYPE	0
#घोषणा HTT_BACKPRESSURE_LMAC_RING_TYPE	1

क्रमागत htt_backpressure_umac_ringid अणु
	HTT_SW_RING_IDX_REO_REO2SW1_RING,
	HTT_SW_RING_IDX_REO_REO2SW2_RING,
	HTT_SW_RING_IDX_REO_REO2SW3_RING,
	HTT_SW_RING_IDX_REO_REO2SW4_RING,
	HTT_SW_RING_IDX_REO_WBM2REO_LINK_RING,
	HTT_SW_RING_IDX_REO_REO2TCL_RING,
	HTT_SW_RING_IDX_REO_REO2FW_RING,
	HTT_SW_RING_IDX_REO_REO_RELEASE_RING,
	HTT_SW_RING_IDX_WBM_PPE_RELEASE_RING,
	HTT_SW_RING_IDX_TCL_TCL2TQM_RING,
	HTT_SW_RING_IDX_WBM_TQM_RELEASE_RING,
	HTT_SW_RING_IDX_WBM_REO_RELEASE_RING,
	HTT_SW_RING_IDX_WBM_WBM2SW0_RELEASE_RING,
	HTT_SW_RING_IDX_WBM_WBM2SW1_RELEASE_RING,
	HTT_SW_RING_IDX_WBM_WBM2SW2_RELEASE_RING,
	HTT_SW_RING_IDX_WBM_WBM2SW3_RELEASE_RING,
	HTT_SW_RING_IDX_REO_REO_CMD_RING,
	HTT_SW_RING_IDX_REO_REO_STATUS_RING,
	HTT_SW_UMAC_RING_IDX_MAX,
पूर्ण;

क्रमागत htt_backpressure_lmac_ringid अणु
	HTT_SW_RING_IDX_FW2RXDMA_BUF_RING,
	HTT_SW_RING_IDX_FW2RXDMA_STATUS_RING,
	HTT_SW_RING_IDX_FW2RXDMA_LINK_RING,
	HTT_SW_RING_IDX_SW2RXDMA_BUF_RING,
	HTT_SW_RING_IDX_WBM2RXDMA_LINK_RING,
	HTT_SW_RING_IDX_RXDMA2FW_RING,
	HTT_SW_RING_IDX_RXDMA2SW_RING,
	HTT_SW_RING_IDX_RXDMA2RELEASE_RING,
	HTT_SW_RING_IDX_RXDMA2REO_RING,
	HTT_SW_RING_IDX_MONITOR_STATUS_RING,
	HTT_SW_RING_IDX_MONITOR_BUF_RING,
	HTT_SW_RING_IDX_MONITOR_DESC_RING,
	HTT_SW_RING_IDX_MONITOR_DEST_RING,
	HTT_SW_LMAC_RING_IDX_MAX,
पूर्ण;

/* ppdu stats
 *
 * @details
 * The following field definitions describe the क्रमmat of the HTT target
 * to host ppdu stats indication message.
 *
 *
 * |31                         16|15   12|11   10|9      8|7            0 |
 * |----------------------------------------------------------------------|
 * |    payload_size             | rsvd  |pdev_id|mac_id  |    msg type   |
 * |----------------------------------------------------------------------|
 * |                          ppdu_id                                     |
 * |----------------------------------------------------------------------|
 * |                        Timestamp in us                               |
 * |----------------------------------------------------------------------|
 * |                          reserved                                    |
 * |----------------------------------------------------------------------|
 * |                    type-specअगरic stats info                          |
 * |                     (see htt_ppdu_stats.h)                           |
 * |----------------------------------------------------------------------|
 * Header fields:
 *  - MSG_TYPE
 *    Bits 7:0
 *    Purpose: Identअगरies this is a PPDU STATS indication
 *             message.
 *    Value: 0x1d
 *  - mac_id
 *    Bits 9:8
 *    Purpose: mac_id of this ppdu_id
 *    Value: 0-3
 *  - pdev_id
 *    Bits 11:10
 *    Purpose: pdev_id of this ppdu_id
 *    Value: 0-3
 *     0 (क्रम rings at SOC level),
 *     1/2/3 PDEV -> 0/1/2
 *  - payload_size
 *    Bits 31:16
 *    Purpose: total tlv size
 *    Value: payload_size in bytes
 */

#घोषणा HTT_T2H_PPDU_STATS_INFO_PDEV_ID GENMASK(11, 10)
#घोषणा HTT_T2H_PPDU_STATS_INFO_PAYLOAD_SIZE GENMASK(31, 16)

काष्ठा ath11k_htt_ppdu_stats_msg अणु
	u32 info;
	u32 ppdu_id;
	u32 बारtamp;
	u32 rsvd;
	u8 data[0];
पूर्ण __packed;

काष्ठा htt_tlv अणु
	u32 header;
	u8 value[0];
पूर्ण __packed;

#घोषणा HTT_TLV_TAG			GENMASK(11, 0)
#घोषणा HTT_TLV_LEN			GENMASK(23, 12)

क्रमागत HTT_PPDU_STATS_BW अणु
	HTT_PPDU_STATS_BANDWIDTH_5MHZ   = 0,
	HTT_PPDU_STATS_BANDWIDTH_10MHZ  = 1,
	HTT_PPDU_STATS_BANDWIDTH_20MHZ  = 2,
	HTT_PPDU_STATS_BANDWIDTH_40MHZ  = 3,
	HTT_PPDU_STATS_BANDWIDTH_80MHZ  = 4,
	HTT_PPDU_STATS_BANDWIDTH_160MHZ = 5, /* includes 80+80 */
	HTT_PPDU_STATS_BANDWIDTH_DYN    = 6,
पूर्ण;

#घोषणा HTT_PPDU_STATS_CMN_FLAGS_FRAME_TYPE_M	GENMASK(7, 0)
#घोषणा HTT_PPDU_STATS_CMN_FLAGS_QUEUE_TYPE_M	GENMASK(15, 8)
/* bw - HTT_PPDU_STATS_BW */
#घोषणा HTT_PPDU_STATS_CMN_FLAGS_BW_M		GENMASK(19, 16)

काष्ठा htt_ppdu_stats_common अणु
	u32 ppdu_id;
	u16 sched_cmdid;
	u8 ring_id;
	u8 num_users;
	u32 flags; /* %HTT_PPDU_STATS_COMMON_FLAGS_*/
	u32 chain_mask;
	u32 fes_duration_us; /* frame exchange sequence */
	u32 ppdu_sch_eval_start_tsपंचांगp_us;
	u32 ppdu_sch_end_tsपंचांगp_us;
	u32 ppdu_start_tsपंचांगp_us;
	/* BIT [15 :  0] - phy mode (WLAN_PHY_MODE) with which ppdu was transmitted
	 * BIT [31 : 16] - bandwidth (in MHz) with which ppdu was transmitted
	 */
	u16 phy_mode;
	u16 bw_mhz;
पूर्ण __packed;

क्रमागत htt_ppdu_stats_gi अणु
	HTT_PPDU_STATS_SGI_0_8_US,
	HTT_PPDU_STATS_SGI_0_4_US,
	HTT_PPDU_STATS_SGI_1_6_US,
	HTT_PPDU_STATS_SGI_3_2_US,
पूर्ण;

#घोषणा HTT_PPDU_STATS_USER_RATE_INFO0_USER_POS_M	GENMASK(3, 0)
#घोषणा HTT_PPDU_STATS_USER_RATE_INFO0_MU_GROUP_ID_M	GENMASK(11, 4)

#घोषणा HTT_PPDU_STATS_USER_RATE_INFO1_RESP_TYPE_VALD_M	BIT(0)
#घोषणा HTT_PPDU_STATS_USER_RATE_INFO1_PPDU_TYPE_M	GENMASK(5, 1)

#घोषणा HTT_PPDU_STATS_USER_RATE_FLAGS_LTF_SIZE_M	GENMASK(1, 0)
#घोषणा HTT_PPDU_STATS_USER_RATE_FLAGS_STBC_M		BIT(2)
#घोषणा HTT_PPDU_STATS_USER_RATE_FLAGS_HE_RE_M		BIT(3)
#घोषणा HTT_PPDU_STATS_USER_RATE_FLAGS_TXBF_M		GENMASK(7, 4)
#घोषणा HTT_PPDU_STATS_USER_RATE_FLAGS_BW_M		GENMASK(11, 8)
#घोषणा HTT_PPDU_STATS_USER_RATE_FLAGS_NSS_M		GENMASK(15, 12)
#घोषणा HTT_PPDU_STATS_USER_RATE_FLAGS_MCS_M		GENMASK(19, 16)
#घोषणा HTT_PPDU_STATS_USER_RATE_FLAGS_PREAMBLE_M	GENMASK(23, 20)
#घोषणा HTT_PPDU_STATS_USER_RATE_FLAGS_GI_M		GENMASK(27, 24)
#घोषणा HTT_PPDU_STATS_USER_RATE_FLAGS_DCM_M		BIT(28)
#घोषणा HTT_PPDU_STATS_USER_RATE_FLAGS_LDPC_M		BIT(29)

#घोषणा HTT_USR_RATE_PREAMBLE(_val) \
		FIELD_GET(HTT_PPDU_STATS_USER_RATE_FLAGS_PREAMBLE_M, _val)
#घोषणा HTT_USR_RATE_BW(_val) \
		FIELD_GET(HTT_PPDU_STATS_USER_RATE_FLAGS_BW_M, _val)
#घोषणा HTT_USR_RATE_NSS(_val) \
		FIELD_GET(HTT_PPDU_STATS_USER_RATE_FLAGS_NSS_M, _val)
#घोषणा HTT_USR_RATE_MCS(_val) \
		FIELD_GET(HTT_PPDU_STATS_USER_RATE_FLAGS_MCS_M, _val)
#घोषणा HTT_USR_RATE_GI(_val) \
		FIELD_GET(HTT_PPDU_STATS_USER_RATE_FLAGS_GI_M, _val)
#घोषणा HTT_USR_RATE_DCM(_val) \
		FIELD_GET(HTT_PPDU_STATS_USER_RATE_FLAGS_DCM_M, _val)

#घोषणा HTT_PPDU_STATS_USER_RATE_RESP_FLAGS_LTF_SIZE_M		GENMASK(1, 0)
#घोषणा HTT_PPDU_STATS_USER_RATE_RESP_FLAGS_STBC_M		BIT(2)
#घोषणा HTT_PPDU_STATS_USER_RATE_RESP_FLAGS_HE_RE_M		BIT(3)
#घोषणा HTT_PPDU_STATS_USER_RATE_RESP_FLAGS_TXBF_M		GENMASK(7, 4)
#घोषणा HTT_PPDU_STATS_USER_RATE_RESP_FLAGS_BW_M		GENMASK(11, 8)
#घोषणा HTT_PPDU_STATS_USER_RATE_RESP_FLAGS_NSS_M		GENMASK(15, 12)
#घोषणा HTT_PPDU_STATS_USER_RATE_RESP_FLAGS_MCS_M		GENMASK(19, 16)
#घोषणा HTT_PPDU_STATS_USER_RATE_RESP_FLAGS_PREAMBLE_M		GENMASK(23, 20)
#घोषणा HTT_PPDU_STATS_USER_RATE_RESP_FLAGS_GI_M		GENMASK(27, 24)
#घोषणा HTT_PPDU_STATS_USER_RATE_RESP_FLAGS_DCM_M		BIT(28)
#घोषणा HTT_PPDU_STATS_USER_RATE_RESP_FLAGS_LDPC_M		BIT(29)

काष्ठा htt_ppdu_stats_user_rate अणु
	u8 tid_num;
	u8 reserved0;
	u16 sw_peer_id;
	u32 info0; /* %HTT_PPDU_STATS_USER_RATE_INFO0_*/
	u16 ru_end;
	u16 ru_start;
	u16 resp_ru_end;
	u16 resp_ru_start;
	u32 info1; /* %HTT_PPDU_STATS_USER_RATE_INFO1_ */
	u32 rate_flags; /* %HTT_PPDU_STATS_USER_RATE_FLAGS_ */
	/* Note: resp_rate_info is only valid क्रम अगर resp_type is UL */
	u32 resp_rate_flags; /* %HTT_PPDU_STATS_USER_RATE_RESP_FLAGS_ */
पूर्ण __packed;

#घोषणा HTT_PPDU_STATS_TX_INFO_FLAGS_RATECODE_M		GENMASK(7, 0)
#घोषणा HTT_PPDU_STATS_TX_INFO_FLAGS_IS_AMPDU_M		BIT(8)
#घोषणा HTT_PPDU_STATS_TX_INFO_FLAGS_BA_ACK_FAILED_M	GENMASK(10, 9)
#घोषणा HTT_PPDU_STATS_TX_INFO_FLAGS_BW_M		GENMASK(13, 11)
#घोषणा HTT_PPDU_STATS_TX_INFO_FLAGS_SGI_M		BIT(14)
#घोषणा HTT_PPDU_STATS_TX_INFO_FLAGS_PEERID_M		GENMASK(31, 16)

#घोषणा HTT_TX_INFO_IS_AMSDU(_flags) \
			FIELD_GET(HTT_PPDU_STATS_TX_INFO_FLAGS_IS_AMPDU_M, _flags)
#घोषणा HTT_TX_INFO_BA_ACK_FAILED(_flags) \
			FIELD_GET(HTT_PPDU_STATS_TX_INFO_FLAGS_BA_ACK_FAILED_M, _flags)
#घोषणा HTT_TX_INFO_RATECODE(_flags) \
			FIELD_GET(HTT_PPDU_STATS_TX_INFO_FLAGS_RATECODE_M, _flags)
#घोषणा HTT_TX_INFO_PEERID(_flags) \
			FIELD_GET(HTT_PPDU_STATS_TX_INFO_FLAGS_PEERID_M, _flags)

काष्ठा htt_tx_ppdu_stats_info अणु
	काष्ठा htt_tlv tlv_hdr;
	u32 tx_success_bytes;
	u32 tx_retry_bytes;
	u32 tx_failed_bytes;
	u32 flags; /* %HTT_PPDU_STATS_TX_INFO_FLAGS_ */
	u16 tx_success_msdus;
	u16 tx_retry_msdus;
	u16 tx_failed_msdus;
	u16 tx_duration; /* united in us */
पूर्ण __packed;

क्रमागत  htt_ppdu_stats_usr_compln_status अणु
	HTT_PPDU_STATS_USER_STATUS_OK,
	HTT_PPDU_STATS_USER_STATUS_FILTERED,
	HTT_PPDU_STATS_USER_STATUS_RESP_TIMEOUT,
	HTT_PPDU_STATS_USER_STATUS_RESP_MISMATCH,
	HTT_PPDU_STATS_USER_STATUS_ABORT,
पूर्ण;

#घोषणा HTT_PPDU_STATS_USR_CMPLTN_CMN_FLAGS_LONG_RETRY_M	GENMASK(3, 0)
#घोषणा HTT_PPDU_STATS_USR_CMPLTN_CMN_FLAGS_SHORT_RETRY_M	GENMASK(7, 4)
#घोषणा HTT_PPDU_STATS_USR_CMPLTN_CMN_FLAGS_IS_AMPDU_M		BIT(8)
#घोषणा HTT_PPDU_STATS_USR_CMPLTN_CMN_FLAGS_RESP_TYPE_M		GENMASK(12, 9)

#घोषणा HTT_USR_CMPLTN_IS_AMPDU(_val) \
	    FIELD_GET(HTT_PPDU_STATS_USR_CMPLTN_CMN_FLAGS_IS_AMPDU_M, _val)
#घोषणा HTT_USR_CMPLTN_LONG_RETRY(_val) \
	    FIELD_GET(HTT_PPDU_STATS_USR_CMPLTN_CMN_FLAGS_LONG_RETRY_M, _val)
#घोषणा HTT_USR_CMPLTN_SHORT_RETRY(_val) \
	    FIELD_GET(HTT_PPDU_STATS_USR_CMPLTN_CMN_FLAGS_SHORT_RETRY_M, _val)

काष्ठा htt_ppdu_stats_usr_cmpltn_cmn अणु
	u8 status;
	u8 tid_num;
	u16 sw_peer_id;
	/* RSSI value of last ack packet (units = dB above noise न्यूनमान) */
	u32 ack_rssi;
	u16 mpdu_tried;
	u16 mpdu_success;
	u32 flags; /* %HTT_PPDU_STATS_USR_CMPLTN_CMN_FLAGS_LONG_RETRIES*/
पूर्ण __packed;

#घोषणा HTT_PPDU_STATS_ACK_BA_INFO_NUM_MPDU_M	GENMASK(8, 0)
#घोषणा HTT_PPDU_STATS_ACK_BA_INFO_NUM_MSDU_M	GENMASK(24, 9)
#घोषणा HTT_PPDU_STATS_ACK_BA_INFO_TID_NUM	GENMASK(31, 25)

#घोषणा HTT_PPDU_STATS_NON_QOS_TID	16

काष्ठा htt_ppdu_stats_usr_cmpltn_ack_ba_status अणु
	u32 ppdu_id;
	u16 sw_peer_id;
	u16 reserved0;
	u32 info; /* %HTT_PPDU_STATS_USR_CMPLTN_CMN_INFO_ */
	u16 current_seq;
	u16 start_seq;
	u32 success_bytes;
पूर्ण __packed;

काष्ठा htt_ppdu_stats_usr_cmn_array अणु
	काष्ठा htt_tlv tlv_hdr;
	u32 num_ppdu_stats;
	/* tx_ppdu_stats_info is filled by multiple काष्ठा htt_tx_ppdu_stats_info
	 * elements.
	 * tx_ppdu_stats_info is variable length, with length =
	 *     number_of_ppdu_stats * माप (काष्ठा htt_tx_ppdu_stats_info)
	 */
	काष्ठा htt_tx_ppdu_stats_info tx_ppdu_info[0];
पूर्ण __packed;

काष्ठा htt_ppdu_user_stats अणु
	u16 peer_id;
	u32 tlv_flags;
	bool is_valid_peer_id;
	काष्ठा htt_ppdu_stats_user_rate rate;
	काष्ठा htt_ppdu_stats_usr_cmpltn_cmn cmpltn_cmn;
	काष्ठा htt_ppdu_stats_usr_cmpltn_ack_ba_status ack_ba;
पूर्ण;

#घोषणा HTT_PPDU_STATS_MAX_USERS	8
#घोषणा HTT_PPDU_DESC_MAX_DEPTH	16

काष्ठा htt_ppdu_stats अणु
	काष्ठा htt_ppdu_stats_common common;
	काष्ठा htt_ppdu_user_stats user_stats[HTT_PPDU_STATS_MAX_USERS];
पूर्ण;

काष्ठा htt_ppdu_stats_info अणु
	u32 ppdu_id;
	काष्ठा htt_ppdu_stats ppdu_stats;
	काष्ठा list_head list;
पूर्ण;

/**
 * @brief target -> host packet log message
 *
 * @details
 * The following field definitions describe the क्रमmat of the packet log
 * message sent from the target to the host.
 * The message consists of a 4-octet header,followed by a variable number
 * of 32-bit अक्षरacter values.
 *
 * |31                         16|15  12|11   10|9    8|7            0|
 * |------------------------------------------------------------------|
 * |        payload_size         | rsvd |pdev_id|mac_id|   msg type   |
 * |------------------------------------------------------------------|
 * |                              payload                             |
 * |------------------------------------------------------------------|
 *   - MSG_TYPE
 *     Bits 7:0
 *     Purpose: identअगरies this as a pktlog message
 *     Value: HTT_T2H_MSG_TYPE_PKTLOG
 *   - mac_id
 *     Bits 9:8
 *     Purpose: identअगरies which MAC/PHY instance generated this pktlog info
 *     Value: 0-3
 *   - pdev_id
 *     Bits 11:10
 *     Purpose: pdev_id
 *     Value: 0-3
 *     0 (क्रम rings at SOC level),
 *     1/2/3 PDEV -> 0/1/2
 *   - payload_size
 *     Bits 31:16
 *     Purpose: explicitly specअगरy the payload size
 *     Value: payload size in bytes (payload size is a multiple of 4 bytes)
 */
काष्ठा htt_pktlog_msg अणु
	u32 hdr;
	u8 payload[0];
पूर्ण;

/**
 * @brief host -> target FW extended statistics retrieve
 *
 * @details
 * The following field definitions describe the क्रमmat of the HTT host
 * to target FW extended stats retrieve message.
 * The message specअगरies the type of stats the host wants to retrieve.
 *
 * |31          24|23          16|15           8|7            0|
 * |-----------------------------------------------------------|
 * |   reserved   | stats type   |   pdev_mask  |   msg type   |
 * |-----------------------------------------------------------|
 * |                   config param [0]                        |
 * |-----------------------------------------------------------|
 * |                   config param [1]                        |
 * |-----------------------------------------------------------|
 * |                   config param [2]                        |
 * |-----------------------------------------------------------|
 * |                   config param [3]                        |
 * |-----------------------------------------------------------|
 * |                         reserved                          |
 * |-----------------------------------------------------------|
 * |                        cookie LSBs                        |
 * |-----------------------------------------------------------|
 * |                        cookie MSBs                        |
 * |-----------------------------------------------------------|
 * Header fields:
 *  - MSG_TYPE
 *    Bits 7:0
 *    Purpose: identअगरies this is a extended stats upload request message
 *    Value: 0x10
 *  - PDEV_MASK
 *    Bits 8:15
 *    Purpose: identअगरies the mask of PDEVs to retrieve stats from
 *    Value: This is a overloaded field, refer to usage and पूर्णांकerpretation of
 *           PDEV in पूर्णांकerface करोcument.
 *           Bit   8    :  Reserved क्रम SOC stats
 *           Bit 9 - 15 :  Indicates PDEV_MASK in DBDC
 *                         Indicates MACID_MASK in DBS
 *  - STATS_TYPE
 *    Bits 23:16
 *    Purpose: identअगरies which FW statistics to upload
 *    Value: Defined by htt_dbg_ext_stats_type (see htt_stats.h)
 *  - Reserved
 *    Bits 31:24
 *  - CONFIG_PARAM [0]
 *    Bits 31:0
 *    Purpose: give an opaque configuration value to the specअगरied stats type
 *    Value: stats-type specअगरic configuration value
 *           Refer to htt_stats.h क्रम पूर्णांकerpretation क्रम each stats sub_type
 *  - CONFIG_PARAM [1]
 *    Bits 31:0
 *    Purpose: give an opaque configuration value to the specअगरied stats type
 *    Value: stats-type specअगरic configuration value
 *           Refer to htt_stats.h क्रम पूर्णांकerpretation क्रम each stats sub_type
 *  - CONFIG_PARAM [2]
 *    Bits 31:0
 *    Purpose: give an opaque configuration value to the specअगरied stats type
 *    Value: stats-type specअगरic configuration value
 *           Refer to htt_stats.h क्रम पूर्णांकerpretation क्रम each stats sub_type
 *  - CONFIG_PARAM [3]
 *    Bits 31:0
 *    Purpose: give an opaque configuration value to the specअगरied stats type
 *    Value: stats-type specअगरic configuration value
 *           Refer to htt_stats.h क्रम पूर्णांकerpretation क्रम each stats sub_type
 *  - Reserved [31:0] क्रम future use.
 *  - COOKIE_LSBS
 *    Bits 31:0
 *    Purpose: Provide a mechanism to match a target->host stats confirmation
 *        message with its preceding host->target stats request message.
 *    Value: LSBs of the opaque cookie specअगरied by the host-side requestor
 *  - COOKIE_MSBS
 *    Bits 31:0
 *    Purpose: Provide a mechanism to match a target->host stats confirmation
 *        message with its preceding host->target stats request message.
 *    Value: MSBs of the opaque cookie specअगरied by the host-side requestor
 */

काष्ठा htt_ext_stats_cfg_hdr अणु
	u8 msg_type;
	u8 pdev_mask;
	u8 stats_type;
	u8 reserved;
पूर्ण __packed;

काष्ठा htt_ext_stats_cfg_cmd अणु
	काष्ठा htt_ext_stats_cfg_hdr hdr;
	u32 cfg_param0;
	u32 cfg_param1;
	u32 cfg_param2;
	u32 cfg_param3;
	u32 reserved;
	u32 cookie_lsb;
	u32 cookie_msb;
पूर्ण __packed;

/* htt stats config शेष params */
#घोषणा HTT_STAT_DEFAULT_RESET_START_OFFSET 0
#घोषणा HTT_STAT_DEFAULT_CFG0_ALL_HWQS 0xffffffff
#घोषणा HTT_STAT_DEFAULT_CFG0_ALL_TXQS 0xffffffff
#घोषणा HTT_STAT_DEFAULT_CFG0_ALL_CMDQS 0xffff
#घोषणा HTT_STAT_DEFAULT_CFG0_ALL_RINGS 0xffff
#घोषणा HTT_STAT_DEFAULT_CFG0_ACTIVE_PEERS 0xff
#घोषणा HTT_STAT_DEFAULT_CFG0_CCA_CUMULATIVE 0x00
#घोषणा HTT_STAT_DEFAULT_CFG0_ACTIVE_VDEVS 0x00

/* HTT_DBG_EXT_STATS_PEER_INFO
 * PARAMS:
 * @config_param0:
 *  [Bit0] - [0] क्रम sw_peer_id, [1] क्रम mac_addr based request
 *  [Bit15 : Bit 1] htt_peer_stats_req_mode_t
 *  [Bit31 : Bit16] sw_peer_id
 * @config_param1:
 *  peer_stats_req_type_mask:32 (क्रमागत htt_peer_stats_tlv_क्रमागत)
 *   0 bit htt_peer_stats_cmn_tlv
 *   1 bit htt_peer_details_tlv
 *   2 bit htt_tx_peer_rate_stats_tlv
 *   3 bit htt_rx_peer_rate_stats_tlv
 *   4 bit htt_tx_tid_stats_tlv/htt_tx_tid_stats_v1_tlv
 *   5 bit htt_rx_tid_stats_tlv
 *   6 bit htt_msdu_flow_stats_tlv
 * @config_param2: [Bit31 : Bit0] mac_addr31to0
 * @config_param3: [Bit15 : Bit0] mac_addr47to32
 *                [Bit31 : Bit16] reserved
 */
#घोषणा HTT_STAT_PEER_INFO_MAC_ADDR BIT(0)
#घोषणा HTT_STAT_DEFAULT_PEER_REQ_TYPE 0x7f

/* Used to set dअगरferent configs to the specअगरied stats type.*/
काष्ठा htt_ext_stats_cfg_params अणु
	u32 cfg0;
	u32 cfg1;
	u32 cfg2;
	u32 cfg3;
पूर्ण;

/**
 * @brief target -> host extended statistics upload
 *
 * @details
 * The following field definitions describe the क्रमmat of the HTT target
 * to host stats upload confirmation message.
 * The message contains a cookie echoed from the HTT host->target stats
 * upload request, which identअगरies which request the confirmation is
 * क्रम, and a single stats can span over multiple HTT stats indication
 * due to the HTT message size limitation so every HTT ext stats indication
 * will have tag-length-value stats inक्रमmation elements.
 * The tag-length header क्रम each HTT stats IND message also includes a
 * status field, to indicate whether the request क्रम the stat type in
 * question was fully met, partially met, unable to be met, or invalid
 * (अगर the stat type in question is disabled in the target).
 * A Done bit 1's indicate the end of the of stats info elements.
 *
 *
 * |31                         16|15    12|11|10 8|7   5|4       0|
 * |--------------------------------------------------------------|
 * |                   reserved                   |    msg type   |
 * |--------------------------------------------------------------|
 * |                         cookie LSBs                          |
 * |--------------------------------------------------------------|
 * |                         cookie MSBs                          |
 * |--------------------------------------------------------------|
 * |      stats entry length     | rsvd   | D|  S |   stat type   |
 * |--------------------------------------------------------------|
 * |                   type-specअगरic stats info                   |
 * |                      (see htt_stats.h)                       |
 * |--------------------------------------------------------------|
 * Header fields:
 *  - MSG_TYPE
 *    Bits 7:0
 *    Purpose: Identअगरies this is a extended statistics upload confirmation
 *             message.
 *    Value: 0x1c
 *  - COOKIE_LSBS
 *    Bits 31:0
 *    Purpose: Provide a mechanism to match a target->host stats confirmation
 *        message with its preceding host->target stats request message.
 *    Value: LSBs of the opaque cookie specअगरied by the host-side requestor
 *  - COOKIE_MSBS
 *    Bits 31:0
 *    Purpose: Provide a mechanism to match a target->host stats confirmation
 *        message with its preceding host->target stats request message.
 *    Value: MSBs of the opaque cookie specअगरied by the host-side requestor
 *
 * Stats Inक्रमmation Element tag-length header fields:
 *  - STAT_TYPE
 *    Bits 7:0
 *    Purpose: identअगरies the type of statistics info held in the
 *        following inक्रमmation element
 *    Value: htt_dbg_ext_stats_type
 *  - STATUS
 *    Bits 10:8
 *    Purpose: indicate whether the requested stats are present
 *    Value: htt_dbg_ext_stats_status
 *  - DONE
 *    Bits 11
 *    Purpose:
 *        Indicates the completion of the stats entry, this will be the last
 *        stats conf HTT segment क्रम the requested stats type.
 *    Value:
 *        0 -> the stats retrieval is ongoing
 *        1 -> the stats retrieval is complete
 *  - LENGTH
 *    Bits 31:16
 *    Purpose: indicate the stats inक्रमmation size
 *    Value: This field specअगरies the number of bytes of stats inक्रमmation
 *       that follows the element tag-length header.
 *       It is expected but not required that this length is a multiple of
 *       4 bytes.
 */

#घोषणा HTT_T2H_EXT_STATS_INFO1_DONE	BIT(11)
#घोषणा HTT_T2H_EXT_STATS_INFO1_LENGTH   GENMASK(31, 16)

काष्ठा ath11k_htt_extd_stats_msg अणु
	u32 info0;
	u64 cookie;
	u32 info1;
	u8 data[0];
पूर्ण __packed;

काष्ठा htt_mac_addr अणु
	u32 mac_addr_l32;
	u32 mac_addr_h16;
पूर्ण;

अटल अंतरभूत व्योम ath11k_dp_get_mac_addr(u32 addr_l32, u16 addr_h16, u8 *addr)
अणु
	अगर (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN)) अणु
		addr_l32 = swab32(addr_l32);
		addr_h16 = swab16(addr_h16);
	पूर्ण

	स_नकल(addr, &addr_l32, 4);
	स_नकल(addr + 4, &addr_h16, ETH_ALEN - 4);
पूर्ण

पूर्णांक ath11k_dp_service_srng(काष्ठा ath11k_base *ab,
			   काष्ठा ath11k_ext_irq_grp *irq_grp,
			   पूर्णांक budget);
पूर्णांक ath11k_dp_htt_connect(काष्ठा ath11k_dp *dp);
व्योम ath11k_dp_vdev_tx_attach(काष्ठा ath11k *ar, काष्ठा ath11k_vअगर *arvअगर);
व्योम ath11k_dp_मुक्त(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_dp_alloc(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_dp_pdev_alloc(काष्ठा ath11k_base *ab);
व्योम ath11k_dp_pdev_pre_alloc(काष्ठा ath11k_base *ab);
व्योम ath11k_dp_pdev_मुक्त(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_dp_tx_htt_srng_setup(काष्ठा ath11k_base *ab, u32 ring_id,
				पूर्णांक mac_id, क्रमागत hal_ring_type ring_type);
पूर्णांक ath11k_dp_peer_setup(काष्ठा ath11k *ar, पूर्णांक vdev_id, स्थिर u8 *addr);
व्योम ath11k_dp_peer_cleanup(काष्ठा ath11k *ar, पूर्णांक vdev_id, स्थिर u8 *addr);
व्योम ath11k_dp_srng_cleanup(काष्ठा ath11k_base *ab, काष्ठा dp_srng *ring);
पूर्णांक ath11k_dp_srng_setup(काष्ठा ath11k_base *ab, काष्ठा dp_srng *ring,
			 क्रमागत hal_ring_type type, पूर्णांक ring_num,
			 पूर्णांक mac_id, पूर्णांक num_entries);
व्योम ath11k_dp_link_desc_cleanup(काष्ठा ath11k_base *ab,
				 काष्ठा dp_link_desc_bank *desc_bank,
				 u32 ring_type, काष्ठा dp_srng *ring);
पूर्णांक ath11k_dp_link_desc_setup(काष्ठा ath11k_base *ab,
			      काष्ठा dp_link_desc_bank *link_desc_banks,
			      u32 ring_type, काष्ठा hal_srng *srng,
			      u32 n_link_desc);
व्योम ath11k_dp_shaकरोw_start_समयr(काष्ठा ath11k_base *ab,
				  काष्ठा hal_srng	*srng,
				  काष्ठा ath11k_hp_update_समयr *update_समयr);
व्योम ath11k_dp_shaकरोw_stop_समयr(काष्ठा ath11k_base *ab,
				 काष्ठा ath11k_hp_update_समयr *update_समयr);
व्योम ath11k_dp_shaकरोw_init_समयr(काष्ठा ath11k_base *ab,
				 काष्ठा ath11k_hp_update_समयr *update_समयr,
				 u32 पूर्णांकerval, u32 ring_id);
व्योम ath11k_dp_stop_shaकरोw_समयrs(काष्ठा ath11k_base *ab);

#पूर्ण_अगर
