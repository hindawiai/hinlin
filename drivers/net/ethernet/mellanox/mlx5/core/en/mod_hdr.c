<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2020 Mellanox Technologies

#समावेश <linux/jhash.h>
#समावेश "mod_hdr.h"

#घोषणा MLX5_MH_ACT_SZ MLX5_UN_SZ_BYTES(set_add_copy_action_in_स्वतः)

काष्ठा mod_hdr_key अणु
	पूर्णांक num_actions;
	व्योम *actions;
पूर्ण;

काष्ठा mlx5e_mod_hdr_handle अणु
	/* a node of a hash table which keeps all the mod_hdr entries */
	काष्ठा hlist_node mod_hdr_hlist;

	काष्ठा mod_hdr_key key;

	काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr;

	refcount_t refcnt;
	काष्ठा completion res_पढ़ोy;
	पूर्णांक compl_result;
पूर्ण;

अटल u32 hash_mod_hdr_info(काष्ठा mod_hdr_key *key)
अणु
	वापस jhash(key->actions,
		     key->num_actions * MLX5_MH_ACT_SZ, 0);
पूर्ण

अटल पूर्णांक cmp_mod_hdr_info(काष्ठा mod_hdr_key *a, काष्ठा mod_hdr_key *b)
अणु
	अगर (a->num_actions != b->num_actions)
		वापस 1;

	वापस स_भेद(a->actions, b->actions,
		      a->num_actions * MLX5_MH_ACT_SZ);
पूर्ण

व्योम mlx5e_mod_hdr_tbl_init(काष्ठा mod_hdr_tbl *tbl)
अणु
	mutex_init(&tbl->lock);
	hash_init(tbl->hlist);
पूर्ण

व्योम mlx5e_mod_hdr_tbl_destroy(काष्ठा mod_hdr_tbl *tbl)
अणु
	mutex_destroy(&tbl->lock);
पूर्ण

अटल काष्ठा mlx5e_mod_hdr_handle *mod_hdr_get(काष्ठा mod_hdr_tbl *tbl,
						काष्ठा mod_hdr_key *key,
						u32 hash_key)
अणु
	काष्ठा mlx5e_mod_hdr_handle *mh, *found = शून्य;

	hash_क्रम_each_possible(tbl->hlist, mh, mod_hdr_hlist, hash_key) अणु
		अगर (!cmp_mod_hdr_info(&mh->key, key)) अणु
			refcount_inc(&mh->refcnt);
			found = mh;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

काष्ठा mlx5e_mod_hdr_handle *
mlx5e_mod_hdr_attach(काष्ठा mlx5_core_dev *mdev,
		     काष्ठा mod_hdr_tbl *tbl,
		     क्रमागत mlx5_flow_namespace_type namespace,
		     काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts)
अणु
	पूर्णांक num_actions, actions_size, err;
	काष्ठा mlx5e_mod_hdr_handle *mh;
	काष्ठा mod_hdr_key key;
	u32 hash_key;

	num_actions  = mod_hdr_acts->num_actions;
	actions_size = MLX5_MH_ACT_SZ * num_actions;

	key.actions = mod_hdr_acts->actions;
	key.num_actions = num_actions;

	hash_key = hash_mod_hdr_info(&key);

	mutex_lock(&tbl->lock);
	mh = mod_hdr_get(tbl, &key, hash_key);
	अगर (mh) अणु
		mutex_unlock(&tbl->lock);
		रुको_क्रम_completion(&mh->res_पढ़ोy);

		अगर (mh->compl_result < 0) अणु
			err = -EREMOTEIO;
			जाओ attach_header_err;
		पूर्ण
		जाओ attach_header;
	पूर्ण

	mh = kzalloc(माप(*mh) + actions_size, GFP_KERNEL);
	अगर (!mh) अणु
		mutex_unlock(&tbl->lock);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	mh->key.actions = (व्योम *)mh + माप(*mh);
	स_नकल(mh->key.actions, key.actions, actions_size);
	mh->key.num_actions = num_actions;
	refcount_set(&mh->refcnt, 1);
	init_completion(&mh->res_पढ़ोy);

	hash_add(tbl->hlist, &mh->mod_hdr_hlist, hash_key);
	mutex_unlock(&tbl->lock);

	mh->modअगरy_hdr = mlx5_modअगरy_header_alloc(mdev, namespace,
						  mh->key.num_actions,
						  mh->key.actions);
	अगर (IS_ERR(mh->modअगरy_hdr)) अणु
		err = PTR_ERR(mh->modअगरy_hdr);
		mh->compl_result = err;
		जाओ alloc_header_err;
	पूर्ण
	mh->compl_result = 1;
	complete_all(&mh->res_पढ़ोy);

attach_header:
	वापस mh;

alloc_header_err:
	complete_all(&mh->res_पढ़ोy);
attach_header_err:
	mlx5e_mod_hdr_detach(mdev, tbl, mh);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlx5e_mod_hdr_detach(काष्ठा mlx5_core_dev *mdev,
			  काष्ठा mod_hdr_tbl *tbl,
			  काष्ठा mlx5e_mod_hdr_handle *mh)
अणु
	अगर (!refcount_dec_and_mutex_lock(&mh->refcnt, &tbl->lock))
		वापस;
	hash_del(&mh->mod_hdr_hlist);
	mutex_unlock(&tbl->lock);

	अगर (mh->compl_result > 0)
		mlx5_modअगरy_header_dealloc(mdev, mh->modअगरy_hdr);

	kमुक्त(mh);
पूर्ण

काष्ठा mlx5_modअगरy_hdr *mlx5e_mod_hdr_get(काष्ठा mlx5e_mod_hdr_handle *mh)
अणु
	वापस mh->modअगरy_hdr;
पूर्ण

