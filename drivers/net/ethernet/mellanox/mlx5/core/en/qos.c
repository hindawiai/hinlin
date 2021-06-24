<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020, Mellanox Technologies inc. All rights reserved. */

#समावेश "en.h"
#समावेश "params.h"
#समावेश "../qos.h"

#घोषणा BYTES_IN_MBIT 125000

पूर्णांक mlx5e_qos_max_leaf_nodes(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस min(MLX5E_QOS_MAX_LEAF_NODES, mlx5_qos_max_leaf_nodes(mdev));
पूर्ण

पूर्णांक mlx5e_qos_cur_leaf_nodes(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक last = find_last_bit(priv->htb.qos_used_qids, mlx5e_qos_max_leaf_nodes(priv->mdev));

	वापस last == mlx5e_qos_max_leaf_nodes(priv->mdev) ? 0 : last + 1;
पूर्ण

/* Software representation of the QoS tree (पूर्णांकernal to this file) */

अटल पूर्णांक mlx5e_find_unused_qos_qid(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक size = mlx5e_qos_max_leaf_nodes(priv->mdev);
	पूर्णांक res;

	WARN_ONCE(!mutex_is_locked(&priv->state_lock), "%s: state_lock is not held\n", __func__);
	res = find_first_zero_bit(priv->htb.qos_used_qids, size);

	वापस res == size ? -ENOSPC : res;
पूर्ण

काष्ठा mlx5e_qos_node अणु
	काष्ठा hlist_node hnode;
	काष्ठा rcu_head rcu;
	काष्ठा mlx5e_qos_node *parent;
	u64 rate;
	u32 bw_share;
	u32 max_average_bw;
	u32 hw_id;
	u32 classid; /* 16-bit, except root. */
	u16 qid;
पूर्ण;

#घोषणा MLX5E_QOS_QID_INNER 0xffff
#घोषणा MLX5E_HTB_CLASSID_ROOT 0xffffffff

अटल काष्ठा mlx5e_qos_node *
mlx5e_sw_node_create_leaf(काष्ठा mlx5e_priv *priv, u16 classid, u16 qid,
			  काष्ठा mlx5e_qos_node *parent)
अणु
	काष्ठा mlx5e_qos_node *node;

	node = kzalloc(माप(*node), GFP_KERNEL);
	अगर (!node)
		वापस ERR_PTR(-ENOMEM);

	node->parent = parent;

	node->qid = qid;
	__set_bit(qid, priv->htb.qos_used_qids);

	node->classid = classid;
	hash_add_rcu(priv->htb.qos_tc2node, &node->hnode, classid);

	mlx5e_update_tx_netdev_queues(priv);

	वापस node;
पूर्ण

अटल काष्ठा mlx5e_qos_node *mlx5e_sw_node_create_root(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_qos_node *node;

	node = kzalloc(माप(*node), GFP_KERNEL);
	अगर (!node)
		वापस ERR_PTR(-ENOMEM);

	node->qid = MLX5E_QOS_QID_INNER;
	node->classid = MLX5E_HTB_CLASSID_ROOT;
	hash_add_rcu(priv->htb.qos_tc2node, &node->hnode, node->classid);

	वापस node;
पूर्ण

अटल काष्ठा mlx5e_qos_node *mlx5e_sw_node_find(काष्ठा mlx5e_priv *priv, u32 classid)
अणु
	काष्ठा mlx5e_qos_node *node = शून्य;

	hash_क्रम_each_possible(priv->htb.qos_tc2node, node, hnode, classid) अणु
		अगर (node->classid == classid)
			अवरोध;
	पूर्ण

	वापस node;
पूर्ण

अटल काष्ठा mlx5e_qos_node *mlx5e_sw_node_find_rcu(काष्ठा mlx5e_priv *priv, u32 classid)
अणु
	काष्ठा mlx5e_qos_node *node = शून्य;

	hash_क्रम_each_possible_rcu(priv->htb.qos_tc2node, node, hnode, classid) अणु
		अगर (node->classid == classid)
			अवरोध;
	पूर्ण

	वापस node;
पूर्ण

अटल व्योम mlx5e_sw_node_delete(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_qos_node *node)
अणु
	hash_del_rcu(&node->hnode);
	अगर (node->qid != MLX5E_QOS_QID_INNER) अणु
		__clear_bit(node->qid, priv->htb.qos_used_qids);
		mlx5e_update_tx_netdev_queues(priv);
	पूर्ण
	kमुक्त_rcu(node, rcu);
पूर्ण

/* TX datapath API */

अटल u16 mlx5e_qid_from_qos(काष्ठा mlx5e_channels *chs, u16 qid)
अणु
	/* These channel params are safe to access from the datapath, because:
	 * 1. This function is called only after checking priv->htb.maj_id != 0,
	 *    and the number of queues can't change जबतक HTB offload is active.
	 * 2. When priv->htb.maj_id becomes 0, synchronize_rcu रुकोs क्रम
	 *    mlx5e_select_queue to finish जबतक holding priv->state_lock,
	 *    preventing other code from changing the number of queues.
	 */
	bool is_ptp = MLX5E_GET_PFLAG(&chs->params, MLX5E_PFLAG_TX_PORT_TS);

	वापस (chs->params.num_channels + is_ptp) * chs->params.num_tc + qid;
पूर्ण

पूर्णांक mlx5e_get_txq_by_classid(काष्ठा mlx5e_priv *priv, u16 classid)
अणु
	काष्ठा mlx5e_qos_node *node;
	u16 qid;
	पूर्णांक res;

	rcu_पढ़ो_lock();

	node = mlx5e_sw_node_find_rcu(priv, classid);
	अगर (!node) अणु
		res = -ENOENT;
		जाओ out;
	पूर्ण
	qid = READ_ONCE(node->qid);
	अगर (qid == MLX5E_QOS_QID_INNER) अणु
		res = -EINVAL;
		जाओ out;
	पूर्ण
	res = mlx5e_qid_from_qos(&priv->channels, qid);

out:
	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण

अटल काष्ठा mlx5e_txqsq *mlx5e_get_qos_sq(काष्ठा mlx5e_priv *priv, पूर्णांक qid)
अणु
	काष्ठा mlx5e_params *params = &priv->channels.params;
	काष्ठा mlx5e_txqsq __rcu **qos_sqs;
	काष्ठा mlx5e_channel *c;
	पूर्णांक ix;

	ix = qid % params->num_channels;
	qid /= params->num_channels;
	c = priv->channels.c[ix];

	qos_sqs = mlx5e_state_dereference(priv, c->qos_sqs);
	वापस mlx5e_state_dereference(priv, qos_sqs[qid]);
पूर्ण

/* SQ lअगरecycle */

अटल पूर्णांक mlx5e_खोलो_qos_sq(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_channels *chs,
			     काष्ठा mlx5e_qos_node *node)
अणु
	काष्ठा mlx5e_create_cq_param ccp = अणुपूर्ण;
	काष्ठा mlx5e_txqsq __rcu **qos_sqs;
	काष्ठा mlx5e_sq_param param_sq;
	काष्ठा mlx5e_cq_param param_cq;
	पूर्णांक txq_ix, ix, qid, err = 0;
	काष्ठा mlx5e_params *params;
	काष्ठा mlx5e_channel *c;
	काष्ठा mlx5e_txqsq *sq;

	params = &chs->params;

	txq_ix = mlx5e_qid_from_qos(chs, node->qid);

	WARN_ON(node->qid > priv->htb.max_qos_sqs);
	अगर (node->qid == priv->htb.max_qos_sqs) अणु
		काष्ठा mlx5e_sq_stats *stats, **stats_list = शून्य;

		अगर (priv->htb.max_qos_sqs == 0) अणु
			stats_list = kvसुस्मृति(mlx5e_qos_max_leaf_nodes(priv->mdev),
					      माप(*stats_list),
					      GFP_KERNEL);
			अगर (!stats_list)
				वापस -ENOMEM;
		पूर्ण
		stats = kzalloc(माप(*stats), GFP_KERNEL);
		अगर (!stats) अणु
			kvमुक्त(stats_list);
			वापस -ENOMEM;
		पूर्ण
		अगर (stats_list)
			WRITE_ONCE(priv->htb.qos_sq_stats, stats_list);
		WRITE_ONCE(priv->htb.qos_sq_stats[node->qid], stats);
		/* Order max_qos_sqs increment after writing the array poपूर्णांकer.
		 * Pairs with smp_load_acquire in en_stats.c.
		 */
		smp_store_release(&priv->htb.max_qos_sqs, priv->htb.max_qos_sqs + 1);
	पूर्ण

	ix = node->qid % params->num_channels;
	qid = node->qid / params->num_channels;
	c = chs->c[ix];

	qos_sqs = mlx5e_state_dereference(priv, c->qos_sqs);
	sq = kzalloc(माप(*sq), GFP_KERNEL);

	अगर (!sq)
		वापस -ENOMEM;

	mlx5e_build_create_cq_param(&ccp, c);

	स_रखो(&param_sq, 0, माप(param_sq));
	स_रखो(&param_cq, 0, माप(param_cq));
	mlx5e_build_sq_param(priv->mdev, params, &param_sq);
	mlx5e_build_tx_cq_param(priv->mdev, params, &param_cq);
	err = mlx5e_खोलो_cq(priv, params->tx_cq_moderation, &param_cq, &ccp, &sq->cq);
	अगर (err)
		जाओ err_मुक्त_sq;
	err = mlx5e_खोलो_txqsq(c, priv->tisn[c->lag_port][0], txq_ix, params,
			       &param_sq, sq, 0, node->hw_id, node->qid);
	अगर (err)
		जाओ err_बंद_cq;

	rcu_assign_poपूर्णांकer(qos_sqs[qid], sq);

	वापस 0;

err_बंद_cq:
	mlx5e_बंद_cq(&sq->cq);
err_मुक्त_sq:
	kमुक्त(sq);
	वापस err;
पूर्ण

अटल व्योम mlx5e_activate_qos_sq(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_qos_node *node)
अणु
	काष्ठा mlx5e_txqsq *sq;

	sq = mlx5e_get_qos_sq(priv, node->qid);

	WRITE_ONCE(priv->txq2sq[mlx5e_qid_from_qos(&priv->channels, node->qid)], sq);

	/* Make the change to txq2sq visible beक्रमe the queue is started.
	 * As mlx5e_xmit runs under a spinlock, there is an implicit ACQUIRE,
	 * which pairs with this barrier.
	 */
	smp_wmb();

	qos_dbg(priv->mdev, "Activate QoS SQ qid %u\n", node->qid);
	mlx5e_activate_txqsq(sq);
पूर्ण

अटल व्योम mlx5e_deactivate_qos_sq(काष्ठा mlx5e_priv *priv, u16 qid)
अणु
	काष्ठा mlx5e_txqsq *sq;

	sq = mlx5e_get_qos_sq(priv, qid);
	अगर (!sq) /* Handle the हाल when the SQ failed to खोलो. */
		वापस;

	qos_dbg(priv->mdev, "Deactivate QoS SQ qid %u\n", qid);
	mlx5e_deactivate_txqsq(sq);

	/* The queue is disabled, no synchronization with datapath is needed. */
	priv->txq2sq[mlx5e_qid_from_qos(&priv->channels, qid)] = शून्य;
पूर्ण

अटल व्योम mlx5e_बंद_qos_sq(काष्ठा mlx5e_priv *priv, u16 qid)
अणु
	काष्ठा mlx5e_txqsq __rcu **qos_sqs;
	काष्ठा mlx5e_params *params;
	काष्ठा mlx5e_channel *c;
	काष्ठा mlx5e_txqsq *sq;
	पूर्णांक ix;

	params = &priv->channels.params;

	ix = qid % params->num_channels;
	qid /= params->num_channels;
	c = priv->channels.c[ix];
	qos_sqs = mlx5e_state_dereference(priv, c->qos_sqs);
	sq = rcu_replace_poपूर्णांकer(qos_sqs[qid], शून्य, lockdep_is_held(&priv->state_lock));
	अगर (!sq) /* Handle the हाल when the SQ failed to खोलो. */
		वापस;

	synchronize_rcu(); /* Sync with NAPI. */

	mlx5e_बंद_txqsq(sq);
	mlx5e_बंद_cq(&sq->cq);
	kमुक्त(sq);
पूर्ण

व्योम mlx5e_qos_बंद_queues(काष्ठा mlx5e_channel *c)
अणु
	काष्ठा mlx5e_txqsq __rcu **qos_sqs;
	पूर्णांक i;

	qos_sqs = rcu_replace_poपूर्णांकer(c->qos_sqs, शून्य, lockdep_is_held(&c->priv->state_lock));
	अगर (!qos_sqs)
		वापस;
	synchronize_rcu(); /* Sync with NAPI. */

	क्रम (i = 0; i < c->qos_sqs_size; i++) अणु
		काष्ठा mlx5e_txqsq *sq;

		sq = mlx5e_state_dereference(c->priv, qos_sqs[i]);
		अगर (!sq) /* Handle the हाल when the SQ failed to खोलो. */
			जारी;

		mlx5e_बंद_txqsq(sq);
		mlx5e_बंद_cq(&sq->cq);
		kमुक्त(sq);
	पूर्ण

	kvमुक्त(qos_sqs);
पूर्ण

अटल व्योम mlx5e_qos_बंद_all_queues(काष्ठा mlx5e_channels *chs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < chs->num; i++)
		mlx5e_qos_बंद_queues(chs->c[i]);
पूर्ण

अटल पूर्णांक mlx5e_qos_alloc_queues(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_channels *chs)
अणु
	u16 qos_sqs_size;
	पूर्णांक i;

	qos_sqs_size = DIV_ROUND_UP(mlx5e_qos_max_leaf_nodes(priv->mdev), chs->num);

	क्रम (i = 0; i < chs->num; i++) अणु
		काष्ठा mlx5e_txqsq **sqs;

		sqs = kvसुस्मृति(qos_sqs_size, माप(काष्ठा mlx5e_txqsq *), GFP_KERNEL);
		अगर (!sqs)
			जाओ err_मुक्त;

		WRITE_ONCE(chs->c[i]->qos_sqs_size, qos_sqs_size);
		smp_wmb(); /* Pairs with mlx5e_napi_poll. */
		rcu_assign_poपूर्णांकer(chs->c[i]->qos_sqs, sqs);
	पूर्ण

	वापस 0;

err_मुक्त:
	जबतक (--i >= 0) अणु
		काष्ठा mlx5e_txqsq **sqs;

		sqs = rcu_replace_poपूर्णांकer(chs->c[i]->qos_sqs, शून्य,
					  lockdep_is_held(&priv->state_lock));

		synchronize_rcu(); /* Sync with NAPI. */
		kvमुक्त(sqs);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

पूर्णांक mlx5e_qos_खोलो_queues(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_channels *chs)
अणु
	काष्ठा mlx5e_qos_node *node = शून्य;
	पूर्णांक bkt, err;

	अगर (!priv->htb.maj_id)
		वापस 0;

	err = mlx5e_qos_alloc_queues(priv, chs);
	अगर (err)
		वापस err;

	hash_क्रम_each(priv->htb.qos_tc2node, bkt, node, hnode) अणु
		अगर (node->qid == MLX5E_QOS_QID_INNER)
			जारी;
		err = mlx5e_खोलो_qos_sq(priv, chs, node);
		अगर (err) अणु
			mlx5e_qos_बंद_all_queues(chs);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम mlx5e_qos_activate_queues(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_qos_node *node = शून्य;
	पूर्णांक bkt;

	hash_क्रम_each(priv->htb.qos_tc2node, bkt, node, hnode) अणु
		अगर (node->qid == MLX5E_QOS_QID_INNER)
			जारी;
		mlx5e_activate_qos_sq(priv, node);
	पूर्ण
पूर्ण

व्योम mlx5e_qos_deactivate_queues(काष्ठा mlx5e_channel *c)
अणु
	काष्ठा mlx5e_params *params = &c->priv->channels.params;
	काष्ठा mlx5e_txqsq __rcu **qos_sqs;
	पूर्णांक i;

	qos_sqs = mlx5e_state_dereference(c->priv, c->qos_sqs);
	अगर (!qos_sqs)
		वापस;

	क्रम (i = 0; i < c->qos_sqs_size; i++) अणु
		u16 qid = params->num_channels * i + c->ix;
		काष्ठा mlx5e_txqsq *sq;

		sq = mlx5e_state_dereference(c->priv, qos_sqs[i]);
		अगर (!sq) /* Handle the हाल when the SQ failed to खोलो. */
			जारी;

		qos_dbg(c->mdev, "Deactivate QoS SQ qid %u\n", qid);
		mlx5e_deactivate_txqsq(sq);

		/* The queue is disabled, no synchronization with datapath is needed. */
		c->priv->txq2sq[mlx5e_qid_from_qos(&c->priv->channels, qid)] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम mlx5e_qos_deactivate_all_queues(काष्ठा mlx5e_channels *chs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < chs->num; i++)
		mlx5e_qos_deactivate_queues(chs->c[i]);
पूर्ण

/* HTB API */

पूर्णांक mlx5e_htb_root_add(काष्ठा mlx5e_priv *priv, u16 htb_maj_id, u16 htb_defcls,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_qos_node *root;
	bool खोलोed;
	पूर्णांक err;

	qos_dbg(priv->mdev, "TC_HTB_CREATE handle %04x:, default :%04x\n", htb_maj_id, htb_defcls);

	अगर (!mlx5_qos_is_supported(priv->mdev)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Missing QoS capabilities. Try disabling SRIOV or use a supported device.");
		वापस -EOPNOTSUPP;
	पूर्ण

	खोलोed = test_bit(MLX5E_STATE_OPENED, &priv->state);
	अगर (खोलोed) अणु
		err = mlx5e_qos_alloc_queues(priv, &priv->channels);
		अगर (err)
			वापस err;
	पूर्ण

	root = mlx5e_sw_node_create_root(priv);
	अगर (IS_ERR(root)) अणु
		err = PTR_ERR(root);
		जाओ err_मुक्त_queues;
	पूर्ण

	err = mlx5_qos_create_root_node(priv->mdev, &root->hw_id);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Firmware error. Try upgrading firmware.");
		जाओ err_sw_node_delete;
	पूर्ण

	WRITE_ONCE(priv->htb.defcls, htb_defcls);
	/* Order maj_id after defcls - pairs with
	 * mlx5e_select_queue/mlx5e_select_htb_queues.
	 */
	smp_store_release(&priv->htb.maj_id, htb_maj_id);

	वापस 0;

err_sw_node_delete:
	mlx5e_sw_node_delete(priv, root);

err_मुक्त_queues:
	अगर (खोलोed)
		mlx5e_qos_बंद_all_queues(&priv->channels);
	वापस err;
पूर्ण

पूर्णांक mlx5e_htb_root_del(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_qos_node *root;
	पूर्णांक err;

	qos_dbg(priv->mdev, "TC_HTB_DESTROY\n");

	WRITE_ONCE(priv->htb.maj_id, 0);
	synchronize_rcu(); /* Sync with mlx5e_select_htb_queue and TX data path. */

	root = mlx5e_sw_node_find(priv, MLX5E_HTB_CLASSID_ROOT);
	अगर (!root) अणु
		qos_err(priv->mdev, "Failed to find the root node in the QoS tree\n");
		वापस -ENOENT;
	पूर्ण
	err = mlx5_qos_destroy_node(priv->mdev, root->hw_id);
	अगर (err)
		qos_err(priv->mdev, "Failed to destroy root node %u, err = %d\n",
			root->hw_id, err);
	mlx5e_sw_node_delete(priv, root);

	mlx5e_qos_deactivate_all_queues(&priv->channels);
	mlx5e_qos_बंद_all_queues(&priv->channels);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_htb_convert_rate(काष्ठा mlx5e_priv *priv, u64 rate,
				  काष्ठा mlx5e_qos_node *parent, u32 *bw_share)
अणु
	u64 share = 0;

	जबतक (parent->classid != MLX5E_HTB_CLASSID_ROOT && !parent->max_average_bw)
		parent = parent->parent;

	अगर (parent->max_average_bw)
		share = भाग64_u64(भाग_u64(rate * 100, BYTES_IN_MBIT),
				  parent->max_average_bw);
	अन्यथा
		share = 101;

	*bw_share = share == 0 ? 1 : share > 100 ? 0 : share;

	qos_dbg(priv->mdev, "Convert: rate %llu, parent ceil %llu -> bw_share %u\n",
		rate, (u64)parent->max_average_bw * BYTES_IN_MBIT, *bw_share);

	वापस 0;
पूर्ण

अटल व्योम mlx5e_htb_convert_उच्चमान(काष्ठा mlx5e_priv *priv, u64 उच्चमान, u32 *max_average_bw)
अणु
	*max_average_bw = भाग_u64(उच्चमान, BYTES_IN_MBIT);

	qos_dbg(priv->mdev, "Convert: ceil %llu -> max_average_bw %u\n",
		उच्चमान, *max_average_bw);
पूर्ण

पूर्णांक mlx5e_htb_leaf_alloc_queue(काष्ठा mlx5e_priv *priv, u16 classid,
			       u32 parent_classid, u64 rate, u64 उच्चमान,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_qos_node *node, *parent;
	पूर्णांक qid;
	पूर्णांक err;

	qos_dbg(priv->mdev, "TC_HTB_LEAF_ALLOC_QUEUE classid %04x, parent %04x, rate %llu, ceil %llu\n",
		classid, parent_classid, rate, उच्चमान);

	qid = mlx5e_find_unused_qos_qid(priv);
	अगर (qid < 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "Maximum amount of leaf classes is reached.");
		वापस qid;
	पूर्ण

	parent = mlx5e_sw_node_find(priv, parent_classid);
	अगर (!parent)
		वापस -EINVAL;

	node = mlx5e_sw_node_create_leaf(priv, classid, qid, parent);
	अगर (IS_ERR(node))
		वापस PTR_ERR(node);

	node->rate = rate;
	mlx5e_htb_convert_rate(priv, rate, node->parent, &node->bw_share);
	mlx5e_htb_convert_उच्चमान(priv, उच्चमान, &node->max_average_bw);

	err = mlx5_qos_create_leaf_node(priv->mdev, node->parent->hw_id,
					node->bw_share, node->max_average_bw,
					&node->hw_id);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Firmware error when creating a leaf node.");
		qos_err(priv->mdev, "Failed to create a leaf node (class %04x), err = %d\n",
			classid, err);
		mlx5e_sw_node_delete(priv, node);
		वापस err;
	पूर्ण

	अगर (test_bit(MLX5E_STATE_OPENED, &priv->state)) अणु
		err = mlx5e_खोलो_qos_sq(priv, &priv->channels, node);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Error creating an SQ.");
			qos_warn(priv->mdev, "Failed to create a QoS SQ (class %04x), err = %d\n",
				 classid, err);
		पूर्ण अन्यथा अणु
			mlx5e_activate_qos_sq(priv, node);
		पूर्ण
	पूर्ण

	वापस mlx5e_qid_from_qos(&priv->channels, node->qid);
पूर्ण

पूर्णांक mlx5e_htb_leaf_to_inner(काष्ठा mlx5e_priv *priv, u16 classid, u16 child_classid,
			    u64 rate, u64 उच्चमान, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_qos_node *node, *child;
	पूर्णांक err, पंचांगp_err;
	u32 new_hw_id;
	u16 qid;

	qos_dbg(priv->mdev, "TC_HTB_LEAF_TO_INNER classid %04x, upcoming child %04x, rate %llu, ceil %llu\n",
		classid, child_classid, rate, उच्चमान);

	node = mlx5e_sw_node_find(priv, classid);
	अगर (!node)
		वापस -ENOENT;

	err = mlx5_qos_create_inner_node(priv->mdev, node->parent->hw_id,
					 node->bw_share, node->max_average_bw,
					 &new_hw_id);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Firmware error when creating an inner node.");
		qos_err(priv->mdev, "Failed to create an inner node (class %04x), err = %d\n",
			classid, err);
		वापस err;
	पूर्ण

	/* Intentionally reuse the qid क्रम the upcoming first child. */
	child = mlx5e_sw_node_create_leaf(priv, child_classid, node->qid, node);
	अगर (IS_ERR(child)) अणु
		err = PTR_ERR(child);
		जाओ err_destroy_hw_node;
	पूर्ण

	child->rate = rate;
	mlx5e_htb_convert_rate(priv, rate, node, &child->bw_share);
	mlx5e_htb_convert_उच्चमान(priv, उच्चमान, &child->max_average_bw);

	err = mlx5_qos_create_leaf_node(priv->mdev, new_hw_id, child->bw_share,
					child->max_average_bw, &child->hw_id);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Firmware error when creating a leaf node.");
		qos_err(priv->mdev, "Failed to create a leaf node (class %04x), err = %d\n",
			classid, err);
		जाओ err_delete_sw_node;
	पूर्ण

	/* No fail poपूर्णांक. */

	qid = node->qid;
	/* Pairs with mlx5e_get_txq_by_classid. */
	WRITE_ONCE(node->qid, MLX5E_QOS_QID_INNER);

	अगर (test_bit(MLX5E_STATE_OPENED, &priv->state)) अणु
		mlx5e_deactivate_qos_sq(priv, qid);
		mlx5e_बंद_qos_sq(priv, qid);
	पूर्ण

	err = mlx5_qos_destroy_node(priv->mdev, node->hw_id);
	अगर (err) /* Not fatal. */
		qos_warn(priv->mdev, "Failed to destroy leaf node %u (class %04x), err = %d\n",
			 node->hw_id, classid, err);

	node->hw_id = new_hw_id;

	अगर (test_bit(MLX5E_STATE_OPENED, &priv->state)) अणु
		err = mlx5e_खोलो_qos_sq(priv, &priv->channels, child);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Error creating an SQ.");
			qos_warn(priv->mdev, "Failed to create a QoS SQ (class %04x), err = %d\n",
				 classid, err);
		पूर्ण अन्यथा अणु
			mlx5e_activate_qos_sq(priv, child);
		पूर्ण
	पूर्ण

	वापस 0;

err_delete_sw_node:
	child->qid = MLX5E_QOS_QID_INNER;
	mlx5e_sw_node_delete(priv, child);

err_destroy_hw_node:
	पंचांगp_err = mlx5_qos_destroy_node(priv->mdev, new_hw_id);
	अगर (पंचांगp_err) /* Not fatal. */
		qos_warn(priv->mdev, "Failed to roll back creation of an inner node %u (class %04x), err = %d\n",
			 new_hw_id, classid, पंचांगp_err);
	वापस err;
पूर्ण

अटल काष्ठा mlx5e_qos_node *mlx5e_sw_node_find_by_qid(काष्ठा mlx5e_priv *priv, u16 qid)
अणु
	काष्ठा mlx5e_qos_node *node = शून्य;
	पूर्णांक bkt;

	hash_क्रम_each(priv->htb.qos_tc2node, bkt, node, hnode)
		अगर (node->qid == qid)
			अवरोध;

	वापस node;
पूर्ण

अटल व्योम mlx5e_reactivate_qos_sq(काष्ठा mlx5e_priv *priv, u16 qid, काष्ठा netdev_queue *txq)
अणु
	qos_dbg(priv->mdev, "Reactivate QoS SQ qid %u\n", qid);
	netdev_tx_reset_queue(txq);
	netअगर_tx_start_queue(txq);
पूर्ण

अटल व्योम mlx5e_reset_qdisc(काष्ठा net_device *dev, u16 qid)
अणु
	काष्ठा netdev_queue *dev_queue = netdev_get_tx_queue(dev, qid);
	काष्ठा Qdisc *qdisc = dev_queue->qdisc_sleeping;

	अगर (!qdisc)
		वापस;

	spin_lock_bh(qdisc_lock(qdisc));
	qdisc_reset(qdisc);
	spin_unlock_bh(qdisc_lock(qdisc));
पूर्ण

पूर्णांक mlx5e_htb_leaf_del(काष्ठा mlx5e_priv *priv, u16 classid, u16 *old_qid,
		       u16 *new_qid, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_qos_node *node;
	काष्ठा netdev_queue *txq;
	u16 qid, moved_qid;
	bool खोलोed;
	पूर्णांक err;

	qos_dbg(priv->mdev, "TC_HTB_LEAF_DEL classid %04x\n", classid);

	*old_qid = *new_qid = 0;

	node = mlx5e_sw_node_find(priv, classid);
	अगर (!node)
		वापस -ENOENT;

	/* Store qid क्रम reuse. */
	qid = node->qid;

	खोलोed = test_bit(MLX5E_STATE_OPENED, &priv->state);
	अगर (खोलोed) अणु
		txq = netdev_get_tx_queue(priv->netdev,
					  mlx5e_qid_from_qos(&priv->channels, qid));
		mlx5e_deactivate_qos_sq(priv, qid);
		mlx5e_बंद_qos_sq(priv, qid);
	पूर्ण

	err = mlx5_qos_destroy_node(priv->mdev, node->hw_id);
	अगर (err) /* Not fatal. */
		qos_warn(priv->mdev, "Failed to destroy leaf node %u (class %04x), err = %d\n",
			 node->hw_id, classid, err);

	mlx5e_sw_node_delete(priv, node);

	moved_qid = mlx5e_qos_cur_leaf_nodes(priv);

	अगर (moved_qid == 0) अणु
		/* The last QoS SQ was just destroyed. */
		अगर (खोलोed)
			mlx5e_reactivate_qos_sq(priv, qid, txq);
		वापस 0;
	पूर्ण
	moved_qid--;

	अगर (moved_qid < qid) अणु
		/* The highest QoS SQ was just destroyed. */
		WARN(moved_qid != qid - 1, "Gaps in queue numeration: destroyed queue %u, the highest queue is %u",
		     qid, moved_qid);
		अगर (खोलोed)
			mlx5e_reactivate_qos_sq(priv, qid, txq);
		वापस 0;
	पूर्ण

	WARN(moved_qid == qid, "Can't move node with qid %u to itself", qid);
	qos_dbg(priv->mdev, "Moving QoS SQ %u to %u\n", moved_qid, qid);

	node = mlx5e_sw_node_find_by_qid(priv, moved_qid);
	WARN(!node, "Could not find a node with qid %u to move to queue %u",
	     moved_qid, qid);

	/* Stop traffic to the old queue. */
	WRITE_ONCE(node->qid, MLX5E_QOS_QID_INNER);
	__clear_bit(moved_qid, priv->htb.qos_used_qids);

	अगर (खोलोed) अणु
		txq = netdev_get_tx_queue(priv->netdev,
					  mlx5e_qid_from_qos(&priv->channels, moved_qid));
		mlx5e_deactivate_qos_sq(priv, moved_qid);
		mlx5e_बंद_qos_sq(priv, moved_qid);
	पूर्ण

	/* Prevent packets from the old class from getting पूर्णांकo the new one. */
	mlx5e_reset_qdisc(priv->netdev, moved_qid);

	__set_bit(qid, priv->htb.qos_used_qids);
	WRITE_ONCE(node->qid, qid);

	अगर (test_bit(MLX5E_STATE_OPENED, &priv->state)) अणु
		err = mlx5e_खोलो_qos_sq(priv, &priv->channels, node);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Error creating an SQ.");
			qos_warn(priv->mdev, "Failed to create a QoS SQ (class %04x) while moving qid %u to %u, err = %d\n",
				 node->classid, moved_qid, qid, err);
		पूर्ण अन्यथा अणु
			mlx5e_activate_qos_sq(priv, node);
		पूर्ण
	पूर्ण

	mlx5e_update_tx_netdev_queues(priv);
	अगर (खोलोed)
		mlx5e_reactivate_qos_sq(priv, moved_qid, txq);

	*old_qid = mlx5e_qid_from_qos(&priv->channels, moved_qid);
	*new_qid = mlx5e_qid_from_qos(&priv->channels, qid);
	वापस 0;
पूर्ण

पूर्णांक mlx5e_htb_leaf_del_last(काष्ठा mlx5e_priv *priv, u16 classid, bool क्रमce,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_qos_node *node, *parent;
	u32 old_hw_id, new_hw_id;
	पूर्णांक err, saved_err = 0;
	u16 qid;

	qos_dbg(priv->mdev, "TC_HTB_LEAF_DEL_LAST%s classid %04x\n",
		क्रमce ? "_FORCE" : "", classid);

	node = mlx5e_sw_node_find(priv, classid);
	अगर (!node)
		वापस -ENOENT;

	err = mlx5_qos_create_leaf_node(priv->mdev, node->parent->parent->hw_id,
					node->parent->bw_share,
					node->parent->max_average_bw,
					&new_hw_id);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Firmware error when creating a leaf node.");
		qos_err(priv->mdev, "Failed to create a leaf node (class %04x), err = %d\n",
			classid, err);
		अगर (!क्रमce)
			वापस err;
		saved_err = err;
	पूर्ण

	/* Store qid क्रम reuse and prevent clearing the bit. */
	qid = node->qid;
	/* Pairs with mlx5e_get_txq_by_classid. */
	WRITE_ONCE(node->qid, MLX5E_QOS_QID_INNER);

	अगर (test_bit(MLX5E_STATE_OPENED, &priv->state)) अणु
		mlx5e_deactivate_qos_sq(priv, qid);
		mlx5e_बंद_qos_sq(priv, qid);
	पूर्ण

	/* Prevent packets from the old class from getting पूर्णांकo the new one. */
	mlx5e_reset_qdisc(priv->netdev, qid);

	err = mlx5_qos_destroy_node(priv->mdev, node->hw_id);
	अगर (err) /* Not fatal. */
		qos_warn(priv->mdev, "Failed to destroy leaf node %u (class %04x), err = %d\n",
			 node->hw_id, classid, err);

	parent = node->parent;
	mlx5e_sw_node_delete(priv, node);

	node = parent;
	WRITE_ONCE(node->qid, qid);

	/* Early वापस on error in क्रमce mode. Parent will still be an inner
	 * node to be deleted by a following delete operation.
	 */
	अगर (saved_err)
		वापस saved_err;

	old_hw_id = node->hw_id;
	node->hw_id = new_hw_id;

	अगर (test_bit(MLX5E_STATE_OPENED, &priv->state)) अणु
		err = mlx5e_खोलो_qos_sq(priv, &priv->channels, node);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Error creating an SQ.");
			qos_warn(priv->mdev, "Failed to create a QoS SQ (class %04x), err = %d\n",
				 classid, err);
		पूर्ण अन्यथा अणु
			mlx5e_activate_qos_sq(priv, node);
		पूर्ण
	पूर्ण

	err = mlx5_qos_destroy_node(priv->mdev, old_hw_id);
	अगर (err) /* Not fatal. */
		qos_warn(priv->mdev, "Failed to destroy leaf node %u (class %04x), err = %d\n",
			 node->hw_id, classid, err);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_qos_update_children(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_qos_node *node,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5e_qos_node *child;
	पूर्णांक err = 0;
	पूर्णांक bkt;

	hash_क्रम_each(priv->htb.qos_tc2node, bkt, child, hnode) अणु
		u32 old_bw_share = child->bw_share;
		पूर्णांक err_one;

		अगर (child->parent != node)
			जारी;

		mlx5e_htb_convert_rate(priv, child->rate, node, &child->bw_share);
		अगर (child->bw_share == old_bw_share)
			जारी;

		err_one = mlx5_qos_update_node(priv->mdev, child->hw_id, child->bw_share,
					       child->max_average_bw, child->hw_id);
		अगर (!err && err_one) अणु
			err = err_one;

			NL_SET_ERR_MSG_MOD(extack, "Firmware error when modifying a child node.");
			qos_err(priv->mdev, "Failed to modify a child node (class %04x), err = %d\n",
				node->classid, err);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक mlx5e_htb_node_modअगरy(काष्ठा mlx5e_priv *priv, u16 classid, u64 rate, u64 उच्चमान,
			  काष्ठा netlink_ext_ack *extack)
अणु
	u32 bw_share, max_average_bw;
	काष्ठा mlx5e_qos_node *node;
	bool उच्चमान_changed = false;
	पूर्णांक err;

	qos_dbg(priv->mdev, "TC_HTB_LEAF_MODIFY classid %04x, rate %llu, ceil %llu\n",
		classid, rate, उच्चमान);

	node = mlx5e_sw_node_find(priv, classid);
	अगर (!node)
		वापस -ENOENT;

	node->rate = rate;
	mlx5e_htb_convert_rate(priv, rate, node->parent, &bw_share);
	mlx5e_htb_convert_उच्चमान(priv, उच्चमान, &max_average_bw);

	err = mlx5_qos_update_node(priv->mdev, node->parent->hw_id, bw_share,
				   max_average_bw, node->hw_id);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Firmware error when modifying a node.");
		qos_err(priv->mdev, "Failed to modify a node (class %04x), err = %d\n",
			classid, err);
		वापस err;
	पूर्ण

	अगर (max_average_bw != node->max_average_bw)
		उच्चमान_changed = true;

	node->bw_share = bw_share;
	node->max_average_bw = max_average_bw;

	अगर (उच्चमान_changed)
		err = mlx5e_qos_update_children(priv, node, extack);

	वापस err;
पूर्ण
