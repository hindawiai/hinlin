<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2020 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/delay.h>

#समावेश "mac.h"
#समावेश "core.h"
#समावेश "hif.h"
#समावेश "debug.h"
#समावेश "wmi.h"
#समावेश "wow.h"

पूर्णांक ath11k_wow_enable(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k *ar = ath11k_ab_to_ar(ab, 0);
	पूर्णांक i, ret;

	clear_bit(ATH11K_FLAG_HTC_SUSPEND_COMPLETE, &ab->dev_flags);

	क्रम (i = 0; i < ATH11K_WOW_RETRY_NUM; i++) अणु
		reinit_completion(&ab->htc_suspend);

		ret = ath11k_wmi_wow_enable(ar);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to issue wow enable: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = रुको_क्रम_completion_समयout(&ab->htc_suspend, 3 * HZ);
		अगर (ret == 0) अणु
			ath11k_warn(ab,
				    "timed out while waiting for htc suspend completion\n");
			वापस -ETIMEDOUT;
		पूर्ण

		अगर (test_bit(ATH11K_FLAG_HTC_SUSPEND_COMPLETE, &ab->dev_flags))
			/* success, suspend complete received */
			वापस 0;

		ath11k_warn(ab, "htc suspend not complete, retrying (try %d)\n",
			    i);
		msleep(ATH11K_WOW_RETRY_WAIT_MS);
	पूर्ण

	ath11k_warn(ab, "htc suspend not complete, failing after %d tries\n", i);

	वापस -ETIMEDOUT;
पूर्ण

पूर्णांक ath11k_wow_wakeup(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k *ar = ath11k_ab_to_ar(ab, 0);
	पूर्णांक ret;

	reinit_completion(&ab->wow.wakeup_completed);

	ret = ath11k_wmi_wow_host_wakeup_ind(ar);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to send wow wakeup indication: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&ab->wow.wakeup_completed, 3 * HZ);
	अगर (ret == 0) अणु
		ath11k_warn(ab, "timed out while waiting for wow wakeup completion\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण
