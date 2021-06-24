<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 */

#समावेश "core.h"

#अगर_घोषित CONFIG_NL80211_TESTMODE

व्योम ath10k_tesपंचांगode_destroy(काष्ठा ath10k *ar);

bool ath10k_पंचांग_event_wmi(काष्ठा ath10k *ar, u32 cmd_id, काष्ठा sk_buff *skb);
पूर्णांक ath10k_पंचांग_cmd(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  व्योम *data, पूर्णांक len);

#अन्यथा

अटल अंतरभूत व्योम ath10k_tesपंचांगode_destroy(काष्ठा ath10k *ar)
अणु
पूर्ण

अटल अंतरभूत bool ath10k_पंचांग_event_wmi(काष्ठा ath10k *ar, u32 cmd_id,
				       काष्ठा sk_buff *skb)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_पंचांग_cmd(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				व्योम *data, पूर्णांक len)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर
