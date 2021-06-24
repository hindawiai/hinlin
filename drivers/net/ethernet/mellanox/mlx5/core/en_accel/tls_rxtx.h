<शैली गुरु>
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
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
 *
 */

#अगर_अघोषित __MLX5E_TLS_RXTX_H__
#घोषणा __MLX5E_TLS_RXTX_H__

#समावेश "accel/accel.h"
#समावेश "en_accel/ktls_txrx.h"

#अगर_घोषित CONFIG_MLX5_EN_TLS

#समावेश <linux/skbuff.h>
#समावेश "en.h"
#समावेश "en/txrx.h"

u16 mlx5e_tls_get_stop_room(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_params *params);

bool mlx5e_tls_handle_tx_skb(काष्ठा net_device *netdev, काष्ठा mlx5e_txqsq *sq,
			     काष्ठा sk_buff *skb, काष्ठा mlx5e_accel_tx_tls_state *state);

अटल अंतरभूत bool mlx5e_tls_skb_offloaded(काष्ठा sk_buff *skb)
अणु
	वापस skb->sk && tls_is_sk_tx_device_offloaded(skb->sk);
पूर्ण

अटल अंतरभूत व्योम
mlx5e_tls_handle_tx_wqe(काष्ठा mlx5_wqe_ctrl_seg *cseg,
			काष्ठा mlx5e_accel_tx_tls_state *state)
अणु
	cseg->tis_tir_num = cpu_to_be32(state->tls_tisn << 8);
पूर्ण

व्योम mlx5e_tls_handle_rx_skb_metadata(काष्ठा mlx5e_rq *rq, काष्ठा sk_buff *skb,
				      u32 *cqe_bcnt);

अटल अंतरभूत व्योम
mlx5e_tls_handle_rx_skb(काष्ठा mlx5e_rq *rq, काष्ठा sk_buff *skb,
			काष्ठा mlx5_cqe64 *cqe, u32 *cqe_bcnt)
अणु
	अगर (unlikely(get_cqe_tls_offload(cqe))) /* cqe bit indicates a TLS device */
		वापस mlx5e_ktls_handle_rx_skb(rq, skb, cqe, cqe_bcnt);

	अगर (unlikely(test_bit(MLX5E_RQ_STATE_FPGA_TLS, &rq->state) && is_metadata_hdr_valid(skb)))
		वापस mlx5e_tls_handle_rx_skb_metadata(rq, skb, cqe_bcnt);
पूर्ण

#अन्यथा

अटल अंतरभूत bool
mlx5e_accel_is_tls(काष्ठा mlx5_cqe64 *cqe, काष्ठा sk_buff *skb) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम
mlx5e_tls_handle_rx_skb(काष्ठा mlx5e_rq *rq, काष्ठा sk_buff *skb,
			काष्ठा mlx5_cqe64 *cqe, u32 *cqe_bcnt) अणुपूर्ण
अटल अंतरभूत u16 mlx5e_tls_get_stop_room(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_params *params)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_EN_TLS */

#पूर्ण_अगर /* __MLX5E_TLS_RXTX_H__ */
