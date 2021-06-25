<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश "dr_types.h"

पूर्णांक mlx5dr_table_set_miss_action(काष्ठा mlx5dr_table *tbl,
				 काष्ठा mlx5dr_action *action)
अणु
	काष्ठा mlx5dr_matcher *last_matcher = शून्य;
	काष्ठा mlx5dr_htbl_connect_info info;
	काष्ठा mlx5dr_ste_htbl *last_htbl;
	पूर्णांक ret;

	अगर (action && action->action_type != DR_ACTION_TYP_FT)
		वापस -EOPNOTSUPP;

	mlx5dr_करोमुख्य_lock(tbl->dmn);

	अगर (!list_empty(&tbl->matcher_list))
		last_matcher = list_last_entry(&tbl->matcher_list,
					       काष्ठा mlx5dr_matcher,
					       matcher_list);

	अगर (tbl->dmn->type == MLX5DR_DOMAIN_TYPE_NIC_RX ||
	    tbl->dmn->type == MLX5DR_DOMAIN_TYPE_FDB) अणु
		अगर (last_matcher)
			last_htbl = last_matcher->rx.e_anchor;
		अन्यथा
			last_htbl = tbl->rx.s_anchor;

		tbl->rx.शेष_icm_addr = action ?
			action->dest_tbl->tbl->rx.s_anchor->chunk->icm_addr :
			tbl->rx.nic_dmn->शेष_icm_addr;

		info.type = CONNECT_MISS;
		info.miss_icm_addr = tbl->rx.शेष_icm_addr;

		ret = mlx5dr_ste_htbl_init_and_postsend(tbl->dmn,
							tbl->rx.nic_dmn,
							last_htbl,
							&info, true);
		अगर (ret) अणु
			mlx5dr_dbg(tbl->dmn, "Failed to set RX miss action, ret %d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (tbl->dmn->type == MLX5DR_DOMAIN_TYPE_NIC_TX ||
	    tbl->dmn->type == MLX5DR_DOMAIN_TYPE_FDB) अणु
		अगर (last_matcher)
			last_htbl = last_matcher->tx.e_anchor;
		अन्यथा
			last_htbl = tbl->tx.s_anchor;

		tbl->tx.शेष_icm_addr = action ?
			action->dest_tbl->tbl->tx.s_anchor->chunk->icm_addr :
			tbl->tx.nic_dmn->शेष_icm_addr;

		info.type = CONNECT_MISS;
		info.miss_icm_addr = tbl->tx.शेष_icm_addr;

		ret = mlx5dr_ste_htbl_init_and_postsend(tbl->dmn,
							tbl->tx.nic_dmn,
							last_htbl, &info, true);
		अगर (ret) अणु
			mlx5dr_dbg(tbl->dmn, "Failed to set TX miss action, ret %d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Release old action */
	अगर (tbl->miss_action)
		refcount_dec(&tbl->miss_action->refcount);

	/* Set new miss action */
	tbl->miss_action = action;
	अगर (tbl->miss_action)
		refcount_inc(&action->refcount);

out:
	mlx5dr_करोमुख्य_unlock(tbl->dmn);
	वापस ret;
पूर्ण

अटल व्योम dr_table_uninit_nic(काष्ठा mlx5dr_table_rx_tx *nic_tbl)
अणु
	mlx5dr_htbl_put(nic_tbl->s_anchor);
पूर्ण

अटल व्योम dr_table_uninit_fdb(काष्ठा mlx5dr_table *tbl)
अणु
	dr_table_uninit_nic(&tbl->rx);
	dr_table_uninit_nic(&tbl->tx);
पूर्ण

अटल व्योम dr_table_uninit(काष्ठा mlx5dr_table *tbl)
अणु
	mlx5dr_करोमुख्य_lock(tbl->dmn);

	चयन (tbl->dmn->type) अणु
	हाल MLX5DR_DOMAIN_TYPE_NIC_RX:
		dr_table_uninit_nic(&tbl->rx);
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_NIC_TX:
		dr_table_uninit_nic(&tbl->tx);
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_FDB:
		dr_table_uninit_fdb(tbl);
		अवरोध;
	शेष:
		WARN_ON(true);
		अवरोध;
	पूर्ण

	mlx5dr_करोमुख्य_unlock(tbl->dmn);
पूर्ण

अटल पूर्णांक dr_table_init_nic(काष्ठा mlx5dr_करोमुख्य *dmn,
			     काष्ठा mlx5dr_table_rx_tx *nic_tbl)
अणु
	काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn = nic_tbl->nic_dmn;
	काष्ठा mlx5dr_htbl_connect_info info;
	पूर्णांक ret;

	nic_tbl->शेष_icm_addr = nic_dmn->शेष_icm_addr;

	nic_tbl->s_anchor = mlx5dr_ste_htbl_alloc(dmn->ste_icm_pool,
						  DR_CHUNK_SIZE_1,
						  MLX5DR_STE_LU_TYPE_DONT_CARE,
						  0);
	अगर (!nic_tbl->s_anchor) अणु
		mlx5dr_err(dmn, "Failed allocating htbl\n");
		वापस -ENOMEM;
	पूर्ण

	info.type = CONNECT_MISS;
	info.miss_icm_addr = nic_dmn->शेष_icm_addr;
	ret = mlx5dr_ste_htbl_init_and_postsend(dmn, nic_dmn,
						nic_tbl->s_anchor,
						&info, true);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed int and send htbl\n");
		जाओ मुक्त_s_anchor;
	पूर्ण

	mlx5dr_htbl_get(nic_tbl->s_anchor);

	वापस 0;

मुक्त_s_anchor:
	mlx5dr_ste_htbl_मुक्त(nic_tbl->s_anchor);
	वापस ret;
पूर्ण

अटल पूर्णांक dr_table_init_fdb(काष्ठा mlx5dr_table *tbl)
अणु
	पूर्णांक ret;

	ret = dr_table_init_nic(tbl->dmn, &tbl->rx);
	अगर (ret)
		वापस ret;

	ret = dr_table_init_nic(tbl->dmn, &tbl->tx);
	अगर (ret)
		जाओ destroy_rx;

	वापस 0;

destroy_rx:
	dr_table_uninit_nic(&tbl->rx);
	वापस ret;
पूर्ण

अटल पूर्णांक dr_table_init(काष्ठा mlx5dr_table *tbl)
अणु
	पूर्णांक ret = 0;

	INIT_LIST_HEAD(&tbl->matcher_list);

	mlx5dr_करोमुख्य_lock(tbl->dmn);

	चयन (tbl->dmn->type) अणु
	हाल MLX5DR_DOMAIN_TYPE_NIC_RX:
		tbl->table_type = MLX5_FLOW_TABLE_TYPE_NIC_RX;
		tbl->rx.nic_dmn = &tbl->dmn->info.rx;
		ret = dr_table_init_nic(tbl->dmn, &tbl->rx);
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_NIC_TX:
		tbl->table_type = MLX5_FLOW_TABLE_TYPE_NIC_TX;
		tbl->tx.nic_dmn = &tbl->dmn->info.tx;
		ret = dr_table_init_nic(tbl->dmn, &tbl->tx);
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_FDB:
		tbl->table_type = MLX5_FLOW_TABLE_TYPE_FDB;
		tbl->rx.nic_dmn = &tbl->dmn->info.rx;
		tbl->tx.nic_dmn = &tbl->dmn->info.tx;
		ret = dr_table_init_fdb(tbl);
		अवरोध;
	शेष:
		WARN_ON(true);
		अवरोध;
	पूर्ण

	mlx5dr_करोमुख्य_unlock(tbl->dmn);

	वापस ret;
पूर्ण

अटल पूर्णांक dr_table_destroy_sw_owned_tbl(काष्ठा mlx5dr_table *tbl)
अणु
	वापस mlx5dr_cmd_destroy_flow_table(tbl->dmn->mdev,
					     tbl->table_id,
					     tbl->table_type);
पूर्ण

अटल पूर्णांक dr_table_create_sw_owned_tbl(काष्ठा mlx5dr_table *tbl)
अणु
	bool en_encap = !!(tbl->flags & MLX5_FLOW_TABLE_TUNNEL_EN_REFORMAT);
	bool en_decap = !!(tbl->flags & MLX5_FLOW_TABLE_TUNNEL_EN_DECAP);
	काष्ठा mlx5dr_cmd_create_flow_table_attr ft_attr = अणुपूर्ण;
	u64 icm_addr_rx = 0;
	u64 icm_addr_tx = 0;
	पूर्णांक ret;

	अगर (tbl->rx.s_anchor)
		icm_addr_rx = tbl->rx.s_anchor->chunk->icm_addr;

	अगर (tbl->tx.s_anchor)
		icm_addr_tx = tbl->tx.s_anchor->chunk->icm_addr;

	ft_attr.table_type = tbl->table_type;
	ft_attr.icm_addr_rx = icm_addr_rx;
	ft_attr.icm_addr_tx = icm_addr_tx;
	ft_attr.level = tbl->dmn->info.caps.max_ft_level - 1;
	ft_attr.sw_owner = true;
	ft_attr.decap_en = en_decap;
	ft_attr.reक्रमmat_en = en_encap;

	ret = mlx5dr_cmd_create_flow_table(tbl->dmn->mdev, &ft_attr,
					   शून्य, &tbl->table_id);

	वापस ret;
पूर्ण

काष्ठा mlx5dr_table *mlx5dr_table_create(काष्ठा mlx5dr_करोमुख्य *dmn, u32 level, u32 flags)
अणु
	काष्ठा mlx5dr_table *tbl;
	पूर्णांक ret;

	refcount_inc(&dmn->refcount);

	tbl = kzalloc(माप(*tbl), GFP_KERNEL);
	अगर (!tbl)
		जाओ dec_ref;

	tbl->dmn = dmn;
	tbl->level = level;
	tbl->flags = flags;
	refcount_set(&tbl->refcount, 1);

	ret = dr_table_init(tbl);
	अगर (ret)
		जाओ मुक्त_tbl;

	ret = dr_table_create_sw_owned_tbl(tbl);
	अगर (ret)
		जाओ uninit_tbl;

	वापस tbl;

uninit_tbl:
	dr_table_uninit(tbl);
मुक्त_tbl:
	kमुक्त(tbl);
dec_ref:
	refcount_dec(&dmn->refcount);
	वापस शून्य;
पूर्ण

पूर्णांक mlx5dr_table_destroy(काष्ठा mlx5dr_table *tbl)
अणु
	पूर्णांक ret;

	अगर (refcount_पढ़ो(&tbl->refcount) > 1)
		वापस -EBUSY;

	ret = dr_table_destroy_sw_owned_tbl(tbl);
	अगर (ret)
		वापस ret;

	dr_table_uninit(tbl);

	अगर (tbl->miss_action)
		refcount_dec(&tbl->miss_action->refcount);

	refcount_dec(&tbl->dmn->refcount);
	kमुक्त(tbl);

	वापस ret;
पूर्ण

u32 mlx5dr_table_get_id(काष्ठा mlx5dr_table *tbl)
अणु
	वापस tbl->table_id;
पूर्ण
