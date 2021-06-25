<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019-2020, Mellanox Technologies inc. All rights reserved. */

#समावेश <net/xdp_sock_drv.h>
#समावेश "pool.h"
#समावेश "setup.h"
#समावेश "en/params.h"

अटल पूर्णांक mlx5e_xsk_map_pool(काष्ठा mlx5e_priv *priv,
			      काष्ठा xsk_buff_pool *pool)
अणु
	काष्ठा device *dev = mlx5_core_dma_dev(priv->mdev);

	वापस xsk_pool_dma_map(pool, dev, 0);
पूर्ण

अटल व्योम mlx5e_xsk_unmap_pool(काष्ठा mlx5e_priv *priv,
				 काष्ठा xsk_buff_pool *pool)
अणु
	वापस xsk_pool_dma_unmap(pool, 0);
पूर्ण

अटल पूर्णांक mlx5e_xsk_get_pools(काष्ठा mlx5e_xsk *xsk)
अणु
	अगर (!xsk->pools) अणु
		xsk->pools = kसुस्मृति(MLX5E_MAX_NUM_CHANNELS,
				     माप(*xsk->pools), GFP_KERNEL);
		अगर (unlikely(!xsk->pools))
			वापस -ENOMEM;
	पूर्ण

	xsk->refcnt++;
	xsk->ever_used = true;

	वापस 0;
पूर्ण

अटल व्योम mlx5e_xsk_put_pools(काष्ठा mlx5e_xsk *xsk)
अणु
	अगर (!--xsk->refcnt) अणु
		kमुक्त(xsk->pools);
		xsk->pools = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_xsk_add_pool(काष्ठा mlx5e_xsk *xsk, काष्ठा xsk_buff_pool *pool, u16 ix)
अणु
	पूर्णांक err;

	err = mlx5e_xsk_get_pools(xsk);
	अगर (unlikely(err))
		वापस err;

	xsk->pools[ix] = pool;
	वापस 0;
पूर्ण

अटल व्योम mlx5e_xsk_हटाओ_pool(काष्ठा mlx5e_xsk *xsk, u16 ix)
अणु
	xsk->pools[ix] = शून्य;

	mlx5e_xsk_put_pools(xsk);
पूर्ण

अटल bool mlx5e_xsk_is_pool_sane(काष्ठा xsk_buff_pool *pool)
अणु
	वापस xsk_pool_get_headroom(pool) <= 0xffff &&
		xsk_pool_get_chunk_size(pool) <= 0xffff;
पूर्ण

व्योम mlx5e_build_xsk_param(काष्ठा xsk_buff_pool *pool, काष्ठा mlx5e_xsk_param *xsk)
अणु
	xsk->headroom = xsk_pool_get_headroom(pool);
	xsk->chunk_size = xsk_pool_get_chunk_size(pool);
पूर्ण

अटल पूर्णांक mlx5e_xsk_enable_locked(काष्ठा mlx5e_priv *priv,
				   काष्ठा xsk_buff_pool *pool, u16 ix)
अणु
	काष्ठा mlx5e_params *params = &priv->channels.params;
	काष्ठा mlx5e_xsk_param xsk;
	काष्ठा mlx5e_channel *c;
	पूर्णांक err;

	अगर (unlikely(mlx5e_xsk_get_pool(&priv->channels.params, &priv->xsk, ix)))
		वापस -EBUSY;

	अगर (unlikely(!mlx5e_xsk_is_pool_sane(pool)))
		वापस -EINVAL;

	err = mlx5e_xsk_map_pool(priv, pool);
	अगर (unlikely(err))
		वापस err;

	err = mlx5e_xsk_add_pool(&priv->xsk, pool, ix);
	अगर (unlikely(err))
		जाओ err_unmap_pool;

	mlx5e_build_xsk_param(pool, &xsk);

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state)) अणु
		/* XSK objects will be created on खोलो. */
		जाओ validate_बंदd;
	पूर्ण

	अगर (!params->xdp_prog) अणु
		/* XSK objects will be created when an XDP program is set,
		 * and the channels are reखोलोed.
		 */
		जाओ validate_बंदd;
	पूर्ण

	c = priv->channels.c[ix];

	err = mlx5e_खोलो_xsk(priv, params, &xsk, pool, c);
	अगर (unlikely(err))
		जाओ err_हटाओ_pool;

	mlx5e_activate_xsk(c);

	/* Don't wait for WQEs, because the newer xdpsock sample doesn't provide
	 * any Fill Ring entries at the setup stage.
	 */

	err = mlx5e_xsk_redirect_rqt_to_channel(priv, priv->channels.c[ix]);
	अगर (unlikely(err))
		जाओ err_deactivate;

	वापस 0;

err_deactivate:
	mlx5e_deactivate_xsk(c);
	mlx5e_बंद_xsk(c);

err_हटाओ_pool:
	mlx5e_xsk_हटाओ_pool(&priv->xsk, ix);

err_unmap_pool:
	mlx5e_xsk_unmap_pool(priv, pool);

	वापस err;

validate_बंदd:
	/* Check the configuration in advance, rather than fail at a later stage
	 * (in mlx5e_xdp_set or on खोलो) and end up with no channels.
	 */
	अगर (!mlx5e_validate_xsk_param(params, &xsk, priv->mdev)) अणु
		err = -EINVAL;
		जाओ err_हटाओ_pool;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_xsk_disable_locked(काष्ठा mlx5e_priv *priv, u16 ix)
अणु
	काष्ठा xsk_buff_pool *pool = mlx5e_xsk_get_pool(&priv->channels.params,
						   &priv->xsk, ix);
	काष्ठा mlx5e_channel *c;

	अगर (unlikely(!pool))
		वापस -EINVAL;

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		जाओ हटाओ_pool;

	/* XSK RQ and SQ are only created अगर XDP program is set. */
	अगर (!priv->channels.params.xdp_prog)
		जाओ हटाओ_pool;

	c = priv->channels.c[ix];
	mlx5e_xsk_redirect_rqt_to_drop(priv, ix);
	mlx5e_deactivate_xsk(c);
	mlx5e_बंद_xsk(c);

हटाओ_pool:
	mlx5e_xsk_हटाओ_pool(&priv->xsk, ix);
	mlx5e_xsk_unmap_pool(priv, pool);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_xsk_enable_pool(काष्ठा mlx5e_priv *priv, काष्ठा xsk_buff_pool *pool,
				 u16 ix)
अणु
	पूर्णांक err;

	mutex_lock(&priv->state_lock);
	err = mlx5e_xsk_enable_locked(priv, pool, ix);
	mutex_unlock(&priv->state_lock);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_xsk_disable_pool(काष्ठा mlx5e_priv *priv, u16 ix)
अणु
	पूर्णांक err;

	mutex_lock(&priv->state_lock);
	err = mlx5e_xsk_disable_locked(priv, ix);
	mutex_unlock(&priv->state_lock);

	वापस err;
पूर्ण

पूर्णांक mlx5e_xsk_setup_pool(काष्ठा net_device *dev, काष्ठा xsk_buff_pool *pool, u16 qid)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5e_params *params = &priv->channels.params;
	u16 ix;

	अगर (unlikely(!mlx5e_qid_get_ch_अगर_in_group(params, qid, MLX5E_RQ_GROUP_XSK, &ix)))
		वापस -EINVAL;

	वापस pool ? mlx5e_xsk_enable_pool(priv, pool, ix) :
		      mlx5e_xsk_disable_pool(priv, ix);
पूर्ण
