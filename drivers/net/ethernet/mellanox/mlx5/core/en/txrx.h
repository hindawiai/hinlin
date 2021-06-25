<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5_EN_TXRX_H___
#घोषणा __MLX5_EN_TXRX_H___

#समावेश "en.h"
#समावेश <linux/indirect_call_wrapper.h>

#घोषणा MLX5E_TX_WQE_EMPTY_DS_COUNT (माप(काष्ठा mlx5e_tx_wqe) / MLX5_SEND_WQE_DS)

/* The mult of MLX5_SEND_WQE_MAX_WQEBBS * MLX5_SEND_WQEBB_NUM_DS
 * (16 * 4 == 64) करोes not fit in the 6-bit DS field of Ctrl Segment.
 * We use a bound lower that MLX5_SEND_WQE_MAX_WQEBBS to let a
 * full-session WQE be cache-aligned.
 */
#अगर L1_CACHE_BYTES < 128
#घोषणा MLX5E_TX_MPW_MAX_WQEBBS (MLX5_SEND_WQE_MAX_WQEBBS - 1)
#अन्यथा
#घोषणा MLX5E_TX_MPW_MAX_WQEBBS (MLX5_SEND_WQE_MAX_WQEBBS - 2)
#पूर्ण_अगर

#घोषणा MLX5E_TX_MPW_MAX_NUM_DS (MLX5E_TX_MPW_MAX_WQEBBS * MLX5_SEND_WQEBB_NUM_DS)

#घोषणा INL_HDR_START_SZ (माप(((काष्ठा mlx5_wqe_eth_seg *)शून्य)->अंतरभूत_hdr.start))

#घोषणा MLX5E_RX_ERR_CQE(cqe) (get_cqe_opcode(cqe) != MLX5_CQE_RESP_SEND)

अटल अंतरभूत
kसमय_प्रकार mlx5e_cqe_ts_to_ns(cqe_ts_to_ns func, काष्ठा mlx5_घड़ी *घड़ी, u64 cqe_ts)
अणु
	वापस INसूचीECT_CALL_2(func, mlx5_real_समय_cyc2समय, mlx5_समयcounter_cyc2समय,
			       घड़ी, cqe_ts);
पूर्ण

क्रमागत mlx5e_icosq_wqe_type अणु
	MLX5E_ICOSQ_WQE_NOP,
	MLX5E_ICOSQ_WQE_UMR_RX,
#अगर_घोषित CONFIG_MLX5_EN_TLS
	MLX5E_ICOSQ_WQE_UMR_TLS,
	MLX5E_ICOSQ_WQE_SET_PSV_TLS,
	MLX5E_ICOSQ_WQE_GET_PSV_TLS,
#पूर्ण_अगर
पूर्ण;

/* General */
अटल अंतरभूत bool mlx5e_skb_is_multicast(काष्ठा sk_buff *skb)
अणु
	वापस skb->pkt_type == PACKET_MULTICAST || skb->pkt_type == PACKET_BROADCAST;
पूर्ण

व्योम mlx5e_trigger_irq(काष्ठा mlx5e_icosq *sq);
व्योम mlx5e_completion_event(काष्ठा mlx5_core_cq *mcq, काष्ठा mlx5_eqe *eqe);
व्योम mlx5e_cq_error_event(काष्ठा mlx5_core_cq *mcq, क्रमागत mlx5_event event);
पूर्णांक mlx5e_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
पूर्णांक mlx5e_poll_ico_cq(काष्ठा mlx5e_cq *cq);

/* RX */
व्योम mlx5e_page_dma_unmap(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_dma_info *dma_info);
व्योम mlx5e_page_release_dynamic(काष्ठा mlx5e_rq *rq,
				काष्ठा mlx5e_dma_info *dma_info,
				bool recycle);
INसूचीECT_CALLABLE_DECLARE(bool mlx5e_post_rx_wqes(काष्ठा mlx5e_rq *rq));
INसूचीECT_CALLABLE_DECLARE(bool mlx5e_post_rx_mpwqes(काष्ठा mlx5e_rq *rq));
पूर्णांक mlx5e_poll_rx_cq(काष्ठा mlx5e_cq *cq, पूर्णांक budget);
व्योम mlx5e_मुक्त_rx_descs(काष्ठा mlx5e_rq *rq);
व्योम mlx5e_मुक्त_rx_in_progress_descs(काष्ठा mlx5e_rq *rq);

/* TX */
u16 mlx5e_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		       काष्ठा net_device *sb_dev);
netdev_tx_t mlx5e_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
bool mlx5e_poll_tx_cq(काष्ठा mlx5e_cq *cq, पूर्णांक napi_budget);
व्योम mlx5e_मुक्त_txqsq_descs(काष्ठा mlx5e_txqsq *sq);

अटल अंतरभूत bool
mlx5e_wqc_has_room_क्रम(काष्ठा mlx5_wq_cyc *wq, u16 cc, u16 pc, u16 n)
अणु
	वापस (mlx5_wq_cyc_ctr2ix(wq, cc - pc) >= n) || (cc == pc);
पूर्ण

अटल अंतरभूत व्योम *mlx5e_fetch_wqe(काष्ठा mlx5_wq_cyc *wq, u16 pi, माप_प्रकार wqe_size)
अणु
	व्योम *wqe;

	wqe = mlx5_wq_cyc_get_wqe(wq, pi);
	स_रखो(wqe, 0, wqe_size);

	वापस wqe;
पूर्ण

#घोषणा MLX5E_TX_FETCH_WQE(sq, pi) \
	((काष्ठा mlx5e_tx_wqe *)mlx5e_fetch_wqe(&(sq)->wq, pi, माप(काष्ठा mlx5e_tx_wqe)))

अटल अंतरभूत काष्ठा mlx5e_tx_wqe *
mlx5e_post_nop(काष्ठा mlx5_wq_cyc *wq, u32 sqn, u16 *pc)
अणु
	u16                         pi   = mlx5_wq_cyc_ctr2ix(wq, *pc);
	काष्ठा mlx5e_tx_wqe        *wqe  = mlx5_wq_cyc_get_wqe(wq, pi);
	काष्ठा mlx5_wqe_ctrl_seg   *cseg = &wqe->ctrl;

	स_रखो(cseg, 0, माप(*cseg));

	cseg->opmod_idx_opcode = cpu_to_be32((*pc << 8) | MLX5_OPCODE_NOP);
	cseg->qpn_ds           = cpu_to_be32((sqn << 8) | 0x01);

	(*pc)++;

	वापस wqe;
पूर्ण

अटल अंतरभूत काष्ठा mlx5e_tx_wqe *
mlx5e_post_nop_fence(काष्ठा mlx5_wq_cyc *wq, u32 sqn, u16 *pc)
अणु
	u16                         pi   = mlx5_wq_cyc_ctr2ix(wq, *pc);
	काष्ठा mlx5e_tx_wqe        *wqe  = mlx5_wq_cyc_get_wqe(wq, pi);
	काष्ठा mlx5_wqe_ctrl_seg   *cseg = &wqe->ctrl;

	स_रखो(cseg, 0, माप(*cseg));

	cseg->opmod_idx_opcode = cpu_to_be32((*pc << 8) | MLX5_OPCODE_NOP);
	cseg->qpn_ds           = cpu_to_be32((sqn << 8) | 0x01);
	cseg->fm_ce_se         = MLX5_FENCE_MODE_INITIATOR_SMALL;

	(*pc)++;

	वापस wqe;
पूर्ण

काष्ठा mlx5e_tx_wqe_info अणु
	काष्ठा sk_buff *skb;
	u32 num_bytes;
	u8 num_wqebbs;
	u8 num_dma;
	u8 num_fअगरo_pkts;
#अगर_घोषित CONFIG_MLX5_EN_TLS
	काष्ठा page *resync_dump_frag_page;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत u16 mlx5e_txqsq_get_next_pi(काष्ठा mlx5e_txqsq *sq, u16 size)
अणु
	काष्ठा mlx5_wq_cyc *wq = &sq->wq;
	u16 pi, contig_wqebbs;

	pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
	contig_wqebbs = mlx5_wq_cyc_get_contig_wqebbs(wq, pi);
	अगर (unlikely(contig_wqebbs < size)) अणु
		काष्ठा mlx5e_tx_wqe_info *wi, *edge_wi;

		wi = &sq->db.wqe_info[pi];
		edge_wi = wi + contig_wqebbs;

		/* Fill SQ frag edge with NOPs to aव्योम WQE wrapping two pages. */
		क्रम (; wi < edge_wi; wi++) अणु
			*wi = (काष्ठा mlx5e_tx_wqe_info) अणु
				.num_wqebbs = 1,
			पूर्ण;
			mlx5e_post_nop(wq, sq->sqn, &sq->pc);
		पूर्ण
		sq->stats->nop += contig_wqebbs;

		pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
	पूर्ण

	वापस pi;
पूर्ण

काष्ठा mlx5e_icosq_wqe_info अणु
	u8 wqe_type;
	u8 num_wqebbs;

	/* Auxiliary data क्रम dअगरferent wqe types. */
	जोड़ अणु
		काष्ठा अणु
			काष्ठा mlx5e_rq *rq;
		पूर्ण umr;
#अगर_घोषित CONFIG_MLX5_EN_TLS
		काष्ठा अणु
			काष्ठा mlx5e_ktls_offload_context_rx *priv_rx;
		पूर्ण tls_set_params;
		काष्ठा अणु
			काष्ठा mlx5e_ktls_rx_resync_buf *buf;
		पूर्ण tls_get_params;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

व्योम mlx5e_मुक्त_icosq_descs(काष्ठा mlx5e_icosq *sq);

अटल अंतरभूत u16 mlx5e_icosq_get_next_pi(काष्ठा mlx5e_icosq *sq, u16 size)
अणु
	काष्ठा mlx5_wq_cyc *wq = &sq->wq;
	u16 pi, contig_wqebbs;

	pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
	contig_wqebbs = mlx5_wq_cyc_get_contig_wqebbs(wq, pi);
	अगर (unlikely(contig_wqebbs < size)) अणु
		काष्ठा mlx5e_icosq_wqe_info *wi, *edge_wi;

		wi = &sq->db.wqe_info[pi];
		edge_wi = wi + contig_wqebbs;

		/* Fill SQ frag edge with NOPs to aव्योम WQE wrapping two pages. */
		क्रम (; wi < edge_wi; wi++) अणु
			*wi = (काष्ठा mlx5e_icosq_wqe_info) अणु
				.wqe_type   = MLX5E_ICOSQ_WQE_NOP,
				.num_wqebbs = 1,
			पूर्ण;
			mlx5e_post_nop(wq, sq->sqn, &sq->pc);
		पूर्ण

		pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
	पूर्ण

	वापस pi;
पूर्ण

अटल अंतरभूत व्योम
mlx5e_notअगरy_hw(काष्ठा mlx5_wq_cyc *wq, u16 pc, व्योम __iomem *uar_map,
		काष्ठा mlx5_wqe_ctrl_seg *ctrl)
अणु
	ctrl->fm_ce_se |= MLX5_WQE_CTRL_CQ_UPDATE;
	/* ensure wqe is visible to device beक्रमe updating करोorbell record */
	dma_wmb();

	*wq->db = cpu_to_be32(pc);

	/* ensure करोorbell record is visible to device beक्रमe ringing the
	 * करोorbell
	 */
	wmb();

	mlx5_ग_लिखो64((__be32 *)ctrl, uar_map);
पूर्ण

अटल अंतरभूत व्योम mlx5e_cq_arm(काष्ठा mlx5e_cq *cq)
अणु
	काष्ठा mlx5_core_cq *mcq;

	mcq = &cq->mcq;
	mlx5_cq_arm(mcq, MLX5_CQ_DB_REQ_NOT, mcq->uar->map, cq->wq.cc);
पूर्ण

अटल अंतरभूत काष्ठा mlx5e_sq_dma *
mlx5e_dma_get(काष्ठा mlx5e_txqsq *sq, u32 i)
अणु
	वापस &sq->db.dma_fअगरo[i & sq->dma_fअगरo_mask];
पूर्ण

अटल अंतरभूत व्योम
mlx5e_dma_push(काष्ठा mlx5e_txqsq *sq, dma_addr_t addr, u32 size,
	       क्रमागत mlx5e_dma_map_type map_type)
अणु
	काष्ठा mlx5e_sq_dma *dma = mlx5e_dma_get(sq, sq->dma_fअगरo_pc++);

	dma->addr = addr;
	dma->size = size;
	dma->type = map_type;
पूर्ण

अटल अंतरभूत
काष्ठा sk_buff **mlx5e_skb_fअगरo_get(काष्ठा mlx5e_skb_fअगरo *fअगरo, u16 i)
अणु
	वापस &fअगरo->fअगरo[i & fअगरo->mask];
पूर्ण

अटल अंतरभूत
व्योम mlx5e_skb_fअगरo_push(काष्ठा mlx5e_skb_fअगरo *fअगरo, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff **skb_item = mlx5e_skb_fअगरo_get(fअगरo, (*fअगरo->pc)++);

	*skb_item = skb;
पूर्ण

अटल अंतरभूत
काष्ठा sk_buff *mlx5e_skb_fअगरo_pop(काष्ठा mlx5e_skb_fअगरo *fअगरo)
अणु
	वापस *mlx5e_skb_fअगरo_get(fअगरo, (*fअगरo->cc)++);
पूर्ण

अटल अंतरभूत व्योम
mlx5e_tx_dma_unmap(काष्ठा device *pdev, काष्ठा mlx5e_sq_dma *dma)
अणु
	चयन (dma->type) अणु
	हाल MLX5E_DMA_MAP_SINGLE:
		dma_unmap_single(pdev, dma->addr, dma->size, DMA_TO_DEVICE);
		अवरोध;
	हाल MLX5E_DMA_MAP_PAGE:
		dma_unmap_page(pdev, dma->addr, dma->size, DMA_TO_DEVICE);
		अवरोध;
	शेष:
		WARN_ONCE(true, "mlx5e_tx_dma_unmap unknown DMA type!\n");
	पूर्ण
पूर्ण

व्योम mlx5e_sq_xmit_simple(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb, bool xmit_more);
व्योम mlx5e_tx_mpwqe_ensure_complete(काष्ठा mlx5e_txqsq *sq);

अटल अंतरभूत bool mlx5e_tx_mpwqe_is_full(काष्ठा mlx5e_tx_mpwqe *session)
अणु
	वापस session->ds_count == MLX5E_TX_MPW_MAX_NUM_DS;
पूर्ण

अटल अंतरभूत व्योम mlx5e_rqwq_reset(काष्ठा mlx5e_rq *rq)
अणु
	अगर (rq->wq_type == MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ) अणु
		mlx5_wq_ll_reset(&rq->mpwqe.wq);
		rq->mpwqe.actual_wq_head = 0;
	पूर्ण अन्यथा अणु
		mlx5_wq_cyc_reset(&rq->wqe.wq);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mlx5e_dump_error_cqe(काष्ठा mlx5e_cq *cq, u32 qn,
					काष्ठा mlx5_err_cqe *err_cqe)
अणु
	काष्ठा mlx5_cqwq *wq = &cq->wq;
	u32 ci;

	ci = mlx5_cqwq_ctr2ix(wq, wq->cc - 1);

	netdev_err(cq->netdev,
		   "Error cqe on cqn 0x%x, ci 0x%x, qn 0x%x, opcode 0x%x, syndrome 0x%x, vendor syndrome 0x%x\n",
		   cq->mcq.cqn, ci, qn,
		   get_cqe_opcode((काष्ठा mlx5_cqe64 *)err_cqe),
		   err_cqe->syndrome, err_cqe->venकरोr_err_synd);
	mlx5_dump_err_cqe(cq->mdev, err_cqe);
पूर्ण

अटल अंतरभूत u32 mlx5e_rqwq_get_size(काष्ठा mlx5e_rq *rq)
अणु
	चयन (rq->wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		वापस mlx5_wq_ll_get_size(&rq->mpwqe.wq);
	शेष:
		वापस mlx5_wq_cyc_get_size(&rq->wqe.wq);
	पूर्ण
पूर्ण

अटल अंतरभूत u32 mlx5e_rqwq_get_cur_sz(काष्ठा mlx5e_rq *rq)
अणु
	चयन (rq->wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		वापस rq->mpwqe.wq.cur_sz;
	शेष:
		वापस rq->wqe.wq.cur_sz;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 mlx5e_rqwq_get_head(काष्ठा mlx5e_rq *rq)
अणु
	चयन (rq->wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		वापस mlx5_wq_ll_get_head(&rq->mpwqe.wq);
	शेष:
		वापस mlx5_wq_cyc_get_head(&rq->wqe.wq);
	पूर्ण
पूर्ण

अटल अंतरभूत u16 mlx5e_rqwq_get_wqe_counter(काष्ठा mlx5e_rq *rq)
अणु
	चयन (rq->wq_type) अणु
	हाल MLX5_WQ_TYPE_LINKED_LIST_STRIDING_RQ:
		वापस mlx5_wq_ll_get_counter(&rq->mpwqe.wq);
	शेष:
		वापस mlx5_wq_cyc_get_counter(&rq->wqe.wq);
	पूर्ण
पूर्ण

/* SW parser related functions */

काष्ठा mlx5e_swp_spec अणु
	__be16 l3_proto;
	u8 l4_proto;
	u8 is_tun;
	__be16 tun_l3_proto;
	u8 tun_l4_proto;
पूर्ण;

अटल अंतरभूत व्योम mlx5e_eseg_swp_offsets_add_vlan(काष्ठा mlx5_wqe_eth_seg *eseg)
अणु
	/* SWP offsets are in 2-bytes words */
	eseg->swp_outer_l3_offset += VLAN_HLEN / 2;
	eseg->swp_outer_l4_offset += VLAN_HLEN / 2;
	eseg->swp_inner_l3_offset += VLAN_HLEN / 2;
	eseg->swp_inner_l4_offset += VLAN_HLEN / 2;
पूर्ण

अटल अंतरभूत व्योम
mlx5e_set_eseg_swp(काष्ठा sk_buff *skb, काष्ठा mlx5_wqe_eth_seg *eseg,
		   काष्ठा mlx5e_swp_spec *swp_spec)
अणु
	/* SWP offsets are in 2-bytes words */
	eseg->swp_outer_l3_offset = skb_network_offset(skb) / 2;
	अगर (swp_spec->l3_proto == htons(ETH_P_IPV6))
		eseg->swp_flags |= MLX5_ETH_WQE_SWP_OUTER_L3_IPV6;
	अगर (swp_spec->l4_proto) अणु
		eseg->swp_outer_l4_offset = skb_transport_offset(skb) / 2;
		अगर (swp_spec->l4_proto == IPPROTO_UDP)
			eseg->swp_flags |= MLX5_ETH_WQE_SWP_OUTER_L4_UDP;
	पूर्ण

	अगर (swp_spec->is_tun) अणु
		eseg->swp_inner_l3_offset = skb_inner_network_offset(skb) / 2;
		अगर (swp_spec->tun_l3_proto == htons(ETH_P_IPV6))
			eseg->swp_flags |= MLX5_ETH_WQE_SWP_INNER_L3_IPV6;
	पूर्ण अन्यथा अणु /* typically क्रम ipsec when xfrm mode != XFRM_MODE_TUNNEL */
		eseg->swp_inner_l3_offset = skb_network_offset(skb) / 2;
		अगर (swp_spec->l3_proto == htons(ETH_P_IPV6))
			eseg->swp_flags |= MLX5_ETH_WQE_SWP_INNER_L3_IPV6;
	पूर्ण
	चयन (swp_spec->tun_l4_proto) अणु
	हाल IPPROTO_UDP:
		eseg->swp_flags |= MLX5_ETH_WQE_SWP_INNER_L4_UDP;
		fallthrough;
	हाल IPPROTO_TCP:
		eseg->swp_inner_l4_offset = skb_inner_transport_offset(skb) / 2;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 mlx5e_stop_room_क्रम_wqe(u16 wqe_size)
अणु
	BUILD_BUG_ON(PAGE_SIZE / MLX5_SEND_WQE_BB < MLX5_SEND_WQE_MAX_WQEBBS);

	/* A WQE must not cross the page boundary, hence two conditions:
	 * 1. Its size must not exceed the page size.
	 * 2. If the WQE size is X, and the space reमुख्यing in a page is less
	 *    than X, this space needs to be padded with NOPs. So, one WQE of
	 *    size X may require up to X-1 WQEBBs of padding, which makes the
	 *    stop room of X-1 + X.
	 * WQE size is also limited by the hardware limit.
	 */

	अगर (__builtin_स्थिरant_p(wqe_size))
		BUILD_BUG_ON(wqe_size > MLX5_SEND_WQE_MAX_WQEBBS);
	अन्यथा
		WARN_ON_ONCE(wqe_size > MLX5_SEND_WQE_MAX_WQEBBS);

	वापस wqe_size * 2 - 1;
पूर्ण

अटल अंतरभूत bool mlx5e_icosq_can_post_wqe(काष्ठा mlx5e_icosq *sq, u16 wqe_size)
अणु
	u16 room = sq->reserved_room + mlx5e_stop_room_क्रम_wqe(wqe_size);

	वापस mlx5e_wqc_has_room_क्रम(&sq->wq, sq->cc, sq->pc, room);
पूर्ण
#पूर्ण_अगर
