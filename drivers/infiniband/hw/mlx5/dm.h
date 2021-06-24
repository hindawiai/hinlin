<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2021, Mellanox Technologies inc. All rights reserved.
 */

#अगर_अघोषित _MLX5_IB_DM_H
#घोषणा _MLX5_IB_DM_H

#समावेश "mlx5_ib.h"

बाह्य स्थिर काष्ठा ib_device_ops mlx5_ib_dev_dm_ops;
बाह्य स्थिर काष्ठा uapi_definition mlx5_ib_dm_defs[];

काष्ठा mlx5_ib_dm अणु
	काष्ठा ib_dm		ibdm;
	u32			type;
	phys_addr_t		dev_addr;
	माप_प्रकार			size;
पूर्ण;

काष्ठा mlx5_ib_dm_op_entry अणु
	काष्ठा mlx5_user_mmap_entry	mentry;
	phys_addr_t			op_addr;
	काष्ठा mlx5_ib_dm_memic		*dm;
	u8				op;
पूर्ण;

काष्ठा mlx5_ib_dm_memic अणु
	काष्ठा mlx5_ib_dm           base;
	काष्ठा mlx5_user_mmap_entry mentry;
	काष्ठा xarray               ops;
	काष्ठा mutex                ops_xa_lock;
	काष्ठा kref                 ref;
	माप_प्रकार                      req_length;
पूर्ण;

काष्ठा mlx5_ib_dm_icm अणु
	काष्ठा mlx5_ib_dm      base;
	u32                    obj_id;
पूर्ण;

अटल अंतरभूत काष्ठा mlx5_ib_dm *to_mdm(काष्ठा ib_dm *ibdm)
अणु
	वापस container_of(ibdm, काष्ठा mlx5_ib_dm, ibdm);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_dm_memic *to_memic(काष्ठा ib_dm *ibdm)
अणु
	वापस container_of(ibdm, काष्ठा mlx5_ib_dm_memic, base.ibdm);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_dm_icm *to_icm(काष्ठा ib_dm *ibdm)
अणु
	वापस container_of(ibdm, काष्ठा mlx5_ib_dm_icm, base.ibdm);
पूर्ण

काष्ठा ib_dm *mlx5_ib_alloc_dm(काष्ठा ib_device *ibdev,
			       काष्ठा ib_ucontext *context,
			       काष्ठा ib_dm_alloc_attr *attr,
			       काष्ठा uverbs_attr_bundle *attrs);
व्योम mlx5_ib_dm_mmap_मुक्त(काष्ठा mlx5_ib_dev *dev,
			  काष्ठा mlx5_user_mmap_entry *mentry);
व्योम mlx5_cmd_dealloc_memic(काष्ठा mlx5_dm *dm, phys_addr_t addr,
			    u64 length);
व्योम mlx5_cmd_dealloc_memic_op(काष्ठा mlx5_dm *dm, phys_addr_t addr,
			       u8 operation);

#पूर्ण_अगर /* _MLX5_IB_DM_H */
