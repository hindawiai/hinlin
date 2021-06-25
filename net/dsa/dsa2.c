<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/dsa/dsa2.c - Hardware चयन handling, binding version 2
 * Copyright (c) 2008-2009 Marvell Semiconductor
 * Copyright (c) 2013 Florian Fainelli <florian@खोलोwrt.org>
 * Copyright (c) 2016 Andrew Lunn <andrew@lunn.ch>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <net/devlink.h>

#समावेश "dsa_priv.h"

अटल DEFINE_MUTEX(dsa2_mutex);
LIST_HEAD(dsa_tree_list);

/**
 * dsa_tree_notअगरy - Execute code क्रम all चयनes in a DSA चयन tree.
 * @dst: collection of काष्ठा dsa_चयन devices to notअगरy.
 * @e: event, must be of type DSA_NOTIFIER_*
 * @v: event-specअगरic value.
 *
 * Given a काष्ठा dsa_चयन_tree, this can be used to run a function once क्रम
 * each member DSA चयन. The other alternative of traversing the tree is only
 * through its ports list, which करोes not uniquely list the चयनes.
 */
पूर्णांक dsa_tree_notअगरy(काष्ठा dsa_चयन_tree *dst, अचिन्हित दीर्घ e, व्योम *v)
अणु
	काष्ठा raw_notअगरier_head *nh = &dst->nh;
	पूर्णांक err;

	err = raw_notअगरier_call_chain(nh, e, v);

	वापस notअगरier_to_त्रुटि_सं(err);
पूर्ण

/**
 * dsa_broadcast - Notअगरy all DSA trees in the प्रणाली.
 * @e: event, must be of type DSA_NOTIFIER_*
 * @v: event-specअगरic value.
 *
 * Can be used to notअगरy the चयनing fabric of events such as cross-chip
 * bridging between disjoपूर्णांक trees (such as islands of tagger-compatible
 * चयनes bridged by an incompatible middle चयन).
 */
पूर्णांक dsa_broadcast(अचिन्हित दीर्घ e, व्योम *v)
अणु
	काष्ठा dsa_चयन_tree *dst;
	पूर्णांक err = 0;

	list_क्रम_each_entry(dst, &dsa_tree_list, list) अणु
		err = dsa_tree_notअगरy(dst, e, v);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/**
 * dsa_lag_map() - Map LAG netdev to a linear LAG ID
 * @dst: Tree in which to record the mapping.
 * @lag: Netdev that is to be mapped to an ID.
 *
 * dsa_lag_id/dsa_lag_dev can then be used to translate between the
 * two spaces. The size of the mapping space is determined by the
 * driver by setting ds->num_lag_ids. It is perfectly legal to leave
 * it unset अगर it is not needed, in which हाल these functions become
 * no-ops.
 */
व्योम dsa_lag_map(काष्ठा dsa_चयन_tree *dst, काष्ठा net_device *lag)
अणु
	अचिन्हित पूर्णांक id;

	अगर (dsa_lag_id(dst, lag) >= 0)
		/* Alपढ़ोy mapped */
		वापस;

	क्रम (id = 0; id < dst->lags_len; id++) अणु
		अगर (!dsa_lag_dev(dst, id)) अणु
			dst->lags[id] = lag;
			वापस;
		पूर्ण
	पूर्ण

	/* No IDs left, which is OK. Some drivers करो not need it. The
	 * ones that करो, e.g. mv88e6xxx, will discover that dsa_lag_id
	 * वापसs an error क्रम this device when joining the LAG. The
	 * driver can then वापस -EOPNOTSUPP back to DSA, which will
	 * fall back to a software LAG.
	 */
पूर्ण

/**
 * dsa_lag_unmap() - Remove a LAG ID mapping
 * @dst: Tree in which the mapping is recorded.
 * @lag: Netdev that was mapped.
 *
 * As there may be multiple users of the mapping, it is only हटाओd
 * अगर there are no other references to it.
 */
व्योम dsa_lag_unmap(काष्ठा dsa_चयन_tree *dst, काष्ठा net_device *lag)
अणु
	काष्ठा dsa_port *dp;
	अचिन्हित पूर्णांक id;

	dsa_lag_क्रमeach_port(dp, dst, lag)
		/* There are reमुख्यing users of this mapping */
		वापस;

	dsa_lags_क्रमeach_id(id, dst) अणु
		अगर (dsa_lag_dev(dst, id) == lag) अणु
			dst->lags[id] = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा dsa_चयन *dsa_चयन_find(पूर्णांक tree_index, पूर्णांक sw_index)
अणु
	काष्ठा dsa_चयन_tree *dst;
	काष्ठा dsa_port *dp;

	list_क्रम_each_entry(dst, &dsa_tree_list, list) अणु
		अगर (dst->index != tree_index)
			जारी;

		list_क्रम_each_entry(dp, &dst->ports, list) अणु
			अगर (dp->ds->index != sw_index)
				जारी;

			वापस dp->ds;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_चयन_find);

अटल काष्ठा dsa_चयन_tree *dsa_tree_find(पूर्णांक index)
अणु
	काष्ठा dsa_चयन_tree *dst;

	list_क्रम_each_entry(dst, &dsa_tree_list, list)
		अगर (dst->index == index)
			वापस dst;

	वापस शून्य;
पूर्ण

अटल काष्ठा dsa_चयन_tree *dsa_tree_alloc(पूर्णांक index)
अणु
	काष्ठा dsa_चयन_tree *dst;

	dst = kzalloc(माप(*dst), GFP_KERNEL);
	अगर (!dst)
		वापस शून्य;

	dst->index = index;

	INIT_LIST_HEAD(&dst->rtable);

	INIT_LIST_HEAD(&dst->ports);

	INIT_LIST_HEAD(&dst->list);
	list_add_tail(&dst->list, &dsa_tree_list);

	kref_init(&dst->refcount);

	वापस dst;
पूर्ण

अटल व्योम dsa_tree_मुक्त(काष्ठा dsa_चयन_tree *dst)
अणु
	अगर (dst->tag_ops)
		dsa_tag_driver_put(dst->tag_ops);
	list_del(&dst->list);
	kमुक्त(dst);
पूर्ण

अटल काष्ठा dsa_चयन_tree *dsa_tree_get(काष्ठा dsa_चयन_tree *dst)
अणु
	अगर (dst)
		kref_get(&dst->refcount);

	वापस dst;
पूर्ण

अटल काष्ठा dsa_चयन_tree *dsa_tree_touch(पूर्णांक index)
अणु
	काष्ठा dsa_चयन_tree *dst;

	dst = dsa_tree_find(index);
	अगर (dst)
		वापस dsa_tree_get(dst);
	अन्यथा
		वापस dsa_tree_alloc(index);
पूर्ण

अटल व्योम dsa_tree_release(काष्ठा kref *ref)
अणु
	काष्ठा dsa_चयन_tree *dst;

	dst = container_of(ref, काष्ठा dsa_चयन_tree, refcount);

	dsa_tree_मुक्त(dst);
पूर्ण

अटल व्योम dsa_tree_put(काष्ठा dsa_चयन_tree *dst)
अणु
	अगर (dst)
		kref_put(&dst->refcount, dsa_tree_release);
पूर्ण

अटल bool dsa_port_is_dsa(काष्ठा dsa_port *port)
अणु
	वापस port->type == DSA_PORT_TYPE_DSA;
पूर्ण

अटल bool dsa_port_is_cpu(काष्ठा dsa_port *port)
अणु
	वापस port->type == DSA_PORT_TYPE_CPU;
पूर्ण

अटल bool dsa_port_is_user(काष्ठा dsa_port *dp)
अणु
	वापस dp->type == DSA_PORT_TYPE_USER;
पूर्ण

अटल काष्ठा dsa_port *dsa_tree_find_port_by_node(काष्ठा dsa_चयन_tree *dst,
						   काष्ठा device_node *dn)
अणु
	काष्ठा dsa_port *dp;

	list_क्रम_each_entry(dp, &dst->ports, list)
		अगर (dp->dn == dn)
			वापस dp;

	वापस शून्य;
पूर्ण

अटल काष्ठा dsa_link *dsa_link_touch(काष्ठा dsa_port *dp,
				       काष्ठा dsa_port *link_dp)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;
	काष्ठा dsa_चयन_tree *dst;
	काष्ठा dsa_link *dl;

	dst = ds->dst;

	list_क्रम_each_entry(dl, &dst->rtable, list)
		अगर (dl->dp == dp && dl->link_dp == link_dp)
			वापस dl;

	dl = kzalloc(माप(*dl), GFP_KERNEL);
	अगर (!dl)
		वापस शून्य;

	dl->dp = dp;
	dl->link_dp = link_dp;

	INIT_LIST_HEAD(&dl->list);
	list_add_tail(&dl->list, &dst->rtable);

	वापस dl;
पूर्ण

अटल bool dsa_port_setup_routing_table(काष्ठा dsa_port *dp)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;
	काष्ठा dsa_चयन_tree *dst = ds->dst;
	काष्ठा device_node *dn = dp->dn;
	काष्ठा of_phandle_iterator it;
	काष्ठा dsa_port *link_dp;
	काष्ठा dsa_link *dl;
	पूर्णांक err;

	of_क्रम_each_phandle(&it, err, dn, "link", शून्य, 0) अणु
		link_dp = dsa_tree_find_port_by_node(dst, it.node);
		अगर (!link_dp) अणु
			of_node_put(it.node);
			वापस false;
		पूर्ण

		dl = dsa_link_touch(dp, link_dp);
		अगर (!dl) अणु
			of_node_put(it.node);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool dsa_tree_setup_routing_table(काष्ठा dsa_चयन_tree *dst)
अणु
	bool complete = true;
	काष्ठा dsa_port *dp;

	list_क्रम_each_entry(dp, &dst->ports, list) अणु
		अगर (dsa_port_is_dsa(dp)) अणु
			complete = dsa_port_setup_routing_table(dp);
			अगर (!complete)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस complete;
पूर्ण

अटल काष्ठा dsa_port *dsa_tree_find_first_cpu(काष्ठा dsa_चयन_tree *dst)
अणु
	काष्ठा dsa_port *dp;

	list_क्रम_each_entry(dp, &dst->ports, list)
		अगर (dsa_port_is_cpu(dp))
			वापस dp;

	वापस शून्य;
पूर्ण

अटल पूर्णांक dsa_tree_setup_शेष_cpu(काष्ठा dsa_चयन_tree *dst)
अणु
	काष्ठा dsa_port *cpu_dp, *dp;

	cpu_dp = dsa_tree_find_first_cpu(dst);
	अगर (!cpu_dp) अणु
		pr_err("DSA: tree %d has no CPU port\n", dst->index);
		वापस -EINVAL;
	पूर्ण

	/* Assign the शेष CPU port to all ports of the fabric */
	list_क्रम_each_entry(dp, &dst->ports, list)
		अगर (dsa_port_is_user(dp) || dsa_port_is_dsa(dp))
			dp->cpu_dp = cpu_dp;

	वापस 0;
पूर्ण

अटल व्योम dsa_tree_tearकरोwn_शेष_cpu(काष्ठा dsa_चयन_tree *dst)
अणु
	काष्ठा dsa_port *dp;

	list_क्रम_each_entry(dp, &dst->ports, list)
		अगर (dsa_port_is_user(dp) || dsa_port_is_dsa(dp))
			dp->cpu_dp = शून्य;
पूर्ण

अटल पूर्णांक dsa_port_setup(काष्ठा dsa_port *dp)
अणु
	काष्ठा devlink_port *dlp = &dp->devlink_port;
	bool dsa_port_link_रेजिस्टरed = false;
	bool dsa_port_enabled = false;
	पूर्णांक err = 0;

	अगर (dp->setup)
		वापस 0;

	चयन (dp->type) अणु
	हाल DSA_PORT_TYPE_UNUSED:
		dsa_port_disable(dp);
		अवरोध;
	हाल DSA_PORT_TYPE_CPU:
		err = dsa_port_link_रेजिस्टर_of(dp);
		अगर (err)
			अवरोध;
		dsa_port_link_रेजिस्टरed = true;

		err = dsa_port_enable(dp, शून्य);
		अगर (err)
			अवरोध;
		dsa_port_enabled = true;

		अवरोध;
	हाल DSA_PORT_TYPE_DSA:
		err = dsa_port_link_रेजिस्टर_of(dp);
		अगर (err)
			अवरोध;
		dsa_port_link_रेजिस्टरed = true;

		err = dsa_port_enable(dp, शून्य);
		अगर (err)
			अवरोध;
		dsa_port_enabled = true;

		अवरोध;
	हाल DSA_PORT_TYPE_USER:
		of_get_mac_address(dp->dn, dp->mac);
		err = dsa_slave_create(dp);
		अगर (err)
			अवरोध;

		devlink_port_type_eth_set(dlp, dp->slave);
		अवरोध;
	पूर्ण

	अगर (err && dsa_port_enabled)
		dsa_port_disable(dp);
	अगर (err && dsa_port_link_रेजिस्टरed)
		dsa_port_link_unरेजिस्टर_of(dp);
	अगर (err)
		वापस err;

	dp->setup = true;

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_port_devlink_setup(काष्ठा dsa_port *dp)
अणु
	काष्ठा devlink_port *dlp = &dp->devlink_port;
	काष्ठा dsa_चयन_tree *dst = dp->ds->dst;
	काष्ठा devlink_port_attrs attrs = अणुपूर्ण;
	काष्ठा devlink *dl = dp->ds->devlink;
	स्थिर अचिन्हित अक्षर *id;
	अचिन्हित अक्षर len;
	पूर्णांक err;

	id = (स्थिर अचिन्हित अक्षर *)&dst->index;
	len = माप(dst->index);

	attrs.phys.port_number = dp->index;
	स_नकल(attrs.चयन_id.id, id, len);
	attrs.चयन_id.id_len = len;
	स_रखो(dlp, 0, माप(*dlp));

	चयन (dp->type) अणु
	हाल DSA_PORT_TYPE_UNUSED:
		attrs.flavour = DEVLINK_PORT_FLAVOUR_UNUSED;
		अवरोध;
	हाल DSA_PORT_TYPE_CPU:
		attrs.flavour = DEVLINK_PORT_FLAVOUR_CPU;
		अवरोध;
	हाल DSA_PORT_TYPE_DSA:
		attrs.flavour = DEVLINK_PORT_FLAVOUR_DSA;
		अवरोध;
	हाल DSA_PORT_TYPE_USER:
		attrs.flavour = DEVLINK_PORT_FLAVOUR_PHYSICAL;
		अवरोध;
	पूर्ण

	devlink_port_attrs_set(dlp, &attrs);
	err = devlink_port_रेजिस्टर(dl, dlp, dp->index);

	अगर (!err)
		dp->devlink_port_setup = true;

	वापस err;
पूर्ण

अटल व्योम dsa_port_tearकरोwn(काष्ठा dsa_port *dp)
अणु
	काष्ठा devlink_port *dlp = &dp->devlink_port;

	अगर (!dp->setup)
		वापस;

	devlink_port_type_clear(dlp);

	चयन (dp->type) अणु
	हाल DSA_PORT_TYPE_UNUSED:
		अवरोध;
	हाल DSA_PORT_TYPE_CPU:
		dsa_port_disable(dp);
		dsa_port_link_unरेजिस्टर_of(dp);
		अवरोध;
	हाल DSA_PORT_TYPE_DSA:
		dsa_port_disable(dp);
		dsa_port_link_unरेजिस्टर_of(dp);
		अवरोध;
	हाल DSA_PORT_TYPE_USER:
		अगर (dp->slave) अणु
			dsa_slave_destroy(dp->slave);
			dp->slave = शून्य;
		पूर्ण
		अवरोध;
	पूर्ण

	dp->setup = false;
पूर्ण

अटल व्योम dsa_port_devlink_tearकरोwn(काष्ठा dsa_port *dp)
अणु
	काष्ठा devlink_port *dlp = &dp->devlink_port;

	अगर (dp->devlink_port_setup)
		devlink_port_unरेजिस्टर(dlp);
	dp->devlink_port_setup = false;
पूर्ण

अटल पूर्णांक dsa_devlink_info_get(काष्ठा devlink *dl,
				काष्ठा devlink_info_req *req,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);

	अगर (ds->ops->devlink_info_get)
		वापस ds->ops->devlink_info_get(ds, req, extack);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक dsa_devlink_sb_pool_get(काष्ठा devlink *dl,
				   अचिन्हित पूर्णांक sb_index, u16 pool_index,
				   काष्ठा devlink_sb_pool_info *pool_info)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);

	अगर (!ds->ops->devlink_sb_pool_get)
		वापस -EOPNOTSUPP;

	वापस ds->ops->devlink_sb_pool_get(ds, sb_index, pool_index,
					    pool_info);
पूर्ण

अटल पूर्णांक dsa_devlink_sb_pool_set(काष्ठा devlink *dl, अचिन्हित पूर्णांक sb_index,
				   u16 pool_index, u32 size,
				   क्रमागत devlink_sb_threshold_type threshold_type,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);

	अगर (!ds->ops->devlink_sb_pool_set)
		वापस -EOPNOTSUPP;

	वापस ds->ops->devlink_sb_pool_set(ds, sb_index, pool_index, size,
					    threshold_type, extack);
पूर्ण

अटल पूर्णांक dsa_devlink_sb_port_pool_get(काष्ठा devlink_port *dlp,
					अचिन्हित पूर्णांक sb_index, u16 pool_index,
					u32 *p_threshold)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_port_to_ds(dlp);
	पूर्णांक port = dsa_devlink_port_to_port(dlp);

	अगर (!ds->ops->devlink_sb_port_pool_get)
		वापस -EOPNOTSUPP;

	वापस ds->ops->devlink_sb_port_pool_get(ds, port, sb_index,
						 pool_index, p_threshold);
पूर्ण

अटल पूर्णांक dsa_devlink_sb_port_pool_set(काष्ठा devlink_port *dlp,
					अचिन्हित पूर्णांक sb_index, u16 pool_index,
					u32 threshold,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_port_to_ds(dlp);
	पूर्णांक port = dsa_devlink_port_to_port(dlp);

	अगर (!ds->ops->devlink_sb_port_pool_set)
		वापस -EOPNOTSUPP;

	वापस ds->ops->devlink_sb_port_pool_set(ds, port, sb_index,
						 pool_index, threshold, extack);
पूर्ण

अटल पूर्णांक
dsa_devlink_sb_tc_pool_bind_get(काष्ठा devlink_port *dlp,
				अचिन्हित पूर्णांक sb_index, u16 tc_index,
				क्रमागत devlink_sb_pool_type pool_type,
				u16 *p_pool_index, u32 *p_threshold)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_port_to_ds(dlp);
	पूर्णांक port = dsa_devlink_port_to_port(dlp);

	अगर (!ds->ops->devlink_sb_tc_pool_bind_get)
		वापस -EOPNOTSUPP;

	वापस ds->ops->devlink_sb_tc_pool_bind_get(ds, port, sb_index,
						    tc_index, pool_type,
						    p_pool_index, p_threshold);
पूर्ण

अटल पूर्णांक
dsa_devlink_sb_tc_pool_bind_set(काष्ठा devlink_port *dlp,
				अचिन्हित पूर्णांक sb_index, u16 tc_index,
				क्रमागत devlink_sb_pool_type pool_type,
				u16 pool_index, u32 threshold,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_port_to_ds(dlp);
	पूर्णांक port = dsa_devlink_port_to_port(dlp);

	अगर (!ds->ops->devlink_sb_tc_pool_bind_set)
		वापस -EOPNOTSUPP;

	वापस ds->ops->devlink_sb_tc_pool_bind_set(ds, port, sb_index,
						    tc_index, pool_type,
						    pool_index, threshold,
						    extack);
पूर्ण

अटल पूर्णांक dsa_devlink_sb_occ_snapshot(काष्ठा devlink *dl,
				       अचिन्हित पूर्णांक sb_index)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);

	अगर (!ds->ops->devlink_sb_occ_snapshot)
		वापस -EOPNOTSUPP;

	वापस ds->ops->devlink_sb_occ_snapshot(ds, sb_index);
पूर्ण

अटल पूर्णांक dsa_devlink_sb_occ_max_clear(काष्ठा devlink *dl,
					अचिन्हित पूर्णांक sb_index)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);

	अगर (!ds->ops->devlink_sb_occ_max_clear)
		वापस -EOPNOTSUPP;

	वापस ds->ops->devlink_sb_occ_max_clear(ds, sb_index);
पूर्ण

अटल पूर्णांक dsa_devlink_sb_occ_port_pool_get(काष्ठा devlink_port *dlp,
					    अचिन्हित पूर्णांक sb_index,
					    u16 pool_index, u32 *p_cur,
					    u32 *p_max)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_port_to_ds(dlp);
	पूर्णांक port = dsa_devlink_port_to_port(dlp);

	अगर (!ds->ops->devlink_sb_occ_port_pool_get)
		वापस -EOPNOTSUPP;

	वापस ds->ops->devlink_sb_occ_port_pool_get(ds, port, sb_index,
						     pool_index, p_cur, p_max);
पूर्ण

अटल पूर्णांक
dsa_devlink_sb_occ_tc_port_bind_get(काष्ठा devlink_port *dlp,
				    अचिन्हित पूर्णांक sb_index, u16 tc_index,
				    क्रमागत devlink_sb_pool_type pool_type,
				    u32 *p_cur, u32 *p_max)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_port_to_ds(dlp);
	पूर्णांक port = dsa_devlink_port_to_port(dlp);

	अगर (!ds->ops->devlink_sb_occ_tc_port_bind_get)
		वापस -EOPNOTSUPP;

	वापस ds->ops->devlink_sb_occ_tc_port_bind_get(ds, port,
							sb_index, tc_index,
							pool_type, p_cur,
							p_max);
पूर्ण

अटल स्थिर काष्ठा devlink_ops dsa_devlink_ops = अणु
	.info_get			= dsa_devlink_info_get,
	.sb_pool_get			= dsa_devlink_sb_pool_get,
	.sb_pool_set			= dsa_devlink_sb_pool_set,
	.sb_port_pool_get		= dsa_devlink_sb_port_pool_get,
	.sb_port_pool_set		= dsa_devlink_sb_port_pool_set,
	.sb_tc_pool_bind_get		= dsa_devlink_sb_tc_pool_bind_get,
	.sb_tc_pool_bind_set		= dsa_devlink_sb_tc_pool_bind_set,
	.sb_occ_snapshot		= dsa_devlink_sb_occ_snapshot,
	.sb_occ_max_clear		= dsa_devlink_sb_occ_max_clear,
	.sb_occ_port_pool_get		= dsa_devlink_sb_occ_port_pool_get,
	.sb_occ_tc_port_bind_get	= dsa_devlink_sb_occ_tc_port_bind_get,
पूर्ण;

अटल पूर्णांक dsa_चयन_setup_tag_protocol(काष्ठा dsa_चयन *ds)
अणु
	स्थिर काष्ठा dsa_device_ops *tag_ops = ds->dst->tag_ops;
	काष्ठा dsa_चयन_tree *dst = ds->dst;
	पूर्णांक port, err;

	अगर (tag_ops->proto == dst->शेष_proto)
		वापस 0;

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (!dsa_is_cpu_port(ds, port))
			जारी;

		err = ds->ops->change_tag_protocol(ds, port, tag_ops->proto);
		अगर (err) अणु
			dev_err(ds->dev, "Unable to use tag protocol \"%s\": %pe\n",
				tag_ops->name, ERR_PTR(err));
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_चयन_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा dsa_devlink_priv *dl_priv;
	काष्ठा dsa_port *dp;
	पूर्णांक err;

	अगर (ds->setup)
		वापस 0;

	/* Initialize ds->phys_mii_mask beक्रमe रेजिस्टरing the slave MDIO bus
	 * driver and beक्रमe ops->setup() has run, since the चयन drivers and
	 * the slave MDIO bus driver rely on these values क्रम probing PHY
	 * devices or not
	 */
	ds->phys_mii_mask |= dsa_user_ports(ds);

	/* Add the चयन to devlink beक्रमe calling setup, so that setup can
	 * add dpipe tables
	 */
	ds->devlink = devlink_alloc(&dsa_devlink_ops, माप(*dl_priv));
	अगर (!ds->devlink)
		वापस -ENOMEM;
	dl_priv = devlink_priv(ds->devlink);
	dl_priv->ds = ds;

	err = devlink_रेजिस्टर(ds->devlink, ds->dev);
	अगर (err)
		जाओ मुक्त_devlink;

	/* Setup devlink port instances now, so that the चयन
	 * setup() can रेजिस्टर regions etc, against the ports
	 */
	list_क्रम_each_entry(dp, &ds->dst->ports, list) अणु
		अगर (dp->ds == ds) अणु
			err = dsa_port_devlink_setup(dp);
			अगर (err)
				जाओ unरेजिस्टर_devlink_ports;
		पूर्ण
	पूर्ण

	err = dsa_चयन_रेजिस्टर_notअगरier(ds);
	अगर (err)
		जाओ unरेजिस्टर_devlink_ports;

	ds->configure_vlan_जबतक_not_filtering = true;

	err = ds->ops->setup(ds);
	अगर (err < 0)
		जाओ unरेजिस्टर_notअगरier;

	err = dsa_चयन_setup_tag_protocol(ds);
	अगर (err)
		जाओ tearकरोwn;

	devlink_params_publish(ds->devlink);

	अगर (!ds->slave_mii_bus && ds->ops->phy_पढ़ो) अणु
		ds->slave_mii_bus = devm_mdiobus_alloc(ds->dev);
		अगर (!ds->slave_mii_bus) अणु
			err = -ENOMEM;
			जाओ tearकरोwn;
		पूर्ण

		dsa_slave_mii_bus_init(ds);

		err = mdiobus_रेजिस्टर(ds->slave_mii_bus);
		अगर (err < 0)
			जाओ tearकरोwn;
	पूर्ण

	ds->setup = true;

	वापस 0;

tearकरोwn:
	अगर (ds->ops->tearकरोwn)
		ds->ops->tearकरोwn(ds);
unरेजिस्टर_notअगरier:
	dsa_चयन_unरेजिस्टर_notअगरier(ds);
unरेजिस्टर_devlink_ports:
	list_क्रम_each_entry(dp, &ds->dst->ports, list)
		अगर (dp->ds == ds)
			dsa_port_devlink_tearकरोwn(dp);
	devlink_unरेजिस्टर(ds->devlink);
मुक्त_devlink:
	devlink_मुक्त(ds->devlink);
	ds->devlink = शून्य;

	वापस err;
पूर्ण

अटल व्योम dsa_चयन_tearकरोwn(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा dsa_port *dp;

	अगर (!ds->setup)
		वापस;

	अगर (ds->slave_mii_bus && ds->ops->phy_पढ़ो)
		mdiobus_unरेजिस्टर(ds->slave_mii_bus);

	dsa_चयन_unरेजिस्टर_notअगरier(ds);

	अगर (ds->ops->tearकरोwn)
		ds->ops->tearकरोwn(ds);

	अगर (ds->devlink) अणु
		list_क्रम_each_entry(dp, &ds->dst->ports, list)
			अगर (dp->ds == ds)
				dsa_port_devlink_tearकरोwn(dp);
		devlink_unरेजिस्टर(ds->devlink);
		devlink_मुक्त(ds->devlink);
		ds->devlink = शून्य;
	पूर्ण

	ds->setup = false;
पूर्ण

अटल पूर्णांक dsa_tree_setup_चयनes(काष्ठा dsa_चयन_tree *dst)
अणु
	काष्ठा dsa_port *dp;
	पूर्णांक err;

	list_क्रम_each_entry(dp, &dst->ports, list) अणु
		err = dsa_चयन_setup(dp->ds);
		अगर (err)
			जाओ tearकरोwn;
	पूर्ण

	list_क्रम_each_entry(dp, &dst->ports, list) अणु
		err = dsa_port_setup(dp);
		अगर (err) अणु
			dsa_port_devlink_tearकरोwn(dp);
			dp->type = DSA_PORT_TYPE_UNUSED;
			err = dsa_port_devlink_setup(dp);
			अगर (err)
				जाओ tearकरोwn;
			जारी;
		पूर्ण
	पूर्ण

	वापस 0;

tearकरोwn:
	list_क्रम_each_entry(dp, &dst->ports, list)
		dsa_port_tearकरोwn(dp);

	list_क्रम_each_entry(dp, &dst->ports, list)
		dsa_चयन_tearकरोwn(dp->ds);

	वापस err;
पूर्ण

अटल व्योम dsa_tree_tearकरोwn_चयनes(काष्ठा dsa_चयन_tree *dst)
अणु
	काष्ठा dsa_port *dp;

	list_क्रम_each_entry(dp, &dst->ports, list)
		dsa_port_tearकरोwn(dp);

	list_क्रम_each_entry(dp, &dst->ports, list)
		dsa_चयन_tearकरोwn(dp->ds);
पूर्ण

अटल पूर्णांक dsa_tree_setup_master(काष्ठा dsa_चयन_tree *dst)
अणु
	काष्ठा dsa_port *dp;
	पूर्णांक err;

	list_क्रम_each_entry(dp, &dst->ports, list) अणु
		अगर (dsa_port_is_cpu(dp)) अणु
			err = dsa_master_setup(dp->master, dp);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dsa_tree_tearकरोwn_master(काष्ठा dsa_चयन_tree *dst)
अणु
	काष्ठा dsa_port *dp;

	list_क्रम_each_entry(dp, &dst->ports, list)
		अगर (dsa_port_is_cpu(dp))
			dsa_master_tearकरोwn(dp->master);
पूर्ण

अटल पूर्णांक dsa_tree_setup_lags(काष्ठा dsa_चयन_tree *dst)
अणु
	अचिन्हित पूर्णांक len = 0;
	काष्ठा dsa_port *dp;

	list_क्रम_each_entry(dp, &dst->ports, list) अणु
		अगर (dp->ds->num_lag_ids > len)
			len = dp->ds->num_lag_ids;
	पूर्ण

	अगर (!len)
		वापस 0;

	dst->lags = kसुस्मृति(len, माप(*dst->lags), GFP_KERNEL);
	अगर (!dst->lags)
		वापस -ENOMEM;

	dst->lags_len = len;
	वापस 0;
पूर्ण

अटल व्योम dsa_tree_tearकरोwn_lags(काष्ठा dsa_चयन_tree *dst)
अणु
	kमुक्त(dst->lags);
पूर्ण

अटल पूर्णांक dsa_tree_setup(काष्ठा dsa_चयन_tree *dst)
अणु
	bool complete;
	पूर्णांक err;

	अगर (dst->setup) अणु
		pr_err("DSA: tree %d already setup! Disjoint trees?\n",
		       dst->index);
		वापस -EEXIST;
	पूर्ण

	complete = dsa_tree_setup_routing_table(dst);
	अगर (!complete)
		वापस 0;

	err = dsa_tree_setup_शेष_cpu(dst);
	अगर (err)
		वापस err;

	err = dsa_tree_setup_चयनes(dst);
	अगर (err)
		जाओ tearकरोwn_शेष_cpu;

	err = dsa_tree_setup_master(dst);
	अगर (err)
		जाओ tearकरोwn_चयनes;

	err = dsa_tree_setup_lags(dst);
	अगर (err)
		जाओ tearकरोwn_master;

	dst->setup = true;

	pr_info("DSA: tree %d setup\n", dst->index);

	वापस 0;

tearकरोwn_master:
	dsa_tree_tearकरोwn_master(dst);
tearकरोwn_चयनes:
	dsa_tree_tearकरोwn_चयनes(dst);
tearकरोwn_शेष_cpu:
	dsa_tree_tearकरोwn_शेष_cpu(dst);

	वापस err;
पूर्ण

अटल व्योम dsa_tree_tearकरोwn(काष्ठा dsa_चयन_tree *dst)
अणु
	काष्ठा dsa_link *dl, *next;

	अगर (!dst->setup)
		वापस;

	dsa_tree_tearकरोwn_lags(dst);

	dsa_tree_tearकरोwn_master(dst);

	dsa_tree_tearकरोwn_चयनes(dst);

	dsa_tree_tearकरोwn_शेष_cpu(dst);

	list_क्रम_each_entry_safe(dl, next, &dst->rtable, list) अणु
		list_del(&dl->list);
		kमुक्त(dl);
	पूर्ण

	pr_info("DSA: tree %d torn down\n", dst->index);

	dst->setup = false;
पूर्ण

/* Since the dsa/tagging sysfs device attribute is per master, the assumption
 * is that all DSA चयनes within a tree share the same tagger, otherwise
 * they would have क्रमmed disjoपूर्णांक trees (dअगरferent "dsa,member" values).
 */
पूर्णांक dsa_tree_change_tag_proto(काष्ठा dsa_चयन_tree *dst,
			      काष्ठा net_device *master,
			      स्थिर काष्ठा dsa_device_ops *tag_ops,
			      स्थिर काष्ठा dsa_device_ops *old_tag_ops)
अणु
	काष्ठा dsa_notअगरier_tag_proto_info info;
	काष्ठा dsa_port *dp;
	पूर्णांक err = -EBUSY;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	/* At the moment we करोn't allow changing the tag protocol under
	 * traffic. The rtnl_mutex also happens to serialize concurrent
	 * attempts to change the tagging protocol. If we ever lअगरt the IFF_UP
	 * restriction, there needs to be another mutex which serializes this.
	 */
	अगर (master->flags & IFF_UP)
		जाओ out_unlock;

	list_क्रम_each_entry(dp, &dst->ports, list) अणु
		अगर (!dsa_is_user_port(dp->ds, dp->index))
			जारी;

		अगर (dp->slave->flags & IFF_UP)
			जाओ out_unlock;
	पूर्ण

	info.tag_ops = tag_ops;
	err = dsa_tree_notअगरy(dst, DSA_NOTIFIER_TAG_PROTO, &info);
	अगर (err)
		जाओ out_unwind_tagger;

	dst->tag_ops = tag_ops;

	rtnl_unlock();

	वापस 0;

out_unwind_tagger:
	info.tag_ops = old_tag_ops;
	dsa_tree_notअगरy(dst, DSA_NOTIFIER_TAG_PROTO, &info);
out_unlock:
	rtnl_unlock();
	वापस err;
पूर्ण

अटल काष्ठा dsa_port *dsa_port_touch(काष्ठा dsa_चयन *ds, पूर्णांक index)
अणु
	काष्ठा dsa_चयन_tree *dst = ds->dst;
	काष्ठा dsa_port *dp;

	list_क्रम_each_entry(dp, &dst->ports, list)
		अगर (dp->ds == ds && dp->index == index)
			वापस dp;

	dp = kzalloc(माप(*dp), GFP_KERNEL);
	अगर (!dp)
		वापस शून्य;

	dp->ds = ds;
	dp->index = index;

	INIT_LIST_HEAD(&dp->list);
	list_add_tail(&dp->list, &dst->ports);

	वापस dp;
पूर्ण

अटल पूर्णांक dsa_port_parse_user(काष्ठा dsa_port *dp, स्थिर अक्षर *name)
अणु
	अगर (!name)
		name = "eth%d";

	dp->type = DSA_PORT_TYPE_USER;
	dp->name = name;

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_port_parse_dsa(काष्ठा dsa_port *dp)
अणु
	dp->type = DSA_PORT_TYPE_DSA;

	वापस 0;
पूर्ण

अटल क्रमागत dsa_tag_protocol dsa_get_tag_protocol(काष्ठा dsa_port *dp,
						  काष्ठा net_device *master)
अणु
	क्रमागत dsa_tag_protocol tag_protocol = DSA_TAG_PROTO_NONE;
	काष्ठा dsa_चयन *mds, *ds = dp->ds;
	अचिन्हित पूर्णांक mdp_upstream;
	काष्ठा dsa_port *mdp;

	/* It is possible to stack DSA चयनes onto one another when that
	 * happens the चयन driver may want to know अगर its tagging protocol
	 * is going to work in such a configuration.
	 */
	अगर (dsa_slave_dev_check(master)) अणु
		mdp = dsa_slave_to_port(master);
		mds = mdp->ds;
		mdp_upstream = dsa_upstream_port(mds, mdp->index);
		tag_protocol = mds->ops->get_tag_protocol(mds, mdp_upstream,
							  DSA_TAG_PROTO_NONE);
	पूर्ण

	/* If the master device is not itself a DSA slave in a disjoपूर्णांक DSA
	 * tree, then वापस immediately.
	 */
	वापस ds->ops->get_tag_protocol(ds, dp->index, tag_protocol);
पूर्ण

अटल पूर्णांक dsa_port_parse_cpu(काष्ठा dsa_port *dp, काष्ठा net_device *master,
			      स्थिर अक्षर *user_protocol)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;
	काष्ठा dsa_चयन_tree *dst = ds->dst;
	स्थिर काष्ठा dsa_device_ops *tag_ops;
	क्रमागत dsa_tag_protocol शेष_proto;

	/* Find out which protocol the चयन would prefer. */
	शेष_proto = dsa_get_tag_protocol(dp, master);
	अगर (dst->शेष_proto) अणु
		अगर (dst->शेष_proto != शेष_proto) अणु
			dev_err(ds->dev,
				"A DSA switch tree can have only one tagging protocol\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		dst->शेष_proto = शेष_proto;
	पूर्ण

	/* See अगर the user wants to override that preference. */
	अगर (user_protocol) अणु
		अगर (!ds->ops->change_tag_protocol) अणु
			dev_err(ds->dev, "Tag protocol cannot be modified\n");
			वापस -EINVAL;
		पूर्ण

		tag_ops = dsa_find_tagger_by_name(user_protocol);
	पूर्ण अन्यथा अणु
		tag_ops = dsa_tag_driver_get(शेष_proto);
	पूर्ण

	अगर (IS_ERR(tag_ops)) अणु
		अगर (PTR_ERR(tag_ops) == -ENOPROTOOPT)
			वापस -EPROBE_DEFER;

		dev_warn(ds->dev, "No tagger for this switch\n");
		वापस PTR_ERR(tag_ops);
	पूर्ण

	अगर (dst->tag_ops) अणु
		अगर (dst->tag_ops != tag_ops) अणु
			dev_err(ds->dev,
				"A DSA switch tree can have only one tagging protocol\n");

			dsa_tag_driver_put(tag_ops);
			वापस -EINVAL;
		पूर्ण

		/* In the हाल of multiple CPU ports per चयन, the tagging
		 * protocol is still reference-counted only per चयन tree.
		 */
		dsa_tag_driver_put(tag_ops);
	पूर्ण अन्यथा अणु
		dst->tag_ops = tag_ops;
	पूर्ण

	dp->master = master;
	dp->type = DSA_PORT_TYPE_CPU;
	dsa_port_set_tag_protocol(dp, dst->tag_ops);
	dp->dst = dst;

	/* At this poपूर्णांक, the tree may be configured to use a dअगरferent
	 * tagger than the one chosen by the चयन driver during
	 * .setup, in the हाल when a user selects a custom protocol
	 * through the DT.
	 *
	 * This is resolved by syncing the driver with the tree in
	 * dsa_चयन_setup_tag_protocol once .setup has run and the
	 * driver is पढ़ोy to accept calls to .change_tag_protocol. If
	 * the driver करोes not support the custom protocol at that
	 * poपूर्णांक, the tree is wholly rejected, thereby ensuring that the
	 * tree and driver are always in agreement on the protocol to
	 * use.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक dsa_port_parse_of(काष्ठा dsa_port *dp, काष्ठा device_node *dn)
अणु
	काष्ठा device_node *ethernet = of_parse_phandle(dn, "ethernet", 0);
	स्थिर अक्षर *name = of_get_property(dn, "label", शून्य);
	bool link = of_property_पढ़ो_bool(dn, "link");

	dp->dn = dn;

	अगर (ethernet) अणु
		काष्ठा net_device *master;
		स्थिर अक्षर *user_protocol;

		master = of_find_net_device_by_node(ethernet);
		अगर (!master)
			वापस -EPROBE_DEFER;

		user_protocol = of_get_property(dn, "dsa-tag-protocol", शून्य);
		वापस dsa_port_parse_cpu(dp, master, user_protocol);
	पूर्ण

	अगर (link)
		वापस dsa_port_parse_dsa(dp);

	वापस dsa_port_parse_user(dp, name);
पूर्ण

अटल पूर्णांक dsa_चयन_parse_ports_of(काष्ठा dsa_चयन *ds,
				     काष्ठा device_node *dn)
अणु
	काष्ठा device_node *ports, *port;
	काष्ठा dsa_port *dp;
	पूर्णांक err = 0;
	u32 reg;

	ports = of_get_child_by_name(dn, "ports");
	अगर (!ports) अणु
		/* The second possibility is "ethernet-ports" */
		ports = of_get_child_by_name(dn, "ethernet-ports");
		अगर (!ports) अणु
			dev_err(ds->dev, "no ports child node found\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम_each_available_child_of_node(ports, port) अणु
		err = of_property_पढ़ो_u32(port, "reg", &reg);
		अगर (err)
			जाओ out_put_node;

		अगर (reg >= ds->num_ports) अणु
			dev_err(ds->dev, "port %pOF index %u exceeds num_ports (%zu)\n",
				port, reg, ds->num_ports);
			err = -EINVAL;
			जाओ out_put_node;
		पूर्ण

		dp = dsa_to_port(ds, reg);

		err = dsa_port_parse_of(dp, port);
		अगर (err)
			जाओ out_put_node;
	पूर्ण

out_put_node:
	of_node_put(ports);
	वापस err;
पूर्ण

अटल पूर्णांक dsa_चयन_parse_member_of(काष्ठा dsa_चयन *ds,
				      काष्ठा device_node *dn)
अणु
	u32 m[2] = अणु 0, 0 पूर्ण;
	पूर्णांक sz;

	/* Don't error out if this optional property isn't found */
	sz = of_property_पढ़ो_variable_u32_array(dn, "dsa,member", m, 2, 2);
	अगर (sz < 0 && sz != -EINVAL)
		वापस sz;

	ds->index = m[1];

	ds->dst = dsa_tree_touch(m[0]);
	अगर (!ds->dst)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_चयन_touch_ports(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा dsa_port *dp;
	पूर्णांक port;

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		dp = dsa_port_touch(ds, port);
		अगर (!dp)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_चयन_parse_of(काष्ठा dsa_चयन *ds, काष्ठा device_node *dn)
अणु
	पूर्णांक err;

	err = dsa_चयन_parse_member_of(ds, dn);
	अगर (err)
		वापस err;

	err = dsa_चयन_touch_ports(ds);
	अगर (err)
		वापस err;

	वापस dsa_चयन_parse_ports_of(ds, dn);
पूर्ण

अटल पूर्णांक dsa_port_parse(काष्ठा dsa_port *dp, स्थिर अक्षर *name,
			  काष्ठा device *dev)
अणु
	अगर (!म_भेद(name, "cpu")) अणु
		काष्ठा net_device *master;

		master = dsa_dev_to_net_device(dev);
		अगर (!master)
			वापस -EPROBE_DEFER;

		dev_put(master);

		वापस dsa_port_parse_cpu(dp, master, शून्य);
	पूर्ण

	अगर (!म_भेद(name, "dsa"))
		वापस dsa_port_parse_dsa(dp);

	वापस dsa_port_parse_user(dp, name);
पूर्ण

अटल पूर्णांक dsa_चयन_parse_ports(काष्ठा dsa_चयन *ds,
				  काष्ठा dsa_chip_data *cd)
अणु
	bool valid_name_found = false;
	काष्ठा dsa_port *dp;
	काष्ठा device *dev;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < DSA_MAX_PORTS; i++) अणु
		name = cd->port_names[i];
		dev = cd->netdev[i];
		dp = dsa_to_port(ds, i);

		अगर (!name)
			जारी;

		err = dsa_port_parse(dp, name, dev);
		अगर (err)
			वापस err;

		valid_name_found = true;
	पूर्ण

	अगर (!valid_name_found && i == DSA_MAX_PORTS)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_चयन_parse(काष्ठा dsa_चयन *ds, काष्ठा dsa_chip_data *cd)
अणु
	पूर्णांक err;

	ds->cd = cd;

	/* We करोn't support पूर्णांकerconnected चयनes nor multiple trees via
	 * platक्रमm data, so this is the unique चयन of the tree.
	 */
	ds->index = 0;
	ds->dst = dsa_tree_touch(0);
	अगर (!ds->dst)
		वापस -ENOMEM;

	err = dsa_चयन_touch_ports(ds);
	अगर (err)
		वापस err;

	वापस dsa_चयन_parse_ports(ds, cd);
पूर्ण

अटल व्योम dsa_चयन_release_ports(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा dsa_चयन_tree *dst = ds->dst;
	काष्ठा dsa_port *dp, *next;

	list_क्रम_each_entry_safe(dp, next, &dst->ports, list) अणु
		अगर (dp->ds != ds)
			जारी;
		list_del(&dp->list);
		kमुक्त(dp);
	पूर्ण
पूर्ण

अटल पूर्णांक dsa_चयन_probe(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा dsa_चयन_tree *dst;
	काष्ठा dsa_chip_data *pdata;
	काष्ठा device_node *np;
	पूर्णांक err;

	अगर (!ds->dev)
		वापस -ENODEV;

	pdata = ds->dev->platक्रमm_data;
	np = ds->dev->of_node;

	अगर (!ds->num_ports)
		वापस -EINVAL;

	अगर (np) अणु
		err = dsa_चयन_parse_of(ds, np);
		अगर (err)
			dsa_चयन_release_ports(ds);
	पूर्ण अन्यथा अगर (pdata) अणु
		err = dsa_चयन_parse(ds, pdata);
		अगर (err)
			dsa_चयन_release_ports(ds);
	पूर्ण अन्यथा अणु
		err = -ENODEV;
	पूर्ण

	अगर (err)
		वापस err;

	dst = ds->dst;
	dsa_tree_get(dst);
	err = dsa_tree_setup(dst);
	अगर (err) अणु
		dsa_चयन_release_ports(ds);
		dsa_tree_put(dst);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक dsa_रेजिस्टर_चयन(काष्ठा dsa_चयन *ds)
अणु
	पूर्णांक err;

	mutex_lock(&dsa2_mutex);
	err = dsa_चयन_probe(ds);
	dsa_tree_put(ds->dst);
	mutex_unlock(&dsa2_mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_रेजिस्टर_चयन);

अटल व्योम dsa_चयन_हटाओ(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा dsa_चयन_tree *dst = ds->dst;

	dsa_tree_tearकरोwn(dst);
	dsa_चयन_release_ports(ds);
	dsa_tree_put(dst);
पूर्ण

व्योम dsa_unरेजिस्टर_चयन(काष्ठा dsa_चयन *ds)
अणु
	mutex_lock(&dsa2_mutex);
	dsa_चयन_हटाओ(ds);
	mutex_unlock(&dsa2_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_unरेजिस्टर_चयन);
