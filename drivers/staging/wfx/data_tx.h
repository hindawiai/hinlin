<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Datapath implementation.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#अगर_अघोषित WFX_DATA_TX_H
#घोषणा WFX_DATA_TX_H

#समावेश <linux/list.h>
#समावेश <net/mac80211.h>

#समावेश "hif_api_cmd.h"
#समावेश "hif_api_mib.h"

काष्ठा wfx_tx_priv;
काष्ठा wfx_dev;
काष्ठा wfx_vअगर;

काष्ठा tx_policy अणु
	काष्ठा list_head link;
	पूर्णांक usage_count;
	u8 rates[12];
	bool uploaded;
पूर्ण;

काष्ठा tx_policy_cache अणु
	काष्ठा tx_policy cache[HIF_TX_RETRY_POLICY_MAX];
	// FIXME: use a trees and drop hash from tx_policy
	काष्ठा list_head used;
	काष्ठा list_head मुक्त;
	spinlock_t lock;
पूर्ण;

काष्ठा wfx_tx_priv अणु
	kसमय_प्रकार xmit_बारtamp;
	अचिन्हित अक्षर icv_size;
पूर्ण;

व्योम wfx_tx_policy_init(काष्ठा wfx_vअगर *wvअगर);
व्योम wfx_tx_policy_upload_work(काष्ठा work_काष्ठा *work);

व्योम wfx_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_tx_control *control,
	    काष्ठा sk_buff *skb);
व्योम wfx_tx_confirm_cb(काष्ठा wfx_dev *wdev, स्थिर काष्ठा hअगर_cnf_tx *arg);
व्योम wfx_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	       u32 queues, bool drop);

अटल अंतरभूत काष्ठा wfx_tx_priv *wfx_skb_tx_priv(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *tx_info;

	अगर (!skb)
		वापस शून्य;
	tx_info = IEEE80211_SKB_CB(skb);
	वापस (काष्ठा wfx_tx_priv *)tx_info->rate_driver_data;
पूर्ण

अटल अंतरभूत काष्ठा hअगर_req_tx *wfx_skb_txreq(काष्ठा sk_buff *skb)
अणु
	काष्ठा hअगर_msg *hअगर = (काष्ठा hअगर_msg *)skb->data;
	काष्ठा hअगर_req_tx *req = (काष्ठा hअगर_req_tx *)hअगर->body;

	वापस req;
पूर्ण

#पूर्ण_अगर /* WFX_DATA_TX_H */
