<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2020, Mellanox Technologies inc. All rights reserved.
 */

#अगर_अघोषित _MLX5_IB_WR_H
#घोषणा _MLX5_IB_WR_H

#समावेश "mlx5_ib.h"

क्रमागत अणु
	MLX5_IB_SQ_UMR_INLINE_THRESHOLD = 64,
पूर्ण;

काष्ठा mlx5_wqe_eth_pad अणु
	u8 rsvd0[16];
पूर्ण;


/* get_sq_edge - Get the next nearby edge.
 *
 * An 'edge' is defined as the first following address after the end
 * of the fragment or the SQ. Accordingly, during the WQE स्थिरruction
 * which repetitively increases the poपूर्णांकer to ग_लिखो the next data, it
 * simply should check अगर it माला_लो to an edge.
 *
 * @sq - SQ buffer.
 * @idx - Stride index in the SQ buffer.
 *
 * Return:
 *	The new edge.
 */
अटल अंतरभूत व्योम *get_sq_edge(काष्ठा mlx5_ib_wq *sq, u32 idx)
अणु
	व्योम *fragment_end;

	fragment_end = mlx5_frag_buf_get_wqe
		(&sq->fbc,
		 mlx5_frag_buf_get_idx_last_contig_stride(&sq->fbc, idx));

	वापस fragment_end + MLX5_SEND_WQE_BB;
पूर्ण

पूर्णांक mlx5_ib_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
		      स्थिर काष्ठा ib_send_wr **bad_wr, bool drain);
पूर्णांक mlx5_ib_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
		      स्थिर काष्ठा ib_recv_wr **bad_wr, bool drain);

अटल अंतरभूत पूर्णांक mlx5_ib_post_send_nodrain(काष्ठा ib_qp *ibqp,
					    स्थिर काष्ठा ib_send_wr *wr,
					    स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	वापस mlx5_ib_post_send(ibqp, wr, bad_wr, false);
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_ib_post_send_drain(काष्ठा ib_qp *ibqp,
					  स्थिर काष्ठा ib_send_wr *wr,
					  स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	वापस mlx5_ib_post_send(ibqp, wr, bad_wr, true);
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_ib_post_recv_nodrain(काष्ठा ib_qp *ibqp,
					    स्थिर काष्ठा ib_recv_wr *wr,
					    स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	वापस mlx5_ib_post_recv(ibqp, wr, bad_wr, false);
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_ib_post_recv_drain(काष्ठा ib_qp *ibqp,
					  स्थिर काष्ठा ib_recv_wr *wr,
					  स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	वापस mlx5_ib_post_recv(ibqp, wr, bad_wr, true);
पूर्ण
#पूर्ण_अगर /* _MLX5_IB_WR_H */
