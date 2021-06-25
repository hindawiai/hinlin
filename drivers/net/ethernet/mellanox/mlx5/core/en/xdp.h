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
#अगर_अघोषित __MLX5_EN_XDP_H__
#घोषणा __MLX5_EN_XDP_H__

#समावेश <linux/indirect_call_wrapper.h>

#समावेश "en.h"
#समावेश "en/txrx.h"

#घोषणा MLX5E_XDP_MIN_INLINE (ETH_HLEN + VLAN_HLEN)
#घोषणा MLX5E_XDP_TX_DS_COUNT (MLX5E_TX_WQE_EMPTY_DS_COUNT + 1 /* SG DS */)

#घोषणा MLX5E_XDP_INLINE_WQE_MAX_DS_CNT 16
#घोषणा MLX5E_XDP_INLINE_WQE_SZ_THRSD \
	(MLX5E_XDP_INLINE_WQE_MAX_DS_CNT * MLX5_SEND_WQE_DS - \
	 माप(काष्ठा mlx5_wqe_अंतरभूत_seg))

काष्ठा mlx5e_xsk_param;
पूर्णांक mlx5e_xdp_max_mtu(काष्ठा mlx5e_params *params, काष्ठा mlx5e_xsk_param *xsk);
bool mlx5e_xdp_handle(काष्ठा mlx5e_rq *rq, काष्ठा mlx5e_dma_info *di,
		      u32 *len, काष्ठा xdp_buff *xdp);
व्योम mlx5e_xdp_mpwqe_complete(काष्ठा mlx5e_xdpsq *sq);
bool mlx5e_poll_xdpsq_cq(काष्ठा mlx5e_cq *cq);
व्योम mlx5e_मुक्त_xdpsq_descs(काष्ठा mlx5e_xdpsq *sq);
व्योम mlx5e_set_xmit_fp(काष्ठा mlx5e_xdpsq *sq, bool is_mpw);
व्योम mlx5e_xdp_rx_poll_complete(काष्ठा mlx5e_rq *rq);
पूर्णांक mlx5e_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n, काष्ठा xdp_frame **frames,
		   u32 flags);

INसूचीECT_CALLABLE_DECLARE(bool mlx5e_xmit_xdp_frame_mpwqe(काष्ठा mlx5e_xdpsq *sq,
							  काष्ठा mlx5e_xmit_data *xdptxd,
							  काष्ठा mlx5e_xdp_info *xdpi,
							  पूर्णांक check_result));
INसूचीECT_CALLABLE_DECLARE(bool mlx5e_xmit_xdp_frame(काष्ठा mlx5e_xdpsq *sq,
						    काष्ठा mlx5e_xmit_data *xdptxd,
						    काष्ठा mlx5e_xdp_info *xdpi,
						    पूर्णांक check_result));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक mlx5e_xmit_xdp_frame_check_mpwqe(काष्ठा mlx5e_xdpsq *sq));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक mlx5e_xmit_xdp_frame_check(काष्ठा mlx5e_xdpsq *sq));

अटल अंतरभूत व्योम mlx5e_xdp_tx_enable(काष्ठा mlx5e_priv *priv)
अणु
	set_bit(MLX5E_STATE_XDP_TX_ENABLED, &priv->state);

	अगर (priv->channels.params.xdp_prog)
		set_bit(MLX5E_STATE_XDP_ACTIVE, &priv->state);
पूर्ण

अटल अंतरभूत व्योम mlx5e_xdp_tx_disable(काष्ठा mlx5e_priv *priv)
अणु
	अगर (priv->channels.params.xdp_prog)
		clear_bit(MLX5E_STATE_XDP_ACTIVE, &priv->state);

	clear_bit(MLX5E_STATE_XDP_TX_ENABLED, &priv->state);
	/* Let other device's napi(s) and XSK wakeups see our new state. */
	synchronize_net();
पूर्ण

अटल अंतरभूत bool mlx5e_xdp_tx_is_enabled(काष्ठा mlx5e_priv *priv)
अणु
	वापस test_bit(MLX5E_STATE_XDP_TX_ENABLED, &priv->state);
पूर्ण

अटल अंतरभूत bool mlx5e_xdp_is_active(काष्ठा mlx5e_priv *priv)
अणु
	वापस test_bit(MLX5E_STATE_XDP_ACTIVE, &priv->state);
पूर्ण

अटल अंतरभूत व्योम mlx5e_xmit_xdp_करोorbell(काष्ठा mlx5e_xdpsq *sq)
अणु
	अगर (sq->करोorbell_cseg) अणु
		mlx5e_notअगरy_hw(&sq->wq, sq->pc, sq->uar_map, sq->करोorbell_cseg);
		sq->करोorbell_cseg = शून्य;
	पूर्ण
पूर्ण

/* Enable अंतरभूत WQEs to shअगरt some load from a congested HCA (HW) to
 * a less congested cpu (SW).
 */
अटल अंतरभूत bool mlx5e_xdp_get_अंतरभूत_state(काष्ठा mlx5e_xdpsq *sq, bool cur)
अणु
	u16 outstanding = sq->xdpi_fअगरo_pc - sq->xdpi_fअगरo_cc;

#घोषणा MLX5E_XDP_INLINE_WATERMARK_LOW	10
#घोषणा MLX5E_XDP_INLINE_WATERMARK_HIGH 128

	अगर (cur && outstanding <= MLX5E_XDP_INLINE_WATERMARK_LOW)
		वापस false;

	अगर (!cur && outstanding >= MLX5E_XDP_INLINE_WATERMARK_HIGH)
		वापस true;

	वापस cur;
पूर्ण

अटल अंतरभूत bool mlx5e_xdp_mpqwe_is_full(काष्ठा mlx5e_tx_mpwqe *session)
अणु
	अगर (session->अंतरभूत_on)
		वापस session->ds_count + MLX5E_XDP_INLINE_WQE_MAX_DS_CNT >
		       MLX5E_TX_MPW_MAX_NUM_DS;
	वापस mlx5e_tx_mpwqe_is_full(session);
पूर्ण

काष्ठा mlx5e_xdp_wqe_info अणु
	u8 num_wqebbs;
	u8 num_pkts;
पूर्ण;

अटल अंतरभूत व्योम
mlx5e_xdp_mpwqe_add_dseg(काष्ठा mlx5e_xdpsq *sq,
			 काष्ठा mlx5e_xmit_data *xdptxd,
			 काष्ठा mlx5e_xdpsq_stats *stats)
अणु
	काष्ठा mlx5e_tx_mpwqe *session = &sq->mpwqe;
	काष्ठा mlx5_wqe_data_seg *dseg =
		(काष्ठा mlx5_wqe_data_seg *)session->wqe + session->ds_count;
	u32 dma_len = xdptxd->len;

	session->pkt_count++;
	session->bytes_count += dma_len;

	अगर (session->अंतरभूत_on && dma_len <= MLX5E_XDP_INLINE_WQE_SZ_THRSD) अणु
		काष्ठा mlx5_wqe_अंतरभूत_seg *अंतरभूत_dseg =
			(काष्ठा mlx5_wqe_अंतरभूत_seg *)dseg;
		u16 ds_len = माप(*अंतरभूत_dseg) + dma_len;
		u16 ds_cnt = DIV_ROUND_UP(ds_len, MLX5_SEND_WQE_DS);

		अंतरभूत_dseg->byte_count = cpu_to_be32(dma_len | MLX5_INLINE_SEG);
		स_नकल(अंतरभूत_dseg->data, xdptxd->data, dma_len);

		session->ds_count += ds_cnt;
		stats->inlnw++;
		वापस;
	पूर्ण

	dseg->addr       = cpu_to_be64(xdptxd->dma_addr);
	dseg->byte_count = cpu_to_be32(dma_len);
	dseg->lkey       = sq->mkey_be;
	session->ds_count++;
पूर्ण

अटल अंतरभूत व्योम
mlx5e_xdpi_fअगरo_push(काष्ठा mlx5e_xdp_info_fअगरo *fअगरo,
		     काष्ठा mlx5e_xdp_info *xi)
अणु
	u32 i = (*fअगरo->pc)++ & fअगरo->mask;

	fअगरo->xi[i] = *xi;
पूर्ण

अटल अंतरभूत काष्ठा mlx5e_xdp_info
mlx5e_xdpi_fअगरo_pop(काष्ठा mlx5e_xdp_info_fअगरo *fअगरo)
अणु
	वापस fअगरo->xi[(*fअगरo->cc)++ & fअगरo->mask];
पूर्ण
#पूर्ण_अगर
