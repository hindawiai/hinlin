<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * DebugFS code क्रम ST-Ericsson CW1200 mac80211 driver
 *
 * Copyright (c) 2011, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#अगर_अघोषित CW1200_DEBUG_H_INCLUDED
#घोषणा CW1200_DEBUG_H_INCLUDED

काष्ठा cw1200_debug_priv अणु
	काष्ठा dentry *debugfs_phy;
	पूर्णांक tx;
	पूर्णांक tx_agg;
	पूर्णांक rx;
	पूर्णांक rx_agg;
	पूर्णांक tx_multi;
	पूर्णांक tx_multi_frames;
	पूर्णांक tx_cache_miss;
	पूर्णांक tx_align;
	पूर्णांक tx_ttl;
	पूर्णांक tx_burst;
	पूर्णांक ba_cnt;
	पूर्णांक ba_acc;
	पूर्णांक ba_cnt_rx;
	पूर्णांक ba_acc_rx;
पूर्ण;

पूर्णांक cw1200_debug_init(काष्ठा cw1200_common *priv);
व्योम cw1200_debug_release(काष्ठा cw1200_common *priv);

अटल अंतरभूत व्योम cw1200_debug_txed(काष्ठा cw1200_common *priv)
अणु
	++priv->debug->tx;
पूर्ण

अटल अंतरभूत व्योम cw1200_debug_txed_agg(काष्ठा cw1200_common *priv)
अणु
	++priv->debug->tx_agg;
पूर्ण

अटल अंतरभूत व्योम cw1200_debug_txed_multi(काष्ठा cw1200_common *priv,
					   पूर्णांक count)
अणु
	++priv->debug->tx_multi;
	priv->debug->tx_multi_frames += count;
पूर्ण

अटल अंतरभूत व्योम cw1200_debug_rxed(काष्ठा cw1200_common *priv)
अणु
	++priv->debug->rx;
पूर्ण

अटल अंतरभूत व्योम cw1200_debug_rxed_agg(काष्ठा cw1200_common *priv)
अणु
	++priv->debug->rx_agg;
पूर्ण

अटल अंतरभूत व्योम cw1200_debug_tx_cache_miss(काष्ठा cw1200_common *priv)
अणु
	++priv->debug->tx_cache_miss;
पूर्ण

अटल अंतरभूत व्योम cw1200_debug_tx_align(काष्ठा cw1200_common *priv)
अणु
	++priv->debug->tx_align;
पूर्ण

अटल अंतरभूत व्योम cw1200_debug_tx_ttl(काष्ठा cw1200_common *priv)
अणु
	++priv->debug->tx_ttl;
पूर्ण

अटल अंतरभूत व्योम cw1200_debug_tx_burst(काष्ठा cw1200_common *priv)
अणु
	++priv->debug->tx_burst;
पूर्ण

अटल अंतरभूत व्योम cw1200_debug_ba(काष्ठा cw1200_common *priv,
				   पूर्णांक ba_cnt, पूर्णांक ba_acc,
				   पूर्णांक ba_cnt_rx, पूर्णांक ba_acc_rx)
अणु
	priv->debug->ba_cnt = ba_cnt;
	priv->debug->ba_acc = ba_acc;
	priv->debug->ba_cnt_rx = ba_cnt_rx;
	priv->debug->ba_acc_rx = ba_acc_rx;
पूर्ण

#पूर्ण_अगर /* CW1200_DEBUG_H_INCLUDED */
