<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2016-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

#समावेश "spectrum.h"

काष्ठा mlxsw_sp_kvdl अणु
	स्थिर काष्ठा mlxsw_sp_kvdl_ops *kvdl_ops;
	काष्ठा mutex kvdl_lock; /* Protects kvdl allocations */
	अचिन्हित दीर्घ priv[];
	/* priv has to be always the last item */
पूर्ण;

पूर्णांक mlxsw_sp_kvdl_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	स्थिर काष्ठा mlxsw_sp_kvdl_ops *kvdl_ops = mlxsw_sp->kvdl_ops;
	काष्ठा mlxsw_sp_kvdl *kvdl;
	पूर्णांक err;

	kvdl = kzalloc(माप(*mlxsw_sp->kvdl) + kvdl_ops->priv_size,
		       GFP_KERNEL);
	अगर (!kvdl)
		वापस -ENOMEM;
	mutex_init(&kvdl->kvdl_lock);
	kvdl->kvdl_ops = kvdl_ops;
	mlxsw_sp->kvdl = kvdl;

	err = kvdl_ops->init(mlxsw_sp, kvdl->priv);
	अगर (err)
		जाओ err_init;
	वापस 0;

err_init:
	mutex_destroy(&kvdl->kvdl_lock);
	kमुक्त(kvdl);
	वापस err;
पूर्ण

व्योम mlxsw_sp_kvdl_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_kvdl *kvdl = mlxsw_sp->kvdl;

	kvdl->kvdl_ops->fini(mlxsw_sp, kvdl->priv);
	mutex_destroy(&kvdl->kvdl_lock);
	kमुक्त(kvdl);
पूर्ण

पूर्णांक mlxsw_sp_kvdl_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
			क्रमागत mlxsw_sp_kvdl_entry_type type,
			अचिन्हित पूर्णांक entry_count, u32 *p_entry_index)
अणु
	काष्ठा mlxsw_sp_kvdl *kvdl = mlxsw_sp->kvdl;
	पूर्णांक err;

	mutex_lock(&kvdl->kvdl_lock);
	err = kvdl->kvdl_ops->alloc(mlxsw_sp, kvdl->priv, type,
				    entry_count, p_entry_index);
	mutex_unlock(&kvdl->kvdl_lock);

	वापस err;
पूर्ण

व्योम mlxsw_sp_kvdl_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
			क्रमागत mlxsw_sp_kvdl_entry_type type,
			अचिन्हित पूर्णांक entry_count, पूर्णांक entry_index)
अणु
	काष्ठा mlxsw_sp_kvdl *kvdl = mlxsw_sp->kvdl;

	mutex_lock(&kvdl->kvdl_lock);
	kvdl->kvdl_ops->मुक्त(mlxsw_sp, kvdl->priv, type,
			     entry_count, entry_index);
	mutex_unlock(&kvdl->kvdl_lock);
पूर्ण

पूर्णांक mlxsw_sp_kvdl_alloc_count_query(काष्ठा mlxsw_sp *mlxsw_sp,
				    क्रमागत mlxsw_sp_kvdl_entry_type type,
				    अचिन्हित पूर्णांक entry_count,
				    अचिन्हित पूर्णांक *p_alloc_count)
अणु
	काष्ठा mlxsw_sp_kvdl *kvdl = mlxsw_sp->kvdl;

	वापस kvdl->kvdl_ops->alloc_size_query(mlxsw_sp, kvdl->priv, type,
						entry_count, p_alloc_count);
पूर्ण
