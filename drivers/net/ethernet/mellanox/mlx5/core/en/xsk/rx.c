<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश "rx.h"
#समावेश "en/xdp.h"
#समावेश <net/xdp_sock_drv.h>

/* RX data path */

अटल काष्ठा sk_buff *mlx5e_xsk_स्थिरruct_skb(काष्ठा mlx5e_rq *rq, व्योम *data,
					       u32 cqe_bcnt)
अणु
	काष्ठा sk_buff *skb;

	skb = napi_alloc_skb(rq->cq.napi, cqe_bcnt);
	अगर (unlikely(!skb)) अणु
		rq->stats->buff_alloc_err++;
		वापस शून्य;
	पूर्ण

	skb_put_data(skb, data, cqe_bcnt);

	वापस skb;
पूर्ण

काष्ठा sk_buff *mlx5e_xsk_skb_from_cqe_mpwrq_linear(काष्ठा mlx5e_rq *rq,
						    काष्ठा mlx5e_mpw_info *wi,
						    u16 cqe_bcnt,
						    u32 head_offset,
						    u32 page_idx)
अणु
	काष्ठा xdp_buff *xdp = wi->umr.dma_info[page_idx].xsk;
	u32 cqe_bcnt32 = cqe_bcnt;

	/* Check packet size. Note LRO करोesn't use linear SKB */
	अगर (unlikely(cqe_bcnt > rq->hw_mtu)) अणु
		rq->stats->oversize_pkts_sw_drop++;
		वापस शून्य;
	पूर्ण

	/* head_offset is not used in this function, because xdp->data and the
	 * DMA address poपूर्णांक directly to the necessary place. Furthermore, in
	 * the current implementation, UMR pages are mapped to XSK frames, so
	 * head_offset should always be 0.
	 */
	WARN_ON_ONCE(head_offset);

	xdp->data_end = xdp->data + cqe_bcnt32;
	xdp_set_data_meta_invalid(xdp);
	xsk_buff_dma_sync_क्रम_cpu(xdp, rq->xsk_pool);
	net_prefetch(xdp->data);

	/* Possible flows:
	 * - XDP_REसूचीECT to XSKMAP:
	 *   The page is owned by the userspace from now.
	 * - XDP_TX and other XDP_REसूचीECTs:
	 *   The page was वापसed by ZCA and recycled.
	 * - XDP_DROP:
	 *   Recycle the page.
	 * - XDP_PASS:
	 *   Allocate an SKB, copy the data and recycle the page.
	 *
	 * Pages to be recycled go to the Reuse Ring on MPWQE deallocation. Its
	 * size is the same as the Driver RX Ring's size, and pages क्रम WQEs are
	 * allocated first from the Reuse Ring, so it has enough space.
	 */

	अगर (likely(mlx5e_xdp_handle(rq, शून्य, &cqe_bcnt32, xdp))) अणु
		अगर (likely(__test_and_clear_bit(MLX5E_RQ_FLAG_XDP_XMIT, rq->flags)))
			__set_bit(page_idx, wi->xdp_xmit_biपंचांगap); /* non-atomic */
		वापस शून्य; /* page/packet was consumed by XDP */
	पूर्ण

	/* XDP_PASS: copy the data from the UMEM to a new SKB and reuse the
	 * frame. On SKB allocation failure, शून्य is वापसed.
	 */
	वापस mlx5e_xsk_स्थिरruct_skb(rq, xdp->data, cqe_bcnt32);
पूर्ण

काष्ठा sk_buff *mlx5e_xsk_skb_from_cqe_linear(काष्ठा mlx5e_rq *rq,
					      काष्ठा mlx5_cqe64 *cqe,
					      काष्ठा mlx5e_wqe_frag_info *wi,
					      u32 cqe_bcnt)
अणु
	काष्ठा xdp_buff *xdp = wi->di->xsk;

	/* wi->offset is not used in this function, because xdp->data and the
	 * DMA address poपूर्णांक directly to the necessary place. Furthermore, the
	 * XSK allocator allocates frames per packet, instead of pages, so
	 * wi->offset should always be 0.
	 */
	WARN_ON_ONCE(wi->offset);

	xdp->data_end = xdp->data + cqe_bcnt;
	xdp_set_data_meta_invalid(xdp);
	xsk_buff_dma_sync_क्रम_cpu(xdp, rq->xsk_pool);
	net_prefetch(xdp->data);

	अगर (unlikely(get_cqe_opcode(cqe) != MLX5_CQE_RESP_SEND)) अणु
		rq->stats->wqe_err++;
		वापस शून्य;
	पूर्ण

	अगर (likely(mlx5e_xdp_handle(rq, शून्य, &cqe_bcnt, xdp)))
		वापस शून्य; /* page/packet was consumed by XDP */

	/* XDP_PASS: copy the data from the UMEM to a new SKB. The frame reuse
	 * will be handled by mlx5e_put_rx_frag.
	 * On SKB allocation failure, शून्य is वापसed.
	 */
	वापस mlx5e_xsk_स्थिरruct_skb(rq, xdp->data, cqe_bcnt);
पूर्ण
