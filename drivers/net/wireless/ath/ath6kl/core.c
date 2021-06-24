<शैली गुरु>
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश "core.h"

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/export.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "debug.h"
#समावेश "hif-ops.h"
#समावेश "htc-ops.h"
#समावेश "cfg80211.h"

अचिन्हित पूर्णांक debug_mask;
अटल अचिन्हित पूर्णांक suspend_mode;
अटल अचिन्हित पूर्णांक wow_mode;
अटल अचिन्हित पूर्णांक uart_debug;
अटल अचिन्हित पूर्णांक uart_rate = 115200;
अटल अचिन्हित पूर्णांक ath6kl_p2p;
अटल अचिन्हित पूर्णांक tesपंचांगode;
अटल अचिन्हित पूर्णांक recovery_enable;
अटल अचिन्हित पूर्णांक heart_beat_poll;

module_param(debug_mask, uपूर्णांक, 0644);
module_param(suspend_mode, uपूर्णांक, 0644);
module_param(wow_mode, uपूर्णांक, 0644);
module_param(uart_debug, uपूर्णांक, 0644);
module_param(uart_rate, uपूर्णांक, 0644);
module_param(ath6kl_p2p, uपूर्णांक, 0644);
module_param(tesपंचांगode, uपूर्णांक, 0644);
module_param(recovery_enable, uपूर्णांक, 0644);
module_param(heart_beat_poll, uपूर्णांक, 0644);
MODULE_PARM_DESC(recovery_enable, "Enable recovery from firmware error");
MODULE_PARM_DESC(heart_beat_poll,
		 "Enable fw error detection periodic polling in msecs - Also set recovery_enable for this to be effective");


व्योम ath6kl_core_tx_complete(काष्ठा ath6kl *ar, काष्ठा sk_buff *skb)
अणु
	ath6kl_htc_tx_complete(ar, skb);
पूर्ण
EXPORT_SYMBOL(ath6kl_core_tx_complete);

व्योम ath6kl_core_rx_complete(काष्ठा ath6kl *ar, काष्ठा sk_buff *skb, u8 pipe)
अणु
	ath6kl_htc_rx_complete(ar, skb, pipe);
पूर्ण
EXPORT_SYMBOL(ath6kl_core_rx_complete);

पूर्णांक ath6kl_core_init(काष्ठा ath6kl *ar, क्रमागत ath6kl_htc_type htc_type)
अणु
	काष्ठा ath6kl_bmi_target_info targ_info;
	काष्ठा wireless_dev *wdev;
	पूर्णांक ret = 0, i;

	चयन (htc_type) अणु
	हाल ATH6KL_HTC_TYPE_MBOX:
		ath6kl_htc_mbox_attach(ar);
		अवरोध;
	हाल ATH6KL_HTC_TYPE_PIPE:
		ath6kl_htc_pipe_attach(ar);
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -ENOMEM;
	पूर्ण

	ar->ath6kl_wq = create_singlethपढ़ो_workqueue("ath6kl");
	अगर (!ar->ath6kl_wq)
		वापस -ENOMEM;

	ret = ath6kl_bmi_init(ar);
	अगर (ret)
		जाओ err_wq;

	/*
	 * Turn on घातer to get hardware (target) version and leave घातer
	 * on delibrately as we will boot the hardware anyway within few
	 * seconds.
	 */
	ret = ath6kl_hअगर_घातer_on(ar);
	अगर (ret)
		जाओ err_bmi_cleanup;

	ret = ath6kl_bmi_get_target_info(ar, &targ_info);
	अगर (ret)
		जाओ err_घातer_off;

	ar->version.target_ver = le32_to_cpu(targ_info.version);
	ar->target_type = le32_to_cpu(targ_info.type);
	ar->wiphy->hw_version = le32_to_cpu(targ_info.version);

	ret = ath6kl_init_hw_params(ar);
	अगर (ret)
		जाओ err_घातer_off;

	ar->htc_target = ath6kl_htc_create(ar);

	अगर (!ar->htc_target) अणु
		ret = -ENOMEM;
		जाओ err_घातer_off;
	पूर्ण

	ar->tesपंचांगode = tesपंचांगode;

	ret = ath6kl_init_fetch_firmwares(ar);
	अगर (ret)
		जाओ err_htc_cleanup;

	/* FIXME: we should मुक्त all firmwares in the error हालs below */

	/*
	 * Backwards compatibility support क्रम older ar6004 firmware images
	 * which करो not set these feature flags.
	 */
	अगर (ar->target_type == TARGET_TYPE_AR6004 &&
	    ar->fw_api <= 4) अणु
		__set_bit(ATH6KL_FW_CAPABILITY_64BIT_RATES,
			  ar->fw_capabilities);
		__set_bit(ATH6KL_FW_CAPABILITY_AP_INACTIVITY_MINS,
			  ar->fw_capabilities);

		अगर (ar->hw.id == AR6004_HW_1_3_VERSION)
			__set_bit(ATH6KL_FW_CAPABILITY_MAP_LP_ENDPOINT,
				  ar->fw_capabilities);
	पूर्ण

	/* Indicate that WMI is enabled (although not पढ़ोy yet) */
	set_bit(WMI_ENABLED, &ar->flag);
	ar->wmi = ath6kl_wmi_init(ar);
	अगर (!ar->wmi) अणु
		ath6kl_err("failed to initialize wmi\n");
		ret = -EIO;
		जाओ err_htc_cleanup;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_TRC, "%s: got wmi @ 0x%p.\n", __func__, ar->wmi);

	/* setup access class priority mappings */
	ar->ac_stream_pri_map[WMM_AC_BK] = 0; /* lowest  */
	ar->ac_stream_pri_map[WMM_AC_BE] = 1;
	ar->ac_stream_pri_map[WMM_AC_VI] = 2;
	ar->ac_stream_pri_map[WMM_AC_VO] = 3; /* highest */

	/* allocate some buffers that handle larger AMSDU frames */
	ath6kl_refill_amsdu_rxbufs(ar, ATH6KL_MAX_AMSDU_RX_BUFFERS);

	ath6kl_cookie_init(ar);

	ar->conf_flags = ATH6KL_CONF_IGNORE_ERP_BARKER |
			 ATH6KL_CONF_ENABLE_11N | ATH6KL_CONF_ENABLE_TX_BURST;

	अगर (suspend_mode &&
	    suspend_mode >= WLAN_POWER_STATE_CUT_PWR &&
	    suspend_mode <= WLAN_POWER_STATE_WOW)
		ar->suspend_mode = suspend_mode;
	अन्यथा
		ar->suspend_mode = 0;

	अगर (suspend_mode == WLAN_POWER_STATE_WOW &&
	    (wow_mode == WLAN_POWER_STATE_CUT_PWR ||
	     wow_mode == WLAN_POWER_STATE_DEEP_SLEEP))
		ar->wow_suspend_mode = wow_mode;
	अन्यथा
		ar->wow_suspend_mode = 0;

	अगर (uart_debug)
		ar->conf_flags |= ATH6KL_CONF_UART_DEBUG;
	ar->hw.uarttx_rate = uart_rate;

	set_bit(FIRST_BOOT, &ar->flag);

	ath6kl_debug_init(ar);

	ret = ath6kl_init_hw_start(ar);
	अगर (ret) अणु
		ath6kl_err("Failed to start hardware: %d\n", ret);
		जाओ err_rxbuf_cleanup;
	पूर्ण

	/* give our connected endpoपूर्णांकs some buffers */
	ath6kl_rx_refill(ar->htc_target, ar->ctrl_ep);
	ath6kl_rx_refill(ar->htc_target, ar->ac2ep_map[WMM_AC_BE]);

	ret = ath6kl_cfg80211_init(ar);
	अगर (ret)
		जाओ err_rxbuf_cleanup;

	ret = ath6kl_debug_init_fs(ar);
	अगर (ret) अणु
		wiphy_unरेजिस्टर(ar->wiphy);
		जाओ err_rxbuf_cleanup;
	पूर्ण

	क्रम (i = 0; i < ar->vअगर_max; i++)
		ar->avail_idx_map |= BIT(i);

	rtnl_lock();
	wiphy_lock(ar->wiphy);

	/* Add an initial station पूर्णांकerface */
	wdev = ath6kl_पूर्णांकerface_add(ar, "wlan%d", NET_NAME_ENUM,
				    NL80211_IFTYPE_STATION, 0, INFRA_NETWORK);

	wiphy_unlock(ar->wiphy);
	rtnl_unlock();

	अगर (!wdev) अणु
		ath6kl_err("Failed to instantiate a network device\n");
		ret = -ENOMEM;
		wiphy_unरेजिस्टर(ar->wiphy);
		जाओ err_rxbuf_cleanup;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_TRC, "%s: name=%s dev=0x%p, ar=0x%p\n",
		   __func__, wdev->netdev->name, wdev->netdev, ar);

	ar->fw_recovery.enable = !!recovery_enable;
	अगर (!ar->fw_recovery.enable)
		वापस ret;

	अगर (heart_beat_poll &&
	    test_bit(ATH6KL_FW_CAPABILITY_HEART_BEAT_POLL,
		     ar->fw_capabilities))
		ar->fw_recovery.hb_poll = heart_beat_poll;

	ath6kl_recovery_init(ar);

	वापस ret;

err_rxbuf_cleanup:
	ath6kl_debug_cleanup(ar);
	ath6kl_htc_flush_rx_buf(ar->htc_target);
	ath6kl_cleanup_amsdu_rxbufs(ar);
	ath6kl_wmi_shutकरोwn(ar->wmi);
	clear_bit(WMI_ENABLED, &ar->flag);
	ar->wmi = शून्य;
err_htc_cleanup:
	ath6kl_htc_cleanup(ar->htc_target);
err_घातer_off:
	ath6kl_hअगर_घातer_off(ar);
err_bmi_cleanup:
	ath6kl_bmi_cleanup(ar);
err_wq:
	destroy_workqueue(ar->ath6kl_wq);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ath6kl_core_init);

काष्ठा ath6kl *ath6kl_core_create(काष्ठा device *dev)
अणु
	काष्ठा ath6kl *ar;
	u8 ctr;

	ar = ath6kl_cfg80211_create();
	अगर (!ar)
		वापस शून्य;

	ar->p2p = !!ath6kl_p2p;
	ar->dev = dev;

	ar->vअगर_max = 1;

	ar->max_norm_अगरace = 1;

	spin_lock_init(&ar->lock);
	spin_lock_init(&ar->mcastpsq_lock);
	spin_lock_init(&ar->list_lock);

	init_रुकोqueue_head(&ar->event_wq);
	sema_init(&ar->sem, 1);

	INIT_LIST_HEAD(&ar->amsdu_rx_buffer_queue);
	INIT_LIST_HEAD(&ar->vअगर_list);

	clear_bit(WMI_ENABLED, &ar->flag);
	clear_bit(SKIP_SCAN, &ar->flag);
	clear_bit(DESTROY_IN_PROGRESS, &ar->flag);

	ar->tx_pwr = 0;
	ar->पूर्णांकra_bss = 1;
	ar->lrssi_roam_threshold = DEF_LRSSI_ROAM_THRESHOLD;

	ar->state = ATH6KL_STATE_OFF;

	स_रखो((u8 *)ar->sta_list, 0,
	       AP_MAX_NUM_STA * माप(काष्ठा ath6kl_sta));

	/* Init the PS queues */
	क्रम (ctr = 0; ctr < AP_MAX_NUM_STA; ctr++) अणु
		spin_lock_init(&ar->sta_list[ctr].psq_lock);
		skb_queue_head_init(&ar->sta_list[ctr].psq);
		skb_queue_head_init(&ar->sta_list[ctr].apsdq);
		ar->sta_list[ctr].mgmt_psq_len = 0;
		INIT_LIST_HEAD(&ar->sta_list[ctr].mgmt_psq);
		ar->sta_list[ctr].aggr_conn =
			kzalloc(माप(काष्ठा aggr_info_conn), GFP_KERNEL);
		अगर (!ar->sta_list[ctr].aggr_conn) अणु
			ath6kl_err("Failed to allocate memory for sta aggregation information\n");
			ath6kl_core_destroy(ar);
			वापस शून्य;
		पूर्ण
	पूर्ण

	skb_queue_head_init(&ar->mcastpsq);

	स_नकल(ar->ap_country_code, DEF_AP_COUNTRY_CODE, 3);

	वापस ar;
पूर्ण
EXPORT_SYMBOL(ath6kl_core_create);

व्योम ath6kl_core_cleanup(काष्ठा ath6kl *ar)
अणु
	ath6kl_hअगर_घातer_off(ar);

	ath6kl_recovery_cleanup(ar);

	destroy_workqueue(ar->ath6kl_wq);

	अगर (ar->htc_target)
		ath6kl_htc_cleanup(ar->htc_target);

	ath6kl_cookie_cleanup(ar);

	ath6kl_cleanup_amsdu_rxbufs(ar);

	ath6kl_bmi_cleanup(ar);

	ath6kl_debug_cleanup(ar);

	kमुक्त(ar->fw_board);
	kमुक्त(ar->fw_otp);
	vमुक्त(ar->fw);
	kमुक्त(ar->fw_patch);
	kमुक्त(ar->fw_testscript);

	ath6kl_cfg80211_cleanup(ar);
पूर्ण
EXPORT_SYMBOL(ath6kl_core_cleanup);

व्योम ath6kl_core_destroy(काष्ठा ath6kl *ar)
अणु
	ath6kl_cfg80211_destroy(ar);
पूर्ण
EXPORT_SYMBOL(ath6kl_core_destroy);

MODULE_AUTHOR("Qualcomm Atheros");
MODULE_DESCRIPTION("Core module for AR600x SDIO and USB devices.");
MODULE_LICENSE("Dual BSD/GPL");
