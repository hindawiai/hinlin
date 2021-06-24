<शैली गुरु>
/*
 * Copyright (c) 2018, Mellanox Technologies. All rights reserved.
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

#समावेश <linux/bpf_trace.h>
#समावेश <net/xdp_sock_drv.h>
#समावेश "en/xdp.h"
#समावेश "en/params.h"

पूर्णांक mlx5e_xdp_max_mtu(काष्ठा mlx5e_params *params, काष्ठा mlx5e_xsk_param *xsk)
अणु
	पूर्णांक hr = mlx5e_get_linear_rq_headroom(params, xsk);

	/* Let S := SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)).
	 * The condition checked in mlx5e_rx_is_linear_skb is:
	 *   SKB_DATA_ALIGN(sw_mtu + hard_mtu + hr) + S <= PAGE_SIZE         (1)
	 *   (Note that hw_mtu == sw_mtu + hard_mtu.)
	 * What is वापसed from this function is:
	 *   max_mtu = PAGE_SIZE - S - hr - hard_mtu                         (2)
	 * After assigning sw_mtu := max_mtu, the left side of (1) turns to
	 * SKB_DATA_ALIGN(PAGE_SIZE - S) + S, which is equal to PAGE_SIZE,
	 * because both PAGE_SIZE and S are alपढ़ोy aligned. Any number greater
	 * than max_mtu would make the left side of (1) greater than PAGE_SIZE,
	 * so max_mtu is the maximum MTU allowed.
	 */

	वापस MLX5E_HW2SW_MTU(params, SKB_MAX_HEAD(hr));
पूर्ण

अटल अंतरभूत bool
mlx5e_xmit_xdp_buff(काष्ठा mlx5e_xdpsq *sq, काष्ठा mlx5e_rq *rq,
		    काष्ठा mlx5e_dma_info *di, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा mlx5e_xmit_data xdptxd;
	काष्ठा mlx5e_xdp_info xdpi;
	काष्ठा xdp_frame *xdpf;
	dma_addr_t dma_addr;

	xdpf = xdp_convert_buff_to_frame(xdp);
	अगर (unlikely(!xdpf))
		वापस false;

	xdptxd.data = xdpf->data;
	xdptxd.len  = xdpf->len;

	अगर (xdp->rxq->mem.type == MEM_TYPE_XSK_BUFF_POOL) अणु
		/* The xdp_buff was in the UMEM and was copied पूर्णांकo a newly
		 * allocated page. The UMEM page was वापसed via the ZCA, and
		 * this new page has to be mapped at this poपूर्णांक and has to be
		 * unmapped and वापसed via xdp_वापस_frame on completion.
		 */

		/* Prevent द्विगुन recycling of the UMEM page. Even in हाल this
		 * function वापसs false, the xdp_buff shouldn't be recycled,
		 * as it was alपढ़ोy करोne in xdp_convert_zc_to_xdp_frame.
		 */
		__set_bit(MLX5E_RQ_FLAG_XDP_XMIT, rq->flags); /* non-atomic */

		xdpi.mode = MLX5E_XDP_XMIT_MODE_FRAME;

		dma_addr = dma_map_single(sq->pdev, xdptxd.data, xdptxd.len,
					  DMA_TO_DEVICE);
		अगर (dma_mapping_error(sq->pdev, dma_addr)) अणु
			xdp_वापस_frame(xdpf);
			वापस false;
		पूर्ण

		xdptxd.dma_addr     = dma_addr;
		xdpi.frame.xdpf     = xdpf;
		xdpi.frame.dma_addr = dma_addr;
	पूर्ण अन्यथा अणु
		/* Driver assumes that xdp_convert_buff_to_frame वापसs
		 * an xdp_frame that poपूर्णांकs to the same memory region as
		 * the original xdp_buff. It allows to map the memory only
		 * once and to use the DMA_BIसूचीECTIONAL mode.
		 */

		xdpi.mode = MLX5E_XDP_XMIT_MODE_PAGE;

		dma_addr = di->addr + (xdpf->data - (व्योम *)xdpf);
		dma_sync_single_क्रम_device(sq->pdev, dma_addr, xdptxd.len,
					   DMA_TO_DEVICE);

		xdptxd.dma_addr = dma_addr;
		xdpi.page.rq    = rq;
		xdpi.page.di    = *di;
	पूर्ण

	वापस INसूचीECT_CALL_2(sq->xmit_xdp_frame, mlx5e_xmit_xdp_frame_mpwqe,
			       mlx5e_xmit_xdp_frame, sq, &xdptxd, &xdpi, 0);
पूर्ण

/* वापसs true अगर packet was consumed by xdp */
bool mlx5e_xdp_handle(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_dma_info *di,
		      u32 *len, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा bpf_prog *prog = rcu_dereference(rq->xdp_prog);
	u32 act;
	पूर्णांक err;

	अगर (!prog)
		वापस false;

	act = bpf_prog_run_xdp(prog, xdp);
	चयन (act) अणु
	हाल XDP_PASS:
		*len = xdp->data_end - xdp->data;
		वापस false;
	हाल XDP_TX:
		अगर (unlikely(!mlx5e_xmit_xdp_buff(rq->xdpsq, rq, di, xdp)))
			जाओ xdp_पात;
		__set_bit(MLX5E_RQ_FLAG_XDP_XMIT, rq->flags); /* non-atomic */
		वापस true;
	हाल XDP_REसूचीECT:
		/* When XDP enabled then page-refcnt==1 here */
		err = xdp_करो_redirect(rq->netdev, xdp, prog);
		अगर (unlikely(err))
			जाओ xdp_पात;
		__set_bit(MLX5E_RQ_FLAG_XDP_XMIT, rq->flags);
		__set_bit(MLX5E_RQ_FLAG_XDP_REसूचीECT, rq->flags);
		अगर (xdp->rxq->mem.type != MEM_TYPE_XSK_BUFF_POOL)
			mlx5e_page_dma_unmap(rq, di);
		rq->stats->xdp_redirect++;
		वापस true;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
xdp_पात:
		trace_xdp_exception(rq->netdev, prog, act);
		fallthrough;
	हाल XDP_DROP:
		rq->stats->xdp_drop++;
		वापस true;
	पूर्ण
पूर्ण

अटल u16 mlx5e_xdpsq_get_next_pi(काष्ठा mlx5e_xdpsq *sq, u16 size)
अणु
	काष्ठा mlx5_wq_cyc *wq = &sq->wq;
	u16 pi, contig_wqebbs;

	pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
	contig_wqebbs = mlx5_wq_cyc_get_contig_wqebbs(wq, pi);
	अगर (unlikely(contig_wqebbs < size)) अणु
		काष्ठा mlx5e_xdp_wqe_info *wi, *edge_wi;

		wi = &sq->db.wqe_info[pi];
		edge_wi = wi + contig_wqebbs;

		/* Fill SQ frag edge with NOPs to aव्योम WQE wrapping two pages. */
		क्रम (; wi < edge_wi; wi++) अणु
			*wi = (काष्ठा mlx5e_xdp_wqe_info) अणु
				.num_wqebbs = 1,
				.num_pkts = 0,
			पूर्ण;
			mlx5e_post_nop(wq, sq->sqn, &sq->pc);
		पूर्ण
		sq->stats->nops += contig_wqebbs;

		pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
	पूर्ण

	वापस pi;
पूर्ण

अटल व्योम mlx5e_xdp_mpwqe_session_start(काष्ठा mlx5e_xdpsq *sq)
अणु
	काष्ठा mlx5e_tx_mpwqe *session = &sq->mpwqe;
	काष्ठा mlx5e_xdpsq_stats *stats = sq->stats;
	काष्ठा mlx5e_tx_wqe *wqe;
	u16 pi;

	pi = mlx5e_xdpsq_get_next_pi(sq, MLX5E_TX_MPW_MAX_WQEBBS);
	wqe = MLX5E_TX_FETCH_WQE(sq, pi);
	net_prefetchw(wqe->data);

	*session = (काष्ठा mlx5e_tx_mpwqe) अणु
		.wqe = wqe,
		.bytes_count = 0,
		.ds_count = MLX5E_TX_WQE_EMPTY_DS_COUNT,
		.pkt_count = 0,
		.अंतरभूत_on = mlx5e_xdp_get_अंतरभूत_state(sq, session->अंतरभूत_on),
	पूर्ण;

	stats->mpwqe++;
पूर्ण

व्योम mlx5e_xdp_mpwqe_complete(काष्ठा mlx5e_xdpsq *sq)
अणु
	काष्ठा mlx5_wq_cyc       *wq    = &sq->wq;
	काष्ठा mlx5e_tx_mpwqe *session = &sq->mpwqe;
	काष्ठा mlx5_wqe_ctrl_seg *cseg = &session->wqe->ctrl;
	u16 ds_count = session->ds_count;
	u16 pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
	काष्ठा mlx5e_xdp_wqe_info *wi = &sq->db.wqe_info[pi];

	cseg->opmod_idx_opcode =
		cpu_to_be32((sq->pc << 8) | MLX5_OPCODE_ENHANCED_MPSW);
	cseg->qpn_ds = cpu_to_be32((sq->sqn << 8) | ds_count);

	wi->num_wqebbs = DIV_ROUND_UP(ds_count, MLX5_SEND_WQEBB_NUM_DS);
	wi->num_pkts   = session->pkt_count;

	sq->pc += wi->num_wqebbs;

	sq->करोorbell_cseg = cseg;

	session->wqe = शून्य; /* Close session */
पूर्ण

क्रमागत अणु
	MLX5E_XDP_CHECK_OK = 1,
	MLX5E_XDP_CHECK_START_MPWQE = 2,
पूर्ण;

INसूचीECT_CALLABLE_SCOPE पूर्णांक mlx5e_xmit_xdp_frame_check_mpwqe(काष्ठा mlx5e_xdpsq *sq)
अणु
	अगर (unlikely(!sq->mpwqe.wqe)) अणु
		स्थिर u16 stop_room = mlx5e_stop_room_क्रम_wqe(MLX5_SEND_WQE_MAX_WQEBBS);

		अगर (unlikely(!mlx5e_wqc_has_room_क्रम(&sq->wq, sq->cc, sq->pc,
						     stop_room))) अणु
			/* SQ is full, ring करोorbell */
			mlx5e_xmit_xdp_करोorbell(sq);
			sq->stats->full++;
			वापस -EBUSY;
		पूर्ण

		वापस MLX5E_XDP_CHECK_START_MPWQE;
	पूर्ण

	वापस MLX5E_XDP_CHECK_OK;
पूर्ण

INसूचीECT_CALLABLE_SCOPE bool
mlx5e_xmit_xdp_frame_mpwqe(काष्ठा mlx5e_xdpsq *sq, काष्ठा mlx5e_xmit_data *xdptxd,
			   काष्ठा mlx5e_xdp_info *xdpi, पूर्णांक check_result)
अणु
	काष्ठा mlx5e_tx_mpwqe *session = &sq->mpwqe;
	काष्ठा mlx5e_xdpsq_stats *stats = sq->stats;

	अगर (unlikely(xdptxd->len > sq->hw_mtu)) अणु
		stats->err++;
		वापस false;
	पूर्ण

	अगर (!check_result)
		check_result = mlx5e_xmit_xdp_frame_check_mpwqe(sq);
	अगर (unlikely(check_result < 0))
		वापस false;

	अगर (check_result == MLX5E_XDP_CHECK_START_MPWQE) अणु
		/* Start the session when nothing can fail, so it's guaranteed
		 * that अगर there is an active session, it has at least one dseg,
		 * and it's safe to complete it at any समय.
		 */
		mlx5e_xdp_mpwqe_session_start(sq);
	पूर्ण

	mlx5e_xdp_mpwqe_add_dseg(sq, xdptxd, stats);

	अगर (unlikely(mlx5e_xdp_mpqwe_is_full(session)))
		mlx5e_xdp_mpwqe_complete(sq);

	mlx5e_xdpi_fअगरo_push(&sq->db.xdpi_fअगरo, xdpi);
	stats->xmit++;
	वापस true;
पूर्ण

INसूचीECT_CALLABLE_SCOPE पूर्णांक mlx5e_xmit_xdp_frame_check(काष्ठा mlx5e_xdpsq *sq)
अणु
	अगर (unlikely(!mlx5e_wqc_has_room_क्रम(&sq->wq, sq->cc, sq->pc, 1))) अणु
		/* SQ is full, ring करोorbell */
		mlx5e_xmit_xdp_करोorbell(sq);
		sq->stats->full++;
		वापस -EBUSY;
	पूर्ण

	वापस MLX5E_XDP_CHECK_OK;
पूर्ण

INसूचीECT_CALLABLE_SCOPE bool
mlx5e_xmit_xdp_frame(काष्ठा mlx5e_xdpsq *sq, काष्ठा mlx5e_xmit_data *xdptxd,
		     काष्ठा mlx5e_xdp_info *xdpi, पूर्णांक check_result)
अणु
	काष्ठा mlx5_wq_cyc       *wq   = &sq->wq;
	u16                       pi   = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
	काष्ठा mlx5e_tx_wqe      *wqe  = mlx5_wq_cyc_get_wqe(wq, pi);

	काष्ठा mlx5_wqe_ctrl_seg *cseg = &wqe->ctrl;
	काष्ठा mlx5_wqe_eth_seg  *eseg = &wqe->eth;
	काष्ठा mlx5_wqe_data_seg *dseg = wqe->data;

	dma_addr_t dma_addr = xdptxd->dma_addr;
	u32 dma_len = xdptxd->len;

	काष्ठा mlx5e_xdpsq_stats *stats = sq->stats;

	net_prefetchw(wqe);

	अगर (unlikely(dma_len < MLX5E_XDP_MIN_INLINE || sq->hw_mtu < dma_len)) अणु
		stats->err++;
		वापस false;
	पूर्ण

	अगर (!check_result)
		check_result = mlx5e_xmit_xdp_frame_check(sq);
	अगर (unlikely(check_result < 0))
		वापस false;

	cseg->fm_ce_se = 0;

	/* copy the अंतरभूत part अगर required */
	अगर (sq->min_अंतरभूत_mode != MLX5_INLINE_MODE_NONE) अणु
		स_नकल(eseg->अंतरभूत_hdr.start, xdptxd->data, MLX5E_XDP_MIN_INLINE);
		eseg->अंतरभूत_hdr.sz = cpu_to_be16(MLX5E_XDP_MIN_INLINE);
		dma_len  -= MLX5E_XDP_MIN_INLINE;
		dma_addr += MLX5E_XDP_MIN_INLINE;
		dseg++;
	पूर्ण

	/* ग_लिखो the dma part */
	dseg->addr       = cpu_to_be64(dma_addr);
	dseg->byte_count = cpu_to_be32(dma_len);

	cseg->opmod_idx_opcode = cpu_to_be32((sq->pc << 8) | MLX5_OPCODE_SEND);

	sq->pc++;

	sq->करोorbell_cseg = cseg;

	mlx5e_xdpi_fअगरo_push(&sq->db.xdpi_fअगरo, xdpi);
	stats->xmit++;
	वापस true;
पूर्ण

अटल व्योम mlx5e_मुक्त_xdpsq_desc(काष्ठा mlx5e_xdpsq *sq,
				  काष्ठा mlx5e_xdp_wqe_info *wi,
				  u32 *xsk_frames,
				  bool recycle,
				  काष्ठा xdp_frame_bulk *bq)
अणु
	काष्ठा mlx5e_xdp_info_fअगरo *xdpi_fअगरo = &sq->db.xdpi_fअगरo;
	u16 i;

	क्रम (i = 0; i < wi->num_pkts; i++) अणु
		काष्ठा mlx5e_xdp_info xdpi = mlx5e_xdpi_fअगरo_pop(xdpi_fअगरo);

		चयन (xdpi.mode) अणु
		हाल MLX5E_XDP_XMIT_MODE_FRAME:
			/* XDP_TX from the XSK RQ and XDP_REसूचीECT */
			dma_unmap_single(sq->pdev, xdpi.frame.dma_addr,
					 xdpi.frame.xdpf->len, DMA_TO_DEVICE);
			xdp_वापस_frame_bulk(xdpi.frame.xdpf, bq);
			अवरोध;
		हाल MLX5E_XDP_XMIT_MODE_PAGE:
			/* XDP_TX from the regular RQ */
			mlx5e_page_release_dynamic(xdpi.page.rq, &xdpi.page.di, recycle);
			अवरोध;
		हाल MLX5E_XDP_XMIT_MODE_XSK:
			/* AF_XDP send */
			(*xsk_frames)++;
			अवरोध;
		शेष:
			WARN_ON_ONCE(true);
		पूर्ण
	पूर्ण
पूर्ण

bool mlx5e_poll_xdpsq_cq(काष्ठा mlx5e_cq *cq)
अणु
	काष्ठा xdp_frame_bulk bq;
	काष्ठा mlx5e_xdpsq *sq;
	काष्ठा mlx5_cqe64 *cqe;
	u32 xsk_frames = 0;
	u16 sqcc;
	पूर्णांक i;

	xdp_frame_bulk_init(&bq);

	sq = container_of(cq, काष्ठा mlx5e_xdpsq, cq);

	अगर (unlikely(!test_bit(MLX5E_SQ_STATE_ENABLED, &sq->state)))
		वापस false;

	cqe = mlx5_cqwq_get_cqe(&cq->wq);
	अगर (!cqe)
		वापस false;

	/* sq->cc must be updated only after mlx5_cqwq_update_db_record(),
	 * otherwise a cq overrun may occur
	 */
	sqcc = sq->cc;

	i = 0;
	करो अणु
		काष्ठा mlx5e_xdp_wqe_info *wi;
		u16 wqe_counter, ci;
		bool last_wqe;

		mlx5_cqwq_pop(&cq->wq);

		wqe_counter = be16_to_cpu(cqe->wqe_counter);

		करो अणु
			last_wqe = (sqcc == wqe_counter);
			ci = mlx5_wq_cyc_ctr2ix(&sq->wq, sqcc);
			wi = &sq->db.wqe_info[ci];

			sqcc += wi->num_wqebbs;

			mlx5e_मुक्त_xdpsq_desc(sq, wi, &xsk_frames, true, &bq);
		पूर्ण जबतक (!last_wqe);

		अगर (unlikely(get_cqe_opcode(cqe) != MLX5_CQE_REQ)) अणु
			netdev_WARN_ONCE(sq->channel->netdev,
					 "Bad OP in XDPSQ CQE: 0x%x\n",
					 get_cqe_opcode(cqe));
			mlx5e_dump_error_cqe(&sq->cq, sq->sqn,
					     (काष्ठा mlx5_err_cqe *)cqe);
			mlx5_wq_cyc_wqe_dump(&sq->wq, ci, wi->num_wqebbs);
		पूर्ण
	पूर्ण जबतक ((++i < MLX5E_TX_CQ_POLL_BUDGET) && (cqe = mlx5_cqwq_get_cqe(&cq->wq)));

	xdp_flush_frame_bulk(&bq);

	अगर (xsk_frames)
		xsk_tx_completed(sq->xsk_pool, xsk_frames);

	sq->stats->cqes += i;

	mlx5_cqwq_update_db_record(&cq->wq);

	/* ensure cq space is मुक्तd beक्रमe enabling more cqes */
	wmb();

	sq->cc = sqcc;
	वापस (i == MLX5E_TX_CQ_POLL_BUDGET);
पूर्ण

व्योम mlx5e_मुक्त_xdpsq_descs(काष्ठा mlx5e_xdpsq *sq)
अणु
	काष्ठा xdp_frame_bulk bq;
	u32 xsk_frames = 0;

	xdp_frame_bulk_init(&bq);

	rcu_पढ़ो_lock(); /* need क्रम xdp_वापस_frame_bulk */

	जबतक (sq->cc != sq->pc) अणु
		काष्ठा mlx5e_xdp_wqe_info *wi;
		u16 ci;

		ci = mlx5_wq_cyc_ctr2ix(&sq->wq, sq->cc);
		wi = &sq->db.wqe_info[ci];

		sq->cc += wi->num_wqebbs;

		mlx5e_मुक्त_xdpsq_desc(sq, wi, &xsk_frames, false, &bq);
	पूर्ण

	xdp_flush_frame_bulk(&bq);
	rcu_पढ़ो_unlock();

	अगर (xsk_frames)
		xsk_tx_completed(sq->xsk_pool, xsk_frames);
पूर्ण

पूर्णांक mlx5e_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n, काष्ठा xdp_frame **frames,
		   u32 flags)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5e_xdpsq *sq;
	पूर्णांक nxmit = 0;
	पूर्णांक sq_num;
	पूर्णांक i;

	/* this flag is sufficient, no need to test पूर्णांकernal sq state */
	अगर (unlikely(!mlx5e_xdp_tx_is_enabled(priv)))
		वापस -ENETDOWN;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	sq_num = smp_processor_id();

	अगर (unlikely(sq_num >= priv->channels.num))
		वापस -ENXIO;

	sq = &priv->channels.c[sq_num]->xdpsq;

	क्रम (i = 0; i < n; i++) अणु
		काष्ठा xdp_frame *xdpf = frames[i];
		काष्ठा mlx5e_xmit_data xdptxd;
		काष्ठा mlx5e_xdp_info xdpi;
		bool ret;

		xdptxd.data = xdpf->data;
		xdptxd.len = xdpf->len;
		xdptxd.dma_addr = dma_map_single(sq->pdev, xdptxd.data,
						 xdptxd.len, DMA_TO_DEVICE);

		अगर (unlikely(dma_mapping_error(sq->pdev, xdptxd.dma_addr)))
			अवरोध;

		xdpi.mode           = MLX5E_XDP_XMIT_MODE_FRAME;
		xdpi.frame.xdpf     = xdpf;
		xdpi.frame.dma_addr = xdptxd.dma_addr;

		ret = INसूचीECT_CALL_2(sq->xmit_xdp_frame, mlx5e_xmit_xdp_frame_mpwqe,
				      mlx5e_xmit_xdp_frame, sq, &xdptxd, &xdpi, 0);
		अगर (unlikely(!ret)) अणु
			dma_unmap_single(sq->pdev, xdptxd.dma_addr,
					 xdptxd.len, DMA_TO_DEVICE);
			अवरोध;
		पूर्ण
		nxmit++;
	पूर्ण

	अगर (flags & XDP_XMIT_FLUSH) अणु
		अगर (sq->mpwqe.wqe)
			mlx5e_xdp_mpwqe_complete(sq);
		mlx5e_xmit_xdp_करोorbell(sq);
	पूर्ण

	वापस nxmit;
पूर्ण

व्योम mlx5e_xdp_rx_poll_complete(काष्ठा mlx5e_rq *rq)
अणु
	काष्ठा mlx5e_xdpsq *xdpsq = rq->xdpsq;

	अगर (xdpsq->mpwqe.wqe)
		mlx5e_xdp_mpwqe_complete(xdpsq);

	mlx5e_xmit_xdp_करोorbell(xdpsq);

	अगर (test_bit(MLX5E_RQ_FLAG_XDP_REसूचीECT, rq->flags)) अणु
		xdp_करो_flush_map();
		__clear_bit(MLX5E_RQ_FLAG_XDP_REसूचीECT, rq->flags);
	पूर्ण
पूर्ण

व्योम mlx5e_set_xmit_fp(काष्ठा mlx5e_xdpsq *sq, bool is_mpw)
अणु
	sq->xmit_xdp_frame_check = is_mpw ?
		mlx5e_xmit_xdp_frame_check_mpwqe : mlx5e_xmit_xdp_frame_check;
	sq->xmit_xdp_frame = is_mpw ?
		mlx5e_xmit_xdp_frame_mpwqe : mlx5e_xmit_xdp_frame;
पूर्ण
