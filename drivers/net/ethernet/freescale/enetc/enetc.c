<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2017-2019 NXP */

#समावेश "enetc.h"
#समावेश <linux/bpf_trace.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <net/pkt_sched.h>

अटल पूर्णांक enetc_num_stack_tx_queues(काष्ठा enetc_ndev_priv *priv)
अणु
	पूर्णांक num_tx_rings = priv->num_tx_rings;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_rx_rings; i++)
		अगर (priv->rx_ring[i]->xdp.prog)
			वापस num_tx_rings - num_possible_cpus();

	वापस num_tx_rings;
पूर्ण

अटल काष्ठा enetc_bdr *enetc_rx_ring_from_xdp_tx_ring(काष्ठा enetc_ndev_priv *priv,
							काष्ठा enetc_bdr *tx_ring)
अणु
	पूर्णांक index = &priv->tx_ring[tx_ring->index] - priv->xdp_tx_ring;

	वापस priv->rx_ring[index];
पूर्ण

अटल काष्ठा sk_buff *enetc_tx_swbd_get_skb(काष्ठा enetc_tx_swbd *tx_swbd)
अणु
	अगर (tx_swbd->is_xdp_tx || tx_swbd->is_xdp_redirect)
		वापस शून्य;

	वापस tx_swbd->skb;
पूर्ण

अटल काष्ठा xdp_frame *
enetc_tx_swbd_get_xdp_frame(काष्ठा enetc_tx_swbd *tx_swbd)
अणु
	अगर (tx_swbd->is_xdp_redirect)
		वापस tx_swbd->xdp_frame;

	वापस शून्य;
पूर्ण

अटल व्योम enetc_unmap_tx_buff(काष्ठा enetc_bdr *tx_ring,
				काष्ठा enetc_tx_swbd *tx_swbd)
अणु
	/* For XDP_TX, pages come from RX, whereas क्रम the other contexts where
	 * we have is_dma_page_set, those come from skb_frag_dma_map. We need
	 * to match the DMA mapping length, so we need to dअगरferentiate those.
	 */
	अगर (tx_swbd->is_dma_page)
		dma_unmap_page(tx_ring->dev, tx_swbd->dma,
			       tx_swbd->is_xdp_tx ? PAGE_SIZE : tx_swbd->len,
			       tx_swbd->dir);
	अन्यथा
		dma_unmap_single(tx_ring->dev, tx_swbd->dma,
				 tx_swbd->len, tx_swbd->dir);
	tx_swbd->dma = 0;
पूर्ण

अटल व्योम enetc_मुक्त_tx_frame(काष्ठा enetc_bdr *tx_ring,
				काष्ठा enetc_tx_swbd *tx_swbd)
अणु
	काष्ठा xdp_frame *xdp_frame = enetc_tx_swbd_get_xdp_frame(tx_swbd);
	काष्ठा sk_buff *skb = enetc_tx_swbd_get_skb(tx_swbd);

	अगर (tx_swbd->dma)
		enetc_unmap_tx_buff(tx_ring, tx_swbd);

	अगर (xdp_frame) अणु
		xdp_वापस_frame(tx_swbd->xdp_frame);
		tx_swbd->xdp_frame = शून्य;
	पूर्ण अन्यथा अगर (skb) अणु
		dev_kमुक्त_skb_any(skb);
		tx_swbd->skb = शून्य;
	पूर्ण
पूर्ण

/* Let H/W know BD ring has been updated */
अटल व्योम enetc_update_tx_ring_tail(काष्ठा enetc_bdr *tx_ring)
अणु
	/* includes wmb() */
	enetc_wr_reg_hot(tx_ring->tpir, tx_ring->next_to_use);
पूर्ण

अटल पूर्णांक enetc_ptp_parse(काष्ठा sk_buff *skb, u8 *udp,
			   u8 *msgtype, u8 *twostep,
			   u16 *correction_offset, u16 *body_offset)
अणु
	अचिन्हित पूर्णांक ptp_class;
	काष्ठा ptp_header *hdr;
	अचिन्हित पूर्णांक type;
	u8 *base;

	ptp_class = ptp_classअगरy_raw(skb);
	अगर (ptp_class == PTP_CLASS_NONE)
		वापस -EINVAL;

	hdr = ptp_parse_header(skb, ptp_class);
	अगर (!hdr)
		वापस -EINVAL;

	type = ptp_class & PTP_CLASS_PMASK;
	अगर (type == PTP_CLASS_IPV4 || type == PTP_CLASS_IPV6)
		*udp = 1;
	अन्यथा
		*udp = 0;

	*msgtype = ptp_get_msgtype(hdr, ptp_class);
	*twostep = hdr->flag_field[0] & 0x2;

	base = skb_mac_header(skb);
	*correction_offset = (u8 *)&hdr->correction - base;
	*body_offset = (u8 *)hdr + माप(काष्ठा ptp_header) - base;

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_map_tx_buffs(काष्ठा enetc_bdr *tx_ring, काष्ठा sk_buff *skb)
अणु
	bool करो_vlan, करो_onestep_tstamp = false, करो_twostep_tstamp = false;
	काष्ठा enetc_ndev_priv *priv = netdev_priv(tx_ring->ndev);
	काष्ठा enetc_hw *hw = &priv->si->hw;
	काष्ठा enetc_tx_swbd *tx_swbd;
	पूर्णांक len = skb_headlen(skb);
	जोड़ enetc_tx_bd temp_bd;
	u8 msgtype, twostep, udp;
	जोड़ enetc_tx_bd *txbd;
	u16 offset1, offset2;
	पूर्णांक i, count = 0;
	skb_frag_t *frag;
	अचिन्हित पूर्णांक f;
	dma_addr_t dma;
	u8 flags = 0;

	i = tx_ring->next_to_use;
	txbd = ENETC_TXBD(*tx_ring, i);
	prefetchw(txbd);

	dma = dma_map_single(tx_ring->dev, skb->data, len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(tx_ring->dev, dma)))
		जाओ dma_err;

	temp_bd.addr = cpu_to_le64(dma);
	temp_bd.buf_len = cpu_to_le16(len);
	temp_bd.lstatus = 0;

	tx_swbd = &tx_ring->tx_swbd[i];
	tx_swbd->dma = dma;
	tx_swbd->len = len;
	tx_swbd->is_dma_page = 0;
	tx_swbd->dir = DMA_TO_DEVICE;
	count++;

	करो_vlan = skb_vlan_tag_present(skb);
	अगर (skb->cb[0] & ENETC_F_TX_ONESTEP_SYNC_TSTAMP) अणु
		अगर (enetc_ptp_parse(skb, &udp, &msgtype, &twostep, &offset1,
				    &offset2) ||
		    msgtype != PTP_MSGTYPE_SYNC || twostep)
			WARN_ONCE(1, "Bad packet for one-step timestamping\n");
		अन्यथा
			करो_onestep_tstamp = true;
	पूर्ण अन्यथा अगर (skb->cb[0] & ENETC_F_TX_TSTAMP) अणु
		करो_twostep_tstamp = true;
	पूर्ण

	tx_swbd->करो_twostep_tstamp = करो_twostep_tstamp;
	tx_swbd->check_wb = tx_swbd->करो_twostep_tstamp;

	अगर (करो_vlan || करो_onestep_tstamp || करो_twostep_tstamp)
		flags |= ENETC_TXBD_FLAGS_EX;

	अगर (tx_ring->tsd_enable)
		flags |= ENETC_TXBD_FLAGS_TSE | ENETC_TXBD_FLAGS_TXSTART;

	/* first BD needs frm_len and offload flags set */
	temp_bd.frm_len = cpu_to_le16(skb->len);
	temp_bd.flags = flags;

	अगर (flags & ENETC_TXBD_FLAGS_TSE)
		temp_bd.txstart = enetc_txbd_set_tx_start(skb->skb_mstamp_ns,
							  flags);

	अगर (flags & ENETC_TXBD_FLAGS_EX) अणु
		u8 e_flags = 0;
		*txbd = temp_bd;
		enetc_clear_tx_bd(&temp_bd);

		/* add extension BD क्रम VLAN and/or बारtamping */
		flags = 0;
		tx_swbd++;
		txbd++;
		i++;
		अगर (unlikely(i == tx_ring->bd_count)) अणु
			i = 0;
			tx_swbd = tx_ring->tx_swbd;
			txbd = ENETC_TXBD(*tx_ring, 0);
		पूर्ण
		prefetchw(txbd);

		अगर (करो_vlan) अणु
			temp_bd.ext.vid = cpu_to_le16(skb_vlan_tag_get(skb));
			temp_bd.ext.tpid = 0; /* < C-TAG */
			e_flags |= ENETC_TXBD_E_FLAGS_VLAN_INS;
		पूर्ण

		अगर (करो_onestep_tstamp) अणु
			u32 lo, hi, val;
			u64 sec, nsec;
			u8 *data;

			lo = enetc_rd_hot(hw, ENETC_SICTR0);
			hi = enetc_rd_hot(hw, ENETC_SICTR1);
			sec = (u64)hi << 32 | lo;
			nsec = करो_भाग(sec, 1000000000);

			/* Configure extension BD */
			temp_bd.ext.tstamp = cpu_to_le32(lo & 0x3fffffff);
			e_flags |= ENETC_TXBD_E_FLAGS_ONE_STEP_PTP;

			/* Update originTimestamp field of Sync packet
			 * - 48 bits seconds field
			 * - 32 bits nanseconds field
			 */
			data = skb_mac_header(skb);
			*(__be16 *)(data + offset2) =
				htons((sec >> 32) & 0xffff);
			*(__be32 *)(data + offset2 + 2) =
				htonl(sec & 0xffffffff);
			*(__be32 *)(data + offset2 + 6) = htonl(nsec);

			/* Configure single-step रेजिस्टर */
			val = ENETC_PM0_SINGLE_STEP_EN;
			val |= ENETC_SET_SINGLE_STEP_OFFSET(offset1);
			अगर (udp)
				val |= ENETC_PM0_SINGLE_STEP_CH;

			enetc_port_wr(hw, ENETC_PM0_SINGLE_STEP, val);
			enetc_port_wr(hw, ENETC_PM1_SINGLE_STEP, val);
		पूर्ण अन्यथा अगर (करो_twostep_tstamp) अणु
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
			e_flags |= ENETC_TXBD_E_FLAGS_TWO_STEP_PTP;
		पूर्ण

		temp_bd.ext.e_flags = e_flags;
		count++;
	पूर्ण

	frag = &skb_shinfo(skb)->frags[0];
	क्रम (f = 0; f < skb_shinfo(skb)->nr_frags; f++, frag++) अणु
		len = skb_frag_size(frag);
		dma = skb_frag_dma_map(tx_ring->dev, frag, 0, len,
				       DMA_TO_DEVICE);
		अगर (dma_mapping_error(tx_ring->dev, dma))
			जाओ dma_err;

		*txbd = temp_bd;
		enetc_clear_tx_bd(&temp_bd);

		flags = 0;
		tx_swbd++;
		txbd++;
		i++;
		अगर (unlikely(i == tx_ring->bd_count)) अणु
			i = 0;
			tx_swbd = tx_ring->tx_swbd;
			txbd = ENETC_TXBD(*tx_ring, 0);
		पूर्ण
		prefetchw(txbd);

		temp_bd.addr = cpu_to_le64(dma);
		temp_bd.buf_len = cpu_to_le16(len);

		tx_swbd->dma = dma;
		tx_swbd->len = len;
		tx_swbd->is_dma_page = 1;
		tx_swbd->dir = DMA_TO_DEVICE;
		count++;
	पूर्ण

	/* last BD needs 'F' bit set */
	flags |= ENETC_TXBD_FLAGS_F;
	temp_bd.flags = flags;
	*txbd = temp_bd;

	tx_ring->tx_swbd[i].is_eof = true;
	tx_ring->tx_swbd[i].skb = skb;

	enetc_bdr_idx_inc(tx_ring, &i);
	tx_ring->next_to_use = i;

	skb_tx_बारtamp(skb);

	enetc_update_tx_ring_tail(tx_ring);

	वापस count;

dma_err:
	dev_err(tx_ring->dev, "DMA map error");

	करो अणु
		tx_swbd = &tx_ring->tx_swbd[i];
		enetc_मुक्त_tx_frame(tx_ring, tx_swbd);
		अगर (i == 0)
			i = tx_ring->bd_count;
		i--;
	पूर्ण जबतक (count--);

	वापस 0;
पूर्ण

अटल netdev_tx_t enetc_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *ndev)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_bdr *tx_ring;
	पूर्णांक count;

	/* Queue one-step Sync packet अगर alपढ़ोy locked */
	अगर (skb->cb[0] & ENETC_F_TX_ONESTEP_SYNC_TSTAMP) अणु
		अगर (test_and_set_bit_lock(ENETC_TX_ONESTEP_TSTAMP_IN_PROGRESS,
					  &priv->flags)) अणु
			skb_queue_tail(&priv->tx_skbs, skb);
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण

	tx_ring = priv->tx_ring[skb->queue_mapping];

	अगर (unlikely(skb_shinfo(skb)->nr_frags > ENETC_MAX_SKB_FRAGS))
		अगर (unlikely(skb_linearize(skb)))
			जाओ drop_packet_err;

	count = skb_shinfo(skb)->nr_frags + 1; /* fragments + head */
	अगर (enetc_bd_unused(tx_ring) < ENETC_TXBDS_NEEDED(count)) अणु
		netअगर_stop_subqueue(ndev, tx_ring->index);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	enetc_lock_mdio();
	count = enetc_map_tx_buffs(tx_ring, skb);
	enetc_unlock_mdio();

	अगर (unlikely(!count))
		जाओ drop_packet_err;

	अगर (enetc_bd_unused(tx_ring) < ENETC_TXBDS_MAX_NEEDED)
		netअगर_stop_subqueue(ndev, tx_ring->index);

	वापस NETDEV_TX_OK;

drop_packet_err:
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

netdev_tx_t enetc_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	u8 udp, msgtype, twostep;
	u16 offset1, offset2;

	/* Mark tx बारtamp type on skb->cb[0] अगर requires */
	अगर ((skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
	    (priv->active_offloads & ENETC_F_TX_TSTAMP_MASK)) अणु
		skb->cb[0] = priv->active_offloads & ENETC_F_TX_TSTAMP_MASK;
	पूर्ण अन्यथा अणु
		skb->cb[0] = 0;
	पूर्ण

	/* Fall back to two-step बारtamp अगर not one-step Sync packet */
	अगर (skb->cb[0] & ENETC_F_TX_ONESTEP_SYNC_TSTAMP) अणु
		अगर (enetc_ptp_parse(skb, &udp, &msgtype, &twostep,
				    &offset1, &offset2) ||
		    msgtype != PTP_MSGTYPE_SYNC || twostep != 0)
			skb->cb[0] = ENETC_F_TX_TSTAMP;
	पूर्ण

	वापस enetc_start_xmit(skb, ndev);
पूर्ण

अटल irqवापस_t enetc_msix(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा enetc_पूर्णांक_vector	*v = data;
	पूर्णांक i;

	enetc_lock_mdio();

	/* disable पूर्णांकerrupts */
	enetc_wr_reg_hot(v->rbier, 0);
	enetc_wr_reg_hot(v->ricr1, v->rx_ictt);

	क्रम_each_set_bit(i, &v->tx_rings_map, ENETC_MAX_NUM_TXQS)
		enetc_wr_reg_hot(v->tbier_base + ENETC_BDR_OFF(i), 0);

	enetc_unlock_mdio();

	napi_schedule(&v->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम enetc_rx_dim_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा dim *dim = container_of(w, काष्ठा dim, work);
	काष्ठा dim_cq_moder moder =
		net_dim_get_rx_moderation(dim->mode, dim->profile_ix);
	काष्ठा enetc_पूर्णांक_vector	*v =
		container_of(dim, काष्ठा enetc_पूर्णांक_vector, rx_dim);

	v->rx_ictt = enetc_usecs_to_cycles(moder.usec);
	dim->state = DIM_START_MEASURE;
पूर्ण

अटल व्योम enetc_rx_net_dim(काष्ठा enetc_पूर्णांक_vector *v)
अणु
	काष्ठा dim_sample dim_sample;

	v->comp_cnt++;

	अगर (!v->rx_napi_work)
		वापस;

	dim_update_sample(v->comp_cnt,
			  v->rx_ring.stats.packets,
			  v->rx_ring.stats.bytes,
			  &dim_sample);
	net_dim(&v->rx_dim, dim_sample);
पूर्ण

अटल पूर्णांक enetc_bd_पढ़ोy_count(काष्ठा enetc_bdr *tx_ring, पूर्णांक ci)
अणु
	पूर्णांक pi = enetc_rd_reg_hot(tx_ring->tcir) & ENETC_TBCIR_IDX_MASK;

	वापस pi >= ci ? pi - ci : tx_ring->bd_count - ci + pi;
पूर्ण

अटल bool enetc_page_reusable(काष्ठा page *page)
अणु
	वापस (!page_is_pfmeदो_स्मृति(page) && page_ref_count(page) == 1);
पूर्ण

अटल व्योम enetc_reuse_page(काष्ठा enetc_bdr *rx_ring,
			     काष्ठा enetc_rx_swbd *old)
अणु
	काष्ठा enetc_rx_swbd *new;

	new = &rx_ring->rx_swbd[rx_ring->next_to_alloc];

	/* next buf that may reuse a page */
	enetc_bdr_idx_inc(rx_ring, &rx_ring->next_to_alloc);

	/* copy page reference */
	*new = *old;
पूर्ण

अटल व्योम enetc_get_tx_tstamp(काष्ठा enetc_hw *hw, जोड़ enetc_tx_bd *txbd,
				u64 *tstamp)
अणु
	u32 lo, hi, tstamp_lo;

	lo = enetc_rd_hot(hw, ENETC_SICTR0);
	hi = enetc_rd_hot(hw, ENETC_SICTR1);
	tstamp_lo = le32_to_cpu(txbd->wb.tstamp);
	अगर (lo <= tstamp_lo)
		hi -= 1;
	*tstamp = (u64)hi << 32 | tstamp_lo;
पूर्ण

अटल व्योम enetc_tstamp_tx(काष्ठा sk_buff *skb, u64 tstamp)
अणु
	काष्ठा skb_shared_hwtstamps shhwtstamps;

	अगर (skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS) अणु
		स_रखो(&shhwtstamps, 0, माप(shhwtstamps));
		shhwtstamps.hwtstamp = ns_to_kसमय(tstamp);
		skb_txसमय_consumed(skb);
		skb_tstamp_tx(skb, &shhwtstamps);
	पूर्ण
पूर्ण

अटल व्योम enetc_recycle_xdp_tx_buff(काष्ठा enetc_bdr *tx_ring,
				      काष्ठा enetc_tx_swbd *tx_swbd)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(tx_ring->ndev);
	काष्ठा enetc_rx_swbd rx_swbd = अणु
		.dma = tx_swbd->dma,
		.page = tx_swbd->page,
		.page_offset = tx_swbd->page_offset,
		.dir = tx_swbd->dir,
		.len = tx_swbd->len,
	पूर्ण;
	काष्ठा enetc_bdr *rx_ring;

	rx_ring = enetc_rx_ring_from_xdp_tx_ring(priv, tx_ring);

	अगर (likely(enetc_swbd_unused(rx_ring))) अणु
		enetc_reuse_page(rx_ring, &rx_swbd);

		/* sync क्रम use by the device */
		dma_sync_single_range_क्रम_device(rx_ring->dev, rx_swbd.dma,
						 rx_swbd.page_offset,
						 ENETC_RXB_DMA_SIZE_XDP,
						 rx_swbd.dir);

		rx_ring->stats.recycles++;
	पूर्ण अन्यथा अणु
		/* RX ring is alपढ़ोy full, we need to unmap and मुक्त the
		 * page, since there's nothing useful we can करो with it.
		 */
		rx_ring->stats.recycle_failures++;

		dma_unmap_page(rx_ring->dev, rx_swbd.dma, PAGE_SIZE,
			       rx_swbd.dir);
		__मुक्त_page(rx_swbd.page);
	पूर्ण

	rx_ring->xdp.xdp_tx_in_flight--;
पूर्ण

अटल bool enetc_clean_tx_ring(काष्ठा enetc_bdr *tx_ring, पूर्णांक napi_budget)
अणु
	काष्ठा net_device *ndev = tx_ring->ndev;
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	पूर्णांक tx_frm_cnt = 0, tx_byte_cnt = 0;
	काष्ठा enetc_tx_swbd *tx_swbd;
	पूर्णांक i, bds_to_clean;
	bool करो_twostep_tstamp;
	u64 tstamp = 0;

	i = tx_ring->next_to_clean;
	tx_swbd = &tx_ring->tx_swbd[i];

	bds_to_clean = enetc_bd_पढ़ोy_count(tx_ring, i);

	करो_twostep_tstamp = false;

	जबतक (bds_to_clean && tx_frm_cnt < ENETC_DEFAULT_TX_WORK) अणु
		काष्ठा xdp_frame *xdp_frame = enetc_tx_swbd_get_xdp_frame(tx_swbd);
		काष्ठा sk_buff *skb = enetc_tx_swbd_get_skb(tx_swbd);
		bool is_eof = tx_swbd->is_eof;

		अगर (unlikely(tx_swbd->check_wb)) अणु
			काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
			जोड़ enetc_tx_bd *txbd;

			txbd = ENETC_TXBD(*tx_ring, i);

			अगर (txbd->flags & ENETC_TXBD_FLAGS_W &&
			    tx_swbd->करो_twostep_tstamp) अणु
				enetc_get_tx_tstamp(&priv->si->hw, txbd,
						    &tstamp);
				करो_twostep_tstamp = true;
			पूर्ण
		पूर्ण

		अगर (tx_swbd->is_xdp_tx)
			enetc_recycle_xdp_tx_buff(tx_ring, tx_swbd);
		अन्यथा अगर (likely(tx_swbd->dma))
			enetc_unmap_tx_buff(tx_ring, tx_swbd);

		अगर (xdp_frame) अणु
			xdp_वापस_frame(xdp_frame);
		पूर्ण अन्यथा अगर (skb) अणु
			अगर (unlikely(tx_swbd->skb->cb[0] &
				     ENETC_F_TX_ONESTEP_SYNC_TSTAMP)) अणु
				/* Start work to release lock क्रम next one-step
				 * बारtamping packet. And send one skb in
				 * tx_skbs queue अगर has.
				 */
				schedule_work(&priv->tx_onestep_tstamp);
			पूर्ण अन्यथा अगर (unlikely(करो_twostep_tstamp)) अणु
				enetc_tstamp_tx(skb, tstamp);
				करो_twostep_tstamp = false;
			पूर्ण
			napi_consume_skb(skb, napi_budget);
		पूर्ण

		tx_byte_cnt += tx_swbd->len;
		/* Scrub the swbd here so we करोn't have to करो that
		 * when we reuse it during xmit
		 */
		स_रखो(tx_swbd, 0, माप(*tx_swbd));

		bds_to_clean--;
		tx_swbd++;
		i++;
		अगर (unlikely(i == tx_ring->bd_count)) अणु
			i = 0;
			tx_swbd = tx_ring->tx_swbd;
		पूर्ण

		/* BD iteration loop end */
		अगर (is_eof) अणु
			tx_frm_cnt++;
			/* re-arm पूर्णांकerrupt source */
			enetc_wr_reg_hot(tx_ring->idr, BIT(tx_ring->index) |
					 BIT(16 + tx_ring->index));
		पूर्ण

		अगर (unlikely(!bds_to_clean))
			bds_to_clean = enetc_bd_पढ़ोy_count(tx_ring, i);
	पूर्ण

	tx_ring->next_to_clean = i;
	tx_ring->stats.packets += tx_frm_cnt;
	tx_ring->stats.bytes += tx_byte_cnt;

	अगर (unlikely(tx_frm_cnt && netअगर_carrier_ok(ndev) &&
		     __netअगर_subqueue_stopped(ndev, tx_ring->index) &&
		     (enetc_bd_unused(tx_ring) >= ENETC_TXBDS_MAX_NEEDED))) अणु
		netअगर_wake_subqueue(ndev, tx_ring->index);
	पूर्ण

	वापस tx_frm_cnt != ENETC_DEFAULT_TX_WORK;
पूर्ण

अटल bool enetc_new_page(काष्ठा enetc_bdr *rx_ring,
			   काष्ठा enetc_rx_swbd *rx_swbd)
अणु
	bool xdp = !!(rx_ring->xdp.prog);
	काष्ठा page *page;
	dma_addr_t addr;

	page = dev_alloc_page();
	अगर (unlikely(!page))
		वापस false;

	/* For XDP_TX, we क्रमgo dma_unmap -> dma_map */
	rx_swbd->dir = xdp ? DMA_BIसूचीECTIONAL : DMA_FROM_DEVICE;

	addr = dma_map_page(rx_ring->dev, page, 0, PAGE_SIZE, rx_swbd->dir);
	अगर (unlikely(dma_mapping_error(rx_ring->dev, addr))) अणु
		__मुक्त_page(page);

		वापस false;
	पूर्ण

	rx_swbd->dma = addr;
	rx_swbd->page = page;
	rx_swbd->page_offset = rx_ring->buffer_offset;

	वापस true;
पूर्ण

अटल पूर्णांक enetc_refill_rx_ring(काष्ठा enetc_bdr *rx_ring, स्थिर पूर्णांक buff_cnt)
अणु
	काष्ठा enetc_rx_swbd *rx_swbd;
	जोड़ enetc_rx_bd *rxbd;
	पूर्णांक i, j;

	i = rx_ring->next_to_use;
	rx_swbd = &rx_ring->rx_swbd[i];
	rxbd = enetc_rxbd(rx_ring, i);

	क्रम (j = 0; j < buff_cnt; j++) अणु
		/* try reuse page */
		अगर (unlikely(!rx_swbd->page)) अणु
			अगर (unlikely(!enetc_new_page(rx_ring, rx_swbd))) अणु
				rx_ring->stats.rx_alloc_errs++;
				अवरोध;
			पूर्ण
		पूर्ण

		/* update RxBD */
		rxbd->w.addr = cpu_to_le64(rx_swbd->dma +
					   rx_swbd->page_offset);
		/* clear 'R" as well */
		rxbd->r.lstatus = 0;

		enetc_rxbd_next(rx_ring, &rxbd, &i);
		rx_swbd = &rx_ring->rx_swbd[i];
	पूर्ण

	अगर (likely(j)) अणु
		rx_ring->next_to_alloc = i; /* keep track from page reuse */
		rx_ring->next_to_use = i;

		/* update ENETC's consumer index */
		enetc_wr_reg_hot(rx_ring->rcir, rx_ring->next_to_use);
	पूर्ण

	वापस j;
पूर्ण

#अगर_घोषित CONFIG_FSL_ENETC_PTP_CLOCK
अटल व्योम enetc_get_rx_tstamp(काष्ठा net_device *ndev,
				जोड़ enetc_rx_bd *rxbd,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_hwtstamps *shhwtstamps = skb_hwtstamps(skb);
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_hw *hw = &priv->si->hw;
	u32 lo, hi, tstamp_lo;
	u64 tstamp;

	अगर (le16_to_cpu(rxbd->r.flags) & ENETC_RXBD_FLAG_TSTMP) अणु
		lo = enetc_rd_reg_hot(hw->reg + ENETC_SICTR0);
		hi = enetc_rd_reg_hot(hw->reg + ENETC_SICTR1);
		rxbd = enetc_rxbd_ext(rxbd);
		tstamp_lo = le32_to_cpu(rxbd->ext.tstamp);
		अगर (lo <= tstamp_lo)
			hi -= 1;

		tstamp = (u64)hi << 32 | tstamp_lo;
		स_रखो(shhwtstamps, 0, माप(*shhwtstamps));
		shhwtstamps->hwtstamp = ns_to_kसमय(tstamp);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम enetc_get_offloads(काष्ठा enetc_bdr *rx_ring,
			       जोड़ enetc_rx_bd *rxbd, काष्ठा sk_buff *skb)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(rx_ring->ndev);

	/* TODO: hashing */
	अगर (rx_ring->ndev->features & NETIF_F_RXCSUM) अणु
		u16 inet_csum = le16_to_cpu(rxbd->r.inet_csum);

		skb->csum = csum_unfold((__क्रमce __sum16)~htons(inet_csum));
		skb->ip_summed = CHECKSUM_COMPLETE;
	पूर्ण

	अगर (le16_to_cpu(rxbd->r.flags) & ENETC_RXBD_FLAG_VLAN) अणु
		__be16 tpid = 0;

		चयन (le16_to_cpu(rxbd->r.flags) & ENETC_RXBD_FLAG_TPID) अणु
		हाल 0:
			tpid = htons(ETH_P_8021Q);
			अवरोध;
		हाल 1:
			tpid = htons(ETH_P_8021AD);
			अवरोध;
		हाल 2:
			tpid = htons(enetc_port_rd(&priv->si->hw,
						   ENETC_PCVLANR1));
			अवरोध;
		हाल 3:
			tpid = htons(enetc_port_rd(&priv->si->hw,
						   ENETC_PCVLANR2));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		__vlan_hwaccel_put_tag(skb, tpid, le16_to_cpu(rxbd->r.vlan_opt));
	पूर्ण

#अगर_घोषित CONFIG_FSL_ENETC_PTP_CLOCK
	अगर (priv->active_offloads & ENETC_F_RX_TSTAMP)
		enetc_get_rx_tstamp(rx_ring->ndev, rxbd, skb);
#पूर्ण_अगर
पूर्ण

/* This माला_लो called during the non-XDP NAPI poll cycle as well as on XDP_PASS,
 * so it needs to work with both DMA_FROM_DEVICE as well as DMA_BIसूचीECTIONAL
 * mapped buffers.
 */
अटल काष्ठा enetc_rx_swbd *enetc_get_rx_buff(काष्ठा enetc_bdr *rx_ring,
					       पूर्णांक i, u16 size)
अणु
	काष्ठा enetc_rx_swbd *rx_swbd = &rx_ring->rx_swbd[i];

	dma_sync_single_range_क्रम_cpu(rx_ring->dev, rx_swbd->dma,
				      rx_swbd->page_offset,
				      size, rx_swbd->dir);
	वापस rx_swbd;
पूर्ण

/* Reuse the current page without perक्रमming half-page buffer flipping */
अटल व्योम enetc_put_rx_buff(काष्ठा enetc_bdr *rx_ring,
			      काष्ठा enetc_rx_swbd *rx_swbd)
अणु
	माप_प्रकार buffer_size = ENETC_RXB_TRUESIZE - rx_ring->buffer_offset;

	enetc_reuse_page(rx_ring, rx_swbd);

	dma_sync_single_range_क्रम_device(rx_ring->dev, rx_swbd->dma,
					 rx_swbd->page_offset,
					 buffer_size, rx_swbd->dir);

	rx_swbd->page = शून्य;
पूर्ण

/* Reuse the current page by perक्रमming half-page buffer flipping */
अटल व्योम enetc_flip_rx_buff(काष्ठा enetc_bdr *rx_ring,
			       काष्ठा enetc_rx_swbd *rx_swbd)
अणु
	अगर (likely(enetc_page_reusable(rx_swbd->page))) अणु
		rx_swbd->page_offset ^= ENETC_RXB_TRUESIZE;
		page_ref_inc(rx_swbd->page);

		enetc_put_rx_buff(rx_ring, rx_swbd);
	पूर्ण अन्यथा अणु
		dma_unmap_page(rx_ring->dev, rx_swbd->dma, PAGE_SIZE,
			       rx_swbd->dir);
		rx_swbd->page = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *enetc_map_rx_buff_to_skb(काष्ठा enetc_bdr *rx_ring,
						पूर्णांक i, u16 size)
अणु
	काष्ठा enetc_rx_swbd *rx_swbd = enetc_get_rx_buff(rx_ring, i, size);
	काष्ठा sk_buff *skb;
	व्योम *ba;

	ba = page_address(rx_swbd->page) + rx_swbd->page_offset;
	skb = build_skb(ba - rx_ring->buffer_offset, ENETC_RXB_TRUESIZE);
	अगर (unlikely(!skb)) अणु
		rx_ring->stats.rx_alloc_errs++;
		वापस शून्य;
	पूर्ण

	skb_reserve(skb, rx_ring->buffer_offset);
	__skb_put(skb, size);

	enetc_flip_rx_buff(rx_ring, rx_swbd);

	वापस skb;
पूर्ण

अटल व्योम enetc_add_rx_buff_to_skb(काष्ठा enetc_bdr *rx_ring, पूर्णांक i,
				     u16 size, काष्ठा sk_buff *skb)
अणु
	काष्ठा enetc_rx_swbd *rx_swbd = enetc_get_rx_buff(rx_ring, i, size);

	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, rx_swbd->page,
			rx_swbd->page_offset, size, ENETC_RXB_TRUESIZE);

	enetc_flip_rx_buff(rx_ring, rx_swbd);
पूर्ण

अटल bool enetc_check_bd_errors_and_consume(काष्ठा enetc_bdr *rx_ring,
					      u32 bd_status,
					      जोड़ enetc_rx_bd **rxbd, पूर्णांक *i)
अणु
	अगर (likely(!(bd_status & ENETC_RXBD_LSTATUS(ENETC_RXBD_ERR_MASK))))
		वापस false;

	enetc_put_rx_buff(rx_ring, &rx_ring->rx_swbd[*i]);
	enetc_rxbd_next(rx_ring, rxbd, i);

	जबतक (!(bd_status & ENETC_RXBD_LSTATUS_F)) अणु
		dma_rmb();
		bd_status = le32_to_cpu((*rxbd)->r.lstatus);

		enetc_put_rx_buff(rx_ring, &rx_ring->rx_swbd[*i]);
		enetc_rxbd_next(rx_ring, rxbd, i);
	पूर्ण

	rx_ring->ndev->stats.rx_dropped++;
	rx_ring->ndev->stats.rx_errors++;

	वापस true;
पूर्ण

अटल काष्ठा sk_buff *enetc_build_skb(काष्ठा enetc_bdr *rx_ring,
				       u32 bd_status, जोड़ enetc_rx_bd **rxbd,
				       पूर्णांक *i, पूर्णांक *cleaned_cnt, पूर्णांक buffer_size)
अणु
	काष्ठा sk_buff *skb;
	u16 size;

	size = le16_to_cpu((*rxbd)->r.buf_len);
	skb = enetc_map_rx_buff_to_skb(rx_ring, *i, size);
	अगर (!skb)
		वापस शून्य;

	enetc_get_offloads(rx_ring, *rxbd, skb);

	(*cleaned_cnt)++;

	enetc_rxbd_next(rx_ring, rxbd, i);

	/* not last BD in frame? */
	जबतक (!(bd_status & ENETC_RXBD_LSTATUS_F)) अणु
		bd_status = le32_to_cpu((*rxbd)->r.lstatus);
		size = buffer_size;

		अगर (bd_status & ENETC_RXBD_LSTATUS_F) अणु
			dma_rmb();
			size = le16_to_cpu((*rxbd)->r.buf_len);
		पूर्ण

		enetc_add_rx_buff_to_skb(rx_ring, *i, size, skb);

		(*cleaned_cnt)++;

		enetc_rxbd_next(rx_ring, rxbd, i);
	पूर्ण

	skb_record_rx_queue(skb, rx_ring->index);
	skb->protocol = eth_type_trans(skb, rx_ring->ndev);

	वापस skb;
पूर्ण

#घोषणा ENETC_RXBD_BUNDLE 16 /* # of BDs to update at once */

अटल पूर्णांक enetc_clean_rx_ring(काष्ठा enetc_bdr *rx_ring,
			       काष्ठा napi_काष्ठा *napi, पूर्णांक work_limit)
अणु
	पूर्णांक rx_frm_cnt = 0, rx_byte_cnt = 0;
	पूर्णांक cleaned_cnt, i;

	cleaned_cnt = enetc_bd_unused(rx_ring);
	/* next descriptor to process */
	i = rx_ring->next_to_clean;

	जबतक (likely(rx_frm_cnt < work_limit)) अणु
		जोड़ enetc_rx_bd *rxbd;
		काष्ठा sk_buff *skb;
		u32 bd_status;

		अगर (cleaned_cnt >= ENETC_RXBD_BUNDLE)
			cleaned_cnt -= enetc_refill_rx_ring(rx_ring,
							    cleaned_cnt);

		rxbd = enetc_rxbd(rx_ring, i);
		bd_status = le32_to_cpu(rxbd->r.lstatus);
		अगर (!bd_status)
			अवरोध;

		enetc_wr_reg_hot(rx_ring->idr, BIT(rx_ring->index));
		dma_rmb(); /* क्रम पढ़ोing other rxbd fields */

		अगर (enetc_check_bd_errors_and_consume(rx_ring, bd_status,
						      &rxbd, &i))
			अवरोध;

		skb = enetc_build_skb(rx_ring, bd_status, &rxbd, &i,
				      &cleaned_cnt, ENETC_RXB_DMA_SIZE);
		अगर (!skb)
			अवरोध;

		rx_byte_cnt += skb->len;
		rx_frm_cnt++;

		napi_gro_receive(napi, skb);
	पूर्ण

	rx_ring->next_to_clean = i;

	rx_ring->stats.packets += rx_frm_cnt;
	rx_ring->stats.bytes += rx_byte_cnt;

	वापस rx_frm_cnt;
पूर्ण

अटल व्योम enetc_xdp_map_tx_buff(काष्ठा enetc_bdr *tx_ring, पूर्णांक i,
				  काष्ठा enetc_tx_swbd *tx_swbd,
				  पूर्णांक frm_len)
अणु
	जोड़ enetc_tx_bd *txbd = ENETC_TXBD(*tx_ring, i);

	prefetchw(txbd);

	enetc_clear_tx_bd(txbd);
	txbd->addr = cpu_to_le64(tx_swbd->dma + tx_swbd->page_offset);
	txbd->buf_len = cpu_to_le16(tx_swbd->len);
	txbd->frm_len = cpu_to_le16(frm_len);

	स_नकल(&tx_ring->tx_swbd[i], tx_swbd, माप(*tx_swbd));
पूर्ण

/* Puts in the TX ring one XDP frame, mapped as an array of TX software buffer
 * descriptors.
 */
अटल bool enetc_xdp_tx(काष्ठा enetc_bdr *tx_ring,
			 काष्ठा enetc_tx_swbd *xdp_tx_arr, पूर्णांक num_tx_swbd)
अणु
	काष्ठा enetc_tx_swbd *पंचांगp_tx_swbd = xdp_tx_arr;
	पूर्णांक i, k, frm_len = पंचांगp_tx_swbd->len;

	अगर (unlikely(enetc_bd_unused(tx_ring) < ENETC_TXBDS_NEEDED(num_tx_swbd)))
		वापस false;

	जबतक (unlikely(!पंचांगp_tx_swbd->is_eof)) अणु
		पंचांगp_tx_swbd++;
		frm_len += पंचांगp_tx_swbd->len;
	पूर्ण

	i = tx_ring->next_to_use;

	क्रम (k = 0; k < num_tx_swbd; k++) अणु
		काष्ठा enetc_tx_swbd *xdp_tx_swbd = &xdp_tx_arr[k];

		enetc_xdp_map_tx_buff(tx_ring, i, xdp_tx_swbd, frm_len);

		/* last BD needs 'F' bit set */
		अगर (xdp_tx_swbd->is_eof) अणु
			जोड़ enetc_tx_bd *txbd = ENETC_TXBD(*tx_ring, i);

			txbd->flags = ENETC_TXBD_FLAGS_F;
		पूर्ण

		enetc_bdr_idx_inc(tx_ring, &i);
	पूर्ण

	tx_ring->next_to_use = i;

	वापस true;
पूर्ण

अटल पूर्णांक enetc_xdp_frame_to_xdp_tx_swbd(काष्ठा enetc_bdr *tx_ring,
					  काष्ठा enetc_tx_swbd *xdp_tx_arr,
					  काष्ठा xdp_frame *xdp_frame)
अणु
	काष्ठा enetc_tx_swbd *xdp_tx_swbd = &xdp_tx_arr[0];
	काष्ठा skb_shared_info *shinfo;
	व्योम *data = xdp_frame->data;
	पूर्णांक len = xdp_frame->len;
	skb_frag_t *frag;
	dma_addr_t dma;
	अचिन्हित पूर्णांक f;
	पूर्णांक n = 0;

	dma = dma_map_single(tx_ring->dev, data, len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(tx_ring->dev, dma))) अणु
		netdev_err(tx_ring->ndev, "DMA map error\n");
		वापस -1;
	पूर्ण

	xdp_tx_swbd->dma = dma;
	xdp_tx_swbd->dir = DMA_TO_DEVICE;
	xdp_tx_swbd->len = len;
	xdp_tx_swbd->is_xdp_redirect = true;
	xdp_tx_swbd->is_eof = false;
	xdp_tx_swbd->xdp_frame = शून्य;

	n++;
	xdp_tx_swbd = &xdp_tx_arr[n];

	shinfo = xdp_get_shared_info_from_frame(xdp_frame);

	क्रम (f = 0, frag = &shinfo->frags[0]; f < shinfo->nr_frags;
	     f++, frag++) अणु
		data = skb_frag_address(frag);
		len = skb_frag_size(frag);

		dma = dma_map_single(tx_ring->dev, data, len, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(tx_ring->dev, dma))) अणु
			/* Unकरो the DMA mapping क्रम all fragments */
			जबतक (--n >= 0)
				enetc_unmap_tx_buff(tx_ring, &xdp_tx_arr[n]);

			netdev_err(tx_ring->ndev, "DMA map error\n");
			वापस -1;
		पूर्ण

		xdp_tx_swbd->dma = dma;
		xdp_tx_swbd->dir = DMA_TO_DEVICE;
		xdp_tx_swbd->len = len;
		xdp_tx_swbd->is_xdp_redirect = true;
		xdp_tx_swbd->is_eof = false;
		xdp_tx_swbd->xdp_frame = शून्य;

		n++;
		xdp_tx_swbd = &xdp_tx_arr[n];
	पूर्ण

	xdp_tx_arr[n - 1].is_eof = true;
	xdp_tx_arr[n - 1].xdp_frame = xdp_frame;

	वापस n;
पूर्ण

पूर्णांक enetc_xdp_xmit(काष्ठा net_device *ndev, पूर्णांक num_frames,
		   काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा enetc_tx_swbd xdp_redirect_arr[ENETC_MAX_SKB_FRAGS] = अणु0पूर्ण;
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_bdr *tx_ring;
	पूर्णांक xdp_tx_bd_cnt, i, k;
	पूर्णांक xdp_tx_frm_cnt = 0;

	enetc_lock_mdio();

	tx_ring = priv->xdp_tx_ring[smp_processor_id()];

	prefetchw(ENETC_TXBD(*tx_ring, tx_ring->next_to_use));

	क्रम (k = 0; k < num_frames; k++) अणु
		xdp_tx_bd_cnt = enetc_xdp_frame_to_xdp_tx_swbd(tx_ring,
							       xdp_redirect_arr,
							       frames[k]);
		अगर (unlikely(xdp_tx_bd_cnt < 0))
			अवरोध;

		अगर (unlikely(!enetc_xdp_tx(tx_ring, xdp_redirect_arr,
					   xdp_tx_bd_cnt))) अणु
			क्रम (i = 0; i < xdp_tx_bd_cnt; i++)
				enetc_unmap_tx_buff(tx_ring,
						    &xdp_redirect_arr[i]);
			tx_ring->stats.xdp_tx_drops++;
			अवरोध;
		पूर्ण

		xdp_tx_frm_cnt++;
	पूर्ण

	अगर (unlikely((flags & XDP_XMIT_FLUSH) || k != xdp_tx_frm_cnt))
		enetc_update_tx_ring_tail(tx_ring);

	tx_ring->stats.xdp_tx += xdp_tx_frm_cnt;

	enetc_unlock_mdio();

	वापस xdp_tx_frm_cnt;
पूर्ण

अटल व्योम enetc_map_rx_buff_to_xdp(काष्ठा enetc_bdr *rx_ring, पूर्णांक i,
				     काष्ठा xdp_buff *xdp_buff, u16 size)
अणु
	काष्ठा enetc_rx_swbd *rx_swbd = enetc_get_rx_buff(rx_ring, i, size);
	व्योम *hard_start = page_address(rx_swbd->page) + rx_swbd->page_offset;
	काष्ठा skb_shared_info *shinfo;

	/* To be used क्रम XDP_TX */
	rx_swbd->len = size;

	xdp_prepare_buff(xdp_buff, hard_start - rx_ring->buffer_offset,
			 rx_ring->buffer_offset, size, false);

	shinfo = xdp_get_shared_info_from_buff(xdp_buff);
	shinfo->nr_frags = 0;
पूर्ण

अटल व्योम enetc_add_rx_buff_to_xdp(काष्ठा enetc_bdr *rx_ring, पूर्णांक i,
				     u16 size, काष्ठा xdp_buff *xdp_buff)
अणु
	काष्ठा skb_shared_info *shinfo = xdp_get_shared_info_from_buff(xdp_buff);
	काष्ठा enetc_rx_swbd *rx_swbd = enetc_get_rx_buff(rx_ring, i, size);
	skb_frag_t *frag = &shinfo->frags[shinfo->nr_frags];

	/* To be used क्रम XDP_TX */
	rx_swbd->len = size;

	skb_frag_off_set(frag, rx_swbd->page_offset);
	skb_frag_size_set(frag, size);
	__skb_frag_set_page(frag, rx_swbd->page);

	shinfo->nr_frags++;
पूर्ण

अटल व्योम enetc_build_xdp_buff(काष्ठा enetc_bdr *rx_ring, u32 bd_status,
				 जोड़ enetc_rx_bd **rxbd, पूर्णांक *i,
				 पूर्णांक *cleaned_cnt, काष्ठा xdp_buff *xdp_buff)
अणु
	u16 size = le16_to_cpu((*rxbd)->r.buf_len);

	xdp_init_buff(xdp_buff, ENETC_RXB_TRUESIZE, &rx_ring->xdp.rxq);

	enetc_map_rx_buff_to_xdp(rx_ring, *i, xdp_buff, size);
	(*cleaned_cnt)++;
	enetc_rxbd_next(rx_ring, rxbd, i);

	/* not last BD in frame? */
	जबतक (!(bd_status & ENETC_RXBD_LSTATUS_F)) अणु
		bd_status = le32_to_cpu((*rxbd)->r.lstatus);
		size = ENETC_RXB_DMA_SIZE_XDP;

		अगर (bd_status & ENETC_RXBD_LSTATUS_F) अणु
			dma_rmb();
			size = le16_to_cpu((*rxbd)->r.buf_len);
		पूर्ण

		enetc_add_rx_buff_to_xdp(rx_ring, *i, size, xdp_buff);
		(*cleaned_cnt)++;
		enetc_rxbd_next(rx_ring, rxbd, i);
	पूर्ण
पूर्ण

/* Convert RX buffer descriptors to TX buffer descriptors. These will be
 * recycled back पूर्णांकo the RX ring in enetc_clean_tx_ring.
 */
अटल पूर्णांक enetc_rx_swbd_to_xdp_tx_swbd(काष्ठा enetc_tx_swbd *xdp_tx_arr,
					काष्ठा enetc_bdr *rx_ring,
					पूर्णांक rx_ring_first, पूर्णांक rx_ring_last)
अणु
	पूर्णांक n = 0;

	क्रम (; rx_ring_first != rx_ring_last;
	     n++, enetc_bdr_idx_inc(rx_ring, &rx_ring_first)) अणु
		काष्ठा enetc_rx_swbd *rx_swbd = &rx_ring->rx_swbd[rx_ring_first];
		काष्ठा enetc_tx_swbd *tx_swbd = &xdp_tx_arr[n];

		/* No need to dma_map, we alपढ़ोy have DMA_BIसूचीECTIONAL */
		tx_swbd->dma = rx_swbd->dma;
		tx_swbd->dir = rx_swbd->dir;
		tx_swbd->page = rx_swbd->page;
		tx_swbd->page_offset = rx_swbd->page_offset;
		tx_swbd->len = rx_swbd->len;
		tx_swbd->is_dma_page = true;
		tx_swbd->is_xdp_tx = true;
		tx_swbd->is_eof = false;
	पूर्ण

	/* We rely on caller providing an rx_ring_last > rx_ring_first */
	xdp_tx_arr[n - 1].is_eof = true;

	वापस n;
पूर्ण

अटल व्योम enetc_xdp_drop(काष्ठा enetc_bdr *rx_ring, पूर्णांक rx_ring_first,
			   पूर्णांक rx_ring_last)
अणु
	जबतक (rx_ring_first != rx_ring_last) अणु
		enetc_put_rx_buff(rx_ring,
				  &rx_ring->rx_swbd[rx_ring_first]);
		enetc_bdr_idx_inc(rx_ring, &rx_ring_first);
	पूर्ण
	rx_ring->stats.xdp_drops++;
पूर्ण

अटल व्योम enetc_xdp_मुक्त(काष्ठा enetc_bdr *rx_ring, पूर्णांक rx_ring_first,
			   पूर्णांक rx_ring_last)
अणु
	जबतक (rx_ring_first != rx_ring_last) अणु
		काष्ठा enetc_rx_swbd *rx_swbd = &rx_ring->rx_swbd[rx_ring_first];

		अगर (rx_swbd->page) अणु
			dma_unmap_page(rx_ring->dev, rx_swbd->dma, PAGE_SIZE,
				       rx_swbd->dir);
			__मुक्त_page(rx_swbd->page);
			rx_swbd->page = शून्य;
		पूर्ण
		enetc_bdr_idx_inc(rx_ring, &rx_ring_first);
	पूर्ण
	rx_ring->stats.xdp_redirect_failures++;
पूर्ण

अटल पूर्णांक enetc_clean_rx_ring_xdp(काष्ठा enetc_bdr *rx_ring,
				   काष्ठा napi_काष्ठा *napi, पूर्णांक work_limit,
				   काष्ठा bpf_prog *prog)
अणु
	पूर्णांक xdp_tx_bd_cnt, xdp_tx_frm_cnt = 0, xdp_redirect_frm_cnt = 0;
	काष्ठा enetc_tx_swbd xdp_tx_arr[ENETC_MAX_SKB_FRAGS] = अणु0पूर्ण;
	काष्ठा enetc_ndev_priv *priv = netdev_priv(rx_ring->ndev);
	पूर्णांक rx_frm_cnt = 0, rx_byte_cnt = 0;
	काष्ठा enetc_bdr *tx_ring;
	पूर्णांक cleaned_cnt, i;
	u32 xdp_act;

	cleaned_cnt = enetc_bd_unused(rx_ring);
	/* next descriptor to process */
	i = rx_ring->next_to_clean;

	जबतक (likely(rx_frm_cnt < work_limit)) अणु
		जोड़ enetc_rx_bd *rxbd, *orig_rxbd;
		पूर्णांक orig_i, orig_cleaned_cnt;
		काष्ठा xdp_buff xdp_buff;
		काष्ठा sk_buff *skb;
		पूर्णांक पंचांगp_orig_i, err;
		u32 bd_status;

		rxbd = enetc_rxbd(rx_ring, i);
		bd_status = le32_to_cpu(rxbd->r.lstatus);
		अगर (!bd_status)
			अवरोध;

		enetc_wr_reg_hot(rx_ring->idr, BIT(rx_ring->index));
		dma_rmb(); /* क्रम पढ़ोing other rxbd fields */

		अगर (enetc_check_bd_errors_and_consume(rx_ring, bd_status,
						      &rxbd, &i))
			अवरोध;

		orig_rxbd = rxbd;
		orig_cleaned_cnt = cleaned_cnt;
		orig_i = i;

		enetc_build_xdp_buff(rx_ring, bd_status, &rxbd, &i,
				     &cleaned_cnt, &xdp_buff);

		xdp_act = bpf_prog_run_xdp(prog, &xdp_buff);

		चयन (xdp_act) अणु
		शेष:
			bpf_warn_invalid_xdp_action(xdp_act);
			fallthrough;
		हाल XDP_ABORTED:
			trace_xdp_exception(rx_ring->ndev, prog, xdp_act);
			fallthrough;
		हाल XDP_DROP:
			enetc_xdp_drop(rx_ring, orig_i, i);
			अवरोध;
		हाल XDP_PASS:
			rxbd = orig_rxbd;
			cleaned_cnt = orig_cleaned_cnt;
			i = orig_i;

			skb = enetc_build_skb(rx_ring, bd_status, &rxbd,
					      &i, &cleaned_cnt,
					      ENETC_RXB_DMA_SIZE_XDP);
			अगर (unlikely(!skb))
				जाओ out;

			napi_gro_receive(napi, skb);
			अवरोध;
		हाल XDP_TX:
			tx_ring = priv->xdp_tx_ring[rx_ring->index];
			xdp_tx_bd_cnt = enetc_rx_swbd_to_xdp_tx_swbd(xdp_tx_arr,
								     rx_ring,
								     orig_i, i);

			अगर (!enetc_xdp_tx(tx_ring, xdp_tx_arr, xdp_tx_bd_cnt)) अणु
				enetc_xdp_drop(rx_ring, orig_i, i);
				tx_ring->stats.xdp_tx_drops++;
			पूर्ण अन्यथा अणु
				tx_ring->stats.xdp_tx += xdp_tx_bd_cnt;
				rx_ring->xdp.xdp_tx_in_flight += xdp_tx_bd_cnt;
				xdp_tx_frm_cnt++;
				/* The XDP_TX enqueue was successful, so we
				 * need to scrub the RX software BDs because
				 * the ownership of the buffers no दीर्घer
				 * beदीर्घs to the RX ring, and we must prevent
				 * enetc_refill_rx_ring() from reusing
				 * rx_swbd->page.
				 */
				जबतक (orig_i != i) अणु
					rx_ring->rx_swbd[orig_i].page = शून्य;
					enetc_bdr_idx_inc(rx_ring, &orig_i);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल XDP_REसूचीECT:
			/* xdp_वापस_frame करोes not support S/G in the sense
			 * that it leaks the fragments (__xdp_वापस should not
			 * call page_frag_मुक्त only क्रम the initial buffer).
			 * Until XDP_REसूचीECT gains support क्रम S/G let's keep
			 * the code काष्ठाure in place, but dead. We drop the
			 * S/G frames ourselves to aव्योम memory leaks which
			 * would otherwise leave the kernel OOM.
			 */
			अगर (unlikely(cleaned_cnt - orig_cleaned_cnt != 1)) अणु
				enetc_xdp_drop(rx_ring, orig_i, i);
				rx_ring->stats.xdp_redirect_sg++;
				अवरोध;
			पूर्ण

			पंचांगp_orig_i = orig_i;

			जबतक (orig_i != i) अणु
				enetc_flip_rx_buff(rx_ring,
						   &rx_ring->rx_swbd[orig_i]);
				enetc_bdr_idx_inc(rx_ring, &orig_i);
			पूर्ण

			err = xdp_करो_redirect(rx_ring->ndev, &xdp_buff, prog);
			अगर (unlikely(err)) अणु
				enetc_xdp_मुक्त(rx_ring, पंचांगp_orig_i, i);
			पूर्ण अन्यथा अणु
				xdp_redirect_frm_cnt++;
				rx_ring->stats.xdp_redirect++;
			पूर्ण
		पूर्ण

		rx_frm_cnt++;
	पूर्ण

out:
	rx_ring->next_to_clean = i;

	rx_ring->stats.packets += rx_frm_cnt;
	rx_ring->stats.bytes += rx_byte_cnt;

	अगर (xdp_redirect_frm_cnt)
		xdp_करो_flush_map();

	अगर (xdp_tx_frm_cnt)
		enetc_update_tx_ring_tail(tx_ring);

	अगर (cleaned_cnt > rx_ring->xdp.xdp_tx_in_flight)
		enetc_refill_rx_ring(rx_ring, enetc_bd_unused(rx_ring) -
				     rx_ring->xdp.xdp_tx_in_flight);

	वापस rx_frm_cnt;
पूर्ण

अटल पूर्णांक enetc_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा enetc_पूर्णांक_vector
		*v = container_of(napi, काष्ठा enetc_पूर्णांक_vector, napi);
	काष्ठा enetc_bdr *rx_ring = &v->rx_ring;
	काष्ठा bpf_prog *prog;
	bool complete = true;
	पूर्णांक work_करोne;
	पूर्णांक i;

	enetc_lock_mdio();

	क्रम (i = 0; i < v->count_tx_rings; i++)
		अगर (!enetc_clean_tx_ring(&v->tx_ring[i], budget))
			complete = false;

	prog = rx_ring->xdp.prog;
	अगर (prog)
		work_करोne = enetc_clean_rx_ring_xdp(rx_ring, napi, budget, prog);
	अन्यथा
		work_करोne = enetc_clean_rx_ring(rx_ring, napi, budget);
	अगर (work_करोne == budget)
		complete = false;
	अगर (work_करोne)
		v->rx_napi_work = true;

	अगर (!complete) अणु
		enetc_unlock_mdio();
		वापस budget;
	पूर्ण

	napi_complete_करोne(napi, work_करोne);

	अगर (likely(v->rx_dim_en))
		enetc_rx_net_dim(v);

	v->rx_napi_work = false;

	/* enable पूर्णांकerrupts */
	enetc_wr_reg_hot(v->rbier, ENETC_RBIER_RXTIE);

	क्रम_each_set_bit(i, &v->tx_rings_map, ENETC_MAX_NUM_TXQS)
		enetc_wr_reg_hot(v->tbier_base + ENETC_BDR_OFF(i),
				 ENETC_TBIER_TXTIE);

	enetc_unlock_mdio();

	वापस work_करोne;
पूर्ण

/* Probing and Init */
#घोषणा ENETC_MAX_RFS_SIZE 64
व्योम enetc_get_si_caps(काष्ठा enetc_si *si)
अणु
	काष्ठा enetc_hw *hw = &si->hw;
	u32 val;

	/* find out how many of various resources we have to work with */
	val = enetc_rd(hw, ENETC_SICAPR0);
	si->num_rx_rings = (val >> 16) & 0xff;
	si->num_tx_rings = val & 0xff;

	val = enetc_rd(hw, ENETC_SIRFSCAPR);
	si->num_fs_entries = ENETC_SIRFSCAPR_GET_NUM_RFS(val);
	si->num_fs_entries = min(si->num_fs_entries, ENETC_MAX_RFS_SIZE);

	si->num_rss = 0;
	val = enetc_rd(hw, ENETC_SIPCAPR0);
	अगर (val & ENETC_SIPCAPR0_RSS) अणु
		u32 rss;

		rss = enetc_rd(hw, ENETC_SIRSSCAPR);
		si->num_rss = ENETC_SIRSSCAPR_GET_NUM_RSS(rss);
	पूर्ण

	अगर (val & ENETC_SIPCAPR0_QBV)
		si->hw_features |= ENETC_SI_F_QBV;

	अगर (val & ENETC_SIPCAPR0_PSFP)
		si->hw_features |= ENETC_SI_F_PSFP;
पूर्ण

अटल पूर्णांक enetc_dma_alloc_bdr(काष्ठा enetc_bdr *r, माप_प्रकार bd_size)
अणु
	r->bd_base = dma_alloc_coherent(r->dev, r->bd_count * bd_size,
					&r->bd_dma_base, GFP_KERNEL);
	अगर (!r->bd_base)
		वापस -ENOMEM;

	/* h/w requires 128B alignment */
	अगर (!IS_ALIGNED(r->bd_dma_base, 128)) अणु
		dma_मुक्त_coherent(r->dev, r->bd_count * bd_size, r->bd_base,
				  r->bd_dma_base);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_alloc_txbdr(काष्ठा enetc_bdr *txr)
अणु
	पूर्णांक err;

	txr->tx_swbd = vzalloc(txr->bd_count * माप(काष्ठा enetc_tx_swbd));
	अगर (!txr->tx_swbd)
		वापस -ENOMEM;

	err = enetc_dma_alloc_bdr(txr, माप(जोड़ enetc_tx_bd));
	अगर (err) अणु
		vमुक्त(txr->tx_swbd);
		वापस err;
	पूर्ण

	txr->next_to_clean = 0;
	txr->next_to_use = 0;

	वापस 0;
पूर्ण

अटल व्योम enetc_मुक्त_txbdr(काष्ठा enetc_bdr *txr)
अणु
	पूर्णांक size, i;

	क्रम (i = 0; i < txr->bd_count; i++)
		enetc_मुक्त_tx_frame(txr, &txr->tx_swbd[i]);

	size = txr->bd_count * माप(जोड़ enetc_tx_bd);

	dma_मुक्त_coherent(txr->dev, size, txr->bd_base, txr->bd_dma_base);
	txr->bd_base = शून्य;

	vमुक्त(txr->tx_swbd);
	txr->tx_swbd = शून्य;
पूर्ण

अटल पूर्णांक enetc_alloc_tx_resources(काष्ठा enetc_ndev_priv *priv)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < priv->num_tx_rings; i++) अणु
		err = enetc_alloc_txbdr(priv->tx_ring[i]);

		अगर (err)
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	जबतक (i-- > 0)
		enetc_मुक्त_txbdr(priv->tx_ring[i]);

	वापस err;
पूर्ण

अटल व्योम enetc_मुक्त_tx_resources(काष्ठा enetc_ndev_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_tx_rings; i++)
		enetc_मुक्त_txbdr(priv->tx_ring[i]);
पूर्ण

अटल पूर्णांक enetc_alloc_rxbdr(काष्ठा enetc_bdr *rxr, bool extended)
अणु
	माप_प्रकार size = माप(जोड़ enetc_rx_bd);
	पूर्णांक err;

	rxr->rx_swbd = vzalloc(rxr->bd_count * माप(काष्ठा enetc_rx_swbd));
	अगर (!rxr->rx_swbd)
		वापस -ENOMEM;

	अगर (extended)
		size *= 2;

	err = enetc_dma_alloc_bdr(rxr, size);
	अगर (err) अणु
		vमुक्त(rxr->rx_swbd);
		वापस err;
	पूर्ण

	rxr->next_to_clean = 0;
	rxr->next_to_use = 0;
	rxr->next_to_alloc = 0;
	rxr->ext_en = extended;

	वापस 0;
पूर्ण

अटल व्योम enetc_मुक्त_rxbdr(काष्ठा enetc_bdr *rxr)
अणु
	पूर्णांक size;

	size = rxr->bd_count * माप(जोड़ enetc_rx_bd);

	dma_मुक्त_coherent(rxr->dev, size, rxr->bd_base, rxr->bd_dma_base);
	rxr->bd_base = शून्य;

	vमुक्त(rxr->rx_swbd);
	rxr->rx_swbd = शून्य;
पूर्ण

अटल पूर्णांक enetc_alloc_rx_resources(काष्ठा enetc_ndev_priv *priv)
अणु
	bool extended = !!(priv->active_offloads & ENETC_F_RX_TSTAMP);
	पूर्णांक i, err;

	क्रम (i = 0; i < priv->num_rx_rings; i++) अणु
		err = enetc_alloc_rxbdr(priv->rx_ring[i], extended);

		अगर (err)
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	जबतक (i-- > 0)
		enetc_मुक्त_rxbdr(priv->rx_ring[i]);

	वापस err;
पूर्ण

अटल व्योम enetc_मुक्त_rx_resources(काष्ठा enetc_ndev_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_rx_rings; i++)
		enetc_मुक्त_rxbdr(priv->rx_ring[i]);
पूर्ण

अटल व्योम enetc_मुक्त_tx_ring(काष्ठा enetc_bdr *tx_ring)
अणु
	पूर्णांक i;

	अगर (!tx_ring->tx_swbd)
		वापस;

	क्रम (i = 0; i < tx_ring->bd_count; i++) अणु
		काष्ठा enetc_tx_swbd *tx_swbd = &tx_ring->tx_swbd[i];

		enetc_मुक्त_tx_frame(tx_ring, tx_swbd);
	पूर्ण

	tx_ring->next_to_clean = 0;
	tx_ring->next_to_use = 0;
पूर्ण

अटल व्योम enetc_मुक्त_rx_ring(काष्ठा enetc_bdr *rx_ring)
अणु
	पूर्णांक i;

	अगर (!rx_ring->rx_swbd)
		वापस;

	क्रम (i = 0; i < rx_ring->bd_count; i++) अणु
		काष्ठा enetc_rx_swbd *rx_swbd = &rx_ring->rx_swbd[i];

		अगर (!rx_swbd->page)
			जारी;

		dma_unmap_page(rx_ring->dev, rx_swbd->dma, PAGE_SIZE,
			       rx_swbd->dir);
		__मुक्त_page(rx_swbd->page);
		rx_swbd->page = शून्य;
	पूर्ण

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
	rx_ring->next_to_alloc = 0;
पूर्ण

अटल व्योम enetc_मुक्त_rxtx_rings(काष्ठा enetc_ndev_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_rx_rings; i++)
		enetc_मुक्त_rx_ring(priv->rx_ring[i]);

	क्रम (i = 0; i < priv->num_tx_rings; i++)
		enetc_मुक्त_tx_ring(priv->tx_ring[i]);
पूर्ण

अटल पूर्णांक enetc_setup_शेष_rss_table(काष्ठा enetc_si *si, पूर्णांक num_groups)
अणु
	पूर्णांक *rss_table;
	पूर्णांक i;

	rss_table = kदो_स्मृति_array(si->num_rss, माप(*rss_table), GFP_KERNEL);
	अगर (!rss_table)
		वापस -ENOMEM;

	/* Set up RSS table शेषs */
	क्रम (i = 0; i < si->num_rss; i++)
		rss_table[i] = i % num_groups;

	enetc_set_rss_table(si, rss_table, si->num_rss);

	kमुक्त(rss_table);

	वापस 0;
पूर्ण

पूर्णांक enetc_configure_si(काष्ठा enetc_ndev_priv *priv)
अणु
	काष्ठा enetc_si *si = priv->si;
	काष्ठा enetc_hw *hw = &si->hw;
	पूर्णांक err;

	/* set SI cache attributes */
	enetc_wr(hw, ENETC_SICAR0,
		 ENETC_SICAR_RD_COHERENT | ENETC_SICAR_WR_COHERENT);
	enetc_wr(hw, ENETC_SICAR1, ENETC_SICAR_MSI);
	/* enable SI */
	enetc_wr(hw, ENETC_SIMR, ENETC_SIMR_EN);

	अगर (si->num_rss) अणु
		err = enetc_setup_शेष_rss_table(si, priv->num_rx_rings);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम enetc_init_si_rings_params(काष्ठा enetc_ndev_priv *priv)
अणु
	काष्ठा enetc_si *si = priv->si;
	पूर्णांक cpus = num_online_cpus();

	priv->tx_bd_count = ENETC_TX_RING_DEFAULT_SIZE;
	priv->rx_bd_count = ENETC_RX_RING_DEFAULT_SIZE;

	/* Enable all available TX rings in order to configure as many
	 * priorities as possible, when needed.
	 * TODO: Make # of TX rings run-समय configurable
	 */
	priv->num_rx_rings = min_t(पूर्णांक, cpus, si->num_rx_rings);
	priv->num_tx_rings = si->num_tx_rings;
	priv->bdr_पूर्णांक_num = cpus;
	priv->ic_mode = ENETC_IC_RX_ADAPTIVE | ENETC_IC_TX_MANUAL;
	priv->tx_ictt = ENETC_TXIC_TIMETHR;
पूर्ण

पूर्णांक enetc_alloc_si_resources(काष्ठा enetc_ndev_priv *priv)
अणु
	काष्ठा enetc_si *si = priv->si;

	priv->cls_rules = kसुस्मृति(si->num_fs_entries, माप(*priv->cls_rules),
				  GFP_KERNEL);
	अगर (!priv->cls_rules)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम enetc_मुक्त_si_resources(काष्ठा enetc_ndev_priv *priv)
अणु
	kमुक्त(priv->cls_rules);
पूर्ण

अटल व्योम enetc_setup_txbdr(काष्ठा enetc_hw *hw, काष्ठा enetc_bdr *tx_ring)
अणु
	पूर्णांक idx = tx_ring->index;
	u32 tbmr;

	enetc_txbdr_wr(hw, idx, ENETC_TBBAR0,
		       lower_32_bits(tx_ring->bd_dma_base));

	enetc_txbdr_wr(hw, idx, ENETC_TBBAR1,
		       upper_32_bits(tx_ring->bd_dma_base));

	WARN_ON(!IS_ALIGNED(tx_ring->bd_count, 64)); /* multiple of 64 */
	enetc_txbdr_wr(hw, idx, ENETC_TBLENR,
		       ENETC_RTBLENR_LEN(tx_ring->bd_count));

	/* clearing PI/CI रेजिस्टरs क्रम Tx not supported, adjust sw indexes */
	tx_ring->next_to_use = enetc_txbdr_rd(hw, idx, ENETC_TBPIR);
	tx_ring->next_to_clean = enetc_txbdr_rd(hw, idx, ENETC_TBCIR);

	/* enable Tx पूर्णांकs by setting pkt thr to 1 */
	enetc_txbdr_wr(hw, idx, ENETC_TBICR0, ENETC_TBICR0_ICEN | 0x1);

	tbmr = ENETC_TBMR_EN;
	अगर (tx_ring->ndev->features & NETIF_F_HW_VLAN_CTAG_TX)
		tbmr |= ENETC_TBMR_VIH;

	/* enable ring */
	enetc_txbdr_wr(hw, idx, ENETC_TBMR, tbmr);

	tx_ring->tpir = hw->reg + ENETC_BDR(TX, idx, ENETC_TBPIR);
	tx_ring->tcir = hw->reg + ENETC_BDR(TX, idx, ENETC_TBCIR);
	tx_ring->idr = hw->reg + ENETC_SITXIDR;
पूर्ण

अटल व्योम enetc_setup_rxbdr(काष्ठा enetc_hw *hw, काष्ठा enetc_bdr *rx_ring)
अणु
	पूर्णांक idx = rx_ring->index;
	u32 rbmr;

	enetc_rxbdr_wr(hw, idx, ENETC_RBBAR0,
		       lower_32_bits(rx_ring->bd_dma_base));

	enetc_rxbdr_wr(hw, idx, ENETC_RBBAR1,
		       upper_32_bits(rx_ring->bd_dma_base));

	WARN_ON(!IS_ALIGNED(rx_ring->bd_count, 64)); /* multiple of 64 */
	enetc_rxbdr_wr(hw, idx, ENETC_RBLENR,
		       ENETC_RTBLENR_LEN(rx_ring->bd_count));

	अगर (rx_ring->xdp.prog)
		enetc_rxbdr_wr(hw, idx, ENETC_RBBSR, ENETC_RXB_DMA_SIZE_XDP);
	अन्यथा
		enetc_rxbdr_wr(hw, idx, ENETC_RBBSR, ENETC_RXB_DMA_SIZE);

	enetc_rxbdr_wr(hw, idx, ENETC_RBPIR, 0);

	/* enable Rx पूर्णांकs by setting pkt thr to 1 */
	enetc_rxbdr_wr(hw, idx, ENETC_RBICR0, ENETC_RBICR0_ICEN | 0x1);

	rbmr = ENETC_RBMR_EN;

	अगर (rx_ring->ext_en)
		rbmr |= ENETC_RBMR_BDS;

	अगर (rx_ring->ndev->features & NETIF_F_HW_VLAN_CTAG_RX)
		rbmr |= ENETC_RBMR_VTE;

	rx_ring->rcir = hw->reg + ENETC_BDR(RX, idx, ENETC_RBCIR);
	rx_ring->idr = hw->reg + ENETC_SIRXIDR;

	enetc_lock_mdio();
	enetc_refill_rx_ring(rx_ring, enetc_bd_unused(rx_ring));
	enetc_unlock_mdio();

	/* enable ring */
	enetc_rxbdr_wr(hw, idx, ENETC_RBMR, rbmr);
पूर्ण

अटल व्योम enetc_setup_bdrs(काष्ठा enetc_ndev_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_tx_rings; i++)
		enetc_setup_txbdr(&priv->si->hw, priv->tx_ring[i]);

	क्रम (i = 0; i < priv->num_rx_rings; i++)
		enetc_setup_rxbdr(&priv->si->hw, priv->rx_ring[i]);
पूर्ण

अटल व्योम enetc_clear_rxbdr(काष्ठा enetc_hw *hw, काष्ठा enetc_bdr *rx_ring)
अणु
	पूर्णांक idx = rx_ring->index;

	/* disable EN bit on ring */
	enetc_rxbdr_wr(hw, idx, ENETC_RBMR, 0);
पूर्ण

अटल व्योम enetc_clear_txbdr(काष्ठा enetc_hw *hw, काष्ठा enetc_bdr *tx_ring)
अणु
	पूर्णांक delay = 8, समयout = 100;
	पूर्णांक idx = tx_ring->index;

	/* disable EN bit on ring */
	enetc_txbdr_wr(hw, idx, ENETC_TBMR, 0);

	/* रुको क्रम busy to clear */
	जबतक (delay < समयout &&
	       enetc_txbdr_rd(hw, idx, ENETC_TBSR) & ENETC_TBSR_BUSY) अणु
		msleep(delay);
		delay *= 2;
	पूर्ण

	अगर (delay >= समयout)
		netdev_warn(tx_ring->ndev, "timeout for tx ring #%d clear\n",
			    idx);
पूर्ण

अटल व्योम enetc_clear_bdrs(काष्ठा enetc_ndev_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_tx_rings; i++)
		enetc_clear_txbdr(&priv->si->hw, priv->tx_ring[i]);

	क्रम (i = 0; i < priv->num_rx_rings; i++)
		enetc_clear_rxbdr(&priv->si->hw, priv->rx_ring[i]);

	udelay(1);
पूर्ण

अटल पूर्णांक enetc_setup_irqs(काष्ठा enetc_ndev_priv *priv)
अणु
	काष्ठा pci_dev *pdev = priv->si->pdev;
	cpumask_t cpu_mask;
	पूर्णांक i, j, err;

	क्रम (i = 0; i < priv->bdr_पूर्णांक_num; i++) अणु
		पूर्णांक irq = pci_irq_vector(pdev, ENETC_BDR_INT_BASE_IDX + i);
		काष्ठा enetc_पूर्णांक_vector *v = priv->पूर्णांक_vector[i];
		पूर्णांक entry = ENETC_BDR_INT_BASE_IDX + i;
		काष्ठा enetc_hw *hw = &priv->si->hw;

		snम_लिखो(v->name, माप(v->name), "%s-rxtx%d",
			 priv->ndev->name, i);
		err = request_irq(irq, enetc_msix, 0, v->name, v);
		अगर (err) अणु
			dev_err(priv->dev, "request_irq() failed!\n");
			जाओ irq_err;
		पूर्ण
		disable_irq(irq);

		v->tbier_base = hw->reg + ENETC_BDR(TX, 0, ENETC_TBIER);
		v->rbier = hw->reg + ENETC_BDR(RX, i, ENETC_RBIER);
		v->ricr1 = hw->reg + ENETC_BDR(RX, i, ENETC_RBICR1);

		enetc_wr(hw, ENETC_SIMSIRRV(i), entry);

		क्रम (j = 0; j < v->count_tx_rings; j++) अणु
			पूर्णांक idx = v->tx_ring[j].index;

			enetc_wr(hw, ENETC_SIMSITRV(idx), entry);
		पूर्ण
		cpumask_clear(&cpu_mask);
		cpumask_set_cpu(i % num_online_cpus(), &cpu_mask);
		irq_set_affinity_hपूर्णांक(irq, &cpu_mask);
	पूर्ण

	वापस 0;

irq_err:
	जबतक (i--) अणु
		पूर्णांक irq = pci_irq_vector(pdev, ENETC_BDR_INT_BASE_IDX + i);

		irq_set_affinity_hपूर्णांक(irq, शून्य);
		मुक्त_irq(irq, priv->पूर्णांक_vector[i]);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम enetc_मुक्त_irqs(काष्ठा enetc_ndev_priv *priv)
अणु
	काष्ठा pci_dev *pdev = priv->si->pdev;
	पूर्णांक i;

	क्रम (i = 0; i < priv->bdr_पूर्णांक_num; i++) अणु
		पूर्णांक irq = pci_irq_vector(pdev, ENETC_BDR_INT_BASE_IDX + i);

		irq_set_affinity_hपूर्णांक(irq, शून्य);
		मुक्त_irq(irq, priv->पूर्णांक_vector[i]);
	पूर्ण
पूर्ण

अटल व्योम enetc_setup_पूर्णांकerrupts(काष्ठा enetc_ndev_priv *priv)
अणु
	काष्ठा enetc_hw *hw = &priv->si->hw;
	u32 icpt, ictt;
	पूर्णांक i;

	/* enable Tx & Rx event indication */
	अगर (priv->ic_mode &
	    (ENETC_IC_RX_MANUAL | ENETC_IC_RX_ADAPTIVE)) अणु
		icpt = ENETC_RBICR0_SET_ICPT(ENETC_RXIC_PKTTHR);
		/* init to non-0 minimum, will be adjusted later */
		ictt = 0x1;
	पूर्ण अन्यथा अणु
		icpt = 0x1; /* enable Rx पूर्णांकs by setting pkt thr to 1 */
		ictt = 0;
	पूर्ण

	क्रम (i = 0; i < priv->num_rx_rings; i++) अणु
		enetc_rxbdr_wr(hw, i, ENETC_RBICR1, ictt);
		enetc_rxbdr_wr(hw, i, ENETC_RBICR0, ENETC_RBICR0_ICEN | icpt);
		enetc_rxbdr_wr(hw, i, ENETC_RBIER, ENETC_RBIER_RXTIE);
	पूर्ण

	अगर (priv->ic_mode & ENETC_IC_TX_MANUAL)
		icpt = ENETC_TBICR0_SET_ICPT(ENETC_TXIC_PKTTHR);
	अन्यथा
		icpt = 0x1; /* enable Tx पूर्णांकs by setting pkt thr to 1 */

	क्रम (i = 0; i < priv->num_tx_rings; i++) अणु
		enetc_txbdr_wr(hw, i, ENETC_TBICR1, priv->tx_ictt);
		enetc_txbdr_wr(hw, i, ENETC_TBICR0, ENETC_TBICR0_ICEN | icpt);
		enetc_txbdr_wr(hw, i, ENETC_TBIER, ENETC_TBIER_TXTIE);
	पूर्ण
पूर्ण

अटल व्योम enetc_clear_पूर्णांकerrupts(काष्ठा enetc_ndev_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_tx_rings; i++)
		enetc_txbdr_wr(&priv->si->hw, i, ENETC_TBIER, 0);

	क्रम (i = 0; i < priv->num_rx_rings; i++)
		enetc_rxbdr_wr(&priv->si->hw, i, ENETC_RBIER, 0);
पूर्ण

अटल पूर्णांक enetc_phylink_connect(काष्ठा net_device *ndev)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा ethtool_eee edata;
	पूर्णांक err;

	अगर (!priv->phylink)
		वापस 0; /* phy-less mode */

	err = phylink_of_phy_connect(priv->phylink, priv->dev->of_node, 0);
	अगर (err) अणु
		dev_err(&ndev->dev, "could not attach to PHY\n");
		वापस err;
	पूर्ण

	/* disable EEE स्वतःneg, until ENETC driver supports it */
	स_रखो(&edata, 0, माप(काष्ठा ethtool_eee));
	phylink_ethtool_set_eee(priv->phylink, &edata);

	वापस 0;
पूर्ण

अटल व्योम enetc_tx_onestep_tstamp(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा enetc_ndev_priv *priv;
	काष्ठा sk_buff *skb;

	priv = container_of(work, काष्ठा enetc_ndev_priv, tx_onestep_tstamp);

	netअगर_tx_lock(priv->ndev);

	clear_bit_unlock(ENETC_TX_ONESTEP_TSTAMP_IN_PROGRESS, &priv->flags);
	skb = skb_dequeue(&priv->tx_skbs);
	अगर (skb)
		enetc_start_xmit(skb, priv->ndev);

	netअगर_tx_unlock(priv->ndev);
पूर्ण

अटल व्योम enetc_tx_onestep_tstamp_init(काष्ठा enetc_ndev_priv *priv)
अणु
	INIT_WORK(&priv->tx_onestep_tstamp, enetc_tx_onestep_tstamp);
	skb_queue_head_init(&priv->tx_skbs);
पूर्ण

व्योम enetc_start(काष्ठा net_device *ndev)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	पूर्णांक i;

	enetc_setup_पूर्णांकerrupts(priv);

	क्रम (i = 0; i < priv->bdr_पूर्णांक_num; i++) अणु
		पूर्णांक irq = pci_irq_vector(priv->si->pdev,
					 ENETC_BDR_INT_BASE_IDX + i);

		napi_enable(&priv->पूर्णांक_vector[i]->napi);
		enable_irq(irq);
	पूर्ण

	अगर (priv->phylink)
		phylink_start(priv->phylink);
	अन्यथा
		netअगर_carrier_on(ndev);

	netअगर_tx_start_all_queues(ndev);
पूर्ण

पूर्णांक enetc_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	पूर्णांक num_stack_tx_queues;
	पूर्णांक err;

	err = enetc_setup_irqs(priv);
	अगर (err)
		वापस err;

	err = enetc_phylink_connect(ndev);
	अगर (err)
		जाओ err_phy_connect;

	err = enetc_alloc_tx_resources(priv);
	अगर (err)
		जाओ err_alloc_tx;

	err = enetc_alloc_rx_resources(priv);
	अगर (err)
		जाओ err_alloc_rx;

	num_stack_tx_queues = enetc_num_stack_tx_queues(priv);

	err = netअगर_set_real_num_tx_queues(ndev, num_stack_tx_queues);
	अगर (err)
		जाओ err_set_queues;

	err = netअगर_set_real_num_rx_queues(ndev, priv->num_rx_rings);
	अगर (err)
		जाओ err_set_queues;

	enetc_tx_onestep_tstamp_init(priv);
	enetc_setup_bdrs(priv);
	enetc_start(ndev);

	वापस 0;

err_set_queues:
	enetc_मुक्त_rx_resources(priv);
err_alloc_rx:
	enetc_मुक्त_tx_resources(priv);
err_alloc_tx:
	अगर (priv->phylink)
		phylink_disconnect_phy(priv->phylink);
err_phy_connect:
	enetc_मुक्त_irqs(priv);

	वापस err;
पूर्ण

व्योम enetc_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	पूर्णांक i;

	netअगर_tx_stop_all_queues(ndev);

	क्रम (i = 0; i < priv->bdr_पूर्णांक_num; i++) अणु
		पूर्णांक irq = pci_irq_vector(priv->si->pdev,
					 ENETC_BDR_INT_BASE_IDX + i);

		disable_irq(irq);
		napi_synchronize(&priv->पूर्णांक_vector[i]->napi);
		napi_disable(&priv->पूर्णांक_vector[i]->napi);
	पूर्ण

	अगर (priv->phylink)
		phylink_stop(priv->phylink);
	अन्यथा
		netअगर_carrier_off(ndev);

	enetc_clear_पूर्णांकerrupts(priv);
पूर्ण

पूर्णांक enetc_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);

	enetc_stop(ndev);
	enetc_clear_bdrs(priv);

	अगर (priv->phylink)
		phylink_disconnect_phy(priv->phylink);
	enetc_मुक्त_rxtx_rings(priv);
	enetc_मुक्त_rx_resources(priv);
	enetc_मुक्त_tx_resources(priv);
	enetc_मुक्त_irqs(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_setup_tc_mqprio(काष्ठा net_device *ndev, व्योम *type_data)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा tc_mqprio_qopt *mqprio = type_data;
	काष्ठा enetc_bdr *tx_ring;
	पूर्णांक num_stack_tx_queues;
	u8 num_tc;
	पूर्णांक i;

	num_stack_tx_queues = enetc_num_stack_tx_queues(priv);
	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;
	num_tc = mqprio->num_tc;

	अगर (!num_tc) अणु
		netdev_reset_tc(ndev);
		netअगर_set_real_num_tx_queues(ndev, num_stack_tx_queues);

		/* Reset all ring priorities to 0 */
		क्रम (i = 0; i < priv->num_tx_rings; i++) अणु
			tx_ring = priv->tx_ring[i];
			enetc_set_bdr_prio(&priv->si->hw, tx_ring->index, 0);
		पूर्ण

		वापस 0;
	पूर्ण

	/* Check अगर we have enough BD rings available to accommodate all TCs */
	अगर (num_tc > num_stack_tx_queues) अणु
		netdev_err(ndev, "Max %d traffic classes supported\n",
			   priv->num_tx_rings);
		वापस -EINVAL;
	पूर्ण

	/* For the moment, we use only one BD ring per TC.
	 *
	 * Configure num_tc BD rings with increasing priorities.
	 */
	क्रम (i = 0; i < num_tc; i++) अणु
		tx_ring = priv->tx_ring[i];
		enetc_set_bdr_prio(&priv->si->hw, tx_ring->index, i);
	पूर्ण

	/* Reset the number of netdev queues based on the TC count */
	netअगर_set_real_num_tx_queues(ndev, num_tc);

	netdev_set_num_tc(ndev, num_tc);

	/* Each TC is associated with one netdev queue */
	क्रम (i = 0; i < num_tc; i++)
		netdev_set_tc_queue(ndev, i, 1, i);

	वापस 0;
पूर्ण

पूर्णांक enetc_setup_tc(काष्ठा net_device *ndev, क्रमागत tc_setup_type type,
		   व्योम *type_data)
अणु
	चयन (type) अणु
	हाल TC_SETUP_QDISC_MQPRIO:
		वापस enetc_setup_tc_mqprio(ndev, type_data);
	हाल TC_SETUP_QDISC_TAPRIO:
		वापस enetc_setup_tc_taprio(ndev, type_data);
	हाल TC_SETUP_QDISC_CBS:
		वापस enetc_setup_tc_cbs(ndev, type_data);
	हाल TC_SETUP_QDISC_ETF:
		वापस enetc_setup_tc_txसमय(ndev, type_data);
	हाल TC_SETUP_BLOCK:
		वापस enetc_setup_tc_psfp(ndev, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक enetc_setup_xdp_prog(काष्ठा net_device *dev, काष्ठा bpf_prog *prog,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(dev);
	काष्ठा bpf_prog *old_prog;
	bool is_up;
	पूर्णांक i;

	/* The buffer layout is changing, so we need to drain the old
	 * RX buffers and seed new ones.
	 */
	is_up = netअगर_running(dev);
	अगर (is_up)
		dev_बंद(dev);

	old_prog = xchg(&priv->xdp_prog, prog);
	अगर (old_prog)
		bpf_prog_put(old_prog);

	क्रम (i = 0; i < priv->num_rx_rings; i++) अणु
		काष्ठा enetc_bdr *rx_ring = priv->rx_ring[i];

		rx_ring->xdp.prog = prog;

		अगर (prog)
			rx_ring->buffer_offset = XDP_PACKET_HEADROOM;
		अन्यथा
			rx_ring->buffer_offset = ENETC_RXB_PAD;
	पूर्ण

	अगर (is_up)
		वापस dev_खोलो(dev, extack);

	वापस 0;
पूर्ण

पूर्णांक enetc_setup_bpf(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस enetc_setup_xdp_prog(dev, xdp->prog, xdp->extack);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा net_device_stats *enetc_get_stats(काष्ठा net_device *ndev)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	अचिन्हित दीर्घ packets = 0, bytes = 0;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_rx_rings; i++) अणु
		packets += priv->rx_ring[i]->stats.packets;
		bytes	+= priv->rx_ring[i]->stats.bytes;
	पूर्ण

	stats->rx_packets = packets;
	stats->rx_bytes = bytes;
	bytes = 0;
	packets = 0;

	क्रम (i = 0; i < priv->num_tx_rings; i++) अणु
		packets += priv->tx_ring[i]->stats.packets;
		bytes	+= priv->tx_ring[i]->stats.bytes;
	पूर्ण

	stats->tx_packets = packets;
	stats->tx_bytes = bytes;

	वापस stats;
पूर्ण

अटल पूर्णांक enetc_set_rss(काष्ठा net_device *ndev, पूर्णांक en)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_hw *hw = &priv->si->hw;
	u32 reg;

	enetc_wr(hw, ENETC_SIRBGCR, priv->num_rx_rings);

	reg = enetc_rd(hw, ENETC_SIMR);
	reg &= ~ENETC_SIMR_RSSE;
	reg |= (en) ? ENETC_SIMR_RSSE : 0;
	enetc_wr(hw, ENETC_SIMR, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_set_psfp(काष्ठा net_device *ndev, पूर्णांक en)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	पूर्णांक err;

	अगर (en) अणु
		err = enetc_psfp_enable(priv);
		अगर (err)
			वापस err;

		priv->active_offloads |= ENETC_F_QCI;
		वापस 0;
	पूर्ण

	err = enetc_psfp_disable(priv);
	अगर (err)
		वापस err;

	priv->active_offloads &= ~ENETC_F_QCI;

	वापस 0;
पूर्ण

अटल व्योम enetc_enable_rxvlan(काष्ठा net_device *ndev, bool en)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_rx_rings; i++)
		enetc_bdr_enable_rxvlan(&priv->si->hw, i, en);
पूर्ण

अटल व्योम enetc_enable_txvlan(काष्ठा net_device *ndev, bool en)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_tx_rings; i++)
		enetc_bdr_enable_txvlan(&priv->si->hw, i, en);
पूर्ण

पूर्णांक enetc_set_features(काष्ठा net_device *ndev,
		       netdev_features_t features)
अणु
	netdev_features_t changed = ndev->features ^ features;
	पूर्णांक err = 0;

	अगर (changed & NETIF_F_RXHASH)
		enetc_set_rss(ndev, !!(features & NETIF_F_RXHASH));

	अगर (changed & NETIF_F_HW_VLAN_CTAG_RX)
		enetc_enable_rxvlan(ndev,
				    !!(features & NETIF_F_HW_VLAN_CTAG_RX));

	अगर (changed & NETIF_F_HW_VLAN_CTAG_TX)
		enetc_enable_txvlan(ndev,
				    !!(features & NETIF_F_HW_VLAN_CTAG_TX));

	अगर (changed & NETIF_F_HW_TC)
		err = enetc_set_psfp(ndev, !!(features & NETIF_F_HW_TC));

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_FSL_ENETC_PTP_CLOCK
अटल पूर्णांक enetc_hwtstamp_set(काष्ठा net_device *ndev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा hwtstamp_config config;
	पूर्णांक ao;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		priv->active_offloads &= ~ENETC_F_TX_TSTAMP_MASK;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		priv->active_offloads &= ~ENETC_F_TX_TSTAMP_MASK;
		priv->active_offloads |= ENETC_F_TX_TSTAMP;
		अवरोध;
	हाल HWTSTAMP_TX_ONESTEP_SYNC:
		priv->active_offloads &= ~ENETC_F_TX_TSTAMP_MASK;
		priv->active_offloads |= ENETC_F_TX_ONESTEP_SYNC_TSTAMP;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	ao = priv->active_offloads;
	चयन (config.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		priv->active_offloads &= ~ENETC_F_RX_TSTAMP;
		अवरोध;
	शेष:
		priv->active_offloads |= ENETC_F_RX_TSTAMP;
		config.rx_filter = HWTSTAMP_FILTER_ALL;
	पूर्ण

	अगर (netअगर_running(ndev) && ao != priv->active_offloads) अणु
		enetc_बंद(ndev);
		enetc_खोलो(ndev);
	पूर्ण

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
	       -EFAULT : 0;
पूर्ण

अटल पूर्णांक enetc_hwtstamp_get(काष्ठा net_device *ndev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा hwtstamp_config config;

	config.flags = 0;

	अगर (priv->active_offloads & ENETC_F_TX_ONESTEP_SYNC_TSTAMP)
		config.tx_type = HWTSTAMP_TX_ONESTEP_SYNC;
	अन्यथा अगर (priv->active_offloads & ENETC_F_TX_TSTAMP)
		config.tx_type = HWTSTAMP_TX_ON;
	अन्यथा
		config.tx_type = HWTSTAMP_TX_OFF;

	config.rx_filter = (priv->active_offloads & ENETC_F_RX_TSTAMP) ?
			    HWTSTAMP_FILTER_ALL : HWTSTAMP_FILTER_NONE;

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
	       -EFAULT : 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक enetc_ioctl(काष्ठा net_device *ndev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
#अगर_घोषित CONFIG_FSL_ENETC_PTP_CLOCK
	अगर (cmd == SIOCSHWTSTAMP)
		वापस enetc_hwtstamp_set(ndev, rq);
	अगर (cmd == SIOCGHWTSTAMP)
		वापस enetc_hwtstamp_get(ndev, rq);
#पूर्ण_अगर

	अगर (!priv->phylink)
		वापस -EOPNOTSUPP;

	वापस phylink_mii_ioctl(priv->phylink, rq, cmd);
पूर्ण

पूर्णांक enetc_alloc_msix(काष्ठा enetc_ndev_priv *priv)
अणु
	काष्ठा pci_dev *pdev = priv->si->pdev;
	पूर्णांक first_xdp_tx_ring;
	पूर्णांक i, n, err, nvec;
	पूर्णांक v_tx_rings;

	nvec = ENETC_BDR_INT_BASE_IDX + priv->bdr_पूर्णांक_num;
	/* allocate MSIX क्रम both messaging and Rx/Tx पूर्णांकerrupts */
	n = pci_alloc_irq_vectors(pdev, nvec, nvec, PCI_IRQ_MSIX);

	अगर (n < 0)
		वापस n;

	अगर (n != nvec)
		वापस -EPERM;

	/* # of tx rings per पूर्णांक vector */
	v_tx_rings = priv->num_tx_rings / priv->bdr_पूर्णांक_num;

	क्रम (i = 0; i < priv->bdr_पूर्णांक_num; i++) अणु
		काष्ठा enetc_पूर्णांक_vector *v;
		काष्ठा enetc_bdr *bdr;
		पूर्णांक j;

		v = kzalloc(काष्ठा_size(v, tx_ring, v_tx_rings), GFP_KERNEL);
		अगर (!v) अणु
			err = -ENOMEM;
			जाओ fail;
		पूर्ण

		priv->पूर्णांक_vector[i] = v;

		bdr = &v->rx_ring;
		bdr->index = i;
		bdr->ndev = priv->ndev;
		bdr->dev = priv->dev;
		bdr->bd_count = priv->rx_bd_count;
		bdr->buffer_offset = ENETC_RXB_PAD;
		priv->rx_ring[i] = bdr;

		err = xdp_rxq_info_reg(&bdr->xdp.rxq, priv->ndev, i, 0);
		अगर (err) अणु
			kमुक्त(v);
			जाओ fail;
		पूर्ण

		err = xdp_rxq_info_reg_mem_model(&bdr->xdp.rxq,
						 MEM_TYPE_PAGE_SHARED, शून्य);
		अगर (err) अणु
			xdp_rxq_info_unreg(&bdr->xdp.rxq);
			kमुक्त(v);
			जाओ fail;
		पूर्ण

		/* init शेषs क्रम adaptive IC */
		अगर (priv->ic_mode & ENETC_IC_RX_ADAPTIVE) अणु
			v->rx_ictt = 0x1;
			v->rx_dim_en = true;
		पूर्ण
		INIT_WORK(&v->rx_dim.work, enetc_rx_dim_work);
		netअगर_napi_add(priv->ndev, &v->napi, enetc_poll,
			       NAPI_POLL_WEIGHT);
		v->count_tx_rings = v_tx_rings;

		क्रम (j = 0; j < v_tx_rings; j++) अणु
			पूर्णांक idx;

			/* शेष tx ring mapping policy */
			idx = priv->bdr_पूर्णांक_num * j + i;
			__set_bit(idx, &v->tx_rings_map);
			bdr = &v->tx_ring[j];
			bdr->index = idx;
			bdr->ndev = priv->ndev;
			bdr->dev = priv->dev;
			bdr->bd_count = priv->tx_bd_count;
			priv->tx_ring[idx] = bdr;
		पूर्ण
	पूर्ण

	first_xdp_tx_ring = priv->num_tx_rings - num_possible_cpus();
	priv->xdp_tx_ring = &priv->tx_ring[first_xdp_tx_ring];

	वापस 0;

fail:
	जबतक (i--) अणु
		काष्ठा enetc_पूर्णांक_vector *v = priv->पूर्णांक_vector[i];
		काष्ठा enetc_bdr *rx_ring = &v->rx_ring;

		xdp_rxq_info_unreg_mem_model(&rx_ring->xdp.rxq);
		xdp_rxq_info_unreg(&rx_ring->xdp.rxq);
		netअगर_napi_del(&v->napi);
		cancel_work_sync(&v->rx_dim.work);
		kमुक्त(v);
	पूर्ण

	pci_मुक्त_irq_vectors(pdev);

	वापस err;
पूर्ण

व्योम enetc_मुक्त_msix(काष्ठा enetc_ndev_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->bdr_पूर्णांक_num; i++) अणु
		काष्ठा enetc_पूर्णांक_vector *v = priv->पूर्णांक_vector[i];
		काष्ठा enetc_bdr *rx_ring = &v->rx_ring;

		xdp_rxq_info_unreg_mem_model(&rx_ring->xdp.rxq);
		xdp_rxq_info_unreg(&rx_ring->xdp.rxq);
		netअगर_napi_del(&v->napi);
		cancel_work_sync(&v->rx_dim.work);
	पूर्ण

	क्रम (i = 0; i < priv->num_rx_rings; i++)
		priv->rx_ring[i] = शून्य;

	क्रम (i = 0; i < priv->num_tx_rings; i++)
		priv->tx_ring[i] = शून्य;

	क्रम (i = 0; i < priv->bdr_पूर्णांक_num; i++) अणु
		kमुक्त(priv->पूर्णांक_vector[i]);
		priv->पूर्णांक_vector[i] = शून्य;
	पूर्ण

	/* disable all MSIX क्रम this device */
	pci_मुक्त_irq_vectors(priv->si->pdev);
पूर्ण

अटल व्योम enetc_kमुक्त_si(काष्ठा enetc_si *si)
अणु
	अक्षर *p = (अक्षर *)si - si->pad;

	kमुक्त(p);
पूर्ण

अटल व्योम enetc_detect_errata(काष्ठा enetc_si *si)
अणु
	अगर (si->pdev->revision == ENETC_REV1)
		si->errata = ENETC_ERR_VLAN_ISOL | ENETC_ERR_UCMCSWP;
पूर्ण

पूर्णांक enetc_pci_probe(काष्ठा pci_dev *pdev, स्थिर अक्षर *name, पूर्णांक माप_priv)
अणु
	काष्ठा enetc_si *si, *p;
	काष्ठा enetc_hw *hw;
	माप_प्रकार alloc_size;
	पूर्णांक err, len;

	pcie_flr(pdev);
	err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "device enable failed\n");
		वापस err;
	पूर्ण

	/* set up क्रम high or low dma */
	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (err) अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev,
				"DMA configuration failed: 0x%x\n", err);
			जाओ err_dma;
		पूर्ण
	पूर्ण

	err = pci_request_mem_regions(pdev, name);
	अगर (err) अणु
		dev_err(&pdev->dev, "pci_request_regions failed err=%d\n", err);
		जाओ err_pci_mem_reg;
	पूर्ण

	pci_set_master(pdev);

	alloc_size = माप(काष्ठा enetc_si);
	अगर (माप_priv) अणु
		/* align priv to 32B */
		alloc_size = ALIGN(alloc_size, ENETC_SI_ALIGN);
		alloc_size += माप_priv;
	पूर्ण
	/* क्रमce 32B alignment क्रम enetc_si */
	alloc_size += ENETC_SI_ALIGN - 1;

	p = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!p) अणु
		err = -ENOMEM;
		जाओ err_alloc_si;
	पूर्ण

	si = PTR_ALIGN(p, ENETC_SI_ALIGN);
	si->pad = (अक्षर *)si - (अक्षर *)p;

	pci_set_drvdata(pdev, si);
	si->pdev = pdev;
	hw = &si->hw;

	len = pci_resource_len(pdev, ENETC_BAR_REGS);
	hw->reg = ioremap(pci_resource_start(pdev, ENETC_BAR_REGS), len);
	अगर (!hw->reg) अणु
		err = -ENXIO;
		dev_err(&pdev->dev, "ioremap() failed\n");
		जाओ err_ioremap;
	पूर्ण
	अगर (len > ENETC_PORT_BASE)
		hw->port = hw->reg + ENETC_PORT_BASE;
	अगर (len > ENETC_GLOBAL_BASE)
		hw->global = hw->reg + ENETC_GLOBAL_BASE;

	enetc_detect_errata(si);

	वापस 0;

err_ioremap:
	enetc_kमुक्त_si(si);
err_alloc_si:
	pci_release_mem_regions(pdev);
err_pci_mem_reg:
err_dma:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

व्योम enetc_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा enetc_si *si = pci_get_drvdata(pdev);
	काष्ठा enetc_hw *hw = &si->hw;

	iounmap(hw->reg);
	enetc_kमुक्त_si(si);
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
पूर्ण
