<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2019 Mellanox Technologies.

#समावेश "en.h"
#समावेश "en_accel/tls.h"
#समावेश "en_accel/ktls.h"
#समावेश "en_accel/ktls_utils.h"
#समावेश "en_accel/fs_tcp.h"

अटल पूर्णांक mlx5e_ktls_add(काष्ठा net_device *netdev, काष्ठा sock *sk,
			  क्रमागत tls_offload_ctx_dir direction,
			  काष्ठा tls_crypto_info *crypto_info,
			  u32 start_offload_tcp_sn)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	पूर्णांक err;

	अगर (WARN_ON(!mlx5e_ktls_type_check(mdev, crypto_info)))
		वापस -EOPNOTSUPP;

	अगर (direction == TLS_OFFLOAD_CTX_सूची_TX)
		err = mlx5e_ktls_add_tx(netdev, sk, crypto_info, start_offload_tcp_sn);
	अन्यथा
		err = mlx5e_ktls_add_rx(netdev, sk, crypto_info, start_offload_tcp_sn);

	वापस err;
पूर्ण

अटल व्योम mlx5e_ktls_del(काष्ठा net_device *netdev,
			   काष्ठा tls_context *tls_ctx,
			   क्रमागत tls_offload_ctx_dir direction)
अणु
	अगर (direction == TLS_OFFLOAD_CTX_सूची_TX)
		mlx5e_ktls_del_tx(netdev, tls_ctx);
	अन्यथा
		mlx5e_ktls_del_rx(netdev, tls_ctx);
पूर्ण

अटल पूर्णांक mlx5e_ktls_resync(काष्ठा net_device *netdev,
			     काष्ठा sock *sk, u32 seq, u8 *rcd_sn,
			     क्रमागत tls_offload_ctx_dir direction)
अणु
	अगर (unlikely(direction != TLS_OFFLOAD_CTX_सूची_RX))
		वापस -EOPNOTSUPP;

	mlx5e_ktls_rx_resync(netdev, sk, seq, rcd_sn);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tlsdev_ops mlx5e_ktls_ops = अणु
	.tls_dev_add = mlx5e_ktls_add,
	.tls_dev_del = mlx5e_ktls_del,
	.tls_dev_resync = mlx5e_ktls_resync,
पूर्ण;

व्योम mlx5e_ktls_build_netdev(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा mlx5_core_dev *mdev = priv->mdev;

	अगर (mlx5_accel_is_ktls_tx(mdev)) अणु
		netdev->hw_features |= NETIF_F_HW_TLS_TX;
		netdev->features    |= NETIF_F_HW_TLS_TX;
	पूर्ण

	अगर (mlx5_accel_is_ktls_rx(mdev))
		netdev->hw_features |= NETIF_F_HW_TLS_RX;

	netdev->tlsdev_ops = &mlx5e_ktls_ops;
पूर्ण

पूर्णांक mlx5e_ktls_set_feature_rx(काष्ठा net_device *netdev, bool enable)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	पूर्णांक err = 0;

	mutex_lock(&priv->state_lock);
	अगर (enable)
		err = mlx5e_accel_fs_tcp_create(priv);
	अन्यथा
		mlx5e_accel_fs_tcp_destroy(priv);
	mutex_unlock(&priv->state_lock);

	वापस err;
पूर्ण

पूर्णांक mlx5e_ktls_init_rx(काष्ठा mlx5e_priv *priv)
अणु
	पूर्णांक err;

	अगर (!mlx5_accel_is_ktls_rx(priv->mdev))
		वापस 0;

	priv->tls->rx_wq = create_singlethपढ़ो_workqueue("mlx5e_tls_rx");
	अगर (!priv->tls->rx_wq)
		वापस -ENOMEM;

	अगर (priv->netdev->features & NETIF_F_HW_TLS_RX) अणु
		err = mlx5e_accel_fs_tcp_create(priv);
		अगर (err) अणु
			destroy_workqueue(priv->tls->rx_wq);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम mlx5e_ktls_cleanup_rx(काष्ठा mlx5e_priv *priv)
अणु
	अगर (!mlx5_accel_is_ktls_rx(priv->mdev))
		वापस;

	अगर (priv->netdev->features & NETIF_F_HW_TLS_RX)
		mlx5e_accel_fs_tcp_destroy(priv);

	destroy_workqueue(priv->tls->rx_wq);
पूर्ण
