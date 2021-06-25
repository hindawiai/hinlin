<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2020 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ATH11K_DEBUGFS_STA_H_
#घोषणा _ATH11K_DEBUGFS_STA_H_

#समावेश <net/mac80211.h>

#समावेश "core.h"
#समावेश "hal_tx.h"

#अगर_घोषित CONFIG_ATH11K_DEBUGFS

व्योम ath11k_debugfs_sta_op_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_sta *sta, काष्ठा dentry *dir);
व्योम ath11k_debugfs_sta_add_tx_stats(काष्ठा ath11k_sta *arsta,
				     काष्ठा ath11k_per_peer_tx_stats *peer_stats,
				     u8 legacy_rate_idx);
व्योम ath11k_debugfs_sta_update_txcompl(काष्ठा ath11k *ar,
				       काष्ठा sk_buff *msdu,
				       काष्ठा hal_tx_status *ts);

#अन्यथा /* CONFIG_ATH11K_DEBUGFS */

#घोषणा ath11k_debugfs_sta_op_add शून्य

अटल अंतरभूत व्योम
ath11k_debugfs_sta_add_tx_stats(काष्ठा ath11k_sta *arsta,
				काष्ठा ath11k_per_peer_tx_stats *peer_stats,
				u8 legacy_rate_idx)
अणु
पूर्ण

अटल अंतरभूत व्योम ath11k_debugfs_sta_update_txcompl(काष्ठा ath11k *ar,
						     काष्ठा sk_buff *msdu,
						     काष्ठा hal_tx_status *ts)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_ATH11K_DEBUGFS */

#पूर्ण_अगर /* _ATH11K_DEBUGFS_STA_H_ */
