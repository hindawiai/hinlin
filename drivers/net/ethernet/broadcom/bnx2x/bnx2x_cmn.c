<शैली गुरु>
/* bnx2x_cmn.c: QLogic Everest network driver.
 *
 * Copyright (c) 2007-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Eliezer Tamir
 * Based on code from Michael Chan's bnx2 driver
 * UDP CSUM errata workaround by Arik Gendelman
 * Slowpath and fastpath rework by Vladislav Zolotarov
 * Statistics and Link management by Yitchak Gertner
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ip.h>
#समावेश <linux/crash_dump.h>
#समावेश <net/tcp.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/prefetch.h>
#समावेश "bnx2x_cmn.h"
#समावेश "bnx2x_init.h"
#समावेश "bnx2x_sp.h"

अटल व्योम bnx2x_मुक्त_fp_mem_cnic(काष्ठा bnx2x *bp);
अटल पूर्णांक bnx2x_alloc_fp_mem_cnic(काष्ठा bnx2x *bp);
अटल पूर्णांक bnx2x_alloc_fp_mem(काष्ठा bnx2x *bp);
अटल पूर्णांक bnx2x_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);

अटल व्योम bnx2x_add_all_napi_cnic(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	/* Add NAPI objects */
	क्रम_each_rx_queue_cnic(bp, i) अणु
		netअगर_napi_add(bp->dev, &bnx2x_fp(bp, i, napi),
			       bnx2x_poll, NAPI_POLL_WEIGHT);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_add_all_napi(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	/* Add NAPI objects */
	क्रम_each_eth_queue(bp, i) अणु
		netअगर_napi_add(bp->dev, &bnx2x_fp(bp, i, napi),
			       bnx2x_poll, NAPI_POLL_WEIGHT);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_calc_num_queues(काष्ठा bnx2x *bp)
अणु
	पूर्णांक nq = bnx2x_num_queues ? : netअगर_get_num_शेष_rss_queues();

	/* Reduce memory usage in kdump environment by using only one queue */
	अगर (is_kdump_kernel())
		nq = 1;

	nq = clamp(nq, 1, BNX2X_MAX_QUEUES(bp));
	वापस nq;
पूर्ण

/**
 * bnx2x_move_fp - move content of the fastpath काष्ठाure.
 *
 * @bp:		driver handle
 * @from:	source FP index
 * @to:		destination FP index
 *
 * Makes sure the contents of the bp->fp[to].napi is kept
 * पूर्णांकact. This is करोne by first copying the napi काष्ठा from
 * the target to the source, and then mem copying the entire
 * source onto the target. Update txdata poपूर्णांकers and related
 * content.
 */
अटल अंतरभूत व्योम bnx2x_move_fp(काष्ठा bnx2x *bp, पूर्णांक from, पूर्णांक to)
अणु
	काष्ठा bnx2x_fastpath *from_fp = &bp->fp[from];
	काष्ठा bnx2x_fastpath *to_fp = &bp->fp[to];
	काष्ठा bnx2x_sp_objs *from_sp_objs = &bp->sp_objs[from];
	काष्ठा bnx2x_sp_objs *to_sp_objs = &bp->sp_objs[to];
	काष्ठा bnx2x_fp_stats *from_fp_stats = &bp->fp_stats[from];
	काष्ठा bnx2x_fp_stats *to_fp_stats = &bp->fp_stats[to];
	पूर्णांक old_max_eth_txqs, new_max_eth_txqs;
	पूर्णांक old_txdata_index = 0, new_txdata_index = 0;
	काष्ठा bnx2x_agg_info *old_tpa_info = to_fp->tpa_info;

	/* Copy the NAPI object as it has been alपढ़ोy initialized */
	from_fp->napi = to_fp->napi;

	/* Move bnx2x_fastpath contents */
	स_नकल(to_fp, from_fp, माप(*to_fp));
	to_fp->index = to;

	/* Retain the tpa_info of the original `to' version as we don't want
	 * 2 FPs to contain the same tpa_info poपूर्णांकer.
	 */
	to_fp->tpa_info = old_tpa_info;

	/* move sp_objs contents as well, as their indices match fp ones */
	स_नकल(to_sp_objs, from_sp_objs, माप(*to_sp_objs));

	/* move fp_stats contents as well, as their indices match fp ones */
	स_नकल(to_fp_stats, from_fp_stats, माप(*to_fp_stats));

	/* Update txdata poपूर्णांकers in fp and move txdata content accordingly:
	 * Each fp consumes 'max_cos' txdata काष्ठाures, so the index should be
	 * decremented by max_cos x delta.
	 */

	old_max_eth_txqs = BNX2X_NUM_ETH_QUEUES(bp) * (bp)->max_cos;
	new_max_eth_txqs = (BNX2X_NUM_ETH_QUEUES(bp) - from + to) *
				(bp)->max_cos;
	अगर (from == FCOE_IDX(bp)) अणु
		old_txdata_index = old_max_eth_txqs + FCOE_TXQ_IDX_OFFSET;
		new_txdata_index = new_max_eth_txqs + FCOE_TXQ_IDX_OFFSET;
	पूर्ण

	स_नकल(&bp->bnx2x_txq[new_txdata_index],
	       &bp->bnx2x_txq[old_txdata_index],
	       माप(काष्ठा bnx2x_fp_txdata));
	to_fp->txdata_ptr[0] = &bp->bnx2x_txq[new_txdata_index];
पूर्ण

/**
 * bnx2x_fill_fw_str - Fill buffer with FW version string.
 *
 * @bp:        driver handle
 * @buf:       अक्षरacter buffer to fill with the fw name
 * @buf_len:   length of the above buffer
 *
 */
व्योम bnx2x_fill_fw_str(काष्ठा bnx2x *bp, अक्षर *buf, माप_प्रकार buf_len)
अणु
	अगर (IS_PF(bp)) अणु
		u8 phy_fw_ver[PHY_FW_VER_LEN];

		phy_fw_ver[0] = '\0';
		bnx2x_get_ext_phy_fw_version(&bp->link_params,
					     phy_fw_ver, PHY_FW_VER_LEN);
		strlcpy(buf, bp->fw_ver, buf_len);
		snम_लिखो(buf + म_माप(bp->fw_ver), 32 - म_माप(bp->fw_ver),
			 "bc %d.%d.%d%s%s",
			 (bp->common.bc_ver & 0xff0000) >> 16,
			 (bp->common.bc_ver & 0xff00) >> 8,
			 (bp->common.bc_ver & 0xff),
			 ((phy_fw_ver[0] != '\0') ? " phy " : ""), phy_fw_ver);
	पूर्ण अन्यथा अणु
		bnx2x_vf_fill_fw_str(bp, buf, buf_len);
	पूर्ण
पूर्ण

/**
 * bnx2x_shrink_eth_fp - guarantees fastpath काष्ठाures stay पूर्णांकact
 *
 * @bp:	driver handle
 * @delta:	number of eth queues which were not allocated
 */
अटल व्योम bnx2x_shrink_eth_fp(काष्ठा bnx2x *bp, पूर्णांक delta)
अणु
	पूर्णांक i, cos, old_eth_num = BNX2X_NUM_ETH_QUEUES(bp);

	/* Queue poपूर्णांकer cannot be re-set on an fp-basis, as moving poपूर्णांकer
	 * backward aदीर्घ the array could cause memory to be overridden
	 */
	क्रम (cos = 1; cos < bp->max_cos; cos++) अणु
		क्रम (i = 0; i < old_eth_num - delta; i++) अणु
			काष्ठा bnx2x_fastpath *fp = &bp->fp[i];
			पूर्णांक new_idx = cos * (old_eth_num - delta) + i;

			स_नकल(&bp->bnx2x_txq[new_idx], fp->txdata_ptr[cos],
			       माप(काष्ठा bnx2x_fp_txdata));
			fp->txdata_ptr[cos] = &bp->bnx2x_txq[new_idx];
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक bnx2x_load_count[2][3] = अणु अणु0पूर्ण पूर्ण; /* per-path: 0-common, 1-port0, 2-port1 */

/* मुक्त skb in the packet ring at pos idx
 * वापस idx of last bd मुक्तd
 */
अटल u16 bnx2x_मुक्त_tx_pkt(काष्ठा bnx2x *bp, काष्ठा bnx2x_fp_txdata *txdata,
			     u16 idx, अचिन्हित पूर्णांक *pkts_compl,
			     अचिन्हित पूर्णांक *bytes_compl)
अणु
	काष्ठा sw_tx_bd *tx_buf = &txdata->tx_buf_ring[idx];
	काष्ठा eth_tx_start_bd *tx_start_bd;
	काष्ठा eth_tx_bd *tx_data_bd;
	काष्ठा sk_buff *skb = tx_buf->skb;
	u16 bd_idx = TX_BD(tx_buf->first_bd), new_cons;
	पूर्णांक nbd;
	u16 split_bd_len = 0;

	/* prefetch skb end poपूर्णांकer to speedup dev_kमुक्त_skb() */
	prefetch(&skb->end);

	DP(NETIF_MSG_TX_DONE, "fp[%d]: pkt_idx %d  buff @(%p)->skb %p\n",
	   txdata->txq_index, idx, tx_buf, skb);

	tx_start_bd = &txdata->tx_desc_ring[bd_idx].start_bd;

	nbd = le16_to_cpu(tx_start_bd->nbd) - 1;
#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर ((nbd - 1) > (MAX_SKB_FRAGS + 2)) अणु
		BNX2X_ERR("BAD nbd!\n");
		bnx2x_panic();
	पूर्ण
#पूर्ण_अगर
	new_cons = nbd + tx_buf->first_bd;

	/* Get the next bd */
	bd_idx = TX_BD(NEXT_TX_IDX(bd_idx));

	/* Skip a parse bd... */
	--nbd;
	bd_idx = TX_BD(NEXT_TX_IDX(bd_idx));

	अगर (tx_buf->flags & BNX2X_HAS_SECOND_PBD) अणु
		/* Skip second parse bd... */
		--nbd;
		bd_idx = TX_BD(NEXT_TX_IDX(bd_idx));
	पूर्ण

	/* TSO headers+data bds share a common mapping. See bnx2x_tx_split() */
	अगर (tx_buf->flags & BNX2X_TSO_SPLIT_BD) अणु
		tx_data_bd = &txdata->tx_desc_ring[bd_idx].reg_bd;
		split_bd_len = BD_UNMAP_LEN(tx_data_bd);
		--nbd;
		bd_idx = TX_BD(NEXT_TX_IDX(bd_idx));
	पूर्ण

	/* unmap first bd */
	dma_unmap_single(&bp->pdev->dev, BD_UNMAP_ADDR(tx_start_bd),
			 BD_UNMAP_LEN(tx_start_bd) + split_bd_len,
			 DMA_TO_DEVICE);

	/* now मुक्त frags */
	जबतक (nbd > 0) अणु

		tx_data_bd = &txdata->tx_desc_ring[bd_idx].reg_bd;
		dma_unmap_page(&bp->pdev->dev, BD_UNMAP_ADDR(tx_data_bd),
			       BD_UNMAP_LEN(tx_data_bd), DMA_TO_DEVICE);
		अगर (--nbd)
			bd_idx = TX_BD(NEXT_TX_IDX(bd_idx));
	पूर्ण

	/* release skb */
	WARN_ON(!skb);
	अगर (likely(skb)) अणु
		(*pkts_compl)++;
		(*bytes_compl) += skb->len;
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	tx_buf->first_bd = 0;
	tx_buf->skb = शून्य;

	वापस new_cons;
पूर्ण

पूर्णांक bnx2x_tx_पूर्णांक(काष्ठा bnx2x *bp, काष्ठा bnx2x_fp_txdata *txdata)
अणु
	काष्ठा netdev_queue *txq;
	u16 hw_cons, sw_cons, bd_cons = txdata->tx_bd_cons;
	अचिन्हित पूर्णांक pkts_compl = 0, bytes_compl = 0;

#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर (unlikely(bp->panic))
		वापस -1;
#पूर्ण_अगर

	txq = netdev_get_tx_queue(bp->dev, txdata->txq_index);
	hw_cons = le16_to_cpu(*txdata->tx_cons_sb);
	sw_cons = txdata->tx_pkt_cons;

	/* Ensure subsequent loads occur after hw_cons */
	smp_rmb();

	जबतक (sw_cons != hw_cons) अणु
		u16 pkt_cons;

		pkt_cons = TX_BD(sw_cons);

		DP(NETIF_MSG_TX_DONE,
		   "queue[%d]: hw_cons %u  sw_cons %u  pkt_cons %u\n",
		   txdata->txq_index, hw_cons, sw_cons, pkt_cons);

		bd_cons = bnx2x_मुक्त_tx_pkt(bp, txdata, pkt_cons,
					    &pkts_compl, &bytes_compl);

		sw_cons++;
	पूर्ण

	netdev_tx_completed_queue(txq, pkts_compl, bytes_compl);

	txdata->tx_pkt_cons = sw_cons;
	txdata->tx_bd_cons = bd_cons;

	/* Need to make the tx_bd_cons update visible to start_xmit()
	 * beक्रमe checking क्रम netअगर_tx_queue_stopped().  Without the
	 * memory barrier, there is a small possibility that
	 * start_xmit() will miss it and cause the queue to be stopped
	 * क्रमever.
	 * On the other hand we need an rmb() here to ensure the proper
	 * ordering of bit testing in the following
	 * netअगर_tx_queue_stopped(txq) call.
	 */
	smp_mb();

	अगर (unlikely(netअगर_tx_queue_stopped(txq))) अणु
		/* Taking tx_lock() is needed to prevent re-enabling the queue
		 * जबतक it's empty. This could have happen अगर rx_action() माला_लो
		 * suspended in bnx2x_tx_पूर्णांक() after the condition beक्रमe
		 * netअगर_tx_wake_queue(), जबतक tx_action (bnx2x_start_xmit()):
		 *
		 * stops the queue->sees fresh tx_bd_cons->releases the queue->
		 * sends some packets consuming the whole queue again->
		 * stops the queue
		 */

		__netअगर_tx_lock(txq, smp_processor_id());

		अगर ((netअगर_tx_queue_stopped(txq)) &&
		    (bp->state == BNX2X_STATE_OPEN) &&
		    (bnx2x_tx_avail(bp, txdata) >= MAX_DESC_PER_TX_PKT))
			netअगर_tx_wake_queue(txq);

		__netअगर_tx_unlock(txq);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम bnx2x_update_last_max_sge(काष्ठा bnx2x_fastpath *fp,
					     u16 idx)
अणु
	u16 last_max = fp->last_max_sge;

	अगर (SUB_S16(idx, last_max) > 0)
		fp->last_max_sge = idx;
पूर्ण

अटल अंतरभूत व्योम bnx2x_update_sge_prod(काष्ठा bnx2x_fastpath *fp,
					 u16 sge_len,
					 काष्ठा eth_end_agg_rx_cqe *cqe)
अणु
	काष्ठा bnx2x *bp = fp->bp;
	u16 last_max, last_elem, first_elem;
	u16 delta = 0;
	u16 i;

	अगर (!sge_len)
		वापस;

	/* First mark all used pages */
	क्रम (i = 0; i < sge_len; i++)
		BIT_VEC64_CLEAR_BIT(fp->sge_mask,
			RX_SGE(le16_to_cpu(cqe->sgl_or_raw_data.sgl[i])));

	DP(NETIF_MSG_RX_STATUS, "fp_cqe->sgl[%d] = %d\n",
	   sge_len - 1, le16_to_cpu(cqe->sgl_or_raw_data.sgl[sge_len - 1]));

	/* Here we assume that the last SGE index is the biggest */
	prefetch((व्योम *)(fp->sge_mask));
	bnx2x_update_last_max_sge(fp,
		le16_to_cpu(cqe->sgl_or_raw_data.sgl[sge_len - 1]));

	last_max = RX_SGE(fp->last_max_sge);
	last_elem = last_max >> BIT_VEC64_ELEM_SHIFT;
	first_elem = RX_SGE(fp->rx_sge_prod) >> BIT_VEC64_ELEM_SHIFT;

	/* If ring is not full */
	अगर (last_elem + 1 != first_elem)
		last_elem++;

	/* Now update the prod */
	क्रम (i = first_elem; i != last_elem; i = NEXT_SGE_MASK_ELEM(i)) अणु
		अगर (likely(fp->sge_mask[i]))
			अवरोध;

		fp->sge_mask[i] = BIT_VEC64_ELEM_ONE_MASK;
		delta += BIT_VEC64_ELEM_SZ;
	पूर्ण

	अगर (delta > 0) अणु
		fp->rx_sge_prod += delta;
		/* clear page-end entries */
		bnx2x_clear_sge_mask_next_elems(fp);
	पूर्ण

	DP(NETIF_MSG_RX_STATUS,
	   "fp->last_max_sge = %d  fp->rx_sge_prod = %d\n",
	   fp->last_max_sge, fp->rx_sge_prod);
पूर्ण

/* Get Toeplitz hash value in the skb using the value from the
 * CQE (calculated by HW).
 */
अटल u32 bnx2x_get_rxhash(स्थिर काष्ठा bnx2x *bp,
			    स्थिर काष्ठा eth_fast_path_rx_cqe *cqe,
			    क्रमागत pkt_hash_types *rxhash_type)
अणु
	/* Get Toeplitz hash from CQE */
	अगर ((bp->dev->features & NETIF_F_RXHASH) &&
	    (cqe->status_flags & ETH_FAST_PATH_RX_CQE_RSS_HASH_FLG)) अणु
		क्रमागत eth_rss_hash_type htype;

		htype = cqe->status_flags & ETH_FAST_PATH_RX_CQE_RSS_HASH_TYPE;
		*rxhash_type = ((htype == TCP_IPV4_HASH_TYPE) ||
				(htype == TCP_IPV6_HASH_TYPE)) ?
			       PKT_HASH_TYPE_L4 : PKT_HASH_TYPE_L3;

		वापस le32_to_cpu(cqe->rss_hash_result);
	पूर्ण
	*rxhash_type = PKT_HASH_TYPE_NONE;
	वापस 0;
पूर्ण

अटल व्योम bnx2x_tpa_start(काष्ठा bnx2x_fastpath *fp, u16 queue,
			    u16 cons, u16 prod,
			    काष्ठा eth_fast_path_rx_cqe *cqe)
अणु
	काष्ठा bnx2x *bp = fp->bp;
	काष्ठा sw_rx_bd *cons_rx_buf = &fp->rx_buf_ring[cons];
	काष्ठा sw_rx_bd *prod_rx_buf = &fp->rx_buf_ring[prod];
	काष्ठा eth_rx_bd *prod_bd = &fp->rx_desc_ring[prod];
	dma_addr_t mapping;
	काष्ठा bnx2x_agg_info *tpa_info = &fp->tpa_info[queue];
	काष्ठा sw_rx_bd *first_buf = &tpa_info->first_buf;

	/* prपूर्णांक error अगर current state != stop */
	अगर (tpa_info->tpa_state != BNX2X_TPA_STOP)
		BNX2X_ERR("start of bin not in stop [%d]\n", queue);

	/* Try to map an empty data buffer from the aggregation info  */
	mapping = dma_map_single(&bp->pdev->dev,
				 first_buf->data + NET_SKB_PAD,
				 fp->rx_buf_size, DMA_FROM_DEVICE);
	/*
	 *  ...अगर it fails - move the skb from the consumer to the producer
	 *  and set the current aggregation state as ERROR to drop it
	 *  when TPA_STOP arrives.
	 */

	अगर (unlikely(dma_mapping_error(&bp->pdev->dev, mapping))) अणु
		/* Move the BD from the consumer to the producer */
		bnx2x_reuse_rx_data(fp, cons, prod);
		tpa_info->tpa_state = BNX2X_TPA_ERROR;
		वापस;
	पूर्ण

	/* move empty data from pool to prod */
	prod_rx_buf->data = first_buf->data;
	dma_unmap_addr_set(prod_rx_buf, mapping, mapping);
	/* poपूर्णांक prod_bd to new data */
	prod_bd->addr_hi = cpu_to_le32(U64_HI(mapping));
	prod_bd->addr_lo = cpu_to_le32(U64_LO(mapping));

	/* move partial skb from cons to pool (करोn't unmap yet) */
	*first_buf = *cons_rx_buf;

	/* mark bin state as START */
	tpa_info->parsing_flags =
		le16_to_cpu(cqe->pars_flags.flags);
	tpa_info->vlan_tag = le16_to_cpu(cqe->vlan_tag);
	tpa_info->tpa_state = BNX2X_TPA_START;
	tpa_info->len_on_bd = le16_to_cpu(cqe->len_on_bd);
	tpa_info->placement_offset = cqe->placement_offset;
	tpa_info->rxhash = bnx2x_get_rxhash(bp, cqe, &tpa_info->rxhash_type);
	अगर (fp->mode == TPA_MODE_GRO) अणु
		u16 gro_size = le16_to_cpu(cqe->pkt_len_or_gro_seg_len);
		tpa_info->full_page = SGE_PAGES / gro_size * gro_size;
		tpa_info->gro_size = gro_size;
	पूर्ण

#अगर_घोषित BNX2X_STOP_ON_ERROR
	fp->tpa_queue_used |= (1 << queue);
	DP(NETIF_MSG_RX_STATUS, "fp->tpa_queue_used = 0x%llx\n",
	   fp->tpa_queue_used);
#पूर्ण_अगर
पूर्ण

/* Timestamp option length allowed क्रम TPA aggregation:
 *
 *		nop nop kind length echo val
 */
#घोषणा TPA_TSTAMP_OPT_LEN	12
/**
 * bnx2x_set_gro_params - compute GRO values
 *
 * @skb:		packet skb
 * @parsing_flags:	parsing flags from the START CQE
 * @len_on_bd:		total length of the first packet क्रम the
 *			aggregation.
 * @pkt_len:		length of all segments
 * @num_of_coalesced_segs: count of segments
 *
 * Approximate value of the MSS क्रम this aggregation calculated using
 * the first packet of it.
 * Compute number of aggregated segments, and gso_type.
 */
अटल व्योम bnx2x_set_gro_params(काष्ठा sk_buff *skb, u16 parsing_flags,
				 u16 len_on_bd, अचिन्हित पूर्णांक pkt_len,
				 u16 num_of_coalesced_segs)
अणु
	/* TPA aggregation won't have either IP options or TCP options
	 * other than बारtamp or IPv6 extension headers.
	 */
	u16 hdrs_len = ETH_HLEN + माप(काष्ठा tcphdr);

	अगर (GET_FLAG(parsing_flags, PARSING_FLAGS_OVER_ETHERNET_PROTOCOL) ==
	    PRS_FLAG_OVERETH_IPV6) अणु
		hdrs_len += माप(काष्ठा ipv6hdr);
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;
	पूर्ण अन्यथा अणु
		hdrs_len += माप(काष्ठा iphdr);
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;
	पूर्ण

	/* Check अगर there was a TCP बारtamp, अगर there is it's will
	 * always be 12 bytes length: nop nop kind length echo val.
	 *
	 * Otherwise FW would बंद the aggregation.
	 */
	अगर (parsing_flags & PARSING_FLAGS_TIME_STAMP_EXIST_FLAG)
		hdrs_len += TPA_TSTAMP_OPT_LEN;

	skb_shinfo(skb)->gso_size = len_on_bd - hdrs_len;

	/* tcp_gro_complete() will copy NAPI_GRO_CB(skb)->count
	 * to skb_shinfo(skb)->gso_segs
	 */
	NAPI_GRO_CB(skb)->count = num_of_coalesced_segs;
पूर्ण

अटल पूर्णांक bnx2x_alloc_rx_sge(काष्ठा bnx2x *bp, काष्ठा bnx2x_fastpath *fp,
			      u16 index, gfp_t gfp_mask)
अणु
	काष्ठा sw_rx_page *sw_buf = &fp->rx_page_ring[index];
	काष्ठा eth_rx_sge *sge = &fp->rx_sge_ring[index];
	काष्ठा bnx2x_alloc_pool *pool = &fp->page_pool;
	dma_addr_t mapping;

	अगर (!pool->page) अणु
		pool->page = alloc_pages(gfp_mask, PAGES_PER_SGE_SHIFT);
		अगर (unlikely(!pool->page))
			वापस -ENOMEM;

		pool->offset = 0;
	पूर्ण

	mapping = dma_map_page(&bp->pdev->dev, pool->page,
			       pool->offset, SGE_PAGE_SIZE, DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(&bp->pdev->dev, mapping))) अणु
		BNX2X_ERR("Can't map sge\n");
		वापस -ENOMEM;
	पूर्ण

	sw_buf->page = pool->page;
	sw_buf->offset = pool->offset;

	dma_unmap_addr_set(sw_buf, mapping, mapping);

	sge->addr_hi = cpu_to_le32(U64_HI(mapping));
	sge->addr_lo = cpu_to_le32(U64_LO(mapping));

	pool->offset += SGE_PAGE_SIZE;
	अगर (PAGE_SIZE - pool->offset >= SGE_PAGE_SIZE)
		get_page(pool->page);
	अन्यथा
		pool->page = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_fill_frag_skb(काष्ठा bnx2x *bp, काष्ठा bnx2x_fastpath *fp,
			       काष्ठा bnx2x_agg_info *tpa_info,
			       u16 pages,
			       काष्ठा sk_buff *skb,
			       काष्ठा eth_end_agg_rx_cqe *cqe,
			       u16 cqe_idx)
अणु
	काष्ठा sw_rx_page *rx_pg, old_rx_pg;
	u32 i, frag_len, frag_size;
	पूर्णांक err, j, frag_id = 0;
	u16 len_on_bd = tpa_info->len_on_bd;
	u16 full_page = 0, gro_size = 0;

	frag_size = le16_to_cpu(cqe->pkt_len) - len_on_bd;

	अगर (fp->mode == TPA_MODE_GRO) अणु
		gro_size = tpa_info->gro_size;
		full_page = tpa_info->full_page;
	पूर्ण

	/* This is needed in order to enable क्रमwarding support */
	अगर (frag_size)
		bnx2x_set_gro_params(skb, tpa_info->parsing_flags, len_on_bd,
				     le16_to_cpu(cqe->pkt_len),
				     le16_to_cpu(cqe->num_of_coalesced_segs));

#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर (pages > min_t(u32, 8, MAX_SKB_FRAGS) * SGE_PAGES) अणु
		BNX2X_ERR("SGL length is too long: %d. CQE index is %d\n",
			  pages, cqe_idx);
		BNX2X_ERR("cqe->pkt_len = %d\n", cqe->pkt_len);
		bnx2x_panic();
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर

	/* Run through the SGL and compose the fragmented skb */
	क्रम (i = 0, j = 0; i < pages; i += PAGES_PER_SGE, j++) अणु
		u16 sge_idx = RX_SGE(le16_to_cpu(cqe->sgl_or_raw_data.sgl[j]));

		/* FW gives the indices of the SGE as अगर the ring is an array
		   (meaning that "next" element will consume 2 indices) */
		अगर (fp->mode == TPA_MODE_GRO)
			frag_len = min_t(u32, frag_size, (u32)full_page);
		अन्यथा /* LRO */
			frag_len = min_t(u32, frag_size, (u32)SGE_PAGES);

		rx_pg = &fp->rx_page_ring[sge_idx];
		old_rx_pg = *rx_pg;

		/* If we fail to allocate a substitute page, we simply stop
		   where we are and drop the whole packet */
		err = bnx2x_alloc_rx_sge(bp, fp, sge_idx, GFP_ATOMIC);
		अगर (unlikely(err)) अणु
			bnx2x_fp_qstats(bp, fp)->rx_skb_alloc_failed++;
			वापस err;
		पूर्ण

		dma_unmap_page(&bp->pdev->dev,
			       dma_unmap_addr(&old_rx_pg, mapping),
			       SGE_PAGE_SIZE, DMA_FROM_DEVICE);
		/* Add one frag and update the appropriate fields in the skb */
		अगर (fp->mode == TPA_MODE_LRO)
			skb_fill_page_desc(skb, j, old_rx_pg.page,
					   old_rx_pg.offset, frag_len);
		अन्यथा अणु /* GRO */
			पूर्णांक rem;
			पूर्णांक offset = 0;
			क्रम (rem = frag_len; rem > 0; rem -= gro_size) अणु
				पूर्णांक len = rem > gro_size ? gro_size : rem;
				skb_fill_page_desc(skb, frag_id++,
						   old_rx_pg.page,
						   old_rx_pg.offset + offset,
						   len);
				अगर (offset)
					get_page(old_rx_pg.page);
				offset += len;
			पूर्ण
		पूर्ण

		skb->data_len += frag_len;
		skb->truesize += SGE_PAGES;
		skb->len += frag_len;

		frag_size -= frag_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnx2x_frag_मुक्त(स्थिर काष्ठा bnx2x_fastpath *fp, व्योम *data)
अणु
	अगर (fp->rx_frag_size)
		skb_मुक्त_frag(data);
	अन्यथा
		kमुक्त(data);
पूर्ण

अटल व्योम *bnx2x_frag_alloc(स्थिर काष्ठा bnx2x_fastpath *fp, gfp_t gfp_mask)
अणु
	अगर (fp->rx_frag_size) अणु
		/* GFP_KERNEL allocations are used only during initialization */
		अगर (unlikely(gfpflags_allow_blocking(gfp_mask)))
			वापस (व्योम *)__get_मुक्त_page(gfp_mask);

		वापस napi_alloc_frag(fp->rx_frag_size);
	पूर्ण

	वापस kदो_स्मृति(fp->rx_buf_size + NET_SKB_PAD, gfp_mask);
पूर्ण

#अगर_घोषित CONFIG_INET
अटल व्योम bnx2x_gro_ip_csum(काष्ठा bnx2x *bp, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा tcphdr *th;

	skb_set_transport_header(skb, माप(काष्ठा iphdr));
	th = tcp_hdr(skb);

	th->check = ~tcp_v4_check(skb->len - skb_transport_offset(skb),
				  iph->saddr, iph->daddr, 0);
पूर्ण

अटल व्योम bnx2x_gro_ipv6_csum(काष्ठा bnx2x *bp, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा tcphdr *th;

	skb_set_transport_header(skb, माप(काष्ठा ipv6hdr));
	th = tcp_hdr(skb);

	th->check = ~tcp_v6_check(skb->len - skb_transport_offset(skb),
				  &iph->saddr, &iph->daddr, 0);
पूर्ण

अटल व्योम bnx2x_gro_csum(काष्ठा bnx2x *bp, काष्ठा sk_buff *skb,
			    व्योम (*gro_func)(काष्ठा bnx2x*, काष्ठा sk_buff*))
अणु
	skb_reset_network_header(skb);
	gro_func(bp, skb);
	tcp_gro_complete(skb);
पूर्ण
#पूर्ण_अगर

अटल व्योम bnx2x_gro_receive(काष्ठा bnx2x *bp, काष्ठा bnx2x_fastpath *fp,
			       काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_INET
	अगर (skb_shinfo(skb)->gso_size) अणु
		चयन (be16_to_cpu(skb->protocol)) अणु
		हाल ETH_P_IP:
			bnx2x_gro_csum(bp, skb, bnx2x_gro_ip_csum);
			अवरोध;
		हाल ETH_P_IPV6:
			bnx2x_gro_csum(bp, skb, bnx2x_gro_ipv6_csum);
			अवरोध;
		शेष:
			netdev_WARN_ONCE(bp->dev,
					 "Error: FW GRO supports only IPv4/IPv6, not 0x%04x\n",
					 be16_to_cpu(skb->protocol));
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	skb_record_rx_queue(skb, fp->rx_queue);
	napi_gro_receive(&fp->napi, skb);
पूर्ण

अटल व्योम bnx2x_tpa_stop(काष्ठा bnx2x *bp, काष्ठा bnx2x_fastpath *fp,
			   काष्ठा bnx2x_agg_info *tpa_info,
			   u16 pages,
			   काष्ठा eth_end_agg_rx_cqe *cqe,
			   u16 cqe_idx)
अणु
	काष्ठा sw_rx_bd *rx_buf = &tpa_info->first_buf;
	u8 pad = tpa_info->placement_offset;
	u16 len = tpa_info->len_on_bd;
	काष्ठा sk_buff *skb = शून्य;
	u8 *new_data, *data = rx_buf->data;
	u8 old_tpa_state = tpa_info->tpa_state;

	tpa_info->tpa_state = BNX2X_TPA_STOP;

	/* If we there was an error during the handling of the TPA_START -
	 * drop this aggregation.
	 */
	अगर (old_tpa_state == BNX2X_TPA_ERROR)
		जाओ drop;

	/* Try to allocate the new data */
	new_data = bnx2x_frag_alloc(fp, GFP_ATOMIC);
	/* Unmap skb in the pool anyway, as we are going to change
	   pool entry status to BNX2X_TPA_STOP even अगर new skb allocation
	   fails. */
	dma_unmap_single(&bp->pdev->dev, dma_unmap_addr(rx_buf, mapping),
			 fp->rx_buf_size, DMA_FROM_DEVICE);
	अगर (likely(new_data))
		skb = build_skb(data, fp->rx_frag_size);

	अगर (likely(skb)) अणु
#अगर_घोषित BNX2X_STOP_ON_ERROR
		अगर (pad + len > fp->rx_buf_size) अणु
			BNX2X_ERR("skb_put is about to fail...  pad %d  len %d  rx_buf_size %d\n",
				  pad, len, fp->rx_buf_size);
			bnx2x_panic();
			वापस;
		पूर्ण
#पूर्ण_अगर

		skb_reserve(skb, pad + NET_SKB_PAD);
		skb_put(skb, len);
		skb_set_hash(skb, tpa_info->rxhash, tpa_info->rxhash_type);

		skb->protocol = eth_type_trans(skb, bp->dev);
		skb->ip_summed = CHECKSUM_UNNECESSARY;

		अगर (!bnx2x_fill_frag_skb(bp, fp, tpa_info, pages,
					 skb, cqe, cqe_idx)) अणु
			अगर (tpa_info->parsing_flags & PARSING_FLAGS_VLAN)
				__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), tpa_info->vlan_tag);
			bnx2x_gro_receive(bp, fp, skb);
		पूर्ण अन्यथा अणु
			DP(NETIF_MSG_RX_STATUS,
			   "Failed to allocate new pages - dropping packet!\n");
			dev_kमुक्त_skb_any(skb);
		पूर्ण

		/* put new data in bin */
		rx_buf->data = new_data;

		वापस;
	पूर्ण
	अगर (new_data)
		bnx2x_frag_मुक्त(fp, new_data);
drop:
	/* drop the packet and keep the buffer in the bin */
	DP(NETIF_MSG_RX_STATUS,
	   "Failed to allocate or map a new skb - dropping packet!\n");
	bnx2x_fp_stats(bp, fp)->eth_q_stats.rx_skb_alloc_failed++;
पूर्ण

अटल पूर्णांक bnx2x_alloc_rx_data(काष्ठा bnx2x *bp, काष्ठा bnx2x_fastpath *fp,
			       u16 index, gfp_t gfp_mask)
अणु
	u8 *data;
	काष्ठा sw_rx_bd *rx_buf = &fp->rx_buf_ring[index];
	काष्ठा eth_rx_bd *rx_bd = &fp->rx_desc_ring[index];
	dma_addr_t mapping;

	data = bnx2x_frag_alloc(fp, gfp_mask);
	अगर (unlikely(data == शून्य))
		वापस -ENOMEM;

	mapping = dma_map_single(&bp->pdev->dev, data + NET_SKB_PAD,
				 fp->rx_buf_size,
				 DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(&bp->pdev->dev, mapping))) अणु
		bnx2x_frag_मुक्त(fp, data);
		BNX2X_ERR("Can't map rx data\n");
		वापस -ENOMEM;
	पूर्ण

	rx_buf->data = data;
	dma_unmap_addr_set(rx_buf, mapping, mapping);

	rx_bd->addr_hi = cpu_to_le32(U64_HI(mapping));
	rx_bd->addr_lo = cpu_to_le32(U64_LO(mapping));

	वापस 0;
पूर्ण

अटल
व्योम bnx2x_csum_validate(काष्ठा sk_buff *skb, जोड़ eth_rx_cqe *cqe,
				 काष्ठा bnx2x_fastpath *fp,
				 काष्ठा bnx2x_eth_q_stats *qstats)
अणु
	/* Do nothing अगर no L4 csum validation was करोne.
	 * We करो not check whether IP csum was validated. For IPv4 we assume
	 * that अगर the card got as far as validating the L4 csum, it also
	 * validated the IP csum. IPv6 has no IP csum.
	 */
	अगर (cqe->fast_path_cqe.status_flags &
	    ETH_FAST_PATH_RX_CQE_L4_XSUM_NO_VALIDATION_FLG)
		वापस;

	/* If L4 validation was करोne, check अगर an error was found. */

	अगर (cqe->fast_path_cqe.type_error_flags &
	    (ETH_FAST_PATH_RX_CQE_IP_BAD_XSUM_FLG |
	     ETH_FAST_PATH_RX_CQE_L4_BAD_XSUM_FLG))
		qstats->hw_csum_err++;
	अन्यथा
		skb->ip_summed = CHECKSUM_UNNECESSARY;
पूर्ण

अटल पूर्णांक bnx2x_rx_पूर्णांक(काष्ठा bnx2x_fastpath *fp, पूर्णांक budget)
अणु
	काष्ठा bnx2x *bp = fp->bp;
	u16 bd_cons, bd_prod, bd_prod_fw, comp_ring_cons;
	u16 sw_comp_cons, sw_comp_prod;
	पूर्णांक rx_pkt = 0;
	जोड़ eth_rx_cqe *cqe;
	काष्ठा eth_fast_path_rx_cqe *cqe_fp;

#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर (unlikely(bp->panic))
		वापस 0;
#पूर्ण_अगर
	अगर (budget <= 0)
		वापस rx_pkt;

	bd_cons = fp->rx_bd_cons;
	bd_prod = fp->rx_bd_prod;
	bd_prod_fw = bd_prod;
	sw_comp_cons = fp->rx_comp_cons;
	sw_comp_prod = fp->rx_comp_prod;

	comp_ring_cons = RCQ_BD(sw_comp_cons);
	cqe = &fp->rx_comp_ring[comp_ring_cons];
	cqe_fp = &cqe->fast_path_cqe;

	DP(NETIF_MSG_RX_STATUS,
	   "queue[%d]: sw_comp_cons %u\n", fp->index, sw_comp_cons);

	जबतक (BNX2X_IS_CQE_COMPLETED(cqe_fp)) अणु
		काष्ठा sw_rx_bd *rx_buf = शून्य;
		काष्ठा sk_buff *skb;
		u8 cqe_fp_flags;
		क्रमागत eth_rx_cqe_type cqe_fp_type;
		u16 len, pad, queue;
		u8 *data;
		u32 rxhash;
		क्रमागत pkt_hash_types rxhash_type;

#अगर_घोषित BNX2X_STOP_ON_ERROR
		अगर (unlikely(bp->panic))
			वापस 0;
#पूर्ण_अगर

		bd_prod = RX_BD(bd_prod);
		bd_cons = RX_BD(bd_cons);

		/* A rmb() is required to ensure that the CQE is not पढ़ो
		 * beक्रमe it is written by the adapter DMA.  PCI ordering
		 * rules will make sure the other fields are written beक्रमe
		 * the marker at the end of काष्ठा eth_fast_path_rx_cqe
		 * but without rmb() a weakly ordered processor can process
		 * stale data.  Without the barrier TPA state-machine might
		 * enter inconsistent state and kernel stack might be
		 * provided with incorrect packet description - these lead
		 * to various kernel crashed.
		 */
		rmb();

		cqe_fp_flags = cqe_fp->type_error_flags;
		cqe_fp_type = cqe_fp_flags & ETH_FAST_PATH_RX_CQE_TYPE;

		DP(NETIF_MSG_RX_STATUS,
		   "CQE type %x  err %x  status %x  queue %x  vlan %x  len %u\n",
		   CQE_TYPE(cqe_fp_flags),
		   cqe_fp_flags, cqe_fp->status_flags,
		   le32_to_cpu(cqe_fp->rss_hash_result),
		   le16_to_cpu(cqe_fp->vlan_tag),
		   le16_to_cpu(cqe_fp->pkt_len_or_gro_seg_len));

		/* is this a slowpath msg? */
		अगर (unlikely(CQE_TYPE_SLOW(cqe_fp_type))) अणु
			bnx2x_sp_event(fp, cqe);
			जाओ next_cqe;
		पूर्ण

		rx_buf = &fp->rx_buf_ring[bd_cons];
		data = rx_buf->data;

		अगर (!CQE_TYPE_FAST(cqe_fp_type)) अणु
			काष्ठा bnx2x_agg_info *tpa_info;
			u16 frag_size, pages;
#अगर_घोषित BNX2X_STOP_ON_ERROR
			/* sanity check */
			अगर (fp->mode == TPA_MODE_DISABLED &&
			    (CQE_TYPE_START(cqe_fp_type) ||
			     CQE_TYPE_STOP(cqe_fp_type)))
				BNX2X_ERR("START/STOP packet while TPA disabled, type %x\n",
					  CQE_TYPE(cqe_fp_type));
#पूर्ण_अगर

			अगर (CQE_TYPE_START(cqe_fp_type)) अणु
				u16 queue = cqe_fp->queue_index;
				DP(NETIF_MSG_RX_STATUS,
				   "calling tpa_start on queue %d\n",
				   queue);

				bnx2x_tpa_start(fp, queue,
						bd_cons, bd_prod,
						cqe_fp);

				जाओ next_rx;
			पूर्ण
			queue = cqe->end_agg_cqe.queue_index;
			tpa_info = &fp->tpa_info[queue];
			DP(NETIF_MSG_RX_STATUS,
			   "calling tpa_stop on queue %d\n",
			   queue);

			frag_size = le16_to_cpu(cqe->end_agg_cqe.pkt_len) -
				    tpa_info->len_on_bd;

			अगर (fp->mode == TPA_MODE_GRO)
				pages = (frag_size + tpa_info->full_page - 1) /
					 tpa_info->full_page;
			अन्यथा
				pages = SGE_PAGE_ALIGN(frag_size) >>
					SGE_PAGE_SHIFT;

			bnx2x_tpa_stop(bp, fp, tpa_info, pages,
				       &cqe->end_agg_cqe, comp_ring_cons);
#अगर_घोषित BNX2X_STOP_ON_ERROR
			अगर (bp->panic)
				वापस 0;
#पूर्ण_अगर

			bnx2x_update_sge_prod(fp, pages, &cqe->end_agg_cqe);
			जाओ next_cqe;
		पूर्ण
		/* non TPA */
		len = le16_to_cpu(cqe_fp->pkt_len_or_gro_seg_len);
		pad = cqe_fp->placement_offset;
		dma_sync_single_क्रम_cpu(&bp->pdev->dev,
					dma_unmap_addr(rx_buf, mapping),
					pad + RX_COPY_THRESH,
					DMA_FROM_DEVICE);
		pad += NET_SKB_PAD;
		prefetch(data + pad); /* speedup eth_type_trans() */
		/* is this an error packet? */
		अगर (unlikely(cqe_fp_flags & ETH_RX_ERROR_FALGS)) अणु
			DP(NETIF_MSG_RX_ERR | NETIF_MSG_RX_STATUS,
			   "ERROR  flags %x  rx packet %u\n",
			   cqe_fp_flags, sw_comp_cons);
			bnx2x_fp_qstats(bp, fp)->rx_err_discard_pkt++;
			जाओ reuse_rx;
		पूर्ण

		/* Since we करोn't have a jumbo ring
		 * copy small packets अगर mtu > 1500
		 */
		अगर ((bp->dev->mtu > ETH_MAX_PACKET_SIZE) &&
		    (len <= RX_COPY_THRESH)) अणु
			skb = napi_alloc_skb(&fp->napi, len);
			अगर (skb == शून्य) अणु
				DP(NETIF_MSG_RX_ERR | NETIF_MSG_RX_STATUS,
				   "ERROR  packet dropped because of alloc failure\n");
				bnx2x_fp_qstats(bp, fp)->rx_skb_alloc_failed++;
				जाओ reuse_rx;
			पूर्ण
			स_नकल(skb->data, data + pad, len);
			bnx2x_reuse_rx_data(fp, bd_cons, bd_prod);
		पूर्ण अन्यथा अणु
			अगर (likely(bnx2x_alloc_rx_data(bp, fp, bd_prod,
						       GFP_ATOMIC) == 0)) अणु
				dma_unmap_single(&bp->pdev->dev,
						 dma_unmap_addr(rx_buf, mapping),
						 fp->rx_buf_size,
						 DMA_FROM_DEVICE);
				skb = build_skb(data, fp->rx_frag_size);
				अगर (unlikely(!skb)) अणु
					bnx2x_frag_मुक्त(fp, data);
					bnx2x_fp_qstats(bp, fp)->
							rx_skb_alloc_failed++;
					जाओ next_rx;
				पूर्ण
				skb_reserve(skb, pad);
			पूर्ण अन्यथा अणु
				DP(NETIF_MSG_RX_ERR | NETIF_MSG_RX_STATUS,
				   "ERROR  packet dropped because of alloc failure\n");
				bnx2x_fp_qstats(bp, fp)->rx_skb_alloc_failed++;
reuse_rx:
				bnx2x_reuse_rx_data(fp, bd_cons, bd_prod);
				जाओ next_rx;
			पूर्ण
		पूर्ण

		skb_put(skb, len);
		skb->protocol = eth_type_trans(skb, bp->dev);

		/* Set Toeplitz hash क्रम a none-LRO skb */
		rxhash = bnx2x_get_rxhash(bp, cqe_fp, &rxhash_type);
		skb_set_hash(skb, rxhash, rxhash_type);

		skb_checksum_none_निश्चित(skb);

		अगर (bp->dev->features & NETIF_F_RXCSUM)
			bnx2x_csum_validate(skb, cqe, fp,
					    bnx2x_fp_qstats(bp, fp));

		skb_record_rx_queue(skb, fp->rx_queue);

		/* Check अगर this packet was बारtamped */
		अगर (unlikely(cqe->fast_path_cqe.type_error_flags &
			     (1 << ETH_FAST_PATH_RX_CQE_PTP_PKT_SHIFT)))
			bnx2x_set_rx_ts(bp, skb);

		अगर (le16_to_cpu(cqe_fp->pars_flags.flags) &
		    PARSING_FLAGS_VLAN)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       le16_to_cpu(cqe_fp->vlan_tag));

		napi_gro_receive(&fp->napi, skb);
next_rx:
		rx_buf->data = शून्य;

		bd_cons = NEXT_RX_IDX(bd_cons);
		bd_prod = NEXT_RX_IDX(bd_prod);
		bd_prod_fw = NEXT_RX_IDX(bd_prod_fw);
		rx_pkt++;
next_cqe:
		sw_comp_prod = NEXT_RCQ_IDX(sw_comp_prod);
		sw_comp_cons = NEXT_RCQ_IDX(sw_comp_cons);

		/* mark CQE as मुक्त */
		BNX2X_SEED_CQE(cqe_fp);

		अगर (rx_pkt == budget)
			अवरोध;

		comp_ring_cons = RCQ_BD(sw_comp_cons);
		cqe = &fp->rx_comp_ring[comp_ring_cons];
		cqe_fp = &cqe->fast_path_cqe;
	पूर्ण /* जबतक */

	fp->rx_bd_cons = bd_cons;
	fp->rx_bd_prod = bd_prod_fw;
	fp->rx_comp_cons = sw_comp_cons;
	fp->rx_comp_prod = sw_comp_prod;

	/* Update producers */
	bnx2x_update_rx_prod(bp, fp, bd_prod_fw, sw_comp_prod,
			     fp->rx_sge_prod);

	वापस rx_pkt;
पूर्ण

अटल irqवापस_t bnx2x_msix_fp_पूर्णांक(पूर्णांक irq, व्योम *fp_cookie)
अणु
	काष्ठा bnx2x_fastpath *fp = fp_cookie;
	काष्ठा bnx2x *bp = fp->bp;
	u8 cos;

	DP(NETIF_MSG_INTR,
	   "got an MSI-X interrupt on IDX:SB [fp %d fw_sd %d igusb %d]\n",
	   fp->index, fp->fw_sb_id, fp->igu_sb_id);

	bnx2x_ack_sb(bp, fp->igu_sb_id, USTORM_ID, 0, IGU_INT_DISABLE, 0);

#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर (unlikely(bp->panic))
		वापस IRQ_HANDLED;
#पूर्ण_अगर

	/* Handle Rx and Tx according to MSI-X vector */
	क्रम_each_cos_in_tx_queue(fp, cos)
		prefetch(fp->txdata_ptr[cos]->tx_cons_sb);

	prefetch(&fp->sb_running_index[SM_RX_ID]);
	napi_schedule_irqoff(&bnx2x_fp(bp, fp->index, napi));

	वापस IRQ_HANDLED;
पूर्ण

/* HW Lock क्रम shared dual port PHYs */
व्योम bnx2x_acquire_phy_lock(काष्ठा bnx2x *bp)
अणु
	mutex_lock(&bp->port.phy_mutex);

	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_MDIO);
पूर्ण

व्योम bnx2x_release_phy_lock(काष्ठा bnx2x *bp)
अणु
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_MDIO);

	mutex_unlock(&bp->port.phy_mutex);
पूर्ण

/* calculates MF speed according to current linespeed and MF configuration */
u16 bnx2x_get_mf_speed(काष्ठा bnx2x *bp)
अणु
	u16 line_speed = bp->link_vars.line_speed;
	अगर (IS_MF(bp)) अणु
		u16 maxCfg = bnx2x_extract_max_cfg(bp,
						   bp->mf_config[BP_VN(bp)]);

		/* Calculate the current MAX line speed limit क्रम the MF
		 * devices
		 */
		अगर (IS_MF_PERCENT_BW(bp))
			line_speed = (line_speed * maxCfg) / 100;
		अन्यथा अणु /* SD mode */
			u16 vn_max_rate = maxCfg * 100;

			अगर (vn_max_rate < line_speed)
				line_speed = vn_max_rate;
		पूर्ण
	पूर्ण

	वापस line_speed;
पूर्ण

/**
 * bnx2x_fill_report_data - fill link report data to report
 *
 * @bp:		driver handle
 * @data:	link state to update
 *
 * It uses a none-atomic bit operations because is called under the mutex.
 */
अटल व्योम bnx2x_fill_report_data(काष्ठा bnx2x *bp,
				   काष्ठा bnx2x_link_report_data *data)
अणु
	स_रखो(data, 0, माप(*data));

	अगर (IS_PF(bp)) अणु
		/* Fill the report data: effective line speed */
		data->line_speed = bnx2x_get_mf_speed(bp);

		/* Link is करोwn */
		अगर (!bp->link_vars.link_up || (bp->flags & MF_FUNC_DIS))
			__set_bit(BNX2X_LINK_REPORT_LINK_DOWN,
				  &data->link_report_flags);

		अगर (!BNX2X_NUM_ETH_QUEUES(bp))
			__set_bit(BNX2X_LINK_REPORT_LINK_DOWN,
				  &data->link_report_flags);

		/* Full DUPLEX */
		अगर (bp->link_vars.duplex == DUPLEX_FULL)
			__set_bit(BNX2X_LINK_REPORT_FD,
				  &data->link_report_flags);

		/* Rx Flow Control is ON */
		अगर (bp->link_vars.flow_ctrl & BNX2X_FLOW_CTRL_RX)
			__set_bit(BNX2X_LINK_REPORT_RX_FC_ON,
				  &data->link_report_flags);

		/* Tx Flow Control is ON */
		अगर (bp->link_vars.flow_ctrl & BNX2X_FLOW_CTRL_TX)
			__set_bit(BNX2X_LINK_REPORT_TX_FC_ON,
				  &data->link_report_flags);
	पूर्ण अन्यथा अणु /* VF */
		*data = bp->vf_link_vars;
	पूर्ण
पूर्ण

/**
 * bnx2x_link_report - report link status to OS.
 *
 * @bp:		driver handle
 *
 * Calls the __bnx2x_link_report() under the same locking scheme
 * as a link/PHY state managing code to ensure a consistent link
 * reporting.
 */

व्योम bnx2x_link_report(काष्ठा bnx2x *bp)
अणु
	bnx2x_acquire_phy_lock(bp);
	__bnx2x_link_report(bp);
	bnx2x_release_phy_lock(bp);
पूर्ण

/**
 * __bnx2x_link_report - report link status to OS.
 *
 * @bp:		driver handle
 *
 * None atomic implementation.
 * Should be called under the phy_lock.
 */
व्योम __bnx2x_link_report(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_link_report_data cur_data;

	अगर (bp->क्रमce_link_करोwn) अणु
		bp->link_vars.link_up = 0;
		वापस;
	पूर्ण

	/* reपढ़ो mf_cfg */
	अगर (IS_PF(bp) && !CHIP_IS_E1(bp))
		bnx2x_पढ़ो_mf_cfg(bp);

	/* Read the current link report info */
	bnx2x_fill_report_data(bp, &cur_data);

	/* Don't report link करोwn or exactly the same link status twice */
	अगर (!स_भेद(&cur_data, &bp->last_reported_link, माप(cur_data)) ||
	    (test_bit(BNX2X_LINK_REPORT_LINK_DOWN,
		      &bp->last_reported_link.link_report_flags) &&
	     test_bit(BNX2X_LINK_REPORT_LINK_DOWN,
		      &cur_data.link_report_flags)))
		वापस;

	bp->link_cnt++;

	/* We are going to report a new link parameters now -
	 * remember the current data क्रम the next समय.
	 */
	स_नकल(&bp->last_reported_link, &cur_data, माप(cur_data));

	/* propagate status to VFs */
	अगर (IS_PF(bp))
		bnx2x_iov_link_update(bp);

	अगर (test_bit(BNX2X_LINK_REPORT_LINK_DOWN,
		     &cur_data.link_report_flags)) अणु
		netअगर_carrier_off(bp->dev);
		netdev_err(bp->dev, "NIC Link is Down\n");
		वापस;
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *duplex;
		स्थिर अक्षर *flow;

		netअगर_carrier_on(bp->dev);

		अगर (test_and_clear_bit(BNX2X_LINK_REPORT_FD,
				       &cur_data.link_report_flags))
			duplex = "full";
		अन्यथा
			duplex = "half";

		/* Handle the FC at the end so that only these flags would be
		 * possibly set. This way we may easily check अगर there is no FC
		 * enabled.
		 */
		अगर (cur_data.link_report_flags) अणु
			अगर (test_bit(BNX2X_LINK_REPORT_RX_FC_ON,
				     &cur_data.link_report_flags)) अणु
				अगर (test_bit(BNX2X_LINK_REPORT_TX_FC_ON,
				     &cur_data.link_report_flags))
					flow = "ON - receive & transmit";
				अन्यथा
					flow = "ON - receive";
			पूर्ण अन्यथा अणु
				flow = "ON - transmit";
			पूर्ण
		पूर्ण अन्यथा अणु
			flow = "none";
		पूर्ण
		netdev_info(bp->dev, "NIC Link is Up, %d Mbps %s duplex, Flow control: %s\n",
			    cur_data.line_speed, duplex, flow);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_set_next_page_sgl(काष्ठा bnx2x_fastpath *fp)
अणु
	पूर्णांक i;

	क्रम (i = 1; i <= NUM_RX_SGE_PAGES; i++) अणु
		काष्ठा eth_rx_sge *sge;

		sge = &fp->rx_sge_ring[RX_SGE_CNT * i - 2];
		sge->addr_hi =
			cpu_to_le32(U64_HI(fp->rx_sge_mapping +
			BCM_PAGE_SIZE*(i % NUM_RX_SGE_PAGES)));

		sge->addr_lo =
			cpu_to_le32(U64_LO(fp->rx_sge_mapping +
			BCM_PAGE_SIZE*(i % NUM_RX_SGE_PAGES)));
	पूर्ण
पूर्ण

अटल व्योम bnx2x_मुक्त_tpa_pool(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_fastpath *fp, पूर्णांक last)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < last; i++) अणु
		काष्ठा bnx2x_agg_info *tpa_info = &fp->tpa_info[i];
		काष्ठा sw_rx_bd *first_buf = &tpa_info->first_buf;
		u8 *data = first_buf->data;

		अगर (data == शून्य) अणु
			DP(NETIF_MSG_IFDOWN, "tpa bin %d empty on free\n", i);
			जारी;
		पूर्ण
		अगर (tpa_info->tpa_state == BNX2X_TPA_START)
			dma_unmap_single(&bp->pdev->dev,
					 dma_unmap_addr(first_buf, mapping),
					 fp->rx_buf_size, DMA_FROM_DEVICE);
		bnx2x_frag_मुक्त(fp, data);
		first_buf->data = शून्य;
	पूर्ण
पूर्ण

व्योम bnx2x_init_rx_rings_cnic(काष्ठा bnx2x *bp)
अणु
	पूर्णांक j;

	क्रम_each_rx_queue_cnic(bp, j) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[j];

		fp->rx_bd_cons = 0;

		/* Activate BD ring */
		/* Warning!
		 * this will generate an पूर्णांकerrupt (to the TSTORM)
		 * must only be करोne after chip is initialized
		 */
		bnx2x_update_rx_prod(bp, fp, fp->rx_bd_prod, fp->rx_comp_prod,
				     fp->rx_sge_prod);
	पूर्ण
पूर्ण

व्योम bnx2x_init_rx_rings(काष्ठा bnx2x *bp)
अणु
	पूर्णांक func = BP_FUNC(bp);
	u16 ring_prod;
	पूर्णांक i, j;

	/* Allocate TPA resources */
	क्रम_each_eth_queue(bp, j) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[j];

		DP(NETIF_MSG_IFUP,
		   "mtu %d  rx_buf_size %d\n", bp->dev->mtu, fp->rx_buf_size);

		अगर (fp->mode != TPA_MODE_DISABLED) अणु
			/* Fill the per-aggregation pool */
			क्रम (i = 0; i < MAX_AGG_QS(bp); i++) अणु
				काष्ठा bnx2x_agg_info *tpa_info =
					&fp->tpa_info[i];
				काष्ठा sw_rx_bd *first_buf =
					&tpa_info->first_buf;

				first_buf->data =
					bnx2x_frag_alloc(fp, GFP_KERNEL);
				अगर (!first_buf->data) अणु
					BNX2X_ERR("Failed to allocate TPA skb pool for queue[%d] - disabling TPA on this queue!\n",
						  j);
					bnx2x_मुक्त_tpa_pool(bp, fp, i);
					fp->mode = TPA_MODE_DISABLED;
					अवरोध;
				पूर्ण
				dma_unmap_addr_set(first_buf, mapping, 0);
				tpa_info->tpa_state = BNX2X_TPA_STOP;
			पूर्ण

			/* "next page" elements initialization */
			bnx2x_set_next_page_sgl(fp);

			/* set SGEs bit mask */
			bnx2x_init_sge_ring_bit_mask(fp);

			/* Allocate SGEs and initialize the ring elements */
			क्रम (i = 0, ring_prod = 0;
			     i < MAX_RX_SGE_CNT*NUM_RX_SGE_PAGES; i++) अणु

				अगर (bnx2x_alloc_rx_sge(bp, fp, ring_prod,
						       GFP_KERNEL) < 0) अणु
					BNX2X_ERR("was only able to allocate %d rx sges\n",
						  i);
					BNX2X_ERR("disabling TPA for queue[%d]\n",
						  j);
					/* Cleanup alपढ़ोy allocated elements */
					bnx2x_मुक्त_rx_sge_range(bp, fp,
								ring_prod);
					bnx2x_मुक्त_tpa_pool(bp, fp,
							    MAX_AGG_QS(bp));
					fp->mode = TPA_MODE_DISABLED;
					ring_prod = 0;
					अवरोध;
				पूर्ण
				ring_prod = NEXT_SGE_IDX(ring_prod);
			पूर्ण

			fp->rx_sge_prod = ring_prod;
		पूर्ण
	पूर्ण

	क्रम_each_eth_queue(bp, j) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[j];

		fp->rx_bd_cons = 0;

		/* Activate BD ring */
		/* Warning!
		 * this will generate an पूर्णांकerrupt (to the TSTORM)
		 * must only be करोne after chip is initialized
		 */
		bnx2x_update_rx_prod(bp, fp, fp->rx_bd_prod, fp->rx_comp_prod,
				     fp->rx_sge_prod);

		अगर (j != 0)
			जारी;

		अगर (CHIP_IS_E1(bp)) अणु
			REG_WR(bp, BAR_USTRORM_INTMEM +
			       USTORM_MEM_WORKAROUND_ADDRESS_OFFSET(func),
			       U64_LO(fp->rx_comp_mapping));
			REG_WR(bp, BAR_USTRORM_INTMEM +
			       USTORM_MEM_WORKAROUND_ADDRESS_OFFSET(func) + 4,
			       U64_HI(fp->rx_comp_mapping));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnx2x_मुक्त_tx_skbs_queue(काष्ठा bnx2x_fastpath *fp)
अणु
	u8 cos;
	काष्ठा bnx2x *bp = fp->bp;

	क्रम_each_cos_in_tx_queue(fp, cos) अणु
		काष्ठा bnx2x_fp_txdata *txdata = fp->txdata_ptr[cos];
		अचिन्हित pkts_compl = 0, bytes_compl = 0;

		u16 sw_prod = txdata->tx_pkt_prod;
		u16 sw_cons = txdata->tx_pkt_cons;

		जबतक (sw_cons != sw_prod) अणु
			bnx2x_मुक्त_tx_pkt(bp, txdata, TX_BD(sw_cons),
					  &pkts_compl, &bytes_compl);
			sw_cons++;
		पूर्ण

		netdev_tx_reset_queue(
			netdev_get_tx_queue(bp->dev,
					    txdata->txq_index));
	पूर्ण
पूर्ण

अटल व्योम bnx2x_मुक्त_tx_skbs_cnic(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम_each_tx_queue_cnic(bp, i) अणु
		bnx2x_मुक्त_tx_skbs_queue(&bp->fp[i]);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_मुक्त_tx_skbs(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम_each_eth_queue(bp, i) अणु
		bnx2x_मुक्त_tx_skbs_queue(&bp->fp[i]);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_मुक्त_rx_bds(काष्ठा bnx2x_fastpath *fp)
अणु
	काष्ठा bnx2x *bp = fp->bp;
	पूर्णांक i;

	/* ring wasn't allocated */
	अगर (fp->rx_buf_ring == शून्य)
		वापस;

	क्रम (i = 0; i < NUM_RX_BD; i++) अणु
		काष्ठा sw_rx_bd *rx_buf = &fp->rx_buf_ring[i];
		u8 *data = rx_buf->data;

		अगर (data == शून्य)
			जारी;
		dma_unmap_single(&bp->pdev->dev,
				 dma_unmap_addr(rx_buf, mapping),
				 fp->rx_buf_size, DMA_FROM_DEVICE);

		rx_buf->data = शून्य;
		bnx2x_frag_मुक्त(fp, data);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_मुक्त_rx_skbs_cnic(काष्ठा bnx2x *bp)
अणु
	पूर्णांक j;

	क्रम_each_rx_queue_cnic(bp, j) अणु
		bnx2x_मुक्त_rx_bds(&bp->fp[j]);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_मुक्त_rx_skbs(काष्ठा bnx2x *bp)
अणु
	पूर्णांक j;

	क्रम_each_eth_queue(bp, j) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[j];

		bnx2x_मुक्त_rx_bds(fp);

		अगर (fp->mode != TPA_MODE_DISABLED)
			bnx2x_मुक्त_tpa_pool(bp, fp, MAX_AGG_QS(bp));
	पूर्ण
पूर्ण

अटल व्योम bnx2x_मुक्त_skbs_cnic(काष्ठा bnx2x *bp)
अणु
	bnx2x_मुक्त_tx_skbs_cnic(bp);
	bnx2x_मुक्त_rx_skbs_cnic(bp);
पूर्ण

व्योम bnx2x_मुक्त_skbs(काष्ठा bnx2x *bp)
अणु
	bnx2x_मुक्त_tx_skbs(bp);
	bnx2x_मुक्त_rx_skbs(bp);
पूर्ण

व्योम bnx2x_update_max_mf_config(काष्ठा bnx2x *bp, u32 value)
अणु
	/* load old values */
	u32 mf_cfg = bp->mf_config[BP_VN(bp)];

	अगर (value != bnx2x_extract_max_cfg(bp, mf_cfg)) अणु
		/* leave all but MAX value */
		mf_cfg &= ~FUNC_MF_CFG_MAX_BW_MASK;

		/* set new MAX value */
		mf_cfg |= (value << FUNC_MF_CFG_MAX_BW_SHIFT)
				& FUNC_MF_CFG_MAX_BW_MASK;

		bnx2x_fw_command(bp, DRV_MSG_CODE_SET_MF_BW, mf_cfg);
	पूर्ण
पूर्ण

/**
 * bnx2x_मुक्त_msix_irqs - मुक्त previously requested MSI-X IRQ vectors
 *
 * @bp:		driver handle
 * @nvecs:	number of vectors to be released
 */
अटल व्योम bnx2x_मुक्त_msix_irqs(काष्ठा bnx2x *bp, पूर्णांक nvecs)
अणु
	पूर्णांक i, offset = 0;

	अगर (nvecs == offset)
		वापस;

	/* VFs करोn't have a शेष SB */
	अगर (IS_PF(bp)) अणु
		मुक्त_irq(bp->msix_table[offset].vector, bp->dev);
		DP(NETIF_MSG_IFDOWN, "released sp irq (%d)\n",
		   bp->msix_table[offset].vector);
		offset++;
	पूर्ण

	अगर (CNIC_SUPPORT(bp)) अणु
		अगर (nvecs == offset)
			वापस;
		offset++;
	पूर्ण

	क्रम_each_eth_queue(bp, i) अणु
		अगर (nvecs == offset)
			वापस;
		DP(NETIF_MSG_IFDOWN, "about to release fp #%d->%d irq\n",
		   i, bp->msix_table[offset].vector);

		मुक्त_irq(bp->msix_table[offset++].vector, &bp->fp[i]);
	पूर्ण
पूर्ण

व्योम bnx2x_मुक्त_irq(काष्ठा bnx2x *bp)
अणु
	अगर (bp->flags & USING_MSIX_FLAG &&
	    !(bp->flags & USING_SINGLE_MSIX_FLAG)) अणु
		पूर्णांक nvecs = BNX2X_NUM_ETH_QUEUES(bp) + CNIC_SUPPORT(bp);

		/* vfs करोn't have a शेष status block */
		अगर (IS_PF(bp))
			nvecs++;

		bnx2x_मुक्त_msix_irqs(bp, nvecs);
	पूर्ण अन्यथा अणु
		मुक्त_irq(bp->dev->irq, bp->dev);
	पूर्ण
पूर्ण

पूर्णांक bnx2x_enable_msix(काष्ठा bnx2x *bp)
अणु
	पूर्णांक msix_vec = 0, i, rc;

	/* VFs करोn't have a शेष status block */
	अगर (IS_PF(bp)) अणु
		bp->msix_table[msix_vec].entry = msix_vec;
		BNX2X_DEV_INFO("msix_table[0].entry = %d (slowpath)\n",
			       bp->msix_table[0].entry);
		msix_vec++;
	पूर्ण

	/* Cnic requires an msix vector क्रम itself */
	अगर (CNIC_SUPPORT(bp)) अणु
		bp->msix_table[msix_vec].entry = msix_vec;
		BNX2X_DEV_INFO("msix_table[%d].entry = %d (CNIC)\n",
			       msix_vec, bp->msix_table[msix_vec].entry);
		msix_vec++;
	पूर्ण

	/* We need separate vectors क्रम ETH queues only (not FCoE) */
	क्रम_each_eth_queue(bp, i) अणु
		bp->msix_table[msix_vec].entry = msix_vec;
		BNX2X_DEV_INFO("msix_table[%d].entry = %d (fastpath #%u)\n",
			       msix_vec, msix_vec, i);
		msix_vec++;
	पूर्ण

	DP(BNX2X_MSG_SP, "about to request enable msix with %d vectors\n",
	   msix_vec);

	rc = pci_enable_msix_range(bp->pdev, &bp->msix_table[0],
				   BNX2X_MIN_MSIX_VEC_CNT(bp), msix_vec);
	/*
	 * reconfigure number of tx/rx queues according to available
	 * MSI-X vectors
	 */
	अगर (rc == -ENOSPC) अणु
		/* Get by with single vector */
		rc = pci_enable_msix_range(bp->pdev, &bp->msix_table[0], 1, 1);
		अगर (rc < 0) अणु
			BNX2X_DEV_INFO("Single MSI-X is not attainable rc %d\n",
				       rc);
			जाओ no_msix;
		पूर्ण

		BNX2X_DEV_INFO("Using single MSI-X vector\n");
		bp->flags |= USING_SINGLE_MSIX_FLAG;

		BNX2X_DEV_INFO("set number of queues to 1\n");
		bp->num_ethernet_queues = 1;
		bp->num_queues = bp->num_ethernet_queues + bp->num_cnic_queues;
	पूर्ण अन्यथा अगर (rc < 0) अणु
		BNX2X_DEV_INFO("MSI-X is not attainable rc %d\n", rc);
		जाओ no_msix;
	पूर्ण अन्यथा अगर (rc < msix_vec) अणु
		/* how less vectors we will have? */
		पूर्णांक dअगरf = msix_vec - rc;

		BNX2X_DEV_INFO("Trying to use less MSI-X vectors: %d\n", rc);

		/*
		 * decrease number of queues by number of unallocated entries
		 */
		bp->num_ethernet_queues -= dअगरf;
		bp->num_queues = bp->num_ethernet_queues + bp->num_cnic_queues;

		BNX2X_DEV_INFO("New queue configuration set: %d\n",
			       bp->num_queues);
	पूर्ण

	bp->flags |= USING_MSIX_FLAG;

	वापस 0;

no_msix:
	/* fall to INTx अगर not enough memory */
	अगर (rc == -ENOMEM)
		bp->flags |= DISABLE_MSI_FLAG;

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_req_msix_irqs(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i, rc, offset = 0;

	/* no शेष status block क्रम vf */
	अगर (IS_PF(bp)) अणु
		rc = request_irq(bp->msix_table[offset++].vector,
				 bnx2x_msix_sp_पूर्णांक, 0,
				 bp->dev->name, bp->dev);
		अगर (rc) अणु
			BNX2X_ERR("request sp irq failed\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (CNIC_SUPPORT(bp))
		offset++;

	क्रम_each_eth_queue(bp, i) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[i];
		snम_लिखो(fp->name, माप(fp->name), "%s-fp-%d",
			 bp->dev->name, i);

		rc = request_irq(bp->msix_table[offset].vector,
				 bnx2x_msix_fp_पूर्णांक, 0, fp->name, fp);
		अगर (rc) अणु
			BNX2X_ERR("request fp #%d irq (%d) failed  rc %d\n", i,
			      bp->msix_table[offset].vector, rc);
			bnx2x_मुक्त_msix_irqs(bp, offset);
			वापस -EBUSY;
		पूर्ण

		offset++;
	पूर्ण

	i = BNX2X_NUM_ETH_QUEUES(bp);
	अगर (IS_PF(bp)) अणु
		offset = 1 + CNIC_SUPPORT(bp);
		netdev_info(bp->dev,
			    "using MSI-X  IRQs: sp %d  fp[%d] %d ... fp[%d] %d\n",
			    bp->msix_table[0].vector,
			    0, bp->msix_table[offset].vector,
			    i - 1, bp->msix_table[offset + i - 1].vector);
	पूर्ण अन्यथा अणु
		offset = CNIC_SUPPORT(bp);
		netdev_info(bp->dev,
			    "using MSI-X  IRQs: fp[%d] %d ... fp[%d] %d\n",
			    0, bp->msix_table[offset].vector,
			    i - 1, bp->msix_table[offset + i - 1].vector);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक bnx2x_enable_msi(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc;

	rc = pci_enable_msi(bp->pdev);
	अगर (rc) अणु
		BNX2X_DEV_INFO("MSI is not attainable\n");
		वापस -1;
	पूर्ण
	bp->flags |= USING_MSI_FLAG;

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_req_irq(काष्ठा bnx2x *bp)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक irq;

	अगर (bp->flags & (USING_MSI_FLAG | USING_MSIX_FLAG))
		flags = 0;
	अन्यथा
		flags = IRQF_SHARED;

	अगर (bp->flags & USING_MSIX_FLAG)
		irq = bp->msix_table[0].vector;
	अन्यथा
		irq = bp->pdev->irq;

	वापस request_irq(irq, bnx2x_पूर्णांकerrupt, flags, bp->dev->name, bp->dev);
पूर्ण

अटल पूर्णांक bnx2x_setup_irqs(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc = 0;
	अगर (bp->flags & USING_MSIX_FLAG &&
	    !(bp->flags & USING_SINGLE_MSIX_FLAG)) अणु
		rc = bnx2x_req_msix_irqs(bp);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		rc = bnx2x_req_irq(bp);
		अगर (rc) अणु
			BNX2X_ERR("IRQ request failed  rc %d, aborting\n", rc);
			वापस rc;
		पूर्ण
		अगर (bp->flags & USING_MSI_FLAG) अणु
			bp->dev->irq = bp->pdev->irq;
			netdev_info(bp->dev, "using MSI IRQ %d\n",
				    bp->dev->irq);
		पूर्ण
		अगर (bp->flags & USING_MSIX_FLAG) अणु
			bp->dev->irq = bp->msix_table[0].vector;
			netdev_info(bp->dev, "using MSIX IRQ %d\n",
				    bp->dev->irq);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnx2x_napi_enable_cnic(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम_each_rx_queue_cnic(bp, i) अणु
		napi_enable(&bnx2x_fp(bp, i, napi));
	पूर्ण
पूर्ण

अटल व्योम bnx2x_napi_enable(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम_each_eth_queue(bp, i) अणु
		napi_enable(&bnx2x_fp(bp, i, napi));
	पूर्ण
पूर्ण

अटल व्योम bnx2x_napi_disable_cnic(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम_each_rx_queue_cnic(bp, i) अणु
		napi_disable(&bnx2x_fp(bp, i, napi));
	पूर्ण
पूर्ण

अटल व्योम bnx2x_napi_disable(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम_each_eth_queue(bp, i) अणु
		napi_disable(&bnx2x_fp(bp, i, napi));
	पूर्ण
पूर्ण

व्योम bnx2x_netअगर_start(काष्ठा bnx2x *bp)
अणु
	अगर (netअगर_running(bp->dev)) अणु
		bnx2x_napi_enable(bp);
		अगर (CNIC_LOADED(bp))
			bnx2x_napi_enable_cnic(bp);
		bnx2x_पूर्णांक_enable(bp);
		अगर (bp->state == BNX2X_STATE_OPEN)
			netअगर_tx_wake_all_queues(bp->dev);
	पूर्ण
पूर्ण

व्योम bnx2x_netअगर_stop(काष्ठा bnx2x *bp, पूर्णांक disable_hw)
अणु
	bnx2x_पूर्णांक_disable_sync(bp, disable_hw);
	bnx2x_napi_disable(bp);
	अगर (CNIC_LOADED(bp))
		bnx2x_napi_disable_cnic(bp);
पूर्ण

u16 bnx2x_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		       काष्ठा net_device *sb_dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (CNIC_LOADED(bp) && !NO_FCOE(bp)) अणु
		काष्ठा ethhdr *hdr = (काष्ठा ethhdr *)skb->data;
		u16 ether_type = ntohs(hdr->h_proto);

		/* Skip VLAN tag अगर present */
		अगर (ether_type == ETH_P_8021Q) अणु
			काष्ठा vlan_ethhdr *vhdr =
				(काष्ठा vlan_ethhdr *)skb->data;

			ether_type = ntohs(vhdr->h_vlan_encapsulated_proto);
		पूर्ण

		/* If ethertype is FCoE or FIP - use FCoE ring */
		अगर ((ether_type == ETH_P_FCOE) || (ether_type == ETH_P_FIP))
			वापस bnx2x_fcoe_tx(bp, txq_index);
	पूर्ण

	/* select a non-FCoE queue */
	वापस netdev_pick_tx(dev, skb, शून्य) %
			(BNX2X_NUM_ETH_QUEUES(bp) * bp->max_cos);
पूर्ण

व्योम bnx2x_set_num_queues(काष्ठा bnx2x *bp)
अणु
	/* RSS queues */
	bp->num_ethernet_queues = bnx2x_calc_num_queues(bp);

	/* override in STORAGE SD modes */
	अगर (IS_MF_STORAGE_ONLY(bp))
		bp->num_ethernet_queues = 1;

	/* Add special queues */
	bp->num_cnic_queues = CNIC_SUPPORT(bp); /* For FCOE */
	bp->num_queues = bp->num_ethernet_queues + bp->num_cnic_queues;

	BNX2X_DEV_INFO("set number of queues to %d\n", bp->num_queues);
पूर्ण

/**
 * bnx2x_set_real_num_queues - configure netdev->real_num_[tx,rx]_queues
 *
 * @bp:		Driver handle
 * @include_cnic: handle cnic हाल
 *
 * We currently support क्रम at most 16 Tx queues क्रम each CoS thus we will
 * allocate a multiple of 16 क्रम ETH L2 rings according to the value of the
 * bp->max_cos.
 *
 * If there is an FCoE L2 queue the appropriate Tx queue will have the next
 * index after all ETH L2 indices.
 *
 * If the actual number of Tx queues (क्रम each CoS) is less than 16 then there
 * will be the holes at the end of each group of 16 ETh L2 indices (0..15,
 * 16..31,...) with indices that are not coupled with any real Tx queue.
 *
 * The proper configuration of skb->queue_mapping is handled by
 * bnx2x_select_queue() and __skb_tx_hash().
 *
 * bnx2x_setup_tc() takes care of the proper TC mappings so that __skb_tx_hash()
 * will वापस a proper Tx index अगर TC is enabled (netdev->num_tc > 0).
 */
अटल पूर्णांक bnx2x_set_real_num_queues(काष्ठा bnx2x *bp, पूर्णांक include_cnic)
अणु
	पूर्णांक rc, tx, rx;

	tx = BNX2X_NUM_ETH_QUEUES(bp) * bp->max_cos;
	rx = BNX2X_NUM_ETH_QUEUES(bp);

/* account क्रम fcoe queue */
	अगर (include_cnic && !NO_FCOE(bp)) अणु
		rx++;
		tx++;
	पूर्ण

	rc = netअगर_set_real_num_tx_queues(bp->dev, tx);
	अगर (rc) अणु
		BNX2X_ERR("Failed to set real number of Tx queues: %d\n", rc);
		वापस rc;
	पूर्ण
	rc = netअगर_set_real_num_rx_queues(bp->dev, rx);
	अगर (rc) अणु
		BNX2X_ERR("Failed to set real number of Rx queues: %d\n", rc);
		वापस rc;
	पूर्ण

	DP(NETIF_MSG_IFUP, "Setting real num queues to (tx, rx) (%d, %d)\n",
			  tx, rx);

	वापस rc;
पूर्ण

अटल व्योम bnx2x_set_rx_buf_size(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम_each_queue(bp, i) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[i];
		u32 mtu;

		/* Always use a mini-jumbo MTU क्रम the FCoE L2 ring */
		अगर (IS_FCOE_IDX(i))
			/*
			 * Although there are no IP frames expected to arrive to
			 * this ring we still want to add an
			 * IP_HEADER_ALIGNMENT_PADDING to prevent a buffer
			 * overrun attack.
			 */
			mtu = BNX2X_FCOE_MINI_JUMBO_MTU;
		अन्यथा
			mtu = bp->dev->mtu;
		fp->rx_buf_size = BNX2X_FW_RX_ALIGN_START +
				  IP_HEADER_ALIGNMENT_PADDING +
				  ETH_OVERHEAD +
				  mtu +
				  BNX2X_FW_RX_ALIGN_END;
		fp->rx_buf_size = SKB_DATA_ALIGN(fp->rx_buf_size);
		/* Note : rx_buf_size करोesn't take पूर्णांकo account NET_SKB_PAD */
		अगर (fp->rx_buf_size + NET_SKB_PAD <= PAGE_SIZE)
			fp->rx_frag_size = fp->rx_buf_size + NET_SKB_PAD;
		अन्यथा
			fp->rx_frag_size = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_init_rss(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;
	u8 num_eth_queues = BNX2X_NUM_ETH_QUEUES(bp);

	/* Prepare the initial contents क्रम the indirection table अगर RSS is
	 * enabled
	 */
	क्रम (i = 0; i < माप(bp->rss_conf_obj.ind_table); i++)
		bp->rss_conf_obj.ind_table[i] =
			bp->fp->cl_id +
			ethtool_rxfh_indir_शेष(i, num_eth_queues);

	/*
	 * For 57710 and 57711 SEARCHER configuration (rss_keys) is
	 * per-port, so अगर explicit configuration is needed , करो it only
	 * क्रम a PMF.
	 *
	 * For 57712 and newer on the other hand it's a per-function
	 * configuration.
	 */
	वापस bnx2x_config_rss_eth(bp, bp->port.pmf || !CHIP_IS_E1x(bp));
पूर्ण

पूर्णांक bnx2x_rss(काष्ठा bnx2x *bp, काष्ठा bnx2x_rss_config_obj *rss_obj,
	      bool config_hash, bool enable)
अणु
	काष्ठा bnx2x_config_rss_params params = अणुशून्यपूर्ण;

	/* Although RSS is meaningless when there is a single HW queue we
	 * still need it enabled in order to have HW Rx hash generated.
	 *
	 * अगर (!is_eth_multi(bp))
	 *      bp->multi_mode = ETH_RSS_MODE_DISABLED;
	 */

	params.rss_obj = rss_obj;

	__set_bit(RAMROD_COMP_WAIT, &params.ramrod_flags);

	अगर (enable) अणु
		__set_bit(BNX2X_RSS_MODE_REGULAR, &params.rss_flags);

		/* RSS configuration */
		__set_bit(BNX2X_RSS_IPV4, &params.rss_flags);
		__set_bit(BNX2X_RSS_IPV4_TCP, &params.rss_flags);
		__set_bit(BNX2X_RSS_IPV6, &params.rss_flags);
		__set_bit(BNX2X_RSS_IPV6_TCP, &params.rss_flags);
		अगर (rss_obj->udp_rss_v4)
			__set_bit(BNX2X_RSS_IPV4_UDP, &params.rss_flags);
		अगर (rss_obj->udp_rss_v6)
			__set_bit(BNX2X_RSS_IPV6_UDP, &params.rss_flags);

		अगर (!CHIP_IS_E1x(bp)) अणु
			/* valid only क्रम TUNN_MODE_VXLAN tunnel mode */
			__set_bit(BNX2X_RSS_IPV4_VXLAN, &params.rss_flags);
			__set_bit(BNX2X_RSS_IPV6_VXLAN, &params.rss_flags);

			/* valid only क्रम TUNN_MODE_GRE tunnel mode */
			__set_bit(BNX2X_RSS_TUNN_INNER_HDRS, &params.rss_flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		__set_bit(BNX2X_RSS_MODE_DISABLED, &params.rss_flags);
	पूर्ण

	/* Hash bits */
	params.rss_result_mask = MULTI_MASK;

	स_नकल(params.ind_table, rss_obj->ind_table, माप(params.ind_table));

	अगर (config_hash) अणु
		/* RSS keys */
		netdev_rss_key_fill(params.rss_key, T_ETH_RSS_KEY * 4);
		__set_bit(BNX2X_RSS_SET_SRCH, &params.rss_flags);
	पूर्ण

	अगर (IS_PF(bp))
		वापस bnx2x_config_rss(bp, &params);
	अन्यथा
		वापस bnx2x_vfpf_config_rss(bp, &params);
पूर्ण

अटल पूर्णांक bnx2x_init_hw(काष्ठा bnx2x *bp, u32 load_code)
अणु
	काष्ठा bnx2x_func_state_params func_params = अणुशून्यपूर्ण;

	/* Prepare parameters क्रम function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_HW_INIT;

	func_params.params.hw_init.load_phase = load_code;

	वापस bnx2x_func_state_change(bp, &func_params);
पूर्ण

/*
 * Cleans the object that have पूर्णांकernal lists without sending
 * ramrods. Should be run when पूर्णांकerrupts are disabled.
 */
व्योम bnx2x_squeeze_objects(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ ramrod_flags = 0, vlan_mac_flags = 0;
	काष्ठा bnx2x_mcast_ramrod_params rparam = अणुशून्यपूर्ण;
	काष्ठा bnx2x_vlan_mac_obj *mac_obj = &bp->sp_objs->mac_obj;

	/***************** Cleanup MACs' object first *************************/

	/* Wait क्रम completion of requested */
	__set_bit(RAMROD_COMP_WAIT, &ramrod_flags);
	/* Perक्रमm a dry cleanup */
	__set_bit(RAMROD_DRV_CLR_ONLY, &ramrod_flags);

	/* Clean ETH primary MAC */
	__set_bit(BNX2X_ETH_MAC, &vlan_mac_flags);
	rc = mac_obj->delete_all(bp, &bp->sp_objs->mac_obj, &vlan_mac_flags,
				 &ramrod_flags);
	अगर (rc != 0)
		BNX2X_ERR("Failed to clean ETH MACs: %d\n", rc);

	/* Cleanup UC list */
	vlan_mac_flags = 0;
	__set_bit(BNX2X_UC_LIST_MAC, &vlan_mac_flags);
	rc = mac_obj->delete_all(bp, mac_obj, &vlan_mac_flags,
				 &ramrod_flags);
	अगर (rc != 0)
		BNX2X_ERR("Failed to clean UC list MACs: %d\n", rc);

	/***************** Now clean mcast object *****************************/
	rparam.mcast_obj = &bp->mcast_obj;
	__set_bit(RAMROD_DRV_CLR_ONLY, &rparam.ramrod_flags);

	/* Add a DEL command... - Since we're करोing a driver cleanup only,
	 * we take a lock surrounding both the initial send and the CONTs,
	 * as we करोn't want a true completion to disrupt us in the middle.
	 */
	netअगर_addr_lock_bh(bp->dev);
	rc = bnx2x_config_mcast(bp, &rparam, BNX2X_MCAST_CMD_DEL);
	अगर (rc < 0)
		BNX2X_ERR("Failed to add a new DEL command to a multi-cast object: %d\n",
			  rc);

	/* ...and रुको until all pending commands are cleared */
	rc = bnx2x_config_mcast(bp, &rparam, BNX2X_MCAST_CMD_CONT);
	जबतक (rc != 0) अणु
		अगर (rc < 0) अणु
			BNX2X_ERR("Failed to clean multi-cast object: %d\n",
				  rc);
			netअगर_addr_unlock_bh(bp->dev);
			वापस;
		पूर्ण

		rc = bnx2x_config_mcast(bp, &rparam, BNX2X_MCAST_CMD_CONT);
	पूर्ण
	netअगर_addr_unlock_bh(bp->dev);
पूर्ण

#अगर_अघोषित BNX2X_STOP_ON_ERROR
#घोषणा LOAD_ERROR_EXIT(bp, label) \
	करो अणु \
		(bp)->state = BNX2X_STATE_ERROR; \
		जाओ label; \
	पूर्ण जबतक (0)

#घोषणा LOAD_ERROR_EXIT_CNIC(bp, label) \
	करो अणु \
		bp->cnic_loaded = false; \
		जाओ label; \
	पूर्ण जबतक (0)
#अन्यथा /*BNX2X_STOP_ON_ERROR*/
#घोषणा LOAD_ERROR_EXIT(bp, label) \
	करो अणु \
		(bp)->state = BNX2X_STATE_ERROR; \
		(bp)->panic = 1; \
		वापस -EBUSY; \
	पूर्ण जबतक (0)
#घोषणा LOAD_ERROR_EXIT_CNIC(bp, label) \
	करो अणु \
		bp->cnic_loaded = false; \
		(bp)->panic = 1; \
		वापस -EBUSY; \
	पूर्ण जबतक (0)
#पूर्ण_अगर /*BNX2X_STOP_ON_ERROR*/

अटल व्योम bnx2x_मुक्त_fw_stats_mem(काष्ठा bnx2x *bp)
अणु
	BNX2X_PCI_FREE(bp->fw_stats, bp->fw_stats_mapping,
		       bp->fw_stats_data_sz + bp->fw_stats_req_sz);
	वापस;
पूर्ण

अटल पूर्णांक bnx2x_alloc_fw_stats_mem(काष्ठा bnx2x *bp)
अणु
	पूर्णांक num_groups, vf_headroom = 0;
	पूर्णांक is_fcoe_stats = NO_FCOE(bp) ? 0 : 1;

	/* number of queues क्रम statistics is number of eth queues + FCoE */
	u8 num_queue_stats = BNX2X_NUM_ETH_QUEUES(bp) + is_fcoe_stats;

	/* Total number of FW statistics requests =
	 * 1 क्रम port stats + 1 क्रम PF stats + potential 2 क्रम FCoE (fcoe proper
	 * and fcoe l2 queue) stats + num of queues (which includes another 1
	 * क्रम fcoe l2 queue अगर applicable)
	 */
	bp->fw_stats_num = 2 + is_fcoe_stats + num_queue_stats;

	/* vf stats appear in the request list, but their data is allocated by
	 * the VFs themselves. We करोn't include them in the bp->fw_stats_num as
	 * it is used to determine where to place the vf stats queries in the
	 * request काष्ठा
	 */
	अगर (IS_SRIOV(bp))
		vf_headroom = bnx2x_vf_headroom(bp);

	/* Request is built from stats_query_header and an array of
	 * stats_query_cmd_group each of which contains
	 * STATS_QUERY_CMD_COUNT rules. The real number or requests is
	 * configured in the stats_query_header.
	 */
	num_groups =
		(((bp->fw_stats_num + vf_headroom) / STATS_QUERY_CMD_COUNT) +
		 (((bp->fw_stats_num + vf_headroom) % STATS_QUERY_CMD_COUNT) ?
		 1 : 0));

	DP(BNX2X_MSG_SP, "stats fw_stats_num %d, vf headroom %d, num_groups %d\n",
	   bp->fw_stats_num, vf_headroom, num_groups);
	bp->fw_stats_req_sz = माप(काष्ठा stats_query_header) +
		num_groups * माप(काष्ठा stats_query_cmd_group);

	/* Data क्रम statistics requests + stats_counter
	 * stats_counter holds per-STORM counters that are incremented
	 * when STORM has finished with the current request.
	 * memory क्रम FCoE offloaded statistics are counted anyway,
	 * even अगर they will not be sent.
	 * VF stats are not accounted क्रम here as the data of VF stats is stored
	 * in memory allocated by the VF, not here.
	 */
	bp->fw_stats_data_sz = माप(काष्ठा per_port_stats) +
		माप(काष्ठा per_pf_stats) +
		माप(काष्ठा fcoe_statistics_params) +
		माप(काष्ठा per_queue_stats) * num_queue_stats +
		माप(काष्ठा stats_counter);

	bp->fw_stats = BNX2X_PCI_ALLOC(&bp->fw_stats_mapping,
				       bp->fw_stats_data_sz + bp->fw_stats_req_sz);
	अगर (!bp->fw_stats)
		जाओ alloc_mem_err;

	/* Set लघुcuts */
	bp->fw_stats_req = (काष्ठा bnx2x_fw_stats_req *)bp->fw_stats;
	bp->fw_stats_req_mapping = bp->fw_stats_mapping;
	bp->fw_stats_data = (काष्ठा bnx2x_fw_stats_data *)
		((u8 *)bp->fw_stats + bp->fw_stats_req_sz);
	bp->fw_stats_data_mapping = bp->fw_stats_mapping +
		bp->fw_stats_req_sz;

	DP(BNX2X_MSG_SP, "statistics request base address set to %x %x\n",
	   U64_HI(bp->fw_stats_req_mapping),
	   U64_LO(bp->fw_stats_req_mapping));
	DP(BNX2X_MSG_SP, "statistics data base address set to %x %x\n",
	   U64_HI(bp->fw_stats_data_mapping),
	   U64_LO(bp->fw_stats_data_mapping));
	वापस 0;

alloc_mem_err:
	bnx2x_मुक्त_fw_stats_mem(bp);
	BNX2X_ERR("Can't allocate FW stats memory\n");
	वापस -ENOMEM;
पूर्ण

/* send load request to mcp and analyze response */
अटल पूर्णांक bnx2x_nic_load_request(काष्ठा bnx2x *bp, u32 *load_code)
अणु
	u32 param;

	/* init fw_seq */
	bp->fw_seq =
		(SHMEM_RD(bp, func_mb[BP_FW_MB_IDX(bp)].drv_mb_header) &
		 DRV_MSG_SEQ_NUMBER_MASK);
	BNX2X_DEV_INFO("fw_seq 0x%08x\n", bp->fw_seq);

	/* Get current FW pulse sequence */
	bp->fw_drv_pulse_wr_seq =
		(SHMEM_RD(bp, func_mb[BP_FW_MB_IDX(bp)].drv_pulse_mb) &
		 DRV_PULSE_SEQ_MASK);
	BNX2X_DEV_INFO("drv_pulse 0x%x\n", bp->fw_drv_pulse_wr_seq);

	param = DRV_MSG_CODE_LOAD_REQ_WITH_LFA;

	अगर (IS_MF_SD(bp) && bnx2x_port_after_undi(bp))
		param |= DRV_MSG_CODE_LOAD_REQ_FORCE_LFA;

	/* load request */
	(*load_code) = bnx2x_fw_command(bp, DRV_MSG_CODE_LOAD_REQ, param);

	/* अगर mcp fails to respond we must पात */
	अगर (!(*load_code)) अणु
		BNX2X_ERR("MCP response failure, aborting\n");
		वापस -EBUSY;
	पूर्ण

	/* If mcp refused (e.g. other port is in diagnostic mode) we
	 * must पात
	 */
	अगर ((*load_code) == FW_MSG_CODE_DRV_LOAD_REFUSED) अणु
		BNX2X_ERR("MCP refused load request, aborting\n");
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

/* check whether another PF has alपढ़ोy loaded FW to chip. In
 * भवized environments a pf from another VM may have alपढ़ोy
 * initialized the device including loading FW
 */
पूर्णांक bnx2x_compare_fw_ver(काष्ठा bnx2x *bp, u32 load_code, bool prपूर्णांक_err)
अणु
	/* is another pf loaded on this engine? */
	अगर (load_code != FW_MSG_CODE_DRV_LOAD_COMMON_CHIP &&
	    load_code != FW_MSG_CODE_DRV_LOAD_COMMON) अणु
		/* build my FW version dword */
		u32 my_fw = (BCM_5710_FW_MAJOR_VERSION) +
			(BCM_5710_FW_MINOR_VERSION << 8) +
			(BCM_5710_FW_REVISION_VERSION << 16) +
			(BCM_5710_FW_ENGINEERING_VERSION << 24);

		/* पढ़ो loaded FW from chip */
		u32 loaded_fw = REG_RD(bp, XSEM_REG_PRAM);

		DP(BNX2X_MSG_SP, "loaded fw %x, my fw %x\n",
		   loaded_fw, my_fw);

		/* पात nic load अगर version mismatch */
		अगर (my_fw != loaded_fw) अणु
			अगर (prपूर्णांक_err)
				BNX2X_ERR("bnx2x with FW %x was already loaded which mismatches my %x FW. Aborting\n",
					  loaded_fw, my_fw);
			अन्यथा
				BNX2X_DEV_INFO("bnx2x with FW %x was already loaded which mismatches my %x FW, possibly due to MF UNDI\n",
					       loaded_fw, my_fw);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* वापसs the "mcp load_code" according to global load_count array */
अटल पूर्णांक bnx2x_nic_load_no_mcp(काष्ठा bnx2x *bp, पूर्णांक port)
अणु
	पूर्णांक path = BP_PATH(bp);

	DP(NETIF_MSG_IFUP, "NO MCP - load counts[%d]      %d, %d, %d\n",
	   path, bnx2x_load_count[path][0], bnx2x_load_count[path][1],
	   bnx2x_load_count[path][2]);
	bnx2x_load_count[path][0]++;
	bnx2x_load_count[path][1 + port]++;
	DP(NETIF_MSG_IFUP, "NO MCP - new load counts[%d]  %d, %d, %d\n",
	   path, bnx2x_load_count[path][0], bnx2x_load_count[path][1],
	   bnx2x_load_count[path][2]);
	अगर (bnx2x_load_count[path][0] == 1)
		वापस FW_MSG_CODE_DRV_LOAD_COMMON;
	अन्यथा अगर (bnx2x_load_count[path][1 + port] == 1)
		वापस FW_MSG_CODE_DRV_LOAD_PORT;
	अन्यथा
		वापस FW_MSG_CODE_DRV_LOAD_FUNCTION;
पूर्ण

/* mark PMF अगर applicable */
अटल व्योम bnx2x_nic_load_pmf(काष्ठा bnx2x *bp, u32 load_code)
अणु
	अगर ((load_code == FW_MSG_CODE_DRV_LOAD_COMMON) ||
	    (load_code == FW_MSG_CODE_DRV_LOAD_COMMON_CHIP) ||
	    (load_code == FW_MSG_CODE_DRV_LOAD_PORT)) अणु
		bp->port.pmf = 1;
		/* We need the barrier to ensure the ordering between the
		 * writing to bp->port.pmf here and पढ़ोing it from the
		 * bnx2x_periodic_task().
		 */
		smp_mb();
	पूर्ण अन्यथा अणु
		bp->port.pmf = 0;
	पूर्ण

	DP(NETIF_MSG_LINK, "pmf %d\n", bp->port.pmf);
पूर्ण

अटल व्योम bnx2x_nic_load_afex_dcc(काष्ठा bnx2x *bp, पूर्णांक load_code)
अणु
	अगर (((load_code == FW_MSG_CODE_DRV_LOAD_COMMON) ||
	     (load_code == FW_MSG_CODE_DRV_LOAD_COMMON_CHIP)) &&
	    (bp->common.shmem2_base)) अणु
		अगर (SHMEM2_HAS(bp, dcc_support))
			SHMEM2_WR(bp, dcc_support,
				  (SHMEM_DCC_SUPPORT_DISABLE_ENABLE_PF_TLV |
				   SHMEM_DCC_SUPPORT_BANDWIDTH_ALLOCATION_TLV));
		अगर (SHMEM2_HAS(bp, afex_driver_support))
			SHMEM2_WR(bp, afex_driver_support,
				  SHMEM_AFEX_SUPPORTED_VERSION_ONE);
	पूर्ण

	/* Set AFEX शेष VLAN tag to an invalid value */
	bp->afex_def_vlan_tag = -1;
पूर्ण

/**
 * bnx2x_bz_fp - zero content of the fastpath काष्ठाure.
 *
 * @bp:		driver handle
 * @index:	fastpath index to be zeroed
 *
 * Makes sure the contents of the bp->fp[index].napi is kept
 * पूर्णांकact.
 */
अटल व्योम bnx2x_bz_fp(काष्ठा bnx2x *bp, पूर्णांक index)
अणु
	काष्ठा bnx2x_fastpath *fp = &bp->fp[index];
	पूर्णांक cos;
	काष्ठा napi_काष्ठा orig_napi = fp->napi;
	काष्ठा bnx2x_agg_info *orig_tpa_info = fp->tpa_info;

	/* bzero bnx2x_fastpath contents */
	अगर (fp->tpa_info)
		स_रखो(fp->tpa_info, 0, ETH_MAX_AGGREGATION_QUEUES_E1H_E2 *
		       माप(काष्ठा bnx2x_agg_info));
	स_रखो(fp, 0, माप(*fp));

	/* Restore the NAPI object as it has been alपढ़ोy initialized */
	fp->napi = orig_napi;
	fp->tpa_info = orig_tpa_info;
	fp->bp = bp;
	fp->index = index;
	अगर (IS_ETH_FP(fp))
		fp->max_cos = bp->max_cos;
	अन्यथा
		/* Special queues support only one CoS */
		fp->max_cos = 1;

	/* Init txdata poपूर्णांकers */
	अगर (IS_FCOE_FP(fp))
		fp->txdata_ptr[0] = &bp->bnx2x_txq[FCOE_TXQ_IDX(bp)];
	अगर (IS_ETH_FP(fp))
		क्रम_each_cos_in_tx_queue(fp, cos)
			fp->txdata_ptr[cos] = &bp->bnx2x_txq[cos *
				BNX2X_NUM_ETH_QUEUES(bp) + index];

	/* set the tpa flag क्रम each queue. The tpa flag determines the queue
	 * minimal size so it must be set prior to queue memory allocation
	 */
	अगर (bp->dev->features & NETIF_F_LRO)
		fp->mode = TPA_MODE_LRO;
	अन्यथा अगर (bp->dev->features & NETIF_F_GRO_HW)
		fp->mode = TPA_MODE_GRO;
	अन्यथा
		fp->mode = TPA_MODE_DISABLED;

	/* We करोn't want TPA if it's disabled in bp
	 * or अगर this is an FCoE L2 ring.
	 */
	अगर (bp->disable_tpa || IS_FCOE_FP(fp))
		fp->mode = TPA_MODE_DISABLED;
पूर्ण

व्योम bnx2x_set_os_driver_state(काष्ठा bnx2x *bp, u32 state)
अणु
	u32 cur;

	अगर (!IS_MF_BD(bp) || !SHMEM2_HAS(bp, os_driver_state) || IS_VF(bp))
		वापस;

	cur = SHMEM2_RD(bp, os_driver_state[BP_FW_MB_IDX(bp)]);
	DP(NETIF_MSG_IFUP, "Driver state %08x-->%08x\n",
	   cur, state);

	SHMEM2_WR(bp, os_driver_state[BP_FW_MB_IDX(bp)], state);
पूर्ण

पूर्णांक bnx2x_load_cnic(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i, rc, port = BP_PORT(bp);

	DP(NETIF_MSG_IFUP, "Starting CNIC-related load\n");

	mutex_init(&bp->cnic_mutex);

	अगर (IS_PF(bp)) अणु
		rc = bnx2x_alloc_mem_cnic(bp);
		अगर (rc) अणु
			BNX2X_ERR("Unable to allocate bp memory for cnic\n");
			LOAD_ERROR_EXIT_CNIC(bp, load_error_cnic0);
		पूर्ण
	पूर्ण

	rc = bnx2x_alloc_fp_mem_cnic(bp);
	अगर (rc) अणु
		BNX2X_ERR("Unable to allocate memory for cnic fps\n");
		LOAD_ERROR_EXIT_CNIC(bp, load_error_cnic0);
	पूर्ण

	/* Update the number of queues with the cnic queues */
	rc = bnx2x_set_real_num_queues(bp, 1);
	अगर (rc) अणु
		BNX2X_ERR("Unable to set real_num_queues including cnic\n");
		LOAD_ERROR_EXIT_CNIC(bp, load_error_cnic0);
	पूर्ण

	/* Add all CNIC NAPI objects */
	bnx2x_add_all_napi_cnic(bp);
	DP(NETIF_MSG_IFUP, "cnic napi added\n");
	bnx2x_napi_enable_cnic(bp);

	rc = bnx2x_init_hw_func_cnic(bp);
	अगर (rc)
		LOAD_ERROR_EXIT_CNIC(bp, load_error_cnic1);

	bnx2x_nic_init_cnic(bp);

	अगर (IS_PF(bp)) अणु
		/* Enable Timer scan */
		REG_WR(bp, TM_REG_EN_LINEAR0_TIMER + port*4, 1);

		/* setup cnic queues */
		क्रम_each_cnic_queue(bp, i) अणु
			rc = bnx2x_setup_queue(bp, &bp->fp[i], 0);
			अगर (rc) अणु
				BNX2X_ERR("Queue setup failed\n");
				LOAD_ERROR_EXIT(bp, load_error_cnic2);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Initialize Rx filter. */
	bnx2x_set_rx_mode_inner(bp);

	/* re-पढ़ो iscsi info */
	bnx2x_get_iscsi_info(bp);
	bnx2x_setup_cnic_irq_info(bp);
	bnx2x_setup_cnic_info(bp);
	bp->cnic_loaded = true;
	अगर (bp->state == BNX2X_STATE_OPEN)
		bnx2x_cnic_notअगरy(bp, CNIC_CTL_START_CMD);

	DP(NETIF_MSG_IFUP, "Ending successfully CNIC-related load\n");

	वापस 0;

#अगर_अघोषित BNX2X_STOP_ON_ERROR
load_error_cnic2:
	/* Disable Timer scan */
	REG_WR(bp, TM_REG_EN_LINEAR0_TIMER + port*4, 0);

load_error_cnic1:
	bnx2x_napi_disable_cnic(bp);
	/* Update the number of queues without the cnic queues */
	अगर (bnx2x_set_real_num_queues(bp, 0))
		BNX2X_ERR("Unable to set real_num_queues not including cnic\n");
load_error_cnic0:
	BNX2X_ERR("CNIC-related load failed\n");
	bnx2x_मुक्त_fp_mem_cnic(bp);
	bnx2x_मुक्त_mem_cnic(bp);
	वापस rc;
#पूर्ण_अगर /* ! BNX2X_STOP_ON_ERROR */
पूर्ण

/* must be called with rtnl_lock */
पूर्णांक bnx2x_nic_load(काष्ठा bnx2x *bp, पूर्णांक load_mode)
अणु
	पूर्णांक port = BP_PORT(bp);
	पूर्णांक i, rc = 0, load_code = 0;

	DP(NETIF_MSG_IFUP, "Starting NIC load\n");
	DP(NETIF_MSG_IFUP,
	   "CNIC is %s\n", CNIC_ENABLED(bp) ? "enabled" : "disabled");

#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर (unlikely(bp->panic)) अणु
		BNX2X_ERR("Can't load NIC when there is panic\n");
		वापस -EPERM;
	पूर्ण
#पूर्ण_अगर

	bp->state = BNX2X_STATE_OPENING_WAIT4_LOAD;

	/* zero the काष्ठाure w/o any lock, beक्रमe SP handler is initialized */
	स_रखो(&bp->last_reported_link, 0, माप(bp->last_reported_link));
	__set_bit(BNX2X_LINK_REPORT_LINK_DOWN,
		&bp->last_reported_link.link_report_flags);

	अगर (IS_PF(bp))
		/* must be called beक्रमe memory allocation and HW init */
		bnx2x_ilt_set_info(bp);

	/*
	 * Zero fastpath काष्ठाures preserving invariants like napi, which are
	 * allocated only once, fp index, max_cos, bp poपूर्णांकer.
	 * Also set fp->mode and txdata_ptr.
	 */
	DP(NETIF_MSG_IFUP, "num queues: %d", bp->num_queues);
	क्रम_each_queue(bp, i)
		bnx2x_bz_fp(bp, i);
	स_रखो(bp->bnx2x_txq, 0, (BNX2X_MAX_RSS_COUNT(bp) * BNX2X_MULTI_TX_COS +
				  bp->num_cnic_queues) *
				  माप(काष्ठा bnx2x_fp_txdata));

	bp->fcoe_init = false;

	/* Set the receive queues buffer size */
	bnx2x_set_rx_buf_size(bp);

	अगर (IS_PF(bp)) अणु
		rc = bnx2x_alloc_mem(bp);
		अगर (rc) अणु
			BNX2X_ERR("Unable to allocate bp memory\n");
			वापस rc;
		पूर्ण
	पूर्ण

	/* need to be करोne after alloc mem, since it's self adjusting to amount
	 * of memory available क्रम RSS queues
	 */
	rc = bnx2x_alloc_fp_mem(bp);
	अगर (rc) अणु
		BNX2X_ERR("Unable to allocate memory for fps\n");
		LOAD_ERROR_EXIT(bp, load_error0);
	पूर्ण

	/* Allocated memory क्रम FW statistics  */
	अगर (bnx2x_alloc_fw_stats_mem(bp))
		LOAD_ERROR_EXIT(bp, load_error0);

	/* request pf to initialize status blocks */
	अगर (IS_VF(bp)) अणु
		rc = bnx2x_vfpf_init(bp);
		अगर (rc)
			LOAD_ERROR_EXIT(bp, load_error0);
	पूर्ण

	/* As दीर्घ as bnx2x_alloc_mem() may possibly update
	 * bp->num_queues, bnx2x_set_real_num_queues() should always
	 * come after it. At this stage cnic queues are not counted.
	 */
	rc = bnx2x_set_real_num_queues(bp, 0);
	अगर (rc) अणु
		BNX2X_ERR("Unable to set real_num_queues\n");
		LOAD_ERROR_EXIT(bp, load_error0);
	पूर्ण

	/* configure multi cos mappings in kernel.
	 * this configuration may be overridden by a multi class queue
	 * discipline or by a dcbx negotiation result.
	 */
	bnx2x_setup_tc(bp->dev, bp->max_cos);

	/* Add all NAPI objects */
	bnx2x_add_all_napi(bp);
	DP(NETIF_MSG_IFUP, "napi added\n");
	bnx2x_napi_enable(bp);

	अगर (IS_PF(bp)) अणु
		/* set pf load just beक्रमe approaching the MCP */
		bnx2x_set_pf_load(bp);

		/* अगर mcp exists send load request and analyze response */
		अगर (!BP_NOMCP(bp)) अणु
			/* attempt to load pf */
			rc = bnx2x_nic_load_request(bp, &load_code);
			अगर (rc)
				LOAD_ERROR_EXIT(bp, load_error1);

			/* what did mcp say? */
			rc = bnx2x_compare_fw_ver(bp, load_code, true);
			अगर (rc) अणु
				bnx2x_fw_command(bp, DRV_MSG_CODE_LOAD_DONE, 0);
				LOAD_ERROR_EXIT(bp, load_error2);
			पूर्ण
		पूर्ण अन्यथा अणु
			load_code = bnx2x_nic_load_no_mcp(bp, port);
		पूर्ण

		/* mark pmf अगर applicable */
		bnx2x_nic_load_pmf(bp, load_code);

		/* Init Function state controlling object */
		bnx2x__init_func_obj(bp);

		/* Initialize HW */
		rc = bnx2x_init_hw(bp, load_code);
		अगर (rc) अणु
			BNX2X_ERR("HW init failed, aborting\n");
			bnx2x_fw_command(bp, DRV_MSG_CODE_LOAD_DONE, 0);
			LOAD_ERROR_EXIT(bp, load_error2);
		पूर्ण
	पूर्ण

	bnx2x_pre_irq_nic_init(bp);

	/* Connect to IRQs */
	rc = bnx2x_setup_irqs(bp);
	अगर (rc) अणु
		BNX2X_ERR("setup irqs failed\n");
		अगर (IS_PF(bp))
			bnx2x_fw_command(bp, DRV_MSG_CODE_LOAD_DONE, 0);
		LOAD_ERROR_EXIT(bp, load_error2);
	पूर्ण

	/* Init per-function objects */
	अगर (IS_PF(bp)) अणु
		/* Setup NIC पूर्णांकernals and enable पूर्णांकerrupts */
		bnx2x_post_irq_nic_init(bp, load_code);

		bnx2x_init_bp_objs(bp);
		bnx2x_iov_nic_init(bp);

		/* Set AFEX शेष VLAN tag to an invalid value */
		bp->afex_def_vlan_tag = -1;
		bnx2x_nic_load_afex_dcc(bp, load_code);
		bp->state = BNX2X_STATE_OPENING_WAIT4_PORT;
		rc = bnx2x_func_start(bp);
		अगर (rc) अणु
			BNX2X_ERR("Function start failed!\n");
			bnx2x_fw_command(bp, DRV_MSG_CODE_LOAD_DONE, 0);

			LOAD_ERROR_EXIT(bp, load_error3);
		पूर्ण

		/* Send LOAD_DONE command to MCP */
		अगर (!BP_NOMCP(bp)) अणु
			load_code = bnx2x_fw_command(bp,
						     DRV_MSG_CODE_LOAD_DONE, 0);
			अगर (!load_code) अणु
				BNX2X_ERR("MCP response failure, aborting\n");
				rc = -EBUSY;
				LOAD_ERROR_EXIT(bp, load_error3);
			पूर्ण
		पूर्ण

		/* initialize FW coalescing state machines in RAM */
		bnx2x_update_coalesce(bp);
	पूर्ण

	/* setup the leading queue */
	rc = bnx2x_setup_leading(bp);
	अगर (rc) अणु
		BNX2X_ERR("Setup leading failed!\n");
		LOAD_ERROR_EXIT(bp, load_error3);
	पूर्ण

	/* set up the rest of the queues */
	क्रम_each_nonशेष_eth_queue(bp, i) अणु
		अगर (IS_PF(bp))
			rc = bnx2x_setup_queue(bp, &bp->fp[i], false);
		अन्यथा /* VF */
			rc = bnx2x_vfpf_setup_q(bp, &bp->fp[i], false);
		अगर (rc) अणु
			BNX2X_ERR("Queue %d setup failed\n", i);
			LOAD_ERROR_EXIT(bp, load_error3);
		पूर्ण
	पूर्ण

	/* setup rss */
	rc = bnx2x_init_rss(bp);
	अगर (rc) अणु
		BNX2X_ERR("PF RSS init failed\n");
		LOAD_ERROR_EXIT(bp, load_error3);
	पूर्ण

	/* Now when Clients are configured we are पढ़ोy to work */
	bp->state = BNX2X_STATE_OPEN;

	/* Configure a ucast MAC */
	अगर (IS_PF(bp))
		rc = bnx2x_set_eth_mac(bp, true);
	अन्यथा /* vf */
		rc = bnx2x_vfpf_config_mac(bp, bp->dev->dev_addr, bp->fp->index,
					   true);
	अगर (rc) अणु
		BNX2X_ERR("Setting Ethernet MAC failed\n");
		LOAD_ERROR_EXIT(bp, load_error3);
	पूर्ण

	अगर (IS_PF(bp) && bp->pending_max) अणु
		bnx2x_update_max_mf_config(bp, bp->pending_max);
		bp->pending_max = 0;
	पूर्ण

	bp->क्रमce_link_करोwn = false;
	अगर (bp->port.pmf) अणु
		rc = bnx2x_initial_phy_init(bp, load_mode);
		अगर (rc)
			LOAD_ERROR_EXIT(bp, load_error3);
	पूर्ण
	bp->link_params.feature_config_flags &= ~FEATURE_CONFIG_BOOT_FROM_SAN;

	/* Start fast path */

	/* Re-configure vlan filters */
	rc = bnx2x_vlan_reconfigure_vid(bp);
	अगर (rc)
		LOAD_ERROR_EXIT(bp, load_error3);

	/* Initialize Rx filter. */
	bnx2x_set_rx_mode_inner(bp);

	अगर (bp->flags & PTP_SUPPORTED) अणु
		bnx2x_रेजिस्टर_phc(bp);
		bnx2x_init_ptp(bp);
		bnx2x_configure_ptp_filters(bp);
	पूर्ण
	/* Start Tx */
	चयन (load_mode) अणु
	हाल LOAD_NORMAL:
		/* Tx queue should be only re-enabled */
		netअगर_tx_wake_all_queues(bp->dev);
		अवरोध;

	हाल LOAD_OPEN:
		netअगर_tx_start_all_queues(bp->dev);
		smp_mb__after_atomic();
		अवरोध;

	हाल LOAD_DIAG:
	हाल LOAD_LOOPBACK_EXT:
		bp->state = BNX2X_STATE_DIAG;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (bp->port.pmf)
		bnx2x_update_drv_flags(bp, 1 << DRV_FLAGS_PORT_MASK, 0);
	अन्यथा
		bnx2x__link_status_update(bp);

	/* start the समयr */
	mod_समयr(&bp->समयr, jअगरfies + bp->current_पूर्णांकerval);

	अगर (CNIC_ENABLED(bp))
		bnx2x_load_cnic(bp);

	अगर (IS_PF(bp))
		bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_GET_DRV_VERSION, 0);

	अगर (IS_PF(bp) && SHMEM2_HAS(bp, drv_capabilities_flag)) अणु
		/* mark driver is loaded in shmem2 */
		u32 val;
		val = SHMEM2_RD(bp, drv_capabilities_flag[BP_FW_MB_IDX(bp)]);
		val &= ~DRV_FLAGS_MTU_MASK;
		val |= (bp->dev->mtu << DRV_FLAGS_MTU_SHIFT);
		SHMEM2_WR(bp, drv_capabilities_flag[BP_FW_MB_IDX(bp)],
			  val | DRV_FLAGS_CAPABILITIES_LOADED_SUPPORTED |
			  DRV_FLAGS_CAPABILITIES_LOADED_L2);
	पूर्ण

	/* Wait क्रम all pending SP commands to complete */
	अगर (IS_PF(bp) && !bnx2x_रुको_sp_comp(bp, ~0x0UL)) अणु
		BNX2X_ERR("Timeout waiting for SP elements to complete\n");
		bnx2x_nic_unload(bp, UNLOAD_CLOSE, false);
		वापस -EBUSY;
	पूर्ण

	/* Update driver data क्रम On-Chip MFW dump. */
	अगर (IS_PF(bp))
		bnx2x_update_mfw_dump(bp);

	/* If PMF - send ADMIN DCBX msg to MFW to initiate DCBX FSM */
	अगर (bp->port.pmf && (bp->state != BNX2X_STATE_DIAG))
		bnx2x_dcbx_init(bp, false);

	अगर (!IS_MF_SD_STORAGE_PERSONALITY_ONLY(bp))
		bnx2x_set_os_driver_state(bp, OS_DRIVER_STATE_ACTIVE);

	DP(NETIF_MSG_IFUP, "Ending successfully NIC load\n");

	वापस 0;

#अगर_अघोषित BNX2X_STOP_ON_ERROR
load_error3:
	अगर (IS_PF(bp)) अणु
		bnx2x_पूर्णांक_disable_sync(bp, 1);

		/* Clean queueable objects */
		bnx2x_squeeze_objects(bp);
	पूर्ण

	/* Free SKBs, SGEs, TPA pool and driver पूर्णांकernals */
	bnx2x_मुक्त_skbs(bp);
	क्रम_each_rx_queue(bp, i)
		bnx2x_मुक्त_rx_sge_range(bp, bp->fp + i, NUM_RX_SGE);

	/* Release IRQs */
	bnx2x_मुक्त_irq(bp);
load_error2:
	अगर (IS_PF(bp) && !BP_NOMCP(bp)) अणु
		bnx2x_fw_command(bp, DRV_MSG_CODE_UNLOAD_REQ_WOL_MCP, 0);
		bnx2x_fw_command(bp, DRV_MSG_CODE_UNLOAD_DONE, 0);
	पूर्ण

	bp->port.pmf = 0;
load_error1:
	bnx2x_napi_disable(bp);
	bnx2x_del_all_napi(bp);

	/* clear pf_load status, as it was alपढ़ोy set */
	अगर (IS_PF(bp))
		bnx2x_clear_pf_load(bp);
load_error0:
	bnx2x_मुक्त_fw_stats_mem(bp);
	bnx2x_मुक्त_fp_mem(bp);
	bnx2x_मुक्त_mem(bp);

	वापस rc;
#पूर्ण_अगर /* ! BNX2X_STOP_ON_ERROR */
पूर्ण

पूर्णांक bnx2x_drain_tx_queues(काष्ठा bnx2x *bp)
अणु
	u8 rc = 0, cos, i;

	/* Wait until tx fastpath tasks complete */
	क्रम_each_tx_queue(bp, i) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[i];

		क्रम_each_cos_in_tx_queue(fp, cos)
			rc = bnx2x_clean_tx_queue(bp, fp->txdata_ptr[cos]);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

/* must be called with rtnl_lock */
पूर्णांक bnx2x_nic_unload(काष्ठा bnx2x *bp, पूर्णांक unload_mode, bool keep_link)
अणु
	पूर्णांक i;
	bool global = false;

	DP(NETIF_MSG_IFUP, "Starting NIC unload\n");

	अगर (!IS_MF_SD_STORAGE_PERSONALITY_ONLY(bp))
		bnx2x_set_os_driver_state(bp, OS_DRIVER_STATE_DISABLED);

	/* mark driver is unloaded in shmem2 */
	अगर (IS_PF(bp) && SHMEM2_HAS(bp, drv_capabilities_flag)) अणु
		u32 val;
		val = SHMEM2_RD(bp, drv_capabilities_flag[BP_FW_MB_IDX(bp)]);
		SHMEM2_WR(bp, drv_capabilities_flag[BP_FW_MB_IDX(bp)],
			  val & ~DRV_FLAGS_CAPABILITIES_LOADED_L2);
	पूर्ण

	अगर (IS_PF(bp) && bp->recovery_state != BNX2X_RECOVERY_DONE &&
	    (bp->state == BNX2X_STATE_CLOSED ||
	     bp->state == BNX2X_STATE_ERROR)) अणु
		/* We can get here अगर the driver has been unloaded
		 * during parity error recovery and is either रुकोing क्रम a
		 * leader to complete or क्रम other functions to unload and
		 * then अगरकरोwn has been issued. In this हाल we want to
		 * unload and let other functions to complete a recovery
		 * process.
		 */
		bp->recovery_state = BNX2X_RECOVERY_DONE;
		bp->is_leader = 0;
		bnx2x_release_leader_lock(bp);
		smp_mb();

		DP(NETIF_MSG_IFDOWN, "Releasing a leadership...\n");
		BNX2X_ERR("Can't unload in closed or error state\n");
		वापस -EINVAL;
	पूर्ण

	/* Nothing to करो during unload अगर previous bnx2x_nic_load()
	 * have not completed successfully - all resources are released.
	 *
	 * we can get here only after unsuccessful nकरो_* callback, during which
	 * dev->IFF_UP flag is still on.
	 */
	अगर (bp->state == BNX2X_STATE_CLOSED || bp->state == BNX2X_STATE_ERROR)
		वापस 0;

	/* It's important to set the bp->state to the value dअगरferent from
	 * BNX2X_STATE_OPEN and only then stop the Tx. Otherwise bnx2x_tx_पूर्णांक()
	 * may restart the Tx from the NAPI context (see bnx2x_tx_पूर्णांक()).
	 */
	bp->state = BNX2X_STATE_CLOSING_WAIT4_HALT;
	smp_mb();

	/* indicate to VFs that the PF is going करोwn */
	bnx2x_iov_channel_करोwn(bp);

	अगर (CNIC_LOADED(bp))
		bnx2x_cnic_notअगरy(bp, CNIC_CTL_STOP_CMD);

	/* Stop Tx */
	bnx2x_tx_disable(bp);
	netdev_reset_tc(bp->dev);

	bp->rx_mode = BNX2X_RX_MODE_NONE;

	del_समयr_sync(&bp->समयr);

	अगर (IS_PF(bp) && !BP_NOMCP(bp)) अणु
		/* Set ALWAYS_ALIVE bit in shmem */
		bp->fw_drv_pulse_wr_seq |= DRV_PULSE_ALWAYS_ALIVE;
		bnx2x_drv_pulse(bp);
		bnx2x_stats_handle(bp, STATS_EVENT_STOP);
		bnx2x_save_statistics(bp);
	पूर्ण

	/* रुको till consumers catch up with producers in all queues.
	 * If we're recovering, FW can't ग_लिखो to host so no reason
	 * to रुको क्रम the queues to complete all Tx.
	 */
	अगर (unload_mode != UNLOAD_RECOVERY)
		bnx2x_drain_tx_queues(bp);

	/* अगर VF indicate to PF this function is going करोwn (PF will delete sp
	 * elements and clear initializations
	 */
	अगर (IS_VF(bp)) अणु
		bnx2x_clear_vlan_info(bp);
		bnx2x_vfpf_बंद_vf(bp);
	पूर्ण अन्यथा अगर (unload_mode != UNLOAD_RECOVERY) अणु
		/* अगर this is a normal/बंद unload need to clean up chip*/
		bnx2x_chip_cleanup(bp, unload_mode, keep_link);
	पूर्ण अन्यथा अणु
		/* Send the UNLOAD_REQUEST to the MCP */
		bnx2x_send_unload_req(bp, unload_mode);

		/* Prevent transactions to host from the functions on the
		 * engine that करोesn't reset global blocks in हाल of global
		 * attention once global blocks are reset and gates are खोलोed
		 * (the engine which leader will perक्रमm the recovery
		 * last).
		 */
		अगर (!CHIP_IS_E1x(bp))
			bnx2x_pf_disable(bp);

		/* Disable HW पूर्णांकerrupts, NAPI */
		bnx2x_netअगर_stop(bp, 1);
		/* Delete all NAPI objects */
		bnx2x_del_all_napi(bp);
		अगर (CNIC_LOADED(bp))
			bnx2x_del_all_napi_cnic(bp);
		/* Release IRQs */
		bnx2x_मुक्त_irq(bp);

		/* Report UNLOAD_DONE to MCP */
		bnx2x_send_unload_करोne(bp, false);
	पूर्ण

	/*
	 * At this stage no more पूर्णांकerrupts will arrive so we may safely clean
	 * the queueable objects here in हाल they failed to get cleaned so far.
	 */
	अगर (IS_PF(bp))
		bnx2x_squeeze_objects(bp);

	/* There should be no more pending SP commands at this stage */
	bp->sp_state = 0;

	bp->port.pmf = 0;

	/* clear pending work in rtnl task */
	bp->sp_rtnl_state = 0;
	smp_mb();

	/* Free SKBs, SGEs, TPA pool and driver पूर्णांकernals */
	bnx2x_मुक्त_skbs(bp);
	अगर (CNIC_LOADED(bp))
		bnx2x_मुक्त_skbs_cnic(bp);
	क्रम_each_rx_queue(bp, i)
		bnx2x_मुक्त_rx_sge_range(bp, bp->fp + i, NUM_RX_SGE);

	bnx2x_मुक्त_fp_mem(bp);
	अगर (CNIC_LOADED(bp))
		bnx2x_मुक्त_fp_mem_cnic(bp);

	अगर (IS_PF(bp)) अणु
		अगर (CNIC_LOADED(bp))
			bnx2x_मुक्त_mem_cnic(bp);
	पूर्ण
	bnx2x_मुक्त_mem(bp);

	bp->state = BNX2X_STATE_CLOSED;
	bp->cnic_loaded = false;

	/* Clear driver version indication in shmem */
	अगर (IS_PF(bp) && !BP_NOMCP(bp))
		bnx2x_update_mng_version(bp);

	/* Check अगर there are pending parity attentions. If there are - set
	 * RECOVERY_IN_PROGRESS.
	 */
	अगर (IS_PF(bp) && bnx2x_chk_parity_attn(bp, &global, false)) अणु
		bnx2x_set_reset_in_progress(bp);

		/* Set RESET_IS_GLOBAL अगर needed */
		अगर (global)
			bnx2x_set_reset_global(bp);
	पूर्ण

	/* The last driver must disable a "close the gate" अगर there is no
	 * parity attention or "process kill" pending.
	 */
	अगर (IS_PF(bp) &&
	    !bnx2x_clear_pf_load(bp) &&
	    bnx2x_reset_is_करोne(bp, BP_PATH(bp)))
		bnx2x_disable_बंद_the_gate(bp);

	DP(NETIF_MSG_IFUP, "Ending NIC unload\n");

	वापस 0;
पूर्ण

पूर्णांक bnx2x_set_घातer_state(काष्ठा bnx2x *bp, pci_घातer_t state)
अणु
	u16 pmcsr;

	/* If there is no घातer capability, silently succeed */
	अगर (!bp->pdev->pm_cap) अणु
		BNX2X_DEV_INFO("No power capability. Breaking.\n");
		वापस 0;
	पूर्ण

	pci_पढ़ो_config_word(bp->pdev, bp->pdev->pm_cap + PCI_PM_CTRL, &pmcsr);

	चयन (state) अणु
	हाल PCI_D0:
		pci_ग_लिखो_config_word(bp->pdev, bp->pdev->pm_cap + PCI_PM_CTRL,
				      ((pmcsr & ~PCI_PM_CTRL_STATE_MASK) |
				       PCI_PM_CTRL_PME_STATUS));

		अगर (pmcsr & PCI_PM_CTRL_STATE_MASK)
			/* delay required during transition out of D3hot */
			msleep(20);
		अवरोध;

	हाल PCI_D3hot:
		/* If there are other clients above करोn't
		   shut करोwn the घातer */
		अगर (atomic_पढ़ो(&bp->pdev->enable_cnt) != 1)
			वापस 0;
		/* Don't shut करोwn the घातer क्रम emulation and FPGA */
		अगर (CHIP_REV_IS_SLOW(bp))
			वापस 0;

		pmcsr &= ~PCI_PM_CTRL_STATE_MASK;
		pmcsr |= 3;

		अगर (bp->wol)
			pmcsr |= PCI_PM_CTRL_PME_ENABLE;

		pci_ग_लिखो_config_word(bp->pdev, bp->pdev->pm_cap + PCI_PM_CTRL,
				      pmcsr);

		/* No more memory access after this poपूर्णांक until
		* device is brought back to D0.
		*/
		अवरोध;

	शेष:
		dev_err(&bp->pdev->dev, "Can't support state = %d\n", state);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * net_device service functions
 */
अटल पूर्णांक bnx2x_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा bnx2x_fastpath *fp = container_of(napi, काष्ठा bnx2x_fastpath,
						 napi);
	काष्ठा bnx2x *bp = fp->bp;
	पूर्णांक rx_work_करोne;
	u8 cos;

#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर (unlikely(bp->panic)) अणु
		napi_complete(napi);
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	क्रम_each_cos_in_tx_queue(fp, cos)
		अगर (bnx2x_tx_queue_has_work(fp->txdata_ptr[cos]))
			bnx2x_tx_पूर्णांक(bp, fp->txdata_ptr[cos]);

	rx_work_करोne = (bnx2x_has_rx_work(fp)) ? bnx2x_rx_पूर्णांक(fp, budget) : 0;

	अगर (rx_work_करोne < budget) अणु
		/* No need to update SB क्रम FCoE L2 ring as दीर्घ as
		 * it's connected to the शेष SB and the SB
		 * has been updated when NAPI was scheduled.
		 */
		अगर (IS_FCOE_FP(fp)) अणु
			napi_complete_करोne(napi, rx_work_करोne);
		पूर्ण अन्यथा अणु
			bnx2x_update_fpsb_idx(fp);
			/* bnx2x_has_rx_work() पढ़ोs the status block,
			 * thus we need to ensure that status block indices
			 * have been actually पढ़ो (bnx2x_update_fpsb_idx)
			 * prior to this check (bnx2x_has_rx_work) so that
			 * we won't ग_लिखो the "newer" value of the status block
			 * to IGU (अगर there was a DMA right after
			 * bnx2x_has_rx_work and अगर there is no rmb, the memory
			 * पढ़ोing (bnx2x_update_fpsb_idx) may be postponed
			 * to right beक्रमe bnx2x_ack_sb). In this हाल there
			 * will never be another पूर्णांकerrupt until there is
			 * another update of the status block, जबतक there
			 * is still unhandled work.
			 */
			rmb();

			अगर (!(bnx2x_has_rx_work(fp) || bnx2x_has_tx_work(fp))) अणु
				अगर (napi_complete_करोne(napi, rx_work_करोne)) अणु
					/* Re-enable पूर्णांकerrupts */
					DP(NETIF_MSG_RX_STATUS,
					   "Update index to %d\n", fp->fp_hc_idx);
					bnx2x_ack_sb(bp, fp->igu_sb_id, USTORM_ID,
						     le16_to_cpu(fp->fp_hc_idx),
						     IGU_INT_ENABLE, 1);
				पूर्ण
			पूर्ण अन्यथा अणु
				rx_work_करोne = budget;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस rx_work_करोne;
पूर्ण

/* we split the first BD पूर्णांकo headers and data BDs
 * to ease the pain of our fellow microcode engineers
 * we use one mapping क्रम both BDs
 */
अटल u16 bnx2x_tx_split(काष्ठा bnx2x *bp,
			  काष्ठा bnx2x_fp_txdata *txdata,
			  काष्ठा sw_tx_bd *tx_buf,
			  काष्ठा eth_tx_start_bd **tx_bd, u16 hlen,
			  u16 bd_prod)
अणु
	काष्ठा eth_tx_start_bd *h_tx_bd = *tx_bd;
	काष्ठा eth_tx_bd *d_tx_bd;
	dma_addr_t mapping;
	पूर्णांक old_len = le16_to_cpu(h_tx_bd->nbytes);

	/* first fix first BD */
	h_tx_bd->nbytes = cpu_to_le16(hlen);

	DP(NETIF_MSG_TX_QUEUED,	"TSO split header size is %d (%x:%x)\n",
	   h_tx_bd->nbytes, h_tx_bd->addr_hi, h_tx_bd->addr_lo);

	/* now get a new data BD
	 * (after the pbd) and fill it */
	bd_prod = TX_BD(NEXT_TX_IDX(bd_prod));
	d_tx_bd = &txdata->tx_desc_ring[bd_prod].reg_bd;

	mapping = HILO_U64(le32_to_cpu(h_tx_bd->addr_hi),
			   le32_to_cpu(h_tx_bd->addr_lo)) + hlen;

	d_tx_bd->addr_hi = cpu_to_le32(U64_HI(mapping));
	d_tx_bd->addr_lo = cpu_to_le32(U64_LO(mapping));
	d_tx_bd->nbytes = cpu_to_le16(old_len - hlen);

	/* this marks the BD as one that has no inभागidual mapping */
	tx_buf->flags |= BNX2X_TSO_SPLIT_BD;

	DP(NETIF_MSG_TX_QUEUED,
	   "TSO split data size is %d (%x:%x)\n",
	   d_tx_bd->nbytes, d_tx_bd->addr_hi, d_tx_bd->addr_lo);

	/* update tx_bd */
	*tx_bd = (काष्ठा eth_tx_start_bd *)d_tx_bd;

	वापस bd_prod;
पूर्ण

#घोषणा bswab32(b32) ((__क्रमce __le32) swab32((__क्रमce __u32) (b32)))
#घोषणा bswab16(b16) ((__क्रमce __le16) swab16((__क्रमce __u16) (b16)))
अटल __le16 bnx2x_csum_fix(अचिन्हित अक्षर *t_header, u16 csum, s8 fix)
अणु
	__sum16 tsum = (__क्रमce __sum16) csum;

	अगर (fix > 0)
		tsum = ~csum_fold(csum_sub((__क्रमce __wsum) csum,
				  csum_partial(t_header - fix, fix, 0)));

	अन्यथा अगर (fix < 0)
		tsum = ~csum_fold(csum_add((__क्रमce __wsum) csum,
				  csum_partial(t_header, -fix, 0)));

	वापस bswab16(tsum);
पूर्ण

अटल u32 bnx2x_xmit_type(काष्ठा bnx2x *bp, काष्ठा sk_buff *skb)
अणु
	u32 rc;
	__u8 prot = 0;
	__be16 protocol;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस XMIT_PLAIN;

	protocol = vlan_get_protocol(skb);
	अगर (protocol == htons(ETH_P_IPV6)) अणु
		rc = XMIT_CSUM_V6;
		prot = ipv6_hdr(skb)->nexthdr;
	पूर्ण अन्यथा अणु
		rc = XMIT_CSUM_V4;
		prot = ip_hdr(skb)->protocol;
	पूर्ण

	अगर (!CHIP_IS_E1x(bp) && skb->encapsulation) अणु
		अगर (inner_ip_hdr(skb)->version == 6) अणु
			rc |= XMIT_CSUM_ENC_V6;
			अगर (inner_ipv6_hdr(skb)->nexthdr == IPPROTO_TCP)
				rc |= XMIT_CSUM_TCP;
		पूर्ण अन्यथा अणु
			rc |= XMIT_CSUM_ENC_V4;
			अगर (inner_ip_hdr(skb)->protocol == IPPROTO_TCP)
				rc |= XMIT_CSUM_TCP;
		पूर्ण
	पूर्ण
	अगर (prot == IPPROTO_TCP)
		rc |= XMIT_CSUM_TCP;

	अगर (skb_is_gso(skb)) अणु
		अगर (skb_is_gso_v6(skb)) अणु
			rc |= (XMIT_GSO_V6 | XMIT_CSUM_TCP);
			अगर (rc & XMIT_CSUM_ENC)
				rc |= XMIT_GSO_ENC_V6;
		पूर्ण अन्यथा अणु
			rc |= (XMIT_GSO_V4 | XMIT_CSUM_TCP);
			अगर (rc & XMIT_CSUM_ENC)
				rc |= XMIT_GSO_ENC_V4;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/* VXLAN: 4 = 1 (क्रम linear data BD) + 3 (2 क्रम PBD and last BD) */
#घोषणा BNX2X_NUM_VXLAN_TSO_WIN_SUB_BDS         4

/* Regular: 3 = 1 (क्रम linear data BD) + 2 (क्रम PBD and last BD) */
#घोषणा BNX2X_NUM_TSO_WIN_SUB_BDS               3

#अगर (MAX_SKB_FRAGS >= MAX_FETCH_BD - BDS_PER_TX_PKT)
/* check अगर packet requires linearization (packet is too fragmented)
   no need to check fragmentation अगर page size > 8K (there will be no
   violation to FW restrictions) */
अटल पूर्णांक bnx2x_pkt_req_lin(काष्ठा bnx2x *bp, काष्ठा sk_buff *skb,
			     u32 xmit_type)
अणु
	पूर्णांक first_bd_sz = 0, num_tso_win_sub = BNX2X_NUM_TSO_WIN_SUB_BDS;
	पूर्णांक to_copy = 0, hlen = 0;

	अगर (xmit_type & XMIT_GSO_ENC)
		num_tso_win_sub = BNX2X_NUM_VXLAN_TSO_WIN_SUB_BDS;

	अगर (skb_shinfo(skb)->nr_frags >= (MAX_FETCH_BD - num_tso_win_sub)) अणु
		अगर (xmit_type & XMIT_GSO) अणु
			अचिन्हित लघु lso_mss = skb_shinfo(skb)->gso_size;
			पूर्णांक wnd_size = MAX_FETCH_BD - num_tso_win_sub;
			/* Number of winकरोws to check */
			पूर्णांक num_wnds = skb_shinfo(skb)->nr_frags - wnd_size;
			पूर्णांक wnd_idx = 0;
			पूर्णांक frag_idx = 0;
			u32 wnd_sum = 0;

			/* Headers length */
			अगर (xmit_type & XMIT_GSO_ENC)
				hlen = (पूर्णांक)(skb_inner_transport_header(skb) -
					     skb->data) +
					     inner_tcp_hdrlen(skb);
			अन्यथा
				hlen = (पूर्णांक)(skb_transport_header(skb) -
					     skb->data) + tcp_hdrlen(skb);

			/* Amount of data (w/o headers) on linear part of SKB*/
			first_bd_sz = skb_headlen(skb) - hlen;

			wnd_sum  = first_bd_sz;

			/* Calculate the first sum - it's special */
			क्रम (frag_idx = 0; frag_idx < wnd_size - 1; frag_idx++)
				wnd_sum +=
					skb_frag_size(&skb_shinfo(skb)->frags[frag_idx]);

			/* If there was data on linear skb data - check it */
			अगर (first_bd_sz > 0) अणु
				अगर (unlikely(wnd_sum < lso_mss)) अणु
					to_copy = 1;
					जाओ निकास_lbl;
				पूर्ण

				wnd_sum -= first_bd_sz;
			पूर्ण

			/* Others are easier: run through the frag list and
			   check all winकरोws */
			क्रम (wnd_idx = 0; wnd_idx <= num_wnds; wnd_idx++) अणु
				wnd_sum +=
			  skb_frag_size(&skb_shinfo(skb)->frags[wnd_idx + wnd_size - 1]);

				अगर (unlikely(wnd_sum < lso_mss)) अणु
					to_copy = 1;
					अवरोध;
				पूर्ण
				wnd_sum -=
					skb_frag_size(&skb_shinfo(skb)->frags[wnd_idx]);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* in non-LSO too fragmented packet should always
			   be linearized */
			to_copy = 1;
		पूर्ण
	पूर्ण

निकास_lbl:
	अगर (unlikely(to_copy))
		DP(NETIF_MSG_TX_QUEUED,
		   "Linearization IS REQUIRED for %s packet. num_frags %d  hlen %d  first_bd_sz %d\n",
		   (xmit_type & XMIT_GSO) ? "LSO" : "non-LSO",
		   skb_shinfo(skb)->nr_frags, hlen, first_bd_sz);

	वापस to_copy;
पूर्ण
#पूर्ण_अगर

/**
 * bnx2x_set_pbd_gso - update PBD in GSO हाल.
 *
 * @skb:	packet skb
 * @pbd:	parse BD
 * @xmit_type:	xmit flags
 */
अटल व्योम bnx2x_set_pbd_gso(काष्ठा sk_buff *skb,
			      काष्ठा eth_tx_parse_bd_e1x *pbd,
			      u32 xmit_type)
अणु
	pbd->lso_mss = cpu_to_le16(skb_shinfo(skb)->gso_size);
	pbd->tcp_send_seq = bswab32(tcp_hdr(skb)->seq);
	pbd->tcp_flags = pbd_tcp_flags(tcp_hdr(skb));

	अगर (xmit_type & XMIT_GSO_V4) अणु
		pbd->ip_id = bswab16(ip_hdr(skb)->id);
		pbd->tcp_pseuकरो_csum =
			bswab16(~csum_tcpudp_magic(ip_hdr(skb)->saddr,
						   ip_hdr(skb)->daddr,
						   0, IPPROTO_TCP, 0));
	पूर्ण अन्यथा अणु
		pbd->tcp_pseuकरो_csum =
			bswab16(~csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
						 &ipv6_hdr(skb)->daddr,
						 0, IPPROTO_TCP, 0));
	पूर्ण

	pbd->global_data |=
		cpu_to_le16(ETH_TX_PARSE_BD_E1X_PSEUDO_CS_WITHOUT_LEN);
पूर्ण

/**
 * bnx2x_set_pbd_csum_enc - update PBD with checksum and वापस header length
 *
 * @bp:			driver handle
 * @skb:		packet skb
 * @parsing_data:	data to be updated
 * @xmit_type:		xmit flags
 *
 * 57712/578xx related, when skb has encapsulation
 */
अटल u8 bnx2x_set_pbd_csum_enc(काष्ठा bnx2x *bp, काष्ठा sk_buff *skb,
				 u32 *parsing_data, u32 xmit_type)
अणु
	*parsing_data |=
		((((u8 *)skb_inner_transport_header(skb) - skb->data) >> 1) <<
		ETH_TX_PARSE_BD_E2_L4_HDR_START_OFFSET_W_SHIFT) &
		ETH_TX_PARSE_BD_E2_L4_HDR_START_OFFSET_W;

	अगर (xmit_type & XMIT_CSUM_TCP) अणु
		*parsing_data |= ((inner_tcp_hdrlen(skb) / 4) <<
			ETH_TX_PARSE_BD_E2_TCP_HDR_LENGTH_DW_SHIFT) &
			ETH_TX_PARSE_BD_E2_TCP_HDR_LENGTH_DW;

		वापस skb_inner_transport_header(skb) +
			inner_tcp_hdrlen(skb) - skb->data;
	पूर्ण

	/* We support checksum offload क्रम TCP and UDP only.
	 * No need to pass the UDP header length - it's a स्थिरant.
	 */
	वापस skb_inner_transport_header(skb) +
		माप(काष्ठा udphdr) - skb->data;
पूर्ण

/**
 * bnx2x_set_pbd_csum_e2 - update PBD with checksum and वापस header length
 *
 * @bp:			driver handle
 * @skb:		packet skb
 * @parsing_data:	data to be updated
 * @xmit_type:		xmit flags
 *
 * 57712/578xx related
 */
अटल u8 bnx2x_set_pbd_csum_e2(काष्ठा bnx2x *bp, काष्ठा sk_buff *skb,
				u32 *parsing_data, u32 xmit_type)
अणु
	*parsing_data |=
		((((u8 *)skb_transport_header(skb) - skb->data) >> 1) <<
		ETH_TX_PARSE_BD_E2_L4_HDR_START_OFFSET_W_SHIFT) &
		ETH_TX_PARSE_BD_E2_L4_HDR_START_OFFSET_W;

	अगर (xmit_type & XMIT_CSUM_TCP) अणु
		*parsing_data |= ((tcp_hdrlen(skb) / 4) <<
			ETH_TX_PARSE_BD_E2_TCP_HDR_LENGTH_DW_SHIFT) &
			ETH_TX_PARSE_BD_E2_TCP_HDR_LENGTH_DW;

		वापस skb_transport_header(skb) + tcp_hdrlen(skb) - skb->data;
	पूर्ण
	/* We support checksum offload क्रम TCP and UDP only.
	 * No need to pass the UDP header length - it's a स्थिरant.
	 */
	वापस skb_transport_header(skb) + माप(काष्ठा udphdr) - skb->data;
पूर्ण

/* set FW indication according to inner or outer protocols अगर tunneled */
अटल व्योम bnx2x_set_sbd_csum(काष्ठा bnx2x *bp, काष्ठा sk_buff *skb,
			       काष्ठा eth_tx_start_bd *tx_start_bd,
			       u32 xmit_type)
अणु
	tx_start_bd->bd_flags.as_bitfield |= ETH_TX_BD_FLAGS_L4_CSUM;

	अगर (xmit_type & (XMIT_CSUM_ENC_V6 | XMIT_CSUM_V6))
		tx_start_bd->bd_flags.as_bitfield |= ETH_TX_BD_FLAGS_IPV6;

	अगर (!(xmit_type & XMIT_CSUM_TCP))
		tx_start_bd->bd_flags.as_bitfield |= ETH_TX_BD_FLAGS_IS_UDP;
पूर्ण

/**
 * bnx2x_set_pbd_csum - update PBD with checksum and वापस header length
 *
 * @bp:		driver handle
 * @skb:	packet skb
 * @pbd:	parse BD to be updated
 * @xmit_type:	xmit flags
 */
अटल u8 bnx2x_set_pbd_csum(काष्ठा bnx2x *bp, काष्ठा sk_buff *skb,
			     काष्ठा eth_tx_parse_bd_e1x *pbd,
			     u32 xmit_type)
अणु
	u8 hlen = (skb_network_header(skb) - skb->data) >> 1;

	/* क्रम now NS flag is not used in Linux */
	pbd->global_data =
		cpu_to_le16(hlen |
			    ((skb->protocol == cpu_to_be16(ETH_P_8021Q)) <<
			     ETH_TX_PARSE_BD_E1X_LLC_SNAP_EN_SHIFT));

	pbd->ip_hlen_w = (skb_transport_header(skb) -
			skb_network_header(skb)) >> 1;

	hlen += pbd->ip_hlen_w;

	/* We support checksum offload क्रम TCP and UDP only */
	अगर (xmit_type & XMIT_CSUM_TCP)
		hlen += tcp_hdrlen(skb) / 2;
	अन्यथा
		hlen += माप(काष्ठा udphdr) / 2;

	pbd->total_hlen_w = cpu_to_le16(hlen);
	hlen = hlen*2;

	अगर (xmit_type & XMIT_CSUM_TCP) अणु
		pbd->tcp_pseuकरो_csum = bswab16(tcp_hdr(skb)->check);

	पूर्ण अन्यथा अणु
		s8 fix = SKB_CS_OFF(skb); /* चिन्हित! */

		DP(NETIF_MSG_TX_QUEUED,
		   "hlen %d  fix %d  csum before fix %x\n",
		   le16_to_cpu(pbd->total_hlen_w), fix, SKB_CS(skb));

		/* HW bug: fixup the CSUM */
		pbd->tcp_pseuकरो_csum =
			bnx2x_csum_fix(skb_transport_header(skb),
				       SKB_CS(skb), fix);

		DP(NETIF_MSG_TX_QUEUED, "csum after fix %x\n",
		   pbd->tcp_pseuकरो_csum);
	पूर्ण

	वापस hlen;
पूर्ण

अटल व्योम bnx2x_update_pbds_gso_enc(काष्ठा sk_buff *skb,
				      काष्ठा eth_tx_parse_bd_e2 *pbd_e2,
				      काष्ठा eth_tx_parse_2nd_bd *pbd2,
				      u16 *global_data,
				      u32 xmit_type)
अणु
	u16 hlen_w = 0;
	u8 outerip_off, outerip_len = 0;

	/* from outer IP to transport */
	hlen_w = (skb_inner_transport_header(skb) -
		  skb_network_header(skb)) >> 1;

	/* transport len */
	hlen_w += inner_tcp_hdrlen(skb) >> 1;

	pbd2->fw_ip_hdr_to_payload_w = hlen_w;

	/* outer IP header info */
	अगर (xmit_type & XMIT_CSUM_V4) अणु
		काष्ठा iphdr *iph = ip_hdr(skb);
		u32 csum = (__क्रमce u32)(~iph->check) -
			   (__क्रमce u32)iph->tot_len -
			   (__क्रमce u32)iph->frag_off;

		outerip_len = iph->ihl << 1;

		pbd2->fw_ip_csum_wo_len_flags_frag =
			bswab16(csum_fold((__क्रमce __wsum)csum));
	पूर्ण अन्यथा अणु
		pbd2->fw_ip_hdr_to_payload_w =
			hlen_w - ((माप(काष्ठा ipv6hdr)) >> 1);
		pbd_e2->data.tunnel_data.flags |=
			ETH_TUNNEL_DATA_IPV6_OUTER;
	पूर्ण

	pbd2->tcp_send_seq = bswab32(inner_tcp_hdr(skb)->seq);

	pbd2->tcp_flags = pbd_tcp_flags(inner_tcp_hdr(skb));

	/* inner IP header info */
	अगर (xmit_type & XMIT_CSUM_ENC_V4) अणु
		pbd2->hw_ip_id = bswab16(inner_ip_hdr(skb)->id);

		pbd_e2->data.tunnel_data.pseuकरो_csum =
			bswab16(~csum_tcpudp_magic(
					inner_ip_hdr(skb)->saddr,
					inner_ip_hdr(skb)->daddr,
					0, IPPROTO_TCP, 0));
	पूर्ण अन्यथा अणु
		pbd_e2->data.tunnel_data.pseuकरो_csum =
			bswab16(~csum_ipv6_magic(
					&inner_ipv6_hdr(skb)->saddr,
					&inner_ipv6_hdr(skb)->daddr,
					0, IPPROTO_TCP, 0));
	पूर्ण

	outerip_off = (skb_network_header(skb) - skb->data) >> 1;

	*global_data |=
		outerip_off |
		(outerip_len <<
			ETH_TX_PARSE_2ND_BD_IP_HDR_LEN_OUTER_W_SHIFT) |
		((skb->protocol == cpu_to_be16(ETH_P_8021Q)) <<
			ETH_TX_PARSE_2ND_BD_LLC_SNAP_EN_SHIFT);

	अगर (ip_hdr(skb)->protocol == IPPROTO_UDP) अणु
		SET_FLAG(*global_data, ETH_TX_PARSE_2ND_BD_TUNNEL_UDP_EXIST, 1);
		pbd2->tunnel_udp_hdr_start_w = skb_transport_offset(skb) >> 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम bnx2x_set_ipv6_ext_e2(काष्ठा sk_buff *skb, u32 *parsing_data,
					 u32 xmit_type)
अणु
	काष्ठा ipv6hdr *ipv6;

	अगर (!(xmit_type & (XMIT_GSO_ENC_V6 | XMIT_GSO_V6)))
		वापस;

	अगर (xmit_type & XMIT_GSO_ENC_V6)
		ipv6 = inner_ipv6_hdr(skb);
	अन्यथा /* XMIT_GSO_V6 */
		ipv6 = ipv6_hdr(skb);

	अगर (ipv6->nexthdr == NEXTHDR_IPV6)
		*parsing_data |= ETH_TX_PARSE_BD_E2_IPV6_WITH_EXT_HDR;
पूर्ण

/* called with netअगर_tx_lock
 * bnx2x_tx_पूर्णांक() runs without netअगर_tx_lock unless it needs to call
 * netअगर_wake_queue()
 */
netdev_tx_t bnx2x_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	काष्ठा netdev_queue *txq;
	काष्ठा bnx2x_fp_txdata *txdata;
	काष्ठा sw_tx_bd *tx_buf;
	काष्ठा eth_tx_start_bd *tx_start_bd, *first_bd;
	काष्ठा eth_tx_bd *tx_data_bd, *total_pkt_bd = शून्य;
	काष्ठा eth_tx_parse_bd_e1x *pbd_e1x = शून्य;
	काष्ठा eth_tx_parse_bd_e2 *pbd_e2 = शून्य;
	काष्ठा eth_tx_parse_2nd_bd *pbd2 = शून्य;
	u32 pbd_e2_parsing_data = 0;
	u16 pkt_prod, bd_prod;
	पूर्णांक nbd, txq_index;
	dma_addr_t mapping;
	u32 xmit_type = bnx2x_xmit_type(bp, skb);
	पूर्णांक i;
	u8 hlen = 0;
	__le16 pkt_size = 0;
	काष्ठा ethhdr *eth;
	u8 mac_type = UNICAST_ADDRESS;

#अगर_घोषित BNX2X_STOP_ON_ERROR
	अगर (unlikely(bp->panic))
		वापस NETDEV_TX_BUSY;
#पूर्ण_अगर

	txq_index = skb_get_queue_mapping(skb);
	txq = netdev_get_tx_queue(dev, txq_index);

	BUG_ON(txq_index >= MAX_ETH_TXQ_IDX(bp) + (CNIC_LOADED(bp) ? 1 : 0));

	txdata = &bp->bnx2x_txq[txq_index];

	/* enable this debug prपूर्णांक to view the transmission queue being used
	DP(NETIF_MSG_TX_QUEUED, "indices: txq %d, fp %d, txdata %d\n",
	   txq_index, fp_index, txdata_index); */

	/* enable this debug prपूर्णांक to view the transmission details
	DP(NETIF_MSG_TX_QUEUED,
	   "transmitting packet cid %d fp index %d txdata_index %d tx_data ptr %p fp pointer %p\n",
	   txdata->cid, fp_index, txdata_index, txdata, fp); */

	अगर (unlikely(bnx2x_tx_avail(bp, txdata) <
			skb_shinfo(skb)->nr_frags +
			BDS_PER_TX_PKT +
			NEXT_CNT_PER_TX_PKT(MAX_BDS_PER_TX_PKT))) अणु
		/* Handle special storage हालs separately */
		अगर (txdata->tx_ring_size == 0) अणु
			काष्ठा bnx2x_eth_q_stats *q_stats =
				bnx2x_fp_qstats(bp, txdata->parent_fp);
			q_stats->driver_filtered_tx_pkt++;
			dev_kमुक्त_skb(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
		bnx2x_fp_qstats(bp, txdata->parent_fp)->driver_xoff++;
		netअगर_tx_stop_queue(txq);
		BNX2X_ERR("BUG! Tx ring full when queue awake!\n");

		वापस NETDEV_TX_BUSY;
	पूर्ण

	DP(NETIF_MSG_TX_QUEUED,
	   "queue[%d]: SKB: summed %x  protocol %x protocol(%x,%x) gso type %x  xmit_type %x len %d\n",
	   txq_index, skb->ip_summed, skb->protocol, ipv6_hdr(skb)->nexthdr,
	   ip_hdr(skb)->protocol, skb_shinfo(skb)->gso_type, xmit_type,
	   skb->len);

	eth = (काष्ठा ethhdr *)skb->data;

	/* set flag according to packet type (UNICAST_ADDRESS is शेष)*/
	अगर (unlikely(is_multicast_ether_addr(eth->h_dest))) अणु
		अगर (is_broadcast_ether_addr(eth->h_dest))
			mac_type = BROADCAST_ADDRESS;
		अन्यथा
			mac_type = MULTICAST_ADDRESS;
	पूर्ण

#अगर (MAX_SKB_FRAGS >= MAX_FETCH_BD - BDS_PER_TX_PKT)
	/* First, check अगर we need to linearize the skb (due to FW
	   restrictions). No need to check fragmentation अगर page size > 8K
	   (there will be no violation to FW restrictions) */
	अगर (bnx2x_pkt_req_lin(bp, skb, xmit_type)) अणु
		/* Statistics of linearization */
		bp->lin_cnt++;
		अगर (skb_linearize(skb) != 0) अणु
			DP(NETIF_MSG_TX_QUEUED,
			   "SKB linearization failed - silently dropping this SKB\n");
			dev_kमुक्त_skb_any(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	/* Map skb linear data क्रम DMA */
	mapping = dma_map_single(&bp->pdev->dev, skb->data,
				 skb_headlen(skb), DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(&bp->pdev->dev, mapping))) अणु
		DP(NETIF_MSG_TX_QUEUED,
		   "SKB mapping failed - silently dropping this SKB\n");
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	/*
	Please पढ़ो carefully. First we use one BD which we mark as start,
	then we have a parsing info BD (used क्रम TSO or xsum),
	and only then we have the rest of the TSO BDs.
	(करोn't क्रमget to mark the last one as last,
	and to unmap only AFTER you ग_लिखो to the BD ...)
	And above all, all pdb sizes are in words - NOT DWORDS!
	*/

	/* get current pkt produced now - advance it just beक्रमe sending packet
	 * since mapping of pages may fail and cause packet to be dropped
	 */
	pkt_prod = txdata->tx_pkt_prod;
	bd_prod = TX_BD(txdata->tx_bd_prod);

	/* get a tx_buf and first BD
	 * tx_start_bd may be changed during SPLIT,
	 * but first_bd will always stay first
	 */
	tx_buf = &txdata->tx_buf_ring[TX_BD(pkt_prod)];
	tx_start_bd = &txdata->tx_desc_ring[bd_prod].start_bd;
	first_bd = tx_start_bd;

	tx_start_bd->bd_flags.as_bitfield = ETH_TX_BD_FLAGS_START_BD;

	अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)) अणु
		अगर (!(bp->flags & TX_TIMESTAMPING_EN)) अणु
			bp->eth_stats.ptp_skip_tx_ts++;
			BNX2X_ERR("Tx timestamping was not enabled, this packet will not be timestamped\n");
		पूर्ण अन्यथा अगर (bp->ptp_tx_skb) अणु
			bp->eth_stats.ptp_skip_tx_ts++;
			netdev_err_once(bp->dev,
					"Device supports only a single outstanding packet to timestamp, this packet won't be timestamped\n");
		पूर्ण अन्यथा अणु
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
			/* schedule check क्रम Tx बारtamp */
			bp->ptp_tx_skb = skb_get(skb);
			bp->ptp_tx_start = jअगरfies;
			schedule_work(&bp->ptp_task);
		पूर्ण
	पूर्ण

	/* header nbd: indirectly zero other flags! */
	tx_start_bd->general_data = 1 << ETH_TX_START_BD_HDR_NBDS_SHIFT;

	/* remember the first BD of the packet */
	tx_buf->first_bd = txdata->tx_bd_prod;
	tx_buf->skb = skb;
	tx_buf->flags = 0;

	DP(NETIF_MSG_TX_QUEUED,
	   "sending pkt %u @%p  next_idx %u  bd %u @%p\n",
	   pkt_prod, tx_buf, txdata->tx_pkt_prod, bd_prod, tx_start_bd);

	अगर (skb_vlan_tag_present(skb)) अणु
		tx_start_bd->vlan_or_ethertype =
		    cpu_to_le16(skb_vlan_tag_get(skb));
		tx_start_bd->bd_flags.as_bitfield |=
		    (X_ETH_OUTBAND_VLAN << ETH_TX_BD_FLAGS_VLAN_MODE_SHIFT);
	पूर्ण अन्यथा अणु
		/* when transmitting in a vf, start bd must hold the ethertype
		 * क्रम fw to enक्रमce it
		 */
		u16 vlan_tci = 0;
#अगर_अघोषित BNX2X_STOP_ON_ERROR
		अगर (IS_VF(bp)) अणु
#पूर्ण_अगर
			/* Still need to consider inband vlan क्रम enक्रमced */
			अगर (__vlan_get_tag(skb, &vlan_tci)) अणु
				tx_start_bd->vlan_or_ethertype =
					cpu_to_le16(ntohs(eth->h_proto));
			पूर्ण अन्यथा अणु
				tx_start_bd->bd_flags.as_bitfield |=
					(X_ETH_INBAND_VLAN <<
					 ETH_TX_BD_FLAGS_VLAN_MODE_SHIFT);
				tx_start_bd->vlan_or_ethertype =
					cpu_to_le16(vlan_tci);
			पूर्ण
#अगर_अघोषित BNX2X_STOP_ON_ERROR
		पूर्ण अन्यथा अणु
			/* used by FW क्रम packet accounting */
			tx_start_bd->vlan_or_ethertype = cpu_to_le16(pkt_prod);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	nbd = 2; /* start_bd + pbd + frags (updated when pages are mapped) */

	/* turn on parsing and get a BD */
	bd_prod = TX_BD(NEXT_TX_IDX(bd_prod));

	अगर (xmit_type & XMIT_CSUM)
		bnx2x_set_sbd_csum(bp, skb, tx_start_bd, xmit_type);

	अगर (!CHIP_IS_E1x(bp)) अणु
		pbd_e2 = &txdata->tx_desc_ring[bd_prod].parse_bd_e2;
		स_रखो(pbd_e2, 0, माप(काष्ठा eth_tx_parse_bd_e2));

		अगर (xmit_type & XMIT_CSUM_ENC) अणु
			u16 global_data = 0;

			/* Set PBD in enc checksum offload हाल */
			hlen = bnx2x_set_pbd_csum_enc(bp, skb,
						      &pbd_e2_parsing_data,
						      xmit_type);

			/* turn on 2nd parsing and get a BD */
			bd_prod = TX_BD(NEXT_TX_IDX(bd_prod));

			pbd2 = &txdata->tx_desc_ring[bd_prod].parse_2nd_bd;

			स_रखो(pbd2, 0, माप(*pbd2));

			pbd_e2->data.tunnel_data.ip_hdr_start_inner_w =
				(skb_inner_network_header(skb) -
				 skb->data) >> 1;

			अगर (xmit_type & XMIT_GSO_ENC)
				bnx2x_update_pbds_gso_enc(skb, pbd_e2, pbd2,
							  &global_data,
							  xmit_type);

			pbd2->global_data = cpu_to_le16(global_data);

			/* add addition parse BD indication to start BD */
			SET_FLAG(tx_start_bd->general_data,
				 ETH_TX_START_BD_PARSE_NBDS, 1);
			/* set encapsulation flag in start BD */
			SET_FLAG(tx_start_bd->general_data,
				 ETH_TX_START_BD_TUNNEL_EXIST, 1);

			tx_buf->flags |= BNX2X_HAS_SECOND_PBD;

			nbd++;
		पूर्ण अन्यथा अगर (xmit_type & XMIT_CSUM) अणु
			/* Set PBD in checksum offload हाल w/o encapsulation */
			hlen = bnx2x_set_pbd_csum_e2(bp, skb,
						     &pbd_e2_parsing_data,
						     xmit_type);
		पूर्ण

		bnx2x_set_ipv6_ext_e2(skb, &pbd_e2_parsing_data, xmit_type);
		/* Add the macs to the parsing BD अगर this is a vf or अगर
		 * Tx Switching is enabled.
		 */
		अगर (IS_VF(bp)) अणु
			/* override GRE parameters in BD */
			bnx2x_set_fw_mac_addr(&pbd_e2->data.mac_addr.src_hi,
					      &pbd_e2->data.mac_addr.src_mid,
					      &pbd_e2->data.mac_addr.src_lo,
					      eth->h_source);

			bnx2x_set_fw_mac_addr(&pbd_e2->data.mac_addr.dst_hi,
					      &pbd_e2->data.mac_addr.dst_mid,
					      &pbd_e2->data.mac_addr.dst_lo,
					      eth->h_dest);
		पूर्ण अन्यथा अणु
			अगर (bp->flags & TX_SWITCHING)
				bnx2x_set_fw_mac_addr(
						&pbd_e2->data.mac_addr.dst_hi,
						&pbd_e2->data.mac_addr.dst_mid,
						&pbd_e2->data.mac_addr.dst_lo,
						eth->h_dest);
#अगर_घोषित BNX2X_STOP_ON_ERROR
			/* Enक्रमce security is always set in Stop on Error -
			 * source mac should be present in the parsing BD
			 */
			bnx2x_set_fw_mac_addr(&pbd_e2->data.mac_addr.src_hi,
					      &pbd_e2->data.mac_addr.src_mid,
					      &pbd_e2->data.mac_addr.src_lo,
					      eth->h_source);
#पूर्ण_अगर
		पूर्ण

		SET_FLAG(pbd_e2_parsing_data,
			 ETH_TX_PARSE_BD_E2_ETH_ADDR_TYPE, mac_type);
	पूर्ण अन्यथा अणु
		u16 global_data = 0;
		pbd_e1x = &txdata->tx_desc_ring[bd_prod].parse_bd_e1x;
		स_रखो(pbd_e1x, 0, माप(काष्ठा eth_tx_parse_bd_e1x));
		/* Set PBD in checksum offload हाल */
		अगर (xmit_type & XMIT_CSUM)
			hlen = bnx2x_set_pbd_csum(bp, skb, pbd_e1x, xmit_type);

		SET_FLAG(global_data,
			 ETH_TX_PARSE_BD_E1X_ETH_ADDR_TYPE, mac_type);
		pbd_e1x->global_data |= cpu_to_le16(global_data);
	पूर्ण

	/* Setup the data poपूर्णांकer of the first BD of the packet */
	tx_start_bd->addr_hi = cpu_to_le32(U64_HI(mapping));
	tx_start_bd->addr_lo = cpu_to_le32(U64_LO(mapping));
	tx_start_bd->nbytes = cpu_to_le16(skb_headlen(skb));
	pkt_size = tx_start_bd->nbytes;

	DP(NETIF_MSG_TX_QUEUED,
	   "first bd @%p  addr (%x:%x)  nbytes %d  flags %x  vlan %x\n",
	   tx_start_bd, tx_start_bd->addr_hi, tx_start_bd->addr_lo,
	   le16_to_cpu(tx_start_bd->nbytes),
	   tx_start_bd->bd_flags.as_bitfield,
	   le16_to_cpu(tx_start_bd->vlan_or_ethertype));

	अगर (xmit_type & XMIT_GSO) अणु

		DP(NETIF_MSG_TX_QUEUED,
		   "TSO packet len %d  hlen %d  total len %d  tso size %d\n",
		   skb->len, hlen, skb_headlen(skb),
		   skb_shinfo(skb)->gso_size);

		tx_start_bd->bd_flags.as_bitfield |= ETH_TX_BD_FLAGS_SW_LSO;

		अगर (unlikely(skb_headlen(skb) > hlen)) अणु
			nbd++;
			bd_prod = bnx2x_tx_split(bp, txdata, tx_buf,
						 &tx_start_bd, hlen,
						 bd_prod);
		पूर्ण
		अगर (!CHIP_IS_E1x(bp))
			pbd_e2_parsing_data |=
				(skb_shinfo(skb)->gso_size <<
				 ETH_TX_PARSE_BD_E2_LSO_MSS_SHIFT) &
				 ETH_TX_PARSE_BD_E2_LSO_MSS;
		अन्यथा
			bnx2x_set_pbd_gso(skb, pbd_e1x, xmit_type);
	पूर्ण

	/* Set the PBD's parsing_data field अगर not zero
	 * (क्रम the chips newer than 57711).
	 */
	अगर (pbd_e2_parsing_data)
		pbd_e2->parsing_data = cpu_to_le32(pbd_e2_parsing_data);

	tx_data_bd = (काष्ठा eth_tx_bd *)tx_start_bd;

	/* Handle fragmented skb */
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		mapping = skb_frag_dma_map(&bp->pdev->dev, frag, 0,
					   skb_frag_size(frag), DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(&bp->pdev->dev, mapping))) अणु
			अचिन्हित पूर्णांक pkts_compl = 0, bytes_compl = 0;

			DP(NETIF_MSG_TX_QUEUED,
			   "Unable to map page - dropping packet...\n");

			/* we need unmap all buffers alपढ़ोy mapped
			 * क्रम this SKB;
			 * first_bd->nbd need to be properly updated
			 * beक्रमe call to bnx2x_मुक्त_tx_pkt
			 */
			first_bd->nbd = cpu_to_le16(nbd);
			bnx2x_मुक्त_tx_pkt(bp, txdata,
					  TX_BD(txdata->tx_pkt_prod),
					  &pkts_compl, &bytes_compl);
			वापस NETDEV_TX_OK;
		पूर्ण

		bd_prod = TX_BD(NEXT_TX_IDX(bd_prod));
		tx_data_bd = &txdata->tx_desc_ring[bd_prod].reg_bd;
		अगर (total_pkt_bd == शून्य)
			total_pkt_bd = &txdata->tx_desc_ring[bd_prod].reg_bd;

		tx_data_bd->addr_hi = cpu_to_le32(U64_HI(mapping));
		tx_data_bd->addr_lo = cpu_to_le32(U64_LO(mapping));
		tx_data_bd->nbytes = cpu_to_le16(skb_frag_size(frag));
		le16_add_cpu(&pkt_size, skb_frag_size(frag));
		nbd++;

		DP(NETIF_MSG_TX_QUEUED,
		   "frag %d  bd @%p  addr (%x:%x)  nbytes %d\n",
		   i, tx_data_bd, tx_data_bd->addr_hi, tx_data_bd->addr_lo,
		   le16_to_cpu(tx_data_bd->nbytes));
	पूर्ण

	DP(NETIF_MSG_TX_QUEUED, "last bd @%p\n", tx_data_bd);

	/* update with actual num BDs */
	first_bd->nbd = cpu_to_le16(nbd);

	bd_prod = TX_BD(NEXT_TX_IDX(bd_prod));

	/* now send a tx करोorbell, counting the next BD
	 * अगर the packet contains or ends with it
	 */
	अगर (TX_BD_POFF(bd_prod) < nbd)
		nbd++;

	/* total_pkt_bytes should be set on the first data BD अगर
	 * it's not an LSO packet and there is more than one
	 * data BD. In this हाल pkt_size is limited by an MTU value.
	 * However we prefer to set it क्रम an LSO packet (जबतक we करोn't
	 * have to) in order to save some CPU cycles in a none-LSO
	 * हाल, when we much more care about them.
	 */
	अगर (total_pkt_bd != शून्य)
		total_pkt_bd->total_pkt_bytes = pkt_size;

	अगर (pbd_e1x)
		DP(NETIF_MSG_TX_QUEUED,
		   "PBD (E1X) @%p  ip_data %x  ip_hlen %u  ip_id %u  lso_mss %u  tcp_flags %x  xsum %x  seq %u  hlen %u\n",
		   pbd_e1x, pbd_e1x->global_data, pbd_e1x->ip_hlen_w,
		   pbd_e1x->ip_id, pbd_e1x->lso_mss, pbd_e1x->tcp_flags,
		   pbd_e1x->tcp_pseuकरो_csum, pbd_e1x->tcp_send_seq,
		    le16_to_cpu(pbd_e1x->total_hlen_w));
	अगर (pbd_e2)
		DP(NETIF_MSG_TX_QUEUED,
		   "PBD (E2) @%p  dst %x %x %x src %x %x %x parsing_data %x\n",
		   pbd_e2,
		   pbd_e2->data.mac_addr.dst_hi,
		   pbd_e2->data.mac_addr.dst_mid,
		   pbd_e2->data.mac_addr.dst_lo,
		   pbd_e2->data.mac_addr.src_hi,
		   pbd_e2->data.mac_addr.src_mid,
		   pbd_e2->data.mac_addr.src_lo,
		   pbd_e2->parsing_data);
	DP(NETIF_MSG_TX_QUEUED, "doorbell: nbd %d  bd %u\n", nbd, bd_prod);

	netdev_tx_sent_queue(txq, skb->len);

	skb_tx_बारtamp(skb);

	txdata->tx_pkt_prod++;
	/*
	 * Make sure that the BD data is updated beक्रमe updating the producer
	 * since FW might पढ़ो the BD right after the producer is updated.
	 * This is only applicable क्रम weak-ordered memory model archs such
	 * as IA-64. The following barrier is also mandatory since FW will
	 * assumes packets must have BDs.
	 */
	wmb();

	txdata->tx_db.data.prod += nbd;
	/* make sure descriptor update is observed by HW */
	wmb();

	DOORBELL_RELAXED(bp, txdata->cid, txdata->tx_db.raw);

	txdata->tx_bd_prod += nbd;

	अगर (unlikely(bnx2x_tx_avail(bp, txdata) < MAX_DESC_PER_TX_PKT)) अणु
		netअगर_tx_stop_queue(txq);

		/* paired memory barrier is in bnx2x_tx_पूर्णांक(), we have to keep
		 * ordering of set_bit() in netअगर_tx_stop_queue() and पढ़ो of
		 * fp->bd_tx_cons */
		smp_mb();

		bnx2x_fp_qstats(bp, txdata->parent_fp)->driver_xoff++;
		अगर (bnx2x_tx_avail(bp, txdata) >= MAX_DESC_PER_TX_PKT)
			netअगर_tx_wake_queue(txq);
	पूर्ण
	txdata->tx_pkt++;

	वापस NETDEV_TX_OK;
पूर्ण

व्योम bnx2x_get_c2s_mapping(काष्ठा bnx2x *bp, u8 *c2s_map, u8 *c2s_शेष)
अणु
	पूर्णांक mfw_vn = BP_FW_MB_IDX(bp);
	u32 पंचांगp;

	/* If the shmem shouldn't affect configuration, reflect */
	अगर (!IS_MF_BD(bp)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < BNX2X_MAX_PRIORITY; i++)
			c2s_map[i] = i;
		*c2s_शेष = 0;

		वापस;
	पूर्ण

	पंचांगp = SHMEM2_RD(bp, c2s_pcp_map_lower[mfw_vn]);
	पंचांगp = (__क्रमce u32)be32_to_cpu((__क्रमce __be32)पंचांगp);
	c2s_map[0] = पंचांगp & 0xff;
	c2s_map[1] = (पंचांगp >> 8) & 0xff;
	c2s_map[2] = (पंचांगp >> 16) & 0xff;
	c2s_map[3] = (पंचांगp >> 24) & 0xff;

	पंचांगp = SHMEM2_RD(bp, c2s_pcp_map_upper[mfw_vn]);
	पंचांगp = (__क्रमce u32)be32_to_cpu((__क्रमce __be32)पंचांगp);
	c2s_map[4] = पंचांगp & 0xff;
	c2s_map[5] = (पंचांगp >> 8) & 0xff;
	c2s_map[6] = (पंचांगp >> 16) & 0xff;
	c2s_map[7] = (पंचांगp >> 24) & 0xff;

	पंचांगp = SHMEM2_RD(bp, c2s_pcp_map_शेष[mfw_vn]);
	पंचांगp = (__क्रमce u32)be32_to_cpu((__क्रमce __be32)पंचांगp);
	*c2s_शेष = (पंचांगp >> (8 * mfw_vn)) & 0xff;
पूर्ण

/**
 * bnx2x_setup_tc - routine to configure net_device क्रम multi tc
 *
 * @dev: net device to configure
 * @num_tc: number of traffic classes to enable
 *
 * callback connected to the nकरो_setup_tc function poपूर्णांकer
 */
पूर्णांक bnx2x_setup_tc(काष्ठा net_device *dev, u8 num_tc)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	u8 c2s_map[BNX2X_MAX_PRIORITY], c2s_def;
	पूर्णांक cos, prio, count, offset;

	/* setup tc must be called under rtnl lock */
	ASSERT_RTNL();

	/* no traffic classes requested. Aborting */
	अगर (!num_tc) अणु
		netdev_reset_tc(dev);
		वापस 0;
	पूर्ण

	/* requested to support too many traffic classes */
	अगर (num_tc > bp->max_cos) अणु
		BNX2X_ERR("support for too many traffic classes requested: %d. Max supported is %d\n",
			  num_tc, bp->max_cos);
		वापस -EINVAL;
	पूर्ण

	/* declare amount of supported traffic classes */
	अगर (netdev_set_num_tc(dev, num_tc)) अणु
		BNX2X_ERR("failed to declare %d traffic classes\n", num_tc);
		वापस -EINVAL;
	पूर्ण

	bnx2x_get_c2s_mapping(bp, c2s_map, &c2s_def);

	/* configure priority to traffic class mapping */
	क्रम (prio = 0; prio < BNX2X_MAX_PRIORITY; prio++) अणु
		पूर्णांक outer_prio = c2s_map[prio];

		netdev_set_prio_tc_map(dev, prio, bp->prio_to_cos[outer_prio]);
		DP(BNX2X_MSG_SP | NETIF_MSG_IFUP,
		   "mapping priority %d to tc %d\n",
		   outer_prio, bp->prio_to_cos[outer_prio]);
	पूर्ण

	/* Use this configuration to dअगरferentiate tc0 from other COSes
	   This can be used क्रम ets or pfc, and save the efक्रमt of setting
	   up a multio class queue disc or negotiating DCBX with a चयन
	netdev_set_prio_tc_map(dev, 0, 0);
	DP(BNX2X_MSG_SP, "mapping priority %d to tc %d\n", 0, 0);
	क्रम (prio = 1; prio < 16; prio++) अणु
		netdev_set_prio_tc_map(dev, prio, 1);
		DP(BNX2X_MSG_SP, "mapping priority %d to tc %d\n", prio, 1);
	पूर्ण */

	/* configure traffic class to transmission queue mapping */
	क्रम (cos = 0; cos < bp->max_cos; cos++) अणु
		count = BNX2X_NUM_ETH_QUEUES(bp);
		offset = cos * BNX2X_NUM_NON_CNIC_QUEUES(bp);
		netdev_set_tc_queue(dev, cos, count, offset);
		DP(BNX2X_MSG_SP | NETIF_MSG_IFUP,
		   "mapping tc %d to offset %d count %d\n",
		   cos, offset, count);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __bnx2x_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
		     व्योम *type_data)
अणु
	काष्ठा tc_mqprio_qopt *mqprio = type_data;

	अगर (type != TC_SETUP_QDISC_MQPRIO)
		वापस -EOPNOTSUPP;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;

	वापस bnx2x_setup_tc(dev, mqprio->num_tc);
पूर्ण

/* called with rtnl_lock */
पूर्णांक bnx2x_change_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक rc = 0;

	अगर (!is_valid_ether_addr(addr->sa_data)) अणु
		BNX2X_ERR("Requested MAC address is not valid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (IS_MF_STORAGE_ONLY(bp)) अणु
		BNX2X_ERR("Can't change address on STORAGE ONLY function\n");
		वापस -EINVAL;
	पूर्ण

	अगर (netअगर_running(dev))  अणु
		rc = bnx2x_set_eth_mac(bp, false);
		अगर (rc)
			वापस rc;
	पूर्ण

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	अगर (netअगर_running(dev))
		rc = bnx2x_set_eth_mac(bp, true);

	अगर (IS_PF(bp) && SHMEM2_HAS(bp, curr_cfg))
		SHMEM2_WR(bp, curr_cfg, CURR_CFG_MET_OS);

	वापस rc;
पूर्ण

अटल व्योम bnx2x_मुक्त_fp_mem_at(काष्ठा bnx2x *bp, पूर्णांक fp_index)
अणु
	जोड़ host_hc_status_block *sb = &bnx2x_fp(bp, fp_index, status_blk);
	काष्ठा bnx2x_fastpath *fp = &bp->fp[fp_index];
	u8 cos;

	/* Common */

	अगर (IS_FCOE_IDX(fp_index)) अणु
		स_रखो(sb, 0, माप(जोड़ host_hc_status_block));
		fp->status_blk_mapping = 0;
	पूर्ण अन्यथा अणु
		/* status blocks */
		अगर (!CHIP_IS_E1x(bp))
			BNX2X_PCI_FREE(sb->e2_sb,
				       bnx2x_fp(bp, fp_index,
						status_blk_mapping),
				       माप(काष्ठा host_hc_status_block_e2));
		अन्यथा
			BNX2X_PCI_FREE(sb->e1x_sb,
				       bnx2x_fp(bp, fp_index,
						status_blk_mapping),
				       माप(काष्ठा host_hc_status_block_e1x));
	पूर्ण

	/* Rx */
	अगर (!skip_rx_queue(bp, fp_index)) अणु
		bnx2x_मुक्त_rx_bds(fp);

		/* fastpath rx rings: rx_buf rx_desc rx_comp */
		BNX2X_FREE(bnx2x_fp(bp, fp_index, rx_buf_ring));
		BNX2X_PCI_FREE(bnx2x_fp(bp, fp_index, rx_desc_ring),
			       bnx2x_fp(bp, fp_index, rx_desc_mapping),
			       माप(काष्ठा eth_rx_bd) * NUM_RX_BD);

		BNX2X_PCI_FREE(bnx2x_fp(bp, fp_index, rx_comp_ring),
			       bnx2x_fp(bp, fp_index, rx_comp_mapping),
			       माप(काष्ठा eth_fast_path_rx_cqe) *
			       NUM_RCQ_BD);

		/* SGE ring */
		BNX2X_FREE(bnx2x_fp(bp, fp_index, rx_page_ring));
		BNX2X_PCI_FREE(bnx2x_fp(bp, fp_index, rx_sge_ring),
			       bnx2x_fp(bp, fp_index, rx_sge_mapping),
			       BCM_PAGE_SIZE * NUM_RX_SGE_PAGES);
	पूर्ण

	/* Tx */
	अगर (!skip_tx_queue(bp, fp_index)) अणु
		/* fastpath tx rings: tx_buf tx_desc */
		क्रम_each_cos_in_tx_queue(fp, cos) अणु
			काष्ठा bnx2x_fp_txdata *txdata = fp->txdata_ptr[cos];

			DP(NETIF_MSG_IFDOWN,
			   "freeing tx memory of fp %d cos %d cid %d\n",
			   fp_index, cos, txdata->cid);

			BNX2X_FREE(txdata->tx_buf_ring);
			BNX2X_PCI_FREE(txdata->tx_desc_ring,
				txdata->tx_desc_mapping,
				माप(जोड़ eth_tx_bd_types) * NUM_TX_BD);
		पूर्ण
	पूर्ण
	/* end of fastpath */
पूर्ण

अटल व्योम bnx2x_मुक्त_fp_mem_cnic(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;
	क्रम_each_cnic_queue(bp, i)
		bnx2x_मुक्त_fp_mem_at(bp, i);
पूर्ण

व्योम bnx2x_मुक्त_fp_mem(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;
	क्रम_each_eth_queue(bp, i)
		bnx2x_मुक्त_fp_mem_at(bp, i);
पूर्ण

अटल व्योम set_sb_लघुcuts(काष्ठा bnx2x *bp, पूर्णांक index)
अणु
	जोड़ host_hc_status_block status_blk = bnx2x_fp(bp, index, status_blk);
	अगर (!CHIP_IS_E1x(bp)) अणु
		bnx2x_fp(bp, index, sb_index_values) =
			(__le16 *)status_blk.e2_sb->sb.index_values;
		bnx2x_fp(bp, index, sb_running_index) =
			(__le16 *)status_blk.e2_sb->sb.running_index;
	पूर्ण अन्यथा अणु
		bnx2x_fp(bp, index, sb_index_values) =
			(__le16 *)status_blk.e1x_sb->sb.index_values;
		bnx2x_fp(bp, index, sb_running_index) =
			(__le16 *)status_blk.e1x_sb->sb.running_index;
	पूर्ण
पूर्ण

/* Returns the number of actually allocated BDs */
अटल पूर्णांक bnx2x_alloc_rx_bds(काष्ठा bnx2x_fastpath *fp,
			      पूर्णांक rx_ring_size)
अणु
	काष्ठा bnx2x *bp = fp->bp;
	u16 ring_prod, cqe_ring_prod;
	पूर्णांक i, failure_cnt = 0;

	fp->rx_comp_cons = 0;
	cqe_ring_prod = ring_prod = 0;

	/* This routine is called only during fo init so
	 * fp->eth_q_stats.rx_skb_alloc_failed = 0
	 */
	क्रम (i = 0; i < rx_ring_size; i++) अणु
		अगर (bnx2x_alloc_rx_data(bp, fp, ring_prod, GFP_KERNEL) < 0) अणु
			failure_cnt++;
			जारी;
		पूर्ण
		ring_prod = NEXT_RX_IDX(ring_prod);
		cqe_ring_prod = NEXT_RCQ_IDX(cqe_ring_prod);
		WARN_ON(ring_prod <= (i - failure_cnt));
	पूर्ण

	अगर (failure_cnt)
		BNX2X_ERR("was only able to allocate %d rx skbs on queue[%d]\n",
			  i - failure_cnt, fp->index);

	fp->rx_bd_prod = ring_prod;
	/* Limit the CQE producer by the CQE ring size */
	fp->rx_comp_prod = min_t(u16, NUM_RCQ_RINGS*RCQ_DESC_CNT,
			       cqe_ring_prod);

	bnx2x_fp_stats(bp, fp)->eth_q_stats.rx_skb_alloc_failed += failure_cnt;

	वापस i - failure_cnt;
पूर्ण

अटल व्योम bnx2x_set_next_page_rx_cq(काष्ठा bnx2x_fastpath *fp)
अणु
	पूर्णांक i;

	क्रम (i = 1; i <= NUM_RCQ_RINGS; i++) अणु
		काष्ठा eth_rx_cqe_next_page *nextpg;

		nextpg = (काष्ठा eth_rx_cqe_next_page *)
			&fp->rx_comp_ring[RCQ_DESC_CNT * i - 1];
		nextpg->addr_hi =
			cpu_to_le32(U64_HI(fp->rx_comp_mapping +
				   BCM_PAGE_SIZE*(i % NUM_RCQ_RINGS)));
		nextpg->addr_lo =
			cpu_to_le32(U64_LO(fp->rx_comp_mapping +
				   BCM_PAGE_SIZE*(i % NUM_RCQ_RINGS)));
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_alloc_fp_mem_at(काष्ठा bnx2x *bp, पूर्णांक index)
अणु
	जोड़ host_hc_status_block *sb;
	काष्ठा bnx2x_fastpath *fp = &bp->fp[index];
	पूर्णांक ring_size = 0;
	u8 cos;
	पूर्णांक rx_ring_size = 0;

	अगर (!bp->rx_ring_size && IS_MF_STORAGE_ONLY(bp)) अणु
		rx_ring_size = MIN_RX_SIZE_NONTPA;
		bp->rx_ring_size = rx_ring_size;
	पूर्ण अन्यथा अगर (!bp->rx_ring_size) अणु
		rx_ring_size = MAX_RX_AVAIL/BNX2X_NUM_RX_QUEUES(bp);

		अगर (CHIP_IS_E3(bp)) अणु
			u32 cfg = SHMEM_RD(bp,
					   dev_info.port_hw_config[BP_PORT(bp)].
					   शेष_cfg);

			/* Decrease ring size क्रम 1G functions */
			अगर ((cfg & PORT_HW_CFG_NET_SERDES_IF_MASK) ==
			    PORT_HW_CFG_NET_SERDES_IF_SGMII)
				rx_ring_size /= 10;
		पूर्ण

		/* allocate at least number of buffers required by FW */
		rx_ring_size = max_t(पूर्णांक, bp->disable_tpa ? MIN_RX_SIZE_NONTPA :
				     MIN_RX_SIZE_TPA, rx_ring_size);

		bp->rx_ring_size = rx_ring_size;
	पूर्ण अन्यथा /* अगर rx_ring_size specअगरied - use it */
		rx_ring_size = bp->rx_ring_size;

	DP(BNX2X_MSG_SP, "calculated rx_ring_size %d\n", rx_ring_size);

	/* Common */
	sb = &bnx2x_fp(bp, index, status_blk);

	अगर (!IS_FCOE_IDX(index)) अणु
		/* status blocks */
		अगर (!CHIP_IS_E1x(bp)) अणु
			sb->e2_sb = BNX2X_PCI_ALLOC(&bnx2x_fp(bp, index, status_blk_mapping),
						    माप(काष्ठा host_hc_status_block_e2));
			अगर (!sb->e2_sb)
				जाओ alloc_mem_err;
		पूर्ण अन्यथा अणु
			sb->e1x_sb = BNX2X_PCI_ALLOC(&bnx2x_fp(bp, index, status_blk_mapping),
						     माप(काष्ठा host_hc_status_block_e1x));
			अगर (!sb->e1x_sb)
				जाओ alloc_mem_err;
		पूर्ण
	पूर्ण

	/* FCoE Queue uses Default SB and करोesn't ACK the SB, thus no need to
	 * set लघुcuts क्रम it.
	 */
	अगर (!IS_FCOE_IDX(index))
		set_sb_लघुcuts(bp, index);

	/* Tx */
	अगर (!skip_tx_queue(bp, index)) अणु
		/* fastpath tx rings: tx_buf tx_desc */
		क्रम_each_cos_in_tx_queue(fp, cos) अणु
			काष्ठा bnx2x_fp_txdata *txdata = fp->txdata_ptr[cos];

			DP(NETIF_MSG_IFUP,
			   "allocating tx memory of fp %d cos %d\n",
			   index, cos);

			txdata->tx_buf_ring = kसुस्मृति(NUM_TX_BD,
						      माप(काष्ठा sw_tx_bd),
						      GFP_KERNEL);
			अगर (!txdata->tx_buf_ring)
				जाओ alloc_mem_err;
			txdata->tx_desc_ring = BNX2X_PCI_ALLOC(&txdata->tx_desc_mapping,
							       माप(जोड़ eth_tx_bd_types) * NUM_TX_BD);
			अगर (!txdata->tx_desc_ring)
				जाओ alloc_mem_err;
		पूर्ण
	पूर्ण

	/* Rx */
	अगर (!skip_rx_queue(bp, index)) अणु
		/* fastpath rx rings: rx_buf rx_desc rx_comp */
		bnx2x_fp(bp, index, rx_buf_ring) =
			kसुस्मृति(NUM_RX_BD, माप(काष्ठा sw_rx_bd), GFP_KERNEL);
		अगर (!bnx2x_fp(bp, index, rx_buf_ring))
			जाओ alloc_mem_err;
		bnx2x_fp(bp, index, rx_desc_ring) =
			BNX2X_PCI_ALLOC(&bnx2x_fp(bp, index, rx_desc_mapping),
					माप(काष्ठा eth_rx_bd) * NUM_RX_BD);
		अगर (!bnx2x_fp(bp, index, rx_desc_ring))
			जाओ alloc_mem_err;

		/* Seed all CQEs by 1s */
		bnx2x_fp(bp, index, rx_comp_ring) =
			BNX2X_PCI_FALLOC(&bnx2x_fp(bp, index, rx_comp_mapping),
					 माप(काष्ठा eth_fast_path_rx_cqe) * NUM_RCQ_BD);
		अगर (!bnx2x_fp(bp, index, rx_comp_ring))
			जाओ alloc_mem_err;

		/* SGE ring */
		bnx2x_fp(bp, index, rx_page_ring) =
			kसुस्मृति(NUM_RX_SGE, माप(काष्ठा sw_rx_page),
				GFP_KERNEL);
		अगर (!bnx2x_fp(bp, index, rx_page_ring))
			जाओ alloc_mem_err;
		bnx2x_fp(bp, index, rx_sge_ring) =
			BNX2X_PCI_ALLOC(&bnx2x_fp(bp, index, rx_sge_mapping),
					BCM_PAGE_SIZE * NUM_RX_SGE_PAGES);
		अगर (!bnx2x_fp(bp, index, rx_sge_ring))
			जाओ alloc_mem_err;
		/* RX BD ring */
		bnx2x_set_next_page_rx_bd(fp);

		/* CQ ring */
		bnx2x_set_next_page_rx_cq(fp);

		/* BDs */
		ring_size = bnx2x_alloc_rx_bds(fp, rx_ring_size);
		अगर (ring_size < rx_ring_size)
			जाओ alloc_mem_err;
	पूर्ण

	वापस 0;

/* handles low memory हालs */
alloc_mem_err:
	BNX2X_ERR("Unable to allocate full memory for queue %d (size %d)\n",
						index, ring_size);
	/* FW will drop all packets अगर queue is not big enough,
	 * In these हालs we disable the queue
	 * Min size is dअगरferent क्रम OOO, TPA and non-TPA queues
	 */
	अगर (ring_size < (fp->mode == TPA_MODE_DISABLED ?
				MIN_RX_SIZE_NONTPA : MIN_RX_SIZE_TPA)) अणु
			/* release memory allocated क्रम this queue */
			bnx2x_मुक्त_fp_mem_at(bp, index);
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_alloc_fp_mem_cnic(काष्ठा bnx2x *bp)
अणु
	अगर (!NO_FCOE(bp))
		/* FCoE */
		अगर (bnx2x_alloc_fp_mem_at(bp, FCOE_IDX(bp)))
			/* we will fail load process instead of mark
			 * NO_FCOE_FLAG
			 */
			वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_alloc_fp_mem(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	/* 1. Allocate FP क्रम leading - fatal अगर error
	 * 2. Allocate RSS - fix number of queues अगर error
	 */

	/* leading */
	अगर (bnx2x_alloc_fp_mem_at(bp, 0))
		वापस -ENOMEM;

	/* RSS */
	क्रम_each_nonशेष_eth_queue(bp, i)
		अगर (bnx2x_alloc_fp_mem_at(bp, i))
			अवरोध;

	/* handle memory failures */
	अगर (i != BNX2X_NUM_ETH_QUEUES(bp)) अणु
		पूर्णांक delta = BNX2X_NUM_ETH_QUEUES(bp) - i;

		WARN_ON(delta < 0);
		bnx2x_shrink_eth_fp(bp, delta);
		अगर (CNIC_SUPPORT(bp))
			/* move non eth FPs next to last eth FP
			 * must be करोne in that order
			 * FCOE_IDX < FWD_IDX < OOO_IDX
			 */

			/* move FCoE fp even NO_FCOE_FLAG is on */
			bnx2x_move_fp(bp, FCOE_IDX(bp), FCOE_IDX(bp) - delta);
		bp->num_ethernet_queues -= delta;
		bp->num_queues = bp->num_ethernet_queues +
				 bp->num_cnic_queues;
		BNX2X_ERR("Adjusted num of queues from %d to %d\n",
			  bp->num_queues + delta, bp->num_queues);
	पूर्ण

	वापस 0;
पूर्ण

व्योम bnx2x_मुक्त_mem_bp(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bp->fp_array_size; i++)
		kमुक्त(bp->fp[i].tpa_info);
	kमुक्त(bp->fp);
	kमुक्त(bp->sp_objs);
	kमुक्त(bp->fp_stats);
	kमुक्त(bp->bnx2x_txq);
	kमुक्त(bp->msix_table);
	kमुक्त(bp->ilt);
पूर्ण

पूर्णांक bnx2x_alloc_mem_bp(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_fastpath *fp;
	काष्ठा msix_entry *tbl;
	काष्ठा bnx2x_ilt *ilt;
	पूर्णांक msix_table_size = 0;
	पूर्णांक fp_array_size, txq_array_size;
	पूर्णांक i;

	/*
	 * The biggest MSI-X table we might need is as a maximum number of fast
	 * path IGU SBs plus शेष SB (क्रम PF only).
	 */
	msix_table_size = bp->igu_sb_cnt;
	अगर (IS_PF(bp))
		msix_table_size++;
	BNX2X_DEV_INFO("msix_table_size %d\n", msix_table_size);

	/* fp array: RSS plus CNIC related L2 queues */
	fp_array_size = BNX2X_MAX_RSS_COUNT(bp) + CNIC_SUPPORT(bp);
	bp->fp_array_size = fp_array_size;
	BNX2X_DEV_INFO("fp_array_size %d\n", bp->fp_array_size);

	fp = kसुस्मृति(bp->fp_array_size, माप(*fp), GFP_KERNEL);
	अगर (!fp)
		जाओ alloc_err;
	क्रम (i = 0; i < bp->fp_array_size; i++) अणु
		fp[i].tpa_info =
			kसुस्मृति(ETH_MAX_AGGREGATION_QUEUES_E1H_E2,
				माप(काष्ठा bnx2x_agg_info), GFP_KERNEL);
		अगर (!(fp[i].tpa_info))
			जाओ alloc_err;
	पूर्ण

	bp->fp = fp;

	/* allocate sp objs */
	bp->sp_objs = kसुस्मृति(bp->fp_array_size, माप(काष्ठा bnx2x_sp_objs),
			      GFP_KERNEL);
	अगर (!bp->sp_objs)
		जाओ alloc_err;

	/* allocate fp_stats */
	bp->fp_stats = kसुस्मृति(bp->fp_array_size, माप(काष्ठा bnx2x_fp_stats),
			       GFP_KERNEL);
	अगर (!bp->fp_stats)
		जाओ alloc_err;

	/* Allocate memory क्रम the transmission queues array */
	txq_array_size =
		BNX2X_MAX_RSS_COUNT(bp) * BNX2X_MULTI_TX_COS + CNIC_SUPPORT(bp);
	BNX2X_DEV_INFO("txq_array_size %d", txq_array_size);

	bp->bnx2x_txq = kसुस्मृति(txq_array_size, माप(काष्ठा bnx2x_fp_txdata),
				GFP_KERNEL);
	अगर (!bp->bnx2x_txq)
		जाओ alloc_err;

	/* msix table */
	tbl = kसुस्मृति(msix_table_size, माप(*tbl), GFP_KERNEL);
	अगर (!tbl)
		जाओ alloc_err;
	bp->msix_table = tbl;

	/* ilt */
	ilt = kzalloc(माप(*ilt), GFP_KERNEL);
	अगर (!ilt)
		जाओ alloc_err;
	bp->ilt = ilt;

	वापस 0;
alloc_err:
	bnx2x_मुक्त_mem_bp(bp);
	वापस -ENOMEM;
पूर्ण

पूर्णांक bnx2x_reload_अगर_running(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (unlikely(!netअगर_running(dev)))
		वापस 0;

	bnx2x_nic_unload(bp, UNLOAD_NORMAL, true);
	वापस bnx2x_nic_load(bp, LOAD_NORMAL);
पूर्ण

पूर्णांक bnx2x_get_cur_phy_idx(काष्ठा bnx2x *bp)
अणु
	u32 sel_phy_idx = 0;
	अगर (bp->link_params.num_phys <= 1)
		वापस INT_PHY;

	अगर (bp->link_vars.link_up) अणु
		sel_phy_idx = EXT_PHY1;
		/* In हाल link is SERDES, check अगर the EXT_PHY2 is the one */
		अगर ((bp->link_vars.link_status & LINK_STATUS_SERDES_LINK) &&
		    (bp->link_params.phy[EXT_PHY2].supported & SUPPORTED_FIBRE))
			sel_phy_idx = EXT_PHY2;
	पूर्ण अन्यथा अणु

		चयन (bnx2x_phy_selection(&bp->link_params)) अणु
		हाल PORT_HW_CFG_PHY_SELECTION_HARDWARE_DEFAULT:
		हाल PORT_HW_CFG_PHY_SELECTION_FIRST_PHY:
		हाल PORT_HW_CFG_PHY_SELECTION_FIRST_PHY_PRIORITY:
		       sel_phy_idx = EXT_PHY1;
		       अवरोध;
		हाल PORT_HW_CFG_PHY_SELECTION_SECOND_PHY:
		हाल PORT_HW_CFG_PHY_SELECTION_SECOND_PHY_PRIORITY:
		       sel_phy_idx = EXT_PHY2;
		       अवरोध;
		पूर्ण
	पूर्ण

	वापस sel_phy_idx;
पूर्ण
पूर्णांक bnx2x_get_link_cfg_idx(काष्ठा bnx2x *bp)
अणु
	u32 sel_phy_idx = bnx2x_get_cur_phy_idx(bp);
	/*
	 * The selected activated PHY is always after swapping (in हाल PHY
	 * swapping is enabled). So when swapping is enabled, we need to reverse
	 * the configuration
	 */

	अगर (bp->link_params.multi_phy_config &
	    PORT_HW_CFG_PHY_SWAPPED_ENABLED) अणु
		अगर (sel_phy_idx == EXT_PHY1)
			sel_phy_idx = EXT_PHY2;
		अन्यथा अगर (sel_phy_idx == EXT_PHY2)
			sel_phy_idx = EXT_PHY1;
	पूर्ण
	वापस LINK_CONFIG_IDX(sel_phy_idx);
पूर्ण

#अगर_घोषित NETDEV_FCOE_WWNN
पूर्णांक bnx2x_fcoe_get_wwn(काष्ठा net_device *dev, u64 *wwn, पूर्णांक type)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा cnic_eth_dev *cp = &bp->cnic_eth_dev;

	चयन (type) अणु
	हाल NETDEV_FCOE_WWNN:
		*wwn = HILO_U64(cp->fcoe_wwn_node_name_hi,
				cp->fcoe_wwn_node_name_lo);
		अवरोध;
	हाल NETDEV_FCOE_WWPN:
		*wwn = HILO_U64(cp->fcoe_wwn_port_name_hi,
				cp->fcoe_wwn_port_name_lo);
		अवरोध;
	शेष:
		BNX2X_ERR("Wrong WWN type requested - %d\n", type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* called with rtnl_lock */
पूर्णांक bnx2x_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (pci_num_vf(bp->pdev)) अणु
		DP(BNX2X_MSG_IOV, "VFs are enabled, can not change MTU\n");
		वापस -EPERM;
	पूर्ण

	अगर (bp->recovery_state != BNX2X_RECOVERY_DONE) अणु
		BNX2X_ERR("Can't perform change MTU during parity recovery\n");
		वापस -EAGAIN;
	पूर्ण

	/* This करोes not race with packet allocation
	 * because the actual alloc size is
	 * only updated as part of load
	 */
	dev->mtu = new_mtu;

	अगर (!bnx2x_mtu_allows_gro(new_mtu))
		dev->features &= ~NETIF_F_GRO_HW;

	अगर (IS_PF(bp) && SHMEM2_HAS(bp, curr_cfg))
		SHMEM2_WR(bp, curr_cfg, CURR_CFG_MET_OS);

	वापस bnx2x_reload_अगर_running(dev);
पूर्ण

netdev_features_t bnx2x_fix_features(काष्ठा net_device *dev,
				     netdev_features_t features)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (pci_num_vf(bp->pdev)) अणु
		netdev_features_t changed = dev->features ^ features;

		/* Revert the requested changes in features अगर they
		 * would require पूर्णांकernal reload of PF in bnx2x_set_features().
		 */
		अगर (!(features & NETIF_F_RXCSUM) && !bp->disable_tpa) अणु
			features &= ~NETIF_F_RXCSUM;
			features |= dev->features & NETIF_F_RXCSUM;
		पूर्ण

		अगर (changed & NETIF_F_LOOPBACK) अणु
			features &= ~NETIF_F_LOOPBACK;
			features |= dev->features & NETIF_F_LOOPBACK;
		पूर्ण
	पूर्ण

	/* TPA requires Rx CSUM offloading */
	अगर (!(features & NETIF_F_RXCSUM))
		features &= ~NETIF_F_LRO;

	अगर (!(features & NETIF_F_GRO) || !bnx2x_mtu_allows_gro(dev->mtu))
		features &= ~NETIF_F_GRO_HW;
	अगर (features & NETIF_F_GRO_HW)
		features &= ~NETIF_F_LRO;

	वापस features;
पूर्ण

पूर्णांक bnx2x_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	netdev_features_t changes = features ^ dev->features;
	bool bnx2x_reload = false;
	पूर्णांक rc;

	/* VFs or non SRIOV PFs should be able to change loopback feature */
	अगर (!pci_num_vf(bp->pdev)) अणु
		अगर (features & NETIF_F_LOOPBACK) अणु
			अगर (bp->link_params.loopback_mode != LOOPBACK_BMAC) अणु
				bp->link_params.loopback_mode = LOOPBACK_BMAC;
				bnx2x_reload = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bp->link_params.loopback_mode != LOOPBACK_NONE) अणु
				bp->link_params.loopback_mode = LOOPBACK_NONE;
				bnx2x_reload = true;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Don't care about GRO changes */
	changes &= ~NETIF_F_GRO;

	अगर (changes)
		bnx2x_reload = true;

	अगर (bnx2x_reload) अणु
		अगर (bp->recovery_state == BNX2X_RECOVERY_DONE) अणु
			dev->features = features;
			rc = bnx2x_reload_अगर_running(dev);
			वापस rc ? rc : 1;
		पूर्ण
		/* अन्यथा: bnx2x_nic_load() will be called at end of recovery */
	पूर्ण

	वापस 0;
पूर्ण

व्योम bnx2x_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	/* We want the inक्रमmation of the dump logged,
	 * but calling bnx2x_panic() would समाप्त all chances of recovery.
	 */
	अगर (!bp->panic)
#अगर_अघोषित BNX2X_STOP_ON_ERROR
		bnx2x_panic_dump(bp, false);
#अन्यथा
		bnx2x_panic();
#पूर्ण_अगर

	/* This allows the netअगर to be shutकरोwn gracefully beक्रमe resetting */
	bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_TX_TIMEOUT, 0);
पूर्ण

अटल पूर्णांक __maybe_unused bnx2x_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnx2x *bp;

	अगर (!dev) अणु
		dev_err(&pdev->dev, "BAD net device from bnx2x_init_one\n");
		वापस -ENODEV;
	पूर्ण
	bp = netdev_priv(dev);

	rtnl_lock();

	अगर (!netअगर_running(dev)) अणु
		rtnl_unlock();
		वापस 0;
	पूर्ण

	netअगर_device_detach(dev);

	bnx2x_nic_unload(bp, UNLOAD_CLOSE, false);

	rtnl_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused bnx2x_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा bnx2x *bp;
	पूर्णांक rc;

	अगर (!dev) अणु
		dev_err(&pdev->dev, "BAD net device from bnx2x_init_one\n");
		वापस -ENODEV;
	पूर्ण
	bp = netdev_priv(dev);

	अगर (bp->recovery_state != BNX2X_RECOVERY_DONE) अणु
		BNX2X_ERR("Handling parity error recovery. Try again later\n");
		वापस -EAGAIN;
	पूर्ण

	rtnl_lock();

	अगर (!netअगर_running(dev)) अणु
		rtnl_unlock();
		वापस 0;
	पूर्ण

	netअगर_device_attach(dev);

	rc = bnx2x_nic_load(bp, LOAD_OPEN);

	rtnl_unlock();

	वापस rc;
पूर्ण

SIMPLE_DEV_PM_OPS(bnx2x_pm_ops, bnx2x_suspend, bnx2x_resume);

व्योम bnx2x_set_ctx_validation(काष्ठा bnx2x *bp, काष्ठा eth_context *cxt,
			      u32 cid)
अणु
	अगर (!cxt) अणु
		BNX2X_ERR("bad context pointer %p\n", cxt);
		वापस;
	पूर्ण

	/* ustorm cxt validation */
	cxt->ustorm_ag_context.cdu_usage =
		CDU_RSRVD_VALUE_TYPE_A(HW_CID(bp, cid),
			CDU_REGION_NUMBER_UCM_AG, ETH_CONNECTION_TYPE);
	/* xcontext validation */
	cxt->xstorm_ag_context.cdu_reserved =
		CDU_RSRVD_VALUE_TYPE_A(HW_CID(bp, cid),
			CDU_REGION_NUMBER_XCM_AG, ETH_CONNECTION_TYPE);
पूर्ण

अटल व्योम storm_स_रखो_hc_समयout(काष्ठा bnx2x *bp, u8 port,
				    u8 fw_sb_id, u8 sb_index,
				    u8 ticks)
अणु
	u32 addr = BAR_CSTRORM_INTMEM +
		   CSTORM_STATUS_BLOCK_DATA_TIMEOUT_OFFSET(fw_sb_id, sb_index);
	REG_WR8(bp, addr, ticks);
	DP(NETIF_MSG_IFUP,
	   "port %x fw_sb_id %d sb_index %d ticks %d\n",
	   port, fw_sb_id, sb_index, ticks);
पूर्ण

अटल व्योम storm_स_रखो_hc_disable(काष्ठा bnx2x *bp, u8 port,
				    u16 fw_sb_id, u8 sb_index,
				    u8 disable)
अणु
	u32 enable_flag = disable ? 0 : (1 << HC_INDEX_DATA_HC_ENABLED_SHIFT);
	u32 addr = BAR_CSTRORM_INTMEM +
		   CSTORM_STATUS_BLOCK_DATA_FLAGS_OFFSET(fw_sb_id, sb_index);
	u8 flags = REG_RD8(bp, addr);
	/* clear and set */
	flags &= ~HC_INDEX_DATA_HC_ENABLED;
	flags |= enable_flag;
	REG_WR8(bp, addr, flags);
	DP(NETIF_MSG_IFUP,
	   "port %x fw_sb_id %d sb_index %d disable %d\n",
	   port, fw_sb_id, sb_index, disable);
पूर्ण

व्योम bnx2x_update_coalesce_sb_index(काष्ठा bnx2x *bp, u8 fw_sb_id,
				    u8 sb_index, u8 disable, u16 usec)
अणु
	पूर्णांक port = BP_PORT(bp);
	u8 ticks = usec / BNX2X_BTR;

	storm_स_रखो_hc_समयout(bp, port, fw_sb_id, sb_index, ticks);

	disable = disable ? 1 : (usec ? 0 : 1);
	storm_स_रखो_hc_disable(bp, port, fw_sb_id, sb_index, disable);
पूर्ण

व्योम bnx2x_schedule_sp_rtnl(काष्ठा bnx2x *bp, क्रमागत sp_rtnl_flag flag,
			    u32 verbose)
अणु
	smp_mb__beक्रमe_atomic();
	set_bit(flag, &bp->sp_rtnl_state);
	smp_mb__after_atomic();
	DP((BNX2X_MSG_SP | verbose), "Scheduling sp_rtnl task [Flag: %d]\n",
	   flag);
	schedule_delayed_work(&bp->sp_rtnl_task, 0);
पूर्ण
