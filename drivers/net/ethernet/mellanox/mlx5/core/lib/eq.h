<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2018 Mellanox Technologies */

#अगर_अघोषित __LIB_MLX5_EQ_H__
#घोषणा __LIB_MLX5_EQ_H__
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/eq.h>
#समावेश <linux/mlx5/cq.h>

#घोषणा MLX5_EQE_SIZE       (माप(काष्ठा mlx5_eqe))

काष्ठा mlx5_eq_tasklet अणु
	काष्ठा list_head      list;
	काष्ठा list_head      process_list;
	काष्ठा tasklet_काष्ठा task;
	spinlock_t            lock; /* lock completion tasklet list */
पूर्ण;

काष्ठा mlx5_cq_table अणु
	spinlock_t              lock;	/* protect radix tree */
	काष्ठा radix_tree_root  tree;
पूर्ण;

काष्ठा mlx5_eq अणु
	काष्ठा mlx5_frag_buf_ctrl fbc;
	काष्ठा mlx5_frag_buf    frag_buf;
	काष्ठा mlx5_core_dev    *dev;
	काष्ठा mlx5_cq_table    cq_table;
	__be32 __iomem	        *करोorbell;
	u32                     cons_index;
	अचिन्हित पूर्णांक            vecidx;
	अचिन्हित पूर्णांक            irqn;
	u8                      eqn;
	काष्ठा mlx5_rsc_debug   *dbg;
पूर्ण;

काष्ठा mlx5_eq_async अणु
	काष्ठा mlx5_eq          core;
	काष्ठा notअगरier_block   irq_nb;
	spinlock_t              lock; /* To aव्योम irq EQ handle races with resiliency flows */
पूर्ण;

काष्ठा mlx5_eq_comp अणु
	काष्ठा mlx5_eq          core;
	काष्ठा notअगरier_block   irq_nb;
	काष्ठा mlx5_eq_tasklet  tasklet_ctx;
	काष्ठा list_head        list;
पूर्ण;

अटल अंतरभूत u32 eq_get_size(काष्ठा mlx5_eq *eq)
अणु
	वापस eq->fbc.sz_m1 + 1;
पूर्ण

अटल अंतरभूत काष्ठा mlx5_eqe *get_eqe(काष्ठा mlx5_eq *eq, u32 entry)
अणु
	वापस mlx5_frag_buf_get_wqe(&eq->fbc, entry);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_eqe *next_eqe_sw(काष्ठा mlx5_eq *eq)
अणु
	काष्ठा mlx5_eqe *eqe = get_eqe(eq, eq->cons_index & eq->fbc.sz_m1);

	वापस (eqe->owner ^ (eq->cons_index >> eq->fbc.log_sz)) & 1 ? शून्य : eqe;
पूर्ण

अटल अंतरभूत व्योम eq_update_ci(काष्ठा mlx5_eq *eq, पूर्णांक arm)
अणु
	__be32 __iomem *addr = eq->करोorbell + (arm ? 0 : 2);
	u32 val = (eq->cons_index & 0xffffff) | (eq->eqn << 24);

	__raw_ग_लिखोl((__क्रमce u32)cpu_to_be32(val), addr);
	/* We still want ordering, just not swabbing, so add a barrier */
	mb();
पूर्ण

पूर्णांक mlx5_eq_table_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_eq_table_cleanup(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_eq_table_create(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_eq_table_destroy(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_eq_add_cq(काष्ठा mlx5_eq *eq, काष्ठा mlx5_core_cq *cq);
व्योम mlx5_eq_del_cq(काष्ठा mlx5_eq *eq, काष्ठा mlx5_core_cq *cq);
काष्ठा mlx5_eq_comp *mlx5_eqn2comp_eq(काष्ठा mlx5_core_dev *dev, पूर्णांक eqn);
काष्ठा mlx5_eq *mlx5_get_async_eq(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_cq_tasklet_cb(काष्ठा tasklet_काष्ठा *t);
काष्ठा cpumask *mlx5_eq_comp_cpumask(काष्ठा mlx5_core_dev *dev, पूर्णांक ix);

u32 mlx5_eq_poll_irq_disabled(काष्ठा mlx5_eq_comp *eq);
व्योम mlx5_cmd_eq_recover(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_eq_synchronize_async_irq(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_eq_synchronize_cmd_irq(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_debug_eq_add(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq);
व्योम mlx5_debug_eq_हटाओ(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq);
व्योम mlx5_eq_debugfs_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_eq_debugfs_cleanup(काष्ठा mlx5_core_dev *dev);

/* This function should only be called after mlx5_cmd_क्रमce_tearकरोwn_hca */
व्योम mlx5_core_eq_मुक्त_irqs(काष्ठा mlx5_core_dev *dev);

#अगर_घोषित CONFIG_RFS_ACCEL
काष्ठा cpu_rmap *mlx5_eq_table_get_rmap(काष्ठा mlx5_core_dev *dev);
#पूर्ण_अगर

#पूर्ण_अगर
