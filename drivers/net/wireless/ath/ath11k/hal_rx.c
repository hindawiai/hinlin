<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश "debug.h"
#समावेश "hal.h"
#समावेश "hal_tx.h"
#समावेश "hal_rx.h"
#समावेश "hal_desc.h"
#समावेश "hif.h"

अटल व्योम ath11k_hal_reo_set_desc_hdr(काष्ठा hal_desc_header *hdr,
					u8 owner, u8 buffer_type, u32 magic)
अणु
	hdr->info0 = FIELD_PREP(HAL_DESC_HDR_INFO0_OWNER, owner) |
		     FIELD_PREP(HAL_DESC_HDR_INFO0_BUF_TYPE, buffer_type);

	/* Magic pattern in reserved bits क्रम debugging */
	hdr->info0 |= FIELD_PREP(HAL_DESC_HDR_INFO0_DBG_RESERVED, magic);
पूर्ण

अटल पूर्णांक ath11k_hal_reo_cmd_queue_stats(काष्ठा hal_tlv_hdr *tlv,
					  काष्ठा ath11k_hal_reo_cmd *cmd)
अणु
	काष्ठा hal_reo_get_queue_stats *desc;

	tlv->tl = FIELD_PREP(HAL_TLV_HDR_TAG, HAL_REO_GET_QUEUE_STATS) |
		  FIELD_PREP(HAL_TLV_HDR_LEN, माप(*desc));

	desc = (काष्ठा hal_reo_get_queue_stats *)tlv->value;
	स_रखो(&desc->queue_addr_lo, 0,
	       (माप(*desc) - माप(काष्ठा hal_reo_cmd_hdr)));

	desc->cmd.info0 &= ~HAL_REO_CMD_HDR_INFO0_STATUS_REQUIRED;
	अगर (cmd->flag & HAL_REO_CMD_FLG_NEED_STATUS)
		desc->cmd.info0 |= HAL_REO_CMD_HDR_INFO0_STATUS_REQUIRED;

	desc->queue_addr_lo = cmd->addr_lo;
	desc->info0 = FIELD_PREP(HAL_REO_GET_QUEUE_STATS_INFO0_QUEUE_ADDR_HI,
				 cmd->addr_hi);
	अगर (cmd->flag & HAL_REO_CMD_FLG_STATS_CLEAR)
		desc->info0 |= HAL_REO_GET_QUEUE_STATS_INFO0_CLEAR_STATS;

	वापस FIELD_GET(HAL_REO_CMD_HDR_INFO0_CMD_NUMBER, desc->cmd.info0);
पूर्ण

अटल पूर्णांक ath11k_hal_reo_cmd_flush_cache(काष्ठा ath11k_hal *hal, काष्ठा hal_tlv_hdr *tlv,
					  काष्ठा ath11k_hal_reo_cmd *cmd)
अणु
	काष्ठा hal_reo_flush_cache *desc;
	u8 avail_slot = ffz(hal->avail_blk_resource);

	अगर (cmd->flag & HAL_REO_CMD_FLG_FLUSH_BLOCK_LATER) अणु
		अगर (avail_slot >= HAL_MAX_AVAIL_BLK_RES)
			वापस -ENOSPC;

		hal->current_blk_index = avail_slot;
	पूर्ण

	tlv->tl = FIELD_PREP(HAL_TLV_HDR_TAG, HAL_REO_FLUSH_CACHE) |
		  FIELD_PREP(HAL_TLV_HDR_LEN, माप(*desc));

	desc = (काष्ठा hal_reo_flush_cache *)tlv->value;
	स_रखो(&desc->cache_addr_lo, 0,
	       (माप(*desc) - माप(काष्ठा hal_reo_cmd_hdr)));

	desc->cmd.info0 &= ~HAL_REO_CMD_HDR_INFO0_STATUS_REQUIRED;
	अगर (cmd->flag & HAL_REO_CMD_FLG_NEED_STATUS)
		desc->cmd.info0 |= HAL_REO_CMD_HDR_INFO0_STATUS_REQUIRED;

	desc->cache_addr_lo = cmd->addr_lo;
	desc->info0 = FIELD_PREP(HAL_REO_FLUSH_CACHE_INFO0_CACHE_ADDR_HI,
				 cmd->addr_hi);

	अगर (cmd->flag & HAL_REO_CMD_FLG_FLUSH_FWD_ALL_MPDUS)
		desc->info0 |= HAL_REO_FLUSH_CACHE_INFO0_FWD_ALL_MPDUS;

	अगर (cmd->flag & HAL_REO_CMD_FLG_FLUSH_BLOCK_LATER) अणु
		desc->info0 |= HAL_REO_FLUSH_CACHE_INFO0_BLOCK_CACHE_USAGE;
		desc->info0 |=
			FIELD_PREP(HAL_REO_FLUSH_CACHE_INFO0_BLOCK_RESRC_IDX,
				   avail_slot);
	पूर्ण

	अगर (cmd->flag & HAL_REO_CMD_FLG_FLUSH_NO_INVAL)
		desc->info0 |= HAL_REO_FLUSH_CACHE_INFO0_FLUSH_WO_INVALIDATE;

	अगर (cmd->flag & HAL_REO_CMD_FLG_FLUSH_ALL)
		desc->info0 |= HAL_REO_FLUSH_CACHE_INFO0_FLUSH_ALL;

	वापस FIELD_GET(HAL_REO_CMD_HDR_INFO0_CMD_NUMBER, desc->cmd.info0);
पूर्ण

अटल पूर्णांक ath11k_hal_reo_cmd_update_rx_queue(काष्ठा hal_tlv_hdr *tlv,
					      काष्ठा ath11k_hal_reo_cmd *cmd)
अणु
	काष्ठा hal_reo_update_rx_queue *desc;

	tlv->tl = FIELD_PREP(HAL_TLV_HDR_TAG, HAL_REO_UPDATE_RX_REO_QUEUE) |
		  FIELD_PREP(HAL_TLV_HDR_LEN, माप(*desc));

	desc = (काष्ठा hal_reo_update_rx_queue *)tlv->value;
	स_रखो(&desc->queue_addr_lo, 0,
	       (माप(*desc) - माप(काष्ठा hal_reo_cmd_hdr)));

	desc->cmd.info0 &= ~HAL_REO_CMD_HDR_INFO0_STATUS_REQUIRED;
	अगर (cmd->flag & HAL_REO_CMD_FLG_NEED_STATUS)
		desc->cmd.info0 |= HAL_REO_CMD_HDR_INFO0_STATUS_REQUIRED;

	desc->queue_addr_lo = cmd->addr_lo;
	desc->info0 =
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_QUEUE_ADDR_HI,
			   cmd->addr_hi) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_RX_QUEUE_NUM,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_RX_QUEUE_NUM)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_VLD,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_VLD)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_ASSOC_LNK_DESC_CNT,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_ALDC)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_DIS_DUP_DETECTION,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_DIS_DUP_DETECTION)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_SOFT_REORDER_EN,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_SOFT_REORDER_EN)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_AC,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_AC)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_BAR,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_BAR)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_RETRY,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_RETRY)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_CHECK_2K_MODE,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_CHECK_2K_MODE)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_OOR_MODE,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_OOR_MODE)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_BA_WINDOW_SIZE,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_BA_WINDOW_SIZE)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_PN_CHECK,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_PN_CHECK)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_EVEN_PN,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_EVEN_PN)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_UNEVEN_PN,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_UNEVEN_PN)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_PN_HANDLE_ENABLE,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_PN_HANDLE_ENABLE)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_PN_SIZE,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_PN_SIZE)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_IGNORE_AMPDU_FLG,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_IGNORE_AMPDU_FLG)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_SVLD,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_SVLD)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_SSN,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_SSN)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_SEQ_2K_ERR,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_SEQ_2K_ERR)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_PN_VALID,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_PN_VALID)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO0_UPD_PN,
			   !!(cmd->upd0 & HAL_REO_CMD_UPD0_PN));

	desc->info1 =
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_RX_QUEUE_NUMBER,
			   cmd->rx_queue_num) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_VLD,
			   !!(cmd->upd1 & HAL_REO_CMD_UPD1_VLD)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_ASSOC_LNK_DESC_COUNTER,
			   FIELD_GET(HAL_REO_CMD_UPD1_ALDC, cmd->upd1)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_DIS_DUP_DETECTION,
			   !!(cmd->upd1 & HAL_REO_CMD_UPD1_DIS_DUP_DETECTION)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_SOFT_REORDER_EN,
			   !!(cmd->upd1 & HAL_REO_CMD_UPD1_SOFT_REORDER_EN)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_AC,
			   FIELD_GET(HAL_REO_CMD_UPD1_AC, cmd->upd1)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_BAR,
			   !!(cmd->upd1 & HAL_REO_CMD_UPD1_BAR)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_CHECK_2K_MODE,
			   !!(cmd->upd1 & HAL_REO_CMD_UPD1_CHECK_2K_MODE)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_RETRY,
			   !!(cmd->upd1 & HAL_REO_CMD_UPD1_RETRY)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_OOR_MODE,
			   !!(cmd->upd1 & HAL_REO_CMD_UPD1_OOR_MODE)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_PN_CHECK,
			   !!(cmd->upd1 & HAL_REO_CMD_UPD1_PN_CHECK)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_EVEN_PN,
			   !!(cmd->upd1 & HAL_REO_CMD_UPD1_EVEN_PN)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_UNEVEN_PN,
			   !!(cmd->upd1 & HAL_REO_CMD_UPD1_UNEVEN_PN)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_PN_HANDLE_ENABLE,
			   !!(cmd->upd1 & HAL_REO_CMD_UPD1_PN_HANDLE_ENABLE)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO1_IGNORE_AMPDU_FLG,
			   !!(cmd->upd1 & HAL_REO_CMD_UPD1_IGNORE_AMPDU_FLG));

	अगर (cmd->pn_size == 24)
		cmd->pn_size = HAL_RX_REO_QUEUE_PN_SIZE_24;
	अन्यथा अगर (cmd->pn_size == 48)
		cmd->pn_size = HAL_RX_REO_QUEUE_PN_SIZE_48;
	अन्यथा अगर (cmd->pn_size == 128)
		cmd->pn_size = HAL_RX_REO_QUEUE_PN_SIZE_128;

	अगर (cmd->ba_winकरोw_size < 1)
		cmd->ba_winकरोw_size = 1;

	अगर (cmd->ba_winकरोw_size == 1)
		cmd->ba_winकरोw_size++;

	desc->info2 =
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO2_BA_WINDOW_SIZE,
			   cmd->ba_winकरोw_size - 1) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO2_PN_SIZE, cmd->pn_size) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO2_SVLD,
			   !!(cmd->upd2 & HAL_REO_CMD_UPD2_SVLD)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO2_SSN,
			   FIELD_GET(HAL_REO_CMD_UPD2_SSN, cmd->upd2)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO2_SEQ_2K_ERR,
			   !!(cmd->upd2 & HAL_REO_CMD_UPD2_SEQ_2K_ERR)) |
		FIELD_PREP(HAL_REO_UPD_RX_QUEUE_INFO2_PN_ERR,
			   !!(cmd->upd2 & HAL_REO_CMD_UPD2_PN_ERR));

	वापस FIELD_GET(HAL_REO_CMD_HDR_INFO0_CMD_NUMBER, desc->cmd.info0);
पूर्ण

पूर्णांक ath11k_hal_reo_cmd_send(काष्ठा ath11k_base *ab, काष्ठा hal_srng *srng,
			    क्रमागत hal_reo_cmd_type type,
			    काष्ठा ath11k_hal_reo_cmd *cmd)
अणु
	काष्ठा hal_tlv_hdr *reo_desc;
	पूर्णांक ret;

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);
	reo_desc = (काष्ठा hal_tlv_hdr *)ath11k_hal_srng_src_get_next_entry(ab, srng);
	अगर (!reo_desc) अणु
		ret = -ENOBUFS;
		जाओ out;
	पूर्ण

	चयन (type) अणु
	हाल HAL_REO_CMD_GET_QUEUE_STATS:
		ret = ath11k_hal_reo_cmd_queue_stats(reo_desc, cmd);
		अवरोध;
	हाल HAL_REO_CMD_FLUSH_CACHE:
		ret = ath11k_hal_reo_cmd_flush_cache(&ab->hal, reo_desc, cmd);
		अवरोध;
	हाल HAL_REO_CMD_UPDATE_RX_QUEUE:
		ret = ath11k_hal_reo_cmd_update_rx_queue(reo_desc, cmd);
		अवरोध;
	हाल HAL_REO_CMD_FLUSH_QUEUE:
	हाल HAL_REO_CMD_UNBLOCK_CACHE:
	हाल HAL_REO_CMD_FLUSH_TIMEOUT_LIST:
		ath11k_warn(ab, "Unsupported reo command %d\n", type);
		ret = -ENOTSUPP;
		अवरोध;
	शेष:
		ath11k_warn(ab, "Unknown reo command %d\n", type);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	ath11k_dp_shaकरोw_start_समयr(ab, srng, &ab->dp.reo_cmd_समयr);

out:
	ath11k_hal_srng_access_end(ab, srng);
	spin_unlock_bh(&srng->lock);

	वापस ret;
पूर्ण

व्योम ath11k_hal_rx_buf_addr_info_set(व्योम *desc, dma_addr_t paddr,
				     u32 cookie, u8 manager)
अणु
	काष्ठा ath11k_buffer_addr *binfo = (काष्ठा ath11k_buffer_addr *)desc;
	u32 paddr_lo, paddr_hi;

	paddr_lo = lower_32_bits(paddr);
	paddr_hi = upper_32_bits(paddr);
	binfo->info0 = FIELD_PREP(BUFFER_ADDR_INFO0_ADDR, paddr_lo);
	binfo->info1 = FIELD_PREP(BUFFER_ADDR_INFO1_ADDR, paddr_hi) |
		       FIELD_PREP(BUFFER_ADDR_INFO1_SW_COOKIE, cookie) |
		       FIELD_PREP(BUFFER_ADDR_INFO1_RET_BUF_MGR, manager);
पूर्ण

व्योम ath11k_hal_rx_buf_addr_info_get(व्योम *desc, dma_addr_t *paddr,
				     u32 *cookie, u8 *rbm)
अणु
	काष्ठा ath11k_buffer_addr *binfo = (काष्ठा ath11k_buffer_addr *)desc;

	*paddr =
		(((u64)FIELD_GET(BUFFER_ADDR_INFO1_ADDR, binfo->info1)) << 32) |
		FIELD_GET(BUFFER_ADDR_INFO0_ADDR, binfo->info0);
	*cookie = FIELD_GET(BUFFER_ADDR_INFO1_SW_COOKIE, binfo->info1);
	*rbm = FIELD_GET(BUFFER_ADDR_INFO1_RET_BUF_MGR, binfo->info1);
पूर्ण

व्योम ath11k_hal_rx_msdu_link_info_get(व्योम *link_desc, u32 *num_msdus,
				      u32 *msdu_cookies,
				      क्रमागत hal_rx_buf_वापस_buf_manager *rbm)
अणु
	काष्ठा hal_rx_msdu_link *link = (काष्ठा hal_rx_msdu_link *)link_desc;
	काष्ठा hal_rx_msdu_details *msdu;
	पूर्णांक i;

	*num_msdus = HAL_NUM_RX_MSDUS_PER_LINK_DESC;

	msdu = &link->msdu_link[0];
	*rbm = FIELD_GET(BUFFER_ADDR_INFO1_RET_BUF_MGR,
			 msdu->buf_addr_info.info1);

	क्रम (i = 0; i < *num_msdus; i++) अणु
		msdu = &link->msdu_link[i];

		अगर (!FIELD_GET(BUFFER_ADDR_INFO0_ADDR,
			       msdu->buf_addr_info.info0)) अणु
			*num_msdus = i;
			अवरोध;
		पूर्ण
		*msdu_cookies = FIELD_GET(BUFFER_ADDR_INFO1_SW_COOKIE,
					  msdu->buf_addr_info.info1);
		msdu_cookies++;
	पूर्ण
पूर्ण

पूर्णांक ath11k_hal_desc_reo_parse_err(काष्ठा ath11k_base *ab, u32 *rx_desc,
				  dma_addr_t *paddr, u32 *desc_bank)
अणु
	काष्ठा hal_reo_dest_ring *desc = (काष्ठा hal_reo_dest_ring *)rx_desc;
	क्रमागत hal_reo_dest_ring_push_reason push_reason;
	क्रमागत hal_reo_dest_ring_error_code err_code;

	push_reason = FIELD_GET(HAL_REO_DEST_RING_INFO0_PUSH_REASON,
				desc->info0);
	err_code = FIELD_GET(HAL_REO_DEST_RING_INFO0_ERROR_CODE,
			     desc->info0);
	ab->soc_stats.reo_error[err_code]++;

	अगर (push_reason != HAL_REO_DEST_RING_PUSH_REASON_ERR_DETECTED &&
	    push_reason != HAL_REO_DEST_RING_PUSH_REASON_ROUTING_INSTRUCTION) अणु
		ath11k_warn(ab, "expected error push reason code, received %d\n",
			    push_reason);
		वापस -EINVAL;
	पूर्ण

	अगर (FIELD_GET(HAL_REO_DEST_RING_INFO0_BUFFER_TYPE, desc->info0) !=
	    HAL_REO_DEST_RING_BUFFER_TYPE_LINK_DESC) अणु
		ath11k_warn(ab, "expected buffer type link_desc");
		वापस -EINVAL;
	पूर्ण

	ath11k_hal_rx_reo_ent_paddr_get(ab, rx_desc, paddr, desc_bank);

	वापस 0;
पूर्ण

पूर्णांक ath11k_hal_wbm_desc_parse_err(काष्ठा ath11k_base *ab, व्योम *desc,
				  काष्ठा hal_rx_wbm_rel_info *rel_info)
अणु
	काष्ठा hal_wbm_release_ring *wbm_desc = desc;
	क्रमागत hal_wbm_rel_desc_type type;
	क्रमागत hal_wbm_rel_src_module rel_src;

	type = FIELD_GET(HAL_WBM_RELEASE_INFO0_DESC_TYPE,
			 wbm_desc->info0);
	/* We expect only WBM_REL buffer type */
	अगर (type != HAL_WBM_REL_DESC_TYPE_REL_MSDU) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	rel_src = FIELD_GET(HAL_WBM_RELEASE_INFO0_REL_SRC_MODULE,
			    wbm_desc->info0);
	अगर (rel_src != HAL_WBM_REL_SRC_MODULE_RXDMA &&
	    rel_src != HAL_WBM_REL_SRC_MODULE_REO)
		वापस -EINVAL;

	अगर (FIELD_GET(BUFFER_ADDR_INFO1_RET_BUF_MGR,
		      wbm_desc->buf_addr_info.info1) != HAL_RX_BUF_RBM_SW3_BM) अणु
		ab->soc_stats.invalid_rbm++;
		वापस -EINVAL;
	पूर्ण

	rel_info->cookie = FIELD_GET(BUFFER_ADDR_INFO1_SW_COOKIE,
				     wbm_desc->buf_addr_info.info1);
	rel_info->err_rel_src = rel_src;
	अगर (rel_src == HAL_WBM_REL_SRC_MODULE_REO) अणु
		rel_info->push_reason =
			FIELD_GET(HAL_WBM_RELEASE_INFO0_REO_PUSH_REASON,
				  wbm_desc->info0);
		rel_info->err_code =
			FIELD_GET(HAL_WBM_RELEASE_INFO0_REO_ERROR_CODE,
				  wbm_desc->info0);
	पूर्ण अन्यथा अणु
		rel_info->push_reason =
			FIELD_GET(HAL_WBM_RELEASE_INFO0_RXDMA_PUSH_REASON,
				  wbm_desc->info0);
		rel_info->err_code =
			FIELD_GET(HAL_WBM_RELEASE_INFO0_RXDMA_ERROR_CODE,
				  wbm_desc->info0);
	पूर्ण

	rel_info->first_msdu = FIELD_GET(HAL_WBM_RELEASE_INFO2_FIRST_MSDU,
					 wbm_desc->info2);
	rel_info->last_msdu = FIELD_GET(HAL_WBM_RELEASE_INFO2_LAST_MSDU,
					wbm_desc->info2);
	वापस 0;
पूर्ण

व्योम ath11k_hal_rx_reo_ent_paddr_get(काष्ठा ath11k_base *ab, व्योम *desc,
				     dma_addr_t *paddr, u32 *desc_bank)
अणु
	काष्ठा ath11k_buffer_addr *buff_addr = desc;

	*paddr = ((u64)(FIELD_GET(BUFFER_ADDR_INFO1_ADDR, buff_addr->info1)) << 32) |
		  FIELD_GET(BUFFER_ADDR_INFO0_ADDR, buff_addr->info0);

	*desc_bank = FIELD_GET(BUFFER_ADDR_INFO1_SW_COOKIE, buff_addr->info1);
पूर्ण

व्योम ath11k_hal_rx_msdu_link_desc_set(काष्ठा ath11k_base *ab, व्योम *desc,
				      व्योम *link_desc,
				      क्रमागत hal_wbm_rel_bm_act action)
अणु
	काष्ठा hal_wbm_release_ring *dst_desc = desc;
	काष्ठा hal_wbm_release_ring *src_desc = link_desc;

	dst_desc->buf_addr_info = src_desc->buf_addr_info;
	dst_desc->info0 |= FIELD_PREP(HAL_WBM_RELEASE_INFO0_REL_SRC_MODULE,
				      HAL_WBM_REL_SRC_MODULE_SW) |
			   FIELD_PREP(HAL_WBM_RELEASE_INFO0_BM_ACTION, action) |
			   FIELD_PREP(HAL_WBM_RELEASE_INFO0_DESC_TYPE,
				      HAL_WBM_REL_DESC_TYPE_MSDU_LINK);
पूर्ण

व्योम ath11k_hal_reo_status_queue_stats(काष्ठा ath11k_base *ab, u32 *reo_desc,
				       काष्ठा hal_reo_status *status)
अणु
	काष्ठा hal_tlv_hdr *tlv = (काष्ठा hal_tlv_hdr *)reo_desc;
	काष्ठा hal_reo_get_queue_stats_status *desc =
		(काष्ठा hal_reo_get_queue_stats_status *)tlv->value;

	status->unअगरorm_hdr.cmd_num =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_STATUS_NUM,
					  desc->hdr.info0);
	status->unअगरorm_hdr.cmd_status =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_EXEC_STATUS,
					  desc->hdr.info0);

	ath11k_dbg(ab, ATH11k_DBG_HAL, "Queue stats status:\n");
	ath11k_dbg(ab, ATH11k_DBG_HAL, "header: cmd_num %d status %d\n",
		   status->unअगरorm_hdr.cmd_num,
		   status->unअगरorm_hdr.cmd_status);
	ath11k_dbg(ab, ATH11k_DBG_HAL, "ssn %ld cur_idx %ld\n",
		   FIELD_GET(HAL_REO_GET_QUEUE_STATS_STATUS_INFO0_SSN,
			     desc->info0),
		   FIELD_GET(HAL_REO_GET_QUEUE_STATS_STATUS_INFO0_CUR_IDX,
			     desc->info0));
	ath11k_dbg(ab, ATH11k_DBG_HAL, "pn = [%08x, %08x, %08x, %08x]\n",
		   desc->pn[0], desc->pn[1], desc->pn[2], desc->pn[3]);
	ath11k_dbg(ab, ATH11k_DBG_HAL, "last_rx: enqueue_tstamp %08x dequeue_tstamp %08x\n",
		   desc->last_rx_enqueue_बारtamp,
		   desc->last_rx_dequeue_बारtamp);
	ath11k_dbg(ab, ATH11k_DBG_HAL, "rx_bitmap [%08x %08x %08x %08x %08x %08x %08x %08x]\n",
		   desc->rx_biपंचांगap[0], desc->rx_biपंचांगap[1], desc->rx_biपंचांगap[2],
		   desc->rx_biपंचांगap[3], desc->rx_biपंचांगap[4], desc->rx_biपंचांगap[5],
		   desc->rx_biपंचांगap[6], desc->rx_biपंचांगap[7]);
	ath11k_dbg(ab, ATH11k_DBG_HAL, "count: cur_mpdu %ld cur_msdu %ld\n",
		   FIELD_GET(HAL_REO_GET_QUEUE_STATS_STATUS_INFO1_MPDU_COUNT,
			     desc->info1),
		   FIELD_GET(HAL_REO_GET_QUEUE_STATS_STATUS_INFO1_MSDU_COUNT,
			     desc->info1));
	ath11k_dbg(ab, ATH11k_DBG_HAL, "fwd_timeout %ld fwd_bar %ld dup_count %ld\n",
		   FIELD_GET(HAL_REO_GET_QUEUE_STATS_STATUS_INFO2_TIMEOUT_COUNT,
			     desc->info2),
		   FIELD_GET(HAL_REO_GET_QUEUE_STATS_STATUS_INFO2_FDTB_COUNT,
			     desc->info2),
		   FIELD_GET(HAL_REO_GET_QUEUE_STATS_STATUS_INFO2_DUPLICATE_COUNT,
			     desc->info2));
	ath11k_dbg(ab, ATH11k_DBG_HAL, "frames_in_order %ld bar_rcvd %ld\n",
		   FIELD_GET(HAL_REO_GET_QUEUE_STATS_STATUS_INFO3_FIO_COUNT,
			     desc->info3),
		   FIELD_GET(HAL_REO_GET_QUEUE_STATS_STATUS_INFO3_BAR_RCVD_CNT,
			     desc->info3));
	ath11k_dbg(ab, ATH11k_DBG_HAL, "num_mpdus %d num_msdus %d total_bytes %d\n",
		   desc->num_mpdu_frames, desc->num_msdu_frames,
		   desc->total_bytes);
	ath11k_dbg(ab, ATH11k_DBG_HAL, "late_rcvd %ld win_jump_2k %ld hole_cnt %ld\n",
		   FIELD_GET(HAL_REO_GET_QUEUE_STATS_STATUS_INFO4_LATE_RX_MPDU,
			     desc->info4),
		   FIELD_GET(HAL_REO_GET_QUEUE_STATS_STATUS_INFO4_WINDOW_JMP2K,
			     desc->info4),
		   FIELD_GET(HAL_REO_GET_QUEUE_STATS_STATUS_INFO4_HOLE_COUNT,
			     desc->info4));
	ath11k_dbg(ab, ATH11k_DBG_HAL, "looping count %ld\n",
		   FIELD_GET(HAL_REO_GET_QUEUE_STATS_STATUS_INFO5_LOOPING_CNT,
			     desc->info5));
पूर्ण

पूर्णांक ath11k_hal_reo_process_status(u8 *reo_desc, u8 *status)
अणु
	काष्ठा hal_tlv_hdr *tlv = (काष्ठा hal_tlv_hdr *)reo_desc;
	काष्ठा hal_reo_status_hdr *hdr;

	hdr = (काष्ठा hal_reo_status_hdr *)tlv->value;
	*status = FIELD_GET(HAL_REO_STATUS_HDR_INFO0_EXEC_STATUS, hdr->info0);

	वापस FIELD_GET(HAL_REO_STATUS_HDR_INFO0_STATUS_NUM, hdr->info0);
पूर्ण

व्योम ath11k_hal_reo_flush_queue_status(काष्ठा ath11k_base *ab, u32 *reo_desc,
				       काष्ठा hal_reo_status *status)
अणु
	काष्ठा hal_tlv_hdr *tlv = (काष्ठा hal_tlv_hdr *)reo_desc;
	काष्ठा hal_reo_flush_queue_status *desc =
		(काष्ठा hal_reo_flush_queue_status *)tlv->value;

	status->unअगरorm_hdr.cmd_num =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_STATUS_NUM,
					  desc->hdr.info0);
	status->unअगरorm_hdr.cmd_status =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_EXEC_STATUS,
					  desc->hdr.info0);
	status->u.flush_queue.err_detected =
		FIELD_GET(HAL_REO_FLUSH_QUEUE_INFO0_ERR_DETECTED,
			  desc->info0);
पूर्ण

व्योम ath11k_hal_reo_flush_cache_status(काष्ठा ath11k_base *ab, u32 *reo_desc,
				       काष्ठा hal_reo_status *status)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;
	काष्ठा hal_tlv_hdr *tlv = (काष्ठा hal_tlv_hdr *)reo_desc;
	काष्ठा hal_reo_flush_cache_status *desc =
		(काष्ठा hal_reo_flush_cache_status *)tlv->value;

	status->unअगरorm_hdr.cmd_num =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_STATUS_NUM,
					  desc->hdr.info0);
	status->unअगरorm_hdr.cmd_status =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_EXEC_STATUS,
					  desc->hdr.info0);

	status->u.flush_cache.err_detected =
			FIELD_GET(HAL_REO_FLUSH_CACHE_STATUS_INFO0_IS_ERR,
				  desc->info0);
	status->u.flush_cache.err_code =
		FIELD_GET(HAL_REO_FLUSH_CACHE_STATUS_INFO0_BLOCK_ERR_CODE,
			  desc->info0);
	अगर (!status->u.flush_cache.err_code)
		hal->avail_blk_resource |= BIT(hal->current_blk_index);

	status->u.flush_cache.cache_controller_flush_status_hit =
		FIELD_GET(HAL_REO_FLUSH_CACHE_STATUS_INFO0_FLUSH_STATUS_HIT,
			  desc->info0);

	status->u.flush_cache.cache_controller_flush_status_desc_type =
		FIELD_GET(HAL_REO_FLUSH_CACHE_STATUS_INFO0_FLUSH_DESC_TYPE,
			  desc->info0);
	status->u.flush_cache.cache_controller_flush_status_client_id =
		FIELD_GET(HAL_REO_FLUSH_CACHE_STATUS_INFO0_FLUSH_CLIENT_ID,
			  desc->info0);
	status->u.flush_cache.cache_controller_flush_status_err =
		FIELD_GET(HAL_REO_FLUSH_CACHE_STATUS_INFO0_FLUSH_ERR,
			  desc->info0);
	status->u.flush_cache.cache_controller_flush_status_cnt =
		FIELD_GET(HAL_REO_FLUSH_CACHE_STATUS_INFO0_FLUSH_COUNT,
			  desc->info0);
पूर्ण

व्योम ath11k_hal_reo_unblk_cache_status(काष्ठा ath11k_base *ab, u32 *reo_desc,
				       काष्ठा hal_reo_status *status)
अणु
	काष्ठा ath11k_hal *hal = &ab->hal;
	काष्ठा hal_tlv_hdr *tlv = (काष्ठा hal_tlv_hdr *)reo_desc;
	काष्ठा hal_reo_unblock_cache_status *desc =
		(काष्ठा hal_reo_unblock_cache_status *)tlv->value;

	status->unअगरorm_hdr.cmd_num =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_STATUS_NUM,
					  desc->hdr.info0);
	status->unअगरorm_hdr.cmd_status =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_EXEC_STATUS,
					  desc->hdr.info0);

	status->u.unblock_cache.err_detected =
			FIELD_GET(HAL_REO_UNBLOCK_CACHE_STATUS_INFO0_IS_ERR,
				  desc->info0);
	status->u.unblock_cache.unblock_type =
			FIELD_GET(HAL_REO_UNBLOCK_CACHE_STATUS_INFO0_TYPE,
				  desc->info0);

	अगर (!status->u.unblock_cache.err_detected &&
	    status->u.unblock_cache.unblock_type ==
	    HAL_REO_STATUS_UNBLOCK_BLOCKING_RESOURCE)
		hal->avail_blk_resource &= ~BIT(hal->current_blk_index);
पूर्ण

व्योम ath11k_hal_reo_flush_समयout_list_status(काष्ठा ath11k_base *ab,
					      u32 *reo_desc,
					      काष्ठा hal_reo_status *status)
अणु
	काष्ठा hal_tlv_hdr *tlv = (काष्ठा hal_tlv_hdr *)reo_desc;
	काष्ठा hal_reo_flush_समयout_list_status *desc =
		(काष्ठा hal_reo_flush_समयout_list_status *)tlv->value;

	status->unअगरorm_hdr.cmd_num =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_STATUS_NUM,
					  desc->hdr.info0);
	status->unअगरorm_hdr.cmd_status =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_EXEC_STATUS,
					  desc->hdr.info0);

	status->u.समयout_list.err_detected =
			FIELD_GET(HAL_REO_FLUSH_TIMEOUT_STATUS_INFO0_IS_ERR,
				  desc->info0);
	status->u.समयout_list.list_empty =
			FIELD_GET(HAL_REO_FLUSH_TIMEOUT_STATUS_INFO0_LIST_EMPTY,
				  desc->info0);

	status->u.समयout_list.release_desc_cnt =
		FIELD_GET(HAL_REO_FLUSH_TIMEOUT_STATUS_INFO1_REL_DESC_COUNT,
			  desc->info1);
	status->u.समयout_list.fwd_buf_cnt =
		FIELD_GET(HAL_REO_FLUSH_TIMEOUT_STATUS_INFO1_FWD_BUF_COUNT,
			  desc->info1);
पूर्ण

व्योम ath11k_hal_reo_desc_thresh_reached_status(काष्ठा ath11k_base *ab,
					       u32 *reo_desc,
					       काष्ठा hal_reo_status *status)
अणु
	काष्ठा hal_tlv_hdr *tlv = (काष्ठा hal_tlv_hdr *)reo_desc;
	काष्ठा hal_reo_desc_thresh_reached_status *desc =
		(काष्ठा hal_reo_desc_thresh_reached_status *)tlv->value;

	status->unअगरorm_hdr.cmd_num =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_STATUS_NUM,
					  desc->hdr.info0);
	status->unअगरorm_hdr.cmd_status =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_EXEC_STATUS,
					  desc->hdr.info0);

	status->u.desc_thresh_reached.threshold_idx =
		FIELD_GET(HAL_REO_DESC_THRESH_STATUS_INFO0_THRESH_INDEX,
			  desc->info0);

	status->u.desc_thresh_reached.link_desc_counter0 =
		FIELD_GET(HAL_REO_DESC_THRESH_STATUS_INFO1_LINK_DESC_COUNTER0,
			  desc->info1);

	status->u.desc_thresh_reached.link_desc_counter1 =
		FIELD_GET(HAL_REO_DESC_THRESH_STATUS_INFO2_LINK_DESC_COUNTER1,
			  desc->info2);

	status->u.desc_thresh_reached.link_desc_counter2 =
		FIELD_GET(HAL_REO_DESC_THRESH_STATUS_INFO3_LINK_DESC_COUNTER2,
			  desc->info3);

	status->u.desc_thresh_reached.link_desc_counter_sum =
		FIELD_GET(HAL_REO_DESC_THRESH_STATUS_INFO4_LINK_DESC_COUNTER_SUM,
			  desc->info4);
पूर्ण

व्योम ath11k_hal_reo_update_rx_reo_queue_status(काष्ठा ath11k_base *ab,
					       u32 *reo_desc,
					       काष्ठा hal_reo_status *status)
अणु
	काष्ठा hal_tlv_hdr *tlv = (काष्ठा hal_tlv_hdr *)reo_desc;
	काष्ठा hal_reo_status_hdr *desc =
		(काष्ठा hal_reo_status_hdr *)tlv->value;

	status->unअगरorm_hdr.cmd_num =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_STATUS_NUM,
					  desc->info0);
	status->unअगरorm_hdr.cmd_status =
				FIELD_GET(HAL_REO_STATUS_HDR_INFO0_EXEC_STATUS,
					  desc->info0);
पूर्ण

u32 ath11k_hal_reo_qdesc_size(u32 ba_winकरोw_size, u8 tid)
अणु
	u32 num_ext_desc;

	अगर (ba_winकरोw_size <= 1) अणु
		अगर (tid != HAL_DESC_REO_NON_QOS_TID)
			num_ext_desc = 1;
		अन्यथा
			num_ext_desc = 0;
	पूर्ण अन्यथा अगर (ba_winकरोw_size <= 105) अणु
		num_ext_desc = 1;
	पूर्ण अन्यथा अगर (ba_winकरोw_size <= 210) अणु
		num_ext_desc = 2;
	पूर्ण अन्यथा अणु
		num_ext_desc = 3;
	पूर्ण

	वापस माप(काष्ठा hal_rx_reo_queue) +
		(num_ext_desc * माप(काष्ठा hal_rx_reo_queue_ext));
पूर्ण

व्योम ath11k_hal_reo_qdesc_setup(व्योम *vaddr, पूर्णांक tid, u32 ba_winकरोw_size,
				u32 start_seq, क्रमागत hal_pn_type type)
अणु
	काष्ठा hal_rx_reo_queue *qdesc = (काष्ठा hal_rx_reo_queue *)vaddr;
	काष्ठा hal_rx_reo_queue_ext *ext_desc;

	स_रखो(qdesc, 0, माप(*qdesc));

	ath11k_hal_reo_set_desc_hdr(&qdesc->desc_hdr, HAL_DESC_REO_OWNED,
				    HAL_DESC_REO_QUEUE_DESC,
				    REO_QUEUE_DESC_MAGIC_DEBUG_PATTERN_0);

	qdesc->rx_queue_num = FIELD_PREP(HAL_RX_REO_QUEUE_RX_QUEUE_NUMBER, tid);

	qdesc->info0 =
		FIELD_PREP(HAL_RX_REO_QUEUE_INFO0_VLD, 1) |
		FIELD_PREP(HAL_RX_REO_QUEUE_INFO0_ASSOC_LNK_DESC_COUNTER, 1) |
		FIELD_PREP(HAL_RX_REO_QUEUE_INFO0_AC, ath11k_tid_to_ac(tid));

	अगर (ba_winकरोw_size < 1)
		ba_winकरोw_size = 1;

	अगर (ba_winकरोw_size == 1 && tid != HAL_DESC_REO_NON_QOS_TID)
		ba_winकरोw_size++;

	अगर (ba_winकरोw_size == 1)
		qdesc->info0 |= FIELD_PREP(HAL_RX_REO_QUEUE_INFO0_RETRY, 1);

	qdesc->info0 |= FIELD_PREP(HAL_RX_REO_QUEUE_INFO0_BA_WINDOW_SIZE,
				   ba_winकरोw_size - 1);
	चयन (type) अणु
	हाल HAL_PN_TYPE_NONE:
	हाल HAL_PN_TYPE_WAPI_EVEN:
	हाल HAL_PN_TYPE_WAPI_UNEVEN:
		अवरोध;
	हाल HAL_PN_TYPE_WPA:
		qdesc->info0 |=
			FIELD_PREP(HAL_RX_REO_QUEUE_INFO0_PN_CHECK, 1) |
			FIELD_PREP(HAL_RX_REO_QUEUE_INFO0_PN_SIZE,
				   HAL_RX_REO_QUEUE_PN_SIZE_48);
		अवरोध;
	पूर्ण

	/* TODO: Set Ignore ampdu flags based on BA winकरोw size and/or
	 * AMPDU capabilities
	 */
	qdesc->info0 |= FIELD_PREP(HAL_RX_REO_QUEUE_INFO0_IGNORE_AMPDU_FLG, 1);

	qdesc->info1 |= FIELD_PREP(HAL_RX_REO_QUEUE_INFO1_SVLD, 0);

	अगर (start_seq <= 0xfff)
		qdesc->info1 = FIELD_PREP(HAL_RX_REO_QUEUE_INFO1_SSN,
					  start_seq);

	अगर (tid == HAL_DESC_REO_NON_QOS_TID)
		वापस;

	ext_desc = qdesc->ext_desc;

	/* TODO: HW queue descriptors are currently allocated क्रम max BA
	 * winकरोw size क्रम all QOS TIDs so that same descriptor can be used
	 * later when ADDBA request is recevied. This should be changed to
	 * allocate HW queue descriptors based on BA winकरोw size being
	 * negotiated (0 क्रम non BA हालs), and पुनः_स्मृतिate when BA winकरोw
	 * size changes and also send WMI message to FW to change the REO
	 * queue descriptor in Rx peer entry as part of dp_rx_tid_update.
	 */
	स_रखो(ext_desc, 0, 3 * माप(*ext_desc));
	ath11k_hal_reo_set_desc_hdr(&ext_desc->desc_hdr, HAL_DESC_REO_OWNED,
				    HAL_DESC_REO_QUEUE_EXT_DESC,
				    REO_QUEUE_DESC_MAGIC_DEBUG_PATTERN_1);
	ext_desc++;
	ath11k_hal_reo_set_desc_hdr(&ext_desc->desc_hdr, HAL_DESC_REO_OWNED,
				    HAL_DESC_REO_QUEUE_EXT_DESC,
				    REO_QUEUE_DESC_MAGIC_DEBUG_PATTERN_2);
	ext_desc++;
	ath11k_hal_reo_set_desc_hdr(&ext_desc->desc_hdr, HAL_DESC_REO_OWNED,
				    HAL_DESC_REO_QUEUE_EXT_DESC,
				    REO_QUEUE_DESC_MAGIC_DEBUG_PATTERN_3);
पूर्ण

व्योम ath11k_hal_reo_init_cmd_ring(काष्ठा ath11k_base *ab,
				  काष्ठा hal_srng *srng)
अणु
	काष्ठा hal_srng_params params;
	काष्ठा hal_tlv_hdr *tlv;
	काष्ठा hal_reo_get_queue_stats *desc;
	पूर्णांक i, cmd_num = 1;
	पूर्णांक entry_size;
	u8 *entry;

	स_रखो(&params, 0, माप(params));

	entry_size = ath11k_hal_srng_get_entrysize(ab, HAL_REO_CMD);
	ath11k_hal_srng_get_params(ab, srng, &params);
	entry = (u8 *)params.ring_base_vaddr;

	क्रम (i = 0; i < params.num_entries; i++) अणु
		tlv = (काष्ठा hal_tlv_hdr *)entry;
		desc = (काष्ठा hal_reo_get_queue_stats *)tlv->value;
		desc->cmd.info0 =
			FIELD_PREP(HAL_REO_CMD_HDR_INFO0_CMD_NUMBER, cmd_num++);
		entry += entry_size;
	पूर्ण
पूर्ण

व्योम ath11k_hal_reo_hw_setup(काष्ठा ath11k_base *ab, u32 ring_hash_map)
अणु
	u32 reo_base = HAL_SEQ_WCSS_UMAC_REO_REG;
	u32 val;

	val = ath11k_hअगर_पढ़ो32(ab, reo_base + HAL_REO1_GEN_ENABLE);

	val &= ~HAL_REO1_GEN_ENABLE_FRAG_DST_RING;
	val |= FIELD_PREP(HAL_REO1_GEN_ENABLE_FRAG_DST_RING,
			  HAL_SRNG_RING_ID_REO2SW1) |
	       FIELD_PREP(HAL_REO1_GEN_ENABLE_AGING_LIST_ENABLE, 1) |
	       FIELD_PREP(HAL_REO1_GEN_ENABLE_AGING_FLUSH_ENABLE, 1);
	ath11k_hअगर_ग_लिखो32(ab, reo_base + HAL_REO1_GEN_ENABLE, val);

	ath11k_hअगर_ग_लिखो32(ab, reo_base + HAL_REO1_AGING_THRESH_IX_0(ab),
			   HAL_DEFAULT_REO_TIMEOUT_USEC);
	ath11k_hअगर_ग_लिखो32(ab, reo_base + HAL_REO1_AGING_THRESH_IX_1(ab),
			   HAL_DEFAULT_REO_TIMEOUT_USEC);
	ath11k_hअगर_ग_लिखो32(ab, reo_base + HAL_REO1_AGING_THRESH_IX_2(ab),
			   HAL_DEFAULT_REO_TIMEOUT_USEC);
	ath11k_hअगर_ग_लिखो32(ab, reo_base + HAL_REO1_AGING_THRESH_IX_3(ab),
			   HAL_DEFAULT_REO_TIMEOUT_USEC);

	ath11k_hअगर_ग_लिखो32(ab, reo_base + HAL_REO1_DEST_RING_CTRL_IX_0,
			   FIELD_PREP(HAL_REO_DEST_RING_CTRL_HASH_RING_MAP,
				      ring_hash_map));
	ath11k_hअगर_ग_लिखो32(ab, reo_base + HAL_REO1_DEST_RING_CTRL_IX_1,
			   FIELD_PREP(HAL_REO_DEST_RING_CTRL_HASH_RING_MAP,
				      ring_hash_map));
	ath11k_hअगर_ग_लिखो32(ab, reo_base + HAL_REO1_DEST_RING_CTRL_IX_2,
			   FIELD_PREP(HAL_REO_DEST_RING_CTRL_HASH_RING_MAP,
				      ring_hash_map));
	ath11k_hअगर_ग_लिखो32(ab, reo_base + HAL_REO1_DEST_RING_CTRL_IX_3,
			   FIELD_PREP(HAL_REO_DEST_RING_CTRL_HASH_RING_MAP,
				      ring_hash_map));
पूर्ण

अटल क्रमागत hal_rx_mon_status
ath11k_hal_rx_parse_mon_status_tlv(काष्ठा ath11k_base *ab,
				   काष्ठा hal_rx_mon_ppdu_info *ppdu_info,
				   u32 tlv_tag, u8 *tlv_data)
अणु
	u32 info0, info1;

	चयन (tlv_tag) अणु
	हाल HAL_RX_PPDU_START: अणु
		काष्ठा hal_rx_ppdu_start *ppdu_start =
			(काष्ठा hal_rx_ppdu_start *)tlv_data;

		ppdu_info->ppdu_id =
			FIELD_GET(HAL_RX_PPDU_START_INFO0_PPDU_ID,
				  __le32_to_cpu(ppdu_start->info0));
		ppdu_info->chan_num = __le32_to_cpu(ppdu_start->chan_num);
		ppdu_info->ppdu_ts = __le32_to_cpu(ppdu_start->ppdu_start_ts);
		अवरोध;
	पूर्ण
	हाल HAL_RX_PPDU_END_USER_STATS: अणु
		काष्ठा hal_rx_ppdu_end_user_stats *eu_stats =
			(काष्ठा hal_rx_ppdu_end_user_stats *)tlv_data;

		info0 = __le32_to_cpu(eu_stats->info0);
		info1 = __le32_to_cpu(eu_stats->info1);

		ppdu_info->tid =
			ffs(FIELD_GET(HAL_RX_PPDU_END_USER_STATS_INFO6_TID_BITMAP,
				      __le32_to_cpu(eu_stats->info6))) - 1;
		ppdu_info->tcp_msdu_count =
			FIELD_GET(HAL_RX_PPDU_END_USER_STATS_INFO4_TCP_MSDU_CNT,
				  __le32_to_cpu(eu_stats->info4));
		ppdu_info->udp_msdu_count =
			FIELD_GET(HAL_RX_PPDU_END_USER_STATS_INFO4_UDP_MSDU_CNT,
				  __le32_to_cpu(eu_stats->info4));
		ppdu_info->other_msdu_count =
			FIELD_GET(HAL_RX_PPDU_END_USER_STATS_INFO5_OTHER_MSDU_CNT,
				  __le32_to_cpu(eu_stats->info5));
		ppdu_info->tcp_ack_msdu_count =
			FIELD_GET(HAL_RX_PPDU_END_USER_STATS_INFO5_TCP_ACK_MSDU_CNT,
				  __le32_to_cpu(eu_stats->info5));
		ppdu_info->preamble_type =
			FIELD_GET(HAL_RX_PPDU_END_USER_STATS_INFO1_PKT_TYPE, info1);
		ppdu_info->num_mpdu_fcs_ok =
			FIELD_GET(HAL_RX_PPDU_END_USER_STATS_INFO1_MPDU_CNT_FCS_OK,
				  info1);
		ppdu_info->num_mpdu_fcs_err =
			FIELD_GET(HAL_RX_PPDU_END_USER_STATS_INFO0_MPDU_CNT_FCS_ERR,
				  info0);
		अवरोध;
	पूर्ण
	हाल HAL_PHYRX_HT_SIG: अणु
		काष्ठा hal_rx_ht_sig_info *ht_sig =
			(काष्ठा hal_rx_ht_sig_info *)tlv_data;

		info0 = __le32_to_cpu(ht_sig->info0);
		info1 = __le32_to_cpu(ht_sig->info1);

		ppdu_info->mcs = FIELD_GET(HAL_RX_HT_SIG_INFO_INFO0_MCS, info0);
		ppdu_info->bw = FIELD_GET(HAL_RX_HT_SIG_INFO_INFO0_BW, info0);
		ppdu_info->is_stbc = FIELD_GET(HAL_RX_HT_SIG_INFO_INFO1_STBC,
					       info1);
		ppdu_info->ldpc = FIELD_GET(HAL_RX_HT_SIG_INFO_INFO1_FEC_CODING, info1);
		ppdu_info->gi = info1 & HAL_RX_HT_SIG_INFO_INFO1_GI;

		चयन (ppdu_info->mcs) अणु
		हाल 0 ... 7:
			ppdu_info->nss = 1;
			अवरोध;
		हाल 8 ... 15:
			ppdu_info->nss = 2;
			अवरोध;
		हाल 16 ... 23:
			ppdu_info->nss = 3;
			अवरोध;
		हाल 24 ... 31:
			ppdu_info->nss = 4;
			अवरोध;
		पूर्ण

		अगर (ppdu_info->nss > 1)
			ppdu_info->mcs = ppdu_info->mcs % 8;

		ppdu_info->reception_type = HAL_RX_RECEPTION_TYPE_SU;
		अवरोध;
	पूर्ण
	हाल HAL_PHYRX_L_SIG_B: अणु
		काष्ठा hal_rx_lsig_b_info *lsigb =
			(काष्ठा hal_rx_lsig_b_info *)tlv_data;

		ppdu_info->rate = FIELD_GET(HAL_RX_LSIG_B_INFO_INFO0_RATE,
					    __le32_to_cpu(lsigb->info0));
		ppdu_info->reception_type = HAL_RX_RECEPTION_TYPE_SU;
		अवरोध;
	पूर्ण
	हाल HAL_PHYRX_L_SIG_A: अणु
		काष्ठा hal_rx_lsig_a_info *lsiga =
			(काष्ठा hal_rx_lsig_a_info *)tlv_data;

		ppdu_info->rate = FIELD_GET(HAL_RX_LSIG_A_INFO_INFO0_RATE,
					    __le32_to_cpu(lsiga->info0));
		ppdu_info->reception_type = HAL_RX_RECEPTION_TYPE_SU;
		अवरोध;
	पूर्ण
	हाल HAL_PHYRX_VHT_SIG_A: अणु
		काष्ठा hal_rx_vht_sig_a_info *vht_sig =
			(काष्ठा hal_rx_vht_sig_a_info *)tlv_data;
		u32 nsts;
		u32 group_id;
		u8 gi_setting;

		info0 = __le32_to_cpu(vht_sig->info0);
		info1 = __le32_to_cpu(vht_sig->info1);

		ppdu_info->ldpc = FIELD_GET(HAL_RX_VHT_SIG_A_INFO_INFO1_SU_MU_CODING,
					    info0);
		ppdu_info->mcs = FIELD_GET(HAL_RX_VHT_SIG_A_INFO_INFO1_MCS,
					   info1);
		gi_setting = FIELD_GET(HAL_RX_VHT_SIG_A_INFO_INFO1_GI_SETTING,
				       info1);
		चयन (gi_setting) अणु
		हाल HAL_RX_VHT_SIG_A_NORMAL_GI:
			ppdu_info->gi = HAL_RX_GI_0_8_US;
			अवरोध;
		हाल HAL_RX_VHT_SIG_A_SHORT_GI:
		हाल HAL_RX_VHT_SIG_A_SHORT_GI_AMBIGUITY:
			ppdu_info->gi = HAL_RX_GI_0_4_US;
			अवरोध;
		पूर्ण

		ppdu_info->is_stbc = info0 & HAL_RX_VHT_SIG_A_INFO_INFO0_STBC;
		nsts = FIELD_GET(HAL_RX_VHT_SIG_A_INFO_INFO0_NSTS, info0);
		अगर (ppdu_info->is_stbc && nsts > 0)
			nsts = ((nsts + 1) >> 1) - 1;

		ppdu_info->nss = (nsts & VHT_SIG_SU_NSS_MASK) + 1;
		ppdu_info->bw = FIELD_GET(HAL_RX_VHT_SIG_A_INFO_INFO0_BW,
					  info0);
		ppdu_info->beamक्रमmed = info1 &
					HAL_RX_VHT_SIG_A_INFO_INFO1_BEAMFORMED;
		group_id = FIELD_GET(HAL_RX_VHT_SIG_A_INFO_INFO0_GROUP_ID,
				     info0);
		अगर (group_id == 0 || group_id == 63)
			ppdu_info->reception_type = HAL_RX_RECEPTION_TYPE_SU;
		अन्यथा
			ppdu_info->reception_type =
				HAL_RX_RECEPTION_TYPE_MU_MIMO;
		अवरोध;
	पूर्ण
	हाल HAL_PHYRX_HE_SIG_A_SU: अणु
		काष्ठा hal_rx_he_sig_a_su_info *he_sig_a =
			(काष्ठा hal_rx_he_sig_a_su_info *)tlv_data;
		u32 nsts, cp_ltf, dcm;

		info0 = __le32_to_cpu(he_sig_a->info0);
		info1 = __le32_to_cpu(he_sig_a->info1);

		ppdu_info->mcs =
			FIELD_GET(HAL_RX_HE_SIG_A_SU_INFO_INFO0_TRANSMIT_MCS,
				  info0);
		ppdu_info->bw =
			FIELD_GET(HAL_RX_HE_SIG_A_SU_INFO_INFO0_TRANSMIT_BW,
				  info0);
		ppdu_info->ldpc = FIELD_GET(HAL_RX_HE_SIG_A_SU_INFO_INFO1_CODING, info0);
		ppdu_info->is_stbc = info1 &
				     HAL_RX_HE_SIG_A_SU_INFO_INFO1_STBC;
		ppdu_info->beamक्रमmed = info1 &
					HAL_RX_HE_SIG_A_SU_INFO_INFO1_TXBF;
		dcm = info0 & HAL_RX_HE_SIG_A_SU_INFO_INFO0_DCM;
		cp_ltf = FIELD_GET(HAL_RX_HE_SIG_A_SU_INFO_INFO0_CP_LTF_SIZE,
				   info0);
		nsts = FIELD_GET(HAL_RX_HE_SIG_A_SU_INFO_INFO0_NSTS, info0);

		चयन (cp_ltf) अणु
		हाल 0:
		हाल 1:
			ppdu_info->gi = HAL_RX_GI_0_8_US;
			अवरोध;
		हाल 2:
			ppdu_info->gi = HAL_RX_GI_1_6_US;
			अवरोध;
		हाल 3:
			अगर (dcm && ppdu_info->is_stbc)
				ppdu_info->gi = HAL_RX_GI_0_8_US;
			अन्यथा
				ppdu_info->gi = HAL_RX_GI_3_2_US;
			अवरोध;
		पूर्ण

		ppdu_info->nss = nsts + 1;
		ppdu_info->dcm = dcm;
		ppdu_info->reception_type = HAL_RX_RECEPTION_TYPE_SU;
		अवरोध;
	पूर्ण
	हाल HAL_PHYRX_HE_SIG_A_MU_DL: अणु
		काष्ठा hal_rx_he_sig_a_mu_dl_info *he_sig_a_mu_dl =
			(काष्ठा hal_rx_he_sig_a_mu_dl_info *)tlv_data;

		u32 cp_ltf;

		info0 = __le32_to_cpu(he_sig_a_mu_dl->info0);
		info1 = __le32_to_cpu(he_sig_a_mu_dl->info1);

		ppdu_info->bw =
			FIELD_GET(HAL_RX_HE_SIG_A_MU_DL_INFO_INFO0_TRANSMIT_BW,
				  info0);
		cp_ltf = FIELD_GET(HAL_RX_HE_SIG_A_MU_DL_INFO_INFO0_CP_LTF_SIZE,
				   info0);

		चयन (cp_ltf) अणु
		हाल 0:
		हाल 1:
			ppdu_info->gi = HAL_RX_GI_0_8_US;
			अवरोध;
		हाल 2:
			ppdu_info->gi = HAL_RX_GI_1_6_US;
			अवरोध;
		हाल 3:
			ppdu_info->gi = HAL_RX_GI_3_2_US;
			अवरोध;
		पूर्ण

		ppdu_info->is_stbc = info1 &
				     HAL_RX_HE_SIG_A_MU_DL_INFO_INFO1_STBC;
		ppdu_info->reception_type = HAL_RX_RECEPTION_TYPE_MU_MIMO;
		अवरोध;
	पूर्ण
	हाल HAL_PHYRX_HE_SIG_B1_MU: अणु
		काष्ठा hal_rx_he_sig_b1_mu_info *he_sig_b1_mu =
			(काष्ठा hal_rx_he_sig_b1_mu_info *)tlv_data;
		u16 ru_tones;

		info0 = __le32_to_cpu(he_sig_b1_mu->info0);

		ru_tones = FIELD_GET(HAL_RX_HE_SIG_B1_MU_INFO_INFO0_RU_ALLOCATION,
				     info0);
		ppdu_info->ru_alloc = ath11k_he_ru_tones_to_nl80211_he_ru_alloc(ru_tones);
		ppdu_info->reception_type = HAL_RX_RECEPTION_TYPE_MU_MIMO;
		अवरोध;
	पूर्ण
	हाल HAL_PHYRX_HE_SIG_B2_MU: अणु
		काष्ठा hal_rx_he_sig_b2_mu_info *he_sig_b2_mu =
			(काष्ठा hal_rx_he_sig_b2_mu_info *)tlv_data;

		info0 = __le32_to_cpu(he_sig_b2_mu->info0);

		ppdu_info->mcs =
			FIELD_GET(HAL_RX_HE_SIG_B2_MU_INFO_INFO0_STA_MCS,
				  info0);
		ppdu_info->nss =
			FIELD_GET(HAL_RX_HE_SIG_B2_MU_INFO_INFO0_STA_NSTS,
				  info0) + 1;
		ppdu_info->ldpc = FIELD_GET(HAL_RX_HE_SIG_B2_MU_INFO_INFO0_STA_CODING,
					    info0);
		अवरोध;
	पूर्ण
	हाल HAL_PHYRX_HE_SIG_B2_OFDMA: अणु
		काष्ठा hal_rx_he_sig_b2_ofdma_info *he_sig_b2_ofdma =
			(काष्ठा hal_rx_he_sig_b2_ofdma_info *)tlv_data;

		info0 = __le32_to_cpu(he_sig_b2_ofdma->info0);

		ppdu_info->mcs =
			FIELD_GET(HAL_RX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_MCS,
				  info0);
		ppdu_info->nss =
			FIELD_GET(HAL_RX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_NSTS,
				  info0) + 1;
		ppdu_info->beamक्रमmed =
			info0 &
			HAL_RX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_TXBF;
		ppdu_info->ldpc = FIELD_GET(HAL_RX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_CODING,
					    info0);
		ppdu_info->reception_type = HAL_RX_RECEPTION_TYPE_MU_OFDMA;
		अवरोध;
	पूर्ण
	हाल HAL_PHYRX_RSSI_LEGACY: अणु
		काष्ठा hal_rx_phyrx_rssi_legacy_info *rssi =
			(काष्ठा hal_rx_phyrx_rssi_legacy_info *)tlv_data;

		/* TODO: Please note that the combined rssi will not be accurate
		 * in MU हाल. Rssi in MU needs to be retrieved from
		 * PHYRX_OTHER_RECEIVE_INFO TLV.
		 */
		ppdu_info->rssi_comb =
			FIELD_GET(HAL_RX_PHYRX_RSSI_LEGACY_INFO_INFO1_RSSI_COMB,
				  __le32_to_cpu(rssi->info0));
		अवरोध;
	पूर्ण
	हाल HAL_RX_MPDU_START: अणु
		काष्ठा hal_rx_mpdu_info *mpdu_info =
			(काष्ठा hal_rx_mpdu_info *)tlv_data;
		u16 peer_id;

		peer_id = FIELD_GET(HAL_RX_MPDU_INFO_INFO0_PEERID,
				    __le32_to_cpu(mpdu_info->info0));
		अगर (peer_id)
			ppdu_info->peer_id = peer_id;
		अवरोध;
	पूर्ण
	हाल HAL_RXPCU_PPDU_END_INFO: अणु
		काष्ठा hal_rx_ppdu_end_duration *ppdu_rx_duration =
			(काष्ठा hal_rx_ppdu_end_duration *)tlv_data;
		ppdu_info->rx_duration =
			FIELD_GET(HAL_RX_PPDU_END_DURATION,
				  __le32_to_cpu(ppdu_rx_duration->info0));
		अवरोध;
	पूर्ण
	हाल HAL_DUMMY:
		वापस HAL_RX_MON_STATUS_BUF_DONE;
	हाल HAL_RX_PPDU_END_STATUS_DONE:
	हाल 0:
		वापस HAL_RX_MON_STATUS_PPDU_DONE;
	शेष:
		अवरोध;
	पूर्ण

	वापस HAL_RX_MON_STATUS_PPDU_NOT_DONE;
पूर्ण

क्रमागत hal_rx_mon_status
ath11k_hal_rx_parse_mon_status(काष्ठा ath11k_base *ab,
			       काष्ठा hal_rx_mon_ppdu_info *ppdu_info,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा hal_tlv_hdr *tlv;
	क्रमागत hal_rx_mon_status hal_status = HAL_RX_MON_STATUS_BUF_DONE;
	u16 tlv_tag;
	u16 tlv_len;
	u8 *ptr = skb->data;

	करो अणु
		tlv = (काष्ठा hal_tlv_hdr *)ptr;
		tlv_tag = FIELD_GET(HAL_TLV_HDR_TAG, tlv->tl);
		tlv_len = FIELD_GET(HAL_TLV_HDR_LEN, tlv->tl);
		ptr += माप(*tlv);

		/* The actual length of PPDU_END is the combined length of many PHY
		 * TLVs that follow. Skip the TLV header and
		 * rx_rxpcu_classअगरication_overview that follows the header to get to
		 * next TLV.
		 */
		अगर (tlv_tag == HAL_RX_PPDU_END)
			tlv_len = माप(काष्ठा hal_rx_rxpcu_classअगरication_overview);

		hal_status = ath11k_hal_rx_parse_mon_status_tlv(ab, ppdu_info,
								tlv_tag, ptr);
		ptr += tlv_len;
		ptr = PTR_ALIGN(ptr, HAL_TLV_ALIGN);

		अगर ((ptr - skb->data) >= DP_RX_BUFFER_SIZE)
			अवरोध;
	पूर्ण जबतक (hal_status == HAL_RX_MON_STATUS_PPDU_NOT_DONE);

	वापस hal_status;
पूर्ण

व्योम ath11k_hal_rx_reo_ent_buf_paddr_get(व्योम *rx_desc, dma_addr_t *paddr,
					 u32 *sw_cookie, व्योम **pp_buf_addr,
					 u8 *rbm, u32 *msdu_cnt)
अणु
	काष्ठा hal_reo_entrance_ring *reo_ent_ring =
		(काष्ठा hal_reo_entrance_ring *)rx_desc;
	काष्ठा ath11k_buffer_addr *buf_addr_info;
	काष्ठा rx_mpdu_desc *rx_mpdu_desc_info_details;

	rx_mpdu_desc_info_details =
			(काष्ठा rx_mpdu_desc *)&reo_ent_ring->rx_mpdu_info;

	*msdu_cnt = FIELD_GET(RX_MPDU_DESC_INFO0_MSDU_COUNT,
			      rx_mpdu_desc_info_details->info0);

	buf_addr_info = (काष्ठा ath11k_buffer_addr *)&reo_ent_ring->buf_addr_info;

	*paddr = (((u64)FIELD_GET(BUFFER_ADDR_INFO1_ADDR,
				  buf_addr_info->info1)) << 32) |
			FIELD_GET(BUFFER_ADDR_INFO0_ADDR,
				  buf_addr_info->info0);

	*sw_cookie = FIELD_GET(BUFFER_ADDR_INFO1_SW_COOKIE,
			       buf_addr_info->info1);
	*rbm = FIELD_GET(BUFFER_ADDR_INFO1_RET_BUF_MGR,
			 buf_addr_info->info1);

	*pp_buf_addr = (व्योम *)buf_addr_info;
पूर्ण
