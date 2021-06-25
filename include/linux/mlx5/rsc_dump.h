<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies inc. */

#समावेश <linux/mlx5/driver.h>

#अगर_अघोषित __MLX5_RSC_DUMP
#घोषणा __MLX5_RSC_DUMP

क्रमागत mlx5_sgmt_type अणु
	MLX5_SGMT_TYPE_HW_CQPC,
	MLX5_SGMT_TYPE_HW_SQPC,
	MLX5_SGMT_TYPE_HW_RQPC,
	MLX5_SGMT_TYPE_FULL_SRQC,
	MLX5_SGMT_TYPE_FULL_CQC,
	MLX5_SGMT_TYPE_FULL_EQC,
	MLX5_SGMT_TYPE_FULL_QPC,
	MLX5_SGMT_TYPE_SND_BUFF,
	MLX5_SGMT_TYPE_RCV_BUFF,
	MLX5_SGMT_TYPE_SRQ_BUFF,
	MLX5_SGMT_TYPE_CQ_BUFF,
	MLX5_SGMT_TYPE_EQ_BUFF,
	MLX5_SGMT_TYPE_SX_SLICE,
	MLX5_SGMT_TYPE_SX_SLICE_ALL,
	MLX5_SGMT_TYPE_RDB,
	MLX5_SGMT_TYPE_RX_SLICE_ALL,
	MLX5_SGMT_TYPE_PRM_QUERY_QP,
	MLX5_SGMT_TYPE_PRM_QUERY_CQ,
	MLX5_SGMT_TYPE_PRM_QUERY_MKEY,
	MLX5_SGMT_TYPE_MENU,
	MLX5_SGMT_TYPE_TERMINATE,

	MLX5_SGMT_TYPE_NUM, /* Keep last */
पूर्ण;

काष्ठा mlx5_rsc_key अणु
	क्रमागत mlx5_sgmt_type rsc;
	पूर्णांक index1;
	पूर्णांक index2;
	पूर्णांक num_of_obj1;
	पूर्णांक num_of_obj2;
	पूर्णांक size;
पूर्ण;

काष्ठा mlx5_rsc_dump_cmd;

काष्ठा mlx5_rsc_dump_cmd *mlx5_rsc_dump_cmd_create(काष्ठा mlx5_core_dev *dev,
						   काष्ठा mlx5_rsc_key *key);
व्योम mlx5_rsc_dump_cmd_destroy(काष्ठा mlx5_rsc_dump_cmd *cmd);
पूर्णांक mlx5_rsc_dump_next(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_rsc_dump_cmd *cmd,
		       काष्ठा page *page, पूर्णांक *size);
#पूर्ण_अगर /* __MLX5_RSC_DUMP */
