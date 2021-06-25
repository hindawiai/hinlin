<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/mlx5/fs.h>
#समावेश <net/चयनdev.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/act_api.h>
#समावेश <net/devlink.h>
#समावेश <net/ipv6_stubs.h>

#समावेश "eswitch.h"
#समावेश "en.h"
#समावेश "en_rep.h"
#समावेश "en/params.h"
#समावेश "en/txrx.h"
#समावेश "en_tc.h"
#समावेश "en/rep/tc.h"
#समावेश "en/rep/neigh.h"
#समावेश "en/devlink.h"
#समावेश "fs_core.h"
#समावेश "lib/mlx5.h"
#घोषणा CREATE_TRACE_POINTS
#समावेश "diag/en_rep_tracepoint.h"

#घोषणा MLX5E_REP_PARAMS_DEF_LOG_SQ_SIZE \
	max(0x7, MLX5E_PARAMS_MINIMUM_LOG_SQ_SIZE)
#घोषणा MLX5E_REP_PARAMS_DEF_NUM_CHANNELS 1

अटल स्थिर अक्षर mlx5e_rep_driver_name[] = "mlx5e_rep";

अटल व्योम mlx5e_rep_get_drvinfo(काष्ठा net_device *dev,
				  काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	strlcpy(drvinfo->driver, mlx5e_rep_driver_name,
		माप(drvinfo->driver));
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "%d.%d.%04d (%.16s)",
		 fw_rev_maj(mdev), fw_rev_min(mdev),
		 fw_rev_sub(mdev), mdev->board_id);
पूर्ण

अटल स्थिर काष्ठा counter_desc sw_rep_stats_desc[] = अणु
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, rx_bytes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा mlx5e_sw_stats, tx_bytes) पूर्ण,
पूर्ण;

काष्ठा vport_stats अणु
	u64 vport_rx_packets;
	u64 vport_tx_packets;
	u64 vport_rx_bytes;
	u64 vport_tx_bytes;
पूर्ण;

अटल स्थिर काष्ठा counter_desc vport_rep_stats_desc[] = अणु
	अणु MLX5E_DECLARE_STAT(काष्ठा vport_stats, vport_rx_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा vport_stats, vport_rx_bytes) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा vport_stats, vport_tx_packets) पूर्ण,
	अणु MLX5E_DECLARE_STAT(काष्ठा vport_stats, vport_tx_bytes) पूर्ण,
पूर्ण;

#घोषणा NUM_VPORT_REP_SW_COUNTERS ARRAY_SIZE(sw_rep_stats_desc)
#घोषणा NUM_VPORT_REP_HW_COUNTERS ARRAY_SIZE(vport_rep_stats_desc)

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(sw_rep)
अणु
	वापस NUM_VPORT_REP_SW_COUNTERS;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(sw_rep)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_VPORT_REP_SW_COUNTERS; i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN,
		       sw_rep_stats_desc[i].क्रमmat);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(sw_rep)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_VPORT_REP_SW_COUNTERS; i++)
		data[idx++] = MLX5E_READ_CTR64_CPU(&priv->stats.sw,
						   sw_rep_stats_desc, i);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(sw_rep)
अणु
	काष्ठा mlx5e_sw_stats *s = &priv->stats.sw;
	काष्ठा rtnl_link_stats64 stats64 = अणुपूर्ण;

	स_रखो(s, 0, माप(*s));
	mlx5e_fold_sw_stats64(priv, &stats64);

	s->rx_packets = stats64.rx_packets;
	s->rx_bytes   = stats64.rx_bytes;
	s->tx_packets = stats64.tx_packets;
	s->tx_bytes   = stats64.tx_bytes;
	s->tx_queue_dropped = stats64.tx_dropped;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(vport_rep)
अणु
	वापस NUM_VPORT_REP_HW_COUNTERS;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(vport_rep)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_VPORT_REP_HW_COUNTERS; i++)
		म_नकल(data + (idx++) * ETH_GSTRING_LEN, vport_rep_stats_desc[i].क्रमmat);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(vport_rep)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_VPORT_REP_HW_COUNTERS; i++)
		data[idx++] = MLX5E_READ_CTR64_CPU(&priv->stats.vf_vport,
						   vport_rep_stats_desc, i);
	वापस idx;
पूर्ण

अटल MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(vport_rep)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep = rpriv->rep;
	काष्ठा rtnl_link_stats64 *vport_stats;
	काष्ठा अगरla_vf_stats vf_stats;
	पूर्णांक err;

	err = mlx5_eचयन_get_vport_stats(esw, rep->vport, &vf_stats);
	अगर (err) अणु
		netdev_warn(priv->netdev, "vport %d error %d reading stats\n",
			    rep->vport, err);
		वापस;
	पूर्ण

	vport_stats = &priv->stats.vf_vport;
	/* flip tx/rx as we are reporting the counters क्रम the चयन vport */
	vport_stats->rx_packets = vf_stats.tx_packets;
	vport_stats->rx_bytes   = vf_stats.tx_bytes;
	vport_stats->tx_packets = vf_stats.rx_packets;
	vport_stats->tx_bytes   = vf_stats.rx_bytes;
पूर्ण

अटल व्योम mlx5e_rep_get_strings(काष्ठा net_device *dev,
				  u32 stringset, uपूर्णांक8_t *data)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		mlx5e_stats_fill_strings(priv, data);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mlx5e_rep_get_ethtool_stats(काष्ठा net_device *dev,
					काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	mlx5e_ethtool_get_ethtool_stats(priv, stats, data);
पूर्ण

अटल पूर्णांक mlx5e_rep_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस mlx5e_stats_total_num(priv);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम mlx5e_rep_get_ringparam(काष्ठा net_device *dev,
				काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	mlx5e_ethtool_get_ringparam(priv, param);
पूर्ण

अटल पूर्णांक mlx5e_rep_set_ringparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	वापस mlx5e_ethtool_set_ringparam(priv, param);
पूर्ण

अटल व्योम mlx5e_rep_get_channels(काष्ठा net_device *dev,
				   काष्ठा ethtool_channels *ch)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	mlx5e_ethtool_get_channels(priv, ch);
पूर्ण

अटल पूर्णांक mlx5e_rep_set_channels(काष्ठा net_device *dev,
				  काष्ठा ethtool_channels *ch)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	वापस mlx5e_ethtool_set_channels(priv, ch);
पूर्ण

अटल पूर्णांक mlx5e_rep_get_coalesce(काष्ठा net_device *netdev,
				  काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	वापस mlx5e_ethtool_get_coalesce(priv, coal);
पूर्ण

अटल पूर्णांक mlx5e_rep_set_coalesce(काष्ठा net_device *netdev,
				  काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	वापस mlx5e_ethtool_set_coalesce(priv, coal);
पूर्ण

अटल u32 mlx5e_rep_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	वापस mlx5e_ethtool_get_rxfh_key_size(priv);
पूर्ण

अटल u32 mlx5e_rep_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	वापस mlx5e_ethtool_get_rxfh_indir_size(priv);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops mlx5e_rep_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_USE_ADAPTIVE,
	.get_drvinfo	   = mlx5e_rep_get_drvinfo,
	.get_link	   = ethtool_op_get_link,
	.get_strings       = mlx5e_rep_get_strings,
	.get_sset_count    = mlx5e_rep_get_sset_count,
	.get_ethtool_stats = mlx5e_rep_get_ethtool_stats,
	.get_ringparam     = mlx5e_rep_get_ringparam,
	.set_ringparam     = mlx5e_rep_set_ringparam,
	.get_channels      = mlx5e_rep_get_channels,
	.set_channels      = mlx5e_rep_set_channels,
	.get_coalesce      = mlx5e_rep_get_coalesce,
	.set_coalesce      = mlx5e_rep_set_coalesce,
	.get_rxfh_key_size   = mlx5e_rep_get_rxfh_key_size,
	.get_rxfh_indir_size = mlx5e_rep_get_rxfh_indir_size,
पूर्ण;

अटल व्योम mlx5e_sqs2vport_stop(काष्ठा mlx5_eचयन *esw,
				 काष्ठा mlx5_eचयन_rep *rep)
अणु
	काष्ठा mlx5e_rep_sq *rep_sq, *पंचांगp;
	काष्ठा mlx5e_rep_priv *rpriv;

	अगर (esw->mode != MLX5_ESWITCH_OFFLOADS)
		वापस;

	rpriv = mlx5e_rep_to_rep_priv(rep);
	list_क्रम_each_entry_safe(rep_sq, पंचांगp, &rpriv->vport_sqs_list, list) अणु
		mlx5_eचयन_del_send_to_vport_rule(rep_sq->send_to_vport_rule);
		list_del(&rep_sq->list);
		kमुक्त(rep_sq);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_sqs2vport_start(काष्ठा mlx5_eचयन *esw,
				 काष्ठा mlx5_eचयन_rep *rep,
				 u32 *sqns_array, पूर्णांक sqns_num)
अणु
	काष्ठा mlx5_flow_handle *flow_rule;
	काष्ठा mlx5e_rep_priv *rpriv;
	काष्ठा mlx5e_rep_sq *rep_sq;
	पूर्णांक err;
	पूर्णांक i;

	अगर (esw->mode != MLX5_ESWITCH_OFFLOADS)
		वापस 0;

	rpriv = mlx5e_rep_to_rep_priv(rep);
	क्रम (i = 0; i < sqns_num; i++) अणु
		rep_sq = kzalloc(माप(*rep_sq), GFP_KERNEL);
		अगर (!rep_sq) अणु
			err = -ENOMEM;
			जाओ out_err;
		पूर्ण

		/* Add re-inject rule to the PF/representor sqs */
		flow_rule = mlx5_eचयन_add_send_to_vport_rule(esw, rep,
								sqns_array[i]);
		अगर (IS_ERR(flow_rule)) अणु
			err = PTR_ERR(flow_rule);
			kमुक्त(rep_sq);
			जाओ out_err;
		पूर्ण
		rep_sq->send_to_vport_rule = flow_rule;
		list_add(&rep_sq->list, &rpriv->vport_sqs_list);
	पूर्ण
	वापस 0;

out_err:
	mlx5e_sqs2vport_stop(esw, rep);
	वापस err;
पूर्ण

पूर्णांक mlx5e_add_sqs_fwd_rules(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep = rpriv->rep;
	काष्ठा mlx5e_channel *c;
	पूर्णांक n, tc, num_sqs = 0;
	पूर्णांक err = -ENOMEM;
	u32 *sqs;

	sqs = kसुस्मृति(priv->channels.num * priv->channels.params.num_tc, माप(*sqs), GFP_KERNEL);
	अगर (!sqs)
		जाओ out;

	क्रम (n = 0; n < priv->channels.num; n++) अणु
		c = priv->channels.c[n];
		क्रम (tc = 0; tc < c->num_tc; tc++)
			sqs[num_sqs++] = c->sq[tc].sqn;
	पूर्ण

	err = mlx5e_sqs2vport_start(esw, rep, sqs, num_sqs);
	kमुक्त(sqs);

out:
	अगर (err)
		netdev_warn(priv->netdev, "Failed to add SQs FWD rules %d\n", err);
	वापस err;
पूर्ण

व्योम mlx5e_हटाओ_sqs_fwd_rules(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep = rpriv->rep;

	mlx5e_sqs2vport_stop(esw, rep);
पूर्ण

अटल पूर्णांक mlx5e_rep_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep = rpriv->rep;
	पूर्णांक err;

	mutex_lock(&priv->state_lock);
	err = mlx5e_खोलो_locked(dev);
	अगर (err)
		जाओ unlock;

	अगर (!mlx5_modअगरy_vport_admin_state(priv->mdev,
					   MLX5_VPORT_STATE_OP_MOD_ESW_VPORT,
					   rep->vport, 1,
					   MLX5_VPORT_ADMIN_STATE_UP))
		netअगर_carrier_on(dev);

unlock:
	mutex_unlock(&priv->state_lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_rep_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep = rpriv->rep;
	पूर्णांक ret;

	mutex_lock(&priv->state_lock);
	mlx5_modअगरy_vport_admin_state(priv->mdev,
				      MLX5_VPORT_STATE_OP_MOD_ESW_VPORT,
				      rep->vport, 1,
				      MLX5_VPORT_ADMIN_STATE_DOWN);
	ret = mlx5e_बंद_locked(dev);
	mutex_unlock(&priv->state_lock);
	वापस ret;
पूर्ण

bool mlx5e_is_uplink_rep(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep;

	अगर (!MLX5_ESWITCH_MANAGER(priv->mdev))
		वापस false;

	अगर (!rpriv) /* non vport rep mlx5e instances करोn't use this field */
		वापस false;

	rep = rpriv->rep;
	वापस (rep->vport == MLX5_VPORT_UPLINK);
पूर्ण

bool mlx5e_rep_has_offload_stats(स्थिर काष्ठा net_device *dev, पूर्णांक attr_id)
अणु
	चयन (attr_id) अणु
	हाल IFLA_OFFLOAD_XSTATS_CPU_HIT:
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक
mlx5e_get_sw_stats64(स्थिर काष्ठा net_device *dev,
		     काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	mlx5e_fold_sw_stats64(priv, stats);
	वापस 0;
पूर्ण

पूर्णांक mlx5e_rep_get_offload_stats(पूर्णांक attr_id, स्थिर काष्ठा net_device *dev,
				व्योम *sp)
अणु
	चयन (attr_id) अणु
	हाल IFLA_OFFLOAD_XSTATS_CPU_HIT:
		वापस mlx5e_get_sw_stats64(dev, sp);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम
mlx5e_rep_get_stats(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);

	/* update HW stats in background क्रम next समय */
	mlx5e_queue_update_stats(priv);
	स_नकल(stats, &priv->stats.vf_vport, माप(*stats));
पूर्ण

अटल पूर्णांक mlx5e_rep_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	वापस mlx5e_change_mtu(netdev, new_mtu, शून्य);
पूर्ण

अटल काष्ठा devlink_port *mlx5e_rep_get_devlink_port(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_core_dev *dev = priv->mdev;

	वापस mlx5_esw_offloads_devlink_port(dev->priv.eचयन, rpriv->rep->vport);
पूर्ण

अटल पूर्णांक mlx5e_rep_change_carrier(काष्ठा net_device *dev, bool new_carrier)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep = rpriv->rep;
	पूर्णांक err;

	अगर (new_carrier) अणु
		err = mlx5_modअगरy_vport_admin_state(priv->mdev, MLX5_VPORT_STATE_OP_MOD_ESW_VPORT,
						    rep->vport, 1, MLX5_VPORT_ADMIN_STATE_UP);
		अगर (err)
			वापस err;
		netअगर_carrier_on(dev);
	पूर्ण अन्यथा अणु
		err = mlx5_modअगरy_vport_admin_state(priv->mdev, MLX5_VPORT_STATE_OP_MOD_ESW_VPORT,
						    rep->vport, 1, MLX5_VPORT_ADMIN_STATE_DOWN);
		अगर (err)
			वापस err;
		netअगर_carrier_off(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops mlx5e_netdev_ops_rep = अणु
	.nकरो_खोलो                = mlx5e_rep_खोलो,
	.nकरो_stop                = mlx5e_rep_बंद,
	.nकरो_start_xmit          = mlx5e_xmit,
	.nकरो_setup_tc            = mlx5e_rep_setup_tc,
	.nकरो_get_devlink_port    = mlx5e_rep_get_devlink_port,
	.nकरो_get_stats64         = mlx5e_rep_get_stats,
	.nकरो_has_offload_stats	 = mlx5e_rep_has_offload_stats,
	.nकरो_get_offload_stats	 = mlx5e_rep_get_offload_stats,
	.nकरो_change_mtu          = mlx5e_rep_change_mtu,
	.nकरो_change_carrier      = mlx5e_rep_change_carrier,
पूर्ण;

bool mlx5e_eचयन_uplink_rep(काष्ठा net_device *netdev)
अणु
	वापस netdev->netdev_ops == &mlx5e_netdev_ops &&
	       mlx5e_is_uplink_rep(netdev_priv(netdev));
पूर्ण

bool mlx5e_eचयन_vf_rep(काष्ठा net_device *netdev)
अणु
	वापस netdev->netdev_ops == &mlx5e_netdev_ops_rep;
पूर्ण

अटल व्योम mlx5e_build_rep_params(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep = rpriv->rep;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_params *params;

	u8 cq_period_mode = MLX5_CAP_GEN(mdev, cq_period_start_from_cqe) ?
					 MLX5_CQ_PERIOD_MODE_START_FROM_CQE :
					 MLX5_CQ_PERIOD_MODE_START_FROM_EQE;

	priv->max_nch = mlx5e_calc_max_nch(priv, priv->profile);
	params = &priv->channels.params;

	params->num_channels = MLX5E_REP_PARAMS_DEF_NUM_CHANNELS;
	params->hard_mtu    = MLX5E_ETH_HARD_MTU;
	params->sw_mtu      = netdev->mtu;

	/* SQ */
	अगर (rep->vport == MLX5_VPORT_UPLINK)
		params->log_sq_size = MLX5E_PARAMS_DEFAULT_LOG_SQ_SIZE;
	अन्यथा
		params->log_sq_size = MLX5E_REP_PARAMS_DEF_LOG_SQ_SIZE;

	/* RQ */
	mlx5e_build_rq_params(mdev, params);

	/* CQ moderation params */
	params->rx_dim_enabled = MLX5_CAP_GEN(mdev, cq_moderation);
	mlx5e_set_rx_cq_mode_params(params, cq_period_mode);

	params->num_tc                = 1;
	params->tunneled_offload_en = false;

	mlx5_query_min_अंतरभूत(mdev, &params->tx_min_अंतरभूत_mode);

	/* RSS */
	mlx5e_build_rss_params(&priv->rss_params, params->num_channels);
पूर्ण

अटल व्योम mlx5e_build_rep_netdev(काष्ठा net_device *netdev,
				   काष्ठा mlx5_core_dev *mdev)
अणु
	SET_NETDEV_DEV(netdev, mdev->device);
	netdev->netdev_ops = &mlx5e_netdev_ops_rep;
	eth_hw_addr_अक्रमom(netdev);
	netdev->ethtool_ops = &mlx5e_rep_ethtool_ops;

	netdev->watchकरोg_समयo    = 15 * HZ;

#अगर IS_ENABLED(CONFIG_MLX5_CLS_ACT)
	netdev->hw_features    |= NETIF_F_HW_TC;
#पूर्ण_अगर
	netdev->hw_features    |= NETIF_F_SG;
	netdev->hw_features    |= NETIF_F_IP_CSUM;
	netdev->hw_features    |= NETIF_F_IPV6_CSUM;
	netdev->hw_features    |= NETIF_F_GRO;
	netdev->hw_features    |= NETIF_F_TSO;
	netdev->hw_features    |= NETIF_F_TSO6;
	netdev->hw_features    |= NETIF_F_RXCSUM;

	netdev->features |= netdev->hw_features;
	netdev->features |= NETIF_F_VLAN_CHALLENGED;
	netdev->features |= NETIF_F_NETNS_LOCAL;
पूर्ण

अटल पूर्णांक mlx5e_init_rep(काष्ठा mlx5_core_dev *mdev,
			  काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	mlx5e_build_rep_params(netdev);
	mlx5e_बारtamp_init(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_init_ul_rep(काष्ठा mlx5_core_dev *mdev,
			     काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);

	mlx5e_vxlan_set_netdev_info(priv);
	वापस mlx5e_init_rep(mdev, netdev);
पूर्ण

अटल व्योम mlx5e_cleanup_rep(काष्ठा mlx5e_priv *priv)
अणु
पूर्ण

अटल पूर्णांक mlx5e_create_rep_ttc_table(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep = rpriv->rep;
	काष्ठा ttc_params ttc_params = अणुपूर्ण;
	पूर्णांक tt, err;

	priv->fs.ns = mlx5_get_flow_namespace(priv->mdev,
					      MLX5_FLOW_NAMESPACE_KERNEL);

	/* The inner_ttc in the ttc params is पूर्णांकentionally not set */
	ttc_params.any_tt_tirn = priv->direct_tir[0].tirn;
	mlx5e_set_ttc_ft_params(&ttc_params);

	अगर (rep->vport != MLX5_VPORT_UPLINK)
		/* To give uplik rep TTC a lower level क्रम chaining from root ft */
		ttc_params.ft_attr.level = MLX5E_TTC_FT_LEVEL + 1;

	क्रम (tt = 0; tt < MLX5E_NUM_INसूची_TIRS; tt++)
		ttc_params.indir_tirn[tt] = priv->indir_tir[tt].tirn;

	err = mlx5e_create_ttc_table(priv, &ttc_params, &priv->fs.ttc);
	अगर (err) अणु
		netdev_err(priv->netdev, "Failed to create rep ttc table, err=%d\n", err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_create_rep_root_ft(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep = rpriv->rep;
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_flow_namespace *ns;
	पूर्णांक err = 0;

	अगर (rep->vport != MLX5_VPORT_UPLINK) अणु
		/* non uplik reps will skip any bypass tables and go directly to
		 * their own ttc
		 */
		rpriv->root_ft = priv->fs.ttc.ft.t;
		वापस 0;
	पूर्ण

	/* uplink root ft will be used to स्वतः chain, to ethtool or ttc tables */
	ns = mlx5_get_flow_namespace(priv->mdev, MLX5_FLOW_NAMESPACE_OFFLOADS);
	अगर (!ns) अणु
		netdev_err(priv->netdev, "Failed to get reps offloads namespace\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ft_attr.max_fte = 0; /* Empty table, miss rule will always poपूर्णांक to next table */
	ft_attr.prio = 1;
	ft_attr.level = 1;

	rpriv->root_ft = mlx5_create_flow_table(ns, &ft_attr);
	अगर (IS_ERR(rpriv->root_ft)) अणु
		err = PTR_ERR(rpriv->root_ft);
		rpriv->root_ft = शून्य;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम mlx5e_destroy_rep_root_ft(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep = rpriv->rep;

	अगर (rep->vport != MLX5_VPORT_UPLINK)
		वापस;
	mlx5_destroy_flow_table(rpriv->root_ft);
पूर्ण

अटल पूर्णांक mlx5e_create_rep_vport_rx_rule(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_eचयन_rep *rep = rpriv->rep;
	काष्ठा mlx5_flow_handle *flow_rule;
	काष्ठा mlx5_flow_destination dest;

	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft = rpriv->root_ft;

	flow_rule = mlx5_eचयन_create_vport_rx_rule(esw, rep->vport, &dest);
	अगर (IS_ERR(flow_rule))
		वापस PTR_ERR(flow_rule);
	rpriv->vport_rx_rule = flow_rule;
	वापस 0;
पूर्ण

अटल व्योम rep_vport_rx_rule_destroy(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;

	अगर (!rpriv->vport_rx_rule)
		वापस;

	mlx5_del_flow_rules(rpriv->vport_rx_rule);
	rpriv->vport_rx_rule = शून्य;
पूर्ण

पूर्णांक mlx5e_rep_bond_update(काष्ठा mlx5e_priv *priv, bool cleanup)
अणु
	rep_vport_rx_rule_destroy(priv);

	वापस cleanup ? 0 : mlx5e_create_rep_vport_rx_rule(priv);
पूर्ण

अटल पूर्णांक mlx5e_init_rep_rx(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u16 max_nch = priv->max_nch;
	पूर्णांक err;

	mlx5e_init_l2_addr(priv);

	err = mlx5e_खोलो_drop_rq(priv, &priv->drop_rq);
	अगर (err) अणु
		mlx5_core_err(mdev, "open drop rq failed, %d\n", err);
		वापस err;
	पूर्ण

	err = mlx5e_create_indirect_rqt(priv);
	अगर (err)
		जाओ err_बंद_drop_rq;

	err = mlx5e_create_direct_rqts(priv, priv->direct_tir, max_nch);
	अगर (err)
		जाओ err_destroy_indirect_rqts;

	err = mlx5e_create_indirect_tirs(priv, false);
	अगर (err)
		जाओ err_destroy_direct_rqts;

	err = mlx5e_create_direct_tirs(priv, priv->direct_tir, max_nch);
	अगर (err)
		जाओ err_destroy_indirect_tirs;

	err = mlx5e_create_rep_ttc_table(priv);
	अगर (err)
		जाओ err_destroy_direct_tirs;

	err = mlx5e_create_rep_root_ft(priv);
	अगर (err)
		जाओ err_destroy_ttc_table;

	err = mlx5e_create_rep_vport_rx_rule(priv);
	अगर (err)
		जाओ err_destroy_root_ft;

	mlx5e_ethtool_init_steering(priv);

	वापस 0;

err_destroy_root_ft:
	mlx5e_destroy_rep_root_ft(priv);
err_destroy_ttc_table:
	mlx5e_destroy_ttc_table(priv, &priv->fs.ttc);
err_destroy_direct_tirs:
	mlx5e_destroy_direct_tirs(priv, priv->direct_tir, max_nch);
err_destroy_indirect_tirs:
	mlx5e_destroy_indirect_tirs(priv);
err_destroy_direct_rqts:
	mlx5e_destroy_direct_rqts(priv, priv->direct_tir, max_nch);
err_destroy_indirect_rqts:
	mlx5e_destroy_rqt(priv, &priv->indir_rqt);
err_बंद_drop_rq:
	mlx5e_बंद_drop_rq(&priv->drop_rq);
	वापस err;
पूर्ण

अटल व्योम mlx5e_cleanup_rep_rx(काष्ठा mlx5e_priv *priv)
अणु
	u16 max_nch = priv->max_nch;

	mlx5e_ethtool_cleanup_steering(priv);
	rep_vport_rx_rule_destroy(priv);
	mlx5e_destroy_rep_root_ft(priv);
	mlx5e_destroy_ttc_table(priv, &priv->fs.ttc);
	mlx5e_destroy_direct_tirs(priv, priv->direct_tir, max_nch);
	mlx5e_destroy_indirect_tirs(priv);
	mlx5e_destroy_direct_rqts(priv, priv->direct_tir, max_nch);
	mlx5e_destroy_rqt(priv, &priv->indir_rqt);
	mlx5e_बंद_drop_rq(&priv->drop_rq);
पूर्ण

अटल पूर्णांक mlx5e_init_ul_rep_rx(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_create_q_counters(priv);
	वापस mlx5e_init_rep_rx(priv);
पूर्ण

अटल व्योम mlx5e_cleanup_ul_rep_rx(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_cleanup_rep_rx(priv);
	mlx5e_destroy_q_counters(priv);
पूर्ण

अटल पूर्णांक mlx5e_init_uplink_rep_tx(काष्ठा mlx5e_rep_priv *rpriv)
अणु
	काष्ठा mlx5_rep_uplink_priv *uplink_priv;
	काष्ठा net_device *netdev;
	काष्ठा mlx5e_priv *priv;
	पूर्णांक err;

	netdev = rpriv->netdev;
	priv = netdev_priv(netdev);
	uplink_priv = &rpriv->uplink_priv;

	err = mlx5e_rep_tc_init(rpriv);
	अगर (err)
		वापस err;

	mlx5_init_port_tun_entropy(&uplink_priv->tun_entropy, priv->mdev);

	mlx5e_rep_bond_init(rpriv);
	err = mlx5e_rep_tc_netdevice_event_रेजिस्टर(rpriv);
	अगर (err) अणु
		mlx5_core_err(priv->mdev, "Failed to register netdev notifier, err: %d\n",
			      err);
		जाओ err_event_reg;
	पूर्ण

	वापस 0;

err_event_reg:
	mlx5e_rep_bond_cleanup(rpriv);
	mlx5e_rep_tc_cleanup(rpriv);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_init_rep_tx(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	पूर्णांक err;

	err = mlx5e_create_tises(priv);
	अगर (err) अणु
		mlx5_core_warn(priv->mdev, "create tises failed, %d\n", err);
		वापस err;
	पूर्ण

	अगर (rpriv->rep->vport == MLX5_VPORT_UPLINK) अणु
		err = mlx5e_init_uplink_rep_tx(rpriv);
		अगर (err)
			जाओ destroy_tises;
	पूर्ण

	वापस 0;

destroy_tises:
	mlx5e_destroy_tises(priv);
	वापस err;
पूर्ण

अटल व्योम mlx5e_cleanup_uplink_rep_tx(काष्ठा mlx5e_rep_priv *rpriv)
अणु
	mlx5e_rep_tc_netdevice_event_unरेजिस्टर(rpriv);
	mlx5e_rep_bond_cleanup(rpriv);
	mlx5e_rep_tc_cleanup(rpriv);
पूर्ण

अटल व्योम mlx5e_cleanup_rep_tx(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;

	mlx5e_destroy_tises(priv);

	अगर (rpriv->rep->vport == MLX5_VPORT_UPLINK)
		mlx5e_cleanup_uplink_rep_tx(rpriv);
पूर्ण

अटल व्योम mlx5e_rep_enable(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;

	mlx5e_set_netdev_mtu_boundaries(priv);
	mlx5e_rep_neigh_init(rpriv);
पूर्ण

अटल व्योम mlx5e_rep_disable(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;

	mlx5e_rep_neigh_cleanup(rpriv);
पूर्ण

अटल पूर्णांक mlx5e_update_rep_rx(काष्ठा mlx5e_priv *priv)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक uplink_rep_async_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा mlx5e_priv *priv = container_of(nb, काष्ठा mlx5e_priv, events_nb);

	अगर (event == MLX5_EVENT_TYPE_PORT_CHANGE) अणु
		काष्ठा mlx5_eqe *eqe = data;

		चयन (eqe->sub_type) अणु
		हाल MLX5_PORT_CHANGE_SUBTYPE_DOWN:
		हाल MLX5_PORT_CHANGE_SUBTYPE_ACTIVE:
			queue_work(priv->wq, &priv->update_carrier_work);
			अवरोध;
		शेष:
			वापस NOTIFY_DONE;
		पूर्ण

		वापस NOTIFY_OK;
	पूर्ण

	अगर (event == MLX5_DEV_EVENT_PORT_AFFINITY)
		वापस mlx5e_rep_tc_event_port_affinity(priv);

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम mlx5e_uplink_rep_enable(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u16 max_mtu;

	netdev->min_mtu = ETH_MIN_MTU;
	mlx5_query_port_max_mtu(priv->mdev, &max_mtu, 1);
	netdev->max_mtu = MLX5E_HW2SW_MTU(&priv->channels.params, max_mtu);
	mlx5e_set_dev_port_mtu(priv);

	mlx5e_rep_tc_enable(priv);

	अगर (MLX5_CAP_GEN(mdev, uplink_follow))
		mlx5_modअगरy_vport_admin_state(mdev, MLX5_VPORT_STATE_OP_MOD_UPLINK,
					      0, 0, MLX5_VPORT_ADMIN_STATE_AUTO);
	mlx5_lag_add(mdev, netdev);
	priv->events_nb.notअगरier_call = uplink_rep_async_event;
	mlx5_notअगरier_रेजिस्टर(mdev, &priv->events_nb);
	mlx5e_dcbnl_initialize(priv);
	mlx5e_dcbnl_init_app(priv);
	mlx5e_rep_neigh_init(rpriv);

	netdev->wanted_features |= NETIF_F_HW_TC;

	rtnl_lock();
	अगर (netअगर_running(netdev))
		mlx5e_खोलो(netdev);
	netअगर_device_attach(netdev);
	rtnl_unlock();
पूर्ण

अटल व्योम mlx5e_uplink_rep_disable(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = priv->ppriv;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	rtnl_lock();
	अगर (netअगर_running(priv->netdev))
		mlx5e_बंद(priv->netdev);
	netअगर_device_detach(priv->netdev);
	rtnl_unlock();

	mlx5e_rep_neigh_cleanup(rpriv);
	mlx5e_dcbnl_delete_app(priv);
	mlx5_notअगरier_unरेजिस्टर(mdev, &priv->events_nb);
	mlx5e_rep_tc_disable(priv);
	mlx5_lag_हटाओ(mdev);
पूर्ण

अटल MLX5E_DEFINE_STATS_GRP(sw_rep, 0);
अटल MLX5E_DEFINE_STATS_GRP(vport_rep, MLX5E_NDO_UPDATE_STATS);

/* The stats groups order is opposite to the update_stats() order calls */
अटल mlx5e_stats_grp_t mlx5e_rep_stats_grps[] = अणु
	&MLX5E_STATS_GRP(sw_rep),
	&MLX5E_STATS_GRP(vport_rep),
पूर्ण;

अटल अचिन्हित पूर्णांक mlx5e_rep_stats_grps_num(काष्ठा mlx5e_priv *priv)
अणु
	वापस ARRAY_SIZE(mlx5e_rep_stats_grps);
पूर्ण

/* The stats groups order is opposite to the update_stats() order calls */
अटल mlx5e_stats_grp_t mlx5e_ul_rep_stats_grps[] = अणु
	&MLX5E_STATS_GRP(sw),
	&MLX5E_STATS_GRP(qcnt),
	&MLX5E_STATS_GRP(vnic_env),
	&MLX5E_STATS_GRP(vport),
	&MLX5E_STATS_GRP(802_3),
	&MLX5E_STATS_GRP(2863),
	&MLX5E_STATS_GRP(2819),
	&MLX5E_STATS_GRP(phy),
	&MLX5E_STATS_GRP(eth_ext),
	&MLX5E_STATS_GRP(pcie),
	&MLX5E_STATS_GRP(per_prio),
	&MLX5E_STATS_GRP(pme),
	&MLX5E_STATS_GRP(channels),
	&MLX5E_STATS_GRP(per_port_buff_congest),
पूर्ण;

अटल अचिन्हित पूर्णांक mlx5e_ul_rep_stats_grps_num(काष्ठा mlx5e_priv *priv)
अणु
	वापस ARRAY_SIZE(mlx5e_ul_rep_stats_grps);
पूर्ण

अटल स्थिर काष्ठा mlx5e_profile mlx5e_rep_profile = अणु
	.init			= mlx5e_init_rep,
	.cleanup		= mlx5e_cleanup_rep,
	.init_rx		= mlx5e_init_rep_rx,
	.cleanup_rx		= mlx5e_cleanup_rep_rx,
	.init_tx		= mlx5e_init_rep_tx,
	.cleanup_tx		= mlx5e_cleanup_rep_tx,
	.enable		        = mlx5e_rep_enable,
	.disable	        = mlx5e_rep_disable,
	.update_rx		= mlx5e_update_rep_rx,
	.update_stats           = mlx5e_stats_update_nकरो_stats,
	.rx_handlers            = &mlx5e_rx_handlers_rep,
	.max_tc			= 1,
	.rq_groups		= MLX5E_NUM_RQ_GROUPS(REGULAR),
	.stats_grps		= mlx5e_rep_stats_grps,
	.stats_grps_num		= mlx5e_rep_stats_grps_num,
	.rx_ptp_support		= false,
पूर्ण;

अटल स्थिर काष्ठा mlx5e_profile mlx5e_uplink_rep_profile = अणु
	.init			= mlx5e_init_ul_rep,
	.cleanup		= mlx5e_cleanup_rep,
	.init_rx		= mlx5e_init_ul_rep_rx,
	.cleanup_rx		= mlx5e_cleanup_ul_rep_rx,
	.init_tx		= mlx5e_init_rep_tx,
	.cleanup_tx		= mlx5e_cleanup_rep_tx,
	.enable		        = mlx5e_uplink_rep_enable,
	.disable	        = mlx5e_uplink_rep_disable,
	.update_rx		= mlx5e_update_rep_rx,
	.update_stats           = mlx5e_stats_update_nकरो_stats,
	.update_carrier	        = mlx5e_update_carrier,
	.rx_handlers            = &mlx5e_rx_handlers_rep,
	.max_tc			= MLX5E_MAX_NUM_TC,
	/* XSK is needed so we can replace profile with NIC netdev */
	.rq_groups		= MLX5E_NUM_RQ_GROUPS(XSK),
	.stats_grps		= mlx5e_ul_rep_stats_grps,
	.stats_grps_num		= mlx5e_ul_rep_stats_grps_num,
	.rx_ptp_support		= false,
पूर्ण;

/* e-Switch vport representors */
अटल पूर्णांक
mlx5e_vport_uplink_rep_load(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eचयन_rep *rep)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(mlx5_uplink_netdev_get(dev));
	काष्ठा mlx5e_rep_priv *rpriv = mlx5e_rep_to_rep_priv(rep);
	काष्ठा devlink_port *dl_port;
	पूर्णांक err;

	rpriv->netdev = priv->netdev;

	err = mlx5e_netdev_change_profile(priv, &mlx5e_uplink_rep_profile,
					  rpriv);
	अगर (err)
		वापस err;

	dl_port = mlx5_esw_offloads_devlink_port(dev->priv.eचयन, rpriv->rep->vport);
	अगर (dl_port)
		devlink_port_type_eth_set(dl_port, rpriv->netdev);

	वापस 0;
पूर्ण

अटल व्योम
mlx5e_vport_uplink_rep_unload(काष्ठा mlx5e_rep_priv *rpriv)
अणु
	काष्ठा net_device *netdev = rpriv->netdev;
	काष्ठा devlink_port *dl_port;
	काष्ठा mlx5_core_dev *dev;
	काष्ठा mlx5e_priv *priv;

	priv = netdev_priv(netdev);
	dev = priv->mdev;

	dl_port = mlx5_esw_offloads_devlink_port(dev->priv.eचयन, rpriv->rep->vport);
	अगर (dl_port)
		devlink_port_type_clear(dl_port);
	mlx5e_netdev_attach_nic_profile(priv);
पूर्ण

अटल पूर्णांक
mlx5e_vport_vf_rep_load(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eचयन_rep *rep)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = mlx5e_rep_to_rep_priv(rep);
	स्थिर काष्ठा mlx5e_profile *profile;
	काष्ठा devlink_port *dl_port;
	काष्ठा net_device *netdev;
	काष्ठा mlx5e_priv *priv;
	अचिन्हित पूर्णांक txqs, rxqs;
	पूर्णांक nch, err;

	profile = &mlx5e_rep_profile;
	nch = mlx5e_get_max_num_channels(dev);
	txqs = nch * profile->max_tc;
	rxqs = nch * profile->rq_groups;
	netdev = mlx5e_create_netdev(dev, txqs, rxqs);
	अगर (!netdev) अणु
		mlx5_core_warn(dev,
			       "Failed to create representor netdev for vport %d\n",
			       rep->vport);
		वापस -EINVAL;
	पूर्ण

	mlx5e_build_rep_netdev(netdev, dev);
	rpriv->netdev = netdev;

	priv = netdev_priv(netdev);
	priv->profile = profile;
	priv->ppriv = rpriv;
	err = profile->init(dev, netdev);
	अगर (err) अणु
		netdev_warn(netdev, "rep profile init failed, %d\n", err);
		जाओ err_destroy_netdev;
	पूर्ण

	err = mlx5e_attach_netdev(netdev_priv(netdev));
	अगर (err) अणु
		netdev_warn(netdev,
			    "Failed to attach representor netdev for vport %d\n",
			    rep->vport);
		जाओ err_cleanup_profile;
	पूर्ण

	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		netdev_warn(netdev,
			    "Failed to register representor netdev for vport %d\n",
			    rep->vport);
		जाओ err_detach_netdev;
	पूर्ण

	dl_port = mlx5_esw_offloads_devlink_port(dev->priv.eचयन, rpriv->rep->vport);
	अगर (dl_port)
		devlink_port_type_eth_set(dl_port, netdev);
	वापस 0;

err_detach_netdev:
	mlx5e_detach_netdev(netdev_priv(netdev));

err_cleanup_profile:
	priv->profile->cleanup(priv);

err_destroy_netdev:
	mlx5e_destroy_netdev(netdev_priv(netdev));
	वापस err;
पूर्ण

अटल पूर्णांक
mlx5e_vport_rep_load(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eचयन_rep *rep)
अणु
	काष्ठा mlx5e_rep_priv *rpriv;
	पूर्णांक err;

	rpriv = kzalloc(माप(*rpriv), GFP_KERNEL);
	अगर (!rpriv)
		वापस -ENOMEM;

	/* rpriv->rep to be looked up when profile->init() is called */
	rpriv->rep = rep;
	rep->rep_data[REP_ETH].priv = rpriv;
	INIT_LIST_HEAD(&rpriv->vport_sqs_list);

	अगर (rep->vport == MLX5_VPORT_UPLINK)
		err = mlx5e_vport_uplink_rep_load(dev, rep);
	अन्यथा
		err = mlx5e_vport_vf_rep_load(dev, rep);

	अगर (err)
		kमुक्त(rpriv);

	वापस err;
पूर्ण

अटल व्योम
mlx5e_vport_rep_unload(काष्ठा mlx5_eचयन_rep *rep)
अणु
	काष्ठा mlx5e_rep_priv *rpriv = mlx5e_rep_to_rep_priv(rep);
	काष्ठा net_device *netdev = rpriv->netdev;
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *dev = priv->mdev;
	काष्ठा devlink_port *dl_port;
	व्योम *ppriv = priv->ppriv;

	अगर (rep->vport == MLX5_VPORT_UPLINK) अणु
		mlx5e_vport_uplink_rep_unload(rpriv);
		जाओ मुक्त_ppriv;
	पूर्ण

	dl_port = mlx5_esw_offloads_devlink_port(dev->priv.eचयन, rpriv->rep->vport);
	अगर (dl_port)
		devlink_port_type_clear(dl_port);
	unरेजिस्टर_netdev(netdev);
	mlx5e_detach_netdev(priv);
	priv->profile->cleanup(priv);
	mlx5e_destroy_netdev(priv);
मुक्त_ppriv:
	kमुक्त(ppriv); /* mlx5e_rep_priv */
पूर्ण

अटल व्योम *mlx5e_vport_rep_get_proto_dev(काष्ठा mlx5_eचयन_rep *rep)
अणु
	काष्ठा mlx5e_rep_priv *rpriv;

	rpriv = mlx5e_rep_to_rep_priv(rep);

	वापस rpriv->netdev;
पूर्ण

अटल स्थिर काष्ठा mlx5_eचयन_rep_ops rep_ops = अणु
	.load = mlx5e_vport_rep_load,
	.unload = mlx5e_vport_rep_unload,
	.get_proto_dev = mlx5e_vport_rep_get_proto_dev
पूर्ण;

अटल पूर्णांक mlx5e_rep_probe(काष्ठा auxiliary_device *adev,
			   स्थिर काष्ठा auxiliary_device_id *id)
अणु
	काष्ठा mlx5_adev *edev = container_of(adev, काष्ठा mlx5_adev, adev);
	काष्ठा mlx5_core_dev *mdev = edev->mdev;
	काष्ठा mlx5_eचयन *esw;

	esw = mdev->priv.eचयन;
	mlx5_eचयन_रेजिस्टर_vport_reps(esw, &rep_ops, REP_ETH);
	वापस 0;
पूर्ण

अटल व्योम mlx5e_rep_हटाओ(काष्ठा auxiliary_device *adev)
अणु
	काष्ठा mlx5_adev *vdev = container_of(adev, काष्ठा mlx5_adev, adev);
	काष्ठा mlx5_core_dev *mdev = vdev->mdev;
	काष्ठा mlx5_eचयन *esw;

	esw = mdev->priv.eचयन;
	mlx5_eचयन_unरेजिस्टर_vport_reps(esw, REP_ETH);
पूर्ण

अटल स्थिर काष्ठा auxiliary_device_id mlx5e_rep_id_table[] = अणु
	अणु .name = MLX5_ADEV_NAME ".eth-rep", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(auxiliary, mlx5e_rep_id_table);

अटल काष्ठा auxiliary_driver mlx5e_rep_driver = अणु
	.name = "eth-rep",
	.probe = mlx5e_rep_probe,
	.हटाओ = mlx5e_rep_हटाओ,
	.id_table = mlx5e_rep_id_table,
पूर्ण;

पूर्णांक mlx5e_rep_init(व्योम)
अणु
	वापस auxiliary_driver_रेजिस्टर(&mlx5e_rep_driver);
पूर्ण

व्योम mlx5e_rep_cleanup(व्योम)
अणु
	auxiliary_driver_unरेजिस्टर(&mlx5e_rep_driver);
पूर्ण
