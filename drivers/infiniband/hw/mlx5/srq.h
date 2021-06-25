<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2013-2018, Mellanox Technologies. All rights reserved.
 */

#अगर_अघोषित MLX5_IB_SRQ_H
#घोषणा MLX5_IB_SRQ_H

क्रमागत अणु
	MLX5_SRQ_FLAG_ERR    = (1 << 0),
	MLX5_SRQ_FLAG_WQ_SIG = (1 << 1),
	MLX5_SRQ_FLAG_RNDV   = (1 << 2),
पूर्ण;

काष्ठा mlx5_srq_attr अणु
	u32 type;
	u32 flags;
	u32 log_size;
	u32 wqe_shअगरt;
	u32 log_page_size;
	u32 wqe_cnt;
	u32 srqn;
	u32 xrcd;
	u32 page_offset;
	u32 cqn;
	u32 pd;
	u32 lwm;
	u32 user_index;
	u64 db_record;
	__be64 *pas;
	काष्ठा ib_umem *umem;
	u32 पंचांग_log_list_size;
	u32 पंचांग_next_tag;
	u32 पंचांग_hw_phase_cnt;
	u32 पंचांग_sw_phase_cnt;
	u16 uid;
पूर्ण;

काष्ठा mlx5_ib_dev;

काष्ठा mlx5_core_srq अणु
	काष्ठा mlx5_core_rsc_common common; /* must be first */
	u32 srqn;
	पूर्णांक max;
	माप_प्रकार max_gs;
	माप_प्रकार max_avail_gather;
	पूर्णांक wqe_shअगरt;
	व्योम (*event)(काष्ठा mlx5_core_srq *srq, क्रमागत mlx5_event e);

	u16 uid;
पूर्ण;

काष्ठा mlx5_srq_table अणु
	काष्ठा notअगरier_block nb;
	काष्ठा xarray array;
पूर्ण;

पूर्णांक mlx5_cmd_create_srq(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
			काष्ठा mlx5_srq_attr *in);
पूर्णांक mlx5_cmd_destroy_srq(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq);
पूर्णांक mlx5_cmd_query_srq(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
		       काष्ठा mlx5_srq_attr *out);
पूर्णांक mlx5_cmd_arm_srq(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
		     u16 lwm, पूर्णांक is_srq);
काष्ठा mlx5_core_srq *mlx5_cmd_get_srq(काष्ठा mlx5_ib_dev *dev, u32 srqn);

पूर्णांक mlx5_init_srq_table(काष्ठा mlx5_ib_dev *dev);
व्योम mlx5_cleanup_srq_table(काष्ठा mlx5_ib_dev *dev);
#पूर्ण_अगर /* MLX5_IB_SRQ_H */
