<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies. */

#अगर_अघोषित __MLX5_EN_PTP_H__
#घोषणा __MLX5_EN_PTP_H__

#समावेश "en.h"
#समावेश "en_stats.h"
#समावेश <linux/ptp_classअगरy.h>

काष्ठा mlx5e_ptpsq अणु
	काष्ठा mlx5e_txqsq       txqsq;
	काष्ठा mlx5e_cq          ts_cq;
	u16                      skb_fअगरo_cc;
	u16                      skb_fअगरo_pc;
	काष्ठा mlx5e_skb_fअगरo    skb_fअगरo;
	काष्ठा mlx5e_ptp_cq_stats *cq_stats;
पूर्ण;

क्रमागत अणु
	MLX5E_PTP_STATE_TX,
	MLX5E_PTP_STATE_RX,
	MLX5E_PTP_STATE_NUM_STATES,
पूर्ण;

काष्ठा mlx5e_ptp अणु
	/* data path */
	काष्ठा mlx5e_ptpsq         ptpsq[MLX5E_MAX_NUM_TC];
	काष्ठा mlx5e_rq            rq;
	काष्ठा napi_काष्ठा         napi;
	काष्ठा device             *pdev;
	काष्ठा net_device         *netdev;
	__be32                     mkey_be;
	u8                         num_tc;
	u8                         lag_port;

	/* data path - accessed per napi poll */
	काष्ठा mlx5e_ch_stats     *stats;

	/* control */
	काष्ठा mlx5e_priv         *priv;
	काष्ठा mlx5_core_dev      *mdev;
	काष्ठा hwtstamp_config    *tstamp;
	DECLARE_BITMAP(state, MLX5E_PTP_STATE_NUM_STATES);
पूर्ण;

अटल अंतरभूत bool mlx5e_use_ptpsq(काष्ठा sk_buff *skb)
अणु
	काष्ठा flow_keys fk;

	अगर (!(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP))
		वापस false;

	अगर (!skb_flow_dissect_flow_keys(skb, &fk, 0))
		वापस false;

	अगर (fk.basic.n_proto == htons(ETH_P_1588))
		वापस true;

	अगर (fk.basic.n_proto != htons(ETH_P_IP) &&
	    fk.basic.n_proto != htons(ETH_P_IPV6))
		वापस false;

	वापस (fk.basic.ip_proto == IPPROTO_UDP &&
		fk.ports.dst == htons(PTP_EV_PORT));
पूर्ण

पूर्णांक mlx5e_ptp_खोलो(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_params *params,
		   u8 lag_port, काष्ठा mlx5e_ptp **cp);
व्योम mlx5e_ptp_बंद(काष्ठा mlx5e_ptp *c);
व्योम mlx5e_ptp_activate_channel(काष्ठा mlx5e_ptp *c);
व्योम mlx5e_ptp_deactivate_channel(काष्ठा mlx5e_ptp *c);
पूर्णांक mlx5e_ptp_get_rqn(काष्ठा mlx5e_ptp *c, u32 *rqn);
पूर्णांक mlx5e_ptp_alloc_rx_fs(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_ptp_मुक्त_rx_fs(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_ptp_rx_manage_fs(काष्ठा mlx5e_priv *priv, bool set);

क्रमागत अणु
	MLX5E_SKB_CB_CQE_HWTSTAMP  = BIT(0),
	MLX5E_SKB_CB_PORT_HWTSTAMP = BIT(1),
पूर्ण;

व्योम mlx5e_skb_cb_hwtstamp_handler(काष्ठा sk_buff *skb, पूर्णांक hwtstamp_type,
				   kसमय_प्रकार hwtstamp,
				   काष्ठा mlx5e_ptp_cq_stats *cq_stats);

व्योम mlx5e_skb_cb_hwtstamp_init(काष्ठा sk_buff *skb);
#पूर्ण_अगर /* __MLX5_EN_PTP_H__ */
