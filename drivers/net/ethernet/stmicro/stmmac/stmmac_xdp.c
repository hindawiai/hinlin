<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2021, Intel Corporation. */

#समावेश <net/xdp_sock_drv.h>

#समावेश "stmmac.h"
#समावेश "stmmac_xdp.h"

अटल पूर्णांक sपंचांगmac_xdp_enable_pool(काष्ठा sपंचांगmac_priv *priv,
				  काष्ठा xsk_buff_pool *pool, u16 queue)
अणु
	काष्ठा sपंचांगmac_channel *ch = &priv->channel[queue];
	bool need_update;
	u32 frame_size;
	पूर्णांक err;

	अगर (queue >= priv->plat->rx_queues_to_use ||
	    queue >= priv->plat->tx_queues_to_use)
		वापस -EINVAL;

	frame_size = xsk_pool_get_rx_frame_size(pool);
	/* XDP ZC करोes not span multiple frame, make sure XSK pool buffer
	 * size can at least store Q-in-Q frame.
	 */
	अगर (frame_size < ETH_FRAME_LEN + VLAN_HLEN * 2)
		वापस -EOPNOTSUPP;

	err = xsk_pool_dma_map(pool, priv->device, STMMAC_RX_DMA_ATTR);
	अगर (err) अणु
		netdev_err(priv->dev, "Failed to map xsk pool\n");
		वापस err;
	पूर्ण

	need_update = netअगर_running(priv->dev) && sपंचांगmac_xdp_is_enabled(priv);

	अगर (need_update) अणु
		sपंचांगmac_disable_rx_queue(priv, queue);
		sपंचांगmac_disable_tx_queue(priv, queue);
		napi_disable(&ch->rx_napi);
		napi_disable(&ch->tx_napi);
	पूर्ण

	set_bit(queue, priv->af_xdp_zc_qps);

	अगर (need_update) अणु
		napi_enable(&ch->rxtx_napi);
		sपंचांगmac_enable_rx_queue(priv, queue);
		sपंचांगmac_enable_tx_queue(priv, queue);

		err = sपंचांगmac_xsk_wakeup(priv->dev, queue, XDP_WAKEUP_RX);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_xdp_disable_pool(काष्ठा sपंचांगmac_priv *priv, u16 queue)
अणु
	काष्ठा sपंचांगmac_channel *ch = &priv->channel[queue];
	काष्ठा xsk_buff_pool *pool;
	bool need_update;

	अगर (queue >= priv->plat->rx_queues_to_use ||
	    queue >= priv->plat->tx_queues_to_use)
		वापस -EINVAL;

	pool = xsk_get_pool_from_qid(priv->dev, queue);
	अगर (!pool)
		वापस -EINVAL;

	need_update = netअगर_running(priv->dev) && sपंचांगmac_xdp_is_enabled(priv);

	अगर (need_update) अणु
		sपंचांगmac_disable_rx_queue(priv, queue);
		sपंचांगmac_disable_tx_queue(priv, queue);
		synchronize_rcu();
		napi_disable(&ch->rxtx_napi);
	पूर्ण

	xsk_pool_dma_unmap(pool, STMMAC_RX_DMA_ATTR);

	clear_bit(queue, priv->af_xdp_zc_qps);

	अगर (need_update) अणु
		napi_enable(&ch->rx_napi);
		napi_enable(&ch->tx_napi);
		sपंचांगmac_enable_rx_queue(priv, queue);
		sपंचांगmac_enable_tx_queue(priv, queue);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sपंचांगmac_xdp_setup_pool(काष्ठा sपंचांगmac_priv *priv, काष्ठा xsk_buff_pool *pool,
			  u16 queue)
अणु
	वापस pool ? sपंचांगmac_xdp_enable_pool(priv, pool, queue) :
		      sपंचांगmac_xdp_disable_pool(priv, queue);
पूर्ण

पूर्णांक sपंचांगmac_xdp_set_prog(काष्ठा sपंचांगmac_priv *priv, काष्ठा bpf_prog *prog,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = priv->dev;
	काष्ठा bpf_prog *old_prog;
	bool need_update;
	bool अगर_running;

	अगर_running = netअगर_running(dev);

	अगर (prog && dev->mtu > ETH_DATA_LEN) अणु
		/* For now, the driver करोesn't support XDP functionality with
		 * jumbo frames so we वापस error.
		 */
		NL_SET_ERR_MSG_MOD(extack, "Jumbo frames not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	need_update = !!priv->xdp_prog != !!prog;
	अगर (अगर_running && need_update)
		sपंचांगmac_release(dev);

	old_prog = xchg(&priv->xdp_prog, prog);
	अगर (old_prog)
		bpf_prog_put(old_prog);

	/* Disable RX SPH क्रम XDP operation */
	priv->sph = priv->sph_cap && !sपंचांगmac_xdp_is_enabled(priv);

	अगर (अगर_running && need_update)
		sपंचांगmac_खोलो(dev);

	वापस 0;
पूर्ण
