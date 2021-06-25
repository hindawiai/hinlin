<शैली गुरु>
/*
 * Copyright (c) 2015-2016, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/tcp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/geneve.h>
#समावेश <net/dsfield.h>
#समावेश "en.h"
#समावेश "en/txrx.h"
#समावेश "ipoib/ipoib.h"
#समावेश "en_accel/en_accel.h"
#समावेश "en/ptp.h"

अटल व्योम mlx5e_dma_unmap_wqe_err(काष्ठा mlx5e_txqsq *sq, u8 num_dma)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_dma; i++) अणु
		काष्ठा mlx5e_sq_dma *last_pushed_dma =
			mlx5e_dma_get(sq, --sq->dma_fअगरo_pc);

		mlx5e_tx_dma_unmap(sq->pdev, last_pushed_dma);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MLX5_CORE_EN_DCB
अटल अंतरभूत पूर्णांक mlx5e_get_dscp_up(काष्ठा mlx5e_priv *priv, काष्ठा sk_buff *skb)
अणु
	पूर्णांक dscp_cp = 0;

	अगर (skb->protocol == htons(ETH_P_IP))
		dscp_cp = ipv4_get_dsfield(ip_hdr(skb)) >> 2;
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		dscp_cp = ipv6_get_dsfield(ipv6_hdr(skb)) >> 2;

	वापस priv->dcbx_dp.dscp2prio[dscp_cp];
पूर्ण
#पूर्ण_अगर

अटल u16 mlx5e_select_ptpsq(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	पूर्णांक up = 0;

	अगर (!netdev_get_num_tc(dev))
		जाओ वापस_txq;

#अगर_घोषित CONFIG_MLX5_CORE_EN_DCB
	अगर (priv->dcbx_dp.trust_state == MLX5_QPTS_TRUST_DSCP)
		up = mlx5e_get_dscp_up(priv, skb);
	अन्यथा
#पूर्ण_अगर
		अगर (skb_vlan_tag_present(skb))
			up = skb_vlan_tag_get_prio(skb);

वापस_txq:
	वापस priv->port_ptp_tc2realtxq[up];
पूर्ण

अटल पूर्णांक mlx5e_select_htb_queue(काष्ठा mlx5e_priv *priv, काष्ठा sk_buff *skb,
				  u16 htb_maj_id)
अणु
	u16 classid;

	अगर ((TC_H_MAJ(skb->priority) >> 16) == htb_maj_id)
		classid = TC_H_MIN(skb->priority);
	अन्यथा
		classid = READ_ONCE(priv->htb.defcls);

	अगर (!classid)
		वापस 0;

	वापस mlx5e_get_txq_by_classid(priv, classid);
पूर्ण

u16 mlx5e_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		       काष्ठा net_device *sb_dev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	पूर्णांक num_tc_x_num_ch;
	पूर्णांक txq_ix;
	पूर्णांक up = 0;
	पूर्णांक ch_ix;

	/* Sync with mlx5e_update_num_tc_x_num_ch - aव्योम refetching. */
	num_tc_x_num_ch = READ_ONCE(priv->num_tc_x_num_ch);
	अगर (unlikely(dev->real_num_tx_queues > num_tc_x_num_ch)) अणु
		काष्ठा mlx5e_ptp *ptp_channel;

		/* Order maj_id beक्रमe defcls - pairs with mlx5e_htb_root_add. */
		u16 htb_maj_id = smp_load_acquire(&priv->htb.maj_id);

		अगर (unlikely(htb_maj_id)) अणु
			txq_ix = mlx5e_select_htb_queue(priv, skb, htb_maj_id);
			अगर (txq_ix > 0)
				वापस txq_ix;
		पूर्ण

		ptp_channel = READ_ONCE(priv->channels.ptp);
		अगर (unlikely(ptp_channel &&
			     test_bit(MLX5E_PTP_STATE_TX, ptp_channel->state) &&
			     mlx5e_use_ptpsq(skb)))
			वापस mlx5e_select_ptpsq(dev, skb);

		txq_ix = netdev_pick_tx(dev, skb, शून्य);
		/* Fix netdev_pick_tx() not to choose ptp_channel and HTB txqs.
		 * If they are selected, चयन to regular queues.
		 * Driver to select these queues only at mlx5e_select_ptpsq()
		 * and mlx5e_select_htb_queue().
		 */
		अगर (unlikely(txq_ix >= num_tc_x_num_ch))
			txq_ix %= num_tc_x_num_ch;
	पूर्ण अन्यथा अणु
		txq_ix = netdev_pick_tx(dev, skb, शून्य);
	पूर्ण

	अगर (!netdev_get_num_tc(dev))
		वापस txq_ix;

#अगर_घोषित CONFIG_MLX5_CORE_EN_DCB
	अगर (priv->dcbx_dp.trust_state == MLX5_QPTS_TRUST_DSCP)
		up = mlx5e_get_dscp_up(priv, skb);
	अन्यथा
#पूर्ण_अगर
		अगर (skb_vlan_tag_present(skb))
			up = skb_vlan_tag_get_prio(skb);

	/* Normalize any picked txq_ix to [0, num_channels),
	 * So we can वापस a txq_ix that matches the channel and
	 * packet UP.
	 */
	ch_ix = priv->txq2sq[txq_ix]->ch_ix;

	वापस priv->channel_tc2realtxq[ch_ix][up];
पूर्ण

अटल अंतरभूत पूर्णांक mlx5e_skb_l2_header_offset(काष्ठा sk_buff *skb)
अणु
#घोषणा MLX5E_MIN_INLINE (ETH_HLEN + VLAN_HLEN)

	वापस max(skb_network_offset(skb), MLX5E_MIN_INLINE);
पूर्ण

अटल अंतरभूत पूर्णांक mlx5e_skb_l3_header_offset(काष्ठा sk_buff *skb)
अणु
	अगर (skb_transport_header_was_set(skb))
		वापस skb_transport_offset(skb);
	अन्यथा
		वापस mlx5e_skb_l2_header_offset(skb);
पूर्ण

अटल अंतरभूत u16 mlx5e_calc_min_अंतरभूत(क्रमागत mlx5_अंतरभूत_modes mode,
					काष्ठा sk_buff *skb)
अणु
	u16 hlen;

	चयन (mode) अणु
	हाल MLX5_INLINE_MODE_NONE:
		वापस 0;
	हाल MLX5_INLINE_MODE_TCP_UDP:
		hlen = eth_get_headlen(skb->dev, skb->data, skb_headlen(skb));
		अगर (hlen == ETH_HLEN && !skb_vlan_tag_present(skb))
			hlen += VLAN_HLEN;
		अवरोध;
	हाल MLX5_INLINE_MODE_IP:
		hlen = mlx5e_skb_l3_header_offset(skb);
		अवरोध;
	हाल MLX5_INLINE_MODE_L2:
	शेष:
		hlen = mlx5e_skb_l2_header_offset(skb);
	पूर्ण
	वापस min_t(u16, hlen, skb_headlen(skb));
पूर्ण

अटल अंतरभूत व्योम mlx5e_insert_vlan(व्योम *start, काष्ठा sk_buff *skb, u16 ihs)
अणु
	काष्ठा vlan_ethhdr *vhdr = (काष्ठा vlan_ethhdr *)start;
	पूर्णांक cpy1_sz = 2 * ETH_ALEN;
	पूर्णांक cpy2_sz = ihs - cpy1_sz;

	स_नकल(vhdr, skb->data, cpy1_sz);
	vhdr->h_vlan_proto = skb->vlan_proto;
	vhdr->h_vlan_TCI = cpu_to_be16(skb_vlan_tag_get(skb));
	स_नकल(&vhdr->h_vlan_encapsulated_proto, skb->data + cpy1_sz, cpy2_sz);
पूर्ण

/* If packet is not IP's CHECKSUM_PARTIAL (e.g. icmd packet),
 * need to set L3 checksum flag क्रम IPsec
 */
अटल व्योम
ipsec_txwqe_build_eseg_csum(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb,
			    काष्ठा mlx5_wqe_eth_seg *eseg)
अणु
	eseg->cs_flags = MLX5_ETH_WQE_L3_CSUM;
	अगर (skb->encapsulation) अणु
		eseg->cs_flags |= MLX5_ETH_WQE_L3_INNER_CSUM;
		sq->stats->csum_partial_inner++;
	पूर्ण अन्यथा अणु
		sq->stats->csum_partial++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
mlx5e_txwqe_build_eseg_csum(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb,
			    काष्ठा mlx5e_accel_tx_state *accel,
			    काष्ठा mlx5_wqe_eth_seg *eseg)
अणु
	अगर (likely(skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		eseg->cs_flags = MLX5_ETH_WQE_L3_CSUM;
		अगर (skb->encapsulation) अणु
			eseg->cs_flags |= MLX5_ETH_WQE_L3_INNER_CSUM |
					  MLX5_ETH_WQE_L4_INNER_CSUM;
			sq->stats->csum_partial_inner++;
		पूर्ण अन्यथा अणु
			eseg->cs_flags |= MLX5_ETH_WQE_L4_CSUM;
			sq->stats->csum_partial++;
		पूर्ण
#अगर_घोषित CONFIG_MLX5_EN_TLS
	पूर्ण अन्यथा अगर (unlikely(accel && accel->tls.tls_tisn)) अणु
		eseg->cs_flags = MLX5_ETH_WQE_L3_CSUM | MLX5_ETH_WQE_L4_CSUM;
		sq->stats->csum_partial++;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (unlikely(mlx5e_ipsec_eseg_meta(eseg))) अणु
		ipsec_txwqe_build_eseg_csum(sq, skb, eseg);
	पूर्ण अन्यथा
		sq->stats->csum_none++;
पूर्ण

अटल अंतरभूत u16
mlx5e_tx_get_gso_ihs(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb)
अणु
	काष्ठा mlx5e_sq_stats *stats = sq->stats;
	u16 ihs;

	अगर (skb->encapsulation) अणु
		ihs = skb_inner_transport_offset(skb) + inner_tcp_hdrlen(skb);
		stats->tso_inner_packets++;
		stats->tso_inner_bytes += skb->len - ihs;
	पूर्ण अन्यथा अणु
		अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4)
			ihs = skb_transport_offset(skb) + माप(काष्ठा udphdr);
		अन्यथा
			ihs = skb_transport_offset(skb) + tcp_hdrlen(skb);
		stats->tso_packets++;
		stats->tso_bytes += skb->len - ihs;
	पूर्ण

	वापस ihs;
पूर्ण

अटल अंतरभूत पूर्णांक
mlx5e_txwqe_build_dsegs(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb,
			अचिन्हित अक्षर *skb_data, u16 headlen,
			काष्ठा mlx5_wqe_data_seg *dseg)
अणु
	dma_addr_t dma_addr = 0;
	u8 num_dma          = 0;
	पूर्णांक i;

	अगर (headlen) अणु
		dma_addr = dma_map_single(sq->pdev, skb_data, headlen,
					  DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(sq->pdev, dma_addr)))
			जाओ dma_unmap_wqe_err;

		dseg->addr       = cpu_to_be64(dma_addr);
		dseg->lkey       = sq->mkey_be;
		dseg->byte_count = cpu_to_be32(headlen);

		mlx5e_dma_push(sq, dma_addr, headlen, MLX5E_DMA_MAP_SINGLE);
		num_dma++;
		dseg++;
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		पूर्णांक fsz = skb_frag_size(frag);

		dma_addr = skb_frag_dma_map(sq->pdev, frag, 0, fsz,
					    DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(sq->pdev, dma_addr)))
			जाओ dma_unmap_wqe_err;

		dseg->addr       = cpu_to_be64(dma_addr);
		dseg->lkey       = sq->mkey_be;
		dseg->byte_count = cpu_to_be32(fsz);

		mlx5e_dma_push(sq, dma_addr, fsz, MLX5E_DMA_MAP_PAGE);
		num_dma++;
		dseg++;
	पूर्ण

	वापस num_dma;

dma_unmap_wqe_err:
	mlx5e_dma_unmap_wqe_err(sq, num_dma);
	वापस -ENOMEM;
पूर्ण

काष्ठा mlx5e_tx_attr अणु
	u32 num_bytes;
	u16 headlen;
	u16 ihs;
	__be16 mss;
	u16 insz;
	u8 opcode;
पूर्ण;

काष्ठा mlx5e_tx_wqe_attr अणु
	u16 ds_cnt;
	u16 ds_cnt_inl;
	u16 ds_cnt_ids;
	u8 num_wqebbs;
पूर्ण;

अटल u8
mlx5e_tx_wqe_अंतरभूत_mode(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb,
			 काष्ठा mlx5e_accel_tx_state *accel)
अणु
	u8 mode;

#अगर_घोषित CONFIG_MLX5_EN_TLS
	अगर (accel && accel->tls.tls_tisn)
		वापस MLX5_INLINE_MODE_TCP_UDP;
#पूर्ण_अगर

	mode = sq->min_अंतरभूत_mode;

	अगर (skb_vlan_tag_present(skb) &&
	    test_bit(MLX5E_SQ_STATE_VLAN_NEED_L2_INLINE, &sq->state))
		mode = max_t(u8, MLX5_INLINE_MODE_L2, mode);

	वापस mode;
पूर्ण

अटल व्योम mlx5e_sq_xmit_prepare(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb,
				  काष्ठा mlx5e_accel_tx_state *accel,
				  काष्ठा mlx5e_tx_attr *attr)
अणु
	काष्ठा mlx5e_sq_stats *stats = sq->stats;

	अगर (skb_is_gso(skb)) अणु
		u16 ihs = mlx5e_tx_get_gso_ihs(sq, skb);

		*attr = (काष्ठा mlx5e_tx_attr) अणु
			.opcode    = MLX5_OPCODE_LSO,
			.mss       = cpu_to_be16(skb_shinfo(skb)->gso_size),
			.ihs       = ihs,
			.num_bytes = skb->len + (skb_shinfo(skb)->gso_segs - 1) * ihs,
			.headlen   = skb_headlen(skb) - ihs,
		पूर्ण;

		stats->packets += skb_shinfo(skb)->gso_segs;
	पूर्ण अन्यथा अणु
		u8 mode = mlx5e_tx_wqe_अंतरभूत_mode(sq, skb, accel);
		u16 ihs = mlx5e_calc_min_अंतरभूत(mode, skb);

		*attr = (काष्ठा mlx5e_tx_attr) अणु
			.opcode    = MLX5_OPCODE_SEND,
			.mss       = cpu_to_be16(0),
			.ihs       = ihs,
			.num_bytes = max_t(अचिन्हित पूर्णांक, skb->len, ETH_ZLEN),
			.headlen   = skb_headlen(skb) - ihs,
		पूर्ण;

		stats->packets++;
	पूर्ण

	attr->insz = mlx5e_accel_tx_ids_len(sq, accel);
	stats->bytes += attr->num_bytes;
पूर्ण

अटल व्योम mlx5e_sq_calc_wqe_attr(काष्ठा sk_buff *skb, स्थिर काष्ठा mlx5e_tx_attr *attr,
				   काष्ठा mlx5e_tx_wqe_attr *wqe_attr)
अणु
	u16 ds_cnt = MLX5E_TX_WQE_EMPTY_DS_COUNT;
	u16 ds_cnt_inl = 0;
	u16 ds_cnt_ids = 0;

	अगर (attr->insz)
		ds_cnt_ids = DIV_ROUND_UP(माप(काष्ठा mlx5_wqe_अंतरभूत_seg) + attr->insz,
					  MLX5_SEND_WQE_DS);

	ds_cnt += !!attr->headlen + skb_shinfo(skb)->nr_frags + ds_cnt_ids;
	अगर (attr->ihs) अणु
		u16 inl = attr->ihs - INL_HDR_START_SZ;

		अगर (skb_vlan_tag_present(skb))
			inl += VLAN_HLEN;

		ds_cnt_inl = DIV_ROUND_UP(inl, MLX5_SEND_WQE_DS);
		ds_cnt += ds_cnt_inl;
	पूर्ण

	*wqe_attr = (काष्ठा mlx5e_tx_wqe_attr) अणु
		.ds_cnt     = ds_cnt,
		.ds_cnt_inl = ds_cnt_inl,
		.ds_cnt_ids = ds_cnt_ids,
		.num_wqebbs = DIV_ROUND_UP(ds_cnt, MLX5_SEND_WQEBB_NUM_DS),
	पूर्ण;
पूर्ण

अटल व्योम mlx5e_tx_skb_update_hwts_flags(काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP))
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
पूर्ण

अटल व्योम mlx5e_tx_check_stop(काष्ठा mlx5e_txqsq *sq)
अणु
	अगर (unlikely(!mlx5e_wqc_has_room_क्रम(&sq->wq, sq->cc, sq->pc, sq->stop_room))) अणु
		netअगर_tx_stop_queue(sq->txq);
		sq->stats->stopped++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
mlx5e_txwqe_complete(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb,
		     स्थिर काष्ठा mlx5e_tx_attr *attr,
		     स्थिर काष्ठा mlx5e_tx_wqe_attr *wqe_attr, u8 num_dma,
		     काष्ठा mlx5e_tx_wqe_info *wi, काष्ठा mlx5_wqe_ctrl_seg *cseg,
		     bool xmit_more)
अणु
	काष्ठा mlx5_wq_cyc *wq = &sq->wq;
	bool send_करोorbell;

	*wi = (काष्ठा mlx5e_tx_wqe_info) अणु
		.skb = skb,
		.num_bytes = attr->num_bytes,
		.num_dma = num_dma,
		.num_wqebbs = wqe_attr->num_wqebbs,
		.num_fअगरo_pkts = 0,
	पूर्ण;

	cseg->opmod_idx_opcode = cpu_to_be32((sq->pc << 8) | attr->opcode);
	cseg->qpn_ds           = cpu_to_be32((sq->sqn << 8) | wqe_attr->ds_cnt);

	mlx5e_tx_skb_update_hwts_flags(skb);

	sq->pc += wi->num_wqebbs;

	mlx5e_tx_check_stop(sq);

	अगर (unlikely(sq->ptpsq)) अणु
		mlx5e_skb_cb_hwtstamp_init(skb);
		mlx5e_skb_fअगरo_push(&sq->ptpsq->skb_fअगरo, skb);
		skb_get(skb);
	पूर्ण

	send_करोorbell = __netdev_tx_sent_queue(sq->txq, attr->num_bytes, xmit_more);
	अगर (send_करोorbell)
		mlx5e_notअगरy_hw(wq, sq->pc, sq->uar_map, cseg);
पूर्ण

अटल व्योम
mlx5e_sq_xmit_wqe(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb,
		  स्थिर काष्ठा mlx5e_tx_attr *attr, स्थिर काष्ठा mlx5e_tx_wqe_attr *wqe_attr,
		  काष्ठा mlx5e_tx_wqe *wqe, u16 pi, bool xmit_more)
अणु
	काष्ठा mlx5_wqe_ctrl_seg *cseg;
	काष्ठा mlx5_wqe_eth_seg  *eseg;
	काष्ठा mlx5_wqe_data_seg *dseg;
	काष्ठा mlx5e_tx_wqe_info *wi;

	काष्ठा mlx5e_sq_stats *stats = sq->stats;
	पूर्णांक num_dma;

	stats->xmit_more += xmit_more;

	/* fill wqe */
	wi   = &sq->db.wqe_info[pi];
	cseg = &wqe->ctrl;
	eseg = &wqe->eth;
	dseg =  wqe->data;

	eseg->mss = attr->mss;

	अगर (attr->ihs) अणु
		अगर (skb_vlan_tag_present(skb)) अणु
			eseg->अंतरभूत_hdr.sz |= cpu_to_be16(attr->ihs + VLAN_HLEN);
			mlx5e_insert_vlan(eseg->अंतरभूत_hdr.start, skb, attr->ihs);
			stats->added_vlan_packets++;
		पूर्ण अन्यथा अणु
			eseg->अंतरभूत_hdr.sz |= cpu_to_be16(attr->ihs);
			स_नकल(eseg->अंतरभूत_hdr.start, skb->data, attr->ihs);
		पूर्ण
		dseg += wqe_attr->ds_cnt_inl;
	पूर्ण अन्यथा अगर (skb_vlan_tag_present(skb)) अणु
		eseg->insert.type = cpu_to_be16(MLX5_ETH_WQE_INSERT_VLAN);
		अगर (skb->vlan_proto == cpu_to_be16(ETH_P_8021AD))
			eseg->insert.type |= cpu_to_be16(MLX5_ETH_WQE_SVLAN);
		eseg->insert.vlan_tci = cpu_to_be16(skb_vlan_tag_get(skb));
		stats->added_vlan_packets++;
	पूर्ण

	dseg += wqe_attr->ds_cnt_ids;
	num_dma = mlx5e_txwqe_build_dsegs(sq, skb, skb->data + attr->ihs,
					  attr->headlen, dseg);
	अगर (unlikely(num_dma < 0))
		जाओ err_drop;

	mlx5e_txwqe_complete(sq, skb, attr, wqe_attr, num_dma, wi, cseg, xmit_more);

	वापस;

err_drop:
	stats->dropped++;
	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल bool mlx5e_tx_skb_supports_mpwqe(काष्ठा sk_buff *skb, काष्ठा mlx5e_tx_attr *attr)
अणु
	वापस !skb_is_nonlinear(skb) && !skb_vlan_tag_present(skb) && !attr->ihs &&
	       !attr->insz;
पूर्ण

अटल bool mlx5e_tx_mpwqe_same_eseg(काष्ठा mlx5e_txqsq *sq, काष्ठा mlx5_wqe_eth_seg *eseg)
अणु
	काष्ठा mlx5e_tx_mpwqe *session = &sq->mpwqe;

	/* Assumes the session is alपढ़ोy running and has at least one packet. */
	वापस !स_भेद(&session->wqe->eth, eseg, MLX5E_ACCEL_ESEG_LEN);
पूर्ण

अटल व्योम mlx5e_tx_mpwqe_session_start(काष्ठा mlx5e_txqsq *sq,
					 काष्ठा mlx5_wqe_eth_seg *eseg)
अणु
	काष्ठा mlx5e_tx_mpwqe *session = &sq->mpwqe;
	काष्ठा mlx5e_tx_wqe *wqe;
	u16 pi;

	pi = mlx5e_txqsq_get_next_pi(sq, MLX5E_TX_MPW_MAX_WQEBBS);
	wqe = MLX5E_TX_FETCH_WQE(sq, pi);
	net_prefetchw(wqe->data);

	*session = (काष्ठा mlx5e_tx_mpwqe) अणु
		.wqe = wqe,
		.bytes_count = 0,
		.ds_count = MLX5E_TX_WQE_EMPTY_DS_COUNT,
		.pkt_count = 0,
		.अंतरभूत_on = 0,
	पूर्ण;

	स_नकल(&session->wqe->eth, eseg, MLX5E_ACCEL_ESEG_LEN);

	sq->stats->mpwqe_blks++;
पूर्ण

अटल bool mlx5e_tx_mpwqe_session_is_active(काष्ठा mlx5e_txqsq *sq)
अणु
	वापस sq->mpwqe.wqe;
पूर्ण

अटल व्योम mlx5e_tx_mpwqe_add_dseg(काष्ठा mlx5e_txqsq *sq, काष्ठा mlx5e_xmit_data *txd)
अणु
	काष्ठा mlx5e_tx_mpwqe *session = &sq->mpwqe;
	काष्ठा mlx5_wqe_data_seg *dseg;

	dseg = (काष्ठा mlx5_wqe_data_seg *)session->wqe + session->ds_count;

	session->pkt_count++;
	session->bytes_count += txd->len;

	dseg->addr = cpu_to_be64(txd->dma_addr);
	dseg->byte_count = cpu_to_be32(txd->len);
	dseg->lkey = sq->mkey_be;
	session->ds_count++;

	sq->stats->mpwqe_pkts++;
पूर्ण

अटल काष्ठा mlx5_wqe_ctrl_seg *mlx5e_tx_mpwqe_session_complete(काष्ठा mlx5e_txqsq *sq)
अणु
	काष्ठा mlx5e_tx_mpwqe *session = &sq->mpwqe;
	u8 ds_count = session->ds_count;
	काष्ठा mlx5_wqe_ctrl_seg *cseg;
	काष्ठा mlx5e_tx_wqe_info *wi;
	u16 pi;

	cseg = &session->wqe->ctrl;
	cseg->opmod_idx_opcode = cpu_to_be32((sq->pc << 8) | MLX5_OPCODE_ENHANCED_MPSW);
	cseg->qpn_ds = cpu_to_be32((sq->sqn << 8) | ds_count);

	pi = mlx5_wq_cyc_ctr2ix(&sq->wq, sq->pc);
	wi = &sq->db.wqe_info[pi];
	*wi = (काष्ठा mlx5e_tx_wqe_info) अणु
		.skb = शून्य,
		.num_bytes = session->bytes_count,
		.num_wqebbs = DIV_ROUND_UP(ds_count, MLX5_SEND_WQEBB_NUM_DS),
		.num_dma = session->pkt_count,
		.num_fअगरo_pkts = session->pkt_count,
	पूर्ण;

	sq->pc += wi->num_wqebbs;

	session->wqe = शून्य;

	mlx5e_tx_check_stop(sq);

	वापस cseg;
पूर्ण

अटल व्योम
mlx5e_sq_xmit_mpwqe(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb,
		    काष्ठा mlx5_wqe_eth_seg *eseg, bool xmit_more)
अणु
	काष्ठा mlx5_wqe_ctrl_seg *cseg;
	काष्ठा mlx5e_xmit_data txd;

	अगर (!mlx5e_tx_mpwqe_session_is_active(sq)) अणु
		mlx5e_tx_mpwqe_session_start(sq, eseg);
	पूर्ण अन्यथा अगर (!mlx5e_tx_mpwqe_same_eseg(sq, eseg)) अणु
		mlx5e_tx_mpwqe_session_complete(sq);
		mlx5e_tx_mpwqe_session_start(sq, eseg);
	पूर्ण

	sq->stats->xmit_more += xmit_more;

	txd.data = skb->data;
	txd.len = skb->len;

	txd.dma_addr = dma_map_single(sq->pdev, txd.data, txd.len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(sq->pdev, txd.dma_addr)))
		जाओ err_unmap;
	mlx5e_dma_push(sq, txd.dma_addr, txd.len, MLX5E_DMA_MAP_SINGLE);

	mlx5e_skb_fअगरo_push(&sq->db.skb_fअगरo, skb);

	mlx5e_tx_mpwqe_add_dseg(sq, &txd);

	mlx5e_tx_skb_update_hwts_flags(skb);

	अगर (unlikely(mlx5e_tx_mpwqe_is_full(&sq->mpwqe))) अणु
		/* Might stop the queue and affect the retval of __netdev_tx_sent_queue. */
		cseg = mlx5e_tx_mpwqe_session_complete(sq);

		अगर (__netdev_tx_sent_queue(sq->txq, txd.len, xmit_more))
			mlx5e_notअगरy_hw(&sq->wq, sq->pc, sq->uar_map, cseg);
	पूर्ण अन्यथा अगर (__netdev_tx_sent_queue(sq->txq, txd.len, xmit_more)) अणु
		/* Might stop the queue, but we were asked to ring the करोorbell anyway. */
		cseg = mlx5e_tx_mpwqe_session_complete(sq);

		mlx5e_notअगरy_hw(&sq->wq, sq->pc, sq->uar_map, cseg);
	पूर्ण

	वापस;

err_unmap:
	mlx5e_dma_unmap_wqe_err(sq, 1);
	sq->stats->dropped++;
	dev_kमुक्त_skb_any(skb);
पूर्ण

व्योम mlx5e_tx_mpwqe_ensure_complete(काष्ठा mlx5e_txqsq *sq)
अणु
	/* Unlikely in non-MPWQE workloads; not important in MPWQE workloads. */
	अगर (unlikely(mlx5e_tx_mpwqe_session_is_active(sq)))
		mlx5e_tx_mpwqe_session_complete(sq);
पूर्ण

अटल bool mlx5e_txwqe_build_eseg(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_txqsq *sq,
				   काष्ठा sk_buff *skb, काष्ठा mlx5e_accel_tx_state *accel,
				   काष्ठा mlx5_wqe_eth_seg *eseg, u16 ihs)
अणु
	अगर (unlikely(!mlx5e_accel_tx_eseg(priv, skb, eseg, ihs)))
		वापस false;

	mlx5e_txwqe_build_eseg_csum(sq, skb, accel, eseg);

	वापस true;
पूर्ण

netdev_tx_t mlx5e_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5e_accel_tx_state accel = अणुपूर्ण;
	काष्ठा mlx5e_tx_wqe_attr wqe_attr;
	काष्ठा mlx5e_tx_attr attr;
	काष्ठा mlx5e_tx_wqe *wqe;
	काष्ठा mlx5e_txqsq *sq;
	u16 pi;

	sq = priv->txq2sq[skb_get_queue_mapping(skb)];
	अगर (unlikely(!sq)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* May send SKBs and WQEs. */
	अगर (unlikely(!mlx5e_accel_tx_begin(dev, sq, skb, &accel)))
		वापस NETDEV_TX_OK;

	mlx5e_sq_xmit_prepare(sq, skb, &accel, &attr);

	अगर (test_bit(MLX5E_SQ_STATE_MPWQE, &sq->state)) अणु
		अगर (mlx5e_tx_skb_supports_mpwqe(skb, &attr)) अणु
			काष्ठा mlx5_wqe_eth_seg eseg = अणुपूर्ण;

			अगर (unlikely(!mlx5e_txwqe_build_eseg(priv, sq, skb, &accel, &eseg,
							     attr.ihs)))
				वापस NETDEV_TX_OK;

			mlx5e_sq_xmit_mpwqe(sq, skb, &eseg, netdev_xmit_more());
			वापस NETDEV_TX_OK;
		पूर्ण

		mlx5e_tx_mpwqe_ensure_complete(sq);
	पूर्ण

	mlx5e_sq_calc_wqe_attr(skb, &attr, &wqe_attr);
	pi = mlx5e_txqsq_get_next_pi(sq, wqe_attr.num_wqebbs);
	wqe = MLX5E_TX_FETCH_WQE(sq, pi);

	/* May update the WQE, but may not post other WQEs. */
	mlx5e_accel_tx_finish(sq, wqe, &accel,
			      (काष्ठा mlx5_wqe_अंतरभूत_seg *)(wqe->data + wqe_attr.ds_cnt_inl));
	अगर (unlikely(!mlx5e_txwqe_build_eseg(priv, sq, skb, &accel, &wqe->eth, attr.ihs)))
		वापस NETDEV_TX_OK;

	mlx5e_sq_xmit_wqe(sq, skb, &attr, &wqe_attr, wqe, pi, netdev_xmit_more());

	वापस NETDEV_TX_OK;
पूर्ण

व्योम mlx5e_sq_xmit_simple(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb, bool xmit_more)
अणु
	काष्ठा mlx5e_tx_wqe_attr wqe_attr;
	काष्ठा mlx5e_tx_attr attr;
	काष्ठा mlx5e_tx_wqe *wqe;
	u16 pi;

	mlx5e_sq_xmit_prepare(sq, skb, शून्य, &attr);
	mlx5e_sq_calc_wqe_attr(skb, &attr, &wqe_attr);
	pi = mlx5e_txqsq_get_next_pi(sq, wqe_attr.num_wqebbs);
	wqe = MLX5E_TX_FETCH_WQE(sq, pi);
	mlx5e_txwqe_build_eseg_csum(sq, skb, शून्य, &wqe->eth);
	mlx5e_sq_xmit_wqe(sq, skb, &attr, &wqe_attr, wqe, pi, xmit_more);
पूर्ण

अटल व्योम mlx5e_tx_wi_dma_unmap(काष्ठा mlx5e_txqsq *sq, काष्ठा mlx5e_tx_wqe_info *wi,
				  u32 *dma_fअगरo_cc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < wi->num_dma; i++) अणु
		काष्ठा mlx5e_sq_dma *dma = mlx5e_dma_get(sq, (*dma_fअगरo_cc)++);

		mlx5e_tx_dma_unmap(sq->pdev, dma);
	पूर्ण
पूर्ण

अटल व्योम mlx5e_consume_skb(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb,
			      काष्ठा mlx5_cqe64 *cqe, पूर्णांक napi_budget)
अणु
	अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)) अणु
		काष्ठा skb_shared_hwtstamps hwts = अणुपूर्ण;
		u64 ts = get_cqe_ts(cqe);

		hwts.hwtstamp = mlx5e_cqe_ts_to_ns(sq->ptp_cyc2समय, sq->घड़ी, ts);
		अगर (sq->ptpsq)
			mlx5e_skb_cb_hwtstamp_handler(skb, MLX5E_SKB_CB_CQE_HWTSTAMP,
						      hwts.hwtstamp, sq->ptpsq->cq_stats);
		अन्यथा
			skb_tstamp_tx(skb, &hwts);
	पूर्ण

	napi_consume_skb(skb, napi_budget);
पूर्ण

अटल व्योम mlx5e_tx_wi_consume_fअगरo_skbs(काष्ठा mlx5e_txqsq *sq, काष्ठा mlx5e_tx_wqe_info *wi,
					  काष्ठा mlx5_cqe64 *cqe, पूर्णांक napi_budget)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < wi->num_fअगरo_pkts; i++) अणु
		काष्ठा sk_buff *skb = mlx5e_skb_fअगरo_pop(&sq->db.skb_fअगरo);

		mlx5e_consume_skb(sq, skb, cqe, napi_budget);
	पूर्ण
पूर्ण

bool mlx5e_poll_tx_cq(काष्ठा mlx5e_cq *cq, पूर्णांक napi_budget)
अणु
	काष्ठा mlx5e_sq_stats *stats;
	काष्ठा mlx5e_txqsq *sq;
	काष्ठा mlx5_cqe64 *cqe;
	u32 dma_fअगरo_cc;
	u32 nbytes;
	u16 npkts;
	u16 sqcc;
	पूर्णांक i;

	sq = container_of(cq, काष्ठा mlx5e_txqsq, cq);

	अगर (unlikely(!test_bit(MLX5E_SQ_STATE_ENABLED, &sq->state)))
		वापस false;

	cqe = mlx5_cqwq_get_cqe(&cq->wq);
	अगर (!cqe)
		वापस false;

	stats = sq->stats;

	npkts = 0;
	nbytes = 0;

	/* sq->cc must be updated only after mlx5_cqwq_update_db_record(),
	 * otherwise a cq overrun may occur
	 */
	sqcc = sq->cc;

	/* aव्योम dirtying sq cache line every cqe */
	dma_fअगरo_cc = sq->dma_fअगरo_cc;

	i = 0;
	करो अणु
		काष्ठा mlx5e_tx_wqe_info *wi;
		u16 wqe_counter;
		bool last_wqe;
		u16 ci;

		mlx5_cqwq_pop(&cq->wq);

		wqe_counter = be16_to_cpu(cqe->wqe_counter);

		करो अणु
			last_wqe = (sqcc == wqe_counter);

			ci = mlx5_wq_cyc_ctr2ix(&sq->wq, sqcc);
			wi = &sq->db.wqe_info[ci];

			sqcc += wi->num_wqebbs;

			अगर (likely(wi->skb)) अणु
				mlx5e_tx_wi_dma_unmap(sq, wi, &dma_fअगरo_cc);
				mlx5e_consume_skb(sq, wi->skb, cqe, napi_budget);

				npkts++;
				nbytes += wi->num_bytes;
				जारी;
			पूर्ण

			अगर (unlikely(mlx5e_ktls_tx_try_handle_resync_dump_comp(sq, wi,
									       &dma_fअगरo_cc)))
				जारी;

			अगर (wi->num_fअगरo_pkts) अणु
				mlx5e_tx_wi_dma_unmap(sq, wi, &dma_fअगरo_cc);
				mlx5e_tx_wi_consume_fअगरo_skbs(sq, wi, cqe, napi_budget);

				npkts += wi->num_fअगरo_pkts;
				nbytes += wi->num_bytes;
			पूर्ण
		पूर्ण जबतक (!last_wqe);

		अगर (unlikely(get_cqe_opcode(cqe) == MLX5_CQE_REQ_ERR)) अणु
			अगर (!test_and_set_bit(MLX5E_SQ_STATE_RECOVERING,
					      &sq->state)) अणु
				mlx5e_dump_error_cqe(&sq->cq, sq->sqn,
						     (काष्ठा mlx5_err_cqe *)cqe);
				mlx5_wq_cyc_wqe_dump(&sq->wq, ci, wi->num_wqebbs);
				queue_work(cq->priv->wq, &sq->recover_work);
			पूर्ण
			stats->cqe_err++;
		पूर्ण

	पूर्ण जबतक ((++i < MLX5E_TX_CQ_POLL_BUDGET) && (cqe = mlx5_cqwq_get_cqe(&cq->wq)));

	stats->cqes += i;

	mlx5_cqwq_update_db_record(&cq->wq);

	/* ensure cq space is मुक्तd beक्रमe enabling more cqes */
	wmb();

	sq->dma_fअगरo_cc = dma_fअगरo_cc;
	sq->cc = sqcc;

	netdev_tx_completed_queue(sq->txq, npkts, nbytes);

	अगर (netअगर_tx_queue_stopped(sq->txq) &&
	    mlx5e_wqc_has_room_क्रम(&sq->wq, sq->cc, sq->pc, sq->stop_room) &&
	    !test_bit(MLX5E_SQ_STATE_RECOVERING, &sq->state)) अणु
		netअगर_tx_wake_queue(sq->txq);
		stats->wake++;
	पूर्ण

	वापस (i == MLX5E_TX_CQ_POLL_BUDGET);
पूर्ण

अटल व्योम mlx5e_tx_wi_kमुक्त_fअगरo_skbs(काष्ठा mlx5e_txqsq *sq, काष्ठा mlx5e_tx_wqe_info *wi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < wi->num_fअगरo_pkts; i++)
		dev_kमुक्त_skb_any(mlx5e_skb_fअगरo_pop(&sq->db.skb_fअगरo));
पूर्ण

व्योम mlx5e_मुक्त_txqsq_descs(काष्ठा mlx5e_txqsq *sq)
अणु
	काष्ठा mlx5e_tx_wqe_info *wi;
	u32 dma_fअगरo_cc, nbytes = 0;
	u16 ci, sqcc, npkts = 0;

	sqcc = sq->cc;
	dma_fअगरo_cc = sq->dma_fअगरo_cc;

	जबतक (sqcc != sq->pc) अणु
		ci = mlx5_wq_cyc_ctr2ix(&sq->wq, sqcc);
		wi = &sq->db.wqe_info[ci];

		sqcc += wi->num_wqebbs;

		अगर (likely(wi->skb)) अणु
			mlx5e_tx_wi_dma_unmap(sq, wi, &dma_fअगरo_cc);
			dev_kमुक्त_skb_any(wi->skb);

			npkts++;
			nbytes += wi->num_bytes;
			जारी;
		पूर्ण

		अगर (unlikely(mlx5e_ktls_tx_try_handle_resync_dump_comp(sq, wi, &dma_fअगरo_cc)))
			जारी;

		अगर (wi->num_fअगरo_pkts) अणु
			mlx5e_tx_wi_dma_unmap(sq, wi, &dma_fअगरo_cc);
			mlx5e_tx_wi_kमुक्त_fअगरo_skbs(sq, wi);

			npkts += wi->num_fअगरo_pkts;
			nbytes += wi->num_bytes;
		पूर्ण
	पूर्ण

	sq->dma_fअगरo_cc = dma_fअगरo_cc;
	sq->cc = sqcc;

	netdev_tx_completed_queue(sq->txq, npkts, nbytes);
पूर्ण

#अगर_घोषित CONFIG_MLX5_CORE_IPOIB
अटल अंतरभूत व्योम
mlx5i_txwqe_build_datagram(काष्ठा mlx5_av *av, u32 dqpn, u32 dqkey,
			   काष्ठा mlx5_wqe_datagram_seg *dseg)
अणु
	स_नकल(&dseg->av, av, माप(काष्ठा mlx5_av));
	dseg->av.dqp_dct = cpu_to_be32(dqpn | MLX5_EXTENDED_UD_AV);
	dseg->av.key.qkey.qkey = cpu_to_be32(dqkey);
पूर्ण

अटल व्योम mlx5i_sq_calc_wqe_attr(काष्ठा sk_buff *skb,
				   स्थिर काष्ठा mlx5e_tx_attr *attr,
				   काष्ठा mlx5e_tx_wqe_attr *wqe_attr)
अणु
	u16 ds_cnt = माप(काष्ठा mlx5i_tx_wqe) / MLX5_SEND_WQE_DS;
	u16 ds_cnt_inl = 0;

	ds_cnt += !!attr->headlen + skb_shinfo(skb)->nr_frags;

	अगर (attr->ihs) अणु
		u16 inl = attr->ihs - INL_HDR_START_SZ;

		ds_cnt_inl = DIV_ROUND_UP(inl, MLX5_SEND_WQE_DS);
		ds_cnt += ds_cnt_inl;
	पूर्ण

	*wqe_attr = (काष्ठा mlx5e_tx_wqe_attr) अणु
		.ds_cnt     = ds_cnt,
		.ds_cnt_inl = ds_cnt_inl,
		.num_wqebbs = DIV_ROUND_UP(ds_cnt, MLX5_SEND_WQEBB_NUM_DS),
	पूर्ण;
पूर्ण

व्योम mlx5i_sq_xmit(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb,
		   काष्ठा mlx5_av *av, u32 dqpn, u32 dqkey, bool xmit_more)
अणु
	काष्ठा mlx5e_tx_wqe_attr wqe_attr;
	काष्ठा mlx5e_tx_attr attr;
	काष्ठा mlx5i_tx_wqe *wqe;

	काष्ठा mlx5_wqe_datagram_seg *datagram;
	काष्ठा mlx5_wqe_ctrl_seg *cseg;
	काष्ठा mlx5_wqe_eth_seg  *eseg;
	काष्ठा mlx5_wqe_data_seg *dseg;
	काष्ठा mlx5e_tx_wqe_info *wi;

	काष्ठा mlx5e_sq_stats *stats = sq->stats;
	पूर्णांक num_dma;
	u16 pi;

	mlx5e_sq_xmit_prepare(sq, skb, शून्य, &attr);
	mlx5i_sq_calc_wqe_attr(skb, &attr, &wqe_attr);

	pi = mlx5e_txqsq_get_next_pi(sq, wqe_attr.num_wqebbs);
	wqe = MLX5I_SQ_FETCH_WQE(sq, pi);

	stats->xmit_more += xmit_more;

	/* fill wqe */
	wi       = &sq->db.wqe_info[pi];
	cseg     = &wqe->ctrl;
	datagram = &wqe->datagram;
	eseg     = &wqe->eth;
	dseg     =  wqe->data;

	mlx5i_txwqe_build_datagram(av, dqpn, dqkey, datagram);

	mlx5e_txwqe_build_eseg_csum(sq, skb, शून्य, eseg);

	eseg->mss = attr.mss;

	अगर (attr.ihs) अणु
		स_नकल(eseg->अंतरभूत_hdr.start, skb->data, attr.ihs);
		eseg->अंतरभूत_hdr.sz = cpu_to_be16(attr.ihs);
		dseg += wqe_attr.ds_cnt_inl;
	पूर्ण

	num_dma = mlx5e_txwqe_build_dsegs(sq, skb, skb->data + attr.ihs,
					  attr.headlen, dseg);
	अगर (unlikely(num_dma < 0))
		जाओ err_drop;

	mlx5e_txwqe_complete(sq, skb, &attr, &wqe_attr, num_dma, wi, cseg, xmit_more);

	वापस;

err_drop:
	stats->dropped++;
	dev_kमुक्त_skb_any(skb);
पूर्ण
#पूर्ण_अगर
