<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2018 Mellanox Technologies

#समावेश "en.h"
#समावेश "en/hv_vhca_stats.h"
#समावेश "lib/hv_vhca.h"
#समावेश "lib/hv.h"

काष्ठा mlx5e_hv_vhca_per_ring_stats अणु
	u64     rx_packets;
	u64     rx_bytes;
	u64     tx_packets;
	u64     tx_bytes;
पूर्ण;

अटल व्योम
mlx5e_hv_vhca_fill_ring_stats(काष्ठा mlx5e_priv *priv, पूर्णांक ch,
			      काष्ठा mlx5e_hv_vhca_per_ring_stats *data)
अणु
	काष्ठा mlx5e_channel_stats *stats;
	पूर्णांक tc;

	stats = &priv->channel_stats[ch];
	data->rx_packets = stats->rq.packets;
	data->rx_bytes   = stats->rq.bytes;

	क्रम (tc = 0; tc < priv->max_खोलोed_tc; tc++) अणु
		data->tx_packets += stats->sq[tc].packets;
		data->tx_bytes   += stats->sq[tc].bytes;
	पूर्ण
पूर्ण

अटल व्योम mlx5e_hv_vhca_fill_stats(काष्ठा mlx5e_priv *priv, व्योम *data,
				     पूर्णांक buf_len)
अणु
	पूर्णांक ch, i = 0;

	क्रम (ch = 0; ch < priv->max_nch; ch++) अणु
		व्योम *buf = data + i;

		अगर (WARN_ON_ONCE(buf +
				 माप(काष्ठा mlx5e_hv_vhca_per_ring_stats) >
				 data + buf_len))
			वापस;

		mlx5e_hv_vhca_fill_ring_stats(priv, ch, buf);
		i += माप(काष्ठा mlx5e_hv_vhca_per_ring_stats);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_hv_vhca_stats_buf_size(काष्ठा mlx5e_priv *priv)
अणु
	वापस (माप(काष्ठा mlx5e_hv_vhca_per_ring_stats) *
		priv->max_nch);
पूर्ण

अटल व्योम mlx5e_hv_vhca_stats_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5e_hv_vhca_stats_agent *sagent;
	काष्ठा mlx5_hv_vhca_agent *agent;
	काष्ठा delayed_work *dwork;
	काष्ठा mlx5e_priv *priv;
	पूर्णांक buf_len, rc;
	व्योम *buf;

	dwork = to_delayed_work(work);
	sagent = container_of(dwork, काष्ठा mlx5e_hv_vhca_stats_agent, work);
	priv = container_of(sagent, काष्ठा mlx5e_priv, stats_agent);
	buf_len = mlx5e_hv_vhca_stats_buf_size(priv);
	agent = sagent->agent;
	buf = sagent->buf;

	स_रखो(buf, 0, buf_len);
	mlx5e_hv_vhca_fill_stats(priv, buf, buf_len);

	rc = mlx5_hv_vhca_agent_ग_लिखो(agent, buf, buf_len);
	अगर (rc) अणु
		mlx5_core_err(priv->mdev,
			      "%s: Failed to write stats, err = %d\n",
			      __func__, rc);
		वापस;
	पूर्ण

	अगर (sagent->delay)
		queue_delayed_work(priv->wq, &sagent->work, sagent->delay);
पूर्ण

क्रमागत अणु
	MLX5_HV_VHCA_STATS_VERSION     = 1,
	MLX5_HV_VHCA_STATS_UPDATE_ONCE = 0xFFFF,
पूर्ण;

अटल व्योम mlx5e_hv_vhca_stats_control(काष्ठा mlx5_hv_vhca_agent *agent,
					काष्ठा mlx5_hv_vhca_control_block *block)
अणु
	काष्ठा mlx5e_hv_vhca_stats_agent *sagent;
	काष्ठा mlx5e_priv *priv;

	priv = mlx5_hv_vhca_agent_priv(agent);
	sagent = &priv->stats_agent;

	block->version = MLX5_HV_VHCA_STATS_VERSION;
	block->rings   = priv->max_nch;

	अगर (!block->command) अणु
		cancel_delayed_work_sync(&priv->stats_agent.work);
		वापस;
	पूर्ण

	sagent->delay = block->command == MLX5_HV_VHCA_STATS_UPDATE_ONCE ? 0 :
			msecs_to_jअगरfies(block->command * 100);

	queue_delayed_work(priv->wq, &sagent->work, sagent->delay);
पूर्ण

अटल व्योम mlx5e_hv_vhca_stats_cleanup(काष्ठा mlx5_hv_vhca_agent *agent)
अणु
	काष्ठा mlx5e_priv *priv = mlx5_hv_vhca_agent_priv(agent);

	cancel_delayed_work_sync(&priv->stats_agent.work);
पूर्ण

पूर्णांक mlx5e_hv_vhca_stats_create(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक buf_len = mlx5e_hv_vhca_stats_buf_size(priv);
	काष्ठा mlx5_hv_vhca_agent *agent;

	priv->stats_agent.buf = kvzalloc(buf_len, GFP_KERNEL);
	अगर (!priv->stats_agent.buf)
		वापस -ENOMEM;

	agent = mlx5_hv_vhca_agent_create(priv->mdev->hv_vhca,
					  MLX5_HV_VHCA_AGENT_STATS,
					  mlx5e_hv_vhca_stats_control, शून्य,
					  mlx5e_hv_vhca_stats_cleanup,
					  priv);

	अगर (IS_ERR_OR_शून्य(agent)) अणु
		अगर (IS_ERR(agent))
			netdev_warn(priv->netdev,
				    "Failed to create hv vhca stats agent, err = %ld\n",
				    PTR_ERR(agent));

		kvमुक्त(priv->stats_agent.buf);
		वापस IS_ERR_OR_शून्य(agent);
	पूर्ण

	priv->stats_agent.agent = agent;
	INIT_DELAYED_WORK(&priv->stats_agent.work, mlx5e_hv_vhca_stats_work);

	वापस 0;
पूर्ण

व्योम mlx5e_hv_vhca_stats_destroy(काष्ठा mlx5e_priv *priv)
अणु
	अगर (IS_ERR_OR_शून्य(priv->stats_agent.agent))
		वापस;

	mlx5_hv_vhca_agent_destroy(priv->stats_agent.agent);
	kvमुक्त(priv->stats_agent.buf);
पूर्ण
