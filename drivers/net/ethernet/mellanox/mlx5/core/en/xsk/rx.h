<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5_EN_XSK_RX_H__
#घोषणा __MLX5_EN_XSK_RX_H__

#समावेश "en.h"
#समावेश <net/xdp_sock_drv.h>

/* RX data path */

काष्ठा sk_buff *mlx5e_xsk_skb_from_cqe_mpwrq_linear(काष्ठा mlx5e_rq *rq,
						    काष्ठा mlx5e_mpw_info *wi,
						    u16 cqe_bcnt,
						    u32 head_offset,
						    u32 page_idx);
काष्ठा sk_buff *mlx5e_xsk_skb_from_cqe_linear(काष्ठा mlx5e_rq *rq,
					      काष्ठा mlx5_cqe64 *cqe,
					      काष्ठा mlx5e_wqe_frag_info *wi,
					      u32 cqe_bcnt);

अटल अंतरभूत पूर्णांक mlx5e_xsk_page_alloc_pool(काष्ठा mlx5e_rq *rq,
					    काष्ठा mlx5e_dma_info *dma_info)
अणु
	dma_info->xsk = xsk_buff_alloc(rq->xsk_pool);
	अगर (!dma_info->xsk)
		वापस -ENOMEM;

	/* Store the DMA address without headroom. In striding RQ हाल, we just
	 * provide pages क्रम UMR, and headroom is counted at the setup stage
	 * when creating a WQE. In non-striding RQ हाल, headroom is accounted
	 * in mlx5e_alloc_rx_wqe.
	 */
	dma_info->addr = xsk_buff_xdp_get_frame_dma(dma_info->xsk);

	वापस 0;
पूर्ण

अटल अंतरभूत bool mlx5e_xsk_update_rx_wakeup(काष्ठा mlx5e_rq *rq, bool alloc_err)
अणु
	अगर (!xsk_uses_need_wakeup(rq->xsk_pool))
		वापस alloc_err;

	अगर (unlikely(alloc_err))
		xsk_set_rx_need_wakeup(rq->xsk_pool);
	अन्यथा
		xsk_clear_rx_need_wakeup(rq->xsk_pool);

	वापस false;
पूर्ण

#पूर्ण_अगर /* __MLX5_EN_XSK_RX_H__ */
