<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Datapath पूर्णांकerface क्रम ST-Ericsson CW1200 mac80211 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#अगर_अघोषित CW1200_TXRX_H
#घोषणा CW1200_TXRX_H

#समावेश <linux/list.h>

/* बाह्य */ काष्ठा ieee80211_hw;
/* बाह्य */ काष्ठा sk_buff;
/* बाह्य */ काष्ठा wsm_tx;
/* बाह्य */ काष्ठा wsm_rx;
/* बाह्य */ काष्ठा wsm_tx_confirm;
/* बाह्य */ काष्ठा cw1200_txpriv;

काष्ठा tx_policy अणु
	जोड़ अणु
		__le32 tbl[3];
		u8 raw[12];
	पूर्ण;
	u8  defined;
	u8  usage_count;
	u8  retry_count;
	u8  uploaded;
पूर्ण;

काष्ठा tx_policy_cache_entry अणु
	काष्ठा tx_policy policy;
	काष्ठा list_head link;
पूर्ण;

#घोषणा TX_POLICY_CACHE_SIZE	(8)
काष्ठा tx_policy_cache अणु
	काष्ठा tx_policy_cache_entry cache[TX_POLICY_CACHE_SIZE];
	काष्ठा list_head used;
	काष्ठा list_head मुक्त;
	spinlock_t lock; /* Protect policy cache */
पूर्ण;

/* ******************************************************************** */
/* TX policy cache							*/
/* Intention of TX policy cache is an overcomplicated WSM API.
 * Device करोes not accept per-PDU tx retry sequence.
 * It uses "tx retry policy id" instead, so driver code has to sync
 * linux tx retry sequences with a retry policy table in the device.
 */
व्योम tx_policy_init(काष्ठा cw1200_common *priv);
व्योम tx_policy_upload_work(काष्ठा work_काष्ठा *work);
व्योम tx_policy_clean(काष्ठा cw1200_common *priv);

/* ******************************************************************** */
/* TX implementation							*/

u32 cw1200_rate_mask_to_wsm(काष्ठा cw1200_common *priv,
			       u32 rates);
व्योम cw1200_tx(काष्ठा ieee80211_hw *dev,
	       काष्ठा ieee80211_tx_control *control,
	       काष्ठा sk_buff *skb);
व्योम cw1200_skb_dtor(काष्ठा cw1200_common *priv,
		     काष्ठा sk_buff *skb,
		     स्थिर काष्ठा cw1200_txpriv *txpriv);

/* ******************************************************************** */
/* WSM callbacks							*/

व्योम cw1200_tx_confirm_cb(काष्ठा cw1200_common *priv,
			  पूर्णांक link_id,
			  काष्ठा wsm_tx_confirm *arg);
व्योम cw1200_rx_cb(काष्ठा cw1200_common *priv,
		  काष्ठा wsm_rx *arg,
		  पूर्णांक link_id,
		  काष्ठा sk_buff **skb_p);

/* ******************************************************************** */
/* Timeout								*/

व्योम cw1200_tx_समयout(काष्ठा work_काष्ठा *work);

/* ******************************************************************** */
/* Security								*/
पूर्णांक cw1200_alloc_key(काष्ठा cw1200_common *priv);
व्योम cw1200_मुक्त_key(काष्ठा cw1200_common *priv, पूर्णांक idx);
व्योम cw1200_मुक्त_keys(काष्ठा cw1200_common *priv);
पूर्णांक cw1200_upload_keys(काष्ठा cw1200_common *priv);

/* ******************************************************************** */
/* Workaround क्रम WFD test हाल 6.1.10					*/
व्योम cw1200_link_id_reset(काष्ठा work_काष्ठा *work);

#घोषणा CW1200_LINK_ID_GC_TIMEOUT ((अचिन्हित दीर्घ)(10 * HZ))

पूर्णांक cw1200_find_link_id(काष्ठा cw1200_common *priv, स्थिर u8 *mac);
पूर्णांक cw1200_alloc_link_id(काष्ठा cw1200_common *priv, स्थिर u8 *mac);
व्योम cw1200_link_id_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_link_id_gc_work(काष्ठा work_काष्ठा *work);


#पूर्ण_अगर /* CW1200_TXRX_H */
