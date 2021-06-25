<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश "core.h"

#अगर_घोषित CONFIG_NL80211_TESTMODE

bool ath11k_पंचांग_event_wmi(काष्ठा ath11k *ar, u32 cmd_id, काष्ठा sk_buff *skb);
पूर्णांक ath11k_पंचांग_cmd(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  व्योम *data, पूर्णांक len);

#अन्यथा

अटल अंतरभूत bool ath11k_पंचांग_event_wmi(काष्ठा ath11k *ar, u32 cmd_id,
				       काष्ठा sk_buff *skb)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_पंचांग_cmd(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				व्योम *data, पूर्णांक len)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर
