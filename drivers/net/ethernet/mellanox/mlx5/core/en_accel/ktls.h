<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5E_KTLS_H__
#घोषणा __MLX5E_KTLS_H__

#समावेश "en.h"

#अगर_घोषित CONFIG_MLX5_EN_TLS

व्योम mlx5e_ktls_build_netdev(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_ktls_init_rx(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_ktls_cleanup_rx(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_ktls_set_feature_rx(काष्ठा net_device *netdev, bool enable);
काष्ठा mlx5e_ktls_resync_resp *
mlx5e_ktls_rx_resync_create_resp_list(व्योम);
व्योम mlx5e_ktls_rx_resync_destroy_resp_list(काष्ठा mlx5e_ktls_resync_resp *resp_list);
#अन्यथा

अटल अंतरभूत व्योम mlx5e_ktls_build_netdev(काष्ठा mlx5e_priv *priv)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mlx5e_ktls_init_rx(काष्ठा mlx5e_priv *priv)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlx5e_ktls_cleanup_rx(काष्ठा mlx5e_priv *priv)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mlx5e_ktls_set_feature_rx(काष्ठा net_device *netdev, bool enable)
अणु
	netdev_warn(netdev, "kTLS is not supported\n");
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा mlx5e_ktls_resync_resp *
mlx5e_ktls_rx_resync_create_resp_list(व्योम)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम
mlx5e_ktls_rx_resync_destroy_resp_list(काष्ठा mlx5e_ktls_resync_resp *resp_list) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MLX5E_TLS_H__ */
