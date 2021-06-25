<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies */

#समावेश <net/page_pool.h>
#समावेश "en/txrx.h"
#समावेश "en/params.h"
#समावेश "en/trap.h"

अटल पूर्णांक mlx5e_trap_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mlx5e_trap *trap_ctx = container_of(napi, काष्ठा mlx5e_trap, napi);
	काष्ठा mlx5e_ch_stats *ch_stats = trap_ctx->stats;
	काष्ठा mlx5e_rq *rq = &trap_ctx->rq;
	bool busy = false;
	पूर्णांक work_करोne = 0;

	ch_stats->poll++;

	work_करोne = mlx5e_poll_rx_cq(&rq->cq, budget);
	busy |= work_करोne == budget;
	busy |= rq->post_wqes(rq);

	अगर (busy)
		वापस budget;

	अगर (unlikely(!napi_complete_करोne(napi, work_करोne)))
		वापस work_करोne;

	mlx5e_cq_arm(&rq->cq);
	वापस work_करोne;
पूर्ण

अटल व्योम mlx5e_init_trap_rq(काष्ठा mlx5e_trap *t, काष्ठा mlx5e_params *params,
			       काष्ठा mlx5e_rq *rq)
अणु
	काष्ठा mlx5_core_dev *mdev = t->mdev;
	काष्ठा mlx5e_priv *priv = t->priv;

	rq->wq_type      = params->rq_wq_type;
	rq->pdev         = mdev->device;
	rq->netdev       = priv->netdev;
	rq->priv         = priv;
	rq->घड़ी        = &mdev->घड़ी;
	rq->tstamp       = &priv->tstamp;
	rq->mdev         = mdev;
	rq->hw_mtu       = MLX5E_SW2HW_MTU(params, params->sw_mtu);
	rq->stats        = &priv->trap_stats.rq;
	rq->ptp_cyc2समय = mlx5_rq_ts_translator(mdev);
	xdp_rxq_info_unused(&rq->xdp_rxq);
	mlx5e_rq_set_trap_handlers(rq, params);
पूर्ण

अटल पूर्णांक mlx5e_खोलो_trap_rq(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_trap *t)
अणु
	काष्ठा mlx5e_rq_param *rq_param = &t->rq_param;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_create_cq_param ccp = अणुपूर्ण;
	काष्ठा dim_cq_moder trap_moder = अणुपूर्ण;
	काष्ठा mlx5e_rq *rq = &t->rq;
	पूर्णांक node;
	पूर्णांक err;

	node = dev_to_node(mdev->device);

	ccp.node     = node;
	ccp.ch_stats = t->stats;
	ccp.napi     = &t->napi;
	ccp.ix       = 0;
	err = mlx5e_खोलो_cq(priv, trap_moder, &rq_param->cqp, &ccp, &rq->cq);
	अगर (err)
		वापस err;

	mlx5e_init_trap_rq(t, &t->params, rq);
	err = mlx5e_खोलो_rq(&t->params, rq_param, शून्य, node, rq);
	अगर (err)
		जाओ err_destroy_cq;

	वापस 0;

err_destroy_cq:
	mlx5e_बंद_cq(&rq->cq);

	वापस err;
पूर्ण

अटल व्योम mlx5e_बंद_trap_rq(काष्ठा mlx5e_rq *rq)
अणु
	mlx5e_बंद_rq(rq);
	mlx5e_बंद_cq(&rq->cq);
पूर्ण

अटल पूर्णांक mlx5e_create_trap_direct_rq_tir(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_tir *tir,
					   u32 rqn)
अणु
	व्योम *tirc;
	पूर्णांक inlen;
	u32 *in;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(create_tir_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	tirc = MLX5_ADDR_OF(create_tir_in, in, ctx);
	MLX5_SET(tirc, tirc, transport_करोमुख्य, mdev->mlx5e_res.hw_objs.td.tdn);
	MLX5_SET(tirc, tirc, rx_hash_fn, MLX5_RX_HASH_FN_NONE);
	MLX5_SET(tirc, tirc, disp_type, MLX5_TIRC_DISP_TYPE_सूचीECT);
	MLX5_SET(tirc, tirc, अंतरभूत_rqn, rqn);
	err = mlx5e_create_tir(mdev, tir, in);
	kvमुक्त(in);

	वापस err;
पूर्ण

अटल व्योम mlx5e_destroy_trap_direct_rq_tir(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_tir *tir)
अणु
	mlx5e_destroy_tir(mdev, tir);
पूर्ण

अटल व्योम mlx5e_build_trap_params(काष्ठा mlx5_core_dev *mdev,
				    पूर्णांक max_mtu, u16 q_counter,
				    काष्ठा mlx5e_trap *t)
अणु
	काष्ठा mlx5e_params *params = &t->params;

	params->rq_wq_type = MLX5_WQ_TYPE_CYCLIC;
	mlx5e_init_rq_type_params(mdev, params);
	params->sw_mtu = max_mtu;
	mlx5e_build_rq_param(mdev, params, शून्य, q_counter, &t->rq_param);
पूर्ण

अटल काष्ठा mlx5e_trap *mlx5e_खोलो_trap(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक cpu = cpumask_first(mlx5_comp_irq_get_affinity_mask(priv->mdev, 0));
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा mlx5e_trap *t;
	पूर्णांक err;

	t = kvzalloc_node(माप(*t), GFP_KERNEL, cpu_to_node(cpu));
	अगर (!t)
		वापस ERR_PTR(-ENOMEM);

	mlx5e_build_trap_params(priv->mdev, netdev->max_mtu, priv->q_counter, t);

	t->priv     = priv;
	t->mdev     = priv->mdev;
	t->tstamp   = &priv->tstamp;
	t->pdev     = mlx5_core_dma_dev(priv->mdev);
	t->netdev   = priv->netdev;
	t->mkey_be  = cpu_to_be32(priv->mdev->mlx5e_res.hw_objs.mkey.key);
	t->stats    = &priv->trap_stats.ch;

	netअगर_napi_add(netdev, &t->napi, mlx5e_trap_napi_poll, 64);

	err = mlx5e_खोलो_trap_rq(priv, t);
	अगर (unlikely(err))
		जाओ err_napi_del;

	err = mlx5e_create_trap_direct_rq_tir(t->mdev, &t->tir, t->rq.rqn);
	अगर (err)
		जाओ err_बंद_trap_rq;

	वापस t;

err_बंद_trap_rq:
	mlx5e_बंद_trap_rq(&t->rq);
err_napi_del:
	netअगर_napi_del(&t->napi);
	kvमुक्त(t);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlx5e_बंद_trap(काष्ठा mlx5e_trap *trap)
अणु
	mlx5e_destroy_trap_direct_rq_tir(trap->mdev, &trap->tir);
	mlx5e_बंद_trap_rq(&trap->rq);
	netअगर_napi_del(&trap->napi);
	kvमुक्त(trap);
पूर्ण

अटल व्योम mlx5e_activate_trap(काष्ठा mlx5e_trap *trap)
अणु
	napi_enable(&trap->napi);
	mlx5e_activate_rq(&trap->rq);
पूर्ण

व्योम mlx5e_deactivate_trap(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_trap *trap = priv->en_trap;

	mlx5e_deactivate_rq(&trap->rq);
	napi_disable(&trap->napi);
पूर्ण

अटल काष्ठा mlx5e_trap *mlx5e_add_trap_queue(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_trap *trap;

	trap = mlx5e_खोलो_trap(priv);
	अगर (IS_ERR(trap))
		जाओ out;

	mlx5e_activate_trap(trap);
out:
	वापस trap;
पूर्ण

अटल व्योम mlx5e_del_trap_queue(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_deactivate_trap(priv);
	mlx5e_बंद_trap(priv->en_trap);
	priv->en_trap = शून्य;
पूर्ण

अटल पूर्णांक mlx5e_trap_get_tirn(काष्ठा mlx5e_trap *en_trap)
अणु
	वापस en_trap->tir.tirn;
पूर्ण

अटल पूर्णांक mlx5e_handle_action_trap(काष्ठा mlx5e_priv *priv, पूर्णांक trap_id)
अणु
	bool खोलो_queue = !priv->en_trap;
	काष्ठा mlx5e_trap *trap;
	पूर्णांक err;

	अगर (खोलो_queue) अणु
		trap = mlx5e_add_trap_queue(priv);
		अगर (IS_ERR(trap))
			वापस PTR_ERR(trap);
		priv->en_trap = trap;
	पूर्ण

	चयन (trap_id) अणु
	हाल DEVLINK_TRAP_GENERIC_ID_INGRESS_VLAN_FILTER:
		err = mlx5e_add_vlan_trap(priv, trap_id, mlx5e_trap_get_tirn(priv->en_trap));
		अगर (err)
			जाओ err_out;
		अवरोध;
	हाल DEVLINK_TRAP_GENERIC_ID_DMAC_FILTER:
		err = mlx5e_add_mac_trap(priv, trap_id, mlx5e_trap_get_tirn(priv->en_trap));
		अगर (err)
			जाओ err_out;
		अवरोध;
	शेष:
		netdev_warn(priv->netdev, "%s: Unknown trap id %d\n", __func__, trap_id);
		err = -EINVAL;
		जाओ err_out;
	पूर्ण
	वापस 0;

err_out:
	अगर (खोलो_queue)
		mlx5e_del_trap_queue(priv);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_handle_action_drop(काष्ठा mlx5e_priv *priv, पूर्णांक trap_id)
अणु
	चयन (trap_id) अणु
	हाल DEVLINK_TRAP_GENERIC_ID_INGRESS_VLAN_FILTER:
		mlx5e_हटाओ_vlan_trap(priv);
		अवरोध;
	हाल DEVLINK_TRAP_GENERIC_ID_DMAC_FILTER:
		mlx5e_हटाओ_mac_trap(priv);
		अवरोध;
	शेष:
		netdev_warn(priv->netdev, "%s: Unknown trap id %d\n", __func__, trap_id);
		वापस -EINVAL;
	पूर्ण
	अगर (priv->en_trap && !mlx5_devlink_trap_get_num_active(priv->mdev))
		mlx5e_del_trap_queue(priv);

	वापस 0;
पूर्ण

पूर्णांक mlx5e_handle_trap_event(काष्ठा mlx5e_priv *priv, काष्ठा mlx5_trap_ctx *trap_ctx)
अणु
	पूर्णांक err = 0;

	/* Traps are unarmed when पूर्णांकerface is करोwn, no need to update
	 * them. The configuration is saved in the core driver,
	 * queried and applied upon पूर्णांकerface up operation in
	 * mlx5e_खोलो_locked().
	 */
	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		वापस 0;

	चयन (trap_ctx->action) अणु
	हाल DEVLINK_TRAP_ACTION_TRAP:
		err = mlx5e_handle_action_trap(priv, trap_ctx->id);
		अवरोध;
	हाल DEVLINK_TRAP_ACTION_DROP:
		err = mlx5e_handle_action_drop(priv, trap_ctx->id);
		अवरोध;
	शेष:
		netdev_warn(priv->netdev, "%s: Unsupported action %d\n", __func__,
			    trap_ctx->action);
		err = -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_apply_trap(काष्ठा mlx5e_priv *priv, पूर्णांक trap_id, bool enable)
अणु
	क्रमागत devlink_trap_action action;
	पूर्णांक err;

	err = mlx5_devlink_traps_get_action(priv->mdev, trap_id, &action);
	अगर (err)
		वापस err;
	अगर (action == DEVLINK_TRAP_ACTION_TRAP)
		err = enable ? mlx5e_handle_action_trap(priv, trap_id) :
			       mlx5e_handle_action_drop(priv, trap_id);
	वापस err;
पूर्ण

अटल स्थिर पूर्णांक mlx5e_traps_arr[] = अणु
	DEVLINK_TRAP_GENERIC_ID_INGRESS_VLAN_FILTER,
	DEVLINK_TRAP_GENERIC_ID_DMAC_FILTER,
पूर्ण;

पूर्णांक mlx5e_apply_traps(काष्ठा mlx5e_priv *priv, bool enable)
अणु
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mlx5e_traps_arr); i++) अणु
		err = mlx5e_apply_trap(priv, mlx5e_traps_arr[i], enable);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण
