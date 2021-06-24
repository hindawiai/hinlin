<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies. */

#समावेश <net/dst_metadata.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/list.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश "tc.h"
#समावेश "neigh.h"
#समावेश "en_rep.h"
#समावेश "eswitch.h"
#समावेश "lib/fs_chains.h"
#समावेश "en/tc_ct.h"
#समावेश "en/mapping.h"
#समावेश "en/tc_tun.h"
#समावेश "lib/port_tun.h"
#समावेश "esw/sample.h"

काष्ठा mlx5e_rep_indr_block_priv अणु
	काष्ठा net_device *netdev;
	काष्ठा mlx5e_rep_priv *rpriv;

	काष्ठा list_head list;
पूर्ण;

पूर्णांक mlx5e_rep_encap_entry_attach(काष्ठा mlx5e_priv *priv,
				 काष्ठा mlx5e_encap_entry *e,
				 काष्ठा mlx5e_neigh *m_neigh,
				 काष्ठा net_device *neigh_dev)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_rep_uplink_priv *uplink_priv = &rpriv->uplink_priv;
	काष्ठा mlx5_tun_entropy *tun_entropy = &uplink_priv->tun_entropy;
	काष्ठा mlx5e_neigh_hash_entry *nhe;
	पूर्णांक err;

	err = mlx5_tun_entropy_refcount_inc(tun_entropy, e->reक्रमmat_type);
	अगर (err)
		वापस err;

	mutex_lock(&rpriv->neigh_update.encap_lock);
	nhe = mlx5e_rep_neigh_entry_lookup(priv, m_neigh);
	अगर (!nhe) अणु
		err = mlx5e_rep_neigh_entry_create(priv, m_neigh, neigh_dev, &nhe);
		अगर (err) अणु
			mutex_unlock(&rpriv->neigh_update.encap_lock);
			mlx5_tun_entropy_refcount_dec(tun_entropy,
						      e->reक्रमmat_type);
			वापस err;
		पूर्ण
	पूर्ण

	e->nhe = nhe;
	spin_lock(&nhe->encap_list_lock);
	list_add_rcu(&e->encap_list, &nhe->encap_list);
	spin_unlock(&nhe->encap_list_lock);

	mutex_unlock(&rpriv->neigh_update.encap_lock);

	वापस 0;
पूर्ण

व्योम mlx5e_rep_encap_entry_detach(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5e_encap_entry *e)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_rep_uplink_priv *uplink_priv = &rpriv->uplink_priv;
	काष्ठा mlx5_tun_entropy *tun_entropy = &uplink_priv->tun_entropy;

	अगर (!e->nhe)
		वापस;

	spin_lock(&e->nhe->encap_list_lock);
	list_del_rcu(&e->encap_list);
	spin_unlock(&e->nhe->encap_list_lock);

	mlx5e_rep_neigh_entry_release(e->nhe);
	e->nhe = शून्य;
	mlx5_tun_entropy_refcount_dec(tun_entropy, e->reक्रमmat_type);
पूर्ण

व्योम mlx5e_rep_update_flows(काष्ठा mlx5e_priv *priv,
			    काष्ठा mlx5e_encap_entry *e,
			    bool neigh_connected,
			    अचिन्हित अक्षर ha[ETH_ALEN])
अणु
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)e->encap_header;
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	bool encap_connected;
	LIST_HEAD(flow_list);

	ASSERT_RTNL();

	mutex_lock(&esw->offloads.encap_tbl_lock);
	encap_connected = !!(e->flags & MLX5_ENCAP_ENTRY_VALID);
	अगर (encap_connected == neigh_connected && ether_addr_equal(e->h_dest, ha))
		जाओ unlock;

	mlx5e_take_all_encap_flows(e, &flow_list);

	अगर ((e->flags & MLX5_ENCAP_ENTRY_VALID) &&
	    (!neigh_connected || !ether_addr_equal(e->h_dest, ha)))
		mlx5e_tc_encap_flows_del(priv, e, &flow_list);

	अगर (neigh_connected && !(e->flags & MLX5_ENCAP_ENTRY_VALID)) अणु
		काष्ठा net_device *route_dev;

		ether_addr_copy(e->h_dest, ha);
		ether_addr_copy(eth->h_dest, ha);
		/* Update the encap source mac, in हाल that we delete
		 * the flows when encap source mac changed.
		 */
		route_dev = __dev_get_by_index(dev_net(priv->netdev), e->route_dev_अगरindex);
		अगर (route_dev)
			ether_addr_copy(eth->h_source, route_dev->dev_addr);

		mlx5e_tc_encap_flows_add(priv, e, &flow_list);
	पूर्ण
unlock:
	mutex_unlock(&esw->offloads.encap_tbl_lock);
	mlx5e_put_flow_list(priv, &flow_list);
पूर्ण

अटल पूर्णांक
mlx5e_rep_setup_tc_cls_flower(काष्ठा mlx5e_priv *priv,
			      काष्ठा flow_cls_offload *cls_flower, पूर्णांक flags)
अणु
	चयन (cls_flower->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस mlx5e_configure_flower(priv->netdev, priv, cls_flower,
					      flags);
	हाल FLOW_CLS_DESTROY:
		वापस mlx5e_delete_flower(priv->netdev, priv, cls_flower,
					   flags);
	हाल FLOW_CLS_STATS:
		वापस mlx5e_stats_flower(priv->netdev, priv, cls_flower,
					  flags);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल
पूर्णांक mlx5e_rep_setup_tc_cls_matchall(काष्ठा mlx5e_priv *priv,
				    काष्ठा tc_cls_matchall_offload *ma)
अणु
	चयन (ma->command) अणु
	हाल TC_CLSMATCHALL_REPLACE:
		वापस mlx5e_tc_configure_matchall(priv, ma);
	हाल TC_CLSMATCHALL_DESTROY:
		वापस mlx5e_tc_delete_matchall(priv, ma);
	हाल TC_CLSMATCHALL_STATS:
		mlx5e_tc_stats_matchall(priv, ma);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_rep_setup_tc_cb(क्रमागत tc_setup_type type, व्योम *type_data,
				 व्योम *cb_priv)
अणु
	अचिन्हित दीर्घ flags = MLX5_TC_FLAG(INGRESS) | MLX5_TC_FLAG(ESW_OFFLOAD);
	काष्ठा mlx5e_priv *priv = cb_priv;

	अगर (!priv->netdev || !netअगर_device_present(priv->netdev))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस mlx5e_rep_setup_tc_cls_flower(priv, type_data, flags);
	हाल TC_SETUP_CLSMATCHALL:
		वापस mlx5e_rep_setup_tc_cls_matchall(priv, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_rep_setup_ft_cb(क्रमागत tc_setup_type type, व्योम *type_data,
				 व्योम *cb_priv)
अणु
	काष्ठा flow_cls_offload पंचांगp, *f = type_data;
	काष्ठा mlx5e_priv *priv = cb_priv;
	काष्ठा mlx5_eचयन *esw;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	flags = MLX5_TC_FLAG(INGRESS) |
		MLX5_TC_FLAG(ESW_OFFLOAD) |
		MLX5_TC_FLAG(FT_OFFLOAD);
	esw = priv->mdev->priv.eचयन;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		स_नकल(&पंचांगp, f, माप(*f));

		अगर (!mlx5_chains_prios_supported(esw_chains(esw)))
			वापस -EOPNOTSUPP;

		/* Re-use tc offload path by moving the ft flow to the
		 * reserved ft chain.
		 *
		 * FT offload can use prio range [0, पूर्णांक_उच्च], so we normalize
		 * it to range [1, mlx5_esw_chains_get_prio_range(esw)]
		 * as with tc, where prio 0 isn't supported.
		 *
		 * We only support chain 0 of FT offload.
		 */
		अगर (पंचांगp.common.prio >= mlx5_chains_get_prio_range(esw_chains(esw)))
			वापस -EOPNOTSUPP;
		अगर (पंचांगp.common.chain_index != 0)
			वापस -EOPNOTSUPP;

		पंचांगp.common.chain_index = mlx5_chains_get_nf_ft_chain(esw_chains(esw));
		पंचांगp.common.prio++;
		err = mlx5e_rep_setup_tc_cls_flower(priv, &पंचांगp, flags);
		स_नकल(&f->stats, &पंचांगp.stats, माप(f->stats));
		वापस err;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल LIST_HEAD(mlx5e_rep_block_tc_cb_list);
अटल LIST_HEAD(mlx5e_rep_block_ft_cb_list);
पूर्णांक mlx5e_rep_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
		       व्योम *type_data)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा flow_block_offload *f = type_data;

	f->unlocked_driver_cb = true;

	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस flow_block_cb_setup_simple(type_data,
						  &mlx5e_rep_block_tc_cb_list,
						  mlx5e_rep_setup_tc_cb,
						  priv, priv, true);
	हाल TC_SETUP_FT:
		वापस flow_block_cb_setup_simple(type_data,
						  &mlx5e_rep_block_ft_cb_list,
						  mlx5e_rep_setup_ft_cb,
						  priv, priv, true);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक mlx5e_rep_tc_init(काष्ठा mlx5e_rep_priv *rpriv)
अणु
	काष्ठा mlx5_rep_uplink_priv *uplink_priv = &rpriv->uplink_priv;
	पूर्णांक err;

	mutex_init(&uplink_priv->unपढ़ोy_flows_lock);
	INIT_LIST_HEAD(&uplink_priv->unपढ़ोy_flows);

	/* init shared tc flow table */
	err = mlx5e_tc_esw_init(&uplink_priv->tc_ht);
	वापस err;
पूर्ण

व्योम mlx5e_rep_tc_cleanup(काष्ठा mlx5e_rep_priv *rpriv)
अणु
	/* delete shared tc flow table */
	mlx5e_tc_esw_cleanup(&rpriv->uplink_priv.tc_ht);
	mutex_destroy(&rpriv->uplink_priv.unपढ़ोy_flows_lock);
पूर्ण

व्योम mlx5e_rep_tc_enable(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;

	INIT_WORK(&rpriv->uplink_priv.reoffload_flows_work,
		  mlx5e_tc_reoffload_flows_work);
पूर्ण

व्योम mlx5e_rep_tc_disable(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;

	cancel_work_sync(&rpriv->uplink_priv.reoffload_flows_work);
पूर्ण

पूर्णांक mlx5e_rep_tc_event_port_affinity(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;

	queue_work(priv->wq, &rpriv->uplink_priv.reoffload_flows_work);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा mlx5e_rep_indr_block_priv *
mlx5e_rep_indr_block_priv_lookup(काष्ठा mlx5e_rep_priv *rpriv,
				 काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_rep_indr_block_priv *cb_priv;

	/* All callback list access should be रक्षित by RTNL. */
	ASSERT_RTNL();

	list_क्रम_each_entry(cb_priv,
			    &rpriv->uplink_priv.tc_indr_block_priv_list,
			    list)
		अगर (cb_priv->netdev == netdev)
			वापस cb_priv;

	वापस शून्य;
पूर्ण

अटल पूर्णांक
mlx5e_rep_indr_offload(काष्ठा net_device *netdev,
		       काष्ठा flow_cls_offload *flower,
		       काष्ठा mlx5e_rep_indr_block_priv *indr_priv,
		       अचिन्हित दीर्घ flags)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(indr_priv->rpriv->netdev);
	पूर्णांक err = 0;

	अगर (!netअगर_device_present(indr_priv->rpriv->netdev))
		वापस -EOPNOTSUPP;

	चयन (flower->command) अणु
	हाल FLOW_CLS_REPLACE:
		err = mlx5e_configure_flower(netdev, priv, flower, flags);
		अवरोध;
	हाल FLOW_CLS_DESTROY:
		err = mlx5e_delete_flower(netdev, priv, flower, flags);
		अवरोध;
	हाल FLOW_CLS_STATS:
		err = mlx5e_stats_flower(netdev, priv, flower, flags);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_rep_indr_setup_tc_cb(क्रमागत tc_setup_type type,
				      व्योम *type_data, व्योम *indr_priv)
अणु
	अचिन्हित दीर्घ flags = MLX5_TC_FLAG(EGRESS) | MLX5_TC_FLAG(ESW_OFFLOAD);
	काष्ठा mlx5e_rep_indr_block_priv *priv = indr_priv;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस mlx5e_rep_indr_offload(priv->netdev, type_data, priv,
					      flags);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_rep_indr_setup_ft_cb(क्रमागत tc_setup_type type,
				      व्योम *type_data, व्योम *indr_priv)
अणु
	काष्ठा mlx5e_rep_indr_block_priv *priv = indr_priv;
	काष्ठा flow_cls_offload *f = type_data;
	काष्ठा flow_cls_offload पंचांगp;
	काष्ठा mlx5e_priv *mpriv;
	काष्ठा mlx5_eचयन *esw;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	mpriv = netdev_priv(priv->rpriv->netdev);
	esw = mpriv->mdev->priv.eचयन;

	flags = MLX5_TC_FLAG(EGRESS) |
		MLX5_TC_FLAG(ESW_OFFLOAD) |
		MLX5_TC_FLAG(FT_OFFLOAD);

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		स_नकल(&पंचांगp, f, माप(*f));

		/* Re-use tc offload path by moving the ft flow to the
		 * reserved ft chain.
		 *
		 * FT offload can use prio range [0, पूर्णांक_उच्च], so we normalize
		 * it to range [1, mlx5_esw_chains_get_prio_range(esw)]
		 * as with tc, where prio 0 isn't supported.
		 *
		 * We only support chain 0 of FT offload.
		 */
		अगर (!mlx5_chains_prios_supported(esw_chains(esw)) ||
		    पंचांगp.common.prio >= mlx5_chains_get_prio_range(esw_chains(esw)) ||
		    पंचांगp.common.chain_index)
			वापस -EOPNOTSUPP;

		पंचांगp.common.chain_index = mlx5_chains_get_nf_ft_chain(esw_chains(esw));
		पंचांगp.common.prio++;
		err = mlx5e_rep_indr_offload(priv->netdev, &पंचांगp, priv, flags);
		स_नकल(&f->stats, &पंचांगp.stats, माप(f->stats));
		वापस err;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम mlx5e_rep_indr_block_unbind(व्योम *cb_priv)
अणु
	काष्ठा mlx5e_rep_indr_block_priv *indr_priv = cb_priv;

	list_del(&indr_priv->list);
	kमुक्त(indr_priv);
पूर्ण

अटल LIST_HEAD(mlx5e_block_cb_list);

अटल पूर्णांक
mlx5e_rep_indr_setup_block(काष्ठा net_device *netdev, काष्ठा Qdisc *sch,
			   काष्ठा mlx5e_rep_priv *rpriv,
			   काष्ठा flow_block_offload *f,
			   flow_setup_cb_t *setup_cb,
			   व्योम *data,
			   व्योम (*cleanup)(काष्ठा flow_block_cb *block_cb))
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(rpriv->netdev);
	काष्ठा mlx5e_rep_indr_block_priv *indr_priv;
	काष्ठा flow_block_cb *block_cb;

	अगर (!mlx5e_tc_tun_device_to_offload(priv, netdev) &&
	    !(is_vlan_dev(netdev) && vlan_dev_real_dev(netdev) == rpriv->netdev))
		वापस -EOPNOTSUPP;

	अगर (f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS)
		वापस -EOPNOTSUPP;

	f->unlocked_driver_cb = true;
	f->driver_block_list = &mlx5e_block_cb_list;

	चयन (f->command) अणु
	हाल FLOW_BLOCK_BIND:
		indr_priv = mlx5e_rep_indr_block_priv_lookup(rpriv, netdev);
		अगर (indr_priv)
			वापस -EEXIST;

		indr_priv = kदो_स्मृति(माप(*indr_priv), GFP_KERNEL);
		अगर (!indr_priv)
			वापस -ENOMEM;

		indr_priv->netdev = netdev;
		indr_priv->rpriv = rpriv;
		list_add(&indr_priv->list,
			 &rpriv->uplink_priv.tc_indr_block_priv_list);

		block_cb = flow_indr_block_cb_alloc(setup_cb, indr_priv, indr_priv,
						    mlx5e_rep_indr_block_unbind,
						    f, netdev, sch, data, rpriv,
						    cleanup);
		अगर (IS_ERR(block_cb)) अणु
			list_del(&indr_priv->list);
			kमुक्त(indr_priv);
			वापस PTR_ERR(block_cb);
		पूर्ण
		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, &mlx5e_block_cb_list);

		वापस 0;
	हाल FLOW_BLOCK_UNBIND:
		indr_priv = mlx5e_rep_indr_block_priv_lookup(rpriv, netdev);
		अगर (!indr_priv)
			वापस -ENOENT;

		block_cb = flow_block_cb_lookup(f->block, setup_cb, indr_priv);
		अगर (!block_cb)
			वापस -ENOENT;

		flow_indr_block_cb_हटाओ(block_cb, f);
		list_del(&block_cb->driver_list);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल
पूर्णांक mlx5e_rep_indr_setup_cb(काष्ठा net_device *netdev, काष्ठा Qdisc *sch, व्योम *cb_priv,
			    क्रमागत tc_setup_type type, व्योम *type_data,
			    व्योम *data,
			    व्योम (*cleanup)(काष्ठा flow_block_cb *block_cb))
अणु
	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस mlx5e_rep_indr_setup_block(netdev, sch, cb_priv, type_data,
						  mlx5e_rep_indr_setup_tc_cb,
						  data, cleanup);
	हाल TC_SETUP_FT:
		वापस mlx5e_rep_indr_setup_block(netdev, sch, cb_priv, type_data,
						  mlx5e_rep_indr_setup_ft_cb,
						  data, cleanup);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक mlx5e_rep_tc_netdevice_event_रेजिस्टर(काष्ठा mlx5e_rep_priv *rpriv)
अणु
	काष्ठा mlx5_rep_uplink_priv *uplink_priv = &rpriv->uplink_priv;

	/* init indirect block notअगरications */
	INIT_LIST_HEAD(&uplink_priv->tc_indr_block_priv_list);

	वापस flow_indr_dev_रेजिस्टर(mlx5e_rep_indr_setup_cb, rpriv);
पूर्ण

व्योम mlx5e_rep_tc_netdevice_event_unरेजिस्टर(काष्ठा mlx5e_rep_priv *rpriv)
अणु
	flow_indr_dev_unरेजिस्टर(mlx5e_rep_indr_setup_cb, rpriv,
				 mlx5e_rep_indr_block_unbind);
पूर्ण

#अगर IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
अटल bool mlx5e_restore_tunnel(काष्ठा mlx5e_priv *priv, काष्ठा sk_buff *skb,
				 काष्ठा mlx5e_tc_update_priv *tc_priv,
				 u32 tunnel_id)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा tunnel_match_enc_opts enc_opts = अणुपूर्ण;
	काष्ठा mlx5_rep_uplink_priv *uplink_priv;
	काष्ठा mlx5e_rep_priv *uplink_rpriv;
	काष्ठा metadata_dst *tun_dst;
	काष्ठा tunnel_match_key key;
	u32 tun_id, enc_opts_id;
	काष्ठा net_device *dev;
	पूर्णांक err;

	enc_opts_id = tunnel_id & ENC_OPTS_BITS_MASK;
	tun_id = tunnel_id >> ENC_OPTS_BITS;

	अगर (!tun_id)
		वापस true;

	uplink_rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
	uplink_priv = &uplink_rpriv->uplink_priv;

	err = mapping_find(uplink_priv->tunnel_mapping, tun_id, &key);
	अगर (err) अणु
		WARN_ON_ONCE(true);
		netdev_dbg(priv->netdev,
			   "Couldn't find tunnel for tun_id: %d, err: %d\n",
			   tun_id, err);
		वापस false;
	पूर्ण

	अगर (enc_opts_id) अणु
		err = mapping_find(uplink_priv->tunnel_enc_opts_mapping,
				   enc_opts_id, &enc_opts);
		अगर (err) अणु
			netdev_dbg(priv->netdev,
				   "Couldn't find tunnel (opts) for tun_id: %d, err: %d\n",
				   enc_opts_id, err);
			वापस false;
		पूर्ण
	पूर्ण

	अगर (key.enc_control.addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
		tun_dst = __ip_tun_set_dst(key.enc_ipv4.src, key.enc_ipv4.dst,
					   key.enc_ip.tos, key.enc_ip.ttl,
					   key.enc_tp.dst, TUNNEL_KEY,
					   key32_to_tunnel_id(key.enc_key_id.keyid),
					   enc_opts.key.len);
	पूर्ण अन्यथा अगर (key.enc_control.addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) अणु
		tun_dst = __ipv6_tun_set_dst(&key.enc_ipv6.src, &key.enc_ipv6.dst,
					     key.enc_ip.tos, key.enc_ip.ttl,
					     key.enc_tp.dst, 0, TUNNEL_KEY,
					     key32_to_tunnel_id(key.enc_key_id.keyid),
					     enc_opts.key.len);
	पूर्ण अन्यथा अणु
		netdev_dbg(priv->netdev,
			   "Couldn't restore tunnel, unsupported addr_type: %d\n",
			   key.enc_control.addr_type);
		वापस false;
	पूर्ण

	अगर (!tun_dst) अणु
		netdev_dbg(priv->netdev, "Couldn't restore tunnel, no tun_dst\n");
		वापस false;
	पूर्ण

	tun_dst->u.tun_info.key.tp_src = key.enc_tp.src;

	अगर (enc_opts.key.len)
		ip_tunnel_info_opts_set(&tun_dst->u.tun_info,
					enc_opts.key.data,
					enc_opts.key.len,
					enc_opts.key.dst_opt_type);

	skb_dst_set(skb, (काष्ठा dst_entry *)tun_dst);
	dev = dev_get_by_index(&init_net, key.filter_अगरindex);
	अगर (!dev) अणु
		netdev_dbg(priv->netdev,
			   "Couldn't find tunnel device with ifindex: %d\n",
			   key.filter_अगरindex);
		वापस false;
	पूर्ण

	/* Set tun_dev so we करो dev_put() after datapath */
	tc_priv->tun_dev = dev;

	skb->dev = dev;

	वापस true;
पूर्ण

अटल bool mlx5e_restore_skb(काष्ठा sk_buff *skb, u32 chain, u32 reg_c1,
			      काष्ठा mlx5e_tc_update_priv *tc_priv)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(skb->dev);
	u32 tunnel_id = reg_c1 >> ESW_TUN_OFFSET;

	अगर (chain) अणु
		काष्ठा mlx5_rep_uplink_priv *uplink_priv;
		काष्ठा mlx5e_rep_priv *uplink_rpriv;
		काष्ठा tc_skb_ext *tc_skb_ext;
		काष्ठा mlx5_eचयन *esw;
		u32 zone_restore_id;

		tc_skb_ext = tc_skb_ext_alloc(skb);
		अगर (!tc_skb_ext) अणु
			WARN_ON(1);
			वापस false;
		पूर्ण
		tc_skb_ext->chain = chain;
		zone_restore_id = reg_c1 & ESW_ZONE_ID_MASK;
		esw = priv->mdev->priv.eचयन;
		uplink_rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
		uplink_priv = &uplink_rpriv->uplink_priv;
		अगर (!mlx5e_tc_ct_restore_flow(uplink_priv->ct_priv, skb,
					      zone_restore_id))
			वापस false;
	पूर्ण
	वापस mlx5e_restore_tunnel(priv, skb, tc_priv, tunnel_id);
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_TC_SKB_EXT */

bool mlx5e_rep_tc_update_skb(काष्ठा mlx5_cqe64 *cqe,
			     काष्ठा sk_buff *skb,
			     काष्ठा mlx5e_tc_update_priv *tc_priv)
अणु
	काष्ठा mlx5_mapped_obj mapped_obj;
	काष्ठा mlx5_eचयन *esw;
	काष्ठा mlx5e_priv *priv;
	u32 reg_c0, reg_c1;
	पूर्णांक err;

	reg_c0 = (be32_to_cpu(cqe->sop_drop_qpn) & MLX5E_TC_FLOW_ID_MASK);
	अगर (!reg_c0 || reg_c0 == MLX5_FS_DEFAULT_FLOW_TAG)
		वापस true;

	/* If reg_c0 is not equal to the शेष flow tag then skb->mark
	 * is not supported and must be reset back to 0.
	 */
	skb->mark = 0;

	reg_c1 = be32_to_cpu(cqe->ft_metadata);

	priv = netdev_priv(skb->dev);
	esw = priv->mdev->priv.eचयन;
	err = mapping_find(esw->offloads.reg_c0_obj_pool, reg_c0, &mapped_obj);
	अगर (err) अणु
		netdev_dbg(priv->netdev,
			   "Couldn't find mapped object for reg_c0: %d, err: %d\n",
			   reg_c0, err);
		वापस false;
	पूर्ण

#अगर IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
	अगर (mapped_obj.type == MLX5_MAPPED_OBJ_CHAIN)
		वापस mlx5e_restore_skb(skb, mapped_obj.chain, reg_c1, tc_priv);
#पूर्ण_अगर /* CONFIG_NET_TC_SKB_EXT */
#अगर IS_ENABLED(CONFIG_MLX5_TC_SAMPLE)
	अगर (mapped_obj.type == MLX5_MAPPED_OBJ_SAMPLE) अणु
		mlx5_esw_sample_skb(skb, &mapped_obj);
		वापस false;
	पूर्ण
#पूर्ण_अगर /* CONFIG_MLX5_TC_SAMPLE */
	अगर (mapped_obj.type != MLX5_MAPPED_OBJ_SAMPLE &&
	    mapped_obj.type != MLX5_MAPPED_OBJ_CHAIN) अणु
		netdev_dbg(priv->netdev, "Invalid mapped object type: %d\n", mapped_obj.type);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम mlx5_rep_tc_post_napi_receive(काष्ठा mlx5e_tc_update_priv *tc_priv)
अणु
	अगर (tc_priv->tun_dev)
		dev_put(tc_priv->tun_dev);
पूर्ण
