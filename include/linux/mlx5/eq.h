<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2018 Mellanox Technologies. */

#अगर_अघोषित MLX5_CORE_EQ_H
#घोषणा MLX5_CORE_EQ_H

#घोषणा MLX5_IRQ_VEC_COMP_BASE 1
#घोषणा MLX5_NUM_CMD_EQE   (32)
#घोषणा MLX5_NUM_ASYNC_EQE (0x1000)
#घोषणा MLX5_NUM_SPARE_EQE (0x80)

काष्ठा mlx5_eq;
काष्ठा mlx5_core_dev;

काष्ठा mlx5_eq_param अणु
	u8             irq_index;
	पूर्णांक            nent;
	u64            mask[4];
पूर्ण;

काष्ठा mlx5_eq *
mlx5_eq_create_generic(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq_param *param);
पूर्णांक
mlx5_eq_destroy_generic(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq);
पूर्णांक mlx5_eq_enable(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq,
		   काष्ठा notअगरier_block *nb);
व्योम mlx5_eq_disable(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq,
		     काष्ठा notअगरier_block *nb);

काष्ठा mlx5_eqe *mlx5_eq_get_eqe(काष्ठा mlx5_eq *eq, u32 cc);
व्योम mlx5_eq_update_ci(काष्ठा mlx5_eq *eq, u32 cc, bool arm);

/* The HCA will think the queue has overflowed अगर we
 * करोn't tell it we've been processing events.  We
 * create EQs with MLX5_NUM_SPARE_EQE extra entries,
 * so we must update our consumer index at
 * least that often.
 *
 * mlx5_eq_update_cc must be called on every EQE @EQ irq handler
 */
अटल अंतरभूत u32 mlx5_eq_update_cc(काष्ठा mlx5_eq *eq, u32 cc)
अणु
	अगर (unlikely(cc >= MLX5_NUM_SPARE_EQE)) अणु
		mlx5_eq_update_ci(eq, cc, 0);
		cc = 0;
	पूर्ण
	वापस cc;
पूर्ण

काष्ठा mlx5_nb अणु
	काष्ठा notअगरier_block nb;
	u8 event_type;
पूर्ण;

#घोषणा mlx5_nb_cof(ptr, type, member) \
	(container_of(container_of(ptr, काष्ठा mlx5_nb, nb), type, member))

#घोषणा MLX5_NB_INIT(name, handler, event) करो अणु              \
	(name)->nb.notअगरier_call = handler;                  \
	(name)->event_type = MLX5_EVENT_TYPE_##event;        \
पूर्ण जबतक (0)

#पूर्ण_अगर /* MLX5_CORE_EQ_H */
