<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies. All rights reserved.
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

#समावेश <rdma/ib_verbs.h>
#समावेश <linux/mlx5/fs.h>
#समावेश "en.h"
#समावेश "en/params.h"
#समावेश "ipoib.h"

#घोषणा IB_DEFAULT_Q_KEY   0xb1b
#घोषणा MLX5I_PARAMS_DEFAULT_LOG_RQ_SIZE 9

अटल पूर्णांक mlx5i_खोलो(काष्ठा net_device *netdev);
अटल पूर्णांक mlx5i_बंद(काष्ठा net_device *netdev);
अटल पूर्णांक mlx5i_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu);

अटल स्थिर काष्ठा net_device_ops mlx5i_netdev_ops = अणु
	.nकरो_खोलो                = mlx5i_खोलो,
	.nकरो_stop                = mlx5i_बंद,
	.nकरो_get_stats64         = mlx5i_get_stats,
	.nकरो_init                = mlx5i_dev_init,
	.nकरो_uninit              = mlx5i_dev_cleanup,
	.nकरो_change_mtu          = mlx5i_change_mtu,
	.nकरो_करो_ioctl            = mlx5i_ioctl,
पूर्ण;

/* IPoIB mlx5 netdev profile */
अटल व्योम mlx5i_build_nic_params(काष्ठा mlx5_core_dev *mdev,
				   काष्ठा mlx5e_params *params)
अणु
	/* Override RQ params as IPoIB supports only LINKED LIST RQ क्रम now */
	MLX5E_SET_PFLAG(params, MLX5E_PFLAG_RX_STRIDING_RQ, false);
	mlx5e_set_rq_type(mdev, params);
	mlx5e_init_rq_type_params(mdev, params);

	/* RQ size in ipoib by शेष is 512 */
	params->log_rq_mtu_frames = is_kdump_kernel() ?
		MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE :
		MLX5I_PARAMS_DEFAULT_LOG_RQ_SIZE;

	params->lro_en = false;
	params->hard_mtu = MLX5_IB_GRH_BYTES + MLX5_IPOIB_HARD_LEN;
	params->tunneled_offload_en = false;
पूर्ण

/* Called directly after IPoIB netdevice was created to initialize SW काष्ठाs */
पूर्णांक mlx5i_init(काष्ठा mlx5_core_dev *mdev, काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv  = mlx5i_epriv(netdev);

	netअगर_carrier_off(netdev);
	mlx5e_set_netdev_mtu_boundaries(priv);
	netdev->mtu = netdev->max_mtu;

	mlx5e_build_nic_params(priv, शून्य, netdev->mtu);
	mlx5i_build_nic_params(mdev, &priv->channels.params);

	mlx5e_बारtamp_init(priv);

	/* netdev init */
	netdev->hw_features    |= NETIF_F_SG;
	netdev->hw_features    |= NETIF_F_IP_CSUM;
	netdev->hw_features    |= NETIF_F_IPV6_CSUM;
	netdev->hw_features    |= NETIF_F_GRO;
	netdev->hw_features    |= NETIF_F_TSO;
	netdev->hw_features    |= NETIF_F_TSO6;
	netdev->hw_features    |= NETIF_F_RXCSUM;
	netdev->hw_features    |= NETIF_F_RXHASH;

	netdev->netdev_ops = &mlx5i_netdev_ops;
	netdev->ethtool_ops = &mlx5i_ethtool_ops;

	वापस 0;
पूर्ण

/* Called directly beक्रमe IPoIB netdevice is destroyed to cleanup SW काष्ठाs */
व्योम mlx5i_cleanup(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_priv_cleanup(priv);
पूर्ण

अटल व्योम mlx5i_grp_sw_update_stats(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_sw_stats s = अणु 0 पूर्ण;
	पूर्णांक i, j;

	क्रम (i = 0; i < priv->max_nch; i++) अणु
		काष्ठा mlx5e_channel_stats *channel_stats;
		काष्ठा mlx5e_rq_stats *rq_stats;

		channel_stats = &priv->channel_stats[i];
		rq_stats = &channel_stats->rq;

		s.rx_packets += rq_stats->packets;
		s.rx_bytes   += rq_stats->bytes;

		क्रम (j = 0; j < priv->max_खोलोed_tc; j++) अणु
			काष्ठा mlx5e_sq_stats *sq_stats = &channel_stats->sq[j];

			s.tx_packets           += sq_stats->packets;
			s.tx_bytes             += sq_stats->bytes;
			s.tx_queue_dropped     += sq_stats->dropped;
		पूर्ण
	पूर्ण

	स_नकल(&priv->stats.sw, &s, माप(s));
पूर्ण

व्योम mlx5i_get_stats(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा mlx5e_priv     *priv   = mlx5i_epriv(dev);
	काष्ठा mlx5e_sw_stats *sstats = &priv->stats.sw;

	mlx5i_grp_sw_update_stats(priv);

	stats->rx_packets = sstats->rx_packets;
	stats->rx_bytes   = sstats->rx_bytes;
	stats->tx_packets = sstats->tx_packets;
	stats->tx_bytes   = sstats->tx_bytes;
	stats->tx_dropped = sstats->tx_queue_dropped;
पूर्ण

पूर्णांक mlx5i_init_underlay_qp(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5i_priv *ipriv = priv->ppriv;
	पूर्णांक ret;

	अणु
		u32 in[MLX5_ST_SZ_DW(rst2init_qp_in)] = अणुपूर्ण;
		u32 *qpc;

		qpc = MLX5_ADDR_OF(rst2init_qp_in, in, qpc);

		MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);
		MLX5_SET(qpc, qpc, primary_address_path.pkey_index,
			 ipriv->pkey_index);
		MLX5_SET(qpc, qpc, primary_address_path.vhca_port_num, 1);
		MLX5_SET(qpc, qpc, q_key, IB_DEFAULT_Q_KEY);

		MLX5_SET(rst2init_qp_in, in, opcode, MLX5_CMD_OP_RST2INIT_QP);
		MLX5_SET(rst2init_qp_in, in, qpn, ipriv->qpn);
		ret = mlx5_cmd_exec_in(mdev, rst2init_qp, in);
		अगर (ret)
			जाओ err_qp_modअगरy_to_err;
	पूर्ण
	अणु
		u32 in[MLX5_ST_SZ_DW(init2rtr_qp_in)] = अणुपूर्ण;

		MLX5_SET(init2rtr_qp_in, in, opcode, MLX5_CMD_OP_INIT2RTR_QP);
		MLX5_SET(init2rtr_qp_in, in, qpn, ipriv->qpn);
		ret = mlx5_cmd_exec_in(mdev, init2rtr_qp, in);
		अगर (ret)
			जाओ err_qp_modअगरy_to_err;
	पूर्ण
	अणु
		u32 in[MLX5_ST_SZ_DW(rtr2rts_qp_in)] = अणुपूर्ण;

		MLX5_SET(rtr2rts_qp_in, in, opcode, MLX5_CMD_OP_RTR2RTS_QP);
		MLX5_SET(rtr2rts_qp_in, in, qpn, ipriv->qpn);
		ret = mlx5_cmd_exec_in(mdev, rtr2rts_qp, in);
		अगर (ret)
			जाओ err_qp_modअगरy_to_err;
	पूर्ण
	वापस 0;

err_qp_modअगरy_to_err:
	अणु
		u32 in[MLX5_ST_SZ_DW(qp_2err_in)] = अणुपूर्ण;

		MLX5_SET(qp_2err_in, in, opcode, MLX5_CMD_OP_2ERR_QP);
		MLX5_SET(qp_2err_in, in, qpn, ipriv->qpn);
		mlx5_cmd_exec_in(mdev, qp_2err, in);
	पूर्ण
	वापस ret;
पूर्ण

व्योम mlx5i_uninit_underlay_qp(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5i_priv *ipriv = priv->ppriv;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 in[MLX5_ST_SZ_DW(qp_2rst_in)] = अणुपूर्ण;

	MLX5_SET(qp_2rst_in, in, opcode, MLX5_CMD_OP_2RST_QP);
	MLX5_SET(qp_2rst_in, in, qpn, ipriv->qpn);
	mlx5_cmd_exec_in(mdev, qp_2rst, in);
पूर्ण

#घोषणा MLX5_QP_ENHANCED_ULP_STATELESS_MODE 2

पूर्णांक mlx5i_create_underlay_qp(काष्ठा mlx5e_priv *priv)
अणु
	अचिन्हित अक्षर *dev_addr = priv->netdev->dev_addr;
	u32 out[MLX5_ST_SZ_DW(create_qp_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(create_qp_in)] = अणुपूर्ण;
	काष्ठा mlx5i_priv *ipriv = priv->ppriv;
	व्योम *addr_path;
	पूर्णांक qpn = 0;
	पूर्णांक ret = 0;
	व्योम *qpc;

	अगर (MLX5_CAP_GEN(priv->mdev, mkey_by_name)) अणु
		qpn = (dev_addr[1] << 16) + (dev_addr[2] << 8) + dev_addr[3];
		MLX5_SET(create_qp_in, in, input_qpn, qpn);
	पूर्ण

	qpc = MLX5_ADDR_OF(create_qp_in, in, qpc);
	MLX5_SET(qpc, qpc, ts_क्रमmat, mlx5_get_qp_शेष_ts(priv->mdev));
	MLX5_SET(qpc, qpc, st, MLX5_QP_ST_UD);
	MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);
	MLX5_SET(qpc, qpc, ulp_stateless_offload_mode,
		 MLX5_QP_ENHANCED_ULP_STATELESS_MODE);

	addr_path = MLX5_ADDR_OF(qpc, qpc, primary_address_path);
	MLX5_SET(ads, addr_path, vhca_port_num, 1);
	MLX5_SET(ads, addr_path, grh, 1);

	MLX5_SET(create_qp_in, in, opcode, MLX5_CMD_OP_CREATE_QP);
	ret = mlx5_cmd_exec_inout(priv->mdev, create_qp, in, out);
	अगर (ret)
		वापस ret;

	ipriv->qpn = MLX5_GET(create_qp_out, out, qpn);

	वापस 0;
पूर्ण

व्योम mlx5i_destroy_underlay_qp(काष्ठा mlx5_core_dev *mdev, u32 qpn)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_qp_in)] = अणुपूर्ण;

	MLX5_SET(destroy_qp_in, in, opcode, MLX5_CMD_OP_DESTROY_QP);
	MLX5_SET(destroy_qp_in, in, qpn, qpn);
	mlx5_cmd_exec_in(mdev, destroy_qp, in);
पूर्ण

पूर्णांक mlx5i_update_nic_rx(काष्ठा mlx5e_priv *priv)
अणु
	वापस mlx5e_refresh_tirs(priv, true, true);
पूर्ण

पूर्णांक mlx5i_create_tis(काष्ठा mlx5_core_dev *mdev, u32 underlay_qpn, u32 *tisn)
अणु
	u32 in[MLX5_ST_SZ_DW(create_tis_in)] = अणुपूर्ण;
	व्योम *tisc;

	tisc = MLX5_ADDR_OF(create_tis_in, in, ctx);

	MLX5_SET(tisc, tisc, underlay_qpn, underlay_qpn);

	वापस mlx5e_create_tis(mdev, in, tisn);
पूर्ण

अटल पूर्णांक mlx5i_init_tx(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5i_priv *ipriv = priv->ppriv;
	पूर्णांक err;

	err = mlx5i_create_underlay_qp(priv);
	अगर (err) अणु
		mlx5_core_warn(priv->mdev, "create underlay QP failed, %d\n", err);
		वापस err;
	पूर्ण

	err = mlx5i_create_tis(priv->mdev, ipriv->qpn, &priv->tisn[0][0]);
	अगर (err) अणु
		mlx5_core_warn(priv->mdev, "create tis failed, %d\n", err);
		जाओ err_destroy_underlay_qp;
	पूर्ण

	वापस 0;

err_destroy_underlay_qp:
	mlx5i_destroy_underlay_qp(priv->mdev, ipriv->qpn);
	वापस err;
पूर्ण

अटल व्योम mlx5i_cleanup_tx(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5i_priv *ipriv = priv->ppriv;

	mlx5e_destroy_tis(priv->mdev, priv->tisn[0][0]);
	mlx5i_destroy_underlay_qp(priv->mdev, ipriv->qpn);
पूर्ण

अटल पूर्णांक mlx5i_create_flow_steering(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा ttc_params ttc_params = अणुपूर्ण;
	पूर्णांक tt, err;

	priv->fs.ns = mlx5_get_flow_namespace(priv->mdev,
					       MLX5_FLOW_NAMESPACE_KERNEL);

	अगर (!priv->fs.ns)
		वापस -EINVAL;

	err = mlx5e_arfs_create_tables(priv);
	अगर (err) अणु
		netdev_err(priv->netdev, "Failed to create arfs tables, err=%d\n",
			   err);
		priv->netdev->hw_features &= ~NETIF_F_NTUPLE;
	पूर्ण

	mlx5e_set_ttc_basic_params(priv, &ttc_params);
	mlx5e_set_inner_ttc_ft_params(&ttc_params);
	क्रम (tt = 0; tt < MLX5E_NUM_INसूची_TIRS; tt++)
		ttc_params.indir_tirn[tt] = priv->inner_indir_tir[tt].tirn;

	err = mlx5e_create_inner_ttc_table(priv, &ttc_params, &priv->fs.inner_ttc);
	अगर (err) अणु
		netdev_err(priv->netdev, "Failed to create inner ttc table, err=%d\n",
			   err);
		जाओ err_destroy_arfs_tables;
	पूर्ण

	mlx5e_set_ttc_ft_params(&ttc_params);
	क्रम (tt = 0; tt < MLX5E_NUM_INसूची_TIRS; tt++)
		ttc_params.indir_tirn[tt] = priv->indir_tir[tt].tirn;

	err = mlx5e_create_ttc_table(priv, &ttc_params, &priv->fs.ttc);
	अगर (err) अणु
		netdev_err(priv->netdev, "Failed to create ttc table, err=%d\n",
			   err);
		जाओ err_destroy_inner_ttc_table;
	पूर्ण

	वापस 0;

err_destroy_inner_ttc_table:
	mlx5e_destroy_inner_ttc_table(priv, &priv->fs.inner_ttc);
err_destroy_arfs_tables:
	mlx5e_arfs_destroy_tables(priv);

	वापस err;
पूर्ण

अटल व्योम mlx5i_destroy_flow_steering(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_destroy_ttc_table(priv, &priv->fs.ttc);
	mlx5e_destroy_inner_ttc_table(priv, &priv->fs.inner_ttc);
	mlx5e_arfs_destroy_tables(priv);
पूर्ण

अटल पूर्णांक mlx5i_init_rx(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u16 max_nch = priv->max_nch;
	पूर्णांक err;

	mlx5e_create_q_counters(priv);

	err = mlx5e_खोलो_drop_rq(priv, &priv->drop_rq);
	अगर (err) अणु
		mlx5_core_err(mdev, "open drop rq failed, %d\n", err);
		जाओ err_destroy_q_counters;
	पूर्ण

	err = mlx5e_create_indirect_rqt(priv);
	अगर (err)
		जाओ err_बंद_drop_rq;

	err = mlx5e_create_direct_rqts(priv, priv->direct_tir, max_nch);
	अगर (err)
		जाओ err_destroy_indirect_rqts;

	err = mlx5e_create_indirect_tirs(priv, true);
	अगर (err)
		जाओ err_destroy_direct_rqts;

	err = mlx5e_create_direct_tirs(priv, priv->direct_tir, max_nch);
	अगर (err)
		जाओ err_destroy_indirect_tirs;

	err = mlx5i_create_flow_steering(priv);
	अगर (err)
		जाओ err_destroy_direct_tirs;

	वापस 0;

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
err_destroy_q_counters:
	mlx5e_destroy_q_counters(priv);
	वापस err;
पूर्ण

अटल व्योम mlx5i_cleanup_rx(काष्ठा mlx5e_priv *priv)
अणु
	u16 max_nch = priv->max_nch;

	mlx5i_destroy_flow_steering(priv);
	mlx5e_destroy_direct_tirs(priv, priv->direct_tir, max_nch);
	mlx5e_destroy_indirect_tirs(priv);
	mlx5e_destroy_direct_rqts(priv, priv->direct_tir, max_nch);
	mlx5e_destroy_rqt(priv, &priv->indir_rqt);
	mlx5e_बंद_drop_rq(&priv->drop_rq);
	mlx5e_destroy_q_counters(priv);
पूर्ण

/* The stats groups order is opposite to the update_stats() order calls */
अटल mlx5e_stats_grp_t mlx5i_stats_grps[] = अणु
	&MLX5E_STATS_GRP(sw),
	&MLX5E_STATS_GRP(qcnt),
	&MLX5E_STATS_GRP(vnic_env),
	&MLX5E_STATS_GRP(vport),
	&MLX5E_STATS_GRP(802_3),
	&MLX5E_STATS_GRP(2863),
	&MLX5E_STATS_GRP(2819),
	&MLX5E_STATS_GRP(phy),
	&MLX5E_STATS_GRP(pcie),
	&MLX5E_STATS_GRP(per_prio),
	&MLX5E_STATS_GRP(pme),
	&MLX5E_STATS_GRP(channels),
	&MLX5E_STATS_GRP(per_port_buff_congest),
पूर्ण;

अटल अचिन्हित पूर्णांक mlx5i_stats_grps_num(काष्ठा mlx5e_priv *priv)
अणु
	वापस ARRAY_SIZE(mlx5i_stats_grps);
पूर्ण

अटल स्थिर काष्ठा mlx5e_profile mlx5i_nic_profile = अणु
	.init		   = mlx5i_init,
	.cleanup	   = mlx5i_cleanup,
	.init_tx	   = mlx5i_init_tx,
	.cleanup_tx	   = mlx5i_cleanup_tx,
	.init_rx	   = mlx5i_init_rx,
	.cleanup_rx	   = mlx5i_cleanup_rx,
	.enable		   = शून्य, /* mlx5i_enable */
	.disable	   = शून्य, /* mlx5i_disable */
	.update_rx	   = mlx5i_update_nic_rx,
	.update_stats	   = शून्य, /* mlx5i_update_stats */
	.update_carrier    = शून्य, /* no HW update in IB link */
	.rx_handlers       = &mlx5i_rx_handlers,
	.max_tc		   = MLX5I_MAX_NUM_TC,
	.rq_groups	   = MLX5E_NUM_RQ_GROUPS(REGULAR),
	.stats_grps        = mlx5i_stats_grps,
	.stats_grps_num    = mlx5i_stats_grps_num,
	.rx_ptp_support    = false,
पूर्ण;

/* mlx5i netdev NDos */

अटल पूर्णांक mlx5i_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(netdev);
	काष्ठा mlx5e_params new_params;
	पूर्णांक err = 0;

	mutex_lock(&priv->state_lock);

	new_params = priv->channels.params;
	new_params.sw_mtu = new_mtu;

	err = mlx5e_safe_चयन_params(priv, &new_params, शून्य, शून्य, true);
	अगर (err)
		जाओ out;

	netdev->mtu = new_params.sw_mtu;

out:
	mutex_unlock(&priv->state_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5i_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा mlx5e_priv    *priv   = mlx5i_epriv(dev);
	काष्ठा mlx5i_priv    *ipriv  = priv->ppriv;

	/* Set dev address using underlay QP */
	dev->dev_addr[1] = (ipriv->qpn >> 16) & 0xff;
	dev->dev_addr[2] = (ipriv->qpn >>  8) & 0xff;
	dev->dev_addr[3] = (ipriv->qpn) & 0xff;

	/* Add QPN to net-device mapping to HT */
	mlx5i_pkey_add_qpn(dev, ipriv->qpn);

	वापस 0;
पूर्ण

पूर्णांक mlx5i_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(dev);

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस mlx5e_hwstamp_set(priv, अगरr);
	हाल SIOCGHWTSTAMP:
		वापस mlx5e_hwstamp_get(priv, अगरr);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

व्योम mlx5i_dev_cleanup(काष्ठा net_device *dev)
अणु
	काष्ठा mlx5e_priv    *priv   = mlx5i_epriv(dev);
	काष्ठा mlx5i_priv    *ipriv = priv->ppriv;

	mlx5i_uninit_underlay_qp(priv);

	/* Delete QPN to net-device mapping from HT */
	mlx5i_pkey_del_qpn(dev, ipriv->qpn);
पूर्ण

अटल पूर्णांक mlx5i_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *epriv = mlx5i_epriv(netdev);
	काष्ठा mlx5i_priv *ipriv = epriv->ppriv;
	काष्ठा mlx5_core_dev *mdev = epriv->mdev;
	पूर्णांक err;

	mutex_lock(&epriv->state_lock);

	set_bit(MLX5E_STATE_OPENED, &epriv->state);

	err = mlx5i_init_underlay_qp(epriv);
	अगर (err) अणु
		mlx5_core_warn(mdev, "prepare underlay qp state failed, %d\n", err);
		जाओ err_clear_state_खोलोed_flag;
	पूर्ण

	err = mlx5_fs_add_rx_underlay_qpn(mdev, ipriv->qpn);
	अगर (err) अणु
		mlx5_core_warn(mdev, "attach underlay qp to ft failed, %d\n", err);
		जाओ err_reset_qp;
	पूर्ण

	err = mlx5e_खोलो_channels(epriv, &epriv->channels);
	अगर (err)
		जाओ err_हटाओ_fs_underlay_qp;

	epriv->profile->update_rx(epriv);
	mlx5e_activate_priv_channels(epriv);

	mutex_unlock(&epriv->state_lock);
	वापस 0;

err_हटाओ_fs_underlay_qp:
	mlx5_fs_हटाओ_rx_underlay_qpn(mdev, ipriv->qpn);
err_reset_qp:
	mlx5i_uninit_underlay_qp(epriv);
err_clear_state_खोलोed_flag:
	clear_bit(MLX5E_STATE_OPENED, &epriv->state);
	mutex_unlock(&epriv->state_lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5i_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *epriv = mlx5i_epriv(netdev);
	काष्ठा mlx5i_priv *ipriv = epriv->ppriv;
	काष्ठा mlx5_core_dev *mdev = epriv->mdev;

	/* May alपढ़ोy be CLOSED in हाल a previous configuration operation
	 * (e.g RX/TX queue size change) that involves बंद&खोलो failed.
	 */
	mutex_lock(&epriv->state_lock);

	अगर (!test_bit(MLX5E_STATE_OPENED, &epriv->state))
		जाओ unlock;

	clear_bit(MLX5E_STATE_OPENED, &epriv->state);

	netअगर_carrier_off(epriv->netdev);
	mlx5_fs_हटाओ_rx_underlay_qpn(mdev, ipriv->qpn);
	mlx5e_deactivate_priv_channels(epriv);
	mlx5e_बंद_channels(&epriv->channels);
	mlx5i_uninit_underlay_qp(epriv);
unlock:
	mutex_unlock(&epriv->state_lock);
	वापस 0;
पूर्ण

/* IPoIB RDMA netdev callbacks */
अटल पूर्णांक mlx5i_attach_mcast(काष्ठा net_device *netdev, काष्ठा ib_device *hca,
			      जोड़ ib_gid *gid, u16 lid, पूर्णांक set_qkey,
			      u32 qkey)
अणु
	काष्ठा mlx5e_priv    *epriv = mlx5i_epriv(netdev);
	काष्ठा mlx5_core_dev *mdev  = epriv->mdev;
	काष्ठा mlx5i_priv    *ipriv = epriv->ppriv;
	पूर्णांक err;

	mlx5_core_dbg(mdev, "attaching QPN 0x%x, MGID %pI6\n", ipriv->qpn,
		      gid->raw);
	err = mlx5_core_attach_mcg(mdev, gid, ipriv->qpn);
	अगर (err)
		mlx5_core_warn(mdev, "failed attaching QPN 0x%x, MGID %pI6\n",
			       ipriv->qpn, gid->raw);

	अगर (set_qkey) अणु
		mlx5_core_dbg(mdev, "%s setting qkey 0x%x\n",
			      netdev->name, qkey);
		ipriv->qkey = qkey;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx5i_detach_mcast(काष्ठा net_device *netdev, काष्ठा ib_device *hca,
			      जोड़ ib_gid *gid, u16 lid)
अणु
	काष्ठा mlx5e_priv    *epriv = mlx5i_epriv(netdev);
	काष्ठा mlx5_core_dev *mdev  = epriv->mdev;
	काष्ठा mlx5i_priv    *ipriv = epriv->ppriv;
	पूर्णांक err;

	mlx5_core_dbg(mdev, "detaching QPN 0x%x, MGID %pI6\n", ipriv->qpn,
		      gid->raw);

	err = mlx5_core_detach_mcg(mdev, gid, ipriv->qpn);
	अगर (err)
		mlx5_core_dbg(mdev, "failed detaching QPN 0x%x, MGID %pI6\n",
			      ipriv->qpn, gid->raw);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5i_xmit(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		      काष्ठा ib_ah *address, u32 dqpn)
अणु
	काष्ठा mlx5e_priv *epriv = mlx5i_epriv(dev);
	काष्ठा mlx5e_txqsq *sq   = epriv->txq2sq[skb_get_queue_mapping(skb)];
	काष्ठा mlx5_ib_ah *mah   = to_mah(address);
	काष्ठा mlx5i_priv *ipriv = epriv->ppriv;

	mlx5i_sq_xmit(sq, skb, &mah->av, dqpn, ipriv->qkey, netdev_xmit_more());

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम mlx5i_set_pkey_index(काष्ठा net_device *netdev, पूर्णांक id)
अणु
	काष्ठा mlx5i_priv *ipriv = netdev_priv(netdev);

	ipriv->pkey_index = (u16)id;
पूर्ण

अटल पूर्णांक mlx5i_check_required_hca_cap(काष्ठा mlx5_core_dev *mdev)
अणु
	अगर (MLX5_CAP_GEN(mdev, port_type) != MLX5_CAP_PORT_TYPE_IB)
		वापस -EOPNOTSUPP;

	अगर (!MLX5_CAP_GEN(mdev, ipoib_enhanced_offloads)) अणु
		mlx5_core_warn(mdev, "IPoIB enhanced offloads are not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlx5_rdma_netdev_मुक्त(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5i_priv *ipriv = priv->ppriv;
	स्थिर काष्ठा mlx5e_profile *profile = priv->profile;

	mlx5e_detach_netdev(priv);
	profile->cleanup(priv);

	अगर (!ipriv->sub_पूर्णांकerface) अणु
		mlx5i_pkey_qpn_ht_cleanup(netdev);
		mlx5e_destroy_mdev_resources(mdev);
	पूर्ण
पूर्ण

अटल bool mlx5_is_sub_पूर्णांकerface(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस mdev->mlx5e_res.hw_objs.pdn != 0;
पूर्ण

अटल स्थिर काष्ठा mlx5e_profile *mlx5_get_profile(काष्ठा mlx5_core_dev *mdev)
अणु
	अगर (mlx5_is_sub_पूर्णांकerface(mdev))
		वापस mlx5i_pkey_get_profile();
	वापस &mlx5i_nic_profile;
पूर्ण

अटल पूर्णांक mlx5_rdma_setup_rn(काष्ठा ib_device *ibdev, u32 port_num,
			      काष्ठा net_device *netdev, व्योम *param)
अणु
	काष्ठा mlx5_core_dev *mdev = (काष्ठा mlx5_core_dev *)param;
	स्थिर काष्ठा mlx5e_profile *prof = mlx5_get_profile(mdev);
	काष्ठा mlx5i_priv *ipriv;
	काष्ठा mlx5e_priv *epriv;
	काष्ठा rdma_netdev *rn;
	पूर्णांक err;

	ipriv = netdev_priv(netdev);
	epriv = mlx5i_epriv(netdev);

	ipriv->sub_पूर्णांकerface = mlx5_is_sub_पूर्णांकerface(mdev);
	अगर (!ipriv->sub_पूर्णांकerface) अणु
		err = mlx5i_pkey_qpn_ht_init(netdev);
		अगर (err) अणु
			mlx5_core_warn(mdev, "allocate qpn_to_netdev ht failed\n");
			वापस err;
		पूर्ण

		/* This should only be called once per mdev */
		err = mlx5e_create_mdev_resources(mdev);
		अगर (err)
			जाओ destroy_ht;
	पूर्ण

	err = mlx5e_priv_init(epriv, netdev, mdev);
	अगर (err)
		जाओ destroy_mdev_resources;

	epriv->profile = prof;
	epriv->ppriv = ipriv;

	prof->init(mdev, netdev);

	err = mlx5e_attach_netdev(epriv);
	अगर (err)
		जाओ detach;
	netअगर_carrier_off(netdev);

	/* set rdma_netdev func poपूर्णांकers */
	rn = &ipriv->rn;
	rn->hca  = ibdev;
	rn->send = mlx5i_xmit;
	rn->attach_mcast = mlx5i_attach_mcast;
	rn->detach_mcast = mlx5i_detach_mcast;
	rn->set_id = mlx5i_set_pkey_index;

	netdev->priv_deकाष्ठाor = mlx5_rdma_netdev_मुक्त;
	netdev->needs_मुक्त_netdev = 1;

	वापस 0;

detach:
	prof->cleanup(epriv);
	अगर (ipriv->sub_पूर्णांकerface)
		वापस err;
destroy_mdev_resources:
	mlx5e_destroy_mdev_resources(mdev);
destroy_ht:
	mlx5i_pkey_qpn_ht_cleanup(netdev);
	वापस err;
पूर्ण

पूर्णांक mlx5_rdma_rn_get_params(काष्ठा mlx5_core_dev *mdev,
			    काष्ठा ib_device *device,
			    काष्ठा rdma_netdev_alloc_params *params)
अणु
	पूर्णांक nch;
	पूर्णांक rc;

	rc = mlx5i_check_required_hca_cap(mdev);
	अगर (rc)
		वापस rc;

	nch = mlx5e_get_max_num_channels(mdev);

	*params = (काष्ठा rdma_netdev_alloc_params)अणु
		.माप_priv = माप(काष्ठा mlx5i_priv) +
			       माप(काष्ठा mlx5e_priv),
		.txqs = nch * MLX5E_MAX_NUM_TC,
		.rxqs = nch,
		.param = mdev,
		.initialize_rdma_netdev = mlx5_rdma_setup_rn,
	पूर्ण;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlx5_rdma_rn_get_params);
