<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Mac80211 STA पूर्णांकerface क्रम ST-Ericsson CW1200 mac80211 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#अगर_अघोषित STA_H_INCLUDED
#घोषणा STA_H_INCLUDED

/* ******************************************************************** */
/* mac80211 API								*/

पूर्णांक cw1200_start(काष्ठा ieee80211_hw *dev);
व्योम cw1200_stop(काष्ठा ieee80211_hw *dev);
पूर्णांक cw1200_add_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
			 काष्ठा ieee80211_vअगर *vअगर);
व्योम cw1200_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
			     काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक cw1200_change_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
			    काष्ठा ieee80211_vअगर *vअगर,
			    क्रमागत nl80211_अगरtype new_type,
			    bool p2p);
पूर्णांक cw1200_config(काष्ठा ieee80211_hw *dev, u32 changed);
व्योम cw1200_configure_filter(काष्ठा ieee80211_hw *dev,
			     अचिन्हित पूर्णांक changed_flags,
			     अचिन्हित पूर्णांक *total_flags,
			     u64 multicast);
पूर्णांक cw1200_conf_tx(काष्ठा ieee80211_hw *dev, काष्ठा ieee80211_vअगर *vअगर,
		   u16 queue, स्थिर काष्ठा ieee80211_tx_queue_params *params);
पूर्णांक cw1200_get_stats(काष्ठा ieee80211_hw *dev,
		     काष्ठा ieee80211_low_level_stats *stats);
पूर्णांक cw1200_set_key(काष्ठा ieee80211_hw *dev, क्रमागत set_key_cmd cmd,
		   काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		   काष्ठा ieee80211_key_conf *key);

पूर्णांक cw1200_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value);

व्योम cw1200_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  u32 queues, bool drop);

u64 cw1200_prepare_multicast(काष्ठा ieee80211_hw *hw,
			     काष्ठा netdev_hw_addr_list *mc_list);

पूर्णांक cw1200_set_pm(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_set_pm *arg);

/* ******************************************************************** */
/* WSM callbacks							*/

व्योम cw1200_join_complete_cb(काष्ठा cw1200_common *priv,
				काष्ठा wsm_join_complete *arg);

/* ******************************************************************** */
/* WSM events								*/

व्योम cw1200_मुक्त_event_queue(काष्ठा cw1200_common *priv);
व्योम cw1200_event_handler(काष्ठा work_काष्ठा *work);
व्योम cw1200_bss_loss_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_bss_params_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_keep_alive_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_tx_failure_work(काष्ठा work_काष्ठा *work);

व्योम __cw1200_cqm_bssloss_sm(काष्ठा cw1200_common *priv, पूर्णांक init, पूर्णांक good,
			     पूर्णांक bad);
अटल अंतरभूत व्योम cw1200_cqm_bssloss_sm(काष्ठा cw1200_common *priv,
					 पूर्णांक init, पूर्णांक good, पूर्णांक bad)
अणु
	spin_lock(&priv->bss_loss_lock);
	__cw1200_cqm_bssloss_sm(priv, init, good, bad);
	spin_unlock(&priv->bss_loss_lock);
पूर्ण

/* ******************************************************************** */
/* Internal API								*/

पूर्णांक cw1200_setup_mac(काष्ठा cw1200_common *priv);
व्योम cw1200_join_समयout(काष्ठा work_काष्ठा *work);
व्योम cw1200_unjoin_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_join_complete_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_wep_key_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_update_listening(काष्ठा cw1200_common *priv, bool enabled);
व्योम cw1200_update_filtering(काष्ठा cw1200_common *priv);
व्योम cw1200_update_filtering_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_set_beacon_wakeup_period_work(काष्ठा work_काष्ठा *work);
पूर्णांक cw1200_enable_listening(काष्ठा cw1200_common *priv);
पूर्णांक cw1200_disable_listening(काष्ठा cw1200_common *priv);
पूर्णांक cw1200_set_uapsd_param(काष्ठा cw1200_common *priv,
				स्थिर काष्ठा wsm_edca_params *arg);
व्योम cw1200_ba_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_ba_समयr(अचिन्हित दीर्घ arg);

/* AP stuffs */
पूर्णांक cw1200_set_tim(काष्ठा ieee80211_hw *dev, काष्ठा ieee80211_sta *sta,
		   bool set);
पूर्णांक cw1200_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta);
पूर्णांक cw1200_sta_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा ieee80211_sta *sta);
व्योम cw1200_sta_notअगरy(काष्ठा ieee80211_hw *dev, काष्ठा ieee80211_vअगर *vअगर,
		       क्रमागत sta_notअगरy_cmd notअगरy_cmd,
		       काष्ठा ieee80211_sta *sta);
व्योम cw1200_bss_info_changed(काष्ठा ieee80211_hw *dev,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_bss_conf *info,
			     u32 changed);
पूर्णांक cw1200_ampdu_action(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_ampdu_params *params);

व्योम cw1200_suspend_resume(काष्ठा cw1200_common *priv,
			  काष्ठा wsm_suspend_resume *arg);
व्योम cw1200_set_tim_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_set_cts_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_multicast_start_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_multicast_stop_work(काष्ठा work_काष्ठा *work);
व्योम cw1200_mcast_समयout(काष्ठा समयr_list *t);

#पूर्ण_अगर
