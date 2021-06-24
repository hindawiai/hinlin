<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश <crypto/hash.h>
#समावेश "core.h"
#समावेश "dp_tx.h"
#समावेश "hal_tx.h"
#समावेश "hif.h"
#समावेश "debug.h"
#समावेश "dp_rx.h"
#समावेश "peer.h"

अटल व्योम ath11k_dp_htt_htc_tx_complete(काष्ठा ath11k_base *ab,
					  काष्ठा sk_buff *skb)
अणु
	dev_kमुक्त_skb_any(skb);
पूर्ण

व्योम ath11k_dp_peer_cleanup(काष्ठा ath11k *ar, पूर्णांक vdev_id, स्थिर u8 *addr)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_peer *peer;

	/* TODO: Any other peer specअगरic DP cleanup */

	spin_lock_bh(&ab->base_lock);
	peer = ath11k_peer_find(ab, vdev_id, addr);
	अगर (!peer) अणु
		ath11k_warn(ab, "failed to lookup peer %pM on vdev %d\n",
			    addr, vdev_id);
		spin_unlock_bh(&ab->base_lock);
		वापस;
	पूर्ण

	ath11k_peer_rx_tid_cleanup(ar, peer);
	crypto_मुक्त_shash(peer->tfm_mmic);
	spin_unlock_bh(&ab->base_lock);
पूर्ण

पूर्णांक ath11k_dp_peer_setup(काष्ठा ath11k *ar, पूर्णांक vdev_id, स्थिर u8 *addr)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_peer *peer;
	u32 reo_dest;
	पूर्णांक ret = 0, tid;

	/* NOTE: reo_dest ring id starts from 1 unlike mac_id which starts from 0 */
	reo_dest = ar->dp.mac_id + 1;
	ret = ath11k_wmi_set_peer_param(ar, addr, vdev_id,
					WMI_PEER_SET_DEFAULT_ROUTING,
					DP_RX_HASH_ENABLE | (reo_dest << 1));

	अगर (ret) अणु
		ath11k_warn(ab, "failed to set default routing %d peer :%pM vdev_id :%d\n",
			    ret, addr, vdev_id);
		वापस ret;
	पूर्ण

	क्रम (tid = 0; tid <= IEEE80211_NUM_TIDS; tid++) अणु
		ret = ath11k_peer_rx_tid_setup(ar, addr, vdev_id, tid, 1, 0,
					       HAL_PN_TYPE_NONE);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to setup rxd tid queue for tid %d: %d\n",
				    tid, ret);
			जाओ peer_clean;
		पूर्ण
	पूर्ण

	ret = ath11k_peer_rx_frag_setup(ar, addr, vdev_id);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to setup rx defrag context\n");
		वापस ret;
	पूर्ण

	/* TODO: Setup other peer specअगरic resource used in data path */

	वापस 0;

peer_clean:
	spin_lock_bh(&ab->base_lock);

	peer = ath11k_peer_find(ab, vdev_id, addr);
	अगर (!peer) अणु
		ath11k_warn(ab, "failed to find the peer to del rx tid\n");
		spin_unlock_bh(&ab->base_lock);
		वापस -ENOENT;
	पूर्ण

	क्रम (; tid >= 0; tid--)
		ath11k_peer_rx_tid_delete(ar, peer, tid);

	spin_unlock_bh(&ab->base_lock);

	वापस ret;
पूर्ण

व्योम ath11k_dp_srng_cleanup(काष्ठा ath11k_base *ab, काष्ठा dp_srng *ring)
अणु
	अगर (!ring->vaddr_unaligned)
		वापस;

	dma_मुक्त_coherent(ab->dev, ring->size, ring->vaddr_unaligned,
			  ring->paddr_unaligned);

	ring->vaddr_unaligned = शून्य;
पूर्ण

अटल पूर्णांक ath11k_dp_srng_find_ring_in_mask(पूर्णांक ring_num, स्थिर u8 *grp_mask)
अणु
	पूर्णांक ext_group_num;
	u8 mask = 1 << ring_num;

	क्रम (ext_group_num = 0; ext_group_num < ATH11K_EXT_IRQ_GRP_NUM_MAX;
	     ext_group_num++) अणु
		अगर (mask & grp_mask[ext_group_num])
			वापस ext_group_num;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक ath11k_dp_srng_calculate_msi_group(काष्ठा ath11k_base *ab,
					      क्रमागत hal_ring_type type, पूर्णांक ring_num)
अणु
	स्थिर u8 *grp_mask;

	चयन (type) अणु
	हाल HAL_WBM2SW_RELEASE:
		अगर (ring_num < 3) अणु
			grp_mask = &ab->hw_params.ring_mask->tx[0];
		पूर्ण अन्यथा अगर (ring_num == 3) अणु
			grp_mask = &ab->hw_params.ring_mask->rx_wbm_rel[0];
			ring_num = 0;
		पूर्ण अन्यथा अणु
			वापस -ENOENT;
		पूर्ण
		अवरोध;
	हाल HAL_REO_EXCEPTION:
		grp_mask = &ab->hw_params.ring_mask->rx_err[0];
		अवरोध;
	हाल HAL_REO_DST:
		grp_mask = &ab->hw_params.ring_mask->rx[0];
		अवरोध;
	हाल HAL_REO_STATUS:
		grp_mask = &ab->hw_params.ring_mask->reo_status[0];
		अवरोध;
	हाल HAL_RXDMA_MONITOR_STATUS:
	हाल HAL_RXDMA_MONITOR_DST:
		grp_mask = &ab->hw_params.ring_mask->rx_mon_status[0];
		अवरोध;
	हाल HAL_RXDMA_DST:
		grp_mask = &ab->hw_params.ring_mask->rxdma2host[0];
		अवरोध;
	हाल HAL_RXDMA_BUF:
		grp_mask = &ab->hw_params.ring_mask->host2rxdma[0];
		अवरोध;
	हाल HAL_RXDMA_MONITOR_BUF:
	हाल HAL_TCL_DATA:
	हाल HAL_TCL_CMD:
	हाल HAL_REO_CMD:
	हाल HAL_SW2WBM_RELEASE:
	हाल HAL_WBM_IDLE_LINK:
	हाल HAL_TCL_STATUS:
	हाल HAL_REO_REINJECT:
	हाल HAL_CE_SRC:
	हाल HAL_CE_DST:
	हाल HAL_CE_DST_STATUS:
	शेष:
		वापस -ENOENT;
	पूर्ण

	वापस ath11k_dp_srng_find_ring_in_mask(ring_num, grp_mask);
पूर्ण

अटल व्योम ath11k_dp_srng_msi_setup(काष्ठा ath11k_base *ab,
				     काष्ठा hal_srng_params *ring_params,
				     क्रमागत hal_ring_type type, पूर्णांक ring_num)
अणु
	पूर्णांक msi_group_number, msi_data_count;
	u32 msi_data_start, msi_irq_start, addr_lo, addr_hi;
	पूर्णांक ret;

	ret = ath11k_get_user_msi_vector(ab, "DP",
					 &msi_data_count, &msi_data_start,
					 &msi_irq_start);
	अगर (ret)
		वापस;

	msi_group_number = ath11k_dp_srng_calculate_msi_group(ab, type,
							      ring_num);
	अगर (msi_group_number < 0) अणु
		ath11k_dbg(ab, ATH11K_DBG_PCI,
			   "ring not part of an ext_group; ring_type: %d,ring_num %d",
			   type, ring_num);
		ring_params->msi_addr = 0;
		ring_params->msi_data = 0;
		वापस;
	पूर्ण

	अगर (msi_group_number > msi_data_count) अणु
		ath11k_dbg(ab, ATH11K_DBG_PCI,
			   "multiple msi_groups share one msi, msi_group_num %d",
			   msi_group_number);
	पूर्ण

	ath11k_get_msi_address(ab, &addr_lo, &addr_hi);

	ring_params->msi_addr = addr_lo;
	ring_params->msi_addr |= (dma_addr_t)(((uपूर्णांक64_t)addr_hi) << 32);
	ring_params->msi_data = (msi_group_number % msi_data_count)
		+ msi_data_start;
	ring_params->flags |= HAL_SRNG_FLAGS_MSI_INTR;
पूर्ण

पूर्णांक ath11k_dp_srng_setup(काष्ठा ath11k_base *ab, काष्ठा dp_srng *ring,
			 क्रमागत hal_ring_type type, पूर्णांक ring_num,
			 पूर्णांक mac_id, पूर्णांक num_entries)
अणु
	काष्ठा hal_srng_params params = अणु 0 पूर्ण;
	पूर्णांक entry_sz = ath11k_hal_srng_get_entrysize(ab, type);
	पूर्णांक max_entries = ath11k_hal_srng_get_max_entries(ab, type);
	पूर्णांक ret;

	अगर (max_entries < 0 || entry_sz < 0)
		वापस -EINVAL;

	अगर (num_entries > max_entries)
		num_entries = max_entries;

	ring->size = (num_entries * entry_sz) + HAL_RING_BASE_ALIGN - 1;
	ring->vaddr_unaligned = dma_alloc_coherent(ab->dev, ring->size,
						   &ring->paddr_unaligned,
						   GFP_KERNEL);
	अगर (!ring->vaddr_unaligned)
		वापस -ENOMEM;

	ring->vaddr = PTR_ALIGN(ring->vaddr_unaligned, HAL_RING_BASE_ALIGN);
	ring->paddr = ring->paddr_unaligned + ((अचिन्हित दीर्घ)ring->vaddr -
		      (अचिन्हित दीर्घ)ring->vaddr_unaligned);

	params.ring_base_vaddr = ring->vaddr;
	params.ring_base_paddr = ring->paddr;
	params.num_entries = num_entries;
	ath11k_dp_srng_msi_setup(ab, &params, type, ring_num + mac_id);

	चयन (type) अणु
	हाल HAL_REO_DST:
		params.पूर्णांकr_batch_cntr_thres_entries =
					HAL_SRNG_INT_BATCH_THRESHOLD_RX;
		params.पूर्णांकr_समयr_thres_us = HAL_SRNG_INT_TIMER_THRESHOLD_RX;
		अवरोध;
	हाल HAL_RXDMA_BUF:
	हाल HAL_RXDMA_MONITOR_BUF:
	हाल HAL_RXDMA_MONITOR_STATUS:
		params.low_threshold = num_entries >> 3;
		params.flags |= HAL_SRNG_FLAGS_LOW_THRESH_INTR_EN;
		params.पूर्णांकr_batch_cntr_thres_entries = 0;
		params.पूर्णांकr_समयr_thres_us = HAL_SRNG_INT_TIMER_THRESHOLD_RX;
		अवरोध;
	हाल HAL_WBM2SW_RELEASE:
		अगर (ring_num < 3) अणु
			params.पूर्णांकr_batch_cntr_thres_entries =
					HAL_SRNG_INT_BATCH_THRESHOLD_TX;
			params.पूर्णांकr_समयr_thres_us =
					HAL_SRNG_INT_TIMER_THRESHOLD_TX;
			अवरोध;
		पूर्ण
		/* follow through when ring_num >= 3 */
		fallthrough;
	हाल HAL_REO_EXCEPTION:
	हाल HAL_REO_REINJECT:
	हाल HAL_REO_CMD:
	हाल HAL_REO_STATUS:
	हाल HAL_TCL_DATA:
	हाल HAL_TCL_CMD:
	हाल HAL_TCL_STATUS:
	हाल HAL_WBM_IDLE_LINK:
	हाल HAL_SW2WBM_RELEASE:
	हाल HAL_RXDMA_DST:
	हाल HAL_RXDMA_MONITOR_DST:
	हाल HAL_RXDMA_MONITOR_DESC:
		params.पूर्णांकr_batch_cntr_thres_entries =
					HAL_SRNG_INT_BATCH_THRESHOLD_OTHER;
		params.पूर्णांकr_समयr_thres_us = HAL_SRNG_INT_TIMER_THRESHOLD_OTHER;
		अवरोध;
	हाल HAL_RXDMA_सूची_BUF:
		अवरोध;
	शेष:
		ath11k_warn(ab, "Not a valid ring type in dp :%d\n", type);
		वापस -EINVAL;
	पूर्ण

	ret = ath11k_hal_srng_setup(ab, type, ring_num, mac_id, &params);
	अगर (ret < 0) अणु
		ath11k_warn(ab, "failed to setup srng: %d ring_id %d\n",
			    ret, ring_num);
		वापस ret;
	पूर्ण

	ring->ring_id = ret;

	वापस 0;
पूर्ण

व्योम ath11k_dp_stop_shaकरोw_समयrs(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	अगर (!ab->hw_params.supports_shaकरोw_regs)
		वापस;

	क्रम (i = 0; i < DP_TCL_NUM_RING_MAX; i++)
		ath11k_dp_shaकरोw_stop_समयr(ab, &ab->dp.tx_ring_समयr[i]);

	ath11k_dp_shaकरोw_stop_समयr(ab, &ab->dp.reo_cmd_समयr);
पूर्ण

अटल व्योम ath11k_dp_srng_common_cleanup(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	पूर्णांक i;

	ath11k_dp_stop_shaकरोw_समयrs(ab);
	ath11k_dp_srng_cleanup(ab, &dp->wbm_desc_rel_ring);
	ath11k_dp_srng_cleanup(ab, &dp->tcl_cmd_ring);
	ath11k_dp_srng_cleanup(ab, &dp->tcl_status_ring);
	क्रम (i = 0; i < DP_TCL_NUM_RING_MAX; i++) अणु
		ath11k_dp_srng_cleanup(ab, &dp->tx_ring[i].tcl_data_ring);
		ath11k_dp_srng_cleanup(ab, &dp->tx_ring[i].tcl_comp_ring);
	पूर्ण
	ath11k_dp_srng_cleanup(ab, &dp->reo_reinject_ring);
	ath11k_dp_srng_cleanup(ab, &dp->rx_rel_ring);
	ath11k_dp_srng_cleanup(ab, &dp->reo_except_ring);
	ath11k_dp_srng_cleanup(ab, &dp->reo_cmd_ring);
	ath11k_dp_srng_cleanup(ab, &dp->reo_status_ring);
पूर्ण

अटल पूर्णांक ath11k_dp_srng_common_setup(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा hal_srng *srng;
	पूर्णांक i, ret;
	u32 ring_hash_map;

	ret = ath11k_dp_srng_setup(ab, &dp->wbm_desc_rel_ring,
				   HAL_SW2WBM_RELEASE, 0, 0,
				   DP_WBM_RELEASE_RING_SIZE);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set up wbm2sw_release ring :%d\n",
			    ret);
		जाओ err;
	पूर्ण

	ret = ath11k_dp_srng_setup(ab, &dp->tcl_cmd_ring, HAL_TCL_CMD, 0, 0,
				   DP_TCL_CMD_RING_SIZE);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set up tcl_cmd ring :%d\n", ret);
		जाओ err;
	पूर्ण

	ret = ath11k_dp_srng_setup(ab, &dp->tcl_status_ring, HAL_TCL_STATUS,
				   0, 0, DP_TCL_STATUS_RING_SIZE);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set up tcl_status ring :%d\n", ret);
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < DP_TCL_NUM_RING_MAX; i++) अणु
		ret = ath11k_dp_srng_setup(ab, &dp->tx_ring[i].tcl_data_ring,
					   HAL_TCL_DATA, i, 0,
					   DP_TCL_DATA_RING_SIZE);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to set up tcl_data ring (%d) :%d\n",
				    i, ret);
			जाओ err;
		पूर्ण

		ret = ath11k_dp_srng_setup(ab, &dp->tx_ring[i].tcl_comp_ring,
					   HAL_WBM2SW_RELEASE, i, 0,
					   DP_TX_COMP_RING_SIZE);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to set up tcl_comp ring (%d) :%d\n",
				    i, ret);
			जाओ err;
		पूर्ण

		srng = &ab->hal.srng_list[dp->tx_ring[i].tcl_data_ring.ring_id];
		ath11k_hal_tx_init_data_ring(ab, srng);

		ath11k_dp_shaकरोw_init_समयr(ab, &dp->tx_ring_समयr[i],
					    ATH11K_SHADOW_DP_TIMER_INTERVAL,
					    dp->tx_ring[i].tcl_data_ring.ring_id);
	पूर्ण

	ret = ath11k_dp_srng_setup(ab, &dp->reo_reinject_ring, HAL_REO_REINJECT,
				   0, 0, DP_REO_REINJECT_RING_SIZE);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set up reo_reinject ring :%d\n",
			    ret);
		जाओ err;
	पूर्ण

	ret = ath11k_dp_srng_setup(ab, &dp->rx_rel_ring, HAL_WBM2SW_RELEASE,
				   3, 0, DP_RX_RELEASE_RING_SIZE);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set up rx_rel ring :%d\n", ret);
		जाओ err;
	पूर्ण

	ret = ath11k_dp_srng_setup(ab, &dp->reo_except_ring, HAL_REO_EXCEPTION,
				   0, 0, DP_REO_EXCEPTION_RING_SIZE);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set up reo_exception ring :%d\n",
			    ret);
		जाओ err;
	पूर्ण

	ret = ath11k_dp_srng_setup(ab, &dp->reo_cmd_ring, HAL_REO_CMD,
				   0, 0, DP_REO_CMD_RING_SIZE);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set up reo_cmd ring :%d\n", ret);
		जाओ err;
	पूर्ण

	srng = &ab->hal.srng_list[dp->reo_cmd_ring.ring_id];
	ath11k_hal_reo_init_cmd_ring(ab, srng);

	ath11k_dp_shaकरोw_init_समयr(ab, &dp->reo_cmd_समयr,
				    ATH11K_SHADOW_CTRL_TIMER_INTERVAL,
				    dp->reo_cmd_ring.ring_id);

	ret = ath11k_dp_srng_setup(ab, &dp->reo_status_ring, HAL_REO_STATUS,
				   0, 0, DP_REO_STATUS_RING_SIZE);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set up reo_status ring :%d\n", ret);
		जाओ err;
	पूर्ण

	/* When hash based routing of rx packet is enabled, 32 entries to map
	 * the hash values to the ring will be configured. Each hash entry uses
	 * three bits to map to a particular ring. The ring mapping will be
	 * 0:TCL, 1:SW1, 2:SW2, 3:SW3, 4:SW4, 5:Release, 6:FW and 7:Not used.
	 */
	ring_hash_map = HAL_HASH_ROUTING_RING_SW1 << 0 |
			HAL_HASH_ROUTING_RING_SW2 << 3 |
			HAL_HASH_ROUTING_RING_SW3 << 6 |
			HAL_HASH_ROUTING_RING_SW4 << 9 |
			HAL_HASH_ROUTING_RING_SW1 << 12 |
			HAL_HASH_ROUTING_RING_SW2 << 15 |
			HAL_HASH_ROUTING_RING_SW3 << 18 |
			HAL_HASH_ROUTING_RING_SW4 << 21;

	ath11k_hal_reo_hw_setup(ab, ring_hash_map);

	वापस 0;

err:
	ath11k_dp_srng_common_cleanup(ab);

	वापस ret;
पूर्ण

अटल व्योम ath11k_dp_scatter_idle_link_desc_cleanup(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा hal_wbm_idle_scatter_list *slist = dp->scatter_list;
	पूर्णांक i;

	क्रम (i = 0; i < DP_IDLE_SCATTER_BUFS_MAX; i++) अणु
		अगर (!slist[i].vaddr)
			जारी;

		dma_मुक्त_coherent(ab->dev, HAL_WBM_IDLE_SCATTER_BUF_SIZE_MAX,
				  slist[i].vaddr, slist[i].paddr);
		slist[i].vaddr = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_dp_scatter_idle_link_desc_setup(काष्ठा ath11k_base *ab,
						  पूर्णांक size,
						  u32 n_link_desc_bank,
						  u32 n_link_desc,
						  u32 last_bank_sz)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा dp_link_desc_bank *link_desc_banks = dp->link_desc_banks;
	काष्ठा hal_wbm_idle_scatter_list *slist = dp->scatter_list;
	u32 n_entries_per_buf;
	पूर्णांक num_scatter_buf, scatter_idx;
	काष्ठा hal_wbm_link_desc *scatter_buf;
	पूर्णांक align_bytes, n_entries;
	dma_addr_t paddr;
	पूर्णांक rem_entries;
	पूर्णांक i;
	पूर्णांक ret = 0;
	u32 end_offset;

	n_entries_per_buf = HAL_WBM_IDLE_SCATTER_BUF_SIZE /
		ath11k_hal_srng_get_entrysize(ab, HAL_WBM_IDLE_LINK);
	num_scatter_buf = DIV_ROUND_UP(size, HAL_WBM_IDLE_SCATTER_BUF_SIZE);

	अगर (num_scatter_buf > DP_IDLE_SCATTER_BUFS_MAX)
		वापस -EINVAL;

	क्रम (i = 0; i < num_scatter_buf; i++) अणु
		slist[i].vaddr = dma_alloc_coherent(ab->dev,
						    HAL_WBM_IDLE_SCATTER_BUF_SIZE_MAX,
						    &slist[i].paddr, GFP_KERNEL);
		अगर (!slist[i].vaddr) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण

	scatter_idx = 0;
	scatter_buf = slist[scatter_idx].vaddr;
	rem_entries = n_entries_per_buf;

	क्रम (i = 0; i < n_link_desc_bank; i++) अणु
		align_bytes = link_desc_banks[i].vaddr -
			      link_desc_banks[i].vaddr_unaligned;
		n_entries = (DP_LINK_DESC_ALLOC_SIZE_THRESH - align_bytes) /
			     HAL_LINK_DESC_SIZE;
		paddr = link_desc_banks[i].paddr;
		जबतक (n_entries) अणु
			ath11k_hal_set_link_desc_addr(scatter_buf, i, paddr);
			n_entries--;
			paddr += HAL_LINK_DESC_SIZE;
			अगर (rem_entries) अणु
				rem_entries--;
				scatter_buf++;
				जारी;
			पूर्ण

			rem_entries = n_entries_per_buf;
			scatter_idx++;
			scatter_buf = slist[scatter_idx].vaddr;
		पूर्ण
	पूर्ण

	end_offset = (scatter_buf - slist[scatter_idx].vaddr) *
		     माप(काष्ठा hal_wbm_link_desc);
	ath11k_hal_setup_link_idle_list(ab, slist, num_scatter_buf,
					n_link_desc, end_offset);

	वापस 0;

err:
	ath11k_dp_scatter_idle_link_desc_cleanup(ab);

	वापस ret;
पूर्ण

अटल व्योम
ath11k_dp_link_desc_bank_मुक्त(काष्ठा ath11k_base *ab,
			      काष्ठा dp_link_desc_bank *link_desc_banks)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DP_LINK_DESC_BANKS_MAX; i++) अणु
		अगर (link_desc_banks[i].vaddr_unaligned) अणु
			dma_मुक्त_coherent(ab->dev,
					  link_desc_banks[i].size,
					  link_desc_banks[i].vaddr_unaligned,
					  link_desc_banks[i].paddr_unaligned);
			link_desc_banks[i].vaddr_unaligned = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_dp_link_desc_bank_alloc(काष्ठा ath11k_base *ab,
					  काष्ठा dp_link_desc_bank *desc_bank,
					  पूर्णांक n_link_desc_bank,
					  पूर्णांक last_bank_sz)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	पूर्णांक i;
	पूर्णांक ret = 0;
	पूर्णांक desc_sz = DP_LINK_DESC_ALLOC_SIZE_THRESH;

	क्रम (i = 0; i < n_link_desc_bank; i++) अणु
		अगर (i == (n_link_desc_bank - 1) && last_bank_sz)
			desc_sz = last_bank_sz;

		desc_bank[i].vaddr_unaligned =
					dma_alloc_coherent(ab->dev, desc_sz,
							   &desc_bank[i].paddr_unaligned,
							   GFP_KERNEL);
		अगर (!desc_bank[i].vaddr_unaligned) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		desc_bank[i].vaddr = PTR_ALIGN(desc_bank[i].vaddr_unaligned,
					       HAL_LINK_DESC_ALIGN);
		desc_bank[i].paddr = desc_bank[i].paddr_unaligned +
				     ((अचिन्हित दीर्घ)desc_bank[i].vaddr -
				      (अचिन्हित दीर्घ)desc_bank[i].vaddr_unaligned);
		desc_bank[i].size = desc_sz;
	पूर्ण

	वापस 0;

err:
	ath11k_dp_link_desc_bank_मुक्त(ab, dp->link_desc_banks);

	वापस ret;
पूर्ण

व्योम ath11k_dp_link_desc_cleanup(काष्ठा ath11k_base *ab,
				 काष्ठा dp_link_desc_bank *desc_bank,
				 u32 ring_type, काष्ठा dp_srng *ring)
अणु
	ath11k_dp_link_desc_bank_मुक्त(ab, desc_bank);

	अगर (ring_type != HAL_RXDMA_MONITOR_DESC) अणु
		ath11k_dp_srng_cleanup(ab, ring);
		ath11k_dp_scatter_idle_link_desc_cleanup(ab);
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_wbm_idle_ring_setup(काष्ठा ath11k_base *ab, u32 *n_link_desc)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	u32 n_mpdu_link_desc, n_mpdu_queue_desc;
	u32 n_tx_msdu_link_desc, n_rx_msdu_link_desc;
	पूर्णांक ret = 0;

	n_mpdu_link_desc = (DP_NUM_TIDS_MAX * DP_AVG_MPDUS_PER_TID_MAX) /
			   HAL_NUM_MPDUS_PER_LINK_DESC;

	n_mpdu_queue_desc = n_mpdu_link_desc /
			    HAL_NUM_MPDU_LINKS_PER_QUEUE_DESC;

	n_tx_msdu_link_desc = (DP_NUM_TIDS_MAX * DP_AVG_FLOWS_PER_TID *
			       DP_AVG_MSDUS_PER_FLOW) /
			      HAL_NUM_TX_MSDUS_PER_LINK_DESC;

	n_rx_msdu_link_desc = (DP_NUM_TIDS_MAX * DP_AVG_MPDUS_PER_TID_MAX *
			       DP_AVG_MSDUS_PER_MPDU) /
			      HAL_NUM_RX_MSDUS_PER_LINK_DESC;

	*n_link_desc = n_mpdu_link_desc + n_mpdu_queue_desc +
		      n_tx_msdu_link_desc + n_rx_msdu_link_desc;

	अगर (*n_link_desc & (*n_link_desc - 1))
		*n_link_desc = 1 << fls(*n_link_desc);

	ret = ath11k_dp_srng_setup(ab, &dp->wbm_idle_ring,
				   HAL_WBM_IDLE_LINK, 0, 0, *n_link_desc);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to setup wbm_idle_ring: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक ath11k_dp_link_desc_setup(काष्ठा ath11k_base *ab,
			      काष्ठा dp_link_desc_bank *link_desc_banks,
			      u32 ring_type, काष्ठा hal_srng *srng,
			      u32 n_link_desc)
अणु
	u32 tot_mem_sz;
	u32 n_link_desc_bank, last_bank_sz;
	u32 entry_sz, align_bytes, n_entries;
	u32 paddr;
	u32 *desc;
	पूर्णांक i, ret;

	tot_mem_sz = n_link_desc * HAL_LINK_DESC_SIZE;
	tot_mem_sz += HAL_LINK_DESC_ALIGN;

	अगर (tot_mem_sz <= DP_LINK_DESC_ALLOC_SIZE_THRESH) अणु
		n_link_desc_bank = 1;
		last_bank_sz = tot_mem_sz;
	पूर्ण अन्यथा अणु
		n_link_desc_bank = tot_mem_sz /
				   (DP_LINK_DESC_ALLOC_SIZE_THRESH -
				    HAL_LINK_DESC_ALIGN);
		last_bank_sz = tot_mem_sz %
			       (DP_LINK_DESC_ALLOC_SIZE_THRESH -
				HAL_LINK_DESC_ALIGN);

		अगर (last_bank_sz)
			n_link_desc_bank += 1;
	पूर्ण

	अगर (n_link_desc_bank > DP_LINK_DESC_BANKS_MAX)
		वापस -EINVAL;

	ret = ath11k_dp_link_desc_bank_alloc(ab, link_desc_banks,
					     n_link_desc_bank, last_bank_sz);
	अगर (ret)
		वापस ret;

	/* Setup link desc idle list क्रम HW पूर्णांकernal usage */
	entry_sz = ath11k_hal_srng_get_entrysize(ab, ring_type);
	tot_mem_sz = entry_sz * n_link_desc;

	/* Setup scatter desc list when the total memory requirement is more */
	अगर (tot_mem_sz > DP_LINK_DESC_ALLOC_SIZE_THRESH &&
	    ring_type != HAL_RXDMA_MONITOR_DESC) अणु
		ret = ath11k_dp_scatter_idle_link_desc_setup(ab, tot_mem_sz,
							     n_link_desc_bank,
							     n_link_desc,
							     last_bank_sz);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to setup scatting idle list descriptor :%d\n",
				    ret);
			जाओ fail_desc_bank_मुक्त;
		पूर्ण

		वापस 0;
	पूर्ण

	spin_lock_bh(&srng->lock);

	ath11k_hal_srng_access_begin(ab, srng);

	क्रम (i = 0; i < n_link_desc_bank; i++) अणु
		align_bytes = link_desc_banks[i].vaddr -
			      link_desc_banks[i].vaddr_unaligned;
		n_entries = (link_desc_banks[i].size - align_bytes) /
			    HAL_LINK_DESC_SIZE;
		paddr = link_desc_banks[i].paddr;
		जबतक (n_entries &&
		       (desc = ath11k_hal_srng_src_get_next_entry(ab, srng))) अणु
			ath11k_hal_set_link_desc_addr((काष्ठा hal_wbm_link_desc *)desc,
						      i, paddr);
			n_entries--;
			paddr += HAL_LINK_DESC_SIZE;
		पूर्ण
	पूर्ण

	ath11k_hal_srng_access_end(ab, srng);

	spin_unlock_bh(&srng->lock);

	वापस 0;

fail_desc_bank_मुक्त:
	ath11k_dp_link_desc_bank_मुक्त(ab, link_desc_banks);

	वापस ret;
पूर्ण

पूर्णांक ath11k_dp_service_srng(काष्ठा ath11k_base *ab,
			   काष्ठा ath11k_ext_irq_grp *irq_grp,
			   पूर्णांक budget)
अणु
	काष्ठा napi_काष्ठा *napi = &irq_grp->napi;
	पूर्णांक grp_id = irq_grp->grp_id;
	पूर्णांक work_करोne = 0;
	पूर्णांक i = 0, j;
	पूर्णांक tot_work_करोne = 0;

	जबतक (ab->hw_params.ring_mask->tx[grp_id] >> i) अणु
		अगर (ab->hw_params.ring_mask->tx[grp_id] & BIT(i))
			ath11k_dp_tx_completion_handler(ab, i);
		i++;
	पूर्ण

	अगर (ab->hw_params.ring_mask->rx_err[grp_id]) अणु
		work_करोne = ath11k_dp_process_rx_err(ab, napi, budget);
		budget -= work_करोne;
		tot_work_करोne += work_करोne;
		अगर (budget <= 0)
			जाओ करोne;
	पूर्ण

	अगर (ab->hw_params.ring_mask->rx_wbm_rel[grp_id]) अणु
		work_करोne = ath11k_dp_rx_process_wbm_err(ab,
							 napi,
							 budget);
		budget -= work_करोne;
		tot_work_करोne += work_करोne;

		अगर (budget <= 0)
			जाओ करोne;
	पूर्ण

	अगर (ab->hw_params.ring_mask->rx[grp_id]) अणु
		i =  fls(ab->hw_params.ring_mask->rx[grp_id]) - 1;
		work_करोne = ath11k_dp_process_rx(ab, i, napi,
						 budget);
		budget -= work_करोne;
		tot_work_करोne += work_करोne;
		अगर (budget <= 0)
			जाओ करोne;
	पूर्ण

	अगर (ab->hw_params.ring_mask->rx_mon_status[grp_id]) अणु
		क्रम (i = 0; i < ab->num_radios; i++) अणु
			क्रम (j = 0; j < ab->hw_params.num_rxmda_per_pdev; j++) अणु
				पूर्णांक id = i * ab->hw_params.num_rxmda_per_pdev + j;

				अगर (ab->hw_params.ring_mask->rx_mon_status[grp_id] &
					BIT(id)) अणु
					work_करोne =
					ath11k_dp_rx_process_mon_rings(ab,
								       id,
								       napi, budget);
					budget -= work_करोne;
					tot_work_करोne += work_करोne;

					अगर (budget <= 0)
						जाओ करोne;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ab->hw_params.ring_mask->reo_status[grp_id])
		ath11k_dp_process_reo_status(ab);

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		क्रम (j = 0; j < ab->hw_params.num_rxmda_per_pdev; j++) अणु
			पूर्णांक id = i * ab->hw_params.num_rxmda_per_pdev + j;

			अगर (ab->hw_params.ring_mask->rxdma2host[grp_id] & BIT(id)) अणु
				work_करोne = ath11k_dp_process_rxdma_err(ab, id, budget);
				budget -= work_करोne;
				tot_work_करोne += work_करोne;
			पूर्ण

			अगर (budget <= 0)
				जाओ करोne;

			अगर (ab->hw_params.ring_mask->host2rxdma[grp_id] & BIT(id)) अणु
				काष्ठा ath11k *ar = ath11k_ab_to_ar(ab, id);
				काष्ठा ath11k_pdev_dp *dp = &ar->dp;
				काष्ठा dp_rxdma_ring *rx_ring = &dp->rx_refill_buf_ring;

				ath11k_dp_rxbufs_replenish(ab, id, rx_ring, 0,
							   HAL_RX_BUF_RBM_SW3_BM);
			पूर्ण
		पूर्ण
	पूर्ण
	/* TODO: Implement handler क्रम other पूर्णांकerrupts */

करोne:
	वापस tot_work_करोne;
पूर्ण
EXPORT_SYMBOL(ath11k_dp_service_srng);

व्योम ath11k_dp_pdev_मुक्त(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k *ar;
	पूर्णांक i;

	del_समयr_sync(&ab->mon_reap_समयr);

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		ar = ab->pdevs[i].ar;
		ath11k_dp_rx_pdev_मुक्त(ab, i);
		ath11k_debugfs_unरेजिस्टर(ar);
		ath11k_dp_rx_pdev_mon_detach(ar);
	पूर्ण
पूर्ण

व्योम ath11k_dp_pdev_pre_alloc(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k *ar;
	काष्ठा ath11k_pdev_dp *dp;
	पूर्णांक i;
	पूर्णांक j;

	क्रम (i = 0; i <  ab->num_radios; i++) अणु
		ar = ab->pdevs[i].ar;
		dp = &ar->dp;
		dp->mac_id = i;
		idr_init(&dp->rx_refill_buf_ring.bufs_idr);
		spin_lock_init(&dp->rx_refill_buf_ring.idr_lock);
		atomic_set(&dp->num_tx_pending, 0);
		init_रुकोqueue_head(&dp->tx_empty_रुकोq);
		क्रम (j = 0; j < ab->hw_params.num_rxmda_per_pdev; j++) अणु
			idr_init(&dp->rx_mon_status_refill_ring[j].bufs_idr);
			spin_lock_init(&dp->rx_mon_status_refill_ring[j].idr_lock);
		पूर्ण
		idr_init(&dp->rxdma_mon_buf_ring.bufs_idr);
		spin_lock_init(&dp->rxdma_mon_buf_ring.idr_lock);
	पूर्ण
पूर्ण

पूर्णांक ath11k_dp_pdev_alloc(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k *ar;
	पूर्णांक ret;
	पूर्णांक i;

	/* TODO:Per-pdev rx ring unlike tx ring which is mapped to dअगरferent AC's */
	क्रम (i = 0; i < ab->num_radios; i++) अणु
		ar = ab->pdevs[i].ar;
		ret = ath11k_dp_rx_pdev_alloc(ab, i);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to allocate pdev rx for pdev_id :%d\n",
				    i);
			जाओ err;
		पूर्ण
		ret = ath11k_dp_rx_pdev_mon_attach(ar);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to initialize mon pdev %d\n",
				    i);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	ath11k_dp_pdev_मुक्त(ab);

	वापस ret;
पूर्ण

पूर्णांक ath11k_dp_htt_connect(काष्ठा ath11k_dp *dp)
अणु
	काष्ठा ath11k_htc_svc_conn_req conn_req;
	काष्ठा ath11k_htc_svc_conn_resp conn_resp;
	पूर्णांक status;

	स_रखो(&conn_req, 0, माप(conn_req));
	स_रखो(&conn_resp, 0, माप(conn_resp));

	conn_req.ep_ops.ep_tx_complete = ath11k_dp_htt_htc_tx_complete;
	conn_req.ep_ops.ep_rx_complete = ath11k_dp_htt_htc_t2h_msg_handler;

	/* connect to control service */
	conn_req.service_id = ATH11K_HTC_SVC_ID_HTT_DATA_MSG;

	status = ath11k_htc_connect_service(&dp->ab->htc, &conn_req,
					    &conn_resp);

	अगर (status)
		वापस status;

	dp->eid = conn_resp.eid;

	वापस 0;
पूर्ण

अटल व्योम ath11k_dp_update_vdev_search(काष्ठा ath11k_vअगर *arvअगर)
अणु
	 /* When v2_map_support is true:क्रम STA mode, enable address
	  * search index, tcl uses ast_hash value in the descriptor.
	  * When v2_map_support is false: क्रम STA mode, करोnt' enable
	  * address search index.
	  */
	चयन (arvअगर->vdev_type) अणु
	हाल WMI_VDEV_TYPE_STA:
		अगर (arvअगर->ar->ab->hw_params.htt_peer_map_v2) अणु
			arvअगर->hal_addr_search_flags = HAL_TX_ADDRX_EN;
			arvअगर->search_type = HAL_TX_ADDR_SEARCH_INDEX;
		पूर्ण अन्यथा अणु
			arvअगर->hal_addr_search_flags = HAL_TX_ADDRY_EN;
			arvअगर->search_type = HAL_TX_ADDR_SEARCH_DEFAULT;
		पूर्ण
		अवरोध;
	हाल WMI_VDEV_TYPE_AP:
	हाल WMI_VDEV_TYPE_IBSS:
		arvअगर->hal_addr_search_flags = HAL_TX_ADDRX_EN;
		arvअगर->search_type = HAL_TX_ADDR_SEARCH_DEFAULT;
		अवरोध;
	हाल WMI_VDEV_TYPE_MONITOR:
	शेष:
		वापस;
	पूर्ण
पूर्ण

व्योम ath11k_dp_vdev_tx_attach(काष्ठा ath11k *ar, काष्ठा ath11k_vअगर *arvअगर)
अणु
	arvअगर->tcl_metadata |= FIELD_PREP(HTT_TCL_META_DATA_TYPE, 1) |
			       FIELD_PREP(HTT_TCL_META_DATA_VDEV_ID,
					  arvअगर->vdev_id) |
			       FIELD_PREP(HTT_TCL_META_DATA_PDEV_ID,
					  ar->pdev->pdev_id);

	/* set HTT extension valid bit to 0 by शेष */
	arvअगर->tcl_metadata &= ~HTT_TCL_META_DATA_VALID_HTT;

	ath11k_dp_update_vdev_search(arvअगर);
पूर्ण

अटल पूर्णांक ath11k_dp_tx_pending_cleanup(पूर्णांक buf_id, व्योम *skb, व्योम *ctx)
अणु
	काष्ठा ath11k_base *ab = (काष्ठा ath11k_base *)ctx;
	काष्ठा sk_buff *msdu = skb;

	dma_unmap_single(ab->dev, ATH11K_SKB_CB(msdu)->paddr, msdu->len,
			 DMA_TO_DEVICE);

	dev_kमुक्त_skb_any(msdu);

	वापस 0;
पूर्ण

व्योम ath11k_dp_मुक्त(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	पूर्णांक i;

	ath11k_dp_link_desc_cleanup(ab, dp->link_desc_banks,
				    HAL_WBM_IDLE_LINK, &dp->wbm_idle_ring);

	ath11k_dp_srng_common_cleanup(ab);

	ath11k_dp_reo_cmd_list_cleanup(ab);

	क्रम (i = 0; i < DP_TCL_NUM_RING_MAX; i++) अणु
		spin_lock_bh(&dp->tx_ring[i].tx_idr_lock);
		idr_क्रम_each(&dp->tx_ring[i].txbuf_idr,
			     ath11k_dp_tx_pending_cleanup, ab);
		idr_destroy(&dp->tx_ring[i].txbuf_idr);
		spin_unlock_bh(&dp->tx_ring[i].tx_idr_lock);
		kमुक्त(dp->tx_ring[i].tx_status);
	पूर्ण

	/* Deinit any SOC level resource */
पूर्ण

पूर्णांक ath11k_dp_alloc(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_dp *dp = &ab->dp;
	काष्ठा hal_srng *srng = शून्य;
	माप_प्रकार size = 0;
	u32 n_link_desc = 0;
	पूर्णांक ret;
	पूर्णांक i;

	dp->ab = ab;

	INIT_LIST_HEAD(&dp->reo_cmd_list);
	INIT_LIST_HEAD(&dp->reo_cmd_cache_flush_list);
	spin_lock_init(&dp->reo_cmd_lock);

	dp->reo_cmd_cache_flush_count = 0;

	ret = ath11k_wbm_idle_ring_setup(ab, &n_link_desc);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to setup wbm_idle_ring: %d\n", ret);
		वापस ret;
	पूर्ण

	srng = &ab->hal.srng_list[dp->wbm_idle_ring.ring_id];

	ret = ath11k_dp_link_desc_setup(ab, dp->link_desc_banks,
					HAL_WBM_IDLE_LINK, srng, n_link_desc);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to setup link desc: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath11k_dp_srng_common_setup(ab);
	अगर (ret)
		जाओ fail_link_desc_cleanup;

	size = माप(काष्ठा hal_wbm_release_ring) * DP_TX_COMP_RING_SIZE;

	क्रम (i = 0; i < DP_TCL_NUM_RING_MAX; i++) अणु
		idr_init(&dp->tx_ring[i].txbuf_idr);
		spin_lock_init(&dp->tx_ring[i].tx_idr_lock);
		dp->tx_ring[i].tcl_data_ring_id = i;

		dp->tx_ring[i].tx_status_head = 0;
		dp->tx_ring[i].tx_status_tail = DP_TX_COMP_RING_SIZE - 1;
		dp->tx_ring[i].tx_status = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!dp->tx_ring[i].tx_status) अणु
			ret = -ENOMEM;
			जाओ fail_cmn_srng_cleanup;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < HAL_DSCP_TID_MAP_TBL_NUM_ENTRIES_MAX; i++)
		ath11k_hal_tx_set_dscp_tid_map(ab, i);

	/* Init any SOC level resource क्रम DP */

	वापस 0;

fail_cmn_srng_cleanup:
	ath11k_dp_srng_common_cleanup(ab);

fail_link_desc_cleanup:
	ath11k_dp_link_desc_cleanup(ab, dp->link_desc_banks,
				    HAL_WBM_IDLE_LINK, &dp->wbm_idle_ring);

	वापस ret;
पूर्ण

अटल व्योम ath11k_dp_shaकरोw_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा ath11k_hp_update_समयr *update_समयr = from_समयr(update_समयr,
								 t, समयr);
	काष्ठा ath11k_base *ab = update_समयr->ab;
	काष्ठा hal_srng	*srng = &ab->hal.srng_list[update_समयr->ring_id];

	spin_lock_bh(&srng->lock);

	/* when the समयr is fired, the handler checks whether there
	 * are new TX happened. The handler updates HP only when there
	 * are no TX operations during the समयout पूर्णांकerval, and stop
	 * the समयr. Timer will be started again when TX happens again.
	 */
	अगर (update_समयr->समयr_tx_num != update_समयr->tx_num) अणु
		update_समयr->समयr_tx_num = update_समयr->tx_num;
		mod_समयr(&update_समयr->समयr, jअगरfies +
		  msecs_to_jअगरfies(update_समयr->पूर्णांकerval));
	पूर्ण अन्यथा अणु
		update_समयr->started = false;
		ath11k_hal_srng_shaकरोw_update_hp_tp(ab, srng);
	पूर्ण

	spin_unlock_bh(&srng->lock);
पूर्ण

व्योम ath11k_dp_shaकरोw_start_समयr(काष्ठा ath11k_base *ab,
				  काष्ठा hal_srng *srng,
				  काष्ठा ath11k_hp_update_समयr *update_समयr)
अणु
	lockdep_निश्चित_held(&srng->lock);

	अगर (!ab->hw_params.supports_shaकरोw_regs)
		वापस;

	update_समयr->tx_num++;

	अगर (update_समयr->started)
		वापस;

	update_समयr->started = true;
	update_समयr->समयr_tx_num = update_समयr->tx_num;
	mod_समयr(&update_समयr->समयr, jअगरfies +
		  msecs_to_jअगरfies(update_समयr->पूर्णांकerval));
पूर्ण

व्योम ath11k_dp_shaकरोw_stop_समयr(काष्ठा ath11k_base *ab,
				 काष्ठा ath11k_hp_update_समयr *update_समयr)
अणु
	अगर (!ab->hw_params.supports_shaकरोw_regs)
		वापस;

	अगर (!update_समयr->init)
		वापस;

	del_समयr_sync(&update_समयr->समयr);
पूर्ण

व्योम ath11k_dp_shaकरोw_init_समयr(काष्ठा ath11k_base *ab,
				 काष्ठा ath11k_hp_update_समयr *update_समयr,
				 u32 पूर्णांकerval, u32 ring_id)
अणु
	अगर (!ab->hw_params.supports_shaकरोw_regs)
		वापस;

	update_समयr->tx_num = 0;
	update_समयr->समयr_tx_num = 0;
	update_समयr->ab = ab;
	update_समयr->ring_id = ring_id;
	update_समयr->पूर्णांकerval = पूर्णांकerval;
	update_समयr->init = true;
	समयr_setup(&update_समयr->समयr,
		    ath11k_dp_shaकरोw_समयr_handler, 0);
पूर्ण
