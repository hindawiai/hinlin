<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2021 Mellanox Technologies.

#समावेश "eswitch.h"

/* This काष्ठा is used as a key to the hash table and we need it to be packed
 * so hash result is consistent
 */
काष्ठा mlx5_vport_key अणु
	u32 chain;
	u16 prio;
	u16 vport;
	u16 vhca_id;
	स्थिर काष्ठा esw_vport_tbl_namespace *vport_ns;
पूर्ण __packed;

काष्ठा mlx5_vport_table अणु
	काष्ठा hlist_node hlist;
	काष्ठा mlx5_flow_table *fdb;
	u32 num_rules;
	काष्ठा mlx5_vport_key key;
पूर्ण;

अटल काष्ठा mlx5_flow_table *
esw_vport_tbl_create(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_flow_namespace *ns,
		     स्थिर काष्ठा esw_vport_tbl_namespace *vport_ns)
अणु
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_flow_table *fdb;

	अगर (vport_ns->max_num_groups)
		ft_attr.स्वतःgroup.max_num_groups = vport_ns->max_num_groups;
	अन्यथा
		ft_attr.स्वतःgroup.max_num_groups = esw->params.large_group_num;
	ft_attr.max_fte = vport_ns->max_fte;
	ft_attr.prio = FDB_PER_VPORT;
	ft_attr.flags = vport_ns->flags;
	fdb = mlx5_create_स्वतः_grouped_flow_table(ns, &ft_attr);
	अगर (IS_ERR(fdb)) अणु
		esw_warn(esw->dev, "Failed to create per vport FDB Table err %ld\n",
			 PTR_ERR(fdb));
	पूर्ण

	वापस fdb;
पूर्ण

अटल u32 flow_attr_to_vport_key(काष्ठा mlx5_eचयन *esw,
				  काष्ठा mlx5_vport_tbl_attr *attr,
				  काष्ठा mlx5_vport_key *key)
अणु
	key->vport = attr->vport;
	key->chain = attr->chain;
	key->prio = attr->prio;
	key->vhca_id = MLX5_CAP_GEN(esw->dev, vhca_id);
	key->vport_ns  = attr->vport_ns;
	वापस jhash(key, माप(*key), 0);
पूर्ण

/* caller must hold vports.lock */
अटल काष्ठा mlx5_vport_table *
esw_vport_tbl_lookup(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport_key *skey, u32 key)
अणु
	काष्ठा mlx5_vport_table *e;

	hash_क्रम_each_possible(esw->fdb_table.offloads.vports.table, e, hlist, key)
		अगर (!स_भेद(&e->key, skey, माप(*skey)))
			वापस e;

	वापस शून्य;
पूर्ण

काष्ठा mlx5_flow_table *
mlx5_esw_vporttbl_get(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport_tbl_attr *attr)
अणु
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा mlx5_flow_namespace *ns;
	काष्ठा mlx5_flow_table *fdb;
	काष्ठा mlx5_vport_table *e;
	काष्ठा mlx5_vport_key skey;
	u32 hkey;

	mutex_lock(&esw->fdb_table.offloads.vports.lock);
	hkey = flow_attr_to_vport_key(esw, attr, &skey);
	e = esw_vport_tbl_lookup(esw, &skey, hkey);
	अगर (e) अणु
		e->num_rules++;
		जाओ out;
	पूर्ण

	e = kzalloc(माप(*e), GFP_KERNEL);
	अगर (!e) अणु
		fdb = ERR_PTR(-ENOMEM);
		जाओ err_alloc;
	पूर्ण

	ns = mlx5_get_flow_namespace(dev, MLX5_FLOW_NAMESPACE_FDB);
	अगर (!ns) अणु
		esw_warn(dev, "Failed to get FDB namespace\n");
		fdb = ERR_PTR(-ENOENT);
		जाओ err_ns;
	पूर्ण

	fdb = esw_vport_tbl_create(esw, ns, attr->vport_ns);
	अगर (IS_ERR(fdb))
		जाओ err_ns;

	e->fdb = fdb;
	e->num_rules = 1;
	e->key = skey;
	hash_add(esw->fdb_table.offloads.vports.table, &e->hlist, hkey);
out:
	mutex_unlock(&esw->fdb_table.offloads.vports.lock);
	वापस e->fdb;

err_ns:
	kमुक्त(e);
err_alloc:
	mutex_unlock(&esw->fdb_table.offloads.vports.lock);
	वापस fdb;
पूर्ण

व्योम
mlx5_esw_vporttbl_put(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport_tbl_attr *attr)
अणु
	काष्ठा mlx5_vport_table *e;
	काष्ठा mlx5_vport_key key;
	u32 hkey;

	mutex_lock(&esw->fdb_table.offloads.vports.lock);
	hkey = flow_attr_to_vport_key(esw, attr, &key);
	e = esw_vport_tbl_lookup(esw, &key, hkey);
	अगर (!e || --e->num_rules)
		जाओ out;

	hash_del(&e->hlist);
	mlx5_destroy_flow_table(e->fdb);
	kमुक्त(e);
out:
	mutex_unlock(&esw->fdb_table.offloads.vports.lock);
पूर्ण
