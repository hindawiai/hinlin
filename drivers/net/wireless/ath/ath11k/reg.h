<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_REG_H
#घोषणा ATH11K_REG_H

#समावेश <linux/kernel.h>
#समावेश <net/regulatory.h>

काष्ठा ath11k_base;
काष्ठा ath11k;

/* DFS regकरोमुख्यs supported by Firmware */
क्रमागत ath11k_dfs_region अणु
	ATH11K_DFS_REG_UNSET,
	ATH11K_DFS_REG_FCC,
	ATH11K_DFS_REG_ETSI,
	ATH11K_DFS_REG_MKK,
	ATH11K_DFS_REG_CN,
	ATH11K_DFS_REG_KR,
	ATH11K_DFS_REG_MKK_N,
	ATH11K_DFS_REG_UNDEF,
पूर्ण;

/* ATH11K Regulatory API's */
व्योम ath11k_reg_init(काष्ठा ath11k *ar);
व्योम ath11k_reg_मुक्त(काष्ठा ath11k_base *ab);
व्योम ath11k_regd_update_work(काष्ठा work_काष्ठा *work);
काष्ठा ieee80211_regकरोमुख्य *
ath11k_reg_build_regd(काष्ठा ath11k_base *ab,
		      काष्ठा cur_regulatory_info *reg_info, bool पूर्णांकersect);
पूर्णांक ath11k_regd_update(काष्ठा ath11k *ar, bool init);
पूर्णांक ath11k_reg_update_chan_list(काष्ठा ath11k *ar);
#पूर्ण_अगर
