<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2013-2020, Mellanox Technologies inc. All rights reserved.
 */

#अगर_अघोषित _MLX5_IB_QP_H
#घोषणा _MLX5_IB_QP_H

#समावेश "mlx5_ib.h"

पूर्णांक mlx5_init_qp_table(काष्ठा mlx5_ib_dev *dev);
व्योम mlx5_cleanup_qp_table(काष्ठा mlx5_ib_dev *dev);

पूर्णांक mlx5_core_create_dct(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_dct *qp,
			 u32 *in, पूर्णांक inlen, u32 *out, पूर्णांक outlen);
पूर्णांक mlx5_qpc_create_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_qp *qp,
		       u32 *in, पूर्णांक inlen, u32 *out);
पूर्णांक mlx5_core_qp_modअगरy(काष्ठा mlx5_ib_dev *dev, u16 opcode, u32 opt_param_mask,
			व्योम *qpc, काष्ठा mlx5_core_qp *qp, u32 *ece);
पूर्णांक mlx5_core_destroy_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_qp *qp);
पूर्णांक mlx5_core_destroy_dct(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_dct *dct);
पूर्णांक mlx5_core_qp_query(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_qp *qp,
		       u32 *out, पूर्णांक outlen);
पूर्णांक mlx5_core_dct_query(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_dct *dct,
			u32 *out, पूर्णांक outlen);

पूर्णांक mlx5_core_set_delay_drop(काष्ठा mlx5_ib_dev *dev, u32 समयout_usec);

पूर्णांक mlx5_core_destroy_rq_tracked(काष्ठा mlx5_ib_dev *dev,
				 काष्ठा mlx5_core_qp *rq);
पूर्णांक mlx5_core_create_sq_tracked(काष्ठा mlx5_ib_dev *dev, u32 *in, पूर्णांक inlen,
				काष्ठा mlx5_core_qp *sq);
व्योम mlx5_core_destroy_sq_tracked(काष्ठा mlx5_ib_dev *dev,
				  काष्ठा mlx5_core_qp *sq);

पूर्णांक mlx5_core_create_rq_tracked(काष्ठा mlx5_ib_dev *dev, u32 *in, पूर्णांक inlen,
				काष्ठा mlx5_core_qp *rq);

काष्ठा mlx5_core_rsc_common *mlx5_core_res_hold(काष्ठा mlx5_ib_dev *dev,
						पूर्णांक res_num,
						क्रमागत mlx5_res_type res_type);
व्योम mlx5_core_res_put(काष्ठा mlx5_core_rsc_common *res);

पूर्णांक mlx5_core_xrcd_alloc(काष्ठा mlx5_ib_dev *dev, u32 *xrcdn);
पूर्णांक mlx5_core_xrcd_dealloc(काष्ठा mlx5_ib_dev *dev, u32 xrcdn);
पूर्णांक mlx5_ib_qp_set_counter(काष्ठा ib_qp *qp, काष्ठा rdma_counter *counter);
#पूर्ण_अगर /* _MLX5_IB_QP_H */
