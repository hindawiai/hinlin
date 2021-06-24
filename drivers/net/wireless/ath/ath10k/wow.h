<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2015,2017 Qualcomm Atheros, Inc.
 */
#अगर_अघोषित _WOW_H_
#घोषणा _WOW_H_

काष्ठा ath10k_wow अणु
	u32 max_num_patterns;
	काष्ठा completion wakeup_completed;
	काष्ठा wiphy_wowlan_support wowlan_support;
पूर्ण;

#अगर_घोषित CONFIG_PM

पूर्णांक ath10k_wow_init(काष्ठा ath10k *ar);
पूर्णांक ath10k_wow_op_suspend(काष्ठा ieee80211_hw *hw,
			  काष्ठा cfg80211_wowlan *wowlan);
पूर्णांक ath10k_wow_op_resume(काष्ठा ieee80211_hw *hw);
व्योम ath10k_wow_op_set_wakeup(काष्ठा ieee80211_hw *hw, bool enabled);

#अन्यथा

अटल अंतरभूत पूर्णांक ath10k_wow_init(काष्ठा ath10k *ar)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */
#पूर्ण_अगर /* _WOW_H_ */
