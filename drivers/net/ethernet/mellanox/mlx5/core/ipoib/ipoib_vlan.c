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

#समावेश <linux/hash.h>
#समावेश "ipoib.h"

#घोषणा MLX5I_MAX_LOG_PKEY_SUP 7

काष्ठा qpn_to_netdev अणु
	काष्ठा net_device *netdev;
	काष्ठा hlist_node hlist;
	u32 underlay_qpn;
पूर्ण;

काष्ठा mlx5i_pkey_qpn_ht अणु
	काष्ठा hlist_head buckets[1 << MLX5I_MAX_LOG_PKEY_SUP];
	spinlock_t ht_lock; /* Synchronise with NAPI */
पूर्ण;

पूर्णांक mlx5i_pkey_qpn_ht_init(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5i_priv *ipriv = netdev_priv(netdev);
	काष्ठा mlx5i_pkey_qpn_ht *qpn_htbl;

	qpn_htbl = kzalloc(माप(*qpn_htbl), GFP_KERNEL);
	अगर (!qpn_htbl)
		वापस -ENOMEM;

	ipriv->qpn_htbl = qpn_htbl;
	spin_lock_init(&qpn_htbl->ht_lock);

	वापस 0;
पूर्ण

व्योम mlx5i_pkey_qpn_ht_cleanup(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5i_priv *ipriv = netdev_priv(netdev);

	kमुक्त(ipriv->qpn_htbl);
पूर्ण

अटल काष्ठा qpn_to_netdev *mlx5i_find_qpn_to_netdev_node(काष्ठा hlist_head *buckets,
							   u32 qpn)
अणु
	काष्ठा hlist_head *h = &buckets[hash_32(qpn, MLX5I_MAX_LOG_PKEY_SUP)];
	काष्ठा qpn_to_netdev *node;

	hlist_क्रम_each_entry(node, h, hlist) अणु
		अगर (node->underlay_qpn == qpn)
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक mlx5i_pkey_add_qpn(काष्ठा net_device *netdev, u32 qpn)
अणु
	काष्ठा mlx5i_priv *ipriv = netdev_priv(netdev);
	काष्ठा mlx5i_pkey_qpn_ht *ht = ipriv->qpn_htbl;
	u8 key = hash_32(qpn, MLX5I_MAX_LOG_PKEY_SUP);
	काष्ठा qpn_to_netdev *new_node;

	new_node = kzalloc(माप(*new_node), GFP_KERNEL);
	अगर (!new_node)
		वापस -ENOMEM;

	new_node->netdev = netdev;
	new_node->underlay_qpn = qpn;
	spin_lock_bh(&ht->ht_lock);
	hlist_add_head(&new_node->hlist, &ht->buckets[key]);
	spin_unlock_bh(&ht->ht_lock);

	वापस 0;
पूर्ण

पूर्णांक mlx5i_pkey_del_qpn(काष्ठा net_device *netdev, u32 qpn)
अणु
	काष्ठा mlx5e_priv *epriv = mlx5i_epriv(netdev);
	काष्ठा mlx5i_priv *ipriv = epriv->ppriv;
	काष्ठा mlx5i_pkey_qpn_ht *ht = ipriv->qpn_htbl;
	काष्ठा qpn_to_netdev *node;

	node = mlx5i_find_qpn_to_netdev_node(ht->buckets, qpn);
	अगर (!node) अणु
		mlx5_core_warn(epriv->mdev, "QPN to netdev delete from HT failed\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&ht->ht_lock);
	hlist_del_init(&node->hlist);
	spin_unlock_bh(&ht->ht_lock);
	kमुक्त(node);

	वापस 0;
पूर्ण

काष्ठा net_device *mlx5i_pkey_get_netdev(काष्ठा net_device *netdev, u32 qpn)
अणु
	काष्ठा mlx5i_priv *ipriv = netdev_priv(netdev);
	काष्ठा qpn_to_netdev *node;

	node = mlx5i_find_qpn_to_netdev_node(ipriv->qpn_htbl->buckets, qpn);
	अगर (!node)
		वापस शून्य;

	वापस node->netdev;
पूर्ण

अटल पूर्णांक mlx5i_pkey_खोलो(काष्ठा net_device *netdev);
अटल पूर्णांक mlx5i_pkey_बंद(काष्ठा net_device *netdev);
अटल पूर्णांक mlx5i_pkey_dev_init(काष्ठा net_device *dev);
अटल व्योम mlx5i_pkey_dev_cleanup(काष्ठा net_device *netdev);
अटल पूर्णांक mlx5i_pkey_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu);
अटल पूर्णांक mlx5i_pkey_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);

अटल स्थिर काष्ठा net_device_ops mlx5i_pkey_netdev_ops = अणु
	.nकरो_खोलो                = mlx5i_pkey_खोलो,
	.nकरो_stop                = mlx5i_pkey_बंद,
	.nकरो_init                = mlx5i_pkey_dev_init,
	.nकरो_get_stats64         = mlx5i_get_stats,
	.nकरो_uninit              = mlx5i_pkey_dev_cleanup,
	.nकरो_change_mtu          = mlx5i_pkey_change_mtu,
	.nकरो_करो_ioctl            = mlx5i_pkey_ioctl,
पूर्ण;

/* Child NDOs */
अटल पूर्णांक mlx5i_pkey_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(dev);
	काष्ठा mlx5i_priv *ipriv, *parent_ipriv;
	काष्ठा net_device *parent_dev;
	पूर्णांक parent_अगरindex;

	ipriv = priv->ppriv;

	/* Get QPN to netdevice hash table from parent */
	parent_अगरindex = dev->netdev_ops->nकरो_get_अगरlink(dev);
	parent_dev = dev_get_by_index(dev_net(dev), parent_अगरindex);
	अगर (!parent_dev) अणु
		mlx5_core_warn(priv->mdev, "failed to get parent device\n");
		वापस -EINVAL;
	पूर्ण

	parent_ipriv = netdev_priv(parent_dev);
	ipriv->qpn_htbl = parent_ipriv->qpn_htbl;
	dev_put(parent_dev);

	वापस mlx5i_dev_init(dev);
पूर्ण

अटल पूर्णांक mlx5i_pkey_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	वापस mlx5i_ioctl(dev, अगरr, cmd);
पूर्ण

अटल व्योम mlx5i_pkey_dev_cleanup(काष्ठा net_device *netdev)
अणु
	वापस mlx5i_dev_cleanup(netdev);
पूर्ण

अटल पूर्णांक mlx5i_pkey_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *epriv = mlx5i_epriv(netdev);
	काष्ठा mlx5i_priv *ipriv = epriv->ppriv;
	काष्ठा mlx5_core_dev *mdev = epriv->mdev;
	पूर्णांक err;

	mutex_lock(&epriv->state_lock);

	set_bit(MLX5E_STATE_OPENED, &epriv->state);

	err = mlx5i_init_underlay_qp(epriv);
	अगर (err) अणु
		mlx5_core_warn(mdev, "prepare child underlay qp state failed, %d\n", err);
		जाओ err_release_lock;
	पूर्ण

	err = mlx5_fs_add_rx_underlay_qpn(mdev, ipriv->qpn);
	अगर (err) अणु
		mlx5_core_warn(mdev, "attach child underlay qp to ft failed, %d\n", err);
		जाओ err_unपूर्णांक_underlay_qp;
	पूर्ण

	err = mlx5i_create_tis(mdev, ipriv->qpn, &epriv->tisn[0][0]);
	अगर (err) अणु
		mlx5_core_warn(mdev, "create child tis failed, %d\n", err);
		जाओ err_हटाओ_rx_uderlay_qp;
	पूर्ण

	err = mlx5e_खोलो_channels(epriv, &epriv->channels);
	अगर (err) अणु
		mlx5_core_warn(mdev, "opening child channels failed, %d\n", err);
		जाओ err_clear_state_खोलोed_flag;
	पूर्ण
	epriv->profile->update_rx(epriv);
	mlx5e_activate_priv_channels(epriv);
	mutex_unlock(&epriv->state_lock);

	वापस 0;

err_clear_state_खोलोed_flag:
	mlx5e_destroy_tis(mdev, epriv->tisn[0][0]);
err_हटाओ_rx_uderlay_qp:
	mlx5_fs_हटाओ_rx_underlay_qpn(mdev, ipriv->qpn);
err_unपूर्णांक_underlay_qp:
	mlx5i_uninit_underlay_qp(epriv);
err_release_lock:
	clear_bit(MLX5E_STATE_OPENED, &epriv->state);
	mutex_unlock(&epriv->state_lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5i_pkey_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(netdev);
	काष्ठा mlx5i_priv *ipriv = priv->ppriv;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	mutex_lock(&priv->state_lock);

	अगर (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		जाओ unlock;

	clear_bit(MLX5E_STATE_OPENED, &priv->state);

	netअगर_carrier_off(priv->netdev);
	mlx5_fs_हटाओ_rx_underlay_qpn(mdev, ipriv->qpn);
	mlx5i_uninit_underlay_qp(priv);
	mlx5e_deactivate_priv_channels(priv);
	mlx5e_बंद_channels(&priv->channels);
	mlx5e_destroy_tis(mdev, priv->tisn[0][0]);
unlock:
	mutex_unlock(&priv->state_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5i_pkey_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा mlx5e_priv *priv = mlx5i_epriv(netdev);

	mutex_lock(&priv->state_lock);
	netdev->mtu = new_mtu;
	mutex_unlock(&priv->state_lock);

	वापस 0;
पूर्ण

/* Called directly after IPoIB netdevice was created to initialize SW काष्ठाs */
अटल पूर्णांक mlx5i_pkey_init(काष्ठा mlx5_core_dev *mdev,
			   काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5e_priv *priv  = mlx5i_epriv(netdev);
	पूर्णांक err;

	err = mlx5i_init(mdev, netdev);
	अगर (err)
		वापस err;

	/* Override parent nकरो */
	netdev->netdev_ops = &mlx5i_pkey_netdev_ops;

	/* Set child limited ethtool support */
	netdev->ethtool_ops = &mlx5i_pkey_ethtool_ops;

	/* Use dummy rqs */
	priv->channels.params.log_rq_mtu_frames = MLX5E_PARAMS_MINIMUM_LOG_RQ_SIZE;

	वापस 0;
पूर्ण

/* Called directly beक्रमe IPoIB netdevice is destroyed to cleanup SW काष्ठाs */
अटल व्योम mlx5i_pkey_cleanup(काष्ठा mlx5e_priv *priv)
अणु
	mlx5i_cleanup(priv);
पूर्ण

अटल पूर्णांक mlx5i_pkey_init_tx(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक err;

	err = mlx5i_create_underlay_qp(priv);
	अगर (err)
		mlx5_core_warn(priv->mdev, "create child underlay QP failed, %d\n", err);

	वापस err;
पूर्ण

अटल व्योम mlx5i_pkey_cleanup_tx(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5i_priv *ipriv = priv->ppriv;

	mlx5i_destroy_underlay_qp(priv->mdev, ipriv->qpn);
पूर्ण

अटल पूर्णांक mlx5i_pkey_init_rx(काष्ठा mlx5e_priv *priv)
अणु
	/* Since the rx resources are shared between child and parent, the
	 * parent पूर्णांकerface is taking care of rx resource allocation and init
	 */
	वापस 0;
पूर्ण

अटल व्योम mlx5i_pkey_cleanup_rx(काष्ठा mlx5e_priv *priv)
अणु
	/* Since the rx resources are shared between child and parent, the
	 * parent पूर्णांकerface is taking care of rx resource मुक्त and de-init
	 */
पूर्ण

अटल स्थिर काष्ठा mlx5e_profile mlx5i_pkey_nic_profile = अणु
	.init		   = mlx5i_pkey_init,
	.cleanup	   = mlx5i_pkey_cleanup,
	.init_tx	   = mlx5i_pkey_init_tx,
	.cleanup_tx	   = mlx5i_pkey_cleanup_tx,
	.init_rx	   = mlx5i_pkey_init_rx,
	.cleanup_rx	   = mlx5i_pkey_cleanup_rx,
	.enable		   = शून्य,
	.disable	   = शून्य,
	.update_rx	   = mlx5i_update_nic_rx,
	.update_stats	   = शून्य,
	.rx_handlers       = &mlx5i_rx_handlers,
	.max_tc		   = MLX5I_MAX_NUM_TC,
	.rq_groups	   = MLX5E_NUM_RQ_GROUPS(REGULAR),
	.rx_ptp_support	   = false,
पूर्ण;

स्थिर काष्ठा mlx5e_profile *mlx5i_pkey_get_profile(व्योम)
अणु
	वापस &mlx5i_pkey_nic_profile;
पूर्ण
