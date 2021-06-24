<शैली गुरु>
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
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
 *
 */

#समावेश <linux/netdevice.h>
#समावेश <net/ipv6.h>
#समावेश "en_accel/tls.h"
#समावेश "accel/tls.h"

अटल व्योम mlx5e_tls_set_ipv4_flow(व्योम *flow, काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);

	MLX5_SET(tls_flow, flow, ipv6, 0);
	स_नकल(MLX5_ADDR_OF(tls_flow, flow, dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
	       &inet->inet_daddr, MLX5_FLD_SZ_BYTES(ipv4_layout, ipv4));
	स_नकल(MLX5_ADDR_OF(tls_flow, flow, src_ipv4_src_ipv6.ipv4_layout.ipv4),
	       &inet->inet_rcv_saddr, MLX5_FLD_SZ_BYTES(ipv4_layout, ipv4));
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल व्योम mlx5e_tls_set_ipv6_flow(व्योम *flow, काष्ठा sock *sk)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);

	MLX5_SET(tls_flow, flow, ipv6, 1);
	स_नकल(MLX5_ADDR_OF(tls_flow, flow, dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
	       &sk->sk_v6_daddr, MLX5_FLD_SZ_BYTES(ipv6_layout, ipv6));
	स_नकल(MLX5_ADDR_OF(tls_flow, flow, src_ipv4_src_ipv6.ipv6_layout.ipv6),
	       &np->saddr, MLX5_FLD_SZ_BYTES(ipv6_layout, ipv6));
पूर्ण
#पूर्ण_अगर

अटल व्योम mlx5e_tls_set_flow_tcp_ports(व्योम *flow, काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);

	स_नकल(MLX5_ADDR_OF(tls_flow, flow, src_port), &inet->inet_sport,
	       MLX5_FLD_SZ_BYTES(tls_flow, src_port));
	स_नकल(MLX5_ADDR_OF(tls_flow, flow, dst_port), &inet->inet_dport,
	       MLX5_FLD_SZ_BYTES(tls_flow, dst_port));
पूर्ण

अटल पूर्णांक mlx5e_tls_set_flow(व्योम *flow, काष्ठा sock *sk, u32 caps)
अणु
	चयन (sk->sk_family) अणु
	हाल AF_INET:
		mlx5e_tls_set_ipv4_flow(flow, sk);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		अगर (!sk->sk_ipv6only &&
		    ipv6_addr_type(&sk->sk_v6_daddr) == IPV6_ADDR_MAPPED) अणु
			mlx5e_tls_set_ipv4_flow(flow, sk);
			अवरोध;
		पूर्ण
		अगर (!(caps & MLX5_ACCEL_TLS_IPV6))
			जाओ error_out;

		mlx5e_tls_set_ipv6_flow(flow, sk);
		अवरोध;
#पूर्ण_अगर
	शेष:
		जाओ error_out;
	पूर्ण

	mlx5e_tls_set_flow_tcp_ports(flow, sk);
	वापस 0;
error_out:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mlx5e_tls_add(काष्ठा net_device *netdev, काष्ठा sock *sk,
			 क्रमागत tls_offload_ctx_dir direction,
			 काष्ठा tls_crypto_info *crypto_info,
			 u32 start_offload_tcp_sn)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	u32 caps = mlx5_accel_tls_device_caps(mdev);
	पूर्णांक ret = -ENOMEM;
	व्योम *flow;
	u32 swid;

	flow = kzalloc(MLX5_ST_SZ_BYTES(tls_flow), GFP_KERNEL);
	अगर (!flow)
		वापस ret;

	ret = mlx5e_tls_set_flow(flow, sk, caps);
	अगर (ret)
		जाओ मुक्त_flow;

	ret = mlx5_accel_tls_add_flow(mdev, flow, crypto_info,
				      start_offload_tcp_sn, &swid,
				      direction == TLS_OFFLOAD_CTX_सूची_TX);
	अगर (ret < 0)
		जाओ मुक्त_flow;

	अगर (direction == TLS_OFFLOAD_CTX_सूची_TX) अणु
		काष्ठा mlx5e_tls_offload_context_tx *tx_ctx =
		    mlx5e_get_tls_tx_context(tls_ctx);

		tx_ctx->swid = htonl(swid);
		tx_ctx->expected_seq = start_offload_tcp_sn;
	पूर्ण अन्यथा अणु
		काष्ठा mlx5e_tls_offload_context_rx *rx_ctx =
		    mlx5e_get_tls_rx_context(tls_ctx);

		rx_ctx->handle = htonl(swid);
	पूर्ण

	वापस 0;
मुक्त_flow:
	kमुक्त(flow);
	वापस ret;
पूर्ण

अटल व्योम mlx5e_tls_del(काष्ठा net_device *netdev,
			  काष्ठा tls_context *tls_ctx,
			  क्रमागत tls_offload_ctx_dir direction)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	अचिन्हित पूर्णांक handle;

	handle = ntohl((direction == TLS_OFFLOAD_CTX_सूची_TX) ?
		       mlx5e_get_tls_tx_context(tls_ctx)->swid :
		       mlx5e_get_tls_rx_context(tls_ctx)->handle);

	mlx5_accel_tls_del_flow(priv->mdev, handle,
				direction == TLS_OFFLOAD_CTX_सूची_TX);
पूर्ण

अटल पूर्णांक mlx5e_tls_resync(काष्ठा net_device *netdev, काष्ठा sock *sk,
			    u32 seq, u8 *rcd_sn_data,
			    क्रमागत tls_offload_ctx_dir direction)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा mlx5e_priv *priv = netdev_priv(netdev);
	काष्ठा mlx5e_tls_offload_context_rx *rx_ctx;
	__be64 rcd_sn = *(__be64 *)rcd_sn_data;

	अगर (WARN_ON_ONCE(direction != TLS_OFFLOAD_CTX_सूची_RX))
		वापस -EINVAL;
	rx_ctx = mlx5e_get_tls_rx_context(tls_ctx);

	netdev_info(netdev, "resyncing seq %d rcd %lld\n", seq,
		    be64_to_cpu(rcd_sn));
	mlx5_accel_tls_resync_rx(priv->mdev, rx_ctx->handle, seq, rcd_sn);
	atomic64_inc(&priv->tls->sw_stats.rx_tls_resync_reply);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tlsdev_ops mlx5e_tls_ops = अणु
	.tls_dev_add = mlx5e_tls_add,
	.tls_dev_del = mlx5e_tls_del,
	.tls_dev_resync = mlx5e_tls_resync,
पूर्ण;

व्योम mlx5e_tls_build_netdev(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा net_device *netdev = priv->netdev;
	u32 caps;

	अगर (mlx5_accel_is_ktls_device(priv->mdev)) अणु
		mlx5e_ktls_build_netdev(priv);
		वापस;
	पूर्ण

	/* FPGA */
	अगर (!mlx5_accel_is_tls_device(priv->mdev))
		वापस;

	caps = mlx5_accel_tls_device_caps(priv->mdev);
	अगर (caps & MLX5_ACCEL_TLS_TX) अणु
		netdev->features          |= NETIF_F_HW_TLS_TX;
		netdev->hw_features       |= NETIF_F_HW_TLS_TX;
	पूर्ण

	अगर (caps & MLX5_ACCEL_TLS_RX) अणु
		netdev->features          |= NETIF_F_HW_TLS_RX;
		netdev->hw_features       |= NETIF_F_HW_TLS_RX;
	पूर्ण

	अगर (!(caps & MLX5_ACCEL_TLS_LRO)) अणु
		netdev->features          &= ~NETIF_F_LRO;
		netdev->hw_features       &= ~NETIF_F_LRO;
	पूर्ण

	netdev->tlsdev_ops = &mlx5e_tls_ops;
पूर्ण

पूर्णांक mlx5e_tls_init(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_tls *tls;

	अगर (!mlx5_accel_is_tls_device(priv->mdev))
		वापस 0;

	tls = kzalloc(माप(*tls), GFP_KERNEL);
	अगर (!tls)
		वापस -ENOMEM;

	priv->tls = tls;
	वापस 0;
पूर्ण

व्योम mlx5e_tls_cleanup(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_tls *tls = priv->tls;

	अगर (!tls)
		वापस;

	kमुक्त(tls);
	priv->tls = शून्य;
पूर्ण
